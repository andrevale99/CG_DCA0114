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

static struct Planeta sol = {0};
static struct Planeta mercurio = {0};
static struct Planeta venus = {0};
static struct Planeta terra = {0};
static struct Planeta marte = {0};
static struct Planeta jupiter = {0};
static struct Planeta saturno = {0};
static struct Planeta urano = {0};
static struct Planeta netuno = {0};

// @brief Variavel para calcular o tempo percorrido
//
// @note O primeiro index eh o mais recente e o segundo
// eh o antigo
static int deltaTime[] = {0, 0};
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
   glTranslatef(mercurio.x, mercurio.y, mercurio.z);
   // glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
   glutSolidSphere(mercurio.esfera.raio, mercurio.esfera.slices, mercurio.esfera.stacks); /* draw smaller planet */
   
   glPopMatrix();

   glPushMatrix();

   glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
   glTranslatef(venus.x, venus.y, venus.z);
   glutSolidSphere(venus.esfera.raio, venus.esfera.slices, venus.esfera.stacks); /* draw smaller planet */
   
   glPopMatrix();

   // Sol criado na origem do mundo
   glPushMatrix();
   
   glTranslatef(sol.x, sol.y, sol.z);
   glutSolidSphere(sol.esfera.raio, sol.esfera.slices, sol.esfera.stacks); /* draw sun */
   
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
      glutPostRedisplay();
      break;
   case 'D':
      day = (day - 10) % 360;
      glutPostRedisplay();
      break;

   case '+':
      camera.eyez = camera.eyez + 0.5;
      glutPostRedisplay();
      break;

   case '-':
      camera.eyez = camera.eyez - 0.5;
      glutPostRedisplay();
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
   sol.esfera.raio = 1.0;
   sol.esfera.slices = 20;
   sol.esfera.stacks = 16;
   sol.x = 0.;
   sol.y = 0.;
   sol.z = 0.;

   mercurio.esfera.raio = .2;
   mercurio.esfera.slices = 10;
   mercurio.esfera.stacks = 8;
   mercurio.x = 3.0;
   mercurio.y = 0.;
   mercurio.z = 0.;

   venus.esfera.raio = 0.5;
   venus.esfera.slices = 10;
   venus.esfera.stacks = 8;
   venus.x = 5.0;
   venus.y = 0.;
   venus.z = 0.;
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