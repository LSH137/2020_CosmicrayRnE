#!/bin/bash


echo "simulate electron"
for i in {1..500}
do
    cd /home/cosmicray/G4Project/e-/${i}.000000GeV/build
    ./run &
    sleep 0.3
done
wait

echo "simulate muon"
for i in {1..500}
do
    cd /home/cosmicray/G4Project/mu-/${i}.000000GeV/build
    ./run &
    sleep 0.3
done
wait

echo "simulate proton"
for i in {1..500}
do
    cd /home/cosmicray/G4Project/proton/${i}.000000GeV/build
    ./run &
    sleep 0.3
done
wait


