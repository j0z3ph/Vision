import pyfirmata2
from esp32board import esp32

def pinCallback(value: bool):
    """Funcion de callback que sera ejecutada
    cuando ocurra el evento al que sea asociada.

    Args:
        value (bool): Valor del boton
    """
    global pin2
    pin2.write(value)
    
board = pyfirmata2.Board("/dev/cu.usbserial-0001", esp32, baudrate=115200)

# Activa el hilo de muestreo de puertos 
board.samplingOn()

pin13 = board.get_pin('d:13:i')
pin2 = board.get_pin('d:2:o')

pin13.register_callback(pinCallback)

# Activa el muestreo del pin 13
pin13.enable_reporting()

print("Enter para salir.")
input() # Detiene el proceso
board.exit()
