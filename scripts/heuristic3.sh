#!/bin/bash

#export name=roundingSat
export onlyPreSolve=0
export timelimit=1800

names=(withhbrmix withouthbrmix)

module restore pre

#! DEC
#* wihthbr
SATparam=defaultSAT
MIPparam=decmipMix2
solverType=2
rm -r ../test/otherdec/1800loggers/withhbrmix2/
mkdir ../test/otherdec/1800loggers/withhbrmix2
sbatch -J withhbrmix2_1 declhs.sh withhbrmix2 $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withhbrmix2_2 decmid.sh withhbrmix2 $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withhbrmix2_3 decrhs.sh withhbrmix2 $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

#* without hbr
SATparam=offSAT
MIPparam=decmipMix2
solverType=1
rm -r ../test/otherdec/1800loggers/withouthbrmix2/
mkdir ../test/otherdec/1800loggers/withouthbrmix2
sbatch -J withouthbrmix2_1 declhs.sh withouthbrmix2 $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withouthbrmix2_2 decmid.sh withouthbrmix2 $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withouthbrmix2_3 decrhs.sh withouthbrmix2 $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

#! OPT
#* with hbr
SATparam=defaultSAT
MIPparam=optmipMix2
solverType=2
rm -r ../test/otheropt/1800loggers/withhbrmix2/
mkdir ../test/otheropt/1800loggers/withhbrmix2
sbatch -J withhbrmix2_1 optlhs.sh withhbrmix2 $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withhbrmix2_2 optrhs.sh withhbrmix2 $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

#* without hbr
SATparam=offSAT
MIPparam=optmipMix2
solverType=1
rm -r ../test/otheropt/1800loggers/withouthbrmix2/
mkdir ../test/otheropt/1800loggers/withouthbrmix2
sbatch -J withouthbrmix2_1 optlhs.sh withouthbrmix2 $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withouthbrmix2_2 optrhs.sh withouthbrmix2 $SATparam $MIPparam $onlyPreSolve $solverType $timelimit



