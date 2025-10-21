from PySide6.QtWidgets import QMainWindow
from PySide6 import QtWidgets
from PySide6.QtCore import QThread, Signal
from Test_ui import *
import sys
import simplecontroller as sc
import time


class ThreadAnalogIn(QThread):
    value = Signal(float)
    
    def __init__(self, board:sc.Board, pin:int):
        super().__init__()
        self.board = board
        self.pin = pin
        self.board.pinMode(pin, sc.INPUT)
        self.running = True

    def run(self):
        while(self.running):
            value =self.board.analogRead(self.pin)
            time.sleep(0.1)
            self.value.emit(value)

    def stop(self):
        self.running = False
        self.wait()

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, *args, **kwargs):
        QMainWindow.__init__(self, *args, **kwargs)
        self.setupUi(self)
        self.esp32 = sc.Board("COM4")
        self.LED = 2
        self.ANALOGIN = 13
        self.encendido = False
        self.btnLed.clicked.connect(self.digital_write)
        self.dial.valueChanged.connect(self.analog_write)
        self.analogInThread = ThreadAnalogIn(self.esp32, self.ANALOGIN)
        self.analogInThread.value.connect(self.analog_read)
        self.analogInThread.start()
    
    def analog_read(self, value):
        self.progressBar.setValue(value * 100)
    
    def analog_write(self):
        self.esp32.pinMode(self.LED, sc.OUTPUT)
        value = self.dial.value() / self.dial.maximum()
        self.esp32.analogWrite(self.LED, value)
    
    def digital_write(self):
        self.esp32.pinMode(self.LED, sc.OUTPUT)
        if(self.encendido):
            self.esp32.digitalWrite(self.LED, False)
            self.btnLed.setText("Prender")
            self.encendido = False
        else:
            self.esp32.digitalWrite(self.LED, True)
            self.btnLed.setText("Apagar")
            self.encendido = True
        
    
    def closeEvent(self, event):
        self.esp32.close()
        self.analogInThread.stop()
        return super().closeEvent(event)
    
if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
