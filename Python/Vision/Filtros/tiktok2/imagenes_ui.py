# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'imagenes.ui'
##
## Created by: Qt User Interface Compiler version 6.8.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QFrame, QGridLayout, QLabel,
    QMainWindow, QPushButton, QSizePolicy, QWidget)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(324, 294)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.gridLayout = QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.btnGlasses = QPushButton(self.centralwidget)
        self.btnGlasses.setObjectName(u"btnGlasses")

        self.gridLayout.addWidget(self.btnGlasses, 1, 0, 1, 1)

        self.btnMustach = QPushButton(self.centralwidget)
        self.btnMustach.setObjectName(u"btnMustach")

        self.gridLayout.addWidget(self.btnMustach, 1, 1, 1, 1)

        self.lbl_image = QLabel(self.centralwidget)
        self.lbl_image.setObjectName(u"lbl_image")
        self.lbl_image.setFrameShape(QFrame.Box)

        self.gridLayout.addWidget(self.lbl_image, 0, 0, 1, 2)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Filtros", None))
        self.btnGlasses.setText(QCoreApplication.translate("MainWindow", u"Lentes", None))
        self.btnMustach.setText(QCoreApplication.translate("MainWindow", u"Bigote", None))
        self.lbl_image.setText("")
    # retranslateUi

