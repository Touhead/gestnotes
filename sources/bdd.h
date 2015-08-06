#ifndef BDD_H
#define BDD_H

#include <QtSql>
#include <QDebug>
#include <QHash>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QObject>
#include "modelnotemodule.h"
#include "sqlquerymodeloptimized.h"
#include "modelemodule.h"
#include <QStringListModel>

const int nombre_annee = 3;

class Bdd : public QObject{

    Q_OBJECT

public:

    Bdd(const QString&, const QString&, const QString&, const QString&, const QString&);
    virtual ~Bdd();


    bool addUser(const int&, const QString&, const QString&, const QString&, const QString&, const QString&);

    template <class T>
    bool updateUser(const int& id, const QString& field, const T& value);

    QStringList* getFieldUser(const QString& field);
    QHash<QString, QStringList*>* getUser();


    QAbstractTableModel* getModeleUtilisateur(); // Pour l'administration en lecture seulement
    QAbstractTableModel* getModeleEleve();
    QAbstractTableModel* getModeleProfesseur();
    QAbstractTableModel* getModeleAdministration();
    QAbstractTableModel* getModeleSpecialite();
    QAbstractTableModel* getModeleModule();
    QAbstractTableModel* getModeleModuleProfesseur(const QString&);
    QAbstractTableModel* getModeleModuleEleve(const int&, const QString&);
    QAbstractTableModel* getTutorat(const int& idprof);
    QAbstractTableModel* getMatieres(const int& idprof);

    bool existe(const int&);
    QStringList* existe(const QString&, const QString& = "");
    bool isEleve(const int&);
    bool isEleve(const QString&, const QString&);
    bool isProfesseur(const int&);
    bool isProfesseur(const QString&, const QString&);
    bool isAdministration(const int&);
    bool isAdministration(const QString&, const QString&);

    QStringList* getModule(const int& = 0);
    QStringList* getModuleProfesseur(const int&, const int&);
    QStringList* getModuleOpt(const QString&, const int&);
    QStringList* getSpecialite();

    QVector<QStringList*>* getModuleProfesseur(const int&);
    QHash<QString, QAbstractTableModel*>* getModeleModuleProfesseur(const QStringList*, const int&);
    QVector<QHash<QString, QAbstractTableModel*>*>* getModeleModuleProfesseur(const QVector<QStringList*>*);

    QAbstractTableModel* getModeleGroupe(const QString&);
    QHash<QString, QAbstractTableModel*>* getModeleGroupe(const QStringList*);

    QAbstractTableModel* getModeleFormation(const QString&);
    QHash<QString, QAbstractTableModel*>* getModeleFormation(const QStringList*);

    QHash<QString, QAbstractTableModel*>* getModeleModuleEleve(const int&, const QStringList*, const int&);
    QVector<QHash<QString, QAbstractTableModel*>*>* getModeleModuleEleve(const int&, const QVector<QStringList*>*);

    QVector<QStringList*>* getModuleEleve(const int&);
    QStringList* getModuleEleve(const int&, const int&);

    bool insertUtilisateur(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&);
    bool insertAdministration(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&);
    bool insertProfesseur(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&);
    bool insertEleve(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&, const int&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const int& = 0);
    bool insertEleveSpecialite(const int&, const QString&);
    bool insertEleveModule(const int&, const QString&);


    bool getIdUtilisateur(int&, const QString&, const QString&);

    bool getUtilisateur(int&, const QString&, const QString&, QDate&, QString&, QString&);
    bool getUtilisateur(const int&, QString&, QString&, QDate&, QString&, QString&);
    bool getAdministration(int&, const QString&, const QString&, QDate&, QString&, QString&);
    bool getProfesseur(int&, const QString&, const QString&, QString&, QString&);
    bool getProfesseur(int&, const QString&, const QString&, QDate&, QString&, QString&);
    bool getEleve(int&, const QString&, const QString&, QDate&, QString&, QString&, int&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&);
    bool getEleve(const int&, QString&, QString&, QDate&, QString&, QString&, int&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&);

    bool updateUtilisateur(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&);
    bool updateAdministration(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&);
    bool updateProfesseur(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&);
    bool updateEleve(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&, const int&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const int& = 0);

    bool deleteUtilisateur(const int&);
    bool deleteAdministration(const int&);
    bool deleteAdministration(const QString&, const QString&);
    bool deleteProfesseur(const int&);
    bool deleteProfesseur(const QString&, const QString&);
    bool deleteEleve(const int&);
    bool deleteEleve(const QString&, const QString&);
    bool deleteEleveSpecialite(const int&, const QString&);
    bool deleteEleveModule(const int&, const QString&);

    bool getProfesseurTuteur(const QString&, const QString&, QString&, QString&);
    bool updateProfesseurTuteur(const QString&, const QString&, const int&);

    bool getProfesseurRespModule(const int&, const QString&, QString&, QString&);
    bool updateProfesseurRespModule(const int&, const QString&, const int&);

    double moyenneSpecialiteEleve(const int&, int&);
    double moyenneModuleOptEleve(const int&, int&);
    double moyenneModuleEleve(const int& id, const int& annee, const QString& nomModule);
    bool nonAdmissionEleve(const int&, const int&);



public slots:

    bool open();
    void close();

private:

    QSqlDatabase bdd;
    QSqlQuery* query;
};

#endif // BDD_H
