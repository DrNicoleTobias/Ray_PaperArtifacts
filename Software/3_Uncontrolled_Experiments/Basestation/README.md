#### Intro
This is the firmware for a base station to Receive packets using the CC1101 Radio with a MSP430FR994 launchpad.

#### Setup
1. Change the SUPPORT_FILE_DIRECTORY in the makefile to your msp430 gcc include
   path.
2. Hook up a MSP430FR5994 LaunchPad to your computer.
3. Use "make install" to load the program into your device.

#### Gathering Data
You can choose to grab the data direct from a serial port and direct it to a file or grab the information and send it to a database.  ITWbaystation.py is a python3 script that we would run on our basestation that the MSP430 Launchpad was connected to by USB to grab the data and send it to an SQL Database for later processing.  If you want to use this script you would need to update line 22 with the appropriate serial port, and lines 54-57 and 60-64 with appropriate values for your database and basestation ID if you have more than one basestation.

#### Commercial Sensor Comparison (EnOcean)
The folder EnOcean_Sensor_PacketDecoder contains 2 python scripts and instructions on their use to collect and decode the packets sent from the commercial sensor for later comparison with the our Sensor's data and Ground Truth.