#include "SteppingAction.hh"
#include "RunAction.hh"

SteppingAction::SteppingAction(RunAction* runAction)
: fRunAction(runAction) {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    if(!fRunAction) return;

    auto track = step->GetTrack();
    if(track->GetParentID() != 0) return; // only primary

    // Initial kinematics (record once)
    if(fRunAction->E == 0) {
      //        fRunAction->E = track->GetMomentum().mag();
	fRunAction->E = track->GetKineticEnergy();
        auto pos = track->GetPosition();
        fRunAction->x = pos.x();
        fRunAction->y = pos.y();
        fRunAction->z = pos.z();
    }

    // Update final kinematics at each step
    auto finalPos = track->GetPosition();
    fRunAction->finalE = track->GetKineticEnergy();
    fRunAction->finalX = finalPos.x();
    fRunAction->finalY = finalPos.y();
    fRunAction->finalZ = finalPos.z();
}
