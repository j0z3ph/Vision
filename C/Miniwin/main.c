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

int main()
{
    int t;
    float x, y;
    vredimensiona(300, 400);
    vtitulo("Mi juego");

    t = tecla();
    
    while(t != ESCAPE) {
        //color_rgb(100,50,200);
        //rectangulo_lleno(5,5,200,200);
        borra();
        color(AMARILLO);
        if(raton_dentro())
            raton(&x, &y);
        circulo_lleno(x,y,10);
        color(NEGRO);
        circulo_lleno(x,y,9);
        color(AMARILLO);
        circulo_lleno(x,y,5);
        refresca();

        if(raton_boton_izq()) {
            mensaje("Click");
        }

        espera(30);
        
        t = tecla();
    }
    vcierra();
    return 0;
}
