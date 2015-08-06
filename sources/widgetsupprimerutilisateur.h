#ifndef WIDGETSUPPRIMERUTILISATEUR_H
#define WIDGETSUPPRIMERUTILISATEUR_H

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

class WidgetSupprimerUtilisateur : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSupprimerUtilisateur(Modele*, QWidget *parent = 0);

signals:

public slots:

    bool setUtilisateur();
    void reset();
    void removeUtilisateur();

private:
    QGroupBox* groupBoxRechercherUtilisateur;
    QGroupBox* groupBoxUtilisateur;
    QGroupBox* groupBoxEleve;
    QGroupBox* groupBoxModuleOpt1;
    QGroupBox* groupBoxModuleOpt2;
    QGroupBox* groupBoxModuleOpt3;

    QGridLayout* layoutPrincipal;
    QGridLayout* layoutRechercherUtilisateur;
    QGridLayout* layoutUtilisateur;
    QGridLayout* layoutEleve;
    QVBoxLayout* layoutModuleOpt1;
    QVBoxLayout* layoutModuleOpt2;
    QVBoxLayout* layoutModuleOpt3;

    Modele* modele;
    QStringList* listPrenom;

    QLabel* rechercheNom;
    QLabel* recherchePrenom;
    QLabel* typeUtilisateur;
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
    QComboBox* getTypeUtilisateur;
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
    QPushButton* boutonSupprimer;
    QMessageBox* msg;
};

#endif // WIDGETSUPPRIMERUTILISATEUR_H
