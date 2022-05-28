#!/bin/bash

#export name=roundingSat
export onlyPreSolve=0
export timelimit=1800

names=(withhbrmix withouthbrmix)

module restore pre

#! DEC
#* wihthbr
SATparam=defaultSAT
MIPparam=decmipMix
solverType=2
rm -r ../test/otherdec/1800loggers/withhbrmix/
mkdir ../test/otherdec/1800loggers/withhbrmix
sbatch -J withhbrmix_1 declhs.sh withhbrmix $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withhbrmix_2 decmid.sh withhbrmix $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withhbrmix_3 decrhs.sh withhbrmix $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

#* without hbr
SATparam=offSAT
MIPparam=decmipMix
solverType=1
rm -r ../test/otherdec/1800loggers/withouthbrmix/
mkdir ../test/otherdec/1800loggers/withouthbrmix
sbatch -J withouthbrmix_1 declhs.sh withouthbrmix $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withouthbrmix_2 decmid.sh withouthbrmix $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withouthbrmix_3 decrhs.sh withouthbrmix $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

#! OPT
#* with hbr
SATparam=defaultSAT
MIPparam=optmipMix
solverType=2
rm -r ../test/otheropt/1800loggers/withhbrmix/
mkdir ../test/otheropt/1800loggers/withhbrmix
sbatch -J withhbrmix_1 optlhs.sh withhbrmix $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withhbrmix_2 optrhs.sh withhbrmix $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

#* without hbr
SATparam=offSAT
MIPparam=optmipMix
solverType=1
rm -r ../test/otheropt/1800loggers/withouthbrmix/
mkdir ../test/otheropt/1800loggers/withouthbrmix
sbatch -J withouthbrmix_1 optlhs.sh withouthbrmix $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J withouthbrmix_2 optrhs.sh withouthbrmix $SATparam $MIPparam $onlyPreSolve $solverType $timelimit



