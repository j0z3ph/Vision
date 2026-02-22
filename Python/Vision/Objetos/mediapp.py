import mediapipe as mp
from mediapipe.tasks import python
from mediapipe.tasks.python import vision
import cv2
import numpy as np

video_cap = cv2.VideoCapture(0)

base_options = python.BaseOptions(model_asset_path='efficientdet_lite0.tflite')
options = vision.ObjectDetectorOptions(base_options=base_options, score_threshold=0.3)

with vision.ObjectDetector.create_from_options(options) as detector:
    while(True):
        ret, image_bgr = video_cap.read()
        image_rgb = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2RGB)
        
        mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=image_rgb)

        detection_result = detector.detect(mp_image)

        for detection in detection_result.detections:
            bbox = detection.bounding_box
            category = detection.categories[0]
            catmsg = f"{category.category_name} ({category.score:.2f})"
            cv2.putText(image_bgr, catmsg, (bbox.origin_x, bbox.origin_y - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)            
            cv2.rectangle(image_bgr, (bbox.origin_x, bbox.origin_y), (bbox.origin_x + bbox.width, bbox.origin_y + bbox.height), (0,255,0), 5)
        
        cv2.imshow("Image", image_bgr)
        cv2.waitKey(1)

