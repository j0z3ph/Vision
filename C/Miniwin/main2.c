
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "miniwin.h"

const int TAM = 25; // constante
const int FILAS = 20;
const int COLUMNAS = 10;

typedef struct Coord { int x, y; } Coord;

typedef struct Pieza {
   Coord orig;     // bloque central (posici�n absoluta)
   Coord perif[3]; // bloques perif�ricos (posici�n relativa)
   int color;
} Pieza;

Coord posicion(Pieza *p, int n) {
   Coord ret;
   ret.x = p->orig.x;
   ret.y = p->orig.y;
   if (n != 0) {
      ret.x += p->perif[n-1].x;
      ret.y += p->perif[n-1].y;
   }
   return ret;
}

void cuadrado(int x, int y) {
   rectangulo_lleno(20 + 1 + x * TAM,
                    20 + 1 + y * TAM,
                    20 + x * TAM + TAM,
                    20 + y * TAM + TAM);
}

void pinta_pieza(Pieza* P) {
   color(P->color);
   for (int i = 0; i < 4; i++) {
      Coord c = posicion(P,i);
      cuadrado(c.x, c.y);
   }
}

Coord rota_derechaC(Coord* c) {
   Coord ret = { -c->y, c->x };
   return ret;
}

void rota_derecha(Pieza* P) {
   for (int i = 0; i < 3; i++) {
      P->perif[i] = rota_derechaC(&(P->perif[i]));
   }
}

void tablero_vacia(int T[COLUMNAS][FILAS]) {
   for (int i = 0; i < COLUMNAS; i++) {
      for (int j = 0; j < FILAS; j++) {
         T[i][j] = NEGRO; // Esto significa casilla vac�a
      }
   }
}

void tablero_pinta(int T[COLUMNAS][FILAS]) {
   for (int i = 0; i < COLUMNAS; i++) {
      for (int j = 0; j < FILAS; j++) {
         color(T[i][j]);
         cuadrado(i, j);
      }
   }
}

void tablero_incrusta_pieza(int T[COLUMNAS][FILAS], Pieza* P) {
   for (int i = 0; i < 4; i++) {
      Coord c = posicion(P, i);
      T[c.x][c.y] = P->color;
   }
}

bool tablero_colision(int T[COLUMNAS][FILAS], Pieza* P) {
   for (int i = 0; i < 4; i++) {
      Coord c = posicion(P, i);
      // Comprobar l�mites
      if (c.x < 0 || c.x >= COLUMNAS) {
         return true;
      }
      if (c.y < 0 || c.y >= FILAS) {
         return true;
      }
      // Mirar "basurilla"
      if (T[c.x][c.y] != NEGRO) {
         return true;
      }
   }
   return false;
}

const Coord perifs[7][3] = {
   { { 1,0 }, { 0,1 }, { 1,1 } }, // cuadrado
   { { 1,0 }, {-1,1 }, { 0,1 } }, // S
   { { 0,1 }, { 1,1 }, {-1,0 } }, // 2
   { { 0,1 }, { 0,-1}, { 1,1 } }, // L
   { { 0,1 }, { 0,-1}, {-1,1 } }, // Lr
   { {-1,0 }, { 1,0 }, { 0,1 } }, // T
   { { 0,1 }, { 0,-1}, { 0,2 } }, // Palo
};

void pieza_nueva(Pieza* P) {
  P->orig.x = 12;
  P->orig.y = 2;
  P->color = 1 + rand() % 6;
  // Pieza al azar
  int r = rand() % 7;
  for (int i = 0; i < 3; i++) {
     P->perif[i] = perifs[r][i];
  }
}

bool tablero_fila_llena(int T[COLUMNAS][FILAS], int fila) {
   for (int i = 0; i < COLUMNAS; i++) {
      if (T[i][fila] == NEGRO) return false;
   }
   return true;
}

