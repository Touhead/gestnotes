#ifndef PROFESSEUR_H
#define PROFESSEUR_H

#include <personne.h>

class Professeur : public Personne
{
public:
    Professeur(const int&, Bdd*);
    virtual void hello() {qDebug() << "Professeur";};

    virtual bool createDockDonnee(QDockWidget*, QActionGroup*, Bdd*) const;
    virtual bool createDockOutil(QDockWidget*, QActionGroup*, Bdd*) const;
    virtual QAbstractTableModel* getModele(QAction*) const;
    virtual QWidget* getFenetre(QAction*) const;
    virtual void mettreAJour(Bdd*);

private:
    QVector<QStringList*>* module;
    QVector<QHash<QString,QAbstractTableModel*>*>* modeleModule;
    QAbstractTableModel* Tutorat;
    QAbstractTableModel* Matieres;
};

#endif // PROFESSEUR_H
