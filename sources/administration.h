#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

#include <personne.h>

class Administration : public Personne
{
public:
    Administration(const int&, Bdd*);
    virtual void hello() {qDebug() << "Administration";};

    virtual bool createDockDonnee(QDockWidget*, QActionGroup*, Bdd*) const;
    virtual bool createDockOutil(QDockWidget*, QActionGroup*, Bdd*) const;
    virtual QAbstractTableModel* getModele(QAction*) const;
    virtual QWidget* getFenetre(QAction*) const;
    virtual void mettreAJour(Bdd*);

private:

    QStringList* groupe;
    QHash<QString,QAbstractTableModel*>* modeleGroupe;

    QStringList* formation;
    QHash<QString,QAbstractTableModel*>* modeleFormation;
};

#endif // ADMINISTRATION_H
