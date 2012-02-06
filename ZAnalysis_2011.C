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

  NCanvas(1,1,"data");
  NCanvas(1,1,"ratio");

  TH1F * Pyt;
  TH1F * Dat;
  TH1F * Data;

  TFile *fzee = new TFile("ZDiffOutputfile.root");
  Pyt  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_Z2PY6");
  Dat  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_DATA10");
  Data  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_DATA10");
  data->cd(1);
  Data->Draw();

  Float_t scale = Pyt->Integral()/Dat->Integral();
  cout << "Scaling factor to conserve MC luminosity = " << scale << endl;
  ratio->cd(1);
  Dat->Divide(Pyt);
  //  Dat->Scale(scale);
  Dat->Draw();
  cout << "Float_t Z2Weight[] = {" ;
  for (Int_t j = 1;j<=19; j++)   cout <<  Dat->GetBinContent(j) << ", " ;
  cout << " 0 }; " << endl;
}


void FindC4Weight(){

  NCanvas(1,1,"data");
  NCanvas(1,1,"ratio");

  TH1F * Pyt;
  TH1F * Dat;
  TH1F * Data;

  TFile *fzee = new TFile("ZDiffOutputfile.root");
  Pyt  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_4CPY8");
  Dat  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_DATA10");
  Data  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_DATA10");
  data->cd(1);
  Data->Draw();

  Float_t scale = Pyt->Integral()/Dat->Integral();
  cout << "Scaling factor to conserve MC luminosity = " << scale << endl;
  ratio->cd(1);
  Dat->Divide(Pyt);
  //  Dat->Scale(scale);
  Dat->Draw();
  cout << "Float_t C4Weight[] = {" ;
  for (Int_t j = 1;j<=19; j++)   cout <<  Dat->GetBinContent(j) << ", " ;
  cout << " 0 }; " << endl;
}



