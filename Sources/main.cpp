#include <iostream>
#include "Contraintes.h"
#include "Graphe.h"


using namespace std;

int main()
{
    int continuer = 1;
    while(continuer == 1)
    {
        int niveau;
        cout << "\n\nNiveau souhaite : ";
        cin >> niveau;

        switch (niveau)
        {
        case 1 :
        {

            string nom_fichier;
            cout << "Graphe souhaite : ";
            cin >> nom_fichier;
            nom_fichier = "Graphe" + nom_fichier;
            Graphe graphe(nom_fichier);
            graphe.matricesAdjacenceValeur(nom_fichier);

            string trace_nom_fichier = nom_fichier + "_trace.txt";
            ofstream trace(trace_nom_fichier.c_str(), ios::app);

            if(graphe.detectionCircuit(nom_fichier))
            {
                printf("\n\nLe graphe possede un circuit !\n");
                trace << "\n\nLe graphe possede un circuit !\n";
            }
            else
            {
                printf("\n\nLe graphe ne possede pas de circuit !\n");
                trace << "\n\nLe graphe ne possede pas de circuit !\n";
                graphe.calculRang(nom_fichier);
            }

            graphe.~Graphe();

            break;
        }

        case 2 :
        {

            string nom_fichier;
            cout << "Graphe souhaite : ";
            cin >> nom_fichier;
            nom_fichier = "Graphe" + nom_fichier;
            Graphe graphe(nom_fichier);
            graphe.matricesAdjacenceValeur(nom_fichier);

            string trace_nom_fichier = nom_fichier + "_trace.txt";
            ofstream trace(trace_nom_fichier.c_str(), ios::app);

            int resultEntree = graphe.pointEntree();
            int entree = -1;
            if(resultEntree == 1)
            {
                printf("\n\nLe graphe possede une entree : ");
                trace << "\n\nLe graphe possede une entree : ";
                int continuer = 1;

                while(continuer)
                {
                    for(int i = 0; i < graphe.getNbSommets(); i++)
                    {
                        int tmp = 0;
                        for(int j = 0; j < graphe.getNbSommets(); j++)
                        {
                            if(graphe.getMatriceAdjacence()[j][i] == 1)
                            {
                                tmp = 1;
                            }
                        }

                        if(tmp == 0)
                        {
                            entree = i;
                            continuer = 0;
                        }
                    }
                }

                printf("%d", entree);
                trace << entree;
                graphe.setEntree(entree);
            }
            else
            {
                if(resultEntree == 0)
                {
                    printf("\n\nLe graphe ne possede pas d'entree !");
                    trace << "\n\nLe graphe ne possede pas d'entree !";
                }
                else
                {
                    printf("\n\nLe graphe possede plusieurs entrees !");
                    trace << "\n\nLe graphe possede plusieurs entrees !";
                }


            }

            int resultSortie = graphe.pointSortie();
            int sortie = -1;
            if(resultSortie == 1)
            {
                printf("\n\nLe graphe possede une sortie : ");
                trace << "\n\nLe graphe possede une sortie : ";
                int continuer = 1;

                while(continuer)
                {
                    for(int i = 0; i < graphe.getNbSommets(); i++)
                    {
                        int tmp = 0;
                        for(int j = 0; j < graphe.getNbSommets(); j++)
                        {
                            if(graphe.getMatriceAdjacence()[i][j] == 1)
                            {
                                tmp = 1;
                            }
                        }

                        if(tmp == 0)
                        {
                            sortie = i;
                            continuer = 0;
                        }
                    }
                }

                printf("%d", sortie);
                trace << sortie;
                graphe.setSortie(sortie);
            }
            else
            {
                if(resultSortie == 0)
                {
                    printf("\n\nLe graphe ne possede pas de sortie !");
                    trace << "\n\nLe graphe ne possede pas de sortie !";
                }
                else
                {
                    printf("\n\nLe graphe possede plusieurs sorties !");
                    trace << "\n\nLe graphe possede plusieurs sorties !";
                }

            }

            int resultSommetsAccessiblesEntree = 0;
            if(resultEntree == 1)
            {
                resultSommetsAccessiblesEntree = graphe.sommetsAccessiblesEntree(nom_fichier);
                if(resultSommetsAccessiblesEntree == 1)
                {
                    printf("\n\nTous les sommets du graphe sont accessbiles depuis l'entree !\n");
                    trace << "\n\nTous les sommets du graphe sont accessbiles depuis l'entree !\n";
                }
                else
                {
                    printf("\n\nTous les sommets du graphe ne sont pas accessbiles depuis l'entree !\n");
                    trace << "\n\nTous les sommets du graphe ne sont pas accessbiles depuis l'entree !\n";
                }

            }

            int resultSommetsAccessiblesSortie = 0;
            if(resultSortie == 1)
            {
                resultSommetsAccessiblesSortie = graphe.sommetsAccessiblesSorties(nom_fichier);
                if(resultSommetsAccessiblesSortie == 1)
                {
                    printf("\n\nLa sortie est accessible depuis tous les sommets du graphes !\n");
                    trace << "\n\nLa sortie est accessible depuis tous les sommets du graphes !\n";
                }
                else
                {
                    printf("\n\nLa sortie n'est pas accessible depuis tous les sommets du graphes !\n");
                    trace << "\n\nLa sortie n'est pas accessible depuis tous les sommets du graphes !\n";
                }

            }

            int resultatValeursArcs = graphe.valeursArcs();

            if(resultatValeursArcs == 1)
            {
                printf("\n\nTous les arcs sont positifs ou nul !\n");
                trace << "\n\nTous les arcs sont positifs ou nul !\n";
            }
            else
            {
                printf("\n\nTous les arcs ne sont pas positifs ou nul !\n");
                trace << "\n\nTous les arcs ne sont pas positifs ou nul !\n";
            }


            int resultatValeurIdentiqueArcs = graphe.valeurIdentiqueArcs();

            if(resultatValeurIdentiqueArcs == 1)
            {
                printf("\n\nTous les arcs issues d'un sommet sont egaux !\n");
                trace << "\n\nTous les arcs issues d'un sommet sont egaux !\n";
            }
            else
            {
                printf("\n\nTous les arcs issues d'un sommet ne sont pas egaux !\n");
                trace << "\n\nTous les arcs issues d'un sommet ne sont pas egaux !\n";
            }


            int resultatCircuit = graphe.detectionCircuit(nom_fichier);
            if(resultatCircuit == 1)
            {
                printf("\n\nLe graphe possede un circuit !\n");
                trace << "\n\nLe graphe possede un circuit !\n";
            }
            else
            {
                printf("\n\nLe graphe ne possede pas de circuit !\n");
                trace << "\n\nLe graphe ne possede pas de circuit !\n";
                if(resultSortie == 1 && resultEntree == 1)
                    graphe.calculRang(nom_fichier);
            }

            if(resultEntree == 1 && resultSortie == 1 && resultSommetsAccessiblesEntree == 1 && resultSommetsAccessiblesSortie == 1
                    && resultatValeursArcs == 1 && resultatValeurIdentiqueArcs == 1 && resultatCircuit == 0)
            {
                printf("\n\nNous pouvons calculer les differents calendrier et marges!\n");
                trace << "\n\nNous pouvons calculer les differents calendrier et marges!\n";
                graphe.dateSommetAuPlusTot(nom_fichier);
                printf("\nDates au plus tard : \n\n");
                trace << "\nDates au plus tard : \n\n";
                graphe.dateSommetAuPlusTard(100,nom_fichier);
                graphe.calculMarge(nom_fichier);
                printf("\nDates au plus tard (110%): \n\n");
                trace << "\nDates au plus tard (110%): \n\n";
                graphe.dateSommetAuPlusTard(110, nom_fichier);
                graphe.calculMarge(nom_fichier);
            }
            else
            {
                printf("\n\nNous ne pouvons pas calculer les differents calendrier et marges!\n");
                trace << "\n\nNous ne pouvons pas calculer les differents calendrier et marges!\n";
            }


            graphe.~Graphe();

            break;
        }

        case 3 :
        {
            string nom_fichier = "";
            cout << "\n\nContrainte souhaite : ";
            cin >> nom_fichier;
            nom_fichier = "Contrainte" + nom_fichier;
            Contraintes contrainte(nom_fichier);

            string trace_nom_fichier = nom_fichier + "_trace.txt";
            ofstream trace(trace_nom_fichier.c_str(), ios::app);

            Graphe graphe2(contrainte.getMatriceAdjacenceTmp(), contrainte.getMatriceValeurTmp(), contrainte.getTache());

            printf("\n\n");
            trace << endl << endl;
            graphe2.matricesAdjacenceValeur(nom_fichier);

            int resultEntree = graphe2.pointEntree();
            int entree = -1;
            if(resultEntree == 1)
            {
                printf("\n\nLe graphe possede une entree : ");
                trace << "\n\nLe graphe possede une entree : ";
                int continuer = 1;

                while(continuer)
                {
                    for(int i = 0; i < graphe2.getNbSommets(); i++)
                    {
                        int tmp = 0;
                        for(int j = 0; j < graphe2.getNbSommets(); j++)
                        {
                            if(graphe2.getMatriceAdjacence()[j][i] == 1)
                            {
                                tmp = 1;
                            }
                        }

                        if(tmp == 0)
                        {
                            entree = i;
                            continuer = 0;
                        }
                    }
                }

                printf("%d", entree);
                trace << entree;
                graphe2.setEntree(entree);
            }
            else
            {
                if(resultEntree == 0)
                {
                    printf("\n\nLe graphe ne possede pas d'entree !");
                    trace << "\n\nLe graphe ne possede pas d'entree !";
                }
                else
                {
                    printf("\n\nLe graphe possede plusieurs entrees !");
                    trace << "\n\nLe graphe possede plusieurs entrees !";
                }

            }

            int resultSortie = graphe2.pointSortie();
            int sortie = -1;
            if(resultSortie == 1)
            {
                printf("\n\nLe graphe possede une sortie : ");
                trace << "\n\nLe graphe possede une sortie : ";
                int continuer = 1;

                while(continuer)
                {
                    for(int i = 0; i < graphe2.getNbSommets(); i++)
                    {
                        int tmp = 0;
                        for(int j = 0; j < graphe2.getNbSommets(); j++)
                        {
                            if(graphe2.getMatriceAdjacence()[i][j] == 1)
                            {
                                tmp = 1;
                            }
                        }

                        if(tmp == 0)
                        {
                            sortie = i;
                            continuer = 0;
                        }
                    }
                }

                printf("%d", sortie);
                trace << sortie;
                graphe2.setSortie(sortie);
            }
            else
            {
                if(resultSortie == 0)
                {
                    printf("\n\nLe graphe ne possede pas de sortie !");
                    trace << "\n\nLe graphe ne possede pas de sortie !";
                }
                else
                {
                    printf("\n\nLe graphe possede plusieurs sorties !");
                    trace << "\n\nLe graphe possede plusieurs sorties !";
                }

            }

            int resultSommetsAccessiblesEntree = 0;
            if(resultEntree == 1)
            {
                resultSommetsAccessiblesEntree = graphe2.sommetsAccessiblesEntree(nom_fichier);
                if(resultSommetsAccessiblesEntree == 1)
                {
                    printf("\n\nTous les sommets du graphe sont accessbiles depuis l'entree !\n");
                    trace << "\n\nTous les sommets du graphe sont accessbiles depuis l'entree !\n";
                }
                else
                {
                    printf("\n\nTous les sommets du graphe ne sont pas accessbiles depuis l'entree !\n");
                    trace << "\n\nTous les sommets du graphe ne sont pas accessbiles depuis l'entree !\n";
                }

            }

            int resultSommetsAccessiblesSortie = 0;
            if(resultSortie == 1)
            {
                resultSommetsAccessiblesSortie = graphe2.sommetsAccessiblesSorties(nom_fichier);
                if(resultSommetsAccessiblesSortie == 1)
                {
                    printf("\n\nLa sortie est accessible depuis tous les sommets du graphes !\n");
                    trace << "\n\nLa sortie est accessible depuis tous les sommets du graphes !\n";
                }
                else
                {
                    printf("\n\nLa sortie n'est pas accessible depuis tous les sommets du graphes !\n");
                    trace << "\n\nLa sortie n'est pas accessible depuis tous les sommets du graphes !\n";
                }

            }

            int resultatValeursArcs = graphe2.valeursArcs();

            if(resultatValeursArcs == 1)
            {
                printf("\n\nTous les arcs sont positifs ou nul !\n");
                trace << "\n\nTous les arcs sont positifs ou nul !\n";
            }
            else
            {
                printf("\n\nTous les arcs ne sont pas positifs ou nul !\n");
                trace << "\n\nTous les arcs ne sont pas positifs ou nul !\n";
            }

            int resultatValeurIdentiqueArcs = graphe2.valeurIdentiqueArcs();

            if(resultatValeurIdentiqueArcs == 1)
            {
                printf("\n\nTous les arcs issues d'un sommet sont egaux !\n");
                trace << "\n\nTous les arcs issues d'un sommet sont egaux !\n";
            }
            else
            {
                printf("\n\nTous les arcs issues d'un sommet ne sont pas egaux !\n");
                trace << "\n\nTous les arcs issues d'un sommet ne sont pas egaux !\n";
            }


            int resultatCircuit = graphe2.detectionCircuit(nom_fichier);
            if(resultatCircuit == 1)
            {
                printf("\n\nLe graphe possede un circuit !\n");
                trace << "\n\nLe graphe possede un circuit !\n";
            }
            else
            {
                printf("\n\nLe graphe ne possede pas de circuit !\n");
                trace << "\n\nLe graphe ne possede pas de circuit !\n";
                graphe2.calculRang(nom_fichier);
            }

            if(resultEntree == 1 && resultSortie == 1 && resultSommetsAccessiblesEntree == 1 && resultSommetsAccessiblesSortie == 1
                    && resultatValeursArcs == 1 && resultatValeurIdentiqueArcs == 1 && resultatCircuit == 0)
            {
                printf("\n\nNous pouvons calculer les differents calendrier et marges!\n");
                trace << "\n\nNous pouvons calculer les differents calendrier et marges!\n";
                graphe2.dateSommetAuPlusTot(nom_fichier);
                printf("\nDates au plus tard : \n\n");
                trace << "\nDates au plus tard : \n\n";
                graphe2.dateSommetAuPlusTard(100,nom_fichier);
                graphe2.calculMarge(nom_fichier);
                printf("\nDates au plus tard (110%): \n\n");
                trace << "\nDates au plus tard (110%): \n\n";
                graphe2.dateSommetAuPlusTard(110,nom_fichier);
                graphe2.calculMarge(nom_fichier);
            }
            else
            {
                printf("\n\nNous ne pouvons pas calculer les differents calendrier et marges!\n");
                trace << "\n\nNous ne pouvons pas calculer les differents calendrier et marges!\n";
            }


            graphe2.~Graphe();
            contrainte.~Contraintes();

            break;
        }

        case 4 :
        {
            string nom_fichier = "";
            cout << "\n\nContrainte souhaite : ";
            cin >> nom_fichier;
            nom_fichier = "Contrainte" + nom_fichier;
            Contraintes contrainte(nom_fichier);
            Graphe graphe3(contrainte.getMatriceAdjacenceTmp(), contrainte.getMatriceValeurTmp(), contrainte.getTache());

            string trace_nom_fichier = nom_fichier + "_trace.txt";
            ofstream trace(trace_nom_fichier.c_str(), ios::app);

            printf("\n\n");
            trace << endl << endl;

            int resultatCircuit = graphe3.detectionCircuit(nom_fichier);
            int resultatErreurContrainte;
            if(resultatCircuit == 1)
            {
                printf("\n\nLe graphe possede un circuit !\n");
                trace << "\n\nLe graphe possede un circuit !\n";
                printf("\nLes contraintes suivantes posent probleme :\n\n");
                trace << "\nLes contraintes suivantes posent probleme :\n\n";
                resultatErreurContrainte = graphe3.erreurContrainte(nom_fichier);

                if(resultatErreurContrainte == 1)
                {
                    printf("\n\nLe graphe ne possede pas de circuit !\n");
                    trace << "\n\nLe graphe ne possede pas de circuit !\n";
                }
            }
            else
            {
                printf("\n\nLe graphe ne possede pas de circuit !\n");
                trace << "\n\nLe graphe ne possede pas de circuit !\n";
            }

            int resultEntree = graphe3.pointEntree();
            int entree = -1;
            if(resultEntree == 1)
            {
                printf("\n\nLe graphe possede une entree : ");
                trace << "\n\nLe graphe possede une entree : ";
                int continuer = 1;

                while(continuer)
                {
                    for(int i = 0; i < graphe3.getNbSommets(); i++)
                    {
                        int tmp = 0;
                        for(int j = 0; j < graphe3.getNbSommets(); j++)
                        {
                            if(graphe3.getMatriceAdjacence()[j][i] == 1)
                            {
                                tmp = 1;
                            }
                        }

                        if(tmp == 0)
                        {
                            entree = i;
                            continuer = 0;
                        }
                    }
                }

                printf("%d", entree);
                trace << entree;
                graphe3.setEntree(entree);
            }
            else
            {
                if(resultEntree == 0)
                {
                    printf("\n\nLe graphe ne possede pas d'entree !");
                    trace << "\n\nLe graphe ne possede pas d'entree !";
                }

                else
                {
                    printf("\n\nLe graphe possede plusieurs entrees !");
                    trace << "\n\nLe graphe possede plusieurs entrees !";
                }

            }

            int resultSortie = graphe3.pointSortie();
            int sortie = -1;
            if(resultSortie == 1)
            {
                printf("\n\nLe graphe possede une sortie : ");
                trace << "\n\nLe graphe possede une sortie : ";
                int continuer = 1;

                while(continuer)
                {
                    for(int i = 0; i < graphe3.getNbSommets(); i++)
                    {
                        int tmp = 0;
                        for(int j = 0; j < graphe3.getNbSommets(); j++)
                        {
                            if(graphe3.getMatriceAdjacence()[i][j] == 1)
                            {
                                tmp = 1;
                            }
                        }

                        if(tmp == 0)
                        {
                            sortie = i;
                            continuer = 0;
                        }
                    }
                }

                printf("%d", sortie);
                trace << sortie;
                graphe3.setSortie(sortie);
            }
            else
            {
                if(resultSortie == 0)
                {
                    printf("\n\nLe graphe ne possede pas de sortie !");
                    trace << "\n\nLe graphe ne possede pas de sortie !";
                }
                else
                {
                    printf("\n\nLe graphe possede plusieurs sorties !");
                    trace << "\n\nLe graphe possede plusieurs sorties !";
                }

            }

            int resultSommetsAccessiblesEntree = 0;
            if(resultEntree == 1)
            {
                resultSommetsAccessiblesEntree = graphe3.sommetsAccessiblesEntree(nom_fichier);
                if(resultSommetsAccessiblesEntree == 1)
                {
                    printf("\n\nTous les sommets du graphe sont accessbiles depuis l'entree !\n");
                    trace << "\n\nTous les sommets du graphe sont accessbiles depuis l'entree !\n";
                }
                else
                {
                    printf("\n\nTous les sommets du graphe ne sont pas accessbiles depuis l'entree !\n");
                    trace << "\n\nTous les sommets du graphe ne sont pas accessbiles depuis l'entree !\n";
                }

            }

            int resultSommetsAccessiblesSortie = 0;
            if(resultSortie == 1)
            {
                resultSommetsAccessiblesSortie = graphe3.sommetsAccessiblesSorties(nom_fichier);
                if(resultSommetsAccessiblesSortie == 1)
                {
                    printf("\n\nLa sortie est accessible depuis tous les sommets du graphes !\n");
                    trace << "\n\nLa sortie est accessible depuis tous les sommets du graphes !\n";
                }
                else
                {
                    printf("\n\nLa sortie n'est pas accessible depuis tous les sommets du graphes !\n");
                    trace << "\n\nLa sortie n'est pas accessible depuis tous les sommets du graphes !\n";
                }

            }


            int resultatValeursArcs = graphe3.valeursArcs();

            if(resultatValeursArcs == 1)
            {
                printf("\n\nTous les arcs sont positifs ou nul !\n");
                trace << "\n\nTous les arcs sont positifs ou nul !\n";
            }
            else
            {
                printf("\n\nTous les arcs ne sont pas positifs ou nul !\n");
                trace << "\n\nTous les arcs ne sont pas positifs ou nul !\n";
            }

            int resultatValeurIdentiqueArcs = graphe3.valeurIdentiqueArcs();

            if(resultatValeurIdentiqueArcs == 1)
            {
                printf("\n\nTous les arcs issues d'un sommet sont egaux !\n");
                trace << "\n\nTous les arcs issues d'un sommet sont egaux !\n";
            }
            else
            {
                printf("\n\nTous les arcs issues d'un sommet ne sont pas egaux !\n");
                trace << "\n\nTous les arcs issues d'un sommet ne sont pas egaux !\n";
            }

            if(resultEntree == 1 && resultSortie == 1 && resultSommetsAccessiblesEntree == 1 && resultSommetsAccessiblesSortie == 1
                    && resultatValeursArcs == 1 && resultatValeurIdentiqueArcs == 1 && (resultatCircuit == 0 || resultatErreurContrainte == 1))
            {
                graphe3.matricesAdjacenceValeur(nom_fichier);
                graphe3.calculRang(nom_fichier);
                printf("\n\nNous pouvons calculer les differents calendrier et marges!\n");
                trace << "\n\nNous pouvons calculer les differents calendrier et marges!\n";
                graphe3.dateSommetAuPlusTot(nom_fichier);
                printf("\nDates au plus tard : \n\n");
                trace << "\nDates au plus tard : \n\n";
                graphe3.dateSommetAuPlusTard(100,nom_fichier);
                graphe3.calculMarge(nom_fichier);
                printf("\nDates au plus tard (110%): \n\n");
                trace << "\nDates au plus tard (110%): \n\n";
                graphe3.dateSommetAuPlusTard(110,nom_fichier);
                graphe3.calculMarge(nom_fichier);
            }
            else
            {
                printf("\n\nNous ne pouvons pas calculer les differents calendrier et marges!\n");
                trace << "\n\nNous ne pouvons pas calculer les differents calendrier et marges!\n";
            }

            graphe3.~Graphe();
            contrainte.~Contraintes();

            break;

        }

        };

        printf("\n\nSouhaitez-vous continuer? 0 ou 1 : ");
        cin >> continuer;
    }
}
