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
	Button(string, float, float, float, float, Color, Color);
	~Button();
	void setValue(float, float, float, float, Color, Color);
	void draw(const char* text);
private:
	float x, y, width, height;
	Color background;
	Color textColor;
};

class UIManager
{
public:
	UIManager();
	~UIManager();
	void draw2DUI();

private:
	Button exitButton;
	Button userManualButton;
};

#endif
