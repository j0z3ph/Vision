import cv2
import numpy as np

img = cv2.imread("test.png")

#cv2.MORPH_CROSS
#cv2.MORPH_RECT
#cv2.MORPH_ELLIPSE

kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, (5,5))
#print(kernel)

res = cv2.dilate(img, kernel)

cv2.imshow("test", img)
cv2.imshow("Dilatacion", res)
cv2.waitKey()