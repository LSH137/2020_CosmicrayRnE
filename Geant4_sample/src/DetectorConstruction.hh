#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction
    : public G4VUserDetectorConstruction
    {
        public:
            DetectorConstruction();
            virtual ~DetectorConstruction();

            virtual G4VPhysicalVolume* Construct();
    };

#endif