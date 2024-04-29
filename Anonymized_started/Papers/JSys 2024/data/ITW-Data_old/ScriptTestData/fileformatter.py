#   Script:   fileformatter.py dbfilename.csv
#   run:      python3 fileformatter.py Events_asof_April1_ds.csv
#   output:   BayfileArray_W0.csv  BayfileArray_W1.csv  BayfileArray_W3.csv
#   Purpose:  This script reformats the baystations' data to the appropriate files and filters them
#   ToDo:     Still needs the logic to recover data if packet was lost...
import csv
import time
import sys

#[0]record#, [1]date, [2]time stamp, [3]bayID [4]waldoID [5]PKTID,
#[6]Valid [7]Total [8]Ins [9]Outs [10]Passbys [11]others
with open(sys.argv[1]) as baystation_events:
    csv_reader_baystation = csv.reader(baystation_events, delimiter=',')
    bay_array = list(csv_reader_baystation)


#create a big array to place separated data into
Waldo0_all = []
Waldo0_rd = []   #remove duplicates from multiple baystations
Waldo0_final = [] #lab
Waldo0_final.append(['Record#', 'Date', 'Time Stamp', 'Packet#', 'Validity', 
                    'Total', 'Ins', 'Outs', 'Passby'])
Waldo1_all = []
Waldo1_rd = []
Waldo1_final = [] #hallway
Waldo1_final.append(['Record#', 'Date', 'Time Stamp', 'Packet#', 'Validity', 
                    'Total', 'Ins', 'Outs', 'Passby'])
Waldo3_all = []
Waldo3_rd = []
Waldo3_final = [] #classroom
Waldo3_final.append(['Record#', 'Date', 'Time Stamp', 'Packet#', 'Validity', 
                    'Total', 'Ins', 'Outs', 'Passby'])

#Separating raw pkt information into separate groups based on which waldo produced the data
count = 0
for idx in range(len(bay_array)):
    if idx != 0:
        if bay_array[idx][6] == "Valid":
            count += 1
            if int(bay_array[idx][4]) == 0:  #WaldoID is 0
                Waldo0_all.append([bay_array[idx][0], bay_array[idx][1], bay_array[idx][2], bay_array[idx][3], bay_array[idx][4], 
                    bay_array[idx][5], bay_array[idx][6], bay_array[idx][7], bay_array[idx][8], bay_array[idx][9], bay_array[idx][10], bay_array[idx][11],
                    bay_array[idx][12], bay_array[idx][13], bay_array[idx][14], bay_array[idx][15], bay_array[idx][16], bay_array[idx][17], bay_array[idx][18],
                    bay_array[idx][19], bay_array[idx][20], bay_array[idx][21], bay_array[idx][22], bay_array[idx][23], bay_array[idx][24], bay_array[idx][25]])
            elif int(bay_array[idx][4]) == 1:  #WaldoID is 1
                Waldo1_all.append([bay_array[idx][0], bay_array[idx][1], bay_array[idx][2], bay_array[idx][3], bay_array[idx][4], 
                    bay_array[idx][5], bay_array[idx][6], bay_array[idx][7], bay_array[idx][8], bay_array[idx][9], bay_array[idx][10], bay_array[idx][11],
                    bay_array[idx][12], bay_array[idx][13], bay_array[idx][14], bay_array[idx][15], bay_array[idx][16], bay_array[idx][17], bay_array[idx][18],
                    bay_array[idx][19], bay_array[idx][20], bay_array[idx][21], bay_array[idx][22], bay_array[idx][23], bay_array[idx][24], bay_array[idx][25]])
            elif int(bay_array[idx][4]) == 3:  #WaldoID is 3
                Waldo3_all.append([bay_array[idx][0], bay_array[idx][1], bay_array[idx][2], bay_array[idx][3], bay_array[idx][4], 
                    bay_array[idx][5], bay_array[idx][6], bay_array[idx][7], bay_array[idx][8], bay_array[idx][9], bay_array[idx][10], bay_array[idx][11],
                    bay_array[idx][12], bay_array[idx][13], bay_array[idx][14], bay_array[idx][15], bay_array[idx][16], bay_array[idx][17], bay_array[idx][18],
                    bay_array[idx][19], bay_array[idx][20], bay_array[idx][21], bay_array[idx][22], bay_array[idx][23], bay_array[idx][24], bay_array[idx][25]])
                
print(f'Valid Pkt Count = {count}')

