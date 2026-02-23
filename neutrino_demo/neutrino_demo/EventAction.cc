#include "EventAction.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "RunAction.hh"

EventAction::EventAction(RunAction* runAction)
: fRunAction(runAction)
{}

EventAction::~EventAction() {}

void EventAction::EndOfEventAction(const G4Event* event) {
    if(!fRunAction || !fRunAction->GetTree()) return;

    G4TrajectoryContainer* trajContainer = event->GetTrajectoryContainer();
    if(!trajContainer) return;

    for(size_t i=0; i<trajContainer->size(); ++i) {
        auto traj = static_cast<G4Trajectory*>((*trajContainer)[i]);
        if(traj->GetParentID() == 0) { // primary particle
            auto finalPos = traj->GetPoint(traj->GetPointEntries()-1)->GetPosition();

            // Approximate energy by initial momentum magnitude
            fRunAction->finalE = traj->GetInitialMomentum().mag();
            fRunAction->finalX = finalPos.x();
            fRunAction->finalY = finalPos.y();
            fRunAction->finalZ = finalPos.z();

            fRunAction->GetTree()->Fill();
        }
    }
}
