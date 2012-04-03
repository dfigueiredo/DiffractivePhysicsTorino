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



void FindMCPUWeight(){

  NCanvas(1,2,"data");
  
  TH1F * Data;
  TH1F * DataVtx;
  TH1F * PytZ2;
  TH1F * PytZ2_Vis;
  
  TFile *fzee = new TFile("ZDiffOutputfile.root");
  
  Data  =  (TH1F*)fzee->Get("NoCuts_InstLumiPerBx_DATA10");
  DataVtx  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_DATA10");  
  PytZ2  =  (TH1F*)fzee->Get("Gen_PUVtx_Z2PY6");
  PytZ2_Vis  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_Z2PY6");
  
  Float_t DataInt = Data->Integral(); 
  
  data->cd(1);
  
  NSetTitle(Data,"Single bunch luminosity [10^{30}cm^{-2}s^{-1}]","Entries");
  NSetLabelSize(Data);
  NSetTitleSize(Data,0.8,0.8,0.06);
  NStat(Data,0);
  Data->SetTitle("Z Luminosity");
  NHSetMarker(Data);
  Data->Draw();
  
  
  Int_t const NRS = 1000;
  //  Float_t Sigma = 0.0485;
  Float_t Sigma = 0.073;
  Int_t const MaxVtxInEvent = 25;
  Float_t sigma_NSD =  Sigma*pow(10,-24);
  char hname[100]; 
  sprintf(hname,"Pois_Theory");
  gDirectory->Delete(hname);
  TH1F * pois_theory  = new TH1F(hname,hname,MaxVtxInEvent,-0.5,MaxVtxInEvent-0.5); // Pois hystograms
  pois_theory->Sumw2();
  
  for (Int_t NL = 1; NL<=NRS; NL++)
    {
      
      Double_t LumiR = Data->GetRandom();
      
      for (Int_t p=0;p<MaxVtxInEvent;p++)
	{
	  
	  Float_t Lum_bunch = (LumiR*pow(10,30)/11346)*sigma_NSD ;
	  Float_t pois_prob = pow(Lum_bunch,p) * exp(-Lum_bunch)/TMath::Factorial(p) ;		
	  pois_theory->Fill(p+0.01,pois_prob);
	  
	}
    }
  
  if (pois_theory->GetEntries() !=0)
    {
      pois_theory->Scale(DataInt/NRS);
      data->cd(2);
      NSetTitle(pois_theory,"# PU Vertexes in event","Fraction");
      NSetLabelSize(pois_theory);
      NSetTitleSize(pois_theory,0.8,0.8,0.06);
      NStat(pois_theory,0);
      pois_theory->SetTitle("MC PU generated vertex distribution");
      //	    pois_theory->SetTitleSize(1.);
      NHSetMarker(pois_theory);
      DataVtx->Draw();  
      pois_theory->Draw("SAME HIST");
      
    }
  
  //
  //	PytZ2->Scale(1./scale);
  
  Float_t scale = PytZ2_Vis->Integral()/PytZ2->Integral();
  cout << "MC scale =" << scale << endl;
  
  cout << "Float_t Z2Weight[] = {" ;
  for (Int_t j = 1;j<=19; j++)
    { 
      Float_t   ra = scale*pois_theory->GetBinContent(j)/PytZ2->GetBinContent(j);
      cout <<  ra << ", " ;
    }
  cout << " 0 }; " << endl;
  return;
}



// Number of vertices in 2010-11
void Vertex1011(){

  NCanvas(1,1,"data");
  TH1F * Dat10;
  TH1F * Dat11;

  //TFile *fzee = new TFile("ZDiffOutputfile.root");
  TFile *fzee = new TFile("ZDiffOutputfile_73Weight2010.root");
  TFile *fzee1 = new TFile("ZDiffOutputfile_73Weight2011.root");
  Dat10  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_DATA10");
  Dat11  =  (TH1F*)fzee1->Get("NoCuts_GoodVtx_DATA10");
  //Dat11->SetBinContent(1,0);
  //Dat10->SetBinContent(1,0);
  data->cd(1);
  NLogAxis(0,1);
  Dat11->Draw();
  Dat11->GetXaxis()->SetTitle("Number of PU");
  Dat11->GetYaxis()->SetTitle("Entries");
  Dat11->SetTitle("# of PU vertexes for Z->ee events");
  Dat10->Draw("SAME HIST");

 
  TLegend *legend = new TLegend(0.6,0.7,0.75,0.8);
  legend->SetTextFont(72);
  NHSetMarker(Dat11,4,20,0.4);
  NHSetMarker(Dat10,2,20,0.4);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);

  legend->AddEntry(Dat11,"2011","p");
  legend->AddEntry(Dat10,"2010","l");
  legend->Draw();
  

}


