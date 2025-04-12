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
    void drawRobotBody();
    void drawRobotJoint();
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
    bool showDirection;
    bool showRobot;
    bool isHandOpen;
    //base
    float baseLeg_Radius;
    float baseLeg_Height;
    float bodyRadius;
    float bodyHeight;
    float bodyZPosition;
    float baseHead_Radius;
    float baseHead_Height;
    //joint
    float jointZPosition;
    float jointRadius;
    //stand
    float axisRadius;
    float axisHeight;
    float axisHeightOutside;
    float axisHeightInside;
    float standPositionZ;
    float standAxisDistance;
    float standDistance;
    float standWidth;
    float standLength;
    float standHeight;
    float angleX;
    float angleZ;
    //short arm
    float angleLeftShortArm;
    float angleRightShortArm;
    float shortArmDistanceVertical;
    float shortArmDistanceHorizontal;
    float shortArmLength;
    float shortArmRadius;
    //longArm
    float angleLeftLongArm;
    float angleRightLongArm;
    float hingeRadius;
    float longArmRadius;
    float longArmLength;
    float longArmDistanceVertical;
    float longArmDistanceHorizontal;
    //hand
    float handRadius;
    float handHeight;
    float handThickness;
    float handDistanceVertical;
    float handDistanceHorizontal;
    float leftHandAngleStart_Open;
    float leftHandAngleEnd_Open;
    float rightHandAngleStart_Open;
    float rightHandAngleEnd_Open;    
    float leftHandAngleStart_Close;
    float leftHandAngleEnd_Close;
    float rightHandAngleStart_Close;
    float rightHandAngleEnd_Close;

    //container
    float containerLength;
    double distanceContainer;

    Color body_Color;
    Color body_OutlineColor;
    Color joint_Color;
    Color joint_OutlineColor;    
    Color shortArm_Color;
    Color shortArm_OutlineColor;
    Color hinge_Color;
    Color hinge_OutlineColor;
    Color longArm_Color;
    Color longArm_OutlineColor;
    
    Color hand_Color;
    Color hand_OutlineColor;

    Color containerColor;
    Color containerOutlineColor;

    Vector normalBase; // (0,0,1)
    Vector robotDirectionXY_Vertical;// lam goc cho tat ca vector khac;
    Vector robotDirectionXY_Horizontal;
    Vector robotDirectionXYZ;
    Vector leftShortArmDirection;
    Vector rightShortArmDirection;
    Vector leftLongArmDirection;
    Vector rightLongArmDirection;

    Point centerBodyPoint;
    Point leftArmJointPoint;
    Point rightArmJointPoint;
    Point leftShortArmPoint;
    Point rightShortArmPoint;
    Point leftHingePoint;
    Point rightHingePoint;
    Point leftLongArmPoint;
    Point rightLongArmPoint;
    Point wrist;
    Point leftHand;
    Point rightHand;
    Point centerHand;
    Point centerContainer;
};

#endif
