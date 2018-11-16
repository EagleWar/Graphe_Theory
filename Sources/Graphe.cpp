#include "Graphe.h"
#include <fstream>
#include <string>

int Graphe::cpt = 0;
int Graphe::cpt2 = 0;
int Graphe::compteurTableauDureeChemin = 0;

Graphe::Graphe(string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    string nom_fichier2 = nom_fichier + ".txt";

    FILE* fichier = NULL;
    fichier = fopen(nom_fichier2.c_str(), "r");

    if(fichier)
    {
        fscanf(fichier, "%d", &nbSommets);
        fscanf(fichier, "%d", &nbArcs);

        matriceAdjacence = new int * [nbSommets];
        for (int i = 0; i < nbSommets; i++)
        {
            matriceAdjacence[i] = new int[nbSommets];
        }

        matriceValeurArc = new int * [nbSommets];
        for (int i = 0; i < nbSommets; i++)
        {
            matriceValeurArc[i] = new int[nbSommets];
        }

        for (int i = 0; i < nbSommets; i++)
        {
            for (int j = 0; j < nbSommets; j++)
            {
                matriceAdjacence[i][j] = 0;
                matriceValeurArc[i][j] = 0;
            }
        }


        int sommetSource;
        int sommetCible;
        int valeurArc;


        for(int i = 0; i < nbArcs; i++)
        {
            fscanf(fichier, "%d %d %d", &sommetSource, &sommetCible, &valeurArc);
            matriceAdjacence[sommetSource][sommetCible] = 1;
            matriceValeurArc[sommetSource][sommetCible] = valeurArc;
        }

    }
    fclose(fichier);

}

Graphe::Graphe(int ** adjacence, int ** arc, int tache)
{

    nbSommets = tache;

    matriceAdjacence = new int * [tache];
    for (int i = 0; i < nbSommets; i++)
    {
        matriceAdjacence[i] = new int[tache];
    }

    matriceValeurArc = new int * [tache];
    for (int i = 0; i < tache; i++)
    {
        matriceValeurArc[i] = new int[tache];
    }

    for(int i = 0; i < tache; i++)
    {
        for(int j = 0; j < tache; j++)
        {
            matriceAdjacence[i][j] = adjacence[i][j];
            matriceValeurArc[i][j] = arc[i][j];
        }
    }
}

void Graphe::matricesAdjacenceValeur(string nom_fichier)
{

    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    printf("\nMatrice Adjacence :\n");
    trace << "\nMatrice Adjacence :\n";

    for (int i = 0; i < nbSommets; i++)
    {
        printf("\n");
        trace << endl;
        for (int j = 0; j < nbSommets; j++)
        {
            printf("%d ", matriceAdjacence[i][j]);
            trace << matriceAdjacence[i][j] << " ";
        }
    }

    printf("\n\nMatrice Valeur :\n");
    trace << "\n\nMatrice Valeur :\n";
    for (int i = 0; i < nbSommets; i++)
    {
        printf("\n");
        trace << endl;
        for (int j = 0; j < nbSommets; j++)
        {
            printf("%d ", matriceValeurArc[i][j]);
            trace << matriceValeurArc[i][j] << " ";
        }
    }
}

int verificationSommetSuppr(int sommet, int *tab, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        if (sommet == tab[i])
        {
            return 1;
        }
    }
    return 0;
}

int verificationAbscenceCircuit(int *tab1, int * tab2, int taille)
{
    for(int i = 0; i < taille; i++)
    {
        if(tab1[i] != tab2[i])
        {
            return 0;
        }
    }
    return 1;
}

