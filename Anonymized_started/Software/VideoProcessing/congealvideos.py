#!/usr/bin/env python3


import argparse
from tracker import Tracker
import os
import glob
import re
import cv2

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser(description= "Combine 1-minute files into hour-long blocks.")
ap.add_argument('hour', type=int, nargs=1, help='the hour (0–23) that you want to congeal')
ap.add_argument("-i", "--input", help="path to the top-level day directory with the video files")
ap.add_argument("-o", "--output", help="path to the output directory for the combined video file")

args = vars(ap.parse_args())

if args.get("input", None) is None:
    print("Specify a directory with some videos!")
    exit(1)

if args.get("output", None) is None:
    print("You need to specify an output directory.")
    exit(1)

if not os.path.isdir(args["input"]):
    print("Specified input directory (%s) doesn't exist."%(os.path.normpath(args["input"])))
    exit(1)

if not os.path.isdir(args["output"]):
    print("Specified output directory (%s) doesn't exist."%(os.path.normpath(args["output"])))
    exit(1)

basename = os.path.basename(args["input"])
if not re.match("\A\d{8}",basename):
    print("Specified input directory (%s) doesn't follow the format (YYYYMMDD)."%(basename))
    exit(1)

year = int(basename[0:4])
month = int(basename[4:6])
day = int(basename[6:8])
hour = args['hour'][0]

#onlyfiles = glob.glob("%s/%d/*.mp4"%(os.path.normpath(args["input"]), hour))

templistfile = "allfileslist.txt"


### HELPER FUNCTIONS
def resetlistfile(f):
    #clear out filelist
    if (os.path.exists(f)):
        os.remove(f)

def concatfiles(listf, outfile):
    if (not os.path.exists(listf)):
        print("No list file. Ignoring.")
        return
    cmd = "ffmpeg -f concat -safe 0 -i %s -max_muxing_queue_size 1000000 -c copy %s"%(listf,outfile)
    print(cmd)
    os.system(cmd)
    
def getduration_seconds(videofile):
    vs = cv2.VideoCapture(videofile)
    video_params = {
        "fps" : float(vs.get(cv2.CAP_PROP_FPS)),
        "nframes" : float(vs.get(cv2.CAP_PROP_FRAME_COUNT))
    }
    return video_params["nframes"] / video_params["fps"]

def add_file_to_list(fname, tmplist):
    #first remove it's audio
    nsfname ="%s.ns.mp4"%(fname)
    cmd = "ffmpeg -i \"%s\" -vf scale=1280:720 -preset veryfast -an \"%s\" "%(fname,nsfname)
    print(cmd)
    os.system(cmd)
    cmd = "echo file '%s' >> %s"%(nsfname,tmplist)
    print(cmd)
    os.system(cmd)

resetlistfile(templistfile)
outcount = 0
inchunk = False
firstmin = 0
lastmin = 0
# grab all mp4 files
#print ("Processing %d mp4 files."%(len(onlyfiles)))
for min in range(60):
    fname = "%s/%s/%s.mp4"%(args["input"],str(hour).zfill(2),str(min).zfill(2))
    if os.path.exists(fname):
        print("%s exists"%(fname))
        if not inchunk:
            inchunk = True
            firstmin = min+1  #assume the first chunk isn't full.
            seconds = getduration_seconds(fname)
            if (seconds > 58):
                firstmin = min #oh, it was full. Ok.
                add_file_to_list(fname, templistfile)
        else:
            add_file_to_list(fname, templistfile)
        lastmin = min
    else:
        print("%s does not exist"%(fname))
        if inchunk:
            inchunk = False
            concatfiles(templistfile, "%s/%s%s%s_%s_%s_%s.mp4"%(args['output'],str(year),str(month).zfill(2),str(day).zfill(2),str(hour).zfill(2),str(firstmin).zfill(2), str(lastmin).zfill(2)))
            outcount = outcount + 1

if inchunk:
    concatfiles(templistfile, "%s/%s%s%s_%s_%s_%s.mp4"%(args['output'],str(year),str(month).zfill(2),str(day).zfill(2),str(hour).zfill(2),str(firstmin).zfill(2), str(lastmin).zfill(2)))

cmd = "rm %s/%s/*.mp4.ns.mp4"%(args["input"],str(hour).zfill(2))
print(cmd)
os.system(cmd)