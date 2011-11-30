#define ZAnalysis_Class_cxx
#include "ZAnalysis_Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2F.h>
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


TFile *fA;
TTree *tree_fA;
TFile *fB;
TTree *tree_fB;

// TFile *fOut;



Int_t NDIR;  /* number or Directories*/      
string stringa;
string HistoLabel;
char hname[100]; 


void ZAnalysis_Class::Loop()
{

//   In a ROOT session, you can do:
//      Root > .L ZAnalysis_Class.C
//      Root > ZAnalysis_Class t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//


  NDIR   = 2;  /* number or Directories*/      
      
  fA = new TFile("files/zdiff/4_2/Run2010ARepro_ee_v2_0.root");
  TDirectory * dirA = (TDirectory*)fA->Get("files/zdiff/4_2/Run2010ARepro_ee_v2_0.root:/Selection");
  dirA->GetObject("tree_",tree_fA);

  fB = new TFile("files/zdiff/4_2/MC_PYTHIAZ2_v2_0.root");
  TDirectory * dirB = (TDirectory*)fB->Get("files/zdiff/4_2/MC_PYTHIAZ2_v2_0.root:/Selection");
  dirB->GetObject("tree_",tree_fB);

  // tree_fA= (TTree*)gDirectory->Get("tree_");
  
  // fB = new TFile("files/zdiff/4_2/Run2010ARepro_ee_v2_0.root");
  // tree_fB= (TTree*)gDirectory->Get("tree_");	  	  


  TFile *fOut = new TFile("ZOutputFile.root","recreate"); 


  for (Int_t i=1 ; i<=NDIR; i++){  
    if (i==1)
      {
	Init(tree_fA);
	fChain =tree_fA; 
	HistoLabel = "Data";
      }
    else if (i==2)
      { 
	Init(tree_fB);
	fChain =tree_fB; 
	HistoLabel = "PythiaZ2";
      }

    stringa = "HF_Energy_1vtx_"+HistoLabel;
    sprintf (hname,stringa.c_str());
    TH1F *EHF_1vtx  = new TH1F(hname,hname,10, 0.,1000.);

    stringa = "HF_Energy_"+HistoLabel;
    sprintf (hname,stringa.c_str());
    TH1F *EHF  = new TH1F(hname,hname,10, 0.,1000.);
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    
    cout << "Processing " << HistoLabel.c_str() << " with " << nentries << " events." << endl;

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {

      if (jentry % 100000 == 0) cout << "jentry = " << jentry << endl;
      Long64_t ientry = LoadTree(jentry);      
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      if(numberOfVertexes == 1) EHF_1vtx->Fill(sumEHF_plus);
      EHF->Fill(sumEHF_plus);
      
    }
    
    cout << "Writing out files " << endl;
    EHF->Write();
    EHF_1vtx->Write();

  } // NDIR Loop


  fOut->Close(); 

  return;
} 
