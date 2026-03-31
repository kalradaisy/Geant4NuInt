#ifndef EVENTACTION_H
#define EVENTACTION_H

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "RunAction.hh"       // if you use RunAction inside EventAction

class EventAction : public G4UserEventAction {
public:
    EventAction(RunAction* runAction);   // pass pointer to RunAction if needed
    ~EventAction() override;

    // Override correct function
  void BeginOfEventAction(const G4Event*) override;
  void EndOfEventAction(const G4Event* event) override;

private:
    RunAction* fRunAction;
};

#endif
