#!/bin/bash

export name=roundingSat
export SATparam=SAToff
export MIPparam=MIPoff
export onlyPreSolve=0
export solverType=3
export timelimit=5000

rm -r ../test/otheropt/loggers/$name/
mkdir ../test/otheropt/loggers/$name

sbatch lhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch rhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit