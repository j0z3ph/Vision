''' NO FUNCIONA '''

import pyfirmata2
import time
from esp32board import esp32

# Creates a new board
board = pyfirmata2.Board("/dev/cu.usbserial-0001", esp32, baudrate=115200)
pin13 = board.get_pin("d:13:s")
#board.servo_config(13)

angle = 0

while True:
    pin13.write(angle)
    time.sleep(1)
    angle += 10
    if angle >= 180:
        angle = 0
