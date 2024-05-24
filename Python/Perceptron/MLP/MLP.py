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
        self.umbral1 = np.random.uniform()
        self.umbral2 = np.random.uniform()
        self.perdidas = []

    def entrenar(
        self,
        datos_entrenamiento,
        salidas_esperadas,
        taza_aprendizaje=0.2,
        epochs=5000
    ):
        self.taza_aprendizaje = taza_aprendizaje
        self.datos_entrenamiento = datos_entrenamiento
        self.salidas_esperadas = salidas_esperadas
        self.epochs = epochs
        
        self.pesos12 = np.random.uniform(size=len(datos_entrenamiento[0])) # Pesos de la neurona de entrada 1
        self.pesos34 = np.random.uniform(size=len(datos_entrenamiento[0])) # Pesos de la neurona de entrada 2
        
        self.pesos56 = np.random.uniform(size=2) # Pesos de las neuronas de la capa oculta (2 porque son 2 neuronas)
        
        for epoch in range(self.epochs):
            for idx, entrada in enumerate(self.datos_entrenamiento):
                self.propagacion_adelante(entrada)
                self.propagacion_atras(entrada, self.salidas_esperadas[idx])    
                
            if epoch % 500 == 0:
                print("Loss: ", self.perdidas[epoch * len(self.datos_entrenamiento)]) 
        
        
        
    def propagacion_adelante(self, entrada):
        #self.salida_oculta = []
        #self.salida_final = []
        
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
        
        #print(valorE1, valorE2)
        #print(np.dot(entrada, self.pesos12) + self.umbral1)
        #print(np.dot(entrada, self.pesos34) + self.umbral1)
        
        # Funcion de activacion de la capa de entrada
        res1 = self.activacion(valorE1)
        res2 = self.activacion(valorE2)
        
        self.salida_oculta = [res1, res2]
        
        # Capa oculta
        
        for idx, x in enumerate([res1, res2]):
            valorOculto += x * self.pesos56[idx]
        valorOculto += self.umbral2
        
        #print(valorOculto)
        #print(np.dot(self.salida_oculta, self.pesos56) + self.umbral2)
        
        self.salida_final = self.activacion(valorOculto)
        
        #print(self.salida_final)
            
        return self.salida_final
            
    def propagacion_atras(self, entrada, salida_esperada):
        
        perdida = self.error(salida_esperada, self.salida_final)
        self.perdidas.append(perdida)
        
        error = salida_esperada - self.salida_final
        #print(error)
        
        for idx, x in enumerate(entrada):
            self.pesos12[idx] += x * error * (self.gradiente(self.salida_final) * self.pesos56[idx] * self.gradiente(self.salida_oculta[idx])) * self.taza_aprendizaje
            self.pesos34[idx] += x * error * (self.gradiente(self.salida_final) * self.pesos56[idx] * self.gradiente(self.salida_oculta[idx])) * self.taza_aprendizaje
            self.pesos56[idx] += self.salida_oculta[idx] * error * self.gradiente(self.salida_final) * self.taza_aprendizaje 
            self.umbral1 += error * (self.gradiente(self.salida_final) * self.pesos56[idx] * self.gradiente(self.salida_oculta[idx])) * self.taza_aprendizaje
            
        self.umbral2 += error * self.gradiente(self.salida_final) * self.taza_aprendizaje
    
        
        
    def gradiente(self, valor):
        # derivada de la funcion sigmoide
        return valor * (1 - valor)
            
            
    def clasificar(self, entrada):
        #return int(self.propagacion_adelante(entrada)>0.5)
        return self.propagacion_adelante(entrada)

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
    nn.entrenar(entradas, salidas, 0.2, 30000)
    # probamos
    print(nn.clasificar((0, 0)))
    print(nn.clasificar((0, 1)))
    print(nn.clasificar((1, 0)))
    print(nn.clasificar((1, 1)))
    
    