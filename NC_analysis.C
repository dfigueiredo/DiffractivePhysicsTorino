#include <iostream>
#include <sstream>
#include "tdrstyle.C"
#include "NCutil.C"

void fraction_vertex(Int_t vtx)
{

  stringstream stringa;
  stringstream stringam1;
  stringa<<vtx;
  Int_t nevt = vtx-1;
  stringam1<<nevt;

  string cut_b = "istlumiPerBX*6.37>0.1 && RunNumber>140000  ";
  string cut = cut_b+" && numberOfVertexesInEvent=="+stringa.str();
  string title = "Instantaneous lumi per bx for events with "+stringa.str()+" vxt";
  string name = "vxt"+stringa.str();
  string fill = "istlumiPerBX*6.37>>"+name;
  string rat1_title = "Fraction of events with "+stringa.str()+ " vertexes";  
  string prob_title = "Probability of " +stringam1.str()+ " pile-up events (\sigma_{NSD} = 60 mb) ";  

  gDirectory->Delete("istlumi"); 
  gDirectory->Delete(name.c_str());
  gDirectory->Delete("namec");
  gDirectory->Delete("rat1");
  gDirectory->Delete("prob");

  TH1F *istlumi = new TH1F("istlumi", "Instantaneous lumi per bx", 16, 0.1, 0.9);
  TH1F *namec =  (TH1F*) istlumi->Clone(); namec->SetTitle(title.c_str()); namec->SetName(name.c_str());


  data.Draw("istlumiPerBX*6.37>>istlumi",cut_b.c_str(),"goff");
  data.Draw(fill.c_str(), cut.c_str(), "goff");
 
  TH1F *rat1 =  (TH1F*) istlumi->Clone(); rat1->SetTitle(""); rat1->SetName("rat1");
  rat1->Sumw2();
  rat1->Divide(namec,istlumi,1.,1.,"B");  

   rat1->SetMarkerStyle(20);

  TH1F *prob = (TH1F*) istlumi->Clone(); prob->SetTitle("");  prob->SetName("prob"); prob->Reset();
  

  prob->GetXaxis()->SetTitle("Ist. Lumi per bx 10^{-30} cm^{-2}s^{-1}");
  prob->GetYaxis()->SetTitle("Fraction");
  

  Float_t LumiLoop;
  
  for (LumiLoop = 0.025; LumiLoop<=0.9;  LumiLoop += 0.05)
    {
      //      cout << LumiLoop << prob(LumiLoop, nevt) << endl;
      prob->Fill(LumiLoop, prob(LumiLoop, nevt));

    }

  prob->SetMarkerStyle(22);
  prob->SetMarkerColor(2);
  prob->SetStats(kFALSE);
  rat1->SetStats(kFALSE);
  prob->SetMaximum(0.65);
  //  gPad->SetLogy(0);
  prob->Draw("p");
  rat1->Draw(" SAMES p");

  
  TLegend *leg = new TLegend(0.37,0.7, 0.7 ,0.85);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(rat1,rat1_title.c_str(),"p");  
  leg->AddEntry(prob,prob_title.c_str(),"p");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);  
  leg->Draw();

  return();

}

void bxlumi_vs_RunNumber(){
 gDirectory->Delete("Istlumi"); 
  TH2F *Istlumi = new TH2F("Istlumi", "Istlumi; Run Number; Lumi per BX 10^{30} [cm^{-2} s^{-1}]", 200, 138000.,150000., 100, 0.,.7);
  Istlumi->SetStats(kFALSE);

  //  Istlumi->fill(istlumiPerBX*6.37,RunNumber);
  // Istlumi->GetXaxis()->SetTitle("Pippo"); 

  Istlumi->SetTitle("Instantaneous Luminosity per bx vs Run Number");
  Istlumi->Draw();
  DZeeA->cd();
  Istlumi->SetMarkerColor(2);
  tree_->Draw("(istlumiPerBX*6.37):RunNumber>>Istlumi","istlumiPerBX*6.37>0","SAMES");

  DZeeB->cd();
  Istlumi->SetMarkerColor(4);
  tree_->Draw("(istlumiPerBX*6.37):RunNumber>>Istlumi", "istlumiPerBX*6.37>0", "SAMES");

  NArrow(139000,0.4,144200.,0.4, 0.01,"<|>");
  NText(140000,0.45,"Run 2010A");

  //  NArrow(139000,0.4,144200.,0.4, 0.01,"<|>");
  // NText(140000,0.45,"Run A");

}

void bxlumi_gaussian(){


  DZeeB->cd();
  gDirectory->Delete("IstgB"); 

  TH1F *IstgB = new TH1F("IstgB", "Instantaneous Luminosity per bx; Lumi per BX [10^{30} cm^{-2} s^{-1}]; Entries", 20, 0.,.7);
  IstgB->SetStats(kFALSE);  
  IstgB->SetLineColor(kBlue);
  tree_->Draw("(istlumiPerBX*6.37)>>IstgB", "istlumiPerBX*6.37>0.");


  DZeeA->cd();
  gDirectory->Delete("IstgA"); 
  TH1F *IstgA = new TH1F("IstgA", "Instantaneous Luminosity per bx; Lumi per BX [10^{30} cm^{-2} s^{-1}]; Entries", 20, 0.,.7);
  IstgA->SetStats(kFALSE);
  IstgA->SetLineColor(kRed);
  IstgA->SetFillStyle(3004);
  IstgA->SetFillColor(kRed);
  tree_->Draw("(istlumiPerBX*6.37)>>IstgA","istlumiPerBX*6.37>0.","SAMES");


  NArrow(0.1,800.,0.15,200.,0.02,">");
  NText(0.01,800, "Run A = <0.21 10^{30}> [cm^{-2} s^{-1}]");
  
  NArrow(0.55,1000., 0.5,800.,0.02,">");
  NText(0.45,1050, "Run B = <0.36 10^{30}> [cm^{-2} s^{-1}]");

 
  /* THStack hs("hs","test stacked histograms");
      DZeeA->cd();
      hs.Add(IstgA);
      DZeeB->cd();
      hs.Add(IstgB);
      hs.Draw(); 
      */
  return();  
}

