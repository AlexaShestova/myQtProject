#include "controller.h"

#include <QFile>
#include <QDebug>
#include <QGuiApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileInfo>
#include <QDir>

Controller::Controller(MyData *myData, QObject *parent):
    m_myData(myData),
    QObject (parent)
{
    m_listSize.append( qMakePair(5, 10) );
    m_listSize.append( qMakePair(10, 10) );
    m_listSize.append( qMakePair(15, 15) );
    m_listSize.append( qMakePair(20, 20) );

}

bool Controller::getIsFirstPlayer() const
{
    return m_isFirstPlayer;
}

QColor Controller::getFirstColor() const
{
    return QColor(m_color1);
}

QColor Controller::getSecondColor() const
{
    return QColor(m_color2);
}

//void Controller::startGame()
//{
//    m_isFirstPlayer = true;
//    emit isFirstPlayerChanged();
//    m_myData->setCountColumnsRows(m_listSize.at(m_fieldSize).first, m_listSize.at(m_fieldSize).second);
//    m_myData->clearAll();
//    for(int i = 0; i < m_myData->getColumns() * m_myData->getRows(); i++)
//        //        for(int j = 0; j < N; j++)
//    {
//        int randI = rand() % (m_numberColors + 2);


//        while( LIST_COLORS.at(randI) == m_color1 || LIST_COLORS.at(randI) == m_color2 )
//        {
//            randI = rand() % (m_numberColors + 2);

//        }
//        QColor c(LIST_COLORS.at(randI));
//        m_myData->addItem(i, c);
//    }

//    m_myData->replaceData( 0, QColor( m_color1 ));
//    m_myData->replaceData( 1, QColor( m_color1 ));
//    m_myData->replaceData( m_myData->getColumns(), QColor( m_color1 ));
//    m_myData->replaceData( m_myData->getColumns()*m_myData->getRows() - 1, QColor( m_color2 ));
//    m_myData->replaceData( m_myData->getColumns()*m_myData->getRows() - 2, QColor( m_color2 ));
//    m_myData->replaceData( (m_myData->getRows()-1) * m_myData->getColumns() - 1, QColor( m_color2 ));

//    emit countFirstColorChanged();
//    emit countSecondColorChanged();
//}

void Controller::startGame()
{
    m_isFirstPlayer = true;
    emit isFirstPlayerChanged();
    QList<QString> listColors;
    int countColumns = m_listSize.at(m_fieldSize).first;
    int countRows = m_listSize.at(m_fieldSize).second;
    m_myData->setCountColumnsRows( countColumns, countRows);

    for(int i = 0, j = 0; j < LIST_COLORS.size() && i < m_numberColors; j++)
    {
        if( LIST_COLORS.at(j) != m_color1 && LIST_COLORS.at(j) != m_color2 )
        {
            listColors.append(LIST_COLORS.at(j));
            i++;
        }
    }
    m_myData->initializeData(listColors);
    m_myData->replaceData( 0, QColor( m_color1 ));
    m_myData->replaceData( 1, QColor( m_color1 ));
    m_myData->replaceData( countColumns, QColor( m_color1 ));
    m_myData->replaceData( countColumns * countRows - 1, QColor( m_color2 ));
    m_myData->replaceData( countColumns * countRows - 2, QColor( m_color2 ));
    m_myData->replaceData( (countRows - 1) * countColumns - 1, QColor( m_color2 ));

    emit countFirstColorChanged();
    emit countSecondColorChanged();
}

bool Controller::checkRect(int ind) const
{
    bool result = false;
    if( !m_myData->checkColorData(ind, m_color1) && !m_myData->checkColorData(ind, m_color2))
    {

        QList<int> adjCells = m_myData->getAdjacentCells(ind);
        if(m_isFirstPlayer)
        {

            foreach(int a, adjCells)
                result = result || (m_myData->checkColorData(a, m_color1));
        }
        else
        {
            foreach(int a, adjCells)
                result = result || (m_myData->checkColorData(a, m_color2));
        }
    }
    return result;

}

void Controller::move(int ind)
{
    if(m_isFirstPlayer)
    {
        m_myData->process(ind, m_color1, 1);

        emit countFirstColorChanged();
    }
    else
    {
        m_myData->process(ind, m_color2, 1);

        emit countSecondColorChanged();
    }

    if(m_numberPlayers == 1)
    {
        computerMove();
    }
    else
    {
        m_isFirstPlayer = !m_isFirstPlayer;
        emit isFirstPlayerChanged();
    }
}

bool Controller::checkField() const
{
    bool result = true;

    result = m_myData->checkField(m_color1, m_color2);
    result = result && m_myData->checkField(m_color2, m_color1);

    return result;
}

QList<int> Controller::getCountRect() const
{
    return QList<int> () << m_myData->getNumberRectColor(m_color1) << m_myData->getNumberRectColor(m_color2);

}

