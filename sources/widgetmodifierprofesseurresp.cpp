#include "widgetmodifierprofesseurresp.h"

WidgetModifierProfesseurResp::WidgetModifierProfesseurResp(Modele* m, QWidget *parent) :
    modele(m), QWidget(parent)
{
    layoutPrincipal = new QGridLayout;

        groupBoxModule = new QGroupBox;
            layoutModule = new QGridLayout;

            annee = new QLabel("Annee");
            getAnnee = new QSpinBox;
            getAnnee->setMinimum(1);
            getAnnee->setMaximum(3);

            module = new QLabel("Module");
            getModule = new QComboBox;

            layoutModule->addWidget(annee,0,0);
            layoutModule->addWidget(getAnnee,0,1);
            layoutModule->addWidget(module,1,0);
            layoutModule->addWidget(getModule,1,1);
        groupBoxModule->setLayout(layoutModule);

    groupBoxRechercherProfesseurResp = new QGroupBox;
    layoutRechercherProfesseurResp = new QGridLayout;

        rechercheNomProfesseurResp = new QLabel("Nom du professeur tuteur");
        getRechercheNomProfesseurResp = new QLineEdit;
        recherchePrenomProfesseurResp = new QLabel("Prenom du professeur tuteur");
        getRecherchePrenomProfesseurResp = new QComboBox;

        boutonRechercherProfesseur = new QPushButton("Rechercher Professeur");

    layoutRechercherProfesseurResp->addWidget(rechercheNomProfesseurResp,1,0);
    layoutRechercherProfesseurResp->addWidget(getRechercheNomProfesseurResp,1,1);
    layoutRechercherProfesseurResp->addWidget(recherchePrenomProfesseurResp,2,0);
    layoutRechercherProfesseurResp->addWidget(getRecherchePrenomProfesseurResp,2,1);
    layoutRechercherProfesseurResp->addWidget(boutonRechercherProfesseur,3,0,1,2);

    groupBoxRechercherProfesseurResp->setLayout(layoutRechercherProfesseurResp);

    groupBoxProfesseurResp = new QGroupBox;
    layoutProfesseurResp = new QGridLayout;

        idProfesseurResp = new QLabel("ID du professeur tuteur");
        getIdProfesseurResp = new QSpinBox;
        getIdProfesseurResp->setMinimum(20000000);
        getIdProfesseurResp->setMaximum(29999999);
        getIdProfesseurResp->setReadOnly(true);

        dateNaissanceProfesseurResp = new QLabel("Date de naissance");
        getDateNaissanceProfesseurResp = new QDateEdit;
        getDateNaissanceProfesseurResp->setReadOnly(true);
        adresseProfesseurResp = new QLabel("Adresse");
        getAdresseProfesseurResp = new QLineEdit;
        getAdresseProfesseurResp->setReadOnly(true);
        telephoneProfesseurResp = new QLabel("Telephone");
        getTelephoneProfesseurResp = new QLineEdit;
        getTelephoneProfesseurResp->setReadOnly(true);

    layoutProfesseurResp->addWidget(idProfesseurResp,3,0);
    layoutProfesseurResp->addWidget(getIdProfesseurResp,3,1);
    layoutProfesseurResp->addWidget(getDateNaissanceProfesseurResp,4,0);
    layoutProfesseurResp->addWidget(getDateNaissanceProfesseurResp,4,1);
    layoutProfesseurResp->addWidget(adresseProfesseurResp,5,0);
    layoutProfesseurResp->addWidget(getAdresseProfesseurResp,5,1);
    layoutProfesseurResp->addWidget(telephoneProfesseurResp,6,0);
    layoutProfesseurResp->addWidget(getTelephoneProfesseurResp,6,1);

    groupBoxProfesseurResp->setLayout(layoutProfesseurResp);

    boutonModifier = new QPushButton("Modifier");

    groupBoxProfesseurResp->setVisible(false);
    boutonModifier->setVisible(false);

    layoutPrincipal->addWidget(groupBoxModule,0,0);
    layoutPrincipal->addWidget(groupBoxRechercherProfesseurResp,1,0);
    layoutPrincipal->addWidget(groupBoxProfesseurResp,2,0);
    layoutPrincipal->addWidget(boutonModifier,3,0);

    this->setLayout(layoutPrincipal);

    connect(getAnnee,SIGNAL(valueChanged(int)),this,SLOT(setModule(int)));
    connect(getModule,SIGNAL(currentTextChanged(QString)),this,SLOT(setModule()));
    connect(boutonRechercherProfesseur,SIGNAL(clicked()),this,SLOT(resetProfesseurResp()));
    connect(boutonModifier,SIGNAL(clicked()),this,SLOT(updateProfesseurResp()));

    setModule(getAnnee->value());

     msg = new QMessageBox(this);
}

