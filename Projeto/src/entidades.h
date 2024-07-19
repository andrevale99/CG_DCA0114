#ifndef ENTIDADES_H
#define ENTIDADES_H

struct Window
{
    int width;
    int height;

    int posx;
    int posy;

    char *name;
};

typedef struct 
{
    float raio;

    //posicoes no mundo
    int x;
    int y;
    int z;

} Esfera;

struct Planeta
{
    Esfera esfera;

    float massa;
};

struct Camera
{
    int eyex;
    int eyey;
    int eyez;

    int centerx;
    int centery;
    int centerz;

    int upx;
    int upy;
    int upz;
};

#endif