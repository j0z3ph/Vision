from PyQt6.QtWidgets import QMainWindow
from Ui_Ventana import *
import sys
from PyQt6.QtCore import QThread, pyqtSignal
import numpy as np

class ThreadCreaSecuencia(QThread):
    done = pyqtSignal()
    
    def __init__(self, secuence):
        super().__init__()
        self.__secuence = secuence

    def run(self):
        for i in self.__secuence:
            print(i + " ", end="")
            self.sleep(1)
        print()
        self.done.emit()


class ThreadLeeSecuencia(QThread):
    done = pyqtSignal(list, bool)
    
    def __init__(self, secuence):
        super().__init__()
        self.__secuence = secuence

    def run(self):
        x = input('Escriba la secuencia separada por espacios: ')
        lista = x.split()
        if lista and (lista == self.__secuence).all():
            self.done.emit(lista, True)
        else:
            self.done.emit(lista, False)
        print("Favor de ir a la aplicacion.")


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, *args, **kwargs):
        QMainWindow.__init__(self, *args, **kwargs)
        self.setupUi(self)
        self.btnInicio.clicked.connect(self.inicio)
        
    def inicio(self):
        self.btnInicio.setEnabled(False)
        self.lblMensaje.setText("Favor de ir a la consola.")
        self.secuencia = np.random.permutation(["a", "b", "c", "d"])
        self.threadsecuencia = ThreadCreaSecuencia(self.secuencia)
        self.threadsecuencia.done.connect(self.fin)
        self.threadsecuencia.start()
        
    def fin(self):
        self.threadleesecuencia = ThreadLeeSecuencia(self.secuencia)
        self.threadleesecuencia.done.connect(self.resultado)
        self.threadleesecuencia.start()
        
    def resultado(self, lista, ganador):
        self.btnInicio.setEnabled(True)
        str = ""
        if ganador:
            str = "GANADOR\n"
        else:
            str = "PERDEDOR\n"
        for i in lista:
            str = str + i + " "
        self.lblMensaje.setText(str)
        
    
if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
