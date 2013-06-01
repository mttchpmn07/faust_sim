//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: ExN06EventAction.cc,v 1.11 2006-06-29 17:48:05 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#include "ExN06EventAction.hh"
#include "ExN06PMTHit.hh"
//#include "PMT_SD.hh"
#include "ExN06PMTSD.hh"
#include "ThickScintSD.hh"
#include "ThinScintSD.hh"
#include "ExN06UserEventInformation.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"

#include <iostream>
#include <fstream>
#include <vector>

//xxxXXXxxx''''''xxxXXXxxx
#include "CsI_SDHit.hh"
#include "Si_SDHit.hh"
#include "G4HCofThisEvent.hh"



using namespace std;



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
ExN06EventAction::ExN06EventAction()
  :pmtCollID(-1)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
ExN06EventAction::~ExN06EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void ExN06EventAction::BeginOfEventAction(const G4Event*)
{

//xxxXXXxxx''''''xxxXXXxxx
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  fHitsCollectionID = SDman->GetCollectionID("CsICollection");
 // HandsOn4: Getting code for HitsCollection of Silicon Monitor
  fHitsCollectionID_Si = SDman->GetCollectionID("SiCollection");
//xxxXXXxxx

  // G4SDManager* SDman = G4SDManager::GetSDMpointer();
  // if(pmtCollID<0)
  // pmtCollID = SDman->GetCollectionID("pmtHitCollection");

#if defined (G4ANALYSIS_USE_ROOT)
  if (gSystem) gSystem->ProcessEvents();

  if(eventcounter%1000==0){
    eventtimer->Stop();
    //eventtimer->Print();
    eventtimer->Start();
    G4cout << eventcounter << " done " << G4endl;
  }
  eventcounter++;

  totE          = 0;
  edep          = 0;

#endif /* defined (G4ANALYSIS_USE_ROOT) */
  
  //OnceAWhileDoIt();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void ExN06EventAction::EndOfEventAction(const G4Event* event)
{
//xxXX  G4int event_id = evt->GetEventID();

//xxXXExN06UserEventInformation* eventInformation 
//xxXX  = (ExN06UserEventInformation*)evt->GetUserInformation();
  
  // get number of stored trajectories
  //
//xxXX  G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
//xxXX  G4int n_trajectories = 0;
//xxXX  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries(); 

  
  // periodic printing
  //
//xxXX  if (event_id < 100 || event_id%100 == 0) {
//xxXX    G4cout << ">>> Event " << evt->GetEventID() << G4endl;
    // G4cout << "    " << n_trajectories 
    // 	   << " trajectories stored in this event." << G4endl;
//xxXX  }

  //#if defined (G4ANALYSIS_USE_ROOT)
    //G4cout << "USE ROOT defined " << G4endl;
  // if (gSystem) gSystem->ProcessEvents();

//xxXX  G4SDManager *SDman = G4SDManager::GetSDMpointer();
//xxXX  G4String colNam;
  // //G4int PMTColID = SDman->GetCollectionID(colNam="PMTHitsCollection");
//xxXX  G4int ThickScintColID = SDman->GetCollectionID(colNam="thickScintCollection");
//xxXX  G4int ThinScintColID = SDman->GetCollectionID(colNam="thinScintCollection");
 


  //Getting hit collections
  //

  //ExN06PMTHitsCollection *PHC = 0;
//xxXX  ThickScintHitsCollection* ThickSHC = 0;
//xxXX  ThinScintHitsCollection* ThinSHC = 0;
//xxXX  G4HCofThisEvent *HCE = evt->GetHCofThisEvent();

 //xxXX if(HCE){
    //if(pmtCollID>=0)PHC = (ExN06PMTHitsCollection*)(HCE->GetHC(pmtCollID));}
    //PHC = (ExN06PMTHitsCollection*)(HCE->GetHC(PMTColID));
 //xxXX   ThickSHC = (ThickScintHitsCollection*)(HCE->GetHC(ThickScintColID));
 //xxXX   ThinSHC = (ThinScintHitsCollection*)(HCE->GetHC(ThinScintColID));
   
 //xxXX }

  // if(PHC){
  //   G4ThreeVector reconPos(0.,0.,0.);
  //   G4int pmts = PHC->entries();

  //   //G4cout << "----------------PMT-----------------------" << G4endl;
  //   // //gather info from all PMTS
  //   for(G4int i = 0; i<pmts; i++){
  //    //  eventInformation->IncHitCount((*PHC)[i]->GetPhotonCount());
  //   //   reconPos+=(*PHC)[i]->GetPMTPos()*(*PHC)[i]->GetPhotonCount();
  //   //  //  if((*PHC)[i]->GetPhotonCount()>=pmtThreshold){
  //   // // 	eventInformation->IncPMTSAboveThreshold();}
  //   // //   else (//wasnt above the threshold, turn it back off
  //   // // 	    (*PHC)[i]->SetDrawit(false);
  //   //   edep = edep +(*PHC)[i]->GetEdep()/MeV;
  //     // G4String name = (*PHC)[i]->GetParticleName();
  //     // if (name == "opticalphoton"){
  //     // // G4String parentname = (*PHC)[i]->GetParentName();
  //     // // G4double parentenergy = (*PHC)[i]->GetParentEnergy();
  //     // // G4ThreeVector parmodir = (*PHC)[i]->GetParentMoDir(); //parent momentum direction

  //     // // G4double edep = (*PHC)[i]->GetEdep()/MeV;
  //     // // G4int stepno = (*PHC)[i]->GetStepno();
  //     // // G4double globaltime = (*PHC)[i]->GetGtime()/second;
  //     // }

  //   }
   
  //   //hEnergyDeposit->Fill(edep);
  //   // G4cout <<"--Entries-- " << pmts << G4endl;
  // }

 //xxXX if (ThickSHC){
    //G4cout << "Thick Scint!!!!!!! " << G4endl;
 //xxXX   ofstream dataFile ("ThickGammaEnergyData.txt", ios_base::app);
 //xxXX   n_ThickHit = ThickSHC->entries();
    

    //G4cout << "#####Number of hits in Scint: " << n_ThickHit << G4endl;
 //xxXX   G4double EnergyTotal = (n_ThickHit - 1.2167)/ 49.7361;

   
 //xxXX   dataFile << n_ThickHit << "  " << EnergyTotal << endl;
    //dataFile << n_hit << endl;
    
 //xxXX }

 //xxXX if (ThinSHC){
    //G4cout << "Thin Scint!!!!!" << G4endl;
 //xxXX   int n_Thinhit = ThinSHC->entries();
    //G4cout << "####Number in THIN: " << n_Thinhit << G4endl;
 //xxXX   G4double EnergyTotal = (n_Thinhit - 1.2167)/ 49.7361;

 //xxXX   ofstream dataFile ("ThinGammaEnergyData.txt", ios_base::app);
  //xxXX  dataFile << n_Thinhit << "  " << EnergyTotal << endl;
 //xxXX }


  //#endif
  //G4cout << "Hello" << G4endl;

//xxxXXXxxx

  G4HCofThisEvent *hitsCollectionOfThisEvent = event->GetHCofThisEvent();

  if (fHitsCollectionID >= 0)
  {

     CsI_SDHitsCollection* hitsCollection = 
       dynamic_cast<CsI_SDHitsCollection*>(hitsCollectionOfThisEvent->GetHC(fHitsCollectionID));
  
     G4double totalEnergy = 0.;
  
     if ( 0 != hitsCollection ) {
        G4int i(0);
    
        for ( i=0 ; i<100 ; i++ ) {
           CsI_SDHit* aHit = (*hitsCollection)[i];   
           totalEnergy += aHit->GetDepositedEnergy();
      
           aHit->Print();
        }
     }
     G4cout<<"Energy deposited in CsI "<<totalEnergy/MeV<<" MeV"<<G4endl;
  }
  

    
    if (fHitsCollectionID_Si >= 0)
    {
        
        Si_SDHitsCollection* hitsCollection = 
        dynamic_cast<Si_SDHitsCollection*>(hitsCollectionOfThisEvent->GetHC(fHitsCollectionID_Si));
        
        G4double totalEnergy = 0.;
        
        if ( 0 != hitsCollection ) {
            G4int i(0);
            
            for ( i=0 ; i<100 ; i++ ) {
                Si_SDHit* aHit = (*hitsCollection)[i];   
                totalEnergy += aHit->GetDepositedEnergy();
                
                aHit->Print();
            }
        }
        G4cout<<"Energy deposited in Si "<<totalEnergy/MeV<<" MeV"<<G4endl;
    }
    
 
 


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
