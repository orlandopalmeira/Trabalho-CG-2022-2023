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

            arrxTex[1] = texDelta;
            arrzTex[1] = 1;
            arrxTex[2] = 0;
            arrzTex[2] = 1 - texDelta;
        }

        for (int linha = 0; linha < divisions; linha++){
            for (int coluna = 0; coluna < divisions; coluna++){
                // Primeiro triângulo do quadrado
                addPNT(plano, newPonto(arrx[0] + coluna*div_side, h, arrz[0] + linha*div_side), newPontoArr(normal), newPonto2f(arrxTex[0] + coluna*texDelta, arrzTex[0]) );
                addPNT(plano, newPonto(arrx[1] + coluna*div_side, h, arrz[1] + linha*div_side), newPontoArr(normal), newPonto2f(arrxTex[1] + coluna*texDelta, arrzTex[1]) );
                addPNT(plano, newPonto(arrx[2] + coluna*div_side, h, arrz[2] + linha*div_side), newPontoArr(normal), newPonto2f(arrxTex[2] + coluna*texDelta, arrzTex[2]) );
                // Segundo triângulo do quadrado
                addPNT(plano, newPonto(arrx[1] + coluna*div_side, h, arrz[1] + linha*div_side), newPontoArr(normal), newPonto2f(arrxTex[1] + coluna*texDelta, arrzTex[1]) );
                addPNT(plano, newPonto(arrx[3] + coluna*div_side, h, arrz[3] + linha*div_side), newPontoArr(normal), newPonto2f(arrxTex[3] + coluna*texDelta, arrzTex[3]) );
                addPNT(plano, newPonto(arrx[2] + coluna*div_side, h, arrz[2] + linha*div_side), newPontoArr(normal), newPonto2f(arrxTex[2] + coluna*texDelta, arrzTex[2]) );
            }
            arrzTex[0] -= texDelta; arrzTex[1] -= texDelta; arrzTex[2] -= texDelta; arrzTex[3] -= texDelta;
        }
    }
    return plano;
}

//* Verificado
// Direção padrão é o eixo positivo dos Z.
Figura generatePlaneXYposZ(int length, int divisions, float h = 0.0f){
    Figura plano = newEmptyFigura();
    if (plano){
        float dimension2 = (float)length / 2, div_side = (float)length / divisions,
            xA = -dimension2, yA = -dimension2,
            xB = -dimension2, yB = -dimension2 + div_side,
            xC = -dimension2 + div_side, yC = -dimension2,
            xD = -dimension2 + div_side, yD = -dimension2 + div_side;
        float arrx[4] = {xA, xB, xC, xD};
        float arry[4] = {yA, yB, yC, yD};
        //* Posição dos indices dos arrays um mini-quadrado que faz parte da face de um cubo.
        // 1   3
        // 0   2

        // Normal virada para o ponto com z = 1
        float normal[3] = {0.0f ,0.0f, 1.0f};

        // Texture coordinates
        float texDelta = 1.0f / divisions;
        float arrS[4] = {0, 0       , texDelta, texDelta};
        float arrT[4] = {0, texDelta, 0       , texDelta};

        for (int linha = 0; linha < divisions; linha++){
            for (int coluna = 0; coluna < divisions; coluna++){
                float x, y, s, t; int i;

                //* Primeiro triângulo do quadrado. Ordem: 0 -> 2 -> 1
                i = 0;
                x = arrx[i] + coluna*div_side; y = arry[i] + linha*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));
                
                i = 2;
                x = arrx[i] + coluna*div_side; y = arry[i] + linha*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));
                
                i = 1;
                x = arrx[i] + coluna*div_side; y = arry[i] + linha*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));
                
                //* Segundo triângulo do quadrado. Ordem: 1 -> 2 -> 3
                i = 1;
                x = arrx[i] + coluna*div_side; y = arry[i] + linha*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));
                
                i = 2;
                x = arrx[i] + coluna*div_side; y = arry[i] + linha*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));

                i = 3;
                x = arrx[i] + coluna*div_side; y = arry[i] + linha*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));
            }
        }
    }
    return plano;
}

