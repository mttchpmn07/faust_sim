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
// $Id: ExN06DetectorConstruction.hh,v 1.6 2006-06-29 17:47:13 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#ifndef ExN06DetectorConstruction_H
#define ExN06DetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"

class ExN06DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    ExN06DetectorConstruction();
    ~ExN06DetectorConstruction();

    G4VPhysicalVolume* Construct();

  private:
    
    G4double enclosure_x;
    G4double enclosure_y;
    G4double enclosure_z;
    
    G4double CsI_x;
    G4double CsI_y;
    G4double CsI_z;
    
    G4double Si_x;
    G4double Si_y;
    G4double Si_z;
    
    G4double lgz;
    G4double long_lgx;
    G4double long_lgy;
    G4double short_lgx;
    G4double short_lgy;
    
    G4double house_x;


};

#endif

