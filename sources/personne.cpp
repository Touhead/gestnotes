#include "personne.h"
#include "eleve.h"
#include "professeur.h"
#include "administration.h"

Personne::Personne(const int& identifiant) : id(identifiant)
{
}

const int& Personne::getId(){

    return id;
}

Personne* nouvellePersonne(const int& identifiant, Bdd* bdd){

    if(bdd->isEleve(identifiant))
        return new Eleve(identifiant, bdd);

    if(bdd->isProfesseur(identifiant))
        return new Professeur(identifiant, bdd);

    if(bdd->isAdministration(identifiant))
        return new Administration(identifiant, bdd);

    return 0;
}
