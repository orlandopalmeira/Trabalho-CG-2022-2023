#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include <string.h>
#include <stdlib.h>

using namespace std;

// Direção padrão é o eixo positivo dos Y (para cima).
Figura generatePlaneXZ(int length, int divisions, float h = 0.0f, int baixo = 0){
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
        if (baixo == 1){
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

// Direção padrão é o eixo negativo dos Z.
Figura generatePlaneXY(int length, int divisions, float h = 0.0f, int reverse = 0){
    Figura plano = newEmptyFigura();
    if(!plano){ // se deu NULL, é porque houve erros
        return NULL;
    }
    float dimension2 = (float)length / 2, div_side = (float)length/divisions, 
          x1 = -dimension2, z1 = -dimension2,
          x2 = -dimension2, z2 = -dimension2 + div_side,
          x3 = -dimension2 + div_side, z3 = -dimension2,
          x4 = -dimension2 + div_side, z4 = -dimension2 + div_side;
    float arrx[4] = {x1,x2,x3,x4};
    float arrz[4] = {z1,z2,z3,z4};

    // float arrx[4] = {x1,x3,x2,x4};
    // float arrz[4] = {z1,z3,z2,z4};
    if (reverse == 1){
        arrx[1] = x3;
        arrx[2] = x2;
        arrz[1] = z3;
        arrz[2] = z2;
    }
        
    for(int linha = 0; linha < divisions; linha++){
        for(int coluna = 0; coluna < divisions; coluna++){
            // Primeiro triângulo do quadrado
            addPonto(plano, newPonto(arrx[0] + coluna*div_side, arrz[0], h));
            addPonto(plano, newPonto(arrx[1] + coluna*div_side, arrz[1], h));
            addPonto(plano, newPonto(arrx[2] + coluna*div_side, arrz[2], h));
            // Segundo triângulo do quadrado
            addPonto(plano, newPonto(arrx[1] + coluna*div_side, arrz[1], h));
            addPonto(plano, newPonto(arrx[3] + coluna*div_side, arrz[3], h));
            addPonto(plano, newPonto(arrx[2] + coluna*div_side, arrz[2], h));  
        }
        arrz[0] += div_side; arrz[1] += div_side; arrz[2] += div_side; arrz[3] += div_side;
    }   
    return plano;
}

// Direção padrão é o eixo negativo dos X.
Figura generatePlaneYZ(int length, int divisions, float h = 0.0f, int reverse = 0){
    Figura plano = newEmptyFigura();
    if(!plano){ // se deu NULL, é porque houve erros
        return NULL;
    }
    float dimension2 = (float)length / 2, div_side = (float)length/divisions, 
          x1 = -dimension2, z1 = -dimension2,
          x2 = -dimension2, z2 = -dimension2 + div_side,
          x3 = -dimension2 + div_side, z3 = -dimension2,
          x4 = -dimension2 + div_side, z4 = -dimension2 + div_side;
    float arrx[4] = {x1,x2,x3,x4};
    float arrz[4] = {z1,z2,z3,z4};

    // float arrx[4] = {x1,x3,x2,x4};
    // float arrz[4] = {z1,z3,z2,z4};
    if (reverse == 1){
        arrx[1] = x3;
        arrx[2] = x2;
        arrz[1] = z3;
        arrz[2] = z2;
    }
        
    for(int linha = 0; linha < divisions; linha++){
        for(int coluna = 0; coluna < divisions; coluna++){
            // Primeiro triângulo do quadrado
            addPonto(plano, newPonto(h, arrx[0] + coluna*div_side, arrz[0]));
            addPonto(plano, newPonto(h, arrx[1] + coluna*div_side, arrz[1]));
            addPonto(plano, newPonto(h, arrx[2] + coluna*div_side, arrz[2]));
            // Segundo triângulo do quadrado
            addPonto(plano, newPonto(h, arrx[1] + coluna*div_side, arrz[1]));
            addPonto(plano, newPonto(h, arrx[3] + coluna*div_side, arrz[3]));
            addPonto(plano, newPonto(h, arrx[2] + coluna*div_side, arrz[2]));  
        }
        arrz[0] += div_side; arrz[1] += div_side; arrz[2] += div_side; arrz[3] += div_side;
    }   
    return plano;
}

Figura generateBox(int length, int divisions){
    Figura box = newEmptyFigura();
    if(!box){ // se deu NULL, é porque houve erros
        return NULL;
    }
    float dimension2 = (float)length / 2; //, div_side = (float)length/divisions;
    addPontos(box, generatePlaneXZ(length, divisions, -dimension2, 0)); // face de baixo do cubo
    addPontos(box, generatePlaneXZ(length, divisions, dimension2, 1)); // face de cima do cubo
    addPontos(box, generatePlaneXY(length, divisions, -dimension2, 0));
    addPontos(box, generatePlaneXY(length, divisions, dimension2, 1));
    addPontos(box, generatePlaneYZ(length, divisions, -dimension2, 0));
    addPontos(box, generatePlaneYZ(length, divisions, dimension2, 1));

    return box;
}

Figura generateSphere(){
    Figura sphere = newEmptyFigura();
    if(!sphere){ // se deu NULL, é porque houve erros
        return NULL;
    }


    return sphere;
}

Figura generateCone(){
    Figura cone = newEmptyFigura();
    if(!cone){ // se deu NULL, é porque houve erros
        return NULL;
    }


    return cone;
}

int main(int argc, char* argv[]){
    if(argc >= 5){ // Nice
        if(strcmp(argv[1], "plane") == 0){
            int length = atoi(argv[2]), divisions = atoi(argv[3]); // TODO talvez passar logo para float com ATOF
            const char* file_path = argv[4];

            // Figura plano = generatePlaneXZ(length,divisions); // TODO uncomment
            // Testes
            // Figura plano = generatePlaneYZ(length,divisions,0.0f,1);
            Figura plano = generatePlaneXY(length,divisions,-1.0f,1);


            figuraToFile(plano, file_path);
            deleteFigura(plano);
            plano = NULL; // TODO talvez meter esta atribuição a NULL dentro da deleteFigura.

        }else if(strcmp(argv[1], "box") == 0){
            int length = atoi(argv[2]), divisions = atoi(argv[3]);
            const char* file_path = argv[4];

            Figura box = generateBox(length,divisions);
            figuraToFile(box, file_path);
            deleteFigura(box);
            box = NULL; // TODO talvez meter esta atribuição a NULL dentro da deleteFigura.

        }else if(strcmp(argv[1], "sphere") == 0){

        }else if(strcmp(argv[1], "cone") == 0){
            /* code */
        }else{
            printf("Forma inválida\n");
            return 1;
        }
        
    } else {
        printf("Número de argumentos inválido.\n");
        return 1;
    }
    return 0;
}