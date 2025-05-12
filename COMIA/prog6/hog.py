import dlib
import cv2

camara = cv2.VideoCapture(0)
detector = dlib.get_frontal_face_detector()  # hog

if camara.isOpened():
    while cv2.waitKey(1) != 27:
        ret, imagen = camara.read()
        rgb = cv2.cvtColor(imagen, cv2.COLOR_BGR2RGB)
        # perform face detection using dlib's face detector
        # the second argument is the scale factor. 0 means no scale.
        rects = detector(rgb, 0)

        for rect in rects:
            cv2.rectangle(imagen, (rect.left(), rect.top()),
                          (rect.right(), rect.bottom()), (0, 255, 0), 3)

        cv2.imshow("Caras", imagen)

camara.release()
cv2.destroyAllWindows()