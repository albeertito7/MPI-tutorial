#!/bin/bash

#$ -S /bin/bash
#$ -cwd
#$ -pe mpich 2
#$ -N tutorial2
#$ -j y
#$ -o $JOB_NAME.o$JOB_ID
#$ -q all.q

MPICH_MACHINES=$TMPDIR/mpich_machines
cat $PE_HOSTFILE | awk '{print $1":"$2}' > $MPICH_MACHINES

mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial2 2
mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial2 8
mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial2 32
mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial2 128
mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial2 1024
mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial2 8192

rm -rf $MPICH_MACHINES