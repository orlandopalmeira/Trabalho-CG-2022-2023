#include <IL/il.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include "../utils/list.hpp"
#include "../utils/matrix.hpp"
#include "../tinyXML/tinyxml.h"
#include "config.hpp"
#include <math.h>
#include <iostream>
#include <filesystem>

using namespace std;

// Obtenção do tempo actual em segundos
#define NOW ((1.0f*glutGet(GLUT_ELAPSED_TIME))/1000.0f)

// Códigos de cores
#define RED 1.0f,0.0f,0.0f
#define GREEN 0.0f,1.0f,0.0f
#define BLUE 0.0f,0.0f,1.0f
#define YELLOW 1.0f,1.0f,0.0f
#define CYAN 0.0f,1.0f,1.0f
#define WHITE 1.0f,1.0f,1.0f

// Modos da câmara
#define SPHERICAL true
#define FREE false

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
bool cameraMode;

// Variáveis de visualização
int mode = GL_FILL;
int show_eixos = 0;

// Configuração do engine
Config configuration = NULL;

// VBO's
// modelos
GLuint *buffers = NULL; // temos um buffer para cada figura
vector<unsigned int> buffersSizes; // aqui guardamos o tamanho de cada buffer de cada figura
unsigned int figCount = 0; // total de figuras existentes no ficheiro de configuração.
// Normais
GLuint *buffersN = NULL; // temos um buffer para o conjunto de normais de cada figura
vector<unsigned int> buffersNSizes; // aqui guardamos o tamanho de cada buffer de cada normal
// Texturas
GLuint *buffersTC = NULL;
GLuint *textures = NULL;

// Congelamento da animação
bool freeze = false;
int timeOld, timeNew;
float totalTime = 0.0f;

// FIM dos VBO's

// Controlo de tempo
float init_time = 0.0f;
int timebase;

// Título na janela do engine
unsigned int frame = 0;
char title[128];

// Visualização das curvas de Catmull-Rom
bool showCurves = false;

// Visualização das normais
bool showNormais = false;

void loadTexture(const char* texturePath, int* index) {
	FILE *file_ptr = fopen(texturePath, "r");
   	if (file_ptr == NULL) {
   	   printf("Não foi possível abrir a textura com a diretoria '%s'!\n", texturePath);
	   exit(1);
   	}
   	fclose(file_ptr);
	unsigned int t, tw, th;
	unsigned char *texData;
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)texturePath); 
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, textures + *index);
	
	glBindTexture(GL_TEXTURE_2D, *(textures + *index));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D); 
}

