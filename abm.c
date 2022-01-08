#include "struct.h"

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

void alta(Pelicula *datosDePelicula)
{
    FILE *archivo;
    archivo = fopen(ARCHIVO, "ab"); // Se abre el archivo con permiso de escritura
    if (archivo == NULL)
    {
        printf("No se pudo abrir correctamente el archivo\n");
        exit(1);
    }

    // HAY QUE INICIALIZAR DURACION Y PUNTAJE, DE LO CONTRARIO LO LLENA CON BASURA
    datosDePelicula->duracion = 0;
    datosDePelicula->puntaje = 0;

    Pelicula *datos = cargarDatos(datosDePelicula);
    fwrite(datosDePelicula, sizeof(Pelicula), 1, archivo); // Se escribe la estructura dentro del archivo

    printf("Se escribio correctamente\n");

    fclose(archivo);
}

void modificar()
{

    FILE *archivo;
    archivo = fopen(ARCHIVO, "r+b"); // Se abre el archivo con permiso de lectura y escritura

    Pelicula datosDePeliculasAux;

    char titleSearch[MAX];

    if (archivo == NULL)
    {
        printf("No se logro abrir el archivo");
        exit(1);
    }

    printf("\nIngrese la peli a buscar: \n");
    fflush(stdin);
    scanf("%[^\n]", &titleSearch);
    fflush(stdin);

    while (feof(archivo) == 0) // Mientras no sea el fin de archivo..
    {

        fread(&datosDePeliculasAux, sizeof(Pelicula), 1, archivo);

        if (strcmp(datosDePeliculasAux.titulo, titleSearch) == 0 && datosDePeliculasAux.estado == ACTIVO)
        {

            printf("Titulo encontrado\n");

            Pelicula *datos = cargarDatos(&datosDePeliculasAux);

            int posActual = ftell(archivo) - sizeof(Pelicula);
            fseek(archivo, posActual, 0);

            fwrite(&datosDePeliculasAux, sizeof(Pelicula), 1, archivo); // Se escribe la estructura dentro del archivo

            printf("Se escribio correctamente\n");

            break;
        }
    }
    fclose(archivo);
}

void baja()
{
    char peliaux[MAX];

    FILE *arch = fopen(ARCHIVO, "r+b");
    if (arch != NULL)
    {

        printf("\nIngrese el nombre de la pelicula a borrar: ");
        scanf("%s", peliaux);
        Pelicula datoPelicula;

        while (!feof(arch))
        {
            fread(&datoPelicula, sizeof(Pelicula), 1, arch);

            if (strcmp(datoPelicula.titulo, peliaux) == 0)
            {

                int posicion = ftell(arch) - sizeof(Pelicula);
                fseek(arch, posicion, SEEK_SET);

                datoPelicula.estado = BORRADO;

                fwrite(&datoPelicula, sizeof(Pelicula), 1, arch);
                break;
            }
        }
        fclose(arch);
    }
}