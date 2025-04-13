from deepface import DeepFace
import cv2


cam = cv2.VideoCapture(0)

while True:
    _, frame = cam.read()
    
    result = DeepFace.verify(frame, "1.jpg", enforce_detection=False)
    
    cv2.imshow('Frame', frame)

    print(result['verified'])
    
    if cv2.waitKey(1) == 27:
        break