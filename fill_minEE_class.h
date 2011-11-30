//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jan 17 17:23:47 2011 by ROOT version 5.18/00
// from TTree tree_/tree_
// found on file: files/pythia.root
//////////////////////////////////////////////////////////

#ifndef fill_minEE_class_h
#define fill_minEE_class_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
   const Int_t kMaxtimestamp_timeLow = 1;
   const Int_t kMaxtimestamp_timeHigh = 1;

class fill_minEE_class {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //DiffractiveNtuple *DiffRootuple;
   UInt_t          RunNumber;
   UInt_t          EventNumber;
   UInt_t          Lumi;
   Bool_t          HasTwoElectrons;
   Bool_t          ElectronsWithEnoughEt;
   Double_t        InvariantMass;
   Float_t         istlumi;
   Float_t         istlumierr;
 //vector<double>  ptTracks;
 //vector<double>  etaTracks;
 //vector<double>  ecalRawEnergyTracks;
 //vector<double>  hcalRawEnergyTracks;
 //vector<int>     TypeOfTracks;
 //vector<double>  distance;
   Double_t        Epz_Calo;
   Double_t        sumEHF_plus;
   Double_t        sumEHF_minus;
   Double_t        MinsumEHF_minus_plus;
   Double_t        etaMax_Calo;
   Double_t        etaMin_Calo;
   Double_t        Epz_PF_minus;
   Double_t        Epz_PF_plus;
   Double_t        etaMax_PF;
   Double_t        etaMin_PF;
   Double_t        etaMax_PF_ChargedFromOneVertex;
   Double_t        etaMin_PF_ChargedFromOneVertex;
   Double_t        Epz_PF_minus_NOHF;
   Double_t        Epz_PF_plus_NOHF;
   Double_t        etaMax_PF_NOHF;
   Double_t        etaMin_PF_NOHF;
   Bool_t          MoreThanOneVertex;
   Double_t        xi_gen;
   Int_t           nTowersHF_plus;
   Int_t           nTowersHF_minus;
   Double_t        etaAllTracks_PF;
   Double_t        energyTot_PF;
   Double_t        sumECastor_minus;
   Double_t        sumEZDC_minus;
   Double_t        sumEZDC_plus;
   Double_t        sumECastor_plus_gen;
   Double_t        sumECastor_minus_gen;
   Double_t        sumEZDC_minus_gen;
   Double_t        sumEZDC_plus_gen;
   Double_t        etaWeightedOnEnergy_PF;
   Double_t        energyTot_PF_Barrel_minus;
   Double_t        energyTot_PF_Barrel_plus;
   Double_t        energyTot_PF_minus;
   Double_t        energyTot_PF_plus;
   Double_t        numberOfVertexesInEvent;
   Double_t        istlumiPerBX;
   Double_t        xi_PF_minus;
   Double_t        xi_PF_plus;
   Double_t        xi_PF_NOZED_minus;
   Double_t        xi_PF_NOZED_plus;
   Double_t        max_eta_gap_PF;
   Double_t        max_second_eta_gap_PF;
   Double_t        thrustValue;
   Double_t        thrustX;
   Double_t        thrustY;
   Double_t        thrustZ;
   Double_t        sphericity;
   Double_t        planarity;
   Double_t        aplanarity;
   UInt_t          timestamp_timeLow_;
   UInt_t          timestamp_timeHigh_;
   Double_t        xi_PF_minus_charged;
   Double_t        xi_PF_plus_charged;
   Int_t           nTracks_PF;
   Double_t        energyTot_PF_EE_minus;
   Double_t        energyTot_PF_EE_plus;
   Int_t           bx;
   Int_t           numberOfVertexes;
   Double_t        sumEHF_minus_PF;
   Double_t        sumEHF_plus_PF;
   Double_t        etaOutcomingProton;
   Double_t        energyOutcomingProton;
   Double_t        ZDCRecHitTime;
   Double_t        mostEnergeticParticleEnergy_MC;
   Double_t        mostEnergeticParticleType_MC;
   Double_t        mostEnergeticParticleGap_MC;
   Double_t        mostEnergeticParticleEta_MC;
   Double_t        xi_gen_Pythia;
   Double_t        nTracks_gen;
   Double_t        CastoTotalEnergyTh;
   Double_t        sumECastor_Th_minus;

