#!/bin/bash
export OMP_PLACES="{0,1}"
export OMP_NUM_THREADS=2
# /usr/bin/time ./main.bin 1000
N=16
for i in `seq 10`; do
    echo $N
    ./main.bin $N >> result.log
    N=$(($N*2))
done
