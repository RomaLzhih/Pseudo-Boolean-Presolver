#!/bin/bash

export name=roundingSat
export SATparam=offSAT
export MIPparam=offMIP
export onlyPreSolve=0
export solverType=3
export timelimit=500

module restore pre

rm -r ../test/otherdec/loggers/$name/
mkdir ../test/otherdec/loggers/$name

sbatch -J ${name}_1 declhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J ${name}_2 decmid.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J ${name}_3 decrhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit