#ifndef WIDGETMODIFIERPROFESSEURRESP_H
#define WIDGETMODIFIERPROFESSEURRESP_H

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

class WidgetModifierProfesseurResp : public QWidget
{
    Q_OBJECT
public:
    WidgetModifierProfesseurResp(Modele*, QWidget* = 0);

signals:

public slots:

    void setModule(int);
    void setModule();
    bool setProfesseurResp();
    void resetProfesseurResp();
    void updateProfesseurResp();

private:

    QGroupBox* groupBoxModule;
    QGroupBox* groupBoxRechercherProfesseurResp;
    QGroupBox* groupBoxProfesseurResp;

    QGridLayout* layoutPrincipal;
    QGridLayout* layoutModule;
    QGridLayout* layoutRechercherProfesseurResp;
    QGridLayout* layoutProfesseurResp;

    Modele* modele;
    QStringList* listModule;
    QStringList* listPrenomProfesseurResp;

    QLabel* annee;
    QLabel* module;
    QLabel* rechercheNomProfesseurResp;
    QLabel* recherchePrenomProfesseurResp;
    QLabel* idProfesseurResp;
    QLabel* dateNaissanceProfesseurResp;
    QLabel* adresseProfesseurResp;
    QLabel* telephoneProfesseurResp;

    QSpinBox* getAnnee;
    QComboBox* getModule;
    QLineEdit* getRechercheNomProfesseurResp;
    QComboBox* getRecherchePrenomProfesseurResp;
    QSpinBox* getIdProfesseurResp;
    QDateEdit* getDateNaissanceProfesseurResp;
    QLineEdit* getAdresseProfesseurResp;
    QLineEdit* getTelephoneProfesseurResp;

    QPushButton* boutonRechercherProfesseur;
    QPushButton* boutonModifier;
    QMessageBox* msg;
};

#endif // WIDGETMODIFIERPROFESSEURRESP_H
