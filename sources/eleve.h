#ifndef ELEVE_H
#define ELEVE_H

#include <personne.h>

class Eleve : public Personne
{
public:
    Eleve(const int&, Bdd*);
    virtual void hello() {qDebug() << "Eleve";};

    virtual bool createDockDonnee(QDockWidget*, QActionGroup*, Bdd*) const;
    virtual bool createDockOutil(QDockWidget*, QActionGroup*, Bdd*) const;
    virtual QAbstractTableModel* getModele(QAction*) const;
    virtual QWidget* getFenetre(QAction*) const;
    virtual void mettreAJour(Bdd*);


private :
    QVector<QStringList*>* module;
    QVector<QHash<QString,QAbstractTableModel*>*>* modeleModule;
};

#endif // ELEVE_H
