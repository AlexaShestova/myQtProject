#ifndef MYDATA_H
#define MYDATA_H
#include <QAbstractListModel>
#include <QString>
#include <QColor>
#include <QAbstractListModel>

class MyData : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int columns READ getColumns CONSTANT)
    Q_PROPERTY(int rows READ getRows CONSTANT)

public:
    enum {
        IntRole = Qt::UserRole + 1,
       ColorRole
    };
    explicit MyData(int m, int n, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    QMap<int, QVariant> itemData(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;

//    void setData(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    int getColumns() const;
    int getRows() const;

    void clearAll();
    void replaceData(int ind, QColor newColor);
    /*Q_INVOKABLE*/ void addItem (int i, const QColor &c);
    void process(int ind, QString strColorReplace);

    QList<int> getAdjCells(int ind);

    bool checkColorData(int ind, const QString &strColor);
    bool checkField(const QString &strC1, const QString &strC2/*bool isFirstPlayer*/);

    int getNumberRectColor(QString strColor);

    QString getColorsData();
    QSet<int> getAvailableRect(const QString &strFirstColor, const QString &strSecondColor);
signals:


public slots:

private:
    QList<int> m_intData;
    QList<QColor> m_colorData;
    QHash<int, QByteArray> m_roles;
    int M=5;
    int N=5;

};

#endif // MYDATA_H
