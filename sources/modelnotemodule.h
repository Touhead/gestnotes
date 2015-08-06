#ifndef MODELNOTEMODULE_H
#define MODELNOTEMODULE_H

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>

class ModelNoteModule : public QSqlQueryModel
{
    Q_OBJECT

public:
    ModelNoteModule(const QString&, QObject* = 0);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &, const QVariant &, int);
    void setModule(const QString&);
    const QString& getModule() const;

public slots:

    void select();
    void setSort(int column, Qt::SortOrder order);
    void sort(int column, Qt::SortOrder order);

private:
    bool setNoteDE(int, const QString &);
    bool setNoteCE(int, const QString &);
    bool setNoteTP(int, const QString &);
    bool setNotePRJ(int, const QString &);
    void refresh();

    QString module;

    QString orderClause;
    int sortKeyColumn;
    Qt::SortOrder sortOrder;
};

#endif // MODELNOTEMODULE_H
