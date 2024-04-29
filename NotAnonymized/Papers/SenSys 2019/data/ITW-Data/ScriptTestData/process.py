import csv
import os
import sys
import numpy as np

input_file = sys.argv[1];
print('Input File: ' + input_file);

path, input_filename = os.path.split(input_file)
print('Path: ' + path)
print('Filename: ' + input_filename)

output_file = path + '/output-' + input_filename
print('Output File: ' + output_file);

op_flag = raw_input("Do you want to save output to file? (y/n)")

if op_flag == 'y':
    out = open( output_file , 'w') 


with open(input_file, 'r') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    line_count = 0
   
    total_ins = 0
    ins_list = []
    total_in_fneg = 0
    total_in_fpos = 0
    total_det_ins = 0
    total_ins_match = 0

    total_outs = 0
    outs_list = []
    total_out_fneg = 0
    total_out_fpos = 0
    total_det_outs = 0
    total_outs_match = 0
    
    total_passbys = 0
    passbys_list = []
    total_passby_fneg = 0
    total_passby_fpos = 0
    total_det_passbys = 0
    total_passbys_match = 0
    
    for row in spamreader:
        if line_count == 0:
            print(str(row))
            line_count += 1
            continue
        #print(str(row))
        waldo_ins = int(row[4])
        waldo_outs = int(row[5])
        waldo_passbys = int(row[6])
        camera_ins = int(row[9])
        camera_outs = int(row[10])
        camera_passbys = int(row[11]) + int(row[12])
        camera_others = sum(int(row[i]) for i in range(13,18)) 

        #print( "Ins=" + str(waldo_ins) + " | Outs=" + str(waldo_outs) + " | Passbys=" +  str(waldo_passbys) + " | GTIns=" + str(camera_ins) + " | GTOuts=" + str(camera_outs) + " | GTPassBys=" + str(camera_passbys) + " | GTOthers=" + str(camera_others))   

        total_ins += camera_ins
        total_outs += camera_outs
        total_passbys += camera_passbys

        if waldo_ins == camera_ins:
            in_accuracy = 100
            in_fneg = 0
            in_fpos = 0
            total_ins_match += waldo_ins
        elif waldo_ins < camera_ins:
            in_accuracy = 100*float(waldo_ins)/float(camera_ins)
            in_fneg = camera_ins - waldo_ins
            in_fpos = 0
            total_ins_match += waldo_ins
        elif waldo_ins > camera_ins:
            in_accuracy = 100
            in_fneg = 0
            in_fpos = waldo_ins - camera_ins
            total_ins_match += camera_ins

        if waldo_outs == camera_outs:
            out_accuracy = 100
            out_fneg = 0
            out_fpos = 0
            total_outs_match += waldo_outs
        elif waldo_outs < camera_outs:
            out_accuracy = 100*float(waldo_outs)/float(camera_outs)
            out_fneg = camera_outs - waldo_outs
            out_fpos = 0
            total_outs_match += waldo_outs
        elif waldo_outs > camera_outs:
            out_accuracy = 100
            out_fneg = 0
            out_fpos = waldo_outs - camera_outs
            total_outs_match += camera_outs

        if waldo_passbys == camera_passbys:
            passby_accuracy = 100
            passby_fneg = 0
            passby_fpos = 0
            total_passbys_match += waldo_passbys
        elif waldo_passbys < camera_passbys:
            passby_accuracy = 100*float(waldo_passbys)/float(camera_passbys)
            passby_fneg = camera_passbys - waldo_passbys
            passby_fpos = 0
            total_passbys_match += waldo_passbys
        elif waldo_passbys > camera_passbys:
            passby_accuracy = 100
            passby_fneg = 0
            passby_fpos = waldo_passbys - camera_passbys
            total_passbys_match += camera_passbys

        ins_list.append(in_accuracy)
        total_in_fneg += in_fneg
        total_in_fpos += in_fpos
        total_det_ins += waldo_ins
        #print("IN Accuracy = " + str(in_accuracy) + "% | False Negatives = " + str(in_fneg) + " | False Positives = " + str(in_fpos))
        
        outs_list.append(out_accuracy)
        total_out_fneg += out_fneg
        total_out_fpos += out_fpos
        total_det_outs += waldo_outs
        
        passbys_list.append(passby_accuracy)
        total_passby_fneg += passby_fneg
        total_passby_fpos += passby_fpos
        total_det_passbys += waldo_passbys

    print("===========================================================================")
    in_avg = np.mean(ins_list)
    print("Total INs = " + str(total_ins))
    print("INs detected on Waldo = " + str(total_det_ins))
    print("Total INs matched = " + str(total_ins_match))
    print("Average IN Accuracy [Average accuracy per radio packet] = " + str(in_avg) + "%")
    print("Overall IN Accuracy [INs matched/Actual INs] = " + str(100*float(total_ins_match)/float(total_ins)) + "%")
    print("Total IN False Positives = " + str(total_in_fpos))
    print("Total IN False Negatives = " + str(total_in_fneg))

    print("===========================================================================")
    out_avg = np.mean(outs_list)
    print("Total OUTs = " + str(total_outs))
    print("OUTs detected on Waldo = " + str(total_det_outs))
    print("Total OUTs matched = " + str(total_outs_match))
    print("Average OUT Accuracy [Average accuracy per radio packet] = " + str(out_avg) + "%")
    print("Overall OUT Accuracy [OUTs matched/Actual OUTs] = " + str(100*float(total_outs_match)/float(total_outs)) + "%")
    print("Total OUT False Positives = " + str(total_out_fpos))
    print("Total OUT False Negatives = " + str(total_out_fneg))
    
    print("===========================================================================")
    passby_avg = np.mean(passbys_list)
    print("Total PASSBYs = " + str(total_passbys))
    print("PASSBYs detected on Waldo = " + str(total_det_passbys))
    print("Total PASSBYs matched = " + str(total_passbys_match))
    print("Average PASSBY Accuracy [Average accuracy per radio packet] = " + str(passby_avg) + "%")
    print("Overall PASSBY Accuracy [PASSBYs matched/Actual PASSBYs] = " + str(100*float(total_passbys_match)/float(total_passbys)) + "%")
    print("Total PASSBY False Positives = " + str(total_passby_fpos))
    print("Total PASSBY False Negatives = " + str(total_passby_fneg))

