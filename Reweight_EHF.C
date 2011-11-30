
#include <iostream>
#include <sstream>
#include "NCutil.C"

void Reweight_EHF(){

  TCut cutRw = "numberOfVertexes==1";
  gDirectory->Delete("pythia");
  gDirectory->Delete("data");
  gDirectory->Delete("ratio");
  
  TH1F *pythia = new TH1F("pythia","pythia", 10, 0., 1000.);
  ratio=NH1clone("ratio","ratio",pythia); 
  data=NH1clone("data","data",pythia) ;
  
  Pyt_Zee->cd();
  tree_->Draw("TMath::Min(sumEHF_minus,sumEHF_plus)>>pythia");
  Dat_Zee->cd();
  tree_->Draw("TMath::Min(sumEHF_minus,sumEHF_plus)>>data");
  ratio->Sumw2();
  ratio->Divide(pythia,data);
  
}
