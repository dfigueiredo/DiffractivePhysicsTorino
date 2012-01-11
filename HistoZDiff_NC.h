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


    TH1F::SetDefaultSumw2(kTRUE);
    hminEHF = new TH1F(N1+"_minEHF_"+N2,N1+"_minEHF_"+N2, 50, 0., 1000.);
    hEHF = new TH1F(N1+"_EHF_"+N2,N1+"_EHF_"+N2, 50, 0., 1000.);
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

  }


  ~HCand(){
  }

  void Fill(float minEHF, float EHF, float xi_min, int GoodVtx,
	    int PU_NumInt, int nPart_PF, int nVtx, float Mx,
	    float ZMass, float max_eta_gap_PF,
	    float etaZ, float etaWeightedOnEnergy_PF, int nTowersHF_plus,
	    float weight) 
  {

    hminEHF->Fill(minEHF,weight);
    hEHF->Fill(EHF,weight);
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
  }


  void WriteInFile(std::string filename){

    TFile fOut(filename.c_str(),"UPDATE");
    fOut.cd();

    hminEHF->Write();
    hEHF->Write();
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


    fOut.Close();
  }

 public:
  TH1F * hminEHF;
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

};

#endif
