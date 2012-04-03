#ifndef HistoZDiff_NC.h
#define HistoZDiff_NC.h
#define ZAnalysisBase_cxx

/** \class Histograms
 *
 * A set of histograms for ZDiff candidates.
 *
 *  Adapted from a code of Amapane, Botta 
 */
#include "TH1F.h"
#include "TH2F.h"
#include "TString.h"
#include "TFile.h"
#include "Math.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

class HCand {
 public:

  HCand(const TString& name1_, const TString& name2_)  {

    TString N1 = name1_;
    TString N2 = name2_;
    TString N3;


    const Double_t xlow[12] = {0., 4.,10.,20.,40.,60.,80.,100.,120.,140.,160.,180.};
    TH1F::SetDefaultSumw2(kTRUE);

    N3 = "_minEHF_";
    gDirectory->Delete(N1+N3+N2);
    hminEHF = new TH1F(N1+N3+N2,N1+N3+N2, 20, 0., 1000);
    N3 = "_minEHFZoom_";
    gDirectory->Delete(N1+N3+N2);
    hminEHFZoom = new TH1F(N1+N3+N2,N1+N3+N2,40,0.,200.);
    N3 = "_EHF_";
    gDirectory->Delete(N1+N3+N2);
    hEHF = new TH1F(N1+N3+N2,N1+N3+N2, 40, 0., 2000.);
    N3 = "_EHF_L_";
    gDirectory->Delete(N1+N3+N2);
    hEHF_L = new TH1F(N1+N3+N2,N1+N3+N2, 40, 0., 2000);
    N3 = "_EHF_S_";
    gDirectory->Delete(N1+N3+N2);
    hEHF_S = new TH1F(N1+N3+N2,N1+N3+N2, 40, 0., 2000);
    N3 = "_EHFZoom_L_";
    gDirectory->Delete(N1+N3+N2);
    hEHFZoom_L = new TH1F(N1+N3+N2,N1+N3+N2, 40,0.,200.);
    N3 = "_EHFZoom_S_";
    gDirectory->Delete(N1+N3+N2);
    hEHFZoom_S = new TH1F(N1+N3+N2,N1+N3+N2, 40,0.,200.);

    N3 = "_EHFSGT0_SL_";
    gDirectory->Delete(N1+N3+N2);
    hEHFSGT0_SL = new TH1F(N1+N3+N2,N1+N3+N2, 40, 0., 2000);

    N3 = "_EHFLGT0_SL_";
    gDirectory->Delete(N1+N3+N2);
    hEHFLGT0_SL = new TH1F(N1+N3+N2,N1+N3+N2, 40, 0., 2000);

    N3 = "_EHFSLGT0_SL_";
    gDirectory->Delete(N1+N3+N2);
    hEHFSLGT0_SL = new TH1F(N1+N3+N2,N1+N3+N2, 40, 0., 2000);

    N3 = "_EHFZoom_";
    gDirectory->Delete(N1+N3+N2);
    hEHFZoom = new TH1F(N1+N3+N2,N1+N3+N2, 40,0.,200.);

    N3 = "_Xi_PF_";
    gDirectory->Delete(N1+N3+N2);
    hXi_PF = new TH1F(N1+N3+N2,N1+N3+N2, 100, 0., 0.5);

    N3 = "_Xi_Calo_";
    gDirectory->Delete(N1+N3+N2);
    hXi_Calo = new TH1F(N1+N3+N2,N1+N3+N2, 100, 0., 0.5);

    N3 = "_Xi_Z_";
    gDirectory->Delete(N1+N3+N2);
    hXi_Z = new TH1F(N1+N3+N2,N1+N3+N2, 100, 0., 0.5);

    N3 = "_GoodVtx_";
    gDirectory->Delete(N1+N3+N2);
    hGoodVtx = new TH1F(N1+N3+N2,N1+N3+N2, 21, -0.5, 20.5);

    N3 = "_PU_NumInt_";
    gDirectory->Delete(N1+N3+N2);
    hPU_NumInt = new TH1F(N1+N3+N2,N1+N3+N2, 21, -0.5, 20.5);

    N3 = "_nPart_PF_";
    gDirectory->Delete(N1+N3+N2);
    hnPart_PF = new TH1F(N1+N3+N2,N1+N3+N2, 40, -0.5, 400.5);

    N3 = "_vertexMolteplicity_";
    gDirectory->Delete(N1+N3+N2);
    hvertexMolteplicity = new TH1F(N1+N3+N2,N1+N3+N2, 200, -0.5, 200.5);

    N3 = "_Mx_";
    gDirectory->Delete(N1+N3+N2);
    hMx = new TH1F(N1+N3+N2,N1+N3+N2, 50, 0., 3000);

    N3 = "_ZMass_";
    gDirectory->Delete(N1+N3+N2);
    hZMass = new TH1F(N1+N3+N2,N1+N3+N2, 40, 40., 120.);

    N3 = "_max_eta_gap_PF_";
    gDirectory->Delete(N1+N3+N2);
    hmax_eta_gap_PF = new TH1F(N1+N3+N2,N1+N3+N2, 12, 0.,6.);

    N3 = "_max_eta_charged_PF_";
    gDirectory->Delete(N1+N3+N2);
    hmax_eta_charged_PF = new TH1F(N1+N3+N2,N1+N3+N2, 24, -3,3.);

    N3 = "_max_second_eta_gap_";
    gDirectory->Delete(N1+N3+N2);
    hmax_second_eta_gap = new TH1F(N1+N3+N2,N1+N3+N2, 10, 0., 5.);

    N3 = "_max_plus_second_eta_gap_";
    gDirectory->Delete(N1+N3+N2);
    hmax_plus_second_eta_gap = new TH1F(N1+N3+N2,N1+N3+N2, 20, 0., 10.);

    N3 = "_etaZ_";
    gDirectory->Delete(N1+N3+N2);
    hetaZ = new TH1F(N1+N3+N2,N1+N3+N2, 20, -5.,5.);

    N3 = "_etaWeightedOnEnergy_PF_";
    gDirectory->Delete(N1+N3+N2);
    hetaWeightedOnEnergy_PF = new TH1F(N1+N3+N2,N1+N3+N2, 40, -10.,10.);

    N3 = "_nTowersHF_plus_";
    gDirectory->Delete(N1+N3+N2);
    hnTowersHF_plus = new TH1F(N1+N3+N2,N1+N3+N2, 50, 0.,100.);

    N3 = "_EBarrel_";
    gDirectory->Delete(N1+N3+N2);
    hEBarrel = new TH1F(N1+N3+N2,N1+N3+N2, 25, 0.,500.);

    N3 = "_EEndcap_";
    gDirectory->Delete(N1+N3+N2);
    hEEndcap = new TH1F(N1+N3+N2,N1+N3+N2, 30, 0.,1500.);

    N3 = "_EtaEnergy_";
    gDirectory->Delete(N1+N3+N2);
    hEtaEnergy = new TH1F(N1+N3+N2,N1+N3+N2, 40, -5., 5.);

    N3 = "_EtaEnergy_S_";
    gDirectory->Delete(N1+N3+N2);
    hEtaEnergy_S = new TH1F(N1+N3+N2,N1+N3+N2, 80, -5., 5.);

    N3 = "_EtaEnergy_L_";
    gDirectory->Delete(N1+N3+N2);
    hEtaEnergy_L = new TH1F(N1+N3+N2,N1+N3+N2, 80, -5., 5.);

    N3 = "_Gap_Calo_";
    gDirectory->Delete(N1+N3+N2);
    hGap_Calo = new TH1F(N1+N3+N2,N1+N3+N2, 20, 0., 10.);

    N3 = "_Gap_PF_";
    gDirectory->Delete(N1+N3+N2);
    hGap_PF = new TH1F(N1+N3+N2,N1+N3+N2, 20, 0., 10.);

    N3 = "_MaxEtaGap_";
    gDirectory->Delete(N1+N3+N2);
    hMaxEtaGap = new TH1F(N1+N3+N2,N1+N3+N2, 20, 0., 10.);

    N3 = "_InstLumiPerBx_";
    gDirectory->Delete(N1+N3+N2);
    hLumi = new TH1F(N1+N3+N2,N1+N3+N2, 20, 0., 2.);

    N3 = "_EnergyCastorModule_";
    gDirectory->Delete(N1+N3+N2);
    hEnergyCastorModule = new TH1F(N1+N3+N2,N1+N3+N2, 20, 0., 20.);
    N3 = "_sumECastor_minus_";
    gDirectory->Delete(N1+N3+N2);
    hsumECastor_minus = new TH1F(N1+N3+N2,N1+N3+N2, 100, 0., 10000.);


    N3 = "_bx_";
    gDirectory->Delete(N1+N3+N2);
    hbx = new TH1F(N1+N3+N2,N1+N3+N2, 3300, -0.5, 3299.5);

    N3 = "_EHF_vs_Lumi_";
    gDirectory->Delete(N1+N3+N2);
    hEHF_vs_Lumi = new TProfile(N1+N3+N2,N1+N3+N2, 40, 0., 2.,0.,1000);

    N3 = "_EE_vs_Lumi_";
    gDirectory->Delete(N1+N3+N2);
    hEE_vs_Lumi = new TProfile(N1+N3+N2,N1+N3+N2, 40, 0., 2.,0.,1000);


    N3 = "_EB_vs_Lumi_";
    gDirectory->Delete(N1+N3+N2);
    hEB_vs_Lumi = new TProfile(N1+N3+N2,N1+N3+N2, 40, 0., 2.,0.,1000);


    N3 = "_MaxGap_vs_Lumi_";
    gDirectory->Delete(N1+N3+N2);
    hMaxGap_vs_Lumi = new TProfile(N1+N3+N2,N1+N3+N2, 40, 0., 2.,0.,10);


    N3 = "_ECastor_vs_Lumi_";
    gDirectory->Delete(N1+N3+N2);
    hECastor_vs_Lumi = new TProfile(N1+N3+N2,N1+N3+N2, 40, 0., 2.,0.,1000);


  }


