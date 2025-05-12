import cv2
import numpy as np
MAXIMGS = 10

camara = cv2.VideoCapture(0)

clasificador = cv2.CascadeClassifier("haarcascade_frontalface_alt2.xml")
reconocedor = cv2.face.LBPHFaceRecognizer().create()
reconocedor.read("entrenamiento.yaml")

if camara.isOpened():
    while cv2.waitKey(1) != 27:
        ret, imagen = camara.read()
        escala_gris = cv2.cvtColor(imagen, cv2.COLOR_BGR2GRAY)
        # Uso del clasificador
        caras = clasificador.detectMultiScale(escala_gris, 1.3, 5)
        for (x,y,w,h) in caras:
            cv2.rectangle(imagen, (x, y), (x+w, y+h), (0, 255, 0), 3)
            cara = escala_gris[y:y+h, x:x+w]
            normal_imagen = cv2.resize(cara, (200, 200))
            etiqueta, confidencia = reconocedor.predict(normal_imagen)
            cv2.putText(imagen, f"id={etiqueta}, conf={confidencia}", (x, y-10),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        1, (0, 0, 255), 2, cv2.LINE_AA)
            #print(etiqueta, confidencia)
            
        cv2.imshow("Reconocedor", imagen)
                
camara.release()
cv2.destroyAllWindows()