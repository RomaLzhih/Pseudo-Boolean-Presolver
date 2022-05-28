#!/bin/bash

#export name=roundingSat
export onlyPreSolve=0
export timelimit=1800

names=(withhbr withouthbr)

module restore pre

#! DEC
#* wihthbr
SATparam=defaultSAT
MIPparam=decmip1
solverType=2
rm -r ../test/otherdec/1800loggers/withhbr/
mkdir ../test/otherdec/1800loggers/withhbr
sbatch -J withhbr_1 declhs.sh withhbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withhbr_2 decmid.sh withhbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withhbr_3 decrhs.sh withhbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

#* without hbr
SATparam=offSAT
MIPparam=decmip1
solverType=1
rm -r ../test/otherdec/1800loggers/withouthbr/
mkdir ../test/otherdec/1800loggers/withouthbr
sbatch -J withouthbr_1 declhs.sh withouthbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withouthbr_2 decmid.sh withouthbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withouthbr_3 decrhs.sh withouthbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

#! OPT
#* with hbr
SATparam=defaultSAT
MIPparam=optmip1
solverType=2
rm -r ../test/otheropt/1800loggers/withhbr/
mkdir ../test/otheropt/1800loggers/withhbr
sbatch -J withhbr_1 optlhs.sh withhbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withhbr_2 optrhs.sh withhbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

#* without hbr
SATparam=offSAT
MIPparam=optmip1
solverType=1
rm -r ../test/otheropt/1800loggers/withouthbr/
mkdir ../test/otheropt/1800loggers/withouthbr
sbatch -J withouthbr_1 optlhs.sh withouthbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withouthbr_2 optrhs.sh withouthbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit



