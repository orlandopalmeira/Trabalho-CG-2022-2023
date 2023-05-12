#include "light.hpp"

struct light{
    char type; // 'p': point, 'd': directional, 's': spotlight
    vector<float>* pos;
    vector<float>* dir;
    float cutoff;
};

Light newEmptyLight(){
    Light res = (Light)malloc(sizeof(struct light));
    if(res){
        res->type = 0;
        
        res->pos = new vector<float>();
        res->dir = new vector<float>();

        res->pos->push_back(0.0f);
        res->pos->push_back(0.0f);
        res->pos->push_back(0.0f);
        res->pos->push_back(1.0f); // é um ponto

        res->dir->push_back(0.0f);
        res->dir->push_back(0.0f);
        res->dir->push_back(0.0f);
        res->dir->push_back(0.0f);// é um vector

        res->cutoff = 0.0f;
    }
    return res;
}

Light newLight(char type, float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float cutoff) {
    Light res = newEmptyLight();
    if(res){
        res->type = type;
        setLightPos(res, posX, posY, posZ);
        setLightDir(res, dirX, dirY, dirZ);
        res->cutoff = cutoff;
    }
    return res;
}

Light newLight2(char type, float* pos,  float* dir, float cutoff) {
    Light res = newEmptyLight();
    if(res){
        res->type = type;
        setLightPosArr(res, pos);
        setLightDirArr(res, dir);
        res->cutoff = cutoff;
    }
    return res;
}

void setLightType(Light l, char type){
    l->type = type;
}

void setLightPos(Light l, float x, float y, float z){
    float *posArr = l->pos->data();
    posArr[0] = x;
    posArr[1] = y;
    posArr[2] = z;
}

void setLightPosArr(Light l, float* pos){
    setLightPos(l,pos[0],pos[1],pos[2]);
}

void setLightDir(Light l, float x, float y, float z){
    float *dirArr = l->dir->data();
    dirArr[0] = x;
    dirArr[1] = y;
    dirArr[2] = z;
}

void setLightDirArr(Light l, float* dir){
    setLightDir(l,dir[0],dir[1],dir[2]);
}

void setLightCutoff(Light l, float cutoff){
    l->cutoff = cutoff;
}

char getLightType(Light l){
    return l->type;
}

vector<float> getLightPos(Light l){
    vector<float> pos;
    for(int i = 0; i < 4; i++){
        pos.push_back(l->pos->at(i));
    }
    return pos;
}

vector<float> getLightDir(Light l){
    vector<float> dir;
    for(int i = 0; i < 4; i++){
        dir.push_back(l->dir->at(i));
    }
    return dir;
}

float getLightCutoff(Light l){
    return l->cutoff;
}