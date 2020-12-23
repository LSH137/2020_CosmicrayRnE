#!/bin/bash
echo "build RawDataProcess ver1"
ls
g++ -c Class.cpp -m64
g++ -c Constant.cpp -m64
g++ -c FileIO.cpp -m64

g++ -Wall -w -o2 -o dataprocess RawDataProcess.cpp Class.o Constant.o FileIO.o  -m64
echo "build end"
