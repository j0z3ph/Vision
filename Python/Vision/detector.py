import cv2
cap = cv2.VideoCapture(0)
clasificador = cv2.CascadeClassifier('haarcascades/aGest.xml')

while True:
    ret,frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    objects = clasificador.detectMultiScale(gray, 1.1, 4)

    for (x,y,w,h) in objects:
        cv2.rectangle(frame, (x,y),(x+w,y+h),(0,255,0),2)
        cv2.putText(frame,'Object',(x,y-10),2,0.7,(0,255,0),2,cv2.LINE_AA)

    cv2.imshow('Detector',frame)
    
    if cv2.waitKey(1) == 27:
        break
cap.release()
cv2.destroyAllWindows()