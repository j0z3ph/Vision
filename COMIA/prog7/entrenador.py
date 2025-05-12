import cv2
import numpy as np
MAXIMGS = 10

camara = cv2.VideoCapture(0)

clasificador = cv2.CascadeClassifier("haarcascade_frontalface_alt2.xml")
reconocedor = cv2.face.EigenFaceRecognizer().create()

print("Entrenador\n")
print("A continuación, se abrira la cámara y se mostrará un recuadro verde. " +
      "Presione la tecla 'c' para entrenar el rostro.")
print("Se requieren " + str(MAXIMGS) + " imágenes en diversas posiciones.")

imagenes = []
etiquetas = []
contador = 0
key = cv2.waitKey(1)

if camara.isOpened():
    while key != 27:
        ret, imagen = camara.read()
        escala_gris = cv2.cvtColor(imagen, cv2.COLOR_BGR2GRAY)
        # Uso del clasificador
        caras = clasificador.detectMultiScale(escala_gris, 1.3, 5)
        for (x,y,w,h) in caras:
            cv2.rectangle(imagen, (x, y), (x+w, y+h), (0, 255, 0), 3)
            cv2.putText(imagen, 'Muestra ' + str(contador + 1), (0, 40),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        1.5, (0, 0, 255), 3, cv2.LINE_AA)
            cv2.imshow("Entrenador", imagen)
            if key == ord('c'):
                cara = escala_gris[y:y+h, x:x+w]
                normal_imagen = cv2.resize(cara, (200, 200))
                imagenes.append(normal_imagen)
                etiquetas.append(contador)
                contador += 1
                if contador == MAXIMGS:
                    break
                
        key = cv2.waitKey(1)
        
        if contador == MAXIMGS:
            break

    # Entrena
    reconocedor.train(imagenes, np.array(etiquetas))
    reconocedor.save("entrenamiento.yaml")
    
    cv2.imshow("Media", reconocedor.getMean().reshape(200,200).clip(0,255).astype('uint8'))
    cv2.waitKey()

camara.release()
cv2.destroyAllWindows()