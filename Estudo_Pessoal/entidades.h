#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.14159265359

//  @brief Estrutura basica para a janela principal
struct Window
{
    int width;
    int height;

    int posx;
    int posy;

    char *name;
};

//  @brief Estrutura para o Frustum
//  (troco de visualizacao) da camera
//
//  @note Outra maneira de gerar a projecao da camera
//  na tela
typedef struct
{
    GLdouble left;
    GLdouble right;

    GLdouble bottom;
    GLdouble top;

    GLdouble near;
    GLdouble far;
} Frustum;

//  @brief Estrutura para a Pespectiva da camera
typedef struct
{
    int FOV; // [0., 180.] degrees

    int width;
    int height;

    int near;
    int far;
} Perspective;

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

    GLdouble angle;

    Perspective Perspective;
};

//  @brief Estrutura de dados para o mouse
struct Mouse
{
    int x;
    int y;

    int old_x;
    int old_y;

    int button;
    int state;
};

//  @brief Estrutura para a Esfera
struct Esfera
{
    GLdouble posx;
    GLdouble posy;
    GLdouble posz;

    GLdouble raio;

    GLint slices;
    GLint stacks;

} Esfera;

struct Cubo
{
    GLdouble posx;
    GLdouble posy;
    GLdouble posz;

    GLdouble aresta;
};
#endif