   // List of branches
   TBranch        *b_DiffRootuple_RunNumber;   //!
   TBranch        *b_DiffRootuple_EventNumber;   //!
   TBranch        *b_DiffRootuple_Lumi;   //!
   TBranch        *b_DiffRootuple_HasTwoElectrons;   //!
   TBranch        *b_DiffRootuple_ElectronsWithEnoughEt;   //!
   TBranch        *b_DiffRootuple_InvariantMass;   //!
   TBranch        *b_DiffRootuple_istlumi;   //!
   TBranch        *b_DiffRootuple_istlumierr;   //!
   TBranch        *b_DiffRootuple_Epz_Calo;   //!
   TBranch        *b_DiffRootuple_sumEHF_plus;   //!
   TBranch        *b_DiffRootuple_sumEHF_minus;   //!
   TBranch        *b_DiffRootuple_MinsumEHF_minus_plus;   //!
   TBranch        *b_DiffRootuple_etaMax_Calo;   //!
   TBranch        *b_DiffRootuple_etaMin_Calo;   //!
   TBranch        *b_DiffRootuple_Epz_PF_minus;   //!
   TBranch        *b_DiffRootuple_Epz_PF_plus;   //!
   TBranch        *b_DiffRootuple_etaMax_PF;   //!
   TBranch        *b_DiffRootuple_etaMin_PF;   //!
   TBranch        *b_DiffRootuple_etaMax_PF_ChargedFromOneVertex;   //!
   TBranch        *b_DiffRootuple_etaMin_PF_ChargedFromOneVertex;   //!
   TBranch        *b_DiffRootuple_Epz_PF_minus_NOHF;   //!
   TBranch        *b_DiffRootuple_Epz_PF_plus_NOHF;   //!
   TBranch        *b_DiffRootuple_etaMax_PF_NOHF;   //!
   TBranch        *b_DiffRootuple_etaMin_PF_NOHF;   //!
   TBranch        *b_DiffRootuple_MoreThanOneVertex;   //!
   TBranch        *b_DiffRootuple_xi_gen;   //!
   TBranch        *b_DiffRootuple_nTowersHF_plus;   //!
   TBranch        *b_DiffRootuple_nTowersHF_minus;   //!
   TBranch        *b_DiffRootuple_etaAllTracks_PF;   //!
   TBranch        *b_DiffRootuple_energyTot_PF;   //!
   TBranch        *b_DiffRootuple_sumECastor_minus;   //!
   TBranch        *b_DiffRootuple_sumEZDC_minus;   //!
   TBranch        *b_DiffRootuple_sumEZDC_plus;   //!
   TBranch        *b_DiffRootuple_sumECastor_plus_gen;   //!
   TBranch        *b_DiffRootuple_sumECastor_minus_gen;   //!
   TBranch        *b_DiffRootuple_sumEZDC_minus_gen;   //!
   TBranch        *b_DiffRootuple_sumEZDC_plus_gen;   //!
   TBranch        *b_DiffRootuple_etaWeightedOnEnergy_PF;   //!
   TBranch        *b_DiffRootuple_energyTot_PF_Barrel_minus;   //!
   TBranch        *b_DiffRootuple_energyTot_PF_Barrel_plus;   //!
   TBranch        *b_DiffRootuple_energyTot_PF_minus;   //!
   TBranch        *b_DiffRootuple_energyTot_PF_plus;   //!
   TBranch        *b_DiffRootuple_numberOfVertexesInEvent;   //!
   TBranch        *b_DiffRootuple_istlumiPerBX;   //!
   TBranch        *b_DiffRootuple_xi_PF_minus;   //!
   TBranch        *b_DiffRootuple_xi_PF_plus;   //!
   TBranch        *b_DiffRootuple_xi_PF_NOZED_minus;   //!
   TBranch        *b_DiffRootuple_xi_PF_NOZED_plus;   //!
   TBranch        *b_DiffRootuple_max_eta_gap_PF;   //!
   TBranch        *b_DiffRootuple_max_second_eta_gap_PF;   //!
   TBranch        *b_DiffRootuple_thrustValue;   //!
   TBranch        *b_DiffRootuple_thrustX;   //!
   TBranch        *b_DiffRootuple_thrustY;   //!
   TBranch        *b_DiffRootuple_thrustZ;   //!
   TBranch        *b_DiffRootuple_sphericity;   //!
   TBranch        *b_DiffRootuple_planarity;   //!
   TBranch        *b_DiffRootuple_aplanarity;   //!
   TBranch        *b_DiffRootuple_timestamp_timeLow_;   //!
   TBranch        *b_DiffRootuple_timestamp_timeHigh_;   //!
   TBranch        *b_DiffRootuple_xi_PF_minus_charged;   //!
   TBranch        *b_DiffRootuple_xi_PF_plus_charged;   //!
   TBranch        *b_DiffRootuple_nTracks_PF;   //!
   TBranch        *b_DiffRootuple_energyTot_PF_EE_minus;   //!
   TBranch        *b_DiffRootuple_energyTot_PF_EE_plus;   //!
   TBranch        *b_DiffRootuple_bx;   //!
   TBranch        *b_DiffRootuple_numberOfVertexes;   //!
   TBranch        *b_DiffRootuple_sumEHF_minus_PF;   //!
   TBranch        *b_DiffRootuple_sumEHF_plus_PF;   //!
   TBranch        *b_DiffRootuple_etaOutcomingProton;   //!
   TBranch        *b_DiffRootuple_energyOutcomingProton;   //!
   TBranch        *b_DiffRootuple_ZDCRecHitTime;   //!
   TBranch        *b_DiffRootuple_mostEnergeticParticleEnergy_MC;   //!
   TBranch        *b_DiffRootuple_mostEnergeticParticleType_MC;   //!
   TBranch        *b_DiffRootuple_mostEnergeticParticleGap_MC;   //!
   TBranch        *b_DiffRootuple_mostEnergeticParticleEta_MC;   //!
   TBranch        *b_DiffRootuple_xi_gen_Pythia;   //!
   TBranch        *b_DiffRootuple_nTracks_gen;   //!
   TBranch        *b_DiffRootuple_CastoTotalEnergyTh;   //!
   TBranch        *b_DiffRootuple_sumECastor_Th_minus;   //!

