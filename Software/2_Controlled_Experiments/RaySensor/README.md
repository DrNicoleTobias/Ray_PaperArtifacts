#### Intro
SensorControlExperiments.c is the firmware for the Ray Sensor to send a single packet for individual controlled events from its Radio_Module and CC1101 Radio provided there is enough energy available to do so.  Each packet will containing a sequence of the classified result as well as some feature data in the event that you want to infer why an event was a false positive etc.  Be sure to update the evaluate_event() method on line 395 with the equivalent decision tree code from the model that was trained previously.

#### Setup
1. Change the SUPPORT_FILE_DIRECTORY in the makefile to your msp430 gcc include
   path.
2. Hook up a MSP430FR5994 LaunchPad at the Programmer pins to your computer and plug them im to the appropriate programming pins on the MCU_Module.
3. Use "make install" to load the program into your device.
4. Detach from programmer and reconnect the PCB in the enclosure and you are ready to deploy.