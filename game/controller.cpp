#include "controller.h"

#include <QFile>
#include <QDebug>
#include <QGuiApplication>
#include <QJsonObject>
#include <QJsonDocument>

Controller::Controller(MyData *myData, QObject *parent):
    m_myData(myData),
    QObject (parent)
{

}

int Controller::getSize() const
{
    return 5;
}

bool Controller::getIsFirstPlayer() const
{
    return m_isFirstPlayer;
}

void Controller::startGame()
{
    m_isFirstPlayer = true;
    emit isFirsPlayerChanged();
    m_myData->clearAll();
    for(int i = 0; i < m_myData->getColumns() * m_myData->getRows(); i++)
        //        for(int j = 0; j < N; j++)
    {
        int randI = rand() % (m_numberColors + 2);


        while( m_colors.at(randI) == m_color1 || m_colors.at(randI) == m_color2 )
        {
            randI = rand() % (m_numberColors + 2);

        }
        QColor c(m_colors.at(randI));
        m_myData->addItem(i, c);
    }

    m_myData->replaceData( 0, QColor( m_color1 ));
    m_myData->replaceData( 1, QColor( m_color1 ));
    m_myData->replaceData( m_myData->getColumns(), QColor( m_color1 ));
    m_myData->replaceData( m_myData->getColumns()*m_myData->getRows() - 1, QColor( m_color2 ));
    m_myData->replaceData( m_myData->getColumns()*m_myData->getRows() - 2, QColor( m_color2 ));
    m_myData->replaceData( (m_myData->getRows()-1) * m_myData->getColumns() - 1, QColor( m_color2 ));
}

bool Controller::checkRect(int ind)
{
    bool result = false;
    if( !m_myData->checkColorData(ind, m_color1) && !m_myData->checkColorData(ind, m_color2))
    {

        QList<int> adjCells = m_myData->getAdjCells(ind);
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

void Controller::process(int ind)
{
    if(m_isFirstPlayer)
    {
        m_myData->process(ind, m_color1);

        emit countFirstColorChanged();
    }
    else
    {
        m_myData->process(ind, m_color2);

        emit countSecondColorChanged();
    }

    m_isFirstPlayer = !m_isFirstPlayer;
    emit isFirsPlayerChanged();
}

bool Controller::checkPole()
{
    bool result = true;
    if(m_isFirstPlayer)
        result = m_myData->checkPole(m_color1, m_color2);
    else
    {
        result = m_myData->checkPole(m_color2, m_color1);
    }
    return result;
}

QList<int> Controller::getCountRect()
{
    return QList<int> () << m_myData->getNumberRectColor(m_color1) << m_myData->getNumberRectColor(m_color2);

}

bool Controller::loadGame(const QString &fileName)
{

}

bool Controller::saveGame(const QString &fileName)
{
    bool result = false;
    QString fullFileName = QGuiApplication::applicationDirPath() + "/" + fileName;
//    QJsonDocument jsonFile;// = QJsonDocument();
//    QJsonArray dataArray;
//    dataArray.append(QJsonValue())
    QJsonObject obj;// = new QJsonObject();
    obj["M"] = m_myData->getColumns();
    obj["N"] = m_myData->getRows();
    obj["colorsData"] = m_myData->getColorsData();
    obj["isFirstPlayer"] = m_isFirstPlayer;
    obj["numberPlayers"] = m_numberPlayers;


    /////////////////////////////////////////////////////////////

    QFile file( fullFileName );
    if( file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )
    {
        file.write( QJsonDocument(obj).toBinaryData());
        file.close();
        result = true;
    }
    else
    {
        qWarning() << "save game : error open file : " << fullFileName;
    }

    return result;
}

QVariantMap Controller::getSettings()
{
    QVariantMap settingsMap;
    QVariantMap settingsColors;
    settingsColors.insert("numberColors", m_numberColors);
    settingsColors.insert("firstColor", m_color1);
    settingsColors.insert("secondColor", m_color2);
    settingsMap.insert("Colors", settingsColors);

        qDebug()<<settingsMap;
    return settingsMap;

}

void Controller::setSettings(QString groupName, QVariantMap data)
{
//    if(numberColors < m_colors.size())

    if(groupName == "Colors")
    {
        QString key;
        QMapIterator<QString, QVariant> iterator( data );
        while( iterator.hasNext() )
        {
            iterator.next();
            key = iterator.key().trimmed();
            if( !key.isEmpty() && !iterator.value().isNull() )
                if(key == "numberColors")
                    m_numberColors = iterator.value().toInt();
                else if(key == "firstColor")
                    m_color1 = iterator.value().toString();
                else if(key == "secondColor")
                    m_color2 = iterator.value().toString();

        }
    }

}

QStringList Controller::getAllColors(int i)
{
    QStringList result;
    QString playerColor ;
    if(i == 1)
        playerColor = m_color1;
    else if( i== 2)
        playerColor = m_color2;
    else {
        return result;
    }
    for(int i=0; i < m_colors.size(); i++ )
        if(m_colors.at(i) != playerColor)
            result.append( m_colors.at(i) );

    return result;
}

int Controller::getCountFirstColor()
{
    return m_myData->getNumberRectColor( m_color1 );
}

int Controller::getCountSecondColor()
{
    return m_myData->getNumberRectColor( m_color2 );
}
