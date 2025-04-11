#include <GL/glut.h>
#include <iostream>
#include <fstream>

#include "Utils.h"
#include "Config.h"

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
    void drawRobotHand();
    void drawContainer();
    void drawDirection();
    void printAttributes();
    void checkMinValueAngle();
    void checkMaxValueAngle();
    void printAttributeToTxt();
    void update();
    void test();
    
    void rotateAngle(TypeAngle angle, float rotate);
    void changeHandDistanceVertical(float distance);
    void changeHandDistanceHorizontal(float distance);
    void changeStatus(TypeStatus status);

    Vector getVector(TypeVector v);
    float getAngle(TypeAngle a);

private:
    //special
    bool showDirection = false;
    bool isHandOpen = true;
    //base
    float baseLeg_Radius = 4;
    float baseLeg_Height = 0.2;
    float baseBody_Radius = 2;
    float baseBody_Height = 0.75;
    float baseHead_Radius = 1.4;
    float baseHead_Height = 0.45;
    //stand
    float axisRadius = 0.3;
    float axisHeight = 2;
    float axisHeightOutside = 2;
    float axisHeightInside = 1.1;
    float standPositionZ = 1.8;
    float standAxisDistance = 1.1;
    float standDistance = 0.75;
    float standWidth = 0.8;
    float standLength = 0.15;
    float standHeight = 3;
    float angleX = 60.0;
    float angleZ = 55.0;
    //short arm
    float angleShortArm = 72.0;
    float shortArmDistanceVertical = 1.5;
    float shortArmDistanceHorizontal = 0.5;
    float shortArmWidth = 0.8;
    float shortArmLength = 0.15;
    float shortArmHeight = 4;
    float axisShortArmDistance = 3.1;
    float axisShortArmRadius = 0.3;
    float axisShortArmHeight = 2;
    float axisShortArmHeightOutside = 2;
    float axisShortArmHeightInside = 1.5;
    //longArm
    float angleLongArm = -20.0;
    float longArmDistanceVertical = 3;
    float longArmDistanceHorizontal = 0.5;
    float longArmWidth = 0.8;
    float longArmLength = 0.15;
    float longArmHeight = 8;
    float wristDistance = 7.5;
    float wristRadius = 0.7;
    float wristHeight = 1.2;
    //hand
    float handRadius = 1;
    float handHeight = 0.5;
    float handThickness = 0.5;
    float handDistanceVertical = 1.5;
    float handDistanceHorizontal = -0.5;
    float leftHandAngleStart_Open = 200;
    float leftHandAngleEnd_Open = 270;
    float rightHandAngleStart_Open = 350;
    float rightHandAngleEnd_Open = 270;    
    float leftHandAngleStart_Close = 90;
    float leftHandAngleEnd_Close = 270;
    float rightHandAngleStart_Close = 270;
    float rightHandAngleEnd_Close = 450;

    //container
    float containerLength = 2;
    double distanceContainer;

    Color baseLeg_Color = GRAY_LIGHT;
    Color baseLeg_OutlineColor = GREEN;
    Color baseBody_Color = GRAY_LIGHT;
    Color baseBody_OutlineColor = GREEN;
    Color baseHead_Color = GRAY_LIGHT;
    Color baseHead_OutlineColor = GREEN;
    
    Color stand_Color = WHITE;
    Color stand_OutlineColor = DARK_BLUE;
    Color axisStand_Color = WHITE;
    Color axisStand_Outlinecolor = DARK_BLUE;

    Color shortArm_Color = WHITE;
    Color shortArm_OutlineColor = PURPLE;
    Color axisShortArm_Color = WHITE;
    Color axisShortArm_OutlineColor = DARK_BLUE;

    Color longArm_Color = WHITE;
    Color longArm_OutlineColor = DARK_GREEN;
    Color wrist_Color = WHITE;
    Color wrist_OutlineColor = DARK_GREEN;
    
    Color hand_Color = WHITE;
    Color hand_OutlineColor = PURPLE;

    Color containerColor = WHITE;
    Color containerOutlineColor = DARK_BLUE;

    Vector normalBase; // (0,0,1)
    Vector robotDirectionXY_Vertical;// lam goc cho tat ca vector khac;
    Vector robotDirectionXY_Horizontal;
    Vector robotDirectionXYZ;
    Vector shortArmDirection;
    Vector longArmDirection;
    Vector handDirection;
    Vector handMove;
    Vector containerDirection;

    Point centerBaseLeg;
    Point centerBaseBody;
    Point centerBaseHead;
    Point leftStand;
    Point rightStand;
    Point axisStand;
    Point leftShortArm;
    Point rightShortArm;
    Point axisShortArm;
    Point leftLongArm;
    Point rightLongArm;
    Point wrist;
    Point leftHand;
    Point rightHand;
    Point centerHand;
    Point centerContainer;
};

#endif
