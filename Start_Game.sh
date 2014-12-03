#!/bin/bash

killall -9 AmoiensisNQ

DelayTime=0.0015

if [ $1 ];
then
	DelayTime = $1;
fi



./Start_AmoiensisNQ.sh $DelayTime &

sleep 3 

./Start_Test.sh $DelayTime &


