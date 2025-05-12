import cv2

camara = cv2.VideoCapture(0)

if camara.isOpened():
    while cv2.waitKey(1) != 27:
        capturada, imagen = camara.read()
        if capturada:
            cv2.imshow("COMIA", imagen)
camara.release()
cv2.destroyAllWindows()