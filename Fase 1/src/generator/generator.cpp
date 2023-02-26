#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include <string.h>
#include <stdlib.h>

using namespace std;
/*
Figura generatePlaneXZ(int length, int divisions){
    Figura plano = newEmptyFigura();
    if(plano){ // se deu NULL, é porque houve erros
        float dimension2 = (float)length / 2, div_side = (float)length/divisions, 
              x1 = -dimension2, z1 = -dimension2,
              x2 = -dimension2, z2 = -dimension2 + div_side,
              x3 = -dimension2 + div_side, z3 = -dimension2,
              x4 = -dimension2 + div_side, z4 = -dimension2 + div_side;

        for(int linha = 0; linha < divisions; linha++){
            for(int coluna = 0; coluna < divisions; coluna++){
                // Primeiro triângulo do quadrado
                addPonto(plano, newPonto(x1 + coluna*div_side, 0.0f, z1));
                addPonto(plano, newPonto(x2 + coluna*div_side, 0.0f, z2));
                addPonto(plano, newPonto(x3 + coluna*div_side, 0.0f, z3));
                // Segundo triângulo do quadrado
                addPonto(plano, newPonto(x2 + coluna*div_side, 0.0f, z2));
                addPonto(plano, newPonto(x4 + coluna*div_side, 0.0f, z4));
                addPonto(plano, newPonto(x3 + coluna*div_side, 0.0f, z3));  
            }
            z1 += div_side; z2 += div_side; z3 += div_side; z4 += div_side;
        }
    }
    return plano;
}*/

Figura generatePlaneXZ(int length, int divisions, float h = 0.0f, int flag = 0){
    Figura plano = newEmptyFigura();
    if(plano){ // se deu NULL, é porque houve erros
        float dimension2 = (float)length / 2, div_side = (float)length/divisions, 
            x1 = -dimension2, z1 = -dimension2,
            x2 = -dimension2, z2 = -dimension2 + div_side,
            x3 = -dimension2 + div_side, z3 = -dimension2,
            x4 = -dimension2 + div_side, z4 = -dimension2 + div_side;
        float arrx[4] = {x1,x2,x3,x4};
        float arrz[4] = {z1,z2,z3,z4};

        // float arrx[4] = {x1,x3,x2,x4};
        // float arrz[4] = {z1,z3,z2,z4};
        if (flag == 1){
            arrx[1] = x3;
            arrx[2] = x2;
            arrz[1] = z3;
            arrz[2] = z2;
        }
            
        for(int linha = 0; linha < divisions; linha++){
            for(int coluna = 0; coluna < divisions; coluna++){
                // Primeiro triângulo do quadrado
                addPonto(plano, newPonto(arrx[0] + coluna*div_side, h, arrz[0]));
                addPonto(plano, newPonto(arrx[1] + coluna*div_side, h, arrz[1]));
                addPonto(plano, newPonto(arrx[2] + coluna*div_side, h, arrz[2]));
                // Segundo triângulo do quadrado
                addPonto(plano, newPonto(arrx[1] + coluna*div_side, h, arrz[1]));
                addPonto(plano, newPonto(arrx[3] + coluna*div_side, h, arrz[3]));
                addPonto(plano, newPonto(arrx[2] + coluna*div_side, h, arrz[2]));  
            }
            arrz[0] += div_side; arrz[1] += div_side; arrz[2] += div_side; arrz[3] += div_side;
        }   
    }
    return plano;
}

void generateBox(){

}

void generateSphere(){

}

void generateCone(){

}

int main(int argc, char* argv[]){
    if(argc >= 5){ // Nice
        if(strcmp(argv[1], "plane") == 0){
            int length = atoi(argv[2]), divisions = atoi(argv[3]);
            const char* file_path = argv[4];
            Figura plano = generatePlaneXZ(length,divisions,1.0f,0);
            figuraToFile(plano, file_path);
            deleteFigura(plano);
            plano = NULL;

        }else if(strcmp(argv[1], "box") == 0){

        }else if(strcmp(argv[1], "sphere") == 0){

        }else if(strcmp(argv[1], "cone") == 0){
            /* code */
        }else{
            printf("Forma inválida");
            return 1;
        }
        
    } else {
        printf("Número de argumentos inválido.");
        return 1;
    }
    return 0;
}