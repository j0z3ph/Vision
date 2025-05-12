import face_recognition
import cv2

camara = cv2.VideoCapture(0)

while cv2.waitKey(1) != 27:
    ret, imagen = camara.read()
    rgb = cv2.cvtColor(imagen, cv2.COLOR_BGR2RGB)
    # the second argument is the scale factor. 0 means no scale.    
    rects = face_recognition.face_locations(rgb, 0, "cnn")

    for y1, x2, y2, x1 in rects:
        cv2.rectangle(imagen, (x1, y1), (x2, y2), (0, 255, 0), 3)

    cv2.imshow('face_recognition', imagen)
    
camara.release()
cv2.destroyAllWindows()
