#!/bin/bash
int=0
while [ $int -le 5 ]
    do
    job=`printf "%d\n" $int`
    echo dealing.... job:$job
    sed "s/NUM/$job/g"  $1.sh > $1$job.sh
    chmod 755 $1$job.sh
    # hep_sub -u juno $1$job.sh
    int=`expr $int + 1`
done

#end