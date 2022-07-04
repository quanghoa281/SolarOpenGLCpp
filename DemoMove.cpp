#include <Windows.h>
#include<math.h>
#include "SphereObj.h"

SphereObj g_sun;
RectangleObj g_box;
GLuint g_xyz;


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

    //gluLookAt(5.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    gluLookAt(5, 5, 5, 0, 1.0, 0, 0.0, 1.0, 0.0);
    glCallList(g_xyz);

    glTranslated(0.0, 2.0, 0.0);

    GLfloat mat_ambien[] = { 1.0, 1.0, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambien);
    GLfloat diff[] = { 05, 0.5, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);

    glCallList(g_sun.get());

    
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

    g_sun.make(1.0);
    g_box.make(8, 2, 0.2);
    g_xyz = DrawXYZ();
}
void main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Opengl Solar System");

    Init();
    glutReshapeFunc(ReShape);
    glutDisplayFunc(RendenScene);
   /* glutSpecialFunc(OnKeyDown);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);*/

    glutMainLoop();

}