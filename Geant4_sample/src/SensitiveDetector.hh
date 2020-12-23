#ifndef SensitiveDetector_h
#define SensitiveDetector_h 1
 
#include "G4VSensitiveDetector.hh"
#include "Hit.hh"
 
class SensitiveDetector : public G4VSensitiveDetector
{
   public:
      /* constructor takes the unique name (eg "SD_1") */
      SensitiveDetector(G4String SDname);
      ~SensitiveDetector();
 
   public:
      /* Runs every time the SD is active */
      G4bool ProcessHits(G4Step* kStep, G4TouchableHistory*);
 
      /* (optional) methods */
      void Initialize(G4HCofThisEvent* kHCEvent);
      void EndOfEvent(G4HCofThisEvent* kHCEvent);
 
   private:
      /* Pointer to collection of Hits */
      HitsCollection* fHitsCollection;
 
};
 
#endif