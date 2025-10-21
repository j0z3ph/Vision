import cv2 

image = cv2.imread("1.png")

hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)



cv2.imshow("Image", image)

cv2.waitKey()

cv2.destroyAllWindows()