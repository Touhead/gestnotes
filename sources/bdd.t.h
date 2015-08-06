#ifndef BDD_T_H
#define BDD_T_H

#include <bdd.h>

template <class T>
bool Bdd::updateUser(const int& id, const QString& field, const T& value){

    if (!bdd.isOpen())
        return false;

    query->prepare("UPDATE utilisateurs SET " + field + " = :value WHERE id = :id");
    query->bindValue(":value",value);
    query->bindValue(":id",id);

    return query->exec();
}

#endif // BDD_T_H