#Trimming out duplicates from multiple baystations:  Waldo0 is closest to bay0 and Waldo1/Waldo3 are closest to bay1
array = Waldo0_all
x = 0
while x < len(array):
    if x < len(array)-1:
        if (array[x][1] == array[x+1][1] and array[x][2] == array[x+1][2] and array[x][5] == array[x+1][5]):
            Waldo0_rd.append([array[x][0], array[x][1], array[x][2], array[x][3], array[x][4], 
                        array[x][5], array[x][6], array[x][7], array[x][8], array[x][9], array[x][10], array[x][11],
                        array[x][12], array[x][13], array[x][14], array[x][15], array[x][16], array[x][17], array[x][18],
                        array[x][19], array[x][20], array[x][21], array[x][22], array[x][23], array[x][24], array[x][25]])
            x += 1
        else:
            Waldo0_rd.append([array[x][0], array[x][1], array[x][2], array[x][3], array[x][4], 
                        array[x][5], array[x][6], array[x][7], array[x][8], array[x][9], array[x][10], array[x][11],
                        array[x][12], array[x][13], array[x][14], array[x][15], array[x][16], array[x][17], array[x][18],
                        array[x][19], array[x][20], array[x][21], array[x][22], array[x][23], array[x][24], array[x][25]])
    else:
        Waldo0_rd.append([array[x][0], array[x][1], array[x][2], array[x][3], array[x][4], 
                        array[x][5], array[x][6], array[x][7], array[x][8], array[x][9], array[x][10], array[x][11],
                        array[x][12], array[x][13], array[x][14], array[x][15], array[x][16], array[x][17], array[x][18],
                        array[x][19], array[x][20], array[x][21], array[x][22], array[x][23], array[x][24], array[x][25]])
    x += 1

array = Waldo1_all
x = 0
while x < len(array):
    if x < len(array)-1:
        if (array[x][1] == array[x+1][1] and array[x][2] == array[x+1][2] and array[x][5] == array[x+1][5]):
            Waldo1_rd.append([array[x+1][0], array[x+1][1], array[x+1][2], array[x+1][3], array[x+1][4], 
                        array[x+1][5], array[x+1][6], array[x+1][7], array[x+1][8], array[x+1][9], array[x+1][10], array[x+1][11],
                        array[x+1][12], array[x+1][13], array[x+1][14], array[x+1][15], array[x+1][16], array[x+1][17], array[x+1][18],
                        array[x+1][19], array[x+1][20], array[x+1][21], array[x+1][22], array[x+1][23], array[x+1][24], array[x+1][25]])
            x += 1
        else:
            Waldo1_rd.append([array[x][0], array[x][1], array[x][2], array[x][3], array[x][4], 
                        array[x][5], array[x][6], array[x][7], array[x][8], array[x][9], array[x][10], array[x][11],
                        array[x][12], array[x][13], array[x][14], array[x][15], array[x][16], array[x][17], array[x][18],
                        array[x][19], array[x][20], array[x][21], array[x][22], array[x][23], array[x][24], array[x][25]])
    else:
        Waldo1_rd.append([array[x][0], array[x][1], array[x][2], array[x][3], array[x][4], 
                        array[x][5], array[x][6], array[x][7], array[x][8], array[x][9], array[x][10], array[x][11],
                        array[x][12], array[x][13], array[x][14], array[x][15], array[x][16], array[x][17], array[x][18],
                        array[x][19], array[x][20], array[x][21], array[x][22], array[x][23], array[x][24], array[x][25]])
    x += 1

