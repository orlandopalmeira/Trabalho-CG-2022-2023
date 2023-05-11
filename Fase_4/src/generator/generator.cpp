#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include "../utils/matrix.hpp"
#include <string.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

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

        // Normal virada para cima (y = 1)
        float normal[3] = {0.0f ,1.0f, 0.0f};

        // Texture coordinates
        float texDelta = 1.0f / divisions;
        float arrxTex[4] = {0, 0         , texDelta, texDelta};
        float arrzTex[4] = {1, 1-texDelta, 1       , 1-texDelta};

        if (baixo == 1){
            // Faço a troca para que a ordem em que desenha o triangulo passe a ser 0 2 1 3 (imaginando a grelha ordenada).
            // para que a regra da mão direita indique os triangulos para baixo.
            arrx[1] = x3;
            arrz[1] = z3;
            arrx[2] = x2;
            arrz[2] = z2;

            // Vira a normal para baixo (y = -1)
            normal[1] = -1.0f;

            // Processo igual ao efetuado em cima.
            arrxTex[1] = texDelta;
            arrzTex[1] = 1;
            arrxTex[2] = 0;
            arrzTex[2] = 1 - texDelta;
        }

        for (int linha = 0; linha < divisions; linha++){
            for (int coluna = 0; coluna < divisions; coluna++){
                // Primeiro triângulo do quadrado
                addPontoNormalTextCoord(plano, newPonto(arrx[0] + coluna * div_side, h, arrz[0]), newPontoArr(normal), newPonto2f(arrxTex[0] + coluna * texDelta, arrzTex[0]) );
                addPontoNormalTextCoord(plano, newPonto(arrx[1] + coluna * div_side, h, arrz[1]), newPontoArr(normal), newPonto2f(arrxTex[1] + coluna * texDelta, arrzTex[1]) );
                addPontoNormalTextCoord(plano, newPonto(arrx[2] + coluna * div_side, h, arrz[2]), newPontoArr(normal), newPonto2f(arrxTex[2] + coluna * texDelta, arrzTex[2]) );
                // Segundo triângulo do quadrado
                addPontoNormalTextCoord(plano, newPonto(arrx[1] + coluna * div_side, h, arrz[1]), newPontoArr(normal), newPonto2f(arrxTex[1] + coluna * texDelta, arrzTex[1]) );
                addPontoNormalTextCoord(plano, newPonto(arrx[3] + coluna * div_side, h, arrz[3]), newPontoArr(normal), newPonto2f(arrxTex[3] + coluna * texDelta, arrzTex[3]) );
                addPontoNormalTextCoord(plano, newPonto(arrx[2] + coluna * div_side, h, arrz[2]), newPontoArr(normal), newPonto2f(arrxTex[2] + coluna * texDelta, arrzTex[2]) );
            }
            arrz[0] += div_side; arrz[1] += div_side; arrz[2] += div_side; arrz[3] += div_side; 
            arrzTex[0] -= texDelta; arrzTex[1] -= texDelta; arrzTex[2] -= texDelta; arrzTex[3] -= texDelta;
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

        // Normal virada para o ponto com z = -1
        float normal[3] = {0.0f ,0.0f, -1.0f};

        if (reverse == 1){
            arrx[1] = x3;
            arrx[2] = x2;
            arrz[1] = z3;
            arrz[2] = z2;

            normal[2] = 1.0f;
        }

        for (int linha = 0; linha < divisions; linha++)
        {
            for (int coluna = 0; coluna < divisions; coluna++){
                // Primeiro triângulo do quadrado
                addPontoNormalTextCoord(plano, newPonto(arrx[0] + coluna * div_side, arrz[0], h), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord 
                addPontoNormalTextCoord(plano, newPonto(arrx[1] + coluna * div_side, arrz[1], h), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord 
                addPontoNormalTextCoord(plano, newPonto(arrx[2] + coluna * div_side, arrz[2], h), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord 
                // Segundo triângulo do quadrado
                addPontoNormalTextCoord(plano, newPonto(arrx[1] + coluna * div_side, arrz[1], h), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord
                addPontoNormalTextCoord(plano, newPonto(arrx[3] + coluna * div_side, arrz[3], h), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord
                addPontoNormalTextCoord(plano, newPonto(arrx[2] + coluna * div_side, arrz[2], h), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord
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

        // Normal virada para o ponto com x = -1
        float normal[3] = {-1.0f ,0.0f, 0.0f};

        if (reverse == 1){
            arrx[1] = x3;
            arrx[2] = x2;
            arrz[1] = z3;
            arrz[2] = z2;

            normal[0] = 1.0f;
        }

        for (int linha = 0; linha < divisions; linha++){
            for (int coluna = 0; coluna < divisions; coluna++){
                // Primeiro triângulo do quadrado
                addPontoNormalTextCoord(plano, newPonto(h, arrx[0] + coluna * div_side, arrz[0]), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord
                addPontoNormalTextCoord(plano, newPonto(h, arrx[1] + coluna * div_side, arrz[1]), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord
                addPontoNormalTextCoord(plano, newPonto(h, arrx[2] + coluna * div_side, arrz[2]), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord
                // Segundo triângulo do quadrado
                addPontoNormalTextCoord(plano, newPonto(h, arrx[1] + coluna * div_side, arrz[1]), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord
                addPontoNormalTextCoord(plano, newPonto(h, arrx[3] + coluna * div_side, arrz[3]), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord
                addPontoNormalTextCoord(plano, newPonto(h, arrx[2] + coluna * div_side, arrz[2]), newPontoArr(normal), newPonto2f(0,0)); //! sem text coord
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

Figura generateSphere(int radius, int slices, int stacks){
    Figura sphere = newEmptyFigura();
    if (!sphere){
        return NULL;
    }
    
    float alpha_diff = (2.0f * M_PI) / slices;
    float beta_diff = M_PI / stacks;
    
    // flag que indica se o número de stacks é par ou ímpar.
    int n_stacks_is_even = (stacks % 2) == 0;

    stacks /= 2;

    // Construção das faces laterais
    for (int i = 0; i < slices; i++){

        float a1 = i * alpha_diff;
        float a2 = (i+1) * alpha_diff;

        float bUp;
        float bDown;

        if (n_stacks_is_even){ // Se o número de stacks for par, começa-se a construir as faces a partir do plano XZ.
            bUp = 0;
            bDown = 0;
        }
        else{ // Caso contrário, cria-se uma base especial.
            bUp = beta_diff / 2;
            bDown = -(beta_diff / 2);

            // Criação da base
            addPonto(sphere, newPontoSph(a1, bDown, radius)); 
            addPonto(sphere, newPontoSph(a2, bDown, radius));
            addPonto(sphere, newPontoSph(a1, bUp, radius));

            addPonto(sphere, newPontoSph(a1, bUp, radius));
            addPonto(sphere, newPontoSph(a2, bDown, radius));
            addPonto(sphere, newPontoSph(a2, bUp, radius));
        }

        Ponto p1Up = newPontoSph(a1, bUp, radius), p1Up_ = p1Up;
        Ponto p2Up = newPontoSph(a2, bUp, radius), p2Up_ = p2Up;
        Ponto p1Down = newPontoSph(a1, bDown, radius), p1Down_ = p1Down;
        Ponto p2Down = newPontoSph(a2, bDown, radius), p2Down_ = p2Down;

        for (int j = 0; j < stacks - 1; j++){
            // Construção da stack de cima
            // -- Triângulo da esquerda
            addPonto(sphere, dupPonto(p1Up));
            addPonto(sphere, dupPonto(p2Up));
            bUp += beta_diff;
            p1Up = newPontoSph(a1, bUp, radius);
            addPonto(sphere, p1Up);
            // -- Triângulo da direita
            addPonto(sphere, dupPonto(p1Up));
            addPonto(sphere, dupPonto(p2Up));
            p2Up = newPontoSph(a2, bUp, radius);
            addPonto(sphere, p2Up);

            // Construção da stack de baixo
            // -- Triângulo da direita
            addPonto(sphere, dupPonto(p2Down));
            addPonto(sphere, dupPonto(p1Down));
            bDown -= beta_diff;
            p2Down = newPontoSph(a2, bDown, radius);
            addPonto(sphere, p2Down);

            // -- Triângulo da esquerda
            addPonto(sphere, dupPonto(p2Down));
            addPonto(sphere, dupPonto(p1Down));
            p1Down = newPontoSph(a1, bDown, radius);
            addPonto(sphere, p1Down);
        }

        // Construção do triângulo final de cima
        addPonto(sphere, dupPonto(p1Up));
        addPonto(sphere, dupPonto(p2Up));
        addPonto(sphere, newPonto(0.0f, radius, 0.0f));
        
        // Construção do triângulo final de baixo
        addPonto(sphere, dupPonto(p2Down));
        addPonto(sphere, dupPonto(p1Down));
        addPonto(sphere, newPonto(0.0f, -radius, 0.0f));
        deletePonto(p1Up_); deletePonto(p1Down_); // para efeitos de gestão de memória
        deletePonto(p2Up_); deletePonto(p2Down_); // para efeitos de gestão de memória
    }
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

Figura generateRing(float ri, float re, int slices){
    Figura ring = newEmptyFigura();
    float a = 0,delta = (2*M_PI) / slices;
    if(ring){
        for (int i = 0; i < slices; i++, a += delta){
            addPonto(ring, newPontoSph(a,0.0f,ri));
            addPonto(ring, newPontoSph(a,0.0f,re));
            addPonto(ring, newPontoSph(a+delta,0.0f,ri));

            addPonto(ring, newPontoSph(a+delta,0.0f,ri));
            addPonto(ring, newPontoSph(a,0.0f,re));
            addPonto(ring, newPontoSph(a+delta,0.0f,re));

            addPonto(ring, newPontoSph(a+delta,0.0f,ri));
            addPonto(ring, newPontoSph(a,0.0f,re));
            addPonto(ring, newPontoSph(a,0.0f,ri));

            addPonto(ring, newPontoSph(a,0.0f,re));
            addPonto(ring, newPontoSph(a+delta,0.0f,ri));
            addPonto(ring, newPontoSph(a+delta,0.0f,re));
        }
    }
    return ring;
}

vector<vector<vector<float>>> readPatchesFile(const char* filePath){
    FILE* file = fopen(filePath,"r");
    vector<vector<vector<float>>> result;
    if(file){
        char buffer[2048];
        // Obtenção do número de patches
        if(!fgets(buffer,2047,file)) return result;
        int numPatches = atoi(buffer);
        vector<vector<int>> indicesPerPatch; // vector de vectores, cada vector tem tamanho 16

        // Obtenção dos índices de cada patch
        for(int i = 0; i < numPatches; i++){
            if(!fgets(buffer,2047,file)) return result;
            vector<int> indices;
            for(char* token = strtok(buffer,","); token; token = strtok(NULL,",")){
                indices.push_back(atoi(token));
            }
            indicesPerPatch.push_back(indices);
        }

        // Obtenção do número de pontos de controlo
        if(!fgets(buffer,2047,file)) return result;
        int numControlPoints = atoi(buffer);

        // Obtenção dos pontos de controlo
        vector<vector<float>> controlPoints;
        for(int i = 0; i < numControlPoints; i++){
            if(!fgets(buffer,2047,file)) return result;
            vector<float> point;
            for(char* token = strtok(buffer,","); token; token = strtok(NULL,",")){
                point.push_back(atof(token));
            }
            controlPoints.push_back(point);
        }

        // Construção dos patches
        for(vector<int> indices : indicesPerPatch){
            vector<vector<float>> patch; // um patch é um conjunto de pontos, um ponto é um vector<float> de tamanho 3. Um patch terá 16 pontos.
            for(int indice : indices){
                vector<float> point;
                point.push_back(controlPoints[indice][0]);
                point.push_back(controlPoints[indice][1]);
                point.push_back(controlPoints[indice][2]);
                patch.push_back(point);
            }
            result.push_back(patch);
        }
        fclose(file);
    }
    return result;
}

Figura generateSurface(const char* filePath, int tessellation){
    Figura result = newEmptyFigura();
    float u = 0.0f, v = 0.0f, delta = 1.0f/tessellation;
    float A[3], B[3], C[3], D[3];
    vector<vector<vector<float>>> patches = readPatchesFile(filePath);
    for(vector<vector<float>> patch : patches){ // um patch tem 16 pontos
        for(int i = 0; i < tessellation; i++, u += delta){
            for(int j = 0; j < tessellation; j++, v += delta){
                // Cálculo dos pontos
                surfacePoint(u,v,patch,A);
                surfacePoint(u,v+delta,patch,B);
                surfacePoint(u+delta,v,patch,C);
                surfacePoint(u+delta,v+delta,patch,D);
                // Triangulação
                addPontoArr(result,C);
                addPontoArr(result,A);
                addPontoArr(result,B);
                addPontoArr(result,B);
                addPontoArr(result,D);
                addPontoArr(result,C);
            }
            v = 0.0f;
        }
        u = v = 0.0f;
    }
    return result;
}

int main(int argc, char *argv[]){
    if (argc >= 5){
        Figura figura;
        const char *file_path;
        if (strcmp(argv[1], "plane") == 0){
            int length = atoi(argv[2]), divisions = atoi(argv[3]); 
            file_path = argv[4];

            figura = generatePlaneXZ(length, divisions);
        }
        else if (strcmp(argv[1], "box") == 0){
            int length = atoi(argv[2]), divisions = atoi(argv[3]);
            file_path = argv[4];

            figura = generateBox(length, divisions);
        }
        else if (strcmp(argv[1], "sphere") == 0){
            int radius = atoi(argv[2]), slices = atoi(argv[3]), stacks = atoi(argv[4]);
            file_path = argv[5];

            figura = generateSphere(radius, slices, stacks);
        }
        else if (strcmp(argv[1], "cone") == 0){
            int radius = atoi(argv[2]), height = atoi(argv[3]), slices = atoi(argv[4]), stacks = atoi(argv[5]);
            file_path = argv[6];

            figura = generateCone(radius, height, slices, stacks);
        }
        else if(strcmp(argv[1], "ring") == 0){
            float ri = atof(argv[2]), re = atof(argv[3]), slices = atoi(argv[4]);
            file_path = argv[5];

            figura = generateRing(ri,re,slices);  
        }
        else if(strcmp(argv[1], "patch") == 0){
            float tessellation = atoi(argv[2]);
            const char* patchesFile = argv[3];
            file_path = argv[4];

            figura = generateSurface(patchesFile,tessellation);
        }
        else{
            printf("Forma inválida\n");
            return 1;
        }
        figuraToFile(figura, file_path);
        deleteFigura(figura);
    }
    else{
        printf("Número de argumentos inválido.\n");
        return 1;
    }
    return 0;
}