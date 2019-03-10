#!/bin/sh

echo "Server and $1 client processes initiated..."

if [ $1 -eq 1 ]
then
mkdir -p ./logs/1

xterm -title "Server" -e ./tcpserver & 
xterm -title "Client 1" -e "./tcpclient $2 > ./logs/1/client_1.txt" & 


elif [ $1 -eq 2 ]
then

mkdir -p ./logs/2

xterm -title "Server" -e ./tcpserver & 
xterm -title "Client 1" -e "./tcpclient $2 > ./logs/2/client_1.txt" & 
xterm -title "Client 2" -e "./tcpclient $2 > ./logs/2/client_2.txt" & 


elif [ $1 -eq 3 ]
then

mkdir -p ./logs/3

xterm -title "Server" -e ./tcpserver & 
xterm -title "Client 1" -e "./tcpclient $2 > ./logs/3/client_1.txt" &
xterm -title "Client 2" -e "./tcpclient $2 > ./logs/3/client_2.txt" &
xterm -title "Client 3" -e "./tcpclient $2 > ./logs/3/client_3.txt" &


elif [ $1 -eq 4 ]
then

mkdir -p ./logs/4

xterm -title "Server" -e ./tcpserver & 
xterm -title "Client 1" -e "./tcpclient $2 > ./logs/4/client_1.txt" &
xterm -title "Client 2" -e "./tcpclient $2 > ./logs/4/client_2.txt" &
xterm -title "Client 3" -e "./tcpclient $2 > ./logs/4/client_3.txt" &
xterm -title "Client 4" -e "./tcpclient $2 > ./logs/4/client_4.txt" &


elif [ $1 -eq 5 ]
then

mkdir -p ./logs/5

xterm -title "Server" -e ./tcpserver & 
xterm -title "Client 1" -e "./tcpclient $2 > ./logs/5/client_1.txt" &
xterm -title "Client 2" -e "./tcpclient $2 > ./logs/5/client_2.txt" &
xterm -title "Client 3" -e "./tcpclient $2 > ./logs/5/client_3.txt" &
xterm -title "Client 4" -e "./tcpclient $2 > ./logs/5/client_4.txt" &
xterm -title "Client 5" -e "./tcpclient $2 > ./logs/5/client_5.txt" &


else 
echo "Invalid argument: Argument should be between 1 and 5 (inclusive)"

fi

