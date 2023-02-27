#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"

using namespace std;

// Códigos de cores
#define RED 1.0f,0.0f,0.0f
#define GREEN 0.0f,1.0f,0.0f
#define BLUE 0.0f,0.0f,1.0f
#define YELLOW 1.0f, 1.0f, 0.0f
#define CYAN 0.0f, 1.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f

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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

Figura f = NULL; 

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(3.0f,5.0f,3.0f,
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	// put drawing instructions here
	// linhas dos eixos
	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f,-100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f,-100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	// put the geometric transformations here
	// ...
	//

	vector<Ponto> points = getPontos(f);
	// figura
	//(TODO talvez colocar modo de debugs aqui para ver as linhas e os pontos.)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
	for(unsigned long i = 0; i < points.size(); i++){
		Ponto p = points.at(i);
		glVertex3f(getX(p), getY(p), getZ(p));
	}
    glEnd();
	
	// End of frame
	glutSwapBuffers();
}


int main(int argc, char *argv[]) {
	f = fileToFigura("../Fase 1/outputs/plane.3d");
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Fase 1");
		
	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	//glutPostRedisplay();

	
	// put here the registration of the keyboard callbacks
	//glutKeyboardFunc(keyProc);
	//glutSpecialFunc(specKeyProc);


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}