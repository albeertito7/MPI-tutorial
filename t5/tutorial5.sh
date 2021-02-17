#!/bin/bash

#$ -S /bin/bash
#$ -cwd
#$ -pe mpich 2
#$ -N tutorial5
#$ -j y
#$ -o $JOB_NAME.o$JOB_ID
#$ -q all.q

MPICH_MACHINES=$TMPDIR/mpich_machines
cat $PE_HOSTFILE | awk '{print $1":"$2}' > $MPICH_MACHINES

mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial5

rm -rf $MPICH_MACHINES