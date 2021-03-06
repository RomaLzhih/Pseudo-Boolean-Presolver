from cgi import test
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

start = int(sys.argv[1])
token = sys.argv[2]
SATparam = sys.argv[3]
MIPparam = sys.argv[4]
onlyPreSolve = int(sys.argv[5])
solverType = int(sys.argv[6])
T = int(sys.argv[7])

loggerPath = "../test/otheropt/1800loggers/" + token + "/"


def runPre(file):
    if file[-4:] != '.opb' or file[-8:] == '.pre.opb':
        return
    print(file)
    info = ""
    try:
        info = subprocess.run(
            [preLoc, file, SATparam, MIPparam, str(
                onlyPreSolve), str(solverType)],
            stdout=subprocess.PIPE, timeout=T).stdout.decode('utf-8')
    except subprocess.TimeoutExpired:
        print("timeout")
        fileName = file[file.rfind('/')+1:]
        info = "& " + fileName+" timeout\n"
    return str(info)


def fetchFile():
    f = open("../test/otheropt/allOPB.txt", "r")
    lines = f.readlines()
    file = lines[start]
    if file[-1] == '\n':
        file = file[0:len(file)-1]
    return file


if __name__ == '__main__':
    file = fetchFile()
    info = runPre(file)
    name = file[file.rfind('/'):file.rfind('.')]
    # print(info)
    f = open(loggerPath+name+'.txt', "w")
    f.write(info)
    f.flush()
    f.close()
