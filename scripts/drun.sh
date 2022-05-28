#!/bin/bash

export name=onlyredundancy
export SATparam=onlyredundacy
export MIPparam=offMIP
export onlyPreSolve=1
export solverType=0
export timelimit=1800

module restore pre

rm -r ../test/otherdec/1800loggers/$name/
mkdir ../test/otherdec/1800loggers/$name

sbatch -J ${name}_1 declhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J ${name}_2 decmid.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J ${name}_3 decrhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit