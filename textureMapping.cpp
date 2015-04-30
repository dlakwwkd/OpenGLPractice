#if(1)
#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include "lodepng.h"

#define GL_PI 3.14159f
#define TEX_NUM 2

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;

GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat dif[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat lightPos[] = { -50.0f, 50.0f, 100.0f, 1.0f };

GLuint texID[TEX_NUM];

void SetupRC(void)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
}

void LoadTexture()
{
    std::vector<unsigned char> image;
    unsigned int width, height, error;

    glGenTextures(TEX_NUM, texID);

    error = lodepng::decode(image, width, height, "texture.png");
    if (error)
        printf("error %u: %s\n", error, lodepng_error_text(error));
    printf("\nimage size is %i", image.size());

    glBindTexture(GL_TEXTURE_2D, texID[0]);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

    image.clear();
    error = lodepng::decode(image, width, height, "texture2.png");
    if (error)
        printf("error %u: %s\n", error, lodepng_error_text(error));
    printf("\nimage2 size is %i", image.size());

    glBindTexture(GL_TEXTURE_2D, texID[1]);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    {
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, zDistance);

        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);

        glColor3f(1.0f, 1.0f, 1.0f);

        glPushMatrix();
        {
            glTranslatef(-7.0f, 0.0f, 0.0f);
            glBindTexture(GL_TEXTURE_2D, texID[0]);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glutSolidTeapot(5.0f);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(+7.0f, 0.0f, 0.0f);
            glBindTexture(GL_TEXTURE_2D, texID[1]);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
            glutSolidTeapot(5.0f);
        }
        glPopMatrix();
    }
    glPopMatrix();

    glutSwapBuffers();
}

void KeyControl(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)     xRot -= 5.0f;
    if (key == GLUT_KEY_DOWN)   xRot += 5.0f;
    if (key == GLUT_KEY_LEFT)   yRot -= 5.0f;
    if (key == GLUT_KEY_RIGHT)  yRot += 5.0f;
    if (key == GLUT_KEY_F1)     zDistance += 5.0f;
    if (key == GLUT_KEY_F2)     zDistance -= 5.0f;
    glutPostRedisplay();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLfloat fAspect = (GLfloat)w / (GLfloat)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, fAspect, 1.0f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -50.0f);
}

void NormalkeyInput(unsigned char key, int x, int y)
{
    if (key == 'q') exit(-1);
}

int main(void)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("2D Texture");
        glutKeyboardFunc(NormalkeyInput);
    glutSpecialFunc(KeyControl);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    
    SetupRC();
        LoadTexture();
    
    glutMainLoop();
}
#endif