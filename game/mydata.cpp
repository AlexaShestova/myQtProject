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
    if( m_colorData.at(ind) != m_color1 && m_colorData.at(ind) != m_color2)
    {
        int i = ind / M;
        int j = ind % M;
        int a = (i-1) * M + j;
        int b = (i+1) * M + j;
        int c = (i) * M + j-1;
        int d = (i) * M + j+1;
        qDebug() << (i-1) * M + j << (i+1) * M + j <<  (i) * M + j-1 << (i) * M + j+1;
        if(isFirstPlayer)
            return ((a >= 0 && a < m_colorData.size() && m_colorData.at(a) == m_color1) ||
                    (b >= 0 && b < m_colorData.size() && m_colorData.at(b) == m_color1) ||
                    (c >= 0 && c < m_colorData.size() && m_colorData.at(c) == m_color1) ||
                    (d >= 0 && d < m_colorData.size() && m_colorData.at(d) == m_color1) );
        else
            return ((a >= 0 && a < m_colorData.size() && m_colorData.at(a) == m_color2) ||
                    (b >= 0 && b < m_colorData.size() && m_colorData.at(b) == m_color2) ||
                    (c >= 0 && c < m_colorData.size() && m_colorData.at(c) == m_color2) ||
                    (d >= 0 && d < m_colorData.size() && m_colorData.at(d) == m_color2) );
    }
    return false;
}

void MyData::xod(int ind, bool isFirstPlayer)
{
    if(isFirstPlayer)
        m_colorData.replace(ind, m_color1);
    else
        m_colorData.replace(ind, m_color2);

}

void MyData::checkPole(bool isFirstPlayer)
{

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
