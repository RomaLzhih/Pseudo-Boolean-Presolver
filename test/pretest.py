import subprocess
import sys
import os
from timeit import default_timer as timer

preLoc = "../build/pre"
preInsLoc = "../test/lion9-single-obj/"
rsPrefix = "/mnt/d/aMain/0-RoundingSat/roundingsat/"
rSLoc = rsPrefix + "build/roundingsat"
rsInsLoc = rsPrefix + "test/lion9-single-obj/"


def preParser(lines):
    preStat = preObj = preSol = -1
    for line in lines:
        line = line.split()
        if len(line) == 0 or line[0] == 'C':
            pass
        elif line[0] == 'S':
            preStat = 1 if int(line[1]) <= 1 else 0
        elif line[0] == 'O':
            preObj = float(line[1])
        elif line[0] == 'V':
            preSol = line[1:]
    return preStat, preObj, preSol


def rsParser(lines):
    rsStat = rsObj = rsSol = -1
    for line in lines:
        line = line.split()
        if len(line) == 0 or line[0] == 'c':
            pass
        elif line[0] == 's':
            rsStat = 1 if line[1] == "OPTIMUM" else 0
        elif line[0] == 'o':
            rsObj = int(line[1])
        elif line[0] == 'v':
            rsSol = line[1:]
    return rsStat, rsObj, rsSol


def clearlog():
    f1 = open("../test/logger.txt", "w")
    f1.truncate()
    f1.close()


if __name__ == '__main__':
    files, T = os.listdir(preInsLoc), 3600
    clearlog()
    for file in files:
        if file[-8:] == '.pre.opb':
            continue
        f1 = open("../test/logger.txt", "a")
        print(file, ": ")

        # run pre
        preinfile = preInsLoc + file
        start = timer()
        print("\t start pre: ")
        try:
            preOut = subprocess.run(
                [preLoc, preinfile], stdout=subprocess.PIPE, timeout=T).stdout.decode('utf-8')
        except subprocess.TimeoutExpired:
            print("timeout")
        preTime = timer()-start
        lines = preOut.split('\n')
        preStat, preObj, preSol = preParser(lines)
        print(preTime)

        # run roundingSat
        print("\t start rs: ")
        rsinfile = rsInsLoc + file
        start = timer()
        try:
            rsOut = subprocess.run([rSLoc, "--print-sol=1", "--verbosity=0", rsinfile],
                                   stdout=subprocess.PIPE, timeout=T).stdout.decode('utf-8')
        except subprocess.TimeoutExpired:
            print("timeout")
        rsTime = timer()-start
        lines = rsOut.split('\n')
        rsStat, rsObj, rsSol = rsParser(lines)
        print(rsTime)

        if preStat == 1 and rsStat == 1:
            res = ("OK: optimum pass" if abs(preObj-rsObj) <
                   1e-4 else "FAIL: optimum not pass")
        elif preStat == 0 and rsStat == 0:
            res = "OK: infeasible pass"
        else:
            res = "FAIL: " + str(preStat) + " " + str(rsStat)
        print("\t", res)

        out = file + ": \n" + "\t result: " + res + "\n" + \
            "\t\t pre: " + str(preTime) + "\n\t\t rs: " + str(rsTime) + "\n"
        f1.write(out)
        f1.close()
