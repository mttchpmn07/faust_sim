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
// $Id: ExN06DetectorConstruction.cc,v 1.18 2010-10-23 19:27:38 gum Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN06DetectorConstruction.hh"
//#include "PMT_SD.hh"
#include "ExN06PMTSD.hh"
//#include "ScintSD.hh"
#include "ThickScintSD.hh"
#include "ThinScintSD.hh"


#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4MaterialTable.hh"

#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"

#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"

#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4VSolid.hh"
#include "G4UnionSolid.hh"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

#include "G4VisAttributes.hh"

#include "G4SDManager.hh" 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN06DetectorConstruction::ExN06DetectorConstruction()
{
  //-----------------------------------------------------------------------------------------------------------------
  //
  //Dimensions
  //
  //----------------------------------------------------------------------------------------------------------------- 
  expHall_x = expHall_y = expHall_z = 20.0*cm;
  tank_x = 3.0*cm;
  tank_y    = tank_z    =  2.0*cm;
  bubble_x  = 0.00001*cm;
  bubble_y  = bubble_z  =  2.0*cm;
  guide_z = 2.12*cm;
  guideLong_x = guideLong_y = 2.0*cm;
  guideShort_x = guideShort_y = 1.0*cm;
  house_x = 5.12*cm;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN06DetectorConstruction::~ExN06DetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* ExN06DetectorConstruction::Construct()
{
  //------------------------------------------------------------------------------------------------------------
  //  
  //Materials
  //
  //------------------------------------------------------------------------------------------------------------
  
  G4double a, z, density;
  G4int nelements;

  //Aluminum
  //
  G4Material* Al = new G4Material("Aluminum", z=13., a=26.98*g/mole, density=2.7*g/cm3);

  // Air
  // 
  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

  G4Material* Air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  Air->AddElement(N, 70.*perCent);
  Air->AddElement(O, 30.*perCent);

  // Water
  // 
  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);

  G4Material* Water = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
  Water->AddElement(H, 2);
  Water->AddElement(O, 1);

  //Vacuum
  //
  G4Material* Vacuum = new G4Material("Vacuum",z=1.,a=1.01*g/mole,
			  density=universe_mean_density,kStateGas,0.1*kelvin,
			  1.e-19*pascal); 

  //BC408
  //
  G4Element* C = new G4Element("Carbon", "C", z=6., a= 12.011*g/mole);

  G4Material* BC408 = new G4Material("BC408", density=1.302*g/cm3, nelements=2);
  BC408->AddElement(H, 11);
  BC408->AddElement(C, 10);

 //BC418 Plastic
  //
  G4Material* BC418 = new G4Material("BC418", density=1.302*g/cm3, nelements=2);
  BC418->AddElement(H, 11);
  BC418->AddElement(C, 10);


  //Lucite
  //
  G4bool isotopes = false;
  G4Material* PMMA = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLEXIGLASS", isotopes);

  //Glass
  //
  G4Material* Glass = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pyrex_Glass");

  //Bi Alkeli (for Photocathode)
  //
  G4Element* Rb = new G4Element("Rubidium", "Rb", z=37.,  a= 85.4678*g/mole);
  G4Element* Cs = new G4Element("Caesium", "Cs", z=55., a=132.905*g/mole);
  G4Element* Sb = new G4Element("Antimony", "Sb", z=51., a=121.760*g/mole);

  G4Material* BiAlkali = new G4Material("BiAlkali", density=3.0*g/cm3, nelements=3);
  BiAlkali->AddElement(Rb, 2);
  BiAlkali->AddElement(Cs, 1);
  BiAlkali->AddElement(Sb, 1);

  
//------------------------------------------------------------------------------------------------------
//  
//Generate & Add Material Properties Table 
//
//------------------------------------------------------------------------------------------------------

  const G4int nEntries = /*32*/ 6;

  G4double PhotonEnergy[nEntries] =
    { 100*keV, 1080*keV, 2060*keV, 3040*keV, 4020*keV, 5000*keV};

  //
  //Vacuum
  //
  G4double Vacuum_Energy[3]={2.0*eV,7.0*eV,7.14*eV};
  G4double Vacuum_RIND[3]={1.,1.,1.};  
  G4MaterialPropertiesTable *Vacuum_mt = new G4MaterialPropertiesTable();
  Vacuum_mt->AddProperty("RINDEX", Vacuum_Energy, Vacuum_RIND,3);
  Vacuum->SetMaterialPropertiesTable(Vacuum_mt);

//
// BC408 (Water originally)
//	      
  G4double RefractiveIndex1[nEntries] =
    {1.58, 1.58, 1.58, 1.58, 1.58, 1.58};

  G4double Absorption1[nEntries] =
    {210*mm, 210*mm, 210*mm, 210*mm, 210*mm, 210*mm };
    // {0.*m, 0.*m, 0.*m, 0.*m, 0.*m, 0.*m} ;

  G4double ScintilFast[nEntries] =
    {2.1, 2.1, 2.1, 2.1, 2.1, 2.1 };

  G4double ScintilSlow[nEntries] =
    { 14.2, 14.2, 14.2, 14.2, 14.2, 14.2 };

  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();

  myMPT1->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex1,nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("ABSLENGTH",    PhotonEnergy, Absorption1,     nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("FASTCOMPONENT",PhotonEnergy, ScintilFast,     nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("SLOWCOMPONENT",PhotonEnergy, ScintilSlow,     nEntries)
        ->SetSpline(true);
  
  myMPT1->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 2.1*ns);
  myMPT1->AddConstProperty("SLOWTIMECONSTANT", 14.2*ns);
  myMPT1->AddConstProperty("YIELDRATIO",0.8);

  const G4int NUMENTRIES_water = 6;

  G4double ENERGY_BC418/*water*/[NUMENTRIES_water] = {
    100*keV, 2080*keV, 4060*keV, 6040*keV, 8020*keV, 10000*keV  };

  //assume 100 times larger than the rayleigh scattering for now.
  // G4double MIE_water[NUMENTRIES_water] = {
  //    167024.4*m, 158726.7*m, 150742  *m,
  //    143062.5*m, 135680.2*m, 128587.4*m,
  //    121776.3*m, 115239.5*m, 108969.5*m,
  //    102958.8*m, 97200.35*m, 91686.86*m,
  //    86411.33*m, 81366.79*m, 76546.42*m,
  //    71943.46*m, 67551.29*m, 63363.36*m,
  //    59373.25*m, 55574.61*m, 51961.24*m,
  //    48527.00*m, 45265.87*m, 42171.94*m,
  //    39239.39*m, 36462.50*m, 33835.68*m,
  //    31353.41*m, 29010.30*m, 26801.03*m,
  //    24720.42*m, 22763.36*m, 20924.88*m,
  //    19200.07*m, 17584.16*m, 16072.45*m,
  //    14660.38*m, 13343.46*m, 12117.33*m,
  //    10977.70*m, 9920.416*m, 8941.407*m,
  //    8036.711*m, 7202.470*m, 6434.927*m,
  //    5730.429*m, 5085.425*m, 4496.467*m,
  //    3960.210*m, 3473.413*m, 3032.937*m,
  //    2635.746*m, 2278.907*m, 1959.588*m,
  //    1675.064*m, 1422.710*m, 1200.004*m,
  //    1004.528*m, 833.9666*m, 686.1063*m
  // 	       */};

  // // gforward, gbackward, forward backward ratio
  // G4double MIE_water_const[3]={0.99,0.99,0.8};

  // myMPT1->AddProperty("MIEHG",ENERGY_BC418,MIE_water,NUMENTRIES_water)
  //       ->SetSpline(true);
  // myMPT1->AddConstProperty("MIEHG_FORWARD",MIE_water_const[0]);
  // myMPT1->AddConstProperty("MIEHG_BACKWARD",MIE_water_const[1]);
  // myMPT1->AddConstProperty("MIEHG_FORWARD_RATIO",MIE_water_const[2]);

  BC408->SetMaterialPropertiesTable(myMPT1);

  /**********for now, add BC408 Properties to Lucite****************/
  PMMA->SetMaterialPropertiesTable(myMPT1);
  

  // // Set the Birks Constant for the Water scintillator

  // Water->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

//
// Air
//
  G4double RefractiveIndex2[nEntries] =
    {1.58, 1.58, 1.58, 1.58, 1.58, 1.58 };

  G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
 
  G4double Absorption2[nEntries] =
    {100*cm, 100*cm, 100*cm, 100*cm, 100*cm, 100*cm};
  // {0.*cm, 0.*cm, 0.*cm, 0.*cm, 0.*cm, 0.*cm};

  G4double ScintilFast2[nEntries] =
    {0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };

  G4double ScintilSlow2[nEntries] =
    { 1.4, 1.4, 1.4, 1.4, 1.4, 1.4  };

  myMPT2->AddProperty("RINDEX",ENERGY_BC418/*PhotonEnergy*/, RefractiveIndex2, nEntries)
        ->SetSpline(true);
  myMPT2->AddProperty("ABSLENGTH", ENERGY_BC418/*PhotonEnergy*/, Absorption2,     nEntries)
        ->SetSpline(true);
  myMPT2->AddProperty("FASTCOMPONENT", ENERGY_BC418/*PhotonEnergy*/, ScintilFast2,     nEntries)
        ->SetSpline(true);
  myMPT2->AddProperty("SLOWCOMPONENT", ENERGY_BC418 /*PhotonEnergy*/, ScintilSlow2,     nEntries)
        ->SetSpline(true);
  
  myMPT2->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  myMPT2->AddConstProperty("RESOLUTIONSCALE",1.0);
  myMPT2->AddConstProperty("FASTTIMECONSTANT", 0.5*ns);
  myMPT2->AddConstProperty("SLOWTIMECONSTANT", 1.4*ns);
  myMPT2->AddConstProperty("YIELDRATIO",0.8);

  
  BC418->SetMaterialPropertiesTable(myMPT2);

  G4MaterialPropertiesTable* myMPT3 = new G4MaterialPropertiesTable();
 
  G4double RefractiveIndex3[nEntries] =
    {1.58, 1.58, 1.58, 1.58, 1.58, 1.58};

  myMPT3->AddProperty("RINDEX",ENERGY_BC418/*PhotonEnergy*/, RefractiveIndex3, nEntries)
        ->SetSpline(true);
  
  Glass->SetMaterialPropertiesTable(myMPT3);

//-------------------------------------------------------------------------------------------------------
//
//Defining Volumes
//
//-------------------------------------------------------------------------------------------------------

// The experimental Hall
//
  G4Box* expHall_box = new G4Box("World",expHall_x,expHall_y,expHall_z);

  G4LogicalVolume* expHall_log
    = new G4LogicalVolume(expHall_box,Vacuum,"World",0,0,0);

  G4VPhysicalVolume* expHall_phys
    = new G4PVPlacement(0,
			G4ThreeVector(),
			expHall_log,
			"World",
			0,
			false,
			0);

  // The Water Tank
  //	
  G4Box* waterTank_box = new G4Box("Tank",tank_x/2.,tank_y/2.,tank_z/2.);

  G4LogicalVolume* waterTank_log
    = new G4LogicalVolume(waterTank_box,BC408,"Tank",0,0,0);

  G4VPhysicalVolume* waterTank_phys
    = new G4PVPlacement(0,
			G4ThreeVector(0,0,0),
			waterTank_log,
			"Tank",
    			expHall_log,
			false,
			0);
  
 
  // BC418(The Air Bubble)
  //   
  G4Box* bubbleAir_box = new G4Box("Bubble",bubble_x/2.,bubble_y/2.,bubble_z/2.);
  
  G4LogicalVolume* bubbleAir_log
    = new G4LogicalVolume(bubbleAir_box,BC418,"Bubble",0,0,0);

  G4VPhysicalVolume* bubbleAir_phys =
    new G4PVPlacement(0,
		      G4ThreeVector(-/*3.3*/1.65*cm,0,0),
		      bubbleAir_log,
		      "Bubble",
		      expHall_log,
		      false,
		      0);

//Light Guide
//
 
 G4Trd* light_trd = new G4Trd("LightGuide",guideLong_x/2., guideShort_x/2., guideLong_y/2., guideShort_y/2., guide_z/2.);
 
 G4LogicalVolume* light_log
   = new G4LogicalVolume(light_trd, PMMA, "LightGuide", 0,0,0);

 G4RotationMatrix *rotm = new G4RotationMatrix;
 rotm->rotateY(-90*deg);
 
 G4VPhysicalVolume* light_phys 
   = new G4PVPlacement(rotm, 
 		       G4ThreeVector(/*5.11*/2.555*cm,0,0),
 		       light_log, 
 		       "LightGuide", 
 		       expHall_log, 
 		       false, 
 		       0);

// G4VSolid* light_Scint
//   = new G4UnionSolid("scint+light_guide", waterTank_box, light_trd);
// G4LogicalVolume* light_Scint_log
  

 //PMT
 //
 G4double innerRadius = 4.*mm;
 G4double outerRadius = 4.85*mm;
 G4double height_pmt = 45.0*mm;
 G4double height_cathode = 10.*mm;
 G4double startAngle_pmt = 0.*deg;
 G4double spanningAngle_pmt = 360.*deg;

 G4Tubs* pmt = new G4Tubs("pmt_tube", innerRadius, outerRadius, height_pmt/2., startAngle_pmt, spanningAngle_pmt);

 G4LogicalVolume* pmt_log = new G4LogicalVolume(pmt, /*G4Material::GetMaterial("G4_Pyrex_Glass")*/Glass, "pmt_log");

 // G4VPhysicalVolume* pmt_phys = new G4PVPlacement(rotm, 
 // 						 G4ThreeVector(/*7.50*/3.75*cm,0,0), 
 // 						 pmt_log, 
 // 						 "PMT",
 // 						 expHall_log, 
 // 						 false, 
 // 						 0);

 //Photocathode
 //
 G4Tubs* photocath = new G4Tubs("photocath_tube", innerRadius, outerRadius, height_cathode/2., startAngle_pmt, spanningAngle_pmt);

 G4LogicalVolume* photocath_log = new G4LogicalVolume(photocath, BiAlkali, "photocath_log");

 // G4VPhysicalVolume* photocath_phys = new G4PVPlacement(0,
 // 						       G4ThreeVector(0*cm,0, /*0.71*/0*cm), 
 // 						       photocath_log, 
 // 						       "photocath", 
 // 						       pmt_log, 
 // 						       false, 

 // 						       0);

 //-------------------------------------------------------------------------------------------------------------------------------------
 //
 //Sensitive Detectors
 //
 //-------------------------------------------------------------------------------------------------------------------------------------

 G4SDManager* SDman = G4SDManager::GetSDMpointer();

 G4String ScintName = "ThickScintSD";

 ThickScintSD* thickScintSD = new ThickScintSD(ScintName);
 SDman->AddNewDetector(thickScintSD);
 waterTank_log->SetSensitiveDetector(thickScintSD);

 ScintName = "ThinScintSD";
 ThinScintSD* thinScintSD = new ThinScintSD(ScintName);
 SDman->AddNewDetector(thinScintSD);
 bubbleAir_log->SetSensitiveDetector(thinScintSD);
 

 // G4String SDname = "ExN06PMTSD";
 // ExN06PMTSD* photo_SD = new ExN06PMTSD(SDname);
 // SDman->AddNewDetector(photo_SD);
 // photocath_log->SetSensitiveDetector(photo_SD);

 //-------------------------------------------------------------------------------------------------------------------------------------
 //
 //Surfaces 
 //
 //------------------------------------------------------------------------------------------------------------------------------------


 // BC408 (Water Tank)
 //
 G4OpticalSurface* OpWaterSurface = new G4OpticalSurface("WaterSurface");
 OpWaterSurface->SetType(dielectric_metal/*dielectric*/);
 OpWaterSurface->SetFinish(/*ground*/polished);
 OpWaterSurface->SetModel(/*unified*/glisur);

 new G4LogicalBorderSurface("WaterSurface", waterTank_phys, expHall_phys , /*waterTank_phys,*/OpWaterSurface);
 // G4LogicalSkinSurface* WaterSurface =
 //   new G4LogicalSkinSurface("WaterSurface", waterTank_log, OpWaterSurface);
 

 // Air Bubble
 //
 G4OpticalSurface* OpAirSurface = new G4OpticalSurface("AirSurface");
 OpAirSurface->SetType(dielectric_metal/*dielectric*/);
 OpAirSurface->SetFinish(polished);
 OpAirSurface->SetModel(glisur);
 
 new G4LogicalBorderSurface("AirSurface", bubbleAir_phys, expHall_phys, OpAirSurface);
 // G4LogicalSkinSurface* AirSurface = 
 //   new G4LogicalSkinSurface("AirSurface", bubbleAir_log, OpAirSurface);
 
 //
 //Light Guide
 //
 G4OpticalSurface* OpGuideSurface = new G4OpticalSurface("GuideSurface");
 OpGuideSurface->SetType(dielectric_dielectric/*dielectric*/);
 OpGuideSurface->SetFinish(/*ground*/polished);
 OpGuideSurface->SetModel(/*unified*/glisur);
 
 new G4LogicalBorderSurface("GuideSurface", light_phys, expHall_phys, OpWaterSurface);
 // G4LogicalSkinSurface* GuideSurface = 
 // 	  new G4LogicalSkinSurface("GuideSurface", light_log, OpGuideSurface);

 //
 //LightGuide and Scintillator
 //
 G4OpticalSurface* LightScint = new G4OpticalSurface("LightScint");
 LightScint->SetType(dielectric_dielectric);
 LightScint->SetFinish(polishedfrontpainted);
 LightScint->SetModel(unified);

 //new G4LogicalBorderSurface("LightScint", waterTank_phys, light_phys, LightScint);
 
 //-------------------------------------------------------------------------------------------------------------------------------
 //
 //Visualization 
 //
 //-------------------------------------------------------------------------------------------------------------------------------

 G4VisAttributes* GuideVisAtt = new G4VisAttributes(G4Colour(1.0,.0, .0));
 light_log->SetVisAttributes(GuideVisAtt);

 G4VisAttributes* BoxVisAtt = new G4VisAttributes(G4Colour(0.,1.0,.0));
 waterTank_log->SetVisAttributes(BoxVisAtt);

 G4VisAttributes* PhotoCathVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,.0));
 photocath_log->SetVisAttributes(PhotoCathVisAtt);

  // G4OpticalSurface* opticalSurface = dynamic_cast <G4OpticalSurface*>
  //       (AirSurface->GetSurface(bubbleAir_log)->GetSurfaceProperty());

  // if (opticalSurface) opticalSurface->DumpInfo();

