import serial
import getopt
import sys
import time
import MySQLdb
from datetime import datetime
from multiprocessing import Process

def getSerialData():
	global dataLength, opDataLength, packetType, headerCRC, totalDataLength, serialData
	file = 'logStatus.txt'
	s = 0
	i = 0
	Data = []
	DataByte = 0

	while s != '55':
		if ser.inWaiting() != 0:
			s = ser.read(1).encode("hex")

	while ser.inWaiting() < 5:
		()
	dataLength = ser.read(2).encode("hex") #read length field
	opDataLength = ser.read(1).encode("hex") #read op length field
	packetType = ser.read(1).encode("hex") #read packet type field
	headerCRC = ser.read(1).encode("hex") #read header crc field
	#print("dataLength%d ", int(dataLength, 16))
	#print("opDataLength%d  ", int(opDataLength, 16)

	totalDatalength = int(dataLength, 16) + int(opDataLength, 16)
	while DataByte < totalDatalength:
		Data.append(ser.read(1).encode("hex"))
		DataByte += 1
	
	packetCheck = 1
	for item in Data:
		if not item:
			packetCheck = 0
	
	if(packetCheck):
		timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
		
		#update with non-anonymized host
		db = MySQLdb.connect(host = "mysql1.XXXX.edu",
		user = "EnoceanData_vult",
		passwd = "password",
		db = "EnoceanData_vrec")
		cur = db.cursor()
        #print(Data)

		SenderID = Data[5] + Data[6] + Data[7] + Data[8]
        #print("PRog %s\n"%Data[0])
        #print("SenderId: %s\n"%SenderID)
        #print("occupancy status: %s\n"%Data[3])
		if (Data[3] == 'ff'):
			occupancy_status = 'Occupied'
		if (Data[3] == '00'):
			occupancy_status = 'Unoccupied'
        
		#print("device type: %s\n"%Data[4])
		SupperCapVolt = (int(Data[1],16)/254.0)*5.0
        #print("supper cap voltage:%f volts\n"%SupperCapVolt)
        #print("solar panel current:%d microA\n"%int(Data[2],16))
		SolarPanelCurrent = int(Data[2],16)
		
		#Load data received into the database for later processing
		try:
			sql = "INSERT INTO Events (Time_Stamp, SensorID,Occupancy_Status,Supper_Cap_Voltage,Solar_Panel_Current_microA,Receiver_ID) VALUES (%s,%s,%s,%s,%s,%s)"
			val = (timestamp,SenderID,occupancy_status,SupperCapVolt,SolarPanelCurrent,"A")
			cur.execute(sql,val)
			db.commit()
		except:
			db.rollback()
			cur.close()
			db.close()

		LastTimelogging = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
		with open (file,'w') as fileOverWrite:
			fileOverWrite.write(LastTimelogging)
		print(LastTimelogging)
		print('Successfully logged data to the Database')


#main
serialPort ="/dev/ttyUSB1"  #Update for the port the reciever is connected to
global ser
global LastTimelogging
ser = serial.Serial(serialPort, baudrate = 57600,
parity = serial.PARITY_NONE,
stopbits = serial.STOPBITS_ONE,  # STOPBITS_TWO
bytesize = serial.EIGHTBITS,
timeout = None)

if(not ser.isOpen()):
	ser.open()

while (True):
	if(not ser.isOpen()):
		print("USB is disconnected.....")
		ser.open()
	try:
		getSerialData()
	except:
		print("error")
