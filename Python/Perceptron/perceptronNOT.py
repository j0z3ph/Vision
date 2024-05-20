"""
Perceptron entrenado para ser NOT (linealmente separables)
No funciona con XOR (No son linealmente separables)
"""

umbral = 0.5  # umbral de activacion de la neurona (si el resultado es mayor al umbral, la neurona se activa)
taza_aprendizaje = 0.1
pesos = [0, 0]  # pesos iniciales w1, w2 (un peso por cada entrada)

# entradas para entrenar
entradas = [(1, 0), (1, 1)]  # x1, x2 (agregamos una entrada con 1 para tener dos entradas por cada elemento de la lista de entradas)

salidas_deseadas = [1, 0]  # NOT


def neurona(entrada, pesos, umbral):
    # multiplicamos cada entrada por su respectivo peso y los sumamos
    valor = 0
    for idx, x in enumerate(entrada):
        valor += x * pesos[idx]

    # devolvemos 1 si la neurona se activa, 0 si no se activa
    return int(valor > umbral)


if __name__ == "__main__":
    while True:
        cont_errores = 0

        for idx, entrada in enumerate(entradas):
            resultado = neurona(entrada, pesos, umbral)
            error = salidas_deseadas[idx] - resultado
            if error != 0:
                cont_errores += 1
                # si hay error, ajustamos los pesos del perceptron
                for indice, x in enumerate(entrada):
                    pesos[indice] += x * error * taza_aprendizaje

        if cont_errores == 0:
            # si no hay errores, salimos
            break

    print(f"Pesos finales: {pesos}")

    # probamos
    print(neurona((1, 0), pesos, umbral))
    print(neurona((1, 1), pesos, umbral))
