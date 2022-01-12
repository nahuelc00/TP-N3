
#include "html.h"

//////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////

void generarPage()
{
    char *encabezado = leer(ENCABEZADO);

    char *nombreArchivoindex = INDEX;

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
}