// Carrega os dados das figuras para os buffers.
void loadBuffersData(Tree groups, int* index){ 
	if(groups){
		Group group = (Group)getRootValue(groups);
		List models = getGroupModels(group);

		for(unsigned long i = 0; i < getListLength(models); i++, (*index)++){
			Figura fig = (Figura)getListElemAt(models,i);
			vector<float> toBuffer = figuraToVector(fig);
			vector<float> toNormals = figuraToNormals(fig);
			vector<float> toTextCoors = figuraToTextCoords(fig);
			const char* textFile = getTextureFile(fig);
			// Vértices/pontos
			glBindBuffer(GL_ARRAY_BUFFER, buffers[*index]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*toBuffer.size(), toBuffer.data(), GL_STATIC_DRAW);
			buffersSizes.push_back(toBuffer.size()/3); 
			// Normais
			glBindBuffer(GL_ARRAY_BUFFER, buffersN[*index]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*toNormals.size(), toNormals.data(), GL_STATIC_DRAW);
			buffersNSizes.push_back(toNormals.size()/3); 
			// Texturas
			if(textFile){//* foi fornecido um ficheiro de textura?
				glBindBuffer(GL_ARRAY_BUFFER, buffersTC[*index]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float)*toTextCoors.size(), toTextCoors.data(), GL_STATIC_DRAW);
				loadTexture(textFile,index);
			}
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
	if(howManyLights(configuration) > 0) glDisable(GL_LIGHTING);
	if (show_eixos){
		glBegin(GL_LINES);
		// X axis in red
		glColor3f(RED);
		// glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(GREEN);
		// glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(BLUE);
		// glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
		glEnd();
	}
	if(howManyLights(configuration) > 0) glEnable(GL_LIGHTING);
}

// Desenha a curva de catmull rom
void drawCatmullRomCurve(vector<vector<float>> controlPoints){
	if(howManyLights(configuration) > 0) glDisable(GL_LIGHTING);
	float pos[3];
	glBegin(GL_LINE_LOOP);
	float t = 0.0f;
	for (int i = 0; i <= 100; i++, t+= 0.01f) {
		getGlobalCatmullRomPoint(t,controlPoints,pos,NULL);
		glVertex3f(pos[0], pos[1], pos[2]);
	}
	glEnd();
	if(howManyLights(configuration) > 0) glEnable(GL_LIGHTING);
}

void passTime(){
	timeOld = timeNew;
	timeNew = glutGet(GLUT_ELAPSED_TIME);
	if(!freeze){
		totalTime += 1.0f*(timeNew - timeOld)/1000.0f;
	}
}

// Executa as trasnformações geométricas de uma certa figura
void executeTransformations(List transforms){
	if(transforms){
		for(unsigned long i = 0; i < getListLength(transforms); i++){
			Transform t = (Transform)getListElemAt(transforms,i);
			float x = transformX(t);
			float y = transformY(t);
			float z = transformZ(t);
			char tr_type = transformType(t);
			if(tr_type == 'r'){ // Rotação
				float r_angle = transformAngle(t);
				float r_time  = transformTime(t);
				if(r_time > 0.0f){ 
					r_angle = ((totalTime-init_time)*360.0f)/r_time; 
				}
				glRotatef(r_angle, x, y, z);
            } else if(tr_type == 't'){ // Translação
				float t_time = transformTime(t);
				if(t_time > 0.0f){ // se o tempo for utilizado na translação, sabemos que é uma translação referente a uma curva de Catmull-Rom
					float pos[3], deriv[3], y[3], z[3], rot[16];
					vector<vector<float>> points = translatePoints(t);
					getGlobalCatmullRomPoint(totalTime/t_time,points,pos,deriv);
					if (showCurves) drawCatmullRomCurve(points);
					glTranslatef(pos[0],pos[1],pos[2]);

					if(transformAlign(t)){
						normalize(deriv);
						cross(deriv,transformYAxis(t).data(),z); // Xi = deriv
						normalize(z);
						cross(z,deriv,y);// Xi = deriv
						setTransformYAxis(t,y);
						normalize(y);
						buildRotMatrix(deriv,y,z,rot);
						glMultMatrixf(rot); 
					}
					
				}else{
					glTranslatef(x,y,z);
				}
            } else if(tr_type == 's'){ // Escala
				glScalef(x, y, z);
            } 
		}
	}
}

void drawNormals(Figura model){
	if(howManyLights(configuration) > 0) glDisable(GL_LIGHTING);
	glColor3f(WHITE);
	vector<float> normals = figuraToNormals(model);
	vector<float> vertexs = figuraToVector(model);
	glBegin(GL_LINES);
	for(int i = 0; i < normals.size(); i+=3){
		glVertex3f(vertexs[i+0],vertexs[i+1],vertexs[i+2]);
		glVertex3f(vertexs[i+0]+normals[i+0],vertexs[i+1]+normals[i+1],vertexs[i+2]+normals[i+2]);
	}
	glEnd();
	if(howManyLights(configuration) > 0) glEnable(GL_LIGHTING);
}

// Desenha todos os groups do XML
void drawGroups(Tree groups, int* index){
	if(groups){
		glPushMatrix(); // guarda o estado dos eixos

		Group group = (Group)getRootValue(groups);
		List transforms = getGroupTransforms(group);
		List models = getGroupModels(group);
		unsigned long modelsCount = getListLength(models);
		executeTransformations(transforms);

		// Desenha o conteúdo dos buffers
		for(unsigned long i = 0; i < modelsCount; i++, (*index)++){
			Figura model = (Figura)getListElemAt(models,i);
			if(showNormais) drawNormals(model);
			// Definição da cor do modelo/figura
			glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffuse(model).data());
			glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbient(model).data());
			glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecular(model).data());
			glMaterialfv(GL_FRONT, GL_EMISSION, getEmissive(model).data());
			glMaterialf(GL_FRONT, GL_SHININESS, getShininess(model));

			// Texturas
			if(getTextureFile(model)){ //* foi fornecido um ficheiro de textura?
				glBindTexture(GL_TEXTURE_2D, textures[*index]);
				glBindBuffer(GL_ARRAY_BUFFER, buffersTC[*index]);
				glTexCoordPointer(2, GL_FLOAT, 0, 0);
			}
			// Normais
			glBindBuffer(GL_ARRAY_BUFFER,buffersN[*index]);
			glNormalPointer(GL_FLOAT,0,0);
			// Vértices/pontos
			glBindBuffer(GL_ARRAY_BUFFER, buffers[*index]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			glDrawArrays(GL_TRIANGLES, 0, buffersSizes[*index]);
			// Fazer unbind da textura
			if(getTextureFile(model)){ //* só fazemos unbind se existir uma textura
				glBindTexture(GL_TEXTURE_2D, 0);
			}

		}

		// Procede para fazer o mesmo nos nodos filhos. 
        List filhos = getChildren(groups);
        for(unsigned long i = 0; i < getListLength(filhos); i++){
            Tree next = (Tree)getListElemAt(filhos, i);
            drawGroups(next,index);
        }
		glPopMatrix(); // retorna ao respetivo estado anterior dos eixos.
	}
}

