"""
Perceptron entrenado para ser XOR 
Se usan los pesos de los perceptrones AND, OR y NOT
A XOR B = (A AND NOT B) OR (NOT A AND B) = OR(AND(A, NOT(B)), AND(NOT(A), B))
"""

umbral = 0.5  # umbral de activacion de la neurona (si el resultado es mayor al umbral, la neurona se activa)

pesosAND = [0.30000000000000004, 0.30000000000000004]  # obtenidos del entrenamiento para AND
pesosOR = [0.6, 0.6]  # obtenidos del entrenamiento para OR
pesosNOT = [0.6, -0.1]  # obtenidos del entrenamiento para NOT


def neurona(entrada, pesos, umbral):
    # multiplicamos cada entrada por su respectivo peso y los sumamos
    valor = 0
    for idx, x in enumerate(entrada):
        valor += x * pesos[idx]

    # devolvemos 1 si la neurona se activa, 0 si no se activa
    return int(valor > umbral)


def red_neuronal_XOR(entrada):
    # OR(AND(A, NOT(B)), AND(NOT(A), B))
    nA = neurona((1, entrada[0]), pesosNOT, umbral)  # NOT A (No olvidar agregar la entrada con 1 con la que se entreno la neurona)
    nB = neurona((1, entrada[1]), pesosNOT, umbral)  # NOT B (No olvidar agregar la entrada con 1 con la que se entreno la neurona)
    andAnB = neurona((entrada[0], nB), pesosAND, umbral)  # AND(A, NOT(B))
    andnAB = neurona((nA, entrada[1]), pesosAND, umbral)  # AND(NOT(A), B)
    xor = neurona((andAnB, andnAB), pesosOR, umbral)  # OR(AND(A, NOT(B)), AND(NOT(A), B))
    return xor


if __name__ == "__main__":
    print(f"Pesos finales AND: {pesosAND}")
    print(f"Pesos finales OR: {pesosOR}")
    print(f"Pesos finales NOT: {pesosNOT}")

    # probamos
    print(red_neuronal_XOR((0, 0)))
    print(red_neuronal_XOR((0, 1)))
    print(red_neuronal_XOR((1, 0)))
    print(red_neuronal_XOR((1, 1)))
