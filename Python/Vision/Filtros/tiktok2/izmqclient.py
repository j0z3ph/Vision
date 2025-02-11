from imutils.video import VideoStream
import imagezmq
import socket
import time

sender = imagezmq.ImageSender(connect_to="tcp://127.0.0.1:5555")

hostName = socket.gethostname()
vs = VideoStream(src=0).start()
time.sleep(2.0)
 
while True:
	frame = vs.read()
	sender.send_image(hostName, frame)