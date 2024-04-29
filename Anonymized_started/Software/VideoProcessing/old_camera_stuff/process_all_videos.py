#!/usr/bin/env python3


import argparse
from tracker import Tracker
import os
import glob

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--input", help="path to the directory with the video files")
ap.add_argument("-o", "--output", help="path to the output directory for the track videos and summary information")

args = vars(ap.parse_args())

# if the video argument is None, then we are reading from webcam
if args.get("input", None) is None:
    print("Directory with some videos!")
    exit(1)

if args.get("output", None) is None:
    print("You need to specify an output directory.")
    exit(1)

if not os.path.isdir(args["output"]):
    print("Specified output directory (%s) doesn't exist."%(os.path.normpath(args["output"])))
    exit(1)


onlyfiles = glob.glob("%s/*.mp4"%(os.path.normpath(args["input"])))

# grab all mp4 files
print ("Processing %d mp4 files."%(len(onlyfiles)))
for f in onlyfiles:
    cmd = "./process_one_video.py -v \"%s\" -o \"%s\" "%(f,args["output"])
    print(cmd)
    os.system(cmd)


#ffmpeg -i 2019-08-20\ 11\ 15\ 50-P.avi -vcodec libx264 -acodec libfaac 2019-08-20\ 11\ 15\ 50-P.mp4