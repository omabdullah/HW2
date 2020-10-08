#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0, 1, 4, 1}; // TODO: Your code here! setup a proper camera position. It should be 4 dimentions homogeneous coordinate, first three elements represent position and 4th element should be 1.
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples. press SPACE to cycle between problems

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
	for (int i = 0; i < 360; i = i + 36) { // 360 / 10, each pot is placed 36 degrees apart from each other
		glPushMatrix();
		glRotatef(i, 0, 0, 1);  // Takes the angle from i to rotate
		glTranslatef(1, 0, 0); // Distances the teapots from the center
		glutSolidTeapot(0.25); // Sets size of teapot to 0.25
		glPopMatrix();
	}
}

void problem2() {
	float spacing = 0.0; // Initial distance between each pot for equal distance (changes after a new row is created to create a pyramid
	float height = 1.0; // Initial height for top layer (changes as a new row is created to be placed under the previous row properly)
	for (int row = 0; row < 6; row++) { // creates 6 rows
		for (int teapot = 0; teapot <= row; teapot++) { // creates same amount of pots as row, first row = 1 pot, second two = 2 pots, etc
			glPushMatrix();
			glTranslatef(teapot + spacing, height, 0); // sets proper x and y coordinates
			glutSolidTeapot(0.25); // size of teapot 2.5
			glPopMatrix();
		}
		spacing = spacing - 1.0 / 2.0; // formula to change pot position on x axis to create a pyramid
		height = height - 0.5; // formula to change height of new row to properly position pot row under each other
	}
}

void problem3() {

	//sun
		glPushMatrix();
	glTranslatef(1.75, 1.25, -.75);
	for (int i = 0; i < 360; i = i + 36) { // 360 / 10, each pot is placed 36 degrees apart from each other
		glPushMatrix();
		glRotatef(i, 0, 0, 1);  // Takes the angle from i to rotate
		glutSolidTeapot(0.25); // Sets size of teapot to 0.25
		glPopMatrix();
	}
	glPopMatrix();

	//building
	glPushMatrix();
	glutSolidCube(1.5);

	//roof
	glTranslatef(0, .75, 0);
	glPushMatrix();                   
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(.8, 1, 14, 8);
	glPopMatrix();

	// chimney
	glTranslatef(.45, .5, 0);
	glPushMatrix();                  
	glScalef(1, 3, 1);
	glutSolidCube(.20);
	glPopMatrix();
	glPopMatrix();

	// door
	glTranslatef(0, -.45, .61);  
	glPushMatrix();                   
	glScalef(2, 3, 2);
	glutSolidCube(.20);
	glPopMatrix();
	glPopMatrix();

	// window 1
	glTranslatef(-.35, 0.75, 0);
	glPushMatrix();
	glScalef(2, 2, 2);
	glutSolidCube(.20);
	glPopMatrix();
	glPopMatrix();
	// window 2
	glTranslatef(.70, 0, 0);
	glPushMatrix();
	glScalef(2, 2, 2);
	glutSolidCube(.20);
	glPopMatrix();
	glPopMatrix();


}

void display() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x axis
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y axis
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// TODO: Your code here! Use glViewport() and gluPerspective() to setup projection matrix.
	glViewport(0, 0, windowWidth, windowHeight);
	gluPerspective(50, 1.333, 1, 1000); // 1.333 from 640 / 480


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// TODO: Your code here! Use gluLookAt() to setup model-view matrix.
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);


	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot, 0, 1, 0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0]) * .1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 32) { // When pressing space, it will rotate between each model
		if (curProblem != 3) { // will rotate until it hits the third model
			curProblem++;
		}
		else {
			curProblem = 1; // will reset the model to the first since there are only 3 models
		}
	}
	
	if (key == 'q' || key == 'Q' || key == 27) { // when q, Q, or escape is pressed, program will exit
		exit(0);
	}
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}