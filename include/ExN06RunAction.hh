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
// $Id: ExN06RunAction.hh,v 1.9 2006-06-29 17:54:10 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef ExN06RunAction_h
#define ExN06RunAction_h 1

class G4VPhysicalVolume;
class G4Event;
class G4Run;
class G4Track;
class G4Step;

class ExN06DetectorConstruction;

#include "globals.hh"
#include "G4UserRunAction.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "G4ThreeVector.hh"
#include "G4TrackStatus.hh"
#include "G4Types.hh"
#include <time.h>
//#include <vector>
#include <iostream>
#include <cctype>
using namespace std;

#if defined (G4UI_USE_ROOT) || defined (G4UI_BUILD_ROOT_SESSION)
#if !defined (G4ANALYSIS_USE_ROOT)
#define G4ANALYSIS_USE_ROOT 1
#endif /* !defined (G4ANALYSIS_USE_ROOT) */
#endif /* defined (G4UI_USE_ROOT) || defined (G4UI_BUILD_ROOT_SESSION) */

#if defined (G4ANALYSIS_USE_ROOT)

class TH1D;
class TH2D;
class TFile;
class TNtuple;
class TStopwatch;
class TTree;

#endif /* defined (G4ANALYSIS_USE_ROOT) */



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN06RunAction : public G4UserRunAction
{
  public:
    ExN06RunAction();
   ~ExN06RunAction();

  public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

private:
  //G4Timer* timer;

  G4int filecount;
  G4int eventcounter;

  G4double edep;
						
  G4String filename;

#if defined (G4ANALYSIS_USE_ROOT)
  
  TFile *file1; // test file
  TFile *rfile1; //retrieve file

  TStopwatch *timer;
  TStopwatch *eventtimmer;

  TH1D *hEnergyDeposit;

#endif /* defined (G4ANALYSIS_USE_ROOT) */

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*ExN06RunAction_h*/
