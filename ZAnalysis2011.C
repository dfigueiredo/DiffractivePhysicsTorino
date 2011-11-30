#include <iostream>
#include <sstream>
#include "tdrstyle.C"
#include "NCutil.C"

TH1F * ratio_;
TH1F * data_;
TH1F * pythia_;

void EHF(){

  TCanvas *pippo = NCanvas(2,2);

  Int_t nbin = 50;
  TCut cutRw = "numberOfVertexes==1";


  gDirectory->Delete("Hratio");   
  ratio_ = new TH1F("Hratio","Tratio L", nbin, 0., 1000.);
   
  cout << ratio_ << endl ;


  pippo->cd(1); 
 
  NPYTZ2_Zee->cd("Selection");
  gDirectory->Delete("Hpythia");
  pythia_ = new TH1F("Hpythia","Tpythia L", nbin, 0., 1000.);
  tree_->Draw("TMath::Min(sumEHF_minus,sumEHF_plus)>>Hpythia",cutRw);
  NDat_ZeeA->cd("Selection");
  pippo->cd(2);
  gDirectory->Delete("Hdata");
  data_ = new TH1F("Hdata","Tdata L", nbin, 0., 1000.); 
  tree_->Draw("TMath::Min(sumEHF_minus,sumEHF_plus)>>Hdata",cutRw);

  pippo->cd(3);
  ratio_->Sumw2();
  ratio_->Divide(Hpythia,Hdata);
  ratio_->Draw();
  
}
