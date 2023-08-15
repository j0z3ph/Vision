from PyQt6.QtWidgets import QMainWindow, QDialog
from Ui_mi_ventana import *
from Ui_dialogo import *
from PyQt6.uic import loadUi
import sys

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, *args, **kwargs):
        QMainWindow.__init__(self, *args, **kwargs)
        self.setupUi(self)
        # Se conecta el evento clicked con la funcion showDialog
        self.pushButton.clicked.connect(self.showDialog)
        
    def showDialog(self):
        dialog = MiDialogo(self)
        resp = dialog.exec()
        if resp == 1:
            user = dialog.edit_user.text()
            passw = dialog.edit_password.text()
            if user == "jlcruz" and passw == "abcd":
                self.label.setText("Bienvenido Jose Luis Cruz")
            else:
                self.label.setText("Bienvenido Desconocido")
        else:
            self.label.setText("Bienvenido Desconocido")

class MiDialogo(QDialog, Ui_Dialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)
        #loadUi("dialogo.ui", self)

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
