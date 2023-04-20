#include <stdlib.h>
#include <math.h>

//* Calcula a multiplicação entre duas matrizes. 
void multiplyMatrices(int, int, const float*, int, int, const float*, float*, int*, int*);

//* Constrói a matriz de rotação para os eixos X,Y e Z fornecidos
void buildRotMatrix(const float *x, const float *y, const float *z, float *m);

//* Producto cruzado (cross product) de dois vectores
void cross(const float *a, const float *b, float *res);

//* Normaliza um vector para que este tenha norma (comprimento) igual a 1.
void normalize(float *a);

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);