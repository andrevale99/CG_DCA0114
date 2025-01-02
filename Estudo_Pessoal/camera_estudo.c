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
    .pos[0] = 0.,
    .pos[1] = 0.,
    .pos[2] = 0.,

    .raio = 0.5,
    .slices = 10,
    .stacks = 10,
};

float points[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
float colors[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};

float speed = 1.;
float angle = 0;
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

    camera.eyex = 0.0;
    camera.eyey = 0.0;
    camera.eyez = 2.5;

    camera.centerx = camera.centery = camera.centerz = 0.0;

    camera.upx = camera.upz = 0.0;
    camera.upy = 1.0;
    camera.angle_alpha = camera.angle_beta = camera.angle_gamma = 0.;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // Aplica transformações da câmera
    gluLookAt(camera.eyex, camera.eyey, camera.eyez,          // Posição da câmera
              camera.centerx, camera.centery, camera.centerz, // Centro da cena
              camera.upx, camera.upy, camera.upz);            // Direção "up"

    glRotatef(camera.angle_beta, 0,1,1);

    {
        glPushMatrix();

        glTranslatef(0, 0, 0);
        glLineWidth(2.);
        glBegin(GL_LINES);
        for (uint8_t i = 0; i < 9; i += 3)
        {
            glColor3f(colors[i], colors[i + 1], colors[i + 2]);
            glVertex3f(0,0,0);
            glVertex3f(points[i], points[i + 1], points[i + 2]);
        }
        glEnd();

        glPopMatrix();
    }

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.01, 50.);
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
    case 27:
        exit(0);
    default:
        break;
    }
}

void timer(int value)
{
    camera.angle_beta += cos(2)*speed;
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS_FRAME, timer, 0);
}