#   Script:   csvScript.py
#   run:      python3 csvScript.py formatted_WaldoFile.csv GT_WaldoFile.csv
#   input:    WaldoDB_file.csv GT_file.csv
#   output:   ResultsFilename.csv 
#   Purpose:  This script is to run over a sample of the test data to try and line up 
#             likely matches in the waldo data to what is available in the ground truth.
#   Current state:  Kind of working... seems to work on a small dataset; 
#                   Doesn't work with multiple dates yet...

import csv
import datetime
from datetime import date
import time
import sys
import os

#os.remove("LabeledTable.csv")
#print(f'Results file removed.')
print(f'Reading in csv files.....')
#[0]record, [1]date, [2]time, [3]PKTID,
#[4]Valid [5]Total [6]Ins [7]Outs [8]Passbys 
bay_array = []
with open(sys.argv[1]) as csv_file_baystation:
    csv_reader_baystation = csv.reader(csv_file_baystation, delimiter=',')
    array = list(csv_reader_baystation)
    i = 0
    for row in array:
        if i == 0:
            i += 1
            continue
        #[0]record, [1]datetime, [2]PKTID, [3]Valid [4]Total [5]Ins [6]Outs [7]Passbys 
        dt = datetime.datetime.strptime((row[1] + " " + row[2]), "%d-%b %I:%M:%S %p")
        bay_array.append([row[0], dt, row[3], row[4], row[5], row[6], row[7], row[8]])
        i += 1

#[0]doorway, [1]reviewer, [2]date, [3]time,
#[4]ins [5]outs [6]pbsn [7]passbyf [8]linger [9-11]multi in, out, pb
gt_array = []
with open(sys.argv[2]) as csv_file:
    csv_reader_gt = csv.reader(csv_file, delimiter=',')
    array = list(csv_reader_gt)
    i = 0
    for row in array:
        if i == 0:
            i += 1
            continue
        #[0]doorway, [1]reviewer, [2]datetime [3]ins [4]outs [5]pbsn [6]passbyf [7]linger [8-10]multi in, out, pb
        dt = datetime.datetime.strptime((row[2] + " " + row[3]), "%d-%b %I:%M:%S %p")
        
        #get rid of empty str issues
        for i in range(len(row)):
                if row[i] == '':
                    row[i] = 0
        gt_array.append([row[0], row[1], dt, row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11]])

print(f'..........done.........{len(bay_array)}   {len(gt_array)}')

#This matches Record time to the lower boundary ground truth time
# MatchList is a multidimensional array with 4 values per row: 
#                   [bay_array_index, bay_record_number, gt_array_index, matching_gt_time]
MatchList = []
ct = 0
for index_bay in range(len(bay_array)):
        pkt_datetime = bay_array[index_bay][1]
        for index_gt in range(len(gt_array)):
            if index_gt >= 1:
                event_datetime = gt_array[index_gt][2]
                event_datetime_pre = gt_array[index_gt-1][2]

                diff_cur =  pkt_datetime - event_datetime
                diff_pre =  pkt_datetime - event_datetime_pre
                
                if pkt_datetime < event_datetime and ((diff_cur.total_seconds() < 20.0 and diff_cur.total_seconds() >= -10.0) or (diff_pre.total_seconds() < 20.0 and diff_pre.total_seconds() >= -10.0)):  #diff should be 6 sec plus send time - added cushion for gt human error
                    ct +=1
                    if abs(diff_cur.total_seconds()) < abs(diff_pre.total_seconds()):
                        MatchList.append([index_bay, bay_array[index_bay][0], bay_array[index_bay][2], index_gt, gt_array[index_gt - 1][3], gt_array[index_gt][3], diff_cur.total_seconds()])
                    else:
                        MatchList.append([index_bay, bay_array[index_bay][0], bay_array[index_bay][2], index_gt - 1, gt_array[index_gt - 1][3], gt_array[index_gt][3], diff_pre.total_seconds()])
                    break



#bay_array, gt_array, MatchList
#[0]record, [1]datetime, [2]PKTID, [3]Valid [4]Total [5]Ins [6]Outs [7]Passbys 
#gt_array  
#[0]doorway, [1]reviewer, [2]datetime [3]ins [4]outs [5]pbsn [6]passbyf [7]linger [8-10]multi in, out, pb
        
ConfirmedEventTable=[]
ConfirmedEventTable.append(['LabelType', 'Recover#', 'TimeDiff', 'BSidx', 'BSrecord#', 'DateTime', 'PktID', 'Validity', 'Total', 'Ins', 'Outs', 'Passbys',
                            'gtIdx', 'DateTime', 'gtIns', 'gtOuts', 'gtPb_near', 'gt_Pb_far', 'gtlinger', 'gtMultiIns', 'gtMultiOuts', 'gtMultiPbs'])
