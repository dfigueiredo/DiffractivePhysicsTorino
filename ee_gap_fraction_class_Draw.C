#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <TMath.h>
#include <TLegend.h>
#include "string.h"
#include <iomanip>
#include "NCutil.C"

const int xbin = 15;
TH1F * HF_rat[xbin];
TH1F * HF0_dat[xbin];

void Read_File(){

  TFile *f =TFile::Open("ee_gap_fraction_class_files.root"); 

  TH1F * h_all =  (TH1F*)f->Get("h_all");
  TH1F * HF0 =  (TH1F*)f->Get("HF0");
  TH1F * HF_ratio =  (TH1F*)f->Get("HF_ratio");
  TH1F * Gap0 =  (TH1F*)f->Get("Gap0");
  TH1F * Gap_ratio =  (TH1F*)f->Get("Gap_ratio");
  TH1F * Castor0 =  (TH1F*)f->Get("Castor0");
  TH1F * Castor_ratio =  (TH1F*)f->Get("Castor_ratio");
  TH1F * evt_h_all =  (TH1F*)f->Get("evt_h_all");
  TH1F * evt_HF0 =  (TH1F*)f->Get("evt_HF0");
  TH1F * evt_HF_ratio =  (TH1F*)f->Get("evt_HF_ratio");
  TH1F * evt_Gap0 =  (TH1F*)f->Get("evt_Gap0");
  TH1F * evt_Gap_ratio =  (TH1F*)f->Get("evt_Gap_ratio");
  TH1F * Run_Numb =  (TH1F*)f->Get("RunNumb");
  TH1F * RunNumb_Castro0 =  (TH1F*)f->Get("RunNumb_Castor0");
  TH1F * RunNumb_HF0 =  (TH1F*)f->Get("RunNumb_HF0");
  TH1F * RunNumb_Castor_ratio =  (TH1F*)f->Get("RunNumb_Castor_ratio");
  TH1F * RunNumb_HF_ratio =  (TH1F*)f->Get("RunNumb_HF_ratio");
  TH1F * Dat_ee_HF =  (TH1F*)f->Get("Dat_ee_HF");
  TH1F * Dat_Zll_HF =  (TH1F*)f->Get("Dat_Zll_HF");
  TH1F * Xi_HF0 =  (TH1F*)f->Get("Xi_HF0");
  TH1F * Xi_HF0_03 =  (TH1F*)f->Get("Xi_HF0_03");
  TH1F * Xi_HF0_lumi =  (TH1F*)f->Get("Xi_HF0_lumi");
  TH1F * Xi_HF0_03_lumi =  (TH1F*)f->Get("Xi_HF0_03_lumi");

  

  for (Int_t j=0; j<xbin-1;j++){      
    char hname[100];
    sprintf(hname,"HF_rat%i",j);  
    cout << "Opening " << hname << endl;
    HF_rat[j] =  (TH1F*)f->Get(hname);
    sprintf(hname,"HF0_dat%i",j);
    HF0_dat[j] =  (TH1F*)f->Get(hname);
  }
  //  f->Close();
  return;
}

void Draw_HF_rat(){

  TCanvas *My = NCanvas(4,4);
   for (int i=0; i<14; i++) {
     My->cd(i+1);
     Float_t mx = HF_rat[i]->GetMaximum();
     Float_t min = HF_rat[i]->GetMinimum();
     //    cout << mx << " " << min << endl;
     HF_rat[i]->SetStats(0);
     HF_rat[i]->SetTitleSize(5);

     //     HF_rat[i]->SetMaximum(2.);
     // HF_rat[i]->SetMinimum(0.05);

     HF_rat[i]->Fit("pol1");
     //Float_t scale = expo->GetParameter(0);
     //     scale = pow (2.71,scale);
     // cout << "scale = " << scale << endl;
     // HF_rat[i]->Scale(1./scale);
     HF_rat[i]->Fit("pol1");
     expo->SetLineWidth(0.2);  
     expo->SetLineColor(1);
     expo->SetLineStyle(1);
     NHSetMarker(HF_rat[i], 2, 20, 0.8);
     gPad->SetLogy(0);
     HF_rat[i]->Draw();
     HF_rat[i]->GetYaxis()->SetTitle("Fraction");
     HF_rat[i]->GetXaxis()->SetTitle("Luminosity 10^{30} cm^{-2}s^{-1}");

       }

  return;

}


