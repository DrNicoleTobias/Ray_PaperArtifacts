#!/usr/bin/env python3


# import the necessary packages
#from imutils.video import VideoStream
import argparse
import datetime
import imutils
import time
import cv2
from tracker import Tracker
import os
import sys

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video", help="path to the video file")
ap.add_argument("-o", "--output", help="path to the output directory for the track videos and summary information")
ap.add_argument("-a", "--min-area", type=int, default=8000, help="minimum area sized object to consider")
ap.add_argument("-d", "--debug", action="store_true",help="show the video frames and spit out extra text for debugging purposes.")

args = vars(ap.parse_args())

# if the video argument is None, then we are reading from webcam
if args.get("video", None) is None:
    print("I need a video!")
    exit(1)

if args.get("output", None) is None:
    print("You need to specify an output directory.")
    exit(1)

if not os.path.isdir(args["output"]):
    print("Specified output directory (%s) doesn't exist."%(os.path.normpath(args["output"])))
    exit(1)


vs = cv2.VideoCapture(args["video"])
video_params = {
    "fps" : vs.get(cv2.CAP_PROP_FPS),
    "width" : vs.get(cv2.CAP_PROP_FRAME_WIDTH),
    "height" : vs.get(cv2.CAP_PROP_FRAME_HEIGHT)
}

print("video source="+str(video_params))



tracker = Tracker(args["video"], args["output"], video_params, args["debug"])

# initialize the first frame in the video stream
firstFrame = None
frameCount = 0


# loop over the frames of the video
while True:
    # grab the current frame and initialize the occupied/unoccupied
    # text
    ret, frame = vs.read()
    if frame is None:
        break

    text = "Unoccupied"
    frameCount = frameCount+1

    (gray,frameDelta,thresh,rects) = tracker.findObjects(frame, args.get("min_area"))
    if (gray is None):
        continue
    
        
    tracker.considerFrame(frameCount, frame, rects)
    if len(rects) > 0 and args.get("debug"):
        
        # draw the text and timestamp on the frame
        #cv2.putText(frame, "Room Status: {}".format(text), (10, 20),
        #cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
        cv2.putText(frame, str(frameCount),(10, frame.shape[0] - 50), cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)

        if args["debug"]:
            # show the frame and record if the user presses a key
            cv2.imshow("Frame", frame)
            cv2.imshow("Gray", gray)
            cv2.imshow("Thresh", thresh)
            cv2.imshow("Frame Delta", frameDelta)
        
            key = cv2.waitKey(0)
            if key == 27:
                sys.exit()

        # if the `q` key is pressed, break from the loop
        if key == ord("q"):
            break
# close any open windows
cv2.destroyAllWindows()