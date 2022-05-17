#!/bin/bash
export name=$1

rcp -r ziyang@aurora.lunarc.lu.se:/home/ziyang/pre/test/loggers/$name /home/mzy/thesis_project/pre/test/loggers/
echo finish fetch
ls -l ../test/loggers/$name | wc -l

python3 ../test/merge.py $name 
echo finish merge
cp ../test/loggers/analysis/$name.csv /mnt/d/aMain/4-pre/datacollection/
echo finish paste
