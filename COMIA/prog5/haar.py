import cv2

camara = cv2.VideoCapture(0)
cascada_haar = 'haarcascade_frontalface_alt2.xml'  

# Clasficador en Cascada
clasificador = cv2.CascadeClassifier(cascada_haar)

if camara.isOpened():
    while cv2.waitKey(1) != 27:
        ret, imagen = camara.read()
        escala_gris = cv2.cvtColor(imagen, cv2.COLOR_BGR2GRAY)
        
        # Uso del clasificador
        caras = clasificador.detectMultiScale(escala_gris, 1.3, 5)
        for (x,y,w,h) in caras:
            cv2.rectangle(imagen, (x, y), (x+w, y+h), (0, 255, 0), 3)

        cv2.imshow('Caras', imagen)

camara.release()
cv2.destroyAllWindows()
