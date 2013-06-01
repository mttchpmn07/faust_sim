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
// $Id:$
//
// Jane Tinslay - adapted from A01 example
// Tatsumi Koi   Minor modifications for McGill Univ.  tutorial
//
#include "Si_SD.hh"
#include "G4HCofThisEvent.hh"

#include "G4SDManager.hh"
#include "G4Step.hh"    
#include "G4TouchableHistory.hh"
#include "G4Track.hh"

Si_SD::Si_SD(const G4String& name)
  :G4VSensitiveDetector(name)
{
  collectionName.insert("SiCollection");
  fHitsCollectionID_Si = -1;
}

Si_SD::~Si_SD() {}

void Si_SD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent)
{
  // HandsOn4: Creating hit collection
  // Create a new collection
  fHitsCollection =
    new Si_SDHitsCollection(SensitiveDetectorName, collectionName[0]);
 
  if(fHitsCollectionID_Si < 0)
    fHitsCollectionID_Si = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
 
  // Add collection to the event
  hitsCollectionOfThisEvent->AddHitsCollection(fHitsCollectionID_Si, fHitsCollection);
 
  // Initialise hits
  G4int i(0);
 
  for (i=0; i<100; i++) {
    Si_SDHit* aHit = new Si_SDHit(i);
    fHitsCollection->insert(aHit);
  }
}

G4bool Si_SD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  // HandsOn4: Accumulating hit data
  // Get energy deposited in this step
  G4double depositedEnergy = aStep->GetTotalEnergyDeposit();
  if (0 == depositedEnergy) return true;
 
 
  // Get volume and copy number
  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4TouchableHistory* theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
 
  G4VPhysicalVolume* thePhysical = theTouchable->GetVolume();
  G4int copyNo = thePhysical->GetCopyNo();
 
  // Get corresponding hit
 Si_SDHit* aHit = (*fHitsCollection)[copyNo];
 
  // Check to see if this is the first time the hit has been updated
  if (!(aHit->GetLogicalVolume())) {
 
    // Set volume information
    aHit->SetLogicalVolume(thePhysical->GetLogicalVolume());
 
    G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();
    aTrans.Invert();
 
    aHit->SetRotation(aTrans.NetRotation());
    aHit->SetPosition(aTrans.NetTranslation());
  }
 
  // Accumulate energy deposition  
  aHit->AddDepositedEnergy(depositedEnergy);
  return true;
}

void Si_SD::EndOfEvent(G4HCofThisEvent*) {}
