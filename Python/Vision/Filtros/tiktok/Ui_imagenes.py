# Form implementation generated from reading ui file '/Users/j0z3ph/Repos/Vision/Python/Vision/Filtros/tiktok/imagenes.ui'
#
# Created by: PyQt6 UI code generator 6.4.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic6 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt6 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(324, 294)
        self.centralwidget = QtWidgets.QWidget(parent=MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.btnGlasses = QtWidgets.QPushButton(parent=self.centralwidget)
        self.btnGlasses.setObjectName("btnGlasses")
        self.gridLayout.addWidget(self.btnGlasses, 1, 0, 1, 1)
        self.btnMustach = QtWidgets.QPushButton(parent=self.centralwidget)
        self.btnMustach.setObjectName("btnMustach")
        self.gridLayout.addWidget(self.btnMustach, 1, 1, 1, 1)
        self.lbl_image = QtWidgets.QLabel(parent=self.centralwidget)
        self.lbl_image.setFrameShape(QtWidgets.QFrame.Shape.Box)
        self.lbl_image.setText("")
        self.lbl_image.setObjectName("lbl_image")
        self.gridLayout.addWidget(self.lbl_image, 0, 0, 1, 2)
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Filtros"))
        self.btnGlasses.setText(_translate("MainWindow", "Lentes"))
        self.btnMustach.setText(_translate("MainWindow", "Bigote"))