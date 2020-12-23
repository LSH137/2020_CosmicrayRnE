//
// Created by lsh on 20. 4. 3..
//

#include <cstdlib>
#include <cstdio>
#include <thread>
#include "BuildG4Proj.h"
#include "Constant.h"

void Build(int number_of_proj)
{

    char command[250] = {0};
    double energy;
    for(int i = 1; i <= number_of_proj; i++)
    {
        energy = (double)i / divide;
        sprintf(command, "cd %s/proton/%fMeV/build && cmake ../ -DCMAKE_PREFIX_PATH=%s && make -j12 &",ProjectDir, energy, Geant4ConfigDir);
        system(command);

        sprintf(command, "cd %s/e-/%fMeV/build && cmake ../ -DCMAKE_PREFIX_PATH=%s && make -j12 &",ProjectDir, energy, Geant4ConfigDir);
        system(command);

        sprintf(command, "cd %s/mu-/%fMeV/build && cmake ../ -DCMAKE_PREFIX_PATH=%s && make -j12",ProjectDir, energy, Geant4ConfigDir);
        system(command);

        //system("sleep 0.25");
    }
}
