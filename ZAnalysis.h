//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 14 15:52:37 2011 by ROOT version 5.30/02
// from TTree tree_/tree_
// found on file: files/zdiff/4_2/Run2010ARepro_ee_v2_0.root
//////////////////////////////////////////////////////////

#ifndef ZAnalysis_h
#define ZAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
   const Int_t kMaxtimestamp_timeLow = 1;
   const Int_t kMaxtimestamp_timeHigh = 1;

class ZAnalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //DifNtuple       *Rootuple;
   UInt_t          RunNumber;
   UInt_t          EventNumber;
   UInt_t          Lumi;
   Double_t        InvariantMass;
   Float_t         istlumi;
   Float_t         istlumierr;
   Double_t        Epz_Calo_plus;
   Double_t        Epz_Calo_minus;
   Double_t        sumEHF_plus;
   Double_t        sumEHF_minus;
   Double_t        minEHF;
   Double_t        etaMax_Calo;
   Double_t        etaMin_Calo;
   Double_t        Epz_PF_minus;
   Double_t        Epz_PF_plus;
   Double_t        etaMax_PF;
   Double_t        etaMin_PF;
   Double_t        etaMax_Charged_PV_PF;
   Double_t        etaMin_Charged_PV_PF;
   Double_t        Epz_NOHF_PF_minus;
   Double_t        Epz_NOHF_PF_plus;
   Double_t        etaMax_NOHF_PF;
   Double_t        etaMin_NOHF_PF;
   Double_t        xi_gen;
   Double_t        Mx2_gen;
   Double_t        xi_NOZ_gen;
   Int_t           nTowersHF_plus;
   Int_t           nTowersHF_minus;
   Double_t        etaAllTracks_PF;
   Double_t        energyTot_PF;
   Double_t        sumEZDC_minus;
   Double_t        sumEZDC_plus;
   Double_t        sumECastor_gen_plus;
   Double_t        sumECastor_gen_minus;
   Double_t        sumEZDC_gen_minus;
   Double_t        sumEZDC_gen_plus;
   Double_t        etaWeightedOnEnergy_PF;
   Double_t        energyTot_PF_Barrel_minus;
   Double_t        energyTot_PF_Barrel_plus;
   Double_t        energyTot_PF_minus;
   Double_t        energyTot_PF_plus;
   Float_t         istlumiPerBX;
   Double_t        xi_PF_minus;
   Double_t        xi_PF_plus;
   Double_t        xi_Z_minus;
   Double_t        xi_Z_plus;
   Double_t        xi_Z_gen_minus;
   Double_t        xi_Z_gen_plus;
   Double_t        max_eta_gap_PF;
   Double_t        max_second_eta_gap_PF;
   UInt_t          timestamp_timeLow_;
   UInt_t          timestamp_timeHigh_;
   Double_t        xi_PF_charged_minus;
   Double_t        xi_PF_charged_plus;
   Int_t           nTracks_PF;
   Double_t        energyTot_PF_EE_minus;
   Double_t        energyTot_PF_EE_plus;
   Int_t           bx;
   Int_t           numberOfVertexes;
   Double_t        sumEHF_PF_minus;
   Double_t        sumEHF_PF_plus;
   Double_t        etaOutcomingProton;
   Double_t        mostEnergeticParticleGap_MC;
   Double_t        nParticles_gen;
   Double_t        sumECastor_Th_minus;
   Int_t           numberOfLeptons;
   Double_t        etaZ;
   vector<double>  vertexNDOF;
   Double_t        xi_PF_NOHF_minus;
   Double_t        xi_PF_NOHF_plus;
   vector<double>  vertexChiNorm;
   vector<double>  vertexMolteplicity;
   Bool_t          CastorActivity;
   vector<double>  vertexNumberOfRH;
   Double_t        xL_gen;
   Double_t        xL_Num_gen;
   Double_t        sumECastorRaw_minus;
   Double_t        sumECastor_minus;
   Double_t        pixelNCluster;
   vector<double>  V_x;
   vector<double>  V_y;
   vector<double>  V_z;
   Double_t        PV_x;
   Double_t        PV_y;
   Double_t        PV_z;
   Double_t        etaZ_gen;
   Double_t        lepton1Phi;
   Double_t        lepton1Eta;
   Double_t        lepton2Phi;
   Double_t        lepton2Eta;
   Double_t        Mx2;
   Double_t        M_x;
   Double_t        M_y;
   Double_t        M_z;
   Double_t        energyZ_gen;
   Double_t        xi_Calo_minus;
   Double_t        xi_Calo_plus;
   Double_t        p_diss_mass_gen;
   Double_t        xL_p_diss;
   vector<vector<double> > tracksPT;
   vector<double>  tracksPT_gen;
   Int_t           numberoOfTracks_gen;
   vector<double>  etaOfTracksPT_gen;
   vector<double>  electronEnergy;
   vector<double>  muEnergy;
   Int_t           PU_NumInt;
   vector<float>   PU_zpos;
   vector<int>     PU_ntrks_lowpT;
   vector<int>     PU_ntrks_highpT;
   vector<float>   PU_sumpT_lowpT;
   vector<float>   PU_sumpT_highpT;

   // List of branches
   TBranch        *b_Rootuple_RunNumber;   //!
   TBranch        *b_Rootuple_EventNumber;   //!
   TBranch        *b_Rootuple_Lumi;   //!
   TBranch        *b_Rootuple_InvariantMass;   //!
   TBranch        *b_Rootuple_istlumi;   //!
   TBranch        *b_Rootuple_istlumierr;   //!
   TBranch        *b_Rootuple_Epz_Calo_plus;   //!
   TBranch        *b_Rootuple_Epz_Calo_minus;   //!
   TBranch        *b_Rootuple_sumEHF_plus;   //!
   TBranch        *b_Rootuple_sumEHF_minus;   //!
   TBranch        *b_Rootuple_minEHF;   //!
   TBranch        *b_Rootuple_etaMax_Calo;   //!
   TBranch        *b_Rootuple_etaMin_Calo;   //!
   TBranch        *b_Rootuple_Epz_PF_minus;   //!
   TBranch        *b_Rootuple_Epz_PF_plus;   //!
   TBranch        *b_Rootuple_etaMax_PF;   //!
   TBranch        *b_Rootuple_etaMin_PF;   //!
   TBranch        *b_Rootuple_etaMax_Charged_PV_PF;   //!
   TBranch        *b_Rootuple_etaMin_Charged_PV_PF;   //!
   TBranch        *b_Rootuple_Epz_NOHF_PF_minus;   //!
   TBranch        *b_Rootuple_Epz_NOHF_PF_plus;   //!
   TBranch        *b_Rootuple_etaMax_NOHF_PF;   //!
   TBranch        *b_Rootuple_etaMin_NOHF_PF;   //!
   TBranch        *b_Rootuple_xi_gen;   //!
   TBranch        *b_Rootuple_Mx2_gen;   //!
   TBranch        *b_Rootuple_xi_NOZ_gen;   //!
   TBranch        *b_Rootuple_nTowersHF_plus;   //!
   TBranch        *b_Rootuple_nTowersHF_minus;   //!
   TBranch        *b_Rootuple_etaAllTracks_PF;   //!
   TBranch        *b_Rootuple_energyTot_PF;   //!
   TBranch        *b_Rootuple_sumEZDC_minus;   //!
   TBranch        *b_Rootuple_sumEZDC_plus;   //!
   TBranch        *b_Rootuple_sumECastor_gen_plus;   //!
   TBranch        *b_Rootuple_sumECastor_gen_minus;   //!
   TBranch        *b_Rootuple_sumEZDC_gen_minus;   //!
   TBranch        *b_Rootuple_sumEZDC_gen_plus;   //!
   TBranch        *b_Rootuple_etaWeightedOnEnergy_PF;   //!
   TBranch        *b_Rootuple_energyTot_PF_Barrel_minus;   //!
   TBranch        *b_Rootuple_energyTot_PF_Barrel_plus;   //!
   TBranch        *b_Rootuple_energyTot_PF_minus;   //!
   TBranch        *b_Rootuple_energyTot_PF_plus;   //!
   TBranch        *b_Rootuple_istlumiPerBX;   //!
   TBranch        *b_Rootuple_xi_PF_minus;   //!
   TBranch        *b_Rootuple_xi_PF_plus;   //!
   TBranch        *b_Rootuple_xi_Z_minus;   //!
   TBranch        *b_Rootuple_xi_Z_plus;   //!
   TBranch        *b_Rootuple_xi_Z_gen_minus;   //!
   TBranch        *b_Rootuple_xi_Z_gen_plus;   //!
   TBranch        *b_Rootuple_max_eta_gap_PF;   //!
   TBranch        *b_Rootuple_max_second_eta_gap_PF;   //!
   TBranch        *b_Rootuple_timestamp_timeLow_;   //!
   TBranch        *b_Rootuple_timestamp_timeHigh_;   //!
   TBranch        *b_Rootuple_xi_PF_charged_minus;   //!
   TBranch        *b_Rootuple_xi_PF_charged_plus;   //!
   TBranch        *b_Rootuple_nTracks_PF;   //!
   TBranch        *b_Rootuple_energyTot_PF_EE_minus;   //!
   TBranch        *b_Rootuple_energyTot_PF_EE_plus;   //!
   TBranch        *b_Rootuple_bx;   //!
   TBranch        *b_Rootuple_numberOfVertexes;   //!
   TBranch        *b_Rootuple_sumEHF_PF_minus;   //!
   TBranch        *b_Rootuple_sumEHF_PF_plus;   //!
   TBranch        *b_Rootuple_etaOutcomingProton;   //!
   TBranch        *b_Rootuple_mostEnergeticParticleGap_MC;   //!
   TBranch        *b_Rootuple_nParticles_gen;   //!
   TBranch        *b_Rootuple_sumECastor_Th_minus;   //!
   TBranch        *b_Rootuple_numberOfLeptons;   //!
   TBranch        *b_Rootuple_etaZ;   //!
   TBranch        *b_Rootuple_vertexNDOF;   //!
   TBranch        *b_Rootuple_xi_PF_NOHF_minus;   //!
   TBranch        *b_Rootuple_xi_PF_NOHF_plus;   //!
   TBranch        *b_Rootuple_vertexChiNorm;   //!
   TBranch        *b_Rootuple_vertexMolteplicity;   //!
   TBranch        *b_Rootuple_CastorActivity;   //!
   TBranch        *b_Rootuple_vertexNumberOfRH;   //!
   TBranch        *b_Rootuple_xL_gen;   //!
   TBranch        *b_Rootuple_xL_Num_gen;   //!
   TBranch        *b_Rootuple_sumECastorRaw_minus;   //!
   TBranch        *b_Rootuple_sumECastor_minus;   //!
   TBranch        *b_Rootuple_pixelNCluster;   //!
   TBranch        *b_Rootuple_V_x;   //!
   TBranch        *b_Rootuple_V_y;   //!
   TBranch        *b_Rootuple_V_z;   //!
   TBranch        *b_Rootuple_PV_x;   //!
   TBranch        *b_Rootuple_PV_y;   //!
   TBranch        *b_Rootuple_PV_z;   //!
   TBranch        *b_Rootuple_etaZ_gen;   //!
   TBranch        *b_Rootuple_lepton1Phi;   //!
   TBranch        *b_Rootuple_lepton1Eta;   //!
   TBranch        *b_Rootuple_lepton2Phi;   //!
   TBranch        *b_Rootuple_lepton2Eta;   //!
   TBranch        *b_Rootuple_Mx2;   //!
   TBranch        *b_Rootuple_M_x;   //!
   TBranch        *b_Rootuple_M_y;   //!
   TBranch        *b_Rootuple_M_z;   //!
   TBranch        *b_Rootuple_energyZ_gen;   //!
   TBranch        *b_Rootuple_xi_Calo_minus;   //!
   TBranch        *b_Rootuple_xi_Calo_plus;   //!
   TBranch        *b_Rootuple_p_diss_mass_gen;   //!
   TBranch        *b_Rootuple_xL_p_diss;   //!
   TBranch        *b_Rootuple_tracksPT;   //!
   TBranch        *b_Rootuple_tracksPT_gen;   //!
   TBranch        *b_Rootuple_numberoOfTracks_gen;   //!
   TBranch        *b_Rootuple_etaOfTracksPT_gen;   //!
   TBranch        *b_Rootuple_electronEnergy;   //!
   TBranch        *b_Rootuple_muEnergy;   //!
   TBranch        *b_Rootuple_PU_NumInt;   //!
   TBranch        *b_Rootuple_PU_zpos;   //!
   TBranch        *b_Rootuple_PU_ntrks_lowpT;   //!
   TBranch        *b_Rootuple_PU_ntrks_highpT;   //!
   TBranch        *b_Rootuple_PU_sumpT_lowpT;   //!
   TBranch        *b_Rootuple_PU_sumpT_highpT;   //!

   ZAnalysis(TTree *tree=0);
   virtual ~ZAnalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ZAnalysis_cxx
