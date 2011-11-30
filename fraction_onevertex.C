#include <iostream>
#include <sstream>

void fraction_vertex(Int_t vtx)
{


  stringstream stringa;
  stringstream stringam1;
  
  stringa<<vtx;
  Int_t nevt = vtx-1;
  stringam1<<nevt;

  string cut = "istlumiPerBX*6.37>0.05 && numberOfVertexes=="+stringa.str();
  string title = "Instantaneous lumi per bx for events with "+stringa.str()+" vxt";
  string name = "vxt"+stringa.str();
  string fill = "istlumiPerBX*6.37>>"+name;
  string rat1_title = "Fraction of events with "+stringa.str()+ " vertexes";  
  string prob_title = "Probability of " +stringam1.str()+ " pile-up events (\sigma_{NSD} = 60 mb) ";  
  string probstr = "prob(x," +stringam1.str()+ ")";

  gDirectory->Delete("istlumi"); 
  gDirectory->Delete(name.c_str());
  gDirectory->Delete("namec");
  gDirectory->Delete("rat1");
  gDirectory->Delete("prob");

  TH1F *istlumi = new TH1F("istlumi", "Instantaneous lumi per bx", 7, 0., 0.7);
  TH1F *namec =  (TH1F*) istlumi->Clone(); namec->SetTitle(title.c_str()); namec->SetName(name.c_str());


  tree_->Draw("istlumiPerBX*6.37>>istlumi","","goff");
  tree_->Draw(fill.c_str(), cut.c_str(), "goff");
 
  TH1F *rat1 =  (TH1F*) istlumi->Clone(); rat1->SetTitle(""); rat1->SetName("rat1");
  rat1->Sumw2();
  rat1->Divide(namec,istlumi,1.,1.,"B");  

   rat1->SetMarkerStyle(20);

  TH1F *prob = (TH1F*) istlumi->Clone(); prob->SetTitle("");  prob->SetName("prob"); prob->Reset();
  

  prob->GetXaxis()->SetTitle("Luminosity per crossing 10^{-30} cm^{-2}s^{-1}");
  prob->GetYaxis()->SetTitle("Fraction");
  

  Float_t LumiLoop;
  
  for (LumiLoop = 0.05; LumiLoop<=0.66;  LumiLoop += 0.1)
    {
      //      cout << LumiLoop << prob(LumiLoop, nevt) << endl;
      prob->Fill(LumiLoop, prob(LumiLoop, nevt));

    }
  TF1 *HF2 = new TF1("HF2",probstr.c_str(),0.,0.75);
  prob->SetMarkerStyle(22);
  prob->SetMarkerColor(2);
  HF2->SetLineColor(2);
  HF2->SetLineStyle(2);
  HF2->SetTitle();
  HF2->Draw();  
  HF2->SetMaximum(0.65);
  // prob->Draw("SAME p");
  rat1->SetStats(kFALSE);
  rat1->Draw(" SAMES p");

  
  TLegend *leg = new TLegend(0.3,0.85,.7,1.);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(rat1,rat1_title.c_str(),"p");  
  leg->AddEntry(HF2,prob_title.c_str(),"LF");
  leg->Draw();

  return();

}

