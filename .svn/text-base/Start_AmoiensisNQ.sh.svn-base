#!/bin/bash
HOST='192.168.0.66'

DelayTime=0.0015

if [ $1 ];
then
	DelayTime = $1;
fi

./AmoiensisNQ -n 1 -h $HOST -d $DelayTime &

sleep 1

./AmoiensisNQ -n 2 -h $HOST -d $DelayTime &

sleep 1 

./AmoiensisNQ -n 3 -h $HOST -d $DelayTime &

sleep 1

./AmoiensisNQ -n 4 -h $HOST -d $DelayTime &
