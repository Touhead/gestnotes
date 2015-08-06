#include "widgetadmissionanneesup.h"

WidgetAdmissionAnneeSup::WidgetAdmissionAnneeSup(Modele* m, QWidget *parent) :
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

        groupBoxUtilisateur = new QGroupBox;
            layoutUtilisateur = new QGridLayout;

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
            getPromotion->setReadOnly(true);

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

        boutonAdmissible = new QPushButton("Admissible");
        boutonNonAdmission = new QPushButton("Non admission");

    groupBoxUtilisateur->setVisible(false);
    groupBoxEleve->setVisible(false);
    boutonAdmissible->setVisible(false);
    boutonNonAdmission->setVisible(false);

    layoutPrincipal->addWidget(groupBoxRechercherEleve,0,0);
    layoutPrincipal->addWidget(groupBoxUtilisateur,1,0);
    layoutPrincipal->addWidget(groupBoxEleve,2,0);
    layoutPrincipal->addWidget(boutonAdmissible,3,0);
    layoutPrincipal->addWidget(boutonNonAdmission,4,0);

    this->setLayout(layoutPrincipal);

    connect(boutonRechercher,SIGNAL(clicked()),this,SLOT(resetEleve()));
    connect(boutonAdmissible,SIGNAL(clicked()),this,SLOT(admissible()));
    connect(boutonNonAdmission,SIGNAL(clicked()),this,SLOT(nonAdmission()));

    listPrenom = 0;

    msg = new QMessageBox(this);
}

bool WidgetAdmissionAnneeSup::setEleve(){

    groupBoxUtilisateur->setVisible(false);
    groupBoxEleve->setVisible(false);
    boutonAdmissible->setVisible(false);
    boutonNonAdmission->setVisible(false);

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

    int tempID;
    QDate tempDateNaissanse;
    QString tempAdresse;
    QString tempTelephone;
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

    if (!modele->getEleve(tempID,getRechercheNom->text(),getRecherchePrenom->currentText(),tempDateNaissanse,tempAdresse,tempTelephone,tempPromotion,tempSpecialite,tempModuleOpt1_1,tempModuleOpt1_2,tempModuleOpt1_3,tempModuleOpt2_1,tempModuleOpt2_2,tempModuleOpt2_3,tempModuleOpt3_1,tempModuleOpt3_2,tempModuleOpt3_3,tempNomProfesseurTuteur,tempPrenomProfesseurTuteur))
        return false;

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
    boutonAdmissible->setVisible(true);
    return true;
}

void WidgetAdmissionAnneeSup::resetEleve(){

    disconnect(getRecherchePrenom,SIGNAL(currentTextChanged(QString)),this,SLOT(setEleve()));

    if (getRecherchePrenom->count() != 0)
        getRecherchePrenom->clear();

    delete listPrenom;
    listPrenom = 0;

    setEleve();
}

void WidgetAdmissionAnneeSup::admissible(){

    int ponderationMoyenneSpecialite;
    double moyenneSpecialite;
    int ponderationMoyenneModuleOpt;
    double moyenneModuleOpt;

    moyenneSpecialite = modele->moyenneSpecialiteEleve(getId->value(),ponderationMoyenneSpecialite);

    if (moyenneSpecialite == -1){

        msg->setIcon(QMessageBox::Warning);
        msg->setText("Impossible de calculer la moyenne de l'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() + " pour l'instant");
        msg->show();
        return;
    }

    moyenneModuleOpt = modele->moyenneModuleOptEleve(getId->value(),ponderationMoyenneModuleOpt);

    if(moyenneModuleOpt == -1){

        msg->setIcon(QMessageBox::Warning);
        msg->setText("Impossible de calculer la moyenne de l'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() +" pour l'instant");
        msg->show();
        return;
    }

    int moyenneFinalSpecialite = moyenneSpecialite/ponderationMoyenneSpecialite;
    int moyenneFinalTotal = (moyenneSpecialite+moyenneModuleOpt)/(ponderationMoyenneSpecialite+ponderationMoyenneSpecialite);
    int annee = QDate::currentDate().year() - getPromotion->value() + 3;

    if ((moyenneFinalSpecialite < 10)||(moyenneFinalTotal < 10)){

        if (annee == 1){

            msg->setIcon(QMessageBox::Warning);
            msg->setText("L'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() +" n'obtient pas son diplome avec une moyenne de " + QString::number(moyenneFinalSpecialite) + " dans sa specialite et de " + QString::number(moyenneFinalTotal) + " avec les modules optionnels");
            msg->show();
            boutonNonAdmission->setVisible(true);
            return;
        }

        msg->setIcon(QMessageBox::Warning);
        msg->setText("L'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() +" n'est pas admissible en " + QString::number(annee) + " annee avec une moyenne de " + QString::number(moyenneFinalSpecialite) + " dans sa specialite et de " + QString::number(moyenneFinalTotal) + " avec les modules optionnels");
        msg->show();
        boutonNonAdmission->setVisible(true);
        return;
    }

    if (annee == 3){

        msg->setIcon(QMessageBox::Information);
        msg->setText("L'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() +" obtient son diplome avec une moyenne de " + QString::number(moyenneFinalSpecialite) + " dans sa specialite et de " + QString::number(moyenneFinalTotal) + " avec les modules optionnels");
        msg->show();
        return;
    }

    msg->setIcon(QMessageBox::Information);
    msg->setText("L'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() +" est admissible en " + QString::number(annee) + " annee avec une moyenne de " + QString::number(moyenneFinalSpecialite) + " dans sa specialite et de " + QString::number(moyenneFinalTotal) + " avec les modules optionnels");
    msg->show();
    return;
}

void WidgetAdmissionAnneeSup::nonAdmission(){

    int annee = QDate::currentDate().year() - getPromotion->value() + 3;

    if (annee == 1){

        msg->setIcon(QMessageBox::Information);
        msg->setText("L'eleve ne redoubler car il est en 1er annee");
        msg->show();
        return;
    }

    if (modele->nonAdmissionEleve(getId->value(),getPromotion->value()+1)){

        msg->setIcon(QMessageBox::Information);
        msg->setText("L'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() +" a bien redoubler");
        msg->show();
        this->close();
        return;
    }

    msg->setIcon(QMessageBox::Critical);
    msg->setText("L'eleve " + getRecherchePrenom->currentText() + " " + getRechercheNom->text() +" n'a pas redoubler");
    msg->show();
    return;
}

