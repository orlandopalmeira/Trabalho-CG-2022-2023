#include "figura.hpp"

using namespace std;

struct figura{
    vector<Ponto>* pontos;
    vector<Ponto>* normais;
    vector<Ponto>* textCoords;
    char* textureFile;
    // Color
    vector<float>* diffuse;
    vector<float>* ambient;
    vector<float>* specular;
    vector<float>* emissive;
    float shininess;
};

Figura newEmptyFigura(){
    Figura r = (Figura)malloc(sizeof(struct figura));
    if(r != NULL){
        r->pontos     = new vector<Ponto>();
        r->normais    = new vector<Ponto>();
        r->textCoords = new vector<Ponto>();
        r->diffuse = new vector<float>();
        r->ambient = new vector<float>();
        r->specular = new vector<float>();
        r->emissive = new vector<float>();
        r->textureFile = NULL;
        // Colocação dos valores de cores padrão impostos pelo enunciado.
        r->diffuse->push_back(200.0f);r->diffuse->push_back(200.0f);r->diffuse->push_back(200.0f);r->diffuse->push_back(1.0f);
        r->ambient->push_back(50.0f);r->ambient->push_back(50.0f);r->ambient->push_back(50.0f);r->ambient->push_back(1.0f);
        r->specular->push_back(0.0f);r->specular->push_back(0.0f);r->specular->push_back(0.0f);r->specular->push_back(1.0f);
        r->emissive->push_back(0.0f);r->emissive->push_back(0.0f);r->emissive->push_back(0.0f);r->emissive->push_back(1.0f);
        r->shininess = 0.0f;
    }
    return r;
}

// Argumento recebe apenas o array de posiçoes
Figura newFigura(vector<Ponto> pontos){
    Figura r = newEmptyFigura();
    if(r != NULL){
        for(unsigned long i = 0; i < pontos.size(); i++){
            addPonto(r, pontos[i]);
        }
    }
    return r;
}

// Recebe uma struct Ponto para adicionar ao array das posições.
void addPonto(Figura f, Ponto p){
    if(f){
        f->pontos->push_back(p);
    }
}

// Recebe uma array de 3 valores que constituem o ponto a adicionar.
void addPontoArr(Figura f, float* p){
    addPonto(f,newPonto(p[0],p[1],p[2]));
}


// Recebe 3 Pontos para adicionar aos respetivos arrays de valores.
void addPNT(Figura f, Ponto ponto, Ponto normal, Ponto textCoord){
    addPonto(f,ponto);
    f->normais->push_back(normalizePonto(normal));
    if (textCoord) f->textCoords->push_back(textCoord);
    else{
        f->textCoords->push_back(newPonto2f(0,0));
    }
}

// Calcula automaticamente a normal do ponto, tendo em conta que é uma esfera.
void addSpherePoint(Figura f, Ponto ponto, Ponto textCoord){
    addPonto(f,ponto);

    // Cálculo da normal
    Ponto normal = normalizePonto(ponto);
    f->normais->push_back(normal);
    if (textCoord) f->textCoords->push_back(textCoord);
    else{
        f->textCoords->push_back(newPonto2f(0,0));
    }
}

// Recebe 3 pontos, no formato de array, para adicionar aos respetivos arrays de valores
void addPNTArr(Figura f, float *ponto = NULL, float* normal = NULL, float* textCoord = NULL){
    addPontoArr(f, ponto);
    normalize(normal);
    f->normais->push_back(newPonto(normal[0],normal[1],normal[2]));
    if(textCoord) f->textCoords->push_back(newPonto2f(textCoord[0],textCoord[1]));
    else{
        f->textCoords->push_back(newPonto2f(0, 0));
    }
}

void addPontos(Figura f, Figura toAdd){
    if(f){
        vector<Ponto>* pontos = toAdd->pontos;
        for(Ponto p: *pontos){
            addPonto(f,p);
        }
        vector<Ponto>* pontosNormal = toAdd->normais;
        for(Ponto p: *pontosNormal){
            f->normais->push_back(p);
        }
        vector<Ponto>* pontosTex = toAdd->textCoords;
        for(Ponto p: *pontosTex){
            f->textCoords->push_back(p);
        }
    }
}

void setDiffuse(Figura f, float r, float g, float b){
    float* aux = f->diffuse->data();
    aux[0] = r;
    aux[1] = g;
    aux[2] = b;
}

vector<float> getDiffuse(Figura f){
    vector<float> result;
    result.push_back(f->diffuse->at(0)/255.0f);
    result.push_back(f->diffuse->at(1)/255.0f);
    result.push_back(f->diffuse->at(2)/255.0f);
    result.push_back(f->diffuse->at(3)/255.0f);
    return result;
}

