#!/usr/bin/env python3


import argparse
from tracker import Tracker
import os
import glob

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--input", help="path to the directory with the video files")

args = vars(ap.parse_args())

# if the video argument is None, then we are reading from webcam
if args.get("input", None) is None:
    print("Directory with some videos!")
    exit(1)

if not os.path.isdir(args["input"]):
    print("Specified input directory (%s) doesn't exist."%(os.path.normpath(args["input"])))
    exit(1)


onlyfiles = glob.glob("%s/*.avi"%(os.path.normpath(args["input"])))

# convert files from avi to mp4, because the cameras do something
# weird with the formatting
print ("Converting avi files to mp4 files.")
for f in onlyfiles:
    mp4file = f.replace(".avi",".mp4")
    cmd = "ffmpeg -i \"%s\" -vcodec libx264 -acodec libfaac \"%s\""%(f,mp4file)
    print(cmd)
    os.system(cmd)


#ffmpeg -i 2019-08-20\ 11\ 15\ 50-P.avi -vcodec libx264 -acodec libfaac 2019-08-20\ 11\ 15\ 50-P.mp4