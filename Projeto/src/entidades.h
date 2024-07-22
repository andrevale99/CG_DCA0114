#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//  @brief Estrutura basica para a janela principal
struct Window
{
    int width;
    int height;

    int posx;
    int posy;

    char *name;
};

//  @brief Estrutura para a Esfera
typedef struct 
{
    double raio;

    GLint slices;
    GLint stacks;

} Esfera;

//  @brief Estrutura para os planetas
struct Planeta
{
    Esfera esfera;

    //posicoes no mundo
    GLfloat x;
    GLfloat y;
    GLfloat z;

    float massa;
};

//  @brief Estrutura para a Pespectiva da camera
typedef struct 
{
    int FOV;

    int width;
    int height;

    int near;
    int far;
}Perspective;

//  @brief Estrutura para a Camera 
struct Camera
{
    GLdouble eyex;
    GLdouble eyey;
    GLdouble eyez;

    GLdouble centerx;
    GLdouble centery;
    GLdouble centerz;

    GLdouble upx;
    GLdouble upy;
    GLdouble upz;

    Perspective Perspective;
};

#endif