array = Waldo3_all
x = 0
while x < len(array):
    if x < len(array)-1:
        if (array[x][1] == array[x+1][1] and array[x][2] == array[x+1][2] and array[x][5] == array[x+1][5]):
            Waldo3_rd.append([array[x+1][0], array[x+1][1], array[x+1][2], array[x+1][3], array[x+1][4], 
                        array[x+1][5], array[x+1][6], array[x+1][7], array[x+1][8], array[x+1][9], array[x+1][10], array[x+1][11],
                        array[x+1][12], array[x+1][13], array[x+1][14], array[x+1][15], array[x+1][16], array[x+1][17], array[x+1][18],
                        array[x+1][19], array[x+1][20], array[x+1][21], array[x+1][22], array[x+1][23], array[x+1][24], array[x+1][25]])
            x += 1
        else:
            Waldo3_rd.append([array[x][0], array[x][1], array[x][2], array[x][3], array[x][4], 
                        array[x][5], array[x][6], array[x][7], array[x][8], array[x][9], array[x][10], array[x][11],
                        array[x][12], array[x][13], array[x][14], array[x][15], array[x][16], array[x][17], array[x][18],
                        array[x][19], array[x][20], array[x][21], array[x][22], array[x][23], array[x][24], array[x][25]])
    else:
        Waldo3_rd.append([array[x][0], array[x][1], array[x][2], array[x][3], array[x][4], 
                        array[x][5], array[x][6], array[x][7], array[x][8], array[x][9], array[x][10], array[x][11],
                        array[x][12], array[x][13], array[x][14], array[x][15], array[x][16], array[x][17], array[x][18],
                        array[x][19], array[x][20], array[x][21], array[x][22], array[x][23], array[x][24], array[x][25]])
    x += 1

#Packet Recovery   PktID is currently 4, but will need to be switched to 3 once bayID is removed
#WALDO0################################################################
curPKT = 0
prePKT = -1
pre_array = []
#[0]record#, [1]date, [2]time stamp, [3]bayID [4]waldoID [5]PKTID,
#[6]Valid [7]Total [8]Ins [9]Outs [10]Passbys [11]others
#row format::  Record#, Date, Time, PKT#, Validity, Total, Ins, Outs, Passby
pkt_ct = 0
for row in Waldo0_rd:
    curPKT = int(row[5])
    #first packet in the file
    if pkt_ct == 0 and curPKT == 0:
        Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif pkt_ct == 0 and curPKT == 1:
        if row[13] == 'Valid':
            Waldo0_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif pkt_ct == 0 and curPKT > 1:
        if row[20] == 'Valid':
            Waldo0_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
        if row[13] == 'Valid':
            Waldo0_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    
    #if pkt is not the first one in the file and normal sequence is happening
    elif curPKT > prePKT:
        if curPKT - prePKT == 1:   #normal
            Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT - prePKT == 2: #missed one
            if row[13] == 'Valid':
                Waldo0_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT - prePKT >= 3: #missed two or more
            if row[20] == 'Valid':
                Waldo0_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
            if row[13] == 'Valid':
                Waldo0_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])

    #if pkt is not one, but system has restarted
    elif prePKT == 0 and curPKT == 1 and (row[5] != pre_array[3] or row[6] != pre_array[4] or row[7] != pre_array[5] or row[8] != pre_array[6] or row[9] != pre_array[7] or row[10] != pre_array[8]):
        if row[13] == 'Valid':
            Waldo0_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif curPKT == prePKT and curPKT == 0:  #double restarts
        Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif curPKT == prePKT and curPKT == 1:  #double restarts
        if row[13] == 'Valid':
            Waldo0_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif curPKT == prePKT and curPKT >= 2:
        if row[20] == 'Valid':
            Waldo0_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
        if row[13] == 'Valid':
            Waldo0_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    
    elif curPKT < prePKT:
        if curPKT == 0 :   #normal
            Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT == 1: #missed one
            if row[13] == 'Valid':
                Waldo0_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT >= 2: #missed two or more
            if row[20] == 'Valid':
                Waldo0_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
            if row[13] == 'Valid':
                Waldo0_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo0_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])


    pkt_ct += 1
    prePKT = curPKT
    pre_array = [row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]]
print(f'Waldo0_final has {pkt_ct} received packets.')