void WidgetModifierProfesseurResp::setModule(int annee){

    if (listModule != 0)
        delete listModule;
    listModule = modele->getModule(annee);
    delete getModule->model();
    getModule->setModel(new QStringListModel(*listModule));
}

void WidgetModifierProfesseurResp::setModule(){

    QString tempNomProfesseurResp;
    QString tempPrenomProfesseurResp;

    modele->getProfesseurRespModule(getAnnee->value(),getModule->currentText(),tempNomProfesseurResp,tempPrenomProfesseurResp);

    getRechercheNomProfesseurResp->setText(tempNomProfesseurResp);

    if (getRecherchePrenomProfesseurResp->count() != 0)
        getRecherchePrenomProfesseurResp->clear();
    getRecherchePrenomProfesseurResp->addItem(tempPrenomProfesseurResp);

    resetProfesseurResp();
}

bool WidgetModifierProfesseurResp::setProfesseurResp(){

    groupBoxProfesseurResp->setVisible(false);
    boutonModifier->setVisible(false);

    if (getModule->currentText().isEmpty())
        return false;

    if (listPrenomProfesseurResp == 0){

        listPrenomProfesseurResp = modele->existe(getRechercheNomProfesseurResp->text());

        for(int i = 0; i < listPrenomProfesseurResp->size(); i++){

            if (!modele->isProfesseur(getRechercheNomProfesseurResp->text(),listPrenomProfesseurResp->at(i))){
                listPrenomProfesseurResp->removeAt(i);
                i--;
            }
        }

        if (listPrenomProfesseurResp->size() == 0)
            return false;

        getRecherchePrenomProfesseurResp->setModel(new QStringListModel(*listPrenomProfesseurResp));

        if (listPrenomProfesseurResp->size() > 1)
            connect(getRecherchePrenomProfesseurResp,SIGNAL(currentTextChanged(QString)),this,SLOT(setProfesseurResp()));
    }

    int tempIdProfesseurResp;
    QDate tempDateNaissanseProfesseurResp;
    QString tempAdresseProfesseurResp;
    QString tempTelephoneProfesseurResp;

    if (!modele->getProfesseur(tempIdProfesseurResp,getRechercheNomProfesseurResp->text(),getRecherchePrenomProfesseurResp->currentText(),tempDateNaissanseProfesseurResp,tempAdresseProfesseurResp,tempTelephoneProfesseurResp))
        return false;

    getIdProfesseurResp->setValue(tempIdProfesseurResp);
    getDateNaissanceProfesseurResp->setDate(tempDateNaissanseProfesseurResp);
    getAdresseProfesseurResp->setText(tempAdresseProfesseurResp);
    getTelephoneProfesseurResp->setText(tempTelephoneProfesseurResp);

    groupBoxProfesseurResp->setVisible(true);
    boutonModifier->setVisible(true);

    return true;
}

void WidgetModifierProfesseurResp::resetProfesseurResp(){

    disconnect(getRecherchePrenomProfesseurResp,SIGNAL(currentTextChanged(QString)),this,SLOT(setProfesseurResp()));

    if (getRecherchePrenomProfesseurResp->count() != 0)
        getRecherchePrenomProfesseurResp->clear();

    delete listPrenomProfesseurResp;
    listPrenomProfesseurResp = 0;

    setProfesseurResp();
}

void WidgetModifierProfesseurResp::updateProfesseurResp(){

    if (getRechercheNomProfesseurResp->text().isEmpty()){
        msg->setIcon(QMessageBox::Critical);
        msg->setText("Le professeur reponsable du module " + getModule->currentText() + " n'a pas été modifié");
        msg->show();
        return;
    }
    if (getRecherchePrenomProfesseurResp->currentText().isEmpty()){
        msg->setIcon(QMessageBox::Critical);
        msg->setText("Le professeur reponsable du module " + getModule->currentText() + " n'a pas été modifié");
        msg->show();
        return;
    }

    if (modele->updateProfesseurRespModule(getAnnee->value(),getModule->currentText(),getIdProfesseurResp->value())){

        msg->setIcon(QMessageBox::Information);
        msg->setText("Le professeur reponsable du module " + getModule->currentText() + " a bien été modifié");
        msg->show();
        return;
    }

    msg->setIcon(QMessageBox::Critical);
    msg->setText("Le professeur reponsable du module " + getModule->currentText() + " n'a pas été modifié");
    msg->show();
    return;

    return;
}
