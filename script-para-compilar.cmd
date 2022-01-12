gcc -c main.c -o main.o
gcc -c abm.c -o abm.o
gcc -c funciones.c -o funciones.o
gcc -c html.c -o html.o
gcc -c validar.c -o validar.o
gcc main.o abm.o funciones.o html.o validar.o -o programa.exe