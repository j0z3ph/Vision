import cv2
import numpy as np

img = cv2.imread("lenna.png", cv2.IMREAD_GRAYSCALE)

sobel_x = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])
sobel_y = np.array([[-1,-2,-1],[0,0,0],[1,2,1]])

gx = cv2.filter2D(img, -1, sobel_x)
gy = cv2.filter2D(img, -1, sobel_y)

g =  np.abs(gx) + np.abs(gy)

cv2.imshow("Original", img)
cv2.imshow("X", gx)
cv2.imshow("Y", gy)
cv2.imshow("G", g)

cv2.waitKey()
