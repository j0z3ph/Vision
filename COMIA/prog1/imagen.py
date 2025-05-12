from PIL import Image

rgb = ((255,0,0), (0,255,0), (0,0,255))
img = Image.new('RGB', (3, 1))
img.putdata(rgb)
img.save('image.png')