   fill_minEE_class(TTree *tree=0);
   virtual ~fill_minEE_class();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef fill_minEE_class_cxx
fill_minEE_class::fill_minEE_class(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.

   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("files/pythia.root");
      //      cout << "loading Pythia"<< endl ;
      if (!f) {
         f = new TFile("files/pythia.root");
      }
      tree = (TTree*)gDirectory->Get("tree_");

   }

   Init(tree);
}

fill_minEE_class::~fill_minEE_class()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t fill_minEE_class::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t fill_minEE_class::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void fill_minEE_class::Init(TTree *tree)
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

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_DiffRootuple_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_DiffRootuple_EventNumber);
   fChain->SetBranchAddress("Lumi", &Lumi, &b_DiffRootuple_Lumi);
   fChain->SetBranchAddress("HasTwoElectrons", &HasTwoElectrons, &b_DiffRootuple_HasTwoElectrons);
   fChain->SetBranchAddress("ElectronsWithEnoughEt", &ElectronsWithEnoughEt, &b_DiffRootuple_ElectronsWithEnoughEt);
   fChain->SetBranchAddress("InvariantMass", &InvariantMass, &b_DiffRootuple_InvariantMass);
   fChain->SetBranchAddress("istlumi", &istlumi, &b_DiffRootuple_istlumi);
   fChain->SetBranchAddress("istlumierr", &istlumierr, &b_DiffRootuple_istlumierr);
   fChain->SetBranchAddress("Epz_Calo", &Epz_Calo, &b_DiffRootuple_Epz_Calo);
   fChain->SetBranchAddress("sumEHF_plus", &sumEHF_plus, &b_DiffRootuple_sumEHF_plus);
   fChain->SetBranchAddress("sumEHF_minus", &sumEHF_minus, &b_DiffRootuple_sumEHF_minus);
   fChain->SetBranchAddress("MinsumEHF_minus_plus", &MinsumEHF_minus_plus, &b_DiffRootuple_MinsumEHF_minus_plus);
   fChain->SetBranchAddress("etaMax_Calo", &etaMax_Calo, &b_DiffRootuple_etaMax_Calo);
   fChain->SetBranchAddress("etaMin_Calo", &etaMin_Calo, &b_DiffRootuple_etaMin_Calo);
   fChain->SetBranchAddress("Epz_PF_minus", &Epz_PF_minus, &b_DiffRootuple_Epz_PF_minus);
   fChain->SetBranchAddress("Epz_PF_plus", &Epz_PF_plus, &b_DiffRootuple_Epz_PF_plus);
   fChain->SetBranchAddress("etaMax_PF", &etaMax_PF, &b_DiffRootuple_etaMax_PF);
   fChain->SetBranchAddress("etaMin_PF", &etaMin_PF, &b_DiffRootuple_etaMin_PF);
   fChain->SetBranchAddress("etaMax_PF_ChargedFromOneVertex", &etaMax_PF_ChargedFromOneVertex, &b_DiffRootuple_etaMax_PF_ChargedFromOneVertex);
   fChain->SetBranchAddress("etaMin_PF_ChargedFromOneVertex", &etaMin_PF_ChargedFromOneVertex, &b_DiffRootuple_etaMin_PF_ChargedFromOneVertex);
   fChain->SetBranchAddress("Epz_PF_minus_NOHF", &Epz_PF_minus_NOHF, &b_DiffRootuple_Epz_PF_minus_NOHF);
   fChain->SetBranchAddress("Epz_PF_plus_NOHF", &Epz_PF_plus_NOHF, &b_DiffRootuple_Epz_PF_plus_NOHF);
   fChain->SetBranchAddress("etaMax_PF_NOHF", &etaMax_PF_NOHF, &b_DiffRootuple_etaMax_PF_NOHF);
   fChain->SetBranchAddress("etaMin_PF_NOHF", &etaMin_PF_NOHF, &b_DiffRootuple_etaMin_PF_NOHF);
   fChain->SetBranchAddress("MoreThanOneVertex", &MoreThanOneVertex, &b_DiffRootuple_MoreThanOneVertex);
   fChain->SetBranchAddress("xi_gen", &xi_gen, &b_DiffRootuple_xi_gen);
   fChain->SetBranchAddress("nTowersHF_plus", &nTowersHF_plus, &b_DiffRootuple_nTowersHF_plus);
   fChain->SetBranchAddress("nTowersHF_minus", &nTowersHF_minus, &b_DiffRootuple_nTowersHF_minus);
   fChain->SetBranchAddress("etaAllTracks_PF", &etaAllTracks_PF, &b_DiffRootuple_etaAllTracks_PF);
   fChain->SetBranchAddress("energyTot_PF", &energyTot_PF, &b_DiffRootuple_energyTot_PF);
   fChain->SetBranchAddress("sumECastor_minus", &sumECastor_minus, &b_DiffRootuple_sumECastor_minus);
   fChain->SetBranchAddress("sumEZDC_minus", &sumEZDC_minus, &b_DiffRootuple_sumEZDC_minus);
   fChain->SetBranchAddress("sumEZDC_plus", &sumEZDC_plus, &b_DiffRootuple_sumEZDC_plus);
   fChain->SetBranchAddress("sumECastor_plus_gen", &sumECastor_plus_gen, &b_DiffRootuple_sumECastor_plus_gen);
   fChain->SetBranchAddress("sumECastor_minus_gen", &sumECastor_minus_gen, &b_DiffRootuple_sumECastor_minus_gen);
   fChain->SetBranchAddress("sumEZDC_minus_gen", &sumEZDC_minus_gen, &b_DiffRootuple_sumEZDC_minus_gen);
   fChain->SetBranchAddress("sumEZDC_plus_gen", &sumEZDC_plus_gen, &b_DiffRootuple_sumEZDC_plus_gen);
   fChain->SetBranchAddress("etaWeightedOnEnergy_PF", &etaWeightedOnEnergy_PF, &b_DiffRootuple_etaWeightedOnEnergy_PF);
   fChain->SetBranchAddress("energyTot_PF_Barrel_minus", &energyTot_PF_Barrel_minus, &b_DiffRootuple_energyTot_PF_Barrel_minus);
   fChain->SetBranchAddress("energyTot_PF_Barrel_plus", &energyTot_PF_Barrel_plus, &b_DiffRootuple_energyTot_PF_Barrel_plus);
   fChain->SetBranchAddress("energyTot_PF_minus", &energyTot_PF_minus, &b_DiffRootuple_energyTot_PF_minus);
   fChain->SetBranchAddress("energyTot_PF_plus", &energyTot_PF_plus, &b_DiffRootuple_energyTot_PF_plus);
   fChain->SetBranchAddress("numberOfVertexesInEvent", &numberOfVertexesInEvent, &b_DiffRootuple_numberOfVertexesInEvent);
   fChain->SetBranchAddress("istlumiPerBX", &istlumiPerBX, &b_DiffRootuple_istlumiPerBX);
   fChain->SetBranchAddress("xi_PF_minus", &xi_PF_minus, &b_DiffRootuple_xi_PF_minus);
   fChain->SetBranchAddress("xi_PF_plus", &xi_PF_plus, &b_DiffRootuple_xi_PF_plus);
   fChain->SetBranchAddress("xi_PF_NOZED_minus", &xi_PF_NOZED_minus, &b_DiffRootuple_xi_PF_NOZED_minus);
   fChain->SetBranchAddress("xi_PF_NOZED_plus", &xi_PF_NOZED_plus, &b_DiffRootuple_xi_PF_NOZED_plus);
   fChain->SetBranchAddress("max_eta_gap_PF", &max_eta_gap_PF, &b_DiffRootuple_max_eta_gap_PF);
   fChain->SetBranchAddress("max_second_eta_gap_PF", &max_second_eta_gap_PF, &b_DiffRootuple_max_second_eta_gap_PF);
   fChain->SetBranchAddress("thrustValue", &thrustValue, &b_DiffRootuple_thrustValue);
   fChain->SetBranchAddress("thrustX", &thrustX, &b_DiffRootuple_thrustX);
   fChain->SetBranchAddress("thrustY", &thrustY, &b_DiffRootuple_thrustY);
   fChain->SetBranchAddress("thrustZ", &thrustZ, &b_DiffRootuple_thrustZ);
   fChain->SetBranchAddress("sphericity", &sphericity, &b_DiffRootuple_sphericity);
   fChain->SetBranchAddress("planarity", &planarity, &b_DiffRootuple_planarity);
   fChain->SetBranchAddress("aplanarity", &aplanarity, &b_DiffRootuple_aplanarity);
   fChain->SetBranchAddress("timestamp.timeLow_", &timestamp_timeLow_, &b_DiffRootuple_timestamp_timeLow_);
   fChain->SetBranchAddress("timestamp.timeHigh_", &timestamp_timeHigh_, &b_DiffRootuple_timestamp_timeHigh_);
   fChain->SetBranchAddress("xi_PF_minus_charged", &xi_PF_minus_charged, &b_DiffRootuple_xi_PF_minus_charged);
   fChain->SetBranchAddress("xi_PF_plus_charged", &xi_PF_plus_charged, &b_DiffRootuple_xi_PF_plus_charged);
   fChain->SetBranchAddress("nTracks_PF", &nTracks_PF, &b_DiffRootuple_nTracks_PF);
   fChain->SetBranchAddress("energyTot_PF_EE_minus", &energyTot_PF_EE_minus, &b_DiffRootuple_energyTot_PF_EE_minus);
   fChain->SetBranchAddress("energyTot_PF_EE_plus", &energyTot_PF_EE_plus, &b_DiffRootuple_energyTot_PF_EE_plus);
   fChain->SetBranchAddress("bx", &bx, &b_DiffRootuple_bx);
   fChain->SetBranchAddress("numberOfVertexes", &numberOfVertexes, &b_DiffRootuple_numberOfVertexes);
   fChain->SetBranchAddress("sumEHF_minus_PF", &sumEHF_minus_PF, &b_DiffRootuple_sumEHF_minus_PF);
   fChain->SetBranchAddress("sumEHF_plus_PF", &sumEHF_plus_PF, &b_DiffRootuple_sumEHF_plus_PF);
   fChain->SetBranchAddress("etaOutcomingProton", &etaOutcomingProton, &b_DiffRootuple_etaOutcomingProton);
   fChain->SetBranchAddress("energyOutcomingProton", &energyOutcomingProton, &b_DiffRootuple_energyOutcomingProton);
   fChain->SetBranchAddress("ZDCRecHitTime", &ZDCRecHitTime, &b_DiffRootuple_ZDCRecHitTime);
   fChain->SetBranchAddress("mostEnergeticParticleEnergy_MC", &mostEnergeticParticleEnergy_MC, &b_DiffRootuple_mostEnergeticParticleEnergy_MC);
   fChain->SetBranchAddress("mostEnergeticParticleType_MC", &mostEnergeticParticleType_MC, &b_DiffRootuple_mostEnergeticParticleType_MC);
   fChain->SetBranchAddress("mostEnergeticParticleGap_MC", &mostEnergeticParticleGap_MC, &b_DiffRootuple_mostEnergeticParticleGap_MC);
   fChain->SetBranchAddress("mostEnergeticParticleEta_MC", &mostEnergeticParticleEta_MC, &b_DiffRootuple_mostEnergeticParticleEta_MC);
   fChain->SetBranchAddress("xi_gen_Pythia", &xi_gen_Pythia, &b_DiffRootuple_xi_gen_Pythia);
   fChain->SetBranchAddress("nTracks_gen", &nTracks_gen, &b_DiffRootuple_nTracks_gen);
   fChain->SetBranchAddress("CastoTotalEnergyTh", &CastoTotalEnergyTh, &b_DiffRootuple_CastoTotalEnergyTh);
   fChain->SetBranchAddress("sumECastor_Th_minus", &sumECastor_Th_minus, &b_DiffRootuple_sumECastor_Th_minus);
   Notify();
}

Bool_t fill_minEE_class::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void fill_minEE_class::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t fill_minEE_class::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef fill_minEE_class_cxx
