#pragma once
#include <gl\glut.h>

class SphereObj
{
private:
	int cradius;
	GLuint g_obj;
public:
	/*SphereObj(int radius)
	: cradius(radius)
	{
	}*/
	void makeSphere(int radius);
	GLuint getObj();
};

class ShapeObj
{
};
