#include <TH2.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "string.h"
#include <sstream>
#include <iomanip>
#include <TRandom.h>
#include "NClasses.h"
#include <iostream>
#include <fstream>
#include <TMath.h> 
#include <TProfile.h> 

void FindZ2Weight(){
  TH1F * Pyt;
  TH1F * Dat;

  TFile *fzee = new TFile("ZDiffOutputfile.root");
  Pyt  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_PythiaZ2");
  Dat  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_Data10");

  Float_t scale = Pyt->Integral()/Dat->Integral();
  cout << "Scaling factor to conserve MC luminosity = " << scale << endl;
  Dat->Divide(Pyt);
  //  Dat->Scale(scale);
  Dat->Draw();
  cout << "Float_t Z2Weight[] = {" ;
  for (Int_t j = 1;j<=19; j++)   cout <<  Dat->GetBinContent(j) << ", " ;
  cout << " 0 }; " << endl;
}


void FindZ2HFWeight(){

  NCanvas(2,2,"test");
  TH1F * Pyt1;
  TH1F * Dat1;
  TH1F * Pyt2;
  TH1F * Dat2;

  TH1F * DifPyt;
  TH1F * DifDat;

  TFile *fzee = new TFile("ZDiffOutputfile.root");
  Pyt1  =  (TH1F*)fzee->Get("NVTX1_nTowersHF_plus_PythiaZ2");
  Dat1  =  (TH1F*)fzee->Get("NVTX1_nTowersHF_plus_Data10");

  Pyt2  =  (TH1F*)fzee->Get("NVTX2_nTowersHF_plus_PythiaZ2");
  Dat2  =  (TH1F*)fzee->Get("NVTX2_nTowersHF_plus_Data10");
  test->cd(1);
  Pyt1->Draw();
  Dat1->Draw("SAMEH");
  test->cd(2);
  Pyt2->Draw();
  Dat2->Draw("SAMEH");
  test->cd(3);
  DifDat = (TH1F*)Dat1->Clone();
  DifPyt = (TH1F*)Pyt1->Clone();

  DifDat->Add(Dat2,-1);
  DifPyt->Add(Pyt2,-1);
  DifDat->Draw();
  DifPyt->Draw("SAMEH");

}

