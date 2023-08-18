#include "GL/freeglut.h"
#include <vector>
#include <iostream>
#include "./numbers.cpp"
#include <chrono>
using namespace std;
vector<double> x;
vector<double> y;
vector<int> count;

using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::seconds;


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	auto t1 = high_resolution_clock::now();
	for (int i = 0; i < x.size(); i++)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(count[i], count[i], count[i]);
		glVertex2f(i / (width), i % (height));
		
	}
	auto t2 = high_resolution_clock::now();
	duration<double> ms_double = t2 - t1;

	glEnd();
	glFlush();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, height, 0, width, -3.0, 3.0);
}
double cumm_zoom = 1;
double zoom = 1.2;
void print(int i)
{
	auto t1 = high_resolution_clock::now();
	x.clear();
	y.clear();
	count.clear();
	max_x /= zoom;
	max_y /= zoom;
	cumm_zoom *= zoom;
	gen_num(&x, &y, &count);
	glColor3f(1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	auto t2 = high_resolution_clock::now();
	for (int i = 0; i < count.size(); i++)
	{
		
		glColor3f(((count[i])) %255, ((count[i])-400) % 255, ((count[i])-800) %255);
		glVertex2f(i / (width), i % height);
	}

	glEnd();
	glFlush();
	auto t3 = high_resolution_clock::now();
	duration<double> ms_double = t3 - t1;

	glutTimerFunc(0, print, 0);
}

void click(int i, int j, int x, int y)
{
	if (j == 0 || j == 2)
	{
		glutTimerFunc(0, print, 0);
		return;
	}
	
	glutTimerFunc(0, print, 0);

}
bool pause = true;


int main(int argc, char **argv)
{

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(height, width);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Points");

	auto t1 = high_resolution_clock::now();
	gen_num(&x, &y, &count);
	auto t2 = high_resolution_clock::now();
	duration<double> ms_double = t2 - t1;
	glutDisplayFunc(display);
	glutTimerFunc(0, print, 0);
	
	init();
	glutMainLoop();
}