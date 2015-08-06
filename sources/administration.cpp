#include "administration.h"

Administration::Administration(const int& id, Bdd* bdd) : Personne(id)
{
    groupe = new QStringList;
    (*groupe) << "utilisateurs" << "administration" << "professeurs" << "eleves";

    modeleGroupe = bdd->getModeleGroupe(groupe);

    formation = new QStringList;
    (*formation) << "specialites" << "modules";

    modeleFormation = bdd->getModeleFormation(formation);
}

bool Administration::createDockDonnee(QDockWidget* dock, QActionGroup* actions, Bdd* bdd) const{

    qDebug() << "Entrer createDock";

    QScrollArea* scrollAreaDonnee = new QScrollArea;
        QBoxLayout* layoutDonnee = new QBoxLayout(QBoxLayout::TopToBottom);
            QToolBox* toolBoxDonnee = new QToolBox;
                QAction* action;

                QToolBar* toolBarGroupe = new QToolBar;
                toolBarGroupe->setOrientation(Qt::Vertical);
                toolBarGroupe->setObjectName("groupe");

                action = new QAction("Utilisateurs",toolBarGroupe);
                action->setObjectName("utilisateurs");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

                action = new QAction("Administration",toolBarGroupe);
                action->setObjectName("administration");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

                action = new QAction("Professeurs",toolBarGroupe);
                action->setObjectName("professeurs");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

                action = new QAction("Eleves",toolBarGroupe);
                action->setObjectName("eleves");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

            toolBoxDonnee->addItem(toolBarGroupe,"Groupe");

                QToolBar* toolBarAutre = new QToolBar;
                toolBarAutre->setOrientation(Qt::Vertical);
                toolBarAutre->setObjectName("formation");

                action = new QAction("Modules",toolBarAutre);
                action->setObjectName("modules");
                actions->addAction(action);
                toolBarAutre->addAction(action);

                action = new QAction("Specialités",toolBarAutre);
                action->setObjectName("specialites");
                actions->addAction(action);
                toolBarAutre->addAction(action);

            toolBoxDonnee->addItem(toolBarAutre,"Formation");

            layoutDonnee->addWidget(toolBoxDonnee);
        scrollAreaDonnee->setLayout(layoutDonnee);
    dock->setWidget(scrollAreaDonnee);

    qDebug() << "Sortie createDock";
    return true;
}

bool Administration::createDockOutil(QDockWidget* dock, QActionGroup* actions, Bdd* bdd) const{

    qDebug() << "Entrer createDock";

    QScrollArea* scrollAreaDonnee = new QScrollArea;
        QBoxLayout* layoutDonnee = new QBoxLayout(QBoxLayout::TopToBottom);
            QToolBox* toolBoxDonnee = new QToolBox;
                QAction* action;

                QToolBar* toolBarGroupe = new QToolBar;
                toolBarGroupe->setOrientation(Qt::Vertical);
                toolBarGroupe->setObjectName("edition");

                action = new QAction("Ajouter utilisateur",toolBarGroupe);
                action->setObjectName("ajouterUtilisateurs");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

                action = new QAction("Modifier utilisateur",toolBarGroupe);
                action->setObjectName("modifierUtilisateurs");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

                action = new QAction("Supprimer utilisateur",toolBarGroupe);
                action->setObjectName("supprimerUtilisateurs");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

                action = new QAction("Modifier professeur responsable",toolBarGroupe);
                action->setObjectName("modifierProfesseurResp");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

                action = new QAction("Modifier professeur tuteur",toolBarGroupe);
                action->setObjectName("modifierProfesseurTuteur");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

                action = new QAction("Admission en année supérieure",toolBarGroupe);
                action->setObjectName("admissionAnneeSup");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

                /*action = new QAction("Ajouter module",toolBarGroupe);
                action->setObjectName("ajouterModule");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

                action = new QAction("Ajouter specialite",toolBarGroupe);
                action->setObjectName("ajouterSpecialite");
                actions->addAction(action);
                toolBarGroupe->addAction(action);*/

            toolBoxDonnee->addItem(toolBarGroupe,"Edition");

            layoutDonnee->addWidget(toolBoxDonnee);
        scrollAreaDonnee->setLayout(layoutDonnee);
    dock->setWidget(scrollAreaDonnee);

    qDebug() << "Sortie createDock";
    return true;
}

QAbstractTableModel* Administration::getModele(QAction* action) const{

    if (action->parent()->objectName() == "groupe"){

        return modeleGroupe->value(action->objectName());
    }

    if (action->parent()->objectName() == "formation"){

        return modeleFormation->value(action->objectName());
    }

    return 0;
}

QWidget* Administration::getFenetre(QAction* action) const{

    if (action->parent()->objectName() == "edition"){

        if (action->objectName() == "utilisateurs")
            //return new WidgetAjouterUtilisateur;
            return 0;
    }

    return 0;
}

void Administration::mettreAJour(Bdd* bdd){

    delete modeleGroupe;
    delete modeleFormation;

    modeleGroupe = bdd->getModeleGroupe(groupe);
    modeleFormation = bdd->getModeleFormation(formation);
}
