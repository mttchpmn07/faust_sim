//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// Jane Tinslay - adapted from A01 example
// Tatsumi Koi - add Silicon Monitor Output 
//
#include "EventAction.hh"
#include "CsI_SDHit.hh"
////////////////////////////////////////////////////////////////////////
// HandsOn4: define Hit of Silicon Monitor
#include "Si_SDHit.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"

EventAction::EventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event*) 
{
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  fHitsCollectionID = SDman->GetCollectionID("CsICollection");
  ////////////////////////////////////////////////////////////////////////
  // HandsOn4: Getting code for HitsCollection of Silicon Monitor
  fHitsCollectionID_Si = SDman->GetCollectionID("SiCollection");
}


void EventAction::EndOfEventAction(const G4Event* event)
{

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