void n_vertexes(){

  Dat_DAV_mmB1->cd();
  gDirectory->Delete("TVertexB"); 
  TH1F *VertexB = new TH1F("TVertexB", "Number of vertexes; Number of vertexes; Entries", 16, -0.5,15.5);
  VertexB->SetStats(kFALSE);
  VertexB->GetYaxis()->SetTitleOffset(1.2);

  VertexB->SetLineColor(kBlue);
  tree_->Draw("numberOfVertexes>>TVertexB", "istlumiPerBX*6.37>0.");


  /*  Dat_DAV_mmA->cd();
  gDirectory->Delete("TVertexA"); 
  TH1F *VertexA = new TH1F("TVertexA", "Number of vertexes; Number of vertexes; Entries", 16, -0.5,15.5);
  VertexA->SetStats(kFALSE);
  VertexA->SetLineColor(kRed);
  VertexA->SetFillStyle(3004);
  VertexA->SetFillColor(kRed);
  
  tree_->Draw("numberOfVertexes>>TVertexA", "istlumiPerBX*6.37>0.","SAMES");
  */

  // NArrow(3.,800.,2,430.,0.02,">");
  // NText(2.5,850, "1 Pileup event");
  // NArrow(6.,800.,3,230.,0.02,">");
  NText(1,200, "# of vertexes-1 =  Pileup events");
  // NText(.75,150, "Run2010A");
  NText(4.,200000, "CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}",1,0.06);

  NLogAxis(0,1);
  //NArrow(0.55,1000., 0.5,800.,0.02,">");
  // NText(0.45,1050, "Run B = <0.36 10^{-30}>");

  /*  
      THStack hs("hs","test stacked histograms");
      hs.Add(IstgA);
      hs.Add(IstgB);
      hs.Draw(); 
  */
  return();  
}



void Mult_NDOF(){

  Dat_DAV_mmB1->cd();

  gDirectory->Delete("TVertexC"); 
  TH1F *VertexC = new TH1F("TVertexC", "Vertex NDOF for vertices with 2,3 and 4 tracks; Vertex NDOF; Entries", 100, 0.,5.);
  VertexC->SetStats(kFALSE);
  VertexC->GetYaxis()->SetTitleOffset(1.2);
  VertexC->SetLineStyle(3);
  VertexC->SetLineColor(6);
  tree_->Draw("vertexNDOF[1]>>TVertexC", "istlumiPerBX*6.37>0.&& vertexMolteplicity[1]==2");



  gDirectory->Delete("TVertexB"); 
  TH1F *VertexB = new TH1F("TVertexB", "Vertex NDOF for vertices with 2,3 and 4 tracks; Vertex NDOF; Entries", 100, 0.,5.);
  VertexB->SetStats(kFALSE);
  VertexB->GetYaxis()->SetTitleOffset(1.2);
  VertexB->SetLineColor(2);
  tree_->Draw("vertexNDOF[1]>>TVertexB", "istlumiPerBX*6.37>0.&& vertexMolteplicity[1]==3", "SAME");

  gDirectory->Delete("TVertexA"); 
  TH1F *VertexA = new TH1F("TVertexA", "Track Multiplicity; Track Multiplicity; Entries", 100, 0.,5); 
  VertexB->SetLineStyle(2);
  VertexB->SetLineColor(4);
  tree_->Draw("vertexNDOF[1]>>TVertexA", "istlumiPerBX*6.37>0.&& vertexMolteplicity[1]==4","SAME");

  TLegend *leg = new TLegend(0.4,0.7, 0.7 ,0.85);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(TVertexA,"4-track Vertex" ,"L");  
  leg->AddEntry(TVertexB,"3-track Vertex" ,"L");  
  leg->AddEntry(TVertexC,"2-track Vertex","L");  

  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);  
  leg->Draw();



  // NArrow(3.,800.,2,430.,0.02,">");
  // NText(2.5,850, "1 Pileup event");
  // NArrow(6.,800.,3,230.,0.02,">");
  
  //NArrow(0.55,1000., 0.5,800.,0.02,">");
  // NText(0.45,1050, "Run B = <0.36 10^{-30}>");

  /*  
      THStack hs("hs","test stacked histograms");
      hs.Add(IstgA);
      hs.Add(IstgB);
      hs.Draw(); 
  */
  return();  
}


TH1F *VertexD ;
TH1F *VertexTotD;
TH1F *VertexCW ;
TH1F *VertexTotCW;
TH1F *VertexP8;
TH1F *VertexTotP8;

void Fake_mult(){
  // NCZload_MB()
  // .L NCZload.C   
  gDirectory->Delete("vertexD");
  gDirectory->Delete("vertexTotD");
  gDirectory->Delete("vertexCW");
  gDirectory->Delete("vertexTotCW");
  gDirectory->Delete("vertexP8");
  gDirectory->Delete("vertexTotP8");

  VertexD = new TH1F("VertexD", "VertexD", 15, -0.5,14.5);
  VertexTotD = new TH1F("VertexTotD", "VertexTotD", 15, -0.5,14.5);
  VertexCW = new TH1F("VertexCW", "VertexCW", 15, -0.5,14.5);
  VertexTotCW = new TH1F("VertexTotCW", "VertexTotCW", 15, -0.5,14.5);
  VertexP8 = new TH1F("VertexP8", "VertexP8", 15, -0.5,14.5);
  VertexTotP8 = new TH1F("VertexTotP8", "VertexTotP8", 15, -0.5,14.5);


  MBPythia8_DAV->cd();
  tree_->Draw("vertexMolteplicity[1]>>VertexP8","vertexNDOF[1]>0.5 && fabs(sqrt(pow(V_x[1],2)+ pow(V_y[1],2))-0.463)<0.06");
  tree_->Draw("vertexMolteplicity[1]>>VertexCW","vertexNDOF[1]>0.5");
  tree_->Draw("vertexMolteplicity[0]>>VertexTotP8", "vertexNDOF[0]>0.5 && fabs(sqrt(pow(V_x[0],2)+ pow(V_y[0],2))-0.463)<0.06");

  // Float_t scale = 0.01*3276600;

  VertexD->Add(VertexP8);
  VertexD->Divide(VertexTotP8);
  VertexTotD->Add(VertexCW);
  VertexTotD->Divide(VertexTotP8);


  VertexTotD->SetLineStyle(2);
  VertexTotD->Draw();
  VertexD->Draw("SAME");
  VertexTotD->GetXaxis()->SetTitle("Vertex Track Multiplicity");
  VertexTotD->GetYaxis()->SetTitle("Fraction of Secondary Vertices");


  //  NText(0,4., " Track multiplicity for secondary vertices",1,0.05);

  NText(0.,0., "CMS Simulation",1,0.06);
  
  TLegend *leg = new TLegend(0.6,0.6, 0.8 ,0.8);
  leg->AddEntry(VertexTotD,"Without Transverse Position Cut","L");  
  leg->AddEntry(VertexD,"With Transverse Position Cut","L");

  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);  
  leg->Draw();

  //NArrow(0.55,1000., 0.5,800.,0.02,">");
  // NText(0.45,1050, "Run B = <0.36 10^{-30}>");

  /*  
      THStack hs("hs","test stacked histograms");
      hs.Add(IstgA);
      hs.Add(IstgB);
      hs.Draw(); 
  */
  return();  
}


