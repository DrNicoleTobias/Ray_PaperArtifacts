# Ray Sensor Documentation Notes

Ray is a batteryless, doorframe/passageway-mounted room-level occupancy monitoring sensor that uses changes in indoor ambient light reflections to detect people entering and exiting a room or hallway and estimate their direction of travel.  

In this document, we provide the abstract of the work with highlights from our experiments, comments for the JSys reviewers, a layout of the folder/file structure, and instructions on how to build a Ray sensor and set it and a base station up for deployment.

# Abstract
Room-level occupancy-tracking systems enable intelligent control of building functions like air conditioning and power delivery to adapt to the needs of their occupants. Unfortunately, existing occupancy-tracking systems are bulky, have short battery lifetimes, are not privacy-preserving, or only provide coarse-grain occupancy information. Furthermore, retrofitting existing infrastructures with wired sensors is prohibitively expensive.

In this paper, we present **Ray, a batteryless, doorframe/passageway-mounted room-level occupancy monitoring sensor** that uses changes in indoor ambient light reflections to detect people entering and exiting a room or hallway and estimate direction of travel. We evaluated Ray in mixed lighting conditions on both sides of the doorway in an office-style setting, using subjects with a wide variety of physical characteristics. We conducted 881 controlled experiments in 7 doorways with 9 individuals and achieved a total detection accuracy of 100% and movement direction accuracy averaging 96.4%. Furthermore, we deployed Ray sensors for 64 days in 5 locations, comparing them with a commercial batteryless occupancy sensor. Ray outperformed the commercial sensor, particularly where traffic is moderate to heavy. Ray demonstrates that ambient light reflections provide both a promising low-cost, long-term sustainable option for monitoring how people use buildings and an exciting new research direction for batteryless computing.

# Artifact Evaluation - For JSys Reviewers
The artifacts associated with this paper consist of both hardware and software for building a functioning deployment of the Ray sensor. 

We are including the custom PCB designs, Bill of Materials, and 3D prototype housing files used to create a Ray sensor. PDFs of the schematic and Design files are also included for reviewer convenience. Software for training and the firmware that runs the Ray sensor and base station are also provided. Documentation includes both how to build, set up, tune, train, and deploy a Ray sensor as well as how to set up a base station for receiving the sensor data.

As the claims of this work are of the effectiveness of our custom Ray sensor, it is hard to automate items for testing and evaluation without actually having a physical sensor built, trained, and deployed for you to test yourselves.  After speaking with the chair of the Artifact Evaluation Board, we determined the best way to show you that the usability and reproducibility of this work by providing the design files (raw and as pdfs for convenience) and making several demo videos to show the system working in both controlled demos, in the presence of confounding cases, and when comparing to a commercial occupancy sensor.  We hope they allow you enough insight to judge the effectiveness, claims, and reproducibility of the work as it is hard to exactly recreate some of these experiments as they were gathered from live individuals walking through passageways.

# Folder/File Layout

StackEdit stores your files in your browser, which means all your files are automatically saved locally and are accessible **offline!**

## Hardware

The file explorer is accessible using the button in left corner of the navigation bar. You can create a new file by clicking the **New file** button in the file explorer. You can also create folders by clicking the **New folder** button.
### 3D_Housing
 - Base Station Firmware
 - Ray Sensor Firmware
### PCB_Designs
 - Base Station Firmware
 - Ray Sensor Firmware

## Software

All your files and folders are presented as a tree in the file explorer. You can switch from one to another by clicking a file in the tree.
### 1_Train_Model
 - Base Station Firmware
 - Ray Sensor Firmware
### 2_Controlled_Studies
 - Base Station Firmware
 - Ray Sensor Firmware
### 3_Uncontrolled_Studies
 - Base Station Firmware
 - Ray Sensor Firmware

## Video_Demos

words
# Deploying a Ray Sensor

words

## Building a Ray Sensor

### Ordering parts and assembly

### Training the event classification model

### Installing Firmware

### Installing on a doorway

## Setting up a Base Station

### Parts and Assembly
### Installing Firmware
### Collecting Data?










# Waldo

**Waldo** is a project whose goal is to accomplish batteryless occupancy detection.  

This repo stores code, hardware files, and other technical documents for the project. Subdirectories are described below.

### Software
Source code, testing code, and documentation.

### Hardware
Hardware PCB version files, 3D enclosures, and documentation.

### Papers
All files, data, and figures used in submission attempts for this project.


