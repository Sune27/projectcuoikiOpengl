#include <GL/glut.h>
#include <iostream>

#include "Utils.h"

#ifndef ROBOTARM_H
#define ROBOTARM_H

class RobotArm
{
public:
    RobotArm();
    ~RobotArm();
    void draw();
    void drawRobotBase();
    void drawRobotStand();
    void drawRobotShortArm();
    void drawRobotLongArm();
    void drawDirection();
    void printAttributes();
    void checkMinValueAngle();
    void checkMaxValueAngle();
    void update();
    void test();

    void rotateAngle(TypeAngle angle, float rotate);

    Vector getVector(TypeVector v);
    float getAngle(TypeAngle a);

private:
    //base
    float baseLeg_Radius = 4;
    float baseLeg_Height = 0.2;
    float baseBody_Radius = 2;
    float baseBody_Height = 0.75;
    float baseHead_Radius = 1.4;
    float baseHead_Height = 0.45;
    float axisRadius = 0.3;
    float axisHeight = 2;
    //stand
    float standPositionZ = 1.8;
    float standAxisDistance = 1.1;
    float standDistance = 0.75;
    float standWidth = 0.8;
    float standLength = 0.15;
    float standHeight = 3;
    float angleX = 60.0;
    float angleZ = 55.0;
    //short arm
    float angleShortArm = 100.0;
    float shortArmDistance = 0.5;
    float shortArmWidth = 0.8;
    float shortArmLength = 0.15;
    float shortArmHeight = 4;
    float axisShortArmRadius = 0.3;
    float axisShortArmHeight = 2;
    //longArm
    float angleLongArm = -10.0;
    
    Color baseLeg_Color = GRAY_LIGHT;
    Color baseBody_Color = GRAY_LIGHT;
    Color baseHead_Color = GRAY_LIGHT;
    Color baseLeg_OutlineColor = GREEN;
    Color baseBody_OutlineColor = GREEN;
    Color baseHead_OutlineColor = GREEN;

    Vector normalBase; // (0,0,1)
    Vector robotDirectionXY_Vertical;// lam goc cho tat ca vector khac;
    Vector robotDirectionXY_Horizontal;
    Vector robotDirectionXYZ;
    Vector shortArmDirection;
    Vector longArmDirection;

    Point centerBaseLeg;
    Point centerBaseBody;
    Point centerBaseHead;
    Point leftStand;
    Point rightStand;
    Point axisStand;
    Point leftShortArm;
    Point rightShortArm;
    Point axisShortArm;
};

#endif