TFile *Cor;
void LumiRange(){


  if (Cor==0)
    {
      //      Cor = TFile::Open("Vertexes_Data_NDOFGT1_BlinLim0.0_RunList=1_LumiCor=1_ee_DAV.root");
      //TFile *NoCor = TFile::Open("Vertexes_Data_NDOFGT1_BlinLim0.0_RunList=1_LumiCor=0_ee_DAV.root");
      Cor = TFile::Open("Vertexes_Data_NDOFGT1_RunList=1_LumiCor=1_SystCheck0_Sm_DAV.root");
      TFile *NoCor = TFile::Open("Vertexes_Data_NDOFGT1_RunList=1_LumiCor=0_SystCheck0_Sm_DAV.root");

      
      TH1F  *CorDat =   (TH1F*)Cor->Get("Dat_all_Lumi");
      TH1F  *NoCorDat =   (TH1F*)NoCor->Get("Dat_all_Lumi");
    }

  CorDat->Draw("p");
  CorDat->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  CorDat->GetYaxis()->SetTitle("Events");

  NoCorDat->SetMarkerColor(2);
  NoCorDat->SetMarkerStyle(24);
  NoCorDat->SetMarkerSize(1.);
  NoCorDat->Draw("pSAME");



  TLegend *leg = new TLegend(0.4,0.4, 0.7 ,0.6);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(CorDat,"Corrected Luminosity" ,"p");  
  leg->AddEntry(NoCorDat,"Un-corrected Luminosity" ,"p");  

  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);  
  leg->Draw();



}




TFile *Cor;
void TruePois(){

  if (Cor==0)
    {
      //      Cor = TFile::Open("Vertexes_Data_NDOFGT1_BlinLim0.0_RunList=1_LumiCor=1_ee_DAV.root");
      //TFile *NoCor = TFile::Open("Vertexes_Data_NDOFGT1_BlinLim0.0_RunList=1_LumiCor=0_ee_DAV.root");
      Cor = TFile::Open("Vertex_Migration_HADR1_0.060mb_500111_NDOFGT1_PtCut250_RunList=1_LumiCor=0_SystCheck0_Sm_DAV.root");
      //      TFile *NoCor = TFile::Open("Vertexes_Data_NDOFGT1_RunList=1_LumiCor=0_SystCheck0_Sm_DAV.root");

      
      TH1F  *Pois2 =   (TH1F*)Cor->Get("Pois_Theory_Lumi0.666");
      TH1F  *Pois1 =   (TH1F*)Cor->Get("Pois_Theory_Lumi0.089");
    }

  NCanvas(1,1);
  // My->cd(1);
  Pois1->SetMaximum(0.7);
 
  Pois1->Draw("HIST");
  NText(0,0.71," True number of vertices in two luminosity bins",1,0.04);
  Pois1->GetXaxis()->SetTitle("Number of vertices");
  Pois1->GetYaxis()->SetTitle("Fraction");
  Pois1->SetLineColor(2);

  Pois2->SetLineStyle(2);
  Pois2->SetLineColor(4);
  Pois2->Draw("SAMEHIST");
  Pois2->GetXaxis()->SetTitle("Number of vertices");
  Pois2->GetYaxis()->SetTitle("Fraction");

  sprintf(CMSPrel,"CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}") ;
  NText(2.,0.65,CMSPrel,1,0.06);
  TLegend *leg = new TLegend(0.5,0.6, 0.7 ,0.8);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Pois2,"<L> = 0.67  10^{30} cm^{-2}s^{-1}" ,"L");  
  leg->AddEntry(Pois1,"<L> = 0.09  10^{30} cm^{-2}s^{-1}" ,"L");  

  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);  
  leg->SetFillColor(0);  
  leg->Draw();



}




TFile *Cor;
void TrackMult(){

  if (Cor==0)
    {
        TFile *Cor = TFile::Open("Vertexes_Data_NDOFGT1_RunList=1_LumiCor=0_SystCheck0_Sm_DAV.root");

      
      TH1F  *Pois2 =   (TH1F*)Cor->Get("Vertex1Mult");
      TH1F  *Pois1 =   (TH1F*)Cor->Get("Vertex0Mult");
    }

  NCanvas(1,1);
  // My->cd(1);
  Pois1->SetMaximum(15000);
 
  Pois1->Draw("HIST");
  NText(0,15100," Vertex track multiplicity for primary and pile-up events",1,0.06);
  NText(100.,14000, "CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}",1,0.06);

  Pois1->GetXaxis()->SetTitle("Vertex track multiplicity");
  Pois1->GetYaxis()->SetTitle("Events");
  Pois1->SetLineColor(2);

  Pois2->SetLineStyle(2);
  Pois2->SetLineColor(4);
  Pois2->Draw("SAMEHIST");
  Pois2->GetXaxis()->SetTitle("Number of vertices");
  Pois2->GetYaxis()->SetTitle("Fraction");

  TLegend *leg = new TLegend(0.5,0.6, 0.7 ,0.8);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Pois1,"Primary event" ,"L");  
  leg->AddEntry(Pois2,"Pile-up" ,"L");  

  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);  
  leg->SetFillColor(0);  
  leg->Draw();



}



TFile *Cor;
void BlinDist(){

  if (Cor==0)
    {
        TFile *Cor = TFile::Open("Vertexes_Data_NDOFGT1_RunList=0_LumiCor=0_SystCheck0_ee_STD.root");

      
      TH1F  *Pois1 =   (TH1F*)Cor->Get("BlindSpotMult_0_25");
      TH1F  *Pois2 =   (TH1F*)Cor->Get("BlindSpotMult_100_125");
      TH1F  *Pois3 =   (TH1F*)Cor->Get("BlindSpotMult_175_200");

    }

  NCanvas(1,1);
  // My->cd(1);
  Pois1->SetMaximum(1.4);
 
  Pois1->Draw("HIST");
  NText(0,1.42,"Blind distance for 3 different vertex track multiplicity intervals",1,0.06);
  NText(1.5,1.25, "CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}",1,0.06);

  Pois1->GetXaxis()->SetTitle("Distance [cm]");
  Pois1->GetYaxis()->SetTitle("Efficiency");
  Pois1->SetLineColor(2);

  Pois2->SetLineStyle(2);
  Pois2->SetLineColor(4);
  Pois2->Draw("SAMEHIST");
  Pois2->GetXaxis()->SetTitle("Number of vertices");
  Pois2->GetYaxis()->SetTitle("Fraction");


  Pois3->SetLineStyle(3);
  Pois3->SetLineColor(6);
  Pois3->Draw("SAMEHIST");


  TLegend *leg = new TLegend(0.6,0.2, 0.8 ,0.4);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Pois1,"0-25 track multiplicity" ,"L");  
  leg->AddEntry(Pois2,"100-125 track multiplicity" ,"L");  
  leg->AddEntry(Pois3,"175-200 track multiplicity" ,"L");  

  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);  
  leg->SetFillColor(0);  
  leg->Draw();



}




