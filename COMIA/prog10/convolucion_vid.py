import cv2
import numpy as np

camara = cv2.VideoCapture(0)
#kernel = np.array([[1/9,1/9,1/9],[1/9,1/9,1/9],[1/9,1/9,1/9]])
kernel = np.ones((9,9))/81
#kernel = np.array([[0,-1,0],[-1,5,-1],[0,-1,0]])

if camara.isOpened():
    while cv2.waitKey(1) != 27:
        ret, imagen = camara.read()
        if ret:
            filtrada = cv2.filter2D(imagen, -1, kernel)

        cv2.imshow("Original", imagen)
        cv2.imshow("Filtro", filtrada)

camara.release()
cv2.destroyAllWindows()