//* Verificado
// Direção do eixo negativo dos Z.
Figura generatePlaneXY(int length, int divisions, float h = 0.0f){
    Figura plano = newEmptyFigura();
    if (plano){
        float dimension2 = (float)length / 2, div_side = (float)length / divisions,
            xA = -dimension2, yA = -dimension2,
            xB = -dimension2, yB = -dimension2 + div_side,
            xC = -dimension2 + div_side, yC = -dimension2,
            xD = -dimension2 + div_side, yD = -dimension2 + div_side;
        float arrx[4] = {xA, xB, xC, xD};
        float arry[4] = {yA, yB, yC, yD};
        //* Posição dos indices dos arrays um mini-quadrado que faz parte da face de um cubo.
        // 3   1
        // 2   0

        // Normal virada para o ponto com z = -1
        float normal[3] = {0.0f ,0.0f, -1.0f};

        // Texture coordinates
        float texDelta = 1.0f / divisions;
        float arrS[4] = {1, 1       , 1-texDelta, 1-texDelta};
        float arrT[4] = {0, texDelta, 0         , texDelta};

        for (int linha = 0; linha < divisions; linha++){
            for (int coluna = 0; coluna < divisions; coluna++){
                float x, y, s, t; int i;

                //* Primeiro triângulo do quadrado.  Ordem: 0 -> 1 -> 2
                i = 0;
                x=arrx[i] + coluna*div_side; y=arry[i] + linha*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));
                
                i = 1;
                x=arrx[i] + coluna*div_side; y=arry[i] + linha*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));
                
                i = 2;
                x=arrx[i] + coluna*div_side; y=arry[i] + linha*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));
                
                //* Segundo triângulo do quadrado. Ordem: 1 -> 3 -> 2
                i = 1;
                x=arrx[i] + coluna*div_side; y=arry[i] + linha*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));
                
                i = 3;
                x=arrx[i] + coluna*div_side; y=arry[i] + linha*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));

                i = 2;
                x=arrx[i] + coluna*div_side; y=arry[i] + linha*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(x, y, h), newPontoArr(normal), newPonto2f(s, t));
            }
        }
    }
    return plano;
}

//* Verificado
// Direção do eixo positivo dos X.
Figura generatePlaneYZposX(int length, int divisions, float h = 0.0f){
    Figura plano = newEmptyFigura();
    if (plano){
        float dimension2 = (float)length / 2, div_side = (float)length / divisions,
            yA = -dimension2, zA = -dimension2,
            yB = -dimension2, zB = -dimension2 + div_side,
            yC = -dimension2 + div_side, zC = -dimension2,
            yD = -dimension2 + div_side, zD = -dimension2 + div_side;
        float arry[4] = {yA, yB, yC, yD};
        float arrz[4] = {zA, zB, zC, zD};
        //* Posição dos indices dos arrays um mini-quadrado que faz parte da face de um cubo.
        // 3   2
        // 1   0

        // Normal virada para o ponto com x = 1
        float normal[3] = {1.0f ,0.0f, 0.0f};

        // Texture coordinates
        float texDelta = 1.0f / divisions;
        float arrS[4] = {1, 1-texDelta, 1       , 1-texDelta};
        float arrT[4] = {0, 0         , texDelta, texDelta};

        for (int linha = 0; linha < divisions; linha++){
            for (int coluna = 0; coluna < divisions; coluna++){
                float y, z, s, t; int i;

                //* Primeiro triângulo do quadrado. Ordem: 0 -> 2 -> 1
                i = 0;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));
                
                i = 2;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));
                
                i = 1;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));
                
                //* Segundo triângulo do quadrado. Ordem: 2 -> 3 -> 1
                i = 2;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));
                
                i = 3;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));

                i = 1;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] - coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));
            }
        }
    }
    return plano;
}

