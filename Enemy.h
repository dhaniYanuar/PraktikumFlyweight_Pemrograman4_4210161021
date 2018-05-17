#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <string>
#include <sstream>
#include <cstring>
#include <time.h>
#define Pi 3.14159265f
using namespace std;

class Enemy {
private :
	GLfloat xSpeed = 0.01f, ySpeed= 1.0f;
	GLfloat ballradius = 0.2f;
	GLfloat ballX = 0.50f,ballY = 0.0f;
public :
	Enemy();
	void createEnemy(float x, float color);
};
