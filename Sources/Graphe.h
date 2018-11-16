#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

class Graphe
{
private:
    int nbSommets;
    int nbArcs;
    int **matriceAdjacence;
    int **matriceValeurArc;
    int *rangs;
    static int cpt;
    static int cpt2;
    int entree;
    int sortie;
    int * matriceDegresAuPlusTot;
    int * matriceDegresAuPlusTard;
    int * matriceDegresAuPlusTardPourcentage;
    int * dureeParSommet;
    static int compteurTableauDureeChemin;
    int datePlusTotFinProjet;
    int * marge;
    int * sommetsCircuit;

public:
    Graphe(string fichier);
    Graphe(int ** adjacence, int ** arc, int tache);
    ~Graphe() {}

    int getNbSommets()
    {
        return nbSommets;
    }

    void setEntree(int entree)
    {
        this->entree = entree;
    }

    void setSortie(int sortie)
    {
        this->sortie = sortie;
    }

    int **getMatriceAdjacence()
    {
        return matriceAdjacence;
    }
    void matricesAdjacenceValeur(string nom_fichier);
    int detectionCircuit(string nom_fichier);
    void calculRang(string nom_fichier);
    int pointEntree();
    int pointSortie();
    void exploreGraphe(int position, int depth, int n, int target, int * path, int * taboo, int verifDegree, string nom_fichier);
    static void compteur();
    int sommetsAccessiblesEntree(string nom_fichier);
    int sommetsAccessiblesSorties(string nom_fichier);
    int valeursArcs();
    int valeurIdentiqueArcs();
    void dateSommetAuPlusTot(string nom_fichier);
    void dateSommetAuPlusTard(int pourcentage,string nom_fichier);
    void calculMarge(string nom_fichier);
    int erreurContrainte(string nom_fichier);

};

#endif




