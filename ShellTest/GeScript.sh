#!/bin/bash
int=0
while [ $int -le 5 ]
    do
    job=`printf "%d\n" $int`
    echo dealing.... job:$job
    sed "s/NUM/$job/g"  Pre2D.sh > Pre2D$job.sh
    chmod 755 Pre2D$job.sh
    # hep_sub -u juno Pre2D$job.sh
    int=`expr $int + 1`
done

#end