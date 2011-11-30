{
  // TFile *_file1 = TFile::Open("files/MBPythia8_v1_16_CHA.root")  ;
  TCanvas *pippo = NCanvas(1,2,"pippo");
  pippo->cd(1);

  tree_->Draw("V_y[1]","vertexNDOF[1]>0");
  tree_->Draw("V_y[1]","vertexNDOF[1]>1","SAME");
  NLogAxis(0,1);
  pippo->cd(2);
  tree_->Draw("V_x[1]","vertexNDOF[1]>0");
  tree_->Draw("V_x[1]","vertexNDOF[1]>1","SAME");
  NLogAxis(0,1);

}
