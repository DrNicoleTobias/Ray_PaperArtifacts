import csv
import os
import sys
import numpy as np

input_file = sys.argv[1]
print('Input File: ' + input_file)

#path, input_filename = os.path.split(input_file)
#print('Path: ' + path)
#print('Filename: ' + input_filename)


with open(input_file, 'r') as csvfile:
    summaryArray = csv.reader(csvfile, delimiter=',', quotechar='|')
    line_count = 0
   
    tp_ins = tp_outs = tp_pb = 0
    fp_ins = fp_outs = fp_pb = 0
    fn_ins = fn_outs = fn_pb = 0
    total = 0
    gt_others = 0
    gt_long = 0
    for row in summaryArray:
        if line_count == 0:
            print(str(row))
            line_count += 1
            continue
        #print(str(row))
        bay_ins = int(row[4])
        bay_outs = int(row[5])
        bay_passbys = int(row[6])
        bay_events = bay_ins + bay_outs + bay_passbys
        gt_ins = int(row[9])
        gt_outs = int(row[10])
        gt_passbys = int(row[11]) + int(row[12]) + int(row[17])
        gt_others += sum(int(row[i]) for i in range(13,18)) - int(row[14]) - int(row[17])
        gt_long += int(row[14])
        gt_events = gt_ins + gt_outs + gt_passbys + gt_others

        if bay_ins == gt_ins and gt_ins != 0:
            tp_ins += bay_ins
        elif bay_ins > gt_ins:
            tp_ins += gt_ins
            fp_ins += bay_ins - gt_ins
        elif gt_ins > bay_ins:
            tp_ins += bay_ins
            fn_ins += gt_ins - bay_ins
        
        if bay_outs == gt_outs and gt_outs != 0:
            tp_outs += bay_outs
        elif bay_outs > gt_outs:
            tp_outs += gt_outs
            fp_outs += bay_outs - gt_outs
        elif gt_outs > bay_outs:
            tp_outs += bay_outs
            fn_outs += gt_outs - bay_outs
        
        if bay_passbys == gt_passbys and gt_passbys != 0:
            tp_pb += bay_passbys
        elif bay_passbys > gt_passbys:
            tp_pb += gt_passbys
            fp_pb += bay_passbys - gt_passbys
        elif gt_passbys > bay_passbys:
            tp_pb += bay_passbys
            fn_pb += gt_passbys - bay_passbys
        
        total += gt_ins + gt_outs + gt_passbys

TP = tp_ins + tp_outs + tp_pb
FP = fp_ins + fp_outs + fp_pb
FN = fn_ins + fn_outs + fn_pb

Precision = TP / (TP + FP)
Recall = TP / (TP + FN)
Accuracy = (TP / total)
F1score = 2 * ((Precision * Recall) / (Precision + Recall))

'''
event_fn = event_fp = event_tp = 0
eventdetection = bay_events / gt_events
if bay_events == gt_events and gt_events != 0:
    event_tp = bay_events
elif bay_events > gt_events:
    event_tp = gt_events
    event_fp = bay_events - gt_events
elif bay_events > gt_events:
    event_tp = bay_events
    event_fn = gt_events - bay_events

ePrecision = event_tp / (event_tp + event_fp)
eRecall = event_tp / (event_tp + event_fn)
eAccuracy = (event_tp / gt_events)
eF1score = 2 * ((ePrecision * eRecall) / (ePrecision + eRecall))
'''
#TPRate = TP / (TP + FN)
print("===========================================================================")
print("Total = " + str(total))
print("TP = " + str(TP))
print("FP = " + str(FP))
print("FN = " + str(FN))
print("Precision [TP / (TP + FP)] = " + str(Precision * 100) + "%")
print("Recall [TP / (TP + FN)] = " + str(Recall * 100) + "%")
print("Accuracy [(TP / total_gt_inoutpbEvents)]= " + str(Accuracy * 100) + "%")
print("F1 score [2 * ((Precision * Recall) / (Precision + Recall))]= " + str(F1score * 100) + "%")
print(f'   others ->  {gt_others} and longs ->  {gt_long}')
print("===========================================================================")
'''
print("Total = " + str(gt_events))
print("TP = " + str(event_tp))
print("FP = " + str(event_fp))
print("FN = " + str(event_fn))
print("Event Precision [TP / (TP + FP)] = " + str(ePrecision * 100) + "%")
print("Event Recall [TP / (TP + FN)] = " + str(eRecall * 100) + "%")
print("Event Accuracy [(TP / total_gt_inoutpbEvents)]= " + str(eAccuracy * 100) + "%")
print("Event F1 score [2 * ((Precision * Recall) / (Precision + Recall))]= " + str(eF1score * 100) + "%")
print("Event Detection [basestation_events / gt_events]= " + str(eventdetection * 100) + "%")
'''      
'''
    print("===========================================================================")
    in_avg = np.mean(ins_list)
    print("Total INs = " + str(total_ins))
    print("INs detected on Waldo = " + str(total_det_ins))
    print("Total INs matched = " + str(total_ins_match))
    print("Average IN Accuracy [Average accuracy per radio packet] = " + str(in_avg) + "%")
    print("Overall IN Accuracy [INs matched/Actual INs] = " + str(100*float(total_ins_match)/float(total_ins)) + "%")
    print("Total IN False Positives = " + str(total_in_fpos))
    print("Total IN False Negatives = " + str(total_in_fneg))
'''
    