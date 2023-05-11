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

Ponto newPontoSph(float a, float b, float radius){
    float x = radius * cos(b) * sin(a);
    float y = radius * sin(b);
    float z = radius * cos(b) * cos(a);
    
    return newPonto(x, y, z);
}

// Recebe um array com três elementos.
Ponto newPontoArr(float* p){
    return newPonto(p[0], p[1], p[2]);
}

Ponto newPonto2f(float x, float y){
    return newPonto(x, y, 0);
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

float distanceToOrigin(Ponto p){
    float dx = getX(p);
    float dy = getY(p);
    float dz = getZ(p);
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

float distance(Ponto p1, Ponto p2){
    float dx = getX(p2) - getX(p1);
    float dy = getY(p2) - getY(p1);
    float dz = getZ(p2) - getZ(p1);
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

Ponto normalizePonto(Ponto p){
    Ponto novo = dupPonto(p);
    float x = getX(novo), y = getY(novo), z = getZ(novo);
    float l = sqrt(x*x + y*y + z*z);
    novo->x /= l;
    novo->y /= l;
    novo->z /= l;
    return novo;
}

Ponto dupPonto(Ponto ponto){
    return newPonto(ponto->x, ponto->y, ponto->z);
}

void deletePonto(Ponto p){
    free(p);
}