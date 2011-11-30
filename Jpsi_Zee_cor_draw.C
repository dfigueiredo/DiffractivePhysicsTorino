{
NCanvas(1,2);
 MyC->cd(1);
 Z_all_ratio->SetMarkerColor(2);
 Z_all_ratio->SetLineColor(2);
 Z_HF0_ratio->SetMarkerColor(4);
 Z_HF0_ratio->SetLineColor(4);
 Z_all_ratio_Draw();
 Z_HF0_ratio_Draw("SAME");

 MyC->cd(2);
 JPsi_all_ratio->SetMarkerColor(2);
 JPsi_all_ratio->SetLineColor(2);
 Jpsi_HF0_ratio->SetMarkerColor(4);
 Jpsi_HF0_ratio->SetLineColor(4);
 JPsi_all_ratio_Draw();
 JPsi_HF0_ratio_Draw("SAME");
}
