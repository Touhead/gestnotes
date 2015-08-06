#include "modelemodule.h"

ModeleModule::ModeleModule(QSqlDatabase bdd)
    : QSqlTableModel(0,bdd)
{
}

Qt::ItemFlags ModeleModule::flags(const QModelIndex& index) const{

    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() > 2 && index.column() < 7)
        flags |= Qt::ItemIsEditable;
    return flags;
}