  ~HCand(){
  }

  void Fill(int MCFlag,float minEHF, float EHF_S, float EHF_L, 
	    float xi_min, float xi_min_calo, float xi_min_Z, int GoodVtx,
	    int PU_NumInt, int nPart_PF, int nVtx, float Mx,
	    float ZMass, float max_eta_gap_PF, float etaZ, float etaWeightedOnEnergy_PF,
	    int nTowersHF_plus,	float EB, float EE,int bx,
	    std::vector<float>& EtaE, 
	    float EtaE_S[],
	    float EtaE_L[],
	    float max_second_eta_gap, float MaxEtaGap, float Gap_Calo, float Gap_PF, 
	    float Lumi,
	    std::vector<float>& EnergyCastorModule,float sumECastor_minus, 
	    float MaxEtaCharged, float weight) 
  {


    for (Int_t i=0;i<80;i++)
      {


	if (i<40)hEtaEnergy->AddBinContent(i+1, EtaE[i]);
	if (i<15)hEnergyCastorModule->AddBinContent(i+1, EnergyCastorModule[i]);

 
	hEtaEnergy_S->AddBinContent(i+1, EtaE_S[i]);
	hEtaEnergy_L->AddBinContent(i+1, EtaE_L[i]);
      }

    float EHFTot= EHF_S+EHF_L;
    hEBarrel->Fill(EB, weight);
    hEEndcap->Fill(EE, weight);
    hbx->Fill(bx, weight);
    hminEHF->Fill(minEHF,weight);
    hminEHFZoom->Fill(minEHF,weight);

    hEHF->Fill(EHFTot,weight);
    hEHFZoom->Fill(EHFTot,weight);
    hEHF_S->Fill(EHF_S,weight);
    hEHF_L->Fill(EHF_L,weight);
    hEHFZoom_S->Fill(EHF_S,weight);
    hEHFZoom_L->Fill(EHF_L,weight);

    if (EHF_L > 0 )     hEHFLGT0_SL->Fill(EHFTot,weight); 
    if (EHF_S > 0 )     hEHFSGT0_SL->Fill(EHFTot,weight); 
    if (EHF_S > 0 && EHF_L > 0 )     hEHFSLGT0_SL->Fill(EHFTot,weight); 

    hXi_PF->Fill(xi_min,weight);
    hXi_Calo->Fill(xi_min_calo,weight);
    hXi_Z->Fill(xi_min_Z,weight);
    hGoodVtx->Fill(GoodVtx,weight);
    hPU_NumInt->Fill(PU_NumInt,weight);
    hnPart_PF->Fill(nPart_PF,weight);
    hvertexMolteplicity->Fill(nVtx,weight);
    hMx->Fill(Mx,weight);
    hZMass->Fill(ZMass,weight);
    hmax_eta_gap_PF->Fill(max_eta_gap_PF,weight);
    hetaZ->Fill(etaZ,weight);
    hetaWeightedOnEnergy_PF->Fill(etaWeightedOnEnergy_PF, weight);
    hnTowersHF_plus->Fill(nTowersHF_plus ,weight);
    hmax_second_eta_gap->Fill(max_second_eta_gap ,weight);
    hmax_plus_second_eta_gap->Fill(max_eta_gap_PF+max_second_eta_gap ,weight);
    hGap_Calo->Fill(Gap_Calo,weight);
    hGap_PF->Fill(Gap_PF,weight);
    hMaxEtaGap->Fill(MaxEtaGap,weight);
    hsumECastor_minus->Fill(sumECastor_minus,weight);
    hmax_eta_charged_PF->Fill(MaxEtaCharged,weight);
    hLumi->Fill(Lumi*6.37);
    hEHF_vs_Lumi->Fill(Lumi*6.37, EHF_S+EHF_L);
    hEE_vs_Lumi->Fill(Lumi*6.37, EE);
    hEB_vs_Lumi->Fill(Lumi*6.37, EB);
    hMaxGap_vs_Lumi->Fill(Lumi*6.37, max_eta_gap_PF);
    hECastor_vs_Lumi->Fill(Lumi*6.37, sumECastor_minus);


    
  }


