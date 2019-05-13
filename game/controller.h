#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mydata.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isFirstPlayer READ getIsFirstPlayer)

    Q_PROPERTY(int size READ getSize CONSTANT)
public:
    Controller(MyData *myData, QObject *parent = nullptr);

    bool getIsFirstPlayer() const;
    int getSize() const;
    Q_INVOKABLE void startGame();

    Q_INVOKABLE bool checkRect(int ind);
    Q_INVOKABLE void process(int ind);

    Q_INVOKABLE bool checkPole();

private:
    MyData * m_myData;

    bool m_isFirstPlayer = true;

    //settings
    /*const*/ QList<QString> m_colors={"yellow", "red", "green", "cyan", "magenta", "blue" };
    const QColor m_color1 = QColor(m_colors.at(0));
    const QColor m_color2 = QColor(m_colors.at(m_colors.size() - 1));
    int numberColors = 4;
};

#endif // CONTROLLER_H
