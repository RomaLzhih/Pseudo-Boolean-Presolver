import subprocess
import os
import sys
from multiprocessing import Pool
from tabnanny import check
from timeit import default_timer as timer
from unittest import case

prefix = 1
folder = ["../test/otherdec/PB16-used-dec/"]

f = open("../test/otherdec/allDEC.txt", "w")
F = []
for subfolder in folder:
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
