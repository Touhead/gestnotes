#ifndef MODELE_H
#define MODELE_H

#include <QObject>
#include <QDockWidget>
#include <QActionGroup>
#include <bdd.h>
#include <personne.h>

class Modele : public QObject
{
    Q_OBJECT
public:
    Modele(const QString& host, const QString& user, const QString& password, const QString& dataBase, const int& id);
    virtual ~Modele();

    const int& getId();

    QStringList* existe(const QString&, const QString& = "");
    bool isEleve(const QString&, const QString&);
    bool isProfesseur(const QString&, const QString&);
    bool isAdministration(const QString&, const QString&);

    QStringList* getModule(const int& = 0);
    QStringList* getModuleOpt(const QString&, const int&) const;
    QStringList* getSpecialite();

    bool createDockDonnee(QDockWidget*, QActionGroup*) const;
    bool createDockOutil(QDockWidget*, QActionGroup*) const;
    QAbstractTableModel* getModele(QAction*) const;
    QWidget* getFenetre(QAction*) const;

    bool insertAdministration(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&);
    bool insertProfesseur(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&);
    bool insertEleve(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&, const int&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const int& = 0);

    bool getAdministration(int&, const QString&, const QString&, QDate&, QString&, QString&);
    bool getProfesseur(int&, const QString&, const QString&, QDate&, QString&, QString&);
    bool getEleve(int&, const QString&, const QString&, QDate&, QString&, QString&, int&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&);
    bool getEleve(const int&, QString&, QString&, QDate&, QString&, QString&, int&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&);

    bool updateAdministration(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&);
    bool updateProfesseur(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&);
    bool updateEleve(const int&, const QString&, const QString&, const QDate&, const QString&, const QString&, const int&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const int& = 0);

    bool deleteAdministration(const int&);
    bool deleteProfesseur(const int&);
    bool deleteEleve(const int&);

    bool getProfesseurTuteur(const QString&, const QString&, QString&, QString&);
    bool updateProfesseurTuteur(const QString&, const QString&, const int&);

    bool getProfesseurRespModule(const int&, const QString&, QString&, QString&);
    bool updateProfesseurRespModule(const int&, const QString&, const int&);

    double moyenneSpecialiteEleve(const int&, int&);
    double moyenneModuleOptEleve(const int&, int&);

    bool nonAdmissionEleve(const int&, const int&);

signals:

public slots:

    void mettreAJour();

private:

    Bdd* bdd;
    Personne* p;
};

#endif // MODELE_H
