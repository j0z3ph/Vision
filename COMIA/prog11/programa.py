import cv2

camara = cv2.VideoCapture(0)

detector = cv2.FaceDetectorYN.create(
    "face_detection_yunet_2023mar.onnx",  "", (0, 0))

if camara.isOpened():
    ret, imagen = camara.read()
    height, width, _ = imagen.shape
    detector.setInputSize((width, height))
    while cv2.waitKey(1) != 27:
        ret, imagen = camara.read()
        _, faces = detector.detect(imagen)

        if faces is not None:
            for face in faces:
                # parameters: x1, y1, w, h, x_re, y_re, x_le, y_le, x_nt, y_nt, x_rcm, y_rcm, x_lcm, y_lcm
                # bouding box
                box = list(map(int, face[:4]))
                cv2.rectangle(imagen, box, (0, 255, 0), 5)
                # confidence
                confidence = face[-1]
                cv2.putText(imagen, f"Conf={confidence}", (box[0], box[1] - 10),
                            cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2, cv2.LINE_AA)
        
        cv2.imshow("YuNet", imagen)

camara.release()
cv2.destroyAllWindows()