confirmed = 0
probable = 0
missing = 0
FPpkt = 0
line_ct = 0
index_of_interest = 0

for row in gt_array:
    if line_ct == 0:
        line_ct += 1
        continue
    ConfirmedEventTable.append(['Null', 0, "", "", "", "", "", "", "", "", "", "",
        line_ct, row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10]])
    line_ct += 1

shamt = 0
uniqueconfirmed = 0
Confirmedrecovered = 0
FPrecovered = 0
uniqueFPpkt = 0
#Pass 1 and Pass 2, adding confirmed and insert FPpkts...
for index_bay in range(len(bay_array)):
    #basestation date + time
    pkt_datetime = bay_array[index_bay][1]

    for index_gt in range(len(gt_array)):
        
        #days must match
        event_datetime = gt_array[index_gt][2]      

        if pkt_datetime < event_datetime:
            #ground truth date + time
            event_datetime_pre = gt_array[index_gt-1][2]
            diff_cur = pkt_datetime - event_datetime
            diff_pre = pkt_datetime - event_datetime_pre 

            if abs(diff_pre.total_seconds()) <= abs(diff_cur.total_seconds()) and (diff_pre.total_seconds() < 20 and diff_pre.total_seconds() >= -10):  #diff should be 6 sec plus send time - added cushion for gt human error
                ConfirmedEventTable[index_gt-1+shamt][0] = 'CONFIRMED'
                ConfirmedEventTable[index_gt-1+shamt][1] += 1
                ConfirmedEventTable[index_gt-1+shamt][2] = diff_pre.total_seconds() 
                ConfirmedEventTable[index_gt-1+shamt][3] = index_bay 
                ConfirmedEventTable[index_gt-1+shamt][4] = bay_array[index_bay][0] 
                ConfirmedEventTable[index_gt-1+shamt][5] = bay_array[index_bay][1] 
                ConfirmedEventTable[index_gt-1+shamt][6] = bay_array[index_bay][2]
                ConfirmedEventTable[index_gt-1+shamt][7] = bay_array[index_bay][3]
                ConfirmedEventTable[index_gt-1+shamt][8] = bay_array[index_bay][4]
                ConfirmedEventTable[index_gt-1+shamt][9] = bay_array[index_bay][5]
                ConfirmedEventTable[index_gt-1+shamt][10] = bay_array[index_bay][6]
                ConfirmedEventTable[index_gt-1+shamt][11] = bay_array[index_bay][7]
                if ConfirmedEventTable[index_gt-1+shamt][1] == 1:
                    uniqueconfirmed += 1
                else:
                    Confirmedrecovered += 1
                break
            elif abs(diff_cur.total_seconds()) < abs(diff_pre.total_seconds()) and (diff_cur.total_seconds() < 20 and diff_cur.total_seconds() >= -10):  #diff should be 6 sec plus send time - added cushion for gt human error
                ConfirmedEventTable[index_gt+shamt][0] = 'CONFIRMED'
                ConfirmedEventTable[index_gt+shamt][1] += 1 
                ConfirmedEventTable[index_gt+shamt][2] = diff_cur.total_seconds() 
                ConfirmedEventTable[index_gt+shamt][3] = index_bay 
                ConfirmedEventTable[index_gt+shamt][4] = bay_array[index_bay][0] 
                ConfirmedEventTable[index_gt+shamt][5] = bay_array[index_bay][1] 
                ConfirmedEventTable[index_gt+shamt][6] = bay_array[index_bay][2]
                ConfirmedEventTable[index_gt+shamt][7] = bay_array[index_bay][3]
                ConfirmedEventTable[index_gt+shamt][8] = bay_array[index_bay][4]
                ConfirmedEventTable[index_gt+shamt][9] = bay_array[index_bay][5]
                ConfirmedEventTable[index_gt+shamt][10] = bay_array[index_bay][6]
                ConfirmedEventTable[index_gt+shamt][11] = bay_array[index_bay][7]
                if ConfirmedEventTable[index_gt+shamt][1] == 1:
                    uniqueconfirmed += 1
                else:
                    Confirmedrecovered += 1
                break
            else:
                if bay_array[index_bay][0] == ConfirmedEventTable[index_gt-1+shamt][4]:
                    ConfirmedEventTable[index_gt-1+shamt][1] += 1
                    FPrecovered += 1
                else:
                    ConfirmedEventTable.insert(index_gt+shamt, ['FPpkt', 1, "", index_bay, bay_array[index_bay][0], bay_array[index_bay][1], bay_array[index_bay][2], bay_array[index_bay][3], bay_array[index_bay][4], bay_array[index_bay][5], bay_array[index_bay][6], bay_array[index_bay][7],
                        "", "", "", "", "", "", "", "", "", ""])
                    uniqueFPpkt += 1
                    shamt += 1
                break