// Number of vertices in 2010-11
void VertexMult(){

  NCanvas(1,1,"data");
  TH1F * Pyt;
  TH1F * Dat11;

  TFile *fzee = new TFile("ZDiffOutputfile.root");
  //TFile *fzee = new TFile("ZDiffOutputfile_73Weight2011.root");
  Dat11  =  (TH1F*)fzee->Get("NoCuts_vertexMolteplicity_DATA");
  Pyt  =  (TH1F*)fzee->Get("NoCuts_vertexMolteplicity_Z2PY6");
  data->cd(1);
  NLogAxis(1,1);
  Dat11->Draw();
  Dat11->GetXaxis()->SetTitle("Vertex Track Multiplicity");
  Dat11->GetYaxis()->SetTitle("Entries");
  Dat11->SetTitle("Vertex Multiplicity for Z->ee events");
  Pyt->Draw("SAME HIST");

 
  TLegend *legend = new TLegend(0.6,0.7,0.75,0.8);
  legend->SetTextFont(72);
  NHSetMarker(Dat11,4,20,0.4);
  NHSetMarker(Pyt,2,20,0.4);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->AddEntry(Dat11,"2011","p");
  legend->AddEntry(Pyt,"PYTHIA Z2","l");
  legend->Draw();
  

}




void FindZ2HFWeight(){

  NCanvas(2,2,"test");
  TH1F * Pyt1;
  TH1F * Dat1;
  TH1F * Pyt2;
  TH1F * Dat2;

  TH1F * DifPyt;
  TH1F * DifDat;

  TFile *fzee = new TFile("ZDiffOutputfile_Weight2011.root");
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

  NT[k++] = "NVTX1_nPart_PF_";
  NT[k++] = "NVTX1_Xi_PF_";
  NT[k++] = "NVTX1_vertexMolteplicity_";
  NT[k++] = "NVTX1_nTowersHF_plus_";

  NT[k++] = "HF0NVTX1_nPart_PF_";
  NT[k++] = "HF0NVTX1_Xi_PF_";
  NT[k++] = "HF0NVTX1_etaZ_";
  NT[k++] = "HF0NVTX1_vertexMolteplicity_";


  NT[k++] = "NVTX1_EBarrel_";
  NT[k++] = "NVTX1_EEndcap_";
  //  NT[k++] = "NVTX1_EHF_S_";
  //NT[k++] = "NVTX1_EHF_L_";
  NT[k++] = "NVTX1_EHF_";
  NT[k++] = "NVTX2_EBarrel_";
  NT[k++] = "NVTX2_EEndcap_";
  NT[k++] = "NVTX2_EHF_";
  NT[k++] = "NVTX2_EBarrel_";
  NT[k++] = "NVTX2_EEndcap_";
  NT[k++] = "NVTX2_EHF_";

  NT[k++] = "NVTX1_nTowersHF_plus_";
  NT[k++] = "NVTX1_max_eta_gap_PF_";
  NT[k++] = "NVTX1_etaZ_";
  NT[k++] = "NVTX1_vertexMolteplicity_";

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
      Dat[ii]  =  (TH1F*)fzee->Get(NT[ii]+"DATA");

      Pyt[ii]->SetMinimum(1.) ;
      Dat[ii]->SetMinimum(1.);

      cout << NT[ii] << " " << ii << " " << Dat[ii]<< endl;

      Int_t k1 = 3;
      Int_t k2 = 7;

      if (ii<= k1) HFNVTX1->cd(ii+1);
      if (ii>k1 && ii<= k2)  HF0NVTX1->cd(ii-k1);
      k1 = k2;
      k2 = k1+9;
      if (ii> k1 && ii<= k2) NVTX1_A->cd(ii-k1);
      k1 = k2;
      k2 = k1+4;
      //      cout << "k1 = " << k1 << " k2 = " << k2 << endl;
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
  
  Int_t const Nhist = 8;

  TH1F * Pyt[Nhist];
  TH1F * Dat[Nhist];
  TH1F * Pom[Nhist];

  //  TFile *fzee11 = new TFile("ZDiffOutputfile2011_AllLumi.root");
  //  TFile *fzee10 = new TFile("ZDiffOutputfile_73Weight2010.root");

  TFile *fzee10 = new TFile("ZDiffOutputfile2010HFCorEHFMinS.root");
  TFile *fzee11 = new TFile("ZDiffOutputfile2011HFCorEHFMinS.root");




  //  cout<< fzee << endl;

  TString NT[Nhist];
  //NT[0] = "NVTX1_max_eta_gap_PF_";
  NT[0] = "HF0NVTX1_Gap_Calo_";
  NT[0] = "HF0NVTX1_etaZ_";
  //  NT[1] = "HF0NVTX1_MaxEtaGap_";
  NT[1] = "HF0_etaWeightedOnEnergy_PF_";
    NT[2] = "HF0NVTX1_Xi_Calo_";
  NT[3] = "HF0NVTX1_Xi_PF_";

  //HFyear2010
  NT[4] = "NVTX1_EHFZoom_";
  NT[5] = "NVTX1_EHFZoom_L_";
  NT[6] = "NVTX1_EHFZoom_S_";
  NT[7] = "NVTX1_minEHFZoom_";
  //  NT[1] = "NVTX1_EHFZoom_L_";

  TString Str[Nhist];

  Str[0] = "Eta Z";
  Str[1] = "MaxEtaGap";
  Str[2] = "Xi_Calo";
  Str[3] = "Xi_PF";
  Str[4] = "Cor EHF Tot ";
  Str[5] = "Cor EHF L ";
  Str[6] = "Cor EHF S ";
  Str[7] = "Cor EHFMin ";

  NCanvas(2,2,"year2010");  
  NCanvas(2,2,"year2011");
  NCanvas(2,2,"HFyear2010");  
  NCanvas(2,2,"HFyear2011");  

  for (Int_t i=0;i<Nhist;i++)
    {
      Pyt[i]  =  (TH1F*)fzee10->Get(NT[i]+"Z2PY6");  
      Dat[i]  =  (TH1F*)fzee10->Get(NT[i]+"DATA");
      Pom[i]  =  (TH1F*)fzee10->Get(NT[i]+"POMPYT");

      cout << Dat[i] << " i " << i << endl;
      if (Pyt[i] == 0)
	{
	  cout << " Pythia Pointers not assigned" << endl;
	  return;
	}

      if (Pom[i] == 0)
	{
	  cout << " Pompyt Pointers not assigned" << endl;
	  return;
	}

      if (Dat[i] == 0)
	{
	  cout << " Data Pointers not assigned" << endl;
	  return;
	}

      if (i<4) 
	{
	  year2010->cd(i+1);
	  gPad->SetLogx(0);
	  gPad->SetLogy(1);
	}
      else  
	{
	  HFyear2010->cd(i-3);
	  gPad->SetLogx(0);
	  gPad->SetLogy(0);
	}

      NFitMCToData(Dat[i], Pyt[i], Pom[i], Str[i]);
    


      Pyt[i]  =  (TH1F*)fzee11->Get(NT[i]+"Z2PY6");  
      Dat[i]  =  (TH1F*)fzee11->Get(NT[i]+"DATA");
      Pom[i]  =  (TH1F*)fzee11->Get(NT[i]+"POMPYT");

      cout << Dat[i] << " i " << i << endl;
      if (Pyt[i] == 0)
	{
	  cout << " Pythia Pointers not assigned" << endl;
	  return;
	}

      if (Pom[i] == 0)
	{
	  cout << " Pompyt Pointers not assigned" << endl;
	  return;
	}

      if (Dat[i] == 0)
	{
	  cout << " Data Pointers not assigned" << endl;
	  return;
	}


      if (i<4) 
	{
	  year2011->cd(i+1);
	  gPad->SetLogx(0);
	  gPad->SetLogy(1);
	}
      else  
	{
	  HFyear2011->cd(i-3);
	  gPad->SetLogx(0);
	  gPad->SetLogy(0);
	}

      NFitMCToData(Dat[i], Pyt[i], Pom[i], Str[i]);

    }

  return;

}  

