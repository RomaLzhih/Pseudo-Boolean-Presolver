#!/bin/bash

#export name=roundingSat
export SATparam=offSAT
export MIPparam=offMIP
export onlyPreSolve=0
export solverType=3
export timelimit=1800

names=(onlyCoeffStrengthen onlyColSingleton onlyDoubletoneq onlyDualFix onlyParallelRow onlyProbing onlyPropagation onlyPureLit onlySimpleProbing onlySimplifyIneq onlySparsify onlyStuffing offMIP)

module restore pre

#roundingSat
SATparam=offSAT
MIPparam=offMIP
solverType=3
rm -r ../test/otherdec/1800loggers/roundingSat/
mkdir ../test/otherdec/1800loggers/roundingSat
sbatch -J roundingSat_1 declhs.sh roundingSat $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J roundingSat_2 decmid.sh roundingSat $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J roundingSat_2 decrhs.sh roundingSat $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

for name in "${names[@]}"
do
    rm -r ../test/otherdec/1800loggers/$name/
    mkdir ../test/otherdec/1800loggers/$name
    SATparam=offSAT
    MIPparam=$name
    solverType=1
    sbatch -J ${name}_1 declhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
    sbatch -J ${name}_1 decmid.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
    sbatch -J ${name}_2 decrhs.sh $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
done

#hbr
SATparam=onlyhbr
MIPparam=offMIP
solverType=0
rm -r ../test/otherdec/1800loggers/onlyhbr/
mkdir ../test/otherdec/1800loggers/onlyhbr
sbatch -J onlyhbr_1 declhs.sh onlyhbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J onlyhbr_1 decmid.sh onlyhbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J onlyhbr_2 decrhs.sh onlyhbr $SATparam $MIPparam $onlyPreSolve $solverType $timelimit

#all
SATparam=defaultSAT
MIPparam=defaultMIP
solverType=2
rm -r ../test/otherdec/1800loggers/all/
mkdir ../test/otherdec/1800loggers/all
sbatch -J all_1 declhs.sh all $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J all_1 decmid.sh all $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
sbatch -J all_2 decrhs.sh all $SATparam $MIPparam $onlyPreSolve $solverType $timelimit



