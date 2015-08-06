#include "widgetajouterutilisateur.h"

WidgetAjouterUtilisateur::WidgetAjouterUtilisateur(Modele* m, QWidget*  parent) :
    modele(m), QWidget(parent)
{
    layoutPrincipal = new QGridLayout;

        typeUtilisateur = new QLabel("Type d'utilisateur*");
        getTypeUtilisateur = new QComboBox;

        getTypeUtilisateur->addItem("Administrateur");
        getTypeUtilisateur->addItem("Professeur");
        getTypeUtilisateur->addItem("Eleve");

        groupBoxUtilisateur = new QGroupBox;
            layoutUtilisateur = new QGridLayout;
                id = new QLabel("ID*");
                getId = new QSpinBox;
                getId->setMinimum(20000000);
                getId->setMaximum(29999999);
                nom = new QLabel("Nom*");
                getNom = new QLineEdit;
                prenom = new QLabel("Prenom*");
                getPrenom = new QLineEdit;
                dateNaissance = new QLabel("Date de naissance*");
                getDateNaissance = new QDateEdit;
                adresse = new QLabel("Adresse*");
                getAdresse = new QLineEdit;
                telephone = new QLabel("Telephone*");
                getTelephone = new QLineEdit;
			layoutUtilisateur->addWidget(id,0,0);
			layoutUtilisateur->addWidget(getId,0,1);
			layoutUtilisateur->addWidget(nom,1,0);
			layoutUtilisateur->addWidget(getNom,1,1);
			layoutUtilisateur->addWidget(prenom,2,0);
			layoutUtilisateur->addWidget(getPrenom,2,1);
			layoutUtilisateur->addWidget(dateNaissance,3,0);
			layoutUtilisateur->addWidget(getDateNaissance,3,1);
			layoutUtilisateur->addWidget(adresse,4,0);
			layoutUtilisateur->addWidget(getAdresse,4,1);
            layoutUtilisateur->addWidget(telephone,5,0);
            layoutUtilisateur->addWidget(getTelephone,5,1);
        groupBoxUtilisateur->setLayout(layoutUtilisateur);

    groupBoxEleve = new QGroupBox;
    layoutEleve = new QGridLayout;

        promotion = new QLabel("Promotion*");
        getPromotion = new QSpinBox;
        getPromotion->setMinimum(QDate::currentDate().year());
        getPromotion->setMaximum(QDate::currentDate().year()+2);

        listSpecialite = modele->getSpecialite();
        specialite = new QLabel("Specialite*");
        getSpecialite = new QComboBox;
        getSpecialite->setModel(new QStringListModel(*listSpecialite));
        moduleOpt = new QLabel("Modules optionnels*");

        groupBoxModuleOpt1 = new QGroupBox("1er annee");
            layoutModuleOpt1 = new QVBoxLayout;
            listModuleOpt1 = modele->getModuleOpt(getSpecialite->currentText(),1);
                getModuleOpt1_1 = new QComboBox;
                getModuleOpt1_1->setModel(new QStringListModel(*listModuleOpt1));
                getModuleOpt1_2 = new QComboBox;
                getModuleOpt1_2->setModel(new QStringListModel(*listModuleOpt1));
                getModuleOpt1_3 = new QComboBox;
                getModuleOpt1_3->setModel(new QStringListModel(*listModuleOpt1));
            layoutModuleOpt1->addWidget(getModuleOpt1_1);
            layoutModuleOpt1->addWidget(getModuleOpt1_2);
            layoutModuleOpt1->addWidget(getModuleOpt1_3);
        groupBoxModuleOpt1->setLayout(layoutModuleOpt1);

        groupBoxModuleOpt2 = new QGroupBox("2eme annee");
            layoutModuleOpt2 = new QVBoxLayout;
            listModuleOpt2 = modele->getModuleOpt(getSpecialite->currentText(),2);
                getModuleOpt2_1 = new QComboBox;
                getModuleOpt2_1->setModel(new QStringListModel(*listModuleOpt2));
                getModuleOpt2_2 = new QComboBox;
                getModuleOpt2_2->setModel(new QStringListModel(*listModuleOpt2));
                getModuleOpt2_3 = new QComboBox;
                getModuleOpt2_3->setModel(new QStringListModel(*listModuleOpt2));
            layoutModuleOpt2->addWidget(getModuleOpt2_1);
            layoutModuleOpt2->addWidget(getModuleOpt2_2);
            layoutModuleOpt2->addWidget(getModuleOpt2_3);
        groupBoxModuleOpt2->setLayout(layoutModuleOpt2);

        groupBoxModuleOpt3 = new QGroupBox("3eme annnee");
            layoutModuleOpt3 = new QVBoxLayout;
            listModuleOpt3 = modele->getModuleOpt(getSpecialite->currentText(),3);
                getModuleOpt3_1 = new QComboBox;
                getModuleOpt3_1->setModel(new QStringListModel(*listModuleOpt3));
                getModuleOpt3_2 = new QComboBox;
                getModuleOpt3_2->setModel(new QStringListModel(*listModuleOpt3));
                getModuleOpt3_3 = new QComboBox;
                getModuleOpt3_3->setModel(new QStringListModel(*listModuleOpt3));
            layoutModuleOpt3->addWidget(getModuleOpt3_1);
            layoutModuleOpt3->addWidget(getModuleOpt3_2);
            layoutModuleOpt3->addWidget(getModuleOpt3_3);
        groupBoxModuleOpt3->setLayout(layoutModuleOpt3);

    layoutEleve->addWidget(promotion,0,0);
    layoutEleve->addWidget(getPromotion,0,1);
    layoutEleve->addWidget(specialite,1,0);
    layoutEleve->addWidget(getSpecialite,1,1);
    layoutEleve->addWidget(moduleOpt,2,0,3,1);
    layoutEleve->addWidget(groupBoxModuleOpt1,2,1);
    layoutEleve->addWidget(groupBoxModuleOpt2,3,1);
    layoutEleve->addWidget(groupBoxModuleOpt3,4,1);

    groupBoxEleve->setLayout(layoutEleve);

    boutonAjouter = new QPushButton("Ajouter");

    groupBoxEleve->setVisible(false);

    layoutPrincipal->addWidget(typeUtilisateur,0,0);
    layoutPrincipal->addWidget(getTypeUtilisateur,0,1);
    layoutPrincipal->addWidget(groupBoxUtilisateur,1,0,1,2);
    layoutPrincipal->addWidget(groupBoxEleve,2,0,1,2);
    layoutPrincipal->addWidget(boutonAjouter,3,0,1,2);

    this->setLayout(layoutPrincipal);

    connect(getTypeUtilisateur,SIGNAL(activated(QString)),this,SLOT(setGroupBoxTypeUtilisateur(QString)));
    connect(getSpecialite,SIGNAL(currentTextChanged(QString)),this,SLOT(setGroupBoxModuleOpt(QString)));
    connect(boutonAjouter,SIGNAL(clicked()),this,SLOT(insertUtilisateur()));

    msg = new QMessageBox(this);
}