TFile *Cor;
void Zpos(){

  if (Cor==0)
    {
        TFile *Cor = TFile::Open("Vertexes_Data_NDOFGT1_RunList=0_LumiCor=0_SystCheck0_ee_STD.root");

      
      TH1F  *Pois1 =   (TH1F*)Cor->Get("Vz");
    }

  NCanvas(1,1);
  // My->cd(1);
  Pois1->SetMaximum(150000);
 
  Pois1->Draw("HIST");
  NText(-15,151000,"z-vertex position for pile-up events ",1,0.06);
  NText(0,140000, "CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}",1,0.06);

  Pois1->GetXaxis()->SetTitle("z [cm]");
  Pois1->GetYaxis()->SetTitle("Entries");
  Pois1->SetLineColor(2);
}



TFile *Cor;
void MeasLumi(){

  if (Cor==0)
    {
        TFile *Cor = TFile::Open("Vertexes_Data_NDOFGT1_RunList=0_LumiCor=0_SystCheck0_ee_STD.root");

      
      TH1F  *Pois1 =   (TH1F*)Cor->Get("LumiBin8");
    }

  NCanvas(1,1);
  // My->cd(1);
  Pois1->SetMaximum(6000);
 
  Pois1->Draw("HIST");
  //  NText(-15,151000,"Luminosity ",1,0.06);
  NText(0.355,5500, "CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}",1,0.06);

  Pois1->GetXaxis()->SetTitle("Luminosity  [10^{30} cm^{-2}s^{-1}]");
  Pois1->GetYaxis()->SetTitle("Entries");
  Pois1->SetLineColor(2);
}





