#include "GL/freeglut.h"
#include <vector>
#include <iostream>
#include "./numbers.cpp"
#include <chrono>
#include <thread>

using namespace std;

using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::seconds;



void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, height, 0, width, -3.0, 3.0);
}
int count = 0;
void display(int k)
{
	if(displaying)
	{
	auto t1 = high_resolution_clock::now();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);


	while(frame_queue[count%num_threads]->size()==0);
	if(frame_queue[count%num_threads]->front()->size() < width*height)
	exit(0);
	for (int i = 0; i < frame_queue[count%num_threads]->front()->size(); i++)
	{
		glColor3f((*(frame_queue[count%num_threads]->front()->at(i)))%255 , ((*(frame_queue[count%num_threads]->front()->at(i))-400)%255), ((*(frame_queue[count%num_threads]->front()->at(i))-800)%255));
		glVertex2f(i / (width), i % height);
	}

	glEnd();
	glFlush();
	//delete frame_queue[count%8]->front();
	frame_queue[count%num_threads]->pop();
	count++;
	auto t2 = high_resolution_clock::now();
	duration<double> ms_double = t2-t1;
	//cout << "FPS : "<< 1/ms_double.count()<< endl;
	glutTimerFunc(0, display, 0);
	}
	else{
		//cout << "end"<< endl;
	}
}

int main(int argc, char **argv)
{
	fill_max();
    queue<vector<int*>*>* q1 = new queue<vector<int*>*>;
    frame_queue.push_back(q1);
    thread t1(loop,0);
    
        queue<vector<int*>*>* q2 = new queue<vector<int*>*>;
    frame_queue.push_back(q2);
    thread t2(loop,1);

        queue<vector<int*>*>* q3 = new queue<vector<int*>*>;
    frame_queue.push_back(q3);
    thread t3(loop,2);

        queue<vector<int*>*>* q4 = new queue<vector<int*>*>;
    frame_queue.push_back(q4);
    thread t4(loop,3);

        queue<vector<int*>*>* q5 = new queue<vector<int*>*>;
    frame_queue.push_back(q5);
    thread t5(loop,4);

        queue<vector<int*>*>* q6 = new queue<vector<int*>*>;
    frame_queue.push_back(q6);
    thread t6(loop,5);

     queue<vector<int*>*>* q7 = new queue<vector<int*>*>;
    frame_queue.push_back(q7);
    thread t7(loop,6);

    //  queue<vector<int*>*>* q8 = new queue<vector<int*>*>;
    // frame_queue.push_back(q8);
    // thread t8(loop,7);
	std::this_thread::sleep_for(15s);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(height, width);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Points");

	glutTimerFunc(0, display, 0);
	
	init();
	glutMainLoop();
}