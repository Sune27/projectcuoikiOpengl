#include "RobotArm.h"

using namespace std;

RobotArm::RobotArm()
{
    showDirection = true;
    isHandOpen = true;
    showRobot = true;
    //base
    bodyRadius = 4;
    bodyHeight = 7;
    bodyZPosition = 3.5;
    //joint
    jointZPosition = 2.5;
    jointRadius = 1;
    //stand
    angleX = 485;
    angleZ = 55;
    //short arm
    angleLeftShortArm = 110;
    angleRightShortArm = 110;
    shortArmDistanceVertical = 1.7;
    shortArmDistanceHorizontal = 0.5;
    shortArmLength = 4;
    shortArmRadius = 0.85;
    //longArm
    angleXLeftLongArm = -65;
    angleXRightLongArm = -65;
    angleZLeftLongArm = 35;
    angleZRightLongArm = 35;
    hingeRadius = 1;
    longArmRadius = 0.85;
    longArmLength = 3;
    //hand
    wristRadius = 0.5;
    handRadius = 1;
    handHeight = 0.5;
    handThickness = 0.5;
    fingerDistance = 1;

    //container
    containerLength = 2;

    body_Color = GOLD3;
    body_OutlineColor = DARK_GRAY;
    joint_Color = SILVER;
    joint_OutlineColor = BLACK;    
    shortArm_Color = WHITE;
    shortArm_OutlineColor = BLACK;
    hinge_Color = ALUMINUM;
    hinge_OutlineColor = DARK_GRAY;
    longArm_Color = LIGHT_BLUE;
    longArm_OutlineColor = DARK_GREEN;
    wrist_Color = DARK_GRAY;
    wrist_OutlineColor = BLACK;

    //set value
    normalBase.setValue(0,0,1);
    centerBodyPoint.setValue(0, 0, bodyZPosition);
    
    robotDirectionXY_Vertical.vertical(angleX);
    robotDirectionXY_Horizontal.horizontal(robotDirectionXY_Vertical);
}

void RobotArm::printAttributeToTxt()
{
    // ofstream outputFile("attributes.txt");
    // if(outputFile.is_open() == false)
    // {
    //     cerr << "khong the mo file attribute.txt";
    // }
    // else
    // {
    //     outputFile << "float baseLeg_Radius = " << baseLeg_Radius << ";" << endl;
    //     outputFile << "float baseLeg_Height = " << baseLeg_Height << ";" << endl;

    //     outputFile << "leftLongArm_Color: WHITE 255 255 255"  << endl;
    // }
}

void RobotArm::printAttributes()
{
    cout << __TIME__ << endl;
    cout << "angleX: " << angleX << endl;
    cout << "angleZ: " << angleZ << endl;
    cout << "angleLeftShortArm: " << angleLeftShortArm << endl;
    cout << "angleRightShortArm: " << angleRightShortArm << endl;
    cout << "angleXLeftLongArm: " << angleXLeftLongArm << endl;
    cout << "angleXRightLongArm: " << angleXRightLongArm << endl;
    cout << "angleZLeftLongArm: " << angleZLeftLongArm << endl;
    cout << "angleZRightLongArm: " << angleZRightLongArm << endl;
    cout << "longArmRadius: " << longArmRadius << endl;
    cout << "longArmLength: " << longArmLength << endl;
    cout << "eyeX: " << eyeX << endl;
	cout << "eyeY: " << eyeY << endl;
	cout << "eyeZ: " << eyeZ << endl;
	cout << "centerX: " << centerX << endl;
	cout << "centerY: " << centerY << endl;
	cout << "centerZ: " << centerZ << endl;
	cout << "upX: " << upX << endl;
	cout << "upY: " << upY << endl;
	cout << "upZ: " << upZ << endl;

}

