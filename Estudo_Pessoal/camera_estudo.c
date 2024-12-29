#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "entidades.h"

#define FPS_FRAME 30

struct Camera camera;
struct Mouse mouse;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // Define a cor de fundo como preto
    glEnable(GL_DEPTH_TEST);          // Habilita teste de profundidade

    camera.eyex = camera.eyey = 0.0;
    camera.eyez = 5.0;

    camera.centerx = camera.centery = camera.centerz = 0.0;

    camera.upx = camera.upz = 0.0;
    camera.upy = 1.0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // Aplica transformações da câmera
    glTranslatef(0.0, 0.0, -camera.eyez);
    glRotated(camera.angle, 0, 1, 0);
              
    // Desenha o cubo
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
}

void getMousePos(int x, int y)
{
    mouse.x = x;
    if (mouse.x < mouse.old_x)
        camera.eyez += 0.5;
    else
        camera.eyez -= 0.5;

    mouse.old_x = mouse.x;
}

void getKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
        exit(0);
    case 'r':
        camera.eyez = 5.0;
        break;
    case '+':
        camera.eyez += 0.5;
        break;
    case '-':
        camera.eyez -= 0.5;
        break;
    default:
        break;
    }
}

void timer(int value)
{
    camera.angle += 1;
    if (camera.angle >= 360)
        camera.angle -= 360;

    glutPostRedisplay();
    glutTimerFunc(1000 / FPS_FRAME, timer, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(getMousePos);
    glutKeyboardFunc(getKeyboard);
    glutTimerFunc(1000 / FPS_FRAME, timer, 0);

    glutMainLoop();

    return 0;
}
