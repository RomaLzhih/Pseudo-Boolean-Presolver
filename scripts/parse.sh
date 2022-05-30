#!/bin/bash
export name=$1


rcp -r ziyang@aurora.lunarc.lu.se:/home/ziyang/pre/test/otherdec/1800loggers/$name /home/mzy/thesis_project/pre/test/otherdec/1800loggers/
echo finish fetch
ls -l ../test/otherdec/1800loggers/$name | wc -l

python3 ../test/merge.py $name 1
echo finish merge 
cp ../test/otherdec/1800loggers/analysis/$name.csv /mnt/d/aMain/4-pre/datacollection/
echo finish paste
