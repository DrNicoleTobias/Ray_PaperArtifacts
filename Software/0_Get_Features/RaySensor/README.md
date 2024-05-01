#### Intro
This is the firmware for the Ray Sensor to send Raw Feature packets using the CC1101 Radio with a MSP430FR994 launchpad.  The features can be trimmed down to just ch1_start, ch1_end, ch2_start, ch2_end and the rest post processed from those values if you need to save energy due to packet size.

#### Setup
1. Change the SUPPORT_FILE_DIRECTORY in the makefile to your msp430 gcc include
   path.
2. Hook up a MSP430FR5994 LaunchPad to your computer.
3. Connect the sensor to the Programmer pins on the launchpad (You may need to remove some jumpers to accomplish this) and plug them in to the appropriate programming pins on the MCU_Module.
4. Use "make install" to load the program into your device.
5. Detach from programmer and reconnect the PCB in the enclosure and you are ready to deploy.