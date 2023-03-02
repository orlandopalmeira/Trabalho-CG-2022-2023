#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include <string.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define PI 3.14159265358979323846

using namespace std;

// Direção padrão é o eixo positivo dos Y (para cima).
Figura generatePlaneXZ(int length, int divisions, float h = 0.0f, int baixo = 0){
    Figura plano = newEmptyFigura();
    if (plano){ // se deu NULL, é porque houve erros
        float dimension2 = (float)length / 2, div_side = (float)length / divisions,
              x1 = -dimension2, z1 = -dimension2,
              x2 = -dimension2, z2 = -dimension2 + div_side,
              x3 = -dimension2 + div_side, z3 = -dimension2,
              x4 = -dimension2 + div_side, z4 = -dimension2 + div_side;
        float arrx[4] = {x1, x2, x3, x4};
        float arrz[4] = {z1, z2, z3, z4};

        // float arrx[4] = {x1,x3,x2,x4};
        // float arrz[4] = {z1,z3,z2,z4};
        if (baixo == 1){
            arrx[1] = x3;
            arrx[2] = x2;
            arrz[1] = z3;
            arrz[2] = z2;
        }

        for (int linha = 0; linha < divisions; linha++){
            for (int coluna = 0; coluna < divisions; coluna++){
                // Primeiro triângulo do quadrado
                addPonto(plano, newPonto(arrx[0] + coluna * div_side, h, arrz[0]));
                addPonto(plano, newPonto(arrx[1] + coluna * div_side, h, arrz[1]));
                addPonto(plano, newPonto(arrx[2] + coluna * div_side, h, arrz[2]));
                addPonto(plano, newPonto(arrx[0] + coluna * div_side, h, arrz[0]));
                addPonto(plano, newPonto(arrx[1] + coluna * div_side, h, arrz[1]));
                addPonto(plano, newPonto(arrx[2] + coluna * div_side, h, arrz[2]));
                // Segundo triângulo do quadrado
                addPonto(plano, newPonto(arrx[1] + coluna * div_side, h, arrz[1]));
                addPonto(plano, newPonto(arrx[3] + coluna * div_side, h, arrz[3]));
                addPonto(plano, newPonto(arrx[2] + coluna * div_side, h, arrz[2]));
                addPonto(plano, newPonto(arrx[1] + coluna * div_side, h, arrz[1]));
                addPonto(plano, newPonto(arrx[3] + coluna * div_side, h, arrz[3]));
                addPonto(plano, newPonto(arrx[2] + coluna * div_side, h, arrz[2]));
            }
            arrz[0] += div_side;arrz[1] += div_side;arrz[2] += div_side;arrz[3] += div_side;
        }
    }
    return plano;
}

// Direção padrão é o eixo negativo dos Z.
Figura generatePlaneXY(int length, int divisions, float h = 0.0f, int reverse = 0){
    Figura plano = newEmptyFigura();
    if (plano){
        float dimension2 = (float)length / 2, div_side = (float)length / divisions,
            x1 = -dimension2, z1 = -dimension2,
            x2 = -dimension2, z2 = -dimension2 + div_side,
            x3 = -dimension2 + div_side, z3 = -dimension2,
            x4 = -dimension2 + div_side, z4 = -dimension2 + div_side;
        float arrx[4] = {x1, x2, x3, x4};
        float arrz[4] = {z1, z2, z3, z4};

        // float arrx[4] = {x1,x3,x2,x4};
        // float arrz[4] = {z1,z3,z2,z4};
        if (reverse == 1)
        {
            arrx[1] = x3;
            arrx[2] = x2;
            arrz[1] = z3;
            arrz[2] = z2;
        }

        for (int linha = 0; linha < divisions; linha++)
        {
            for (int coluna = 0; coluna < divisions; coluna++){
                // Primeiro triângulo do quadrado
                addPonto(plano, newPonto(arrx[0] + coluna * div_side, arrz[0], h));
                addPonto(plano, newPonto(arrx[1] + coluna * div_side, arrz[1], h));
                addPonto(plano, newPonto(arrx[2] + coluna * div_side, arrz[2], h));
                addPonto(plano, newPonto(arrx[0] + coluna * div_side, arrz[0], h));
                addPonto(plano, newPonto(arrx[1] + coluna * div_side, arrz[1], h));
                addPonto(plano, newPonto(arrx[2] + coluna * div_side, arrz[2], h));
                // Segundo triângulo do quadrado
                addPonto(plano, newPonto(arrx[1] + coluna * div_side, arrz[1], h));
                addPonto(plano, newPonto(arrx[3] + coluna * div_side, arrz[3], h));
                addPonto(plano, newPonto(arrx[2] + coluna * div_side, arrz[2], h));
                addPonto(plano, newPonto(arrx[1] + coluna * div_side, arrz[1], h));
                addPonto(plano, newPonto(arrx[3] + coluna * div_side, arrz[3], h));
                addPonto(plano, newPonto(arrx[2] + coluna * div_side, arrz[2], h));
            }
            arrz[0] += div_side;
            arrz[1] += div_side;
            arrz[2] += div_side;
            arrz[3] += div_side;
        }
    }
    return plano;
}

