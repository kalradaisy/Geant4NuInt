#pragma once
#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

class RunAction;

class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction(RunAction* runAction);
    ~SteppingAction() override = default;

    void UserSteppingAction(const G4Step* step) override;

private:
    RunAction* fRunAction;
};