  void WriteInFile(std::string filename){

    TFile fOut(filename.c_str(),"UPDATE");
    fOut.cd();

    hEBarrel->Write();
    hEEndcap->Write();
    hbx->Write();
    hminEHF->Write();
    hminEHFZoom->Write();
    hEHF->Write();
    hEHF_S->Write();
    hEHF_L->Write();
    hEHFZoom_S->Write();
    hEHFZoom_L->Write();
    hEHFSGT0_SL->Write();
    hEHFLGT0_SL->Write();
    hEHFSLGT0_SL->Write();

    hEHFZoom->Write();
    hXi_PF->Write();
    hXi_Calo->Write();
    hXi_Z->Write();
    hGoodVtx->Write(); 
    hPU_NumInt->Write();
    hnPart_PF->Write();
    hvertexMolteplicity->Write();
    hMx->Write();
    hZMass->Write();
    hmax_eta_gap_PF->Write();
    hetaZ->Write();
    hetaWeightedOnEnergy_PF->Write();
    hnTowersHF_plus->Write();
    hmax_eta_charged_PF->Write();
    Float_t scale = hZMass->GetEntries();

    cout << "N entries in histo: = " << scale <<  endl;
    hEtaEnergy->Scale(1./(scale+1.));
    hEtaEnergy->Write();

    hEtaEnergy_L->Scale(1./(scale+1.));
    hEtaEnergy_L->Write();

    hEtaEnergy_S->Scale(1./(scale+1.));
    hEtaEnergy_S->Write();

    hEnergyCastorModule->Scale(1./(scale+1.));
    hEnergyCastorModule->Write();
    hmax_second_eta_gap->Write();
    hmax_plus_second_eta_gap->Write();

    hGap_Calo->Write();
    hGap_PF->Write();
    hMaxEtaGap->Write();
    hLumi->Write();
    hsumECastor_minus->Write();

    hEE_vs_Lumi->Write();
    hEHF_vs_Lumi->Write();
    hEB_vs_Lumi->Write();
    hMaxGap_vs_Lumi->Write();
    hECastor_vs_Lumi->Write();


    fOut.Close();
  }

