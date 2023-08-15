import cv2
import numpy as np

img = cv2.imread("lenna.png")
height, width, channels = img.shape
vals = np.array([[1/3],[1/3],[1/3]])
grayimg = np.clip(img.dot(vals), 0, 255).astype('uint8')
cv2.imshow("Gris", grayimg)
cv2.waitKey()
cv2.destroyAllWindows()
