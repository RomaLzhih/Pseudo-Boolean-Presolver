#!/bin/bash

# names=(roundingSat onlyCoeffStrengthen onlyColSingleton onlyDoubletoneq onlyDualFix onlyhbr onlyParallelRow onlyProbing onlyPropagation onlyPureLit onlySimpleProbing onlySimplifyIneq onlySparsify onlyStuffing offMIP all)
names=(withouthbrmix withhbrmix withouthbrmix2 withhbrmix2)

# # dec
# rcp -r ziyang@aurora.lunarc.lu.se:/home/ziyang/pre/test/otherdec/1800loggers/{withhbrmix,withouthbrmix,withhbrmix2,withouthbrmix2} /home/mzy/thesis_project/pre/test/otherdec/1800loggers/

# #opt
# rcp -r ziyang@aurora.lunarc.lu.se:/home/ziyang/pre/test/otheropt/1800loggers/{withhbrmix,withouthbrmix,withhbrmix2,withouthbrmix2} /home/mzy/thesis_project/pre/test/otheropt/1800loggers/

echo finish fetch

for name in "${names[@]}"
do
    ls -l ../test/otherdec/1800loggers/$name | wc -l   
    python3 ../test/merge.py $name 0
    python3 ../test/merge.py $name 1
    echo finish merge $name 
    cp ../test/otherdec/1800loggers/analysis/$name.csv /mnt/d/aMain/4-pre/datacollection/
    cp ../test/otherdec/1800loggers/analysis/$name.csv /mnt/d/aMain/4-pre/dataplot/dec/
    cp ../test/otherdec/1800loggers/analysis/$name-param.csv /mnt/d/aMain/4-pre/dataplot/dec/
    echo finish paste $name
done

for name in "${names[@]}"
do
    ls -l ../test/otheropt/1800loggers/$name | wc -l   
    python3 ../test/mergeopt.py $name 0
    python3 ../test/mergeopt.py $name 1
    echo finish mergeopt $name 
    cp ../test/otheropt/1800loggers/analysis/$name.csv /mnt/d/aMain/4-pre/datacollection-opt-1800/
    cp ../test/otheropt/1800loggers/analysis/$name.csv /mnt/d/aMain/4-pre/dataplot/opt/
    cp ../test/otheropt/1800loggers/analysis/$name-param.csv /mnt/d/aMain/4-pre/dataplot/opt/
    echo finish paste $name
done

