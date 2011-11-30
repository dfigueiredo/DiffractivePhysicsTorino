
#include <iostream>
#include <sstream>

const Int_t hnbin = 30;  /* number of bins */

Float_t *Pczmm = new Float_t [hnbin];
Float_t *Pezmm = new Float_t [hnbin];

void calc_norm()
{

  Dat_Zmm->cd();
  TH1F *Zmass = new TH1F("Zmass","Zmass", hnbin,60.,120.);
  tree_->Draw("InvariantMass>>Zmass");
  Double_t scale = 1./Zmass->Integral();
  Zmass->Scale(scale);
  Zmass->Draw();
  NHtoV(Zmass, Pczmm, Pezmm);
  for (int i = 0; i<hnbin;i++){
    cout<< ","<<Pczmm[i];
  }
  cout << endl;
  return;
}
