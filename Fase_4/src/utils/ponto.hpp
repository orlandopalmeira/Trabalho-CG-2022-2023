#ifndef PONTO
#define PONTO
#include <stdlib.h>
#include <math.h>

typedef struct ponto* Ponto;

Ponto newEmptyPonto();

Ponto newPonto(float x, float y, float z);

Ponto newPontoSph(float a, float b, float radius);

Ponto newPonto2f(float x, float y);

Ponto newPontoArr(float* p);

Ponto newPonto2fArr(float* p);

Ponto newPonto2fSph(float* center, float a, float raio);

float getX(Ponto p);

float getY(Ponto p);

float getZ(Ponto p);

float distanceToOrigin(Ponto p);

float distance(Ponto p1, Ponto p2);

Ponto normalizePonto(Ponto p);

/**
 * Calcula o vetor a partir formado por dois pontos.
 * @param a Ponto A
 * @param b Ponto B
 * @param res Vector resultante da diferença entre B-A, ou seja vetor parte de A para B.
 */
void vetorFrom2Pontos(Ponto a, Ponto b, float *res);

Ponto dupPonto(Ponto);

void deletePonto(Ponto p);

#endif // PONTO