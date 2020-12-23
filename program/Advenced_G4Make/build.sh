#!/bin/bash
echo "build RunGeant4 ver10"
ls
g++ -c  BuildG4Proj.cpp Constant.cpp MakeDir.cpp CreateFile.cpp
g++ -Wall -w -o2 -o RunGeant4 main.cpp BuildG4Proj.o Constant.o MakeDir.o CreateFile.o
echo "build end"
