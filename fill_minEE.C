#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <istream>


TH1F *Hpompyt;
TH1F *Hpythia;
TH1F *Hdata;


void fill_minEE(){

  gDirectory->Delete("Hpompyt");
  gDirectory->Delete("Hdata");
  gDirectory->Delete("Hpythia");
  Hpompyt = new TH1F("Hpompyt", "pompyt", 100, 0., 400.);
  Hpythia = new TH1F("Hpythia", "pythia", 100, 0., 400.);
  Hdata = new TH1F("Hdata", "data", 100, 0., 400.);
  Int_t nbin = Hpythia->GetNbinsX();

  NCanvas(2,2);
  Pompyt->cd();

  MyC->cd(1);
  tree_->Draw("TMath::Min(energyTot_PF_EE_minus,energyTot_PF_EE_plus)>>Hpompyt");
  Float_t *Pcpompyt; 
  Pcpompyt = new  Float_t [nbin];
  Float_t *Pepompyt; 
  Pepompyt = new Float_t [nbin];
  Pompyt->cd();
  NHtoV(Hpompyt, Pcpompyt, Pepompyt);
  cout << " the content of pompyt[2] is = " << Pcpompyt[2] << "+-"<<Pepompyt[2] << endl ;


  Zee->cd();
  MyC->cd(2);
  tree_->Draw("TMath::Min(energyTot_PF_EE_minus,energyTot_PF_EE_plus)>>Hdata");

  Float_t *Pcdata; 
  Pcdata = new  Float_t [nbin];
  Float_t *Pedata; 
  Pedata = new Float_t [nbin];
  NHtoV(Hdata, Pcdata, Pedata);
  cout << " the content of data[2] is = " << Pcdata[2] << "+-"<<Pedata[2] << endl ;


  Pythia->cd();
  MyC->cd(3);

  tree_->Draw("TMath::Min(energyTot_PF_EE_minus,energyTot_PF_EE_plus)>>Hpythia");

  Float_t *Pcpythia; 
  Pcpythia = new  Float_t [nbin];
  Float_t *Pepythia; 
  Pepythia = new Float_t [nbin];
  NHtoV(Hpythia, Pcpythia, Pepythia);





  cout << " the content of pythia[2] is = " << Pcpythia[2] << "+-"<<Pepythia[2] << endl ;

  
  return;

}


void  NHtoV(TH1F* file_in, Float_t* content, Float_t* econtent){


  // cout << "number of bins= " << nbin << endl;
  // Double_t content[nbin];
  Int_t nbin = Hpythia->GetNbinsX();
  for (int i=0;i< nbin;i++){
    *(content+i) = file_in->GetBinContent(i);
    *(econtent+i) = file_in->GetBinError(i);
    //     cout << content[i] << " " << i << endl;
    // cout << econtent[i] << " " << i << endl;
  };
  return;
}
