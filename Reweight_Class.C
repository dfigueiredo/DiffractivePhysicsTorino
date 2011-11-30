#define Reweight_Class_cxx
#include "Reweight_Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLegend.h>
#include "string.h"
#include <iomanip>
#include "NCutil.C"

TH1F * ratio;
TH1F * Pyt_HF;
TH1F * Dat_HF;
TH1F * Dat_HF_LowLumi;
TH1F * Dat_HF_HighLumi;
TH1F * Ratio_HF_HighLumi;
TH1F * Ratio_HF_LowLumi;
TH1F * Ratio_HF;

TTree          *fChain;   //!Pointer to the analyzed TTree or TChain

const Int_t NDIR   = 2;  /* number or Directories*/

void Reweight_Class::Loop()
{

//   In a ROOT session, you can do:
//      Root > .L Reweight_Class.C
//      Root > Reweight_Class t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

  

  gDirectory->Delete("Pyt_HF");
  gDirectory->Delete("Dat_HF");
  gDirectory->Delete("Dat_HF_HighLumi");
  gDirectory->Delete("Dat_HF_LowLumi");
  gDirectory->Delete("Ratio_HF_LowLumi");
  gDirectory->Delete("Ratio_HF_HighLumi");
  gDirectory->Delete("Ratio_HF");

  Pyt_HF->Sumw2();
  Dat_HF->Sumw2();
  Ratio_HF->Sumw2();

 

  TCanvas *MyC = new TCanvas("MyC","Test canvas",1);
  MyC->Divide(1,2);

  for (Int_t i=1 ; i<=NDIR; i++){
    
    // Loop on Pythia and Dat
    
    if (i==1){
      TFile *fDat = (TFile*)gROOT->GetListOfFiles()->FindObject("files/pythiaD6T_ee_v1.root");
      if(!fDat)    fDat = new TFile("files/ZetaSkim_ee_v1.root");
    }
    else if (i==2){ 
      TFile *fDat = (TFile*)gROOT->GetListOfFiles()->FindObject("files/ZetaSkim_ee_v1.root");
      if(!fDat)    fDat = new TFile("files/ZetaSkim_ee_v1.root");
    };

    fChain = (TTree*)gDirectory->Get("tree_");
    //    fChain =tree; 
    Init(fChain);

  if (fChain == 0) return;
  
    
    Long64_t nentries = fChain->GetEntriesFast();
    
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(numberOfVertexes==1) 
	{
	  if (i==1) {
	    Pyt_HF->Fill(TMath::Min(sumEHF_minus,sumEHF_plus));
	  }
	  else if (i==2) {
	    if  (istlumiPerBX*6.37>0.005 && istlumiPerBX*6.37<0.2){
	      Dat_HF_LowLumi->Fill(TMath::Min(sumEHF_minus,sumEHF_plus));
	    }
	    else if  (istlumiPerBX*6.37>0.2){
	      Dat_HF_HighLumi->Fill(TMath::Min(sumEHF_minus,sumEHF_plus));
	    }
	  }
	  
	} // # of Vertexes
    } //jentry
  } //NDIR

} // ::Loop()
