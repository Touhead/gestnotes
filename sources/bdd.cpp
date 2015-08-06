#include "bdd.h"
#include <QTextCodec>

Bdd::Bdd(const QString& host, const QString& user, const QString& password, const QString& dataBase, const QString& connectionName)
{
    bdd = QSqlDatabase::addDatabase("QMYSQL",connectionName);
    bdd.setHostName(host);
    bdd.setUserName(user);
    bdd.setPassword(password);
    bdd.setDatabaseName(dataBase);
    bdd.setPort(3306);

    query = new QSqlQuery(bdd);
}

Bdd::~Bdd()
{
    delete query;
}

bool Bdd::open(){

    return bdd.open();
}

void Bdd::close(){

    bdd.close();
}

bool Bdd::addUser(const int& id, const QString& nom, const QString& prenom, const QString& dateNaissance, const QString& adresse, const QString& telephone){

    if (!bdd.isOpen())
        return false;

    query->prepare("INSERT INTO utilisateurs (id,nom,prenom,dateNaissance,adresse,telephone) VALUES (:id,:nom,:prenom,:dateNaissance,:adresse,:telephone)");
    query->bindValue(":id",id);
    query->bindValue(":nom",nom);
    query->bindValue(":prenom",prenom);
    query->bindValue(":dateNaissance",dateNaissance);
    query->bindValue(":adresse",adresse);
    query->bindValue(":telephone",telephone);

    return query->exec();
}

QStringList* Bdd::getFieldUser(const QString& field){

    if (!bdd.isOpen())
        return 0;

    query->prepare("SELECT " + field + " FROM utilisateurs");

    if(!query->exec())
        return 0;

    QStringList* list = new QStringList;

    while (query->next()){

        list->push_back(query->value(0).toString());
    }

    return list;
}

QHash<QString, QStringList*>* Bdd::getUser(){

    if (!bdd.isOpen())
        return 0;

    if(!query->exec("SELECT * FROM utilisateurs"))
        return 0;

    QHash<QString, QStringList*>* hash = new QHash<QString, QStringList*>;
    QSqlRecord record = query->record();

    for(int cpt=0; cpt<record.count(); cpt++){

        (*hash)[record.fieldName(cpt)] = new QStringList;
    }

    while(query->next()){

        for(int cpt=0; cpt<record.count(); cpt++){

            (*hash)[record.fieldName(cpt)]->push_back(query->value(cpt).toString());
        }
    }

    return hash;
}

QAbstractTableModel* Bdd::getModeleUtilisateur(){

    SqlQueryModelOptimized* modele = new SqlQueryModelOptimized;

    modele->setQuery("SELECT id, nom, prenom, dateNaissance, adresse, telephone FROM utilisateurs");

    return modele;
}

QAbstractTableModel* Bdd::getModeleEleve(){

    SqlQueryModelOptimized* modele = new SqlQueryModelOptimized;

    modele->setQuery("SELECT E.id, nom, prenom, promotion, specialite, dateNaissance, adresse, telephone FROM utilisateurs U, eleves E WHERE U.id = E.id");

    return modele;
}

QAbstractTableModel* Bdd::getModeleProfesseur(){

    SqlQueryModelOptimized* modele = new SqlQueryModelOptimized;

    modele->setQuery("SELECT P.id, nom, prenom, dateNaissance, adresse, telephone FROM utilisateurs U, professeurs P WHERE U.id = P.id");

    return modele;
}

QAbstractTableModel* Bdd::getModeleAdministration(){

    SqlQueryModelOptimized* modele = new SqlQueryModelOptimized;

    modele->setQuery("SELECT A.id, nom, prenom, dateNaissance, adresse, telephone FROM utilisateurs U, administration A WHERE U.id = A.id");

    return modele;
}

QAbstractTableModel* Bdd::getModeleSpecialite(){

    SqlQueryModelOptimized* modele = new SqlQueryModelOptimized;

    modele->setQuery("SELECT * FROM specialites");

    return modele;
}

QAbstractTableModel* Bdd::getModeleModule(){

    SqlQueryModelOptimized* modele = new SqlQueryModelOptimized;

    modele->setQuery("SELECT * FROM modules");

    return modele;
}

QAbstractTableModel* Bdd::getModeleModuleProfesseur(const QString& module){

    return new ModelNoteModule(module);
}

QAbstractTableModel* Bdd::getModeleModuleEleve(const int& id, const QString& module){

    SqlQueryModelOptimized* modele = new SqlQueryModelOptimized;

    modele->setQuery("SELECT id, noteCE, noteDE, noteTP, notePRJ FROM " + module + " WHERE id = " + QString::number(id));

    return modele;
}

QAbstractTableModel* Bdd::getTutorat(const int& idprof){

    QSqlQueryModel* modele = new QSqlQueryModel();

    if (!bdd.isOpen())
        return NULL;

    modele->setQuery("SELECT E.id, U.nom, U.prenom, U.telephone FROM utilisateurs U, eleves E WHERE U.id = E.id AND E.professeurTuteur = " + QString::number(idprof),bdd);

    return modele;

/* EXPLICATION
Dans la table Eleve, case professeur tuteur si cette idée est égale à celui du prof entré en paramètre
On récupère l'id des élèves qu'on récupère ensuite pour prendre les infos dans la table Utilisateurs
*/
}

QAbstractTableModel* Bdd::getMatieres(const int& idprof){

    ModeleModule* modele = new ModeleModule(bdd);
    modele->setTable("modules");
    modele->setFilter("professeurResp = " + QString::number(idprof));
    modele->setEditStrategy(QSqlTableModel::OnFieldChange);
    return modele;
}

