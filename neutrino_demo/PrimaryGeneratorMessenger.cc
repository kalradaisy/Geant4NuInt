// PrimaryGeneratorMessenger.cc
#include "PrimaryGeneratorMessenger.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGenerator* gen)
 : fGenerator(gen)
{
    fParticleCmd = new G4UIcmdWithAString("/gun/particle", this);
    fParticleCmd->SetGuidance("Set particle type");

    fEnergyCmd = new G4UIcmdWithADoubleAndUnit("/gun/energy", this);
    fEnergyCmd->SetGuidance("Set particle energy");
    fEnergyCmd->SetUnitCategory("Energy");
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger() {
    delete fParticleCmd;
    delete fEnergyCmd;
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
    if (command == fParticleCmd)
        fGenerator->SetParticleName(newValue);
    else if (command == fEnergyCmd)
        fGenerator->SetEnergy(fEnergyCmd->GetNewDoubleValue(newValue));
}
