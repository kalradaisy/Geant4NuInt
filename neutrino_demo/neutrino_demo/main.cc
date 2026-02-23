#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4PhysListFactory.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGenerator.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorMessenger.hh"
#include "EventAction.hh"

int main(int argc, char** argv) {
    // Create the run manager
    G4RunManager* runManager = new G4RunManager;

    // Detector construction
    auto detector = new DetectorConstruction();
    runManager->SetUserInitialization(detector);

    // Physics list
    G4PhysListFactory factory;
    runManager->SetUserInitialization(factory.GetReferencePhysList("QGSP_BERT"));

    // Run action (must be created before PrimaryGenerator if PG uses its TTree)
    auto runAction = new RunAction();
    runManager->SetUserAction(runAction);

    // Primary generator, pass runAction pointer
    auto primary = new PrimaryGenerator(runAction);
    runManager->SetUserAction(primary);

    // Attach messenger to allow macro control of primary generator
    auto messenger = new PrimaryGeneratorMessenger(primary);

    // Event action, pass runAction pointer
    runManager->SetUserAction(new EventAction(runAction));

    // Initialize Geant4
    runManager->Initialize();

    // UI / macro execution
    G4UImanager* uiManager = G4UImanager::GetUIpointer();
    if (argc == 2) {
        uiManager->ApplyCommand("/control/execute " + std::string(argv[1]));
    }

    // Cleanup
    delete runManager;

    return 0;
}
