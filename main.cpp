#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <string>
#include <sstream>
#include <cstring>
#include <time.h>
#include "Factory.h"
#define Pi 3.14159265f
/*
*/
using namespace std;
char title[] = "Car (2D)";
//ukuran layar window
int windowWidth = 480;
int windowHeight = 567;
//posisi window
int windowPosX = 0;
int windowPosY = 0;

int refreshMilis = 30;
//screen are
GLfloat clipAreaXLeft, clipAreaXRight,clipAreaYbuttom,clipAreaYtop;
//ball variable
GLfloat ballradius = 0.2f;
GLfloat ballX = 0.50f,ballY = 0.0f;
GLfloat ballXmax, ballYmax, ballXmin, ballYmin;
GLfloat xSpeed = 0.01f, ySpeed= 1.0f;
GLfloat moveX;
//gravitasi
GLfloat gravity = -9.8;

bool first = true;
float pos = 0.50f;
const GLfloat e = 0.8f;
int score;

Factory myFactory;



void init()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);
}

void print(string _string)
{
    glRasterPos2f(0,0);
    int i;
    int len = _string.length();
    for(i=0;i<len;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,_string[i]);
    }
}

void collision()
{
    GLfloat dist;
    GLfloat x1,x2,y1,y2;
    GLfloat dx = moveX - ballX;
    GLfloat dy = (-0.7) - ballY;
    x1 = fabs(dx);
    y1 = fabs(dy);
    x2 = pow(x1,2);
    y2 = pow(y1,2);
    dist = sqrt(x2+y2);
    if(dist <= 0.2)
    {
        ySpeed=0;
    }
}

void CreateBall(float x)
{
    glTranslatef(x,ySpeed,0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f,1.0f,0.0f);
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
}

void createBalok(float positiony)
{
    glTranslatef(moveX,positiony,0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f,1.0f,1.0f);
    glVertex2f(0.2,0.05);
    glVertex2f(-0.2,0.05);
    glVertex2f(-0.2,-0.05);
    glVertex2f(0.2,-0.05);
    glEnd();
}

void display()
{
    int position[] = {5,-5};
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    createBalok(-0.7);
    glPopMatrix();
    float last = pos;
    if(ballY < ballYmin){

        int ran = rand() % 2;
        pos = position[ran]*0.1;
        while(last == pos){
            ran = rand() % 5;
            pos = position[ran]*0.1;
        }
        ySpeed = 1.5f;
    }
    CreateBall(pos);
    myFactory.createMore();
    glPushMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

void resharp(GLsizei width, GLsizei height)
{
    if(height == 0)
        height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(width >= height)
    {
        clipAreaXLeft = -1.0f * aspect;
        clipAreaXRight = 1.0f * aspect;
        clipAreaYbuttom = -1.0;
        clipAreaYtop = 1.0;
    }
    else{
        clipAreaXLeft = -1.0f;
        clipAreaXRight = 1.0f;
        clipAreaYbuttom = -1.0 / aspect;
        clipAreaYtop = 1.0/ aspect;
    }
    gluOrtho2D(clipAreaXLeft,clipAreaXRight,clipAreaYbuttom,clipAreaYtop);
    ballXmin = clipAreaXLeft + ballradius;
    ballXmax = clipAreaXRight - ballradius;
    ballYmin = clipAreaYbuttom + ballradius;
    ballYmax = clipAreaYtop - ballradius;
}

void Timer(int value)
{
    glutPostRedisplay();
    ySpeed += gravity * 0.1 /15;
    glutTimerFunc(refreshMilis,Timer,0);
}

void keyboard(unsigned char key,int x,int y)
{
    if(key == 'a')
        moveX = -0.50f;
    else if(key == 'd')
        moveX = 0.50f;
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(windowPosX,windowPosY);
    glutCreateWindow(title);
    glutDisplayFunc(display);
    glutReshapeFunc(resharp);
    glutTimerFunc(0,Timer,0);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
