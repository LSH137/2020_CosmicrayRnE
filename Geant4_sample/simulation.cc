#include <stdio.h>
#include "globals.hh"

#include "G4RunManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

#include "QBBC.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

int main(int argc, char** argv)
{
    G4RunManager* runManager = new G4RunManager;

    G4VModularPhysicsList* physicsList = new QBBC;
    runManager -> SetUserInitialization(physicsList);
    runManager -> SetUserInitialization(new DetectorConstruction());
    runManager -> SetUserAction(new PrimaryGeneratorAction());
    runManager -> SetUserAction(new RunAction());
    runManager -> SetUserAction(new SteppingAction());
    runManager -> Initialize();

    G4VisManager* visManager = new G4VisExecutive;
    visManager -> Initialize();

    

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if(argc != 1)
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager -> ApplyCommand(command + fileName);
    }
    else
    {
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        UImanager -> ApplyCommand("/control/execute vis.mac");
        UImanager -> ApplyCommand("/run/beamOn 10000");
        ui -> SessionStart();
        delete ui;
    }

    

    delete visManager;
/*
    //read a macro file of commands
    G4UImanager * ui = G4UImanager::GetUIpointer();

    //G4String fileName = argv[1];
    ui->ApplyCommand("/control/execute vis.mac");
    ui->ApplyCommand("/run/beamOn 100");

    //int number_of_event = 100;
    //runManager -> BeamOn(number_of_event);

    printf("simulation end\n");
*/
    delete runManager;

    return 0;
    
}