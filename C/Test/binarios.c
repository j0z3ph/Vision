#include<stdio.h>

struct Fecha
{
    int dia;
    int mes;
    int anio;
};


int main()
{
    FILE *archivo = fopen("mi_archivo.bin", "rb");
    char cadena[100];
    int variable = 10;
    struct Fecha fecha;

    if(archivo == NULL) {
        printf("ERROR!!!!");
        return 1;
    }

    //fscanf(archivo, "%s", &cadena);
    //fprintf(archivo, "%i", variable);

    //fwrite(&fecha, sizeof(struct Fecha), 1, archivo);

    fread(&fecha, sizeof(struct Fecha), 1, archivo);


    fclose(archivo);

    printf("%02i/%02i/%04i", fecha.dia, fecha.mes, fecha.anio);
    
    return 0;
}
