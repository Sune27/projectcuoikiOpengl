#include "UserInterface.h"

using namespace std;

Button::Button(){}
void Button::setValue(float x, float y, float width, float height, Color background, Color textColor)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->background = background;
	this->textColor = textColor;
}
void Button::draw(const char* text)
{
	drawButton(x, y, width, height, background, textColor, text);
}

UIManager::UIManager()
{
    cout << "Constructor UI class" << endl;
	exitButton.setValue
	(
		10, 10, 100, 100,
		RED, BLACK
	);
	userManualButton.setValue
	(
		200, 200, 100, 100,
		DARK_BLUE, WHITE
	);
}
void UIManager::draw2DUI()
{
	glDisable(GL_DEPTH_TEST);
	// Lưu lại projection matrix và modelview matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0); // Thiết lập orthographic projection
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
  
	// Vẽ các thành phần UI 2D
	exitButton.draw("EXIT");
	userManualButton.draw("User Manual");
  
	// Khôi phục projection matrix và modelview matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
}

UIManager::~UIManager()
{
    cout << "Destructor UI class" << endl;
}
Button::~Button(){}
