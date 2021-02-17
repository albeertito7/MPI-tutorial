#!/bin/bash

#$ -S /bin/bash
#$ -cwd
#$ -pe mpich 8
#$ -N tutorial1
#$ -j y
#$ -o $JOB_NAME.o$JOB_ID
#$ -q all.q

## In this line you have to write the command that will execute your application.
mpiexec -n $NSLOTS ./tutorial1


rm -rf $MPICH_MACHINES