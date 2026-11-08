import numpy as np
from scipy.fftpack import dct, idct

# 1. Creamos un bloque de prueba de 8x8 (ej. intensidades de gris en una sección del cielo)
bloque_original = np.array([
    [140, 144, 147, 140, 140, 155, 179, 175],
    [144, 152, 140, 147, 140, 148, 167, 179],
    [152, 145, 144, 144, 140, 147, 160, 171],
    [147, 140, 140, 150, 144, 145, 155, 152],
    [140, 155, 152, 152, 152, 144, 147, 147],
    [147, 160, 155, 155, 155, 145, 145, 145],
    [160, 160, 160, 167, 160, 145, 145, 145],
    [160, 167, 167, 171, 167, 145, 145, 145]
], dtype=np.float32)

# Normalizamos restando 128 (típico en el estándar JPEG)
bloque_centrado = bloque_original - 128

# 2. Aplicamos la DCT en 2D (por filas y luego por columnas)
def aplicar_dct2d(bloque):
    return dct(dct(bloque.T, norm='ortho').T, norm='ortho')

coeficientes_dct = aplicar_dct2d(bloque_centrado)

# 3. Matriz de Cuantificación Estándar JPEG (Define el nivel de "pérdida")
matriz_cuantificacion = np.array([
    [16, 11, 10, 16, 24,  40,  51,  61],
    [12, 12, 14, 19, 26,  58,  60,  55],
    [14, 13, 16, 24, 40,  57,  69,  56],
    [14, 17, 22, 29, 51,  87,  80,  62],
    [18, 22, 37, 56, 68,  109, 103, 77],
    [24, 35, 55, 64, 81,  104, 113, 92],
    [49, 64, 78, 87, 103, 121, 120, 101],
    [72, 92, 95, 98, 112, 100, 103, 99]
], dtype=np.float32)

# PASO CON PÉRDIDA: División y redondeo. Muchos valores se transforman en 0.
bloque_cuantificado = np.round(coeficientes_dct / matriz_cuantificacion)

# 4. DECODIFICACIÓN (Proceso inverso para recuperar la imagen)
def aplicar_idct2d(bloque):
    return idct(idct(bloque.T, norm='ortho').T, norm='ortho')

# Descuantificación
coeficientes_recuperados = bloque_cuantificado * matriz_cuantificacion
# Transformada inversa y revertir el centrado
bloque_reconstruido = aplicar_idct2d(coeficientes_recuperados) + 128
bloque_reconstruido = np.clip(np.round(bloque_reconstruido), 0, 255)

# --- IMPRESIÓN DE RESULTADOS ---
print("--- Bloque Original ---")
print(bloque_original.astype(int))

print("\n--- Coeficientes Cuantificados (Datos comprimidos) ---")
# Notarás la gran cantidad de ceros en las altas frecuencias (abajo a la derecha)
print(bloque_cuantificado.astype(int))

print("\n--- Bloque Reconstruido (Con pérdida) ---")
print(bloque_reconstruido.astype(int))