void ControlPlots(int arg){

  // arg == 1: Endcaps
  // arg == 2: Ntracks
  // arg == 3: HF
  // arg == 4: ZDC
  // arg == 5: Castor
  // arg == 6: EHF ==0
  if(arg==1){
    Int_t nhisto = 2;
    TString histo[nhisto] = {"EEP_1","EEP_all"};
    for (int i=0; i<nhisto,i++){
      gDirectory->Delete(histo[i]);
    }

  gDirectory->Delete("EEP_all");
  gDirectory->Delete("EEP_1_pfx");
  gDirectory->Delete("EEP_all_pfx");
  gDirectory->Delete("EEM_1");
  gDirectory->Delete("EEM_all");
  gDirectory->Delete("EEM_1_pfx");
  gDirectory->Delete("EEM_all_pfx");
  gDirectory->Delete("EE_1");
  gDirectory->Delete("EE_all");
  gDirectory->Delete("EE_1_pfx");
  gDirectory->Delete("EE_all_pfx");
 
  TH2F *EEP_all = new TH2F("EEP_all","Endcap Energy; Inst.  Lumi; Endcap Energy [GeV]",14 ,0.,0.7,100,0.,600.);
  
  NH2clone("EEP_1","EEP_1", EEP_all);
  NH2clone("EEM_1","EEM_1", EEP_all);
  NH2clone("EEM_all","EEM_all", EEP_all);

  data.Draw("energyTot_PF_EE_plus:(istlumiPerBX*6.37)>>EEP_1","istlumiPerBX*6.37>0.1 && numberOfVertexesInEvent==1","goff");
  data.Draw("energyTot_PF_EE_plus:(istlumiPerBX*6.37)>>EEP_all","istlumiPerBX*6.37>0.1","goff");
  data.Draw("energyTot_PF_EE_minus:(istlumiPerBX*6.37)>>EEM_1","istlumiPerBX*6.37>0.1 && numberOfVertexesInEvent==1","goff");
  data.Draw("energyTot_PF_EE_minus:(istlumiPerBX*6.37)>>EEM_all","istlumiPerBX*6.37>0.1","goff");


  EE_1 = (*EEP_1) + (*EEM_1);
  EE_1.SetName("EE_1");
  EE_all = (*EEP_all) + (*EEM_all);
  EE_all.SetName("EE_all");


  EE_all.ProfileX();

  EE_all_pfx->SetTitle("(Endcap Energy) vs (Inst. Lumi per bx)");
  EE_all_pfx->SetStats(kFALSE);
  EE_all_pfx->GetYaxis()->SetTitleOffset(1.2);
  EE_all_pfx->GetYaxis()->SetTitle("Endcap Energy [GeV]");  
  EE_all_pfx->SetMarkerStyle(20);
  EE_all_pfx->SetMarkerColor(2);
  EE_all_pfx->SetLineColor(2);
  EE_all_pfx->SetMinimum(35.);
  EE_all_pfx->SetMarkerSize(1.);
  EE_all_pfx->Draw();
  NText(0.2,40.,"1 vxt events",4);

  EE_1.ProfileX();
  EE_1_pfx->SetMarkerStyle(20);
  EE_1_pfx->SetMarkerSize(1.);
  EE_1_pfx->SetMarkerColor(4);
  EE_1_pfx->SetLineColor(4);
  EE_1_pfx->SetTitle("(Endcap Energy) vs (Inst. Lumi per bx) for 1-vxt events");
  EE_1_pfx->SetStats(kFALSE);
  EE_1_pfx->GetYaxis()->SetTitleOffset(0.9);
  EE_1_pfx->GetYaxis()->SetTitle("Endcap Energy [GeV]");
  EE_1_pfx->Draw("SAMES");
  NText(0.1,80.,"All events",2);

}

  if(arg==2){
    
    gDirectory->Delete("NT_1");
    gDirectory->Delete("NT_all");
    gDirectory->Delete("NT_1_pfx");
    gDirectory->Delete("NT_all_pfx");
  TH2F *NT_all = new TH2F("NT_all","Number of tracks vs Inst. Lumi per bx; Inst.  Lumi per BX [10^{30} cm^{-2} s^{-1}]; Number of tracks",16,0.,0.8,100,0.,800.) ;
  TH2F *NT_1 = new TH2F("NT_1","Number of tracks vs Inst. Lumi per bx; Inst.  Lumi per BX [10^{30} cm^{-2} s^{-1}]; Number of tracks",16,0.,0.8,100,0.,800.) ;
  data.Draw("nTracks_PF:(istlumiPerBX*6.37)>>NT_1","istlumiPerBX*6.37>0.1 && numberOfVertexesInEvent==1","goff");
  data.Draw("nTracks_PF:(istlumiPerBX*6.37)>>NT_all","istlumiPerBX*6.37>0.1","goff");
  NT_1->ProfileX();
  NT_all->ProfileX();


  NT_all_pfx->SetTitle("(# Tracks) vs (Inst. Lumi per bx)");
  NT_all_pfx->SetStats(kFALSE);
  NT_all_pfx->GetYaxis()->SetTitleOffset(1.2);
  NT_all_pfx->SetMarkerStyle(20);
  NT_all_pfx->SetMarkerColor(2);
  NT_all_pfx->SetLineColor(2);
  NT_all_pfx->SetMinimum(80.);
  NT_all_pfx->SetMarkerSize(1.);
  NT_all_pfx->GetYaxis()->SetTitle("# Tracks");
  NT_all_pfx->Draw();
  NText(0.35., 90, "1 vxt events",4);

  NT_1->ProfileX();
  NT_1_pfx->SetMarkerStyle(20);
  NT_1_pfx->SetMarkerSize(1.);
  NT_1_pfx->SetMarkerColor(4);
  NT_1_pfx->SetLineColor(4);
  NT_1_pfx->SetStats(kFALSE);
  NT_1_pfx->GetYaxis()->SetTitleOffset(0.9);
  NT_1_pfx->Draw("SAMES");
  NText(0.1,200.,"All events",2);

}

  if(arg==3){
  gDirectory->Delete("HF_1");
  gDirectory->Delete("HF_all");
  gDirectory->Delete("HF_1_pfx");
  gDirectory->Delete("HF_all_pfx");
  gDirectory->Delete("HFP_1");
  gDirectory->Delete("HFP_all");
  gDirectory->Delete("HFP_1_pfx");
  gDirectory->Delete("HFP_all_pfx");
  gDirectory->Delete("HFM_1");
  gDirectory->Delete("HFM_all");
  gDirectory->Delete("HFM_1_pfx");
  gDirectory->Delete("HFM_all_pfx");
  TH2F *HFM_all = new TH2F("HFM_all","HF vs Inst. Lumi per bx; Inst.  Lumi; Endcap Energy [GeV]",14 ,0.,0.7,100,0.,3000.) ;

  NH2clone("HFM_1","HFM_1", HFM_all);
  NH2clone("HFP_1","HFP_1", HFM_all);
  NH2clone("HFP_all","HFP_all", HFM_all);

  //  NH2clone("HF_1","HF_1", HFM_all); 
  // NH2clone("HF_all","HF_all", HFM_all);


  data.Draw("sumEHF_plus:(istlumiPerBX*6.37)>>HFP_1","istlumiPerBX*6.37>0.1 && numberOfVertexesInEvent==1","goff");
  data.Draw("sumEHF_plus:(istlumiPerBX*6.37)>>HFP_all","istlumiPerBX*6.37>0.1","goff");
  data.Draw("sumEHF_minus:(istlumiPerBX*6.37)>>HFM_1","istlumiPerBX*6.37>0.1 && numberOfVertexesInEvent==1","goff");
  data.Draw("sumEHF_minus:(istlumiPerBX*6.37)>>HFM_all","istlumiPerBX*6.37>0.1","goff");

  //  TProfile *HFprofX_all = 

  HF_1 = (*HFM_1)+(*HFP_1);
  HF_1.SetName("HF_1");

  //  HF_all->Add(HFM_all);
  // HF_all->Add(HFP_all);

  HF_all = (*HFM_all)+(*HFP_all);
  HF_all.SetName("HF_all");

  HF_all.ProfileX();
  HF_all_pfx->SetTitle("(HF Energy) vs (Inst. Lumi per bx)");
  HF_all_pfx->SetStats(kFALSE);
  HF_all_pfx->GetYaxis()->SetTitleOffset(0.9);
  HF_all_pfx->GetYaxis()->SetTitle("HF Energy [GeV]");  
  HF_all_pfx->SetMarkerStyle(20);
  HF_all_pfx->SetMarkerColor(2);
  HF_all_pfx->SetLineColor(2);
  HF_all_pfx->SetMinimum(150.);
  HF_all_pfx->SetMarkerSize(1.);
  HF_all_pfx->Draw();
  NText(0.4,300.,"1 vxt events",4);

  HF_1.ProfileX();
  HF_1_pfx->SetMarkerStyle(20);
  HF_1_pfx->SetMarkerSize(1.);
  HF_1_pfx->SetMarkerColor(4);
  HF_1_pfx->SetLineColor(4);
  HF_1_pfx->SetTitle("(HF Energy) vs (Inst. Lumi per bx) for 1-vxt events");
  HF_1_pfx->SetStats(kFALSE);
  HF_1_pfx->GetYaxis()->SetTitleOffset(0.9);
  HF_1_pfx->GetYaxis()->SetTitle("HF Energy [GeV]");
  HF_1_pfx->Draw("SAMES");
  NText(0.1,700.,"All events",2);
  return();
}

  if(arg==4){
    
  gDirectory->Delete("ZDC_1");
  gDirectory->Delete("ZDC_all");
  gDirectory->Delete("ZDC_1_pfx");
  gDirectory->Delete("ZDC_all_pfx");
  gDirectory->Delete("ZDCP_1");
  gDirectory->Delete("ZDCP_all");
  gDirectory->Delete("ZDCP_1_pfx");
  gDirectory->Delete("ZDCP_all_pfx");
  gDirectory->Delete("ZDCM_1");
  gDirectory->Delete("ZDCM_all");
  gDirectory->Delete("ZDCM_1_pfx");
  gDirectory->Delete("ZDCM_all_pfx");

  TH2F *ZDCM_all = new TH2F("ZDCM_all","ZDC vs Inst. Lumi per bx; Inst.  Lumi; Endcap Energy [GeV]",14 ,0.,0.7,100,0.,5000.) ;

  NH2clone("ZDCM_1","ZDCM_1", ZDCM_all);
  NH2clone("ZDCP_1","ZDCP_1", ZDCM_all);
  NH2clone("ZDCP_all","ZDCP_all", ZDCM_all);

  //  NH2clone("ZDC_1","ZDC_1", ZDCM_all); 
  // NH2clone("ZDC_all","ZDC_all", ZDCM_all);


  data.Draw("sumEZDC_plus:(istlumiPerBX*6.37)>>ZDCP_1","istlumiPerBX*6.37>0.1 && numberOfVertexesInEvent==1","goff");
  data.Draw("sumEZDC_plus:(istlumiPerBX*6.37)>>ZDCP_all","istlumiPerBX*6.37>0.1","goff");
  data.Draw("sumEZDC_minus:(istlumiPerBX*6.37)>>ZDCM_1","istlumiPerBX*6.37>0.1 && numberOfVertexesInEvent==1","goff");
  data.Draw("sumEZDC_minus:(istlumiPerBX*6.37)>>ZDCM_all","istlumiPerBX*6.37>0.1","goff");

  //  TProfile *ZDCprofX_all = 

  ZDC_1 = (*ZDCM_1)+(*ZDCP_1);
  ZDC_1.SetName("ZDC_1");

  //  ZDC_all->Add(ZDCM_all);
  // ZDC_all->Add(ZDCP_all);

  ZDC_all = (*ZDCM_all)+(*ZDCP_all);
  ZDC_all.SetName("ZDC_all");

  ZDC_all.ProfileX();
  ZDC_all_pfx->SetTitle("(ZDC Energy) vs (Inst. Lumi per bx)");
  ZDC_all_pfx->SetStats(kFALSE);
  ZDC_all_pfx->GetYaxis()->SetTitleOffset(0.9);
  ZDC_all_pfx->GetYaxis()->SetTitle("ZDC Energy [GeV]");  
  ZDC_all_pfx->SetMarkerStyle(20);
  ZDC_all_pfx->SetMarkerColor(2);
  ZDC_all_pfx->SetLineColor(2);
  ZDC_all_pfx->SetMinimum(150.);
  ZDC_all_pfx->SetMarkerSize(1.);
  ZDC_all_pfx->Draw();
  NText(0.4,300.,"1 vxt events",4);

  ZDC_1.ProfileX();
  ZDC_1_pfx->SetMarkerStyle(20);
  ZDC_1_pfx->SetMarkerSize(1.);
  ZDC_1_pfx->SetMarkerColor(4);
  ZDC_1_pfx->SetLineColor(4);
  ZDC_1_pfx->SetTitle("(ZDC Energy) vs (Inst. Lumi per bx) for 1-vxt events");
  ZDC_1_pfx->SetStats(kFALSE);
  ZDC_1_pfx->GetYaxis()->SetTitleOffset(0.9);
  ZDC_1_pfx->GetYaxis()->SetTitle("ZDC Energy [GeV]");
  ZDC_1_pfx->Draw("SAMES");
  NText(0.1,700.,"All events",2);
  return();
}


  if(arg==5){
    Zee->cd();
    gDirectory->Delete("CA_1");
    gDirectory->Delete("CA_all");
    gDirectory->Delete("CA_1_pfx");
    gDirectory->Delete("CA_all_pfx");
    
    
    TH2F *CA_all = new TH2F("CA_all","CA vs Inst. Lumi per bx; Inst.  Lumi per bx; Endcap Energy [GeV]",14 ,0.,0.7,100,0.,1000.) ;
    NH2clone("CA_1","CA_1", CA_all);
    tree_->Draw("sumECastor_minus:(istlumiPerBX*6.37)>>CA_1","istlumiPerBX*6.37>0.1 && numberOfVertexesInEvent==1 && RunNumber > 148900","goff");
    tree_->Draw("sumECastor_minus:(istlumiPerBX*6.37)>>CA_all","istlumiPerBX*6.37>0.1 && RunNumber > 148900","goff");

  CA_all->ProfileX();
  CA_all_pfx->SetTitle("(Castor Energy) vs (Inst. Lumi per bx)");
  CA_all_pfx->SetStats(kFALSE);
  CA_all_pfx->GetYaxis()->SetTitleOffset(0.9);
  CA_all_pfx->GetYaxis()->SetTitle("Castor Energy [GeV]");  
  CA_all_pfx->SetMarkerStyle(20);
  CA_all_pfx->SetMarkerColor(2);
  CA_all_pfx->SetLineColor(2);
  CA_all_pfx->SetMinimum(0.);
  CA_all_pfx->SetMarkerSize(1.);
  CA_all_pfx->Draw();
  NText(0.4,30.,"1 vxt events",4);

  CA_1->ProfileX();
  CA_1_pfx->SetMarkerStyle(20);
  CA_1_pfx->SetMarkerSize(1.);
  CA_1_pfx->SetMarkerColor(4);
  CA_1_pfx->SetLineColor(4);
  CA_1_pfx->SetTitle("(Castor Energy) vs (Inst. Lumi per bx) for 1-vxt events");
  CA_1_pfx->SetStats(kFALSE);
  CA_1_pfx->GetYaxis()->SetTitleOffset(0.9);
  CA_1_pfx->GetYaxis()->SetTitle("Castor Energy [GeV]");
  CA_1_pfx->Draw("SAMES");
  NText(0.1,100.,"All events",2);
  return;
}

  if(arg==6){

    // it needs: NCanvas(2,2) and .x datachain.C

    string cut_1 = "istlumiPerBX*6.37>0.1 && numberOfVertexesInEvent==1 && (sumEHF_minus_PF==0 || sumEHF_plus_PF==0)";
    string cut_all = "istlumiPerBX*6.37>0.1 && numberOfVertexesInEvent==1";

    gDirectory->Delete("JP_1");
    gDirectory->Delete("JP_all");
    gDirectory->Delete("JP");    
    gDirectory->Delete("JP_RN_1");
    gDirectory->Delete("JP_RN_all");
    gDirectory->Delete("JP_RN");    
    

    // string cut_1 = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 && (sumEHF_PF_minus==0 || sumEHF_PF_plus==0) &&  (RunNumber<146400 || RunNumber>146460)";      string cut_all = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 &&  (RunNumber<146400 || RunNumber>146460)";
    //    string cut_1 = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 && (sumEHF_minus<4. || sumEHF_plus<4.) &&  (RunNumber<146400 || RunNumber>146460)";      string cut_all = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 &&  (RunNumber<146400 || RunNumber>146460)";
    string cut_1 = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 && (sumEHF_minus<4. || sumEHF_plus<4.)";      string cut_all = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 &&  (RunNumber<146400 || RunNumber>146460)";

    TH1F *JP_all = new TH1F("JP_all","Gap vs Inst. Lumi per bx; Inst.  Lumi per bx; Fraction",28,0.,0.7) ;    
    TH1F *JP_RN_all = new TH1F("JP_RN_all","Gap; Run Number; Fraction",100,140000.,150000) ;    


    TH1F *JP_1; 
    TH1F *JP; 
    TH1F *JP_RN_1; 
    TH1F *JP_RN; 
    JP =   NH1clone("JP","Fraction of 2  high Pt \mu \mu events with at least one HF< 4 GeV", JP_all);
    JP_1 = NH1clone("JP_1","JP_1", JP_all);

    JP_RN =   NH1clone("JP_RN","Fraction of 2 high Pt \mu \mu events with at least one HF< 4 GeV", JP_RN_all);
    JP_RN_1 = NH1clone("JP_RN_1","JP_1", JP_RN_all);

    JP->Sumw2();
    data.Draw("(istlumiPerBX*6.37)>>JP_1",cut_1.c_str(),"goff");
    data.Draw("(istlumiPerBX*6.37)>>JP_all",cut_all.c_str(),"goff");
    JP_RN->Sumw2();
    data.Draw("RunNumber>>JP_RN_1",cut_1.c_str(),"goff");
    data.Draw("RunNumber>>JP_RN_all",cut_all.c_str(),"goff");
    
    JP->Divide(JP_1,JP_all);
    JP_RN->Divide(JP_RN_1,JP_RN_all);
    
    Float_t max = 1.3*JP->GetMaximum();
    JP->SetMaximum(max);
    
    //      JP->SetMaximum(0.045);
    //JP->SetMinimum(0.006);
    
    JP->GetYaxis()->SetTitleOffset(0.8);
    JP->SetMarkerStyle(20);
    JP->SetMarkerColor(2);
    JP->SetLineColor(2);
    JP->SetMarkerSize(1.);

    //MyC->Update();

    MyC->cd(1);          
    JP->Draw("e");
    // MyC->Update();


    MyC->cd(2);          
    JP_RN->GetYaxis()->SetTitleOffset(0.8);
    JP_RN->SetMarkerStyle(20);
    JP_RN->SetMarkerColor(4);
    JP_RN->SetMarkerSize(1.);
    JP_RN->SetLineColor(4);
    MyC_2->SetLogy();

    JP_RN->SetMinimum(0.005);
    JP_RN->Draw("e");
    // c1->Update();
    

    return;
  }


  return;
}

