#include "Contraintes.h"

Contraintes::Contraintes(string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    string nom_fichier2 = nom_fichier + ".txt";

    FILE* fichier = NULL;
    fichier = fopen(nom_fichier2.c_str(), "r");

    int * valeurTache;

    if(fichier)
    {
        fscanf(fichier, "%d", &nbTaches);
        valeurTache = new int [nbTaches + 2];
        int tmp;
        valeurTache[0] = 0;
        valeurTache[nbTaches + 1] = 0;
        for (int i = 1; i < nbTaches + 1; i++)
        {
            fscanf(fichier, "%d %d", &tmp, &valeurTache[i]);
        }

        matriceAdajcenceTmp = new int * [nbTaches + 2];
        for (int i = 0; i < nbTaches + 2; i++)
        {
            matriceAdajcenceTmp[i] = new int[nbTaches + 2];
        }

        matriceValeurTmp = new int * [nbTaches + 2];
        for (int i = 0; i < nbTaches + 2; i++)
        {
            matriceValeurTmp[i] = new int[nbTaches + 2];
        }

        for (int i = 0; i < nbTaches + 2; i++)
        {
            for (int j = 0; j < nbTaches + 2; j++)
            {
                matriceAdajcenceTmp[i][j] = 0;
                matriceValeurTmp[i][j] = 0;
            }
        }

        int sommetSource;
        int sommetCible;

        for(int i = 0; i < nbTaches; i++)
        {
            fscanf(fichier, "%d", &sommetCible);
            int continuer = 1;
            while(continuer == 1)
            {
                fscanf(fichier, "%d", &sommetSource);
                if(sommetSource != 0)
                {
                    matriceAdajcenceTmp[sommetSource][sommetCible] = 1;
                    matriceValeurTmp[sommetSource][sommetCible] = valeurTache[sommetSource];
                }
                else
                {
                    continuer = 0;
                }
            }
        }

    }
    fclose(fichier);

    for(int i = 0; i < nbTaches + 2; i++)
    {
        int entree = 1;
        int sortie = 1;
        for(int j = 0; j < nbTaches + 2; j++)
        {
            if(i != 0 && i != nbTaches + 1)
            {
                if(matriceAdajcenceTmp[j][i] == 1)
                {
                    entree = 0;
                }
            }

            if(j != nbTaches + 1)
            {
                if(matriceAdajcenceTmp[i][j] == 1)
                {
                    sortie = 0;
                }
            }
        }

        if(entree == 1 && i != 0 && i != nbTaches + 1)
        {
            matriceAdajcenceTmp[0][i] = 1;
        }

        if(sortie == 1 && i != 0 && i != nbTaches + 1)
        {
            matriceAdajcenceTmp[i][nbTaches + 1] = 1;
            matriceValeurTmp[i][nbTaches + 1] = valeurTache[i];
        }
    }

}

void Contraintes::matricesAdjacenceValeurTmp(string nom_fichier)
{
    string trace_nom_fichier = nom_fichier + "_trace.txt";
    ofstream trace(trace_nom_fichier.c_str(), ios::app);

    printf("\nMatrice Adjacence Contraintes:\n");
    trace << "\nMatrice Adjacence Contraintes:\n";
    for (int i = 0; i < nbTaches + 2; i++)
    {
        printf("\n");
        for (int j = 0; j < nbTaches + 2; j++)
        {
            printf("%d ", matriceAdajcenceTmp[i][j]);
            trace << matriceAdajcenceTmp[i][j] + " ";
        }
    }

    printf("\n\nMatrice Valeur Contraintes :\n");
    trace << "\n\nMatrice Valeur Contraintes :\n";

    for (int i = 0; i < nbTaches + 2; i++)
    {
        printf("\n");
        for (int j = 0; j < nbTaches + 2; j++)
        {
            printf("%d ", matriceValeurTmp[i][j]);
            trace << matriceValeurTmp[i][j] + " ";
        }
    }
}
