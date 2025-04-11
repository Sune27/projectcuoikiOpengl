#include "UserInterface.h"

using namespace std;

UI::UI()
{
    cout << "Constructor UI class" << endl;
}
void UI::draw2DUI()
{
	// Lưu lại projection matrix và modelview matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0); // Thiết lập orthographic projection
  
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
  
	// Vẽ các thành phần UI 2D
	glColor3f(1.0f, 1.0f, 1.0f); // Màu trắng
	glBegin(GL_QUADS);
		glVertex2f(10, 10);
		glVertex2f(10 + 100, 10);
		glVertex2f(10 + 100, 10 + 50);
		glVertex2f(10, 10 + 50);
	glEnd();
  
	// Khôi phục projection matrix và modelview matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

UI::~UI()
{
    cout << "Destructor UI class" << endl;
}
