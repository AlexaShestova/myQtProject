#include "mydata.h"
#include <QDebug>

MyData::MyData(int m, int n, QObject *parent) :
    QAbstractListModel(parent),
    N(n),
    M(m)
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

bool MyData::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // model.ColorData = "red"

    if (!index.isValid()) {
        return false;
    }

    switch (role) {
    case ColorRole:
        //            m_colorData[index.row()] = QColor(value.toString());
        return false;   // This property can not be set
    case IntRole:
        //            m_intData.replace(index.row(), value.toInt()) ;
        break;
    default:
        return false;
    }

    //        emit dataChanged(index, index/*, QVector<int>() << role*/);

    return true;
}

int MyData::getColumns() const
{
    return M;
}

int MyData::getRows() const
{
    return N;
}

void MyData::clearAll()
{
    m_intData.clear();
    m_colorData.clear();
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

void MyData::process(int ind, QColor cReplace)
{
    QColor c = m_colorData.at(ind);
    m_colorData.replace(ind, cReplace);
    QList<int> adjCells = getAdjCells(ind);

    foreach(int a, adjCells)
    {
        if(m_colorData.at(a) == c)
            process(a, cReplace);
    }

    QModelIndex index = createIndex(ind,0);
    emit dataChanged(index, index, QVector<int>() << ColorRole);
}

//void MyData::startGame()
//{
//    m_intData.clear();
//    m_colorData.clear();
//    for(int i = 0; i < M; i++)
//        for(int j = 0; j < N; j++)
//        {
//            int randI = rand()%(m_colors.size()-2) + 1;
//            QColor c(m_colors.at(randI));
//            addItem(i*M + j, c);
//        }

//    m_colorData.replace( 0, m_color1);
//    m_colorData.replace( 1, m_color1);
//    m_colorData.replace( M, m_color1);
//    m_colorData.replace( M*N - 1, m_color2);
//    m_colorData.replace( M*N - 2, m_color2);
//    m_colorData.replace( (M-1) * N - 1, m_color2);
//}

bool MyData::checkColorData(int ind, QColor color)
{
    return m_colorData.at(ind) == color;
}

bool MyData::checkPole(QColor c1, QColor c2) // если хоть одна доступная клетка ??
{
    bool result = false;
    //   foreach(QColor aC, m_colorData)
    for(int i = 0; i < M*N; i++)
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

int MyData::getNumberRectColor(QColor color)
{
    int result = 0;
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

QList<int> MyData::getAdjCells(int ind)
{
    QList <int> adjCells;
    int i = ind / M;
    int j = ind % M;
    if( i - 1 >= 0 )
        adjCells.append( (i-1) * M + j);
    if( i + 1 < N )
        adjCells.append( (i+1) * M + j);
    if( j-1 >= 0 )
        adjCells.append( (i) * M + j-1);
    if( j+1 < M )
        adjCells.append( (i) * M + j+1);

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
//    return M;
//}