int Graphe::detectionCircuit(string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    printf("\n\nDetection Circuit :\n");
    trace << "\n\nDetection Circuit :\n";

    int *sommets = new int[nbSommets];
    for(int i = 0; i < nbSommets; i++)
    {
        sommets[i] = i;
    }

    int * sommetsSuppr = new int[nbSommets];
    for(int i = 0; i < nbSommets; i++)
    {
        sommetsSuppr[i] = -1;
    }
    int possibleSuppression = 1;

    int continuer = nbSommets;

    while(continuer > 0)
    {
        for(int i = 0; i < nbSommets; i++)
        {
            if(!verificationSommetSuppr(i, sommetsSuppr, nbSommets))
            {
                possibleSuppression = 1;

                for(int j = 0; j < nbSommets; j++)
                {
                    if(!verificationSommetSuppr(j, sommetsSuppr,nbSommets))
                    {
                        if(matriceAdjacence[j][i] == 1)
                        {
                            possibleSuppression = 0;
                        }
                    }
                }

                if(possibleSuppression == 1)
                {
                    sommetsSuppr[i] = i;
                    printf("\nSommet %d supprime !", sommetsSuppr[i]);
                    trace << "\nSommet " << sommetsSuppr[i] << " !";
                }
            }
        }

        if(verificationAbscenceCircuit(sommets, sommetsSuppr, nbSommets))
        {
            return 0;
        }

        continuer --;
    }

    sommetsCircuit = new int[nbSommets];

    for(int i = 0; i < nbSommets; i++)
    {
        if(sommetsSuppr[i] == -1)
        {
            sommetsCircuit[i] = i;
        }
        else
            sommetsCircuit[i] = -1;
    }


    /*for(int i = 0; i < nbSommets; i++)
    {
       printf("\n%d", sommetsCircuit[i]);
    }*/

    return 1;
}

int Graphe::erreurContrainte(string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    for(int i = 0; i < nbSommets; i++)
    {
        for(int j = 0; j < nbSommets; j++)
        {
            if(matriceAdjacence[j][i] == 1 && sommetsCircuit[i] == i && sommetsCircuit[j] == j)
            {
                printf("\n%d a besoin de %d !", i, j);
                trace << i << "\n a besoin de " << j << " !";
            }
        }
    }

    int sommetContrainteSuppr1;
    int sommetContrainteSuppr2;
    printf("\n\nContraintes a enlever ?\n\nSommet i : ");
    trace << "\n\nContraintes a enlever ?\n\nSommet i : ";
    cin >> sommetContrainteSuppr1;
    printf("\nSommet j : ");
    trace << "\nSommet j : ";
    cin >> sommetContrainteSuppr2;

    if(sommetsCircuit[sommetContrainteSuppr1] == sommetContrainteSuppr1 && sommetsCircuit[sommetContrainteSuppr2] == sommetContrainteSuppr2)
    {
        matriceAdjacence[sommetContrainteSuppr2][sommetContrainteSuppr1] = 0;
        matriceValeurArc[sommetContrainteSuppr2][sommetContrainteSuppr1] = 0;

        if(this->detectionCircuit(nom_fichier) == 1)
        {
            this->erreurContrainte(nom_fichier);
        }
        else
            return 1;
    }

    else
    {
        printf("\n\nLa contrainte selectionnee ne pose pas de probleme !\n\n");
        trace << "\n\nLa contrainte selectionnee ne pose pas de probleme !\n\n";
        this->erreurContrainte(nom_fichier);
    }

    return 0;
}

