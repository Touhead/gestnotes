#include "widgetsupprimerutilisateur.h"

WidgetSupprimerUtilisateur::WidgetSupprimerUtilisateur(Modele* m, QWidget *parent) :
    modele(m), QWidget(parent)
{
    layoutPrincipal = new QGridLayout;

        groupBoxRechercherUtilisateur = new QGroupBox;
            layoutRechercherUtilisateur = new QGridLayout;
                rechercheNom = new QLabel("Nom*");
                getRechercheNom = new QLineEdit;
                recherchePrenom = new QLabel("Prenom");
                getRecherchePrenom = new QComboBox;

                boutonRechercher = new QPushButton("Rechercher");

            layoutRechercherUtilisateur->addWidget(rechercheNom,0,0);
            layoutRechercherUtilisateur->addWidget(getRechercheNom,0,1);
            layoutRechercherUtilisateur->addWidget(recherchePrenom,1,0);
            layoutRechercherUtilisateur->addWidget(getRecherchePrenom,1,1);
            layoutRechercherUtilisateur->addWidget(boutonRechercher,2,0,1,2);
        groupBoxRechercherUtilisateur->setLayout(layoutRechercherUtilisateur);

        groupBoxUtilisateur = new QGroupBox;
            layoutUtilisateur = new QGridLayout;

                typeUtilisateur = new QLabel("Type d'utilisateur");
                getTypeUtilisateur = new QComboBox;
                id = new QLabel("ID");
                getId = new QSpinBox;
                getId->setMinimum(20000000);
                getId->setMaximum(29999999);
                getId->setReadOnly(true);
                nom = new QLabel("Nom*");
                getNom = new QLineEdit;
                getNom->setReadOnly(true);
                prenom = new QLabel("Prenom*");
                getPrenom = new QLineEdit;
                getPrenom->setReadOnly(true);
                dateNaissance = new QLabel("Date de naissance");
                getDateNaissance = new QDateEdit;
                getDateNaissance->setReadOnly(true);
                adresse = new QLabel("Adresse");
                getAdresse = new QLineEdit;
                getAdresse->setReadOnly(true);
                telephone = new QLabel("Telephone");
                getTelephone = new QLineEdit;
                getTelephone->setReadOnly(true);


            layoutUtilisateur->addWidget(typeUtilisateur,0,0);
            layoutUtilisateur->addWidget(getTypeUtilisateur,0,1);
            layoutUtilisateur->addWidget(nom,1,0);
            layoutUtilisateur->addWidget(getNom,1,1);
            layoutUtilisateur->addWidget(prenom,2,0);
            layoutUtilisateur->addWidget(getPrenom,2,1);
            layoutUtilisateur->addWidget(id,3,0);
            layoutUtilisateur->addWidget(getId,3,1);
            layoutUtilisateur->addWidget(dateNaissance,4,0);
            layoutUtilisateur->addWidget(getDateNaissance,4,1);
            layoutUtilisateur->addWidget(adresse,5,0);
            layoutUtilisateur->addWidget(getAdresse,5,1);
            layoutUtilisateur->addWidget(telephone,6,0);
            layoutUtilisateur->addWidget(getTelephone,6,1);
        groupBoxUtilisateur->setLayout(layoutUtilisateur);

    groupBoxEleve = new QGroupBox;
    layoutEleve = new QGridLayout;

        promotion = new QLabel("Promotion");
        getPromotion = new QSpinBox;
        getPromotion->setMinimum(QDate::currentDate().year());
        getPromotion->setMaximum(QDate::currentDate().year()+2);
        getPrenom->setReadOnly(true);

        specialite = new QLabel("Specialite*");
        getSpecialite = new QComboBox;
        moduleOpt = new QLabel("Modules optionnels*");

        moduleOpt = new QLabel("Modules optionnels");

        groupBoxModuleOpt1 = new QGroupBox("1er annee");
            layoutModuleOpt1 = new QVBoxLayout;
                getModuleOpt1_1 = new QComboBox;
                getModuleOpt1_2 = new QComboBox;
                getModuleOpt1_3 = new QComboBox;
            layoutModuleOpt1->addWidget(getModuleOpt1_1);
            layoutModuleOpt1->addWidget(getModuleOpt1_2);
            layoutModuleOpt1->addWidget(getModuleOpt1_3);
        groupBoxModuleOpt1->setLayout(layoutModuleOpt1);

        groupBoxModuleOpt2 = new QGroupBox("2eme annee");
            layoutModuleOpt2 = new QVBoxLayout;
                getModuleOpt2_1 = new QComboBox;
                getModuleOpt2_2 = new QComboBox;
                getModuleOpt2_3 = new QComboBox;
            layoutModuleOpt2->addWidget(getModuleOpt2_1);
            layoutModuleOpt2->addWidget(getModuleOpt2_2);
            layoutModuleOpt2->addWidget(getModuleOpt2_3);
        groupBoxModuleOpt2->setLayout(layoutModuleOpt2);

        groupBoxModuleOpt3 = new QGroupBox("3eme annnee");
            layoutModuleOpt3 = new QVBoxLayout;
                getModuleOpt3_1 = new QComboBox;
                getModuleOpt3_2 = new QComboBox;
                getModuleOpt3_3 = new QComboBox;
            layoutModuleOpt3->addWidget(getModuleOpt3_1);
            layoutModuleOpt3->addWidget(getModuleOpt3_2);
            layoutModuleOpt3->addWidget(getModuleOpt3_3);
        groupBoxModuleOpt3->setLayout(layoutModuleOpt3);

        nomProfesseurTuteur = new QLabel("Nom du professeur tuteur");
        getNomProfesseurTuteur = new QLineEdit;
        getNomProfesseurTuteur->setReadOnly(true);
        prenomProfesseurTuteur = new QLabel("Prenom du professeur tuteur");
        getPrenomProfesseurTuteur = new QLineEdit;
        getPrenomProfesseurTuteur->setReadOnly(true);

    layoutEleve->addWidget(promotion,0,0);
    layoutEleve->addWidget(getPromotion,0,1);
    layoutEleve->addWidget(specialite,1,0);
    layoutEleve->addWidget(getSpecialite,1,1);
    layoutEleve->addWidget(moduleOpt,2,0,3,1);
    layoutEleve->addWidget(groupBoxModuleOpt1,2,1);
    layoutEleve->addWidget(groupBoxModuleOpt2,3,1);
    layoutEleve->addWidget(groupBoxModuleOpt3,4,1);
    layoutEleve->addWidget(nomProfesseurTuteur,5,0);
    layoutEleve->addWidget(getNomProfesseurTuteur,5,1);
    layoutEleve->addWidget(prenomProfesseurTuteur,6,0);
    layoutEleve->addWidget(getPrenomProfesseurTuteur,6,1);

    groupBoxEleve->setLayout(layoutEleve);

    boutonSupprimer = new QPushButton("Supprimer");

    groupBoxUtilisateur->setVisible(false);
    groupBoxEleve->setVisible(false);
    boutonSupprimer->setVisible(false);

    layoutPrincipal->addWidget(groupBoxRechercherUtilisateur,0,0);
    layoutPrincipal->addWidget(groupBoxUtilisateur,1,0);
    layoutPrincipal->addWidget(groupBoxEleve,2,0);
    layoutPrincipal->addWidget(boutonSupprimer,3,0);


    this->setLayout(layoutPrincipal);

    connect(boutonRechercher,SIGNAL(clicked()),this,SLOT(reset()));
    connect(boutonSupprimer,SIGNAL(clicked()),this,SLOT(removeUtilisateur()));

    listPrenom = 0;

    msg = new QMessageBox(this);
}

