#include "figura.hpp"

using namespace std;

struct figura{
    //vector<Ponto> pontos;
    List pontos; // lista de pontos
};

Figura newEmptyFigura(){
    Figura r = (Figura)malloc(sizeof(struct figura));
    if(r != NULL){
        //r->pontos = vector<Ponto>();
        r->pontos = newEmptyList();
    }
    return r;
}

Figura newFigura(List pontos){
    Figura r = newEmptyFigura();
    if(r != NULL){
        //for(unsigned long i = 0; i < pontos.size(); i++){
        //    addPonto(r, pontos.at(i));
        //}
        for(unsigned long i = 0; i < getListLength(pontos); i++){
            addPonto(r, (Ponto)getListElemAt(pontos,i));
        }
    }
    return r;
}

void addPonto(Figura f, Ponto p){
    if(f){
        //f->pontos.push_back(p);
        addValueList(f->pontos, p);
    }
}

// TODO FUNCAO DO PEDRO QUE N SABE BEM O QUE FEZ, VERIFICAR SE ESTÁ BEM.
void addPontos(Figura f, Figura toAdd){
    if(f){
        //vector<Ponto> pontos = toAdd->pontos;
        //for (Ponto p: pontos){
        //    f->pontos.push_back(p);
        //}
        List pontos = toAdd->pontos;
        for(unsigned long i = 0; i < getListLength(pontos); i++){
            addValueList(f->pontos,getListElemAt(pontos,i));
        }
    }
}

void figuraToFile(Figura f, const char* path){
    if(!f){
        printf("A figura está vazia na chamada a FiguraToFile.\n");
        return;
    }
    FILE* file = fopen(path, "w");
    if (!file){
        printf("Ocorreu um erro na abertura do ficheiro '%s'\n", path);
        return;
    }
    //fprintf(file, "%lu\n", f->pontos.size());
    //for(unsigned long i = 0; i < f->pontos.size(); i++){
    //    Ponto p = f->pontos.at(i);
    //    fprintf(file, "%f,%f,%f\n", getX(p), getY(p), getZ(p));
    //}
    fprintf(file,"%lu\n",getListLength(f->pontos));
    for(unsigned long i = 0; i < getListLength(f->pontos); i++){
        Ponto p = (Ponto)getListElemAt(f->pontos, i);
        fprintf(file, "%f,%f,%f\n", getX(p), getY(p), getZ(p));
    }
    fclose(file);
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

List getPontos(Figura f){
    if(f){
        return f->pontos;
    }
    return NULL;
}

void deleteFigura(Figura f){
    if(f){
        //for(Ponto p: f->pontos){
        //    deletePonto(p);
        //}
        //f->pontos.resize(0);
        //f->pontos.shrink_to_fit();
        for(unsigned long i = 0; i < getListLength(f->pontos); i++){
            deletePonto((Ponto)getListElemAt(f->pontos,i));
        }
        deleteList(f->pontos);
        free(f);
    }
}

void deleteFigura2(Figura f){
    if(f){
        //f->pontos.resize(0);
        //f->pontos.shrink_to_fit();
        deleteList(f->pontos);
        free(f);
    }
}
