#ifndef RUNACTION_H
#define RUNACTION_H

#include "G4UserRunAction.hh"
#include "TFile.h"
#include "TTree.h"

class RunAction : public G4UserRunAction {
public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*) override;
    virtual void EndOfRunAction(const G4Run*) override;

    TTree* GetTree() { return fTree; }

    // Variables for ROOT branches (non-static)
    double E, x, y, z;
    double finalE, finalX, finalY, finalZ;

private:
    TFile* fFile;
    TTree* fTree;
};

#endif
