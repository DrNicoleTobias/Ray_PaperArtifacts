import serial
import pymysql
from datetime import datetime

ser = serial.Serial('/dev/cu.usbmodem11103', 9600)
bayID = 0
Name = "Justin"
event_type = ""
print("Here we go...\n")

while True:
    read_serial=ser.readline()
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    print(timestamp)
    print(read_serial)
    tx = read_serial.split()
#    print(tx)
#ignore [0-2] indices as they are the values "packet", "received:", and the key value 57
    db = pymysql.connect(host= "mysql1.cs.clemson.edu" , 
                    user = "uw7k5cup",
                    passwd ="Math1234!!",
                    db= "Waldo_v2_ControlData_r60f")
    cur = db.cursor()

    try:
        #sql = "INSERT INTO Events (Time_stamp, BaystationID, Name, WaldoID, PacketID, CURRENT_event) VALUES (%s,%s,%s,%s,%s,%s)"
        sql = "INSERT INTO Waldo_Control_Data (Time_stamp, BaystationID, Name, WaldoID, PacketID, Control, CURRENT_event, ch1_st, ch1_end, ch2_st, ch2_end, value_check) VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"
        val=(timestamp, bayID, Name,  tx[0],  tx[1], event_type, tx[2], tx[3], tx[4], tx[5], tx[6], tx[7])
        cur.execute(sql,val)
        db.commit()
        print("Successful database commit")
    except Exception as e:
        db.rollback()
        print('Failed to upload: ' + str(e))
        print("Database not updated")

    cur.close()
    db.close()
        
        