void tablero_colapsa(int T[COLUMNAS][FILAS], int fila) {
   // Copiar de abajo a arriba
   for (int j = fila; j > 0; j--) {
      for (int i = 0; i < COLUMNAS; i++) {
         T[i][j] = T[i][j-1];
      }
   }
   // Vaciar la de arriba
   for (int i = 0; i < COLUMNAS; i++) {
      T[i][0] = NEGRO;
   }
}

int tablero_cuenta_lineas(int T[COLUMNAS][FILAS]) {
   int fila = FILAS - 1, cont = 0;
   while (fila >= 0) {
      if (tablero_fila_llena(T, fila)) {
         tablero_colapsa(T, fila);
         cont++;
      } else {
         fila--;
      }
   }
   return cont;
}

void a_string(int puntos, char *str) {
   sprintf(str, "%i", puntos);
}

void repinta(int T[COLUMNAS][FILAS], Pieza* p, Pieza* sig,
             int puntos, int nivel)
{
   const int ancho = TAM * COLUMNAS;
   const int alto  = TAM * FILAS;
   char str[1000];
   borra();
   tablero_pinta(T);
   color_rgb(128, 128, 128);
   linea(20, 20, 20, 20 + alto);
   linea(20, 20 + alto,
         20 + ancho, 20 + alto);
   linea(20 + ancho, 20 + alto,
         20 + ancho, 20);
   texto(40 + ancho, 20, "Pieza siguiente");
   texto(40 + ancho, 150, "Nivel");
   texto(40 + ancho, 250, "Puntos");
   color(BLANCO);
   a_string(puntos, str);
   texto(40 + ancho, 270, str);
   a_string(nivel + 1, str);
   texto(40 + ancho, 170, str);
   pinta_pieza(p);
   pinta_pieza(sig);
   refresca();
}

const int puntos_limite[10] = {
   50, 100, 130, 150, 170, 200, 220, 240, 260, 400
};

const int tics_nivel[10] = {
   33, 25, 20, 18, 16, 14, 12, 10, 8, 2
};

void game_over() {
   color(BLANCO);
   texto(140, 240, "GAME OVER!");
   refresca();
   espera(1000);
   vcierra();
}

int main() {
   int Tablero[COLUMNAS][FILAS];
   vredimensiona(TAM * COLUMNAS + 220, TAM * FILAS + 100);
   //vtitulo("Tetrix");
   srand(time(0)); // Inicializar los n�meros al azar (poner la semilla)

   int tic = 0, puntos = 0, nivel = 0;

   tablero_vacia(Tablero);
   Pieza c, sig;
   pieza_nueva(&c);
   pieza_nueva(&sig);
   c.orig.x = 5;

   repinta(Tablero, &c, &sig, puntos, nivel);

   int t = tecla();
   while (t != ESCAPE) {
      // 0. Copiar la pieza actual
      Pieza copia = c;

      if (t == NINGUNA && tic > tics_nivel[nivel]) {
         tic = 0;
         t = ABAJO;
      }

      if (t == 'N') {
         nivel++;
      }

      // 1. Prueba el movimiento
      if (t == ABAJO) {
         c.orig.y++;
      } else if (t == ARRIBA) {
         rota_derecha(&c);
      } else if (t == DERECHA) {
         c.orig.x++;
      } else if (t == IZQUIERDA) {
         c.orig.x--;
      }
      // 2. Mirar si hay colisi�n
      if (tablero_colision(Tablero, &c)) {
         c = copia;
         if (t == ABAJO) {
            tablero_incrusta_pieza(Tablero, &c);
            int cont = tablero_cuenta_lineas(Tablero);
            puntos += cont * cont;
            if (puntos > puntos_limite[nivel]) {
               nivel++;
            }
            c = sig;
            pieza_nueva(&sig);
            c.orig.x = 5;
            if (tablero_colision(Tablero, &c)) {
               game_over();
            }
         }
      }

      // Repintar
      if (t != NINGUNA) {
         repinta(Tablero, &c, &sig, puntos, nivel);
      }

      espera(30);
      tic++;
      t = tecla();
   }
   vcierra();
   return 0;
}
