
#include <gl\glut.h>
#include <math.h>
#include <stdio.h>


float g_x = 0.0;
float g_z = 0.0;
float lz = 0;
float lx = 0.0;
float angle = 0.0;

float deltaAngle = 0.0f;
int xOrigin = -1;
bool g_is_rotate = false;

void Init()
{
    g_x = 0 * sin(angle);
    g_z = 0 * cos(angle);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = { 0.0, 0.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

    GLfloat diff_use[] = { 0.7, 0.7, 0.7, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

    GLfloat shininess = 50.0f;
    glMateriali(GL_FRONT, GL_SHININESS, shininess);

}

void ReShape(int width, int height)
{
    glViewport(0, 0, width, height);
    float ratio = (float)width / (float)height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ratio, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void OnKeyDown(int key, int xx, int yy) {
    switch (key)
    {
    case GLUT_KEY_LEFT:
        g_x -= 0.3;
        break;
    case GLUT_KEY_RIGHT:
        g_x += 0.3;
        break;
    case GLUT_KEY_UP:
        g_z -= 0.3;
        break;
    case GLUT_KEY_DOWN:
        g_z += 0.3;
        break;
    }
}

void mouseButton(int button, int state, int x, int y)
{
    // only start motion if the left button is pressed
    if (button == GLUT_RIGHT_BUTTON)
    {
        // when the button is released
        if (state == GLUT_UP)
        {
            angle += deltaAngle;
            xOrigin = -3;
            g_is_rotate = false;
        }
        else
        {
            g_is_rotate = true;
            deltaAngle = 0.0;
            xOrigin = x;
        }
    }
}

void mouseMove(int x, int y)
{
    //if (g_is_rotate)
    {
        // this will only be true when the left button is down
        //deltaAngle += (x - xOrigin) * 0.0005f;
        // update camera's direction
        //g_x = 10 * sin(angle + deltaAngle);
        //g_z = 10 * cos(angle + deltaAngle);
        if (lx > x) {
            g_x += 0.5;
        }
        else {
            g_x -= 0.5;
        }
        if (lz > y) {
            g_z += 0.5;
        }
        else {
            g_z -= 0.5;
        }
        lx = x;
        lz = y;
        printf("x = %d , y = %d , g_x = %f, g_z = %f \n", x, y, g_x, g_z);
    }

}


void DrawCoordinate()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-100.0, 0.0, 0.0);
    glVertex3f(100.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -100.0, 0.0);
    glVertex3f(0.0, 100.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -100.0);
    glVertex3f(0.0, 0.0, 100.0);
    glEnd();
    glEnable(GL_LIGHTING);
}

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(8, 1.0, 8, g_x, 1.0, g_z, 0, 1, 0);
    DrawCoordinate();

    glPushMatrix();
    glutSolidTeapot(1.0);
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

void main()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Opengl Study");
    Init();
    glutReshapeFunc(ReShape);
    glutDisplayFunc(RenderScene);
    glutIdleFunc(RenderScene);
    glutSpecialFunc(OnKeyDown);
    glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mouseMove);
    //glutMotionFunc(mouseMove);
    glutMainLoop();

    return;
}