void Draw_HF_Many_Lumi(){

  TCanvas *My = NCanvas(3,4);

  const int Nbin = Dat_ee_HF->GetNbinsX(); // number of bin in the HF distribution
  const int nHists=Nbin;

  TH1F *  EHFLumi[15];
  TH1F * myHists[nHists];

  Float_t Cont;
  Float_t BinC;

  char hftitle[100];
  char hfname[100];
  for (Int_t j=2;j<Nbin;j++){
    cout << "j = "<< j << endl;
    BinC = HF_rat[1]->GetBinCenter(j);
    sprintf(hfname,"Lumi = %f",BinC);
    sprintf(hftitle,"EHFLumi%i",j);
    EHFLumi[j] = NH1clone(hftitle,hfname,Dat_ee_HF);
    cout << "Creating histo "<< hftitle << endl;
  }
  for (Int_t j=2;j<Nbin;j++){
    for (int i=0; i<14; i++) {
      Cont = HF_rat[i]->GetBinContent(j);
      EHFLumi[j]->SetBinContent(i,Cont);
      cout << "i= " << i << " cont = " << Cont << endl;
    }
    My->cd(j-1);
    NLogAxis(1,1);
    EHFLumi[j]->Draw("p");
  }

   // cin >> " pippo" >> endl;

  return;
}

void Draw_HF_0Lumi(){
  Double_t p0;
  Double_t p1;
  const int xbin = 15;
  Float_t xlow[xbin] = {0., 4.,10.,20.,40.,60.,90.,120.,150.,250.,400.,600.,800.,1000.,1500. };
  TH1F *HF_0Lumi = new TH1F("HF_0Lumi","HF_0Lumi",14,xlow);
  for (int i=0; i<14; i++) {
    HF_rat[i]->Fit("expo");
    p0 = expo->GetParameter(0);
    p1 = pow(2.71, p0);
    
    cout << " The p0 parameter is = "<< p0 << " while p1 is: " << p1 << endl;
    HF_0Lumi->SetBinContent(i+1,p1);

      }

  TCanvas *My = NCanvas(1,1);
  NLogAxis(1,1);
  Int_t scale = Dat_ee_HF->GetEntries();
  HF_0Lumi->Scale(scale);
  Dat_ee_HF->SetStats(0); 
  //  NstatOff(Dat_ee_HF);
  //NstatOff(HF_0Lumi);
  NHSetMarker(Dat_ee_HF, 2, 20, 1.2);
  Dat_ee_HF->Draw("e");
  Dat_ee_HF->SetTitle("HF Energy Distribution for events ee with pt>10 GeV");
  Dat_ee_HF->GetXaxis()->SetTitle("Energy [GeV]");
  Dat_ee_HF->GetYaxis()->SetTitle("Entries");
  NHSetMarker(HF_0Lumi, 4, 20, 1.2);
  HF_0Lumi->Draw("SAME HIST E");
 
  leg = new TLegend(0.1,0.75,0.6,0.9); 
  leg->AddEntry(Dat_ee_HF," HF  <Lumi> = 0.31 10^{30} cm^{-2}s^{-1}, <Ghost> = 0.95 ","p"); 
  leg->AddEntry(HF_0Lumi,"HF - Ghost Subtracted ","p"); 
  leg->Draw();
  
  return;
}


void Draw_HF_slopes()
{

  Double_t p0;
  Double_t p1;
  const int xbin = 15;
  Float_t xlow[xbin] = {0., 4.,10.,20.,40.,60.,90.,120.,150.,250.,400.,600.,800.,1000.,1500. };
  TH1F *HF_0Lumi = new TH1F("HF_0Lumi","HF_0Lumi",14,xlow);
  for (int i=0; i<14; i++) {
    HF_rat[i]->Fit("expo");
    p1 = expo->GetParameter(1);
    p0 = expo->GetParError(1);
    cout << " The p1 parameter is = "<< p1 << " while p1 is: " << p1 << endl;
    HF_0Lumi->SetBinContent(i+1,p1);
    HF_0Lumi->SetBinError(i+1,p0);

      }

  TCanvas *My = NCanvas(1,1);
  gPad->SetLogx();
  HF_0Lumi->SetStats(0); 
  NHSetMarker(HF_0Lumi, 4, 20, 1.2);
  HF_0Lumi->Draw("E");
  HF_0Lumi->SetTitle("HF Slope Parameter");
  HF_0Lumi->GetXaxis()->SetTitle("Energy [GeV]");
  HF_0Lumi->GetYaxis()->SetTitle("Slope");

  return;
}

void Draw_Xi(){
  NCanvas(1,1);
  MyC->cd(1);
  Xi_ra = NH1clone("Xi_ra","Xi_ra",Xi_HF0_lumi);
  Xi_ra->Add(Xi_HF0_03_lumi);
  Xi_ra->Divide(Xi_HF0_lumi);
  Xi_ra->SetTitle("Fraction of HF=0 events with Xi<0.03");
  NHSetMarker(Xi_ra, 2,20,1.2);
  NStatOff(Xi_ra);
  Xi_ra->Draw();
  Xi_ra->GetYaxis()->SetTitle("Fraction");
  Xi_ra->GetXaxis()->SetTitle("Luminosity 10^{30} cm^{-2}s^{-1}");
  return;
}





 
