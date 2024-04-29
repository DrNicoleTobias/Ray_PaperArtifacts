#   Script:   csvScript.py
#   run:      python3 csvScript.py formatted_WaldoFile.csv GT_WaldoFile.csv ResultsFilename.csv
#   input:    WaldoDB_file.csv GT_file.csv
#   output:   ResultsFilename.csv 
#   Purpose:  This script is to run over a sample of the test data to try and line up 
#             likely matches in the waldo data to what is available in the ground truth.
#   Current state:  Kind of working... seems to work on a small dataset; 
#                   Doesn't work with multiple dates yet...

import csv
from datetime import datetime, date, time
import sys
import os

#os.remove(sys.argv[3])
#print(f'Results file removed.')
print(f'Reading in csv files.....')
#[0]record, [1]date, [2]time, [3]PKTID,
#[4]Valid [5]Total [6]Ins [7]Outs [8]Passbys 
with open(sys.argv[1]) as csv_file_baystation:
    csv_reader_baystation = csv.reader(csv_file_baystation, delimiter=',')
    bay_array = list(csv_reader_baystation)
    #for index_bay in range(len(bay_array)):
    #    if index_bay != 0:
    #        temp = time.strptime(bay_array[index_bay][2], "%I:%M:%S %p")
    #        bay_array[index_bay][2] = temp

#[0]doorway, [1]reviewer, [2]date, [3]time,
#[4]ins [5]outs [6]pbsn [7]passbyf [8]linger [9-11]multi in, out, pb
with open(sys.argv[2]) as csv_file:
    csv_reader_gt = csv.reader(csv_file, delimiter=',')
    gt_array = list(csv_reader_gt)
    for index_gt in range(len(gt_array)):
        #if index_gt != 0:
        #    temp = time.strptime(gt_array[index_gt][3], "%I:%M:%S %p")
        #    gt_array[index_gt][3] = temp

            #get rid of empty str issues
            for i in range(len(gt_array[index_gt])):
                    if gt_array[index_gt][i] == '':
                        gt_array[index_gt][i] = 0

#This matches Record time to the lower boundary ground truth time
# MatchList is a multidimensional array with 4 values per row: 
#                   [bay_array_index, bay_record_number, gt_array_index, matching_gt_time]
print(f'Finding possible matches.....')
MatchList = []
#ct = 0
for index_bay in range(len(bay_array)):
    if index_bay != 0:
        str_bay = bay_array[index_bay][1] + " " + bay_array[index_bay][2]   #date + time
        ticktock_bay = datetime.strptime(str_bay, "%d-%b %I:%M:%S %p")
        #print(f'{datetime.strftime(ticktock_bay, "%d-%b %I:%M:%S %p")}')
        for index_gt in range(len(gt_array)):
            if index_gt >= 2:
                str_gt = gt_array[index_gt-1][2] + " " + gt_array[index_gt-1][3]   #date + time
                ticktock_gt = datetime.strptime(str_gt, "%d-%b %I:%M:%S %p")
                diff = abs(ticktock_bay - ticktock_gt)
                if bay_array[index_bay][1] == gt_array[index_gt-1][2] and bay_array[index_bay][2] < gt_array[index_gt][3] and diff.total_seconds() < 15:  #diff should be 6 sec plus send time - added cushion for gt human error
                    #ct +=1
                    #print(f'{ct}. {ticktock_bay} Index {bay_array[index_bay][0]} on day {bay_array[index_bay][1]} at {bay_array[index_bay][2]} MATCHES {gt_array[index_gt - 1][2]} at {gt_array[index_gt - 1][3]}')
                    MatchList.append([index_bay, bay_array[index_bay][0], index_gt - 1, gt_array[index_gt - 1][3]])
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
        if MatchList[index_match][1] == MatchList[index_match + 1][1] and MatchList[index_match][1] == MatchList[index_match + 2][1]:
            num_duplicate_records = 2
            
        elif MatchList[index_match][1] == MatchList[index_match + 1][1]:
            num_duplicate_records = 1
    #print(f'{num_duplicate_records}')
    next_rec = 0
    for m in range(num_duplicate_records, -1, -1):

        #Compute summary over the past 5 events (as long as they are not already counted in a prior baystation record)
        for i in range(0, 5, +1):
            gt_ref_idx = int(int(MatchList[index_match][2]) - (i + 5*m))
            if gt_ref_idx != 0:
                gt_day = gt_array[gt_ref_idx][2]
                #Checking to make sure that you are not marching over another record's data
                if gt_array[gt_ref_idx][3] == gt_array[MatchList[index_match - 1][2]][3]:
                    marching_over = True
                if not marching_over:
                    #Computing summary of record window
                    #print(f'{gt_array[gt_ref_idx][4]}')
                    gt_ins += int(gt_array[gt_ref_idx][4])
                    gt_outs += int(gt_array[gt_ref_idx][5])
                    gt_pb_n += int(gt_array[gt_ref_idx][6])
                    gt_pb_f += int(gt_array[gt_ref_idx][7])
                    str_ex = str(gt_array[gt_ref_idx][8])
                    if not str_ex.isdigit():
                        gt_linger += int(str_ex[0])
                        gt_ll += 1
                    else:
                        gt_linger += int(gt_array[gt_ref_idx][8])
                    gt_multi_in += int(gt_array[gt_ref_idx][9])
                    gt_multi_out += int(gt_array[gt_ref_idx][10])
                    gt_multi_passby += int(gt_array[gt_ref_idx][11])
        
        #next_rec += 1  #allows correct shifting for duplicates informataion
        bay_ref_idx = MatchList[ct][0] #+ next_rec
        reported_date = bay_array[bay_ref_idx][1]
        reported_time = bay_array[bay_ref_idx][2]
        reported_ins = bay_array[bay_ref_idx][6]
        reported_outs = bay_array[bay_ref_idx][7]
        reported_pbs = bay_array[bay_ref_idx][8]
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
