#ifndef PrimaryGenerator_h
#define PrimaryGenerator_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

class PrimaryGenerator : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGenerator();
    ~PrimaryGenerator();

    void GeneratePrimaries(G4Event* event) override;

    // Methods to set parameters from macro
    void SetParticleName(const G4String& name) { fParticleName = name; }
    void SetEnergy(G4double e) { fEnergy = e; }
    void SetPosition(const G4ThreeVector& pos) { fPosition = pos; }
    void SetDirection(const G4ThreeVector& dir) { fDirection = dir; }

private:
    G4ParticleGun* fParticleGun;
    G4String fParticleName;
    G4double fEnergy;
    G4ThreeVector fPosition;
    G4ThreeVector fDirection;
};

#endif
