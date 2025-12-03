import cv2
import numpy as np


vid = cv2.VideoCapture(0)

while cv2.waitKey(1) != 27:
    ret, img = vid.read()
    gris = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    #img = cv2.imread("lenna.png", cv2.IMREAD_GRAYSCALE)

    sobel_x = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])
    sobel_y = np.array([[-1,-2,-1],[0,0,0],[1,2,1]])

    gx = cv2.filter2D(gris, -1, sobel_x)
    gy = cv2.filter2D(gris, -1, sobel_y)

    #g = np.sqrt(gx**2 + gy**2)
    g =  np.abs(gx) + np.abs(gy)

    cv2.imshow("Original", img)
    cv2.imshow("X", gx)
    cv2.imshow("Y", gy)
    cv2.imshow("G", g)

cv2.destroyAllWindows()
