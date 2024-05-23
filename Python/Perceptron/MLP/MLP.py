import numpy as np

class MLP:
    """Clase Multi-Layer perceptron
    Implementacion de una red con una capa oculta de dos neuronas y una
    capa de salida con una neurona.
    Se esperan dos entradas, por lo que se deben aplicar dos pesos (uno por entrada) y
    un umbral de activacion a la primer neurona de entrada.
    Como la capa oculta es de dos neuronas, se requiere aplicar otros dos pesos
    a las entradas y el mismo umbral a la segunda neurona de entrada.
    
    Cada neurona de la capa oculta aplicara un peso a su salida, por lo que
    se necesitan dos pesos adicionales, para aplicarlos a las dos salidas 
    de las neuronas de la capa oculta, y un nuevo umbral para su activacion.
    
    Por lo tanto, se requieren seis pesos y dos umbrales. 4 pesos para la capa de entrada 
    y la capa oculta. 2 pesos para la capa oculta y la salida. 1 umbral para la entrada a la
    capa oculta. 1 umbral para capa oculta y la salida.
    
    Entrada1 - w1 -
                    > u1 - NeuronaOculta1 - w5 -
    Entrada2 - w2 -                              \
                                                    > u2 - Salida
    Entrada1 - w3 -                              /
                    > u1 - NeuronaOculta2 - w6 -
    Entrada2 - w4 -
    """

    def __init__(self) -> None:
        self.umbral1 = -0.5
        self.umbral2 = -0.5
        self.perdidas = []

    def entrenar(
        self,
        datos_entrenamiento,
        salidas_esperadas,
        taza_aprendizaje=0.01,
        epochs=5000
    ):
        self.taza_aprendizaje = taza_aprendizaje
        self.datos_entrenamiento = datos_entrenamiento
        self.salidas_esperadas = salidas_esperadas
        self.epochs = epochs
        
        self.pesos12 = np.zeros(len(datos_entrenamiento[0])) # Pesos de la neurona de entrada 1
        self.pesos34 = np.zeros(len(datos_entrenamiento[0])) # Pesos de la neurona de entrada 2
        
        self.pesos56 = np.zeros(2) # Pesos de las neuronas de la capa oculta (2 porque son 2 neuronas)
        
        for epoch in range(self.epochs):
            self.propagacion_adelante(self.datos_entrenamiento)
            self.propagacion_atras()    
                
            if epoch % 500 == 0:
                print("Loss: ", self.perdidas[epoch]) 
        
        
        
    def propagacion_adelante(self, entradas):
        self.salida_oculta = []
        self.salida_final = []
        
        for entrada in entradas:
            # Capa de entrada
            valorE1 = 0
            valorE2 = 0
            valorOculto = 0
            
            # Entrada 1
            for idx, x in enumerate(entrada):
                valorE1 += x * self.pesos12[idx]
            valorE1 += self.umbral1
            
            # Entrada 2
            for idx, x in enumerate(entrada):
                valorE2 += x * self.pesos34[idx]
            valorE2 += self.umbral1
            
            # Funcion de activacion de la capa de entrada
            res1 = self.activacion(valorE1)
            res2 = self.activacion(valorE2)
            
            self.salida_oculta.append([res1, res2])
            
            # Capa oculta
            
            for idx, x in enumerate([res1, res2]):
                valorOculto += x * self.pesos56[idx]
            valorOculto += self.umbral2
            
            res_final = self.activacion(valorOculto)
            
            self.salida_final.append(res_final)
                
        return self.salida_final
            
    def propagacion_atras(self):
        perdida = 0
        for indice, x in enumerate(self.salidas_esperadas):
            perdida += self.error(self.salidas_esperadas[indice], self.salida_final[indice])
        self.perdidas.append(perdida)
        
        for indice, x in enumerate(self.datos_entrenamiento):
            error = self.salidas_esperadas[indice] - self.salida_final[indice]
            
            self.pesos12[0] += x[0] * error * (self.gradiente(self.salida_final[indice]) * self.pesos56[0] * self.gradiente(self.salida_oculta[indice][0])) * self.taza_aprendizaje
            self.pesos12[1] += x[1] * error * (self.gradiente(self.salida_final[indice]) * self.pesos56[1] * self.gradiente(self.salida_oculta[indice][1])) * self.taza_aprendizaje
            
            self.pesos34[0] += x[0] * error * (self.gradiente(self.salida_final[indice]) * self.pesos56[0] * self.gradiente(self.salida_oculta[indice][0])) * self.taza_aprendizaje
            self.pesos34[1] += x[1] * error * (self.gradiente(self.salida_final[indice]) * self.pesos56[1] * self.gradiente(self.salida_oculta[indice][1])) * self.taza_aprendizaje
            
            self.pesos56[0] += self.salida_oculta[indice][0] * error * self.gradiente(self.salida_final[indice]) * self.taza_aprendizaje
            self.pesos56[1] += self.salida_oculta[indice][1] * error * self.gradiente(self.salida_final[indice]) * self.taza_aprendizaje
                
            self.umbral1 += error * (self.gradiente(self.salida_final[indice]) * self.pesos56[0] * self.gradiente(self.salida_oculta[indice][0])) * self.taza_aprendizaje
            self.umbral1 += error * (self.gradiente(self.salida_final[indice]) * self.pesos56[1] * self.gradiente(self.salida_oculta[indice][1])) * self.taza_aprendizaje
            
            self.umbral2 += error * self.gradiente(self.salida_final[indice]) * self.taza_aprendizaje
        
        
        
    def gradiente(self, valor):
        # derivada de la funcion sigmoide
        return valor * (1 - valor)
            
            
    def clasificar(self, entrada):
        return self.propagacion_adelante([entrada])

    def activacion(self, valor):
        # Funcion sigmoide
        return 1 / (1 + np.exp(-valor))

    def error(self, salida_deseada, resultado):
        # Error cuadratico medio
        return 0.5 * (salida_deseada - resultado)**2


if __name__ == "__main__":
    entradas = [(0, 0), (0, 1), (1, 0), (1, 1)]
    salidas = [0, 1, 1, 0]
    
    nn = MLP()
    nn.entrenar(entradas, salidas)
    # probamos
    print(nn.clasificar((0,0)))
    print(nn.clasificar((0, 1)))
    print(nn.clasificar((1, 0)))
    print(nn.clasificar((1, 1)))
    
    