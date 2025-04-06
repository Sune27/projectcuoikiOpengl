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

void RobotArm::printAttributes()
{
    cout << __TIME__ << endl;
    cout << "angleX: " << angleX << endl;
    cout << "angleZ: " << angleZ << endl;
    cout << "angleShortArm: " << angleShortArm << endl;
    cout << "angleLongArm: " << angleLongArm << endl;
}

void RobotArm::update()
{
    //vector
    robotDirectionXY_Vertical.vertical(angleX);
    robotDirectionXY_Horizontal.horizontal(robotDirectionXY_Vertical);
    VectorRotationMethod(robotDirectionXYZ, robotDirectionXY_Vertical, angleZ);
    shortArmDirection.rotateAroundZAxis(robotDirectionXYZ, angleShortArm);
    longArmDirection.rotateAroundZAxis(robotDirectionXYZ, angleLongArm);

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
    drawDirection();
    drawRobotBase();
    drawRobotStand();
    drawRobotShortArm();
}

void RobotArm::drawDirection()
{
    glLineWidth(LINE_WIDTH);
    
    drawLine(robotDirectionXY_Vertical, centerBaseHead, DIRECTION_LENGTH, PURPLE);
    drawLine(robotDirectionXY_Horizontal, centerBaseHead, DIRECTION_LENGTH, BLUE);
    //drawLine(robotDirectionXYZ, centerBaseHead, DIRECTION_LENGTH, DARK_GREEN);
    drawLine(shortArmDirection, axisStand, DIRECTION_LENGTH, RED);
    drawLine(longArmDirection, axisShortArm, DIRECTION_LENGTH, GREEN);
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