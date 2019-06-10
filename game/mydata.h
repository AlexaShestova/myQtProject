#ifndef MYDATA_H
#define MYDATA_H
#include <QAbstractListModel>
#include <QString>
#include <QColor>
#include <QAbstractListModel>
#include <QJsonObject>

class MyData : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int columns READ getColumns NOTIFY columnsChanged)
    Q_PROPERTY(int rows READ getRows NOTIFY rowsChanged)

public:
    enum {
        IntRole = Qt::UserRole + 1,
       ColorRole
    };
    explicit MyData(int columns, int rows, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    QMap<int, QVariant> itemData(const QModelIndex &index) const Q_DECL_OVERRIDE;
//    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;

//    void setData(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
//    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;
//    bool removeRows(int position, int rows, const QModelIndex &parent) Q_DECL_OVERRIDE;

    int getColumns() const;
    int getRows() const;

    void clearAll();
    void initializeData(QList<QString> listColors);
    void setCountColumnsRows(int newColumns, int newRows);
    void replaceData(int ind, QColor newColor);
    /*Q_INVOKABLE*/ void addItem (int i, const QColor &c);
    void process(int ind, QString strColorReplace, int h);
    void updateData(QJsonObject &obj);

    int getTreeHeight(int v, int h);

    bool checkColorData(int ind, const QString &strColor) const;
    bool checkField(const QString &strC1, const QString &strC2/*bool isFirstPlayer*/);

    int getNumberRectColor(QString strColor) const;

    QString getColorsData();
    QSet<int> getAvailableRect(const QString &strFirstColor, const QString &strSecondColor);
    QList<int> getAdjacentCells(int ind);
signals:
    void columnsChanged();
    void rowsChanged();

public slots:

private:
    QList<int> m_intData;
    QList<QColor> m_colorData;
    QHash<int, QByteArray> m_roles;
    int m_columns;
    int m_rows;

    void initializeIntData();
};

#endif // MYDATA_H