void RobotArm::update()
{
    //vector
    robotDirectionXY_Vertical.vertical(angleX);
    robotDirectionXY_Horizontal.horizontal(robotDirectionXY_Vertical);
    VectorRotationMethod(robotDirectionXYZ, robotDirectionXY_Vertical, angleZ);
    leftShortArmDirection.rotateAroundZAxis(robotDirectionXYZ, angleLeftShortArm);
    rightShortArmDirection.rotateAroundZAxis(robotDirectionXYZ, angleRightShortArm);
    leftLongArmDirection.vertical(angleXLeftLongArm);
    rightLongArmDirection.vertical(angleXRightLongArm);
    othorgonalLeftHandDirection.horizontal(leftLongArmDirection);
    othorgonalRightHandDirection.horizontal(rightLongArmDirection);
    VectorRotationMethod(leftLongArmDirection, leftLongArmDirection, angleZLeftLongArm);
    VectorRotationMethod(rightLongArmDirection, rightLongArmDirection, angleZRightLongArm);
    leftHandDirection.rotateAroundZAxis(leftLongArmDirection, 90);
    rightHandDirection.rotateAroundZAxis(rightLongArmDirection, 90);
    //joint
    leftArmJointPoint = centerBodyPoint;
    rightArmJointPoint = centerBodyPoint;
    leftArmJointPoint.move(robotDirectionXY_Horizontal, bodyRadius+jointRadius);
    rightArmJointPoint.move(robotDirectionXY_Horizontal, -bodyRadius-jointRadius);
    leftArmJointPoint.move(normalBase, jointZPosition);
    rightArmJointPoint.move(normalBase, jointZPosition);
    //shortarm
    leftShortArmPoint = leftArmJointPoint;
    rightShortArmPoint = rightArmJointPoint;
    leftShortArmPoint.move(leftShortArmDirection, jointRadius+shortArmLength/2);
    rightShortArmPoint.move(rightShortArmDirection, jointRadius+shortArmLength/2);

    //longarm
    leftHingePoint = leftShortArmPoint;
    rightHingePoint = rightShortArmPoint;
    leftHingePoint.move(leftShortArmDirection, hingeRadius+shortArmLength/2);
    rightHingePoint.move(rightShortArmDirection, hingeRadius+shortArmLength/2);
    leftLongArmPoint = leftHingePoint;
    rightLongArmPoint = rightHingePoint;
    leftLongArmPoint.move(leftLongArmDirection, hingeRadius+longArmLength/2);
    rightLongArmPoint.move(rightLongArmDirection, hingeRadius+longArmLength/2);
    //hand
    leftWristPoint = leftLongArmPoint;
    rightWristPoint = rightLongArmPoint;
    leftWristPoint.move(leftLongArmDirection, wristRadius+longArmLength/2);
    rightWristPoint.move(rightLongArmDirection, wristRadius + longArmLength/2);
    centerLeftHand = leftWristPoint;
    centerRightHand = rightWristPoint;
    centerLeftHand.move(leftLongArmDirection, wristRadius);
    centerRightHand.move(rightLongArmDirection, wristRadius);
    fingerLeftHand1 = centerLeftHand;
    fingerLeftHand2 = centerLeftHand;
    fingerRightHand1 = centerRightHand;
    fingerRightHand2 = centerRightHand;
    fingerLeftHand1.move(othorgonalLeftHandDirection, fingerDistance);
    fingerLeftHand2.move(othorgonalLeftHandDirection, -fingerDistance);
    fingerRightHand1.move(othorgonalRightHandDirection, fingerDistance);
    fingerRightHand2.move(othorgonalRightHandDirection, -fingerDistance);

}

void RobotArm::draw()
{
    update();
    printAttributes();
    printAttributeToTxt();
    drawDirection();
    if(showRobot)
    {
        drawRobotBody();
        drawRobotJoint();
        drawRobotShortArm();
        drawRobotLongArm();
        drawRobotHand();
    }
    // drawContainer();
}

void RobotArm::drawDirection()
{
    if(showDirection == true)
    {
        glLineWidth(LINE_WIDTH);
        
        drawLine(robotDirectionXY_Vertical, centerBodyPoint, DIRECTION_LENGTH, PURPLE);
        drawLine(robotDirectionXY_Horizontal, centerBodyPoint, DIRECTION_LENGTH, BLUE);
        drawLine(robotDirectionXYZ, centerBodyPoint, DIRECTION_LENGTH, GREEN);
        // drawLine(leftShortArmDirection, leftArmJointPoint, DIRECTION_LENGTH, GREEN);
        // drawLine(rightShortArmDirection, rightArmJointPoint, DIRECTION_LENGTH, ORANGE);
        // drawLine(leftLongArmDirection, leftHingePoint, DIRECTION_LENGTH, RED);
        // drawLine(rightLongArmDirection, rightHingePoint, DIRECTION_LENGTH, PINK);
        drawLine(leftHandDirection, leftWristPoint, DIRECTION_LENGTH, YELLOW);
        drawLine(rightHandDirection, rightWristPoint, DIRECTION_LENGTH, ORANGE);
        drawLine(othorgonalLeftHandDirection, leftWristPoint, DIRECTION_LENGTH, RED);
        drawLine(othorgonalRightHandDirection, rightWristPoint, DIRECTION_LENGTH, PINK);
    }
}

void RobotArm::drawRobotHand()
{
    drawSolidSphere(leftWristPoint, wristRadius, wrist_Color);
    drawWireSphere(leftWristPoint, wristRadius, wrist_OutlineColor);
    drawSolidSphere(rightWristPoint, wristRadius, wrist_Color);
    drawWireSphere(rightWristPoint, wristRadius, wrist_OutlineColor);

}