Double_t func(Double_t*x,Double_t*par)
{
  Double_t res=0., xx=x[0];
  if (xx<=0) return 0;
  // Poisson distribution
  // par[1] - distribution parameter 
  return par[0]*TMath::Power(par[1],xx)/TMath::Gamma(xx+1)/TMath::Exp(par[1]);
}





void poisson()
{
   TF1 *pois1 = new TF1("pois1",func,0,10,2); // x in [0;10], 2 parameters
   pois1->SetParName(0,"Const");
   pois1->SetParName(1,"#mu");
   // Create histogram with poisson distribution
   TH1F*testhi = new TH1F("testhi","Poisson distribution",100,0,5);
   pois1->SetParameter(0,3.75654);
   pois1->SetParameter(1,2.95437);
   testhi->FillRandom("pois1",20000);
   
   // Fitting it 
   pois1->SetParameter(0,1);  // not the best shots 
			    // 'cause we fill with 20000 events
			    // so constant will be in 1000 times bigger 
   pois1->SetParameter(1,1);  // :)
   TCanvas *cc = new TCanvas("cc","Canvas",600,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(111);
   testhi->Fit("pois1");
   testhi->Draw();
   return();
}



void Reweight_EHF(){

  TCanvas *pippo = NCanvas(2,2);
  
  TCut cutRw = "numberOfVertexes==1";
  gDirectory->Delete("pythia");
  gDirectory->Delete("data");
  gDirectory->Delete("ratio");
  
  TH1F *pythia = new TH1F("pythia","pythia", 10, 0., 1000.);
  TH1F *data = new TH1F("data","data", 10, 0., 1000.);
  TH1F *ratio = new TH1F("ratio","ratio", 10, 0., 1000.);

  
  NPYTZ2_Zee->cd("Selection");
  pippo->cd(1);
  pythia->Draw();
  tree_->Draw("TMath::Min(sumEHF_minus,sumEHF_plus)>>pythia",cutRw,"SAME");
  NDat_ZeeA->cd("Selection");
  pippo->cd(2);
  data->Draw();
  tree_->Draw("TMath::Min(sumEHF_minus,sumEHF_plus)>>data",cutRw,"SAME");
  pippo->cd(3);
  ratio->Sumw2();
  ratio->Divide(pythia,data);
  ratio->Draw();
  
}

void TransverseCut(){

  // TFile *_file0 = TFile::Open("files/SkimA_sm_DAV_v1_16.root")
  // TFile *_file0 = TFile::Open("files/MCZZ_P6Z2_PU2011_v1_16.root")

  TCanvas *pippo = NCanvas(1,2);
  pippo->cd(1);
  TH2F *DataTr = new TH2F("DataTr","DATATr;Vertex Multiplicity; Transverse Position", 60,0.,120,100,0.,1.);
  TH1F *Tr1 = new TH1F("Tr1","DATATr;Transverse Position", 100,0.,1.);
  TH1F *Tr2 = new TH1F("Tr2","DATATr;Transverse Position", 100,0.,1.);
  DataTr->SetMarkerSize(0.1);
  NLogAxis(0,0);
  tree_->Draw("sqrt(pow(V_x[1],2)+pow(V_y[1],2)):vertexMolteplicity[1]>>DataTr");
  DataTr->GetXaxis()->SetTitle("Track Multiplicity ");
  DataTr->GetYaxis()->SetTitle("Vertex Transverse Position [cm]");

  pippo->cd(2);
  tree_->Draw("sqrt(pow(V_x[1],2)+pow(V_y[1],2))>>Tr1", "vertexMolteplicity[1]>5");
  tree_->Draw("sqrt(pow(V_x[1],2)+pow(V_y[1],2))>>Tr2", "vertexMolteplicity[1]<5","SAMES");
  Tr1->Fit("gaus"); 
  Tr1->Draw(); 
  NText(40.,0.8, "CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}",1,0.06);
  NLogAxis(0,1);
  Tr1->GetXaxis()->SetTitle("Vertex Transverse Position [cm]");
  Tr1->GetYaxis()->SetTitle("Entries");
  Tr2->SetLineStyle(2);
  Tr2->SetLineColor(2);
  Tr2->Draw("SAME");
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(111);
 
  TLegend *leg = new TLegend(0.37,0.7, 0.7 ,0.85);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Tr1,"Multiplicity > 5", "L");  
  leg->AddEntry(Tr2,"Multiplicity <5","L");
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.05);  
  leg->Draw();

  return;
}