 public:

  TH1F * hEBarrel;
  TH1F * hEEndcap;
  TH1F * hbx;
  TH1F * hminEHFZoom;
  TH1F * hminEHF;
  TH1F * hEHF_S;
  TH1F * hEHF_L;
  TH1F * hEHFZoom_S;
  TH1F * hEHFZoom_L;

  TH1F * hEHFSGT0_SL;
  TH1F * hEHFLGT0_SL;
  TH1F * hEHFSLGT0_SL;

  TH1F * hEHFZoom;
  TH1F * hEHF;
  TH1F * hXi_PF;
  TH1F * hXi_Calo;
  TH1F * hXi_Z;
  TH1F * hGoodVtx;
  TH1F * hPU_NumInt;
  TH1F *  hnPart_PF;
  TH1F *  hvertexMolteplicity;
  TH1F * hMx;
  TH1F * hZMass;
  TH1F * hmax_eta_gap_PF;
  TH1F *hetaZ;
  TH1F *hetaWeightedOnEnergy_PF;
  TH1F *hnTowersHF_plus;
  TH1F *hEtaEnergy;
  TH1F *hEtaEnergy_S;
  TH1F *hEtaEnergy_L;
  TH1F *hmax_second_eta_gap;
  TH1F *hmax_plus_second_eta_gap;
  TH1F  *hGap_Calo;
  TH1F  *hGap_PF;
  TH1F  *hMaxEtaGap;
  TH1F  *hLumi;
  TH1F  *hEnergyCastorModule;
  TH1F  *hsumECastor_minus;
  TH1F * hmax_eta_charged_PF;

