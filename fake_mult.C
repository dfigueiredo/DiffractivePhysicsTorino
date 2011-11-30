TH1F *VertexD ;
TH1F *VertexTotD;
TH1F *VertexCW ;
TH1F *VertexTotCW;
TH1F *VertexZ;
TH1F *VertexTotZ;
void Fake_mult(){

  gDirectory->Delete("vertexD");
  gDirectory->Delete("vertexTotD");
  gDirectory->Delete("vertexCW");
  gDirectory->Delete("vertexTotCW");
  gDirectory->Delete("vertexZ");
  gDirectory->Delete("vertexTotZ");

  VertexD = new TH1F("VertexD", "VertexD", 15, -0.5,14.5);
  VertexTotD = new TH1F("VertexTotD", "VertexTotD", 15, -0.5,200.5);
  VertexCW = new TH1F("VertexCW", "VertexCW", 15, -0.5,14.5);
  VertexTotCW = new TH1F("VertexTotCW", "VertexTotCW", 15, -0.5,200.5);
  VertexZ = new TH1F("VertexZ", "VertexZ", 15, -0.5,14.5);
  VertexTotZ = new TH1F("VertexTotZ", "VertexTotZ", 15, -0.5,200.5);

  //  VertexZ2->SetLineColor(2);
  MBPythiaZ2_STD->cd();
  tree_->Draw("vertexMolteplicity[1]>>VertexZ");
  tree_->Draw("vertexMolteplicity[0]>>VertexTotZ");
  Float_t scale = 0.01*VertexTotZ->GetEntries();
  // Float_t scale = 0.01*2088000;
  cout << "Scale = "<< scale<< endl;

  if (scale>0)
    {
      VertexZ->Scale(1./scale);
      VertexZ->SetMaximum(5.);
    }
  VertexD->SetLineColor(4);

  MBPythiaD6T_STD->cd();
  tree_->Draw("vertexMolteplicity[1]>>VertexD");
  tree_->Draw("vertexMolteplicity[0]>>VertexTotD");
  Float_t scale = 0.01*VertexTotD->GetEntries();
  // Float_t scale = 0.01*3276600;
  cout << "Scale = "<< scale<< endl;
  if (scale>0)
    {
      VertexD->Scale(1./scale);
      
      VertexD->Draw("SAME");
    }
  VertexCW->SetLineColor(6);
  MBPythiaCW_DAV->cd();
  tree_->Draw("vertexMolteplicity[1]>>VertexCW");
  tree_->Draw("vertexMolteplicity[0]>>VertexTotCW");
  Float_t scale = 0.01*VertexTotCW->GetEntries();
  cout << "Scale = "<< scale<< endl;
  if (scale>0)
    {
      VertexCW->Scale(1./scale);
      

    }

  VertexZ->Draw();
  VertexD->Draw("SAME");
  VertexCW->Draw("SAME");

  // NArrow(3.,800.,2,430.,0.02,">");
  // NText(2.5,850, "1 Pileup event");
  // NArrow(6.,800.,3,230.,0.02,">");

  NText(0,4., " Track multiplicity for secondary vertices",1,0.05);
  NText(4.,4.5, "CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}",1,0.06);
  

  return();  
}

