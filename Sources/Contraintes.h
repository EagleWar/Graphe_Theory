#ifndef CONTRAINTES_H_INCLUDED
#define CONTRAINTES_H_INCLUDED
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

class Contraintes
{
public:
    Contraintes(string fichier);
    ~Contraintes()
    {

    }
    void matricesAdjacenceValeurTmp(string nom_fichier);
    int ** getMatriceAdjacenceTmp()
    {
        return matriceAdajcenceTmp;
    }

    int ** getMatriceValeurTmp()
    {
        return matriceValeurTmp;
    }

    int getTache()
    {
        return nbTaches + 2;
    }

private:
    int ** matriceAdajcenceTmp;
    int ** matriceValeurTmp;
    int nbTaches;
};

#endif // CONTRAINTES_H
