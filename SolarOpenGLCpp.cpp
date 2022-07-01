#include <Windows.h>
#include<math.h>
#include "SphereObj.h"

#define DEBUG 0
#define PI 3.14

#if DEBUG
SphereObj g_sun;
SphereObj g_earth;
//SphereObj g_moon;
#else

GLuint g_sun;
GLuint g_earth;
GLuint g_moon;
GLuint g_xyz;

#endif 

GLuint g_angle_day = 0;
GLuint g_angle_year = 0;
GLuint gl_angle_moon = 0;


GLuint MakeSphere(const float& radius)
{
    GLuint boxDisplay;
    boxDisplay = glGenLists(1);
    glNewList(boxDisplay, GL_COMPILE);
    glutSolidSphere(radius, 64, 16);
    glEndList();
    return boxDisplay;
}
void drawHollowCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius) {
    int i;
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_LINE_LOOP);
    for (i = 0; i <= lineAmount; i++) {
        glVertex3f(
            x + (radius * cos(i * twicePi / lineAmount)),
            y,
            z + (radius * sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}
GLuint DrawXYZ()
{
    GLuint boxDisplay;
    boxDisplay = glGenLists(1);
    glNewList(boxDisplay, GL_COMPILE);

    glColor3f(1, 0, 0);
    glBegin(GL_LINES); // X red
    glVertex3f(10.0, 0.0, 0.0);
    glVertex3f(-10.0, 0.0, 0.0);
    glEnd();

    glColor3f(0, 1, 1);
    glBegin(GL_LINES); // Y yallow
    glVertex3f(0.0, 10.0, 0.0);
    glVertex3f(0.0, -10.0, 0.0);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_LINES); // Z blue
    glVertex3f(0.0, 0.0, 10.0);
    glVertex3f(0.0, 0.0, -10.0);
    glEnd();

    glBegin(GL_POINTS);
    glPointSize(3.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();


    glEndList();
    return boxDisplay;
}


void RendenScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //glCallList(g_xyz);

    glTranslated(0.0, 2.0, 0.0);

    GLfloat mat_ambien[] = { 1.0, 1.0, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambien);
    GLfloat diff[] = { 05, 0.5, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
    drawHollowCircle(0, -1, 0, 8);
    glRotatef(g_angle_year, 0.0f, 1.0f, 0.0f);
    glCallList(g_sun);

    glTranslated(8.0, 0.0, 0.0);
    glRotatef(g_angle_day, 0.0f, 1.0f, 0.0f);

    GLfloat mat_ambien2[] = { 0.0, 0.0, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambien2);
    GLfloat diff2[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff2);
    glCallList(g_earth);

    drawHollowCircle(0, -0.25, 0, 2);

    glRotatef(gl_angle_moon, 0.0f, 1.0f, 0.0f);
    glTranslated(2.0, 0.0, 0.0);

    GLfloat mat_ambien3[] = { 0.7, 0.7, 0.7f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambien3);
    GLfloat diff3[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff3);
    glCallList(g_moon);

    Sleep(83);
    gl_angle_moon = (gl_angle_moon + 13);
    if (gl_angle_moon >= 360)
    {
        gl_angle_moon = 0;
    }

    g_angle_day = (g_angle_day + 360);
    if (g_angle_day >= 360)
    {
        g_angle_day = 0;
    }

    g_angle_year = (g_angle_year + 1);
    if (g_angle_year >= 360)
    {
        g_angle_year = 0;
    }

    glutSwapBuffers();
    glFlush();

    glutPostRedisplay();
}
void ReShape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float ratio = (float)width / (float)height;
    gluPerspective(45.0, ratio, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat ambient[] = { 1.0, 1.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

    GLfloat diff_use[] = { 0.5, 0.5, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

    GLfloat shininess = 50.0f;
    glMateriali(GL_FRONT, GL_SHININESS, shininess);
#if DEBUG
    g_sun.makeSphere(2.0);
    g_earth.makeSphere(1.0);
    //g_moon.makeSphere(0.2);
#else
    g_sun = MakeSphere(2.0);
    g_earth = MakeSphere(1.0);
    g_moon = MakeSphere(0.2);
#endif
    g_xyz = DrawXYZ();
}
void main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Opengl Solar System");

    Init();
    glutReshapeFunc(ReShape);
    glutDisplayFunc(RendenScene);

    glutMainLoop();

}