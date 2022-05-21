#!/bin/bash
export name=$1


rcp -r ziyang@aurora.lunarc.lu.se:/home/ziyang/pre/test/otherdec/loggers/$name /home/mzy/thesis_project/pre/test/otherdec/loggers/
echo finish fetch
ls -l ../test/otherdec/loggers/$name | wc -l

python3 ../test/merge.py $name 
echo finish merge
cp ../test/otherdec/loggers/analysis/$name.csv /mnt/d/aMain/4-pre/datacollection/
echo finish paste
