#include<stdio.h>

struct Fecha
{
    int anio;
    int mes;
    int dia;
};

struct Alumno
{
    char nombre[100];
    char boleta[10];
    struct Fecha fnacimiento;
};



int main()
{
    struct Fecha mi_cumple;
    mi_cumple.anio = 2004;
    mi_cumple.mes = 11;
    mi_cumple.dia = 13;

    struct Alumno al1[100];
    
    return 0;
}
