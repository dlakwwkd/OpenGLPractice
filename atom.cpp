#if(1)
#include <windows.h>
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void RenderScene(void)
{
    static GLfloat fElect1 = 0.0f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    glTranslatef(0.0f, 0.0f, -10.0f);
    glColor3f(255, 0, 0);
    glutSolidSphere(10.0f, 15.0f, 15.0f);

    glPushMatrix();
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    glTranslatef(50.0f, 0.0f, 0.0f);
    glColor3ub(255, 255, 0);
    glutSolidSphere(3.0f, 15.0f, 15.0f);

    glPushMatrix();
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    glTranslatef(-30.0f, 0.0f, 0.0f);
    glColor3ub(0, 255, 0);
    glutSolidSphere(3.0f, 15.0f, 15.0f);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 20.0f);
    glColor3ub(0, 0, 255);
    glutSolidSphere(3.0f, 15.0f, 15.0f);
    glPopMatrix();

    fElect1 += 10.0f;
    if (fElect1 > 360.0f)
        fElect1 = 0.0f;

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
    GLfloat nRange = 100.0f;
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
    glutCreateWindow("Atom");

    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33, TimerFunc, 1);
    glutSpecialFunc(KeyControl);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
}
#endif