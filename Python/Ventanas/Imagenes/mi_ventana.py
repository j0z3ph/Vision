from PySide6.QtWidgets import QMainWindow, QMessageBox, QApplication
from ventana_ui import *
import sys

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, *args, **kwargs):
        QMainWindow.__init__(self, *args, **kwargs)
        self.setupUi(self)
        
        self.pushButton.clicked.connect(self.click1)
        self.pushButton_2.clicked.connect(self.click2)
        
    def click1(self):
        msg = QMessageBox(self)
        msg.setWindowTitle("Mensaje")
        msg.setText(self.Input.text())
        msg.setStandardButtons(QMessageBox.StandardButton.Ok)
        msg.setIcon(QMessageBox.Icon.Information)
        msg.exec()
    
    def click2(self):
        QMessageBox.warning(self, "Mensaje x2", self.Input.text() + " x2")
        
    
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
