from PyQt6 import QtGui, QtWidgets
from PyQt6.QtCore import QThread, pyqtSignal
from PyQt6.QtWidgets import QMainWindow
from Ui_imagenes import *
import numpy as np
import cv2
import sys


class VideoThread(QThread):
    change_pixmap_signal = pyqtSignal(np.ndarray)
    showMustache = False
    showGlasses = False

    def __init__(self):
        super().__init__()
        self._run_flag = True
        self.mustache = cv2.imread("imgs/mustache.png", cv2.IMREAD_UNCHANGED)
        self.glasses = cv2.imread("imgs/lentes.png", cv2.IMREAD_UNCHANGED)
        self.clasificador = cv2.CascadeClassifier(
            "haarcascades/haarcascade_frontalface_alt2.xml"
        )

    def run(self):
        cap = cv2.VideoCapture(0)
        if not cap.isOpened():
            print("Cannot open camera")
        else:
            while self._run_flag:
                ret, cv_img = cap.read()
                if ret:
                    cv_img = cv2.resize(
                        cv_img, (cv_img.shape[1] // 2, cv_img.shape[0] // 2)
                    )
                    faces = self.clasificador.detectMultiScale(cv_img)
                    for x, y, w, h in faces:
                        if self.showGlasses:
                            tmp = cv2.resize(self.glasses, (w, int(h * 0.2)))
                            self.add_transparent_image(cv_img, tmp, x, y + int(h * 0.3))

                        if self.showMustache:
                            tmp = cv2.resize(
                                self.mustache, (int(w * 0.8), int(h * 0.2))
                            )
                            self.add_transparent_image(
                                cv_img, tmp, x + int(w * 0.1), y + int(h * 0.65)
                            )

                        # cv2.rectangle(cv_img, (x, y), (x+w, y+h), (255, 0, 0), 2)
                    self.change_pixmap_signal.emit(cv_img)
        cap.release()

    def stop(self):
        self._run_flag = False
        self.wait()

    def add_transparent_image(
        self, background, foreground, x_offset=None, y_offset=None
    ):
        """
        https://stackoverflow.com/questions/40895785/using-opencv-to-overlay-transparent-image-onto-another-image
        """
        bg_h, bg_w, bg_channels = background.shape
        fg_h, fg_w, fg_channels = foreground.shape

        if x_offset is None:
            x_offset = (bg_w - fg_w) // 2
        if y_offset is None:
            y_offset = (bg_h - fg_h) // 2

        w = min(fg_w, bg_w, fg_w + x_offset, bg_w - x_offset)
        h = min(fg_h, bg_h, fg_h + y_offset, bg_h - y_offset)

        if w < 1 or h < 1:
            return

        bg_x = max(0, x_offset)
        bg_y = max(0, y_offset)
        fg_x = max(0, x_offset * -1)
        fg_y = max(0, y_offset * -1)
        foreground = foreground[fg_y : fg_y + h, fg_x : fg_x + w]
        background_subsection = background[bg_y : bg_y + h, bg_x : bg_x + w]

        foreground_colors = foreground[:, :, :3]
        alpha_channel = foreground[:, :, 3] / 255  # 0-255 => 0.0-1.0

        alpha_mask = np.dstack((alpha_channel, alpha_channel, alpha_channel))

        composite = (
            background_subsection * (1 - alpha_mask) + foreground_colors * alpha_mask
        )

        background[bg_y : bg_y + h, bg_x : bg_x + w] = composite


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, *args, **kwargs):
        QMainWindow.__init__(self, *args, **kwargs)
        self.setupUi(self)
        self.vthread = VideoThread()
        self.vthread.change_pixmap_signal.connect(self.update_image)
        # start the thread
        self.vthread.start()
        self.btnGlasses.clicked.connect(self.addGlasses)
        self.btnMustach.clicked.connect(self.addMustache)

    def addMustache(self):
        self.vthread.showMustache = not self.vthread.showMustache

    def addGlasses(self):
        self.vthread.showGlasses = not self.vthread.showGlasses

    def closeEvent(self, event):
        self.vthread.stop()
        event.accept()

    def update_image(self, cv_img):
        self.cv_img = cv_img
        self.lbl_image.setPixmap(self.convert_cv_qt(self.cv_img))

    def convert_cv_qt(self, cv_img):
        """Convert from an opencv image to QPixmap"""
        rgb_image = cv2.cvtColor(cv_img, cv2.COLOR_BGR2RGB)
        h, w, ch = rgb_image.shape
        bytes_per_line = ch * w
        converted_image = QtGui.QImage(
            rgb_image.data, w, h, bytes_per_line, QtGui.QImage.Format.Format_RGB888
        )
        return QtGui.QPixmap.fromImage(converted_image)


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())