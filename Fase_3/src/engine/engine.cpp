#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
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

// Variáveis de visualização
int mode = GL_LINE;
int show_eixos = 0;

// Configuração do engine
Config configuration = NULL;

// VBO's
GLuint *buffers = NULL; // temos um buffer para cada figura
vector<unsigned int> buffersSizes; // aqui guardamos o tamanho de cada buffer de cada figura
unsigned int figCount = 0; // total de figuras existentes no ficheiro de configuração.

// Carrega os dados das figuras para os buffers.
void loadBuffersData(Tree groups, int* index){ //* o index é um endereço de um inteiro que serve para seleccionar os buffers em que vamos escrever
	if(groups){
		Group group = (Group)getRootValue(groups);
		List models = getGroupModels(group);

		for(unsigned long i = 0; i < getListLength(models); i++){
			Figura fig = (Figura)getListElemAt(models,i);
			vector<float> toBuffer = figuraToVector(fig);
			glBindBuffer(GL_ARRAY_BUFFER, buffers[(*index)++]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*toBuffer.size(), toBuffer.data(), GL_STATIC_DRAW);
			buffersSizes.push_back(toBuffer.size()/3); // dividimos por 3 porque cada ponto tem 3 coordenadas
		}

		List filhos = getChildren(groups);
        for(unsigned long i = 0; i < getListLength(filhos); i++){
            Tree next = (Tree)getListElemAt(filhos, i);
			loadBuffersData(next,index);
        }
	}
}

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

void drawGroups(Tree groups, int* index){
	if(groups){
		glPushMatrix(); // guarda o estado dos eixos

		Group group = (Group)getRootValue(groups);
		List transforms = getGroupTransforms(group);
		unsigned long modelsCount = getListLength(getGroupModels(group));

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

		for(unsigned long i = 0; i < modelsCount; i++, (*index)++){
			glBindBuffer(GL_ARRAY_BUFFER, buffers[*index]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			glDrawArrays(GL_TRIANGLES, 0, buffersSizes[*index]);
		}

		// Procede para fazer o mesmo nos nodos filho. 
        List filhos = getChildren(groups);
        for(unsigned long i = 0; i < getListLength(filhos); i++){
            Tree next = (Tree)getListElemAt(filhos, i);
            drawGroups(next,index);
        }
		glPopMatrix(); // retorna ao respetivo estado anterior dos eixos.
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

	// figuras
	glColor3f(WHITE);
	glPolygonMode(GL_FRONT_AND_BACK, mode);

	int index = 0; // serve para seleccionar o buffer que vai ser lido
	drawGroups(getTreeGroups(configuration),&index);
	
	// End of frame
	glutSwapBuffers();
}


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
	figCount = figureCount(configuration); // número de figuras existentes na configuração
	buffers = (GLuint*)calloc(figCount, sizeof(GLuint)); // teremos um buffer para cada figura
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	//glutInitWindowSize(800,800);
	glutInitWindowSize(getWindowWidth(configuration), getWindowHeight(configuration));
	glutCreateWindow("Fase 3");
		
	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
	// put here the registration of the keyboard callbacks (por enquanto só mexem na camara como forma de debug)
	glutKeyboardFunc(keyProc);
	glutSpecialFunc(specKeyProc);


	glewInit();
	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_VERTEX_ARRAY);
	glPolygonMode(GL_FRONT, GL_LINE);
	// Cria os buffers
	glGenBuffers(figCount, buffers);
	// Carrega os dados para os buffers
	int index = 0; // serve para seleccionar o buffer que vai ser escrito
	loadBuffersData(getTreeGroups(configuration),&index);
	// enter GLUT's main cycle
	glutMainLoop();
	
	deleteConfig(configuration); 
	return 0;
}