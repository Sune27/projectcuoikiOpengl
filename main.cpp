#include <bits/stdc++.h>
#include <GL/glut.h>
//#include <GL/glfw3.h>
#include "Config.h"
#include "Utils.h"
#include "Console.h"
#include "RobotArm.h"
#include "UserInterface.h"
using namespace std;

RobotArm robotArm;
UIManager uiManager;
vector<bool> keys(256, false);

void display();
void reshape(int, int);
void keyboardFunc(unsigned char, int, int);
void specialKeys(int, int, int);
void keyboardUpFunc(unsigned char, int, int);
void mouseFunc(int, int, int, int);
void passiveMouseMotion(int, int);

void checkEventKeyboard();

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutCreateWindow("Project");
	hideCursor();
	
	glEnable(GL_DEPTH_TEST);
	
	//event
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutSpecialFunc(specialKeys);
	glutMouseFunc(mouseFunc);
	glutPassiveMotionFunc(passiveMouseMotion);
	//glutMotionFunc();
	//glutIdleFunc();
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
	uiManager.draw2DUI();
	checkEventKeyboard();

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
	
	if(key == 32) 
		robotArm.changeStatus(HAND_OPEN);
	else if(key == '=')
		robotArm.changeStatus(SHOW_DIRECTION);
	else if(key == '+')
	{
		if(robotArm.checkHandClaw())
		robotArm.changeStatus(LEFT_HAND_CLAWING);
	}
	else keys[key] = true;
}
void keyboardUpFunc(unsigned char key, int x, int y)
{
	keys[key] = false;
}
void mouseFunc(int button, int state, int x, int y) 
{
    if (button == GLUT_LEFT_BUTTON) 
	{
        if (state == GLUT_DOWN) 
		{
			uiManager.mouseLeftClicked(x, y);
        } else if (state == GLUT_UP) 
		{
                cout << "Mouse Clicked in " << x << " " << y << endl;
        }
        glutPostRedisplay(); // Vẽ lại
    }
}

void passiveMouseMotion(int x, int y) 
{
	uiManager.passiveMouseMotion(x, y);
}

void checkEventKeyboard()
{
	float rotate = 1.0;
	if(keys[27])
		exit(0);
	if(keys['6']) 
		robotArm.rotateAngle(ANGLEZ_RIGHT_LONG_ARM, rotate);
	if(keys['3'])
		robotArm.rotateAngle(ANGLEZ_RIGHT_LONG_ARM, -rotate);
	if(keys['e'])
		robotArm.rotateAngle(ANGLEZ_LEFT_LONG_ARM, rotate);
	if(keys['d'])
		robotArm.rotateAngle(ANGLEZ_LEFT_LONG_ARM, -rotate);
	if(keys['5'])
		robotArm.rotateAngle(ANGLEX_RIGHT_LONG_ARM, rotate);
	if(keys['2'])
		robotArm.rotateAngle(ANGLEX_RIGHT_LONG_ARM, -rotate);
	if(keys['w'])
		robotArm.rotateAngle(ANGLEX_LEFT_LONG_ARM, rotate);
	if(keys['s'])
		robotArm.rotateAngle(ANGLEX_LEFT_LONG_ARM, -rotate);
	if(keys['-'])
		robotArm.changeStatus(SHOW_OBJECT_STATUS);
	if(keys['q'])
		robotArm.rotateAngle(ANGLE_LEFT_SHORT_ARM, rotate);
	if(keys['a'])
		robotArm.rotateAngle(ANGLE_LEFT_SHORT_ARM, -rotate);
	if(keys['4'])
		robotArm.rotateAngle(ANGLE_RIGHT_SHORT_ARM, rotate);
	if(keys['1'])
		robotArm.rotateAngle(ANGLE_RIGHT_SHORT_ARM, -rotate);
	if(keys['z'])
		robotArm.rotateAngle(ANGLE_X, rotate);
	if(keys['x'])
		robotArm.rotateAngle(ANGLE_X, -rotate);

	robotArm.checkMinValueAngle();
	robotArm.checkMaxValueAngle();
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) 
{
	switch (key)
	{
	case GLUT_KEY_F1:
		if(robotArm.checkHandClaw())
		robotArm.changeStatus(RIGHT_HAND_CLAWING);
		break;

	
	default:
		break;
	}
}
