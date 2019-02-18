#!/bin/sh

echo "Server and $1 client processes initiated..."

if [ $1 -eq 1 ]
then

mkdir -p ./logs/1

xterm -e ./server & 
xterm -e ./client_1 & ./client_1 > ./logs/1/client_1.txt &


elif [ $1 -eq 2 ]
then

mkdir -p ./logs/2

xterm -e ./server & 
xterm -e ./client_1 & ./client_1 > ./logs/2/client_1.txt &
xterm -e ./client_2 & ./client_2 > ./logs/2/client_2.txt &

elif [ $1 -eq 3 ]
then

mkdir -p ./logs/3

xterm -e ./server & 
xterm -e ./client_1 & ./client_1 > ./logs/3/client_1.txt &
xterm -e ./client_2 & ./client_2 > ./logs/3/client_2.txt &
xterm -e ./client_3 & ./client_3 > ./logs/3/client_3.txt &

elif [ $1 -eq 4 ]
then

mkdir -p ./logs/4

xterm -e ./server & 
xterm -e ./client_1 & ./client_1 > ./logs/4/client_1.txt &
xterm -e ./client_2 & ./client_2 > ./logs/4/client_2.txt &
xterm -e ./client_3 & ./client_3 > ./logs/4/client_3.txt &
xterm -e ./client_4 & ./client_4 > ./logs/4/client_4.txt &

elif [ $1 -eq 5 ]
then

mkdir -p ./logs/5

xterm -e ./server & 
xterm -e ./client_1 & ./client_1 > ./logs/5/client_1.txt &
xterm -e ./client_2 & ./client_2 > ./logs/5/client_2.txt &
xterm -e ./client_3 & ./client_3 > ./logs/5/client_3.txt &
xterm -e ./client_4 & ./client_4 > ./logs/5/client_4.txt &
xterm -e ./client_5 & ./client_5 > ./logs/5/client_5.txt &

else 
echo "Invalid argument: Argument should be between 1 and 5 (inclusive)"

fi

