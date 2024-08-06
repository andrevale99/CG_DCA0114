#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "entidades.h"

#define ESC_KEY 27

//=================================================
// VARIAVEIS
//=================================================

static int year = 0, day = 0;

// Variavel para manipular o basico
// da janela principal
static struct Window window = {
    .width = 640,
    .height = 480,
    .posx = 500,
    .posy = 500,

    .name = "Planeta",
};

static GLfloat iluminacao[] = {0, 5.0, 0};
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess[] = {50.0};

static struct Camera camera = {0};

static struct Planeta planetas[2]; 

// @brief Variavel para calcular o tempo percorrido
//
// @note A primeira posicao eh o mais recente e o segundo
// eh o anterior
static int deltaTime[] = {0, 0};

// Estrutura para manipulacao de arquivos
FILE arq;
//=================================================
// PROTOTIPOS
//=================================================

// @brief Funcao de initicialização
void init(void);

// @brief Callback para desenhar os objetos
void display(void);

// @brief Callback para refazer a janela e as perspectivas
// do programa
//
// @param w Largura da janela (width)
// @param h Altura da janela (height)
void reshape(int w, int h);

// @brief Callback para capturar os eventos do teclado
//
// @param key Tecla pressionada
// @param x Posicao 'x' o qual o mouse pressionou
// @param y Posicao 'y' o qual o mouse pressionou
void keyboard(unsigned char key, int x, int y);

// @brief Callback que ira realizar as coisas
// enquanto nao houver eventos
void idle(void);

// @brief configracao inicial dos planetas
void set_planetas(void);

// @brief Passagem de parametros ao executar o arquivo
//
// @param argc Quantidade de parametros
// @param *argv[] Valores (em char** ou char *[]) dos parametros
void Arg_parse(const int argc, char *argv[]);

//=================================================
// MAIN
//=================================================
int main(int argc, char **argv)
{
   Arg_parse(argc, argv);

   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

   glutInitWindowSize(window.width, window.height);
   glutInitWindowPosition(100, 100);

   glutCreateWindow(window.name);

   init();

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(idle);

   glutMainLoop();

   return 0;
}

//=============================================
// FUNCOES
//=============================================
void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);

   camera.eyex = 0.;
   camera.eyey = 5.;
   camera.eyez = 10.;
   camera.upy = 1.0;

   glShadeModel(GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, iluminacao);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

   set_planetas();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3f(1.0, 1.0, 1.0);

   glPushMatrix();

   glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
   glTranslatef(planetas[1].x, planetas[1].y, planetas[1].z);
   // glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
   glutSolidSphere(planetas[1].esfera.raio, planetas[1].esfera.slices, planetas[1].esfera.stacks); /* draw smaller planet */
   
   glPopMatrix();

   // Sol criado na origem do mundo
   glPushMatrix();
   
   glTranslatef(planetas[0].x, planetas[0].y, planetas[0].z);
   glutSolidSphere(planetas[0].esfera.raio, planetas[0].esfera.slices, planetas[0].esfera.stacks); /* draw sun */
   
   glPopMatrix();   

   glLoadIdentity();
   gluLookAt(camera.eyex, camera.eyey, camera.eyez,
             camera.centerx, camera.centery, camera.centerz,
             camera.upx, camera.upy, camera.upz);

   glPopMatrix();

   glutSwapBuffers();
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

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 'd':
      day = (day + 10) % 360;
      break;
   case 'D':
      day = (day - 10) % 360;
      break;

   case '+':
      camera.eyez = camera.eyez + 0.5;
      break;

   case '-':
      camera.eyez = camera.eyez - 0.5;
      break;

   case ESC_KEY:
      exit(0);
      break;

   default:
      break;
   }
}

void idle(void)
{
   deltaTime[0] = glutGet(GLUT_ELAPSED_TIME);

   if ((deltaTime[0] - deltaTime[1]) > 100)
   {
      year = (year + 5) % 360;
      glutPostRedisplay();

      deltaTime[1] = deltaTime[0];
   }
}

void set_planetas(void)
{

   planetas[0].esfera.raio = 1.0;
   planetas[0].esfera.slices = 20;
   planetas[0].esfera.stacks = 16;
   planetas[0].x = 0.;
   planetas[0].y = 0.;
   planetas[0].z = 0.;
   planetas[0].velocidade_x = 0.;
   planetas[0].velocidade_y = 0.;

   planetas[1].esfera.raio = .2;
   planetas[1].esfera.slices = 10;
   planetas[1].esfera.stacks = 8;
   planetas[1].x = 3.0;
   planetas[1].y = 0.;
   planetas[1].z = 0.;
   planetas[1].velocidade_x = 0.;
   planetas[1].velocidade_y = 2 * PI;
}

void Arg_parse(const int argc, char *argv[])
{
   if (argc == 2 && (strcmp(argv[1], "--help") == 0))
   {
      printf("\n Usage: ./Planeta.out [OPTIONS...] \n\n"
             "--help \t Mensagem de ajuda do programa\n"
             "-w \t Largura da Janela [default=%d]\n"
             "-h \t Altura da Janela [default=%d]\n"
             "\n",
             window.width, window.height);

      exit(0);
   }
   else
   {
      int idx = 1;
      for (idx = 1; idx < argc; ++idx)
      {
         if (strcmp(argv[idx], "-w") == 0)
            window.width = atoi(argv[++idx]);

         if (strcmp(argv[idx], "-h") == 0)
            window.height = atoi(argv[++idx]);
      }
   }
}