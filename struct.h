#define MAX 100
#define ARCHIVO "archivo.dat"
#define ACTIVO 1
#define BORRADO 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char titulo[MAX];
    char genero[MAX];
    float duracion;
    char descripcion[MAX];
    int puntaje;
    char linkDeImagen[1000];
    int estado;
} Pelicula;