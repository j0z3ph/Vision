import cv2
import numpy as np

imagen = cv2.imread("logo.png")
kernel = np.array([[1/9,1/9,1/9],[1/9,1/9,1/9],[1/9,1/9,1/9]])
#kernel = np.array([[0,-1,0],[-1,5,-1],[0,-1,0]])
filtrada = cv2.filter2D(imagen, -1, kernel)

cv2.imshow("Original", imagen)
cv2.imshow("Filtro", filtrada)
cv2.waitKey(0)
