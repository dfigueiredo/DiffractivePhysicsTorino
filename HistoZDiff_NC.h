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

class HCand{
 public:

  HCand(const TString& name1_, const TString& name2_)  {

    TString N1 = name1_;
    TString N2 = name2_;

    TH1F::SetDefaultSumw2(kTRUE);
    hHF = new TH1F(N1+"_HFEnergy_"+N2,N1+"_HFEnergy_"+N2, 100, 0., 500.);
    hXi_PF = new TH1F(N1+"_Xi_PF_"+N2,N1+"_Xi_PF_"+N2, 100, 0., 0.5);
    hGoodVtx = new TH1F(N1+"_GoodVtx_"+N2,N1+"_GoodVtx_"+N2, 21, -0.5, 20.5);
    hPU_NumInt = new TH1F(N1+"_PU_NumInt_"+N2,N1+"_PU_NumInt_"+N2, 21, -0.5, 20.5);

  }

  HCand(TString name, TFile* file){
    TString N = name;
    hHF = (TH1F *) file->Get(N+"_HFEnergy");    
  }


  ~HCand(){
  }

  void Fill(float HFEnergy, float xi, int GoodVtx, int PU_NumInt, float weight) 
  {

    hHF->Fill(HFEnergy,weight);
    hXi_PF->Fill(xi,weight);
    hGoodVtx->Fill(GoodVtx,weight);
    hPU_NumInt->Fill(PU_NumInt,weight);
  }


  void WriteInFile(std::string filename){

    TFile fOut(filename.c_str(),"UPDATE");
    fOut.cd();

    hHF->Write();
    hXi_PF->Write();
    hXi_PF->Write();
    hGoodVtx->Write();
    hPU_NumInt->Write();

    fOut.Close();
  }

 public:
  TH1F * hHF;
  TH1F * hXi_PF;
  TH1F * hGoodVtx;
  TH1F * hPU_NumInt;

};

#endif
