#!/bin/bash

names=(roundingSat onlyCoeffStrengthen onlyColSingleton onlyDoubletoneq onlyDualFix onlyhbr onlyParallelRow onlyProbing onlyPropagation onlyPureLit onlySimpleProbing onlySimplifyIneq onlySparsify onlyStuffing offMIP all)

#rcp -r ziyang@aurora.lunarc.lu.se:/home/ziyang/pre/test/otherdec/loggers /home/mzy/thesis_project/pre/#test/otherdec/
#echo finish fetch
for name in "${names[@]}"
do
    ls -l ../test/otherdec/loggers/$name | wc -l   
    python3 ../test/merge.py $name    
    echo finish merge $name
    cp ../test/otherdec/loggers/analysis/$name.csv /mnt/d/aMain/4-pre/datacollection/
    echo finish paste $name
done