//-----------------------------------------------------------------------------------------------------------------------------------
//
// Generate & Add Material Properties Table attached to the optical surfaces
//
//-----------------------------------------------------------------------------------------------------------------------------------
  const G4int num = 5;
  G4double Ephoton[num] = {/*2.034*eV, 4.136*eV*/4.133*eV, 2.61*eV, 1.907*eV, 1.503*eV, 1.24*eV  };

  G4double Ephoton2[num] = {5.0*eV, 7.*eV, 8.5*eV, 10.0*eV, 15.2*eV};

  //OpticalWaterSurface 
  G4double RefractiveIndex[num] = {1.35, 1.40};
  G4double SpecularLobe[num]    = {0.3, 0.3};
  G4double SpecularSpike[num]   = {0.2, 0.2};
  G4double Backscatter[num]     = {0.2, 0.2};

  G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();
  
  myST1->AddProperty("RINDEX",                Ephoton, RefractiveIndex, num);
  myST1->AddProperty("SPECULARLOBECONSTANT",  Ephoton, SpecularLobe,    num);
  myST1->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike,   num);
  myST1->AddProperty("BACKSCATTERCONSTANT",   Ephoton, Backscatter,     num);

 
  //OpticalAirSurface
  G4double Reflectivity[num] = {/*0.3, 0.5*/0.95,0.95,0.95,0.95,0.95,};
  G4double Efficiency[num]   = {/*0.8, 1.0*/0.95,0.95,0.95,0.95,0.95,};

  G4MaterialPropertiesTable *myST2 = new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *myST3 = new G4MaterialPropertiesTable();

  myST2->AddProperty("REFLECTIVITY", Ephoton, Reflectivity, num);
  myST2->AddProperty("EFFICIENCY",   Ephoton, Efficiency,   num);
  myST3->AddProperty("REFLECTIVITY", Ephoton2, Reflectivity, num);
  myST3->AddProperty("EFFICIENCY", Ephoton2, Efficiency, num);

  OpWaterSurface->SetMaterialPropertiesTable(myST1);
  OpAirSurface->SetMaterialPropertiesTable(myST2);
  OpGuideSurface->SetMaterialPropertiesTable(myST2);
  LightScint->SetMaterialPropertiesTable(myST3);
  

//always return the physical World
  return expHall_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
