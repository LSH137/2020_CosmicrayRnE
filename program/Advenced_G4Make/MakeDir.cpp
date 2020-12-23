//
// Created by lsh on 20. 4. 3..
//

#include "MakeDir.h"
#include <cstdlib>
#include <cstdio>

#include "Constant.h"


void MakeDir(int number_of_proj)
{
    char command[250] = {0};

    sprintf(command, "mkdir %s/e-", ProjectDir);
    system(command);

    sprintf(command, "mkdir %s/mu-", ProjectDir);
    system(command);

    sprintf(command, "mkdir %s/proton", ProjectDir);
    system(command);


    for(int i = 1; i <= number_of_proj; i++)
    {
        double energy = (double)i / divide;

        sprintf(command, "mkdir %s/e-/%fGeV", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/e-/%fGeV/build", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/e-/%fGeV/src", ProjectDir, energy);
        system(command);
        ///////////////////////////////////////////////////////////////////////////

        sprintf(command, "mkdir %s/mu-/%fGeV", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/mu-/%fGeV/build", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/mu-/%fGeV/src", ProjectDir, energy);
        system(command);
        ///////////////////////////////////////////////////////////////////////////
        sprintf(command, "mkdir %s/proton/%fGeV", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/proton/%fGeV/build", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/proton/%fGeV/src", ProjectDir, energy);
        system(command);
        ///////////////////////////////////////////////////////////////////////////
        

        sprintf(command, "cp %s/CMakeLists.txt %s/e-/%fGeV/CMakeLists.txt", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/simulation.cc %s/e-/%fGeV/simulation.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/vis.mac %s/e-/%fGeV/vis.mac", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.cc %s/e-/%fGeV/src/DetectorConstruction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.hh %s/e-/%fGeV/src/DetectorConstruction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.cc %s/e-/%fGeV/src/Hit.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.hh %s/e-/%fGeV/src/Hit.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/PrimaryGeneratorAction.hh %s/e-/%fGeV/src/PrimaryGeneratorAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/RunAction.hh %s/e-/%fGeV/src/RunAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.cc %s/e-/%fGeV/src/SensitiveDetector.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.hh %s/e-/%fGeV/src/SensitiveDetector.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.cc %s/e-/%fGeV/src/SteppingAction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.hh %s/e-/%fGeV/src/SteppingAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/build/run %s/e-/%fGeV/build/run", SampleDir, ProjectDir, energy);
        system(command);

        /////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////
    
        sprintf(command, "cp %s/CMakeLists.txt %s/mu-/%fGeV/CMakeLists.txt", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/simulation.cc %s/mu-/%fGeV/simulation.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/vis.mac %s/mu-/%fGeV/vis.mac", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.cc %s/mu-/%fGeV/src/DetectorConstruction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.hh %s/mu-/%fGeV/src/DetectorConstruction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.cc %s/mu-/%fGeV/src/Hit.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.hh %s/mu-/%fGeV/src/Hit.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/PrimaryGeneratorAction.hh %s/mu-/%fGeV/src/PrimaryGeneratorAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/RunAction.hh %s/mu-/%fGeV/src/RunAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.cc %s/mu-/%fGeV/src/SensitiveDetector.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.hh %s/mu-/%fGeV/src/SensitiveDetector.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.cc %s/mu-/%fGeV/src/SteppingAction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.hh %s/mu-/%fGeV/src/SteppingAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/build/run %s/mu-/%fGeV/build/run", SampleDir, ProjectDir, energy);
        system(command);

        /////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////

        sprintf(command, "cp %s/CMakeLists.txt %s/proton/%fGeV/CMakeLists.txt", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/simulation.cc %s/proton/%fGeV/simulation.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/vis.mac %s/proton/%fGeV/vis.mac", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.cc %s/proton/%fGeV/src/DetectorConstruction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.hh %s/proton/%fGeV/src/DetectorConstruction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.cc %s/proton/%fGeV/src/Hit.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.hh %s/proton/%fGeV/src/Hit.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/PrimaryGeneratorAction.hh %s/proton/%fGeV/src/PrimaryGeneratorAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/RunAction.hh %s/proton/%fGeV/src/RunAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.cc %s/proton/%fGeV/src/SensitiveDetector.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.hh %s/proton/%fGeV/src/SensitiveDetector.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.cc %s/proton/%fGeV/src/SteppingAction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.hh %s/proton/%fGeV/src/SteppingAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/build/run %s/proton/%fGeV/build/run", SampleDir, ProjectDir, energy);
        system(command);
    
    }

}