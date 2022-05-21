#!/bin/bash

#export name=roundingSat
export SATparam=offSAT
export MIPparam=offMIP
export onlyPreSolve=0
export solverType=3
export timelimit=500

names=(onlyCoeffStrengthen onlyColSingleton onlyDoubletoneq onlyDualFix onlyParallelRow onlyProbing onlyPropagation onlyPureLit onlySimpleProbing onlySimplifyIneq onlySparsify onlyStuffing offMIP)

module restore pre

#roundingSat
SATparam=offSAT
MIPparam=offMIP
solverType=3
rm -r ../test/otheropt/loggers/roundingSat/
mkdir ../test/otheropt/loggers/roundingSat
sbatch -J roundingSat_1 optlhs.sh roundingSat $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J roundingSat_2 optrhs.sh roundingSat $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

for name in "${names[@]}"
do
    rm -r ../test/otheropt/loggers/$name/
    mkdir ../test/otheropt/loggers/$name
    SATparam=offSAT
    MIPparam=$name
    solverType=1
    sbatch -J ${name}_1 optlhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
    sbatch -J ${name}_2 optrhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
done

#hbr
SATparam=onlyhbr
MIPparam=offMIP
solverType=0
rm -r ../test/otheropt/loggers/onlyhbr/
mkdir ../test/otheropt/loggers/onlyhbr
sbatch -J onlyhbr_1 optlhs.sh onlyhbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J onlyhbr_2 optrhs.sh onlyhbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

#all
SATparam=defaultSAT
MIPparam=defaultMIP
solverType=2
rm -r ../test/otheropt/loggers/all/
mkdir ../test/otheropt/loggers/all
sbatch -J all_1 optlhs.sh all $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J all_2 optrhs.sh all $SATparam $MIPparam $onlyPreSolve $solverType $timelimit



