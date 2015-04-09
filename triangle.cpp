#if(0)
#include <windows.h>
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

bool iCull = false;
bool iDepth = false;
bool iOutline = false;

void ProcessMenu(int value)
{
    switch (value)
    {
    case 1:
        iCull = !iCull;
        break;
    case 2:
        iDepth = !iDepth;
        break;
    case 3:
        iOutline = !iOutline;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);  // 플렛 쉐이딩
    glFrontFace(GL_CW);     // 시계방향이 앞면
}
void RenderScene(void)
{
    GLfloat x, y, angle;
    int iPivot = 1;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

#define EX 2
#if (EX == 1)
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(25.0f, 25.0f);
    glVertex2f(50.0f, 0.0f);
    glVertex2f(-50.0f, 0.0f);
    glVertex2f(-75.0f, 50.0f);
    glVertex2f(-25.0f, 0.0f);
    glEnd();
#endif
#if(EX == 2)
    if (iCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
    if (iDepth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
    if (iOutline)
        glPolygonMode(GL_BACK, GL_LINE);
    else
        glPolygonMode(GL_BACK, GL_FILL);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 75.0f);  // 기준점
    for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
    {
        x = 50.0f*sin(angle);
        y = 50.0f*cos(angle);
        if ((iPivot % 2) == 0)
            glColor3f(0.0f, 1.0f, 0.0f);
        else
            glColor3f(1.0f, 0.0f, 0.0f);
        iPivot++;
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);  // 기준점
    for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
    {
        x = 50.0f*sin(angle);
        y = 50.0f*cos(angle);
        if ((iPivot % 2) == 0)
            glColor3f(0.0f, 1.0f, 0.0f);
        else
            glColor3f(1.0f, 0.0f, 0.0f);
        iPivot++;
        glVertex2f(x, y);
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
    GLfloat nRange = 100.0f;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, nRange, -nRange);
    else
        glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, nRange, -nRange);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(void)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Triangle");
    
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("은면 제거", 1);
    glutAddMenuEntry("깊이 테스트", 2);
    glutAddMenuEntry("뒷면 라인 그리기", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(KeyControl);
    SetupRC();
    glutMainLoop();
}
#endif