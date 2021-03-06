import subprocess
import os
import sys
from multiprocessing import Pool
from tabnanny import check
from timeit import default_timer as timer
from unittest import case

prefix = 0
folder = ["../test/opt/", "../test/dec/",
          "../test/PB16/normalized-PB16/DEC-SMALLINT-LIN/", "../test/PB16/normalized-PB16/OPT-SMALLINT-LIN/"]
optfolder = ["../test/opt/", "../test/PB16/normalized-PB16/OPT-SMALLINT-LIN/"]
decfolder = ["../test/PB16/normalized-PB16/DEC-SMALLINT-LIN/"]

f = open("decfile.txt", "w")
F = []
for subfolder in decfolder:
    for path, subdirs, files in os.walk(subfolder):
        for name in files:
            file = name
            if prefix:
                file = os.path.join(path, name)
            if file[-4:] != '.opb' or file[-8:] == '.pre.opb':
                continue
            F.append(file)

print(len(F))
for file in F:
    f.write(str(file)+'\n')
f.close()
