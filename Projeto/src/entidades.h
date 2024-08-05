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

    float distance;

    float velocidade_x;
    float velocidade_y;
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

//  @brief Calcula a orbita do PLaneta usando o
//  metodo Euler-Cromer
//
//  @param *planeta Ponteiro para o planeta
//  @param dt Taxa de variacao do tempo
//
//  @note O calculo foi baseado no livro 
//  Computitonal Physics: second edition
//  (Nicholas J. Giordadno; Hisao Nakanishi)
void calculo_orbita(struct Planeta *planeta, float dt)
{
    //variveis para guardar os valores anteriores
    float vx_i = planeta->velocidade_x;
    float vy_i = planeta->velocidade_y;
    
    float x_i = planeta->x;
    float y_i = planeta->y;

    planeta->distance = sqrt(powf(planeta->x, 2) + powf(planeta->y, 2));
    
    planeta->velocidade_x = vx_i - (4 * powf(PI, 2) * planeta->x) / powf(planeta->distance, 3) * dt;
    planeta->velocidade_y = vy_i - (4 * powf(PI, 2) * planeta->y) / powf(planeta->distance, 3) * dt;

    planeta->x = x_i + planeta->velocidade_x * dt;
    planeta->y = y_i + planeta->velocidade_y * dt;
}

#endif