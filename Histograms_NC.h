#ifndef HistoZDiff_NC.h
#define HistoZDiff_NC.h

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

  HCand(const TString& name_)  {

    TString N = name_;

    TH1F::SetDefaultSumw2(kTRUE);

    // Plots for the candidate
    hHF = new TH1F(N+"_HFENERGY",N+"_HFENERGY", 100, 0., 100.);

  }

  HCand(TString name, TFile* file){
    //    TString N = "ZZ4muAnalysis/" + name;
    TString N = name;
    hHF = (TH1F *) file->Get(N+"_HFENERGY");    
  }


  ~HCand(){
  }

  // Assume that vectors are sorted!
  void Fill(float HFEnergy) {

    hHF->Fill(HFEnergy);
  }


  void WriteInFile(std::string filename){

    TFile fOut(filename.c_str(),"UPDATE");
    fOut.cd();

    hHF->Write();

    fOut.Close();
  }

 public:
  TH1F * hHF;

};

#endif
