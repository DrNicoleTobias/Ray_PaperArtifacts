import os
import stat
import time
import datetime
from subprocess import check_call
import subprocess
import sys

counter=0
file0 = '/home/arwa/Desktop/logStatus.txt'
file1 = '/home/arwa/Desktop/logRestart.txt'
while (True):
	with open (file1,'a') as logRestart:
			logRestart.write(",") 
	counter +=1
	if counter >60:
		counter= 0
		with open (file1,'a') as logRestart:
			logRestart.write("\n")

	time.sleep(60)  #sleep for 1 min
	modTimeinceEpoc = os.path.getmtime(file0)
	modificationTime = datetime.datetime.fromtimestamp(modTimeinceEpoc)
	CurrentTime = datetime.datetime.now()
	TimeDifference = CurrentTime -modificationTime
	TimeDifferenceInMinutes = divmod(TimeDifference.seconds,60)
	#print(TimeDifferenceInMinutes[0])
	#print(TimeDifference)
	if (TimeDifferenceInMinutes[0] > 9):
		print("TimeDifference",TimeDifferenceInMinutes[0] )
		try:
			check_call(["pkill","-9","-f","ENOCEAN_PacketDecoder_A.py"])
		except:
			print("not running")
		Restart_time= datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
		with open (file1,'a') as logRestart:
			logRestart.write("\n") 
			logRestart.write(Restart_time) 
			logRestart.write("\n") 
		cmd= 'python /home/arwa/Desktop/ENOCEAN_PacketDecoder_A.py &'
		subprocess.call(cmd,shell=True)






