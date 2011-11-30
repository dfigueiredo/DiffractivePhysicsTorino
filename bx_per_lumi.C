{
  gDirectory->Delete("Istlumi"); 
  TH2F *Istlumi = new TH2F("Istlumi", "Istlumi; Run Number; Lumi per BX [10^{30}]", 200, 138000.,150000., 100, 0.,.7);
  Istlumi->SetStats(kFALSE);

  //  Istlumi->fill(istlumiPerBX*6.37,RunNumber);
  // Istlumi->GetXaxis()->SetTitle("Pippo"); 

  Istlumi->SetTitle("Instantaneous Luminosity per bx vs Run Number");
  Istlumi->Draw();


  DZeeA->cd();
  Istlumi->SetMarkerColor(2);

  tree_->Draw("(istlumiPerBX*6.37):RunNumber>>Istlumi","istlumiPerBX*6.37>0","SAMES");

  DZeeB->cd();
  Istlumi->SetMarkerColor(2);
  tree_->Draw("(istlumiPerBX*6.37):RunNumber>>Istlumi", "istlumiPerBX*6.37>0", "SAMES");

  NArrow(139000,0.4,144200.,0.4, 0.01,"<|>");
  NText(140000,0.45,"Run A");

  //  NArrow(139000,0.4,144200.,0.4, 0.01,"<|>");
  // NText(140000,0.45,"Run A");




}