#WALDO1################################################################
curPKT = 0
prePKT = -1
pre_array = []
#[0]record#, [1]date, [2]time stamp, [3]bayID [4]waldoID [5]PKTID,
#[6]Valid [7]Total [8]Ins [9]Outs [10]Passbys [11]others
#row format::  Record#, Date, Time, PKT#, Validity, Total, Ins, Outs, Passby
pkt_ct = 0
for row in Waldo1_rd:
    curPKT = int(row[5])
    #first packet in the file
    if pkt_ct == 0 and curPKT == 0:
        Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif pkt_ct == 0 and curPKT == 1:
        if row[13] == 'Valid':
            Waldo1_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif pkt_ct == 0 and curPKT > 1:
        if row[20] == 'Valid':
            Waldo1_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
        if row[13] == 'Valid':
            Waldo1_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    
    #if pkt is not the first one in the file and normal sequence is happening
    elif curPKT > prePKT:
        if curPKT - prePKT == 1:   #normal
            Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT - prePKT == 2: #missed one
            if row[13] == 'Valid':
                Waldo1_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT - prePKT >= 3: #missed two or more
            if row[20] == 'Valid':
                Waldo1_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
            if row[13] == 'Valid':
                Waldo1_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])

    #if pkt is not one, but system has restarted
    elif prePKT ==0 and curPKT == 1 and (row[5] != pre_array[3] or row[6] != pre_array[4] or row[7] != pre_array[5] or row[8] != pre_array[6] or row[9] != pre_array[7] or row[10] != pre_array[8]):
        if row[13] == 'Valid':
            Waldo1_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif curPKT == prePKT and curPKT == 0:  #double restarts
        Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif curPKT == prePKT and curPKT == 1:  #double restarts
        if row[13] == 'Valid':
            Waldo1_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif curPKT == prePKT and curPKT >= 2:
        if row[20] == 'Valid':
            Waldo1_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
        if row[13] == 'Valid':
            Waldo1_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    
    elif curPKT < prePKT:
        if curPKT == 0 :   #normal
            Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT == 1: #missed one
            if row[13] == 'Valid':
                Waldo1_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT >= 2: #missed two or more
            if row[20] == 'Valid':
                Waldo1_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
            if row[13] == 'Valid':
                Waldo1_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo1_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])


    pkt_ct += 1
    prePKT = curPKT
    pre_array = [row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]]
print(f'Waldo1_final has {pkt_ct} received packets.')

#WALDO3################################################################
curPKT = 0
prePKT = -1
pre_array = []
#[0]record#, [1]date, [2]time stamp, [3]bayID [4]waldoID [5]PKTID,
#[6]Valid [7]Total [8]Ins [9]Outs [10]Passbys [11]others
#row format::  Record#, Date, Time, PKT#, Validity, Total, Ins, Outs, Passby
pkt_ct = 0
for row in Waldo3_rd:
    curPKT = int(row[5])
    #first packet in the file
    if pkt_ct == 0 and curPKT == 0:
        Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif pkt_ct == 0 and curPKT == 1:
        Waldo3_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif pkt_ct == 0 and curPKT > 1:
        Waldo3_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
        Waldo3_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    
    #if pkt is not the first one in the file and normal sequence is happening
    elif curPKT > prePKT:
        if curPKT - prePKT == 1:   #normal
            Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT - prePKT == 2: #missed one
            Waldo3_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT - prePKT >= 3: #missed two or more
            Waldo3_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
            Waldo3_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])

    #if pkt is not one, but system has restarted
    elif curPKT == 1 and (row[5] != pre_array[3] or row[6] != pre_array[4] or row[7] != pre_array[5] or row[8] != pre_array[6] or row[9] != pre_array[7] or row[10] != pre_array[8]):
        Waldo3_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif curPKT == prePKT and curPKT == 0:  #double restarts
        Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif curPKT == prePKT and curPKT == 1:  #double restarts
        Waldo3_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    elif curPKT == prePKT and curPKT >= 2:
        Waldo3_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
        Waldo3_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
        Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
    
    elif curPKT < prePKT:
        if curPKT == 0 :   #normal
            Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT == 1: #missed one
            Waldo3_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])
        elif curPKT >= 2: #missed two or more
            Waldo3_final.append([row[0], row[1], row[2], row[19], row[20], row[21], row[22], row[23], row[24]])
            Waldo3_final.append([row[0], row[1], row[2], row[12], row[13], row[14], row[15], row[16], row[17]])
            Waldo3_final.append([row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]])


    pkt_ct += 1
    prePKT = curPKT
    pre_array = [row[0], row[1], row[2], row[5], row[6], row[7], row[8], row[9], row[10]]
print(f'Waldo3_final has {pkt_ct} received packets.')



#Write all the separated and recovered data to a file
with open('BayfileArray_W0.csv', mode = 'w') as _file0:
    _writer0 = csv.writer(_file0, delimiter=",", )

    for row in Waldo0_final:
        _writer0.writerow(row)

with open('BayfileArray_W1.csv', mode = 'w') as _file1:
    _writer1 = csv.writer(_file1, delimiter=",", )

    for row in Waldo1_final:
        _writer1.writerow(row)

with open('BayfileArray_W3.csv', mode = 'w') as _file3:
    _writer3 = csv.writer(_file3, delimiter=",", )

    for row in Waldo3_final:
        _writer3.writerow(row)