bool Bdd::existe(const int& id){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT COUNT(id) FROM utilisateurs WHERE id = :id");
    query->bindValue(":id",id);

    if(!query->exec())
        return false;

    if(!query->next())
        return false;

    if (query->value(0).toInt() == 0)
        return false;

    return true;
}

QStringList* Bdd::existe(const QString& nom, const QString& prenom){

    if (!bdd.isOpen())
        return 0;

    query->prepare("SELECT prenom FROM utilisateurs WHERE nom = :nom AND prenom LIKE :prenom");
    query->bindValue(":nom",nom);
    if (prenom.isEmpty()){
        query->bindValue(":prenom","%");
    }
    else{
        query->bindValue(":prenom",prenom);
    }

    if (!query->exec())
        return 0;

    QStringList* listePrenom = new QStringList;

    while (query->next())
        (*listePrenom) << query->value(0).toString();

    return listePrenom;
}

bool Bdd::isEleve(const int& id){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT COUNT(id) FROM eleves WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    if (query->value(0).toInt() == 0)
        return false;

    return true;
}

bool Bdd::isEleve(const QString& nom, const QString& prenom){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT id FROM utilisateurs WHERE nom = :nom AND prenom = :prenom");
    query->bindValue(":nom",nom);
    query->bindValue(":prenom",prenom);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    if (!isEleve(query->value(0).toInt()))
            return false;

    return true;
}

bool Bdd::isProfesseur(const int& id){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT COUNT(id) FROM professeurs WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    if (query->value(0).toInt() == 0)
        return false;

    return true;
}

bool Bdd::isProfesseur(const QString& nom, const QString& prenom){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT id FROM utilisateurs WHERE nom = :nom AND prenom = :prenom");
    query->bindValue(":nom",nom);
    query->bindValue(":prenom",prenom);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    if (!isProfesseur(query->value(0).toInt()))
            return false;

    return true;
}

bool Bdd::isAdministration(const int& id){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT COUNT(id) FROM administration WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    if (query->value(0).toInt() == 0)
        return false;

    return true;
}

bool Bdd::isAdministration(const QString& nom, const QString& prenom){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT id FROM utilisateurs WHERE nom = :nom AND prenom = :prenom");
    query->bindValue(":nom",nom);
    query->bindValue(":prenom",prenom);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    if (!isAdministration(query->value(0).toInt()))
            return false;

    return true;
}

QStringList* Bdd::getModule(const int& annee){

    if (!bdd.isOpen())
        return 0;

    query->prepare("SELECT nom FROM modules WHERE annee = :annee");
    if (annee == 0){
        query->bindValue(":annee","%");
    }
    else{
        query->bindValue(":annee",annee);
    }

    if(!query->exec())
        return 0;

    QStringList* listModule = new QStringList;

    while(query->next()){

        (*listModule) << query->value(0).toString();
    }

    return listModule;
}

QStringList* Bdd::getModuleProfesseur(const int& id, const int& annee){

    if (!bdd.isOpen())
        return 0;

    query->prepare("SELECT nom FROM modules WHERE professeurResp = :id AND annee = :annee");
    query->bindValue(":annee",annee);
    query->bindValue(":id",id);

    if(!query->exec())
        return 0;

    QStringList* list = new QStringList;

    while(query->next()){

        (*list) << query->value(0).toString();
    }

    return list;
}

QStringList* Bdd::getModuleOpt(const QString& specialite, const int& annee){

    if (!bdd.isOpen())
        return 0;

    query->prepare("SELECT nom FROM modules WHERE annee = :annee");
    query->bindValue(":annee",annee);

    if (!query->exec())
        return 0;

    QStringList* module = new QStringList;

    while (query->next()) {

        (*module) << query->value(0).toString();
    }

    query->prepare("SELECT module" + QString::number(annee) + "_1, module" + QString::number(annee) + "_2, module" + QString::number(annee) + "_3, module" + QString::number(annee) + "_4, module" + QString::number(annee) + "_5, module" + QString::number(annee) + "_6, module" + QString::number(annee) + "_7 FROM specialites WHERE nom = :specialite");
    query->bindValue(":specialite",specialite);

    if (!query->exec())
        return 0;


    QStringList moduleSpecialite;

    query->next();

    for(int cpt = 0; cpt < 7; cpt++){

        moduleSpecialite << query->value(cpt).toString();
    }

    for(QStringList::Iterator i = moduleSpecialite.begin(); i != moduleSpecialite.end(); i++){

        module->removeAll(*i);
    }

    return module;
}

QStringList* Bdd::getSpecialite(){

    if (!bdd.isOpen())
        return 0;

    query->prepare("SELECT nom FROM specialites");

    if (!query->exec())
        return 0;

    QStringList* specialite = new QStringList;

    while (query->next()) {

        (*specialite) << query->value(0).toString();
    }

    return specialite;
}

QVector<QStringList*>* Bdd::getModuleProfesseur(const int& id){

    QVector<QStringList*>* module = new QVector<QStringList*>;

    for(int cpt = 0; cpt < nombre_annee; cpt++)
        module->push_back(getModuleProfesseur(id,cpt+1));

    return module;
}

QHash<QString, QAbstractTableModel*>* Bdd::getModeleModuleProfesseur(const QStringList* module, const int& annee){

    QHash<QString, QAbstractTableModel*>* modele = new QHash<QString, QAbstractTableModel*>;
    QLocale c;

    for(QStringList::const_iterator i = module->begin(); i != module->end(); i++)
        modele->insert(*i,getModeleModuleProfesseur("modules" + c.toString(annee) + "_" + *i));

    return modele;
}

