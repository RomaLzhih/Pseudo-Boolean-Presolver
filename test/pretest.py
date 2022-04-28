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
checkTerm = int(sys.argv[2])
solverType = int(sys.argv[3])

InsLoc = InsLoc + filePathTerm + '/'
loggerPath = InsLoc + "0-logger.txt"


def clearlog():
    f1 = open(loggerPath, "w")
    f1.truncate()
    f1.close()


def preParser(lines):
    preStat = solStat = preObj = preSol = fileType = -1
    pre01 = False  # 0-1 check
    for line in lines:
        line = line.split()
        if len(line) == 0 or line[0] == 'C':
            pass
        elif line[0] == 'FILE':
            fileType = int(line[1])
        elif line[0] == 'PRESOLVE_STAT':  # presolved status
            if int(line[1]) == -1:  # already solve
                preStat = 2
            elif int(line[1]) >= 2:  # unbounded or infeasible
                preStat = 0
            else:  # unchanged or reduced
                preStat = 1
        elif line[0] == 'SAT':
            solStat = int(line[1])
        elif line[0] == 'OBJ':
            preObj = line[1]
        elif line[0] == 'VAR':
            preSol = line[1:]
        elif line[0] == 'BOOLEAN':
            pre01 = bool(int(line[1]))
    if preStat == 0 or preStat == 2:  # unbounded or already solve
        pre01 = True
    return (preStat, solStat, preObj, preSol, fileType), pre01


def rsParser(lines):
    rsSolStat = rsObj = rsSol = -1
    for line in lines:
        line = line.split()
        if len(line) == 0 or line[0] == 'c':
            pass
        elif line[0] == 's':
            rsSolStat = 1 if(line[1] == "OPTIMUM" or line[1]
                             == "SATISFIABLE") else 0
        elif line[0] == 'o':
            rsObj = line[1]
        elif line[0] == 'v':
            rsSol = line[1:]
    return rsSolStat, rsObj, rsSol


def runPre(file, onlyPreSolve, solverType):
    start = timer()
    preOut = ""
    solved = True
    print("\t start pre: ")

    try:
        preOut = subprocess.run(
            [preLoc, file, str(onlyPreSolve), str(solverType)], stdout=subprocess.PIPE, timeout=T).stdout.decode('utf-8')
    except subprocess.TimeoutExpired:
        print("timeout")
        solved = False

    preTime = timer()-start
    lines = preOut.split('\n')
    preAns, pre01 = preParser(lines)
    return preAns, pre01, preTime, solved


def runRs(file):
    print("\t start rs: ")
    start = timer()
    solved = True
    rsOut = ""

    try:
        rsOut = subprocess.run([rSLoc, "--print-sol=1", "--verbosity=0", file],
                               stdout=subprocess.PIPE, timeout=T).stdout.decode('utf-8')
    except subprocess.TimeoutExpired:
        print("timeout")
        solved = False

    rsTime = timer()-start
    lines = rsOut.split('\n')
    return rsParser(lines), rsTime, solved


def cmpOpt(preStat, solStat, preObj, preSol, fileType, rsSolStat, rsObj, rsSol):
    flag = True
    res = ""
    # print(preStat, solStat, preObj, preSol, fileType)
    if fileType == 0:
        if solStat == rsSolStat:
            if solStat == 1:
                res = ("OK: optimum pass" + "\t" + preObj + "\t" + rsObj
                       if preObj == rsObj else "FAIL: optimum not pass")
            else:
                res = "OK: infeasible pass"
        else:
            res = "FAIL: OPT " + str(solStat) + str(rsSolStat)
            flag = False
    elif fileType == 1:
        if solStat == rsSolStat:
            res = "OK: satisfiablility pass"
        else:
            res = "FAIL: distinct output for dec"
            flag = False
    return res, flag


def checkOpt(file):
    preSol, pre01, preTime, preSolved = runPre(InsLoc+file, 0, solverType)
    rsSol, rsTime, rsSolved = runRs(InsLoc+file)
    if(preSolved and rsSolved):
        res, optflag = cmpOpt(*preSol, *rsSol)
    else:
        optflag = True
        pre01 = True
        res = "UNKNOWN: preSolved: " + \
            str(preSolved) + ", rsSolved: " + str(rsSolved)

    print(res, "\n\t", preTime, "\n\t", rsTime, '\n', pre01)
    out = file + ": \n" + "\t result: " + res + "\n" + \
        "\t\t pre: " + str(preTime) + "\n\t\t rs: " + str(rsTime) + "\n"
    return out, optflag, pre01


def checkPseudoBoolean(file):
    preAns, pre01, preTime, preSolved = runPre(InsLoc+file, 1, solverType)
    if preSolved:
        out = file + ":\n " + "\t" + str(pre01) + "\n"
    else:
        out = file + ":\n " + "\t" + "UNABLE PRESOLVE" + "\n"
        pre01 = True
    print(pre01)
    return out, pre01


def simpleRun(file):
    runPre(InsLoc+file, 0, solverType)


if __name__ == '__main__':
    files, T, N = os.listdir(InsLoc), 60, 1300
    out, optFlag, PBFlag = "", True, True
    clearlog()
    # files = files[:N]

    for file in files:
        if file[-4:] != '.opb' or file[-8:] == '.pre.opb':
            continue
        f1 = open(loggerPath, "a")
        print(file, ": ")

        if checkTerm == 0:  # checkopt
            out, optflag, pre01 = checkOpt(file)
            optFlag = optFlag and optflag
            PBFlag = PBFlag and pre01
        elif checkTerm == 1:  # only presolve
            out, pre01 = checkPseudoBoolean(file)
            PBFlag = PBFlag and pre01
        else:
            simpleRun(file)

        f1.write(out)
        f1.close()

    print("All pre-soluiton are 0-1? ", PBFlag)
    if(checkTerm == 0):
        print("All soluiton pass? ", optFlag)
