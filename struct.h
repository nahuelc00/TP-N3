
#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#define ARCHIVO "archivo.dat"
#define ENCABEZADO "encabezado.html"
#define INDEX "index.html"

#define MAX 100
#define ACTIVO 1
#define BORRADO 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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

#endif