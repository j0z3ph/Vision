import pyfirmata
import time
import inspect

if not hasattr(inspect, 'getargspec'):
    inspect.getargspec = inspect.getfullargspec


board = pyfirmata.Arduino('/dev/cu.usbserial-0001')

it = pyfirmata.util.Iterator(board)
it.start()

angle = 0

def writePWNToServo(pin, angle):
    __servo_pwm_freq = 50 # Para este servo, la frecuencia de trabajo es de 50 Hz
    __min_u10_duty = 26 # offset for correction
    __max_u10_duty = 123 # offset for correction
    min_angle = 0
    max_angle = 180
    __angle_conversion_factor = (__max_u10_duty - __min_u10_duty) / (max_angle - min_angle)
    
    duty_u10 = int((angle - min_angle) * __angle_conversion_factor) + __min_u10_duty
    
    datasToWrite = []

    datasToWrite.append(pin)
    datasToWrite.append(0) #Canal (hasta 16 canales para el ESP32, hasta 8 canales para el ESP32S2)
    datasToWrite.append(0) #Multiplo de la frecuencia: Hz=0, KHz=1, MHz=2 
    datasToWrite.append(__servo_pwm_freq) #Frecuencia (desde 50 Hz hasta 40 MHz)
    datasToWrite.append(10) #Resolución en bits (de 1 a 15) (10 es 2^10, es decir valores d0 1 hasta 1023)

    v = divmod(duty_u10, 127)

    for i in range(1, v[0]):
        datasToWrite.append(127)

    if (v[0] >= 1):
        datasToWrite.append(v[1])
    else:
        datasToWrite.append(duty_u10)

    print(datasToWrite)
    return datasToWrite

while True:
    board.send_sysex(0x04, writePWNToServo(13, angle))
    time.sleep(1)
    angle += 10
    if angle >= 180:
        angle = 0
