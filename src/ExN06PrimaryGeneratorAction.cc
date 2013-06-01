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
// $Id: ExN06PrimaryGeneratorAction.cc,v 1.6 2006-06-29 17:54:27 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN06PrimaryGeneratorAction.hh"
#include "ExN06PrimaryGeneratorMessenger.hh"
#include "Randomize.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN06PrimaryGeneratorAction::ExN06PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);
  
  //create a messenger for this class
  gunMessenger = new ExN06PrimaryGeneratorMessenger(this);
  
  //default kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("alpha");
 
  // particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleTime(0.0*ns);
  particleGun->SetParticlePosition(G4ThreeVector(-5.0*cm,0.0*cm,0.0*cm));
//xxXX  particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
//xxXX  particleGun->SetParticleEnergy(15.0*MeV);


//xxxXXX
  G4float x_mom = 0.;
  G4float y_mom = 0.;
  G4float z_mom = 0.;
  G4float energy = 0.;

  x_mom = rand() * .1;
  y_mom = rand() * -.02+float(.04*rand()/(RAND_MAX + 1.0)); 
  z_mom = rand() * -.02+float(.04*rand()/(RAND_MAX + 1.0)); 
  energy = rand() * 15.;
 
  particleGun->SetParticleMomentumDirection(G4ThreeVector(x_mom,y_mom,z_mom));
  particleGun->SetParticleEnergy(energy*MeV);



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN06PrimaryGeneratorAction::~ExN06PrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  // static G4ParticleDefinition* part = 0;
  // if (!part)
  //   {
  //     part = particleTable->GetIon(40,90,400.);
  //     particleGun->SetParticleDefinition(part);
  //   }
  particleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->GetIon(40,90,0.));  
  particleGun->GeneratePrimaryVertex(anEvent);
  
  //G4int i = anEvent->get_eventID() % 3;
  //switch(i)
  //{
  //  case 0:
  //    particleGun->SetParticleMomentumDirection(G4ThreeVector(1.0,0.0,0.0));
  //    break;
  //  case 1:
  //    particleGun->SetParticleMomentumDirection(G4ThreeVector(1.0,0.1,0.0));
  //    break;
  //  case 2:
  //    particleGun->SetParticleMomentumDirection(G4ThreeVector(1.0,0.0,0.1));
  //    break;
  //}

//xxxXXX
  G4float x_mom = 0.;
  G4float y_mom = 0.;
  G4float z_mom = 0.;
  G4float energy = 0.;

  x_mom = rand() * .1;
  y_mom = rand() * -.02+float(.04*rand()/(RAND_MAX + 1.0)); 
  z_mom = rand() * -.02+float(.04*rand()/(RAND_MAX + 1.0)); 
  energy = rand() * 15.;
 
  particleGun->SetParticleMomentumDirection(G4ThreeVector(x_mom,y_mom,z_mom));
  particleGun->SetParticleEnergy(energy*MeV);


  particleGun->GeneratePrimaryVertex(anEvent);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
 if (particleGun->GetParticleDefinition()->GetParticleName() != "opticalphoton")
   {
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
               "the particleGun is not an opticalphoton" << G4endl;
     return;
   }
     	       
 G4ThreeVector normal (1., 0., 0.);
 G4ThreeVector kphoton = particleGun->GetParticleMomentumDirection();
 G4ThreeVector product = normal.cross(kphoton); 
 G4double modul2       = product*product;
 
 G4ThreeVector e_perpend (0., 0., 1.);
 if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product; 
 G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
 G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 particleGun->SetParticlePolarization(polar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
