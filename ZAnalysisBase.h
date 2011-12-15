//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Dec 12 10:59:00 2011 by ROOT version 5.30/02
// from TTree tree_/tree_
// found on file: files/zdiff/4_2/PompytZee_v2_2.root
//////////////////////////////////////////////////////////

#ifndef ZAnalysisBase_h
#define ZAnalysisBase_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
   const Int_t kMaxtimestamp_timeLow = 1;
   const Int_t kMaxtimestamp_timeHigh = 1;

class ZAnalysisBase {

public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //DifNtuple       *Rootuple;
   UInt_t          RunNumber;
   UInt_t          EventNumber;
   UInt_t          LumiSection;
   UInt_t          timestamp_timeLow_;
   UInt_t          timestamp_timeHigh_;
   Int_t           bx;
   Float_t         istlumi;
   Float_t         istlumierr;
   Float_t         istlumiPerBX;
   Double_t        etaZ_gen;
   Double_t        ZMass;
   Double_t        etaZ;
   Double_t        energyZ_gen;
   Double_t        lepton1Phi;
   Double_t        lepton1Eta;
   Double_t        lepton2Phi;
   Double_t        lepton2Eta;
   vector<double>  electronEnergy;
   vector<double>  muEnergy;
   Double_t        Epz_Calo_minus;
   Double_t        Epz_Calo_plus;
   Double_t        Epz_PF_minus;
   Double_t        Epz_PF_plus;
   Double_t        Epz_NOHF_PF_minus;
   Double_t        Epz_NOHF_PF_plus;
   Double_t        etaMax_Calo;
   Double_t        etaMin_Calo;
   Double_t        etaMax_PF;
   Double_t        etaMin_PF;
   Double_t        etaMax_Charged_PV_PF;
   Double_t        etaMin_Charged_PV_PF;
   Double_t        etaMax_NOHF_PF;
   Double_t        etaMin_NOHF_PF;
   Double_t        etaWeightedOnEnergy_PF;
   Double_t        etaAllTracks_PF;
   Double_t        max_eta_gap_PF;
   Double_t        max_second_eta_gap_PF;
   Double_t        eta_gap_limplus;
   Double_t        Mx2;
   Double_t        Mx2_plus;
   Double_t        Mx2_minus;
   Double_t        P_x;
   Double_t        P_y;
   Double_t        P_z;
   Double_t        Mx2_gen;
   Double_t        Mx2_NOZ_gen;
   Int_t           nTowersHF_plus;
   Int_t           nTowersHF_minus;
   Double_t        sumEHF_plus;
   Double_t        sumEHF_minus;
   Double_t        sumEHF_PF_minus;
   Double_t        sumEHF_PF_plus;
   Double_t        minEHF;
   Double_t        sumEZDC_minus;
   Double_t        sumEZDC_plus;
   Double_t        sumECastor_gen_plus;
   Double_t        sumECastor_gen_minus;
   Double_t        sumECastor_Th_minus;
   Double_t        sumEZDC_gen_minus;
   Double_t        sumEZDC_gen_plus;
   Bool_t          CastorActivity;
   Double_t        sumECastorRaw_minus;
   Double_t        sumECastor_minus;
   Double_t        energyTot_PF;
   Double_t        energyTot_PF_Barrel_minus;
   Double_t        energyTot_PF_Barrel_plus;
   Double_t        energyTot_PF_minus;
   Double_t        energyTot_PF_plus;
   Double_t        energyTot_PF_EE_minus;
   Double_t        energyTot_PF_EE_plus;
   Double_t        xi_PF_minus;
   Double_t        xi_PF_plus;
   Double_t        xi_Z_minus;
   Double_t        xi_Z_plus;
   Double_t        xi_Z_gen_minus;
   Double_t        xi_Z_gen_plus;
   Double_t        xi_PV_PF_charged_minus;
   Double_t        xi_PV_PF_charged_plus;
   Double_t        xi_PF_NOHF_minus;
   Double_t        xi_PF_NOHF_plus;
   Double_t        xi_Calo_minus;
   Double_t        xi_Calo_plus;
   Double_t        xL_gen;
   Double_t        xL_Num_gen;
   Double_t        p_diss_mass_gen;
   Double_t        xL_p_diss;
   Int_t           nPart_PF;
   Int_t           N_mx2plus;
   Int_t           N_mx2minus;
   Double_t        etaOutcomingProton;
   Double_t        nParticles_gen;
   Int_t           numberOfLeptons;
   Int_t           numberOfVertexes;
   vector<vector<double> > tracksPT;
   vector<double>  vertexNDOF;
   vector<double>  vertexChiNorm;
   vector<double>  vertexMolteplicity;
   vector<double>  V_x;
   vector<double>  V_y;
   vector<double>  V_z;
   Int_t           numberOfTracks_gen;
   vector<double>  tracksPT_gen;
   vector<double>  etaOfTracksPT_gen;
   Double_t        PUMCweight;
   Int_t           PU_NumInt;
   vector<float>   PU_zpos;
   vector<int>     PU_ntrks_lowpT;
   vector<int>     PU_ntrks_highpT;
   vector<float>   PU_sumpT_lowpT;
   vector<float>   PU_sumpT_highpT;
   vector<float>   EnergyInEta;

