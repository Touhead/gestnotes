    #include "modele.h"

Modele::Modele(const QString& host, const QString& user, const QString& password, const QString& dataBase, const int& id)
{
    bdd = new Bdd(host,user,password,dataBase,"connectionModele");
    bdd->open();

    p = nouvellePersonne(id,bdd);
    p->hello();
}

Modele::~Modele(){

    bdd->close();
    delete bdd;
    QSqlDatabase::removeDatabase("connectionModele");
}

const int& Modele::getId(){

    return p->getId();
}

QStringList* Modele::existe(const QString& nom, const QString& prenom){

   return bdd->existe(nom,prenom);
}

bool Modele::isEleve(const QString& nom, const QString& prenom){

    return bdd->isEleve(nom,prenom);
}

bool Modele::isProfesseur(const QString& nom, const QString& prenom){

    return bdd->isProfesseur(nom,prenom);
}

bool Modele::isAdministration(const QString& nom, const QString& prenom){

    return bdd->isAdministration(nom,prenom);
}

QStringList* Modele::getModule(const int& annee){

    return bdd->getModule(annee);
}

QStringList* Modele::getModuleOpt(const QString& specialite, const int& annee) const{

    return bdd->getModuleOpt(specialite,annee);
}

QStringList* Modele::getSpecialite(){

    return bdd->getSpecialite();
}

bool Modele::createDockDonnee(QDockWidget* dock, QActionGroup* actions) const{

    return p->createDockDonnee(dock,actions,bdd);
}

bool Modele::createDockOutil(QDockWidget* dock, QActionGroup* actions) const{

    return p->createDockOutil(dock,actions,bdd);
}

QAbstractTableModel* Modele::getModele(QAction* action) const{

    return p->getModele(action);
}

QWidget* Modele::getFenetre(QAction* action) const{

    return p->getFenetre(action);
}

bool Modele::insertAdministration(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone){

    return bdd->insertAdministration(id,nom,prenom,dateNaissance,adresse,telephone);
}

bool Modele::insertProfesseur(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone){

    return bdd->insertProfesseur(id,nom,prenom,dateNaissance,adresse,telephone);
}

bool Modele::insertEleve(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone, const int& promotion, const QString& specialite, const QString& module1_1, const QString& module1_2, const QString& module1_3, const QString& module2_1, const QString& module2_2, const QString& module2_3, const QString& module3_1, const QString& module3_2, const QString& module3_3, const int& professeurTuteur){

    return bdd->insertEleve(id,nom,prenom,dateNaissance,adresse,telephone,promotion,specialite,module1_1,module1_2,module1_3,module2_1,module2_2,module2_3,module3_1,module3_2,module3_3,professeurTuteur);
}

bool Modele::getAdministration(int& id, const QString& nom, const QString& prenom, QDate& dateNaissance, QString& adresse, QString& telephone){

    return bdd->getAdministration(id,nom,prenom,dateNaissance,adresse,telephone);
}

bool Modele::getProfesseur(int& id, const QString& nom, const QString& prenom, QDate& dateNaissance, QString& adresse, QString& telephone){

    return bdd->getProfesseur(id,nom,prenom,dateNaissance,adresse,telephone);
}

bool Modele::getEleve(int& id, const QString& nom, const QString& prenom, QDate& dateNaissance, QString& adresse, QString& telephone, int& promotion, QString& specialite, QString& module1_1, QString& module1_2, QString& module1_3, QString& module2_1, QString& module2_2, QString& module2_3, QString& module3_1, QString& module3_2, QString& module3_3, QString& nomProfesseurTuteur, QString& prenomProfesseurTuteur){

    return bdd->getEleve(id,nom,prenom,dateNaissance,adresse,telephone,promotion,specialite,module1_1,module1_2,module1_3,module2_1,module2_2,module2_3,module3_1,module3_2,module3_3,nomProfesseurTuteur,prenomProfesseurTuteur);
}

bool Modele::getEleve(const int& id, QString& nom, QString& prenom, QDate& dateNaissance, QString& adresse, QString& telephone, int& promotion, QString& specialite, QString& module1_1, QString& module1_2, QString& module1_3, QString& module2_1, QString& module2_2, QString& module2_3, QString& module3_1, QString& module3_2, QString& module3_3, QString& nomProfesseurTuteur, QString& prenomProfesseurTuteur){

    return bdd->getEleve(id,nom,prenom,dateNaissance,adresse,telephone,promotion,specialite,module1_1,module1_2,module1_3,module2_1,module2_2,module2_3,module3_1,module3_2,module3_3,nomProfesseurTuteur,prenomProfesseurTuteur);
}

bool Modele::updateAdministration(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone){

    return bdd->updateAdministration(id,nom,prenom,dateNaissance,adresse,telephone);
}

bool Modele::updateProfesseur(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone){

    return bdd->updateProfesseur(id,nom,prenom,dateNaissance,adresse,telephone);
}

bool Modele::updateEleve(const int& id, const QString& nom, const QString& prenom, const QDate& dateNaissance, const QString& adresse, const QString& telephone, const int& promotion, const QString& specialite, const QString& module1_1, const QString& module1_2, const QString& module1_3, const QString& module2_1, const QString& module2_2, const QString& module2_3, const QString& module3_1, const QString& module3_2, const QString& module3_3, const int& professeurTuteur){

    return bdd->updateEleve(id,nom,prenom,dateNaissance,adresse,telephone,promotion,specialite,module1_1,module1_2,module1_3,module2_1,module2_2,module2_3,module3_1,module3_2,module3_3,professeurTuteur);
}

bool Modele::deleteAdministration(const int& id){

    return bdd->deleteAdministration(id);
}

bool Modele::deleteProfesseur(const int& id){

    return bdd->deleteProfesseur(id);
}

bool Modele::deleteEleve(const int& id){

    return bdd->deleteEleve(id);
}

bool Modele::getProfesseurTuteur(const QString& nom, const QString& prenom, QString& nomProfesseurTuteur, QString& prenomProfesseurTuteur){

    return bdd->getProfesseurTuteur(nom,prenom,nomProfesseurTuteur,prenomProfesseurTuteur);
}

bool Modele::updateProfesseurTuteur(const QString& nom, const QString& prenom, const int& idProfesseurTuteur){

    return bdd->updateProfesseurTuteur(nom,prenom,idProfesseurTuteur);
}

bool Modele::getProfesseurRespModule(const int& annee, const QString& nomModule, QString& nomProfesseurResp, QString& prenomProfesseurResp){

    return bdd->getProfesseurRespModule(annee,nomModule,nomProfesseurResp,prenomProfesseurResp);
}

bool Modele::updateProfesseurRespModule(const int& annee, const QString& nomModule, const int& idProfesseurResp){

    return bdd->updateProfesseurRespModule(annee,nomModule,idProfesseurResp);
}

double Modele::moyenneSpecialiteEleve(const int& id, int& ponderation){

    return bdd->moyenneSpecialiteEleve(id,ponderation);
}

double Modele::moyenneModuleOptEleve(const int& id, int& ponderation){

    return bdd->moyenneModuleOptEleve(id,ponderation);
}

bool Modele::nonAdmissionEleve(const int& id, const int& promotion){

    return bdd->nonAdmissionEleve(id,promotion);
}

void Modele::mettreAJour(){

    return p->mettreAJour(bdd);
}
