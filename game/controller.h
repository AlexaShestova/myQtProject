#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mydata.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isFirstPlayer READ getIsFirstPlayer NOTIFY isFirsPlayerChanged)

    Q_PROPERTY(int size READ getSize CONSTANT)

    Q_PROPERTY(int countFirstColor READ getCountFirstColor NOTIFY countFirstColorChanged)
    Q_PROPERTY(int countSecondColor READ getCountSecondColor NOTIFY countSecondColorChanged)
public:
    Controller(MyData *myData, QObject *parent = nullptr);

    bool getIsFirstPlayer() const;
    int getSize() const;

    int getCountFirstColor();
    int getCountSecondColor();

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
    void isFirsPlayerChanged();
    void countFirstColorChanged();
    void countSecondColorChanged();

public slots:

private:
    MyData * m_myData;

    bool m_isFirstPlayer = true;

    //settings
    const QList<QString> m_colors={"yellow", "red", "green", "cyan", "magenta", "pink", "brown", "orange", "purple", "grey", "blue" };
    QString m_color1 = m_colors.at(0);
    QString m_color2 = m_colors.at(1);
    int m_numberColors = 2;

    //game mode
    int m_numberPlayers = 1;

    //
    void move();
};

#endif // CONTROLLER_H
