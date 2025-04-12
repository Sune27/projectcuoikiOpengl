#include <GL/glut.h>
using namespace std;


#ifndef CONFIG_H
#define CONFIG_H

const GLdouble eyeX = 30.0, eyeY = -20.0, eyeZ = 30.0;
const GLdouble centerX = 0.0, centerY = 0.0, centerZ = 0.0;
const GLdouble upX = 0.0, upY = 0.0, upZ = 1.0;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;
const int WINDOW_POSITION_X = 450;
const int WINDOW_POSITION_Y = 50;
const int FPS = 60;

const float LINE_WIDTH = 5.0;
const float THICKNESS = 0.2;
const float INITIAL_ANGLE = 45.0;
const float DIRECTION_LENGTH = 20.0;
const float ANGLEZ_MIN = 55;
const float ANGLEZ_MAX = 85;
const float ANGLESHORTARM_MIN = 35.0;
const float ANGLESHORTARM_MAX = 100.0;
const float ANGLELONGARM_MAX = 25.0;
const float ANGLELONGARM_MIN = -60.0;

const double PI = 3.14193;
const int NUM_SEGMENTS = 30;

enum TypeStatus
{
    SHOW_DIRECTION,
    HAND_OPEN,
    SHOW_OBJECT_STATUS,

    TOTAL_STATUS
};

enum TypeAngle
{
    ANGLE_X,
    ANGLE_Z,
    ANGLE_LEFT_SHORT_ARM,
    ANGLE_RIGHT_SHORT_ARM,
    ANGLEX_LEFT_LONG_ARM,
    ANGLEX_RIGHT_LONG_ARM,
    ANGLEZ_LEFT_LONG_ARM,
    ANGLEZ_RIGHT_LONG_ARM,

    TOTAL_ANGLE
};

enum TypeVector
{
    NORMALBASE,
    ROBOTDIRECTIONXY_VERTICAL,
    ROBOTDIRECTIONXY_HORIZONTAL,
    ROBOTDIRECTIONXYZ,
    SHORTARM,
    LONGARM,

    TOTAL_VECTOR
};

enum Color
{
    GOLD2,
    GOLD1,
    GOLD3,
	DARK_GRAY,
	GRAY,
	LIGHT_GRAY,
	SILVER,
	DIM_BLACK,
	ALUMINUM,
	OFF_WHILE,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE,
    BLACK,
    GRAY_MATERIAL,
    GRAY_LIGHT,
    PINK, 
    LIGHT_GREEN,
    PURPLE,
    DARK_GREEN,
    LIGHT_BLUE,
    DARK_BLUE,
    ORANGE,
};


#endif