bool Controller::loadGame(QString fileName)
{
    bool result = false;

    QFileInfo fileInfo(fileName);
    QDir::setCurrent(fileInfo.path());
    QFile file(fileName);
    if( file.open( QIODevice::ReadOnly ) )
    {
        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        QJsonObject obj(doc.object());

        m_myData->updateData(obj);

        m_isFirstPlayer = obj.value("isFirstPlayer").toBool();
        m_color1 = obj.value("color1").toString();
        m_color2 = obj.value("color2").toString();
        m_numberPlayers = obj.value("numberPlayers").toInt();
        m_level = obj.value("level").toInt();
        emit isFirstPlayerChanged();
        emit countFirstColorChanged();
        emit countSecondColorChanged();
        emit firstColorChanged();
        emit secondColorChanged();
        file.close();
        qDebug() << "load game : fullFileName : " << fileName;
        result = true;
    }
    else
    {
        qWarning() << "load game : error open file : " << fileName;
    }
    return result;
}

bool Controller::saveGame(const QString &fileName)
{
    QString fullFileName = QGuiApplication::applicationDirPath() + "/" + fileName;

    return saveGameAs(fullFileName);
}

bool Controller::saveGameAs(const QString &fullFileName)
{
    bool result = false;
    QJsonObject obj;
    obj["columns"] = m_myData->getColumns();
    obj["rows"] = m_myData->getRows();
    obj.insert("colorsData", m_myData->getColorsData());
    obj["isFirstPlayer"] = m_isFirstPlayer;
    obj["numberPlayers"] = m_numberPlayers;
    obj["color1"] = m_color1;
    obj["color2"] = m_color2;
    obj["level"] = m_level;
    /////////////////////////////////////////////////////////////

    QFile file( fullFileName );
    QFileInfo fileInfo(file);
    QDir::setCurrent(fileInfo.path());
    if( file.open( QIODevice::WriteOnly ) )
    {

        file.write( QJsonDocument(obj).toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "save game : saved game : fullFileName : " << fullFileName;
        result = true;
    }
    else
    {
        qWarning() << "save game : error open file : " << fullFileName;
    }

    return result;
}


QVariantMap Controller::getSettings() const
{
    QVariantMap settingsMap;
    QVariantMap settingsColors;
    settingsColors.insert("numberColors", m_numberColors);
    settingsColors.insert("firstColor", m_color1);
    settingsColors.insert("secondColor", m_color2);
    settingsMap.insert("Colors", settingsColors);

    QVariantMap settingsField;
    settingsField.insert("fieldSize", m_fieldSize);
    settingsField.insert("level", m_level);
    settingsMap.insert("Field", settingsField);

    qDebug()<<settingsMap;
    return settingsMap;

}

void Controller::setSettings(QString groupName, QVariantMap data)
{
    if(groupName == "Colors")
    {
        QString key;
        QMapIterator<QString, QVariant> iterator( data );
        while( iterator.hasNext() )
        {
            iterator.next();
            key = iterator.key().trimmed();
            if( !key.isEmpty() && !iterator.value().isNull() )
            {
                if(key == "numberColors")
                    m_numberColors = iterator.value().toInt();
                else if(key == "firstColor")
                    m_color1 = iterator.value().toString();
                else if(key == "secondColor")
                    m_color2 = iterator.value().toString();
            }

        }
    }
    if(groupName == "Field")
    {
        QString key;
        QMapIterator<QString, QVariant> iterator( data );
        while( iterator.hasNext() )
        {
            iterator.next();
            key = iterator.key().trimmed();
            if( !key.isEmpty() && !iterator.value().isNull() )
            {
                if(key == "fieldSize")
                    m_fieldSize = iterator.value().toInt();
                else if(key == "level")
                    m_level = iterator.value().toInt();
            }
        }
    }
}

QStringList Controller::getAllColors() const
{
    return LIST_COLORS;
}

void Controller::computerMove()
{
    QSet<int> rect = m_myData->getAvailableRect(m_color2, m_color1);
    int randI = 0;
    if(m_level == 1)
    {
     randI = rand()% rect.size();
    }
    else
    {
        for(int i = 0; i < rect.size(); i++ )
        {
            int h = m_myData->getTreeHeight(rect.toList().at(i),0);
            if(h > m_level)
            {
                randI = i;
                break;
            }
        }
    }
    m_myData->process(rect.toList().at(randI), m_color2, 1);

    emit countSecondColorChanged();
}

int Controller::getCountFirstColor() const
{
    return m_myData->getNumberRectColor( m_color1 );
}

int Controller::getCountSecondColor() const
{
    return m_myData->getNumberRectColor( m_color2 );
}

void Controller::setNumberPlayers(int numberPlayers)
{
    if( numberPlayers == 1 || numberPlayers == 2)
        m_numberPlayers = numberPlayers;
    else {
        qWarning() << "Controller : invalid parameters : numberPlayers = " << numberPlayers;
        return; // ERROR
    }
}
