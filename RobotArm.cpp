#include "RobotArm.h"

using namespace std;

RobotArm::RobotArm()
{
    //set value
    normalBase.setValue(0,0,1);
    centerBaseLeg.setValue(0, 0, 0);
    centerBaseBody.setValue(0, 0, 0.5);
    centerBaseHead.setValue(0, 0, 1.0);
    centerContainer.setValue(10,0,4);
    
    robotDirectionXY_Vertical.vertical(angleX);
    robotDirectionXY_Horizontal.horizontal(robotDirectionXY_Vertical);
    containerDirection.setValue(robotDirectionXY_Horizontal.arr[0], robotDirectionXY_Horizontal.arr[1], robotDirectionXY_Horizontal.arr[2]);
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
    leftShortArm = axisStand;
    rightShortArm = axisStand;
    axisShortArm = axisStand;

    leftShortArm.move(shortArmDirection, shortArmDistanceVertical);
    rightShortArm.move(shortArmDirection, shortArmDistanceVertical);
    axisShortArm.move(shortArmDirection, axisShortArmDistance);
    leftShortArm.move(robotDirectionXY_Horizontal, shortArmDistanceHorizontal);
    rightShortArm.move(robotDirectionXY_Horizontal, -shortArmDistanceHorizontal);

    //longarm
    leftLongArm = axisShortArm;
    rightLongArm = axisShortArm;
    wrist = axisShortArm;
    leftLongArm.move(longArmDirection, longArmDistanceVertical);
    rightLongArm.move(longArmDirection, longArmDistanceVertical);
    leftLongArm.move(robotDirectionXY_Horizontal, longArmDistanceHorizontal);
    rightLongArm.move(robotDirectionXY_Horizontal, -longArmDistanceHorizontal);
    wrist.move(longArmDirection, wristDistance);

    //hand
    leftHand = wrist;
    rightHand = wrist;
    centerHand = wrist;
    leftHand.move(longArmDirection, handDistanceVertical);
    rightHand.move(longArmDirection, handDistanceVertical);
    centerHand.move(longArmDirection, handDistanceVertical);
    leftHand.move(handMove, handDistanceHorizontal);
    rightHand.move(handMove, -handDistanceHorizontal);

}

//done
void RobotArm::drawRobotShortArm()
{
    drawBox(shortArmLength, shortArmWidth, shortArmHeight, shortArmDirection, leftShortArm, shortArm_Color);
    drawBox(shortArmLength, shortArmWidth, shortArmHeight, shortArmDirection, rightShortArm, shortArm_Color);
    drawBoxOutline(shortArmLength, shortArmWidth, shortArmHeight, shortArmDirection, leftShortArm, shortArm_OutlineColor);
    drawBoxOutline(shortArmLength, shortArmWidth, shortArmHeight, shortArmDirection, rightShortArm, shortArm_OutlineColor);
    drawCylinderWithCaps(axisShortArmRadius, axisShortArmHeight, axisShortArmRadius, axisShortArm, robotDirectionXY_Horizontal, axisShortArm_Color);
    drawCylinderOutline(axisShortArmRadius, axisShortArmHeightOutside, axisShortArm, robotDirectionXY_Horizontal, axisShortArm_OutlineColor);
    drawCylinderOutline(axisShortArmRadius, axisShortArmHeightInside, axisShortArm, robotDirectionXY_Horizontal, axisShortArm_OutlineColor);

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
    drawContainer();
    test();
}

//done
void RobotArm::drawRobotLongArm()
{
    drawBox(longArmLength, longArmWidth, longArmHeight, longArmDirection, leftLongArm, longArm_Color);
    drawBox(longArmLength, longArmWidth, longArmHeight, longArmDirection, rightLongArm, longArm_Color);
    drawBoxOutline(longArmLength, longArmWidth, longArmHeight, longArmDirection, leftLongArm, longArm_OutlineColor);
    drawBoxOutline(longArmLength, longArmWidth, longArmHeight, longArmDirection, rightLongArm, longArm_OutlineColor);
    drawCylinderWithCaps(wristRadius, wristHeight, wristRadius, wrist, longArmDirection, wrist_Color);
    drawCylinderOutline(wristRadius, wristHeight, wrist, longArmDirection, wrist_OutlineColor);
}

void RobotArm::drawContainer()
{
    drawBox(containerLength, containerLength, containerLength, containerDirection, centerContainer, containerColor);
    drawBoxOutline(containerLength, containerLength, containerLength, containerDirection, centerContainer, containerOutlineColor);
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
        drawLine(handDirection, centerHand, DIRECTION_LENGTH, YELLOW);
        drawLine(handMove, centerHand, DIRECTION_LENGTH, PINK);
    }
}

//done
void RobotArm::drawRobotHand()
{
    if(isHandOpen == true)
    {
        drawMissingCylinder(handRadius, handHeight, handThickness, leftHand, handDirection, hand_Color, leftHandAngleStart_Open, leftHandAngleEnd_Open);
        drawMissingCylinder(handRadius, handHeight, handThickness, rightHand, handDirection, hand_Color, rightHandAngleStart_Open, rightHandAngleEnd_Open);
        drawMissingCylinderOutline(handRadius, handHeight, leftHand, handDirection, hand_OutlineColor, leftHandAngleStart_Open, leftHandAngleEnd_Open);
        drawMissingCylinderOutline(handRadius, handHeight, rightHand, handDirection, hand_OutlineColor, rightHandAngleStart_Open, rightHandAngleEnd_Open);
    }
    else 
    {
        drawMissingCylinder(handRadius, handHeight, handThickness, leftHand, handDirection, hand_Color, leftHandAngleStart_Close, leftHandAngleEnd_Close);
        drawMissingCylinder(handRadius, handHeight, handThickness, rightHand, handDirection, hand_Color, rightHandAngleStart_Close, rightHandAngleEnd_Close);
        drawMissingCylinderOutline(handRadius, handHeight, leftHand, handDirection, hand_OutlineColor, leftHandAngleStart_Close, leftHandAngleEnd_Close);
        drawMissingCylinderOutline(handRadius, handHeight, rightHand, handDirection, hand_OutlineColor, rightHandAngleStart_Close, rightHandAngleEnd_Close);
    }
}

void RobotArm::test()
{
}

void RobotArm::changeStatus(TypeStatus status)
{
    switch(status)
    {
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

//done
void RobotArm::drawRobotStand()
{
    drawBox(standLength, standWidth, standHeight, robotDirectionXYZ, leftStand, stand_Color);
    drawBox(standLength, standWidth, standHeight, robotDirectionXYZ, rightStand, stand_Color);
    drawBoxOutline(standLength, standWidth, standHeight, robotDirectionXYZ, leftStand, stand_OutlineColor);
    drawBoxOutline(standLength, standWidth, standHeight, robotDirectionXYZ, rightStand, stand_OutlineColor);
    drawCylinderWithCaps(axisRadius, axisHeight, axisRadius, axisStand, robotDirectionXY_Horizontal,axisStand_Color);
    drawCylinderOutline(axisRadius, axisHeightOutside, axisStand, robotDirectionXY_Horizontal, axisStand_Outlinecolor);
    drawCylinderOutline(axisRadius, axisHeightInside, axisStand, robotDirectionXY_Horizontal, axisStand_Outlinecolor);
}

//done
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
