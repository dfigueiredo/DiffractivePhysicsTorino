//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec  2 22:56:22 2010 by ROOT version 5.18/00
// from TTree tree_/tree_
// found on file: DiffractiveMC.root
//////////////////////////////////////////////////////////

#ifndef DiffAnalysis_h
#define DiffAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>


class DiffAnalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   TFile*    _outF;
   Double_t  _cutEnergy;

   TH1F* hNC;

   UInt_t          RunNumber;
   UInt_t          EventNumber;
   UInt_t          Lumi;
   Bool_t          HasTwoElectrons;
   Bool_t          ElectronsWithEnoughEt;
   Float_t         istlumi;
   Float_t         istlumierr;
 //vector<double>  ptTracks;
 //vector<double>  etaTracks;
 //vector<double>  ecalRawEnergyTracks;
 //vector<double>  hcalRawEnergyTracks;
 //vector<int>     TypeOfTracks;
 //vector<double>  distance;
   Double_t        Epz;
   Double_t        sumEHF_plus;
   Double_t        sumEHF_minus;
   Double_t        MinsumEHF_minus_plus;
   Double_t        etaMax_Calo;
   Double_t        etaMin_Calo;
   Double_t        Epz_PF_minus;
   Double_t        Epz_PF_plus;
   Double_t        etaMax_PF;
   Double_t        etaMin_PF;
   Double_t        etaMax_PF_Vertex_Selection;
   Double_t        etaMin_PF_Vertex_Selection;
   Double_t        Epz_PF_minus_NOHF;
   Double_t        Epz_PF_plus_NOHF;
   Double_t        etaMax_PF_NOHF;
   Double_t        etaMin_PF_NOHF;
   Bool_t          MoreThanOneVertex;
   Double_t        xi_gen;
   Int_t           nTowersHF_plus;
   Int_t           nTowersHF_minus;
   Double_t        etaAllTracks;
   Double_t        energyTot;
   Double_t        CastorMaxEnergy;
   Double_t        ZDCMaxEnergy;
   Double_t        etaWeightedOnEnergy;
   Double_t        energyTot_Barrel;
   Double_t        energyTot_minus;
   Double_t        energyTot_plus;

   // List of branches
   TBranch        *b_DiffRootuple_RunNumber;
   TBranch        *b_DiffRootuple_EventNumber;
   TBranch        *b_DiffRootuple_Lumi;
   TBranch        *b_DiffRootuple_HasTwoElectrons;
   TBranch        *b_DiffRootuple_ElectronsWithEnoughEt;
   TBranch        *b_DiffRootuple_istlumi;
   TBranch        *b_DiffRootuple_istlumierr;
   TBranch        *b_DiffRootuple_Epz;
   TBranch        *b_DiffRootuple_sumEHF_plus;
   TBranch        *b_DiffRootuple_sumEHF_minus;
   TBranch        *b_DiffRootuple_MinsumEHF_minus_plus;
   TBranch        *b_DiffRootuple_etaMax_Calo;
   TBranch        *b_DiffRootuple_etaMin_Calo;
   TBranch        *b_DiffRootuple_Epz_PF_minus;
   TBranch        *b_DiffRootuple_Epz_PF_plus;
   TBranch        *b_DiffRootuple_etaMax_PF;
   TBranch        *b_DiffRootuple_etaMin_PF;
   TBranch        *b_DiffRootuple_etaMax_PF_Vertex_Selection;
   TBranch        *b_DiffRootuple_etaMin_PF_Vertex_Selection;
   TBranch        *b_DiffRootuple_Epz_PF_minus_NOHF;
   TBranch        *b_DiffRootuple_Epz_PF_plus_NOHF;
   TBranch        *b_DiffRootuple_etaMax_PF_NOHF;
   TBranch        *b_DiffRootuple_etaMin_PF_NOHF;
   TBranch        *b_DiffRootuple_MoreThanOneVertex;
   TBranch        *b_DiffRootuple_xi_gen;
   TBranch        *b_DiffRootuple_nTowersHF_plus;
   TBranch        *b_DiffRootuple_nTowersHF_minus;
   TBranch        *b_DiffRootuple_etaAllTracks;
   TBranch        *b_DiffRootuple_energyTot;
   TBranch        *b_DiffRootuple_CastorMaxEnergy;
   TBranch        *b_DiffRootuple_ZDCMaxEnergy;
   TBranch        *b_DiffRootuple_etaWeightedOnEnergy;
   TBranch        *b_DiffRootuple_energyTot_Barrel;
   TBranch        *b_DiffRootuple_energyTot_minus;
   TBranch        *b_DiffRootuple_energyTot_plus;
   
   DiffAnalysis(TTree *tree=0);
   virtual ~DiffAnalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef DiffAnalysis_cxx
