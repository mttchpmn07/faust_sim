//******************************************************************************
//
//Building the Tree for the Data in Root
//
//******************************************************************************
#include "EventAnalysis.hh"

//#include "Riostream.h"
// #include "TFile.h"
// #include "TTree.h"

#define MAX 20000000

EventAnalysis* EventAnalysis::DataPointer;

EventAnalysis::EventAnalysis()
{
  //constructor

  //Create Pointers to ROOT Analysis Tree and Branches

  DataFile = new TFile("photon_data.root", "RECREATE");

  PhotonTree = new TTree("PhotonTree", "Photon Data");
  
  //Photon Members:
  G4int GammaCounter;
  G4double Time;
  G4double Energy;

  PhotonTree->Branch("GammaCount", GammaCounter, "GammaCounter/I");
  PhotonTree->Branch("Time", Time, "Time/D");
  PhotonTree->Branch("Energy", Energy, "Energy/D");
}

EventAnalysis::~EventAnalysis()
{
  //Destructor and close root file
  PhotonTree->Write();
  DataFile->Write();
  DataFile->Flush();
  DateFile->Close();

  G4cout << "####### Created Root Tree File ######" << G4endl;
  delete DataFile;
}

void EventAnalysis::GetData(G4int pCount, G4double Ttime, G4double Tenergy)
{
  GammaCounter = pCount;
  Time = Ttime;
  Energy = Tenergy;
}

void EventAnalysis::FillTree()
{
  PhotonTree->Fill();
}
  

// void MakeTree(void)
// {

//   //declaration of structure for the data
//   struct Photon_Event{
//     Int_t Gamma;
//     Double_t Time;
//     Double_t Energy;
//   };

//   Photon_Event event;

//   //Open the data file for reading
//   ifstream file;
//   file.open("photon_data.data");

//   UInt_t nEvents = 100000;

//   //Open ROOT file to save the TTree in
//   TFile *ftree = new TFile("photon_data.root", "recreate");

//   //Creation of TTree
//   TTree *photon = new TTree("photon", "Photon Data Tree");

//   //creation of branched to hold the variables of the structure
//   photon->Branch("photonCount", &event.Gamma, "Gamma/I");
//   photon->Branch("time", &event.Time, "Time/D");
//   photon->Branch("energy", &event.Energy, "Energy/D");

//   // while((nEvents--)>0){
//   //   file >> event.Gamma;
//   //   file >> event.Time;
//   //   file >> event.Energy;
//   // }

 
  
//   if(!(nEvents%1000)) cout << "Events left = " << nEvents << endl;
// }

// file.close();

// //write and close the ROOT file
// photon->Write();
// delete ftree;
// } 