void EFlowHF_SL ()
{
  
  Int_t const Nhist = 11;

  TH1F * Pyt[Nhist];
  TH1F * Dat[Nhist];
  TH1F * Ra[Nhist];


  // TFile *fzee = new TFile("ZDiffOutputfile2010HFCorEHFMinS.root");
  TFile *fzee = new TFile("ZDiffOutputfile2011HFCorEHFMinS_AllLumi.root");

  //  cout<< fzee << endl;

  TString NT[Nhist];

  NT[0] = "NVTX1_EHFSGT0_SL_";
  NT[1] = "NVTX1_EHFLGT0_SL_";
  NT[2] = "NVTX1_EHFSLGT0_SL_";
  NT[3] = "NVTX1_EtaEnergy_S_";
  NT[4] = "NVTX1_EtaEnergy_L_";
  NT[5] = "NVTX1_EtaEnergy_";
  NT[6] = "NVTX2_EtaEnergy_";
  NT[7] = "NVTX2_EtaEnergy_S_";
  NT[8] = "NVTX2_EtaEnergy_L_";
  NT[9] = "NVTX3_EtaEnergy_S_";
  NT[10] = "NVTX3_EtaEnergy_L_";

  TString Str[Nhist];

  Str[0] = "VTX1 HF_S>0";
  Str[1] = "VTX1 HF_L>0";
  Str[2] = "VTX1 HF_SL>0 ";
  Str[3] = "VTX1 HF_S ";
  Str[4] = "VTX1 HF_L ";
  Str[5] = "VTX1 EFlow ";
  Str[6] = "VTX2 EFlow ";
  Str[7] = "VTX2 HF_S ";
  Str[8] = "VTX2 HF_L ";
  Str[9] = "VTX3 HF_S ";
  Str[10] = "VTX3 HF_L ";


  NCanvas(3,2,"VTX1_HF_SL");
  NCanvas(2,2,"VTX1_HF");
  NCanvas(2,2,"VTX2_HF");
  NCanvas(2,2,"VTX3_HF");
  NCanvas(2,2,"VTX1_EFlow");


  for (Int_t i=0;i<Nhist;i++)
    {
      Pyt[i]  =  (TH1F*)fzee->Get(NT[i]+"Z2PY6");  
      Dat[i]  =  (TH1F*)fzee->Get(NT[i]+"DATA");

      if (Pyt[i] == 0 || Dat[i] == 0) 
	{
	  cout << "Pointers not assigned" << endl;
	  return;
	}
      if(i<3)
	{
	  VTX1_HF_SL->cd(i+1);
	  gPad->SetLogx(0);
	  gPad->SetLogy(1);
	  NSetTitle(Dat[i],"Events","HF Energy [GeV]");
	  NSetLabelSize(Dat[i],0.01,0.01,0.04);
	  NSetTitleSize(Dat[i],0.8,0.8,0.06);
	  NStat(Dat[i],0);
	  NHSetLine(Dat[i],2,1,1.);
	  NHSetLine(Pyt[i],4,2,1.);

	  Dat[i]->SetTitle(Str[i]);
	  Dat[i]->GetXaxis()->SetRange(0,30);
	  Dat[i]->Draw();
	  Pyt[i]->Draw("SAME HIST");
	  //      Dat[i]->Divide(Pyt[i]);
	  //Dat[i]->Draw();

	  Ra[i] = (TH1F*) Dat[i]->Clone();
	  Ra[i]->Divide(Pyt[i]);

	  TLegend *legend = new TLegend(0.4,0.6,0.7,0.8);
	  legend->SetTextFont(72);
	  legend->SetTextSize(0.05);
	  legend->SetBorderSize(0.);
	  legend->AddEntry(Dat[i],"Data","l");
	  legend->AddEntry(Pyt[i]," Z2","l");
	  legend->Draw();

	  VTX1_HF_SL->cd(i+4);
	  NHSetMarker(Ra[i],4,20,0.4);
	  NSetTitle(Ra[i],"Enery","Ratio");
	  Ra[i]->SetMaximum(2);
	  Ra[i]->SetMinimum(0.5);
	  Ra[i]->Draw("P");

	}
      else if (i>=3 && i<5)
	{
	  VTX1_HF->cd(i-2);
	  NSetTitle(Dat[i],"Rapidity","Energy [GeV]");
	  NSetLabelSize(Dat[i]);
	  NSetTitleSize(Dat[i],0.8,0.8,0.06);
	  NStat(Dat[i],0);
	  NHSetLine(Dat[i],2,1,1.);
	  NHSetLine(Pyt[i],4,2,1.);

	  Dat[i]->SetTitle(Str[i]);
	  //	  Dat[i]->SetMaximum(30);
	  Dat[i]->Draw();	
	  Dat[i]->Fit("pol1");	  
  
	  Pyt[i]->Draw("SAME HIST");
	  Ra[i] = (TH1F*) Dat[i]->Clone();
	  Ra[i]->Divide(Pyt[i]);

	  
	  TLegend *legend = new TLegend(0.4,0.6,0.7,0.8);
	  legend->SetTextFont(72);
	  legend->SetTextSize(0.05);
	  legend->SetBorderSize(0.);
	  legend->AddEntry(Dat[i],"Data","l");
	  legend->AddEntry(Pyt[i]," Z2","l");
	  legend->Draw();

	  VTX1_HF->cd(i);
	  NHSetMarker(Ra[i],4,20,0.4);
	  NSetTitle(Ra[i],"Rapidity","Ratio");
	  Ra[i]->SetMaximum(1.6);
	  Ra[i]->Draw("P");

	}
      else if (i>=5 && i<7) // EFlow
	{
	  VTX1_EFlow->cd(i-4);
	  NSetTitle(Dat[i],"Rapidity","Energy/Event [GeV]");
	  NSetLabelSize(Dat[i],0.01,0.01,0.04);
	  NSetTitleSize(Dat[i],0.9,0.9,0.05);
	  NStat(Dat[i],0);
	  NHSetLine(Dat[i],2,1,1.);
	  NHSetLine(Pyt[i],4,2,1.);

	  Dat[i]->SetTitle(Str[i]);
	  Dat[i]->SetMaximum(160);

	  Dat[i]->Draw();
	  
	  Pyt[i]->Draw("SAME HIST");
	  Ra[i] = (TH1F*) Dat[i]->Clone();
	  Ra[i]->Divide(Pyt[i]);
	  
	  TLegend *legend = new TLegend(0.4,0.7,0.8,0.8);
	  legend->SetTextFont(72);
	  legend->SetTextSize(0.05);
	  legend->SetBorderSize(0.);
	  legend->AddEntry(Dat[i],"Data","l");
	  legend->AddEntry(Pyt[i]," Z2","l");
	  legend->Draw();


	  VTX1_EFlow->cd(i-2);
	  NHSetMarker(Ra[i],4,20,0.4);
	  NSetTitle(Ra[i],"Rapidity","Ratio");
	  Ra[i]->SetMaximum(1.8);
	  Ra[i]->SetMinimum(0);
	  Ra[i]->Draw("P");
	}
      else if (i>=7 && i<9)
	{
	  VTX2_HF->cd(i-6);
	  NSetTitle(Dat[i],"Rapidity","Energy [GeV]");
	  NSetLabelSize(Dat[i]);
	  NSetTitleSize(Dat[i],0.8,0.8,0.06);
	  NStat(Dat[i],0);
	  NHSetLine(Dat[i],2,1,1.);
	  NHSetLine(Pyt[i],4,2,1.);

	  Dat[i]->SetTitle(Str[i]);
	  //	  Dat[i]->SetMaximum(30);
	  Dat[i]->Draw();	
	  Dat[i]->Fit("pol1");	  
  
	  Pyt[i]->Draw("SAME HIST");
	  Ra[i] = (TH1F*) Dat[i]->Clone();
	  Ra[i]->Divide(Pyt[i]);

	  
	  TLegend *legend = new TLegend(0.4,0.6,0.7,0.8);
	  legend->SetTextFont(72);
	  legend->SetTextSize(0.05);
	  legend->SetBorderSize(0.);
	  legend->AddEntry(Dat[i],"Data","l");
	  legend->AddEntry(Pyt[i]," Z2","l");
	  legend->Draw();

	  VTX2_HF->cd(i-4);
	  NHSetMarker(Ra[i],4,20,0.4);
	  NSetTitle(Ra[i],"Rapidity","Ratio");
	  Ra[i]->SetMaximum(1.6);
	  Ra[i]->Draw("P");

	}

      else if (i>=9 && i<11)
	{
	  VTX3_HF->cd(i-8);
	  NSetTitle(Dat[i],"Rapidity","Energy [GeV]");
	  NSetLabelSize(Dat[i]);
	  NSetTitleSize(Dat[i],0.8,0.8,0.06);
	  NStat(Dat[i],0);
	  NHSetLine(Dat[i],2,1,1.);
	  NHSetLine(Pyt[i],4,2,1.);

	  Dat[i]->SetTitle(Str[i]);
	  //	  Dat[i]->SetMaximum(30);
	  Dat[i]->Draw();	
	  Dat[i]->Fit("pol1");	  
  
	  Pyt[i]->Draw("SAME HIST");
	  Ra[i] = (TH1F*) Dat[i]->Clone();
	  Ra[i]->Divide(Pyt[i]);

	  
	  TLegend *legend = new TLegend(0.4,0.6,0.7,0.8);
	  legend->SetTextFont(72);
	  legend->SetTextSize(0.05);
	  legend->SetBorderSize(0.);
	  legend->AddEntry(Dat[i],"Data","l");
	  legend->AddEntry(Pyt[i]," Z2","l");
	  legend->Draw();

	  VTX3_HF->cd(i-6);
	  NHSetMarker(Ra[i],4,20,0.4);
	  NSetTitle(Ra[i],"Rapidity","Ratio");
	  Ra[i]->SetMaximum(1.6);
	  Ra[i]->Draw("P");

	}



    }


  return;

}  



