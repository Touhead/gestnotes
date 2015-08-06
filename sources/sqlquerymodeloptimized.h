#ifndef SQLQUERYMODELOPTIMIZED_H
#define SQLQUERYMODELOPTIMIZED_H

#include <QSqlQueryModel>

class SqlQueryModelOptimized : public QSqlQueryModel
{
    Q_OBJECT

public:
    SqlQueryModelOptimized(QObject* = 0);
    void setQuery(const QString&);

public slots:

    void select();
    void setSort(int column, Qt::SortOrder order);
    void sort(int column, Qt::SortOrder order);

private:

    void refresh();

    QString queryClause;
    QString orderClause;
    int sortKeyColumn;
    Qt::SortOrder sortOrder;
};

#endif // SQLQUERYMODELOPTIMIZED_H
