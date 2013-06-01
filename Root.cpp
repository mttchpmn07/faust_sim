#include <iostream>
//#include <ifstream>
#include <vector>
using namespace std;

int plots_maker()
{
  static Int_t numEvents = 100;
  
  //Int_t FillArray = numEvents + 10;

  TFile* outputFile = new TFile("Photon_Data.root", "UPDATE");
  
  TString nomblah;

  TH1F *ThickTimePlot[2001];
  TString nom2;
  for(Int_t lj= 0; lj<numEvents; lj++){
    nom2 = Form("Thickplot%d",lj);
    ThickTimePlot[lj]= new TH1F(nom2,nom2, 400, -0.5, 100.5);
  //TimePlot->SetTitle("Time nom3 = Form("Thinplot%d",lj);Histogram");
  }

  TH1F *ThinTimePlot[2001];
  TString nom3;
  for(Int_t lj= 0; lj<numEvents; lj++){
    nom3 = Form("Thinplot%d",lj);
    ThinTimePlot[lj]= new TH1F(nom3,nom3, 400, -0.5, 100.5);
    //TimePlot->SetTitle("Time Histogram");
  }

  TH1F *ThickEnergyPlot = new TH1F("ThickEnergyPlot", "ThickEnergy Hist", 400, -0.5, 100.5);
  ThickEnergyPlot->SetTitle("Thick Energy Histogram");

  TH1F *ThinEnergyPlot = new TH1F("ThinEnergyPlot", "ThinEnergy Hist", 400, -0.5, 100.5);
  ThinEnergyPlot->SetTitle("Thin Energy Histogram");
 
  TH1F *TotalThickTime = new TH1F("ThickTotalTime", "Thick Total Time", 400, -0.5, 100.5);
  TotalThickTime->SetTitle("Thick Total Time Histogram");
  
  TH1F *TotalThinTime = new TH1F("ThinTotalTime", "Thin Total Time", 400, -0.5, 100.5);
  TotalThinTime->SetTitle("Thin Total Time Histogram");

  TF1 *func[2001];
  TString nom5;
  for(Int_t ii=0; ii<numEvents; ii++){
    nom5 = Form("Fit%d",ii);
    // func[ii] = new TF1(nom5,fitf ,0, 70, 4);
    func[ii] = new TF1(nom5,"[0]*TMath::Exp(-([1])*(x-[2]))",0,70);
  }

  Int_t ThickgammaCount[2001];
  Double_t ThickTime=0;
  Double_t ThickTotalEnergy[2001];

  Int_t ThingammaCount[2001];
  Double_t ThinTime=0;
  Double_t ThinTotalEnergy[2001];

  Int_t plot_counter = 0;

  ifstream ThickDataFile;
  ThickDataFile.open("ThickGammaEnergyData.txt");
  if (ThickDataFile.is_open()){
    for (int i = 0; i < numEvents; i++)
      {
	ThickDataFile >> ThickgammaCount[i] >> ThickTotalEnergy[i];
	ThickEnergyPlot->Fill(ThickTotalEnergy[i]);
	 }

    outputFile->cd();
    ThickEnergyPlot->Write();
  }
  
  ifstream ThickTimefile;
  ThickTimefile.open("ThickTimeData.txt");
  //cout << "CHEERS!" << endl;
  if(ThickTimefile.is_open()){
    while(plot_counter < numEvents){
      for (int i = 0; i<ThickgammaCount[plot_counter]; i++){

  	  ThickTimefile >> ThickTime;
	  ThickTimePlot[plot_counter]->Fill(ThickTime);
	  TotalThickTime->Fill(ThickTime);
	  
      }
      outputFile->cd();
      nomblah = Form("Fit%d", plot_counter);
      cout << "-----------Plot Number: " << plot_counter << endl;
      ThickTimePlot[plot_counter]->Fit("landau");
      ThickTimePlot[plot_counter]->Write();
      TotalThickTime->Write();
  
      plot_counter++;
     
    }
  }
 
 Int_t plot_counter = 0;

  ifstream ThinDataFile;
  ThinDataFile.open("ThinGammaEnergyData.txt");
  if (ThinDataFile.is_open()){
    for (int i = 0; i < numEvents; i++)
      {
	ThinDataFile >> ThingammaCount[i] >> ThinTotalEnergy[i];
	ThinEnergyPlot->Fill(ThinTotalEnergy[i]);
      }

    outputFile->cd();
    ThinEnergyPlot->Write();
  }
  
  ifstream ThinTimefile;
  ThinTimefile.open("ThinTimeData.txt");
  //cout << "CHEERS!" << endl;
  if(ThinTimefile.is_open()){
    while(plot_counter < numEvents){
      // cout << "ha" << endl;
  
      //cout << ThingammaCount[plot_counter] << "  " << plot_counter << endl;
      for (int i = 0; i<ThingammaCount[plot_counter]; i++){
	//cout << "LOOP 2" << endl;
   
  	  ThinTimefile >> ThinTime;
	  //cout << ThinTime << endl;
  	  ThinTimePlot[plot_counter]->Fill(ThinTime);
	  TotalThinTime->Fill(ThinTime);
      }
      outputFile->cd();
      nomblah = Form("Fit%d", plot_counter);
      //ThinTimePlot[plot_counter]->Fit("landau");
      
      ThinTimePlot[plot_counter]->Write();
      TotalThinTime->Write();

      //cout << "HAHA2" << endl;
      // cout << plot_counter << endl;     
      plot_counter++;
     
      // }
    //file >> TotalEnergy;
    // counter++;
    }
  }
  
  cout << "FILL HISTOS " << plot_counter << endl;

  // TString nom;
  // // TCanvas *Thickcanvas[100];
  // for(Int_t tt=0; tt<plot_counter; tt++) {
  //   //nom = Form("Thickcanvas%d",tt);
  // // Thickcanvas[tt]= new TCanvas(nom,nom, 1);
  // }
  // //TCanvas *canvas1 = new TCanvas("nom","nom", 1);

  // for(Int_t jj=0; jj<numEvents; jj++) {
  //   Thickcanvas[jj]->cd();
  //   //TimePlot[jj]->Draw("HIST");
  //   // TimePlot[jj]->SetTitle("Time Histogram");
  // }

  // // TCanvas *Thickcanvas2 = new TCanvas("ThickcanvasEnergy", "ThickcanvasEnergy", 1);
  // // EnergyPlot->Draw("HIST");
  
  // TString nom4;
  // // TCanvas *Thincanvas[100];
  // for(Int_t tt=0; tt<plot_counter; tt++) {
  // // nom4 = Form("Thincanvas%d",tt);
  // // Thincanvas[tt]= new TCanvas(nom4,nom4, 1);
  // }
  // //TCanvas *canvas1 = new TCanvas("nom","nom", 1);

  // for(Int_t jj=0; jj<numEvents; jj++) {
  //   Thincanvas[jj]->cd();
  //   //TimePlot[jj]->Draw("HIST");
  //   // TimePlot[jj]->SetTitle("Time Histogram");
  // }

  //TCanvas *Thincanvas2 = new TCanvas("ThincanvasEnergy", "ThincanvasEnergy", 1);
  // EnergyPlot->Draw("HIST");
  




  // Timefile.close();
  
  outputFile->Close();
  ThickDataFile.close();
  
  return 0;
}

