
#include "validar.h"

//////////////////////////////////////////////////////////////////

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