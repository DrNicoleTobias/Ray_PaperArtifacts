#Waldo Rev. F (NT)
Status:  Currently being developed/tested - Under construction.

This folder contains the PCB design this project.  

# Rev. F
Status:  Currently being developed/tested - Under construction.
This folder contains the version of the PCB design that is currently being developed.  This folder contains all files and complete hardware documentation for the state of Rev. F.  


This folder contains all of the board and schematic files associated with the three Waldo modules (Solar Processing, MCU, and Radio Modules).  Gerbers generated from these files are zipped by module and also included in the Gerbers folder.  References to modified notes associated with Rev D are located in the References folder for the meantime.  A complete BOM as of this date is included and separated by module along with a combined list for ordering for all three modules at once.   The makefile that is included only provides a clean tag to help clean up any of the junk files from this folder as users edit the .brd and .sch files, if they choose to use it.

Current operating version (This is the version used in the ITW deployment for TOSN submission):  
(WALDO v2) Solar2 > MCU1 < Radio


-->Note:  Documentation of this Waldo hardware revision has been developed by Nicole Tobias, Oct 2018.  Let me know if you have additional questions or concerns.

Major updates from Rev. D PCB:
(- removed, + added, +/- modified)
v0
	+/- MCU has been upgraded to a MSP430FR5994 microcontroller.
	+/- Modified how the modules interconnect and modified shape to be smaller and more linear for ease of developing a case to if needed for this PCB..
	+ Added the ability to be able to capture raw wave forms and added active probe circuitry to accomplish reading these signals without effecting them by reading them.
	+/- Changed many of the exposed headers to be probe pads instead to reduce space when not needed, and to help uncomplicate soldering tasks later.
	+/- Changed all possible resistors and capacitors to 0603, instead of 0805 to help reduce space as well.
	- Removed Real-Time Clock, Digipots, etc circuitry to clean up design since they were not being populated in Rev. D.
	+/- Combined both solar boards into one board.
	+ Switch added to solar board to assist with discharging capacitors when needed.
	+/- Switches on MCU module for external battery power, replaced with a jumper to reduce space and confusion on board.
v1
	+ added a 47k resistor and 2.2nF capacitor on the reset pin as specified on the datasheet
	+ added version number to brd silkscreen
	+/- removed +3V3 parts from schematic and changed to DVCC labels for readability and to lower confusion.
v2
	+/- changed resistor and capacitor values on the filters and resistor dividers to decrease power loss over those parts of the circuit.
	+ added connections on the solar board to allow for raw signal reading by the MCU module.
	+/- Moved low pass filters out of the path of the harvesting circuit on the solar board.	
