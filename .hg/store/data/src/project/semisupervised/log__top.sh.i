         Z   Y      |��������A�Ti5sݏ�@,�N ��7            u#!/bin/bash

while [ 1 ]
do
    top -n1 > log_top_`date +'%F_%T'`.txt;
    sleep $1
done
