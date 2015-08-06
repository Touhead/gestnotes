#ifndef MODELEMODULE_H
#define MODELEMODULE_H

#include <QSqlTableModel>

class ModeleModule : public QSqlTableModel
{
    Qt::ItemFlags flags(const QModelIndex& index) const;

public:
    ModeleModule(QSqlDatabase);
};

#endif // MODELEMODULE_H
