import pyfirmata2
from esp32board import esp32
import time

def pinCallback(value):
    """Funcion de callback que sera ejecutada
    cuando ocurra el evento al que sea asociada.

    Args:
        value (float): Valor obtenido de la entrada analogica
    """
    # con ESP32 el valor maximo es 4095, mientras que con Arduino es 1023.
    # El valor devuelto se mapea entre 0 y 1 tomando como base el valor maximo de Arduino,
    # por lo que ajustamos dividiendo entre 4.0029 ya que 4095/1023 es 4.00293255
    print(f"{value / 4.0029}") 
    pin13.enable_reporting() # mandamos de nuevo el mensaje 
    
board = pyfirmata2.Board("/dev/cu.usbserial-0001", esp32, baudrate=115200)
board.samplingOn()

pin13 = board.get_pin('a:13:i')
pin13.register_callback(pinCallback)
pin13.enable_reporting()

time.sleep(10)
board.exit()
