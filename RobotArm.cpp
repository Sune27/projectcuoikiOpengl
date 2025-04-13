#include "RobotArm.h"

using namespace std;

RobotArm::RobotArm()
{
    showDirection = true;
    isHandOpen = true;
    showRobot = true;
    isLeftHandClaw = false;
    isRightHandClaw = false;
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
    fingerRadius = 1;
    fingerHeight = 0.5;
    fingerThickness = 0.5;
    fingerDistance = 1;
    angleFingerLeftHand1_Open = make_pair(90.0, 270.0);
    angleFingerLeftHand2_Open = make_pair(90.0, 270.0);
    angleFingerRightHand1_Open = make_pair(90.0, 270.0);
    angleFingerRightHand2_Open = make_pair(90.0, 270.0);
    angleFingerRightHand1_Close = make_pair(90.0, 180.0);
    angleFingerRightHand2_Close = make_pair(90.0, 180.0);
    angleFingerLeftHand1_Close = make_pair(90.0, 180.0);
    angleFingerLeftHand2_Close = make_pair(90.0, 180.0);

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
    fingerDisableClaw_Color = ALUMINUM;
    fingerDisableClaw_OutlineColor = DARK_GRAY;
    container_Color = SILVER;
    container_OutlineColor = DARK_GREEN;

    //set value
    normalBase.setValue(0,0,1);
    centerBodyPoint.setValue(0, 0, bodyZPosition);
    containerPoint.setValue(10, 10, 8);
    
    robotDirectionXY_Vertical.vertical(angleX);
    robotDirectionXY_Horizontal.horizontal(robotDirectionXY_Vertical);
    containerDirection = robotDirectionXY_Vertical;
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
    centerLeftHandPoint = leftWristPoint;
    centerRightHandPoint = rightWristPoint;
    centerLeftHandPoint.move(leftLongArmDirection, wristRadius);
    centerRightHandPoint.move(rightLongArmDirection, wristRadius);
    fingerLeftHand1Point = centerLeftHandPoint;
    fingerLeftHand2Point = centerLeftHandPoint;
    fingerRightHand1Point = centerRightHandPoint;
    fingerRightHand2Point = centerRightHandPoint;
    fingerLeftHand1Point.move(othorgonalLeftHandDirection, fingerDistance);
    fingerLeftHand2Point.move(othorgonalLeftHandDirection, -fingerDistance);
    fingerRightHand1Point.move(othorgonalRightHandDirection, fingerDistance);
    fingerRightHand2Point.move(othorgonalRightHandDirection, -fingerDistance);
    //container
}

