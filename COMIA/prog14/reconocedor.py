import cv2

camara = cv2.VideoCapture(0)

detector = cv2.FaceDetectorYN.create(
    "face_detection_yunet_2023mar.onnx",  "", (0, 0))
recognizer = cv2.FaceRecognizerSF.create(
            "face_recognizer_fast.onnx","")

if camara.isOpened():
    yo = cv2.imread("1.jpg")
    height, width, _ = yo.shape
    detector.setInputSize((width, height))
    _, cara_original = detector.detect(yo)
    ret, imagen = camara.read()
    height, width, _ = imagen.shape
    detector.setInputSize((width, height))
    while cv2.waitKey(1) != 27:
        ret, imagen = camara.read()
        _,faces = detector.detect(imagen)

        if faces is not None:
            for face in faces:
                #v2.imwrite("1.jpg",imagen)
                face1_align = recognizer.alignCrop(yo, cara_original[0])
                face2_align = recognizer.alignCrop(imagen, face)
    
                # Extract features
                face1_feature = recognizer.feature(face1_align)
                face2_feature = recognizer.feature(face2_align)
                
                cosine_score = recognizer.match(face1_feature, face2_feature, cv2.FaceRecognizerSF_FR_COSINE)
                l2_score = recognizer.match(face1_feature, face2_feature, cv2.FaceRecognizerSF_FR_NORM_L2)
                
                # parameters: x1, y1, w, h, x_re, y_re, x_le, y_le, x_nt, y_nt, x_rcm, y_rcm, x_lcm, y_lcm
                # bouding box
                box = list(map(int, face[:4]))
                cv2.rectangle(imagen, box, (0, 255, 0), 5)
                
                cv2.putText(imagen, f"Cosine={cosine_score:.3}, l2={l2_score:.3}", (box[0], box[1] - 10),
                            cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2, cv2.LINE_AA)
        
        cv2.imshow("YuNet", imagen)

camara.release()
cv2.destroyAllWindows()