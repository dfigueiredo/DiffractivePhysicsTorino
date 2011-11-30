{
  TF1 HF("HF","0.008325/(0.008325-0.01899*x+0.01151*x*x)",0.,0.6); 
  HF.SetMaximum(15);
  HF.SetLineColor(2);
  HF.Draw();
  HF.GetXaxis()->SetTitle("Luminosity per bx [10^{30} cm^{-2}s^{-1}]");
  HF.GetYaxis()->SetTitle("Correction");
  HF.GetYaxis()->SetTitleOffset(1.3);
  HF.SetTitle("Gap Correction Function");
  NText(0.1,12,"Castor+HF=0",6);
  NText(0.4,2,"HF=0",2);
  NText(0.45,6,"Eta<2.85",4);

  TF1 Eta("Eta","0.003738/(0.003738-0.008972*x+0.005977*x*x)",0.,0.6); 
  Eta.SetLineStyle(2);
  Eta.SetLineColor(4);
  Eta.Draw("SAME");

  TF1 Castor("Castor","0.001922/(0.001922-0.01115*x+0.01678*x*x)",0.,0.35); 
  Castor.SetLineStyle(4);
  Castor.SetLineColor(6);
  Castor.Draw("SAME");

  }
