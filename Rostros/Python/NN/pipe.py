import mediapipe as mp
from mediapipe.tasks import python
from mediapipe.tasks.python import vision
import cv2

model_path = '/Users/j0z3ph/Repos/Vision/Rostros/Python/NN/blaze_face_short_range.tflite'

BaseOptions = mp.tasks.BaseOptions
FaceDetector = mp.tasks.vision.FaceDetector
FaceDetectorOptions = mp.tasks.vision.FaceDetectorOptions
VisionRunningMode = mp.tasks.vision.RunningMode

# Create a face detector instance with the video mode:
options = FaceDetectorOptions(
    base_options=BaseOptions(model_asset_path=model_path),
    running_mode=VisionRunningMode.IMAGE)
with FaceDetector.create_from_options(options) as detector:
  cam = cv2.VideoCapture(0)
  while True:
    _, frame = cam.read()
      
    mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=frame)
    face_detector_result = detector.detect(mp_image)
    
    for detection in face_detector_result.detections:
        # Draw bounding_box
        bbox = detection.bounding_box
        start_point = bbox.origin_x, bbox.origin_y
        end_point = bbox.origin_x + bbox.width, bbox.origin_y + bbox.height
        cv2.rectangle(frame, start_point, end_point, (255,0,0), 3)
    
    cv2.imshow('Frame', frame)
    if cv2.waitKey(1) == 27:
        break
    