void Graphe::calculRang(string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    printf("\nCalcul de Rang :\n");
    trace << "\nCalcul de Rang :\n";

    int *sommets = new int[nbSommets];
    for(int i = 0; i < nbSommets; i++)
    {
        sommets[i] = i;
    }

    int * sommetsSuppr = new int[nbSommets];
    for(int i = 0; i < nbSommets; i++)
    {
        sommetsSuppr[i] = -1;
    }

    int possibleSuppression = 1;
    int rang = 0;

    rangs = new int [nbSommets];
    for(int i = 0; i < nbSommets; i++)
    {
        rangs[i] = -1;
    }

    int *sommetsSupprTmp = new int[nbSommets];
    for(int i = 0; i < nbSommets; i++)
    {
        sommetsSupprTmp[i] = -1;
    }

    int rangPositif = 0;

    while(!rangPositif)
    {
        rangPositif = 1;
        for(int i = 0; i < nbSommets; i++)
        {
            if(!verificationSommetSuppr(i, sommetsSuppr, nbSommets))
            {
                possibleSuppression = 1;

                for(int j = 0; j < nbSommets; j++)
                {
                    if(!verificationSommetSuppr(j, sommetsSuppr,nbSommets))
                    {
                        if(matriceAdjacence[j][i] == 1)
                        {
                            possibleSuppression = 0;
                        }
                    }
                }

                if(possibleSuppression == 1)
                {
                    sommetsSupprTmp[i] = i;
                    rangs[i] = rang;
                }
            }
        }

        for(int i = 0; i < nbSommets; i++)
        {
            if(sommetsSupprTmp[i] > 0 || sommetsSupprTmp[i] == 0)
            {
                sommetsSuppr[i] = i;
            }
        }

        for(int i = 0; i < nbSommets; i++)
        {
            if(rangs[i] < 0)
            {
                rangPositif = 0;
            }
        }

        printf("\nIteration %d", rang+1);
        trace << "\nIteration " + rang+1;
        for (int i = 0; i < nbSommets; i++)
        {
            printf("\nSommet %d : Rang %d", i, rangs[i]);
            trace << "\nSommet " << i << " : Rang " << rangs[i];
        }

        printf("\n");
        trace << "\n";

        rang++;
    }
}

int Graphe::pointEntree()
{
    int nbEntree = 0;

    for(int i = 0; i < nbSommets; i++)
    {
        int tmp = 0;
        for(int j = 0; j < nbSommets; j++)
        {
            if(matriceAdjacence[j][i] == 1)
            {
                tmp = 1;
            }
        }

        if(tmp == 0)
        {
            nbEntree ++;
        }
    }

    if(nbEntree == 1)
    {
        return 1;
    }
    else
        return nbEntree;
}

int Graphe::pointSortie()
{
    int nbSortie = 0;

    for(int i = 0; i < nbSommets; i++)
    {
        int tmp = 0;
        for(int j = 0; j < nbSommets; j++)
        {
            if(matriceAdjacence[i][j] == 1)
            {
                tmp = 1;
            }
        }

        if(tmp == 0)
        {
            nbSortie ++;
        }
    }

    if(nbSortie == 1)
    {
        return 1;
    }
    else
        return nbSortie;
}


void Graphe::compteur()
{
    cpt++;
}

void Graphe::exploreGraphe(int position, int depth, int n, int target, int * path, int * taboo, int verifDegree, string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    path[depth]=position;

    if (position==target)
    {
        int temps = 0;
        for(int i=0; i<=depth; i++)
        {
            if(verifDegree == 0)
            {
                printf("%d ",path[i]);
                trace << path[i] + " ";
            }
            if(i != 0)
            {
                temps = temps + matriceValeurArc[path[i - 1]][path[i]];
            }
        }

        compteur();

        if(verifDegree == 0)
        {
            printf("Temps/cout : %d\n", temps);
            trace << "Temps/cout : " << temps << "\n";
        }

        if(verifDegree == 1)
        {
            dureeParSommet[compteurTableauDureeChemin] = temps;
            compteurTableauDureeChemin++;
        }
        return;
    }

    taboo[position]=1;

    for(int i=0; i<n; i++)
    {
        int tmp = 0;
        if (matriceAdjacence[position][i] == 0 || taboo[i] == 1)
            tmp = 1;
        if (tmp == 0)
            exploreGraphe(i,depth+1, n, target, path, taboo, verifDegree, nom_fichier);
    }

    taboo[position]=0;
}

