{
//=========Macro generated from canvas: MyC/Test canvas
//=========  (Tue Jan 11 21:03:03 2011) by ROOT version5.18/00
   TCanvas *MyC = new TCanvas("MyC", "Test canvas",50,34,699,501);
   MyC->Range(-0.1,-13.251,0.9,119.259);
   MyC->SetBorderSize(2);
   MyC->SetFrameFillColor(0);
   
   TProfile *EE_all_pfx = new TProfile("EE_all_pfx","(Endcap Energy) vs (Inst. Lumi per bx)",8,0,0.8,"");
   EE_all_pfx->SetBinEntries(1,177);
   EE_all_pfx->SetBinEntries(2,647);
   EE_all_pfx->SetBinEntries(3,3010);
   EE_all_pfx->SetBinEntries(4,3136);
   EE_all_pfx->SetBinEntries(5,2500);
   EE_all_pfx->SetBinEntries(6,1084);
   EE_all_pfx->SetBinEntries(7,34);
   EE_all_pfx->SetBinContent(1,13690);
   EE_all_pfx->SetBinContent(2,36294);
   EE_all_pfx->SetBinContent(3,191896);
   EE_all_pfx->SetBinContent(4,227308);
   EE_all_pfx->SetBinContent(5,200476);
   EE_all_pfx->SetBinContent(6,92924);
   EE_all_pfx->SetBinContent(7,3156);
   EE_all_pfx->SetBinError(1,1294.754);
   EE_all_pfx->SetBinError(2,1837.171);
   EE_all_pfx->SetBinError(3,4502.562);
   EE_all_pfx->SetBinError(4,5157.677);
   EE_all_pfx->SetBinError(5,5070.97);
   EE_all_pfx->SetBinError(6,3479.722);
   EE_all_pfx->SetBinError(7,607.8487);
   EE_all_pfx->SetEntries(10636);
   EE_all_pfx->SetStats(0);
   EE_all_pfx->SetLineColor(2);
   EE_all_pfx->SetMarkerColor(2);
   EE_all_pfx->SetMarkerStyle(20);
   EE_all_pfx->GetXaxis()->SetTitle(" Inst.  Lumi per BX [10^{30} cm^{-2} s^{-1}]");
   EE_all_pfx->GetYaxis()->SetTitle("Endcap Energy [GeV]");
   EE_all_pfx->GetYaxis()->SetTitleOffset(0.9);
   EE_all_pfx->Draw("");
   
   TPaveText *pt = new TPaveText(0.01,0.9408647,0.6131933,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   TText *text = pt->AddText("(Endcap Energy) vs (Inst. Lumi per bx)");
   pt->Draw();
   MyC->Modified();
   MyC->cd();
   MyC->SetSelected(MyC);
}
