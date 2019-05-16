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
    void process(int ind, QColor cReplace);

    QList<int> getAdjCells(int ind);

    bool checkColorData(int ind, QColor color);
    bool checkPole(QColor c1, QColor c2/*bool isFirstPlayer*/);

    int getNumberRectColor(QColor color);

    QString getColorsData();

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
