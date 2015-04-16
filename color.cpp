#if(0)
#include <windows.h>
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

struct Vertex
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

#define EX 2
#if(EX == 1)
    glBegin(GL_TRIANGLES);
    glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
    glVertex3f(0.0f, 200.0f, 0.0f);

    glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
    glVertex3f(200.0f, -70.0f, 0.0f);

    glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
    glVertex3f(-200.0f, -70.0f, 0.0f);
    glEnd();
#endif
#if(EX == 2)
    Vertex vertex[8];
    vertex[0] = { 0, 0, 0 };
    vertex[1] = { 0, 100, 0 };
    vertex[2] = { 100, 100, 0 };
    vertex[3] = { 100, 0, 0 };
    vertex[4] = { 0, 0, 100 };
    vertex[5] = { 0, 100, 100 };
    vertex[6] = { 100, 100, 100 };
    vertex[7] = { 100, 0, 100 };
    glBegin(GL_QUADS);
    glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
    for (int i = 0; i < 4; ++i)
    {
        glVertex3f(vertex[i].x, vertex[i].y, vertex[i].z);
    }

    glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
    glVertex3f(vertex[0].x, vertex[0].y, vertex[0].z);
    glVertex3f(vertex[3].x, vertex[3].y, vertex[3].z);
    glVertex3f(vertex[7].x, vertex[7].y, vertex[7].z);
    glVertex3f(vertex[4].x, vertex[4].y, vertex[4].z);

    glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
    glVertex3f(vertex[6].x, vertex[6].y, vertex[6].z);
    glVertex3f(vertex[7].x, vertex[7].y, vertex[7].z);
    glVertex3f(vertex[3].x, vertex[3].y, vertex[3].z);
    glVertex3f(vertex[2].x, vertex[2].y, vertex[2].z);

    glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
    glVertex3f(vertex[5].x, vertex[5].y, vertex[5].z);
    glVertex3f(vertex[6].x, vertex[6].y, vertex[6].z);
    glVertex3f(vertex[2].x, vertex[2].y, vertex[2].z);
    glVertex3f(vertex[1].x, vertex[1].y, vertex[1].z);

    glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
    glVertex3f(vertex[4].x, vertex[4].y, vertex[4].z);
    glVertex3f(vertex[5].x, vertex[5].y, vertex[5].z);
    glVertex3f(vertex[1].x, vertex[1].y, vertex[1].z);
    glVertex3f(vertex[0].x, vertex[0].y, vertex[0].z);

    glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
    for (int i = 7; i > 3; --i)
    {
        glVertex3f(vertex[i].x, vertex[i].y, vertex[i].z);
    }
    glEnd();
#endif

    glPopMatrix();
    glutSwapBuffers();
}

void KeyControl(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        xRot -= 5.0f;
    if (key == GLUT_KEY_DOWN)
        xRot += 5.0f;
    if (key == GLUT_KEY_LEFT)
        yRot -= 5.0f;
    if (key == GLUT_KEY_RIGHT)
        yRot += 5.0f;
    glutPostRedisplay();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLfloat nRange = 300.0f;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, nRange*2.0f, -nRange*2.0f);
    else
        glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, nRange*2.0f, -nRange*2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(void)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Color");

    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(KeyControl);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
}
#endif