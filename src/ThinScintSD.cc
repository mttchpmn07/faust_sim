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

#include "ThinScintSD.hh"
#include "ThinScintHit.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ThinScintSD::ThinScintSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="thinScintCollection");
}

ThinScintSD::~ThinScintSD(){;}

void  ThinScintSD::Initialize(G4HCofThisEvent* HCE)
{
  static int HCID = -1;
  thinScintCollection = new ThinScintHitsCollection
                      (SensitiveDetectorName,collectionName[0]); 
  if(HCID<0)
  { HCID = GetCollectionID(0); }
  HCE->AddHitsCollection(HCID,thinScintCollection);
}

G4bool ThinScintSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  G4int gammaCounter;

  // G4double edep = aStep->GetTotalEnergyDeposit();
  // if(edep==0.) return false;

  ThinScintHit* newHit = new ThinScintHit();
  // newHit->SetEdep( edep );
  
  
  //  G4cout << "Process Hits!!!!!!!!!!!!!!!!" << G4endl;
 if(aStep->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
    {
      if(aStep->GetTrack()->GetParentID()>0)
	{
	  newHit->SetPos( aStep->GetPreStepPoint()->GetPosition() );
	  thinScintCollection->insert( newHit );
	  //  gammaCounter++;
	  G4double time = aStep->GetTrack()->GetGlobalTime();
	  
	  //G4cout << time << " time" << G4endl;
	  ofstream dataFile ("ThinTimeData.txt", ios_base::app);
	  dataFile << time  << endl;
	 
	}
    }
  return true;
}

void ThinScintSD::EndOfEvent(G4HCofThisEvent*)
{
}

void ThinScintSD::clear()
{
} 

void ThinScintSD::DrawAll()
{
} 

void ThinScintSD::PrintAll()
{
} 
