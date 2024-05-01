# Ray Sensor Documentation Notes

Ray is a batteryless, doorframe/passageway-mounted room-level occupancy monitoring sensor that uses changes in indoor ambient light reflections to detect people entering and exiting a room or hallway and estimate their direction of travel.  


<table style="width: 150%; border-collapse: collapse;">
  <tr>
    <td style="width: 100%; text-align: center;">
      <img src="_scenario.png" alt="Ray Use Scenario" width="500" >
      <br>
      <strong>Ray Use Scenario/Concept</strong>
    </td>
  </tr>
</table>



In this document, we provide the abstract of the work with highlights from our experiments, comments for the JSys reviewers, a layout of the folder/file structure, and instructions on how to build a Ray sensor and set it and a base station up for deployment.

# Abstract
Room-level occupancy-tracking systems enable intelligent control of building functions like air conditioning and power delivery to adapt to the needs of their occupants. Unfortunately, existing occupancy-tracking systems are bulky, have short battery lifetimes, are not privacy-preserving, or only provide coarse-grain occupancy information. Furthermore, retrofitting existing infrastructures with wired sensors is prohibitively expensive.

In this paper, we present **Ray, a batteryless, doorframe/passageway-mounted room-level occupancy monitoring sensor** that uses changes in indoor ambient light reflections to detect people entering and exiting a room or hallway and estimate direction of travel. We evaluated Ray in mixed lighting conditions on both sides of the doorway in an office-style setting, using subjects with a wide variety of physical characteristics. We conducted 881 controlled experiments in 7 doorways with 9 individuals and achieved a total detection accuracy of 100\% and movement direction accuracy averaging 96.4\%. Furthermore, we deployed Ray sensors for 64 days in 5 locations, comparing them with a commercial batteryless occupancy sensor. Ray outperformed the commercial sensor, particularly where traffic is moderate to heavy. Ray demonstrates that ambient light reflections provide both a promising low-cost, long-term sustainable option for monitoring how people use buildings and an exciting new research direction for batteryless computing.

# Artifact Evaluation - For JSys Reviewers
The artifacts associated with this paper consist of both hardware and software for building a functioning deployment of the Ray sensor. 

We are including the custom PCB designs, Bill of Materials, and 3D prototype housing files used to create a Ray sensor. PDFs of the schematic and Design files are also included for reviewer convenience. Software for training and the firmware that runs the Ray sensor and base station are also provided. Documentation includes both how to build, set up, tune, train, and deploy a Ray sensor as well as how to set up a base station for receiving the sensor data.

As the claims of this work are of the effectiveness of our custom Ray sensor, it is hard to automate items for testing and evaluation without actually having a physical sensor built, trained, and deployed for you to test yourselves.  After speaking with the chair of the Artifact Evaluation Board, we determined the best way to show you that the usability and reproducibility of this work by providing the design files (raw and as pdfs for convenience) and making several demo videos to show the system working in both controlled demos, in the presence of confounding cases, and when comparing to a commercial occupancy sensor.  We hope they allow you enough insight to judge the effectiveness, claims, and reproducibility of the work as it is hard to exactly recreate some of these experiments as they were gathered from live individuals walking through passageways.

# Folder/File Layout
This repo stores code, hardware files, and other technical documents for the project. Subdirectories are described below.

## Hardware
This folder contains all of the custom PCB Eagle design files (PDFs of the schematic and board design files are also included for reviewer convenience), Bill of Materials (BOM), and 3D prototype housing/enclosures files used to create a Ray sensor. 

## Software
All software provided is either C code compiled and ran on the MSP430FR5994 chips used for our sensor and base station or python3 scripting code that is processed on a base station or laptop. The following subfolders contain the code needed to gather the raw features from a Ray sensor (0_Get_Features) and train a decision tree classifier model using those features (1_Train_Model).  Once trained, the model will need to be implemented in the experiment code subfolders 2_Controlled_Studies and 3_Uncontrolled_Studies.

### 0_Get_Features
This folder contains the firmware needed for both the Ray sensor and for a basestation in order to gather the raw feature data that the sensor is collecting on a doorway/passageway that you wish to train your classification model for capturing direction and various corner cases such as pass-bys.  Have sample subjects walk in and out in a controlled manner so that you can capture what the raw features from your sensor look like under your lighting conditions and environment.  Collect this data using what is received at the basestation and the result for that data that you wish to train with in a CSV file for use in training the model in the next step.  

### 1_Train_Model

### 2_Controlled_Studies

### 3_Uncontrolled_Studies


## Video_Demos

words

# Building a Ray Sensor

In this section, we describe the steps it takes to build a physical Ray Sensor for deployment.
<table style="width: 150%; border-collapse: collapse;">
  <tr>
    <td style="width: 50%; text-align: center;">
      <img src="_waldoguts-anon-white.png" alt="Ray Use Scenario" width="500" >
      <br>
      <strong>Ray PCB Close Up</strong>
    </td>
    <td style="width: 100%; text-align: center;">
      <img src="_full_sensor_pcbopen.png" alt="Ray Use Scenario" width="500" >
      <br>
      <strong>Ray Full Sensor</strong>
    </td>
  </tr>