void RobotArm::drawRobotLongArm()
{
    drawSolidSphere(leftHingePoint, hingeRadius, hinge_Color);
    drawWireSphere(leftHingePoint, hingeRadius, hinge_OutlineColor);
    drawSolidSphere(rightHingePoint, hingeRadius, hinge_Color);
    drawWireSphere(rightHingePoint, hingeRadius, hinge_OutlineColor);
    drawCylinderWithCaps(longArmRadius, longArmLength, longArmRadius, leftLongArmPoint, leftLongArmDirection, longArm_Color);
    drawCylinderOutline(longArmRadius, longArmLength, leftLongArmPoint, leftLongArmDirection, longArm_OutlineColor);
    drawCylinderWithCaps(longArmRadius, longArmLength, longArmRadius, rightLongArmPoint, rightLongArmDirection, longArm_Color);
    drawCylinderOutline(longArmRadius, longArmLength, rightLongArmPoint, rightLongArmDirection, longArm_OutlineColor);
}
void RobotArm::drawRobotShortArm()
{
    drawCylinderWithCaps(shortArmRadius, shortArmLength, shortArmRadius, leftShortArmPoint, leftShortArmDirection, shortArm_Color);
    drawCylinderOutline(shortArmRadius, shortArmLength, leftShortArmPoint, leftShortArmDirection, shortArm_OutlineColor);
    
    drawCylinderWithCaps(shortArmRadius, shortArmLength, shortArmRadius, rightShortArmPoint, rightShortArmDirection, shortArm_Color);
    drawCylinderOutline(shortArmRadius, shortArmLength, rightShortArmPoint, rightShortArmDirection, shortArm_OutlineColor);
}
void RobotArm::drawRobotJoint()
{
    drawSolidSphere(leftArmJointPoint, jointRadius, joint_Color);
    drawWireSphere(leftArmJointPoint, jointRadius, joint_OutlineColor);
    drawSolidSphere(rightArmJointPoint, jointRadius, joint_Color);
    drawWireSphere(rightArmJointPoint, jointRadius, joint_OutlineColor);
}
void RobotArm::drawRobotBody()
{
    drawCylinderWithCaps(bodyRadius, bodyHeight, bodyRadius, centerBodyPoint, normalBase, body_Color);
    drawCylinderOutline(bodyRadius, bodyHeight, centerBodyPoint, normalBase, body_OutlineColor);
}

void RobotArm::changeStatus(TypeStatus status)
{
    switch(status)
    {
        case SHOW_OBJECT_STATUS:
            showRobot = !showRobot;
            break;
        case SHOW_DIRECTION:
            showDirection = !showDirection;
            break;
        case HAND_OPEN:
            isHandOpen = !isHandOpen;
            break;
        default:
            break;
    }
}
void RobotArm::checkMinValueAngle()
{
    if(angleZ < ANGLEZ_MIN) angleZ = ANGLEZ_MIN;
    if(angleLeftShortArm < ANGLESHORTARM_MIN) angleLeftShortArm = ANGLESHORTARM_MIN;
}
void RobotArm::checkMaxValueAngle()
{
    if(angleZ > ANGLEZ_MAX) angleZ = ANGLEZ_MAX;
    if(angleLeftShortArm > ANGLESHORTARM_MAX) angleLeftShortArm = ANGLESHORTARM_MAX;
}
RobotArm::~RobotArm()
{
}
float RobotArm::getAngle(TypeAngle a)
{
    switch (a)
    {
        case ANGLE_X:
            return angleX;
    }
}
Vector RobotArm::getVector(TypeVector v)
{
    switch(v)
    {
        case NORMALBASE:
            return normalBase;
        case ROBOTDIRECTIONXY_HORIZONTAL:
            return robotDirectionXY_Horizontal;
        case ROBOTDIRECTIONXY_VERTICAL:
            return robotDirectionXY_Vertical;
        case ROBOTDIRECTIONXYZ:
            return robotDirectionXYZ;
        case SHORTARM:
            return leftShortArmDirection;
    }
}

void RobotArm::rotateAngle(TypeAngle angle, float rotate)
{
    switch (angle)
    {
    case ANGLEZ_LEFT_LONG_ARM:
        angleZLeftLongArm += rotate;
        break;
    case ANGLEZ_RIGHT_LONG_ARM:
        angleZRightLongArm += rotate;
        break;
    case ANGLEX_RIGHT_LONG_ARM:
        angleXRightLongArm += rotate;
        break;
    case ANGLEX_LEFT_LONG_ARM:
        angleXLeftLongArm += rotate;
        break;
    case ANGLE_LEFT_SHORT_ARM:
        angleLeftShortArm += rotate;
        break;
    case ANGLE_RIGHT_SHORT_ARM:
        angleRightShortArm += rotate;
        break;
    case ANGLE_X:
        angleX += rotate;
        angleXLeftLongArm += rotate;
        angleXRightLongArm += rotate;
        break;
    default:
        break;
    }
}