void Blind2(){

  // TFile *_file0 = TFile::Open("files/SkimA_sm_DAV_v1_16.root")
  // TFile *_file0 = TFile::Open("files/MCZZ_P6Z2_PU2011_v1_16.root")

  TCanvas *pippo = NCanvas(1,1);
  pippo->cd(1);
  TH2F *DataTr = new TH2F("DataTr","DataTr", 60,-0.25.,0.25,100,0.,200.);
  DataTr->SetMarkerSize(0.1);
  NLogAxis(0,0);
  tree_->Draw("(vertexMolteplicity[1]+vertexMolteplicity[0]):(V_z[0] - V_z[1])>>DataTr");
  DataTr->GetYaxis()->SetTitle("Summed Track Multiplicity ");
  DataTr->GetXaxis()->SetTitle("Distance between vertices [cm]");

  return;
}


void Lumi_vs_vtx(){
  //TFile *_file0 = TFile::Open("files/SkimB_sm_DAV_v1_16.root")
  TH2F *Lum = new TH2F("Lum", "Lum", 50, 0.01,0.8, 100, 0.,10);
  //NSetLabelSize(Lum, 0.01,0.01,0.06);
  // NSetTitleSize(Lum,0.01,0.01,0.06);
  Lum->SetMarkerSize(0.1);
 Lum->GetXaxis()->SetTitleOffset(0.7);
 Lum->GetYaxis()->SetTitleOffset(0.7);
  tree_->Draw("numberOfVertexes:istlumiPerBX*6.37>>Lum");

  Lum->GetYaxis()->SetTitle(" Inst.  Luminosity [10^{30} cm^{-2} s^{-1}] ");
  Lum->GetYaxis()->SetTitle("Number of Vertices");
  NText(100.,14000, "CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}",1,0.06);
}

