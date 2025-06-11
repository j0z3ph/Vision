from PySide6 import QtGui, QtWidgets
from PySide6.QtCore import QThread, Signal
from PySide6.QtWidgets import QMainWindow
from imagenes_ui import *
import numpy as np
import socket, cv2, pickle, struct
import sys

socket.setdefaulttimeout(2)

class RemoteVideoReceiver(QThread):
    video_received = Signal(np.ndarray)

    def __init__(self, socket):
        super().__init__()
        self._run_flag = True
        self.client_socket = socket

    def run(self):
        # Init Message
        self.client_socket.send(b"Receiver")
        while self.client_socket.recv(1024).decode() != "OK":
            pass
        while self._run_flag:
            try:
                data = b""
                payload_size = struct.calcsize("Q")

                while len(data) < payload_size:
                    packet = self.client_socket.recv(4 * 1024)  # 4K
                    if not packet:
                        break
                    data += packet
                packed_msg_size = data[:payload_size]
                data = data[payload_size:]
                msg_size = struct.unpack("Q", packed_msg_size)[0]

                while len(data) < msg_size:
                    data += self.client_socket.recv(4 * 1024)
                frame_data = data[:msg_size]
                data = data[msg_size:]
                frame = pickle.loads(frame_data)
                nparr = np.frombuffer(frame, np.uint8)
                cv_img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
                self.video_received.emit(cv_img)
            except:
                cv_img = np.zeros((200, 600, 3), dtype=np.uint8)
                cv2.putText(
                    cv_img,
                    "Sin conexion",
                    (10, 50),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    1,
                    (0, 255, 0),
                    2,
                    cv2.LINE_AA,
                )
                self.video_received.emit(cv_img)

    def stop(self):
        self._run_flag = False
        self.wait()


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, *args, **kwargs):
        QMainWindow.__init__(self, *args, **kwargs)
        self.setupUi(self)
        self.setWindowTitle("Video Receiver")

        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        host_ip = '127.0.0.1'
        port = 65535
        #host_ip = "34.31.147.126"
        #port = 80
        self.client_socket.connect((host_ip, port))

        self.vthread = RemoteVideoReceiver(self.client_socket)
        self.vthread.video_received.connect(self.update_image)
        # start the thread
        self.vthread.start()
        self.btnGlasses.setDisabled(True)
        self.btnMustach.setDisabled(True)
        self.btnGlasses.setVisible(False)
        self.btnMustach.setVisible(False)
                
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
