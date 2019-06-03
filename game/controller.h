#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mydata.h"
const QList<QString> LIST_COLORS={"yellow", "red", "green", "cyan", "magenta", "pink", "brown", "orange", "purple", "grey", "blue" };

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isFirstPlayer READ getIsFirstPlayer NOTIFY isFirstPlayerChanged)

    Q_PROPERTY(int countFirstColor READ getCountFirstColor NOTIFY countFirstColorChanged)
    Q_PROPERTY(int countSecondColor READ getCountSecondColor NOTIFY countSecondColorChanged)

    Q_PROPERTY(int numberPlayers WRITE setNumberPlayers)
public:
    Controller(MyData *myData, QObject *parent = nullptr);

    bool getIsFirstPlayer() const;

    int getCountFirstColor();
    int getCountSecondColor();

    void setNumberPlayers(int numberPlayers);

    Q_INVOKABLE void startGame();

    Q_INVOKABLE bool checkRect(int ind);
    Q_INVOKABLE void process(int ind);

    Q_INVOKABLE bool checkField();

    Q_INVOKABLE QList<int> getCountRect();

    Q_INVOKABLE bool loadGame( const QString & fileName );
    Q_INVOKABLE bool saveGame( const QString & fileName );


    Q_INVOKABLE QVariantMap getSettings();

    Q_INVOKABLE void setSettings(QString groupName, QVariantMap data);
    Q_INVOKABLE QStringList getAllColors();

signals:
    void isFirstPlayerChanged();
    void countFirstColorChanged();
    void countSecondColorChanged();

public slots:

private:
    MyData * m_myData;

    bool m_isFirstPlayer = true;

    //settings
    QString m_color1 = LIST_COLORS.at(0);
    QString m_color2 = LIST_COLORS.at(1);
    int m_numberColors = 2;

    //game mode
    int m_numberPlayers = 2;

    //
    void move();
};

#endif // CONTROLLER_H
