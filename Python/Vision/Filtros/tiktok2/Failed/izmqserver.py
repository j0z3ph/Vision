from imutils import build_montages
from datetime import datetime
import numpy as np
import imagezmq
import argparse
import imutils
import cv2

# stores the estimated number of Pis, active checking period, and
# calculates the duration seconds to wait before making a check to
# see if a device was active
ESTIMATED_NUM_PIS = 4
ACTIVE_CHECK_PERIOD = 10
ACTIVE_CHECK_SECONDS = ESTIMATED_NUM_PIS * ACTIVE_CHECK_PERIOD

# initialize the ImageHub object
imageHub = imagezmq.ImageHub()

# initialize the dictionary which will contain  information regarding
# when a device was last active, then store the last time the check
# was made was now
lastActive = {}
lastActiveCheck = datetime.now()

while True:
	(hostName, frame) = imageHub.recv_image()
	imageHub.send_reply(b'OK')

	# if a device is not in the last active dictionary then it means
	# that its a newly connected device
	if hostName not in lastActive.keys():
		print("[INFO] receiving data from {}...".format(hostName))

	# record the last active time for the device from which we just
	# received a frame
	lastActive[hostName] = datetime.now()

	cv2.imshow("Vid", frame)
	# detect any kepresses
	key = cv2.waitKey(1) & 0xFF

	# if current time *minus* last time when the active device check
	# was made is greater than the threshold set then do a check
	if (datetime.now() - lastActiveCheck).seconds > ACTIVE_CHECK_SECONDS:
		# loop over all previously active devices
		for (hostName, ts) in list(lastActive.items()):
			# remove the RPi from the last active and frame
			# dictionaries if the device hasn't been active recently
			if (datetime.now() - ts).seconds > ACTIVE_CHECK_SECONDS:
				print("[INFO] lost connection to {}".format(hostName))
				lastActive.pop(hostName)

		# set the last active check time as current time
		lastActiveCheck = datetime.now()

	# if the `q` key was pressed, break from the loop
	if key == ord("q"):
		break

# do a bit of cleanup
cv2.destroyAllWindows()