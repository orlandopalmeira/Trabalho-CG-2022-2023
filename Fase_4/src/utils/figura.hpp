#ifndef FIGURA
#define FIGURA
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ponto.hpp"
#include "list.hpp"
#include "matrix.hpp"

using namespace std;

typedef struct figura* Figura;

Figura newEmptyFigura();

Figura newFigura(vector<Ponto>);

void addPonto(Figura, Ponto);

void addPontoArr(Figura, float*);

void addPNT(Figura f, Ponto, Ponto, Ponto textCoord = NULL);

void addSpherePoint(Figura f, Ponto, Ponto textCoord = NULL);

void addPNTArr(Figura f, float*, float*, float*);

void addPontos(Figura, Figura);

void setDiffuse(Figura f, float r = 200.0f, float g = 200.0f, float b = 200.0f);

vector<float> getDiffuse(Figura f);

void setAmbient(Figura f, float r = 50.0f, float g = 50.0f, float b = 50.0f);

vector<float> getAmbient(Figura f);

void setSpecular(Figura f, float r = 0.0f, float g = 0.0f, float b = 0.0f);

vector<float> getSpecular(Figura f);

void setEmissive(Figura f, float r = 0.0f, float g = 0.0f, float b = 0.0f);

vector<float> getEmissive(Figura f);

void setShininess(Figura f, float shininess = 0.0f);

float getShininess(Figura);

void setTextureFile(Figura f, const char* textFile);

const char* getTextureFile(Figura f);

void figuraToFile(Figura, const char*);

Figura fileToFigura(const char*);

vector<float> figuraToVector(Figura);

vector<float> figuraToNormals(Figura);

vector<float> figuraToTextCoords(Figura);

int size(Figura f);

void deleteFigura(void*);

void deleteFigura2(void*);

#endif // FIGURA