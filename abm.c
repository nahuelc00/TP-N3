#include "abm.h"

//////////////////////////////////////////////////////////////////
void mostrarMenu()
{
    printf("\n");
    printf("1- Agregar pelicula\n");
    printf("2- Borrar pelicula\n");
    printf("3- Modificar pelicula\n");
    printf("4- Generar pagina web\n");
    printf("5- Leer archivo\n");
    printf("6- Salir\n");
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

void alta(Pelicula *datosDePelicula)
{
    FILE *archivo;
    archivo = fopen(ARCHIVO, "ab"); // Se abre el archivo con permiso de escritura
    if (archivo == NULL)
    {
        printf("No se pudo abrir correctamente el archivo\n");
        system("pause");
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

//////////////////////////////////////////////////////////////////

void modificar()
{

    FILE *archivo;
    archivo = fopen(ARCHIVO, "r+b"); // Se abre el archivo con permiso de lectura y escritura

    Pelicula datosDePeliculasAux;

    char titleSearch[MAX];

    if (archivo == NULL)
    {
        printf("No se logro abrir el archivo\n");
        system("pause");
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

//////////////////////////////////////////////////////////////////

void baja()
{
    char peliaux[MAX];

    FILE *arch = fopen(ARCHIVO, "r+b");
    if (arch != NULL)
    {

        printf("\nIngrese el nombre de la pelicula a borrar: ");
        fflush(stdin);
        scanf("%[^\n]", &peliaux);
        fflush(stdin);

        Pelicula datoPelicula;

        while (!feof(arch))
        {
            fread(&datoPelicula, sizeof(Pelicula), 1, arch);

            if (strcmp(datoPelicula.titulo, peliaux) == 0 && datoPelicula.estado == ACTIVO)
            {

                int posicion = ftell(arch) - sizeof(Pelicula);
                fseek(arch, posicion, SEEK_SET);

                datoPelicula.estado = BORRADO;

                fwrite(&datoPelicula, sizeof(Pelicula), 1, arch);

                printf("La pelicula fue eliminada correctamente\n");
                break;
            }
        }
        fclose(arch);
    }
    else
    {
        printf("No se pudo abrir correctamente el archivo\n");
        system("pause");
        exit(1);
    }
}