void setAmbient(Figura f, float r, float g, float b){
    float* aux = f->ambient->data();
    aux[0] = r;
    aux[1] = g;
    aux[2] = b;
}

vector<float> getAmbient(Figura f){
    vector<float> result;
    result.push_back(f->ambient->at(0)/255.0f);
    result.push_back(f->ambient->at(1)/255.0f);
    result.push_back(f->ambient->at(2)/255.0f);
    result.push_back(f->ambient->at(3)/255.0f);
    return result;
}

void setSpecular(Figura f, float r, float g, float b){
    float* aux = f->specular->data();
    aux[0] = r;
    aux[1] = g;
    aux[2] = b;
}

vector<float> getSpecular(Figura f){
    vector<float> result;
    result.push_back(f->specular->at(0)/255.0f);
    result.push_back(f->specular->at(1)/255.0f);
    result.push_back(f->specular->at(2)/255.0f);
    result.push_back(f->specular->at(3)/255.0f);
    return result;
}

void setEmissive(Figura f, float r, float g, float b){
    float* aux = f->emissive->data();
    aux[0] = r;
    aux[1] = g;
    aux[2] = b;
}

vector<float> getEmissive(Figura f){
    vector<float> result;
    result.push_back(f->emissive->at(0)/255.0f);
    result.push_back(f->emissive->at(1)/255.0f);
    result.push_back(f->emissive->at(2)/255.0f);
    result.push_back(f->emissive->at(3)/255.0f);
    return result;
}

void setShininess(Figura f, float shininess){
    f->shininess = shininess;
}

float getShininess(Figura f){
    return f->shininess;
}

void setTextureFile(Figura f, const char* textFile){
    f->textureFile = strdup(textFile);
}

const char* getTextureFile(Figura f){
    return f->textureFile;
}

float arred(float num){
    long double places = 4.0;
    long double pow10 = std::pow(10.0,places);
    return std::round(num * pow10) / pow10;
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
    vector<Ponto> pontos = *(f->pontos);
    vector<Ponto> normais = *(f->normais);
    vector<Ponto> textCoords = *(f->textCoords);
    size_t len = pontos.size();
    fprintf(file,"%lu\n",len);
    for(unsigned long i = 0; i < len; i++){
        Ponto p = pontos[i], normal = normais[i], textCoord = textCoords[i]; 
        fprintf(file, "%g,%g,%g ; %g,%g,%g ; %g,%g\n", arred(getX(p)), arred(getY(p)), arred(getZ(p)), arred(getX(normal)), arred(getY(normal)), arred(getZ(normal)), arred(getX(textCoord)), arred(getY(textCoord)));
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
        float xp, yp, zp, xn, yn, zn, xtc, ytc;
        for(int i = 0; i < vertices; i++){
            fgets(buffer, 1023, file);
            sscanf(buffer, "%f,%f,%f ; %f,%f,%f ; %f,%f", &xp, &yp, &zp, &xn, &yn, &zn, &xtc, &ytc);
            addPNT(f, newPonto(xp, yp, zp), newPonto(xn, yn, zn), newPonto(xtc, ytc, 0.0f));
        }
        fclose(file);
    }
    return f;
}

vector<float> figuraToVector(Figura f){
    vector<float> result;
    vector<Ponto> pontos = *(f->pontos);
    size_t len = pontos.size();
    for(unsigned long i = 0; i < len; i++){
        Ponto p = pontos[i];
        result.push_back(getX(p));
        result.push_back(getY(p));
        result.push_back(getZ(p));
    }
    return result;
}

vector<float> figuraToNormals(Figura f){
    vector<float> result;
    vector<Ponto> normais = *(f->normais);
    size_t len = normais.size();
    for(unsigned long i = 0; i < len; i++){
        Ponto p = normais[i];
        result.push_back(getX(p));
        result.push_back(getY(p));
        result.push_back(getZ(p));
    }
    return result;
}

vector<float> figuraToTextCoords(Figura f){
    vector<float> result;
    vector<Ponto> textCoords = *(f->textCoords);
    size_t len = textCoords.size();
    for(unsigned long i = 0; i < len; i++){
        Ponto p = textCoords[i];
        result.push_back(getX(p));
        result.push_back(getY(p));
    }
    return result;
}

int size(Figura f){
    vector<Ponto> pontos = *(f->pontos);
    size_t len = pontos.size();
    return len;
}

void deleteFigura(void* figura){
    if(figura){
        Figura fig = (Figura)figura;
        for(Ponto p: *(fig->pontos)){
            deletePonto(p);
        }
        free(fig->textureFile);
        delete fig->pontos;
        free(figura);
    }
}

void deleteFigura2(void* figura){
    if(figura){
        delete ((Figura)figura)->pontos;
        free(figura);
    }
}