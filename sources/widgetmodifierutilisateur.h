#ifndef WIDGETMODIFIERUTILISATEUR_H
#define WIDGETMODIFIERUTILISATEUR_H

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

class WidgetModifierUtilisateur : public QWidget
{
    Q_OBJECT
public:
    WidgetModifierUtilisateur(Modele*, QWidget* = 0);

signals:

public slots:

    void setGroupBoxModuleOpt(QString);
    bool setUtilisateur();
    void reset();
    void updateUtilisateur();

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
    QStringList* listSpecialite;
    QStringList* listModuleOpt1;
    QStringList* listModuleOpt2;
    QStringList* listModuleOpt3;
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
    QPushButton* boutonModifier;
    QMessageBox* msg;
};

#endif // WIDGETMODIFIERUTILISATEUR_H
