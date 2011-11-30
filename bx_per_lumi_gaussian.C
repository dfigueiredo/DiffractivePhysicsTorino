#include <iostream>
#include <sstream>

void lumi_gaussian(){

   gDirectory->Delete("IstgA"); 
   gDirectory->Delete("IstgB"); 
  TH1F *IstgA = new TH1F("IstgA", "Instantaneous Luminosity per bx; Lumi per BX [10^{30}]; Entries", 20, 0.,.7);
  TH1F *IstgB = new TH1F("IstgB", "Instantaneous Luminosity per bx; Lumi per BX [10^{30}]; Entries", 20, 0.,.7);
 
  //  Istg->SetMaximum(1500);
  // Istg->Draw();
  NCanvas(1,1);
  MyC->cd(1);
  // return();
  DZeeB->cd();
  //  Istlumi->SetMarkerColor(4);
  IstgB->SetLineColor(kBlue);

  tree_->Draw("(istlumiPerBX*6.37)>>IstgB", "istlumiPerBX*6.37>0.");

  IstgA->SetLineColor(kRed);
  IstgA->SetFillStyle(3004);
  IstgA->SetFillColor(kRed);
  //  MyC->cd(2);
  DZeeA->cd();
  //  Istlumi->SetMarkerColor(2);
  tree_->Draw("(istlumiPerBX*6.37)>>IstgA","istlumiPerBX*6.37>0.","SAMES");

  //  IstgB->Draw();
  NArrow(0.1,800.,0.15,200.,0.02,">");
  NText(0.01,800, "Run A = <0.21 10^{-30}>");



}
