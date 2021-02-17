#!/bin/bash

#$ -S /bin/bash
#$ -cwd
#$ -pe mpich 8
#$ -N tutorial1_machines
#$ -j y
#$ -o $JOB_NAME.o$JOB_ID
#$ -q all.q

MPICH_MACHINES=$TMPDIR/mpich_machines
cat $PE_HOSTFILE | awk '{print $1":"$2}' > $MPICH_MACHINES


## In this line you have to write the command that will execute your application.
mpiexec -f ./hostsfile -n $NSLOTS ./tutorial1


rm -rf $MPICH_MACHINES