
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/glut.h>

#include "Car.h"

// g++ main2.cpp  -o main2 -lGL -lGLU -lglut

void road();
void signal();
void mydisplay();
void display();
void frontsreen();
void drawstring();
void setFont();
void update();
void control();
void moveLeft();
void moveRight();

GLint a = 300, b = -300, flag = 0, speed = 0;
GLfloat red = 0, green = .5, blue = 1;

GLfloat p = 1, q = 0, r = 0; // p = red, q = yellow, r = green

Car rayo;
Car rayoStart;
Car route66;
Car light;
Car tree;

int count_speed = 0;

//-----------
void *currentfont;

void setFont(void *font)
{
	currentfont = font;
}

void drawstring(float x, float y, float z, char *string) //writing function
{
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++)
	{
		glColor3f(1, 1, 1);
		glutBitmapCharacter(currentfont, *c);
	}
}

void frontscreen(void)
{
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glClearColor(0.15, 0.1, 0.01, 0); /*background for cover page*/
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	rayoStart.carStart();
	glColor3f(1.0, 1.0, 1.0);
	drawstring(543, 100, 0.0, "PRESS ENTER TO START");
	glFlush();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 13:
		if (flag == 1)
		{
			mydisplay();
		}
		if (flag == 0) //Ascii of 'enter' key is 13
		{
			flag = 1;
			mydisplay();
		}
		break;
	case 's':
		if (flag == 1)
		{
			speed = 1;
			;
		}
		break;

	default:
		break;
	}
}

void spKey(int key, int x, int y)
{
	switch (key)
	{

	case GLUT_KEY_RIGHT:
		flag = 1;
		moveLeft();
		break;
	case GLUT_KEY_LEFT:
		flag = 1;
		moveRight();
		break;
	default:
		break;
	}
}

void mydisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (flag == 0)
		frontscreen();
	if (flag == 1)
		display();
	glutSwapBuffers();
}

void update(int value)
{
	if (count_speed == 10 || count_speed == 70 || count_speed == 130)
	{
		p = 0;
		q = 1;
		r = 0;
	}
	else if (count_speed == 12 || count_speed == 72 || count_speed == 172)
	{
		p = 0;
		q = 0;
		r = 1;
	}
	if (count_speed % 60 == 0)
	{
		a = 200, b = -300;
		p = 1;
		q = 0;
		r = 0;
	}

	count_speed++;
	if (speed = 1)
	{
		a = a - 18;
		b = b + 18;
		speed = 0;
	}
	a = a - 6;
	b = b + 6;
	glutPostRedisplay();
}

void updateRight(int value)
{
	if (count_speed == 10 || count_speed == 70 || count_speed == 130)
	{
		p = 0;
		q = 1;
		r = 0;
	}
	else if (count_speed == 12 || count_speed == 72 || count_speed == 172)
	{
		p = 0;
		q = 0;
		r = 1;
	}
	if (count_speed % 60 == 0)
	{
		a = 200, b = -300;
		p = 1;
		q = 0;
		r = 0;
	}
	count_speed--;
	if (speed = 1)
	{
		a = a + 18;
		b = b - 18;
		speed = 0;
	}
	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(red, green, blue, 0); /*back ground for sky*/
	route66.road();
	light.signal(p, q, r);
	rayo.drawCar(b, 1.0, 0.0); // red
	tree.tree();

	glPushMatrix();
	glTranslated(-700, 0, 0);
	tree.tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(250, 100, 0);
	rayo.drawCar(b, 0.0, 1.7);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	drawstring(543, 100, 0.0, "Press the arrows to move.");

	glFlush();
}

void moveLeft(void)
{
	glutTimerFunc(50, update, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(red, green, blue, 0); /*back ground for sky*/
	tree.tree();
	route66.road();
	light.signal(p, q, r);
	rayo.drawCar(b, 1.0, 0.0);

	glFlush();
}

void moveRight(void)
{
	glutTimerFunc(50, updateRight, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(red, green, blue, 0); /*back ground for sky*/
	tree.tree();
	route66.road();
	light.signal(p, q, r);

	rayo.drawCar(b, 1.0, 0.0);

	glFlush();
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1346.0, 0.0, 728.0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1346, 728);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Car on the road");

	/*call back functions*/
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(spKey);
	myinit();
	glutMainLoop();
}