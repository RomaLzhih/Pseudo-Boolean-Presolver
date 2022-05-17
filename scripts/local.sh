#!/bin/bash
#SBATCH -t 12:00:00
#SBATCH -J pre
#SBATCH -A lu2022-2-31
#SBATCH --reservation=lu2022-2-31
#SBATCH -o calcflow_m1_%j.out
#SBATCH -e calcflow_m1_%j.err
#SBATCH --mail-user=mzy791191656@gmail.com
#SBATCH --mail-type=ALL

#SBATCH -N 50
#SBATCH --tasks-per-node=1
#SBATCH -c 6

export NB_of_jobs=100
export name=$1
export SATparam=$2
export MIPparam=$3
export onlyPreSolve=$4
export solverType=$5
export timelimit=$6

SATparam=../param/${SATparam}.txt
MIPparam=../param/${MIPparam}.txt

rm -r ../test/loggers/$name/
mkdir ../test/loggers/$name

for ((i=0; i<$NB_of_jobs; i++))
do
    python3 go.py $i $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit
done

cd ../test/loggers/$name
cat *.txt>$name.csv

