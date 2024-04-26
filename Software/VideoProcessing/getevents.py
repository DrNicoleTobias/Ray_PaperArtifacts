#!/usr/bin/env python3


# import the necessary packages
#from imutils.video import VideoStream
import argparse
import datetime
from multiprocessing import Event
import imutils
import time
import cv2
from matplotlib.pyplot import gray
from tracker import Tracker
import os
import sys
import re
import numpy as np
import math


## HELPER FUNCTIONS

# saves an event video
def saveEvent(frames, video_params, filename):    
    outfile = cv2.VideoWriter(filename,cv2.VideoWriter_fourcc('M','J','P','G'), video_params["fps"], (int(video_params["width"]),int(video_params["height"])))
    for frame in frames:
        outfile.write(frame)
    outfile.release()
    print("file (%s) saved."%(filename))

# Print iterations progress
def printProgressBar (iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = '█', printEnd = "\r"):
    """
    Call in a loop to create terminal progress bar
    @params:
        iteration   - Required  : current iteration (Int)
        total       - Required  : total iterations (Int)
        prefix      - Optional  : prefix string (Str)
        suffix      - Optional  : suffix string (Str)
        decimals    - Optional  : positive number of decimals in percent complete (Int)
        length      - Optional  : character length of bar (Int)
        fill        - Optional  : bar fill character (Str)
        printEnd    - Optional  : end character (e.g. "\r", "\r\n") (Str)
    """
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    print(f'\r{prefix} |{bar}| {percent}% {suffix}', end = printEnd)
    # Print New Line on Complete
    if iteration == total: 
        print()

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video", help="path to the video file")
ap.add_argument("-o", "--output", help="path to the output directory for the track videos and summary information")
ap.add_argument("-a", "--min-area", type=int, default=2000, help="minimum area sized object to consider")
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

videobasename = os.path.basename(args["video"])
print(videobasename)
if not re.match("\A\d{8}_\d{2}_\d{2}_\d{2}.mp4$",videobasename):
    print("Specified input file (%s) doesn't follow the format (YYYYMMDD_HH_MM_MM)."%(videobasename))
    exit(1)

ymd = videobasename[0:8]
hour = int(videobasename[9:11])
minstart = int(videobasename[12:14])
minend = int(videobasename[15:17])

vs = cv2.VideoCapture(args["video"])
video_params = {
    "fps"       : vs.get(cv2.CAP_PROP_FPS),
    "width"     : vs.get(cv2.CAP_PROP_FRAME_WIDTH),
    "height"    : vs.get(cv2.CAP_PROP_FRAME_HEIGHT),
    "nframes"   : vs.get(cv2.CAP_PROP_FRAME_COUNT)
}
secs_per_frame = 1.0/video_params["fps"]
print("video source="+str(video_params))


#tracker = Tracker(args["video"], args["output"], video_params)

# initialize the first frame in the video stream
refFrame    = None
previousFrame  = None
previousFullFrame  = None
frameCount = 0
count = 0
MOTION_THRESHOLD = 5.0
inEvent = False
EventFrames = []
EVENT_TTL = 5  # 5 frames of no movement ends an event
eventTTL = EVENT_TTL
secs_counter = minstart*60
EventTime = secs_counter
framecounter = 0


while True:
    ret, frame = vs.read()
    if frame is None:
        break
    secs_counter += secs_per_frame
    framecounter += 1
    printProgressBar(framecounter, video_params['nframes'], prefix = 'Progress:', suffix = 'Complete', length = 50)

    grayframe = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    w = int(video_params["width"])
    h = int(video_params["height"])
    grayframe[h-90 : h-1, w-350 : w-1] = (0)
    grayframe = cv2.GaussianBlur(grayframe, (15, 15), 0)
    
    # if the first frame is None, initialize it
    if refFrame is None:
        refFrame = frame 
        previousFrame = grayframe
        previousFullFrame = frame
        #note, this assumes that the first frame doesn't have motion. Might need a fancier solution in the future.
        continue

    # compute the absolute difference between the current frame and
    # first frame
    frameDelta = cv2.absdiff(previousFrame, grayframe)
    thresh = cv2.threshold(frameDelta, 20, 255, cv2.THRESH_BINARY)[1]/255.0
    

        
    maxdelta = np.sum(thresh) # get the number of changed pixels
    
    #if motion
    if (maxdelta > MOTION_THRESHOLD):
        #uncomment if you want to actually watch what it's doing.
        
        #frame changed
        if not inEvent:
            inEvent = True
            EventTime = secs_counter
            EventFrames = [previousFullFrame]
            
        eventTTL = EVENT_TTL
        EventFrames.append(frame)
    else:
        #no change
        if inEvent:
            eventTTL = eventTTL - 1
            if eventTTL <= 0:
                #wrap up event
                inEvent = False
                
                #save event to file
                minutes = math.floor(EventTime/60)
                seconds = math.floor(EventTime - (minutes * 60))
                fname = "%s/%s_%s_%s_%s.evt.avi"%(os.path.dirname(args['video']),ymd,str(hour).zfill(2), str(minutes).zfill(2), str(seconds).zfill(2))
                saveEvent(EventFrames, video_params, fname)
                print("Save it! %d frames -> %s"%(len(EventFrames), fname))
                EventFrames = []
        else:
            #refFrame = grayframe
            grayframe = grayframe
    previousFrame = grayframe
    previousFullFrame = frame


# close any open windows
cv2.destroyAllWindows()

sys.exit()

