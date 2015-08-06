#include "sqlquerymodeloptimized.h"

SqlQueryModelOptimized::SqlQueryModelOptimized(QObject *parent) :
    QSqlQueryModel(parent)
{
}

void SqlQueryModelOptimized::setQuery(const QString& query){

    queryClause = query;
    sortKeyColumn = -1;
    sortOrder = Qt::AscendingOrder;
}

void SqlQueryModelOptimized::select(){

    clear();

    if(sortKeyColumn >= 0){

        orderClause = " ORDER BY " + QString::number(sortKeyColumn+1) + " " + ((sortOrder == Qt::AscendingOrder)? "ASC" : "DESC");
    }

    refresh();
}

void SqlQueryModelOptimized::setSort(int column, Qt::SortOrder order)
{
    sortKeyColumn = column;
    sortOrder = order;
}

void SqlQueryModelOptimized::sort(int column, Qt::SortOrder order)
{
    if ((sortKeyColumn != column) || (sortOrder != order)) {
        setSort(column, order);
        select();
    }
}

void SqlQueryModelOptimized::refresh(){

    QSqlQueryModel::setQuery(queryClause + orderClause,QSqlDatabase::database("connectionModele"));
}
