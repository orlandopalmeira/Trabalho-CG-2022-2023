#ifndef FIGURA
#define FIGURA
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "ponto.hpp"

using namespace std;

typedef struct figura* Figura;

Figura newEmptyFigura();

Figura newFigura(std::vector<Ponto>);

void addPonto(Figura, Ponto);

void figuraToFile(Figura, const char*);

Figura fileToFigura(const char*);

void deleteFigura(Figura);

#endif // FIGURA