bool WidgetSupprimerUtilisateur::setUtilisateur(){

    groupBoxEleve->setVisible(false);
    groupBoxUtilisateur->setVisible(false);
    boutonSupprimer->setVisible(false);

    if (getRechercheNom->text().isEmpty())
        return false;

    if (listPrenom == 0){
        listPrenom = modele->existe(getRechercheNom->text());

        if (listPrenom->size() == 0)
            return false;

        getRecherchePrenom->setModel(new QStringListModel(*listPrenom));

        if (listPrenom->size() > 1)
            connect(getRecherchePrenom,SIGNAL(currentTextChanged(QString)),this,SLOT(setUtilisateur()));
    }

    int tempID;
    QDate tempDateNaissanse;
    QString tempAdresse;
    QString tempTelephone;

    if (modele->isAdministration(getRechercheNom->text(),getRecherchePrenom->currentText())){
        if (!modele->getAdministration(tempID,getRechercheNom->text(),getRecherchePrenom->currentText(),tempDateNaissanse,tempAdresse,tempTelephone))
            return false;

        if (getTypeUtilisateur->count() != 0)
            getTypeUtilisateur->clear();
        getTypeUtilisateur->addItem("Administrateur");
        getNom->setText(getRechercheNom->text());
        getPrenom->setText(getRecherchePrenom->currentText());
        getId->setValue(tempID);
        getDateNaissance->setDate(tempDateNaissanse);
        getAdresse->setText(tempAdresse);
        getTelephone->setText(tempTelephone);

        groupBoxUtilisateur->setVisible(true);
        boutonSupprimer->setVisible(true);
        return true;
    }

    if (modele->isProfesseur(getRechercheNom->text(),getRecherchePrenom->currentText())){
        if (!modele->getProfesseur(tempID,getRechercheNom->text(),getRecherchePrenom->currentText(),tempDateNaissanse,tempAdresse,tempTelephone))
            return false;

        if (getTypeUtilisateur->count() != 0)
            getTypeUtilisateur->clear();

        getTypeUtilisateur->addItem("Professeur");
        getNom->setText(getRechercheNom->text());
        getPrenom->setText(getRecherchePrenom->currentText());
        getId->setValue(tempID);
        getDateNaissance->setDate(tempDateNaissanse);
        getAdresse->setText(tempAdresse);
        getTelephone->setText(tempTelephone);

        groupBoxUtilisateur->setVisible(true);
        boutonSupprimer->setVisible(true);
        return true;
    }

    int tempPromotion;
    QString tempSpecialite;
    QString tempModuleOpt1_1;
    QString tempModuleOpt1_2;
    QString tempModuleOpt1_3;
    QString tempModuleOpt2_1;
    QString tempModuleOpt2_2;
    QString tempModuleOpt2_3;
    QString tempModuleOpt3_1;
    QString tempModuleOpt3_2;
    QString tempModuleOpt3_3;
    QString tempNomProfesseurTuteur;
    QString tempPrenomProfesseurTuteur;

    if (modele->isEleve(getRechercheNom->text(),getRecherchePrenom->currentText())){
        if (!modele->getEleve(tempID,getRechercheNom->text(),getRecherchePrenom->currentText(),tempDateNaissanse,tempAdresse,tempTelephone,tempPromotion,tempSpecialite,tempModuleOpt1_1,tempModuleOpt1_2,tempModuleOpt1_3,tempModuleOpt2_1,tempModuleOpt2_2,tempModuleOpt2_3,tempModuleOpt3_1,tempModuleOpt3_2,tempModuleOpt3_3,tempNomProfesseurTuteur,tempPrenomProfesseurTuteur))
            return false;

        if (getTypeUtilisateur->count() != 0)
            getTypeUtilisateur->clear();
        getTypeUtilisateur->addItem("Eleve");
        getNom->setText(getRechercheNom->text());
        getPrenom->setText(getRecherchePrenom->currentText());
        getId->setValue(tempID);
        getDateNaissance->setDate(tempDateNaissanse);
        getAdresse->setText(tempAdresse);
        getTelephone->setText(tempTelephone);
        getPromotion->setValue(tempPromotion);

        if (getSpecialite->count() != 0)
            getSpecialite->clear();

        getSpecialite->addItem(tempSpecialite);

        if (getModuleOpt1_1->count() != 0)
            getModuleOpt1_1->clear();
        if (getModuleOpt1_2->count() != 0)
            getModuleOpt1_2->clear();
        if (getModuleOpt1_3->count() != 0)
            getModuleOpt1_3->clear();
        if (getModuleOpt2_1->count() != 0)
            getModuleOpt2_1->clear();
        if (getModuleOpt2_2->count() != 0)
            getModuleOpt2_2->clear();
        if (getModuleOpt2_3->count() != 0)
            getModuleOpt2_3->clear();
        if (getModuleOpt3_1->count() != 0)
            getModuleOpt3_1->clear();
        if (getModuleOpt3_2->count() != 0)
            getModuleOpt3_2->clear();
        if (getModuleOpt3_3->count() != 0)
            getModuleOpt3_3->clear();

        getModuleOpt1_1->addItem(tempModuleOpt1_1);
        getModuleOpt1_2->addItem(tempModuleOpt1_2);
        getModuleOpt1_3->addItem(tempModuleOpt1_3);
        getModuleOpt2_1->addItem(tempModuleOpt2_1);
        getModuleOpt2_2->addItem(tempModuleOpt2_2);
        getModuleOpt2_3->addItem(tempModuleOpt2_3);
        getModuleOpt3_1->addItem(tempModuleOpt3_1);
        getModuleOpt3_2->addItem(tempModuleOpt3_2);
        getModuleOpt3_3->addItem(tempModuleOpt3_3);
        getNomProfesseurTuteur->setText(tempNomProfesseurTuteur);
        getPrenomProfesseurTuteur->setText(tempPrenomProfesseurTuteur);

        groupBoxUtilisateur->setVisible(true);
        groupBoxEleve->setVisible(true);
        boutonSupprimer->setVisible(true);
        return true;
    }

    return false;
}

