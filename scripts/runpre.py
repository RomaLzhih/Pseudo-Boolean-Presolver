from mailbox import linesep
import subprocess
import os
import sys
from multiprocessing import Pool
from tabnanny import check
from timeit import default_timer as timer
from tracemalloc import start
from unittest import case
import time

preLoc = "../build/pre"

file = sys.argv[1]
token = sys.argv[2]
onlyPreSolve = int(sys.argv[3])
solverType = int(sys.argv[4])
T = int(sys.argv[5])

loggerPath = "../test/loggers/" + token


def runPre(file):
    if file[-4:] != '.opb' or file[-8:] == '.pre.opb':
        return
    print(file)
    info = ""
    try:
        info = subprocess.run(
            [preLoc, file, str(onlyPreSolve), str(solverType)],
            stdout=subprocess.PIPE, timeout=T).stdout.decode('utf-8')
    except subprocess.TimeoutExpired:
        print("timeout")
        fileName = file[file.rfind('/')+1:]
        info = "& " + fileName+" timeout\n"
    return str(info)


def clearlog():
    f1 = open(loggerPath, "w")
    f1.truncate()
    f1.close()


if __name__ == '__main__':
    if file[-1] == '\n':
        file = file[0:len(file)-1]
    info = runPre(file)
    name = file[file.rfind('/'):file.rfind('.')]
    # print(info)
    f = open(loggerPath+name+'.txt', "w")
    f.write(info)
    f.flush()
    f.close()