// Devolve a constante GL_LIGHT(i) dado o seu índice
int gl_light(int i){
	switch(i){
		case 0: return GL_LIGHT0;
		case 1: return GL_LIGHT1;
		case 2: return GL_LIGHT2;
		case 3: return GL_LIGHT3;
		case 4: return GL_LIGHT4;
		case 5: return GL_LIGHT5;
		case 6: return GL_LIGHT6;
		case 7: return GL_LIGHT7;
	}
	return -1;
}

void executeLights(){
	vector<Light> lights = getLights(configuration);
	for(int i = 0; i < lights.size(); i++){
		Light luz = lights[i];
		vector<float> lPos = getLightPos(luz); 
		vector<float> lDir = getLightDir(luz); normalize(lDir.data());
		float cutoff = getLightCutoff(luz);

		switch(getLightType(luz)){
			case 'p':{
				glLightfv(gl_light(i), GL_POSITION, lPos.data());
				break;
			}

			case 'd':{
				glLightfv(gl_light(i), GL_POSITION, lDir.data());
				break;
			}

			case 's':{
				glLightfv(gl_light(i), GL_POSITION, lPos.data());
				glLightfv(gl_light(i), GL_SPOT_DIRECTION, lDir.data());
				glLightf(gl_light(i), GL_SPOT_CUTOFF, cutoff);
				glLightf(gl_light(i), GL_SPOT_EXPONENT, 0.0); 
				break;
			}
		}
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
	gluPerspective(getFov(configuration), ratio, getNear(configuration), getFar(configuration));

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

// Deslocação da câmara no modo SPHERICAL
void sphericalCamera(){
	camx = radius*cos(beta_)*sin(alpha);
	camy = radius*sin(beta_);
	camz = radius*cos(beta_)*cos(alpha);
}

// Deslocações da câmara em modo FREE
void walkLeft(){
	float v_up[3] = {upx,upy,upz}, v_r[3], v_d[3] = {lookAtx-camx,lookAty-camy,lookAtz-camz};
	cross(v_d,v_up,v_r); normalize(v_r); // r = d * up
	normalize(v_d);
	float k = -1.0f; // velocidade de deslocação
	camx += k*v_r[0]; camy += k*v_r[1]; camz += k*v_r[2];
	lookAtx = camx + v_d[0]; lookAty = camy + v_d[1]; lookAtz = camz + v_d[2]; 
}

void walkRight(){
	float v_up[3] = {upx,upy,upz}, v_r[3], v_d[3] = {lookAtx-camx,lookAty-camy,lookAtz-camz};
	cross(v_d,v_up,v_r); normalize(v_r); // r = d * up
	normalize(v_d);
	float k = 1.0f; // velocidade de deslocação
	camx += k*v_r[0]; camy += k*v_r[1]; camz += k*v_r[2];
	lookAtx = camx + v_d[0]; lookAty = camy + v_d[1]; lookAtz = camz + v_d[2];
}

void walkForward(){
	float v_d[3] = {lookAtx-camx,lookAty-camy,lookAtz-camz};
	normalize(v_d);
	float k = 1.0f;
	camx += k*v_d[0]; camy += k*v_d[1]; camz += k*v_d[2];
	lookAtx = camx + v_d[0]; lookAty = camy + v_d[1]; lookAtz = camz + v_d[2];
}

void walkBackwards(){
	float v_d[3] = {lookAtx-camx,lookAty-camy,lookAtz-camz};
	normalize(v_d);
	float k = -1.0f;
	camx += k*v_d[0]; camy += k*v_d[1]; camz += k*v_d[2];
	lookAtx = camx + v_d[0]; lookAty = camy + v_d[1]; lookAtz = camz + v_d[2];
}

void moveHead(){
	lookAtx = camx + radius * cos(beta_) * sin(alpha);
    lookAty = camy + radius * sin(beta_);
    lookAtz = camz + radius * cos(beta_) * cos(alpha);
}
// Fim das deslocações da câmara em modo FREE

void renderScene(void) {
	passTime();
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity(); // super pop, faz refresh a tudo.
	if (cameraMode == SPHERICAL)
		sphericalCamera();
	gluLookAt(camx,camy,camz, lookAtx,lookAty,lookAtz, upx,upy,upz);
	// Desenha os eixos, caso a flag esteja ativa.
	drawEixos();
	// figuras
	glColor3f(WHITE);
	executeLights(); 
	glPolygonMode(GL_FRONT_AND_BACK, mode);
	int index = 0; // serve para seleccionar o buffer que vai ser lido
	drawGroups(getTreeGroups(configuration),&index);
	// FPS Count
	frame++;
	int time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		float fps = frame*1000.0f/(time-timebase);
		snprintf(title,127,"FPS: %.2f, PCAM: (%.2f,%.2f,%.2f), CamMode: %s",fps,camx,camy,camz,cameraMode ? "SPH" : "FREE");
		glutSetWindowTitle(title);
		timebase = time;
		frame = 0;
	} 
	// End of frame
	glutSwapBuffers();
}

// Só altera a posição da camera, para debug.
void specKeyProc(int key_code, int x, int y) {
	x = y; y=x; // Para não aparecerem os warnings.
	switch (key_code){
		case GLUT_KEY_F1:{
			freeze = !freeze;
			break;
		}

		case GLUT_KEY_UP:{
			if(cameraMode == SPHERICAL){
				radius -= 1.0f;
			}else{
				beta_ +=  0.1f;
				moveHead();
			}
			break;
		}
		
		case GLUT_KEY_DOWN:{
			if(cameraMode == SPHERICAL){
				radius += 1.0f;
			}else{
				beta_ -= 0.1f;
				moveHead();
			}
			break;
		}

		case GLUT_KEY_LEFT:{
			if(cameraMode == FREE){
				alpha += 0.1f;
				moveHead();
			}
			break;
		}

		case GLUT_KEY_RIGHT:{
			if(cameraMode == FREE){
				alpha -= 0.1f;
				moveHead();
			}
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
	switch (key){

		case 'n':{
			showNormais = !showNormais;
			break;
		}

		case 'a': { // left
			if(cameraMode == SPHERICAL){
				alpha -= 0.1f;
			}else{
				walkLeft();
			}
			break;
		}

		case 'd': { // right
			if(cameraMode == SPHERICAL){
				alpha += 0.1f;
			} else {
				walkRight();
			}
			break;
		}

		case 'w': { // up 
			if(cameraMode == SPHERICAL){
				beta_ += beta_ <= 1.48f ? 0.1f : 0.0f;
			} else {
				walkForward();
			}
			break;
		}

		case 's': { // down
			if(cameraMode == SPHERICAL){
				beta_ -= beta_ >= -1.48f ? 0.1f : 0.0f;
			}else{
				walkBackwards();
			}
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

		case 'c':
			showCurves = !showCurves;
			break;

		case 'v':{
			if (cameraMode == FREE){
				radius  = sqrt(camx*camx + camy*camy + camz*camz);
				lookAtx = lookAty = lookAtz = 0.0f;
				beta_ = asin(camy/radius);
				alpha = atan(camx/camz);
				sphericalCamera();
				cameraMode = SPHERICAL;
			} else { // cameraMode == SPHERICAL
				float v_d[3] = {lookAtx-camx,lookAty-camy,lookAtz-camz}; normalize(v_d);
				float aux[3] = {-camx, 0.0f, -camz};
				alpha = M_PI+alpha;
				beta_ = -beta_;// para evitar que o lookAt vá para um sítio completamente inesperado.
				lookAtx = camx + cos(beta_) * sin(alpha);
				lookAty = camy + sin(beta_);
				lookAtz = camz + cos(beta_) * cos(alpha);
				cameraMode = FREE;
			}
			break;
		}

		case '+':{
			if(cameraMode == FREE){
				camy += 1.0f;
				lookAty += 1.0f;
			}
			break;
		}

		case '-':{
			if(cameraMode == FREE){
				camy -= 1.0f;
				lookAty -= 1.0f;
			}
			break;
		}
		default:
			break;
	}
	glutPostRedisplay();
}

void init(){
	glewInit();
	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	// Iluminação
	if(howManyLights(configuration) > 0){ //* definiu-se luz(es)?
		glEnable(GL_LIGHTING); 
		glEnable(GL_RESCALE_NORMAL);
		if(howManyLights(configuration) > 8){
			printf("Número de luzes definidas superior a 8\n");
			exit(1);
		}
        GLfloat white[4] = {1.0,1.0,1.0,1.0};
		for(int i = 0; i < howManyLights(configuration); i++){
			glEnable(gl_light(i));
            glLightfv(gl_light(i), GL_DIFFUSE, white);
            glLightfv(gl_light(i), GL_SPECULAR, white);
		}
		
		float amb[4] = { 1.0f, 1.0f, 1.0f, 0.4f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
    	
	}
	// Fim iluminação

	// OpenGL settings
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// glEnable(GL_VERTEX_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPolygonMode(GL_FRONT, GL_LINE);
	// Cria os buffers
	glGenBuffers(figCount, buffers); 
	glGenBuffers(figCount, buffersN);
	glGenBuffers(figCount, buffersTC);
	// Carrega os dados para os buffers
	int index = 0; // serve para seleccionar o buffer que vai ser escrito
	loadBuffersData(getTreeGroups(configuration),&index);
	// Cálculo do tempo
	timebase = glutGet(GLUT_ELAPSED_TIME);
	init_time = NOW;
	timeOld = timeNew = 0;
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
	alpha = (camx == 0 && camz == 0) ? 0.0f : (camx < 0 ? -1.0f : 1.0f)*acos(camz/sqrt(camx*camx + camz*camz));
	beta_ = asin(camy/radius);
	cameraMode = SPHERICAL;
	figCount = figureCount(configuration); // número de figuras existentes na configuração
	buffers = (GLuint*)calloc(figCount, sizeof(GLuint)); // teremos um buffer para cada figura
	buffersN = (GLuint*)calloc(figCount, sizeof(GLuint)); // teremos um buffer para cada normal
	buffersTC = (GLuint*)calloc(figCount, sizeof(GLuint));
	textures = (GLuint*)calloc(figCount, sizeof(GLuint));
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(1200,300);
	//glutInitWindowSize(800,800);
	glutInitWindowSize(getWindowWidth(configuration), getWindowHeight(configuration));
	glutCreateWindow("Fase 4");
		
	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	
	// put here the registration of the keyboard callbacks (por enquanto só mexem na camara como forma de debug)
	glutKeyboardFunc(keyProc);
	glutSpecialFunc(specKeyProc);


	init();
	// enter GLUT's main cycle
	glutMainLoop();
	
	deleteConfig(configuration); 
	return 0;
}