   // List of branches
   TBranch        *b_Rootuple_RunNumber;   //!
   TBranch        *b_Rootuple_EventNumber;   //!
   TBranch        *b_Rootuple_LumiSection;   //!
   TBranch        *b_Rootuple_timestamp_timeLow_;   //!
   TBranch        *b_Rootuple_timestamp_timeHigh_;   //!
   TBranch        *b_Rootuple_bx;   //!
   TBranch        *b_Rootuple_istlumi;   //!
   TBranch        *b_Rootuple_istlumierr;   //!
   TBranch        *b_Rootuple_istlumiPerBX;   //!
   TBranch        *b_Rootuple_etaZ_gen;   //!
   TBranch        *b_Rootuple_ZMass;   //!
   TBranch        *b_Rootuple_etaZ;   //!
   TBranch        *b_Rootuple_energyZ_gen;   //!
   TBranch        *b_Rootuple_lepton1Phi;   //!
   TBranch        *b_Rootuple_lepton1Eta;   //!
   TBranch        *b_Rootuple_lepton2Phi;   //!
   TBranch        *b_Rootuple_lepton2Eta;   //!
   TBranch        *b_Rootuple_electronEnergy;   //!
   TBranch        *b_Rootuple_muEnergy;   //!
   TBranch        *b_Rootuple_Epz_Calo_minus;   //!
   TBranch        *b_Rootuple_Epz_Calo_plus;   //!
   TBranch        *b_Rootuple_Epz_PF_minus;   //!
   TBranch        *b_Rootuple_Epz_PF_plus;   //!
   TBranch        *b_Rootuple_Epz_NOHF_PF_minus;   //!
   TBranch        *b_Rootuple_Epz_NOHF_PF_plus;   //!
   TBranch        *b_Rootuple_etaMax_Calo;   //!
   TBranch        *b_Rootuple_etaMin_Calo;   //!
   TBranch        *b_Rootuple_etaMax_PF;   //!
   TBranch        *b_Rootuple_etaMin_PF;   //!
   TBranch        *b_Rootuple_etaMax_Charged_PV_PF;   //!
   TBranch        *b_Rootuple_etaMin_Charged_PV_PF;   //!
   TBranch        *b_Rootuple_etaMax_NOHF_PF;   //!
   TBranch        *b_Rootuple_etaMin_NOHF_PF;   //!
   TBranch        *b_Rootuple_etaWeightedOnEnergy_PF;   //!
   TBranch        *b_Rootuple_etaAllTracks_PF;   //!
   TBranch        *b_Rootuple_max_eta_gap_PF;   //!
   TBranch        *b_Rootuple_max_second_eta_gap_PF;   //!
   TBranch        *b_Rootuple_eta_gap_limplus;   //!
   TBranch        *b_Rootuple_Mx2;   //!
   TBranch        *b_Rootuple_Mx2_plus;   //!
   TBranch        *b_Rootuple_Mx2_minus;   //!
   TBranch        *b_Rootuple_P_x;   //!
   TBranch        *b_Rootuple_P_y;   //!
   TBranch        *b_Rootuple_P_z;   //!
   TBranch        *b_Rootuple_Mx2_gen;   //!
   TBranch        *b_Rootuple_Mx2_NOZ_gen;   //!
   TBranch        *b_Rootuple_nTowersHF_plus;   //!
   TBranch        *b_Rootuple_nTowersHF_minus;   //!
   TBranch        *b_Rootuple_sumEHF_plus;   //!
   TBranch        *b_Rootuple_sumEHF_minus;   //!
   TBranch        *b_Rootuple_sumEHF_PF_minus;   //!
   TBranch        *b_Rootuple_sumEHF_PF_plus;   //!
   TBranch        *b_Rootuple_minEHF;   //!
   TBranch        *b_Rootuple_sumEZDC_minus;   //!
   TBranch        *b_Rootuple_sumEZDC_plus;   //!
   TBranch        *b_Rootuple_sumECastor_gen_plus;   //!
   TBranch        *b_Rootuple_sumECastor_gen_minus;   //!
   TBranch        *b_Rootuple_sumECastor_Th_minus;   //!
   TBranch        *b_Rootuple_sumEZDC_gen_minus;   //!
   TBranch        *b_Rootuple_sumEZDC_gen_plus;   //!
   TBranch        *b_Rootuple_CastorActivity;   //!
   TBranch        *b_Rootuple_sumECastorRaw_minus;   //!
   TBranch        *b_Rootuple_sumECastor_minus;   //!
   TBranch        *b_Rootuple_energyTot_PF;   //!
   TBranch        *b_Rootuple_energyTot_PF_Barrel_minus;   //!
   TBranch        *b_Rootuple_energyTot_PF_Barrel_plus;   //!
   TBranch        *b_Rootuple_energyTot_PF_minus;   //!
   TBranch        *b_Rootuple_energyTot_PF_plus;   //!
   TBranch        *b_Rootuple_energyTot_PF_EE_minus;   //!
   TBranch        *b_Rootuple_energyTot_PF_EE_plus;   //!
   TBranch        *b_Rootuple_xi_PF_minus;   //!
   TBranch        *b_Rootuple_xi_PF_plus;   //!
   TBranch        *b_Rootuple_xi_Z_minus;   //!
   TBranch        *b_Rootuple_xi_Z_plus;   //!
   TBranch        *b_Rootuple_xi_Z_gen_minus;   //!
   TBranch        *b_Rootuple_xi_Z_gen_plus;   //!
   TBranch        *b_Rootuple_xi_PV_PF_charged_minus;   //!
   TBranch        *b_Rootuple_xi_PV_PF_charged_plus;   //!
   TBranch        *b_Rootuple_xi_PF_NOHF_minus;   //!
   TBranch        *b_Rootuple_xi_PF_NOHF_plus;   //!
   TBranch        *b_Rootuple_xi_Calo_minus;   //!
   TBranch        *b_Rootuple_xi_Calo_plus;   //!
   TBranch        *b_Rootuple_xL_gen;   //!
   TBranch        *b_Rootuple_xL_Num_gen;   //!
   TBranch        *b_Rootuple_p_diss_mass_gen;   //!
   TBranch        *b_Rootuple_xL_p_diss;   //!
   TBranch        *b_Rootuple_nPart_PF;   //!
   TBranch        *b_Rootuple_N_mx2plus;   //!
   TBranch        *b_Rootuple_N_mx2minus;   //!
   TBranch        *b_Rootuple_etaOutcomingProton;   //!
   TBranch        *b_Rootuple_nParticles_gen;   //!
   TBranch        *b_Rootuple_numberOfLeptons;   //!
   TBranch        *b_Rootuple_numberOfVertexes;   //!
   TBranch        *b_Rootuple_tracksPT;   //!
   TBranch        *b_Rootuple_vertexNDOF;   //!
   TBranch        *b_Rootuple_vertexChiNorm;   //!
   TBranch        *b_Rootuple_vertexMolteplicity;   //!
   TBranch        *b_Rootuple_V_x;   //!
   TBranch        *b_Rootuple_V_y;   //!
   TBranch        *b_Rootuple_V_z;   //!
   TBranch        *b_Rootuple_numberOfTracks_gen;   //!
   TBranch        *b_Rootuple_tracksPT_gen;   //!
   TBranch        *b_Rootuple_etaOfTracksPT_gen;   //!
   TBranch        *b_Rootuple_PUMCweight;   //!
   TBranch        *b_Rootuple_PU_NumInt;   //!
   TBranch        *b_Rootuple_PU_zpos;   //!
   TBranch        *b_Rootuple_PU_ntrks_lowpT;   //!
   TBranch        *b_Rootuple_PU_ntrks_highpT;   //!
   TBranch        *b_Rootuple_PU_sumpT_lowpT;   //!
   TBranch        *b_Rootuple_PU_sumpT_highpT;   //!
   TBranch        *b_Rootuple_EnergyInEta;   //!

