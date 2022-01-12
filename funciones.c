
#include "funciones.h"

//////////////////////////////////////////////////////////////////

void readArchive()
{

    FILE *archivo;

    Pelicula datosDePeliculasAux;
    archivo = fopen(ARCHIVO, "rb"); // Se abre el archivo con permiso de lectura

    if (archivo == NULL)
    {
        printf("No se logro abrir el archivo\n");
        system("pause");
        exit(1);
    }

    while (!feof(archivo)) // Mientras no sea el fin de archivo..
    {
        fread(&datosDePeliculasAux, sizeof(Pelicula), 1, archivo);

        if (feof(archivo) == 0 && datosDePeliculasAux.estado == ACTIVO)
        {
            mostrarDatosDePelicula(&datosDePeliculasAux);
        }
    }

    fclose(archivo);
}

//////////////////////////////////////////////////////////////////

void mostrarDatosDePelicula(Pelicula *datosDePelicula)
{
    printf("\n");
    printf(" titulo: %s\n", datosDePelicula->titulo);
    printf(" genero: %s\n", datosDePelicula->genero);
    printf(" duracion: %.2f\n", datosDePelicula->duracion);
    printf(" descripcion: %s\n", datosDePelicula->descripcion);
    printf(" puntaje: %d\n", datosDePelicula->puntaje);
    printf(" link de imagen: %s\n", datosDePelicula->linkDeImagen);
    printf("\n");
}

//////////////////////////////////////////////////////////////////

Pelicula *cargarDatos(Pelicula *datosDePelicula)
{
    fflush(stdin);
    printf("Ingrese titulo\n");
    scanf("%[^\n]", &datosDePelicula->titulo);

    fflush(stdin);
    printf("Ingrese genero\n");
    scanf("%[^\n]", &datosDePelicula->genero);
    fflush(stdin);

    printf("Ingrese duracion en horas\n");
    scanf("%f", &datosDePelicula->duracion);
    fflush(stdin);

    printf("Ingrese descripcion\n");
    scanf("%[^\n]", &datosDePelicula->descripcion);
    fflush(stdin);

    printf("Ingrese puntaje del 1 al 10\n");
    scanf("%d", &datosDePelicula->puntaje);
    fflush(stdin);

    printf("Ingrese link de imagen\n");
    scanf("%[^\n]", &datosDePelicula->linkDeImagen);
    fflush(stdin);

    datosDePelicula->estado = ACTIVO;

    return datosDePelicula;
}
