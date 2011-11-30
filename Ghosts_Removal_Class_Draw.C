#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <TMath.h>
#include <TLegend.h>
#include "string.h"
#include <iomanip>
#include "NCutil.C"

/*
File number 1 has 476697 entries
File number 2 has 10338 entries
File number 3 has 10020 entries
File number 4 has 2430087 entries
File number 5 has 94571 entries
the average luminosity:
High_HF lumi interval= 0.453707 and <ghost> 1.39959
Low_HF lumi interval= 0.22172 and <ghost> 0.683959
Full_HF lumi interval= 0.307871 and <ghost> 0.949718
To get one HF ghost we scale by = 1.32711
High_Xi lumi interval= 0.446139 and <ghost> 1.37624
Low_Xi lumi interval= 0.218969 and <ghost> 0.675474
Full_Xi lumi interval= 0.275752 and <ghost> 0.850635
To get to 0.850635Xi ghost we scale by = 1.21386
*/

void Read_File(){

  TFile *f =TFile::Open("Ghost_Removal_Class_files.root"); 
  TH1F *PytD6T_HF =  (TH1F*)f->Get("PytD6T_HF");
  TH1F *PytZ2_HF =  (TH1F*)f->Get("PytZ2_HF");
  TH1F *Dat_HF_LowLumi =  (TH1F*)f->Get("Dat_HF_LowLumi");
  TH1F *Dat_HF_HighLumi =  (TH1F*)f->Get("Dat_HF_HighLumi");
  TH1F *Dat_HF =  (TH1F*)f->Get("Dat_HF");
  TH1F *Dat_HF_Cor =  (TH1F*)f->Get("Dat_HF_Cor");
  TH1F *Ratio_HF_LowLumi =  (TH1F*)f->Get("Ratio_HF_LowLumi");
  TH1F *Ratio_HF_HighLumi =  (TH1F*)f->Get("Ratio_HF_HighLumi");
  TH1F *Dat_HF_NoGhosts= (TH1F*)f->Get("Dat_HF_NoGhosts");
  TH1F *Ghosts_HF= (TH1F*)f->Get("Ghosts_HF");
  
  //Xi plots

   TH1F *Dat_Xi_LowLumi =  (TH1F*)f->Get("Dat_Xi_LowLumi");
   TH1F *Dat_Xi_HighLumi =  (TH1F*)f->Get("Dat_Xi_HighLumi");
   TH1F *Dat_Xi =  (TH1F*)f->Get("Dat_Xi");
   TH1F *Dat_Xi_Cor =  (TH1F*)f->Get("Dat_Xi_Cor");
   TH1F *Ghosts_Xi= (TH1F*)f->Get("Ghosts_Xi");
   TH1F *Dat_Xi_NoGhosts= (TH1F*)f->Get("Dat_Xi_NoGhosts");
   TH1F *PytD6T_Xi= (TH1F*)f->Get("PytD6T_Xi");
   TH1F *PytZ2_Xi= (TH1F*)f->Get("PytZ2_Xi");
   TH1F *Pom_Xi= (TH1F*)f->Get("Pom_Xi");
   TH1F *Pom_HF= (TH1F*)f->Get("Pom_HF");


  // Lumi plots

   TH1F *Lumi_HF_all =  (TH1F*)f->Get("Lumi_HF_all");
   TH1F *Lumi_HF_HighLumi =  (TH1F*)f->Get("Lumi_HF_HighLumi");
   TH1F *Lumi_HF_LowLumi =  (TH1F*)f->Get("Lumi_HF_LowLumi");
   TH1F *Lumi_Xi_HighLumi =  (TH1F*)f->Get("Lumi_Xi_HighLumi");
   TH1F *Lumi_Xi_LowLumi =  (TH1F*)f->Get("Lumi_Xi_LowLumi");
   TH1F *Lumi_Xi_all =  (TH1F*)f->Get("Lumi_Xi_all");
   f->Close();
   return;
}

void Draw_Xi_Ghost(){

  NCanvas(1,1);
  NHSetMarker(Ghosts_Xi,2,20,0.8);
  NStatOff(Ghosts_Xi);
  Ghosts_Xi->SetTitle();
  Ghosts_Xi->Draw("E"); 
  Ghosts_Xi->GetXaxis()->SetTitle("Xi");
  Ghosts_Xi->GetYaxis()->SetTitle("Entries");
  NText(0.,3.2.,"Ghost Contribution to Xi considerning <0.95> ghosts per event",4) ;
 
  return;

}

