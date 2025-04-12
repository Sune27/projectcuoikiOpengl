#include <bits/stdc++.h>
#include <GL/glut.h>

#include "Config.h"
#include "Utils.h"
#include "Console.h"
#include "RobotArm.h"
#include "UserInterface.h"
using namespace std;

RobotArm robotArm;
UI ui;

void display();
void reshape(int, int);
void keyboardFunc(unsigned char, int, int);
void specialKeys(int, int, int);


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

	ui.draw2DUI();
	
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
			exit(0);break;
		case 32:
			robotArm.changeStatus(HAND_OPEN);break;
		case '-':
			robotArm.changeStatus(SHOW_OBJECT_STATUS);break;
		case 'q':
			robotArm.rotateAngle(ANGLE_LEFT_SHORT_ARM, rotate);break;
		case 'a':
			robotArm.rotateAngle(ANGLE_LEFT_SHORT_ARM, -rotate);break;
		case '4':
			robotArm.rotateAngle(ANGLE_RIGHT_SHORT_ARM, rotate);break;
		case '1':
			robotArm.rotateAngle(ANGLE_RIGHT_SHORT_ARM, -rotate);break;
		case 'z':
			robotArm.rotateAngle(ANGLE_X, rotate);break;
		case 'x':
			robotArm.rotateAngle(ANGLE_X, -rotate);break;
		case 'w':
			robotArm.rotateAngle(ANGLE_Z, rotate);break;
		case 's':
			robotArm.rotateAngle(ANGLE_Z, -rotate);break;
		case '=':
			robotArm.changeStatus(SHOW_DIRECTION);break;
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
