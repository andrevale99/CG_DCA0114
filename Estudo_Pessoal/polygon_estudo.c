#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>

#include "entidades.h"

#define FPS_FRAME 30

// nao coloque mais de 80
#define N_POINTS 4

//=========================================================
//  VARIAVEIS
//=========================================================

struct Camera camera;

float points[N_POINTS*3] = {0};

GLuint vbo;
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
    camera.angle_alpha = camera.angle_beta =
        camera.angle_gamma = 0.;

    float degree = 0;
    float r = 2;
    for (uint8_t i = 0; i < N_POINTS * 3; i += 3)
    {
        points[i] = cos(degree * PI / 180.) * r;
        points[i + 1] = sin(degree * PI / 180.) * r;
        points[i + 2] = 0;

        degree += 360. / (N_POINTS);

    }

    // Gera e vincula um VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Copia os dados dos pontos para o VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Desvincula o VBO (opcional)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(camera.eyex, camera.eyey, camera.eyez,          // Posição da câmera
              camera.centerx, camera.centery, camera.centerz, // Centro da cena
              camera.upx, camera.upy, camera.upz);            // Direção "up"

    glRotatef(camera.angle_beta, 0, 0, 1);
    // Habilita o uso do VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Configura o ponteiro de vértices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0); // Cada vértice tem 3 floats (x, y, z)

    // Desenha os pontos
    glPointSize(5.0f);              // Tamanho dos pontos
    glDrawArrays(GL_LINE_LOOP, 0, N_POINTS); // Desenha 30 pontos a partir do índice 0

    // Desabilita o ponteiro de vértices
    glDisableClientState(GL_VERTEX_ARRAY);

    // Desvincula o VBO (opcional)
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers(); // Troca os buffers para exibir a cena

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

    default:
        break;
    }
}

void TimerFunc(int value)
{
    // camera.angle_beta += sin(2) * 1.5;
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS_FRAME, TimerFunc, 0);
}