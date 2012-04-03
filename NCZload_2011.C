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

TFile *Dat_Zmm;
TFile *Dat_Zee;
TFile *Dat_ZmmA;
TFile *Dat_ZmmB;
TFile *Dat_ZeeA;
TFile *Dat_ZeeB;
TFile *NDat_ZeeA;
TFile *NDat_ZeeB;
TFile *DATA10_Zee;
TFile *DATA11_Zee;
TFile *DATA1011_Zee;
TFile *Dat10_Zee;
TFile *POMPYT10_Zmm;
TFile *Z2PY610_Zmm;
TFile *Z2PY6_Zee;
TFile *POMPYT_Zee;
TFile *C4PY8_Zee;

void NCZload_3_4(){
  

  Dat_Zmm = TFile::Open("files/zdiff/3_4/ZetaSkim_mm_v1_2.root");
  cout<<"Loading  Dat_Zee"<< endl;
  Dat_Zee = TFile::Open("files/zdiff/3_4/ZetaSkim_ee_v1_5.root");

  Dat_ZmmA = TFile::Open("files/zdiff/3_4/Run2010A_mm_v1_5.root");
  cout<<"Loading  Dat_ZmmB"<< endl;
  Dat_ZmmB = TFile::Open("files/zdiff/3_4/Run2010B_mm_v1.root");

  cout<<"Loading  Dat_ZeeA"<< endl;
  Dat_ZeeA = TFile::Open("files/zdiff/3_4/Run2010A_ee_v1_4.root");
  cout<<"Loading  Dat_ZeeB"<< endl;
  Dat_ZeeB = TFile::Open("files/zdiff/3_4/Run2010B_ee_v1_4.root");

  cout<<"Loading  Z2PY610_Zmm"<< endl;
  Z2PY610_Zmm = TFile::Open("files/zdiff/3_4/pythiaZ2_mm_v1_3.root");

  cout<<"Loading  POMPYT10_Zmm"<< endl;
  POMPYT10_Zmm = TFile::Open("files/zdiff/3_4/DiffractiveMC_mm_v1_4.root");



  return;   

}



void NCZload_4_2(){
  
  //  cout<<"Loading  Dat10A_Zee"<< endl;
  // Dat10A_Zee = TFile::Open("files/zdiff/4_2/EGrunAZee_v2_2.root");
  //  DATA10_Zee = TFile::Open("files/zdiff/4_2/EGZee_v2_2.root");
  cout<<"Loading  DATA10_Zee"<< endl;
  DATA10_Zee = TFile::Open("files/zdiff/4_2/Data_Zee_2010_v2_6.root");

  cout<<"Loading  DATA11_Zee"<< endl;
  DATA11_Zee = TFile::Open("files/zdiff/4_2/Data_Zee_2011_v2_6.root");

  cout<<"Loading  DATA1011_Zee"<< endl;
  DATA1011_Zee = TFile::Open("files/zdiff/4_2/Data_Zee_2010_2011_NVTXLT3_v2_4.root");


  cout<<"Loading  Z2PY6_Zee"<< endl;
  Z2PY6_Zee = TFile::Open("files/zdiff/4_2/MC_Zee_Z2PY6_v2_6.root");

  cout<<"Loading  C4PY8_Zee"<< endl;
  C4PY8_Zee = TFile::Open("files/zdiff/4_2/MC_Zee_4CPY8_v2_4.root");

  cout<<"Loading POMPYT_Zee"<< endl;
  POMPYT_Zee = TFile::Open("files/zdiff/4_2/MC_Zee_POMPYT_v2_6.root");


  return;   

}
