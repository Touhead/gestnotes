    #include "modelnotemodule.h"

ModelNoteModule::ModelNoteModule(const QString& mod, QObject *parent) : QSqlQueryModel(parent), module(mod)
{
    setQuery("SELECT M.id, nom, prenom, noteDE, noteCE, noteTP, notePRJ FROM utilisateurs AS U, " + module + " AS M WHERE U.id = M.id" + orderClause,QSqlDatabase::database("connectionModele"));
    sortKeyColumn = -1;
}

Qt::ItemFlags ModelNoteModule::flags(const QModelIndex& index) const{

    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() > 2 && index.column() < 7)
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool ModelNoteModule::setData(const QModelIndex& index, const QVariant& value, int /* role */){

    if (index.column() < 3 || index.column() > 6)
        return false;

    if ((value.toInt() < 0)||(value.toInt() > 20))
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(),0);
    int id = data(primaryKeyIndex).toInt();

    clear();

    bool ok;

    if (index.column() == 3){

        ok = setNoteDE(id, value.toString());
    }
    else if (index.column() == 4){

        ok = setNoteCE(id, value.toString());
    }
    else if (index.column() == 5){

        ok = setNoteTP(id, value.toString());
    }
    else{

        ok = setNotePRJ(id, value.toString());
    }

    refresh();
    return ok;
}

void ModelNoteModule::select(){

    clear();

    if(sortKeyColumn >= 0){

        orderClause = " ORDER BY " + QString::number(sortKeyColumn+1) + " " + ((sortOrder == Qt::AscendingOrder)? "ASC" : "DESC");
    }

    refresh();
}

void ModelNoteModule::setModule(const QString& mod){

    module = mod;
}

const QString& ModelNoteModule::getModule() const{

    return module;
}

void ModelNoteModule::refresh(){

    setQuery("SELECT M.id, nom, prenom, noteDE, noteCE, noteTP, notePRJ FROM utilisateurs AS U, " + module + " AS M WHERE U.id = M.id" + orderClause,QSqlDatabase::database("connectionModele"));
    setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    setHeaderData(3, Qt::Horizontal, QObject::tr("noteDE"));
    setHeaderData(4, Qt::Horizontal, QObject::tr("noteCE"));
    setHeaderData(5, Qt::Horizontal, QObject::tr("noteTP"));
    setHeaderData(6, Qt::Horizontal, QObject::tr("notePRJ"));
}

bool ModelNoteModule::setNoteDE(int id, const QString& note){

    QSqlQuery query(QSqlDatabase::database("connectionModele"));
    query.prepare("UPDATE " + module + " SET noteDE = :note WHERE id = :id");
    query.bindValue(":note",note);
    query.bindValue(":id",id);
    return query.exec();
}

bool ModelNoteModule::setNoteCE(int id, const QString& note){

    QSqlQuery query(QSqlDatabase::database("connectionModele"));
    query.prepare("UPDATE " + module + " SET noteCE = :note WHERE id = :id");
    query.bindValue(":note",note);
    query.bindValue(":id",id);
    return query.exec();
}

bool ModelNoteModule::setNoteTP(int id, const QString& note){

    QSqlQuery query(QSqlDatabase::database("connectionModele"));
    query.prepare("UPDATE " + module + " SET noteTP = :note WHERE id = :id");
    query.bindValue(":note",note);
    query.bindValue(":id",id);
    return query.exec();
}

bool ModelNoteModule::setNotePRJ(int id, const QString& note){

    QSqlQuery query(QSqlDatabase::database("connectionModele"));
    query.prepare("UPDATE " + module + " SET notePRJ = :note WHERE id = :id");
    query.bindValue(":note",note);
    query.bindValue(":id",id);
    return query.exec();
}

void ModelNoteModule::setSort(int column, Qt::SortOrder order)
{
    sortKeyColumn = column;
    sortOrder = order;
}

void ModelNoteModule::sort(int column, Qt::SortOrder order)
{
    if ((sortKeyColumn != column) || (sortOrder != order)) {
        setSort(column, order);
        select();
    }
}
