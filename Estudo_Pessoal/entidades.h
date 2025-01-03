#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PI (float)3.14159265359

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
    GLfloat left;
    GLfloat right;

    GLfloat bottom;
    GLfloat top;

    GLfloat near;
    GLfloat far;
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
    GLfloat eyex;
    GLfloat eyey;
    GLfloat eyez;

    GLfloat centerx;
    GLfloat centery;
    GLfloat centerz;

    GLfloat upx;
    GLfloat upy;
    GLfloat upz;

    GLfloat angle_alpha; // angulo X
    GLfloat angle_beta;  // angulo Y
    GLfloat angle_gamma; // angulo Z

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
    GLfloat pos[3];

    GLfloat raio;

    GLint slices;
    GLint stacks;

} Esfera;

struct Cubo
{
    GLfloat pos[3];

    GLfloat aresta;
};
#endif