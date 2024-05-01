#written for python3
import serial
from multiprocessing import Process
import mysql.connector
import time
import sys
from datetime import datetime

def stayawake():
    count = 0
    while True:
        print(".", end = '', flush = True)
        time.sleep(120) #every 2 minutes
        count = count + 1
        if(count == 30):
            print("::")
            count = 0
                
p = Process(target = stayawake)
p.start()

ser = serial.Serial('/dev/ttyACM1', 9600)
print("Waiting for data... \n")

while True:
    read_serial=ser.readline()  #Packet Received
    print("\n" + read_serial.decode("utf-8"), end = '')
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    print(timestamp)
    
    #wid=ser.readline()  #wid Header
    #print(wid.decode("utf-8"), end = '')
    #waldoID = wid.split()
    
    #read_serial0=ser.readline()  #Headers for each column in the send
    #print(read_serial0.decode("utf-8"), end = '')
    
    #current event information
    read_serial1=ser.readline()  
    print(read_serial1.decode("utf-8"), end = '')
    current = read_serial1.split()
    
    #previous event information
    read_serial2=ser.readline()
    print(read_serial2.decode("utf-8"), end = '')
    previous = read_serial2.split()
    
    #pre-previous event information
    read_serial3=ser.readline()
    print (read_serial3.decode("utf-8"), end = '')
    preprevious = read_serial3.split()

    #ignore [0-2] indices as they are the values "packet", "received:", and the key value 57
    db = mysql.connector.connect(host= "mysql1.cs.clemson.edu" , 
                     user = "WaldoData",
                     passwd ="P3rsistlab",
                     db= "Waldo_ITW_Database")
    cur = db.cursor()
    #timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    bayID = 0
    waldoID = current[0]
    try:
        sql = "INSERT INTO Events (Time_stamp, BaystationID, WaldoID, CURRENT_PacketID, CURRENT_Validity, CURRENT_TotalEvents, CURRENT_e1_time, CURRENT_e1_class, CURRENT_e2_time, CURRENT_e2_class, CURRENT_e3_time, CURRENT_e3_class, CURRENT_e4_time, CURRENT_e4_class, CURRENT_e5_time, CURRENT_e5_class, PRIOR1_PacketID, PRIOR1_Validity, PRIOR1_TotalEvents, PRIOR1_e1_time, PRIOR1_e1_class, PRIOR1_e2_time, PRIOR1_e2_class, PRIOR1_e3_time, PRIOR1_e3_class, PRIOR1_e4_time, PRIOR1_e4_class, PRIOR1_e5_time, PRIOR1_e5_class, PRIOR2_PacketID, PRIOR2_Validity, PRIOR2_TotalEvents, PRIOR2_e1_time, PRIOR2_e1_class, PRIOR2_e2_time, PRIOR2_e2_class, PRIOR2_e3_time, PRIOR2_e3_class, PRIOR2_e4_time, PRIOR2_e4_class, PRIOR2_e5_time, PRIOR2_e5_class) VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"
        val=(timestamp, bayID, waldoID, current[1], current[2], current[3], current[4], current[5], current[6], current[7], current[8], current[9], current[10], current[11], current[12], current[13], previous[1], previous[2], previous[3], previous[4], previous[5], previous[6], previous[7], previous[8], previous[9], previous[10], previous[11], previous[12], previous[13], preprevious[1], preprevious[2], preprevious[3], preprevious[4], preprevious[5], preprevious[6], preprevious[7], preprevious[8], preprevious[9], preprevious[10], preprevious[11], preprevious[12], preprevious[13])
        cur.execute(sql,val)
        db.commit()
        print("Successful database commit")
    except:
        db.rollback()
        print("Database not updated")

    cur.close()
    db.close()
    



	
        
        
