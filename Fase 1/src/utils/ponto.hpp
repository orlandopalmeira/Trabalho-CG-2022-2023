#ifndef PONTO
#define PONTO
#include <stdlib.h>

typedef struct ponto* Ponto;

Ponto newEmptyPonto();

Ponto newPonto(float x, float y, float z);

float getX(Ponto p);

float getY(Ponto p);

float getZ(Ponto p);

void deletePonto(Ponto p);

#endif // PONTO