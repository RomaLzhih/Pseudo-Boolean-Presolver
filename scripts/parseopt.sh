#!/bin/bash
export name=$1

rcp -r ziyang@aurora.lunarc.lu.se:/home/ziyang/pre/test/otheropt/loggers/$name /home/mzy/thesis_project/pre/test/otheropt/loggers/
echo finish fetch opt
ls -l ../test/otheropt/loggers/$name | wc -l

python3 ../test/mergeopt.py $name 
echo finish merge opt
cp ../test/otheropt/loggers/analysis/$name.csv /mnt/d/aMain/4-pre/datacollection-opt/
echo finish paste opt
