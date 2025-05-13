import cv2
import numpy as np

camara = cv2.VideoCapture(0)

filtro_x = np.array([[-1, 0, 1],[-2, 0, 2],[-1, 0, 1]])
filtro_y = np.array([[-1,-2,-1],[0,0,0],[1,2,1],])


if camara.isOpened():
    while cv2.waitKey(1) != 27:
        ret, imagen = camara.read()
        if ret:
            gris = cv2.cvtColor(imagen, cv2.COLOR_BGR2GRAY)
            gx = cv2.filter2D(gris, -1, filtro_x)
            gy = cv2.filter2D(gris, -1, filtro_y)
            sobel = (np.abs(gx) + np.abs(gy)).astype("uint8")
            
            cv2.imshow("Original", imagen)
            cv2.imshow("Sobel", sobel)
            
camara.release()
cv2.destroyAllWindows()