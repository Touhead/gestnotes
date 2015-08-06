#ifndef PERSONNE_H
#define PERSONNE_H

#include <QDebug>
#include <QDockWidget>
#include <bdd.h>
#include <QActionGroup>
#include <QScrollArea>
#include <QBoxLayout>
#include <QToolBox>
#include <QToolBar>

class Personne
{
public:
    Personne(const int& identifiant);
    virtual void hello() = 0;
    virtual const int& getId();

    virtual bool createDockDonnee(QDockWidget*, QActionGroup*, Bdd*) const = 0;
    virtual bool createDockOutil(QDockWidget*, QActionGroup*, Bdd*) const = 0;
    virtual QAbstractTableModel* getModele(QAction*) const = 0;
    virtual QWidget* getFenetre(QAction*) const = 0;
    virtual void mettreAJour(Bdd*) = 0;

private:

    int id;
};

Personne* nouvellePersonne(const int& identifiant, Bdd* bdd);

#endif // PERSONNE_H
