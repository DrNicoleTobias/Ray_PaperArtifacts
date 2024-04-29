This is working basic test code for RX/TX launchpads with cc1101 radios.  -NT Nov14, 2022

#### Intro
This library contains examples on how to Transmit and Receive packets using the CC1101 Radio
with MSP430FR994. It is a build up on the CC1101 library written by Josiah Hester. It uses
interrupt rather than polling when listening for packet arrival in the RX mode. You can edit
delayMilliss() value to reflect how long you want to wait if the interrupt is yet to fire.

#### Setup
1. Clone the repository and change the SUPPORT_FILE_DIRECTORY in the makefile to your msp430 gcc include
   path.
2. Use "make install" to load the program into your device. tx -> transmitter and rx -> receiver
