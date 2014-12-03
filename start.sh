#!/bin/bash
#
# ChinaOpen 2008 sample start script for 3D Simulation Competitions
#

AGENT_BINARY=AmoiensisNQ

killall -9 $AGENT_BINARY

./$AGENT_BINARY -h $1 -n 1 > log/stdout 2> log/stderr &

sleep 2

./$AGENT_BINARY -h $1 -n 2 > log/stdout 2> log/stderr &

sleep 2 

./$AGENT_BINARY -h $1 -n 3 > log/stdout 2> log/stderr &  

sleep 2 

./$AGENT_BINARY -h $1 -n 4 > log/stdout 2> log/stderr &    

sleep 2

./$AGENT_BINARY -h $1 -n 5 > log/stdout 2> log/stderr &     

sleep 2 

./$AGENT_BINARY -h $1 -n 6 > log/stdout 2> log/stderr &      

sleep 2 

./$AGENT_BINARY -h $1 -n 7 > log/stdout 2> log/stderr &     

sleep 2 

./$AGENT_BINARY -h $1 -n 8 > log/stdout 2> log/stderr &     

sleep 2 

./$AGENT_BINARY -h $1 -n 9 > log/stdout 2> log/stderr &
