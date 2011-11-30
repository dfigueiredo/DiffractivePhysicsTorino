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
TFile *Dat10_ZeeA;
TFile *Dat10_ZeeB;
TFile *PYTZ2_Zee;

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


  return;   

}



void NCZload_4_2(){
  
  cout<<"Loading  Dat10_ZeeA"<< endl;
  Dat10_ZeeA = TFile::Open("files/zdiff/4_2/EGrunA_v2_1.root");
  cout<<"Loading  Dat10_ZeeB"<< endl;
  Dat10_ZeeB = TFile::Open("files/zdiff/4_2/EGrunB_v2_1.root");


  cout<<"Loading  PYTZ2_Zee"<< endl;
  PYTZ2_Zee = TFile::Open("files/zdiff/4_2/PythiaZ2_v2_1.root");


  return;   

}
