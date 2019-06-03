#include "mydata.h"
#include <QDebug>

MyData::MyData(int m, int n, QObject *parent) :
    QAbstractListModel(parent),
    m_rows(n),
    m_columns(m)
{
    m_roles.insert(IntRole, "IntData");
    m_roles.insert(ColorRole, "ColorData");

}

int MyData::rowCount(const QModelIndex &parent) const
{
    return m_intData.count();
}

QHash<int, QByteArray> MyData::roleNames() const
{
    return m_roles;
}

QVariant MyData::data(const QModelIndex &index, int role) const
{
    if(role == IntRole) {
        return m_intData.at(index.row());

    } else if(role == ColorRole) {
        return m_colorData.at(index.row());
    }

    return QVariant();
}

QMap<int, QVariant> MyData::itemData(const QModelIndex &index) const
{
    //    return
    QMap<int, QVariant> Data;
    Data.insert(IntRole, m_intData.at(index.row()));
    Data.insert(ColorRole, m_colorData.at(index.row()));

    return Data;
}

//bool MyData::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    // model.ColorData = "red"

//    if (!index.isValid()) {
//        return false;
//    }

//    switch (role) {
//    case ColorRole:
//        //            m_colorData[index.row()] = QColor(value.toString());
//        return false;   // This property can not be set
//    case IntRole:
//        //            m_intData.replace(index.row(), value.toInt()) ;
//        break;
//    default:
//        return false;
//    }

//    //        emit dataChanged(index, index/*, QVector<int>() << role*/);

//    return true;
//}

int MyData::getColumns() const
{
    return m_columns;
}

int MyData::getRows() const
{
    return m_rows;
}

void MyData::clearAll()
{
    m_intData.clear();
    m_colorData.clear();
}

void MyData::initializeData(QList<QString> listColors)
{
//    emit beginInsertRows(QModelIndex(), /*m_colorData.size()*/0, m_colorData.size());
    for(int i = 0; i < m_columns * m_rows; i++)
    {
        int randI = rand() % listColors.size();
        QColor c(listColors.at(randI));
        addItem(i, c);
    }
    QModelIndex index = createIndex(0,0);
    QModelIndex index_ = createIndex(m_columns * m_rows,0);
    emit dataChanged(index, index_, QVector<int>() << ColorRole);
//    emit endInsertRows();
}

void MyData::setCountColumnsRows(int newColumns, int newRows)
{
    clearAll();
    m_columns = newColumns;
    m_rows = newRows;
//    initializeData();
}

void MyData::replaceData(int ind, QColor newColor)
{
    m_colorData.replace(ind, newColor);

    QModelIndex index = createIndex(ind,0);
    emit dataChanged(index, index, QVector<int>() << ColorRole);
}

void MyData::addItem(int i, const QColor &c)
{
    m_intData.append(i);
    m_colorData.append(c);

    QModelIndex index = createIndex(i,0);
    emit dataChanged(index, index, QVector<int>() << ColorRole);
}

void MyData::process(int ind, QString strColorReplace)
{
    QColor c = m_colorData.at(ind);
    QColor cReplace(strColorReplace);
    m_colorData.replace(ind, cReplace);
    QList<int> adjCells = getAdjCells(ind);

    foreach(int a, adjCells)
    {
        if(m_colorData.at(a) == c)
            process(a, strColorReplace);
    }

    QModelIndex index = createIndex(ind,0);
    emit dataChanged(index, index, QVector<int>() << ColorRole);
}

//void MyData::startGame()
//{
//    m_intData.clear();
//    m_colorData.clear();
//    for(int i = 0; i < m_columns; i++)
//        for(int j = 0; j < m_rows; j++)
//        {
//            int randI = rand()%(m_colors.size()-2) + 1;
//            QColor c(m_colors.at(randI));
//            addItem(i*m_columns + j, c);
//        }

//    m_colorData.replace( 0, m_color1);
//    m_colorData.replace( 1, m_color1);
//    m_colorData.replace( m_columns, m_color1);
//    m_colorData.replace( m_columns*m_rows - 1, m_color2);
//    m_colorData.replace( m_columns*m_rows - 2, m_color2);
//    m_colorData.replace( (m_columns-1) * m_rows - 1, m_color2);
//}

bool MyData::checkColorData(int ind, const QString &strColor)
{
    return m_colorData.at(ind) == QColor(strColor);
}

bool MyData::checkField(const QString& strC1, const QString& strC2)
{
    bool result = false;
    QColor c1(strC1);
    QColor c2(strC2);
    for(int i = 0; i < m_columns*m_rows; i++)
    {
        QColor aC = m_colorData.at(i);
        if(aC == c1)
        {
            QList<int> adjCells = getAdjCells( i );

            foreach(int a, adjCells)
            {
                result = m_colorData.at(a) != c1 && m_colorData.at(a) != c2;
                if(result)
                    return result;
            }
        }
    }
    return result;
}

int MyData::getNumberRectColor(QString strColor)
{
    int result = 0;
    QColor  color(strColor);
    foreach(QColor c, m_colorData)
    {
        if(c == color) result++;
    }
    return result;
}

QString MyData::getColorsData()
{
    QString colorsData;

    foreach(QColor c, m_colorData)
    {
        QStringList l = c.colorNames();
        colorsData += c.name() + " ";
    }
    return colorsData;
}

QSet<int> MyData::getAvailableRect(const QString &strFirstColor, const QString &strSecondColor)
{
    QSet<int> res;
    QColor firstCol(strFirstColor);
    QColor secondCol(strSecondColor);
    for(int i = 0; i < m_columns*m_rows; i++)
    {
        QColor aC = m_colorData.at(i);
        if(aC == firstCol)
        {
            QList<int> adjCells = getAdjCells( i );

            foreach(int a, adjCells)
            {
                if(m_colorData.at(a) != firstCol && m_colorData.at(a) != secondCol)
                res.insert(a);
            }
        }
    }

    return res;

}

QList<int> MyData::getAdjCells(int ind)
{
    QList <int> adjCells;
    int i = ind / m_columns;
    int j = ind % m_columns;
    if( i - 1 >= 0 )
        adjCells.append( (i-1) * m_columns + j);
    if( i + 1 < m_rows )
        adjCells.append( (i+1) * m_columns + j);
    if( j-1 >= 0 )
        adjCells.append( (i) * m_columns + j-1);
    if( j+1 < m_columns )
        adjCells.append( (i) * m_columns + j+1);

    return adjCells;
}

//void MyData::checkRect(int ind/*, bool isFirstPlayer*/)
//{
//    if(isFirstPlayer)

//    else
//        return m_colorData.at(ind) != m_color1 && m_colorData.at(ind) != m_color2;
//}

//int MyData::getM()
//{
//    return m_columns;
//}
