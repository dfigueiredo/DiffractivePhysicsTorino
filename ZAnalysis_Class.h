//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec  1 11:36:00 2011 by ROOT version 5.30/02
// from TTree tree_/tree_
// found on file: files/zdiff/4_2/PythiaZ2_v2_1.root
//////////////////////////////////////////////////////////

#ifndef ZAnalysis_Class_h
#define ZAnalysis_Class_h
#define ZAnalysisBase_cxx



#include "ZAnalysisBase.h"
#include "ZAnalysisBase.C"
#include "HistoZDiff_NC.h"


#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
const Int_t kMaxtimestamp_timeLow = 1;
const Int_t kMaxtimestamp_timeHigh = 1;

class ZAnalysis_Class : public ZAnalysisBase {

 public:

  virtual ~ZAnalysis_Class()
    {
      
      if (!fChain) return;
      delete fChain->GetCurrentFile();
    };
  


   TFile *fA;
   TTree *tree_fA;
   TFile *fB;
   TTree *tree_fB;
   TFile *fC;
   TTree *tree_fC;
   TFile *fD;
   TTree *tree_fD;
   
   
   HCand* hCandNoCuts;
   HCand* hCandHF0;
   HCand* hCandNVTX1;
   HCand* hCandNVTX2;
   HCand* hCandNVTX3;
   HCand* hCandHF0NVTX1;
   HCand* hCandHFNVTX1;
   HCand* hCandSGETA1NVTX1;

   HCandGen* hCandGEN;
   

};

#endif