QVector<QHash<QString, QAbstractTableModel*>*>* Bdd::getModeleModuleProfesseur(const QVector<QStringList*>* module){

    QVector<QHash<QString, QAbstractTableModel*>*>* modele = new QVector<QHash<QString, QAbstractTableModel*>*>;

    for(int cpt = 0; cpt < module->size(); cpt++){

        modele->push_back(getModeleModuleProfesseur(module->value(cpt),cpt+1));
    }

    return modele;
}

QAbstractTableModel* Bdd::getModeleGroupe(const QString& table){

    if(table == "utilisateurs")
        return getModeleUtilisateur();

    if(table == "administration")
        return getModeleAdministration();

    if(table == "professeurs")
        return getModeleProfesseur();

    if(table == "eleves")
        return getModeleEleve();

    return 0;
}

QHash<QString, QAbstractTableModel*>* Bdd::getModeleGroupe(const QStringList* groupe){

    QHash<QString, QAbstractTableModel*>* modele = new QHash<QString, QAbstractTableModel*>;

        for(QStringList::const_iterator i = groupe->begin(); i != groupe->end(); i++){

            modele->insert(*i,getModeleGroupe(*i));
        }

    return modele;
}

QAbstractTableModel* Bdd::getModeleFormation(const QString& table){

    if(table == "specialites")
        return getModeleSpecialite();

    if(table == "modules")
        return getModeleModule();

    return 0;
}

QHash<QString, QAbstractTableModel*>* Bdd::getModeleFormation(const QStringList* groupe){

    QHash<QString, QAbstractTableModel*>* modele = new QHash<QString, QAbstractTableModel*>;

        for(QStringList::const_iterator i = groupe->begin(); i != groupe->end(); i++){

            modele->insert(*i,getModeleFormation(*i));
        }

    return modele;
}

QHash<QString, QAbstractTableModel*>* Bdd::getModeleModuleEleve(const int& id, const QStringList* module, const int& annee){

    QHash<QString, QAbstractTableModel*>* modele = new QHash<QString, QAbstractTableModel*>;
    QLocale c;

    for(QStringList::const_iterator i = module->begin(); i != module->end(); i++)
        modele->insert(*i,getModeleModuleEleve(id,"modules" + c.toString(annee) + "_" + *i));

    return modele;
}

QVector<QHash<QString, QAbstractTableModel*>*>* Bdd::getModeleModuleEleve(const int& id, const QVector<QStringList*>* module){

    QVector<QHash<QString, QAbstractTableModel*>*>* modele = new QVector<QHash<QString, QAbstractTableModel*>*>;

    for(int cpt = 0; cpt < module->size(); cpt++){

        modele->push_back(getModeleModuleEleve(id,module->value(cpt),cpt+1));
    }

    return modele;
}

QVector<QStringList*>* Bdd::getModuleEleve(const int& id){

    QVector<QStringList*>* module = new QVector<QStringList*>;

    for(int cpt = 0; cpt < nombre_annee; cpt++)
        module->push_back(getModuleEleve(id,cpt+1));

    return module;
}

QStringList* Bdd::getModuleEleve(const int& id, const int& annee){

    if (!bdd.isOpen())
        return 0;
    QLocale c;
    QString A;
    QStringList* list = new QStringList;

    /*dans A on recupere le nom de la specialité de l eleve*/
    query->prepare("SELECT specialite FROM eleves WHERE id = :id");
    query->bindValue(":id",id);

    if(!query->exec())
        return 0;
    if(!query->next())
        return 0;
    A = query->value(0).toString();

    /*dans list on recupere tous les modules de la specialité de l'elève selon son annee*/
    if(annee == 1)
    query->prepare("SELECT module1_1,module1_2,module1_3,module1_4,module1_5,module1_6,module1_7 FROM specialites WHERE nom = :nomspecialite");
    else if (annee == 2)
    query->prepare("SELECT module2_1,module2_2,module2_3,module2_4,module2_5,module2_6,module2_7 FROM specialites WHERE nom = :nomspecialite");
    else if (annee == 3)
    query->prepare("SELECT module3_1,module3_2,module3_3,module3_4,module3_5,module3_6,module3_7 FROM specialites WHERE nom = :nomspecialite");

    query->bindValue(":nomspecialite",A);

    if(!query->exec())
        return 0;
    if(!query->next())
        return 0;

    for (int cpt = 0; cpt < 5; cpt++)
        (*list) << query->value(cpt).toString();

    if (!query->value(5).toString().isEmpty())
        (*list) << query->value(5).toString();

    if (!query->value(6).toString().isEmpty())
        (*list) << query->value(6).toString();

    /*dans list on récupère aussi les modules optionnels de l eleve*/
    if (annee == 1)
    query->prepare("SELECT module1_1,module1_2,module1_3 FROM eleves WHERE id = :id");
    else if (annee == 2)
    query->prepare("SELECT module2_1,module2_2,module2_3 FROM eleves WHERE id = :id");
    else if (annee == 3)
    query->prepare("SELECT module3_1,module3_2,module3_3 FROM eleves WHERE id = :id");

    query->bindValue(":id",id);

    if(!query->exec())
        return 0;

    if(!query->next())
        return 0;

    for (int cpt = 0; cpt < 3; cpt++)
        (*list) << query->value(cpt).toString();

    /* on a donc dans list un total de 10 modules */

    qDebug() << *list;
    return list;
}

