#include "eleve.h"

Eleve::Eleve(const int& id, Bdd* bdd) : Personne(id)
{
    module = bdd->getModuleEleve(id);
    modeleModule = bdd->getModeleModuleEleve(id,module);
}

bool Eleve::createDockDonnee(QDockWidget* dock, QActionGroup* actions, Bdd* bdd) const{

    qDebug() << "Entrer createDock";
    QScrollArea* scrollAreaDonnee2 = new QScrollArea;
        QBoxLayout* layoutDonnee2 = new QBoxLayout(QBoxLayout::TopToBottom);
            QToolBox* toolBoxDonnee2 = new QToolBox;
                    QToolBar* toolBarModule2;
                    QAction* action2;
                    QLocale c2;

                    for(int cpt = 0; cpt < module->size(); cpt++){

                        toolBarModule2 = new QToolBar;
                        toolBarModule2->setOrientation(Qt::Vertical);
                        toolBarModule2->setObjectName("modules" + c2.toString(cpt+1));
                        for(QStringList::iterator i = module->value(cpt)->begin(); i != module->value(cpt)->end(); i++){

                            action2 = new QAction(*i,toolBarModule2);
                            actions->addAction(action2);
                            action2->setObjectName(*i);
                            toolBarModule2->addAction(action2);
                        }
                        toolBoxDonnee2->addItem(toolBarModule2,"Module(s) A" + c2.toString(cpt+1));
                    }

            layoutDonnee2->addWidget(toolBoxDonnee2);
        scrollAreaDonnee2->setLayout(layoutDonnee2);
    dock->setWidget(scrollAreaDonnee2);

    qDebug() << "Sortie createDock";
    return true;
}

bool Eleve::createDockOutil(QDockWidget* dock, QActionGroup* actions, Bdd* ) const{

    qDebug() << "Entrer createDock";

    QScrollArea* scrollAreaDonnee = new QScrollArea;
        QBoxLayout* layoutDonnee = new QBoxLayout(QBoxLayout::TopToBottom);
            QToolBox* toolBoxDonnee = new QToolBox;
                QAction* action;

                QToolBar* toolBarGroupe = new QToolBar;
                toolBarGroupe->setOrientation(Qt::Vertical);
                toolBarGroupe->setObjectName("edition");

                action = new QAction("Choisir modules optionnels",toolBarGroupe);
                action->setObjectName("choisirModuleOpt");
                actions->addAction(action);
                toolBarGroupe->addAction(action);

            toolBoxDonnee->addItem(toolBarGroupe,"Edition");

            layoutDonnee->addWidget(toolBoxDonnee);
        scrollAreaDonnee->setLayout(layoutDonnee);
    dock->setWidget(scrollAreaDonnee);

    qDebug() << "Sortie createDock";
    return true;
}

QAbstractTableModel* Eleve::getModele(QAction* action) const{

    QLocale c;

    for(int cpt = 0; cpt < module->size(); cpt++){

        if(action->parentWidget()->objectName() == "modules" + c.toString(cpt+1))
            return modeleModule->value(cpt)->value(action->objectName());
    }

    return 0;
}

QWidget* Eleve::getFenetre(QAction* action) const{

    return 0;
}

void Eleve::mettreAJour(Bdd* bdd){

    delete module;
    delete modeleModule;

    module = bdd->getModuleEleve(this->getId());
    modeleModule = bdd->getModeleModuleEleve(this->getId(),module);
}