// Direção padrão é o eixo negativo dos X.
Figura generatePlaneYZ(int length, int divisions, float h = 0.0f, int reverse = 0){
    Figura plano = newEmptyFigura();
    if (plano){ 
        float dimension2 = (float)length / 2, div_side = (float)length / divisions,
            x1 = -dimension2, z1 = -dimension2,
            x2 = -dimension2, z2 = -dimension2 + div_side,
            x3 = -dimension2 + div_side, z3 = -dimension2,
            x4 = -dimension2 + div_side, z4 = -dimension2 + div_side;
        float arrx[4] = {x1, x2, x3, x4};
        float arrz[4] = {z1, z2, z3, z4};

        // float arrx[4] = {x1,x3,x2,x4};
        // float arrz[4] = {z1,z3,z2,z4};
        if (reverse == 1)
        {
            arrx[1] = x3;
            arrx[2] = x2;
            arrz[1] = z3;
            arrz[2] = z2;
        }

        for (int linha = 0; linha < divisions; linha++)
        {
            for (int coluna = 0; coluna < divisions; coluna++){
                // Primeiro triângulo do quadrado
                addPonto(plano, newPonto(h, arrx[0] + coluna * div_side, arrz[0]));
                addPonto(plano, newPonto(h, arrx[1] + coluna * div_side, arrz[1]));
                addPonto(plano, newPonto(h, arrx[2] + coluna * div_side, arrz[2]));
                addPonto(plano, newPonto(h, arrx[0] + coluna * div_side, arrz[0]));
                addPonto(plano, newPonto(h, arrx[1] + coluna * div_side, arrz[1]));
                addPonto(plano, newPonto(h, arrx[2] + coluna * div_side, arrz[2]));
                // Segundo triângulo do quadrado
                addPonto(plano, newPonto(h, arrx[1] + coluna * div_side, arrz[1]));
                addPonto(plano, newPonto(h, arrx[3] + coluna * div_side, arrz[3]));
                addPonto(plano, newPonto(h, arrx[2] + coluna * div_side, arrz[2]));
                addPonto(plano, newPonto(h, arrx[1] + coluna * div_side, arrz[1]));
                addPonto(plano, newPonto(h, arrx[3] + coluna * div_side, arrz[3]));
                addPonto(plano, newPonto(h, arrx[2] + coluna * div_side, arrz[2]));
            }
            arrz[0] += div_side;
            arrz[1] += div_side;
            arrz[2] += div_side;
            arrz[3] += div_side;
        }
    }
    return plano;
}

Figura generateBox(int length, int divisions){
    Figura box = newEmptyFigura();
    if (box){// se deu NULL, é porque houve erros
        float dimension2 = (float)length / 2; //, div_side = (float)length/divisions;
        Figura faceCima, faceBaixo, faceLateral1, faceLateral2, faceLateral3, faceLateral4;
        faceCima = generatePlaneXZ(length, divisions, dimension2, 0);
        faceBaixo = generatePlaneXZ(length, divisions, -dimension2, 1);
        faceLateral1 = generatePlaneXY(length, divisions, -dimension2, 0);
        faceLateral2 = generatePlaneXY(length, divisions, dimension2, 1);
        faceLateral3 = generatePlaneYZ(length, divisions, -dimension2, 0);
        faceLateral4 = generatePlaneYZ(length, divisions, dimension2, 1);
        addPontos(box, faceCima);  // face de baixo do cubo
        addPontos(box, faceBaixo); // face de cima do cubo
        addPontos(box, faceLateral1);
        addPontos(box, faceLateral2);
        addPontos(box, faceLateral3);
        addPontos(box, faceLateral4);
        deleteFigura2(faceCima);
        deleteFigura2(faceBaixo);
        deleteFigura2(faceLateral1);
        deleteFigura2(faceLateral2);
        deleteFigura2(faceLateral3);
        deleteFigura2(faceLateral4);
    }
    return box;
}

