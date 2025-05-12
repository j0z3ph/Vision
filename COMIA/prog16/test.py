from deepface import DeepFace
import cv2

cam = cv2.VideoCapture(0)

while cv2.waitKey(1) != 27:
    _, frame = cam.read()
    result = DeepFace.verify(frame, "1.jpg", enforce_detection=False)
    if result:
        rect = result["facial_areas"]["img1"]
        cv2.rectangle(frame, (rect["x"], rect["y"]), (rect["x"] + rect["w"], rect["y"] + rect["h"]), (0, 255, 0), 3)
        cv2.putText(frame,f'Verified={result["verified"]}, dist={result["distance"]:.4}', (rect["x"], rect["y"]-10), cv2.FONT_HERSHEY_SIMPLEX,
                    1, (0, 255, 0), 3)
    #objs = DeepFace.analyze(frame, actions = ['age', 'gender', 'race', 'emotion'])
    cv2.imshow('Deepface', frame)
    print(result)
    

cam.release()
cv2.destroyAllWindows()