void RobotArm::draw()
{
    update();
    printAttributes();
    printAttributeToTxt();
    drawDirection();
    drawFloor(SIZE_FLOOR, DIVISION_FLOOR, GRAY);
    if(showRobot)
    {
        drawRobotBody();
        drawRobotJoint();
        drawRobotShortArm();
        drawRobotLongArm();
        drawRobotHand();
        drawContainer();
    }
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

void RobotArm::drawContainer()
{
    if(isLeftHandClaw == false && isRightHandClaw == false)
    {
        drawBox(containerLength, containerLength, containerLength, containerDirection, containerPoint, container_Color);
        drawBoxOutline(containerLength, containerLength, containerLength, containerDirection, containerPoint, container_OutlineColor);
    }
    else if(isLeftHandClaw == true)
    {
        drawBox(containerLength, containerLength, containerLength, containerDirection, centerLeftHandPoint, container_Color);
        drawBoxOutline(containerLength, containerLength, containerLength, containerDirection, centerLeftHandPoint, container_OutlineColor);
    }
    else if(isRightHandClaw == true)
    {
        drawBox(containerLength, containerLength, containerLength, containerDirection, centerRightHandPoint, container_Color);
        drawBoxOutline(containerLength, containerLength, containerLength, containerDirection, centerRightHandPoint, container_OutlineColor);
    }
}

void RobotArm::drawRobotHand()
{
    drawSolidSphere(leftWristPoint, wristRadius, wrist_Color);
    drawWireSphere(leftWristPoint, wristRadius, wrist_OutlineColor);
    drawSolidSphere(rightWristPoint, wristRadius, wrist_Color);
    drawWireSphere(rightWristPoint, wristRadius, wrist_OutlineColor);
    if(isHandOpen == true)
    {
        drawMissingCylinder(fingerRadius, fingerHeight, fingerThickness, fingerLeftHand1Point, leftHandDirection, fingerDisableClaw_Color, angleFingerLeftHand1_Open.first, angleFingerLeftHand1_Open.second);
        drawMissingCylinderOutline(fingerRadius, fingerHeight, fingerLeftHand1Point, leftHandDirection, fingerDisableClaw_OutlineColor, angleFingerLeftHand1_Open.first, angleFingerLeftHand1_Open.second);
        drawMissingCylinder(fingerRadius, fingerHeight, fingerThickness, fingerLeftHand2Point, leftHandDirection, fingerDisableClaw_Color, angleFingerLeftHand2_Open.first, angleFingerLeftHand2_Open.second);
        drawMissingCylinderOutline(fingerRadius, fingerHeight, fingerLeftHand2Point, leftHandDirection, fingerDisableClaw_OutlineColor, angleFingerLeftHand2_Open.first, angleFingerLeftHand2_Open.second);
        drawMissingCylinder(fingerRadius, fingerHeight, fingerThickness, fingerRightHand1Point, rightHandDirection, fingerDisableClaw_Color, angleFingerRightHand1_Open.first, angleFingerRightHand1_Open.second);
        drawMissingCylinderOutline(fingerRadius, fingerHeight, fingerRightHand1Point, rightHandDirection, fingerDisableClaw_OutlineColor, angleFingerRightHand1_Open.first, angleFingerRightHand1_Open.second);
        drawMissingCylinder(fingerRadius, fingerHeight, fingerThickness, fingerRightHand2Point, rightHandDirection, fingerDisableClaw_Color, angleFingerRightHand2_Open.first, angleFingerRightHand2_Open.second);
        drawMissingCylinderOutline(fingerRadius, fingerHeight, fingerRightHand2Point, rightHandDirection, fingerDisableClaw_OutlineColor, angleFingerRightHand2_Open.first, angleFingerRightHand2_Open.second);
    }
    else
    {
        drawMissingCylinder(fingerRadius, fingerHeight, fingerThickness, fingerLeftHand1Point, leftHandDirection, fingerDisableClaw_Color, angleFingerLeftHand1_Close.first, angleFingerLeftHand1_Close.second);
        drawMissingCylinderOutline(fingerRadius, fingerHeight, fingerLeftHand1Point, leftHandDirection, fingerDisableClaw_OutlineColor, angleFingerLeftHand1_Close.first, angleFingerLeftHand1_Close.second);
        drawMissingCylinder(fingerRadius, fingerHeight, fingerThickness, fingerLeftHand2Point, leftHandDirection, fingerDisableClaw_Color, angleFingerLeftHand2_Close.first, angleFingerLeftHand2_Close.second);
        drawMissingCylinderOutline(fingerRadius, fingerHeight, fingerLeftHand2Point, leftHandDirection, fingerDisableClaw_OutlineColor, angleFingerLeftHand2_Close.first, angleFingerLeftHand2_Close.second);
        drawMissingCylinder(fingerRadius, fingerHeight, fingerThickness, fingerRightHand1Point, rightHandDirection, fingerDisableClaw_Color, angleFingerRightHand1_Close.first, angleFingerRightHand1_Close.second);
        drawMissingCylinderOutline(fingerRadius, fingerHeight, fingerRightHand1Point, rightHandDirection, fingerDisableClaw_OutlineColor, angleFingerRightHand1_Close.first, angleFingerRightHand1_Close.second);
        drawMissingCylinder(fingerRadius, fingerHeight, fingerThickness, fingerRightHand2Point, rightHandDirection, fingerDisableClaw_Color, angleFingerRightHand2_Close.first, angleFingerRightHand2_Close.second);
        drawMissingCylinderOutline(fingerRadius, fingerHeight, fingerRightHand2Point, rightHandDirection, fingerDisableClaw_OutlineColor, angleFingerRightHand2_Close.first, angleFingerRightHand2_Close.second);

    }
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
        normalizeAngle(angleZLeftLongArm);
        break;
    case ANGLEZ_RIGHT_LONG_ARM:
        angleZRightLongArm += rotate;
        normalizeAngle(angleZRightLongArm);
        break;
    case ANGLEX_RIGHT_LONG_ARM:
        angleXRightLongArm += rotate;
        normalizeAngle(angleXRightLongArm);
        break;
    case ANGLEX_LEFT_LONG_ARM:
        angleXLeftLongArm += rotate;
        normalizeAngle(angleXLeftLongArm);
        break;
    case ANGLE_LEFT_SHORT_ARM:
        angleLeftShortArm += rotate;
        normalizeAngle(angleLeftShortArm);
        break;
    case ANGLE_RIGHT_SHORT_ARM:
        angleRightShortArm += rotate;
        normalizeAngle(angleRightShortArm);
        break;
    case ANGLE_X:
        angleX += rotate;
        angleXLeftLongArm += rotate;
        angleXRightLongArm += rotate;
        normalizeAngle(angleX);
        normalizeAngle(angleXLeftLongArm);
        normalizeAngle(angleXRightLongArm);
        break;
    default:
        break;
    }
}
