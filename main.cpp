#include <bits/stdc++.h>
#include <GL/glut.h>

#include "Config.h"
#include "Utils.h"
#include "Console.h"
#include "RobotArm.h"
using namespace std;

RobotArm robotArm;

void display();
void reshape(int, int);
void keyboardFunc(unsigned char, int, int);
void specialKeys(int, int, int);

GLdouble eyeX = 30.0, eyeY = -20.0, eyeZ = 30.0;
GLdouble centerX = 0.0, centerY = 0.0, centerZ = 0.0;
GLdouble upX = 0.0, upY = 0.0, upZ = 1.0;


int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutCreateWindow("Project");
	
	glEnable(GL_DEPTH_TEST);
	
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialKeys);
	glutReshapeFunc(reshape);
	
	glutMainLoop();
	
	return 0;
}

void display() 
{
	setCursorPosition(0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt
	(
		eyeX, eyeY, eyeZ,
		centerX, centerY, centerZ,
		upX, upY, upZ
	);
	robotArm.draw();
	
	glFlush();
	glutSwapBuffers(); 
}
  
void reshape(int w, int h) 
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0); 
  
}

void keyboardFunc(unsigned char key, int x, int y)
{
	float rotate = 1.0;
	switch(key)
	{
		case 27:
			exit(0);
			break;
		case 'z':
			robotArm.rotateAngle(ANGLE_X, rotate);
			break;
		case 'x':
			robotArm.rotateAngle(ANGLE_X, -rotate);
			break;
		case 'w':
			robotArm.rotateAngle(ANGLE_Z, rotate);
			break;
		case 's':
			robotArm.rotateAngle(ANGLE_Z, -rotate);
			break;
		case 't':
			robotArm.rotateAngle(ANGLE_SHORT_ARM, rotate);
			break;
		case 'g':
			robotArm.rotateAngle(ANGLE_SHORT_ARM, -rotate);
			break;
		case 'y':
			robotArm.rotateAngle(ANGLE_LONG_ARM, rotate);
			break;
		case 'h':
			robotArm.rotateAngle(ANGLE_LONG_ARM, -rotate);
			break;
		default:
			break;
	}
	robotArm.checkMinValueAngle();
	robotArm.checkMaxValueAngle();
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) 
{
	
}
