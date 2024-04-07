import pyfirmata
import time
import inspect

if not hasattr(inspect, 'getargspec'):
    inspect.getargspec = inspect.getfullargspec


board = pyfirmata.Arduino('/dev/cu.usbserial-0001')

it = pyfirmata.util.Iterator(board)
it.start()

analog_value = 0

def handle_read(*data):
    global analog_value
    analog_value = sum(data)
    
board.add_cmd_handler(0x02, handle_read)

def writePwmValue(pin, value):
    datasToWrite = []

    datasToWrite.append(pin)
    datasToWrite.append(0)
    datasToWrite.append(15)
    datasToWrite.append(10)

    v = divmod(value, 127)

    for i in range(1, v[0]):
        datasToWrite.append(127)

    if (v[0] >= 1):
        datasToWrite.append(v[1])
    else:
        datasToWrite.append(value)

    print(datasToWrite)
    return datasToWrite

while True:
    board.send_sysex(0x02, [12])
    board.send_sysex(0x04, writePwmValue(13, analog_value))
    time.sleep(0.01)
