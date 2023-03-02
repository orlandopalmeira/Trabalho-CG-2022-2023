#ifndef PONTO
#define PONTO
#include <stdlib.h>
#include <math.h>

typedef struct ponto* Ponto;

Ponto newEmptyPonto();

Ponto newPonto(float x, float y, float z);

float getX(Ponto p);

float getY(Ponto p);

float getZ(Ponto p);

float distanceToOrigin(Ponto p);

float distance(Ponto p1, Ponto p2);

void deletePonto(Ponto p);

#endif // PONTO