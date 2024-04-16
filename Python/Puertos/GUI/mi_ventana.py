from PyQt6.QtWidgets import QMainWindow
from Ui_motor import *
import sys
import pyfirmata
import time
import inspect


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, *args, **kwargs):
        QMainWindow.__init__(self, *args, **kwargs)
        self.setupUi(self)
        self.dial.valueChanged.connect(self.mueveMotor)
        
    def mueveMotor(self, value):
        print(value)
        pin9.write(value)
        


if __name__ == "__main__":
    if not hasattr(inspect, 'getargspec'):
        inspect.getargspec = inspect.getfullargspec
            
    board=pyfirmata.Arduino('/dev/cu.usbmodem14201')

    it = pyfirmata.util.Iterator(board)
    it.start()

    pin9 = board.get_pin('d:9:s') # s para servo

    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