DiffAnalysis::DiffAnalysis(TTree *tree)
 :_outF(0)
 , _cutEnergy(0.0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("DiffractiveMC.root");
      if (!f) {
         f = new TFile("DiffractiveMC.root");
      }
      tree = (TTree*)gDirectory->Get("tree_");

   }
   Init(tree);
}

DiffAnalysis::~DiffAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t DiffAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DiffAnalysis::LoadTree(Long64_t entry)
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

void DiffAnalysis::Init(TTree *tree)
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
   fChain->SetBranchAddress("istlumi", &istlumi, &b_DiffRootuple_istlumi);
   fChain->SetBranchAddress("istlumierr", &istlumierr, &b_DiffRootuple_istlumierr);
   fChain->SetBranchAddress("Epz", &Epz, &b_DiffRootuple_Epz);
   fChain->SetBranchAddress("sumEHF_plus", &sumEHF_plus, &b_DiffRootuple_sumEHF_plus);
   fChain->SetBranchAddress("sumEHF_minus", &sumEHF_minus, &b_DiffRootuple_sumEHF_minus);
   fChain->SetBranchAddress("MinsumEHF_minus_plus", &MinsumEHF_minus_plus, &b_DiffRootuple_MinsumEHF_minus_plus);
   fChain->SetBranchAddress("etaMax_Calo", &etaMax_Calo, &b_DiffRootuple_etaMax_Calo);
   fChain->SetBranchAddress("etaMin_Calo", &etaMin_Calo, &b_DiffRootuple_etaMin_Calo);
   fChain->SetBranchAddress("Epz_PF_minus", &Epz_PF_minus, &b_DiffRootuple_Epz_PF_minus);
   fChain->SetBranchAddress("Epz_PF_plus", &Epz_PF_plus, &b_DiffRootuple_Epz_PF_plus);
   fChain->SetBranchAddress("etaMax_PF", &etaMax_PF, &b_DiffRootuple_etaMax_PF);
   fChain->SetBranchAddress("etaMin_PF", &etaMin_PF, &b_DiffRootuple_etaMin_PF);
   fChain->SetBranchAddress("etaMax_PF_Vertex_Selection", &etaMax_PF_Vertex_Selection, &b_DiffRootuple_etaMax_PF_Vertex_Selection);
   fChain->SetBranchAddress("etaMin_PF_Vertex_Selection", &etaMin_PF_Vertex_Selection, &b_DiffRootuple_etaMin_PF_Vertex_Selection);
   fChain->SetBranchAddress("Epz_PF_minus_NOHF", &Epz_PF_minus_NOHF, &b_DiffRootuple_Epz_PF_minus_NOHF);
   fChain->SetBranchAddress("Epz_PF_plus_NOHF", &Epz_PF_plus_NOHF, &b_DiffRootuple_Epz_PF_plus_NOHF);
   fChain->SetBranchAddress("etaMax_PF_NOHF", &etaMax_PF_NOHF, &b_DiffRootuple_etaMax_PF_NOHF);
   fChain->SetBranchAddress("etaMin_PF_NOHF", &etaMin_PF_NOHF, &b_DiffRootuple_etaMin_PF_NOHF);
   fChain->SetBranchAddress("MoreThanOneVertex", &MoreThanOneVertex, &b_DiffRootuple_MoreThanOneVertex);
   fChain->SetBranchAddress("xi_gen", &xi_gen, &b_DiffRootuple_xi_gen);
   fChain->SetBranchAddress("nTowersHF_plus", &nTowersHF_plus, &b_DiffRootuple_nTowersHF_plus);
   fChain->SetBranchAddress("nTowersHF_minus", &nTowersHF_minus, &b_DiffRootuple_nTowersHF_minus);
   fChain->SetBranchAddress("etaAllTracks", &etaAllTracks, &b_DiffRootuple_etaAllTracks);
   fChain->SetBranchAddress("energyTot", &energyTot, &b_DiffRootuple_energyTot);
   fChain->SetBranchAddress("CastorMaxEnergy", &CastorMaxEnergy, &b_DiffRootuple_CastorMaxEnergy);
   fChain->SetBranchAddress("ZDCMaxEnergy", &ZDCMaxEnergy, &b_DiffRootuple_ZDCMaxEnergy);
   fChain->SetBranchAddress("etaWeightedOnEnergy", &etaWeightedOnEnergy, &b_DiffRootuple_etaWeightedOnEnergy);
   fChain->SetBranchAddress("energyTot_Barrel", &energyTot_Barrel, &b_DiffRootuple_energyTot_Barrel);
   fChain->SetBranchAddress("energyTot_minus", &energyTot_minus, &b_DiffRootuple_energyTot_minus);
   fChain->SetBranchAddress("energyTot_plus", &energyTot_plus, &b_DiffRootuple_energyTot_plus);

   hNC = new TH1F("hNC","NC",10,0,10);
   
   Notify();
}

Bool_t DiffAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DiffAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DiffAnalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef DiffAnalysis_cxx
