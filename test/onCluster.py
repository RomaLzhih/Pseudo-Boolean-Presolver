import subprocess
import os
import sys
from tabnanny import check
from timeit import default_timer as timer
from unittest import case

preLoc = "/home/mzy/thesis_project/pre/build/pre"
rSLoc = "/home/mzy/thesis_project/roundingsat/build/roundingsat"
InsLoc = "/home/mzy/thesis_project/pre/"

addToken = sys.argv[1]
onlyPreSolve = int(sys.argv[2])
solverType = int(sys.argv[3])
T, N = 60, 1300

loggerPath = ""

decins = ["../test/PB16/normalized-PB16/DEC-SMALLINT-LIN/",
          "../test/dec/"]
optins = ["../test/PB16/normalized-PB16/OPT-SMALLINT-LIN/",
          "../test/PB16/normalized-PB16/OPT-BIGINT-LIN/",
          "../test/opt/"]


def runPre(files):
    for file in files:
        if file[-4:] != '.opb' or file[-8:] == '.pre.opb':
            continue
        print(file)
        try:
            subprocess.run(
                [preLoc, file, loggerPath, str(onlyPreSolve), str(solverType)], stdout=subprocess.PIPE, timeout=T).stdout.decode('utf-8')
        except subprocess.TimeoutExpired:
            print("timeout")
            f = open(loggerPath, "a")
            fileName = file[file.rfind('/')+1:]
            f.write("@ " + fileName+" timeout\n")
            f.close()


def clearlog():
    f1 = open(loggerPath, "w")
    f1.truncate()
    f1.close()


if __name__ == '__main__':
    F = []
    loggerPath = "../test/loggers/opt/" + addToken + ".txt"
    clearlog()
    for opt in optins:
        for path, subdirs, files in os.walk(opt):
            for name in files:
                file = os.path.join(path, name)
                F.append(file)
    runPre(F)

    F = []
    loggerPath = "../test/loggers/dec/" + addToken + ".txt"
    clearlog()
    for dec in decins:
        for path, subdirs, files in os.walk(dec):
            for name in files:
                file = os.path.join(path, name)
                F.append(file)
    runPre(F)
