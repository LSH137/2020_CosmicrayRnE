#!/bin/bash

k=10

echo "simulate electron"
for i in {0..20}
do
    for j in {0..9}
    do
        cd /home/lsh/G4Project/e-/${i}.${j}00000MeV/build
        ./run &
        sleep 0.3
    done
done
wait

echo "simulate muon"
for i in {0..20}
do
    for j in {0..9}
    do
        cd /home/lsh/G4Project/mu-/${i}.${j}00000MeV/build
        ./run &
        sleep 0.3
    done
done
wait

echo "simulate proton"
for i in {0..20}
do
    for j in {0..9}
    do
        cd /home/lsh/G4Project/proton/${i}.${j}00000MeV/build
        ./run &
        sleep 0.3
    done
done
wait