void EtaCharged()
{
  NCanvas(1,2,"data");

  TH1F * HDatHF0;
  TH1F * HDat;

  TFile *fzee = new TFile("ZDiffOutputfile.root");
  // TFile *fzee = new TFile("ZDiffOutputfile.root");
  HDat  =  (TH1F*)fzee->Get("NoCuts_max_eta_charged_PF_DATA");
  
  HDatZ2  =  (TH1F*)fzee->Get("NoCuts_max_eta_charged_PF_Z2PY6");
  data->cd(1);
  HDat->Draw();
  NSetTitle(HDat,"Eta", "Entries");
  HDat->SetTitle("EtaMax Charged PrimaryVertex");
  HDatZ2->Draw("SAME HIST");
  NHSetMarker(HDat,2,20,0.4);
  TLegend *legend = new TLegend(0.6,0.7,0.9,0.8);
  legend->SetTextFont(72);
  legend->SetTextSize(0.06);
  legend->SetBorderSize(0);


  legend->AddEntry(HDat,"Data","p");
  legend->AddEntry(HDatZ2,"PYTHIA Z2","l");
  legend->Draw();


  TH1F * Hra = (TH1F * ) HDatZ2->Clone();
  //  Hra->GetXaxis->SetRange(0,12);
  NStat(Hra,0);
  Hra->Divide(HDat);
  NLogAxis(0,1);
  data->cd(2);

  Hra->Draw();
  Hra->SetTitle("");

  NSetTitle(Hra,"Eta", "Ratio");
  NLogAxis(0,0);
}

