#include "PrimaryGenerator.hh"
#include "RunAction.hh"
#include "G4ParticleTable.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "TTree.h"

PrimaryGenerator::PrimaryGenerator(RunAction* runAction)
: fRunAction(runAction)
{
    // Create a particle gun with 1 particle per event
    fParticleGun = new G4ParticleGun(1);

    // Default particle and energy
    fParticleName = "nu_mu";          // default particle
    fEnergy = 1.0 * CLHEP::GeV;       // use CLHEP::GeV
    fPosition = G4ThreeVector(0, 0, -1 * CLHEP::cm);

    // Initialize particle gun
    G4ParticleDefinition* particle
        = G4ParticleTable::GetParticleTable()->FindParticle(fParticleName);
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(fEnergy);
    fParticleGun->SetParticlePosition(fPosition);
}

PrimaryGenerator::~PrimaryGenerator()
{
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* event)
{
    // Update particle definition in case messenger changed it
    G4ParticleDefinition* particle
        = G4ParticleTable::GetParticleTable()->FindParticle(fParticleName);
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(fEnergy);
    fParticleGun->SetParticlePosition(fPosition);

    // Shoot particle
    fParticleGun->GeneratePrimaryVertex(event);

    // Fill TTree in RunAction if available
    if (fRunAction && fRunAction->GetTree()) {
        TTree* tree = fRunAction->GetTree();

        // Store initial particle info
        Double_t E = fEnergy;
        Double_t x = fPosition.x();
        Double_t y = fPosition.y();
        Double_t z = fPosition.z();
        Double_t finalE = 0.0;
        Double_t finalX = 0.0;
        Double_t finalY = 0.0;
        Double_t finalZ = 0.0;

        tree->Fill();  // Note: We'll assume tree has branches bound to RunAction member variables
    }
}
