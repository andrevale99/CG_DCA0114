#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "entidades.h"

#define FPS_FRAME 30

//=========================================================
//  VARIAVEIS
//=========================================================
struct Camera camera;
struct Esfera obj;

//=========================================================
//  PROTOTIPOS
//=========================================================
void init(void);
void display(void);
void reshape(int w, int h);
void getKeyboard(unsigned char key, int x, int y);
void TimerFunc(int value);

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
    glutKeyboardFunc(getKeyboard);
    glutTimerFunc(1000 / FPS_FRAME, TimerFunc, 0);

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
    camera.angle_alpha = camera.angle_beta = camera.angle_gamma = 0.;

    obj.posx = obj.posy = obj.posz = 0.;
    obj.raio = 1.0;
    obj.slices = 10;
    obj.stacks = 20;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(camera.eyex, camera.eyey, camera.eyez,          // Posição da câmera
              camera.centerx, camera.centery, camera.centerz, // Centro da cena
              camera.upx, camera.upy, camera.upz);            // Direção "up"

    glRotated(camera.angle_alpha, 1, 0, 0);
    glRotated(camera.angle_beta, 0, 1, 0);
    glRotated(camera.angle_gamma, 0, 0, 1);

    {
        glPushMatrix();
        glTranslated(obj.posx, obj.posy, obj.posz);
        glutWireSphere(obj.raio, obj.slices, obj.stacks);
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
}

void getKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
        exit(0);
        break;

    case 'W':
        camera.angle_beta += 0.2;
        break;

    case 'w':
        camera.angle_beta -= 0.2;
        break;

    case 'A':
        camera.angle_alpha += 0.2;

        break;

    case 'a':
        camera.angle_alpha -= 0.2;
        break;

    case GLUT_KEY_RIGHT:
        camera.angle_gamma += 0.2;
        break;

    case GLUT_KEY_LEFT:
        camera.angle_gamma -= 0.2;
        break;

    default:
        break;
    }
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS_FRAME, TimerFunc, 0);
}