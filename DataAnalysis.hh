//**************************************************************************************************************************************************
//
//EventAnalysis.hh
//
//**************************************************************************************************************************************************

#ifndef DATARECORD_H
#define DATARECORD_H

#include <iostream>
using namespace std;

#include <iomanip>
#include <fstream>

// #include "/home/reeses/ROOT/core/base/inc/Riostream.h"
// #include "/home/reeses/ROOT/include/TFile.h"
// #include "/home/reeses/ROOT/include/TTree.h"
#include "globals.hh"
#include "G4UnitsTable.hh"

class EventAnalysis
{
private:
  //initialized in class constructor in EventAnalysis.cc

  TFile* DataFile;
  TTree* PhotonTree;

public:
  EventAnalysis();
  ~EventAnalysis();

  //creates a pointer to data analysis in main() program
  static EventAnalysis* DataPointer;

  void GetData(G4int gamma, G4double time, G4double energy);
  void FillTree();

};

#endif
