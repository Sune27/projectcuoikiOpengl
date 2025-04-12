#include "RobotArm.h"

using namespace std;

RobotArm::RobotArm()
{
    showDirection = true;
    isHandOpen = true;
    showRobot = true;
    //base
    baseLeg_Radius = 4;
    baseLeg_Height = 0.2;
    bodyRadius = 4;
    bodyHeight = 7;
    bodyZPosition = 3.5;
    baseHead_Radius = 1.4;
    baseHead_Height = 0.45;
    //joint
    jointZPosition = 2.5;
    jointRadius = 1;
    //stand
    axisRadius = 0.3;
    axisHeight = 2;
    axisHeightOutside = 2;
    axisHeightInside = 1.1;
    standPositionZ = 1.8;
    standAxisDistance = 1.1;
    standDistance = 0.75;
    standWidth = 0.8;
    standLength = 0.15;
    standHeight = 3;
    angleX = 290;
    angleZ = 55.0;
    //short arm
    angleLeftShortArm = 72.0;
    angleRightShortArm = 72.0;
    shortArmDistanceVertical = 1.5;
    shortArmDistanceHorizontal = 0.5;
    shortArmLength = 2;
    shortArmRadius = 0.5;
    //longArm
    angleLongArm = -20.0;
    longArmDistanceVertical = 3;
    longArmDistanceHorizontal = 0.5;
    longArmWidth = 0.8;
    longArmLength = 0.15;
    longArmHeight = 8;
    wristDistance = 7.5;
    wristRadius = 0.7;
    wristHeight = 1.2;
    //hand
    handRadius = 1;
    handHeight = 0.5;
    handThickness = 0.5;
    handDistanceVertical = 1.5;
    handDistanceHorizontal = -0.5;
    leftHandAngleStart_Open = 200;
    leftHandAngleEnd_Open = 270;
    rightHandAngleStart_Open = 350;
    rightHandAngleEnd_Open = 270;    
    leftHandAngleStart_Close = 90;
    leftHandAngleEnd_Close = 270;
    rightHandAngleStart_Close = 270;
    rightHandAngleEnd_Close = 450;

    //container
    containerLength = 2;

    body_Color = GRAY_LIGHT;
    body_OutlineColor = GREEN;
    joint_Color = WHITE;
    joint_OutlineColor = BLACK;    
    stand_Color = WHITE;
    stand_OutlineColor = DARK_BLUE;
    axisStand_Color = WHITE;
    axisStand_Outlinecolor = DARK_BLUE;

    shortArm_OutlineColor = PURPLE;
    shortArm_Color = WHITE;

    longArm_Color = WHITE;
    longArm_OutlineColor = DARK_GREEN;
    wrist_Color = WHITE;
    wrist_OutlineColor = DARK_GREEN;
    
    hand_Color = WHITE;
    hand_OutlineColor = PURPLE;
    containerColor = WHITE;
    containerOutlineColor = DARK_BLUE;

    //set value
    normalBase.setValue(0,0,1);
    centerBodyPoint.setValue(0, 0, bodyZPosition);
    centerContainer.setValue(10,0,4);
    
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
    VectorRotationMethod(leftShortArmDirection, robotDirectionXY_Vertical, angleLeftShortArm);
    VectorRotationMethod(rightShortArmDirection, robotDirectionXY_Vertical, angleRightShortArm);
    VectorRotationMethod(robotDirectionXYZ, robotDirectionXY_Vertical, angleZ);
    longArmDirection.rotateAroundZAxis(robotDirectionXYZ, angleLongArm);
    handDirection.rotateAroundZAxis(longArmDirection, 90);
    handMove = crossProduct(longArmDirection, robotDirectionXY_Vertical);
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
    leftLongArm = axisShortArm;
    rightLongArm = axisShortArm;

}

//done
void RobotArm::drawRobotShortArm()
{
    drawCylinderWithCaps(shortArmRadius, shortArmLength, shortArmRadius, leftShortArmPoint, leftShortArmDirection, shortArm_Color);
    drawCylinderWithCaps(shortArmRadius, shortArmLength, shortArmRadius, rightShortArmPoint, leftShortArmDirection, shortArm_Color);
    drawCylinderOutline(shortArmRadius, shortArmLength, leftShortArmPoint, leftShortArmDirection, shortArm_OutlineColor);
    drawCylinderOutline(shortArmRadius, shortArmLength, rightShortArmPoint, rightShortArmDirection, shortArm_OutlineColor);
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
    }
    // drawRobotLongArm();
    // drawRobotHand();
    // drawContainer();
    test();
}

void RobotArm::drawRobotLongArm()
{
}

void RobotArm::drawContainer()
{
}

void RobotArm::drawDirection()
{
    if(showDirection == true)
    {
        glLineWidth(LINE_WIDTH);
        
        drawLine(robotDirectionXY_Vertical, centerBodyPoint, DIRECTION_LENGTH, PURPLE);
        drawLine(robotDirectionXY_Horizontal, centerBodyPoint, DIRECTION_LENGTH, BLUE);
        drawLine(leftShortArmDirection, leftArmJointPoint, DIRECTION_LENGTH, GREEN);
        drawLine(rightShortArmDirection, rightArmJointPoint, DIRECTION_LENGTH, ORANGE);
        //drawLine(robotDirectionXYZ, centerBaseHead, DIRECTION_LENGTH, DARK_GREEN);
    }
}

//done
void RobotArm::drawRobotHand()
{
}

void RobotArm::test()
{
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

void RobotArm::drawRobotJoint()
{
    drawSolidSphere(leftArmJointPoint, jointRadius, joint_Color, joint_OutlineColor);
    drawSolidSphere(rightArmJointPoint, jointRadius, joint_Color, joint_OutlineColor);
}

//done
void RobotArm::drawRobotBody()
{
    drawCylinderWithCaps(bodyRadius, bodyHeight, bodyRadius, centerBodyPoint, normalBase, body_Color);
    drawCylinderOutline(bodyRadius, bodyHeight, centerBodyPoint, normalBase, body_OutlineColor);
}

void RobotArm::checkMinValueAngle()
{
    if(angleZ < ANGLEZ_MIN) angleZ = ANGLEZ_MIN;
    if(angleLeftShortArm < ANGLESHORTARM_MIN) angleLeftShortArm = ANGLESHORTARM_MIN;
    if(angleLongArm < ANGLELONGARM_MIN) angleLongArm = ANGLELONGARM_MIN;
}

void RobotArm::checkMaxValueAngle()
{
    if(angleZ > ANGLEZ_MAX) angleZ = ANGLEZ_MAX;
    if(angleLeftShortArm > ANGLESHORTARM_MAX) angleLeftShortArm = ANGLESHORTARM_MAX;
    if(angleLongArm > ANGLELONGARM_MAX) angleLongArm = ANGLELONGARM_MAX;
}

void RobotArm::changeHandDistanceVertical(float distance)
{
    handDistanceVertical += distance/10;
}

void RobotArm::changeHandDistanceHorizontal(float distance)
{
    handDistanceHorizontal += distance/10;
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
        case ANGLE_Z:
            return ANGLE_Z;
        case ANGLE_LONG_ARM:
            return angleLongArm;
        case ANGLE_SHORT_ARM:
            return angleLeftShortArm;
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
        case LONGARM:
            return longArmDirection;
    }
}

void RobotArm::rotateAngle(TypeAngle angle, float rotate)
{
    switch (angle)
    {
    case ANGLE_LEFT_SHORT_ARM:
        angleLeftShortArm += rotate;
        break;
    case ANGLE_RIGHT_SHORT_ARM:
        angleRightShortArm += rotate;
        break;
    case ANGLE_X:
        angleX += rotate;
        break;
    case ANGLE_Z:
        angleZ += rotate;
        break;
    case ANGLE_LONG_ARM:
        angleLongArm += rotate;
        break;
    default:
        break;
    }
}
