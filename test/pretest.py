import subprocess
import os
import sys
from tabnanny import check
from timeit import default_timer as timer
from unittest import case

preLoc = "/home/mzy/thesis_project/pre/build/pre"
rSLoc = "/home/mzy/thesis_project/roundingsat/build/roundingsat"
InsLoc = "/home/mzy/thesis_project/pre/test/"

filePathTerm = sys.argv[1]
checkTerm = sys.argv[2]

InsLoc = InsLoc + filePathTerm + '/'


def preParser(lines):
    preStat = preObj = preSol = -1
    pre01 = False  # 0-1 check
    for line in lines:
        line = line.split()
        if len(line) == 0 or line[0] == 'C':
            pass
        elif line[0] == 'S':
            if int(line[1]) == -1:  # already solve
                preStat = 2
            elif int(line[1]) >= 2:  # unbounded or infeasible
                preStat = 0
            else:  # unchanged or reduced
                preStat = 1
        elif line[0] == 'O':
            preObj = line[1]
        elif line[0] == 'V':
            preSol = line[1:]
        elif line[0] == 'P':
            pre01 = bool(int(line[1]))
    if preStat == 0 or preStat == 2:
        pre01 = True
    return (preStat, preObj, preSol), pre01


def rsParser(lines):
    rsStat = rsObj = rsSol = -1
    for line in lines:
        line = line.split()
        if len(line) == 0 or line[0] == 'c':
            pass
        elif line[0] == 's':
            rsStat = 1 if line[1] == "OPTIMUM" else 0
        elif line[0] == 'o':
            rsObj = line[1]
        elif line[0] == 'v':
            rsSol = line[1:]
    return rsStat, rsObj, rsSol


def clearlog():
    f1 = open("../test/logger.txt", "w")
    f1.truncate()
    f1.close()


def runPre(file, onlyPreSolve):
    start = timer()
    print("\t start pre: ")
    try:
        preOut = subprocess.run(
            [preLoc, file, str(onlyPreSolve)], stdout=subprocess.PIPE, timeout=T).stdout.decode('utf-8')
    except subprocess.TimeoutExpired:
        print("timeout")

    preTime = timer()-start
    lines = preOut.split('\n')

    preAns, pre01 = preParser(lines)
    return preAns, pre01, preTime


def runRs(file):
    print("\t start rs: ")
    start = timer()
    try:
        rsOut = subprocess.run([rSLoc, "--print-sol=1", "--verbosity=0", file],
                               stdout=subprocess.PIPE, timeout=T).stdout.decode('utf-8')
    except subprocess.TimeoutExpired:
        print("timeout")
    rsTime = timer()-start
    lines = rsOut.split('\n')
    return rsParser(lines), rsTime


def cmpOpt(preStat, preObj, preSol, rsStat, rsObj, rsSol):
    flag = True
    if preStat >= 1 and rsStat == 1:  # *pre already-solve 2/reduced 1
        res = ("OK: optimum pass" + "\t" + preObj + "\t" + rsObj
               if preObj == rsObj else "FAIL: optimum not pass")
    elif preStat == 0 and rsStat == 0:
        res = "OK: infeasible pass"
    else:
        res = "FAIL: " + str(preStat) + " " + str(rsStat)
        flag = False
    return res, flag


def checkOpt(file):
    preSol, pre01, preTime = runPre(InsLoc+file, 0)
    rsSol, rsTime = runRs(InsLoc+file)
    res, optflag = cmpOpt(*preSol, *rsSol)

    print(res, "\n\t", preTime, "\n\t", rsTime)
    out = file + ": \n" + "\t result: " + res + "\n" + \
        "\t\t pre: " + str(preTime) + "\n\t\t rs: " + str(rsTime) + "\n"
    return out, optflag, pre01


def checkPseudoBoolean(file):
    preAns, pre01, preTime = runPre(InsLoc+file, 1)
    out = file + ":\n " + "\t" + str(pre01) + "\n"
    print(pre01)
    return out, pre01


if __name__ == '__main__':
    files, T, N = os.listdir(InsLoc), 600, 1300
    out, optFlag, PBFlag = "", True, True
    clearlog()
    # files = files[:N]

    for file in files:

        if file[-8:] == '.pre.opb':
            continue
        f1 = open("../test/logger.txt", "a")
        print(file, ": ")

        if int(checkTerm) == 0:  # checkopt
            out, optflag, pre01 = checkOpt(file)
            optFlag = optFlag and optflag
            PBFlag = PBFlag and pre01
        elif int(checkTerm) == 1:  # only presolve
            out, pre01 = checkPseudoBoolean(file)
            PBFlag = PBFlag and pre01

        f1.write(out)
        f1.close()

    print("All pre-soluiton are 0-1? ", PBFlag)
    if(int(checkTerm) == 0):
        print("All soluiton pass? ", optFlag)