   ZAnalysisBase(TTree *tree=0);

   virtual ~ZAnalysisBase();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ZAnalysisBase_cxx

ZAnalysisBase::ZAnalysisBase(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("files/zdiff/4_2/PompytZee_v2_2.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("files/zdiff/4_2/PompytZee_v2_2.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("files/zdiff/4_2/PompytZee_v2_2.root:/Selection");
      dir->GetObject("tree_",tree);

   }
   Init(tree);
}

ZAnalysisBase::~ZAnalysisBase()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ZAnalysisBase::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ZAnalysisBase::LoadTree(Long64_t entry)
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

void ZAnalysisBase::Init(TTree *tree)
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
   fChain->SetBranchAddress("LumiSection", &LumiSection, &b_Rootuple_LumiSection);
   fChain->SetBranchAddress("timestamp.timeLow_", &timestamp_timeLow_, &b_Rootuple_timestamp_timeLow_);
   fChain->SetBranchAddress("timestamp.timeHigh_", &timestamp_timeHigh_, &b_Rootuple_timestamp_timeHigh_);
   fChain->SetBranchAddress("bx", &bx, &b_Rootuple_bx);
   fChain->SetBranchAddress("istlumi", &istlumi, &b_Rootuple_istlumi);
   fChain->SetBranchAddress("istlumierr", &istlumierr, &b_Rootuple_istlumierr);
   fChain->SetBranchAddress("istlumiPerBX", &istlumiPerBX, &b_Rootuple_istlumiPerBX);
   fChain->SetBranchAddress("etaZ_gen", &etaZ_gen, &b_Rootuple_etaZ_gen);
   fChain->SetBranchAddress("ZMass", &ZMass, &b_Rootuple_ZMass);
   fChain->SetBranchAddress("etaZ", &etaZ, &b_Rootuple_etaZ);
   fChain->SetBranchAddress("energyZ_gen", &energyZ_gen, &b_Rootuple_energyZ_gen);
   fChain->SetBranchAddress("lepton1Phi", &lepton1Phi, &b_Rootuple_lepton1Phi);
   fChain->SetBranchAddress("lepton1Eta", &lepton1Eta, &b_Rootuple_lepton1Eta);
   fChain->SetBranchAddress("lepton2Phi", &lepton2Phi, &b_Rootuple_lepton2Phi);
   fChain->SetBranchAddress("lepton2Eta", &lepton2Eta, &b_Rootuple_lepton2Eta);
   fChain->SetBranchAddress("electronEnergy", &electronEnergy, &b_Rootuple_electronEnergy);
   fChain->SetBranchAddress("muEnergy", &muEnergy, &b_Rootuple_muEnergy);
   fChain->SetBranchAddress("Epz_Calo_minus", &Epz_Calo_minus, &b_Rootuple_Epz_Calo_minus);
   fChain->SetBranchAddress("Epz_Calo_plus", &Epz_Calo_plus, &b_Rootuple_Epz_Calo_plus);
   fChain->SetBranchAddress("Epz_PF_minus", &Epz_PF_minus, &b_Rootuple_Epz_PF_minus);
   fChain->SetBranchAddress("Epz_PF_plus", &Epz_PF_plus, &b_Rootuple_Epz_PF_plus);
   fChain->SetBranchAddress("Epz_NOHF_PF_minus", &Epz_NOHF_PF_minus, &b_Rootuple_Epz_NOHF_PF_minus);
   fChain->SetBranchAddress("Epz_NOHF_PF_plus", &Epz_NOHF_PF_plus, &b_Rootuple_Epz_NOHF_PF_plus);
   fChain->SetBranchAddress("etaMax_Calo", &etaMax_Calo, &b_Rootuple_etaMax_Calo);
   fChain->SetBranchAddress("etaMin_Calo", &etaMin_Calo, &b_Rootuple_etaMin_Calo);
   fChain->SetBranchAddress("etaMax_PF", &etaMax_PF, &b_Rootuple_etaMax_PF);
   fChain->SetBranchAddress("etaMin_PF", &etaMin_PF, &b_Rootuple_etaMin_PF);
   fChain->SetBranchAddress("etaMax_Charged_PV_PF", &etaMax_Charged_PV_PF, &b_Rootuple_etaMax_Charged_PV_PF);
   fChain->SetBranchAddress("etaMin_Charged_PV_PF", &etaMin_Charged_PV_PF, &b_Rootuple_etaMin_Charged_PV_PF);
   fChain->SetBranchAddress("etaMax_NOHF_PF", &etaMax_NOHF_PF, &b_Rootuple_etaMax_NOHF_PF);
   fChain->SetBranchAddress("etaMin_NOHF_PF", &etaMin_NOHF_PF, &b_Rootuple_etaMin_NOHF_PF);
   fChain->SetBranchAddress("etaWeightedOnEnergy_PF", &etaWeightedOnEnergy_PF, &b_Rootuple_etaWeightedOnEnergy_PF);
   fChain->SetBranchAddress("etaAllTracks_PF", &etaAllTracks_PF, &b_Rootuple_etaAllTracks_PF);
   fChain->SetBranchAddress("max_eta_gap_PF", &max_eta_gap_PF, &b_Rootuple_max_eta_gap_PF);
   fChain->SetBranchAddress("max_second_eta_gap_PF", &max_second_eta_gap_PF, &b_Rootuple_max_second_eta_gap_PF);
   fChain->SetBranchAddress("eta_gap_limplus", &eta_gap_limplus, &b_Rootuple_eta_gap_limplus);
   fChain->SetBranchAddress("Mx2", &Mx2, &b_Rootuple_Mx2);
   fChain->SetBranchAddress("Mx2_plus", &Mx2_plus, &b_Rootuple_Mx2_plus);
   fChain->SetBranchAddress("Mx2_minus", &Mx2_minus, &b_Rootuple_Mx2_minus);
   fChain->SetBranchAddress("P_x", &P_x, &b_Rootuple_P_x);
   fChain->SetBranchAddress("P_y", &P_y, &b_Rootuple_P_y);
   fChain->SetBranchAddress("P_z", &P_z, &b_Rootuple_P_z);
   fChain->SetBranchAddress("Mx2_gen", &Mx2_gen, &b_Rootuple_Mx2_gen);
   fChain->SetBranchAddress("Mx2_NOZ_gen", &Mx2_NOZ_gen, &b_Rootuple_Mx2_NOZ_gen);
   fChain->SetBranchAddress("nTowersHF_plus", &nTowersHF_plus, &b_Rootuple_nTowersHF_plus);
   fChain->SetBranchAddress("nTowersHF_minus", &nTowersHF_minus, &b_Rootuple_nTowersHF_minus);
   fChain->SetBranchAddress("sumEHF_plus", &sumEHF_plus, &b_Rootuple_sumEHF_plus);
   fChain->SetBranchAddress("sumEHF_minus", &sumEHF_minus, &b_Rootuple_sumEHF_minus);
   fChain->SetBranchAddress("sumEHF_PF_minus", &sumEHF_PF_minus, &b_Rootuple_sumEHF_PF_minus);
   fChain->SetBranchAddress("sumEHF_PF_plus", &sumEHF_PF_plus, &b_Rootuple_sumEHF_PF_plus);
   fChain->SetBranchAddress("minEHF", &minEHF, &b_Rootuple_minEHF);
   fChain->SetBranchAddress("sumEZDC_minus", &sumEZDC_minus, &b_Rootuple_sumEZDC_minus);
   fChain->SetBranchAddress("sumEZDC_plus", &sumEZDC_plus, &b_Rootuple_sumEZDC_plus);
   fChain->SetBranchAddress("sumECastor_gen_plus", &sumECastor_gen_plus, &b_Rootuple_sumECastor_gen_plus);
   fChain->SetBranchAddress("sumECastor_gen_minus", &sumECastor_gen_minus, &b_Rootuple_sumECastor_gen_minus);
   fChain->SetBranchAddress("sumECastor_Th_minus", &sumECastor_Th_minus, &b_Rootuple_sumECastor_Th_minus);
   fChain->SetBranchAddress("sumEZDC_gen_minus", &sumEZDC_gen_minus, &b_Rootuple_sumEZDC_gen_minus);
   fChain->SetBranchAddress("sumEZDC_gen_plus", &sumEZDC_gen_plus, &b_Rootuple_sumEZDC_gen_plus);
   fChain->SetBranchAddress("CastorActivity", &CastorActivity, &b_Rootuple_CastorActivity);
   fChain->SetBranchAddress("sumECastorRaw_minus", &sumECastorRaw_minus, &b_Rootuple_sumECastorRaw_minus);
   fChain->SetBranchAddress("sumECastor_minus", &sumECastor_minus, &b_Rootuple_sumECastor_minus);
   fChain->SetBranchAddress("energyTot_PF", &energyTot_PF, &b_Rootuple_energyTot_PF);
   fChain->SetBranchAddress("energyTot_PF_Barrel_minus", &energyTot_PF_Barrel_minus, &b_Rootuple_energyTot_PF_Barrel_minus);
   fChain->SetBranchAddress("energyTot_PF_Barrel_plus", &energyTot_PF_Barrel_plus, &b_Rootuple_energyTot_PF_Barrel_plus);
   fChain->SetBranchAddress("energyTot_PF_minus", &energyTot_PF_minus, &b_Rootuple_energyTot_PF_minus);
   fChain->SetBranchAddress("energyTot_PF_plus", &energyTot_PF_plus, &b_Rootuple_energyTot_PF_plus);
   fChain->SetBranchAddress("energyTot_PF_EE_minus", &energyTot_PF_EE_minus, &b_Rootuple_energyTot_PF_EE_minus);
   fChain->SetBranchAddress("energyTot_PF_EE_plus", &energyTot_PF_EE_plus, &b_Rootuple_energyTot_PF_EE_plus);
   fChain->SetBranchAddress("xi_PF_minus", &xi_PF_minus, &b_Rootuple_xi_PF_minus);
   fChain->SetBranchAddress("xi_PF_plus", &xi_PF_plus, &b_Rootuple_xi_PF_plus);
   fChain->SetBranchAddress("xi_Z_minus", &xi_Z_minus, &b_Rootuple_xi_Z_minus);
   fChain->SetBranchAddress("xi_Z_plus", &xi_Z_plus, &b_Rootuple_xi_Z_plus);
   fChain->SetBranchAddress("xi_Z_gen_minus", &xi_Z_gen_minus, &b_Rootuple_xi_Z_gen_minus);
   fChain->SetBranchAddress("xi_Z_gen_plus", &xi_Z_gen_plus, &b_Rootuple_xi_Z_gen_plus);
   fChain->SetBranchAddress("xi_PV_PF_charged_minus", &xi_PV_PF_charged_minus, &b_Rootuple_xi_PV_PF_charged_minus);
   fChain->SetBranchAddress("xi_PV_PF_charged_plus", &xi_PV_PF_charged_plus, &b_Rootuple_xi_PV_PF_charged_plus);
   fChain->SetBranchAddress("xi_PF_NOHF_minus", &xi_PF_NOHF_minus, &b_Rootuple_xi_PF_NOHF_minus);
   fChain->SetBranchAddress("xi_PF_NOHF_plus", &xi_PF_NOHF_plus, &b_Rootuple_xi_PF_NOHF_plus);
   fChain->SetBranchAddress("xi_Calo_minus", &xi_Calo_minus, &b_Rootuple_xi_Calo_minus);
   fChain->SetBranchAddress("xi_Calo_plus", &xi_Calo_plus, &b_Rootuple_xi_Calo_plus);
   fChain->SetBranchAddress("xL_gen", &xL_gen, &b_Rootuple_xL_gen);
   fChain->SetBranchAddress("xL_Num_gen", &xL_Num_gen, &b_Rootuple_xL_Num_gen);
   fChain->SetBranchAddress("p_diss_mass_gen", &p_diss_mass_gen, &b_Rootuple_p_diss_mass_gen);
   fChain->SetBranchAddress("xL_p_diss", &xL_p_diss, &b_Rootuple_xL_p_diss);
   fChain->SetBranchAddress("nPart_PF", &nPart_PF, &b_Rootuple_nPart_PF);
   fChain->SetBranchAddress("N_mx2plus", &N_mx2plus, &b_Rootuple_N_mx2plus);
   fChain->SetBranchAddress("N_mx2minus", &N_mx2minus, &b_Rootuple_N_mx2minus);
   fChain->SetBranchAddress("etaOutcomingProton", &etaOutcomingProton, &b_Rootuple_etaOutcomingProton);
   fChain->SetBranchAddress("nParticles_gen", &nParticles_gen, &b_Rootuple_nParticles_gen);
   fChain->SetBranchAddress("numberOfLeptons", &numberOfLeptons, &b_Rootuple_numberOfLeptons);
   fChain->SetBranchAddress("numberOfVertexes", &numberOfVertexes, &b_Rootuple_numberOfVertexes);
   fChain->SetBranchAddress("tracksPT", &tracksPT, &b_Rootuple_tracksPT);
   fChain->SetBranchAddress("vertexNDOF", &vertexNDOF, &b_Rootuple_vertexNDOF);
   fChain->SetBranchAddress("vertexChiNorm", &vertexChiNorm, &b_Rootuple_vertexChiNorm);
   fChain->SetBranchAddress("vertexMolteplicity", &vertexMolteplicity, &b_Rootuple_vertexMolteplicity);
   fChain->SetBranchAddress("V_x", &V_x, &b_Rootuple_V_x);
   fChain->SetBranchAddress("V_y", &V_y, &b_Rootuple_V_y);
   fChain->SetBranchAddress("V_z", &V_z, &b_Rootuple_V_z);
   fChain->SetBranchAddress("numberOfTracks_gen", &numberOfTracks_gen, &b_Rootuple_numberOfTracks_gen);
   fChain->SetBranchAddress("tracksPT_gen", &tracksPT_gen, &b_Rootuple_tracksPT_gen);
   fChain->SetBranchAddress("etaOfTracksPT_gen", &etaOfTracksPT_gen, &b_Rootuple_etaOfTracksPT_gen);
   fChain->SetBranchAddress("PUMCweight", &PUMCweight, &b_Rootuple_PUMCweight);
   fChain->SetBranchAddress("PU_NumInt", &PU_NumInt, &b_Rootuple_PU_NumInt);
   fChain->SetBranchAddress("PU_zpos", &PU_zpos, &b_Rootuple_PU_zpos);
   fChain->SetBranchAddress("PU_ntrks_lowpT", &PU_ntrks_lowpT, &b_Rootuple_PU_ntrks_lowpT);
   fChain->SetBranchAddress("PU_ntrks_highpT", &PU_ntrks_highpT, &b_Rootuple_PU_ntrks_highpT);
   fChain->SetBranchAddress("PU_sumpT_lowpT", &PU_sumpT_lowpT, &b_Rootuple_PU_sumpT_lowpT);
   fChain->SetBranchAddress("PU_sumpT_highpT", &PU_sumpT_highpT, &b_Rootuple_PU_sumpT_highpT);
   fChain->SetBranchAddress("EnergyInEta", &EnergyInEta, &b_Rootuple_EnergyInEta);
   Notify();
}

Bool_t ZAnalysisBase::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ZAnalysisBase::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ZAnalysisBase::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ZAnalysisBase_cxx
