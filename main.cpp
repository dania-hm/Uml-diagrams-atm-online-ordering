// GLUT 3D shapes
// lab 9

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <glut.h>
#define ROT_INC    0.1

void drawSphere(void);

static GLfloat g_rotate = 0;
static GLfloat g_rotInc = ROT_INC;
static void (*drawPrimP)(void) = drawSphere;

void drawSphere(void)
{
    glutWireSphere(6.0, 20, 20);
}

void drawCube(void)
{
    glutWireCube(6.0);
}

void drawCone(void)
{
    glutWireCone(6.0, 8.0, 30, 20);
}

void drawTorus(void)
{
    glutWireTorus(1.0, 6.0, 10, 20);
}

void drawTeapot(void)
{
    glutWireTeapot(6.0);
}

void setPrim(int value)
{
    switch (value)
    {
    case 1:
        drawPrimP = drawSphere;
        break;
    case 2:
        drawPrimP = drawCube;
        break;
    case 3:
        drawPrimP = drawCone;
        break;
    case 4:
        drawPrimP = drawTorus;
        break;
    case 5:
        drawPrimP = drawTeapot;
        break;
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    /* set matrix mode to modelview */
    glMatrixMode(GL_MODELVIEW);

    /* save matrix */
    glPushMatrix();

    /* global rotation */
    glRotatef(g_rotate, 1.0, 1.0, 1.0);

    /* draw the geometry */
    (*drawPrimP)();

    /* restore matrix */
    glPopMatrix();

    /* swap buffers to display the frame */
    glutSwapBuffers();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* perspective parameters: field of view, aspect, near clip, far clip */
    gluPerspective(60.0, (GLdouble)w / (GLdouble)h, 0.1, 40.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 20.0, /* eye at (0,0,20) */
              0.0, 0.0, 0.0, /* lookat point */
              0.0, 1.0, 0.0); /* up is in positive y */
}

void myKey(unsigned char k, int x, int y)
{
    switch (k)
    {
    case 'q':
    case 'Q':
        exit(0);
        break;
    default:
        printf("Unknown keyboard command \'%c\'.\n", k);
        break;
    }
}

void myMouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        g_rotInc += ROT_INC;

    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        g_rotInc = ROT_INC;

    glutPostRedisplay();
}

void myIdleFunc(void)
{
    g_rotate += g_rotInc;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Shapes Test");

    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(myIdleFunc);
    glutKeyboardFunc(myKey);
    glutMouseFunc(myMouse);

    /* set up right menu */
    glutCreateMenu(setPrim);
    glutAddMenuEntry("Sphere", 1);
    glutAddMenuEntry("Cube", 2);
    glutAddMenuEntry("Cone", 3);
    glutAddMenuEntry("Torus", 4);
    glutAddMenuEntry("Teapot", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    /* set clear colour */
    glClearColor(1.0, 1.0, 1.0, 1.0);

    /* set current colour to black */
    glColor3f(0.0, 0.0, 0.0);

    glutMainLoop();
    return 0;
}