bool Bdd::insertUtilisateur(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone){

    if (!bdd.isOpen())
        return false;

    query->prepare("INSERT INTO utilisateurs (id, nom, prenom, dateNaissance, adresse, telephone) VALUES(:id, :nom, :prenom, :dateNaissance, :adresse, :telephone)");
    query->bindValue(":id",id);
    query->bindValue(":nom",nom);
    query->bindValue(":prenom",prenom);
    query->bindValue(":dateNaissance",dateNaissance);
    query->bindValue(":adresse",adresse);
    query->bindValue(":telephone",telephone);

    if (!query->exec())
        return false;

    return true;
}

bool Bdd::insertAdministration(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone){

    if (!bdd.isOpen())
        return false;

    if (!insertUtilisateur(id,nom,prenom,dateNaissance,adresse,telephone))
        return false;

    query->prepare("INSERT INTO administration (id) VALUES(:id)");
    query->bindValue(":id",id);

    if (!query->exec()){

        query->prepare("DELETE FROM utilisateurs WHERE id = :id");
        query->bindValue(":id",id);
        query->exec();
        return false;
    }

    return true;
}

bool Bdd::insertProfesseur(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone){

    if (!bdd.isOpen())
        return false;

    if (!insertUtilisateur(id,nom,prenom,dateNaissance,adresse,telephone))
        return false;

    query->prepare("INSERT INTO professeurs (id) VALUES(:id)");
    query->bindValue(":id",id);

    if(!query->exec()){

        query->prepare("DELETE FROM utilisateurs WHERE id = :id");
        query->bindValue(":id",id);
        query->exec();
        return false;
    }

    return true;
}

bool Bdd::insertEleve(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone, const int& promotion, const QString& specialite, const QString& module1_1, const QString& module1_2, const QString& module1_3, const QString& module2_1, const QString& module2_2, const QString& module2_3, const QString& module3_1, const QString& module3_2, const QString& module3_3, const int& professeurTuteur){

    if (!bdd.isOpen())
        return false;

    if (!insertUtilisateur(id,nom,prenom,dateNaissance,adresse,telephone))
        return false;

    query->prepare("INSERT INTO eleves (id, promotion, specialite, module1_1, module1_2, module1_3, module2_1, module2_2, module2_3, module3_1, module3_2, module3_3, professeurTuteur) VALUES (:id, :promotion, :specialite, :module1_1, :module1_2, :module1_3, :module2_1, :module2_2, :module2_3, :module3_1,:module3_2, :module3_3, :professeurTuteur)");
    query->bindValue(":id",id);
    query->bindValue(":promotion",promotion);
    query->bindValue(":specialite",specialite);
    query->bindValue(":module1_1",module1_1);
    query->bindValue(":module1_2",module1_2);
    query->bindValue(":module1_3",module1_3);
    query->bindValue(":module2_1",module2_1);
    query->bindValue(":module2_2",module2_2);
    query->bindValue(":module2_3",module2_3);
    query->bindValue(":module3_1",module3_1);
    query->bindValue(":module3_2",module3_2);
    query->bindValue(":module3_3",module3_3);

    if (professeurTuteur != 0)
        query->bindValue(":professeurTuteur",professeurTuteur);

    if (!query->exec()){
        query->prepare("DELETE FROM utilisateurs WHERE id = :id");
        query->bindValue(":id",id);
        query->exec();
        return false;
    }

    if (!insertEleveSpecialite(id,specialite)){
        deleteEleve(id);
        return false;
    }

    if (!insertEleveModule(id,"modules1_"+module1_1)){
        deleteEleve(id);
        return false;
    }

    if (!insertEleveModule(id,"modules1_"+module1_2)){
        deleteEleve(id);
        return false;
    }

    if (!insertEleveModule(id,"modules1_"+module1_3)){
        deleteEleve(id);
        return false;
    }

    if (!insertEleveModule(id,"modules2_"+module2_1)){
        deleteEleve(id);
        return false;
    }

    if (!insertEleveModule(id,"modules2_"+module2_2)){
        deleteEleve(id);
        return false;
    }

    if (!insertEleveModule(id,"modules2_"+module2_3)){
        deleteEleve(id);
        return false;
    }

    if (!insertEleveModule(id,"modules3_"+module3_1)){
        deleteEleve(id);
        return false;
    }

    if (!insertEleveModule(id,"modules3_"+module3_2)){
        deleteEleve(id);
        return false;
    }

    if (!insertEleveModule(id,"modules3_"+module3_3)){
        deleteEleve(id);
        return false;
    }

    return true;
}

bool Bdd::insertEleveSpecialite(const int& id, const QString& nomSpecialite){

    if (!bdd.isOpen())
        return false;

    QSqlQuery* tempQuery = new QSqlQuery(bdd);

    tempQuery->prepare("SELECT module1_1, module1_2, module1_3, module1_4, module1_5, module1_6, module1_7, module2_1, module2_2, module2_3, module2_4, module2_5, module2_6, module2_7, module3_1, module3_2, module3_3, module3_4, module3_5, module3_6, module3_7 FROM specialites WHERE nom = :nomSpecialite");
    tempQuery->bindValue(":nomSpecialite",nomSpecialite);

    if (!tempQuery->exec())
        return false;

    if (!tempQuery->next())
        return false;

    for(int cpt = 0; cpt < 21; cpt++){

        if (!tempQuery->value(cpt).toString().isEmpty()){
            if (!insertEleveModule(id,"modules"+QString::number((cpt/7)+1)+"_"+tempQuery->value(cpt).toString()))
                return false;
        }
    }

    return true;
}

