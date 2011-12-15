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
TFile *DatA10_Zee;
TFile *Dat10_Zee;
TFile *PYTZ2_Zee;
TFile *POMPYT_Zee;

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
  
  cout<<"Loading  Dat10A_Zee"<< endl;
  Dat10A_Zee = TFile::Open("files/zdiff/4_2/EGrunAZee_v2_2.root");
  cout<<"Loading  Dat10_Zee"<< endl;
  Dat10_Zee = TFile::Open("files/zdiff/4_2/EGZee_v2_2.root");

  cout<<"Loading  PYTZ2_Zee"<< endl;
  PYTZ2_Zee = TFile::Open("files/zdiff/4_2/PythiaZ2Zee_v2_2.root");

  cout<<"Loading POMPYT_Zee"<< endl;
  POMPYT_Zee = TFile::Open("files/zdiff/4_2/PompytZee_v2_2.root");


  return;   

}