void WidgetSupprimerUtilisateur::reset(){

    disconnect(getRecherchePrenom,SIGNAL(currentTextChanged(QString)),this,SLOT(setUtilisateur()));

    if (getRecherchePrenom->count() != 0)
        getRecherchePrenom->clear();

    delete listPrenom;
    listPrenom = 0;

    setUtilisateur();
}

void WidgetSupprimerUtilisateur::removeUtilisateur(){

    if (getId->text().isEmpty()){
        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'administrateur " + getPrenom->text() + " " + getNom->text() + " n'a pas été supprimé");
        msg->show();
        return;
    }

    if (getTypeUtilisateur->currentText() == "Administrateur"){
        if (modele->deleteAdministration(getId->value())){

            msg->setIcon(QMessageBox::Information);
            msg->setText("L'administrateur " + getPrenom->text() + " " + getNom->text() + " a bien été supprimé");
            msg->show();
            return;
        }

        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'administrateur " + getPrenom->text() + " " + getNom->text() + " n'a pas été supprimé");
        msg->show();
        return;
    }

    if (getTypeUtilisateur->currentText() == "Professeur"){
        if (modele->deleteProfesseur(getId->value())){

            msg->setIcon(QMessageBox::Information);
            msg->setText("Le professeur " + getPrenom->text() + " " + getNom->text() + " a bien été supprimé");
            msg->show();
            return;
        }

        msg->setIcon(QMessageBox::Critical);
        msg->setText("Le professeur " + getPrenom->text() + " " + getNom->text() + " n'a pas été supprimé");
        msg->show();
        return;
    }

    if (getTypeUtilisateur->currentText() == "Eleve"){
        if (modele->deleteEleve(getId->value())){

            msg->setIcon(QMessageBox::Information);
            msg->setText("L'eleve " + getPrenom->text() + " " + getNom->text() + " a bien été supprimé");
            msg->show();
            return;
        }

        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'eleve " + getPrenom->text() + " " + getNom->text() + " n'a pas été supprimé");
        msg->show();
        return;
    }

    return;
}