//* VERIFICADO
// Direção do eixo negativo dos X.
Figura generatePlaneYZ(int length, int divisions, float h = 0.0f){
    Figura plano = newEmptyFigura();
    if (plano){ 
        float dimension2 = (float)length / 2, div_side = (float)length / divisions,
            yA = -dimension2, zA = -dimension2,
            yB = -dimension2, zB = -dimension2 + div_side,
            yC = -dimension2 + div_side, zC = -dimension2,
            yD = -dimension2 + div_side, zD = -dimension2 + div_side;
        float arry[4] = {yA, yB, yC, yD};
        float arrz[4] = {zA, zB, zC, zD};
        //* Posição dos indices dos arrays um mini-quadrado que faz parte da face de um cubo.
        // 2   3
        // 0   1

        // Normal virada para o ponto com x = -1
        float normal[3] = {-1.0f ,0.0f, 0.0f};

        // Texture coordinates
        float texDelta = 1.0f / divisions;
        float arrS[4] = {0, texDelta, 0       , texDelta};
        float arrT[4] = {0, 0       , texDelta, texDelta};

        for (int linha = 0; linha < divisions; linha++){
            for (int coluna = 0; coluna < divisions; coluna++){
                float y, z, s, t; int i;

                //* Primeiro triângulo do quadrado. Ordem: 0 -> 1 -> 2
                i = 0;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));

                i = 1;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));

                i = 2;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));

                //* Segundo triângulo do quadrado. Ordem: 1 -> 3 -> 2
                i = 1;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));

                i = 3;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));

                i = 2;
                y = arry[i] + linha*div_side; z = arrz[i] + coluna*div_side;
                s = arrS[i] + coluna*texDelta; t = arrT[i] + linha*texDelta;
                addPNT(plano, newPonto(h, y, z), newPontoArr(normal), newPonto2f(s, t));
            }
        }
    }
    return plano;
}


