import pyfirmata2
import esp32board

def pinCallback(value):
    pin2.write(round(value,1))
    pin13.enable_reporting() # mandamos de nuevo el mensaje 

pyfirmata2.Board._handle_analog_message = esp32board.esp32_analog_message
    
board = pyfirmata2.Board("/dev/cu.usbserial-0001", esp32board.esp32, baudrate=115200)

board.samplingOn()

pin13 = board.get_pin('a:13:i')
pin2 = board.get_pin('d:2:p')
pin13.register_callback(pinCallback)
pin13.enable_reporting()

print("Enter para salir.")
input()
board.exit()
