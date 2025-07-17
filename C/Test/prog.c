/**
 * @file prog.c
 * @author Jose Luis Cruz (jlcruz@ipn.mx)
 * @brief Ejemplo
 * @version 0.1
 * @date 2025-07-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include"biblioteca.h"

int main()
{
    int a = 5;
    int b = 3;
    int c = suma(a, b);
    int d = resta(a, b);

    printf("%i\n%i\n", c, d);
    return 0;
}

