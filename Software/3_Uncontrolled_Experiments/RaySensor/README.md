#### Intro
This is the firmware for the Ray Sensor to send Raw Feature Packets packets using the CC1101 Radio with a MSP430FR994 launchpad.  The features can be trimmed down to just ch1_start, ch1_end, ch2_start, ch2_end and the rest post processed from those values if you need to save energy due to packet size.

#### Setup
1. Change the SUPPORT_FILE_DIRECTORY in the makefile to your msp430 gcc include
   path.
2. Use "make install" to load the program into your device.