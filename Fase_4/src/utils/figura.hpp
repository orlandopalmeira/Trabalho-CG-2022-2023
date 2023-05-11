#ifndef FIGURA
#define FIGURA
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "ponto.hpp"
#include "list.hpp"

using namespace std;

typedef struct figura* Figura;

Figura newEmptyFigura();

Figura newFigura(vector<Ponto>);

void addPonto(Figura, Ponto);

void addPontoArr(Figura, float*);

void addPontoNormalTextCoord(Figura f, Ponto, Ponto, Ponto);

void addPontoNormalTextCoordArr(Figura f, float*, float*, float*);

void addPontos(Figura, Figura);

void figuraToFile(Figura, const char*);

Figura fileToFigura(const char*);

vector<float> figuraToVector(Figura);

int size(Figura f);

void deleteFigura(void*);

void deleteFigura2(void*);

#endif // FIGURA