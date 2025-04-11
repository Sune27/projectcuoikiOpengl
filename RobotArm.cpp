#include "RobotArm.h"

using namespace std;

RobotArm::RobotArm()
{
    //set value
    normalBase.setValue(0,0,1);
    centerBaseLeg.setValue(0, 0, 0);
    centerBaseBody.setValue(0, 0, 0.5);
    centerBaseHead.setValue(0, 0, 1.0);
    
}

void RobotArm::printAttributeToTxt()
{
    ofstream outputFile("attributes.txt");
    if(outputFile.is_open() == false)
    {
        cerr << "khong the mo file attribute.txt";
    }
    else
    {
        outputFile << "float baseLeg_Radius = " << baseLeg_Radius << ";" << endl;
    }
}

void RobotArm::printAttributes()
{
    cout << __TIME__ << endl;
    cout << "angleX: " << angleX << endl;
    cout << "angleZ: " << angleZ << endl;
    cout << "angleShortArm: " << angleShortArm << endl;
    cout << "angleLongArm: " << angleLongArm << endl;
    cout << "handDistanceVertical: " << handDistanceVertical << endl;
    cout << "handDistanceHorizontal: " << handDistanceHorizontal << endl;
    cout << leftHand << endl;
}

void RobotArm::update()
{
    //vector
    robotDirectionXY_Vertical.vertical(angleX);
    robotDirectionXY_Horizontal.horizontal(robotDirectionXY_Vertical);
    VectorRotationMethod(robotDirectionXYZ, robotDirectionXY_Vertical, angleZ);
    shortArmDirection.rotateAroundZAxis(robotDirectionXYZ, angleShortArm);
    longArmDirection.rotateAroundZAxis(robotDirectionXYZ, angleLongArm);
    handDirection.rotateAroundZAxis(longArmDirection, 90);
    handMove = crossProduct(longArmDirection, robotDirectionXY_Vertical);
    //stand
    leftStand.setValue(0, 0, standPositionZ);
    rightStand.setValue(0, 0, standPositionZ);
    axisStand.setValue(0, 0, standPositionZ);
    leftStand.move(robotDirectionXY_Horizontal, standDistance);
    rightStand.move(robotDirectionXY_Horizontal, -standDistance);
    axisStand.move(robotDirectionXYZ, standAxisDistance);

    //shortarm
    leftShortArm.setValue(axisStand.arr[0], axisStand.arr[1], axisStand.arr[2]);
    rightShortArm.setValue(axisStand.arr[0], axisStand.arr[1], axisStand.arr[2]);
    axisShortArm.setValue(axisStand.arr[0], axisStand.arr[1], axisStand.arr[2]);

    leftShortArm.move(shortArmDirection, 1.5);
    rightShortArm.move(shortArmDirection, 1.5);
    axisShortArm.move(shortArmDirection, shortArmHeight-0.9);
    leftShortArm.move(robotDirectionXY_Horizontal, shortArmDistance);
    rightShortArm.move(robotDirectionXY_Horizontal, -shortArmDistance);

    //longarm
    leftLongArm.setValue(axisShortArm.arr[0], axisShortArm.arr[1], axisShortArm.arr[2]);
    rightLongArm.setValue(axisShortArm.arr[0], axisShortArm.arr[1], axisShortArm.arr[2]);
    wrist.setValue(axisShortArm.arr[0], axisShortArm.arr[1], axisShortArm.arr[2]);
    leftLongArm.move(longArmDirection, 3);
    rightLongArm.move(longArmDirection, 3);
    leftLongArm.move(robotDirectionXY_Horizontal, longArmDistance);
    rightLongArm.move(robotDirectionXY_Horizontal, -longArmDistance);
    wrist.move(longArmDirection, wristDistance);

    //hand
    leftHand.setValue(wrist.arr[0], wrist.arr[1], wrist.arr[2]);
    rightHand.setValue(wrist.arr[0], wrist.arr[1], wrist.arr[2]);
    leftHand.move(longArmDirection, handDistanceVertical);
    rightHand.move(longArmDirection, handDistanceVertical);
    leftHand.move(handMove, handDistanceHorizontal);
    rightHand.move(handMove, -handDistanceHorizontal);
}


void RobotArm::drawRobotShortArm()
{
    drawBox(shortArmLength, shortArmWidth, shortArmHeight, shortArmDirection, leftShortArm, WHITE);
    drawBox(shortArmLength, shortArmWidth, shortArmHeight, shortArmDirection, rightShortArm, WHITE);
    drawBoxOutline(shortArmLength, shortArmWidth, shortArmHeight, shortArmDirection, leftShortArm, PURPLE);
    drawBoxOutline(shortArmLength, shortArmWidth, shortArmHeight, shortArmDirection, rightShortArm, PURPLE);
    drawCylinderWithCaps(axisShortArmRadius, axisShortArmHeight, axisShortArmRadius, axisShortArm, robotDirectionXY_Horizontal, WHITE);
    drawCylinderOutline(axisShortArmRadius, axisShortArmHeight, axisShortArm, robotDirectionXY_Horizontal, DARK_BLUE);
    drawCylinderOutline(axisShortArmRadius, axisShortArmHeight - 0.5, axisShortArm, robotDirectionXY_Horizontal, DARK_BLUE);

}

