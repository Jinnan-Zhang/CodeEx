#!/bin/bash

HOST=202.38.129.227
DB_NAME=junopmttest
USERNAME=pmtRo
USERPASS=JUNO@PanAsia2017
NANCOUNTER=0

:<<!
for line in `cat pmt_list.txt`
do
     #echo $line
     CMD="select NO, SN, SK, SP, IDB, SKB, Ebb, DC, Tr, Tf, PP, AP, QE, DE from junopmttest.hamamatsudbt where SN = '$line'"
     mysql -u $USERNAME -h $HOST -p$USERPASS $DB_NAME -N -B -e "$CMD"
     CMD="select NO, CD, SN, NQE, HV, G, PvsV, R, DE, DR, TTS, PP, AP, NL, RT, FT, VS from junopmttest.nnvtdbt where SN = '$line'"
     mysql -u $USERNAME -h $HOST -p$USERPASS $DB_NAME -N -B -e "$CMD"
done
!


echo "SN Ebb DC DE QE"
for line in `cat pmt_list.txt`
do
     #echo $line
     if [[ $line =~ "NAN" ]]; then
        NANCOUNTER=$((NANCOUNTER + 1))
        echo "NAN$NANCOUNTER	NAN	NAN	NAN"
    fi
     CMD="select SN, Ebb, DC, DE, QE from junopmttest.hamamatsudbt where SN = '$line'"
     mysql -u $USERNAME -h $HOST -p$USERPASS $DB_NAME -N -B -e "$CMD"
     CMD="select SN, HV, DR, DE from junopmttest.nnvtdbt where SN = '$line'"
     mysql -u $USERNAME -h $HOST -p$USERPASS $DB_NAME -N -B -e "$CMD"
done


