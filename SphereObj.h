#pragma once
#include <gl\glut.h>

class SphereObj
{
private:
	int cradius;
public:
	SphereObj(int radius)
	: cradius(radius)
	{
	}
	GLuint MakeSphere()
	{
		GLuint boxDisplay;
		boxDisplay = glGenLists(1);
		glNewList(boxDisplay, GL_COMPILE);
		glutSolidSphere(cradius, 64, 16);
		glEndList();
		return boxDisplay;
	}
};

