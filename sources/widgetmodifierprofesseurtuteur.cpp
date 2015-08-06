#include "widgetmodifierprofesseurtuteur.h"

WidgetModifierProfesseurTuteur::WidgetModifierProfesseurTuteur(Modele* m, QWidget *parent) :
    modele(m), QWidget(parent)
{
    layoutPrincipal = new QGridLayout;

        groupBoxRechercherEleve = new QGroupBox;
            layoutRechercherEleve = new QGridLayout;
                rechercheNom = new QLabel("Nom*");
                getRechercheNom = new QLineEdit;
                recherchePrenom = new QLabel("Prenom");
                getRecherchePrenom = new QComboBox;

                boutonRechercher = new QPushButton("Rechercher");

            layoutRechercherEleve->addWidget(rechercheNom,0,0);
            layoutRechercherEleve->addWidget(getRechercheNom,0,1);
            layoutRechercherEleve->addWidget(recherchePrenom,1,0);
            layoutRechercherEleve->addWidget(getRecherchePrenom,1,1);
            layoutRechercherEleve->addWidget(boutonRechercher,2,0,1,2);
        groupBoxRechercherEleve->setLayout(layoutRechercherEleve);

    groupBoxRechercherProfesseurTuteur = new QGroupBox;
    layoutRechercherProfesseurTuteur = new QGridLayout;

        rechercheNomProfesseurTuteur = new QLabel("Nom du professeur tuteur");
        getRechercheNomProfesseurTuteur = new QLineEdit;
        recherchePrenomProfesseurTuteur = new QLabel("Prenom du professeur tuteur");
        getRecherchePrenomProfesseurTuteur = new QComboBox;

        boutonRechercherProfesseur = new QPushButton("Rechercher Professeur");

    layoutRechercherProfesseurTuteur->addWidget(rechercheNomProfesseurTuteur,1,0);
    layoutRechercherProfesseurTuteur->addWidget(getRechercheNomProfesseurTuteur,1,1);
    layoutRechercherProfesseurTuteur->addWidget(recherchePrenomProfesseurTuteur,2,0);
    layoutRechercherProfesseurTuteur->addWidget(getRecherchePrenomProfesseurTuteur,2,1);
    layoutRechercherProfesseurTuteur->addWidget(boutonRechercherProfesseur,3,0,1,2);

    groupBoxRechercherProfesseurTuteur->setLayout(layoutRechercherProfesseurTuteur);

    groupBoxProfesseurTuteur = new QGroupBox;
    layoutProfesseurTuteur = new QGridLayout;

        idProfesseurTuteur = new QLabel("ID du professeur tuteur");
        getIdProfesseurTuteur = new QSpinBox;
        getIdProfesseurTuteur->setMinimum(20000000);
        getIdProfesseurTuteur->setMaximum(29999999);
        getIdProfesseurTuteur->setReadOnly(true);

        dateNaissanceProfesseurTuteur = new QLabel("Date de naissance");
        getDateNaissanceProfesseurTuteur = new QDateEdit;
        getDateNaissanceProfesseurTuteur->setReadOnly(true);
        adresseProfesseurTuteur = new QLabel("Adresse");
        getAdresseProfesseurTuteur = new QLineEdit;
        getAdresseProfesseurTuteur->setReadOnly(true);
        telephoneProfesseurTuteur = new QLabel("Telephone");
        getTelephoneProfesseurTuteur = new QLineEdit;
        getTelephoneProfesseurTuteur->setReadOnly(true);

    layoutProfesseurTuteur->addWidget(idProfesseurTuteur,3,0);
    layoutProfesseurTuteur->addWidget(getIdProfesseurTuteur,3,1);
    layoutProfesseurTuteur->addWidget(dateNaissanceProfesseurTuteur,4,0);
    layoutProfesseurTuteur->addWidget(getDateNaissanceProfesseurTuteur,4,1);
    layoutProfesseurTuteur->addWidget(adresseProfesseurTuteur,5,0);
    layoutProfesseurTuteur->addWidget(getAdresseProfesseurTuteur,5,1);
    layoutProfesseurTuteur->addWidget(telephoneProfesseurTuteur,6,0);
    layoutProfesseurTuteur->addWidget(getTelephoneProfesseurTuteur,6,1);

    groupBoxProfesseurTuteur->setLayout(layoutProfesseurTuteur);

    boutonModifier = new QPushButton("Modifier");


    groupBoxRechercherProfesseurTuteur->setVisible(false);
    groupBoxProfesseurTuteur->setVisible(false);
    boutonModifier->setVisible(false);

    layoutPrincipal->addWidget(groupBoxRechercherEleve,0,0);
    layoutPrincipal->addWidget(groupBoxRechercherProfesseurTuteur,1,0);
    layoutPrincipal->addWidget(groupBoxProfesseurTuteur,2,0);
    layoutPrincipal->addWidget(boutonModifier,3,0);

    this->setLayout(layoutPrincipal);

    connect(boutonRechercher,SIGNAL(clicked()),this,SLOT(resetEleve()));
    connect(boutonModifier,SIGNAL(clicked()),this,SLOT(updateProfesseurTuteur()));
    connect(boutonRechercherProfesseur,SIGNAL(clicked()),this,SLOT(resetProfesseurTuteur()));

    listPrenom = 0;
    listPrenomProfesseurTuteur = 0;

     msg = new QMessageBox(this);
}

