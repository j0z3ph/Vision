import pyfirmata
import time
from esp32board import esp32

# Creates a new board
board = pyfirmata.Board("/dev/cu.usbserial-0001", esp32, baudrate=115200)
pin2 = board.get_pin("d:2:o")

while True:
    pin2.write(1)
    time.sleep(1)
    pin2.write(0)
    time.sleep(1)


# close the serial connection
board.exit()
