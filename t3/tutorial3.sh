#!/bin/bash

#$ -S /bin/bash
#$ -cwd
#$ -pe mpich 2
#$ -N tutorial3
#$ -j y
#$ -o $JOB_NAME.o$JOB_ID
#$ -q all.q

MPICH_MACHINES=$TMPDIR/mpich_machines
cat $PE_HOSTFILE | awk '{print $1":"$2}' > $MPICH_MACHINES

mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial3_bloqueante
mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial3_bloqueanteBuffer
mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial3_bloqueanteSincrona
mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial3_nobloqueante
mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial3_nobloqueanteBuffer
mpiexec -f $MPICH_MACHINES -n $NSLOTS ./tutorial3_nobloqueanteSincrona

rm -rf $MPICH_MACHINES