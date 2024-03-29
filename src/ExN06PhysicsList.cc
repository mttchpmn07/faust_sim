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
// $Id: ExN06PhysicsList.cc,v 1.19 2010-10-23 19:14:03 gum Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "ExN06PhysicsList.hh"
#include "ExN06PhysicsListMessenger.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4IonConstructor.hh"

#include "G4ProcessManager.hh"

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpMieHG.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"
 
//''''xxxXXXXXXxxx''''''xxxXXXXXXxxx''''''
//  I M P O R T   O F   F A U S T
//  
// -Adding includes that differ

#include "G4BaryonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4ComptonScattering.hh"
#include "G4Decay.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eIonisation.hh"
#include "G4eplusAnnihilation.hh"
#include "G4GammaConversion.hh"
#include "G4hIonisation.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuIonisation.hh"
#include "G4MuPairProduction.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#include "G4ionIonisation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN06PhysicsList::ExN06PhysicsList() :  G4VUserPhysicsList()
{
  theCerenkovProcess           = NULL;
  theScintillationProcess      = NULL;
  theAbsorptionProcess         = NULL;
  theRayleighScatteringProcess = NULL;
  theMieHGScatteringProcess    = NULL;
  theBoundaryProcess           = NULL;
  
  pMessenger = new ExN06PhysicsListMessenger(this);  
  SetVerboseLevel(0);

//xxxXXX
  defaultCutValue = 1.0*mm;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN06PhysicsList::~ExN06PhysicsList() { delete pMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program.

  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();

//xxxXXX

  G4Geantino::GeantinoDefinition();
    
    //  Baryons
    G4BaryonConstructor baryons;
    baryons.ConstructParticle();
    
    // Bosons (including geantinos)
    G4BosonConstructor bosons;
    bosons.ConstructParticle();
    
    // Ions
    G4IonConstructor ions;
    ions.ConstructParticle();
    
    // Leptons
    G4LeptonConstructor leptons;
    leptons.ConstructParticle();
    
    // Construct all mesons
    G4MesonConstructor mesons;
    mesons.ConstructParticle();
    
    // Resonances and quarks
    G4ShortLivedConstructor shortLiveds;
    shortLiveds.ConstructParticle();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::ConstructBosons()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();

  //alpha
  G4Alpha::AlphaDefinition();

  // optical photon
  G4OpticalPhoton::OpticalPhotonDefinition();

  //Generic Ion
  // G4GenericIon::GenericIonDefinition();
  G4IonConstructor pIons;
  pIons.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::ConstructLeptons()
{
  // leptons
  //  e+/-
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  // mu+/-
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  // nu_e
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  // nu_mu
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::ConstructMesons()
{
  //  mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::ConstructBaryons()
{
  //  barions
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();

  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructGeneral();
  ConstructEM();
  ConstructOp();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::ConstructGeneral()
{
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();

  theParticleIterator->reset();

  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (theDecayProcess->IsApplicable(*particle)) {
      pmanager ->AddProcess(theDecayProcess);

      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::ConstructEM()
{
  theParticleIterator->reset();

  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") {
      // Construct processes for gamma
      pmanager->AddDiscreteProcess(new G4GammaConversion());
      pmanager->AddDiscreteProcess(new G4ComptonScattering());
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect());

    } else if (particleName == "e-") {
      // Construct processes for electron
      pmanager->AddProcess(new G4eMultipleScattering(),-1, 1, 1);
      pmanager->AddProcess(new G4eIonisation(),        -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung(),    -1, 3, 3);

    } else if (particleName == "e+") {
      // Construct processes for positron
      pmanager->AddProcess(new G4eMultipleScattering(),-1, 1, 1);
      pmanager->AddProcess(new G4eIonisation(),        -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung(),    -1, 3, 3);
      pmanager->AddProcess(new G4eplusAnnihilation(),   0,-1, 4);

    } else if( particleName == "mu+" ||
               particleName == "mu-"    ) {
      // Construct processes for muon
      pmanager->AddProcess(new G4MuMultipleScattering(),-1, 1, 1);
      pmanager->AddProcess(new G4MuIonisation(),        -1, 2, 2);
      pmanager->AddProcess(new G4MuBremsstrahlung(),    -1, 3, 3);
      pmanager->AddProcess(new G4MuPairProduction(),    -1, 4, 4);

    } else if (particleName == "alpha"){
      //construct process for alpha
      pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
      pmanager->AddProcess(new G4MuIonisation(),        -1, 2, 2);

    }   else {
      //if ((particle->GetPDGCharge() != 0.0) &&
      //    (particle->GetParticleName() != "chargedgeantino")) {
       // all others charged particles except geantino
       //pmanager->AddProcess(new G4hMultipleScattering(),-1,1,1);
       //pmanager->AddProcess(new G4hIonisation(),       -1,2,2);
     }
    }
   
  G4ProcessManager* pmanager=0;
  pmanager = G4GenericIon::GenericIon()->GetProcessManager();
  // Add EM Processes to Generic Ions
  pmanager->AddProcess(new G4hMultipleScattering,-1,1,1);
  pmanager->AddProcess(new G4ionIonisation,       -1,2,2);
  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::ConstructOp()
{
  //theCerenkovProcess           = new G4Cerenkov("Cerenkov");
  theScintillationProcess      = new G4Scintillation("Scintillation");
  theAbsorptionProcess         = new G4OpAbsorption();
  theRayleighScatteringProcess = new G4OpRayleigh();
  theMieHGScatteringProcess    = new G4OpMieHG();
  theBoundaryProcess           = new G4OpBoundaryProcess();

//  theCerenkovProcess->DumpPhysicsTable();
//  theScintillationProcess->DumpPhysicsTable();
//  theRayleighScatteringProcess->DumpPhysicsTable();

  SetVerbose(0);
  
  // theCerenkovProcess->SetMaxNumPhotonsPerStep(20);
  // theCerenkovProcess->SetMaxBetaChangePerStep(10.0);
  // theCerenkovProcess->SetTrackSecondariesFirst(true);
  
  theScintillationProcess->SetScintillationYieldFactor(1.);
  theScintillationProcess->SetTrackSecondariesFirst(true);

  // Use Birks Correction in the Scintillation process

  G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
  theScintillationProcess->AddSaturation(emSaturation);

  //G4OpticalSurfaceModel themodel = unified;
  //theBoundaryProcess->SetModel(themodel);

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    // if (theCerenkovProcess->IsApplicable(*particle)) {
    //   pmanager->AddProcess(theCerenkovProcess);
    //   pmanager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
    // }
    if (theScintillationProcess->IsApplicable(*particle)) {
      pmanager->AddProcess(theScintillationProcess);
      pmanager->SetProcessOrderingToLast(theScintillationProcess, idxAtRest);
      pmanager->SetProcessOrderingToLast(theScintillationProcess, idxPostStep);
    }
    if (particleName == "opticalphoton") {
      G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
      pmanager->AddDiscreteProcess(theAbsorptionProcess);
      pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
      pmanager->AddDiscreteProcess(theMieHGScatteringProcess);
      pmanager->AddDiscreteProcess(theBoundaryProcess);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::SetVerbose(G4int verbose)
{
  //theCerenkovProcess->SetVerboseLevel(verbose);
  theScintillationProcess->SetVerboseLevel(verbose);
  theAbsorptionProcess->SetVerboseLevel(verbose);
  theRayleighScatteringProcess->SetVerboseLevel(verbose);
  theMieHGScatteringProcess->SetVerboseLevel(verbose);
  theBoundaryProcess->SetVerboseLevel(verbose);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::SetNbOfPhotonsCerenkov(G4int MaxNumber)
{  
  //theCerenkovProcess->SetMaxNumPhotonsPerStep(MaxNumber);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06PhysicsList::SetCuts()
{
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
  //   the default cut value for all particle types
  // 
  SetCutsWithDefault();
  
  if (verboseLevel>0) DumpCutValuesTable();   
}






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
