#ifndef PONTO
#define PONTO
#include <stdlib.h>
#include <math.h>

typedef struct ponto* Ponto;

Ponto newEmptyPonto();

Ponto newPonto(float x, float y, float z);

Ponto newPontoSph(float a, float b, float radius);

Ponto newPontoArr(float* p);

Ponto newPonto2f(float x, float y);

float getX(Ponto p);

float getY(Ponto p);

float getZ(Ponto p);

float distanceToOrigin(Ponto p);

float distance(Ponto p1, Ponto p2);

Ponto normalizePonto(Ponto p);

Ponto coneNormal(float a, float h, float raio);

Ponto dupPonto(Ponto);

void deletePonto(Ponto p);

#endif // PONTO