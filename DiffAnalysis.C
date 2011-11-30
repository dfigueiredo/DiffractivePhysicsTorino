#define DiffAnalysis_cxx
#include "DiffAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void DiffAnalysis::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L DiffAnalysis.C
//      Root > DiffAnalysis t
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

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   int nPass = 0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      //      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // NC: edit here to add more branches
      // read only these branches
      b_DiffRootuple_RunNumber->GetEntry(ientry);
      b_DiffRootuple_EventNumber->GetEntry(ientry);
      b_DiffRootuple_Lumi->GetEntry(ientry);
      b_DiffRootuple_HasTwoElectrons->GetEntry(ientry);
      b_DiffRootuple_ElectronsWithEnoughEt->GetEntry(ientry);
      b_DiffRootuple_istlumi->GetEntry(ientry);
      b_DiffRootuple_istlumierr->GetEntry(ientry);
      b_DiffRootuple_Epz->GetEntry(ientry);
      b_DiffRootuple_sumEHF_plus->GetEntry(ientry);
      b_DiffRootuple_sumEHF_minus->GetEntry(ientry);
      b_DiffRootuple_MinsumEHF_minus_plus->GetEntry(ientry);
      b_DiffRootuple_etaMax_Calo->GetEntry(ientry);
      b_DiffRootuple_etaMin_Calo->GetEntry(ientry);
      b_DiffRootuple_Epz_PF_minus->GetEntry(ientry);
      b_DiffRootuple_Epz_PF_plus->GetEntry(ientry);
      b_DiffRootuple_etaMax_PF->GetEntry(ientry);
      b_DiffRootuple_etaMin_PF->GetEntry(ientry);
      b_DiffRootuple_etaMax_PF_Vertex_Selection->GetEntry(ientry);
      b_DiffRootuple_etaMin_PF_Vertex_Selection->GetEntry(ientry);
      b_DiffRootuple_Epz_PF_minus_NOHF->GetEntry(ientry);
      b_DiffRootuple_Epz_PF_plus_NOHF->GetEntry(ientry);
      b_DiffRootuple_etaMax_PF_NOHF->GetEntry(ientry);
      b_DiffRootuple_etaMin_PF_NOHF->GetEntry(ientry);
      b_DiffRootuple_MoreThanOneVertex->GetEntry(ientry);
      b_DiffRootuple_xi_gen->GetEntry(ientry);
      b_DiffRootuple_nTowersHF_plus->GetEntry(ientry);
      b_DiffRootuple_nTowersHF_minus->GetEntry(ientry);
      b_DiffRootuple_etaAllTracks->GetEntry(ientry);
      b_DiffRootuple_energyTot->GetEntry(ientry);
      b_DiffRootuple_CastorMaxEnergy->GetEntry(ientry);
      b_DiffRootuple_ZDCMaxEnergy->GetEntry(ientry);
      b_DiffRootuple_etaWeightedOnEnergy->GetEntry(ientry);
      b_DiffRootuple_energyTot_Barrel->GetEntry(ientry);
      b_DiffRootuple_energyTot_minus->GetEntry(ientry);
      b_DiffRootuple_energyTot_plus->GetEntry(ientry); 

      // if (Cut(ientry) < 0) continue;
      // NC: Here goes the code to be added for each entry

            if (energyTot_Barrel>_cutEnergy) {
      cout  << jentry << " " << RunNumber << " " << energyTot_Barrel << endl;
      hNC->Fill(RunNumber);
      nPass++;
      }

   }
   cout << "NPASS " << nPass << endl;

   if ( _outF != 0 ) {
     _outF->cd();
     hNC->Write();
     _outF->Write();
     _outF->Close();
   }
   
   return;

}
