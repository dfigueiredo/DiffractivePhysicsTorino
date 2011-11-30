#define Jpsi_Zee_correction_control_class_cxx
#include "Jpsi_Zee_correction_control_class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLegend.h>
#include "NCutil.C"
#include <iomanip>
#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;


TH1F *JPsi_all;
TH1F *Z_all;
TH1F *JPsi_HF0_ratio;
TH1F *JPsi_cor_ratio;
TH1F *Z_HF0_ratio;
TH1F *Z_cor_ratio;
TH1F *JPsi_HF0;
TH1F *JPsi_HF0_Cor;
TH1F *Z_HF0;
TH1F *Z_HF0_Cor;

TH1F *RunNumb_Z;
TH1F *RunNumb_JPsi;
TH1F *RunNumb_HF0_Z;
TH1F *RunNumb_HF0_JPsi;
TH1F *RunNumb_JPsi_ratio;
TH1F *RunNumb_Z_ratio;


const Int_t NDIR   = 4;  /* number or Directories*/

void Jpsi_Zee_correction_control_class::Loop()
{

  int nbin = 7;

  gDirectory->Delete("JPsi_all");
  gDirectory->Delete("JPsi_cor_ratio");
  gDirectory->Delete("JPsi_HF0_ratio");
  gDirectory->Delete("JPsi_HF0");
  gDirectory->Delete("JPsi_HF0_Cor");
  gDirectory->Delete("Z_all");
  gDirectory->Delete("Z__HF0_ratio");
  gDirectory->Delete("Z__cor_ratio");
  gDirectory->Delete("Z_HF0");
  gDirectory->Delete("Z_HF0_Cor");

  gDirectory->Delete("RunNumb_Z");
  gDirectory->Delete("RunNumb_HF0_Z");
  gDirectory->Delete("RunNumb_Z_ratio");
  gDirectory->Delete("RunNumb_JPsi");
  gDirectory->Delete("RunNumb_HF0_JPsi");
  gDirectory->Delete("RunNumb_JPsi_ratio");


  JPsi_all = new TH1F("JPsi_all", "JPsi_all", nbin, 0., 0.7);
  JPsi_HF0 = NH1clone("JPsi_HF0","JPsi_HF0", JPsi_all);
  JPsi_HF0_Cor = NH1clone("JPsi_HF0_Cor","JPsi_HF0_Cor", JPsi_all);
  JPsi_HF0_ratio = NH1clone("JPsi_HF0_ratio","JPsi_HF0_ratio", JPsi_all);
  JPsi_cor_ratio = NH1clone("JPsi_cor_ratio","JPsi_cor_ratio", JPsi_all);

  Z_HF0 = NH1clone("Z_HF0","Z_HF0", JPsi_all);
  Z_HF0_Cor = NH1clone("Z_HF0_Cor","Z_HF0_Cor", JPsi_all);
  Z_HF0_ratio = NH1clone("Z_HF0_ratio","Z_ratio", JPsi_all);
  Z_cor_ratio = NH1clone("Z_cor_ratio","Z_ratio", JPsi_all);
  Z_all = NH1clone("Z_all","Z_all", JPsi_all);

  RunNumb_Z = new TH1F("RunNumb_Z", "RunNumb",1000, 140000,150000);
  RunNumb_HF0_Z = NH1clone("RunNumb_HF0_Z","RunNumb_HF0",RunNumb_Z);
  RunNumb_Z_ratio = NH1clone("RunNumb_HF0_ratio","RunNumb_HF0_ratio",RunNumb_Z);

  RunNumb_JPsi = NH1clone("RunNumb_JPsi","RunNumb_JPsi",RunNumb_Z);
  RunNumb_HF0_JPsi = NH1clone("RunNumb_HF0_JPsi","RunNumb_HF0",RunNumb_Z);
  RunNumb_JPsi_ratio = NH1clone("RunNumb_JPsi_ratio","RunNumb_Castor_ratio",RunNumb_Z);


  JPsi_all->Sumw2();
  JPsi_HF0->Sumw2();
  JPsi_HF0_Cor->Sumw2();
  JPsi_HF0_ratio->Sumw2();
  JPsi_cor_ratio->Sumw2();
  Z_all->Sumw2();
  Z_HF0->Sumw2();
  Z_HF0_Cor->Sumw2();
  Z_HF0_ratio->Sumw2();
  Z_cor_ratio->Sumw2();

  RunNumb_Z->Sumw2();
  RunNumb_JPsi->Sumw2();
  RunNumb_HF0_JPsi->Sumw2();
  RunNumb_HF0_Z->Sumw2();
  RunNumb_JPsi_ratio->Sumw2();
  RunNumb_Z_ratio->Sumw2();



  TFile *Zmm = new TFile("files/ZetaSkim_mm_v1.root");
  // TFile *Zmm = new TFile("files/Run2010B_mm_v1.root");
  TTree *tree_Zmm= (TTree*)gDirectory->Get("tree_");

  TFile *Zee = new TFile("files/ZetaSkim_ee_v1.root");
  // TFile *Zee = new TFile("files/Run2010B_ee_v1.root");
  TTree *tree_Zee= (TTree*)gDirectory->Get("tree_");


  // TFile *JPsi = new TFile("files/oldfiles/Dat_JPsiee_Sep.root");
  TFile *JPsi_Sep = new TFile("files/JPsiSep_ee_v1.root");
  TTree *tree_JPsi_Sep= (TTree*)gDirectory->Get("tree_");

  TFile *JPsi_Aug = new TFile("files/JPsiAug_ee_v1.root");
  TTree *tree_JPsi_Aug= (TTree*)gDirectory->Get("tree_");



//   In a ROOT session, you can do:
//      Root > .L Jpsi_Zee_correction_control_class.C
//      Root > Jpsi_Zee_correction_control_class t
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

 for (Int_t i=1 ; i<=NDIR; i++){
    
    // Loop and RunA
    
    if (i==1){
      fChain =tree_Zee;  /* Loop RunB */ 
    }
    else if (i==2){ 
      fChain =tree_Zmm;  /* Loop RunB */ 
    }
    else if (i==3){ 
      fChain =tree_JPsi_Aug;  /* Loop Aug */ 
    }
    else if (i==4){ 
      fChain =tree_JPsi_Sep;  /* Loop Sept */ 
    }
    
    Init(fChain);
    
    if (fChain == 0) return;


   Long64_t nentries = fChain->GetEntriesFast();
   cout << "for i = " << i << " entries =" << nentries << endl; 

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);



      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if(numberOfVertexes==1 && istlumiPerBX*6.37>0.005) 
	{
	  if (TMath::Min(sumEHF_PF_minus,sumEHF_PF_plus)<4. && (sumEHF_PF_minus+sumEHF_PF_plus)>4. && RunNumber<1499900)
	    // if ( (etaMax_PF<2.85 || etaMin_PF>-2.85) && !(etaMax_PF<2.85 && etaMin_PF>-2.85) )
	    {
	      if(i==1 || i==2){
		Z_HF0_Cor->Fill(istlumiPerBX*6.37,HFCor(istlumiPerBX));
		Z_HF0->Fill(istlumiPerBX*6.37);
		RunNumb_HF0_Z->Fill(RunNumber);

	      }
	      if (i == 3 || i == 4) {
		JPsi_HF0->Fill(istlumiPerBX*6.37);
		RunNumb_HF0_JPsi->Fill(RunNumber);
		JPsi_HF0_Cor->Fill(istlumiPerBX*6.37,HFCor(istlumiPerBX));
		 }
	    }
	  if(i==1 || i==2){
	    Z_all->Fill(istlumiPerBX*6.37);
	    RunNumb_Z->Fill(RunNumber);
	  }
	  if (i == 3 || i ==4 ) {
	    JPsi_all->Fill(istlumiPerBX*6.37);
	    RunNumb_JPsi->Fill(RunNumber);
	  }
	}
   }
   
 }
 Z_HF0_ratio->Divide(Z_HF0,Z_all);
 Z_HF0_ratio->SetMarkerColor(4);
 Z_HF0_ratio->SetLineColor(4);
 Z_HF0_ratio->SetMaximum(0.03);
 Z_HF0_ratio->SetStats(kFALSE);
 Z_HF0_ratio->Draw();
 /*TF1 HF = new TF1("HF","3.2*(0.008325-0.01899*x+0.01151*x*x)",0.,0.6);
 HF.SetLineColor(4); 
 HF.SetLineStyle(4);
 HF.Draw("SAME"); */
 JPsi_HF0_ratio->Divide(JPsi_HF0,JPsi_all);
 JPsi_HF0_ratio->SetMarkerColor(2);
 JPsi_HF0_ratio->SetLineColor(2);
 JPsi_HF0_ratio->Draw("SAME");
 /* TF1 HF1("HF1","1.4*(0.008325-0.01899*x+0.01151*x*x)",0.,0.4);
 HF1.SetLineColor(2); 
 HF1.SetLineStyle(2);
 HF1.Draw("SAME"); */
 Z_HF0_ratio->GetXaxis()->SetTitle("Luminosity per bx [10^{30} cm^{-2}s^{-1}]");
 Z_HF0_ratio->GetYaxis()->SetTitle("Fraction"); 
 Z_HF0_ratio->GetYaxis()->SetTitleOffset(1.3);
 Z_HF0_ratio->SetTitle("Fraction of Events with HF = 0");
 NText(0.2,0.02,"Z->ee && Z->\mu \mu",4);
 NText(0.1,0.002,"JPsi->ee (and more)",2);

}