print(f'Writing ReferenceLabelTable...')
#print(f'BayArray len = {len(bay_array)}, MatchList len = {len(MatchList)}') 
#MatchList has been populated with baystation records and their likely corresponding gt times
#Write all the summarized data to a file
with open("ReferenceLabeledTable_W3.csv", mode = 'w') as _filem:
    _writer = csv.writer(_filem, delimiter=",", )

    for row in ConfirmedEventTable:
        _writer.writerow(row)

PPstats = []
PPstatsheader = ['PktRec#', 'bsins', 'bsouts', 'bspbs', '#Plausibles', '#EventWindow', 'Extras', 'Misses', 'gtIns', 'gtOuts', 'gtPbnear', 'gtPbfar', 'gtlinger', 'gtll', 'gtmultiin', 'gtmultiout', 'gtmultipb']
extra = 0
misses = 0
PP = 0
event_ct = 0
gin = 0
gout = 0
gpbn = 0
gpbf = 0
gl = 0
gll = 0
gmin = 0
gmout = 0
gmpb = 0
stat_line_ct = 0
pktwmisses = 0
pktwextras = 0
prepktnum = 0
for x in range(len(ConfirmedEventTable)):
    if x == 0:
        continue
    if ConfirmedEventTable[x][0] == 'CONFIRMED' or ConfirmedEventTable[x][0] == 'FPpkt':
        if ConfirmedEventTable[x][0] == 'CONFIRMED':
            event_ct += 1
            gin += int(ConfirmedEventTable[x][14])
            gout += int(ConfirmedEventTable[x][15])
            gpbn += int(ConfirmedEventTable[x][16])
            gpbf += int(ConfirmedEventTable[x][17])
            str_ex = str(ConfirmedEventTable[x][18])
            if not str_ex.isdigit():
                gl += int(str_ex[0])
                gll += 1
            else:
                gl += int(ConfirmedEventTable[x][18])
            gmin += int(ConfirmedEventTable[x][19])
            gmout += int(ConfirmedEventTable[x][20])
            gmpb += int(ConfirmedEventTable[x][21])
        if prepktnum != -1:
            myPktID = int(ConfirmedEventTable[x][6])  #pktid
        PP = 5*int(ConfirmedEventTable[x][1])
        if PP > event_ct:
            extra = PP - event_ct
            pktwextras += 1
            PP = PP - extra
        elif PP < event_ct:
            misses = event_ct - PP
            pktwmisses += 1
        PPstats.append([ConfirmedEventTable[x][4], ConfirmedEventTable[x][9], ConfirmedEventTable[x][10], ConfirmedEventTable[x][11], PP, event_ct, extra, misses, gin, gout, gpbn, gpbf, gl, gll, gmin, gmout, gmpb])
        stat_line_ct += 1
        #resetting counters for next block summary
        event_ct = 0
        extra = 0
        misses = 0
        PP = 0
        gin = 0
        gout = 0
        gpbn = 0
        gpbf = 0
        gl = 0
        gll = 0
        gmin = 0
        gmout = 0
        gmpb = 0

    else:
        event_ct += 1
        gin += int(ConfirmedEventTable[x][14])
        gout += int(ConfirmedEventTable[x][15])
        gpbn += int(ConfirmedEventTable[x][16])
        gpbf += int(ConfirmedEventTable[x][17])
        str_ex = str(ConfirmedEventTable[x][18])
        if not str_ex.isdigit():
            gl += int(str_ex[0])
            gll += 1
        else:
            gl += int(ConfirmedEventTable[x][18])
        gmin += int(ConfirmedEventTable[x][19])
        gmout += int(ConfirmedEventTable[x][20])
        gmpb += int(ConfirmedEventTable[x][21])

print(f'Writing PPtable...')
with open("PPTable_W3.csv", mode = 'w') as _filem:
    _writer = csv.writer(_filem, delimiter=",", )
    _writer.writerow(PPstatsheader)
    for row in PPstats:
        _writer.writerow(row)


#Display Stats:
#--------------------------------------------------------------------------------------
print(f'>>>Total Pkts = {len(bay_array)} and Total GT videos = {len(gt_array)}')
print(f'>>>Confirmed Pkts = {uniqueconfirmed}')
print(f'>>>FP pkts = {uniqueFPpkt}')
print(f'>>>Recovered Pkts = {(Confirmedrecovered + FPrecovered)}   conf = {Confirmedrecovered}')
print(f'>>>Total PP = {sum(int(row[4]) for row in PPstats)} and avgPP is {(sum(int(row[4]) for row in PPstats) / stat_line_ct)}')
print(f'>>>Total Extra = {sum(int(row[6]) for row in PPstats)}, total pkts with associated extras = {pktwextras}')
print(f'>>>Total Missed = {sum(int(row[7]) for row in PPstats)}, total pkts with associated misses = {pktwmisses}')