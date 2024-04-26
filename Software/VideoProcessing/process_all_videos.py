#!/usr/bin/env python3


import argparse
from tracker import Tracker
import os
import glob
import re
import shutil
from colorama import init, Fore, Back, Style

# initialize colorama
init(autoreset=True)


##HELPERS
def dosystem(cmd):
    print(Style.BRIGHT + Fore.GREEN + cmd)
    os.system(cmd)



# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--input", help="path to the camera files root directory --- contains subdirectories with the video files, each must be named \"YYYYMMDD\".")
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

npath = os.path.normpath(args["input"])
noutputpath = os.path.normpath(args["output"])
print(npath)
print(noutputpath)
entries = glob.glob("%s/*"%(npath))
print(entries)
for entry in entries:
    bname = os.path.basename(entry)
    dname = os.path.dirname(entry)
    if not re.match("\A\d{8}$",bname):
        print("Subdirectory does not match the expected YYYYMMDD format: %s -- skipping it..."%(entry))
        continue
    entrydest = "%s/%s"%(noutputpath,bname)
    if not os.path.isdir(entrydest):
        os.mkdir(entrydest)    
    
    for hour in range(24):
        datedirname = "%s/%s"%(entry,str(hour).zfill(2))
        destdatedirname = "%s/%s"%(entrydest,str(hour).zfill(2))
        if not os.path.isdir(datedirname):
            continue
        if os.path.isdir(destdatedirname):
            shutil.rmtree(destdatedirname)
        os.mkdir(destdatedirname)
        
        cmd = "./congealvideos.py %d -i \"%s\" -o \"%s\" "%(hour,entry,destdatedirname)
        dosystem(cmd)

        congealedfilename = glob.glob("%s/*.mp4"%(destdatedirname))[0]
        cmd = "./getevents.py -v \"%s\" -o \"%s\" -d"%(congealedfilename, destdatedirname)
        dosystem(cmd)

        events = glob.glob("%s/*evt.avi"%(destdatedirname))
        for event in events:
            cmd = "./process_one_video.py -v \"%s\" -o \"%s\" "%(event, destdatedirname)
            dosystem(cmd)
    
