#!/bin/bash

if [ -f \lSystemGenerator.o ]
then
	echo "Deleting existing object file 'lSystemGenerator.o'..."
	rm lSystemGenerator.o
fi

if [ -f lsystem ]
then
	echo "Deleting existing executable file 'getJSONfromFile'..."
	rm lsystem
fi

g++ -std=c++11 -c lSystemGenerator.cpp && \
g++ -std=c++11 -o lsystem lSystemGenerator.o && \
echo "Excuting lsystem program:"
echo "" # Empty line.
./lsystem "$1" 