  TProfile * hEE_vs_Lumi;
  TProfile * hEHF_vs_Lumi;
  TProfile * hEB_vs_Lumi;
  TProfile * hMaxGap_vs_Lumi;
  TProfile * hECastor_vs_Lumi;


};



class HCandGen {

 public:

  HCandGen(const TString& name1_, const TString& name2_)  {

    TString N1 = name1_;
    TString N2 = name2_;
    TString N3;

    N3 = "_PUVtx_";
    gDirectory->Delete(N1+N3+N2);
    hVtx_Gen = new TH1F(N1+N3+N2,N1+N3+N2, 30, 0.,30.);
    N3 = "_Weight_";
    gDirectory->Delete(N1+N3+N2);
    hWeight_Gen = new TH1F(N1+N3+N2,N1+N3+N2, 100, 0.,0.01);

  }

  ~HCandGen(){
  }

  void Fill(Int_t NVtx_gen, Float_t weight)
  { 
    hVtx_Gen->Fill(NVtx_gen);
    hWeight_Gen->Fill(weight);
  }

  void WriteInFileGEN(std::string filename)
  {

    TFile fOut(filename.c_str(),"UPDATE");
    fOut.cd();

    hVtx_Gen->Write();
    hWeight_Gen->Write();

    
    fOut.Close();
  }

 public:
  TH1F * hVtx_Gen;
  TH1F * hWeight_Gen;

};

#endif
