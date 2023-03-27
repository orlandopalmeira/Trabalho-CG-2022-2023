#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include "../utils/list.hpp"
#include "../tinyXML/tinyxml.h"
#include "config.hpp"
#include "math.h"
#include <iostream>
#include <filesystem>

using namespace std;

// Códigos de cores
#define RED 1.0f,0.0f,0.0f
#define GREEN 0.0f,1.0f,0.0f
#define BLUE 0.0f,0.0f,1.0f
#define YELLOW 1.0f, 1.0f, 0.0f
#define CYAN 0.0f, 1.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f

// Variáveis da câmara
float alpha = M_PI / 4;
float beta_ = M_PI / 4;
float radius = 5.0f;
float camx = 5.0f;
float camy = 5.0f;
float camz = 5.0f;
float lookAtx = 0.0f;
float lookAty = 0.0f;
float lookAtz = 0.0f;
float upx = 0.0f;
float upy = 0.0f;
float upz = 0.0f;

int mode = GL_LINE;
int show_eixos = 0;

Config configuration = NULL;

// Desenha os eixos, caso a flag esteja ativa.
void drawEixos(){
	if (show_eixos){
		glBegin(GL_LINES);
		// X axis in red
		glColor3f(RED);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(GREEN);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(BLUE);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
		glEnd();
	}
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	//gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
	gluPerspective(getFov(configuration), ratio, getNear(configuration), getFar(configuration));

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawFiguras(List figs){
	for(unsigned long i = 0; i < getListLength(figs); i++){
		Figura fig = (Figura)getListElemAt(figs,i);
		List figPontos = getPontos(fig);
		for(unsigned long j = 0; j < getListLength(figPontos); j++){
			Ponto point = (Ponto)getListElemAt(figPontos,j);
			glVertex3f(getX(point), getY(point), getZ(point));
		}
	}
}

void drawGroups(Tree groups){
	if(groups){
		glPushMatrix(); // guarda o estado dos eixos

		Group group = (Group)getRootValue(groups);
		List transforms = getGroupTransforms(group), models = getGroupModels(group);

		// Definição das transformações
		for(unsigned long i = 0; i < getListLength(transforms); i++){
			Transform t = (Transform)getListElemAt(transforms,i);
			float x = transformX(t);
			float y = transformY(t);
			float z = transformZ(t);
			char tr_type = transformType(t);
			if(tr_type == 'r'){
				float angle = transformAngle(t);
				glRotatef(angle, x, y, z);
            } else if(tr_type == 't'){
				glTranslatef(x, y, z);
            } else if(tr_type == 's'){
				glScalef(x, y, z);
            } 
		}

		// Desenho das figuras
		glBegin(GL_TRIANGLES);
		drawFiguras(models);
		glEnd();

		// Procede para fazer o mesmo aos nodos filho. 
        List filhos = getChildren(groups);
        for(unsigned long i = 0; i < getListLength(filhos); i++){
            Tree next = (Tree)getListElemAt(filhos, i);
            drawGroups(next);
        }
		glPopMatrix(); // retorna ao respetivo estado anterior dos eixos.
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(radius*cos(beta_)*sin(alpha), radius*sin(beta_), radius*cos(beta_)*cos(alpha),
		      lookAtx,lookAty,lookAtz,
			  upx,upy,upz);

	// put drawing instructions here
	// Desenha os eixos, caso a flag esteja ativa.
	drawEixos();

	// put the geometric transformations here
	// ...
	//
	// figuras
	glColor3f(WHITE);
	glPolygonMode(GL_FRONT_AND_BACK, mode);

	// glBegin(GL_TRIANGLES);
	//drawFiguras(figuras);
	drawGroups(getTreeGroups(configuration));
    // glEnd();
	
	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events

// Só altera a posição da camera, para debug.
void specKeyProc(int key_code, int x, int y) {
	x = y; y=x; // Para não aparecerem os warnings.
	switch (key_code){
		case GLUT_KEY_UP:{
			radius -= 5.0f;
			break;
		}
		
		case GLUT_KEY_DOWN:{
			radius += 5.0f;
			break;
		}

		default:
			break;
	}
	glutPostRedisplay();
}

// Só altera a posição da camera, para debug, e altera os modes para GL_FILL, GL_LINES, GL_POINT
void keyProc(unsigned char key, int x, int y) {
	x = y; y=x; // Para não aparecerem os warnings.
	switch (key)
	{
		case 'a': { // left
			alpha -= 0.1f;
			break;
		}

		case 'd': { // right
			alpha += 0.1f;
			break;
		}

		case 'w': { // up 
			beta_ += beta_ <= 1.48f ? 0.1f : 0.0f;
			break;
		}

		case 's': { // down
			beta_ -= beta_ >= -1.48f ? 0.1f : 0.0f;
			break;
		}

		case('f'):
			mode = GL_FILL;
			break;

		case('l'):
			mode = GL_LINE;
			break;

		case('p'):
			mode = GL_POINT;
			break;
		
		case('x'):
			show_eixos = !show_eixos;
			break;

		default:
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {

	if (argc < 2){
		printf("Erro: Insira a diretoria para o ficheiro XML a ser analisado!\n");
		return 1;
	}
	FILE *file_ptr = fopen(argv[1], "r");
   	if (file_ptr == NULL) {
   	   printf("Erro: Diretoria não existente!\n");
   	   return 1;
   	}
   	fclose(file_ptr);

	// Carregamento da configuração
	configuration = xmlToConfig(argv[1]); 
	// drawTreeDEBUG(configuration);
	
	camx    = getXPosCam(configuration);
	camy    = getYPosCam(configuration);
	camz    = getZPosCam(configuration);
	radius  = sqrt(camx*camx + camy*camy + camz*camz);
	lookAtx = getXLookAt(configuration);
	lookAty = getYLookAt(configuration);
	lookAtz = getZLookAt(configuration);
	upx 	= getXUp(configuration);
	upy 	= getYUp(configuration);
	upz 	= getZUp(configuration);
	alpha = acos(camz/sqrt(camx*camx + camz*camz));
	beta_ = asin(camy/radius);
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	//glutInitWindowSize(800,800);
	glutInitWindowSize(getWindowWidth(configuration), getWindowHeight(configuration));
	glutCreateWindow("Fase 2");
		
	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
	// put here the registration of the keyboard callbacks (por enquanto só mexem na camara como forma de debug)
	glutKeyboardFunc(keyProc);
	glutSpecialFunc(specKeyProc);


	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	// enter GLUT's main cycle
	glutMainLoop();
	
	deleteConfig(configuration); 
	return 1;
}