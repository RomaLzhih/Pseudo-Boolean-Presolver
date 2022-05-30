#!/bin/bash

export name=onlyredundancy
export SATparam=onlyredundacy
export MIPparam=offMIP
export onlyPreSolve=1
export solverType=0
export timelimit=1800

module restore pre
rm -r ../test/otheropt/1800loggers/$name/
mkdir ../test/otheropt/1800loggers/$name

sbatch -J ${name}_1 optlhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J ${name}_2 optmid.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J ${name}_3 optrhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