void RobotArm::draw()
{
    update();
    printAttributes();
    printAttributeToTxt();
    drawDirection();
    drawRobotBase();
    drawRobotStand();
    drawRobotShortArm();
    drawRobotLongArm();
    drawRobotHand();
    test();
}

void RobotArm::drawRobotLongArm()
{
    drawBox(longArmLength, longArmWidth, longArmHeight, longArmDirection, leftLongArm, WHITE);
    drawBox(longArmLength, longArmWidth, longArmHeight, longArmDirection, rightLongArm, WHITE);
    drawBoxOutline(longArmLength, longArmWidth, longArmHeight, longArmDirection, leftLongArm, DARK_GREEN);
    drawBoxOutline(longArmLength, longArmWidth, longArmHeight, longArmDirection, rightLongArm, DARK_GREEN);
    drawCylinderWithCaps(wristRadius, wristHeight, wristRadius, wrist, longArmDirection, WHITE);
    drawCylinderOutline(wristRadius, wristHeight, wrist, longArmDirection, DARK_BLUE);
}

void RobotArm::drawDirection()
{
    if(showDirection == true)
    {
        glLineWidth(LINE_WIDTH);
        
        drawLine(robotDirectionXY_Vertical, centerBaseHead, DIRECTION_LENGTH, PURPLE);
        drawLine(robotDirectionXY_Horizontal, centerBaseHead, DIRECTION_LENGTH, BLUE);
        //drawLine(robotDirectionXYZ, centerBaseHead, DIRECTION_LENGTH, DARK_GREEN);
        drawLine(shortArmDirection, axisStand, DIRECTION_LENGTH, RED);
        drawLine(longArmDirection, axisShortArm, DIRECTION_LENGTH, GREEN);
        drawLine(handDirection, rightHand, DIRECTION_LENGTH, YELLOW);
        drawLine(handMove, rightHand, DIRECTION_LENGTH, PINK);
    }
}

void RobotArm::drawRobotHand()
{
    drawMissingCylinder(handRadius, handHeight, handThickness, leftHand, handDirection, WHITE, leftHandAngleStart, leftHandAngleEnd);
    drawMissingCylinder(handRadius, handHeight, handThickness, rightHand, handDirection, WHITE, rightHandAngleStart, rightHandAngleEnd);

}

void RobotArm::test()
{
}

void RobotArm::drawRobotStand()
{
    drawBox(standLength, standWidth, standHeight, robotDirectionXYZ, leftStand, WHITE);
    drawBox(standLength, standWidth, standHeight, robotDirectionXYZ, rightStand, WHITE);
    drawBoxOutline(standLength, standWidth, standHeight, robotDirectionXYZ, leftStand, DARK_BLUE);
    drawBoxOutline(standLength, standWidth, standHeight, robotDirectionXYZ, rightStand, DARK_BLUE);
    drawCylinderWithCaps(axisRadius, axisHeight, axisRadius, axisStand, robotDirectionXY_Horizontal, WHITE);
    drawCylinderOutline(axisRadius, axisHeight, axisStand, robotDirectionXY_Horizontal, DARK_BLUE);
    drawCylinderOutline(axisRadius, axisHeight-0.9, axisStand, robotDirectionXY_Horizontal, DARK_BLUE);
}

void RobotArm::drawRobotBase()
{
    drawCylinderWithCaps(baseLeg_Radius, baseLeg_Height, baseLeg_Radius, centerBaseLeg, normalBase, baseLeg_Color);
    drawCylinderOutline(baseLeg_Radius, baseLeg_Height, centerBaseLeg, normalBase, baseLeg_OutlineColor);
    drawCylinderWithCaps(baseBody_Radius, baseBody_Height, baseBody_Radius, centerBaseBody, normalBase, baseBody_Color);
    drawCylinderOutline(baseBody_Radius, baseBody_Height, centerBaseBody, normalBase, baseBody_OutlineColor);
    drawCylinderWithCaps(baseHead_Radius, baseHead_Height, baseHead_Radius, centerBaseHead, normalBase, baseHead_Color);
    drawCylinderOutline(baseHead_Radius, baseHead_Height, centerBaseLeg, normalBase, baseHead_OutlineColor);

}

void RobotArm::checkMinValueAngle()
{
    if(angleZ < ANGLEZ_MIN) angleZ = ANGLEZ_MIN;
    if(angleShortArm < ANGLESHORTARM_MIN) angleShortArm = ANGLESHORTARM_MIN;
    if(angleLongArm < ANGLELONGARM_MIN) angleLongArm = ANGLELONGARM_MIN;
}

void RobotArm::checkMaxValueAngle()
{
    if(angleZ > ANGLEZ_MAX) angleZ = ANGLEZ_MAX;
    if(angleShortArm > ANGLESHORTARM_MAX) angleShortArm = ANGLESHORTARM_MAX;
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

void RobotArm::changeStatusShowDirection()
{
    showDirection = !showDirection;
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
            return angleShortArm;
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
            return shortArmDirection;
        case LONGARM:
            return longArmDirection;
    }
}

void RobotArm::rotateAngle(TypeAngle angle, float rotate)
{
    switch (angle)
    {
    case ANGLE_X:
        angleX += rotate;
        break;
    case ANGLE_Z:
        angleZ += rotate;
        break;
    case ANGLE_SHORT_ARM:
        angleShortArm += rotate;
        break;
    case ANGLE_LONG_ARM:
        angleLongArm += rotate;
        break;
    default:
        break;
    }
}