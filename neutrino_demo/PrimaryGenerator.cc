#include "PrimaryGenerator.hh"
#include "G4ParticleTable.hh"
#include "G4AnalysisManager.hh"

PrimaryGenerator::PrimaryGenerator()
 : fParticleGun(new G4ParticleGun(1)),
   fParticleName("nu_mu"),            // default
   fEnergy(1.0*GeV),
   fPosition(G4ThreeVector(0,0,-1*cm)),
   fDirection(G4ThreeVector(0,0,1))
{}

PrimaryGenerator::~PrimaryGenerator() {
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* event) {
    auto particleTable = G4ParticleTable::GetParticleTable();
    fParticleGun->SetParticleDefinition(particleTable->FindParticle(fParticleName));
    fParticleGun->SetParticleEnergy(fEnergy);
    fParticleGun->SetParticlePosition(fPosition);
    fParticleGun->SetParticleMomentumDirection(fDirection);

    fParticleGun->GeneratePrimaryVertex(event);

    // Fill ROOT ntuple
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, fEnergy);
    analysisManager->FillNtupleDColumn(1, fPosition.x());
    analysisManager->FillNtupleDColumn(2, fPosition.y());
    analysisManager->FillNtupleDColumn(3, fPosition.z());
    analysisManager->AddNtupleRow();
}

/*#include "PrimaryGenerator.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

PrimaryGenerator::PrimaryGenerator() {
    fParticleGun = new G4ParticleGun(1); // 1 particle per event
    auto particleTable = G4ParticleTable::GetParticleTable();
    fParticleGun->SetParticleDefinition(particleTable->FindParticle("nu_mu"));
    fParticleGun->SetParticleEnergy(1.0*GeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0,0,-50*cm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
}

PrimaryGenerator::~PrimaryGenerator() {
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* event) {
    fParticleGun->GeneratePrimaryVertex(event);

    // Fill ROOT ntuple with primary particle info
    auto analysisManager = G4AnalysisManager::Instance();
    G4double E = fParticleGun->GetParticleEnergy();
    G4ThreeVector pos = fParticleGun->GetParticlePosition();
    analysisManager->FillNtupleDColumn(0, E);
    analysisManager->FillNtupleDColumn(1, pos.x());
    analysisManager->FillNtupleDColumn(2, pos.y());
    analysisManager->FillNtupleDColumn(3, pos.z());
    analysisManager->AddNtupleRow();
}
*/
