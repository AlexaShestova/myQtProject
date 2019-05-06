#ifndef MYDATA_H
#define MYDATA_H
#include <QAbstractListModel>
#include <QString>
#include <QColor>
#include <QAbstractListModel>

class MyData : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int size READ getSize CONSTANT)
public:
    enum {
        IntRole = Qt::UserRole + 1,
       ColorRole
    };
    explicit MyData(int n, int m, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    QMap<int, QVariant> itemData(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;

//    void setData(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    int getSize() const;

    Q_INVOKABLE void addItem (int i, const QColor &c);
    Q_INVOKABLE void startGame();

    Q_INVOKABLE bool checkRect(int ind, bool isFirstPlayer);
    Q_INVOKABLE void process(int ind, bool isFirstPlayer);

signals:


public slots:

private:
    QList<int> m_intData;
    QList<QColor> m_colorData;
    QHash<int, QByteArray> m_roles;
    int M=5;
    int N=5;

    const QList<QString> m_colors={"yellow", "red", "green", "cyan", "magenta", "blue" };
    const QColor m_color1 = QColor(m_colors.at(0));
    const QColor m_color2 = QColor(m_colors.at(m_colors.size() - 1));

    bool checkPole(/*bool isFirstPlayer*/);

    QList<int> getAdjCells(int ind);
};

#endif // MYDATA_H
