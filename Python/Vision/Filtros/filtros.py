import cv2
import numpy as np

img = cv2.imread("lenna.png")
height, width, channels = img.shape
#kernel = np.array([[1/9,1/9,1/9],[1/9,1/9,1/9],[1/9,1/9,1/9]])
#kernel = np.array([[-1,-1,-1],[-1,8,-1],[-1,-1,-1]]) #aplicar a ecala de grises
kernel = np.array([[0,-1,0],[-1,5,-1],[0,-1,0]])
xmed = kernel.shape[0]//2
ymed = kernel.shape[1]//2

timg = np.zeros((height, width, channels), np.uint8)

for i in range(ymed, height - ymed):
    for j in range(xmed, width - xmed):
        acc = 0
        for ik in range(kernel.shape[0]):
            for jk in range(kernel.shape[1]):
                acc += img[i-ymed+ik, j-ymed+jk].astype("int16") * kernel[ik,jk]
        timg[i,j] = np.clip(acc, 0, 255).astype("uint8")
        
cv2.imshow("Blur", timg)
cv2.waitKey()
cv2.destroyAllWindows()
