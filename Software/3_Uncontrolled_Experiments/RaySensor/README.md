#### Intro
ITWDeploymentCode.c is the firmware for the Ray Sensor to send complete packets from its Radio_Module and CC1101 Radio provided there is enough energy available to do so.  Each packet will containing a sequence of 5 events, an estimate of their time between events, and history of the last two packets sent for redundancy.  This version of the code also includes sending heartbeat event when there has been no activity detected in approximately 2 minutes. Be sure to update the evaluate_event() method on line 453 with the equivalent decision tree code from the model that was trained previously.


#### Setup
1. Change the SUPPORT_FILE_DIRECTORY in the makefile to your msp430 gcc include
   path.
2. Hook up a MSP430FR5994 LaunchPad to your computer.
3. Connect the sensor to the Programmer pins on the launchpad (You may need to remove some jumpers to accomplish this) and plug them in to the appropriate programming pins on the MCU_Module.
4. Use "make install" to load the program into your device.
5. Detach from programmer and reconnect the PCB in the enclosure and you are ready to deploy.