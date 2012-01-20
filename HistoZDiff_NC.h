#ifndef HistoZDiff_NC.h
#define HistoZDiff_NC.h
#define ZAnalysisBase_cxx

/** \class Histograms
 *
 * A set of histograms for ZDiff candidates.
 *
 *  Adapted from a code of Amapane, Botta 
 */
#include "TH1F.h"
#include "TH2F.h"
#include "TString.h"
#include "TFile.h"
#include "Math.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

class HCand {
 public:

  HCand(const TString& name1_, const TString& name2_)  {

    TString N1 = name1_;
    TString N2 = name2_;
    TString N3;


    const Double_t xlow[12] = {0., 4.,10.,20.,40.,60.,80.,100.,120.,140.,160.,180.};
    TH1F::SetDefaultSumw2(kTRUE);
    hminEHF = new TH1F(N1+"_minEHF_"+N2,N1+"_minEHF_"+N2, 20, 0., 1000);
    hminEHFZoom = new TH1F(N1+"_minEHFZoom_"+N2,N1+"_minEHFZoom_"+N2,10,xlow);
    hEHF = new TH1F(N1+"_EHF_"+N2,N1+"_EHF_"+N2, 40, 0., 2000.);
    hEHFZoom = new TH1F(N1+"_EHFZoom_"+N2,N1+"_EHFZoom_"+N2, 10,xlow);
    hXi_PF = new TH1F(N1+"_Xi_PF_"+N2,N1+"_Xi_PF_"+N2, 50, 0., 0.5);
    hGoodVtx = new TH1F(N1+"_GoodVtx_"+N2,N1+"_GoodVtx_"+N2, 21, -0.5, 20.5);
    hPU_NumInt = new TH1F(N1+"_PU_NumInt_"+N2,N1+"_PU_NumInt_"+N2, 21, -0.5, 20.5);
    hnPart_PF = new TH1F(N1+"_nPart_PF_"+N2,N1+"_nPart_PF_"+N2, 40, -0.5, 400.5);
    hvertexMolteplicity = new TH1F(N1+"_vertexMolteplicity_"+N2,N1+"_vertexMolteplicity_"+N2, 40, -0.5, 200.5);
    hMx = new TH1F(N1+"_Mx_"+N2,N1+"_Mx_"+N2, 50, 0., 3000);
    hZMass = new TH1F(N1+"_ZMass_"+N2,N1+"_ZMass_"+N2, 40, 40., 120.);
    hmax_eta_gap_PF = new TH1F(N1+"_max_eta_gap_PF_"+N2,N1+"_max_eta_gap_PF_"+N2, 30, 0.,6.);

    hetaZ = new TH1F(N1+"_etaZ_"+N2,N1+"_etaZ_"+N2, 20, -5.,5.);
    hetaWeightedOnEnergy_PF = new TH1F(N1+"_etaWeightedOnEnergy_PF_"+N2,N1+"_etaWeightedOnEnergy_PF_"+N2, 20, -5.,5.);
    N3 = "_nTowersHF_plus_";
    hnTowersHF_plus = new TH1F(N1+N3+N2,N1+N3+N2, 50, 0.,100.);

    N3 = "_EBarrel_";
    hEBarrel = new TH1F(N1+N3+N2,N1+N3+N2, 25, 0.,500.);
    N3 = "_EEndcap_";
    hEEndcap = new TH1F(N1+N3+N2,N1+N3+N2, 30, 0.,1500.);
    N3 = "_EtaEnergy_";
    hEtaEnergy = new TH1F(N1+N3+N2,N1+N3+N2, 40, -5., 5.);


  }


  ~HCand(){
  }

  void Fill(float minEHF, float EHF, float xi_min, int GoodVtx,
	    int PU_NumInt, int nPart_PF, int nVtx, float Mx,
	    float ZMass, float max_eta_gap_PF,
	    float etaZ, float etaWeightedOnEnergy_PF, int nTowersHF_plus,
	    float EB, float EEminus,float EEplus,
	    std::vector<float>& EtaE,
	    float weight) 
  {

    
    hEBarrel->Fill(EB, weight);
    hEEndcap->Fill(EEminus, weight);
    hEEndcap->Fill(EEplus, weight);
    hminEHF->Fill(minEHF,weight);
    hminEHFZoom->Fill(minEHF,weight);
    hEHF->Fill(EHF,weight);
    hEHFZoom->Fill(EHF,weight);
    hXi_PF->Fill(xi_min,weight);
    hGoodVtx->Fill(GoodVtx,weight);
    hPU_NumInt->Fill(PU_NumInt,weight);
    hnPart_PF->Fill(nPart_PF,weight);
    hvertexMolteplicity->Fill(nVtx,weight);
    hMx->Fill(Mx,weight);
    hZMass->Fill(ZMass,weight);
    hmax_eta_gap_PF->Fill(max_eta_gap_PF,weight);
    hetaZ->Fill(etaZ,weight);
    hetaWeightedOnEnergy_PF->Fill(etaWeightedOnEnergy_PF, weight);
    hnTowersHF_plus->Fill(nTowersHF_plus ,weight);

    for (Int_t i=0;i<40;i++) hEtaEnergy->SetBinContent(i+1, EtaE[i]);
    // for (Int_t i=0;i<40;i++) hEtaEnergy->AddBinContent(i+1, 1);

  }


  void WriteInFile(std::string filename){

    TFile fOut(filename.c_str(),"UPDATE");
    fOut.cd();

    hEBarrel->Write();
    hEEndcap->Write();
    hminEHF->Write();
    hminEHFZoom->Write();
    hEHF->Write();
    hEHFZoom->Write();
    hXi_PF->Write();
    hGoodVtx->Write(); 
    hPU_NumInt->Write();
    hnPart_PF->Write();
    hvertexMolteplicity->Write();
    hMx->Write();
    hZMass->Write();
    hmax_eta_gap_PF->Write();
    hetaZ->Write();
    hetaWeightedOnEnergy_PF->Write();
    hnTowersHF_plus->Write();
    //Float_t scale = hZMass->GetEntries();
    //cout << "N entries in histo: = " << scale <<  endl;
    //hEtaEnergy->Scale(1./(scale+1.));
    hEtaEnergy->Write();

    fOut.Close();
  }

 public:

  TH1F * hEBarrel;
  TH1F * hEEndcap;
  TH1F * hminEHFZoom;
  TH1F * hminEHF;
  TH1F * hEHFZoom;
  TH1F * hEHF;
  TH1F * hXi_PF;
  TH1F * hGoodVtx;
  TH1F * hPU_NumInt;
  TH1F *  hnPart_PF;
  TH1F *  hvertexMolteplicity;
  TH1F * hMx;
  TH1F * hZMass;
  TH1F * hmax_eta_gap_PF;
  TH1F *hetaZ;
  TH1F *hetaWeightedOnEnergy_PF;
  TH1F *hnTowersHF_plus;
  TH1F *hEtaEnergy;
};

#endif
