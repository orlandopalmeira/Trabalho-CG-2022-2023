#include "ponto.hpp"

struct ponto{
    float x, y, z;
};

Ponto newEmptyPonto(){
    return newPonto(0.0f, 0.0f, 0.0f);
}

Ponto newPonto(float x, float y, float z){
    Ponto r = (Ponto)malloc(sizeof(struct ponto));
    if(r != NULL){
        r->x = x; r->y = y; r->z = z;
    }
    return r;
}

float getX(Ponto p){
    if(p){
        return p->x;
    }
    return 0.0f;
}

float getY(Ponto p){
    if(p){
        return p->y;
    }
    return 0.0f;
}

float getZ(Ponto p){
    if(p){
        return p->z;
    }
    return 0.0f;
}

void deletePonto(Ponto p){
    free(p);
}