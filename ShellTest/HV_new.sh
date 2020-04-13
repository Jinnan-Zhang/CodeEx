#!/bin/bash
HOST=202.38.129.227
DB_NAME=junopmttest
USERNAME=pmtRo
USERPASS=JUNO@PanAsia2017
string="Pass"
string1="Go SS"
echo "PMT_ID HV"
Drawer=201
NANs=1
while read row1 row2;
do
    pmtid=$row1;
    purpose=$row2;
    # echo $purpose;

    if [ "$purpose" == "1000" ]||[ "$purpose" == "1001" ];
    then 
        CMD="select PMT_ID, HV from junopmttest.container_test where PMT_ID = '$pmtid' and Indication in ('$string','$string1') order by Date desc limit 0,1"
        mysql -u $USERNAME -h $HOST -p$USERPASS $DB_NAME -N -B -e "$CMD"
        # echo $Drawer 
        Drawer=`expr $Drawer + 1`
    elif [ "$purpose" == "2" ];
    then
        echo NAN$NANs $Drawer 0 2
        NANs=`expr $NANs + 1`
        Drawer=`expr $Drawer + 1`
    elif [ "$purpose" == "0" ]
    then
        CMD="select SN, Ebb from junopmttest.hamamatsudbt where SN = '$pmtid'"
        mysql -u $USERNAME -h $HOST -p$USERPASS $DB_NAME -N -B -e "$CMD"
        Drawer=`expr $Drawer + 1`
    else
        CMD="select SN, HV from junopmttest.nnvtdbt where SN = '$pmtid'"
        mysql -u $USERNAME -h $HOST -p$USERPASS $DB_NAME -N -B -e "$CMD"
        Drawer=`expr $Drawer + 1`
    fi
done < pmt_list.txt