void ZVXT1HF0()
{

  NCanvas(1,1,"data");
  NCanvas(1,1,"ratio");

  TH1F * HDatHF0;
  TH1F * HDat;

  TFile *fzee = new TFile("ZDiffOutputfile_DataOnly_2010_2011.root");
  // TFile *fzee = new TFile("ZDiffOutputfile.root");
  HDat  =  (TH1F*)fzee->Get("NVTX1_InstLumiPerBx_DATA10");
  
  HDatHF0  =  (TH1F*)fzee->Get("HF0NVTX1_InstLumiPerBx_DATA10");
  data->cd(1);
  HDat->Draw();
  NSetTitle(HDat,"Luminosity [10^{-30} cm^{-2} s^{-1}]", "Entries");
  HDat->SetTitle("Number of Z produced in events without PU");
  HDatHF0->Draw("SAME HIST");
  NHSetMarker(HDat,2,20,0.4);
  TLegend *legend = new TLegend(0.6,0.7,0.9,0.8);
  legend->SetTextFont(72);
  legend->SetTextSize(0.03);
  legend->SetBorderSize(0);


  legend->AddEntry(HDat,"All Z","p");
  legend->AddEntry(HDatHF0,"Z with minE_HF=0","l");
  legend->Draw();


  TH1F * Hra = (TH1F * ) HDatHF0->Clone();
  //  Hra->GetXaxis->SetRange(0,12);
  NStat(Hra,0);
  Hra->Divide(HDat);
  NLogAxis(0,1);
  ratio->cd(1);

  Hra->Draw();
  Hra->SetTitle("Fraction of Z with (PU=0 && E_HF=0)");
  Hra->Fit("expo","","",0.,1.2);
  NSetTitle(Hra,"Luminosity [10^{-30} cm^{-2} s^{-1}]", "Fraction");
  NLogAxis(0,1);
  NText(.05,0.1, "0.62");
  NText(0.3,0.1, "2.47");
  NText(0.7,0.1, "4.93");
  NText(1.1,0.1, "7.4");
  NText(1.4,0.1, "<Number of Int.>");


}