ZAnalysis::ZAnalysis(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("files/zdiff/4_2/Run2010ARepro_ee_v2_0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("files/zdiff/4_2/Run2010ARepro_ee_v2_0.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("files/zdiff/4_2/Run2010ARepro_ee_v2_0.root:/Selection");
      dir->GetObject("tree_",tree);

   }
   Init(tree);
}

ZAnalysis::~ZAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ZAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ZAnalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ZAnalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_Rootuple_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_Rootuple_EventNumber);
   fChain->SetBranchAddress("Lumi", &Lumi, &b_Rootuple_Lumi);
   fChain->SetBranchAddress("InvariantMass", &InvariantMass, &b_Rootuple_InvariantMass);
   fChain->SetBranchAddress("istlumi", &istlumi, &b_Rootuple_istlumi);
   fChain->SetBranchAddress("istlumierr", &istlumierr, &b_Rootuple_istlumierr);
   fChain->SetBranchAddress("Epz_Calo_plus", &Epz_Calo_plus, &b_Rootuple_Epz_Calo_plus);
   fChain->SetBranchAddress("Epz_Calo_minus", &Epz_Calo_minus, &b_Rootuple_Epz_Calo_minus);
   fChain->SetBranchAddress("sumEHF_plus", &sumEHF_plus, &b_Rootuple_sumEHF_plus);
   fChain->SetBranchAddress("sumEHF_minus", &sumEHF_minus, &b_Rootuple_sumEHF_minus);
   fChain->SetBranchAddress("minEHF", &minEHF, &b_Rootuple_minEHF);
   fChain->SetBranchAddress("etaMax_Calo", &etaMax_Calo, &b_Rootuple_etaMax_Calo);
   fChain->SetBranchAddress("etaMin_Calo", &etaMin_Calo, &b_Rootuple_etaMin_Calo);
   fChain->SetBranchAddress("Epz_PF_minus", &Epz_PF_minus, &b_Rootuple_Epz_PF_minus);
   fChain->SetBranchAddress("Epz_PF_plus", &Epz_PF_plus, &b_Rootuple_Epz_PF_plus);
   fChain->SetBranchAddress("etaMax_PF", &etaMax_PF, &b_Rootuple_etaMax_PF);
   fChain->SetBranchAddress("etaMin_PF", &etaMin_PF, &b_Rootuple_etaMin_PF);
   fChain->SetBranchAddress("etaMax_Charged_PV_PF", &etaMax_Charged_PV_PF, &b_Rootuple_etaMax_Charged_PV_PF);
   fChain->SetBranchAddress("etaMin_Charged_PV_PF", &etaMin_Charged_PV_PF, &b_Rootuple_etaMin_Charged_PV_PF);
   fChain->SetBranchAddress("Epz_NOHF_PF_minus", &Epz_NOHF_PF_minus, &b_Rootuple_Epz_NOHF_PF_minus);
   fChain->SetBranchAddress("Epz_NOHF_PF_plus", &Epz_NOHF_PF_plus, &b_Rootuple_Epz_NOHF_PF_plus);
   fChain->SetBranchAddress("etaMax_NOHF_PF", &etaMax_NOHF_PF, &b_Rootuple_etaMax_NOHF_PF);
   fChain->SetBranchAddress("etaMin_NOHF_PF", &etaMin_NOHF_PF, &b_Rootuple_etaMin_NOHF_PF);
   fChain->SetBranchAddress("xi_gen", &xi_gen, &b_Rootuple_xi_gen);
   fChain->SetBranchAddress("Mx2_gen", &Mx2_gen, &b_Rootuple_Mx2_gen);
   fChain->SetBranchAddress("xi_NOZ_gen", &xi_NOZ_gen, &b_Rootuple_xi_NOZ_gen);
   fChain->SetBranchAddress("nTowersHF_plus", &nTowersHF_plus, &b_Rootuple_nTowersHF_plus);
   fChain->SetBranchAddress("nTowersHF_minus", &nTowersHF_minus, &b_Rootuple_nTowersHF_minus);
   fChain->SetBranchAddress("etaAllTracks_PF", &etaAllTracks_PF, &b_Rootuple_etaAllTracks_PF);
   fChain->SetBranchAddress("energyTot_PF", &energyTot_PF, &b_Rootuple_energyTot_PF);
   fChain->SetBranchAddress("sumEZDC_minus", &sumEZDC_minus, &b_Rootuple_sumEZDC_minus);
   fChain->SetBranchAddress("sumEZDC_plus", &sumEZDC_plus, &b_Rootuple_sumEZDC_plus);
   fChain->SetBranchAddress("sumECastor_gen_plus", &sumECastor_gen_plus, &b_Rootuple_sumECastor_gen_plus);
   fChain->SetBranchAddress("sumECastor_gen_minus", &sumECastor_gen_minus, &b_Rootuple_sumECastor_gen_minus);
   fChain->SetBranchAddress("sumEZDC_gen_minus", &sumEZDC_gen_minus, &b_Rootuple_sumEZDC_gen_minus);
   fChain->SetBranchAddress("sumEZDC_gen_plus", &sumEZDC_gen_plus, &b_Rootuple_sumEZDC_gen_plus);
   fChain->SetBranchAddress("etaWeightedOnEnergy_PF", &etaWeightedOnEnergy_PF, &b_Rootuple_etaWeightedOnEnergy_PF);
   fChain->SetBranchAddress("energyTot_PF_Barrel_minus", &energyTot_PF_Barrel_minus, &b_Rootuple_energyTot_PF_Barrel_minus);
   fChain->SetBranchAddress("energyTot_PF_Barrel_plus", &energyTot_PF_Barrel_plus, &b_Rootuple_energyTot_PF_Barrel_plus);
   fChain->SetBranchAddress("energyTot_PF_minus", &energyTot_PF_minus, &b_Rootuple_energyTot_PF_minus);
   fChain->SetBranchAddress("energyTot_PF_plus", &energyTot_PF_plus, &b_Rootuple_energyTot_PF_plus);
   fChain->SetBranchAddress("istlumiPerBX", &istlumiPerBX, &b_Rootuple_istlumiPerBX);
   fChain->SetBranchAddress("xi_PF_minus", &xi_PF_minus, &b_Rootuple_xi_PF_minus);
   fChain->SetBranchAddress("xi_PF_plus", &xi_PF_plus, &b_Rootuple_xi_PF_plus);
   fChain->SetBranchAddress("xi_Z_minus", &xi_Z_minus, &b_Rootuple_xi_Z_minus);
   fChain->SetBranchAddress("xi_Z_plus", &xi_Z_plus, &b_Rootuple_xi_Z_plus);
   fChain->SetBranchAddress("xi_Z_gen_minus", &xi_Z_gen_minus, &b_Rootuple_xi_Z_gen_minus);
   fChain->SetBranchAddress("xi_Z_gen_plus", &xi_Z_gen_plus, &b_Rootuple_xi_Z_gen_plus);
   fChain->SetBranchAddress("max_eta_gap_PF", &max_eta_gap_PF, &b_Rootuple_max_eta_gap_PF);
   fChain->SetBranchAddress("max_second_eta_gap_PF", &max_second_eta_gap_PF, &b_Rootuple_max_second_eta_gap_PF);
   fChain->SetBranchAddress("timestamp.timeLow_", &timestamp_timeLow_, &b_Rootuple_timestamp_timeLow_);
   fChain->SetBranchAddress("timestamp.timeHigh_", &timestamp_timeHigh_, &b_Rootuple_timestamp_timeHigh_);
   fChain->SetBranchAddress("xi_PF_charged_minus", &xi_PF_charged_minus, &b_Rootuple_xi_PF_charged_minus);
   fChain->SetBranchAddress("xi_PF_charged_plus", &xi_PF_charged_plus, &b_Rootuple_xi_PF_charged_plus);
   fChain->SetBranchAddress("nTracks_PF", &nTracks_PF, &b_Rootuple_nTracks_PF);
   fChain->SetBranchAddress("energyTot_PF_EE_minus", &energyTot_PF_EE_minus, &b_Rootuple_energyTot_PF_EE_minus);
   fChain->SetBranchAddress("energyTot_PF_EE_plus", &energyTot_PF_EE_plus, &b_Rootuple_energyTot_PF_EE_plus);
   fChain->SetBranchAddress("bx", &bx, &b_Rootuple_bx);
   fChain->SetBranchAddress("numberOfVertexes", &numberOfVertexes, &b_Rootuple_numberOfVertexes);
   fChain->SetBranchAddress("sumEHF_PF_minus", &sumEHF_PF_minus, &b_Rootuple_sumEHF_PF_minus);
   fChain->SetBranchAddress("sumEHF_PF_plus", &sumEHF_PF_plus, &b_Rootuple_sumEHF_PF_plus);
   fChain->SetBranchAddress("etaOutcomingProton", &etaOutcomingProton, &b_Rootuple_etaOutcomingProton);
   fChain->SetBranchAddress("mostEnergeticParticleGap_MC", &mostEnergeticParticleGap_MC, &b_Rootuple_mostEnergeticParticleGap_MC);
   fChain->SetBranchAddress("nParticles_gen", &nParticles_gen, &b_Rootuple_nParticles_gen);
   fChain->SetBranchAddress("sumECastor_Th_minus", &sumECastor_Th_minus, &b_Rootuple_sumECastor_Th_minus);
   fChain->SetBranchAddress("numberOfLeptons", &numberOfLeptons, &b_Rootuple_numberOfLeptons);
   fChain->SetBranchAddress("etaZ", &etaZ, &b_Rootuple_etaZ);
   fChain->SetBranchAddress("vertexNDOF", &vertexNDOF, &b_Rootuple_vertexNDOF);
   fChain->SetBranchAddress("xi_PF_NOHF_minus", &xi_PF_NOHF_minus, &b_Rootuple_xi_PF_NOHF_minus);
   fChain->SetBranchAddress("xi_PF_NOHF_plus", &xi_PF_NOHF_plus, &b_Rootuple_xi_PF_NOHF_plus);
   fChain->SetBranchAddress("vertexChiNorm", &vertexChiNorm, &b_Rootuple_vertexChiNorm);
   fChain->SetBranchAddress("vertexMolteplicity", &vertexMolteplicity, &b_Rootuple_vertexMolteplicity);
   fChain->SetBranchAddress("CastorActivity", &CastorActivity, &b_Rootuple_CastorActivity);
   fChain->SetBranchAddress("vertexNumberOfRH", &vertexNumberOfRH, &b_Rootuple_vertexNumberOfRH);
   fChain->SetBranchAddress("xL_gen", &xL_gen, &b_Rootuple_xL_gen);
   fChain->SetBranchAddress("xL_Num_gen", &xL_Num_gen, &b_Rootuple_xL_Num_gen);
   fChain->SetBranchAddress("sumECastorRaw_minus", &sumECastorRaw_minus, &b_Rootuple_sumECastorRaw_minus);
   fChain->SetBranchAddress("sumECastor_minus", &sumECastor_minus, &b_Rootuple_sumECastor_minus);
   fChain->SetBranchAddress("pixelNCluster", &pixelNCluster, &b_Rootuple_pixelNCluster);
   fChain->SetBranchAddress("V_x", &V_x, &b_Rootuple_V_x);
   fChain->SetBranchAddress("V_y", &V_y, &b_Rootuple_V_y);
   fChain->SetBranchAddress("V_z", &V_z, &b_Rootuple_V_z);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_Rootuple_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_Rootuple_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_Rootuple_PV_z);
   fChain->SetBranchAddress("etaZ_gen", &etaZ_gen, &b_Rootuple_etaZ_gen);
   fChain->SetBranchAddress("lepton1Phi", &lepton1Phi, &b_Rootuple_lepton1Phi);
   fChain->SetBranchAddress("lepton1Eta", &lepton1Eta, &b_Rootuple_lepton1Eta);
   fChain->SetBranchAddress("lepton2Phi", &lepton2Phi, &b_Rootuple_lepton2Phi);
   fChain->SetBranchAddress("lepton2Eta", &lepton2Eta, &b_Rootuple_lepton2Eta);
   fChain->SetBranchAddress("Mx2", &Mx2, &b_Rootuple_Mx2);
   fChain->SetBranchAddress("M_x", &M_x, &b_Rootuple_M_x);
   fChain->SetBranchAddress("M_y", &M_y, &b_Rootuple_M_y);
   fChain->SetBranchAddress("M_z", &M_z, &b_Rootuple_M_z);
   fChain->SetBranchAddress("energyZ_gen", &energyZ_gen, &b_Rootuple_energyZ_gen);
   fChain->SetBranchAddress("xi_Calo_minus", &xi_Calo_minus, &b_Rootuple_xi_Calo_minus);
   fChain->SetBranchAddress("xi_Calo_plus", &xi_Calo_plus, &b_Rootuple_xi_Calo_plus);
   fChain->SetBranchAddress("p_diss_mass_gen", &p_diss_mass_gen, &b_Rootuple_p_diss_mass_gen);
   fChain->SetBranchAddress("xL_p_diss", &xL_p_diss, &b_Rootuple_xL_p_diss);
   fChain->SetBranchAddress("tracksPT", &tracksPT, &b_Rootuple_tracksPT);
   fChain->SetBranchAddress("tracksPT_gen", &tracksPT_gen, &b_Rootuple_tracksPT_gen);
   fChain->SetBranchAddress("numberoOfTracks_gen", &numberoOfTracks_gen, &b_Rootuple_numberoOfTracks_gen);
   fChain->SetBranchAddress("etaOfTracksPT_gen", &etaOfTracksPT_gen, &b_Rootuple_etaOfTracksPT_gen);
   fChain->SetBranchAddress("electronEnergy", &electronEnergy, &b_Rootuple_electronEnergy);
   fChain->SetBranchAddress("muEnergy", &muEnergy, &b_Rootuple_muEnergy);
   fChain->SetBranchAddress("PU_NumInt", &PU_NumInt, &b_Rootuple_PU_NumInt);
   fChain->SetBranchAddress("PU_zpos", &PU_zpos, &b_Rootuple_PU_zpos);
   fChain->SetBranchAddress("PU_ntrks_lowpT", &PU_ntrks_lowpT, &b_Rootuple_PU_ntrks_lowpT);
   fChain->SetBranchAddress("PU_ntrks_highpT", &PU_ntrks_highpT, &b_Rootuple_PU_ntrks_highpT);
   fChain->SetBranchAddress("PU_sumpT_lowpT", &PU_sumpT_lowpT, &b_Rootuple_PU_sumpT_lowpT);
   fChain->SetBranchAddress("PU_sumpT_highpT", &PU_sumpT_highpT, &b_Rootuple_PU_sumpT_highpT);
   Notify();
}

Bool_t ZAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ZAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ZAnalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ZAnalysis_cxx
