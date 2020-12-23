//
// Created by lsh on 20. 4. 3..
// Updated by lsh on 20. 12.17
// Updated by lsh on 20. 12.21
//

#include "CreateFile.h"
#include <fstream>
#include <iostream>
#include <cstring>

#include "Constant.h"

void MakeFile(int number_of_proj)
{
    char dir[250] = {0};
    char particle[10] = {0};
    double energy = 0;

    char temp_mu[5] = {"mu-"};
    strcpy(particle, temp_mu);
    for(int i = 1; i <= number_of_proj; i++)
    {
        energy = (double)i / divide;
        sprintf(dir, "%s/mu-/%fMeV/src/PrimaryGeneratorAction.cc",ProjectDir, energy);
        std::ofstream PrimaryGeneratorAction(dir);

        //PrimaryGeneratorAction.precision(3);
        PrimaryGeneratorAction<<"#include \"PrimaryGeneratorAction.hh\"\n"
                                "\n"
                                "#include \"G4LogicalVolumeStore.hh\"\n"
                                "#include \"G4LogicalVolume.hh\"\n"
                                "#include \"G4Box.hh\"\n"
                                "#include \"G4RunManager.hh\"\n"
                                "#include \"G4ParticleGun.hh\"\n"
                                "#include \"G4ParticleTable.hh\"\n"
                                "#include \"G4ParticleDefinition.hh\"\n"
                                "#include \"G4SystemOfUnits.hh\"\n"
                                "#include \"Randomize.hh\"\n"
                                "\n"
                                "G4double energy = "<<energy<<";\n"
                                                              "int ipja = 0;\n"
                                "\n"
                                "PrimaryGeneratorAction::PrimaryGeneratorAction()\n"
                                ": G4VUserPrimaryGeneratorAction()\n"
                                "{\n"
                                "    G4int n_particle = 1;\n"
                                "    fParticleGun = new G4ParticleGun(n_particle);\n"
                                "\n"
                                "    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();\n"
                                "    G4String particleName;\n"
                                "    particleName = \""<< particle<<"\";\n"
                                "    G4ParticleDefinition* particle = particleTable -> FindParticle(particleName);\n"
                                "\n"
                                "    fParticleGun -> SetParticleDefinition(particle);\n"
                                "    fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));\n"
                                "    fParticleGun -> SetParticleEnergy("<<energy<<"*MeV);\n"
                                "\n"
                                "}\n"
                                "\n"
                                "PrimaryGeneratorAction::~PrimaryGeneratorAction()\n"
                                "{\n"
                                "    delete fParticleGun;\n"
                                "}\n"
                                "\n"
                                "void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)\n"
                                "{\n"
                                "    // this function is called at the begining of each event\n"
                                "    fParticleGun -> GeneratePrimaryVertex(anEvent);\n"
                                "}" <<std::endl;

        PrimaryGeneratorAction.close();
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(dir, "%s/mu-/%fMeV/src/RunAction.cc",ProjectDir, energy);
        std::ofstream RunAction(dir);

        //RunAction.precision(3);
        RunAction<<"#include \"RunAction.hh\"\n"
                   "#include <time.h>\n"
                   "#include <stdio.h>\n"
                   "#include <stdlib.h>\n"
                   "\n"
                   "struct tm *date; \n"
                   "\n"
                   "\n"
                   "\n"
                   "RunAction::RunAction()\n"
                   ": G4UserRunAction()\n"
                   "{\n"
                   "\n"
                   "}\n"
                   "\n"
                   "RunAction::~RunAction()\n"
                   "{\n"
                   "    delete G4AnalysisManager::Instance();\n"
                   "}\n"
                   "\n"
                   "void RunAction::BeginOfRunAction(const G4Run*)\n"
                   "{\n"
                   "    char file_name[500];\n"
                   "    const time_t t = time(NULL); \n"
                   "    date = localtime(&t);\n"
                   "\n"
                   "    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();\n"
                   "\n"
                   "    srand((int)time(0));\n"
                   "\n"
                   "    sprintf(file_name, \"/media/lsh/CosmicrayRnE/SimulatedData/AdvencedG4Data/"<<(int)((energy)*1000)<<"KeV/%04dY%02dM%02dD%02dh%02dm%02ds_"<<particle<<(int)(energy*1000)<<"KeV%d.csv\", date->tm_year + 1900, date->tm_mon+1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec, rand());\n"
                   "\n"
                   "    analysisManager -> OpenFile(file_name);\n"
                   "\n"
                   "    analysisManager -> CreateNtuple(\"step\", \"step\");\n"
                   "    analysisManager -> CreateNtupleDColumn(\"MeV\");\n"
                   "    analysisManager -> CreateNtupleIColumn(\"particle\");\n"
                   "    analysisManager -> CreateNtupleDColumn(\"edep_ch2\");\n"
                   "    analysisManager -> CreateNtupleDColumn(\"edep_ch3\");\n"
                   "    analysisManager -> FinishNtuple();\n"
                   "}\n"
                   "\n"
                   "void RunAction::EndOfRunAction(const G4Run*)\n"
                   "{\n"
                   "    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();\n"
                   "    analysisManager -> Write();\n"
                   "    analysisManager -> CloseFile();\n"
                   "}"<<std::endl;

        RunAction.close();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //particle[0] = 'e';
    //particle[1] = '-';
    //particle[2] = '\0';
    char temp_p[10] = {"proton"};
    strcpy(particle, temp_p);
    for(int i = 1; i <= number_of_proj; i++)
    {
        energy = (double)i / divide;
        sprintf(dir, "%s/proton/%fMeV/src/PrimaryGeneratorAction.cc",ProjectDir, energy);
        std::ofstream PrimaryGeneratorAction(dir);

        PrimaryGeneratorAction<<"#include \"PrimaryGeneratorAction.hh\"\n"
                                "\n"
                                "#include \"G4LogicalVolumeStore.hh\"\n"
                                "#include \"G4LogicalVolume.hh\"\n"
                                "#include \"G4Box.hh\"\n"
                                "#include \"G4RunManager.hh\"\n"
                                "#include \"G4ParticleGun.hh\"\n"
                                "#include \"G4ParticleTable.hh\"\n"
                                "#include \"G4ParticleDefinition.hh\"\n"
                                "#include \"G4SystemOfUnits.hh\"\n"
                                "#include \"Randomize.hh\"\n"
                                "\n"
                                "G4double energy = "<<energy<<";\n"
                                                              "int ipja = 3;\n" //3: proton
                                "\n"
                                "PrimaryGeneratorAction::PrimaryGeneratorAction()\n"
                                ": G4VUserPrimaryGeneratorAction()\n"
                                "{\n"
                                "    G4int n_particle = 1;\n"
                                "    fParticleGun = new G4ParticleGun(n_particle);\n"
                                "\n"
                                "    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();\n"
                                "    G4String particleName;\n"
                                "    particleName = \""<< particle<<"\";\n"
                                                                    "    G4ParticleDefinition* particle = particleTable -> FindParticle(particleName);\n"
                                                                    "\n"
                                                                    "    fParticleGun -> SetParticleDefinition(particle);\n"
                                                                    "    fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));\n"
                                                                    "    fParticleGun -> SetParticleEnergy("<<energy<<"*MeV);\n"
                                                                                                                      "\n"
                                                                                                                      "}\n"
                                                                                                                      "\n"
                                                                                                                      "PrimaryGeneratorAction::~PrimaryGeneratorAction()\n"
                                                                                                                      "{\n"
                                                                                                                      "    delete fParticleGun;\n"
                                                                                                                      "}\n"
                                                                                                                      "\n"
                                                                                                                      "void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)\n"
                                                                                                                      "{\n"
                                                                                                                      "    // this function is called at the begining of each event\n"
                                                                                                                      "    fParticleGun -> GeneratePrimaryVertex(anEvent);\n"
                                                                                                                      "}" <<std::endl;

        PrimaryGeneratorAction.close();
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(dir, "%s/proton/%fMeV/src/RunAction.cc",ProjectDir, energy);
        std::ofstream RunAction(dir);

        RunAction<<"#include \"RunAction.hh\"\n"
                   "#include <time.h>\n"
                   "#include <stdio.h>\n"
                   "#include <stdlib.h>\n"
                   "\n"
                   "struct tm *date; \n"
                   "\n"
                   "\n"
                   "\n"
                   "RunAction::RunAction()\n"
                   ": G4UserRunAction()\n"
                   "{\n"
                   "\n"
                   "}\n"
                   "\n"
                   "RunAction::~RunAction()\n"
                   "{\n"
                   "    delete G4AnalysisManager::Instance();\n"
                   "}\n"
                   "\n"
                   "void RunAction::BeginOfRunAction(const G4Run*)\n"
                   "{\n"
                   "    char file_name[500];\n"
                   "    const time_t t = time(NULL); \n"
                   "    date = localtime(&t);\n"
                   "\n"
                   "    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();\n"
                   "\n"
                   "    srand((int)time(0));\n"
                   "\n"
                   "    sprintf(file_name, \"/media/lsh/CosmicrayRnE/SimulatedData/AdvencedG4Data/"<<(int)(energy*1000)<<"KeV/%04dY%02dM%02dD%02dh%02dm%02ds_"<<particle<<(int)(energy*1000)<<"KeV%d.csv\", date->tm_year + 1900, date->tm_mon+1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec, rand());\n"
                                                                                                                                                             "\n"
                                                                                                                                                             "    analysisManager -> OpenFile(file_name);\n"
                                                                                                                                                             "\n"
                                                                                                                                                             "  analysisManager -> CreateNtuple(\"step\", \"step\");\n"
                                                                                                                                                             "  analysisManager -> CreateNtupleDColumn(\"MeV\");\n"
                                                                                                                                                             "  analysisManager -> CreateNtupleIColumn(\"particle\");\n"
                                                                                                                                                             "  analysisManager -> CreateNtupleDColumn(\"edep_ch2\");\n"
                                                                                                                                                             "  analysisManager -> CreateNtupleDColumn(\"edep_ch3\");\n"
                                                                                                                                                             "  analysisManager -> FinishNtuple();\n"
                                                                                                                                                             "}\n"
                                                                                                                                                             "\n"
                                                                                                                                                             "void RunAction::EndOfRunAction(const G4Run*)\n"
                                                                                                                                                             "{\n"
                                                                                                                                                             "    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();\n"
                                                                                                                                                             "    analysisManager -> Write();\n"
                                                                                                                                                             "    analysisManager -> CloseFile();\n"
                                                                                                                                                             "}"<<std::endl;

        RunAction.close();
    }

    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char temp_e[10] = {"e-"};
    strcpy(particle, temp_e);
    for(int i = 1; i <= number_of_proj; i++)
    {
        energy = (double)i / divide;
        sprintf(dir, "%s/e-/%fMeV/src/PrimaryGeneratorAction.cc",ProjectDir, energy);
        std::ofstream PrimaryGeneratorAction(dir);

        PrimaryGeneratorAction<<"#include \"PrimaryGeneratorAction.hh\"\n"
                                "\n"
                                "#include \"G4LogicalVolumeStore.hh\"\n"
                                "#include \"G4LogicalVolume.hh\"\n"
                                "#include \"G4Box.hh\"\n"
                                "#include \"G4RunManager.hh\"\n"
                                "#include \"G4ParticleGun.hh\"\n"
                                "#include \"G4ParticleTable.hh\"\n"
                                "#include \"G4ParticleDefinition.hh\"\n"
                                "#include \"G4SystemOfUnits.hh\"\n"
                                "#include \"Randomize.hh\"\n"
                                "\n"
                                "G4double energy = "<<energy<<";\n"
                                                              "int ipja = 2;\n" //2: electron
                                "\n"
                                "PrimaryGeneratorAction::PrimaryGeneratorAction()\n"
                                ": G4VUserPrimaryGeneratorAction()\n"
                                "{\n"
                                "    G4int n_particle = 1;\n"
                                "    fParticleGun = new G4ParticleGun(n_particle);\n"
                                "\n"
                                "    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();\n"
                                "    G4String particleName;\n"
                                "    particleName = \""<< particle<<"\";\n"
                                                                    "    G4ParticleDefinition* particle = particleTable -> FindParticle(particleName);\n"
                                                                    "\n"
                                                                    "    fParticleGun -> SetParticleDefinition(particle);\n"
                                                                    "    fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));\n"
                                                                    "    fParticleGun -> SetParticleEnergy("<<energy<<"*MeV);\n"
                                                                                                                      "\n"
                                                                                                                      "}\n"
                                                                                                                      "\n"
                                                                                                                      "PrimaryGeneratorAction::~PrimaryGeneratorAction()\n"
                                                                                                                      "{\n"
                                                                                                                      "    delete fParticleGun;\n"
                                                                                                                      "}\n"
                                                                                                                      "\n"
                                                                                                                      "void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)\n"
                                                                                                                      "{\n"
                                                                                                                      "    // this function is called at the begining of each event\n"
                                                                                                                      "    fParticleGun -> GeneratePrimaryVertex(anEvent);\n"
                                                                                                                      "}" <<std::endl;

        PrimaryGeneratorAction.close();
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(dir, "%s/e-/%fMeV/src/RunAction.cc",ProjectDir, energy);
        std::ofstream RunAction(dir);

        RunAction<<"#include \"RunAction.hh\"\n"
                   "#include <time.h>\n"
                   "#include <stdio.h>\n"
                   "#include <stdlib.h>\n"
                   "\n"
                   "struct tm *date; \n"
                   "\n"
                   "\n"
                   "\n"
                   "RunAction::RunAction()\n"
                   ": G4UserRunAction()\n"
                   "{\n"
                   "\n"
                   "}\n"
                   "\n"
                   "RunAction::~RunAction()\n"
                   "{\n"
                   "    delete G4AnalysisManager::Instance();\n"
                   "}\n"
                   "\n"
                   "void RunAction::BeginOfRunAction(const G4Run*)\n"
                   "{\n"
                   "    char file_name[500];\n"
                   "    const time_t t = time(NULL); \n"
                   "    date = localtime(&t);\n"
                   "\n"
                   "    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();\n"
                   "\n"
                   "    srand((int)time(0));\n"
                   "\n"
                   "    sprintf(file_name, \"/media/lsh/CosmicrayRnE/SimulatedData/AdvencedG4Data/"<<(int)(energy*1000)<<"KeV/%04dY%02dM%02dD%02dh%02dm%02ds_"<<particle<<(int)(energy*1000)<<"KeV%d.csv\", date->tm_year + 1900, date->tm_mon+1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec, rand());\n"
                                                                                                                                                             "\n"
                                                                                                                                                             "    analysisManager -> OpenFile(file_name);\n"
                                                                                                                                                             "\n"
                                                                                                                                                             "  analysisManager -> CreateNtuple(\"step\", \"step\");\n"
                                                                                                                                                             "  analysisManager -> CreateNtupleDColumn(\"MeV\");\n"
                                                                                                                                                             "  analysisManager -> CreateNtupleIColumn(\"particle\");\n"
                                                                                                                                                             "  analysisManager -> CreateNtupleDColumn(\"edep_ch2\");\n"
                                                                                                                                                             "  analysisManager -> CreateNtupleDColumn(\"edep_ch3\");\n"
                                                                                                                                                             "  analysisManager -> FinishNtuple();\n"
                                                                                                                                                             "}\n"
                                                                                                                                                             "\n"
                                                                                                                                                             "void RunAction::EndOfRunAction(const G4Run*)\n"
                                                                                                                                                             "{\n"
                                                                                                                                                             "    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();\n"
                                                                                                                                                             "    analysisManager -> Write();\n"
                                                                                                                                                             "    analysisManager -> CloseFile();\n"
                                                                                                                                                             "}"<<std::endl;

        RunAction.close();
    }

}