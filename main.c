#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "abm.h"
#include "funciones.h"
#include "html.h"
#include "validar.h"

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
                alta(&datosDePelicula);

                break;
            case 2:
                system("cls");
                baja();

                break;
            case 3:
                system("cls");
                modificar();
                break;
            case 4:
                system("cls");
                generarPage();
                printf("Apretar para abrir page(continua el programa al cerrar la pagina)\n");
                system("pause");
                system("index.html");
                break;
            case 5:
                system("cls");
                readArchive();
                break;
            case 6:
                opcion = 6;
                break;
            default:
                system("cls");
                printf("\nNO ES OPCION DEL MENU\n");
            }
        }

    } while (opcion != 6);

    return 0;
}
