#include <stdio.h>  
#define GLUT_DISABLE_ATEXIT_HACK  
#include <gl/glut.h>  
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "Pol.h"


static Pol curr;
int cur_pointer;
std::vector<Pol> list_of_pols;


void divide() {
	if (list_of_pols.size()>cur_pointer+1) {
		cur_pointer++;
		curr = list_of_pols[cur_pointer];
		std::cout <<"New len : "<< cur_pointer << " "<< list_of_pols.size() << std::endl;
	}
	else {
		std::vector<Vertex> ver;
		float new_len = curr.len / 3;
		Vertex temp;
		int count=0;
		for (std::vector<Edges>::iterator i = curr.edge.begin(); i != curr.edge.end(); i++)
		{
			count++;
			Edges e = *i;
			
			if(e.orientation == 'a') {

				temp.v = e.first;
				ver.push_back(temp);

				temp.v.x = e.first.x;
				temp.v.y = e.first.y - new_len;
				ver.push_back(temp);

				temp.v.x = e.first.x + new_len;
				temp.v.y = e.first.y -new_len;
				ver.push_back(temp);

				temp.v.x = e.first.x + new_len;
				temp.v.y = e.first.y - 2*new_len;
				ver.push_back(temp);

				temp.v.x = e.first.x;
				temp.v.y = e.first.y - 2*new_len;
				ver.push_back(temp);

				

			}
			else if (e.orientation == 'b') {
				temp.v = e.first;
				ver.push_back(temp);

				temp.v.x = e.first.x -new_len;
				temp.v.y = e.first.y;
				ver.push_back(temp);

				temp.v.x = e.first.x - new_len;
				temp.v.y = e.first.y - new_len;
				ver.push_back(temp);

				temp.v.x = e.first.x - 2*new_len;
				temp.v.y = e.first.y - new_len;
				ver.push_back(temp);

				temp.v.x = e.first.x -2*new_len;
				temp.v.y = e.first.y;
				ver.push_back(temp);

			
			}
			else if (e.orientation == 'c') {
				temp.v = e.first;
				ver.push_back(temp);

				temp.v.x = e.first.x;
				temp.v.y = e.first.y + new_len;
				ver.push_back(temp);

				temp.v.x = e.first.x - new_len;
				temp.v.y = e.first.y + new_len;
				ver.push_back(temp);

				temp.v.x = e.first.x - new_len;
				temp.v.y = e.first.y + 2 * new_len;
				ver.push_back(temp);

				temp.v.x = e.first.x;
				temp.v.y = e.first.y + 2 * new_len;
				ver.push_back(temp);

				
			}
			else {
				temp.v = e.first;
				ver.push_back(temp);

				temp.v.x = e.first.x + new_len;
				temp.v.y = e.first.y;
				ver.push_back(temp);

				temp.v.x = e.first.x + new_len;
				temp.v.y = e.first.y + new_len;
				ver.push_back(temp);

				temp.v.x = e.first.x + 2*new_len;
				temp.v.y = e.first.y + new_len;
				ver.push_back(temp);

				temp.v.x = e.first.x +2*new_len;
				temp.v.y = e.first.y;
				ver.push_back(temp);

				
			}
			
		}
		//std::cout << count << std::endl;
		Pol div(ver, new_len);
		list_of_pols.push_back(div);
		curr = list_of_pols.back();
		cur_pointer++;
		//std::cout <<"New len : "<< curr.len << " " << std::endl;
	}
	
}
void back() {
	if (cur_pointer != 0) {
		cur_pointer--;
		curr = list_of_pols[cur_pointer];
		std::cout << "This is len : " << curr.len << std::endl;
	}
	else {
		std::cout << "You've reaches a square" << std::endl;
	}
}
void keys(unsigned char key, int x, int y) {
	switch (key)
	{
	case '+': divide();
		break;
	case '-': back();
		break;
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_LINE_LOOP);
	for (std::vector<Edges>::iterator i = curr.edge.begin(); i != curr.edge.end(); ++i)
	{
		//std::cout << "BOOOM" << std::endl;
		Edges e = *i;
		glVertex2d(e.first.x, e.first.y);
		glVertex2d(e.second.x, e.second.y);
	}
	glEnd();
	glutPostRedisplay();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	GLfloat nRange = 2.0f;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		glOrtho(-nRange, nRange, -nRange * aspect, nRange * aspect, -nRange, nRange);
	}
	else
	{
		glOrtho(-nRange, nRange, -nRange / aspect, nRange / aspect, -nRange, nRange);
	}
}

void init()
{
	list_of_pols.push_back(curr);
	cur_pointer++;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("OpenGL Cube");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	glutMainLoop();
}
