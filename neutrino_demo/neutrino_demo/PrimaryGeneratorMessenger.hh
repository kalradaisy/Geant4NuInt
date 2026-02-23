// PrimaryGeneratorMessenger.hh
#include "G4UImessenger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "PrimaryGenerator.hh"

class PrimaryGeneratorMessenger : public G4UImessenger {
public:
    PrimaryGeneratorMessenger(PrimaryGenerator* gen);
    ~PrimaryGeneratorMessenger();

    void SetNewValue(G4UIcommand* command, G4String newValue) override;

private:
    PrimaryGenerator* fGenerator;
    G4UIcmdWithAString* fParticleCmd;
    G4UIcmdWithADoubleAndUnit* fEnergyCmd;
    // ... you can add position and direction similarly
};
