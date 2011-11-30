{
 
  //    TracksGenEta_All->Draw();
  NHSetMarker(TracksGenEta,2,24,0.3);
    TracksGenEta->Draw();

     
    NHSetMarker(TracksGen_NDOFGT2,4,24,0.3);
    TracksGen_NDOFGT2->Draw("SAME");

    NHSetMarker(TracksGen_NDOFGT1,6,24,0.3);
     TracksGen_NDOFGT1->Draw("SAME");

    NLogAxis(0,1);    

  TLegend *leg = new TLegend(0.4,0.6, 0.6 ,0.8);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(TracksGen_NDOFGT1,"TracksGen_NDOFGT1","pL");  
  leg->AddEntry(TracksGen_NDOFGT2,"TracksGen_NDOFGT2","pL");  
  leg->AddEntry(TracksGenEta,"TracksGenEta","p");  

  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);  
  leg->Draw();


}
