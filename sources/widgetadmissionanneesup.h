#ifndef WIDGETADMISSIONANNEESUP_H
#define WIDGETADMISSIONANNEESUP_H

#include <QWidget>
#include <QLabel>
#include <QDate>
#include <QLineEdit>
#include <QDateEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QStringListModel>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QSpinBox>
#include <QStringList>
#include "modele.h"

class WidgetAdmissionAnneeSup : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetAdmissionAnneeSup(Modele*, QWidget* = 0);

signals:

public slots:

    bool setEleve();
    void resetEleve();
    void admissible();
    void nonAdmission();

private:

    QGroupBox* groupBoxRechercherEleve;
    QGroupBox* groupBoxUtilisateur;
    QGroupBox* groupBoxEleve;
    QGroupBox* groupBoxModuleOpt1;
    QGroupBox* groupBoxModuleOpt2;
    QGroupBox* groupBoxModuleOpt3;

    QGridLayout* layoutPrincipal;
    QGridLayout* layoutRechercherEleve;
    QGridLayout* layoutUtilisateur;
    QGridLayout* layoutEleve;
    QVBoxLayout* layoutModuleOpt1;
    QVBoxLayout* layoutModuleOpt2;
    QVBoxLayout* layoutModuleOpt3;

    Modele* modele;
    QStringList* listPrenom;

    QLabel* rechercheNom;
    QLabel* recherchePrenom;
    QLabel* id;
    QLabel* nom;
    QLabel* prenom;
    QLabel* dateNaissance;
    QLabel* adresse;
    QLabel* telephone;
    QLabel* promotion;
    QLabel* specialite;
    QLabel* moduleOpt;
    QLabel* nomProfesseurTuteur;
    QLabel* prenomProfesseurTuteur;

    QLineEdit* getRechercheNom;
    QComboBox* getRecherchePrenom;
    QSpinBox* getId;
    QLineEdit* getNom;
    QLineEdit* getPrenom;
    QDateEdit* getDateNaissance;
    QLineEdit* getAdresse;
    QLineEdit* getTelephone;
    QSpinBox* getPromotion;
    QComboBox* getSpecialite;
    QComboBox* getModuleOpt1_1;
    QComboBox* getModuleOpt1_2;
    QComboBox* getModuleOpt1_3;
    QComboBox* getModuleOpt2_1;
    QComboBox* getModuleOpt2_2;
    QComboBox* getModuleOpt2_3;
    QComboBox* getModuleOpt3_1;
    QComboBox* getModuleOpt3_2;
    QComboBox* getModuleOpt3_3;
    QLineEdit* getNomProfesseurTuteur;
    QLineEdit* getPrenomProfesseurTuteur;

    QPushButton* boutonRechercher;
    QPushButton* boutonAdmissible;
    QPushButton* boutonNonAdmission;
    QMessageBox* msg;

};

#endif // WIDGETADMISSIONANNEESUP_H