bool WidgetModifierProfesseurTuteur::setEleve(){

    groupBoxRechercherProfesseurTuteur->setVisible(false);
    groupBoxProfesseurTuteur->setVisible(false);
    boutonModifier->setVisible(false);


    if (getRechercheNom->text().isEmpty())
        return false;

    if (listPrenom == 0){
        listPrenom = modele->existe(getRechercheNom->text());

        for(int i = 0; i < listPrenom->size(); i++){

            if (!modele->isEleve(getRechercheNom->text(),listPrenom->at(i))){
                listPrenom->removeAt(i);
                i--;
            }
        }

        if (listPrenom->size() == 0)
            return false;

        getRecherchePrenom->setModel(new QStringListModel(*listPrenom));

        if (listPrenom->size() > 1)
            connect(getRecherchePrenom,SIGNAL(currentTextChanged(QString)),this,SLOT(setEleve()));
    }

    //int tempIdProfesseurTuteur;
    QString tempNomProfesseurTuteur;
    QString tempPrenomProfesseurTuteur;

    modele->getProfesseurTuteur(getRechercheNom->text(),getRecherchePrenom->currentText(),tempNomProfesseurTuteur,tempPrenomProfesseurTuteur);

    getRechercheNomProfesseurTuteur->setText(tempNomProfesseurTuteur);

    if (getRecherchePrenomProfesseurTuteur->count() != 0)
        getRecherchePrenomProfesseurTuteur->clear();

    getRecherchePrenomProfesseurTuteur->addItem(tempPrenomProfesseurTuteur);

    connect(getRechercheNomProfesseurTuteur,SIGNAL(editingFinished()),this,SLOT(setProfesseurTuteur()));

    groupBoxRechercherEleve->setVisible(true);
    groupBoxRechercherProfesseurTuteur->setVisible(true);


    resetProfesseurTuteur();

    return true;
}

bool WidgetModifierProfesseurTuteur::setProfesseurTuteur(){

    groupBoxProfesseurTuteur->setVisible(false);
    boutonModifier->setVisible(false);

    if (getRechercheNomProfesseurTuteur->text().isEmpty())
        return false;

    if (listPrenomProfesseurTuteur == 0){

        listPrenomProfesseurTuteur = modele->existe(getRechercheNomProfesseurTuteur->text());

        for(int i = 0; i < listPrenomProfesseurTuteur->size(); i++){

            if (!modele->isProfesseur(getRechercheNomProfesseurTuteur->text(),listPrenomProfesseurTuteur->at(i))){
                listPrenomProfesseurTuteur->removeAt(i);
                i--;
            }
        }

        if (listPrenomProfesseurTuteur->size() == 0)
            return false;

        getRecherchePrenomProfesseurTuteur->setModel(new QStringListModel(*listPrenomProfesseurTuteur));

        if (listPrenomProfesseurTuteur->size() > 1)
            connect(getRecherchePrenomProfesseurTuteur,SIGNAL(currentTextChanged(QString)),this,SLOT(setProfesseurTuteur()));
    }

    int tempIdProfesseurTuteur;
    QDate tempDateNaissanseProfesseurTuteur;
    QString tempAdresseProfesseurTuteur;
    QString tempTelephoneProfesseurTuteur;

    if (!modele->getProfesseur(tempIdProfesseurTuteur,getRechercheNomProfesseurTuteur->text(),getRecherchePrenomProfesseurTuteur->currentText(),tempDateNaissanseProfesseurTuteur,tempAdresseProfesseurTuteur,tempTelephoneProfesseurTuteur))
        return false;

    getIdProfesseurTuteur->setValue(tempIdProfesseurTuteur);
    getDateNaissanceProfesseurTuteur->setDate(tempDateNaissanseProfesseurTuteur);
    getAdresseProfesseurTuteur->setText(tempAdresseProfesseurTuteur);
    getTelephoneProfesseurTuteur->setText(tempTelephoneProfesseurTuteur);

    groupBoxProfesseurTuteur->setVisible(true);
    boutonModifier->setVisible(true);

    return true;
}

void WidgetModifierProfesseurTuteur::resetEleve(){

    disconnect(getRecherchePrenom,SIGNAL(currentTextChanged(QString)),this,SLOT(setEleve()));

    if (getRecherchePrenom->count() != 0)
        getRecherchePrenom->clear();

    delete listPrenom;
    listPrenom = 0;

    setEleve();
}

void WidgetModifierProfesseurTuteur::resetProfesseurTuteur(){

    disconnect(getRecherchePrenomProfesseurTuteur,SIGNAL(currentTextChanged(QString)),this,SLOT(setProfesseurTuteur()));

    if (getRecherchePrenomProfesseurTuteur->count() != 0)
        getRecherchePrenomProfesseurTuteur->clear();

    delete listPrenomProfesseurTuteur;
    listPrenomProfesseurTuteur = 0;

    setProfesseurTuteur();
}

void WidgetModifierProfesseurTuteur::updateProfesseurTuteur(){

    if (getRechercheNomProfesseurTuteur->text().isEmpty()){
        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() + " n'a pas été modifié");
        msg->show();
        return;
    }
    if (getRecherchePrenomProfesseurTuteur->currentText().isEmpty()){
        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() + " n'a pas été modifié");
        msg->show();
        return;
    }

    if (modele->updateProfesseurTuteur(getRechercheNom->text(),getRecherchePrenom->currentText(),getIdProfesseurTuteur->value())){

        msg->setIcon(QMessageBox::Information);
        msg->setText("L'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() + " a bien été modifié");
        msg->show();
        return;
    }

    msg->setIcon(QMessageBox::Critical);
    msg->setText("L'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() + " n'a pas été modifié");
    msg->show();
    return;

    return;
}
