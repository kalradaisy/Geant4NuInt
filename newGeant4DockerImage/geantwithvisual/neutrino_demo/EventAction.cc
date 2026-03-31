#include "EventAction.hh"
#include "G4Event.hh"
//#include "G4TrajectoryContainer.hh"
//#include "G4Trajectory.hh"
#include "RunAction.hh"

EventAction::EventAction(RunAction* runAction)
: fRunAction(runAction)
{}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event*)
{
    if(!fRunAction) return;

    fRunAction->E = 0;
    fRunAction->x = 0;
    fRunAction->y = 0;
    fRunAction->y = 0;

    fRunAction->finalE = 0;
    fRunAction->finalX = 0;
    fRunAction->finalY = 0;
    fRunAction->finalZ = 0;
}

void EventAction::EndOfEventAction(const G4Event*)
{
    if(!fRunAction || !fRunAction->GetTree()) return;

    // Fill ONCE per event
    fRunAction->GetTree()->Fill();
}
/*
void EventAction::EndOfEventAction(const G4Event* event) {
    if(!fRunAction || !fRunAction->GetTree()) return;

    auto trajContainer = event->GetTrajectoryContainer();
    if(!trajContainer || trajContainer->size() == 0) return;

    for(size_t i = 0; i < trajContainer->size(); ++i) {
        auto traj = static_cast<G4Trajectory*>((*trajContainer)[i]);
        if(!traj) continue;

        size_t nPoints = traj->GetPointEntries();
        if(nPoints == 0) continue;  // <-- THIS IS CRITICAL

        if(traj->GetParentID() == 0) {
            auto finalPos = traj->GetPoint(nPoints-1)->GetPosition();
            fRunAction->finalE = traj->GetInitialMomentum().mag();
            fRunAction->finalX = finalPos.x();
            fRunAction->finalY = finalPos.y();
            fRunAction->finalZ = finalPos.z();
            fRunAction->GetTree()->Fill();
        }
    }
}
*/
/*
void EventAction::EndOfEventAction(const G4Event* event) {
     if(!fRunAction || !fRunAction->GetTree()) return;

    G4TrajectoryContainer* trajContainer = event->GetTrajectoryContainer();
    if(!trajContainer || trajContainer->size() == 0) return;

    for(size_t i=0; i<trajContainer->size(); ++i) {
        auto traj = static_cast<G4Trajectory*>((*trajContainer)[i]);
	//       if(traj->GetParentID() == 0) { // primary particle
        if(traj->GetParentID() != 0) continue;  // only primary
	if(traj->GetPointEntries() == 0) continue; // <--- safety check
	  auto finalPos = traj->GetPoint(traj->GetPointEntries()-1)->GetPosition();

            // Approximate energy by initial momentum magnitude
            fRunAction->finalE = traj->GetInitialMomentum().mag();
            fRunAction->finalX = finalPos.x();
            fRunAction->finalY = finalPos.y();
            fRunAction->finalZ = finalPos.z();

            fRunAction->GetTree()->Fill();
	    //   }
    }
}
*/
