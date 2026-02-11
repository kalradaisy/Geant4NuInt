#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Exception.hh"
#include "G4RunManager.hh"
#include "G4GDMLParser.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction()
{
    fMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
    delete fMessenger;
}

// Allows macro-based GDML reloading
void DetectorConstruction::ReadGDML(const G4String& filename)
{
    G4cout << "Reading GDML file: " << filename << G4endl;

    fParser.Read(filename, false);  // false disables schema validation

    G4VPhysicalVolume* world = fParser.GetWorldVolume();
    if (!world) {
        G4cerr << "GDML read, but world volume is NULL!" << G4endl;
        G4cerr << "Check that your GDML defines a <world> and all solids/materials." << G4endl;

        G4Exception("DetectorConstruction::ReadGDML",
                    "NoGDML",
                    FatalException,
                    "World volume is NULL after reading GDML.");
    }

    G4cout << "GDML loaded successfully. World volume: "
           << world->GetName() << G4endl;

    // Reinitialize geometry after macro reload
    G4RunManager::GetRunManager()->ReinitializeGeometry();
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    if (!fGDMLFile.empty()) {
        fParser.Read(fGDMLFile, false);
        return fParser.GetWorldVolume();
    }

    // Default: empty vacuum box
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");

    G4Box* worldSolid = new G4Box("World", 1.*CLHEP::m, 1.*CLHEP::m, 1.*CLHEP::m);
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldSolid, vacuum, "World");
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(
        nullptr, G4ThreeVector(), worldLog, "World", nullptr, false, 0);

    return worldPhys;
}

/*
class DetectorConstruction : public G4VUserDetectorConstruction {
public:
  G4VPhysicalVolume* Construct() override {
    G4GDMLParser parser;
    parser.Read("simple_det.gdml");
    return parser.GetWorldVolume();
   }

*/
/*auto nist = G4NistManager::Instance();

        // World
        G4double worldSize = 1.0*m;
        G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
        G4Box* worldSolid = new G4Box("World", worldSize/2, worldSize/2, worldSize/2);
        G4LogicalVolume* worldLogic = new G4LogicalVolume(worldSolid, air, "World");
        G4VPhysicalVolume* worldPhys = new G4PVPlacement(nullptr, G4ThreeVector(), worldLogic, "World", nullptr, false, 0);

        // Liquid Argon target
        G4Material* LAr = nist->FindOrBuildMaterial("G4_lAr");
        G4double LArSize = 0.5*m;
        G4Box* LArBox = new G4Box("LArBox", LArSize/2, LArSize/2, LArSize/2);
        G4LogicalVolume* LArLogic = new G4LogicalVolume(LArBox, LAr, "LArLogic");
        new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), LArLogic, "LArPhys", worldLogic, false, 0);

        return worldPhys;
	}*/
//};