void Data10Z2Comp(){

  Int_t const Nbin = 28;
  TH1F *Pyt[Nbin];
  TH1F *Dat[Nbin];

  TFile *fzee = new TFile("ZDiffOutputfile.root");
  TString NT[Nbin];

  NCanvas(2,2,"HFNVTX1");
  NCanvas(2,2,"HF0NVTX1");
  NCanvas(2,2,"NVTX1_A");
  NCanvas(2,2,"NVTX1_B");
  NCanvas(2,2,"NVTX2_A");
  NCanvas(2,2,"NVTX3_A");
  NCanvas(2,2,"NoCuts");

  NT[0] = "HFNVTX1_nPart_PF_";
  NT[1] = "HFNVTX1_Xi_PF_";
  NT[2] = "HFNVTX1_vertexMolteplicity_";
  NT[3] = "HFNVTX1_nTowersHF_plus_";

  NT[4] = "HF0NVTX1_nPart_PF_";
  NT[5] = "HF0NVTX1_Xi_PF_";
  NT[6] = "HF0NVTX1_etaZ_";
  NT[7] = "HF0NVTX1_etaWeightedOnEnergy_PF_";

  NT[8] = "NVTX1_EHF_";
  NT[9] = "NVTX1_EHFZoom_";
  NT[10] = "NVTX1_EBarrel_";
  NT[11] = "NVTX1_EEndcap_";


  NT[12] = "NVTX1_nTowersHF_plus_";
  NT[13] = "NVTX1_max_eta_gap_PF_";
  NT[14] = "NVTX1_etaZ_";
  NT[15] = "NVTX1_etaWeightedOnEnergy_PF_";

  NT[16] = "NoCuts_GoodVtx_";
  NT[17] = "NoCuts_Xi_PF_";
  NT[18] = "NoCuts_minEHF_";
  NT[19] = "NoCuts_max_eta_gap_PF_";

  NT[20] = "NVTX2_EHF_";
  NT[21] = "NVTX2_EHFZoom_";
  NT[22] = "NVTX2_EBarrel_";
  NT[23] = "NVTX2_EEndcap_";

  NT[24] = "NVTX3_EHF_";
  NT[25] = "NVTX3_EHFZoom_";
  NT[26] = "NVTX3_EBarrel_";
  NT[27] = "NVTX3_EEndcap_";






  for (Int_t ii = 0; ii<Nbin ; ii++)
    {
      Pyt[ii]  =  (TH1F*)fzee->Get(NT[ii]+"PythiaZ2");
      Dat[ii]  =  (TH1F*)fzee->Get(NT[ii]+"Data10");

      Pyt[ii]->SetMinimum(1.) ;
      Dat[ii]->SetMinimum(1.);

      cout << NT[ii] << " " << ii << " " << Dat[ii]<< endl;
      
      if (ii<=3) HFNVTX1->cd(ii+1);
      else if (ii>3 && ii<=7)  HF0NVTX1->cd(ii-3);
      else if (ii>7 && ii<=11) NVTX1_A->cd(ii-7);
      else if (ii>11 && ii<=15) NVTX1_B->cd(ii-11);
      else if (ii>15 && ii<=19) NoCuts->cd(ii-15);
      else if (ii>19 && ii<=23) NVTX2_A->cd(ii-19);
      else if (ii>23 && ii<=27) NVTX3_A->cd(ii-23);

      Pyt[ii]->SetLineColor(2);
      NStat(Pyt[ii],1);
      NStat(Dat[ii],1);

       if(Dat[ii]->GetMaximum()>Pyt[ii]->GetMaximum())     
	{
	  Dat[ii]->Draw();
	  Pyt[ii]->Draw("HIST SAME ");     
	}
      else
	{
	  Pyt[ii]->Draw("HIST");
	  Dat[ii]->Draw("SAME P ");     
	}


    }




  HFNVTX1->Print("HFNVTX1.gif");
  HF0NVTX1->Print("HF0NVTX1.gif");
  NVTX1_A->Print("NVTX1_A.gif");
  NVTX1_B->Print("NVTX1_B.gif");
  NVTX2_A->Print("NVTX2_A.gif");
  NVTX3_A->Print("NVTX3_A.gif");
  NoCuts->Print("NoCuts.gif");



}

void fit2histo ()
{
  
  TH1F * Pyt[2];
  TH1F * Dat[2];
  TH1F * Pom[2];

  TFile *fzee = new TFile("ZDiffOutputfile.root");

  //  cout<< fzee << endl;

  TString NT[3];
  NT[0] = "NVTX1_max_eta_gap_PF_";
  NT[1] = "HFNVTX1_max_eta_gap_PF_";
  NT[2] = "HF0NVTX1_max_eta_gap_PF_";

  TString Str[3];

  Str[0] = "Eta gap, 1 vxt";
  Str[1] = "Eta gap, 1 vxt && HF != 0";
  Str[2] = "Eta gap, 1 vxt && HF ==0 ";


  NCanvas(2,2,"EtaGap");

  for (Int_t i=0;i<3;i++)
    {
      Pyt[i]  =  (TH1F*)fzee->Get(NT[i]+"PythiaZ2");  
      Dat[i]  =  (TH1F*)fzee->Get(NT[i]+"Data10");
      Pom[i]  =  (TH1F*)fzee->Get(NT[i]+"Pompyt");


      if (Pyt[i] == 0 || Dat[i] == 0 || Pom[i] ==0 ) 
	{
	  cout << "Pointers not assigned" << endl;
	  return;
	}
      EtaGap->cd(i+1);
      gPad->SetLogx(0);
      gPad->SetLogy(1);
      NFitMCToData(Dat[i], Pyt[i], Pom[i], Str[i]);
    }


  return;

}  

