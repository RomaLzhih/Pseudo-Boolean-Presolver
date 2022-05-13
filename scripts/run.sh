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
#SBATCH -c 7

module load foss/2020a
module load CMake
module load Boost
module load GMP

cat $0
export ID=0
export name=$1

rm -r ../test/loggers/$name/
mkdir ../test/loggers/$name
rm -r ../scripts/workers/
mkdir ../scripts/workers

while IFS= read -r line; do
    srun --exclusive -n 1 -N 1 -c 7 python3 runPre.py $line $name 0 3 5000 &> ../scripts/workers/worker_${SLURM_JOB_ID}_${ID} &
    ID=`expr $ID + 1`
    sleep 1
done < ../test/allfile.txt

wait

