#include "professeur.h"

Professeur::Professeur(const int& id, Bdd* bdd) : Personne(id)
{
    module = bdd->getModuleProfesseur(id);
    modeleModule = bdd->getModeleModuleProfesseur(module);

    Tutorat = bdd->getTutorat(id);
    Matieres = bdd->getMatieres(id);
}

bool Professeur::createDockDonnee(QDockWidget* dock, QActionGroup* actions, Bdd* bdd) const{

        qDebug() << "Entrer createDock";

        QScrollArea* scrollAreaDonnee = new QScrollArea;
            QBoxLayout* layoutDonnee = new QBoxLayout(QBoxLayout::TopToBottom);
                QToolBox* toolBoxDonnee = new QToolBox;
                        QToolBar* toolBarModule;
                        QAction* action;
                        QLocale c;

                        for(int cpt = 0; cpt < module->size(); cpt++){

                            toolBarModule = new QToolBar;
                            toolBarModule->setOrientation(Qt::Vertical);
                            toolBarModule->setObjectName("modules" + c.toString(cpt+1));
                            for(QStringList::iterator i = module->value(cpt)->begin(); i != module->value(cpt)->end(); i++){

                                action = new QAction(*i,toolBarModule);
                                actions->addAction(action);
                                action->setObjectName(*i);
                                toolBarModule->addAction(action);
                            }
                            toolBoxDonnee->addItem(toolBarModule,"Module(s) A" + c.toString(cpt+1));
                        }

                       toolBarModule = new QToolBar;
                       toolBarModule->setOrientation(Qt::Vertical);
                       toolBarModule->setObjectName("AUTRE");

                       action = new QAction("Tutorat",toolBarModule);
                       actions->addAction(action);
                       action->setObjectName("Tutorat");
                       toolBarModule->addAction(action);

                       toolBoxDonnee->addItem(toolBarModule,"AUTRE");

                       toolBarModule = new QToolBar;
                       toolBarModule->setOrientation(Qt::Vertical);
                       toolBarModule->setObjectName("MATIERES");

                       action = new QAction("liste",toolBarModule);
                       actions->addAction(action);
                       action->setObjectName("Liste");
                       toolBarModule->addAction(action);

                       toolBoxDonnee->addItem(toolBarModule,"MATIERES");

            layoutDonnee->addWidget(toolBoxDonnee);
        scrollAreaDonnee->setLayout(layoutDonnee);
    dock->setWidget(scrollAreaDonnee);

    qDebug() << "Sortie createDock";
    return true;
}

bool Professeur::createDockOutil(QDockWidget* dock, QActionGroup* actions, Bdd* bdd) const{

    return false;
}

QAbstractTableModel* Professeur::getModele(QAction* action) const{

    QLocale c;

    for(int cpt = 0; cpt < module->size(); cpt++){

        if(action->parentWidget()->objectName() == "modules" + c.toString(cpt+1))
            return modeleModule->value(cpt)->value(action->objectName());
    }

    if(action->objectName() == "Tutorat")
        return Tutorat;

    if(action->objectName() == "Liste")
        return Matieres;

    return 0;
}

QWidget* Professeur::getFenetre(QAction* action) const{

    return 0;
}

void Professeur::mettreAJour(Bdd* bdd){

    delete module;
    delete modeleModule;
    delete Tutorat;
    delete Matieres;

    module = bdd->getModuleProfesseur(this->getId());
    modeleModule = bdd->getModeleModuleProfesseur(module);

    Tutorat = bdd->getTutorat(this->getId());
    Matieres = bdd->getMatieres(this->getId());
}
