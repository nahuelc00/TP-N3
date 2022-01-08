#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "abm.h"

void mostrarMenu();

int validarNumero(char string[]);

void readArchive();

void mostrarDatosDePelicula(Pelicula *datosDePelicula);

char *leer(char nombreArchivo[20])
{
    const char *FLENAME = nombreArchivo;

    FILE *input_file = fopen(FLENAME, "r");

    if (!input_file)
        exit(EXIT_FAILURE);

    struct stat sb;

    if (stat(FLENAME, &sb) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char *file_contents = malloc(sb.st_size);
    fread(file_contents, sb.st_size, 1, input_file);
    fclose(input_file);
    return file_contents;
}

void saveDataPage(Pelicula datosDePeliculasAux, FILE *index)
{
    fprintf(index, "<article class='col-md-4 article-intro'>");
    fprintf(index, "<a href='#'>");
    fprintf(index, "<img class='img-responsive img-rounded' src='%s' alt='' style=' width : 150px;'>", datosDePeliculasAux.linkDeImagen);
    fprintf(index, "</a>");
    fprintf(index, "<h3>");
    fprintf(index, "<a href='#'>%s</a>", datosDePeliculasAux.titulo);
    fprintf(index, "</h3>");
    fprintf(index, "<ul>");
    fprintf(index, "<li>Genero:%s</li>", datosDePeliculasAux.genero);
    fprintf(index, "<li>Puntaje:%d</li>", datosDePeliculasAux.puntaje);
    fprintf(index, "<li>Duracion:%.2fhs</li> ", datosDePeliculasAux.duracion);
    fprintf(index, "</ul>");
    fprintf(index, "<p>%s</p>", datosDePeliculasAux.descripcion);
    fprintf(index, "</article>");
}

void generarPage()
{
    char *encabezado = leer("encabezado.html");

    char *nombreArchivoindex = "index.html";

    FILE *archivo = fopen(ARCHIVO, "rb");          // Lectura
    FILE *index = fopen(nombreArchivoindex, "wb"); // Escritura

    fprintf(index, "%s", encabezado); // Dibuja el encabezado

    Pelicula datosDePeliculasAux;

    if (archivo == NULL)
    {
        printf("No se logro abrir el archivo\n");
        system("pause");
        exit(1);
    }

    while (!feof(archivo)) // Mientras no sea el fin de archivo..
    {
        fread(&datosDePeliculasAux, sizeof(Pelicula), 1, archivo);

        if (feof(archivo) == 0 && datosDePeliculasAux.estado == ACTIVO) // Al pasar por cada registro dibuja en el HTML..
        {
            saveDataPage(datosDePeliculasAux, index);
        }
    }

    free(encabezado);
    fclose(archivo);
    fclose(index);

    printf("Termine de leer el archivo.dat y de escribir dentro del HTML\n");
}

/*/////////////////////// Declaracion de funciones ///////////////////////*/

int main()
{
    Pelicula datosDePelicula;
    int opcion = 0;
    char auxMenu[MAX];

    do
    {
        mostrarMenu();

        printf("Ingrese una opcion del menu: ");
        scanf("%s", &auxMenu);

        if (validarNumero(auxMenu) == 0)
        {
            system("cls");
            printf("\nLO INGRESADO NO ES UN NUMERO!!\n");
        }
        else
        {
            opcion = atoi(auxMenu);

            switch (opcion)
            {
            case 1:
                system("cls");
                printf("Entre al case 1\n");

                alta(&datosDePelicula);

                break;
            case 2:
                system("cls");
                printf("Entre al case 2\n");
                baja();

                break;
            case 3:
                system("cls");
                printf("Entre al case 3");
                modificar();
                break;
            case 4:
                system("cls");
                printf("Entre al case 4\n");
                generarPage();
                printf("Apretar para abrir page\n");
                system("pause");
                system("index.html");

                break;
            case 5:
                system("cls");
                break;

            case 6:
                system("cls");
                readArchive();
            case 7:

                break;
            default:
                system("cls");
                printf("\nNO ES OPCION DEL MENU\n");
            }
        }

    } while (opcion != 7);

    return 0;
}

////////////////////////////////  FUNCIONES  ////////////////////////////////
void mostrarMenu()
{
    printf("\n");
    printf("1- Agregar pelicula\n");
    printf("2- Borrar pelicula\n");
    printf("3- Modificar pelicula\n");
    printf("4- Generar pagina web\n");
    printf("5- ...\n");
    printf("6- Leer archivo\n");
    printf("7- Salir\n");
}

int validarNumero(char string[])
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] != '\0')
        {
            if (string[i] < '0' || string[i] > '9')
            {
                return 0;
            }
            return 1;
        }
    }
}

void readArchive()
{

    printf("Entre a la funcion leer archivo\n");
    FILE *archivo;

    Pelicula datosDePeliculasAux;
    archivo = fopen(ARCHIVO, "rb"); // Se abre el archivo con permiso de lectura

    if (archivo == NULL)
    {
        printf("No se logro abrir el archivo");
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
