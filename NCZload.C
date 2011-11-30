#include <iostream>
#include <sstream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLegend.h>
#include "string.h"
#include <iomanip>
#include <sstream>
#include "NCutil.C"

TFile *Pom_Zee;
TFile *Pom_Zmm;
TFile *Pom_Zee_PDis;
TFile *Pom_Zmm_PDis;
TFile *PytD6T_Zee;
TFile *PytD6T_Zmm;
TFile *PytZ2_Zee;
TFile *PytZ2_Zmm;
TFile *Dat_Zmm;
TFile *Dat_Zee;
TFile *Dat_JPsiee_Sep;
TFile *Dat_JPsiee_Aug;
TFile *Dat_ZmmA;
TFile *Dat_ZmmB;
TFile *Dat_ZeeA;
TFile *Dat_ZeeB;
TFile *Dat_eeA;
TFile *Dat_eeB;
TFile *Dat_DAV_mmA;
TFile *Dat_DAV_mmB1;
TFile *Dat_DAV_mmB2;
TFile *Dat_DAV_eeB;
TFile *MBPythiaZ2_STD;
TFile *MBPythiaD6T_STD;
TFile *MBPythiaCW_DAV;
TFile *MBPythiaCW2_DAV;
TFile *MBPythia8_DAV;

TCut cutVxt1 = "numberOfVertexes==1";
TCut cutMx = "InvariantMass>80. && InvariantMass < 100.";
TCut cutPF1gap = "(etaMax_PF<2.85  || etaMin_PF>-2.85)" ;
TCut cutPF2gap = "(etaMax_PF<2.85 && etaMin_PF>-2.85)";
TCut cutPF2HF0 = "(sumEHF_PF_minus+sumEHF_PF_plus)==0" ;
TCut cutPF1HF0 = "(sumEHF_PF_minus==0 || sumEHF_PF_plus==0) && (!(sumEHF_PF_minus+sumEHF_PF_plus)==0)" ;
TCut cut2HF0 = "(sumEHF_minus+sumEHF_plus)==0" ;
TCut cut1HF0 = "(sumEHF_minus==0 || sumEHF_plus==0) && (!(sumEHF_minus+sumEHF_plus)==0)" ;
TCut cutCastor_Good = "(RunNumber>140200 && RunNumber<146400)";
TCut cutCastor_BadRun2 = "( || RunNumber>146460)";
TCut cutZmm = "nTracks_PF<10 && (TMath::Abs(energyTot_PF_Barrel_plus-energyTot_PF_Barrel_minus)<5.)";
TCut cutAll = cutVxt1 + cutMx + cutPF1gap+cutZmm;

void NCZload_all(){
  
  cout<<"Loading PytD6T_Zee"<<endl;
  PytD6T_Zee = TFile::Open("files/pythiaD6T_ee_v1_4.root");
  cout<<"Loading PytD6T_Zmm"<<endl;
  PytD6T_Zee = TFile::Open("files/pythiaD6T_mm_v1_4.root");
  cout<<"Loading PytZ2_Zee"<<endl;
  PytZ2_Zee = TFile::Open("files/pythiaZ2_ee_v1_2.root");
  cout<<"Loading PytZ2_Zmm"<<endl;
  PytZ2_Zmm = TFile::Open("files/pythiaZ2_mm_v1_3.root");

  cout<<"Loading  Pom_Zmm"<< endl;
  Pom_Zmm = TFile::Open("files/DiffractiveMC_mm_v1_4.Root");
  cout<<"Loading  Pom_Zee"<< endl;
  Pom_Zee = TFile::Open("files/DiffractiveMC_ee_v1_4.root");

  cout<<"Loading  Dat_Zmm"<< endl;
  Dat_Zmm = TFile::Open("files/ZetaSkim_mm_v1_2.root");
  cout<<"Loading  Dat_Zee"<< endl;
  Dat_Zee = TFile::Open("files/ZetaSkim_ee_v1_5.root");

  cout<<"Loading  Dat_JPsiee_Sep"<< endl;
  Dat_JPsiee_Sep = TFile::Open("files/JPsiSep_ee_v1.root");
  cout<<"Loading  Dat_JPsiee_Aug"<< endl;
  Dat_JPsiee_Aug = TFile::Open("files/JPsiAug_ee_v1.root");
  cout<<"Loading  Dat_ZmmA"<< endl;

  Dat_ZmmA = TFile::Open("files/Run2010A_mm_v1_5.root");
  cout<<"Loading  Dat_ZmmB"<< endl;
  Dat_ZmmB = TFile::Open("files/Run2010B_mm_v1.root");

  cout<<"Loading  Dat_ZeeA"<< endl;
  Dat_ZeeA = TFile::Open("files/Run2010A_ee_v1_4.root");
  cout<<"Loading  Dat_ZeeB"<< endl;
  Dat_ZeeB = TFile::Open("files/Run2010B_ee_v1.root");

  cout<<"Loading  Dat_DAV_eeA"<< endl;
  //  Dat_eeA = TFile::Open("files/ZetaSkimA_ee_DL10_v1_6.root");
  Dat_DAV_eeA = TFile::Open("files/SkimA_ee_DL10_DAV_v1_7.root");
  cout<<"Loading  Dat_DAV_eeB"<< endl;
  Dat_DAV_eeB = TFile::Open("files/SkimB_ee_DL10_DAV_v1_7.root");

  return;   
  //  tree_->SetMarkerStyle(20);
  //  tree_->SetMarkerSize(.4);

}

