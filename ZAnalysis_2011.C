#include <TH2.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "string.h"
#include <sstream>
#include <iomanip>
#include <TRandom.h>
#include "NCutil.C"
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

void Data10Z2Comp(){

  Int_t const Nbin = 20;
  TH1F *Pyt[Nbin];
  TH1F *Dat[Nbin];

  TFile *fzee = new TFile("ZDiffOutputfile.root");
  TString NT[Nbin];

  NCanvas(2,2,"HFNVTX1");
  NCanvas(2,2,"HF0NVTX1");
  NCanvas(2,2,"NVTX1_A");
  NCanvas(2,2,"NVTX1_B");
  NCanvas(2,2,"NoCuts");

  NT[0] = "HFNVTX1_nPart_PF_";
  NT[1] = "HFNVTX1_Xi_PF_";
  NT[2] = "HFNVTX1_vertexMolteplicity_";
  NT[3] = "HFNVTX1_nTowersHF_plus_";



  NT[4] = "HF0NVTX1_nPart_PF_";
  NT[5] = "HF0NVTX1_Xi_PF_";
  NT[6] = "HF0NVTX1_etaZ_";
  NT[7] = "HF0NVTX1_etaWeightedOnEnergy_PF_";

  NT[8] = "NVTX1_minEHF_";
  NT[9] = "NVTX1_EHF_";
  NT[10] = "NVTX1_max_eta_gap_PF_";
  NT[11] = "NVTX1_Mx_";

  NT[12] = "NVTX1_nTowersHF_plus_";
  NT[13] = "NVTX1_Xi_PF_";
  NT[14] = "NVTX1_etaZ_";
  NT[15] = "NVTX1_etaWeightedOnEnergy_PF_";

  NT[16] = "NoCuts_GoodVtx_";
  NT[17] = "NoCuts_Xi_PF_";
  NT[18] = "NoCuts_minEHF_";
  NT[19] = "NoCuts_max_eta_gap_PF_";







  for (Int_t ii = 0; ii<Nbin ; ii++)
    {
      Pyt[ii]  =  (TH1F*)fzee->Get(NT[ii]+"PythiaZ2");
      Dat[ii]  =  (TH1F*)fzee->Get(NT[ii]+"Data10");

      cout << NT[ii] << " " << ii << " " << Dat[ii]<< endl;
      
      if (ii<=3) HFNVTX1->cd(ii+1);
      else if (ii>3 && ii<=7)  HF0NVTX1->cd(ii-3);
      else if (ii>7 && ii<=11) NVTX1_A->cd(ii-7);
      else if (ii>11 && ii<=15) NVTX1_B->cd(ii-11);
      else if (ii>15 && ii<=19) NoCuts->cd(ii-15);

      Pyt[ii]->SetLineColor(2);

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

}
