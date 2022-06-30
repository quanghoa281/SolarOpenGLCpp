#include "SphereObj.h"

void SphereObj::makeSphere(int radius)
{
	cradius = (radius);
	g_obj = glGenLists(1);
	glNewList(g_obj, GL_COMPILE);
	glutSolidSphere(cradius, 64, 16);
	glEndList();
	return ;
}

GLuint SphereObj::getObj()
{
	return g_obj;
}
