#include<stdio.h>


int main()
{
    FILE *archivo = fopen("mi_archivo.txt", "a");
    char cadena[100];
    
    if(archivo == NULL) {
        printf("ERROR!!!!");
        return 1;
    }

    //fscanf(archivo, "%s", &cadena);
    fprintf(archivo, "Hola Mundo\n");

    fclose(archivo);

    //printf("%s", cadena);
    
    return 0;
}