int Graphe::sommetsAccessiblesEntree(string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    int * path = new int[nbSommets];
    int * taboo = new int[nbSommets];
    int cheminValide = 0;

    for(int i = 0; i < nbSommets; i++)
    {
        if(i != entree)
        {
            printf("\n\nChemin possible pour atteindre %d a partir de %d :\n", i, entree);
            trace << "\n\nChemin possible pour atteindre " << i << " a partir de " << entree << " :\n";
            exploreGraphe(entree,0,nbSommets,i,path,taboo,0,nom_fichier);

            if(cpt == 0)
            {
                printf("\nAucun chemin existant !");
                trace << "\nAucun chemin existant !";
            }

            if(cpt > 0)
            {
                cheminValide ++;
            }
            cpt = 0;
        }
    }

    if(cheminValide == nbSommets - 1)
    {
        return 1;
    }
    else
        return 0;

}

int Graphe::sommetsAccessiblesSorties(string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    int * path = new int[nbSommets];
    int * taboo = new int[nbSommets];
    int cheminValide = 0;

    for(int i = 0; i < nbSommets; i++)
    {
        if(i != sortie)
        {
            printf("\n\nChemin possible pour atteindre %d a partir de %d:\n",sortie, i);
            trace << "\n\nChemin possible pour atteindre " << sortie << " a partir de " << i << " :\n";
            exploreGraphe(i,0,nbSommets,sortie,path,taboo,0,nom_fichier);

            if(cpt == 0)
            {
                printf("\nAucun chemin existant !");
                trace << "\nAucun chemin existant !";
            }

            if(cpt > 0)
            {
                cheminValide ++;
            }
            cpt = 0;
        }

    }

    if(cheminValide == nbSommets - 1)
    {
        return 1;
    }
    else
        return 0;

}


int Graphe::valeursArcs()
{
    int arcNegatif = 0;

    for(int i = 0; i < nbSommets; i++)
    {
        for(int j = 0; j < nbSommets; j++)
        {
            if(matriceValeurArc[i][j] < 0)
            {
                return 0;
            }
        }
    }

    return 1;
}

int Graphe::valeurIdentiqueArcs()
{
    for(int i = 0; i < nbSommets; i++)
    {
        for(int j = 0; j < nbSommets; j++)
        {
            if(matriceAdjacence[i][j] == 1)
            {
                int tmp = matriceValeurArc[i][j];
                for(int x = 0; x < nbSommets; x++)
                {
                    if(matriceAdjacence[i][x] == 1 && matriceValeurArc[i][x] != tmp)
                    {
                        return 0;
                    }
                }
            }
        }

    }

    return 1;
}

int valeurMax(int * tab, int taille)
{
    int valeurMax = 0;
    for(int i = 0; i < taille; i++)
    {
        if(tab[i] >= valeurMax)
            valeurMax = tab[i];
    }

    return valeurMax;
}

void Graphe::dateSommetAuPlusTot(string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    matriceDegresAuPlusTot = new int [nbSommets];
    int * path = new int[nbSommets];
    int * taboo = new int[nbSommets];
    int cheminValide = 0;
    dureeParSommet = new int [100];
    int * tableauCompteur = new int [nbSommets];
    int compteurLocal = 0;

    for(int i = 0; i < nbSommets; i++)
    {
        if(i != entree)
        {
            exploreGraphe(entree,0,nbSommets,i,path,taboo,1,nom_fichier);
        }

        tableauCompteur[i] = cpt;
        compteurLocal = compteurLocal + cpt;
        cpt = 0;
    }

    printf("\n");
    trace << endl;

    /*for(int i = 0; i < nbSommets; i++) printf("%d ", tableauCompteur[i]);
    printf("\n");
    for(int x = 0; x < compteurLocal; x++) printf("%d ", dureeParSommet[x]);
    printf("\n");
    printf("\n");*/


    int variableTmp = 0;
    for(int i = 0; i < nbSommets; i++)
    {
        if(tableauCompteur[i] != 0)
        {
            int * tableauTmp = new int [tableauCompteur[i]];
            for(int j = 0; j < tableauCompteur[i]; j++)
            {
                tableauTmp[j] = dureeParSommet[variableTmp];
                variableTmp++;
            }

            /*for(int j = 0; j < tableauCompteur[i]; j++)
            {
                printf("%d ",tableauTmp[j]);
            }*/

            matriceDegresAuPlusTot[i] = valeurMax(tableauTmp, tableauCompteur[i]);
            delete []tableauTmp;

            //printf("\n");

        }
        else
            matriceDegresAuPlusTot[i] = 0;
    }

    printf("\nDates au plus tot :\n\n");
    trace << "\nDates au plus tot :\n\n";

    for(int i = 0; i< nbSommets; i++)
    {
        printf("Sommet %d : %d\n",i, matriceDegresAuPlusTot[i]);
        trace << "Sommet " << i << " : " << matriceDegresAuPlusTot[i] << "\n";
    }

    datePlusTotFinProjet = matriceDegresAuPlusTot[sortie];

    delete [] dureeParSommet;

    compteurTableauDureeChemin = 0;
}

