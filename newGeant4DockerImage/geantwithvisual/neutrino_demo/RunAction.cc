#include "RunAction.hh"
#include "G4Run.hh"

RunAction::RunAction()
: G4UserRunAction(),
  fFile(nullptr), fTree(nullptr),
  E(0), x(0), y(0), z(0),
  finalE(0), finalX(0), finalY(0), finalZ(0)
{}

RunAction::~RunAction() {}

//void RunAction::BeginOfRunAction(const G4Run*) {}
//void RunAction::EndOfRunAction(const G4Run*) {}


void RunAction::BeginOfRunAction(const G4Run*) {
    fFile = new TFile("neutrino.root", "RECREATE");
    fTree = new TTree("tree", "Neutrino data");

    fTree->Branch("E", &E, "E/D");
    fTree->Branch("x", &x, "x/D");
    fTree->Branch("y", &y, "y/D");
    fTree->Branch("z", &z, "z/D");

    fTree->Branch("finalE", &finalE, "finalE/D");
    fTree->Branch("finalX", &finalX, "finalX/D");
    fTree->Branch("finalY", &finalY, "finalY/D");
    fTree->Branch("finalZ", &finalZ, "finalZ/D");
}

void RunAction::EndOfRunAction(const G4Run*) {
 if(fTree && fFile) {
   fFile->cd();
   fTree->Write();
   fFile->Close();
 }
}

