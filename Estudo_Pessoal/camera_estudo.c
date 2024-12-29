#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <math.h>

#include "entidades.h"

#define FPS_FRAME 30

//=========================================================
//  VARIAVEIS
//=========================================================
struct Camera camera;
struct Mouse mouse;

struct Esfera esfera = {
    .posx = 0.,
    .posy = 0.,
    .posz = 0.,

    .raio = 0.5,
    .slices = 10,
    .stacks = 10,
};
//=========================================================
//  PROTOTIPOS
//=========================================================
void init(void);
void display(void);
void reshape(int w, int h);
void getMousePos(int x, int y);
void getKeyboard(unsigned char key, int x, int y);
void timer(int value);

//=========================================================
//  MAIN
//=========================================================
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
//=========================================================
//  FUNCOES
//=========================================================
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // Define a cor de fundo como preto
    glEnable(GL_DEPTH_TEST);          // Habilita teste de profundidade

    camera.eyex = camera.eyey = 0.0;
    camera.eyez = 5.;

    camera.centerx = camera.centery = camera.centerz = 0.0;

    camera.upx = camera.upz = 0.0;
    camera.upy = 1.0;
    camera.angle = 0.;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // Aplica transformações da câmera
    gluLookAt(camera.eyex, camera.eyey, camera.eyez,          // Posição da câmera
              camera.centerx, camera.centery, camera.centerz, // Centro da cena
              camera.upx, camera.upy, camera.upz);            // Direção "up"

    glRotated(camera.angle, 0, 1, 0);

    {
        glPushMatrix();
        // Desenha o cubo
        glutWireCube(1.0);

        glTranslated(3., 0., 0.);
        glutWireCube(0.25);

        glPopMatrix();
    }
    {
        glPushMatrix();

        glTranslated(esfera.posx, esfera.posy, esfera.posz);
        glutWireSphere(esfera.raio, esfera.slices, esfera.stacks);

        glPopMatrix();
    }

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, .001, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glTranslated(0., 0., 0.); // Coloca a camera o 0 global
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
        camera.eyez = 0.5;
        break;
    default:
        break;
    }
}

void timer(int value)
{
    camera.angle += 1;
    if (camera.angle >= 360.)
        camera.angle -= 360.;

    glutPostRedisplay();
    glutTimerFunc(1000 / FPS_FRAME, timer, 0);
}