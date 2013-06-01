{
//=========Macro generated from canvas: c1/c1
//=========  (Thu Aug  2 16:38:10 2012) by ROOT version5.99/01
   TCanvas *c1 = new TCanvas("c1", "c1",60,52,700,500);
   c1->Range(-1.88875,-145.5563,11.99875,1310.006);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1F *ThinTotalTime = new TH1F("ThinTotalTime","Thin Total Time Histogram",400,-0.5,100.5);
   ThinTotalTime->SetBinContent(9,1013);
   ThinTotalTime->SetBinContent(10,1109);
   ThinTotalTime->SetBinContent(11,707);
   ThinTotalTime->SetBinContent(12,433);
   ThinTotalTime->SetBinContent(13,314);
   ThinTotalTime->SetBinContent(14,176);
   ThinTotalTime->SetBinContent(15,130);
   ThinTotalTime->SetBinContent(16,104);
   ThinTotalTime->SetBinContent(17,74);
   ThinTotalTime->SetBinContent(18,40);
   ThinTotalTime->SetBinContent(19,38);
   ThinTotalTime->SetBinContent(20,34);
   ThinTotalTime->SetBinContent(21,18);
   ThinTotalTime->SetBinContent(22,19);
   ThinTotalTime->SetBinContent(23,9);
   ThinTotalTime->SetBinContent(24,11);
   ThinTotalTime->SetBinContent(25,8);
   ThinTotalTime->SetBinContent(26,9);
   ThinTotalTime->SetBinContent(27,6);
   ThinTotalTime->SetBinContent(28,6);
   ThinTotalTime->SetBinContent(29,7);
   ThinTotalTime->SetBinContent(30,6);
   ThinTotalTime->SetBinContent(31,4);
   ThinTotalTime->SetBinContent(32,1);
   ThinTotalTime->SetBinContent(33,1);
   ThinTotalTime->SetBinContent(35,3);
   ThinTotalTime->SetBinContent(40,1);
   ThinTotalTime->SetBinContent(42,1);
   ThinTotalTime->SetBinContent(44,1);
   ThinTotalTime->SetBinContent(47,1);
   ThinTotalTime->SetEntries(4284);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *text = ptstats->AddText("ThinTotalTime");
   text->SetTextSize(0.0368);
   text = ptstats->AddText("Entries = 4284   ");
   text = ptstats->AddText("Mean  =  2.295");
   text = ptstats->AddText("RMS   = 0.8385");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   ThinTotalTime->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(ThinTotalTime);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   ThinTotalTime->SetLineColor(ci);
   ThinTotalTime->GetXaxis()->SetRange(1,44);
   ThinTotalTime->GetXaxis()->SetLabelFont(42);
   ThinTotalTime->GetXaxis()->SetLabelSize(0.035);
   ThinTotalTime->GetXaxis()->SetTitleSize(0.035);
   ThinTotalTime->GetXaxis()->SetTitleFont(42);
   ThinTotalTime->GetYaxis()->SetLabelFont(42);
   ThinTotalTime->GetYaxis()->SetLabelSize(0.035);
   ThinTotalTime->GetYaxis()->SetTitleSize(0.035);
   ThinTotalTime->GetYaxis()->SetTitleFont(42);
   ThinTotalTime->GetZaxis()->SetLabelFont(42);
   ThinTotalTime->GetZaxis()->SetLabelSize(0.035);
   ThinTotalTime->GetZaxis()->SetTitleSize(0.035);
   ThinTotalTime->GetZaxis()->SetTitleFont(42);
   ThinTotalTime->Draw("");
   
   TPaveText *pt = new TPaveText(0.2752011,0.9342405,0.7247989,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText("Thin Total Time Histogram");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