Figura generateBox(int length, int divisions){
    Figura box = newEmptyFigura();
    if (box){
        float dimension2 = (float)length / 2;
        Figura faceCima, faceBaixo, faceLateral1, faceLateral2, faceLateral3, faceLateral4;
        faceCima = generatePlaneXZ(length, divisions, dimension2, 0);
        faceBaixo = generatePlaneXZ(length, divisions, -dimension2, 1);

        faceLateral1 = generatePlaneXY(length, divisions, -dimension2);
        faceLateral2 = generatePlaneXYposZ(length, divisions, dimension2);

        faceLateral3 = generatePlaneYZ(length, divisions, -dimension2);
        faceLateral4 = generatePlaneYZposX(length, divisions, dimension2);

        addPontos(box, faceCima);
        addPontos(box, faceBaixo);
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

    // texturas 
    float s_diff = 1.0f/slices ;
    float t_diff = 1.0f/stacks ;
    
    // flag que indica se o número de stacks é par ou ímpar.
    int n_stacks_is_even = (stacks % 2) == 0;

    int stacks_h = stacks / 2;

    // Construção das faces laterais
    for (int i = 0; i < slices; i++){

        float a1 = i * alpha_diff;
        float a2 = (i+1) * alpha_diff;

        float bUp;
        float bDown;

        // texturas
        float tUp;
        float tDown;
        
        if (n_stacks_is_even){ // Se o número de stacks for par, começa-se a construir as faces a partir do plano XZ.
            bUp = 0;
            bDown = 0;

            // Texturas
            tUp = 0.5f;
            tDown = 0.5f;
        }
        else{ // Caso contrário, cria-se uma base especial.
            bUp = beta_diff / 2;
            bDown = -(beta_diff / 2);

            // Texturas
            tUp = t_diff * (stacks_h + 1); 
            tDown = t_diff * (stacks_h); 

            // Criação da base
            addSpherePoint(sphere, newPontoSph(a1, bDown, radius), newPonto2f(s_diff*i, tDown)); 
            addSpherePoint(sphere, newPontoSph(a2, bDown, radius), newPonto2f(s_diff*(i+1), tDown));
            addSpherePoint(sphere, newPontoSph(a1, bUp, radius), newPonto2f(s_diff*i, tUp));

            addSpherePoint(sphere, newPontoSph(a1, bUp, radius), newPonto2f(s_diff*i, tUp));
            addSpherePoint(sphere, newPontoSph(a2, bDown, radius), newPonto2f(s_diff*(i+1), tDown));
            addSpherePoint(sphere, newPontoSph(a2, bUp, radius), newPonto2f(s_diff*(i+1), tUp));
        }

        
        Ponto p1Up = newPontoSph(a1, bUp, radius), p1Up_ = p1Up;         float t1Up[2]   = {s_diff*i, tUp};
        Ponto p2Up = newPontoSph(a2, bUp, radius), p2Up_ = p2Up;         float t2Up[2]   = {s_diff*(i+1), tUp};
        Ponto p1Down = newPontoSph(a1, bDown, radius), p1Down_ = p1Down; float t1Down[2] = {s_diff*i, tDown};
        Ponto p2Down = newPontoSph(a2, bDown, radius), p2Down_ = p2Down; float t2Down[2] = {s_diff*(i+1), tDown};

        for (int j = 0; j < stacks_h - 1; j++){
            // Construção da stack de cima
            // -- Triângulo da esquerda
            addSpherePoint(sphere, dupPonto(p1Up), newPonto2fArr(t1Up));
            addSpherePoint(sphere, dupPonto(p2Up), newPonto2fArr(t2Up));
            bUp += beta_diff;
            p1Up = newPontoSph(a1, bUp, radius);
            t1Up[1] += t_diff;
            addSpherePoint(sphere, p1Up, newPonto2fArr(t1Up));
            // -- Triângulo da direita
            addSpherePoint(sphere, dupPonto(p1Up), newPonto2fArr(t1Up));
            addSpherePoint(sphere, dupPonto(p2Up), newPonto2fArr(t2Up));
            p2Up = newPontoSph(a2, bUp, radius);
            t2Up[1] += t_diff;
            addSpherePoint(sphere, p2Up, newPonto2fArr(t2Up));

            // Construção da stack de baixo
            // -- Triângulo da direita
            addSpherePoint(sphere, dupPonto(p2Down), newPonto2fArr(t2Down));
            addSpherePoint(sphere, dupPonto(p1Down), newPonto2fArr(t1Down));
            bDown -= beta_diff;
            p2Down = newPontoSph(a2, bDown, radius);
            t2Down[1] -= t_diff;
            addSpherePoint(sphere, p2Down, newPonto2fArr(t2Down));

            // -- Triângulo da esquerda
            addSpherePoint(sphere, dupPonto(p2Down), newPonto2fArr(t2Down));
            addSpherePoint(sphere, dupPonto(p1Down), newPonto2fArr(t1Down));
            p1Down = newPontoSph(a1, bDown, radius);
            t1Down[1] -= t_diff;
            addSpherePoint(sphere, p1Down, newPonto2fArr(t1Down));
        }

        // Construção do triângulo final de cima
        addSpherePoint(sphere, dupPonto(p1Up), newPonto2fArr(t1Up));
        addSpherePoint(sphere, dupPonto(p2Up), newPonto2fArr(t2Up));
        t1Up[1] += t_diff;
        addSpherePoint(sphere, newPonto(0.0f, radius, 0.0f), newPonto2fArr(t1Up)); 
        
        // Construção do triângulo final de baixo
        addSpherePoint(sphere, dupPonto(p2Down), newPonto2fArr(t2Down));
        addSpherePoint(sphere, dupPonto(p1Down), newPonto2fArr(t1Down));
        t2Down[1] -= t_diff;
        addSpherePoint(sphere, newPonto(0.0f, -radius, 0.0f), newPonto2fArr(t2Down)); 
        deletePonto(p1Up_); deletePonto(p1Down_);
        deletePonto(p2Up_); deletePonto(p2Down_);
    }
    return sphere;
}

Figura generateCone(int radius, int height, int slices, int stacks){
    Figura cone = newEmptyFigura();
    if (cone){

        //* Criação da base do cone.
        float alpha = 2.0f * M_PI / slices;
        float cur_alpha = 0.0f;
        Ponto basePoints[slices] = {};

        // normals
        Ponto normals[slices] = {};
        float downNormal[3] = {0.0f, -1.0f, 0.0f};

        // texturas 
        float raio_tex = 0.5f;
        float center_tex[2] = {0.5f, 0.5f}; // ponto central da textura

        for (int i = 0; i < slices; i++){
            Ponto np  = newPonto(radius * sin(cur_alpha), 0.0f, radius * cos(cur_alpha));
            basePoints[i] = np;

            //* normals
            Ponto origem = newPonto(0,0,0);
            Ponto apex = newPonto(0.0f, height, 0.0f);
            float vetorA[3]; // cateto horizontal
            float vetorB[3]; // cateto vertical
            float vetorC[3]; // hipotenusa (de baixo para cima)
            float vetorR[3]; // vetor right
            vetorFrom2Pontos(origem, np, vetorA);
            vetorFrom2Pontos(origem, apex, vetorB);
            vetorFrom2Pontos(np, apex, vetorC);

            cross(vetorA, vetorB, vetorR); // A x B = R
            float normalDaAresta[3];
            cross(vetorC, vetorR, normalDaAresta); // C x R = N
            normalize(normalDaAresta);

            // vetor normal da aresta
            normals[i] = newPontoArr(normalDaAresta);
            //* end-normals

            addPNT(cone, np, newPontoArr(downNormal), newPonto2fSph(center_tex, cur_alpha, raio_tex));
            addPNT(cone, newPonto(0.0f, 0.0f, 0.0f), newPontoArr(downNormal), newPonto2fArr(center_tex));
            cur_alpha += alpha;
            addPNT(cone, newPonto(radius * sin(cur_alpha), 0.0f, radius * cos(cur_alpha)), newPontoArr(downNormal), newPonto2fSph(center_tex, cur_alpha, raio_tex));
        }

        //* Tratamento das faces laterais
        float h_diff = (float)height / stacks;

        // texturas
        float cur_alpha_tex = 0.0f;
        float raio_tex_delta = raio_tex / stacks;
        
        // Para cada face
        for(int j = 0; j < slices; j++){
            
            Ponto p1 = basePoints[j]; // Ponto da base 1 -> p1
            Ponto normal1 = normals[j];// Normal da aresta 1
            int nj = j+1;
            if (nj == slices){ // para voltar ao primeiro ponto da base, uma vez que dá uma volta.
                nj = 0;
            }
            Ponto p2 = basePoints[nj]; // Ponto da base 2 -> p2
            Ponto normal2 = normals[nj];// Normal da aresta 2

            float cur_raio_tex = 0.5f;

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
                addPNT(cone, dupPonto(l_p1), normal1, newPonto2fSph(center_tex, cur_alpha_tex, cur_raio_tex));
                addPNT(cone, dupPonto(l_p2), normal2, newPonto2fSph(center_tex, cur_alpha_tex + alpha, cur_raio_tex));
                l_p1 = newPonto(getX(l_p1) - b1x_diff, getY(l_p1) + h_diff, getZ(l_p1) - b1z_diff);
                addPNT(cone, l_p1, normal1, newPonto2fSph(center_tex, cur_alpha_tex, cur_raio_tex - raio_tex_delta));

                // Triangulo da direita
                addPNT(cone, dupPonto(l_p2), normal2, newPonto2fSph(center_tex, cur_alpha_tex + alpha, cur_raio_tex));
                l_p2 = newPonto(getX(l_p2) - b2x_diff, getY(l_p2) + h_diff , getZ(l_p2) - b2z_diff);
                addPNT(cone, l_p2, normal2, newPonto2fSph(center_tex, cur_alpha_tex + alpha, cur_raio_tex - raio_tex_delta));
                addPNT(cone, dupPonto(l_p1), normal1, newPonto2fSph(center_tex, cur_alpha_tex, cur_raio_tex - raio_tex_delta));

                cur_raio_tex -= raio_tex_delta;
            }
            // Construir triangulo do topo.
            addPNT(cone, dupPonto(l_p1), normal1, newPonto2fSph(center_tex, cur_alpha_tex, cur_raio_tex));
            addPNT(cone, dupPonto(l_p2), normal2, newPonto2fSph(center_tex, cur_alpha_tex + alpha, cur_raio_tex));
            addPNT(cone, newPonto(0.0f, height, 0.0f), newPonto(0.0f, 1.0f, 0.0f), newPonto2fArr(center_tex)); // vértice topo do triângulo do topo

            cur_alpha_tex += alpha;
        }
    }
    return cone;
}

