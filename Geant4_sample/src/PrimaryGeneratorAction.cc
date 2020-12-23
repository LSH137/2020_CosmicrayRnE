#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

G4double energy = 10;
int ipja = 0;

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    particleName = "mu-";
    G4ParticleDefinition* particle = particleTable -> FindParticle(particleName);

    fParticleGun -> SetParticleDefinition(particle);
    fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun -> SetParticleEnergy(10*GeV);

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // this function is called at the begining of each event
    fParticleGun -> GeneratePrimaryVertex(anEvent);
}
