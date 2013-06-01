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
// $Id: ExN06RunAction.cc,v 1.10 2006-06-29 17:54:31 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Make this appear first!


#include "ExN06RunAction.hh"
#include "ExN06PMTHit.hh"

#include "G4Run.hh"
#include "G4Timer.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Track.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "G4TrackStatus.hh"
#include "G4Step.hh"
#include "G4Types.hh"
#include "G4SDManager.hh"

#include <sstream>
#include <iostream>
#include <time.h>
#include <cstring>
#include <cstdlib>
#include <string.h>

#if defined (G4ANALYSIS_USE_ROOT)

#include "TROOT.h"
#include "TApplication.h"
#include "TSystem.h"
#include "TH1.h"
#include "TH2.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TStopwatch.h"
#include "TTree.h"
#include "TRandom.h"

#endif /* defined (G4ANALYSIS_USE_ROOT) */

#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN06RunAction::ExN06RunAction()
{
  // timer = new G4Timer;

#if defined (G4ANALYSIS_USE_ROOT)
  
  if (gSystem) gSystem->ProcessEvents();
  
  //sidssdtree = (TTree *)0; // sidssd out tree

  hEnergyDeposit = (TH1D*)0;

#endif /* defined (G4ANALYSIS_USE_ROOT) */
  
  //OnceAWhileDoIt();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN06RunAction::~ExN06RunAction()
{
  //delete timer;

#if defined (G4ANALYSIS_USE_ROOT)
  
  if (gSystem) gSystem->ProcessEvents();
  
#endif /* defined (G4ANALYSIS_USE_ROOT) */

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void ExN06RunAction::BeginOfRunAction(const G4Run* aRun, G4int rank)
void ExN06RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl; 
  //timer->Start();

  eventcounter = 0;

#if defined (G4ANALYSIS_USE_ROOT)

  //stringstream fil;
  //fil << dirname << filename << "_" << rank << ".root";
  //G4String filenam = fil.str();
  //file1 = new TFile(filenam.c_str(),"RECREATE");

  filecount++;

  timer = new TStopwatch();

  if(hEnergyDeposit) hEnergyDeposit->Reset();
  else {
    hEnergyDeposit = new TH1D("hEnergyDeposit","hEnergyDeposit",4000,0,35000);
  }

  eventtimer = new Stopwatch();

  //OnceAWhileDoIt(true); // do it now

#endif /* defined (G4ANALYSIS_USE_ROOT) */



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN06RunAction::EndOfRunAction(const G4Run* aRun)
{   
  //timer->Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent() 
         << " " <</* *timer << */G4endl;

#if defined (G4ANALYSIS_USE_ROOT)
  //if (gSystem) gSystem->ProcessEvents();

  //stringstream fil;
  //fil << dirname << filename << "_" << rank << ".root";
  //G4String filenam = fil.str();
  //file1=gROOT->GetFile(filenam.c_str());

  //file1->cd();
  //hEnergyDeposit->Write();

//file1->Write();
//  file1->Close();
  timer->Stop();
  timer->Print();

#endif /* defined (G4ANALYSIS_USE_ROOT) */
  
  //OnceAWhileDoIt(true); // do it now

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
