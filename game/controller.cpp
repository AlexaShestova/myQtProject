#include "controller.h"


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
    m_myData->clearAll();
    for(int i = 0; i < m_myData->getSize() * m_myData->getSize(); i++)
        //        for(int j = 0; j < N; j++)
    {
        int randI = rand()%(m_colors.size()-2) + 1;
        QColor c(m_colors.at(randI));
        m_myData->addItem(i, c);
    }

    m_myData->replaceData( 0, m_color1);
    m_myData->replaceData( 1, m_color1);
    m_myData->replaceData( m_myData->getSize(), m_color1);
    m_myData->replaceData( m_myData->getSize()*m_myData->getSize() - 1, m_color2);
    m_myData->replaceData( m_myData->getSize()*m_myData->getSize() - 2, m_color2);
    m_myData->replaceData( (m_myData->getSize()-1) * m_myData->getSize() - 1, m_color2);
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
    }
    else
    {
        m_myData->process(ind, m_color2);
    }

    m_isFirstPlayer = !m_isFirstPlayer;
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
