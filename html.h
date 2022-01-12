
#ifndef HTML_H_INCLUDED
#define HTML_H_INCLUDED

#include "struct.h"

char *leer(char nombreArchivo[20]);

void saveDataPage(Pelicula datosDePeliculasAux, FILE *index);

void generarPage();

#endif
