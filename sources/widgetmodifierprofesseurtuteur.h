#ifndef WIDGETMODIFIERPROFESSEURTUTEUR_H
#define WIDGETMODIFIERPROFESSEURTUTEUR_H

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

class WidgetModifierProfesseurTuteur : public QWidget
{
    Q_OBJECT
public:
    WidgetModifierProfesseurTuteur(Modele*, QWidget* = 0);

signals:

public slots:

    bool setEleve();
    bool setProfesseurTuteur();
    void resetEleve();
    void resetProfesseurTuteur();
    void updateProfesseurTuteur();

private:

    QGroupBox* groupBoxRechercherEleve;
    QGroupBox* groupBoxRechercherProfesseurTuteur;
    QGroupBox* groupBoxProfesseurTuteur;


    QGridLayout* layoutPrincipal;
    QGridLayout* layoutRechercherEleve;
    QGridLayout* layoutRechercherProfesseurTuteur;
    QGridLayout* layoutProfesseurTuteur;

    Modele* modele;
    QStringList* listPrenom;
    QStringList* listPrenomProfesseurTuteur;

    QLabel* rechercheNom;
    QLabel* recherchePrenom;
    QLabel* rechercheNomProfesseurTuteur;
    QLabel* recherchePrenomProfesseurTuteur;
    QLabel* idProfesseurTuteur;
    QLabel* dateNaissanceProfesseurTuteur;
    QLabel* adresseProfesseurTuteur;
    QLabel* telephoneProfesseurTuteur;

    QLineEdit* getRechercheNom;
    QComboBox* getRecherchePrenom;
    QLineEdit* getRechercheNomProfesseurTuteur;
    QComboBox* getRecherchePrenomProfesseurTuteur;
    QSpinBox* getIdProfesseurTuteur;
    QDateEdit* getDateNaissanceProfesseurTuteur;
    QLineEdit* getAdresseProfesseurTuteur;
    QLineEdit* getTelephoneProfesseurTuteur;

    QPushButton* boutonRechercher;
    QPushButton* boutonRechercherProfesseur;
    QPushButton* boutonModifier;
    QMessageBox* msg;
};

#endif // WIDGETMODIFIERPROFESSEURTUTEUR_H
