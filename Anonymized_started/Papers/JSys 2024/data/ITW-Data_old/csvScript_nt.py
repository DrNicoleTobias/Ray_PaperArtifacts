#   Script:   csvScript.py
#   run:      python3 csvScript.py formatted_WaldoFile.csv GT_WaldoFile.csv ResultsFilename.csv
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
                
                if pkt_datetime < event_datetime: #and ((diff_cur.total_seconds() < 20.0 and diff_cur.total_seconds() >= -10.0) or (diff_pre.total_seconds() < 20.0 and diff_pre.total_seconds() >= -10.0)):  #diff should be 6 sec plus send time - added cushion for gt human error
                    ct +=1
                    if abs(diff_cur.total_seconds()) < abs(diff_pre.total_seconds()):
                        #MatchList.append([index_bay, bay_array[index_bay][0], bay_array[index_bay][2], index_gt, gt_array[index_gt - 1][3], gt_array[index_gt][3], diff_cur.total_seconds()])
                        MatchList.append([index_bay, bay_array[index_bay][0], index_gt, gt_array[index_gt][2].time()])
                    else:
                        #MatchList.append([index_bay, bay_array[index_bay][0], bay_array[index_bay][2], index_gt - 1, gt_array[index_gt - 1][3], gt_array[index_gt][3], diff_pre.total_seconds()])
                        MatchList.append([index_bay, bay_array[index_bay][0], index_gt - 1, gt_array[index_gt - 1][2].time()])
                    break
  
print(f'BayArray len = {len(bay_array)}, MatchList len = {len(MatchList)}') 
#MatchList has been populated with baystation records and their likely corresponding gt times
#Write all the summarized data to a file
with open("MatchList.csv", mode = 'w') as _filem:
    _writer = csv.writer(_filem, delimiter=",", )

    for row in MatchList:
        _writer.writerow(row)
#Now to calculate the variable windows in the ground truth(gt)
#initialize all of the variables
reported_date = reported_time = reported_ins = reported_outs = reported_pbs = 0
gt_ins = gt_outs = gt_pb_n = gt_pb_f = gt_linger = gt_ll = gt_multi_in = gt_multi_out = gt_multi_passby = 0
marching_over = False

#create a big array to combine the summary data that is computed
SummaryArray = []
SummaryArray.append(['bayIDX', 'bayRecord', 'bayDate', 'bayTime', 'bayIn', 'bayOut', 'bayPassby', 
    'gtDate', 'gtTime', 'gtIns', 'gtOuts','gtPbN', 'gtPbF', 'gtLinger', 'gt_ll', 
    'gtMultiIn', 'gtMultiOut', 'gtMultiPb'])
print(f'Creating summary.....')

#Every MatchList item must have a summary computed over it's associated window of data...
#MatchList = [bayArray_idx, bayRecordID, gt_index, gt_time]
index_match = 0

ct = 0
while index_match < len(MatchList):
    num_duplicate_records = 0
    #Determine if there are duplicate records (this only occurs when a packet is missed and we can recover 
    #some data from a received packet; this is never more than 2)
    if index_match <= (len(MatchList)-2):
        if MatchList[index_match][1] == MatchList[index_match + 1][1]:
            num_duplicate_records = 1
            
        elif MatchList[index_match][1] == MatchList[index_match + 1][1] and MatchList[index_match][1] == MatchList[index_match + 2][1]:
            num_duplicate_records = 2
    #print(f'{num_duplicate_records}')
    next_rec = 0
    for m in range(num_duplicate_records, -1, -1):

        #Compute summary over the past 5 events (as long as they are not already counted in a prior baystation record)
        for i in range(0, 5, +1):
            gt_ref_idx = int(int(MatchList[index_match][2]) - (i + 5*m))
            if gt_ref_idx != 0:
                gt_day = gt_array[gt_ref_idx][2].date()
                #[0]doorway, [1]reviewer, [2]datetime [3]ins [4]outs [5]pbsn [6]passbyf [7]linger [8-10]multi in, out, pb
                #Checking to make sure that you are not marching over another record's data
                #print(f'>>>{MatchList[index_match - 1][2]}')
                if gt_array[gt_ref_idx][2].time() == gt_array[int(MatchList[index_match - 1][2])][2].time():
                    marching_over = True
                if not marching_over:
                    #Computing summary of record window
                    #print(f'{gt_array[gt_ref_idx][4]}')
                    gt_ins += int(gt_array[gt_ref_idx][3])
                    gt_outs += int(gt_array[gt_ref_idx][4])
                    gt_pb_n += int(gt_array[gt_ref_idx][5])
                    gt_pb_f += int(gt_array[gt_ref_idx][6])
                    str_ex = str(gt_array[gt_ref_idx][7])
                    if not str_ex.isdigit():
                        gt_linger += int(str_ex[0])
                        gt_ll += 1
                    else:
                        gt_linger += int(gt_array[gt_ref_idx][7])
                    gt_multi_in += int(gt_array[gt_ref_idx][8])
                    gt_multi_out += int(gt_array[gt_ref_idx][9])
                    gt_multi_passby += int(gt_array[gt_ref_idx][10])
        
        #next_rec += 1  #allows correct shifting for duplicates informataion
        #[0]record, [1]datetime, [2]PKTID, [3]Valid [4]Total [5]Ins [6]Outs [7]Passbys
        bay_ref_idx = MatchList[ct][0] #+ next_rec
        reported_date = bay_array[bay_ref_idx][1].date()
        reported_time = bay_array[bay_ref_idx][1].time()
        reported_ins = bay_array[bay_ref_idx][5]
        reported_outs = bay_array[bay_ref_idx][6]
        reported_pbs = bay_array[bay_ref_idx][7]
        ct += 1
        SummaryArray.append([bay_ref_idx, MatchList[index_match][1], reported_date, reported_time, reported_ins, reported_outs, reported_pbs, 
            gt_day, MatchList[index_match][3], gt_ins, gt_outs, gt_pb_n, gt_pb_f, gt_linger, gt_ll, 
            gt_multi_in, gt_multi_out, gt_multi_passby])
        #index_match += 1
        #resetting flags and counters
        marching_over = False
        gt_ins = gt_outs = gt_pb_n = gt_pb_f = gt_linger = 0
        gt_ll = gt_multi_in = gt_multi_out = gt_multi_passby = 0

    index_match += 1 + num_duplicate_records
print(f'{ct}')

#Write all the summarized data to a file
with open(sys.argv[3], mode = 'w') as _file:
    _writer = csv.writer(_file, delimiter=",", )

    for row in SummaryArray:
        _writer.writerow(row)