void Draw_HF_Ghost(){

  NCanvas(1,1);
  NHSetMarker(Ghosts_HF,2,20,0.8);
  Ghosts_HF->Draw("E");
  NStatOff(Ghosts_HF);
  Ghosts_HF->GetXaxis()->SetTitle("Energy [GeV]");
  Ghosts_HF->GetYaxis()->SetTitle("Entries");
  NText(0.,100.,"Ghost Contribution to HF considerning <0.95> ghosts per event",4) ;
  Ghosts_HF->SetTitle();
  return;
}


void Draw_HF(){

  NCanvas(1,1);
  gPad->SetLogy(1);
  gPad->SetLogx(1);
  NHSetMarker(Dat_HF_NoGhosts,2,20,0.8);
  Dat_HF_NoGhosts->SetTitle();
  Dat_HF_NoGhosts->SetMinimum(2.);
  Dat_HF_NoGhosts->Draw("E");
  NStatOff(Dat_HF_NoGhosts);
  NStatOff(Dat_HF);
  Dat_HF_NoGhosts->GetXaxis()->SetTitle("Energy [GeV]");
  Dat_HF_NoGhosts->GetYaxis()->SetTitle("Entries");
  NText(0.,2000.,"HF distribution with and without Ghost Contribution",4) ;
  Dat_HF->Draw("SAME e");
  leg = new TLegend(0.1,0.75,0.6,0.9); 
  //Full_HF lumi interval= 0.307871 and <ghost> 0.949718
  leg->AddEntry(Dat_HF," HF  <Lumi> = 0.31 10^{30} cm^{-2}s^{-1}, <Ghost> = 0.95 ","p"); 
  leg->AddEntry(Dat_HF_NoGhosts,"HF - Ghost Subtracted","p"); 
  leg->Draw();
  return;
}


void Draw_HF_Low_High_Lumi(){

  NCanvas(1,1);
  gPad->SetLogy(1);
  gPad->SetLogx(1);
  NHSetMarker(Dat_HF_LowLumi,2,20,0.8);
  Dat_HF_LowLumi->SetTitle();
  Dat_HF_LowLumi->Draw("E");
  NStatOff(Dat_HF_LowLumi);
  NStatOff(Dat_HF_HighLumi);
  Dat_HF_LowLumi->GetXaxis()->SetTitle("Energy [GeV]");
  Dat_HF_LowLumi->GetYaxis()->SetTitle("Fraction");
  NText(0.,0.5,"Normalized HF  distribution at low and high Instantaneous Luminosity",4) ;
  Dat_HF_HighLumi->Draw("SAME e");
  leg = new TLegend(0.1,0.75,0.6,0.9); 
  leg->AddEntry(Dat_HF_LowLumi," <Lumi> = 0.22 10^{30} cm^{-2}s^{-1}, <Ghost> = 0.68 ","p"); 
  leg->AddEntry(Dat_HF_HighLumi," <Lumi> = 0.45 10^{30} cm^{-2}s^{-1}, <Ghost> = 1.4 ","p"); 

  leg->Draw();
  return;
}


void Draw_Xi_Low_High_Lumi(){
NCanvas(1,1);
  gPad->SetLogy(0);
  gPad->SetLogx(0);
  NHSetMarker(Dat_HF_LowLumi,2,20,0.8);
  Dat_Xi_LowLumi->SetTitle();

  TH1F * file1 = Dat_Xi_HighLumi;
  TH1F * file2 = Dat_Xi_LowLumi;

  Int_t Max1 = file1->GetMaximumBin();
  Float_t Max1Cont = file1->GetBinContent(Max1); 
  Int_t Max2 = file2->GetMaximumBin();
  Float_t Max2Cont = file2->GetBinContent(Max2); 

  Float_t scale = Max1Cont/Max2Cont;
  file2->Scale(scale);

  NHSetMarker(Dat_Xi_LowLumi,2,20,1.2);
  NHSetMarker(Dat_Xi_HighLumi,4,20,1.2);

  file2->Draw("E");
  NStatOff(Dat_Xi_LowLumi);
  NStatOff(Dat_Xi_HighLumi);
  Dat_Xi_LowLumi->GetXaxis()->SetTitle("Xi");
  Dat_Xi_LowLumi->GetYaxis()->SetTitle("Entries");
  NText(0.,38,"Normalized Xi  distribution at low and high Instantaneous Luminosity",4) ;
  Dat_Xi_HighLumi->Draw("SAME e");
  leg = new TLegend(0.4,0.75,0.9,0.9); 
  leg->AddEntry(Dat_Xi_LowLumi," <Lumi> = 0.22 10^{30} cm^{-2}s^{-1}, <Ghost> = 0.68 ","p"); 
  leg->AddEntry(Dat_Xi_HighLumi," <Lumi> = 0.45 10^{30} cm^{-2}s^{-1}, <Ghost> = 1.4 ","p"); 

  leg->Draw();

}
