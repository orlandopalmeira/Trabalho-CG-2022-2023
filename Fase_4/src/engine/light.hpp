#ifndef LIGHT
#define LIGHT
#include <vector>
#include <stdlib.h>

using namespace std;

typedef struct light *Light;

Light newEmptyLight();

Light newLight(char, float, float, float, float, float, float, float);

Light newLight2(char, float*, float*, float);

void setLightType(Light, char);

void setLightPos(Light, float, float, float);

void setLightPosArr(Light, float*);

void setLightDir(Light, float, float, float);

void setLightDirArr(Light, float*);

void setLightCutoff(Light, float);

char getLightType(Light);

vector<float> getLightPos(Light);

vector<float> getLightDir(Light);

float getLightCutoff(Light);

#endif // LIGHT