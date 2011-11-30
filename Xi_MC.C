#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLegend.h>
#include "string.h"
#include <iomanip>
#include <sstream>
#include "NCutil.C"
#include <iostream>
#include <fstream>
#include <string>
#include "tdrstyle.C"
#include <algorithm>
TFile *fMC;
TCanvas *XiC;
TCanvas *XiC_ratio;

TH1F *XiRatio;

void Xi_ratio()
{
  XiC = NCanvas(1,1,"XiC");
  XiC_ratio = NCanvas(1,1,"XiC_ratio");
  
  readfile();
  // char Fi1[6] = "CW";
  // char Fi1[6] = "DW";
  char Fi1[6] = "P8_CHA";

  fMC = TFile::Open(MCMBFile); 
  if (fMC==0)
    {
      cout << "Problem in opening  MC file = " << MCMBFile << endl;
      return;
    }
  
  char temp[100] = "Xi_";  
  TH1F *Fi1Xi_gen =   (TH1F*)fMC->Get(strcat(temp,Fi1));  
  char temp1[100] = "Xi_NDOFGE2_";  
  TH1F *Fi1Xi_meas =   (TH1F*)fMC->Get(strcat(temp1,Fi1));  
  char temp2[100] = "Xi_TrkGenEta3Pt200_";  
  TH1F *Fi1Xi_gen_3trk =   (TH1F*)fMC->Get(strcat(temp2,Fi1));  


  XiC->cd();
  Fi1Xi_gen->Draw(); 

  Fi1Xi_meas->SetLineColor(2); 
  Fi1Xi_gen_3trk->SetLineColor(4);   
  Fi1Xi_meas->Draw("SAMEHIST"); 
  Fi1Xi_gen_3trk->Draw("SAMEHIST"); 
  Fi1Xi_gen->GetXaxis()->SetTitle("Xi");
  Fi1Xi_gen->GetYaxis()->SetTitle("Entries");

  TLegend *leg = new TLegend(0.3,0.6, 0.7 ,0.8);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Fi1Xi_gen,"Xi gen","L");  
  leg->AddEntry(Fi1Xi_gen_3trk,"Xi gen with 3 tracks","L");  
  leg->AddEntry( Fi1Xi_meas," Xi meas","L");

  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);  
  leg->SetFillColor(0);  
  leg->Draw();

  XiC_ratio->cd();
  XiRatio = NH1clone("XiRatio","XiRatio",Fi1Xi_gen);
  XiRatio->Add(Fi1Xi_gen_3trk);
  XiRatio->Divide(Fi1Xi_gen);
  XiRatio->Draw();


  return;
}

