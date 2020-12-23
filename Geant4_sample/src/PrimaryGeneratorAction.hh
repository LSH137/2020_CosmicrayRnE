#ifndef PRIMARYGENEARATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "globals.hh"

class PrimaryGeneratorAction
    : public G4VUserPrimaryGeneratorAction
    {
        public:
            PrimaryGeneratorAction();
            virtual ~PrimaryGeneratorAction();

            virtual void GeneratePrimaries(G4Event*);

            const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

        private:
            G4ParticleGun* fParticleGun;
    };

#endif