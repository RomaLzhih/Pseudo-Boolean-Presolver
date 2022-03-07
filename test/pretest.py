import subprocess
import sys
import os
from timeit import default_timer as timer

preLoc = "../build/pre"
preInsLoc = "../test/opt/"
rsPrefix = "/mnt/d/aMain/0-RoundingSat/roundingsat/"
rSLoc = rsPrefix + "build/roundingsat"
rsInsLoc = rsPrefix + "test/instances/opb/opt/"


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


hardIns = ["air02.opb", "air03.opb", "air04.opb",
           "air05.opb", "air06.opb", "cracpb1.opb",
           "l152lav.opb", "mod010.opb", "p0548.opb",
           "p2756.opb", "p6000.opb", "stein45.opb"]

if __name__ == '__main__':
	files = os.listdir(preInsLoc)
	T = 3600
	for file in hardIns:
		if file[-8:] == '.pre.opb':
			continue
		print(file, ": ")
		print("\t start pre .. ", end='')
		# run pre
		preinfile = preInsLoc + file
		start = timer()
		try:
			preOut = subprocess.run(
				[preLoc, preinfile], stdout=subprocess.PIPE, timeout=T).stdout.decode('utf-8')
		except subprocess.TimeoutExpired:
			print("timeout")
		end = timer()
		print(end-start)
		lines = preOut.split('\n')
		preStat, preObj, preSol = preParser(lines)

		# run roundingSat
		print("\t start rs .. ", end='')
		rsinfile = rsInsLoc + file
		start = timer()
		try:
			rsOut = subprocess.run([rSLoc, "--print-sol=1", "--verbosity=0", rsinfile],
			                       stdout=subprocess.PIPE, timeout=T).stdout.decode('utf-8')
		except subprocess.TimeoutExpired:
			print("timeout")
		end = timer()
		print(end-start)
		lines = rsOut.split('\n')
		rsStat, rsObj, rsSol = rsParser(lines)

		print("---", end='')
		if preStat == 1 and rsStat == 1:
			res = ("ok: optimum pass" if abs(preObj-rsObj) <
			       1e-4 else "fail: optimum not pass")
		elif preStat == 0 and rsStat == 0:
			res = "ok: infeasible pass"
		else:
			res = "fail: non-match optimum"
		print(res)
