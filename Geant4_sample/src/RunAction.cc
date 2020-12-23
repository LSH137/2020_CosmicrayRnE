#include "RunAction.hh"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct tm *date; 



RunAction::RunAction()
: G4UserRunAction()
{

}

RunAction::~RunAction()
{
    delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run*)
{
    char file_name[500];
    const time_t t = time(NULL); 
    date = localtime(&t);

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    srand((int)time(0));

    sprintf(file_name, "/home/cosmicray/Dropbox/cosmicrayRnE/G4Lab/data/%04dY%02dM%02dD%02dh%02dm%02ds_mu-10000MeV%d.csv", date->tm_year + 1900, date->tm_mon+1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec, rand());

    analysisManager -> OpenFile(file_name);

    analysisManager -> CreateNtuple("step", "step");
    analysisManager -> CreateNtupleDColumn("GeV");
    analysisManager -> CreateNtupleIColumn("particle");
    analysisManager -> CreateNtupleDColumn("edep_ch2");
    analysisManager -> CreateNtupleDColumn("edep_ch3");
    analysisManager -> FinishNtuple();
}

void RunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager -> Write();
    analysisManager -> CloseFile();
}
