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

        sprintf(command, "mkdir %s/e-/%fMeV", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/e-/%fMeV/build", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/e-/%fMeV/src", ProjectDir, energy);
        system(command);
        ///////////////////////////////////////////////////////////////////////////

        sprintf(command, "mkdir %s/mu-/%fMeV", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/mu-/%fMeV/build", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/mu-/%fMeV/src", ProjectDir, energy);
        system(command);
        ///////////////////////////////////////////////////////////////////////////
        sprintf(command, "mkdir %s/proton/%fMeV", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/proton/%fMeV/build", ProjectDir, energy);
        system(command);

        sprintf(command, "mkdir %s/proton/%fMeV/src", ProjectDir, energy);
        system(command);
        ///////////////////////////////////////////////////////////////////////////
        

        sprintf(command, "cp %s/CMakeLists.txt %s/e-/%fMeV/CMakeLists.txt", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/simulation.cc %s/e-/%fMeV/simulation.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/vis.mac %s/e-/%fMeV/vis.mac", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.cc %s/e-/%fMeV/src/DetectorConstruction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.hh %s/e-/%fMeV/src/DetectorConstruction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.cc %s/e-/%fMeV/src/Hit.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.hh %s/e-/%fMeV/src/Hit.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/PrimaryGeneratorAction.hh %s/e-/%fMeV/src/PrimaryGeneratorAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/RunAction.hh %s/e-/%fMeV/src/RunAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.cc %s/e-/%fMeV/src/SensitiveDetector.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.hh %s/e-/%fMeV/src/SensitiveDetector.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.cc %s/e-/%fMeV/src/SteppingAction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.hh %s/e-/%fMeV/src/SteppingAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/build/run %s/e-/%fMeV/build/run", SampleDir, ProjectDir, energy);
        system(command);

        /////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////
    
        sprintf(command, "cp %s/CMakeLists.txt %s/mu-/%fMeV/CMakeLists.txt", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/simulation.cc %s/mu-/%fMeV/simulation.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/vis.mac %s/mu-/%fMeV/vis.mac", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.cc %s/mu-/%fMeV/src/DetectorConstruction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.hh %s/mu-/%fMeV/src/DetectorConstruction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.cc %s/mu-/%fMeV/src/Hit.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.hh %s/mu-/%fMeV/src/Hit.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/PrimaryGeneratorAction.hh %s/mu-/%fMeV/src/PrimaryGeneratorAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/RunAction.hh %s/mu-/%fMeV/src/RunAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.cc %s/mu-/%fMeV/src/SensitiveDetector.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.hh %s/mu-/%fMeV/src/SensitiveDetector.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.cc %s/mu-/%fMeV/src/SteppingAction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.hh %s/mu-/%fMeV/src/SteppingAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/build/run %s/mu-/%fMeV/build/run", SampleDir, ProjectDir, energy);
        system(command);

        /////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////

        sprintf(command, "cp %s/CMakeLists.txt %s/proton/%fMeV/CMakeLists.txt", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/simulation.cc %s/proton/%fMeV/simulation.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/vis.mac %s/proton/%fMeV/vis.mac", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.cc %s/proton/%fMeV/src/DetectorConstruction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/DetectorConstruction.hh %s/proton/%fMeV/src/DetectorConstruction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.cc %s/proton/%fMeV/src/Hit.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/Hit.hh %s/proton/%fMeV/src/Hit.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/PrimaryGeneratorAction.hh %s/proton/%fMeV/src/PrimaryGeneratorAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/RunAction.hh %s/proton/%fMeV/src/RunAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.cc %s/proton/%fMeV/src/SensitiveDetector.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SensitiveDetector.hh %s/proton/%fMeV/src/SensitiveDetector.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.cc %s/proton/%fMeV/src/SteppingAction.cc", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/src/SteppingAction.hh %s/proton/%fMeV/src/SteppingAction.hh", SampleDir, ProjectDir, energy);
        system(command);

        sprintf(command, "cp %s/build/run %s/proton/%fMeV/build/run", SampleDir, ProjectDir, energy);
        system(command);
    
    }

}