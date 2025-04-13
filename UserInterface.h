#include <GL/glut.h>
#include "Config.h"
#include "Utils.h"

using namespace std;

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H


class Button
{
public:
	Button();
	~Button();
	void setValue(float, float, float, float, Color, Color, Color);
	void draw(const char* text);
	bool isMouseLeftOver(int mouseX, int mouseY) const;
	bool isMousseRightOver(int mouseX, int mouseY) const;
private:
	float x, y, width, height;
	Color background;
	Color backgroundHover;
	Color textColor;
};

class UIManager
{
public:
	UIManager();
	~UIManager();
	void draw2DUI();
	void mouseLeftClicked(int mouseX, int mouseY);
	void exitButtonLeftClicked();

private:
	Button exitButton;
	Button userManualButton;
	Button leftArrow;
	Button rightArrow;
};

#endif