void Xi_3track(){
  //  TFile *_file0 = TFile::Open("Vertex_MCMB_nTrkPt_EtaCut2.6.root")


  TH1F  *Xi_All =   (TH1F*)_file0->Get("Xi_P8_CHA");
  TH1F  *Xi_All_3trk =   (TH1F*)_file0->Get("Xi_TrkGenEta3Pt200_P8_CHA");
  TH1F  *Xi_All_2trk =   (TH1F*)_file0->Get("Xi_TrkGenEta2Pt200_P8_CHA");
  
  Xi_All->Draw();
  Xi_All_3trk->Draw("SAME");
  Xi_All_3trk->SetLineStyle(2);
  Xi_All_3trk->SetLineColor(2);


  Int_t BinLim = Xi_All->FindBin(-3.6);
  //  Int_t BinLim = Xi_All->FindBin(-6);
  cout << " Bin Limit = " << BinLim << endl;
  Int_t IntAll = Xi_All->Integral(BinLim, 200);
  Int_t IntAll2 = Xi_All_2trk->Integral(BinLim, 200);
  
  Float_t scale = (Float_t) IntAll/IntAll2;

  Float_t Int2trk = Xi_All_2trk->Integral(0,BinLim);
  Float_t RealArea = IntAll + Int2trk;
  
  Float_t A2trk = Xi_All_2trk->Integral();
  //  RealArea = A2trk;

  for (Int_t ip = 40; ip<100;ip++)
    {
      if (Xi_All->Integral(ip,200)> RealArea && Xi_All->Integral(ip+1,200)<RealArea ) 
      	{
        cout << "Bin = " << ip << " Low edge = " << Xi_All->GetBinLowEdge(ip) << endl;
	Rightx = Xi_All->GetBinLowEdge(ip);
      	}
    }
  
  cout << "2 trk area = " << RealArea << " scale = " << scale << endl;
  Float_t rr = pow(10, 	Rightx );
  cout << " Equivalent limit = " << rr << endl;

  NLine(-4.2, 0, -4.2, 1000, 2) ;

  Xi_All_2trk->Scale(scale);

  Xi_All_3trk->Scale(scale);
  Xi_All_2trk->Draw("SAME");

  Xi_All_2trk->SetLineStyle(4);
  Xi_All_2trk->SetLineColor(4);
  Xi_All->GetXaxis()->SetTitle("log_{10}#xi");
  Xi_All->GetYaxis()->SetTitle("Events");
  TLegend *leg = new TLegend(0.2,0.7, 0.5 ,0.9);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Xi_All,"All events" ,"L");  
  leg->AddEntry(Xi_All_3trk,"Events with 3 tracks, p_{t}> 200 MeV" ,"L");  
  leg->AddEntry(Xi_All_2trk,"Events with 2 tracks, p_{t}> 200 MeV" ,"L");  

  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.0);  
  leg->Draw();
  NText(-7.,18000, "CMS Simulation",1,0.06);    
  NLogAxis(0,1);

}



void Xi_Study(){
  //  TFile *_file0 = TFile::Open("Vertex_MCMB_nTrkPt_EtaCut2.6.root")


  TH1F  *Xi_All =   (TH1F*)_file0->Get("Xi_P8_CHA");
  TH1F  *Xi_All_3trk =   (TH1F*)_file0->Get("Xi_TrkGenEta3Pt200_P8_CHA");
  TH1F  *Xi_All_2trk =   (TH1F*)_file0->Get("Xi_TrkGenEta2Pt200_P8_CHA");

  TH1F *Xi_ratio = NH1clone("Xi_ratio","Xi_ratio",Xi_All);

  Xi_ratio->Add(Xi_All_2trk);
  Xi_ratio->Divide(Xi_All);

  // Xi_ratio->GetXaxis()->SetRange(-8.,-3.6);
  Xi_ratio->Draw();
  Int_t BinLim = Xi_ratio->FindBin(-3.6);
  Float_t IntAll = Xi_All->Integral(BinLim, 200);
  //  Float_t Int2trk = Xi_All_2trk->Integral(0,BinLim);
  Float_t Int2trk = Xi_All_2trk->Integral(BinLim,200);
  Float_t RealArea = IntAll + Int2trk;
  
  cout << "All (-3.6) + 2 trk = " << RealArea << "; All area = " << IntAll << "; 2trk Area =" << Int2trk << endl;

  cout << "intergral till bin -4.2 = " << Xi_P8_CHA->Integral(77,200) << endl;


  return;

  Xi_All_3trk->Draw("SAME");
  Xi_All_3trk->SetLineStyle(2);
  Xi_All_3trk->SetLineColor(2);

  Xi_All_2trk->Draw("SAME");
  Xi_All_2trk->SetLineStyle(4);
  Xi_All_2trk->SetLineColor(4);
  Xi_All->GetXaxis()->SetTitle("#xi");
  Xi_All->GetYaxis()->SetTitle("Events");
  TLegend *leg = new TLegend(0.2,0.7, 0.5 ,0.9);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Xi_All,"All events" ,"L");  
  leg->AddEntry(Xi_All_3trk,"Events wit 3 tracks, p_{t}> 200 MeV" ,"L");  
  leg->AddEntry(Xi_All_2trk,"Events wit 2 tracks, p_{t}> 200 MeV" ,"L");  

  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.0);  
  leg->Draw();
  NText(-7.,18000, "CMS Simulation",1,0.06);    
  NLogAxis(0,1);
}