void ZVXT1NVTX()
{

  NCanvas(1,1,"data");
  NCanvas(1,1,"ratio");

  TH1F * HDatHF0;
  TH1F * HDat;

  TFile *fzee = new TFile("ZDiffOutputfile_DataOnly_2010_2011.root");
  // TFile *fzee = new TFile("ZDiffOutputfile.root");
  HDat  =  (TH1F*)fzee->Get("NoCuts_InstLumiPerBx_DATA10");
  
  HDatNVTX1  =  (TH1F*)fzee->Get("NVTX1_InstLumiPerBx_DATA10");
  data->cd(1);
  HDat->Draw();
  NStat(HDat,0);

  NSetTitle(HDat,"Luminosity [10^{-30} cm^{-2} s^{-1}]", "Entries");
  HDat->SetTitle("Z production luminosity");
  HDatNVTX1->Draw("SAME HIST");
  NHSetMarker(HDat,2,20,0.4);
  TLegend *legend = new TLegend(0.6,0.7,0.9,0.8);
  legend->SetTextFont(72);
  legend->SetTextSize(0.03);
  legend->SetBorderSize(0);


  legend->AddEntry(HDat,"All Z","p");
  legend->AddEntry(HDatNVTX1,"Z with PU=0","l");
  legend->Draw();


  TH1F * Hra = (TH1F * ) HDatNVTX1->Clone();
  //  Hra->GetXaxis->SetRange(0,12);
  NStat(Hra,0);
  Hra->Divide(HDat);
  NLogAxis(0,1);
  ratio->cd(1);
  Hra->Draw();
  Hra->SetTitle("Fraction of Z with PU=0");
  //  Hra->Fit("expo","","",0.1,1.2);
  NSetTitle(Hra,"Luminosity [10^{-30} cm^{-2} s^{-1}]", "Fraction");
  NLogAxis(0,1);
}


