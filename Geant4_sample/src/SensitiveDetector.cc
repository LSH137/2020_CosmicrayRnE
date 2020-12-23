#include "SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4HCtable.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "SteppingAction.hh"
#include "G4SystemOfUnits.hh"

#include "Hit.hh"

G4double edep_ch2 = 0;
G4double edep_ch3 = 0;
int flag = 0;
extern double energy;
extern int ipja;

/* constructor */
SensitiveDetector::SensitiveDetector(G4String SDname)
  : G4VSensitiveDetector(SDname)
{
   /* create a SD identified by a name */
   collectionName.insert(SDname); // 'collectionName' is protected member of SD
}
 
/* destructor */
SensitiveDetector::~SensitiveDetector(){}
 
/* create new Hit Collection at start of the event */
void SensitiveDetector::Initialize(G4HCofThisEvent* kHCEvent)
{
   /* create a collection to store info about the hits */
   fHitsCollection = new HitsCollection(SensitiveDetectorName, collectionName[0]);
 
   /* To insert the collection, we need to get an unique ID for it */
   auto mCollectionID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
   /* add the info into the collection */
   kHCEvent->AddHitsCollection(mCollectionID, fHitsCollection);

   //printf("eventID: %d\n", eventID);
}

/* core of the SD, running whenever a step is inside the assigned volume(s) */
G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  flag = 1;
 
  G4int volumeID = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetCopyNo();

  if(volumeID == 1)
    edep_ch2 = edep_ch2 + step->GetTotalEnergyDeposit();
  else if(volumeID == 2)
    edep_ch3 = edep_ch3 + step->GetTotalEnergyDeposit();
 
  return true;
}
 
/* Action taken at the end of the event, but before EventAction */
void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
  if(flag == 1)
  {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager -> FillNtupleDColumn(0, energy);
    analysisManager -> FillNtupleIColumn(1, ipja);
    analysisManager -> FillNtupleDColumn(2, edep_ch2/keV);
    analysisManager -> FillNtupleDColumn(3, edep_ch3/keV);
    analysisManager -> AddNtupleRow();

    edep_ch2 = 0;
    edep_ch3 = 0;

    flag = 0;
  }
    

     if ( verboseLevel>1 ) 
      { 
        auto nofHits = fHitsCollection->entries();
        G4cout
          << G4endl 
          << "-------->Hits Collection: in this event they are " << nofHits 
          << " hits in the tracker chambers: " << G4endl;
        for ( std::size_t i=0; i<nofHits; ++i ) (*fHitsCollection)[i]->Print();
      }
}
