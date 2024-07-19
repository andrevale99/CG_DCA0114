#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "entidades.h"

#define ESC_KEY 27

static int year = 0, day = 0;

static struct Window window = {
    .width = 640,
    .height = 480,
    .posx = 500,
    .posy = 500,

    .name = "Planeta",
};

static struct Camera camera = {0};
static struct Planeta sol = {0};

void init(void);
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

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
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);

   glPushMatrix();
   glutWireSphere(1.0, 20, 16); /* draw sun */
   glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
   glTranslatef(2.0, 0.0, 0.0);
   glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
   glutWireSphere(0.2, 10, 8); /* draw smaller planet */
   glPopMatrix();
   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
   case 'y':
      year = (year + 5) % 360;
      glutPostRedisplay();
      break;
   case 'Y':
      year = (year - 5) % 360;
      glutPostRedisplay();
      break;

   case ESC_KEY:
      exit(0);
      break;

   default:
      break;
   }
}

void Arg_parse(const int argc, char *argv[])
{
   if (argc == 2 && (strcmp(argv[1], "--help") == 0))
   {
      printf("\n Usage: ./Planeta.out [OPTIONS...] \n\n"
             "--help \t Mensagem de ajuda do programa\n"
             "-w \t Largura da Janela [default=%d]\n"
             "-h \t Altura da Janela [default=%d]\n"
             "\n" , 
             window.width, window.height);

      exit(0);
   }
   else
   {
      int idx = 1;
      for(idx = 1; idx < argc; ++idx)
      {
         if (strcmp(argv[idx], "-w") == 0)
            window.width = atoi(argv[++idx]);

         if (strcmp(argv[idx], "-h") == 0)
            window.height = atoi(argv[++idx]);
      }
   }
}