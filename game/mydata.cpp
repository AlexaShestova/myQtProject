#include "mydata.h"
#include <QDebug>

MyData::MyData(int n, int m, QObject *parent) :
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

int MyData::getSize() const
{
    return M;
}

void MyData::addItem(int i, const QColor &c)
{
    m_intData.append(i);
    m_colorData.append(c);
}

void MyData::startGame()
{
    m_intData.clear();
    m_colorData.clear();
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
        {
            int randI = rand()%(m_colors.size()-2) + 1;
            QColor c(m_colors.at(randI));
            addItem(i*M + j, c);
        }

    m_colorData.replace( 0, m_color1);
    m_colorData.replace( 1, m_color1);
    m_colorData.replace( M, m_color1);
    m_colorData.replace( M*N - 1, m_color2);
    m_colorData.replace( M*N - 2, m_color2);
    m_colorData.replace( (M-1) * N - 1, m_color2);
}

bool MyData::checkRect(int ind, bool isFirstPlayer)
{
    bool result = false;
    if( m_colorData.at(ind) != m_color1 && m_colorData.at(ind) != m_color2)
    {

        QList<int> adjCells = getAdjCells(ind);
        if(isFirstPlayer)
        {
            foreach(int a, adjCells)
                result = result || (m_colorData.at(a) == m_color1);
        }
        else
        {
            foreach(int a, adjCells)
                result = result || (m_colorData.at(a) == m_color2);
        }
    }
    return result;
}

void MyData::process(int ind, bool isFirstPlayer)
{
    QColor color = m_colorData.at(ind);
    if(isFirstPlayer)
    {
        m_colorData.replace(ind, m_color1);
        QList<int> adjCells = getAdjCells(ind);

        foreach(int a, adjCells)
        {
            if(m_colorData.at(a) == color)
                process(a, isFirstPlayer);
        }
    }
    else
    {
        m_colorData.replace(ind, m_color2);
        QList<int> adjCells = getAdjCells(ind);
        foreach(int a, adjCells)
        {
            if(m_colorData.at(a) == color)
                process(a, isFirstPlayer);
                //m_colorData.replace(a, m_color1);
        }
    }
    QModelIndex index = createIndex(ind,0);
    emit dataChanged(index, index, QVector<int>() << ColorRole);
}

bool MyData::checkPole() // если хоть одна доступная клетка ??
{
   bool result = false;
   foreach(QColor c, m_colorData)
   {
       result = c != m_color1 && c != m_color2;
       if(result)
           break;
   }
    return result;
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
    if( j+1 < N )
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