void EflowCASTOR()
{

  NCanvas(1,2,"data");

  TH1F * HDat;
  TH1F * HZ2;

  //  TFile *fzee = new TFile("ZDiffOutputfile_73Weight2010.root");
  TFile *fzee = new TFile("ZDiffOutputfile.root");
  // TFile *fzee = new TFile("ZDiffOutputfile.root");
  HDat  =  (TH1F*)fzee->Get("NVTX1_EnergyCastorModule_DATA");
  HZ2  =  (TH1F*)fzee->Get("NVTX1_EnergyCastorModule_Z2PY6");
  data->cd(1);
  NHSetMarker(HDat,2,20,0.8);
  HDat->SetMinimum(10);
  HDat->Draw();
  NStat(HDat,0);
  NSetTitle(HDat,"CASTOR Modules", "Entries");

  HDat->SetTitle("CASTOR Module Energy 2010");
  HZ2->Draw("SAME HIST");
  NHSetMarker(HDat,2,20,0.4);
  TLegend *legend = new TLegend(0.6,0.7,0.9,0.8);
  legend->SetTextFont(72);
  legend->SetTextSize(0.06);
  legend->SetBorderSize(0);


  legend->AddEntry(HDat,"Data2010","p");
  legend->AddEntry(HZ2,"Z2","l");
  legend->Draw();


  TH1F * Hra = (TH1F * ) HDat->Clone();
  //  Hra->GetXaxis->SetRange(0,12);
  NStat(Hra,0);
  NHSetMarker(Hra,4,20,0.8);
  Hra->SetMinimum(1);
  Hra->Divide(HZ2);
  NLogAxis(0,0);
  data->cd(2);
  Hra->Draw();
  Hra->SetTitle("Ratio DATA/MC");
  Hra->Fit("pol0");
  NSetTitle(Hra,"CASTOR Modules", "Ratio");
  NLogAxis(0,1);

}


