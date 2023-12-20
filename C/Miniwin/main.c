/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include"miniwin.h"
#define FPS 60
#define GRAVEDAD 10
#define HEIGHT 400
#define WEIGTH 400

int main()
{
    int t;
    float x=5, y=5;
    float ancho = 50, alto = 50, salto = -200;
    vredimensiona(WEIGTH, HEIGHT);
    vtitulo("Mi juego");

    t = tecla();
    
    while(t != ESCAPE) {
        y += GRAVEDAD;

        if(y + alto > HEIGHT) y = HEIGHT - alto;
        if(y < 0) y = 0;

        borra();
        color(AZUL);
        
        rectangulo_lleno(x,y,x+ancho, y+alto);

        t = tecla();
        if(t == ESPACIO) {
            y += salto;
            t = tecla();
        }
        if(t == IZQUIERDA) x-=10;
        if(t == DERECHA) x+=10;
        refresca();
        espera(1000/FPS);
    }
    vcierra();
    return 0;
}
