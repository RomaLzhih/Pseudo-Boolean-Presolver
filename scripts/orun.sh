#!/bin/bash

export name=roundingSat
export SATparam=offSAT
export MIPparam=offMIP
export onlyPreSolve=0
export solverType=3
export timelimit=500

module restore pre
rm -r ../test/otheropt/loggers/$name/
mkdir ../test/otheropt/loggers/$name

sbatch -J ${name}_1 optlhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J ${name}_2 optrhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit