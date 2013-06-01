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
//
#include "Si_SDHit.hh"
#include "ExN06PrimaryGeneratorAction.hh"
#include "G4AttDef.hh"
#include "G4AttDefStore.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
// HandsOn5: Draw box
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4ParticleGun.hh"
#include "G4VisAttributes.hh"
#include "G4VVisManager.hh"

#include <iostream>
#include <fstream>
using namespace std;
G4Allocator<Si_SDHit> Si_SDHitAllocator;

Si_SDHit::Si_SDHit()
:fCellID(-1)
,fDepositedEnergy(0)
,fPosition()
,fRotation()
,pLogicalVolume(0)
{}

Si_SDHit::Si_SDHit(G4int id)
:fCellID(id)
,fDepositedEnergy(0)
,fPosition()
,fRotation()
,pLogicalVolume(0)
{}

Si_SDHit::~Si_SDHit() {}

void Si_SDHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    
    if(pVVisManager && (fDepositedEnergy>0.)) {
        
        // HandsOn5: Draw a box with depth propotional to the energy deposition
        //G4double scale = ExN06PrimaryGeneratorAction::Gun()->GetParticleEnergy();
        //G4double depth = (50.*cm)*(fDepositedEnergy*MeV)/(scale*MeV);
        G4double depth = (50.*cm)*(fDepositedEnergy*MeV)/(MeV);
        
        // Back face of box is flat against front face of calorimeter cell
        double z = fPosition.z()  + 25.*cm;
        G4ThreeVector myPos(fPosition.x(), fPosition.y(), z+depth);
        
        G4Transform3D trans(fRotation.inverse(), myPos);
        G4VisAttributes attribs;
        
        // Magenta with transparency
        G4Colour colour(1., 0., 1., 0.6);
        attribs.SetColour(colour);
        attribs.SetForceSolid(true);
        
        G4Box box("MyBox", 5.*cm, 5.*cm, depth);
        
        pVVisManager->Draw(box, attribs, trans);
    }
}

const std::map<G4String,G4AttDef>* Si_SDHit::GetAttDefs() const
{
    G4bool isNew;
    std::map<G4String,G4AttDef>* store 
    = G4AttDefStore::GetInstance("Si_SDHit",isNew);
    
    if (isNew) {
        G4String HitType("HitType");
        (*store)[HitType] = G4AttDef(HitType,"Hit Type", "Bookkeeping", "", "G4String");
        
        G4String ID("ID");
        (*store)[ID] = G4AttDef(ID, "ID", "Bookkeeping", "", "G4int");
        
        G4String Column("Column");
        (*store)[Column] = G4AttDef(Column, "Column ID", "Bookkeeping", "", "G4int");
        
        G4String Row("Row");
        (*store)[Row] = G4AttDef(Row, "Row ID", "Bookkeeping", "", "G4int");
        
        G4String Energy("Energy");
        (*store)[Energy] = G4AttDef(Energy, "Energy Deposited", "Physics", 
                                    "G4BestUnit", "G4double");
        
        G4String Pos("Pos");
        (*store)[Pos] = G4AttDef(Pos, "Position", "Physics", "G4BestUnit", "G4ThreeVector");
        
        G4String LVol("LVol");
        (*store)[LVol] = G4AttDef(LVol, "Logical Volume", "Bookkeeping", "", "G4String");
    }
    
    return store;
}

std::vector<G4AttValue>* Si_SDHit::CreateAttValues() const
{
    std::vector<G4AttValue>* values = new std::vector<G4AttValue>;
    
    values->push_back(G4AttValue("HitType", "EmCalorimeterHit", ""));
    
    values->push_back
    (G4AttValue("ID", G4UIcommand::ConvertToString(fCellID), ""));
    
    values->push_back(G4AttValue("Column", " ", ""));
    
    values->push_back(G4AttValue("Row", " ", ""));
    
    values->push_back(G4AttValue("Energy", G4BestUnit(fDepositedEnergy, "Energy"), ""));
    
    values->push_back(G4AttValue("Pos", G4BestUnit(fPosition,"Length"), ""));
    
    if (pLogicalVolume) values->push_back(G4AttValue("LVol", pLogicalVolume->GetName(), ""));
    else values->push_back(G4AttValue("LVol", " ", ""));
    
    return values;
}

void Si_SDHit::Print()
{
    G4cout << "  Si#[" << fCellID << "] " << fDepositedEnergy/MeV << " (MeV)" << G4endl;
    
    ofstream dataFile ("Si_out.txt", ios_base::app);
    
    dataFile << "  " << fCellID << " " << fDepositedEnergy/MeV << " " << endl;
}


