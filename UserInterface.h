#include <GL/glut.h>
#include <memory>
#include <vector>
#include "Config.h"
#include "Utils.h"

using namespace std;

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

class UIElemet
{
	public:
	UIElemet();
	~UIElemet();
	
};

class Button
{
	public:
	Button();
	~Button();
	private:
};

class UIManager
{
	public:
	UIManager();
	~UIManager();
	void draw2DUI();

	private:

};

#endif
