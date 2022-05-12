import subprocess
import os
import sys
from multiprocessing import Pool
from tabnanny import check
from timeit import default_timer as timer
from unittest import case

preLoc = "../build/pre"

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


def runPre(file):
    if file[-4:] != '.opb' or file[-8:] == '.pre.opb':
        return
    print(file)
    info = ""
    try:
        info = subprocess.run(
            [preLoc, file, loggerPath, str(onlyPreSolve), str(solverType)],
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


def run(folder):
    for subfolder in folder:
        F = []
        pool = Pool()

        for path, subdirs, files in os.walk(subfolder):
            for name in files:
                file = os.path.join(path, name)
                F.append(file)

        result = pool.map_async(runPre, F)
        answer = result.get(timeout=T+100)
        f = open(loggerPath, "a")
        for info in answer:
            if info != None:
                f.write(info)
        f.close()


if __name__ == '__main__':
    loggerPath = "../test/loggers/opt/" + addToken + ".txt"
    clearlog()
    run(optins)

    loggerPath = "../test/loggers/dec/" + addToken + ".txt"
    clearlog()
    run(decins)