void WidgetAjouterUtilisateur::setGroupBoxTypeUtilisateur(QString type){

    if (type == "Administration") {

        groupBoxEleve->setVisible(false);
        return;
    }

    if (type == "Professeur"){

        groupBoxEleve->setVisible(false);
        return;
    }

    if (type == "Eleve") {

        groupBoxEleve->setVisible(true);
        return;
    }

    return;
}

void WidgetAjouterUtilisateur::setGroupBoxModuleOpt(QString specialite){

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

void WidgetAjouterUtilisateur::insertUtilisateur(){

    if (getId->text().isEmpty()){
        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'administrateur " + getPrenom->text() + " " + getNom->text() + " n'a pas été ajouté");
        msg->show();
        return;
    }
    if (getNom->text().isEmpty()){
        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'administrateur " + getPrenom->text() + " " + getNom->text() + " n'a pas été ajouté");
        msg->show();
        return;
    }
    if (getPrenom->text().isEmpty()){
        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'administrateur " + getPrenom->text() + " " + getNom->text() + " n'a pas été ajouté");
        msg->show();
        return;
    }
    if (!getDateNaissance->date().isValid()){
        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'administrateur " + getPrenom->text() + " " + getNom->text() + " n'a pas été ajouté");
        msg->show();
        return;
    }
    if (getAdresse->text().isEmpty()){
        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'administrateur " + getPrenom->text() + " " + getNom->text() + " n'a pas été ajouté");
        msg->show();
        return;
    }
    if (getTelephone->text().size() != 10){
        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'administrateur " + getPrenom->text() + " " + getNom->text() + " n'a pas été ajouté");
        msg->show();
        return;
    }

    if (getTypeUtilisateur->currentText() == "Administrateur"){
        if (modele->insertAdministration(getId->value(),getNom->text(),getPrenom->text(),getDateNaissance->date(),getAdresse->text(),getTelephone->text())){

            msg->setIcon(QMessageBox::Information);
            msg->setText("L'administrateur " + getPrenom->text() + " " + getNom->text() + " a bien été ajouté");
            msg->show();
            this->close();
            return;
        }

        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'administrateur " + getPrenom->text() + " " + getNom->text() + " n'a pas été ajouté");
        msg->show();
        return;
    }

    if (getTypeUtilisateur->currentText() == "Professeur"){
        if (modele->insertProfesseur(getId->value(),getNom->text(),getPrenom->text(),getDateNaissance->date(),getAdresse->text(),getTelephone->text())){

            msg->setIcon(QMessageBox::Information);
            msg->setText("Le professeur " + getPrenom->text() + " " + getNom->text() + " a bien été ajouté");
            msg->show();
            this->close();
            return;
        }

        msg->setIcon(QMessageBox::Critical);
        msg->setText("Le professeur " + getPrenom->text() + " " + getNom->text() + " n'a pas été ajouté");
        msg->show();
        return;
    }

    if (getTypeUtilisateur->currentText() == "Eleve"){

        if      ((getModuleOpt1_1->currentText() == getModuleOpt1_2->currentText())
            ||  (getModuleOpt1_1->currentText() == getModuleOpt1_3->currentText())
            ||  (getModuleOpt1_2->currentText() == getModuleOpt1_3->currentText())
            ||  (getModuleOpt2_1->currentText() == getModuleOpt2_3->currentText())
            ||  (getModuleOpt2_1->currentText() == getModuleOpt2_3->currentText())
            ||  (getModuleOpt2_2->currentText() == getModuleOpt2_3->currentText())
            ||  (getModuleOpt3_1->currentText() == getModuleOpt3_3->currentText())
            ||  (getModuleOpt3_1->currentText() == getModuleOpt3_2->currentText())
            ||  (getModuleOpt3_2->currentText() == getModuleOpt3_3->currentText())){

            msg->setIcon(QMessageBox::Critical);
            msg->setText("L'eleve " + getPrenom->text() + " " + getNom->text() + " n'a pas été modifié");
            msg->show();
            return;
        }

        if (modele->insertEleve(getId->value(),getNom->text(),getPrenom->text(),getDateNaissance->date(),getAdresse->text(),getTelephone->text(),getPromotion->value(),getSpecialite->currentText(),getModuleOpt1_1->currentText(),getModuleOpt1_2->currentText(),getModuleOpt1_3->currentText(),getModuleOpt2_1->currentText(),getModuleOpt2_2->currentText(),getModuleOpt2_3->currentText(),getModuleOpt3_1->currentText(),getModuleOpt3_2->currentText(),getModuleOpt3_3->currentText())){

            msg->setIcon(QMessageBox::Information);
            msg->setText("L'eleve " + getPrenom->text() + " " + getNom->text() + " a bien été ajouté");
            msg->show();
            this->close();
            return;
        }

        msg->setIcon(QMessageBox::Critical);
        msg->setText("L'eleve " + getPrenom->text() + " " + getNom->text() + " n'a pas été ajouté");
        msg->show();
        return;
    }

    return;
}
