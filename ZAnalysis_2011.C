#include <TH2.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "string.h"
#include <sstream>
#include <iomanip>
#include <TRandom.h>
#include "NCutil.C"
#include <iostream>
#include <fstream>
#include <TMath.h> 
#include <TProfile.h> 

void FindZ2Weight(){
  TH1F * Pyt;
  TH1F * Dat;

  TFile *fzee = new TFile("ZDiffOutputfile.root");
  Pyt  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_PythiaZ2");
  Dat  =  (TH1F*)fzee->Get("NoCuts_GoodVtx_DataAB");

  Float_t scale = NoCuts_GoodVtx_PythiaZ2->Integral()/NoCuts_GoodVtx_DataAB->Integral();
  cout << "Scaling factor to conserve MC luminosity = " << scale << endl;
  Dat->Divide(Pyt);
  Dat->Scale(scale);
  Dat->Draw();
  cout << "Float_t Z2Weight[] = {" ;
  for (Int_t j = 1;j<=20; j++)   cout <<  Dat->GetBinContent(j) << ", " ;
  cout << " 0 } " << endl;
}
