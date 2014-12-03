#!/bin/bash

TeamName='TestTeam1'

HOST='192.168.0.66'

DelayTime=0.0015

if [ $1 ];
then
	DelayTime = $1;
fi

./AmoiensisNQ -t $TeamName -n 1 -h $HOST -d $DelayTime &

sleep 1

./AmoiensisNQ -t $TeamName -n 2 -h $HOST -d $DelayTime &

sleep 1 

./AmoiensisNQ -t $TeamName -n 3 -h $HOST -d $DelayTime &

sleep 1 

./AmoiensisNQ -t $TeamName -n 4 -h $HOST -d $DelayTime &

sleep 1 '

./AmoiensisNQ -t $TeamName -n 5 -h $HOST -d $DelayTime &

sleep 1 

./AmoiensisNQ -t $TeamName -n 6 -h $HOST -d $DelayTime &

sleep 1 

./AmoiensisNQ -t $TeamName -n 7 -h $HOST -d $DelayTime &

sleep 1 

./AmoiensisNQ -t $TeamName -n 8 -h $HOST -d $DelayTime &

sleep 1 

./AmoiensisNQ -t $TeamName -n 9 -h $HOST -d $DelayTime &'
