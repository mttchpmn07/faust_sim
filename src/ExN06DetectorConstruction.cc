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
// $Id: ExN06DetectorConstruction.cc,v 1.9 2006-06-29 17:47:19 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#include "ExN06DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include <math.h>

//  Create CsI calorimeter 
#include "CsI_SD.hh"
#include "Si_SD.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"     
#include "G4RunManager.hh"
#include "G4VisAttributes.hh"
#include "G4VSolid.hh"
#include "G4UnionSolid.hh"
//  Defining sensitive detector
#include "G4SDManager.hh"
#include <sstream>
#include <iostream>

using namespace std;


ExN06DetectorConstruction::ExN06DetectorConstruction(){
    
    enclosure_x = enclosure_y = enclosure_z = 90.*cm;
    // scintillator dimensions 
//    CsI_z = CsI_y = 2.*cm;
   // CsI_x = 2.*cm;
       
    // Detector dimensions
    Si_z  = Si_y  = 2.*cm;
    Si_x  = 0.03*cm;
    //Light guide
    long_lgx = long_lgy = 2.1*cm;
    short_lgx = short_lgy = 1.*cm;
    lgz = 2.12*cm;
}

ExN06DetectorConstruction::~ExN06DetectorConstruction()
{
}

G4VPhysicalVolume* ExN06DetectorConstruction::Construct()
{

  //------------------------------------------------------ materials

  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;
    G4int nelements;
    
    //Vacuum
    G4Material* Vacuum = new G4Material("Vacuum",z=1.,a=1.01*g/mole,density=universe_mean_density,kStateGas,0.1*kelvin,1.e-19*pascal); 
    
    // Silicon
    G4Material* Si = new G4Material("Silicon", z=14., a=28.0855*g/mole, density= 2.33*g/cm3);
    
    // CsI
    G4Element* I = new G4Element("Iodine", "I", z=53., a=126.9044*g/mole);
    G4Element* Cs= new G4Element("Caesium", "Cs", z=55., a=132.9054*g/mole);
    G4Material* CsI = new G4Material("CsI", density = 4.51*g/cm3, nelements=2);
    CsI->AddElement(Cs, 1);
    CsI->AddElement(I, 1);
    //Lucite
    G4bool isotopes = false;
    G4Material* PMMA = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLEXIGLASS", isotopes);
    
    
  //------------------------------------------------------ volumes

    
    //  !-------------- The enclosure -------------------!
    
    G4Box* enclosure_box = new G4Box("World",1.5*enclosure_x,enclosure_y,enclosure_z);
    
    G4LogicalVolume* enclosure_log = new G4LogicalVolume(enclosure_box, Vacuum,"World",0,0,0);
    
    G4VPhysicalVolume* enclosure_phys = new G4PVPlacement(0, G4ThreeVector(),enclosure_log, "World", 0, false, 0);


    
    //  !---------------------------------------------------------!
    //  !--------------------- Repetition ------------------------!
    //   !---------------------------------------------------------!
    
    //!-------------- sensitive detector ------------!
    
    G4VSensitiveDetector* detector = new CsI_SD("CsI"); 
    // Get pointer to detector manager
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    // Register detector with manager
    SDman->AddNewDetector(detector);
    
    // Create a new SiliconMonitor sensitive detector
    G4VSensitiveDetector* monitor = new Si_SD("Si"); 
    // Register detector with manager
    G4SDManager::GetSDMpointer()->AddNewDetector(monitor);

    
    
    /* G4SDManager* SDman = G4SDManager::GetSDMpointer(); 
    
    G4String ScintName = "ThickScintSD";
    ThickScintSD* thickScintSD = new ThickScintSD(ScintName);
    SDman->AddNewDetector(thickScintSD);
    
    
    ScintName = "ThinScintSD";
    ThinScintSD* thinScintSD = new ThinScintSD(ScintName);
    SDman->AddNewDetector(thinScintSD);
    */

       
    
    //!------------- visuals -------------------!
    G4VisAttributes* BoxVisAtt = new G4VisAttributes(G4Colour(0.,1.0,.0));
    G4VisAttributes* GuideVisAtt = new G4VisAttributes(G4Colour(1.0,.0, .0));
    G4VisAttributes* SiVisAtt   = new G4VisAttributes(G4Colour(0.2,0.,0.8));
    SiVisAtt->SetForceSolid(true);
    
    
    //!------------ surfaces-------------------!
   /* G4OpticalSurface* OpWaterSurface = new G4OpticalSurface("WaterSurface");
    OpWaterSurface->SetType(dielectric_metal);
    OpWaterSurface->SetFinish(polished);
    OpWaterSurface->SetModel(glisur);
    
    G4OpticalSurface* OpGuideSurface = new G4OpticalSurface("GuideSurface");
    OpGuideSurface->SetType(dielectric_dielectric);
    OpGuideSurface->SetFinish(polished);
    OpGuideSurface->SetModel(glisur);
    
    G4OpticalSurface* OpAirSurface = new G4OpticalSurface("AirSurface");
    OpAirSurface->SetType(dielectric_metal);
    OpAirSurface->SetFinish(polished);
    OpAirSurface->SetModel(glisur);
    */
    
    //!-------------------Volumes----------------!
    G4Box* Si_box[68];              //Si
    G4LogicalVolume* Si_log[68];
    G4VPhysicalVolume* Si_phys[68];
    G4RotationMatrix* rotmSI[68];
    
    G4Trd* scintillator_box[68];        // CsI
    G4LogicalVolume* scintillator_log[68];
    G4VPhysicalVolume* scintillator_phys[68];
    G4RotationMatrix* CsIrotm[68];
    
    G4Trd* light_trd[68];       // light guide
    G4LogicalVolume* light_log[68];
    G4VPhysicalVolume* light_phys[68];
    G4RotationMatrix* lightrotm[68];
    
    
    
    
    
    string initialstring, numberstring, resultstring;
    stringstream ss;
    
    initialstring = "scintillator";
    
    //  !--------- coordinates ---------!
    
    // X_Y_Z in notes, here Z_Y_X, Z on paper is X in code

    float Z[]   = { 2.1385, 0, -2.1385, -2.1415, -2.1385, 0, 2.1385, 2.1415, 
        
        3.2096, 1.0720, -1.0720, -3.2096, -3.2287, -3.2287, -3.2096, -1.0720, 1.0720, 3.2096, 3.2287, 3.2287,
        
        4.2242, 2.1324, 0, -2.1324, -4.2242, -4.3065, -4.3273, -4.3065, -4.2242, -2.1324, 0, 2.1324, 4.2242, 4.3065, 4.3273, 4.3065,
        
        
        4.2672, 2.1586, 0, -2.1586, -4.2672, -4.4213, -4.4731, -4.4213, -4.2672, -2.1586, 0, 2.1586, 4.2672, 4.4213, 4.4731, 4.4213,
        
        
        4.284, 2.1766, 0, -2.1766, -4.284, - 4.7228, -4.7362, -4.7228, -4.284, -2.1766, 0, 2.1766, 4.2840, 4.7228, 4.7362, 4.7228
        
    };
    
    
    float Y[] = { 2.1385, 2.1415, 2.1385, 0, -2.1385, -2.1415, -2.1385, 0,
        
        3.2096, 3.2287, 3.2287, 3.2096, 1.0720, -1.0720,-3.2096, -3.2287, -3.2287,  -3.2096, -1.0720, 1.0720,
        
        4.2242, 4.3065, 4.3273, 4.3065, 4.2242, 2.1324, 0, -2.1324, -4.2242, -4.3065, -4.3273, -4.3065, -4.2242, -2.1324, 0, 2.1324,
        
        4.2672, 4.4213, 4.4731, 4.4213, 4.2672, 2.1586, 0 , -2.1586, -4.2672, - 4.4213, -4.4731, -4.4213, -4.2672, -2.1586, 0, 2.1586,
        
        4.2840, 4.6228, 4.7362, 4.6228, 4.284, 2.06, 0, -2.06, -4.284, -4.6228, -4.7362, -4.6228, -4.284, -2.06, 0, 2.06
        
        
    };
    
    float X[] = { 39.8855, 39.889,39.8855, 39.889,39.8855, 39.889,39.8855, 39.889, 
       
        27.4907, 27.6544, 27.6544, 27.4907, 27.6544, 27.6544, 27.4907, 27.6544, 27.6544, 27.4907, 27.6544, 27.6544,
        
        20.9138,  21.2208, 21.3234, 21.2208,   20.9138,  21.2208, 21.3234, 21.2208,   20.9138,  21.2208, 21.3234, 21.2208,   20.9138,  21.2208, 21.3234, 21.2208,
        
        12.8849, 13.3503, 13.5067, 13.3503, 12.8849, 13.3503, 13.5067, 13.3503, 12.8849, 13.3503, 13.5067, 13.3503, 12.8849, 13.3503, 13.5067, 13.3503,
        
        7.9203, 8.5631, 8.7751, 8.5631, 7.9203, 8.5631, 8.7751, 8.5631, 7.9203, 8.5631, 8.7751, 8.5631, 7.9203, 8.5631, 8.7751, 8.5631   
        
    };
        
    
    
    float CZ[] = { 2.2285, 0, -2.2285, -2.1915, -2.2285, 0, 2.2285, 2.1915, 
        
        3.3996, 1.1620, -1.1620, -3.3996, -3.387, -3.387, -3.3996, -1.1620, 1.1620, 3.3996, 3.387, 3.387,
        
        4.6242, 2.3324, 0, -2.3324, -4.6242, -4.6865, -4.7573, -4.6865, -4.6242, -2.3324, 0, 2.3324, 4.6242, 4.6865, 4.7573, 4.6865,
        
        
        4.9672, 2.5586, 0, -2.5586, -4.9672, -4.9213, -4.9731, -4.9213, -4.9672, -2.5586, 0, 2.5586, 4.9672, 4.9213, 4.9731, 4.9213,
        
        
        
        4.960, 2.706, 0, -2.706, -4.960, - 5.618, -5.5362, -5.618, -4.960, -2.706, 0, 2.706, 4.960, 5.618, 5.5362, 5.618
        
        
        
    };
    
    float CY[] = { 2.2085, 2.1915, 2.2085, 0, -2.2085, -2.1915, -2.2085, 0,
        
        3.3296, 3.387, 3.387, 3.3296, 1.1020, -1.1020,-3.3296, -3.387, -3.387,  -3.3296, -1.1020, 1.1020,
        
        4.6242, 4.6865, 4.7573, 4.6865, 4.6242, 2.3324, 0, -2.3324, -4.6242, -4.6865, -4.7573, -4.6865, -4.6242, -2.3324, 0, 2.3324,
        
        4.9672, 4.9213, 4.9731, 4.9213, 4.9672, 2.5586, 0 , -2.5586, -4.9672, - 4.9213, -4.931, -4.9213, -4.9672, -2.5586, 0, 2.5586,
        
                
        4.960, 5.218, 5.5362, 5.218, 4.960, 2.316, 0, -2.316, -4.960, -5.218, -5.7362, -5.218, -4.960, -2.316, 0, 2.316
        
    };
    
    
    float CX[] = { 39.9855, 39.989,39.9855, 39.989,39.9855, 39.989,39.9855, 39.989, 
        
        27.5507, 27.7144, 27.7144, 27.5507, 27.7144, 27.7144, 27.5507, 27.7144, 27.7144, 27.5507, 27.7144, 27.7144,
        
        21.3138,  21.6208, 21.7234, 21.6208,   21.3138,  21.6208, 21.7234, 21.6208,   21.3138,  21.6208, 21.7234, 21.6208,   21.3138,  21.6208, 21.7234, 21.6208,
        
        13.1849, 13.7503, 13.9067, 13.7503, 13.1849, 13.7503, 13.9067, 13.7503, 13.1849, 13.7503, 13.9067, 13.7503, 13.1849, 13.7503, 13.9067, 13.7503,
        
        7.8203, 8.6631, 8.8751, 8.6631, 7.8203, 8.6631, 8.8751, 8.6631, 7.8203, 8.6631, 8.8751, 8.6631, 7.8203, 8.6631, 8.8751, 8.6631
        
    };
    
    
   float CsIx[] = {2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,
        2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,
        2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,
        2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,2.99974, 2.99974,
        2.2606,2.2606,2.2606,2.2606,2.2606,2.2606,2.2606,2.2606,2.2606,2.2606,2.2606,2.2606,2.2606,2.2606,2.2606,2.2606};
    
    
    
    float long_CsIy[] = {2.16662,2.16662,2.16662,2.16662,2.16662,2.16662,2.16662,2.16662,
        2.24,2.24,2.24,2.24,2.24,2.24,2.24,2.24,2.24,2.24,2.24,2.24,
        2.30,2.30,2.30,2.30,2.30,2.30,2.30,2.30,2.30,2.30,2.30,2.30,2.30,2.30,2.30,2.30,
        2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,
        2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4};
    
    
    float long_CsIz[] = {2.245,2.245,2.245,2.245,2.245,2.245,2.245,2.245,
        2.319, 2.319, 2.319, 2.319, 2.319, 2.319, 2.319, 2.319, 2.319, 2.319, 2.319, 2.319,
        2.38,2.38,2.38,2.38,2.38,2.38,2.38,2.38,2.38,2.38,2.38,2.38,2.38,2.38,2.38, 2.38,
        2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,2.469,
        2.441,2.441,2.441,2.441,2.441,2.441,2.441,2.441,2.441,2.441,2.441,2.441,2.441,2.441,2.441, 2.441}; 
    

    float short_CsIy[] = {2.0168,2.0168,2.0168,2.0168,2.0168,2.0168,2.0168,2.0168,
        2.024,2.024,2.024,2.024,2.024,2.024,2.024,2.024,2.024,2.024,2.024,2.024,
        2.029,2.029,2.029,2.029,2.029,2.029,2.029,2.029,2.029,2.029,2.029,2.029,2.029,2.029,2.029,2.029,
        2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,
        1.966,1.966,1.966,1.966,1.966,1.966,1.966,1.966,1.966,1.966,1.966,1.966,1.966,1.966,1.966,1.966};
        
        float short_CsIz[] = {2.095,2.095,2.095,2.095,2.095,2.095,2.095,2.095,
            2.100, 2.100, 2.100, 2.100, 2.100, 2.100, 2.100, 2.100, 2.100, 2.100, 2.100, 2.100,
            2.110,2.110,2.110,2.110,2.110,2.110,2.110,2.110,2.110,2.110,2.110,2.110,2.110,2.110,2.110,2.110,
            2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047,2.047, 
            2.004,2.004,2.004,2.004,2.004,2.004,2.004,2.004,2.004,2.004,2.004,2.004,2.004,2.004,2.004, 2.004}; 
    

    
    //second in wrl file {4.611
    
    float zrot[]={1.730, 2.247, 1.730, 0, -1.730, -2.247, -1.730, 0,         
        
        3.878, 4.395, 4.395, 3.878, 1, -1, -3.878, -4.395, -4.395, -3.878,   -1, 1,
        
      
        
        10.304, 7.255, 10.639, 7.255, 10.304, 7.255 , 0, -7.255, -10.304, -7.255, -10.639, -7.255, -10.304, -7.255,0, 7.255,
        
        
        20.5295, 11.597, 17.477, 11.597, 20.5295, 9.015 , 0, -9.015, -20.5295, -11.597, -17.477, -11.597, -20.5295, -9.015, 0, 9.015,
        
        
        31.421, 23.762, 34.89, 23.762, 31.421, 13.762 , 0, -13.762, -31.421, -23.762, -34.89, -23.762, -31.421, -13.762, 0, 13.762  
    };
    
    
    //third in wrl file, and slowly second (yrot on paper) -10.304,  -21.552
    float yrot[]={-3.547, 0, 3.547, 2.247, 3.547, 0, -3.547, -2.247,          
        
        -8.554, -3.64, 3.64, 8.554, 6.390, 6.390, 8.554, 3.64, -3.64, -8.554, -6.390,  -6.390,
       
        
        -10.304 , -7.255, 0 , 7.255, 10.304, 7.255, 10.639, 7.255, 10.304, 7.255, 0 , -7.255, -10.304, -7.255, -10.639, -7.255, 
        
        
        -24.250 , -14.62, 0 , 9.015, 24.250, 14.62, 20.639, 14.62, 24.250, 9.015, 0 , -9.015, -24.250, -14.62, -20.639, -14.62, 
        
        
        -35.912 , -21.548, 0 , 21.548, 31.912, 36.548, 34.89, 36.548, 35.912, 21.548, 0 , -21.548, -35.912, -36.548, -34.89, -36.548
        
    };
    
 
        
    
    
    int n=0;
    
    while (n<68) {
        
        //w[n] = r[n]*sin(theta[n]*0.01745)*cos(phi[n]*0.01745);
        //  y[n] = r[n]*sin(theta[n]*0.01745)*sin(phi[n]*0.01745);
        // x[n] = r[n]*cos(theta[n]*0.01745);
        
        
        ss<< initialstring << n;
        resultstring = ss.str();
       
    
        rotmSI[n] = new G4RotationMatrix;
        rotmSI[n]->rotateZ(-zrot[n]*0.01745);
        rotmSI[n]->rotateY(-yrot[n]*0.01745);
      
        
        lightrotm[n] = new G4RotationMatrix;
        lightrotm[n]->rotateZ(-zrot[n]*0.01745);
        lightrotm[n]->rotateY(-yrot[n]*0.01745-0*0.01745);
        
        CsIrotm[n] = new G4RotationMatrix;
        CsIrotm[n]->rotateZ(-zrot[n]*0.01745);
        CsIrotm[n]->rotateY(-yrot[n]*0.01745+90*0.01745);
       
        
             //  !------------------- Si --------------------!
        //  !-------------------------------------------!
        Si_box[n] = new G4Box("Si", Si_x/2., Si_y/2., Si_z/2.);
        
        Si_log[n] = new G4LogicalVolume(Si_box[n], Si, "Si",0,0,0);
        
        Si_phys[n] = new G4PVPlacement(rotmSI[n], G4ThreeVector((X[n])*cm,(Y[n])*cm,(Z[n])*cm), Si_log[n], "Si", enclosure_log, false, n);
        
        
       // Si_log[n]->SetSensitiveDetector(thinScintSD);
        Si_log[n]->SetVisAttributes(SiVisAtt);
        // Attach detector to volume defining calorimeter cells
        Si_log[n]->SetSensitiveDetector(monitor);

        //  !------------------- CsI -------------------!
        //  !-------------------------------------------!
        scintillator_box[n] = new G4Trd("Scintillator",long_CsIz[n]/2.*cm, short_CsIz[n]/2.*cm, long_CsIy[n]/2.*cm, short_CsIy[n]/2.*cm, CsIx[n]/2.*cm);
        
        scintillator_log[n] = new G4LogicalVolume(scintillator_box[n],CsI,"Scintillator",0,0,0);
        
        scintillator_phys[n] = new G4PVPlacement(CsIrotm[n], G4ThreeVector((CsIx[n]/2.+CX[n])*cm, (CY[n])*cm,(CZ[n])*cm),scintillator_log[n],"Scintillator", enclosure_log, false, n);
               
       // scintillator_log[n]->SetSensitiveDetector(thickScintSD);
        
        scintillator_log[n]->SetVisAttributes(BoxVisAtt);
        
        // Attach detector to volume defining calorimeter cells
        scintillator_log[n]->SetSensitiveDetector(detector);
        
        
       /* //  !----------------- Light Guide --------------!
        //  !--------------------------------------------!
        light_trd[n] = new G4Trd("LightGuide",long_lgx/2., short_lgx/2., long_lgy/2., short_lgy/2., lgz/2.);
        
        light_log[n] = new G4LogicalVolume(light_trd[n], PMMA, "LightGuide", 0,0,0);
        
            
        light_phys[n] = new G4PVPlacement(lightrotm[n], G4ThreeVector((+0.65+CsIx[n]+1.06+X[n])*cm, (Y[n])*cm,(Z[n])*cm), light_log[n], "LightGuide",enclosure_log, false, 0);
        
        
        light_log[n]->SetVisAttributes(GuideVisAtt);
        
     */
        n++;
    }
    
    //  !-----------------------------------------------------------!
    //  !-------------------------end repeat -----------------------!
    //  !-----------------------------------------------------------!

    
    
    return enclosure_phys;
}

