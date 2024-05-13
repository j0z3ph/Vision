#include <stdio.h>

int main()
{
    FILE *img = fopen("Lenna.bmp", "rb");
    FILE *imgGray = fopen("Lenna_Gray.bmp", "wb");
    FILE *imgBri = fopen("Lenna_Bri.bmp", "wb");
    FILE *imgR = fopen("Lenna_R.bmp", "wb");
    FILE *imgG = fopen("Lenna_G.bmp", "wb");
    FILE *imgB = fopen("Lenna_B.bmp", "wb");
    FILE *imgN = fopen("Lenna_N.bmp", "wb");
    
    unsigned int w = 0, h = 0, p = 0, size=0;
    unsigned char header[54], alpha, zero = 0, r, g, b,temp, brig=100;

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
    fread(header, sizeof(unsigned char), 54, img);
    fwrite(header, sizeof(unsigned char), 54, imgGray);
    fwrite(header, sizeof(unsigned char), 54, imgR);
    fwrite(header, sizeof(unsigned char), 54, imgG);
    fwrite(header, sizeof(unsigned char), 54, imgB);
    fwrite(header, sizeof(unsigned char), 54, imgBri);
    fwrite(header, sizeof(unsigned char), 54, imgN);
    
    // Inicia la data
    // Primer byte - Alpha
    // Segundo byte - Green
    // Tercer byte - Red
    // Cuarto byte - Blue
    
    fseek(img, 54, SEEK_SET);

    for (unsigned int i = 0; i < size; i+=3)
    {
        // Componentes
        //fread(&alpha, sizeof(char), 1, img);
        fread(&b, sizeof(unsigned char), 1, img);
        fread(&g, sizeof(unsigned char), 1, img);
        fread(&r, sizeof(unsigned char), 1, img);
        
        // Alpha
        //fwrite(&alpha, sizeof(char), 1, imgR);
        //fwrite(&alpha, sizeof(char), 1, imgG);
        //fwrite(&alpha, sizeof(char), 1, imgB);

        // Red
        fwrite(&zero, sizeof(unsigned char), 1, imgR);
        fwrite(&zero, sizeof(unsigned char), 1, imgR);
        fwrite(&r, sizeof(unsigned char), 1, imgR);
        
        // Green
        fwrite(&zero, sizeof(unsigned char), 1, imgG);
        fwrite(&g, sizeof(unsigned char), 1, imgG);
        fwrite(&zero, sizeof(unsigned char), 1, imgG);

        // Blue
        fwrite(&b, sizeof(unsigned char), 1, imgB);
        fwrite(&zero, sizeof(unsigned char), 1, imgB);
        fwrite(&zero, sizeof(unsigned char), 1, imgB);
        
        // Gray
        temp = (unsigned char)(((int)r + (int)g + (int)b) / 3);
        //fwrite(&temp, sizeof(char), 1, imgGray);
        fwrite(&temp, sizeof(unsigned char), 1, imgGray);
        fwrite(&temp, sizeof(unsigned char), 1, imgGray);
        fwrite(&temp, sizeof(unsigned char), 1, imgGray);

        // Brillo
        //temp = ((int)alpha + (int)brig) > 255 ? 255 : alpha + brig;
        //fwrite(&temp, sizeof(char), 1, imgBri);
        temp = ((int)b + (int)brig) > 255 ? 255 : b + brig;
        fwrite(&temp, sizeof(char), 1, imgBri);
        temp = ((int)g + (int)brig) > 255 ? 255 : g + brig;
        fwrite(&temp, sizeof(char), 1, imgBri);
        temp = ((int)r + (int)brig) > 255 ? 255 : r + brig;
        fwrite(&temp, sizeof(char), 1, imgBri);
        

        // Negativo
        //temp = (unsigned int)255 - alpha;
        //fwrite(&temp, sizeof(char), 1, imgN);
        temp = (unsigned int)255 - b;
        fwrite(&temp, sizeof(char), 1, imgN);
        temp = (unsigned int)255 - g;
        fwrite(&temp, sizeof(char), 1, imgN);
        temp = (unsigned int)255 - r;
        fwrite(&temp, sizeof(char), 1, imgN);
        
        
    }
    

    fclose(img);
    fclose(imgGray);
    fclose(imgR);
    fclose(imgG);
    fclose(imgB);
    fclose(imgBri);
    fclose(imgBri);


    return 0;
}
