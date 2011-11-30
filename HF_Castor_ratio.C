{
  RunNumb_HF_ratio->SetMarkerColor(4);
    RunNumb_HF_ratio->SetStats(kFALSE);
    RunNumb_HF_ratio->SetLineColor(4);
    RunNumb_HF_ratio->Draw();
    RunNumb_Castor_ratio->SetMarkerColor(2);
    RunNumb_Castor_ratio->SetLineColor(2);
    RunNumb_Castor_ratio->Draw("SAME");
    TLegend *leg1 = new TLegend(0.2,0.7, .4 ,0.85);
    leg1->AddEntry(RunNumb_HF_ratio,"E_{HF}< 4 GeV","p");
    leg1->AddEntry(RunNumb_Castor_ratio,"E_{Castor}=0","p"); 
    leg1->Draw();
    RunNumb_HF_ratio->GetXaxis()->SetTitle("Run Number");
    RunNumb_HF_ratio->GetYaxis()->SetTitle("Fraction of events");
    RunNumb_HF_ratio->GetYaxis()->SetTitleOffset(1.3);
    RunNumb_HF_ratio->SetTitle();
}
