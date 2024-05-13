#include <stdio.h>

int main()
{
    FILE *img = fopen("Lenna.bmp", "r");
    FILE *imgGray = fopen("Lenna_Gray.bmp", "w");
    FILE *imgBri = fopen("Lenna_Bri.bmp", "w");
    FILE *imgR = fopen("Lenna_R.bmp", "w");
    FILE *imgG = fopen("Lenna_G.bmp", "w");
    FILE *imgB = fopen("Lenna_B.bmp", "w");
    unsigned int w = 0, h = 0, p = 0, size=0;
    unsigned char header[54], alpha, zero = 0, r, g, b,temp, one = 255, brig=100;

    if(img == NULL || imgG == NULL) {
        printf("No fue posible abrir las imagenes.");
        return 1;
    }

    // Obtenemos las dimensiones de la imagen
    fseek(img, 18, SEEK_SET);
    fread(&w, 4, 1, img);
    fseek(img, 22, SEEK_SET);
    fread(&h, 4, 1, img);
    fseek(img, 28, SEEK_SET);
    fread(&p, 2, 1, img);
    fseek(img, 34, SEEK_SET);
    fread(&size, 4, 1, img);

    printf("Ancho: %i, Alto: %i, Bits: %i, Tamanio en bytes: %i", w, h, p, size);

    // Copiamos en encabezado
    fseek(img, 0, SEEK_SET);
    fread(header, sizeof(char), 54, img);
    fwrite(header, sizeof(char), 54, imgGray);
    fwrite(header, sizeof(char), 54, imgR);
    fwrite(header, sizeof(char), 54, imgG);
    fwrite(header, sizeof(char), 54, imgB);
    fwrite(header, sizeof(char), 54, imgBri);
    
    // Inicia la data
    // Primer byte - Alpha
    // Segundo byte - Green
    // Tercer byte - Red
    // Cuarto byte - Blue
    
    fseek(img, 54, SEEK_SET);

    for (int i = 0; i < size; i+=4)
    {
        // Componentes
        fread(&alpha, sizeof(char), 1, img);
        fread(&g, sizeof(char), 1, img);
        fread(&r, sizeof(char), 1, img);
        fread(&b, sizeof(char), 1, img);
        
        // Alpha
        fwrite(&alpha, sizeof(char), 1, imgR);
        fwrite(&alpha, sizeof(char), 1, imgG);
        fwrite(&alpha, sizeof(char), 1, imgB);

        // Red
        fwrite(&zero, sizeof(char), 1, imgR);
        fwrite(&r, sizeof(char), 1, imgR);
        fwrite(&zero, sizeof(char), 1, imgR);

        // Green
        fwrite(&g, sizeof(char), 1, imgG);
        fwrite(&zero, sizeof(char), 1, imgG);
        fwrite(&zero, sizeof(char), 1, imgG);

        // Blue
        fwrite(&zero, sizeof(char), 1, imgB);
        fwrite(&zero, sizeof(char), 1, imgB);
        fwrite(&b, sizeof(char), 1, imgB);

        // Gray
        temp = (unsigned char)(((int)r + (int)g + (int)b) / 3);
        fwrite(&temp, sizeof(char), 1, imgGray);
        fwrite(&temp, sizeof(char), 1, imgGray);
        fwrite(&temp, sizeof(char), 1, imgGray);
        fwrite(&temp, sizeof(char), 1, imgGray);

        // Brillo
        temp = ((int)alpha + (int)brig) > 255 ? 255 : alpha + brig;
        fwrite(&temp, sizeof(char), 1, imgBri);
        temp = ((int)g + (int)brig) > 255 ? 255 : g + brig;
        fwrite(&temp, sizeof(char), 1, imgBri);
        temp = ((int)r + (int)brig) > 255 ? 255 : r + brig;
        fwrite(&temp, sizeof(char), 1, imgBri);
        temp = ((int)b + (int)brig) > 255 ? 255 : b + brig;
        fwrite(&temp, sizeof(char), 1, imgBri);
        
    }
    

    fclose(img);
    fclose(imgGray);
    fclose(imgR);
    fclose(imgG);
    fclose(imgB);
    fclose(imgBri);

    return 0;
}
