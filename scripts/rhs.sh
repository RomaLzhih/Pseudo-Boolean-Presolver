#!/bin/bash
#SBATCH -t 24:00:00
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

module load foss/2020a
module load CMake
module load Boost
module load GMP

cat $0
export NB_of_jobs=1055
export name=$1
export SATparam=$2
export MIPparam=$3
export onlyPreSolve=$4
export solverType=$5
export timelimit=$6

SATparam=../param/$SATparam
MIPparam=../param/$MIPparam

rm -r ../test/loggers/$name/
mkdir ../test/loggers/$name
rm -r ../scripts/workers/
mkdir ../scripts/workers

for ((i=527; i<$NB_of_jobs; i++))
do
    srun --exclusive -n 1 -N 1 -c 6 python3 go.py $i $name $SATparam $MIPparam $onlyPreSolve $solverType $timelimit &> ../scripts/workers/worker_${SLURM_JOB_ID}_${i} &
    sleep 1
done

wait

