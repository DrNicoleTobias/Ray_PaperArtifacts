from scipy.spatial import distance as dist
from collections import OrderedDict
import numpy as np
import cv2
import imutils
import copy
from datetime import datetime, timedelta
import os
import time

class Tracker():
    def __init__(self, filename, outputpath, video_params, ttl=2, find_green_box=True, debug=False):
        # initialize the next unique object ID along with two ordered
        # # dictionaries used to keep track of mapping a given object
        # ID to its centroid and number of consecutive frames it has
        # # been marked as "disappeared", respectively
        self.find_green_box = find_green_box
        self.nextObjectID = 0
        self.objectCenters = OrderedDict()
        self.objectTTLs = OrderedDict()
        self.objectTracks = OrderedDict()
        self.currentBatchStart = -1
        self.currentBatch = None
        # store the number of maximum consecutive frames a given
        # object is allowed to be marked as "disappeared" until we
        # need to deregister the object from tracking
        self.ttl        = ttl
        self.lastFrame  = -1
        self.filename   = filename
        self.basename   = os.path.basename(filename)
        self.dirname    = os.path.dirname(filename)
        self.video_params = video_params
        self.debug      = debug
        self.firstFrame = None
        self.outputpath = outputpath

        #get timestamp from filename
        year = int(self.basename[0:4])
        month = int(self.basename[4:6])
        day = int(self.basename[6:8])
        hour = int(self.basename[9:11])
        minute = int(self.basename[12:14])
        second = int(self.basename[15:17])

        self.timestring = "%d%s%s_%s_%s_%s"%(year, str(month).zfill(2), str(day).zfill(2), str(hour).zfill(2), str(minute).zfill(2), str(second).zfill(2))

        self.clipstart  = datetime.strptime(self.timestring, "%Y%m%d_%H_%M_%S")

        #open up the tsv file that will get the summary info
        self.outputfile = open(os.path.normpath(self.outputpath)+"/"+self.timestring+"-stats.tsv","w")
        self.columns = ["id","seconds","frames","first_frame","last_frame","start_time","end_time","start_time_offset_seconds","end_time_offset_seconds","up_moves","down_moves","left_moves","right_moves","up","down","left","right","percent_up","percent_down","up_to_down","down_to_up"]
        self.logEntry(None)
        
    def __del__(self):
        self.outputfile.close()
    
    def considerFrame(self, frame_number, frame, rects):
        if len(rects) == 0:
            for objectID in list(self.objectTTLs.keys()):
               self.decrementTTL(objectID)
            return self.objectCenters
        
        #init matrix for input center points
        inputCenters = np.zeros((len(rects), 2), dtype="int")

        if self.debug:
            print("Considering #%d --> %d rects."%(frame_number, len(rects)))
        
        for (i, (x, y, w, h)) in enumerate(rects):
            centerX = int(x+(w/2))
            centerY = int(y+(h/2))
            inputCenters[i] = (centerX, centerY)
        
        # if we are currently not tracking any objects take the input
        # centroids and register each of them
        if len(self.objectCenters) == 0:
            for i in range(0, len(inputCenters)):
                self.addObject(frame_number, frame, inputCenters[i])
        else:
            # grab the set of object IDs and corresponding center points
            objectIDs = list(self.objectCenters.keys())
            objectCentroids = list(self.objectCenters.values())
 
            # compute the distances between each pair of object
            # centroids and input centroids, respectively -- our
            # goal will be to match an input centroid to an existing
            # object centroid
            D = dist.cdist(np.array(objectCentroids), inputCenters)
 
            # in order to perform this matching we must (1) find the
            # smallest value in each row and then (2) sort the row
            # indexes based on their minimum values so that the row
            # with the smallest value is at the *front* of the index
            # list
            rows = D.min(axis=1).argsort()
 
            # next, we perform a similar process on the columns by
            # finding the smallest value in each column and then
            # sorting using the previously computed row index list
            cols = D.argmin(axis=1)[rows]

            # in order to determine if we need to update, register,
            # or deregister an object we need to keep track of which
            # of the rows and column indexes we have already examined
            usedRows = set()
            usedCols = set()
 
            # loop over the combination of the (row, column) index
            # tuples
            for (row, col) in zip(rows, cols):
                # if we have already examined either the row or
                # column value before, ignore it
                # val
                if row in usedRows or col in usedCols:
                    continue
 
                # otherwise, grab the object ID for the current row,
                # set its new centroid, and reset the disappeared
                # counter
                objectID = objectIDs[row]
                self.objectCenters[objectID] = inputCenters[col]
                self.objectTracks[objectID].append({"frame":frame_number,"actualframe":frame,"center":inputCenters[col]})
                self.objectTTLs[objectID] = self.ttl
 
                # indicate that we have examined each of the row and
                # column indexes, respectively
                usedRows.add(row)
                usedCols.add(col)

            # compute both the row and column index we have NOT yet
            # examined
            unusedRows = set(range(0, D.shape[0])).difference(usedRows)
            unusedCols = set(range(0, D.shape[1])).difference(usedCols)

            # in the event that the number of object centroids is
            # equal or greater than the number of input centroids
            # we need to check and see if some of these objects have
            # potentially disappeared
            if D.shape[0] >= D.shape[1]:
                # loop over the unused row indexes
                for row in unusedRows:
                    # grab the object ID for the corresponding row
                    # index and increment the disappeared counter
                    objectID = objectIDs[row]
                    self.decrementTTL(objectID)
            # otherwise, if the number of input centroids is greater
            # than the number of existing object centroids we need to
            # register each new input centroid as a trackable object
            else:
                for col in unusedCols:
                    self.addObject(frame_number, frame, inputCenters[col])
 
        # return the set of trackable objects
        return self.objectCenters
    
    def addObject(self, framenum, frame, center):
        self.objectCenters[self.nextObjectID] = center
        self.objectTTLs[self.nextObjectID] = self.ttl
        self.objectTracks[self.nextObjectID] = [{"frame":framenum,"actualframe":frame,"center":center}]
        self.nextObjectID = self.nextObjectID+1
    
    def removeObject(self,objectID):
        del self.objectCenters[objectID]
        del self.objectTTLs[objectID]

        track = self.objectTracks[objectID]
        if (len(track) > 2):
            self.printTrack(objectID)
            self.saveTrack(objectID)
            self.logEntry(self.summarizeTrack(objectID))

    def decrementTTL(self,objectID):
        self.objectTTLs[objectID] -= 1
        if self.objectTTLs[objectID] <= 0:
            self.removeObject(objectID)

    def printTrack(self, objectID):
        track = self.objectTracks[objectID]
        firstFrame = track[0]["frame"]
        lastFrame = track[len(track)-1]["frame"]
        print("track: %d--%d (%d frames)"%(firstFrame,lastFrame,lastFrame-firstFrame))
        if (self.debug):
            print("points: ",end="")
            for point in track:
                print(" %s"%(str(point["center"])),end="")
            print("")

    # gather statistics about the track
    # specifically, how long it is (frames and seconds)
    # how many frames are on each side of the FOV and how many
    # crossings occur.
    def summarizeTrack(self, objectID):
        fname = "%s-track-%d.avi"%(self.filename,objectID)
        track = self.objectTracks[objectID]

        midline = int(self.video_params["height"]/2)
        firstFrame = track[0]["frame"]
        lastFrame = track[len(track)-1]["frame"]

        upmovement    = 0
        downmovement  = 0
        leftmovement  = 0
        rightmovement = 0

        
        DwnCrossing = 0
        UpCrossing = 0
        ups = 0
        downs = 0
        for (i,entry) in enumerate(track):
            (X,Y) = track[i]["center"]
            if i > 0:
                (prevX,prevY) = track[i-1]["center"]
            else:
                (prevX,prevY) = (X,Y)

            #get movements
            if X > prevX:
                rightmovement += (X-prevX)
            else:
                leftmovement += (prevX-X)
            
            if Y > prevY:
                downmovement += (Y-prevY)
                downs += 1
            else:
                upmovement += (prevY-Y)
                ups += 1
            
            #get crossings
            point = entry["center"]
            if point[1] > midline:
                if i > 0 and track[i-1]["center"][1] < midline:
                    DwnCrossing += 1
            else:
                if i > 0 and track[i-1]["center"][1] > midline:
                    UpCrossing += 1
        trackstart = self.clipstart + timedelta(seconds=(float(firstFrame) / self.video_params["fps"]))
        trackend = self.clipstart + timedelta(seconds=(float(lastFrame) / self.video_params["fps"]))
        totalmovement = leftmovement + rightmovement + upmovement + downmovement
        return {"id":objectID, 
                "seconds": float(len(track))/self.video_params["fps"],
                "frames": (lastFrame-firstFrame)+1,
                "first_frame": firstFrame,
                "last_frame" : lastFrame,
                "start_time" : str(trackstart),
                "end_time" : str(trackend),
                "start_time_offset_seconds" : (trackstart-self.clipstart).total_seconds(),
                "end_time_offset_seconds" : (trackend-self.clipstart).total_seconds(),
                "up_moves" : upmovement,
                "down_moves" : downmovement,
                "left_moves" : leftmovement,
                "right_moves" : rightmovement,
                "up" : float(upmovement)/max(totalmovement,1),
                "down" : float(downmovement)/max(totalmovement,1),
                "left" : float(leftmovement)/max(totalmovement,1),
                "right" : float(rightmovement)/max(totalmovement,1), 
                "percent_up" : float(ups)*100.0/float(len(track)),
                "percent_down"  : float(downs)*100.0/float(len(track)),
                "up_to_down" : DwnCrossing,
                "down_to_up" : UpCrossing }

    # saves the annotated video for a detected object track to disk.
    def saveTrack(self, objectID):
        fname = "%s/%s-track-%d.avi"%(os.path.normpath(self.outputpath),self.timestring,objectID)
        track = self.objectTracks[objectID]
        
        # Define the codec and create VideoWriter object.The output is stored in 'outpy.avi' file.
        # Define the fps to be equal to 10. Also frame size is passed.
        outfile = cv2.VideoWriter(fname,cv2.VideoWriter_fourcc('M','J','P','G'), self.video_params["fps"], (int(self.video_params["width"]),int(self.video_params["height"])))
        for point in track:
            theframe = point["actualframe"]
            #draw the track on each frame.
            for (i,pt2) in enumerate(track):
                if (i > 0):
                    x1 = track[i-1]["center"][0]
                    y1 = track[i-1]["center"][1]
                    x2 = track[i]["center"][0]
                    y2 = track[i]["center"][1]
                    cv2.line(theframe,(x1,y1),(x2,y2),(0,255,0),1)

            outfile.write(theframe)
        outfile.release()
        print("file (%s) saved."%(fname))

    def findObjects(self, frame, minarea):
        
        gray = None
        if (self.find_green_box):
            #detect the green box in the image
            hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
            lower_green = np.array([50,120,120])
            upper_green = np.array([70,255,255])
    
            mask = cv2.inRange(hsv, lower_green, upper_green)
            res = cv2.bitwise_and(frame,frame, mask= mask)
            if mask.sum() < 1000:
                #doesn't look like we have a box — fall back on the other way
                gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                gray = cv2.GaussianBlur(gray, (45, 45), 0)
            else:
                gray = self.firstFrame + cv2.cvtColor(res, cv2.COLOR_BGR2GRAY)
        else:
            #use my object detection
            #convert it to grayscale, and blur it
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            gray = cv2.GaussianBlur(gray, (45, 45), 0)
        
        # if the first frame is None, initialize it
        if self.firstFrame is None:
            self.firstFrame = gray 
            #note, this assumes that the first frame doesn't have motion. Might need a fancier solution in the future.
            return (None, None, None, None)

        # compute the absolute difference between the current frame and
        # first frame
        frameDelta = cv2.absdiff(self.firstFrame, gray)
        thresh = cv2.threshold(frameDelta, 15, 255, cv2.THRESH_BINARY)[1]

        # dilate the thresholded image to fill in holes, then find contours
        # on thresholded image
        thresh = cv2.dilate(thresh, None, iterations=5)
        cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)
    
        rects = []
        # loop over the contours
        for c in cnts:
            # if the contour is too small, ignore it
            if cv2.contourArea(c) < minarea:
                continue

            
            # compute the bounding box for the contour
            # if it overlaps with any other rects combine the rects
            testrect = cv2.boundingRect(c)
            overlap = False
            for rect in rects:
                if (self.overlapRect(testrect,rect)):
                    overlap = True
                    newrect = self.union(testrect,rect)
                    rects.remove(rect)
                    testrect = newrect
                    break
            if True:
                rects.append(testrect)
        
        for r in rects:
            (x, y, w, h) = r
            center = ((int)(x+(w/2)),(int)(y+(h/2)))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
            cv2.circle(frame, center, 5, (0,255,0))
        
        midline = int(self.video_params["height"]/2)
        width = int(self.video_params["width"])
        cv2.line(frame,(0,midline),(width, midline),(255,0,0),1)


        return (gray,frameDelta,thresh,rects)
    
    def logEntry(self, entry):
        if entry is None:
            self.outputfile.write("\t".join(self.columns)+"\n")
            return

        for col in self.columns:
            if col in entry.keys():
                self.outputfile.write(str(entry[col]))
            self.outputfile.write("\t")
        self.outputfile.write("\n")
    
    # return True if the two rectangles overlap (False otherwise)
    # the rects have the form (x, y, w, h)
    def overlapRect(self, r1, r2):
        padding=10
        (x1,y1,w1,h1) = r1
        (x2,y2,w2,h2) = r2
        if (x1+w1 < x2-padding or x2+w2 < x1-padding):
            return False
        if (y1+h1 < y2-padding or y2+h2 < y1-padding):
            return False
        return True

    # compute the intersection of two rectangles
    # the rects have the form (x, y, w, h)
    def intersection(self,a,b):
        x = max(a[0], b[0])
        y = max(a[1], b[1])
        w = min(a[0]+a[2], b[0]+b[2]) - x
        h = min(a[1]+a[3], b[1]+b[3]) - y
        if w<0 or h<0: return () # or (0,0,0,0) ?
        return (x, y, w, h)

    # compute the union of two rectangles
    # the rects have the form (x, y, w, h)
    def union(self,a,b):
        x = min(a[0], b[0])
        y = min(a[1], b[1])
        w = max(a[0]+a[2], b[0]+b[2]) - x
        h = max(a[1]+a[3], b[1]+b[3]) - y
        return (x, y, w, h)
