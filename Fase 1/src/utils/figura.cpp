#include "figura.hpp"

using namespace std;

struct figura{
    vector<Ponto> pontos;
};

Figura newEmptyFigura(){
    Figura r = (Figura)malloc(sizeof(struct figura));
    if(r != NULL){
        r->pontos = vector<Ponto>();
    }
    return r;
}

Figura newFigura(vector<Ponto> pontos){
    Figura r = newEmptyFigura();
    if(r != NULL){
        for(unsigned long i = 0; i < pontos.size(); i++){
            addPonto(r, pontos.at(i));
        }
    }
    return r;
}

void addPonto(Figura f, Ponto p){
    if(f){
        f->pontos.push_back(p);
    }
}

void figuraToFile(Figura f, const char* path){
    if(f){
        FILE* file = fopen(path, "w");
        fprintf(file, "%lu\n", f->pontos.size());
        for(unsigned long i = 0; i < f->pontos.size(); i++){
            Ponto p = f->pontos.at(i);
            fprintf(file, "%f,%f,%f\n", getX(p), getY(p), getZ(p));
        }
        fclose(file);
    }
}

Figura fileToFigura(const char* path){
    Figura f = newEmptyFigura();
    FILE* file = fopen(path, "r");
    if(f && file){
        char buffer[1024];
        fgets(buffer, 1023, file);
        int vertices = atoi(buffer);
        float x, y, z;
        for(int i = 0; i < vertices; i++){
            fgets(buffer, 1023, file);
            sscanf(buffer, "%f,%f,%f", &x, &y, &z);
            addPonto(f, newPonto(x, y, z));
        }
        fclose(file);
    }
    return f;
}

vector<Ponto> getPontos(Figura f){
    if(f){
        return f->pontos;
    }
    return {};
}

void deleteFigura(Figura f){
    if(f){
        while(f->pontos.size() > 0){
            Ponto p = f->pontos.front();
            deletePonto(p);
            f->pontos.erase(f->pontos.begin());
        }
        f->pontos.clear();
        free(f);
    }
}
