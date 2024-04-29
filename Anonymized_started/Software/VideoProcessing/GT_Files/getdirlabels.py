import os
import sys

path = "/Users/tobias4lyph/Desktop/Waldo/WaldoMain/Software/VideoProcessing/"
Location = "Results_Stairs"
path = path + Location
path = path + "/20230120/"
ref_path = path
allfoldernames = os.listdir(path)

if '.DS_Store' in allfoldernames:
    goodbye = path + ".DS_Store"
    os.remove(goodbye)

allfoldernames = sorted(os.listdir(path))

for folders in allfoldernames:
    path = path + folders
    path = path + "/"

    for files in sorted(os.listdir(path)):
        if files.endswith(".tsv"):
            fi = files.split("_")
            print(fi[0] + ", " + Location.split("_")[1] + ", " + fi[1] + ":" + fi[2] + ":" 
                        + fi[3].split("-")[0])
    path = ref_path