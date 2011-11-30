#define JPsi_gap_cxx
#include "JPsi_gap.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <math.h>
#include "NCutil.C"

void JPsi_gap::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L JPsi_gap.C
//      Root > JPsi_gap t
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

   if (fChain == 0) return;

   TFile *fJP_Sep = new TFile("files/Dat_JPsiee_Sep.root");
   TTree *tree_JP_Sep = (TTree*)gDirectory->Get("tree_");

   TFile *fJP_Aug = new TFile("files/Dat_JPsiee_Aug.root");
   TTree *tree_JP_Aug = (TTree*)gDirectory->Get("tree_");

   Long64_t nentries = fChain->GetEntriesFast();

   gDirectory->Delete("JP_1");
   gDirectory->Delete("JP_all");
   gDirectory->Delete("JP");
   
   
   TH1F *JP_all = new TH1F("JP_all","Gap vs Inst. Lumi per bx; Inst.  Lumi per bx; Fraction",14 ,0.,0.7) ;

   NH1clone("JP_1","JP_1", JP_all);
   NH1clone("JP","JP", JP_all);

   JP->Sumw2();
   JP_1->Sumw2();
   JP_all->Sumw2();

   Long64_t nbytes = 0, nb = 0;

   TTree *fChain_files[2] = {tree_JP_Sep,tree_JP_Aug};

   for (int i=0;i<1;i++){
     
     fChain = fChain_files[i];
     Init(fChain);
     
     for (Long64_t jentry=0; jentry<nentries;jentry++) {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       
       if (numberOfVertexesInEvent==1) {
	 JP_all->Fill(istlumiPerBX*6.37);
	 if (sumEHF_minus_PF==0 || sumEHF_plus_PF==0) {
	   JP_1->Fill(istlumiPerBX*6.37);
	 }
       }
     }
   }

   JP_all->Draw();
   JP_1->Draw("SAMES");
   
}
