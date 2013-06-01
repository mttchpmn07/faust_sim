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
#include "ExN06PMTSD.hh"
#include "ExN06PMTHit.hh"
#include "ExN06DetectorConstruction.hh"
//#include "ExN06UserTrackInformation.hh"
#include "ExN06StackingAction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4SDManager.hh"
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
ExN06PMTSD::ExN06PMTSD(G4String name)
  :G4VSensitiveDetector(name),pmtHitCollection(0),pmtPositionsX(0)
  ,pmtPositionsY(0),pmtPositionsZ(0)
{
  collectionName.insert("PMTHitsCollection");
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
ExN06PMTSD::~ExN06PMTSD()
{;}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void ExN06PMTSD::Initialize(G4HCofThisEvent* HCE){
  pmtHitCollection = new ExN06PMTHitsCollection
                      (SensitiveDetectorName,collectionName[0]); 
  //Store collection with event and keep ID
  static G4int HCID = -1;
  if(HCID<0){ 
    HCID = GetCollectionID(0); 
  }
  HCE->AddHitsCollection( HCID, pmtHitCollection );
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
G4bool ExN06PMTSD::ProcessHits(G4Step* aStep,G4TouchableHistory* ){
  
  // G4String ParticleName = aStep->GetTrack()->GetDefinition()->GetParticleName();

  // ExN06PMTHit* newHit = new ExN06PMTHit();

  G4int PhotonTotal = 0;
 
  G4int energyCount;  //How many MeV need to be used for each hit
  G4double EnergyTotal = 0.*MeV;
  
  //newHit->SetParticleName(aStep->GetTrack()->GetDefinition()->GetParticleName());
  if((aStep->GetTrack()->GetDefinition()->GetParticleName())=="opticalphoton")
    {     
      //for every 50 Photons, increase energy by 1MeV
      //PhotonTotal = PhotonTotal + gammaCounter;
      if (PhotonTotal/50 != 0)
	{
	  energyCount = PhotonTotal/50;
	  EnergyTotal = EnergyTotal + PhotonTotal*(1.0*MeV);
	  PhotonTotal = 0;
	  energyCount = 0;
	}
	  
    }
  G4cout << "PMTTTTTTTT" << G4endl;
}

//Generates a hit and uses the postStepPoint's mother volume replica number
//PostStepPoint because the hit is generated manually when the photon is
//absorbed by the photocathode
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
G4bool ExN06PMTSD::ProcessHits_constStep(const G4Step* aStep,
				       G4TouchableHistory* ){

  // //need to know if this is an optical photon
  // if(aStep->GetTrack()->GetDefinition() 
  //    != G4OpticalPhoton::OpticalPhotonDefinition()) return false;
 
  // //User replica number 1 since photocathode is a daughter volume
  // //to the pmt which was replicated
  // G4int pmtNumber=
  //   aStep->GetPostStepPoint()->GetTouchable()->GetReplicaNumber(1);
  // G4VPhysicalVolume* physVol=
  //   aStep->GetPostStepPoint()->GetTouchable()->GetVolume(1);

  // //Find the correct hit collection
  // G4int n=pmtHitCollection->entries();
  // ExN06PMTHit* hit=NULL;
  // for(G4int i=0;i<n;i++){
  //   if((*pmtHitCollection)[i]->GetPMTNumber()==pmtNumber){
  //     hit=(*pmtHitCollection)[i];
  //     break;
  //   }
  // }
  
  // if(hit==NULL){//this pmt wasnt previously hit in this event
  //   G4cout << "------PMT NOT HIT-----------" << G4endl;
  //   hit = new ExN06PMTHit(); //so create new hit
  //   hit->SetPMTNumber(pmtNumber);
  //   hit->SetPMTPhysVol(physVol);
  //   pmtHitCollection->insert(hit);
  //   hit->SetPMTPos((*pmtPositionsX)[pmtNumber],(*pmtPositionsY)[pmtNumber],
  // 		   (*pmtPositionsZ)[pmtNumber]);
  // }

  // hit->IncPhotonCount(); //increment hit for the selected pmt
    
  // // if(!LXeDetectorConstruction::GetSphereOn()){
  // //   hit->SetDrawit(true);
  // //   //If the sphere is disabled then this hit is automaticaly drawn
  // // }
  // // else{//sphere enabled
  // //   LXeUserTrackInformation* trackInfo=
  // //     (LXeUserTrackInformation*)aStep->GetTrack()->GetUserInformation();
  // //   if(trackInfo->GetTrackStatus()&hitSphere) 
  // //     //only draw this hit if the photon has hit the sphere first
  // //     hit->SetDrawit(true);
  // // }
    
  // return true;
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void ExN06PMTSD::EndOfEvent(G4HCofThisEvent* HCE ){

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4String detName = "ExN06PMTSD";
  // G4int collectionID = SDman->GetCollectionID("PMTHitsCollection");

  // ExN06PMTHitsCollection* myCollection = (ExN06PMTHitsCollection*)(HCE->GetHC(collectionID));


}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void ExN06PMTSD::clear(){
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void ExN06PMTSD::DrawAll(){
} 

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void ExN06PMTSD::PrintAll(){
} 

