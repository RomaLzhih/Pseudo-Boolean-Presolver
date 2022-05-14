#!/bin/bash

export name=roundingSat
export SATparam=SAToff
export MIPparam=MIPoff
export onlyPreSolve=0
export solverType=3
export timelimit=5000

sbatch lhs $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch rhs $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit