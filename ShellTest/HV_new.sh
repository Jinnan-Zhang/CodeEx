#!/bin/bash
HOST=202.38.129.227
DB_NAME=junopmttest
USERNAME=pmtRo
USERPASS=JUNO@PanAsia2017
string="Pass"
string1="Go SS"
NANs=1
channel=0
chArr=()
while read row1 row2;
do
    pmtid=$row1;
    purpose=$row2;
    # echo $purpose;

    if [ "$purpose" == "1000" ]||[ "$purpose" == "1001" ];
    then 
        CMD="select PMT_ID, HV from junopmttest.container_test where PMT_ID = '$pmtid' and Indication in ('$string','$string1') order by Date desc limit 0,1"
        mysql -u $USERNAME -h $HOST -p$USERPASS $DB_NAME -N -B -e "$CMD" >> new.txt
    elif [ "$purpose" == "2" ];
    then
        echo $pmtid$NANs 0 >> new.txt
        NANs=`expr $NANs + 1`
    elif [ "$purpose" == "0" ]
    then
        CMD="select SN, Ebb from junopmttest.hamamatsudbt where SN = '$pmtid'"
        mysql -u $USERNAME -h $HOST -p$USERPASS $DB_NAME -N -B -e "$CMD" >> new.txt
    else
        CMD="select SN, HV from junopmttest.nnvtdbt where SN = '$pmtid'"
        mysql -u $USERNAME -h $HOST -p$USERPASS $DB_NAME -N -B -e "$CMD" >> new.txt
    fi
    chArr[channel]=$purpose
    channel=`expr $channel + 1`
done < pmt_list.txt
read -p "Please input container A or B:" Container
if [ "$Container" == "A" ]
then
    Drawer=101
else
    Drawer=201
fi
echo "PMT_ID Drawer HV types"
channel=0
while read row1 row2;
do
    pmtid=$row1;
    HV=$row2;
    echo -e "$pmtid\t$Drawer\t${HV%.*}\t${chArr[channel]}"
    Drawer=`expr $Drawer + 1`
    channel=`expr $channel + 1`
done < new.txt
rm new.txt