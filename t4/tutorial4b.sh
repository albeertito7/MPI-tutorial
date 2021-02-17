#!/bin/bash

#$ -S /bin/bash
#$ -cwd
#$ -pe mpich 6
#$ -N tutorial4b
#$ -j y
#$ -o $JOB_NAME.o$JOB_ID
#$ -q all.q

MPICH_MACHINES=$TMPDIR/mpich_machines
cat $PE_HOSTFILE | awk '{print $1":"$2}' > $MPICH_MACHINES

mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial4b

rm -rf $MPICH_MACHINES