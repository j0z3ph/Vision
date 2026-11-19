from PySide6.QtWidgets import QMainWindow, QApplication, QFileDialog
from PySide6.QtGui import QPixmap
from test_ui import Ui_MainWindow
import sys

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, *args, **kwargs):
        QMainWindow.__init__(self, *args, **kwargs)
        self.setupUi(self)   
        
        self.actionAbrir.triggered.connect(self.abrir_archivo)
    
    def abrir_archivo(self):
        dialog = QFileDialog(self)

        file, _ = dialog.getOpenFileName(self, "Abrir Imagen", "", "Imagenes (*.png *.jpg *bmp *.jpeg)")
        if file:
            img = QPixmap(file)
            self.label.setPixmap(img)
        
    
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