void NCZload_DAV_ee(){

  cout<<"Loading  Dat_eeA"<< endl;
  //  Dat_eeA = TFile::Open("files/ZetaSkimA_ee_DL10_v1_6.root");
  Dat_DAV_eeA = TFile::Open("files/SkimA_ee_DL10_DAV_v1_7.root");
  cout<<"Loading  Dat_eeB"<< endl;
  Dat_DAV_eeB = TFile::Open("files/SkimB_ee_DL10_DAV_v1_7.root");

  return;
  //  tree_->SetMarkerStyle(20);
  //  tree_->SetMarkerSize(.4);
}


void NCZload_DAV_mm(){

  cout<<"Loading  Dat_DAV_mmA"<< endl;
  //  Dat_eeA = TFile::Open("files/ZetaSkimA_ee_DL10_v1_6.root");
  Dat_DAV_mmA = TFile::Open("files/SkimA_mm_DAV_v1_9.root");
  cout<<"Loading  Dat_DAV_mmB"<< endl;
  Dat_DAV_mmB1 = TFile::Open("files/SkimB1_mm_DAV_v1_9.root");
  Dat_DAV_mmB2 = TFile::Open("files/SkimB2_mm_DAV_v1_9.root");

  return;
  //  tree_->SetMarkerStyle(20);
  //  tree_->SetMarkerSize(.4);
}


void NCZload_ee(){

  cout<<"Loading  Dat_eeA"<< endl;
  Dat_eeA = TFile::Open("files/ZetaSkimA_ee_DL10_v1_6.root");
  cout<<"Loading  Dat_eeB"<< endl;
  Dat_eeB = TFile::Open("files/ZetaSkimB_ee_DL10_v1_6.root");

  return;
  //  tree_->SetMarkerStyle(20);
  //  tree_->SetMarkerSize(.4);
}

void NCZload_Pom_PDis(){

  cout<<"Loading  Pom_Zmm_PDis"<< endl;
  Pom_Zmm_PDis = TFile::Open("files/MCDissociative_mm_v1_7.root");
  cout<<"Loading  Pom_Zee_PDis"<< endl;
  Pom_Zee_PDis = TFile::Open("files/MCDissociative_ee_v1_7.root");


  return;
  //  tree_->SetMarkerStyle(20);
  //  tree_->SetMarkerSize(.4);
}

void NCZload_MB(){

  cout<<"Loading MBPythiaZ2_STD"<< endl;
  MBPythiaZ2_STD = TFile::Open("files/MBPythiaZ2_STD_v1_8.root");

  cout<<"Loading MBPythiaCW2_DAV"<< endl;
  MBPythiaCW2_DAV = TFile::Open("files/MBPythiaCW_DAV_v1_12.root");

  cout<<"Loading MBPythiaCW_DAV"<< endl;
  MBPythiaCW_DAV = TFile::Open("files/MBPythiaCW_DAV_v1_8.root");


  cout<<"Loading MBPythia8_DAV"<< endl;
  MBPythia8_DAV = TFile::Open("files/MBPythia8_v1_16_CHA.root");


  return;
    }
