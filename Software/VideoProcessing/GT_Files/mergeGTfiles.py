import os
import sys
import pandas as pd

path = "/Users/tobias4lyph/Desktop/Waldo/WaldoMain/Software/VideoProcessing/GT_Files/labHW/"

allfilenames = sorted(os.listdir(path))


print(allfilenames)

dataframe = pd.DataFrame()

for files in allfilenames:
    filepath = path + files
    print("\nStarting...\n",filepath)
    #print(filepath)
    dataframe_temp = pd.read_csv(filepath, sep=',', encoding='latin-1',
                  names=["Date", "Loc", "Time_stamp", "Num_People", "Category", "Direction", "Comment"])
    print("\nReading the CSV file...\n",filepath)
    dataframe = dataframe.append(dataframe_temp, ignore_index=True)

#for columns in dataframe:
#    rows = dataframe[columns]
#    print('Column Name:', columns)
#    print('Contents: ', rows.values)

for i, rows in dataframe.iterrows():
    date = str(rows["Date"])
    YYYY = date[0:4]
    MM = date[4:6]
    DD = date[6:8]
    date = YYYY + '-' + MM + '-' + DD
    dataframe.at[i, "Date"] = date
    #print(date)
    #print('Contents: ', rows[0])

dataframe["Time_stamp"] = dataframe["Date"].astype(str) + " " + dataframe["Time_stamp"].astype(str)

df = pd.DataFrame().assign(Time_stamp=dataframe["Time_stamp"], Location=dataframe["Loc"], People=dataframe["Num_People"], Category=dataframe["Category"], Direction=dataframe["Direction"], Comments=dataframe["Comment"])
#x = df.to_string(header=False, index=False).split('\n')
#vals = [','.join(ele.split()) for ele in x]
#print(x)
resultsfilename = path + "GT_All_LabHW_Results.csv"
df.to_csv(resultsfilename, header =False, index=False)