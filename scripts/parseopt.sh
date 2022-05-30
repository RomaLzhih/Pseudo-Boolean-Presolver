#!/bin/bash
export name=$1

rcp -r ziyang@aurora.lunarc.lu.se:/home/ziyang/pre/test/otheropt/1800loggers/$name /home/mzy/thesis_project/pre/test/otheropt/1800loggers/
echo finish fetch opt
ls -l ../test/otheropt/1800loggers/$name | wc -l

python3 ../test/mergeopt.py $name 1
echo finish merge opt
cp ../test/otheropt/1800loggers/analysis/$name.csv /mnt/d/aMain/4-pre/datacollection-opt-1800/
echo finish paste opt