Figura generateSphere(){
    Figura sphere = newEmptyFigura();

    return sphere;
}

Figura generateCone(int radius, int height, int slices, int stacks){
    Figura cone = newEmptyFigura();
    if (cone){
        // Criação da base do cone.
        float alpha = 2.0f * M_PI / slices;
        float start = 0.0f;
        Ponto basePoints[slices] = {};
        for (int i = 0; i < slices; i++){
            Ponto np = newPonto(radius * sin(start), 0.0f, radius * cos(start));
            basePoints[i] = np;
            addPonto(cone, np);
            addPonto(cone, newPonto(0.0f, 0.0f, 0.0f));
            start += alpha;
            addPonto(cone, newPonto(radius * sin(start), 0.0f, radius * cos(start)));
        }

        // Tratamento das faces laterais
        float h_diff = (float)height / stacks;
        
        // Para cada face
        for(int j = 0; j < slices; j++){
            Ponto p1 = basePoints[j]; // Ponto da base 1 - p1
            int nj = j+1;
            if (j + 1 == slices){ // para voltar ao primeiro ponto da base, uma vez que dá uma volta.
                nj = 0;
            }
            Ponto p2 = basePoints[nj]; // Ponto da base 2 - p2
            //float b1_diff = distanceToOrigin(p1) / stacks;
            float b1x_diff = getX(p1) / stacks; // Diferença entre a coordenada X e 0 do p1
            float b1z_diff = getZ(p1) / stacks; // Diferença entre a coordenada Z e 0 do p1
            //float b2_diff = distanceToOrigin(p2) / stacks;
            float b2x_diff = getX(p2) / stacks; // Diferença entre a coordenada X e 0 do p2
            float b2z_diff = getZ(p2) / stacks; // Diferença entre a coordenada Z e 0 do p2
            Ponto l_p1 = p1;
            Ponto l_p2 = p2;
            // Para cada stack da face
            for(int i = 0; i < stacks-1; i++){
                // Triangulo da esquerda
                addPonto(cone, dupPonto(l_p1));
                addPonto(cone, dupPonto(l_p2));
                l_p1 = newPonto(getX(l_p1) - b1x_diff, getY(l_p1) + h_diff  , getZ(l_p1) - b1z_diff);
                addPonto(cone, l_p1);

                // Triangulo da direita
                addPonto(cone, dupPonto(l_p2));
                l_p2 = newPonto(getX(l_p2) - b2x_diff, getY(l_p2) + h_diff  , getZ(l_p2) - b2z_diff);
                addPonto(cone, l_p2);
                addPonto(cone, dupPonto(l_p1));
            }
            // Construir triangulo do topo.
            addPonto(cone, dupPonto(l_p1));
            addPonto(cone, dupPonto(l_p2));
            addPonto(cone, newPonto(0.0f, (float)height, 0.0f)); // vértice topo do triângulo do topo
        }
    }
    return cone;
}

int main(int argc, char *argv[]){
    if (argc >= 5){ // Nice
        if (strcmp(argv[1], "plane") == 0){
            int length = atoi(argv[2]), divisions = atoi(argv[3]); // TODO talvez passar logo para float com ATOF
            const char *file_path = argv[4];

            Figura plano = generatePlaneXZ(length, divisions);
            figuraToFile(plano, file_path);
            deleteFigura(plano);
        }
        else if (strcmp(argv[1], "box") == 0){
            int length = atoi(argv[2]), divisions = atoi(argv[3]);
            const char *file_path = argv[4];

            Figura box = generateBox(length, divisions);
            figuraToFile(box, file_path); // TODO tbm daria para modular estas figuraTofiles
            deleteFigura(box);
        }
        else if (strcmp(argv[1], "sphere") == 0){

        }
        else if (strcmp(argv[1], "cone") == 0){
            int radius = atoi(argv[2]), height = atoi(argv[3]), slices = atoi(argv[4]), stacks = atoi(argv[5]);
            const char *file_path = argv[6];

            Figura cone = generateCone(radius, height, slices, stacks);
            figuraToFile(cone, file_path);
            deleteFigura(cone);
        }
        else{
            printf("Forma inválida\n");
            return 1;
        }
    }
    else{
        printf("Número de argumentos inválido.\n");
        return 1;
    }
    return 0;
}