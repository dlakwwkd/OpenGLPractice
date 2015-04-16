#if(1)
#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include "GLEXT.H"
#include "gltools.h"

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;

void DrawJet()
{
    GLTVector3 vNormal;	// Storeage for calculated surface normal (glTools.h)

    glColor3ub(128, 128, 128);

    glBegin(GL_TRIANGLES);

    //front bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 60.0f);
    glVertex3f(-15.0f, 0.0f, 30.0f);
    glVertex3f(15.0f,0.0f,30.0f);

    //Right Winng
    GLTVector3 vPoints[3] = { { 15.0f, 0.0f, 30.0f },
    { 0.0f, 15.0f, 30.0f },
    { 0.0f, 0.0f, 60.0f } };

    // Calculate the normal for the plane
    gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal); //(glTools.h)

    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);

    {
        GLTVector3 vPoints[3] = { { 0.0f, 0.0f, 60.0f },
        { 0.0f, 15.0f, 30.0f },
        { -15.0f, 0.0f, 30.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }


    // Body of the Plane ////////////////////////
    {
        GLTVector3 vPoints[3] = { { -15.0f, 0.0f, 30.0f },
        { 0.0f, 15.0f, 30.0f },
        { 0.0f, 0.0f, -56.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }

    {
        GLTVector3 vPoints[3] = { { 0.0f, 0.0f, -56.0f },
        { 0.0f, 15.0f, 30.0f },
        { 15.0f, 0.0f, 30.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }


    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(15.0f, 0.0f, 30.0f);
    glVertex3f(-15.0f, 0.0f, 30.0f);
    glVertex3f(0.0f, 0.0f, -56.0f);

    ///////////////////////////////////////////////
    // Left wing
    // Large triangle for bottom of wing
    {
        GLTVector3 vPoints[3] = { { 0.0f, 2.0f, 27.0f },
        { -60.0f, 2.0f, -8.0f },
        { 60.0f, 2.0f, -8.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }


    {
        GLTVector3 vPoints[3] = { { 60.0f, 2.0f, -8.0f },
        { 0.0f, 7.0f, -8.0f },
        { 0.0f, 2.0f, 27.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }

    {
        GLTVector3 vPoints[3] = { { 60.0f, 2.0f, -8.0f },
        { -60.0f, 2.0f, -8.0f },
        { 0.0f, 7.0f, -8.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }

    {
        GLTVector3 vPoints[3] = { { 0.0f, 2.0f, 27.0f },
        { 0.0f, 7.0f, -8.0f },
        { -60.0f, 2.0f, -8.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }


    // Tail section///////////////////////////////
    // Bottom of back fin
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-30.0f, -0.50f, -57.0f);
    glVertex3f(30.0f, -0.50f, -57.0f);
    glVertex3f(0.0f, -0.50f, -40.0f);

    {
        GLTVector3 vPoints[3] = { { 0.0f, -0.5f, -40.0f },
        { 30.0f, -0.5f, -57.0f },
        { 0.0f, 4.0f, -57.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }


    {
        GLTVector3 vPoints[3] = { { 0.0f, 4.0f, -57.0f },
        { -30.0f, -0.5f, -57.0f },
        { 0.0f, -0.5f, -40.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }


    {
        GLTVector3 vPoints[3] = { { 30.0f, -0.5f, -57.0f },
        { -30.0f, -0.5f, -57.0f },
        { 0.0f, 4.0f, -57.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }

    {
        GLTVector3 vPoints[3] = { { 0.0f, 0.5f, -40.0f },
        { 3.0f, 0.5f, -57.0f },
        { 0.0f, 25.0f, -65.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }

    {
        GLTVector3 vPoints[3] = { { 0.0f, 25.0f, -65.0f },
        { -3.0f, 0.5f, -57.0f },
        { 0.0f, 0.5f, -40.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }

    {
        GLTVector3 vPoints[3] = { { 3.0f, 0.5f, -57.0f },
        { -3.0f, 0.5f, -57.0f },
        { 0.0f, 25.0f, -65.0f } };

        gltGetNormalVector(vPoints[0], vPoints[1], vPoints[2], vNormal);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
    }


    glEnd();
}

void SetupRC(void)
{
    GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPos[] = { 0.0f, 0.0f, 75.0f, 1.0f };
    GLfloat spotDir[] = { 0.0f, 0.0f, -1.0f};
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glFrontFace(GL_CCW);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, zDistance);

    DrawJet();

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
    if (key == GLUT_KEY_F1)
        zDistance += 5.0f;
    if (key == GLUT_KEY_F2)
        zDistance -= 5.0f;
    glutPostRedisplay();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLfloat fAspect = (GLfloat)w / (GLfloat)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, fAspect, 1.0f, 255.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -150.0f);
}

int main(void)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Light Jet");

    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(KeyControl);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
}
#endif