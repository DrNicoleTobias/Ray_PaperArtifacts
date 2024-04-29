This code is written by Arwa Alsubhi to decode Enocean sensor packet and logged the decoded data into a database. Follow the steps below in order to run the codes:

1-Creat two text files:
 first one name it "logStatus.txt". This file is used to keep track of the last database update.
 second one name it "logRestart.txt". This file is used to recored whenever the decoder code is killed and restarted if that last database update was passed 10 mins from current time.

2- plug the receiver into the computer and check the port in your terminal using: ls /dev/
    many open ports will show up but look out for ttyUSBx where x is a number (ubuntu user) or cu.usbserial-FT17TJEx (Mac user) where x is a letter. 

3- in "ENOCEAN_PacketDecoder_A.py" file change the port name (line 79) that you got from step 2. Also, in the same file in line 13 change the path to reflect the path of the "logStatus.txt" file that you created in step 1.

4- in "Monitoring.py" file change line 10 to reflect the path of the "logStatus.txt" file that you created in step 1 and  line 11 to reflect the path of the "logRestart.txt" file that you created in step 1.

Note: "ENOCEAN_PacketDecoder_A.py" is used to received data from receiver A (we labeled it) and logged the receiver ID as "A" in the database. In order to change the receiver ID , change "A" to whatever you want in line 64.

5-run the ENOCEAN_PacketDecoder_A.py by opening your terminal and type :
   python    <path>/ENOCEAN_PacketDecoder_A.py  

where  <path> is the path of  ENOCEAN_PacketDecoder_A.py file.

6- in other terminal run "Monitoring.py" file by typing:
   python  <path>/Monitoring.py

where  <path> is the path of Monitoring.py file.


Database:
https://www.cs.clemson.edu/phpmyadmin/index.php

user = "EnoceanData_vult"
passwd ="Math1234!!",
