#!/bin/bash
#SBATCH -t 24:00:00
#SBATCH -J pre
#SBATCH --mem-per-cpu=4096
#SBATCH -o calcflow_m1_%j.out
#SBATCH -e calcflow_m1_%j.err
#SBATCH --mail-user=ziyang.men@di.ku.dk
#SBATCH --mail-type=ALL

#SBATCH -N 50
#SBATCH --tasks-per-node=10
#SBATCH -n 20

cat $0

module load GCC
module load GLIB
module load GLIBC


python3 onCluster.py rs 0 3