bool Bdd::insertEleveModule(const int& id, const QString& nomModule){

    if (!bdd.isOpen())
        return false;

    QSqlQuery* tempQuery = new QSqlQuery(bdd);

    tempQuery->prepare("INSERT INTO " + nomModule + " (id) VALUES (:id)");
    tempQuery->bindValue(":id",id);

    if (!tempQuery->exec())
        return false;

    return true;
}

bool Bdd::getIdUtilisateur(int& id, const QString& nom, const QString& prenom){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT id FROM utilisateurs WHERE :nom = nom AND :prenom = prenom");
    query->bindValue(":nom",nom);
    query->bindValue(":prenom",prenom);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    id = query->value(0).toInt();

    return true;
}

bool Bdd::getUtilisateur(int& id, const QString& nom, const QString& prenom, QDate& dateNaissance, QString& adresse, QString& telephone){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT id, dateNaissance, adresse, telephone FROM utilisateurs WHERE :nom = nom AND :prenom = prenom");
    query->bindValue(":nom",nom);
    query->bindValue(":prenom",prenom);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    id = query->value(0).toInt();
    dateNaissance = query->value(1).toDate();
    adresse = query->value(2).toString();
    telephone = query->value(3).toString();

    return true;
}

bool Bdd::getUtilisateur(const int& id, QString& nom, QString& prenom, QDate& dateNaissance, QString& adresse, QString& telephone){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT nom, prenom, dateNaissance, adresse, telephone FROM utilisateurs WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    nom = query->value(0).toString();
    prenom = query->value(1).toString();
    dateNaissance = query->value(2).toDate();
    adresse = query->value(3).toString();
    telephone = query->value(4).toString();

    return true;
}

bool Bdd::getAdministration(int& id, const QString& nom, const QString& prenom, QDate& dateNaissance, QString& adresse, QString& telephone){

    if (!bdd.isOpen())
        return false;

    if (!getUtilisateur(id,nom,prenom,dateNaissance,adresse,telephone))
        return false;

    return true;
}

bool Bdd::getProfesseur(int& id, const QString& nom, const QString& prenom, QDate& dateNaissance, QString& adresse, QString& telephone){

    if (!bdd.isOpen())
        return false;

    if (!getUtilisateur(id,nom,prenom,dateNaissance,adresse,telephone))
        return false;

    return true;
}

