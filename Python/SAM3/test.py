from PIL import Image
from sam3 import build_sam3_image_model
from sam3.model.sam3_image_processor import Sam3Processor
import cv2 

# Load model (auto-downloads weights on first run)
model = build_sam3_image_model()
processor = Sam3Processor(model, confidence_threshold=0.5)

# Load and process an image
image = Image.open("b.png")
opencvimg = cv2.imread("b.png")
state = processor.set_image(image)

# Segment with text prompt
state = processor.set_text_prompt("orange ball", state)

# Access results
masks = state["masks"]       # Binary segmentation masks
boxes = state["boxes"]       # Bounding boxes [x0, y0, x1, y1]
scores = state["scores"]     # Confidence scores

print(f"Found {len(scores)} objects")

print(boxes)
print(scores)

for bb in boxes:
    print(bb)
    
    cv2.rectangle(opencvimg,  (int(bb[0]), int(bb[1])), (int(bb[2]), int(bb[3])), (0,255,0), 2)
    
cv2.imshow("Result", opencvimg)
cv2.waitKey()