#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>

#include "entidades.h"

struct Camera camera;
struct Mouse mouse;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

    for (uint8_t i = 0; i < 3; ++i)
        *(&camera.centerx + i * sizeof(GLdouble)) = 0.;

    camera.eyez = 10;

    camera.upx = camera.upz = 0.;
    camera.upy = 1.;

    for (uint8_t i = 0; i < 6; i++)
        *(&mouse.x + i * sizeof(int)) = 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity(); /* clear the matrix */
                      /* viewing transformation  */

    gluLookAt(camera.eyex, camera.eyey, camera.eyez,
              camera.centerx, camera.centery, camera.centerz,
              camera.upx, camera.upy, camera.upz);

    glScalef(1.0, 1.0, 1.0); /* modeling transformation */
    glutWireCube(1.0);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(camera.eyex, camera.eyey, camera.eyez,
              camera.centerx, camera.centery, camera.centerz,
              camera.upx, camera.upy, camera.upz);
}

void getMousePos(int x, int y)
{
    mouse.x = x;
    mouse.y = y;

    printf("%d\t%d\n", mouse.x, mouse.y);
    printf("*%d\t%d\n\n", mouse.old_x, mouse.old_y);

    if (mouse.x < mouse.old_x)
        camera.eyez = camera.eyez - 0.5;

    else
        camera.eyez = camera.eyez + 0.5;

    mouse.old_x = mouse.x;
    mouse.old_y = mouse.y;

    glutPostRedisplay();
}

void getKeyboard(uint8_t key, int x, int y)
{
    switch (key)
    {
    case 'q':
        exit(0);
        break;

    case 'r':
    camera.eyez = 10;
    camera.eyex = camera.eyey = 0;
    glutPostRedisplay();
    break;

    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(getMousePos);
    glutKeyboardFunc(getKeyboard);

    glutMainLoop();

    return EXIT_SUCCESS;
}
