#include "Enemy.h"
using namespace std;

Enemy::Enemy(){
	
}

void Enemy::createEnemy(float x, float color){
	glPushMatrix();
	glTranslatef(x,ySpeed,0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(color,0,color);
    glVertex2f(0.0f,0.0f);
    int numSegment = 100;
    GLfloat angle;
    for(int i = 0; i<=numSegment; i++)
    {
        angle = i * 1.0f * Pi / numSegment;
        glVertex2f(cos(angle)*ballradius,sin(angle)*ballradius);
    }
    glEnd();
    ballY += ySpeed;
    glPopMatrix();
}
