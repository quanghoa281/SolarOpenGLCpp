#include "SphereObj.h"

void SphereObj::make(int radius)
{
	cradius = (radius);
	g_obj = glGenLists(1);
	glNewList(g_obj, GL_COMPILE);
	glutSolidSphere(cradius, 64, 16);
	glEndList();
	return ;
}

GLuint SphereObj::get()
{
	return g_obj;
}

void RectangleObj::make(const float length, const float width, const float height)
{
	g_obj = glGenLists(1);
	glNewList(g_obj, GL_COMPILE);
	float x = length;
	float y = height;
	float z = width;

	//Back
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(x, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(0, y, 0);
	glEnd();

	// left
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, z);
	glVertex3f(0, y, z);
	glVertex3f(0, y, 0);
	glEnd();

	//front
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, z);
	glVertex3f(0, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, 0, z);
	glEnd();

	//// right
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x, 0, z);
	glVertex3f(x, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x, y, z);
	glEnd();

	//Top
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, y, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x, y, z);
	glVertex3f(0, y, z);

	//Bottom
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(x, 0, 0);
	glVertex3f(x, 0, z);
	glVertex3f(0, 0, z);

	glEnd();

	glEndList();

}

GLuint RectangleObj::get()
{
	return g_obj;
}
