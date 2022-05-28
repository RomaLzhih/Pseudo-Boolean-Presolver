from signal import pause
import subprocess
import os
import sys
from multiprocessing import Pool
from tabnanny import check
from timeit import default_timer as timer
from unittest import case
import math
import csv

emptyList = [
    "9vliw_m_9stages_iq3_C1_bug1.opb"
]

summaryName = sys.argv[1]
analysisParam = int(sys.argv[2])

filePathTerm = "../test/otherdec/1800loggers/"+summaryName+'/'
csvFile = "../test/otherdec/1800loggers/analysis/" + \
    summaryName + ('.csv' if analysisParam == 0 else '-param.csv')


header = ['status', 'file', 'sol', 'obj', 'rsTime',
          'preTime', 'totTime', 'variables', 'Constraints']
f = open(csvFile, "w", newline='')
f.truncate()
allFile = open("../test/otherdec/allDEC.txt", "r").readlines()

files = os.listdir(filePathTerm)
writer = csv.writer(f)
writer.writerow(header)


def findPath(file):
    for path in allFile:
        if path.find(file) != -1:
            # print(path)
            f = open(path[:path.rfind('\n')], "r")
            line = f.readline()
            f.close()
            # print(line)
            l = " ".join(line.split())
            l = l.split(' ')
            N = int(l[2])
            M = int(l[4])
            # print(N, M)
            return N, M


def mergeinfo(l, N, M, file):
    nl = [-1] * 9
    nl[0] = l[0]
    nl[1] = file if analysisParam == 0 else l[1]
    nl[2] = l[2]
    if nl[2] == 'timeout':
        nl[3:7] = [-1]*4
    elif summaryName == 'roundingSat':
        nl[3:5] = l[3:5]
        nl[5] = 0
        nl[6] = l[4]
    else:
        nl[3:7] = l[3:7]
    nl[7:9] = [N, M]
    return nl


for file in files:
    f1 = open(filePathTerm+file, "r")
    lines = f1.readlines()
    N, M = 0, 0
    currentFileName = ''
    for line in lines:
        l = " ".join(line.split())
        l = l.split(' ')
        if l[0] == '@' or l[0] == '*' or line[0] == '&' or line[0] == '$' or line[0] == '#':
            if l[1] in emptyList:
                break
            if summaryName == 'offMIP' and l[0] == '*':
                continue
            if l[0] != '*':
                N, M = findPath(l[1])
                currentFileName = l[1]
            writer.writerow(mergeinfo(l, N, M, currentFileName))

    f1.close()

f.close()
print("done")
