#ifndef ENTIDADES_H
#define ENTIDADES_H

typedef struct 
{
    float raio;

    int x;
    int y;
    int z;

} Esfera;

struct Planeta
{
    Esfera esfera;

    float massa;
};


#endif