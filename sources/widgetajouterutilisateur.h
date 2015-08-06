#ifndef WIDGETAJOUTERUTILISATEUR_H
#define WIDGETAJOUTERUTILISATEUR_H

#include <QLabel>
#include <QDate>
#include <QLineEdit>
#include <QDateEdit>
#include <QGridLayout>
#include <QWidget>
#include <QGroupBox>
#include <QStringListModel>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QSpinBox>
#include "modele.h"

class WidgetAjouterUtilisateur : public QWidget
{
    Q_OBJECT

public:
    WidgetAjouterUtilisateur(Modele*, QWidget* = 0);

public slots:

    void setGroupBoxTypeUtilisateur(QString);
    void setGroupBoxModuleOpt(QString);
    void insertUtilisateur();

private:

    QGroupBox* groupBoxUtilisateur;
    QGroupBox* groupBoxEleve;
    QGroupBox* groupBoxModuleOpt1;
    QGroupBox* groupBoxModuleOpt2;
    QGroupBox* groupBoxModuleOpt3;

    QGridLayout* layoutPrincipal;
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

    QPushButton* boutonAjouter;
    QMessageBox* msg;
};

#endif // WIDGETAJOUTERUTILISATEUR_H