// Number of vertices in 2010
void Vertex2010(){

  NCanvas(1,1,"data");
  TH1F * Dat;

  TFile *fzee = new TFile("ZDiffOutputfile.root");
  Dat  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_Data10");
  data->cd(1);
  NLogAxis(0,1);
  Dat->Draw();
  Dat->GetXaxis()->SetTitle("Number of PU");
  Dat->GetYaxis()->SetTitle("Entries");
  Dat->GetYaxis()->SetTitle("Entries");
  Dat->SetTitle("# of PU vertexes for Z->ee events in 2010");
  Int_t nVtx0 = Dat->GetBinContent(1);
 

  NText (10,100,"Num");
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

  Int_t const Nbin = 33;
  TH1F *Pyt[Nbin];
  TH1F *Dat[Nbin];

  TFile *fzee = new TFile("ZDiffOutputfile.root");
  TString NT[Nbin];

  NCanvas(2,2,"HFNVTX1");
  NCanvas(2,2,"HF0NVTX1");
  NCanvas(3,3,"NVTX1_A");
  NCanvas(2,2,"NVTX1_B");
  NCanvas(2,2,"NVTX2_A");
  NCanvas(2,2,"NVTX3_A");
  NCanvas(2,2,"NoCuts");

  Int_t k = 0;

  NT[k++] = "HFNVTX1_nPart_PF_";
  NT[k++] = "HFNVTX1_Xi_PF_";
  NT[k++] = "HFNVTX1_vertexMolteplicity_";
  NT[k++] = "HFNVTX1_nTowersHF_plus_";

  NT[k++] = "HF0NVTX1_nPart_PF_";
  NT[k++] = "HF0NVTX1_Xi_PF_";
  NT[k++] = "HF0NVTX1_etaZ_";
  NT[k++] = "HF0NVTX1_etaWeightedOnEnergy_PF_";


  //  NT[k++] = "NVTX1_EBarrel_";
  // NT[k++] = "NVTX1_EEndcap_";
  NT[k++] = "NVTX1_EHF_S_";
  NT[k++] = "NVTX1_EHF_L_";
  NT[k++] = "NVTX1_EHF_";
  NT[k++] = "NVTX2_EBarrel_";
  NT[k++] = "NVTX2_EEndcap_";
  NT[k++] = "NVTX2_EHF_";
  NT[k++] = "NVTX3_EBarrel_";
  NT[k++] = "NVTX3_EEndcap_";
  NT[k++] = "NVTX3_EHF_";

  NT[k++] = "NVTX1_nTowersHF_plus_";
  NT[k++] = "NVTX1_max_eta_gap_PF_";
  NT[k++] = "NVTX1_etaZ_";
  NT[k++] = "NVTX1_etaWeightedOnEnergy_PF_";

  NT[k++] = "NoCuts_GoodVtx_";
  NT[k++] = "NoCuts_Xi_PF_";
  NT[k++] = "NoCuts_minEHF_";
  NT[k++] = "NoCuts_max_eta_gap_PF_";

  NT[k++] = "NVTX2_EHF_";
  NT[k++] = "NVTX2_EHFZoom_";
  NT[k++] = "NVTX2_EBarrel_";
  NT[k++] = "NVTX2_EEndcap_";

  NT[k++] = "NVTX3_EHF_";
  NT[k++] = "NVTX3_EHFZoom_";
  NT[k++] = "NVTX3_EBarrel_";
  NT[k++] = "NVTX3_EEndcap_";

  for (Int_t ii = 0; ii<Nbin ; ii++)
    {
      Pyt[ii]  =  (TH1F*)fzee->Get(NT[ii]+"Z2PY6");
      Dat[ii]  =  (TH1F*)fzee->Get(NT[ii]+"DATA10");

      Pyt[ii]->SetMinimum(1.) ;
      Dat[ii]->SetMinimum(1.);

      cout << NT[ii] << " " << ii << " " << Dat[ii]<< endl;

      Int_t k1 = 3;
      Int_t k2 = 7;

      if (ii<= k1) HFNVTX1->cd(ii+1);
      if (ii>k1 && ii<= k2)  HF0NVTX1->cd(ii-k1);
      k1 = k2;
      k2 = k1+9;
      cout << "k1 = " << k1 << " k2 = " << k2 << endl;
      if (ii> k1 && ii<= k2) NVTX1_A->cd(ii-k1);
      k1 = k2;
      k2 = k1+4;
      cout << "k1 = " << k1 << " k2 = " << k2 << endl;
      if (ii>k1 && ii<= k2) NVTX1_B->cd(ii-k1);
      k1 = k2;
      k2 = k1+4;
      if (ii>k1 && ii<= k2) NoCuts->cd(ii-k1);
      k1 = k2;
      k2 = k1+4;
      if (ii>k1 && ii<=k2) NVTX2_A->cd(ii-k1);
      k1 = k2;
      k2 = k1+4;
      if (ii>k1 && ii<=k2) NVTX3_A->cd(ii-k1);

      Pyt[ii]->SetLineColor(2);
      NStat(Pyt[ii],1);
      NStat(Dat[ii],1);

       if(Dat[ii]->GetMaximum()>Pyt[ii]->GetMaximum())     
	{
	  Dat[ii]->Draw();
	  Pyt[ii]->Draw("HIST SAME ");     
	  Dat[ii]->SetXTitle("Energy [GeV]");
	  Dat[ii]->SetYTitle("Entries");
	  NStat(Dat[ii],0);
	  //	  NSetLabelSize(Dat[ii]);

	}
      else
	{
	  Pyt[ii]->Draw("HIST");
	  Dat[ii]->Draw("SAME P ");     
	  Pyt[ii]->SetXTitle("Energy [GeV]");
	  Pyt[ii]->SetYTitle("Entries");
	  NStat(Pyt[ii],0);
	  // NSetLabelSize(Pyt[ii]);
	}

       TLegend *legend = new TLegend(0.75,0.7,0.9,0.9);
       legend->SetTextFont(72);
       legend->SetTextSize(0.05);
       legend->AddEntry(Dat[ii],"Data","p");
       legend->AddEntry(Pyt[ii]," Z2","l");
       legend->Draw();
       
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
  
  Int_t const Nhist = 4;

  TH1F * Pyt[Nhist];
  TH1F * Dat[Nhist];
  TH1F * Pom[Nhist];

  TFile *fzee = new TFile("ZDiffOutputfile.root");

  //  cout<< fzee << endl;

  TString NT[Nhist];
  NT[0] = "SGETA1NVTX1_max_eta_gap_PF_";
  NT[1] = "SGETA1NVTX1_max_second_eta_gap_";
  NT[0] = "NVTX1_max_eta_gap_PF_";
  NT[1] = "NVTX1_max_second_eta_gap_";
  NT[2] = "HFNVTX1_max_eta_gap_PF_";
  NT[3] = "NVTX1_EHF_";

  TString Str[Nhist];

  Str[0] = "Eta gap, 1 vxt";
  Str[1] = "Second Eta gap, 1 vxt";
  Str[2] = "Eta gap, 1 vxt && HF !=0 ";
  Str[3] = "HF Energy ";


  NCanvas(1,2,"EtaGap");

  for (Int_t i=0;i<Nhist-2;i++)
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

