
// This example is adapted from the Geant4 example N03

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIsession.hh"
#include "Randomize.hh"

//#include "ILDExDetectorConstruction.hh"
#include "ILDExPhysicsList.h"
#include "ILDExPrimaryGeneratorAction.h"
#include "ILDExRunAction.h"
#include "ILDExEventAction.h"
#include "ILDExSteppingAction.h"
#include "ILDExSteppingVerbose.h"
#include "G4UIExecutive.hh"

#include "DDG4/Geant4DetectorConstruction.h"
#include "DD4hep/LCDD.h"

using namespace DD4hep::Geometry;
using namespace DD4hep::Simulation;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  
  // Choose the Random engine
  //
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  
  LCDD& lcdd = LCDD::getInstance();
  for(int i=1; i<argc-1;++i) {
    // We need to construct the geometry at this level already
    lcdd.fromCompact(argv[i]);
  }

  // User Verbose output class
  //
  G4VSteppingVerbose::SetInstance(new ILDExSteppingVerbose);
  
  // Construct the default run manager
  //
  G4RunManager * runManager = new G4RunManager;
  
  // Get the detector constructed
  //
  Geant4DetectorConstruction* detector = new Geant4DetectorConstruction(lcdd);
  runManager->SetUserInitialization(detector);
  
  //
  G4VUserPhysicsList* physics = new ILDExPhysicsList;
  runManager->SetUserInitialization(physics);
  
  // Set user action classes
  //
  G4VUserPrimaryGeneratorAction* gen_action = 
  new ILDExPrimaryGeneratorAction(lcdd);
  runManager->SetUserAction(gen_action);
  //
  ILDExRunAction* run_action = new ILDExRunAction;  
  runManager->SetUserAction(run_action);
  //
  ILDExEventAction* event_action = new ILDExEventAction(run_action);
  runManager->SetUserAction(event_action);
  //
  G4UserSteppingAction* stepping_action =
  new ILDExSteppingAction(event_action);
  runManager->SetUserAction(stepping_action);
  
  // Initialize G4 kernel
  //
  runManager->Initialize();
  
  // Initialize visualization
  //
  //G4VisManager* visManager = new G4VisExecutive;
  //visManager->Initialize();
    
  // Get the pointer to the User Interface manager
  
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  if (argc!=1) {   // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[2];
    UImanager->ApplyCommand(command+fileName);    
  }
  else {  // interactive mode : define UI session
    
    //G4UIsession* ui = new G4UIQt(argc, argv);
    
    //ui->SessionStart();
    //delete ui;
    
  }
  
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
  
  //delete visManager;
  
  
  delete runManager;
  
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
