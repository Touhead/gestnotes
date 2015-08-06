#include "widgetchoisirmoduleeleve.h"

WidgetChoisirModuleEleve::WidgetChoisirModuleEleve(Modele* m, QWidget *parent) :
    modele(m), QWidget(parent)
{
    layoutPrincipal = new QGridLayout;

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

    boutonModifier = new QPushButton("Modifier");

    layoutPrincipal->addWidget(groupBoxUtilisateur,1,0);
    layoutPrincipal->addWidget(groupBoxEleve,2,0);
    layoutPrincipal->addWidget(boutonModifier,3,0);

    this->setLayout(layoutPrincipal);

    listModuleOpt1 = 0;
    listModuleOpt2 = 0;
    listModuleOpt3 = 0;

    setEleve();
    connect(boutonModifier,SIGNAL(clicked()),this,SLOT(updateEleve()));

    msg = new QMessageBox(this);
}

void WidgetChoisirModuleEleve::setGroupBoxModuleOpt(const QString& specialite){

    if (listModuleOpt1 != 0)
        delete listModuleOpt1;

    listModuleOpt1 = modele->getModuleOpt(specialite,1);
    delete getModuleOpt1_1->model();
    getModuleOpt1_1->setModel(new QStringListModel(*listModuleOpt1));
    delete getModuleOpt1_2->model();
    getModuleOpt1_2->setModel(new QStringListModel(*listModuleOpt1));
    delete getModuleOpt1_3->model();
    getModuleOpt1_3->setModel(new QStringListModel(*listModuleOpt1));

    if (listModuleOpt2 != 0)
        delete listModuleOpt2;

    listModuleOpt2 = modele->getModuleOpt(specialite,2);
    delete getModuleOpt2_1->model();
    getModuleOpt2_1->setModel(new QStringListModel(*listModuleOpt2));
    delete getModuleOpt2_2->model();
    getModuleOpt2_2->setModel(new QStringListModel(*listModuleOpt2));
    delete getModuleOpt2_3->model();
    getModuleOpt2_3->setModel(new QStringListModel(*listModuleOpt2));

    if (listModuleOpt3 != 0)
        delete listModuleOpt3;

    listModuleOpt3 = modele->getModuleOpt(specialite,3);
    delete getModuleOpt3_1->model();
    getModuleOpt3_1->setModel(new QStringListModel(*listModuleOpt3));
    delete getModuleOpt3_2->model();
    getModuleOpt3_2->setModel(new QStringListModel(*listModuleOpt3));
    delete getModuleOpt3_3->model();
    getModuleOpt3_3->setModel(new QStringListModel(*listModuleOpt3));
}

bool WidgetChoisirModuleEleve::setEleve(){

    QString nom;
    QString prenom;
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

    if (!modele->getEleve(modele->getId(),nom,prenom,tempDateNaissanse,tempAdresse,tempTelephone,tempPromotion,tempSpecialite,tempModuleOpt1_1,tempModuleOpt1_2,tempModuleOpt1_3,tempModuleOpt2_1,tempModuleOpt2_2,tempModuleOpt2_3,tempModuleOpt3_1,tempModuleOpt3_2,tempModuleOpt3_3,tempNomProfesseurTuteur,tempPrenomProfesseurTuteur))
        return false;

    getNom->setText(nom);
    getPrenom->setText(prenom);
    getId->setValue(modele->getId());
    getDateNaissance->setDate(tempDateNaissanse);
    getAdresse->setText(tempAdresse);
    getTelephone->setText(tempTelephone);
    getPromotion->setValue(tempPromotion);
    getSpecialite->addItem(tempSpecialite);

    setGroupBoxModuleOpt(getSpecialite->currentText());

    getNomProfesseurTuteur->setText(tempNomProfesseurTuteur);
    getPrenomProfesseurTuteur->setText(tempPrenomProfesseurTuteur);

    groupBoxUtilisateur->setVisible(true);
    groupBoxEleve->setVisible(true);
    boutonModifier->setVisible(true);
    return true;
}

void WidgetChoisirModuleEleve::updateEleve(){

    if      ((getModuleOpt1_1->currentText() == getModuleOpt1_2->currentText())
        ||  (getModuleOpt1_1->currentText() == getModuleOpt1_3->currentText())
        ||  (getModuleOpt1_2->currentText() == getModuleOpt1_3->currentText())){

        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'eleve " + getPrenom->text() + " " + getNom->text() + " n'a pas été modifié");
        msg->show();
        return;
    }

    if (modele->updateEleve(getId->value(),getNom->text(),getPrenom->text(),getDateNaissance->date(),getAdresse->text(),getTelephone->text(),getPromotion->value(),getSpecialite->currentText(),getModuleOpt1_1->currentText(),getModuleOpt1_2->currentText(),getModuleOpt1_3->currentText(),getModuleOpt2_1->currentText(),getModuleOpt2_2->currentText(),getModuleOpt2_3->currentText(),getModuleOpt3_1->currentText(),getModuleOpt3_2->currentText(),getModuleOpt3_3->currentText())){

        msg->setIcon(QMessageBox::Information);
        msg->setText("L'eleve " + getPrenom->text() + " " + getNom->text() + " a bien été modifié");
        msg->show();
        return;
    }

    msg->setIcon(QMessageBox::Critical);
    msg->setText("L'eleve " + getPrenom->text() + " " + getNom->text() + " n'a pas été modifié");
    msg->show();
    return;
}