bool Bdd::getEleve(int& id, const QString& nom, const QString& prenom, QDate& dateNaissance, QString& adresse, QString& telephone, int& promotion, QString& specialite, QString& module1_1, QString& module1_2, QString& module1_3, QString& module2_1, QString& module2_2, QString& module2_3, QString& module3_1, QString& module3_2, QString& module3_3, QString& nomProfesseurTuteur, QString& prenomProfesseurTuteur){

    if (!bdd.isOpen())
        return false;

    if (!getUtilisateur(id,nom,prenom,dateNaissance,adresse,telephone))
        return false;

    query->prepare("SELECT promotion, specialite, module1_1, module1_2, module1_3, module2_1, module2_2, module2_3, module3_1, module3_2, module3_3, professeurTuteur FROM eleves WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    promotion = query->value(0).toInt();
    specialite = query->value(1).toString();
    module1_1 = query->value(2).toString();
    module1_2 = query->value(3).toString();
    module1_3 = query->value(4).toString();
    module2_1 = query->value(5).toString();
    module2_2 = query->value(6).toString();
    module2_3 = query->value(7).toString();
    module3_1 = query->value(8).toString();
    module3_2 = query->value(9).toString();
    module3_3 = query->value(10).toString();

    int tempID = query->value(11).toInt();

    query->prepare("SELECT nom, prenom FROM utilisateurs WHERE id = :id");
    query->bindValue(":id",tempID);
    if (!query->exec())
        return false;

    if (query->next()){

        nomProfesseurTuteur = query->value(0).toString();
        prenomProfesseurTuteur = query->value(1).toString();
    }

    return true;
}

bool Bdd::getEleve(const int& id, QString& nom, QString& prenom, QDate& dateNaissance, QString& adresse, QString& telephone, int& promotion, QString& specialite, QString& module1_1, QString& module1_2, QString& module1_3, QString& module2_1, QString& module2_2, QString& module2_3, QString& module3_1, QString& module3_2, QString& module3_3, QString& nomProfesseurTuteur, QString& prenomProfesseurTuteur){

    if (!bdd.isOpen())
        return false;

    if (!getUtilisateur(id,nom,prenom,dateNaissance,adresse,telephone))
        return false;

    query->prepare("SELECT promotion, specialite, module1_1, module1_2, module1_3, module2_1, module2_2, module2_3, module3_1, module3_2, module3_3, professeurTuteur FROM eleves WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    promotion = query->value(0).toInt();
    specialite = query->value(1).toString();
    module1_1 = query->value(2).toString();
    module1_2 = query->value(3).toString();
    module1_3 = query->value(4).toString();
    module2_1 = query->value(5).toString();
    module2_2 = query->value(6).toString();
    module2_3 = query->value(7).toString();
    module3_1 = query->value(8).toString();
    module3_2 = query->value(9).toString();
    module3_3 = query->value(10).toString();

    int tempID = query->value(11).toInt();

    query->prepare("SELECT nom, prenom FROM utilisateurs WHERE id = :id");
    query->bindValue(":id",tempID);
    if (!query->exec())
        return false;

    if (query->next()){

        nomProfesseurTuteur = query->value(0).toString();
        prenomProfesseurTuteur = query->value(1).toString();
    }

    return true;
}

bool Bdd::updateUtilisateur(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone){

    if (!bdd.isOpen())
        return false;

    query->prepare("UPDATE utilisateurs SET nom = :nom, prenom = :prenom, dateNaissance = :dateNaissance, adresse = :adresse, telephone = :telephone WHERE id = :id");
    query->bindValue(":id",id);
    query->bindValue(":nom",nom);
    query->bindValue(":prenom",prenom);
    query->bindValue(":dateNaissance",dateNaissance);
    query->bindValue(":adresse",adresse);
    query->bindValue(":telephone",telephone);

    if (!query->exec())
        return false;

    return true;
}

bool Bdd::updateAdministration(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone){

    if (!bdd.isOpen())
        return false;

    if (!updateUtilisateur(id,nom,prenom,dateNaissance,adresse,telephone))
        return false;

    return true;
}

bool Bdd::updateProfesseur(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone){

    if (!bdd.isOpen())
        return false;

    if (!updateUtilisateur(id,nom,prenom,dateNaissance,adresse,telephone))
        return false;

    return true;
}

bool Bdd::updateEleve(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone, const int& promotion, const QString& specialite, const QString& module1_1, const QString& module1_2, const QString& module1_3, const QString& module2_1, const QString& module2_2, const QString& module2_3, const QString& module3_1, const QString& module3_2, const QString& module3_3, const int& professeurTuteur){

    if (!bdd.isOpen())
        return false;

    if (!updateUtilisateur(id,nom,prenom,dateNaissance,adresse,telephone))
        return false;

    query->prepare("SELECT specialite, module1_1, module1_2, module1_3, module2_1, module2_2, module2_3, module3_1 = :module3_1, module3_2, module3_3 FROM eleves WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    if (query->value(0).toString() != specialite){
        deleteEleveSpecialite(id,query->value(0).toString());
        insertEleveSpecialite(id,specialite);
    }

    if (query->value(1).toString() != module1_1){
        deleteEleveModule(id,query->value(1).toString()+"1_1");
        insertEleveModule(id,module1_1+"1_1");
    }

    if (query->value(2).toString() != module1_2){
        deleteEleveModule(id,query->value(2).toString()+"1_2");
        insertEleveModule(id,module1_2+"1_2");
    }

    if (query->value(3).toString() != module1_3){
        deleteEleveModule(id,query->value(3).toString()+"1_3");
        insertEleveModule(id,module1_3+"1_3");
    }

    if (query->value(4).toString() != module2_1){
        deleteEleveModule(id,query->value(4).toString()+"2_1");
        insertEleveModule(id,module2_1+"2_1");
    }

    if (query->value(5).toString() != module2_2){
        deleteEleveModule(id,query->value(5).toString()+"2_2");
        insertEleveModule(id,module2_2+"2_2");
    }

    if (query->value(6).toString() != module2_3){
        deleteEleveModule(id,query->value(6).toString()+"2_3");
        insertEleveModule(id,module1_1+"2_3");
    }

    if (query->value(7).toString() != module3_1){
        deleteEleveModule(id,query->value(7).toString()+"3_1");
        insertEleveModule(id,module3_1+"3_1");
    }

    if (query->value(8).toString() != module3_2){
        deleteEleveModule(id,query->value(8).toString()+"3_2");
        insertEleveModule(id,module3_2+"3_2");
    }

    if (query->value(9).toString() != module3_3){
        deleteEleveModule(id,query->value(9).toString()+"3_3");
        insertEleveModule(id,module1_1+"3_3");
    }

    query->prepare("UPDATE eleves SET promotion = :promotion, specialite = :specialite, module1_1 = :module1_1, module1_2 = :module1_2, module1_3 = :module1_3, module2_1 = :module2_1, module2_2 = :module2_2, module2_3 = :module2_3, module3_1 = :module3_1, module3_2 = :module3_2, module3_3 = :module3_3, professeurTuteur = :professeurTuteur WHERE id = :id");
    query->bindValue(":id",id);
    query->bindValue(":promotion",promotion);
    query->bindValue(":specialite",specialite);
    query->bindValue(":module1_1",module1_1);
    query->bindValue(":module1_2",module1_2);
    query->bindValue(":module1_3",module1_3);
    query->bindValue(":module2_1",module2_1);
    query->bindValue(":module2_2",module2_2);
    query->bindValue(":module2_3",module2_3);
    query->bindValue(":module3_1",module3_1);
    query->bindValue(":module3_2",module3_2);
    query->bindValue(":module3_3",module3_3);

    if (professeurTuteur != 0)
        query->bindValue(":professeurTuteur",professeurTuteur);

    if (!query->exec()){
        deleteEleve(id);
        return false;
    }

    return true;
}

bool Bdd::deleteUtilisateur(const int& id){

    if (!bdd.isOpen())
        return false;

    query->prepare("DELETE FROM utilisateurs WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    return true;
}

bool Bdd::deleteAdministration(const int& id){

    if (!bdd.isOpen())
        return false;

    if(!deleteUtilisateur(id))
        return false;

    query->prepare("DELETE FROM administration WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    return true;
}

bool Bdd::deleteAdministration(const QString& nom, const QString& prenom){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT id FROM utilisateurs WHERE nom = :nom AND prenom = :prenom");
    query->bindValue(":nom",nom);
    query->bindValue(":prenom",prenom);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    if (!deleteAdministration(query->value(0).toInt()))
        return false;

    return true;
}

bool Bdd::deleteProfesseur(const int& id){

    if (!bdd.isOpen())
        return false;

    if(!deleteUtilisateur(id))
        return false;

    query->prepare("DELETE FROM professeurs WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    return true;
}

bool Bdd::deleteProfesseur(const QString& nom, const QString& prenom){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT id FROM utilisateurs WHERE nom = :nom AND prenom = :prenom");
    query->bindValue(":nom",nom);
    query->bindValue(":prenom",prenom);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    if (!deleteProfesseur(query->value(0).toInt()))
        return false;

    return true;
}

bool Bdd::deleteEleve(const int& id){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT module1_1, module1_2, module1_3, module2_1, module2_2, module2_3, module3_1, module3_2, module3_3, specialite FROM eleves WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    for(int cpt = 0; cpt < 9; cpt++){

        if (!deleteEleveModule(id,"modules"+QString::number((cpt/3)+1)+"_"+query->value(cpt).toString()))
            return false;
    }

    if (!deleteEleveSpecialite(id,query->value(9).toString()))
        return false;

    if (!deleteUtilisateur(id))
        return false;

    query->prepare("DELETE FROM eleves WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return false;

    return true;
}

bool Bdd::deleteEleve(const QString& nom, const QString& prenom){

    if (!bdd.isOpen())
        return false;

    query->prepare("SELECT id FROM utilisateurs WHERE nom = :nom AND prenom = :prenom");
    query->bindValue(":nom",nom);
    query->bindValue(":prenom",prenom);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    if (!deleteEleve(query->value(0).toInt()))
        return false;

    return true;
}

bool Bdd::deleteEleveSpecialite(const int& id, const QString& nomSpecialite){

    if (!bdd.isOpen())
        return false;

    QSqlQuery* tempQuery = new QSqlQuery(bdd);

    tempQuery->prepare("SELECT module1_1, module1_2, module1_3, module1_4, module1_5, module1_6, module1_7, module2_1, module2_2, module2_3, module2_4, module2_5, module2_6, module2_7, module3_1, module3_2, module3_3, module3_4, module3_5, module3_6, module3_7 FROM specialites WHERE nom = :nomSpecialite");
    tempQuery->bindValue(":nomSpecialite",nomSpecialite);

    if (!tempQuery->exec())
        return false;

    if (!tempQuery->next())
        return false;

    for(int cpt = 0; cpt < 21; cpt++){

        if (!tempQuery->value(cpt).toString().isEmpty()){
            if (!deleteEleveModule(id,"modules"+QString::number((cpt/7)+1)+"_"+tempQuery->value(cpt).toString()))
                return false;
        }
    }

    return true;
}

bool Bdd::deleteEleveModule(const int& id, const QString& nomModule){

    if (!bdd.isOpen())
        return false;

    QSqlQuery* tempQuery = new QSqlQuery(bdd);

    tempQuery->prepare("DELETE FROM " + nomModule + " WHERE id = :id");
    tempQuery->bindValue(":id",id);

    if (!tempQuery->exec())
        return false;

    return true;
}

bool Bdd::getProfesseurTuteur(const QString& nom, const QString& prenom, QString& nomProfesseurTuteur, QString& prenomProfesseurTuteur){

    if (!bdd.isOpen())
        return false;

    int tempId;

    if(!getIdUtilisateur(tempId,nom,prenom))
        return false;

    query->prepare("SELECT professeurTuteur FROM eleves WHERE id = :id");
    query->bindValue(":id",tempId);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    tempId = query->value(0).toInt();

    query->prepare("SELECT nom, prenom FROM utilisateurs WHERE id = :id");
    query->bindValue(":id",tempId);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    nomProfesseurTuteur = query->value(0).toString();
    prenomProfesseurTuteur = query->value(1).toString();

    return true;
}

bool Bdd::updateProfesseurTuteur(const QString& nom, const QString& prenom, const int& idProfesseurTuteur){

    if (!bdd.isOpen())
        return false;

    int tempId;

    if(!getIdUtilisateur(tempId,nom,prenom))
        return false;

    query->prepare("UPDATE eleves SET professeurTuteur = :idProfesseurTuteur WHERE id = :id");
    query->bindValue(":id",tempId);
    query->bindValue(":idProfesseurTuteur",idProfesseurTuteur);

    if (!query->exec())
        return false;

    return true;
}

bool Bdd::getProfesseurRespModule(const int& annee, const QString& nomModule, QString& nomProfesseurResp, QString& prenomProfesseurResp){

    if (!bdd.isOpen())
        return false;

    int tempId;

    query->prepare("SELECT professeurResp FROM modules WHERE annee = :annee AND nom = :nomModule");
    query->bindValue(":annee",annee);
    query->bindValue(":nomModule",nomModule);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    tempId = query->value(0).toInt();

    query->prepare("SELECT nom, prenom FROM utilisateurs WHERE id = :id");
    query->bindValue(":id",tempId);

    if (!query->exec())
        return false;

    if (!query->next())
        return false;

    nomProfesseurResp = query->value(0).toString();
    prenomProfesseurResp = query->value(1).toString();

    return true;
}

bool Bdd::updateProfesseurRespModule(const int& annee, const QString& nomModule, const int& idProfesseurResp){

    if (!bdd.isOpen())
        return false;

    query->prepare("UPDATE modules SET professeurResp = :idProfesseurResp WHERE annee = :annee AND nom = :nomModule");
    query->bindValue(":annee",annee);
    query->bindValue(":nomModule",nomModule);
    query->bindValue(":idProfesseurResp",idProfesseurResp);

    if (!query->exec())
        return false;

    return true;
}

double Bdd::moyenneSpecialiteEleve(const int& id, int& ponderation){

    if (!bdd.isOpen())
        return -1;

    int annee;
    QString tempNomSpecialite;

    query->prepare("SELECT promotion, specialite FROM eleves WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return -1;

    if (!query->next())
        return -1;

    annee = QDate::currentDate().year() - query->value(0).toInt() + 3;
    tempNomSpecialite = query->value(1).toString();

    QSqlQuery* tempQuery = new QSqlQuery(bdd);
    tempQuery->prepare("SELECT module" + QString::number(annee)+ "_1, module" + QString::number(annee)+ "_2, module" + QString::number(annee)+ "_3, module" + QString::number(annee)+ "_4, module" + QString::number(annee)+ "_5, module" + QString::number(annee)+ "_6, module" + QString::number(annee)+ "_7" + " FROM specialites WHERE nom = :nomSpecialite");
    tempQuery->bindValue(":nomSpecialite",tempNomSpecialite);

    if (!tempQuery->exec())
        return -1;

    if (!tempQuery->next())
        return -1;

    int nbModule;
    int temp;
    double moyenne;

    nbModule = 0;
    for (int cpt = 0; cpt < 5; cpt++){

        temp = moyenneModuleEleve(id,annee,tempQuery->value(cpt).toString());
        if (temp == -1)
            return -1;
        moyenne += temp*10;
        nbModule++;
    }

    if (!tempQuery->value(5).toString().isEmpty()){
        temp = moyenneModuleEleve(id,annee,tempQuery->value(6).toString());
        if (temp == -1)
            return -1;
        moyenne += temp*10;
        nbModule++;
    }

    if (!tempQuery->value(6).toString().isEmpty()){
        temp = moyenneModuleEleve(id,annee,tempQuery->value(6).toString());
        if (temp == -1)
            return -1;
        moyenne += temp*10;
        nbModule++;
    }

    ponderation = nbModule*10;

    return moyenne;
}

double Bdd::moyenneModuleOptEleve(const int& id, int& ponderation){

    if (!bdd.isOpen())
        return -1;

    int annee;

    query->prepare("SELECT promotion FROM eleves WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return -1;

    if (!query->next())
        return -1;

    annee = QDate::currentDate().year() - query->value(0).toInt() + 3;

    QSqlQuery* tempQuery = new QSqlQuery(bdd);
    tempQuery->prepare("SELECT module" + QString::number(annee)+ "_1, module" + QString::number(annee)+ "_2, module" + QString::number(annee)+ "_3" + " FROM eleves WHERE id = :id");
    tempQuery->bindValue(":id",id);

    if (!tempQuery->exec())
        return -1;

    if (!tempQuery->next())
        return -1;

    int temp;
    double moyenne;

    for (int cpt = 0; cpt < 3; cpt++){

        temp = moyenneModuleEleve(id,annee,tempQuery->value(cpt).toString());
        if (temp == -1)
            return -1;
        moyenne += temp*10;
    }

    ponderation = 3*10;

    return moyenne;
}

double Bdd::moyenneModuleEleve(const int& id, const int& annee, const QString& nomModule){

    if (!bdd.isOpen())
        return -1;

    QString tempNoteCE;
    QString tempNoteDE;
    QString tempNoteTP;
    QString tempNotePRJ;

    query->prepare("SELECT noteCE, noteDE, noteTP, notePRJ FROM modules" + QString::number(annee) + "_" + nomModule +" WHERE id = :id");
    query->bindValue(":id",id);

    if (!query->exec())
        return -1;

    if (!query->next())
        return -1;

    tempNoteCE = query->value(0).toString();
    tempNoteDE = query->value(1).toString();
    tempNoteTP = query->value(2).toString();
    tempNotePRJ = query->value(3).toString();

    query->prepare("SELECT coeffCE, coeffDE, coeffTP, coeffPRJ FROM modules WHERE annee = :annee AND nom = :nomModule");
    query->bindValue(":annee",annee);
    query->bindValue(":nomModule",nomModule);

    if (!query->exec())
        return -1;

    if (!query->next())
        return -1;

    QString tempCoeffCE;
    QString tempCoeffDE;
    QString tempCoeffTP;
    QString tempCoeffPRJ;

    tempCoeffCE = query->value(0).toString();
    tempCoeffDE = query->value(1).toString();
    tempCoeffTP = query->value(2).toString();
    tempCoeffPRJ = query->value(3).toString();

    if ((tempNoteCE.isEmpty())&&(!tempCoeffCE.isEmpty()))
        return -1;

    if ((tempNoteDE.isEmpty())&&(!tempCoeffDE.isEmpty()))
        return -1;

    if ((tempNoteTP.isEmpty())&&(!tempCoeffTP.isEmpty()))
        return -1;

    if ((tempNotePRJ.isEmpty())&&(!tempCoeffPRJ.isEmpty()))
        return -1;

    return tempNoteCE.toDouble()*tempCoeffCE.toDouble()+tempNoteDE.toDouble()*tempCoeffDE.toDouble()+tempNoteTP.toDouble()*tempCoeffTP.toDouble()+tempNotePRJ.toDouble()*tempCoeffPRJ.toDouble();
}

bool Bdd::nonAdmissionEleve(const int& id, const int& promotion){

    if (!bdd.isOpen())
        return false;

    query->prepare("UPDATE eleves SET promotion = :promotion WHERE id = :id");
    query->bindValue(":id",id);
    query->bindValue(":promotion",promotion);

    if (!query->exec())
        return false;

    return true;
}
