#include <GL/glut.h>
using namespace std;


#ifndef CONFIG_H
#define CONFIG_H

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;
const int WINDOW_POSITION_X = 150;
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

const double PI = 3.14193;
const int NUM_SEGMENTS = 30;

enum TypeAngle
{
    ANGLE_X,
    ANGLE_Z,
    ANGLE_SHORT_ARM,
    ANGLE_LONG_ARM,

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
};

#endif