void Graphe::dateSommetAuPlusTard(int pourcentage, string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    if(pourcentage == 100)
        matriceDegresAuPlusTard = new int [nbSommets];
    else
        matriceDegresAuPlusTardPourcentage = new int [nbSommets];
    int * path = new int[nbSommets];
    int * taboo = new int[nbSommets];
    int cheminValide = 0;
    dureeParSommet = new int [100];
    int * tableauCompteur = new int [nbSommets];
    int compteurLocal = 0;

    for(int i = 0; i < nbSommets; i++)
    {
        if(i != sortie)
        {
            exploreGraphe(i,0,nbSommets,sortie,path,taboo,1,nom_fichier);
        }

        tableauCompteur[i] = cpt;
        compteurLocal = compteurLocal + cpt;
        cpt = 0;
    }

    printf("\n");
    trace << endl;

    /*for(int i = 0; i < nbSommets; i++) printf("%d ", tableauCompteur[i]);
    printf("\n");
    for(int x = 0; x < compteurLocal; x++) printf("%d ", dureeParSommet[x]);
    printf("\n");
    printf("\n");*/


    int variableTmp = 0;
    for(int i = 0; i < nbSommets; i++)
    {
        if(tableauCompteur[i] != 0)
        {
            int * tableauTmp = new int [tableauCompteur[i]];
            for(int j = 0; j < tableauCompteur[i]; j++)
            {
                tableauTmp[j] = dureeParSommet[variableTmp];
                variableTmp++;
            }

            /*for(int j = 0; j < tableauCompteur[i]; j++)
            {
                printf("%d ",tableauTmp[j]);
            }*/

            matriceDegresAuPlusTard[i] = ((datePlusTotFinProjet*pourcentage)/100) - valeurMax(tableauTmp, tableauCompteur[i]);
            delete []tableauTmp;

            //printf("\n");

        }
        else
            matriceDegresAuPlusTard[i] = datePlusTotFinProjet;
    }

    for(int i = 0; i< nbSommets; i++)
    {
        printf("Sommet %d : %d\n",i, matriceDegresAuPlusTard[i]);
        trace << "Sommet " << i << " : " << matriceDegresAuPlusTard[i] << "\n";
    }

    delete [] dureeParSommet;

    compteurTableauDureeChemin = 0;
}

void Graphe::calculMarge(string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    marge = new int [nbSommets];

    for(int i = 0; i < nbSommets; i++)
    {
        marge[i] = matriceDegresAuPlusTard[i] - matriceDegresAuPlusTot[i];
    }

    printf("\nMarge totale :\n\n");
    trace << "\nMarge totale :\n\n";

    for(int i = 0; i< nbSommets; i++)
    {
        printf("Sommet %d : %d\n",i, marge[i]);
        trace << "Sommet " << i << " : " << marge[i] << "\n";
    }

}
















