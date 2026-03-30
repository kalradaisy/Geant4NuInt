#include "PrimaryGeneratorMessenger.hh"
#include "G4ThreeVector.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGenerator* gen)
: fGenerator(gen)
{
    fParticleCmd = new G4UIcmdWithAString("/gun/particle", this);
    fParticleCmd->SetGuidance("Set particle type");

    fEnergyCmd = new G4UIcmdWithADoubleAndUnit("/gun/energy", this);
    fEnergyCmd->SetGuidance("Set particle energy");
    fEnergyCmd->SetUnitCategory("Energy");

    fPositionCmd = new G4UIcmdWith3VectorAndUnit("/gun/position", this);
    fPositionCmd->SetGuidance("Set initial particle position");
    fPositionCmd->SetUnitCategory("Length");

    fDirectionCmd = new G4UIcmdWith3VectorAndUnit("/gun/direction", this);
    fDirectionCmd->SetGuidance("Set initial particle momentum direction");
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger() {
    delete fParticleCmd;
    delete fEnergyCmd;
    delete fPositionCmd;
    delete fDirectionCmd;
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
    if(command == fParticleCmd)
        fGenerator->SetParticleName(newValue);
    else if(command == fEnergyCmd)
        fGenerator->SetEnergy(fEnergyCmd->GetNewDoubleValue(newValue));
    else if(command == fPositionCmd)
        fGenerator->SetPosition(fPositionCmd->GetNew3VectorValue(newValue));
    else if(command == fDirectionCmd)
        fGenerator->SetDirection(fDirectionCmd->GetNew3VectorValue(newValue));
}
