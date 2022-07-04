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
	void make(int radius);
	GLuint get();
};

class ShapeObj
{
};
class RectangleObj
{
private:
	int cradius;
	GLuint g_obj;
public:

	void make(const float length, const float width, const float height);
	GLuint get();
};
