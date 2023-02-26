#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"

void generatePlane(/*int length, int divisions*/){
    Figura plano = newEmptyFigura();
    if(plano){ // se deu NULL, é porque houve erros
        // Não sei para que serve o length e o divisions. Penso que o length é a largura e comprimento do plano
        deleteFigura(plano); 
    }
}

void generateBox(){

}

void generateSphere(){

}

void generateCone(){

}

int main(/*int argc, char* argv[]*/){
    // [Linux] Para obter o executável do generator, executar "make generator.exe"
    return 0;
}