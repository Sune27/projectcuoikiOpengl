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
    float angleX;
    float angleZ;
    float bodyRadius;
    float bodyHeight;
    float bodyZPosition;
    //joint
    float jointZPosition;
    float jointRadius;
    //short arm
    float angleLeftShortArm;
    float angleRightShortArm;
    float shortArmDistanceVertical;
    float shortArmDistanceHorizontal;
    float shortArmLength;
    float shortArmRadius;
    //longArm
    float angleXLeftLongArm;
    float angleXRightLongArm;
    float angleZLeftLongArm;
    float angleZRightLongArm;
    float hingeRadius;
    float longArmRadius;
    float longArmLength;
    //hand
    float wristRadius;
    float handRadius;
    float handHeight;
    float handThickness;
    float fingerDistance;
    pair<float, float> angleFingerLeftHand1;
    pair<float, float> angleFingerRightHand1;
    pair<float, float> angleFingerLeftHand2;
    pair<float, float> angleFingerRightHand2;

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
    Color wrist_Color;
    Color wrist_OutlineColor;
    
    Vector normalBase; // (0,0,1)
    Vector robotDirectionXY_Vertical;// lam goc cho tat ca vector khac;
    Vector robotDirectionXY_Horizontal;
    Vector robotDirectionXYZ;
    Vector leftShortArmDirection;
    Vector rightShortArmDirection;
    Vector leftLongArmDirection;
    Vector rightLongArmDirection;
    Vector leftHandDirection;
    Vector rightHandDirection;
    Vector othorgonalLeftHandDirection;
    Vector othorgonalRightHandDirection;

    Point centerBodyPoint;
    Point leftArmJointPoint;
    Point rightArmJointPoint;
    Point leftShortArmPoint;
    Point rightShortArmPoint;
    Point leftHingePoint;
    Point rightHingePoint;
    Point leftLongArmPoint;
    Point rightLongArmPoint;
    Point leftWristPoint;
    Point rightWristPoint;
    Point centerLeftHand;
    Point centerRightHand;
    Point fingerLeftHand1;
    Point fingerLeftHand2;
    Point fingerRightHand1;
    Point fingerRightHand2;
};

#endif