Figura generateRing(float ri, float re, int slices){
    Figura ring = newEmptyFigura();
    float a = 0, delta = (2*M_PI) / slices;
    //normals
    float normalup[3]   = {0.0f, 1.0f, 0.0f};
    float normaldown[3] = {0.0f, -1.0f, 0.0f};
    //textures 
    float texDelta = 1/slices;
    float s = 0;

    if(ring){
        for (int i = 0; i < slices; i++, a += delta, s += texDelta){
            // Desenho da parte de cima do anel
            addPNT(ring, newPontoSph(a,0.0f,ri), newPontoArr(normalup), newPonto2f(s, 0));
            addPNT(ring, newPontoSph(a,0.0f,re), newPontoArr(normalup), newPonto2f(s, 1));
            addPNT(ring, newPontoSph(a+delta,0.0f,ri), newPontoArr(normalup), newPonto2f(s + texDelta, 0));

            addPNT(ring, newPontoSph(a+delta,0.0f,ri), newPontoArr(normalup), newPonto2f(s + texDelta, 0));
            addPNT(ring, newPontoSph(a,0.0f,re), newPontoArr(normalup), newPonto2f(s, 1));
            addPNT(ring, newPontoSph(a+delta,0.0f,re), newPontoArr(normalup), newPonto2f(s + texDelta, 1));

            // Desenho da parte de baixo do anel
            addPNT(ring, newPontoSph(a+delta,0.0f,ri), newPontoArr(normaldown), newPonto2f(s + texDelta, 0));
            addPNT(ring, newPontoSph(a,0.0f,re), newPontoArr(normaldown), newPonto2f(s, 1));
            addPNT(ring, newPontoSph(a,0.0f,ri), newPontoArr(normaldown), newPonto2f(s, 0));

            addPNT(ring, newPontoSph(a,0.0f,re), newPontoArr(normaldown), newPonto2f(s, 1));
            addPNT(ring, newPontoSph(a+delta,0.0f,ri), newPontoArr(normaldown), newPonto2f(s + texDelta, 0));
            addPNT(ring, newPontoSph(a+delta,0.0f,re), newPontoArr(normaldown), newPonto2f(s + texDelta, 1));
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
    float A[3], B[3], C[3], D[3]; // pontos
    float NA[3], NB[3], NC[3], ND[3]; // normais
    float TCA[2], TCB[2], TCC[2], TCD[2]; // coordenadas de textura
    vector<vector<vector<float>>> patches = readPatchesFile(filePath);

    for(vector<vector<float>> patch : patches){ // um patch tem 16 pontos
        for(int i = 0; i < tessellation; i++, u += delta){
            for(int j = 0; j < tessellation; j++, v += delta){
                // Cálculo dos pontos, normais e coordenadas de textura
                surfacePoint(u,v,patch,A,NA,TCA);
                surfacePoint(u,v+delta,patch,B,NB,TCB);
                surfacePoint(u+delta,v,patch,C,NC,TCC);
                surfacePoint(u+delta,v+delta,patch,D,ND,TCD);
                // Triangulação
                addPNTArr(result,C,NC,TCC);
                addPNTArr(result,A,NA,TCA);
                addPNTArr(result,B,NB,TCB);
                addPNTArr(result,B,NB,TCB);
                addPNTArr(result,D,ND,TCD);
                addPNTArr(result,C,NC,TCC);
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
            const char* patchesFile = argv[2];
            float tessellation = atoi(argv[3]);
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