import pandas as pd

dataframe = pd.read_csv("Waldo_ITW_Data_all_W1.csv", sep=',', 
                  names=["TimeStamp", "BayID", "WaldoID", "cur_PktNum", "cur_Validity", "cur_NumEvents", "cur_e1time", "cur_e1class", "cur_e2time", "cur_e2class", "cur_e3time", "cur_e3class", "cur_e4time", "cur_e4class", "cur_e5time", "cur_e5class",
                  "p_PktNum", "p_Validity", "p_NumEvents", "p_e1time", "p_e1class", "p_e2time", "p_e2class", "p_e3time", "p_e3class", "p_e4time", "p_e4class", "p_e5time", "p_e5class",
                  "pp_PktNum", "pp_Validity", "pp_NumEvents", "pp_e1time", "pp_e1class", "pp_e2time", "pp_e2class", "pp_e3time", "pp_e3class", "pp_e4time", "pp_e4class", "pp_e5time", "pp_e5class"])
print("\nReading the CSV file...\n",dataframe)

numrows = dataframe.size / dataframe.ndim
count = 0 
pkt = -1
df = pd.DataFrame()

#Remove Invalids from Cur_pkt column
dataframe.drop(dataframe[dataframe['cur_Validity'] == "Invalid"].index, inplace = True)

#Get rid of duplicates
df= dataframe.drop_duplicates(subset=['TimeStamp','cur_PktNum','cur_Validity','cur_NumEvents','cur_e1time','cur_e1class','cur_e2time','cur_e2class','cur_e3time','cur_e3class','cur_e4time','cur_e4class','cur_e5time','cur_e5class'], ignore_index=True)
df.reset_index(drop=True, inplace=True)



#Add shit back
#count = 0
#for rows in range(0,df.shape[0] + missing -1):
#    if count > 0:
#        if df['cur_PktNum'][rows] < df['cur_PktNum'][rows-1]:
#            restarts = restarts + 1
#        if (df['cur_PktNum'][rows] - 1) != df['cur_PktNum'][rows-1] and df['cur_PktNum'][rows] != 0 :
#            missing = missing + 1
#            print(df['cur_PktNum'][rows] - 1)
#            if(df['p_PktNum'][rows] == (df['cur_PktNum'][rows] - 1) and df['p_Validity'][rows] == "Valid"):
#                #df.loc[(rows-1)+0.5] = "time", "bae", "w", df['p_PktNum'][rows], df['p_Validity'][rows], df['p_NumEvents'][rows], df['p_e1time'][rows], df['p_e1class'][rows], df['p_e2time'][rows], df['p_e2class'][rows], df['p_e3time'][rows], df['p_e3class'][rows], df['p_e4time'][rows], df['p_e4class'][rows], df['p_e5time'][rows], df['p_e5class'][rows],"","","","","","","","","","","","","","","","","","","","","","","","","",""
#                #df = df.sort_index().reset_index(drop=True)
#                print("added!", df['p_PktNum'][rows])
#    #priorrow = rows[3]
#    #print(rows[2])
#    count = count + 1

df.to_csv('result_waldo2_output_pkts_w1.csv', header = False)