void FindNoPUBx()
{

  TH1F * HDat;
  TH1F * HDat1;

  //  TFile *fzee = new TFile("ZDiffOutputfile_73Weight2010.root");
  TFile *fzee = new TFile("ZDiffOutputfile_Data2011_noPU.root");
  // TFile *fzee = new TFile("ZDiffOutputfile.root");
  HDat  =  (TH1F*)fzee->Get("NoCuts_bx_DATA10");
  HDat1  =  (TH1F*)fzee->Get("NVTX1_bx_DATA10");
  Float_t NBins = NoCuts_bx_DATA10->GetNbinsX();


	cout << "PU =0 for bx -3,-2,-1" << endl;
  for (Int_t i = 4;i<NBins;i++)
    {
      if (  NVTX1_bx_DATA10->GetBinContent(i-3) < 2 &&
	    NVTX1_bx_DATA10->GetBinContent(i-2) < 2 &&
	    NVTX1_bx_DATA10->GetBinContent(i-1) < 2 &&
	    NVTX1_bx_DATA10->GetBinContent(i) >2 )


	cout << "bx == " << i-1  << " || ";
    }
	cout << endl;

	cout << "PU =0 for bx -,1,2,3" << endl;
  for (Int_t i = 4;i<NBins;i++)
    {
      if (  NVTX1_bx_DATA10->GetBinContent(i+3) < 2 &&
	    NVTX1_bx_DATA10->GetBinContent(i+2) < 2 &&
	    NVTX1_bx_DATA10->GetBinContent(i+1) < 2 &&
	    NVTX1_bx_DATA10->GetBinContent(i) >2 )


	cout << "bx == " << i-1  << " || ";
    }
	cout << endl;


	cout << "PU =0 for bx -2,-1,1,2" << endl;
	  for (Int_t i = 4;i<NBins;i++)
	    {
	      if (  NVTX1_bx_DATA10->GetBinContent(i-1) < 2 &&
		    NVTX1_bx_DATA10->GetBinContent(i-2) < 2 &&
		    NVTX1_bx_DATA10->GetBinContent(i+2) < 2 &&
		    NVTX1_bx_DATA10->GetBinContent(i+1) < 2 &&
		    NVTX1_bx_DATA10->GetBinContent(i) >2 )
		
		
		cout << "bx == " << i-1  << " || ";
	    }
	cout << endl;
	




}



void CheckEHF()
{

 
  TH1F * HDat;
  TH1F * HDatnoPUAft;
  TH1F * HDatnoPUBef;

  //  TFile *fzee = new TFile("ZDiffOutputfile_73Weight2010.root");
  TFile *fzee = new TFile("ZDiffOutputfile_Data2011_noPU.root");
  // TFile *fzee = new TFile("ZDiffOutputfile.root");
  HDat  =  (TH1F*)fzee->Get("NVTX1_minEHFZoom_DATA10");
  HDatnoPUAft  =  (TH1F*)fzee->Get("NVTX1noPUAft_minEHFZoom_DATA10");
  HDatnoPUBef  =  (TH1F*)fzee->Get("NVTX1noPUBef_minEHFZoom_DATA10");

  HDat->Scale(1./HDat->GetEntries());
  HDatnoPUAft->Add(HDatnoPUBef);
  HDatnoPUAft->Scale(1./HDatnoPUAft->GetEntries());
  HDatnoPUBef->Scale(1./HDatnoPUBef->GetEntries());
  HDatnoPUAft->SetMinimum(0.);
  NHSetMarker(HDatnoPUAft,2,20,0.8);
  NHSetLine(HDatnoPUAft,2,1,1.);
  HDatnoPUAft->Draw("E1");
  HDatnoPUAft->SetTitle("2011 Z->ee Data, minHF Energy");
  NSetTitle(HDatnoPUAft,"HF Energy [GeV]", "Fraction");


  NHSetMarker(HDatnoPUBef,6,20,0.8);
  NHSetLine(HDatnoPUBef,6,1,1.);
  // HDatnoPUBef->Draw("SAMEP");

  NHSetMarker(HDat,4,20,0.8);
  NHSetLine(HDat,1,1,1.);
  HDat->Draw("SAMEP");

  TLegend *legend = new TLegend(0.6,0.1,0.75,0.4);
  legend->SetTextFont(72);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);

  legend->AddEntry(HDatnoPUBef,"No PU before or after","p");
  //  legend->AddEntry(HDatnoPUBef,"No PU before","p");
  // legend->AddEntry(HDatnoPUAft,"No PU after","p");
  legend->AddEntry(HDat,"PU before && after","p");
  legend->Draw();






  //  NHSetLine(HDatnoPUBef,3,2,1.);
  // HDatnoPUBef->Draw("SAME HIST");

}