</table>

## Housing/Enclosure, Parts, and Assembly
Our prototype hardware integrates a modular custom printed circuit board (PCB) housed in a 3D-printed plastic enclosure, four solar panels, and a TI CC1101 radio.

### Custom PCB
The PCB for the Ray sensor consists of 3 modular parts, a Solar_Module, a MCU_Module, and a Radio_Module.  All design files for these modules and the Bill of Materials for all necessary PCB components can be found in the Hardware/PCB_Designs/ folder.  Boards can be fabricated at many places online, such as OSHpark etc, and the components can be populated by hand or by a manufacture as well.  Design files can be viewed directly by a program like Eagle, but PDFs have been made available for convenience of viewing.  The Solar_Module attaches to the MCU_Module and the MCU_Module attaches to the Radio_Module.

### 3D Enclosure
The 3D printed mounting system is made of PLA plastic and contains the PCB, solar cells, and necessary wiring connecting them. Enclosure designs to house the PCB and attach the solar panels to can be found in Hardware/3D_Enclosure/PCB_Housing_and_20_DegBody_Assembly.stl with a second file Hardware/3D_Enclosure/PCB_Housing_Cap.stl to make a cap to cover the PCB during deployment.  The enclosure provides a nesting place for the solar cells, which angles the solar cell slots such that 2 of the 4 of the solar cells are pointed toward the entry, while the rest are pointed toward the exit.  

### Connecting Solar Panels
Four solar panels need to be attached to the enclosure where they will be divided into two sets of two panels each, one facing inward (the direction the radio antenna is pointing) and one set facing outward.  The inward set of solar panels are connected in series and connected to the SOLAR1 terminal of the Solar Module PCB.  The outward facing panels are also connected in series and then added to the SOLAR2 terminal.

### Tune the Detectors
Ray uses a detection circuit to determine when to wake up the microcontroller to assess the possible event.  The detector circuitry is tunable using trim potentiometers (trim pots) pre-installation in deployment.  You may find that depending on the lighting conditions of a particular doorway you are mounting the Ray sensor to that the sensitivity of the detector circuit's trim pots may need adjusting.  We found in our experiments that we did need to adjust the trim pots some for the general lighting conditions and found that they generally worked for other similar lighting conditions without needing to be readjusted for every doorway.  Using a screwdriver on TM1 for monitoring SOLAR1 or TM2 for monitoring SOLAR2 from the Solar_Module PCB schematics, twisting to one direction will move the detection threshold and make the detectors more sensitive while twisting in the opposite direction will make them less sensitive.

### Attaching a Radio
The Ray PCB also uses a TI CC1101 radio for communication that is to be connected to the Radio_Module in Hardware/PCB_Designs/. For our purposes, we considered the direction the antenna was pointing would be considered *inward* when mounting the sensor for practice, but logically you could train and adjust the code if you prefer it to point the other direction.

### Installing on a doorway
With all the parts assembled, tuned, connected, and attacked to the 3D printed enclosure, you can attach the Ray sensor to the top of a doorway/passageway frame with solar panels facing down anyway that you would like.  For our experiments, we affixed the 3d enclosure to a piece of wood with magnets screwed to the other side for easy in attaching and removing the sensor on different doorway/passageway frames as most within our office building had metal frames or structures to attach to.

## Training the event classification model
### Gather Raw Feature Data

### Train Model**

### Translate Decision Tree Diagram to Implementation**
Now that you 

### Installing Firmware
The Ray firmware implements the detection algorithm with a trained decision tree for event classification discussed in Section 3. Monitoring the interrupts from the detectors and deducing the direction of motion upon triggering are the main tasks of the system. The firmware is designed to be ultra-low power, even in active mode, and has low computational complexity, offloading the bulk of the detection to the hardware circuits. The Ray firmware is composed of 691 lines of commented C code, compiling to a 4459 byte image. This code size comprises only 1.7\% of the available code space on the MSP430FR5994 (256KB), leaving ample room for implementing custom tasks, recognizers, or multiprogramming operating systems.

The Ray firmware implements the detection algorithm with a trained decision tree for event classification once it is deployed.  Monitoring the interrupts from the detectors and deducing the direction of motion upon triggering are the main tasks of the system. The firmware is designed to be ultra-low power, even in active mode, and has low computational complexity, offloading the bulk of the detection to the hardware circuits. The Ray firmware is composed of 691 lines of commented C code, compiling to a 4459 byte image. This code size comprises only 1.7\% of the available code space on the MSP430FR5994 (256KB), leaving ample room for implementing custom tasks, recognizers, or multiprogramming operating systems.  

### Installing on a doorway

## Setting up a Base Station

### Parts and Assembly
### Installing Firmware
### Collecting Data?


