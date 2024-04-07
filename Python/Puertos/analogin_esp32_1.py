import pyfirmata
import time
import inspect

if not hasattr(inspect, 'getargspec'):
    inspect.getargspec = inspect.getfullargspec

board = pyfirmata.Arduino('/dev/cu.usbserial-0001')

it = pyfirmata.util.Iterator(board)
it.start()

def handle_read(*data):
    analog_value = sum(data)/1023
    print(analog_value)

board.add_cmd_handler(0x02, handle_read)

while True:
    board.send_sysex(0x02, [12])
    time.sleep(0.1)
