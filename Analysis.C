// Indice:

// 1-> Efficenza eta_Charge e eta_Max(No HF)
    // With "Kind Of Data" you specify the dataset you want to use: 
    // 1-> Real Data JPsi
    // 11-> Real Data Z
    // 2-> Non Diffractive MC
    // 3-> Diffractive MC

// 2-> Energia_HF Vs eta_Max 

// 3-> Invariant e-e Mass 0-16 GeV. Events with sumHF=0 superimposed.

// 4-> Epz spectrum Non Diffractive MC Vs Diffractive MC, case PF and PF no HF

// 5-> SumHF spectrum Non Diffractive MC Vs Diffractive MC, case PF and PF no HF

// 6-> SumHF spectrum For Z and JPsi

// 7-> Epz spectrum For Z and JPsi

// 8-> csi Resolution
//     1-> (xi_meas-xi_gen)/xi_meas Vs xi_meas  +++++  (xi_meas-xi_gen) Vs xi_meas
//     2-> As point 1 but using profile (errors are the spread!)
//     3-> Purity percentuale dei trovati in un bin che son veramente venuti da quel bin
//     4-> Normal distribution xi_gen and xi_measured
//     5-> (xi_meas-xi_gen)/xi_meas Vs xi_meas  +++++  (xi_meas-xi_gen) Vs xi_meas when one of these detector is sum==0 -> HF,CASTOR,ZDC
//     6-> Efficiency = trovati in un certo bin (measured)/ provientienti da qul bin (teorici) 
//     7-> Migration Map

// 9-> csi Efficiency 

// 10-> Cuts to select signal with variables X:etaWeighted
//     1-> X= (Epz_minus-Epz_plus)
//     2-> X= (HF+ - HF-)
//     3-> X= (HF+ - HF-) / (HF+ + HF-)
//     4-> X= (energy_Tot_plus-energyTot_minus)
//     5-> X= (HF+ - HF-)/ max(HF+,HF-)


// 11-> Z data
//     1-> General Invariant Mass
//     2-> General Invariant Mass when sumHF==0

// 12-> J/Psi data
//     1-> General Invariant Mass
//     2-> General Invariant Mass when sumHF==0

// 13-> Minimum Bias
//     1-> General Invariant Mass
//     2-> General Invariant Mass when sumHF==0
//     3-> (HF+ - HF-)

// 14-> Cross Section Measurement
//     1-> Total Distribution
//     2-> sumHF==0

// 15-> xi_meas As a function of RunNumber
#include <iostream>
#include <sstream>

TFile *PomPyt;
TFile *ZeeData;
TFile *Pythia;
string cut;

void Analysis(int arg1, int arg2){
  //gROOT->Reset();
  int type=arg1;
  int KindOfData=arg2;
  string title;
  //if (KindOfData==3) TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/DiffractiveMC.root");
  //  if (KindOfData==2) TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/pythia/SelectedRootupla_6_0_a9r.root");
  //if (KindOfData==1) TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/JPsi.root");
  //if (KindOfData==11) TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/Zee4NovSkim.root");
  if (type==0){
    cout<<"Loading /castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/pythia.root as Pythia"<<endl;    
      Pythia = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/pythia.root");
      cout<<"Loading /castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/ZetaSkim.root as ZeeData"<<endl;
      ZeeData = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/ZetaSkim.root");
      cout<<"Loading /castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/DiffractiveMC.root as PomPyt"<<endl;
      PomPyt = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/DiffractiveMC.root");
      cut="RunNumber < 145762";


      TH1F *PomPytHisto;
      TH1F *PomPytHisto_plus;   
      TH1F *PomPytScaled;
      TH1F *ZDataEvent;
      TH1F *ZDataEvent_plus;
      TH1F *PythiaHisto;
      TH1F *PythiaHisto_plus;
      TH1F *PythiaScaled;
    
      return;
  }
  if (type==1){
    if (KindOfData==3) title="Cut efficiency: PomPyt Diffractive MC";
    if (KindOfData==2) title="Cut efficiency: Pythia DT6 Non Diffractive MC";
    if (KindOfData==1) title="Cut efficiency: RealData JPsi";
    if (KindOfData==11) title="Cut efficiency: RealData Z->ee";
    cout<<"Number of events "<<tree_->GetEntries()<<endl;
  int size=tree_->GetEntries();
  TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
  c1->Divide(1,2);
  c1->cd(1);
  c1->SetName(title.c_str());
  float etacharge[11];
  float etatot[11];
  float cuts[11]={-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5};
  TH1F *tmp= new TH1F("tmp","tmp",100,-5,5); 
  TH1F *tmp2= new TH1F("tmp2","tmp2",100,-5,5); 
  TH1F *tmp3= new TH1F("tmp3","tmp3",100,-5,5); 
  //TH1F *tmp2=(TH1F*)tmp->Clone();
  stringstream stringa;
  for (int i=0; i<11;i++ ){
    stringa<<cuts[i];
    string cut="etaMax_PF_Vertex_Selection<"+stringa.str();
    string cut2="etaMax_PF_NOHF<"+stringa.str();    
    cout<<cut<<endl;
    tree_->Draw("etaMax_PF_Vertex_Selection>>tmp",cut.c_str(),"goff");
    cout<<tmp->GetEntries()<<endl;
    etacharge[i]=tmp->GetEntries();
    tree_->Draw("etaMax_PF_NOHF>>tmp2",cut2.c_str(),"goff");    
    cout<<tmp2->GetEntries()<<endl;
    etatot[i]=tmp2->GetEntries();   
    stringa.str("");
    tree_->Draw("sumEHF_plus>>tmp3","sumEHF_plus==0","goff");
    //cout<<"The HF plus side has events with zero deposit ->"<<tmp3->GetEntries()<<endl;
    double HFratio=tmp3->GetEntries()/size;
  }
  cout<<"HF ratio "<<HFratio<<endl;
  float etadividedcharge[11];
  float etadividedtot[11];  
  for (int i=0; i<=10;i++ ){
    etadividedcharge[i]=etacharge[i]/(size);
    etadividedtot[i]=etatot[i]/(size);
    cout<<"etadividedcharge "<<etadividedcharge[i]<<" etadividedtot "<<etadividedtot[i]<<endl;
  }  
  TGraph *gr1= new TGraph(11,cuts,etadividedcharge);
  TGraph *gr2= new TGraph(11,cuts,etadividedtot);
  gPad->SetLogy(1);
  gStyle->SetFillColor(0);
  gr1->SetMarkerStyle(20);
  gr2->SetMarkerStyle(24);
  gr1->SetTitle(title.c_str());
  gr1->SetMaximum(2);
  gr1->SetMinimum(0.0001);  
  gr1->Draw("AP");
  gr1->GetXaxis()->SetTitle("Eta");
  gr1->GetYaxis()->SetTitle("Efficency");
  leg = new TLegend(0.2,0.6,0.4,0.89);
  leg->AddEntry(gr1,"eta charge","p");
  leg->AddEntry(gr2,"eta total","p");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.06);  
  leg->Draw();
  gr2->Draw("P");
  TLine *line= new TLine(-2.5,HFratio,2.5,HFratio);
  line->SetLineStyle(2);
  line->SetLineColor(kRed);  
  pt = new TPaveText(0.20,0.4,0.4,0.87, "NDC");
  text = pt->AddText("HF=0 Efficiency");
  pt->SetBorderSize(0);  
  pt->SetTextSize(0.04);
  pt->SetTextColor(kRed); 
  pt->SetX1(0.86);
  pt->SetX2(0.68);
  pt->SetY1(0.54);
  pt->SetY2(0.62);   
  pt->Draw();
  line->Draw();
  c1->Write();

  //Eta Min
  //TCanvas *c2= new TCanvas("c2","c2",400,20,1200,800);
  c1->cd(2);
  for (int i=0; i<11;i++ ){
    stringa<<cuts[i];
    string cut="etaMin_PF_Vertex_Selection>"+stringa.str();
    string cut2="etaMin_PF_NOHF>"+stringa.str();    
    cout<<cut<<endl;
    tree_->Draw("etaMin_PF_Vertex_Selection>>tmp",cut.c_str(),"goff");
    cout<<tmp->GetEntries()<<endl;
    etacharge[i]=tmp->GetEntries();
    tree_->Draw("etaMin_PF_NOHF>>tmp2",cut2.c_str(),"goff");    
    cout<<tmp2->GetEntries()<<endl;
    etatot[i]=tmp2->GetEntries();   
    stringa.str("");
  }
  float etadividedcharge[11];
  float etadividedtot[11];  
  for (int i=0; i<=10;i++ ){
    etadividedcharge[i]=etacharge[i]/size;
    etadividedtot[i]=etatot[i]/size;
    cout<<"etadividedcharge "<<etadividedcharge[i]<<" etadividedtot "<<etadividedtot[i]<<endl;
  }  
  TGraph *gr1= new TGraph(11,cuts,etadividedcharge);
  TGraph *gr2= new TGraph(11,cuts,etadividedtot);
  gPad->SetLogy(1);
  gStyle->SetFillColor(0);
  gr1->SetMarkerStyle(20);
  gr2->SetMarkerStyle(24);
  gr1->Draw("AP");
  gr1->GetXaxis()->SetTitle("Eta");
  gr1->GetYaxis()->SetTitle("Efficency");
  gr1->SetMaximum(2); 
  gr1->SetMinimum(0.0001); 
  gr1->SetTitle("");
  leg = new TLegend(1-0.2,0.6,1-0.4,0.89);
  leg->AddEntry(gr1,"eta charge","p");
  leg->AddEntry(gr2,"eta total","p");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.06);
  leg->Draw();
  gr2->Draw("P"); 
  TLine *line= new TLine(-2.5,HFratio,2.5,HFratio);
  line->SetLineStyle(2);
  line->SetLineColor(kRed);  
  pt = new TPaveText(0.20,0.7,0.5,0.87, "NDC");
  text = pt->AddText("HF=0 efficiency");
  pt->SetBorderSize(0);  
  pt->SetTextSize(0.04);
  pt->SetTextColor(kRed);    
  pt->SetX1(0.86);
  pt->SetX2(0.68);
  pt->SetY1(0.54);
  pt->SetY2(0.62);
  pt->Draw();
  line->Draw();
  c1->Write();
  }

  if (type==3){
    //Completare
    tree_->Draw("InvariantMass","InvariantMass<16");
    tree_->Draw("InvariantMass","sumEHF_plus==0 || sumEHF_minus==0","SAME");
  }

  if (type==4){
    TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/DiffractiveMC.root");
    _file0->cd();
    TH1F *histoDiff=new TH1F("histoDiff","Sum E+pz for Diffractive and not Diffractive MC",20,0,1000);
    TH1F *histoDiff_NOHF=new TH1F("histoDiff_NOHF","Sum E+pz for Diffractive and not Diffractive MC excluding HF",20,0,1000);
    tree_->Draw("Epz_PF_plus_NOHF>>histoDiff_NOHF");
    tree_->Draw("Epz_PF_plus>>histoDiff");

    TFile *_file1 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/pythia.root");
    _file1->cd();   
    TH1F *histoND=new TH1F("histoND","histoND",20,0,1000);
    TH1F *histoND_NOHF=new TH1F("histoND_NOHF","histoND_NOHF",20,0,1000);
    tree_->Draw("Epz_PF_plus_NOHF>>histoND_NOHF");
    tree_->Draw("Epz_PF_plus>>histoND");

    cout<<histoDiff->GetEntries()<<"---"<<histoND->GetEntries()<<endl;
    double ratio=histoDiff->GetEntries()/histoND->GetEntries();
    histoND->Scale(ratio);

    TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
    c1->Divide(1,2);
    c1->cd(1);
    gStyle->SetOptStat("e");
    gStyle->SetFillColor(0);
    histoDiff->GetXaxis()->SetTitle("Energy [GeV]");
    histoDiff->Draw();
    histoND->SetLineStyle(2);
    histoND->SetLineColor(kRed);    
    histoND->Draw("SAME");
    leg = new TLegend(0.2,0.6,0.4,0.89);
    leg->AddEntry(histoND_NOHF,"Non Diffractive MC","l");
    leg->AddEntry(histoDiff_NOHF,"Diffractive MC","l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);  
    leg->Draw();
  
    c1->cd(2);
    gStyle->SetOptStat("e");
    gStyle->SetFillColor(0);
    cout<<histoDiff_NOHF->GetEntries()<<"---"<<histoND_NOHF->GetEntries()<<endl;
    double ratio2=histoDiff_NOHF->GetEntries()/histoND_NOHF->GetEntries();
    histoND_NOHF->Scale(ratio2);
    histoDiff_NOHF->GetXaxis()->SetTitle("Energy [GeV]");
    histoDiff_NOHF->Draw();
    histoND_NOHF->SetLineStyle(2);
    histoND_NOHF->SetLineColor(kRed);
    histoND_NOHF->Draw("SAME");
    leg = new TLegend(0.2,0.6,0.4,0.89);
    leg->AddEntry(histoND_NOHF,"Non Diffractive MC","l");
    leg->AddEntry(histoDiff_NOHF,"Diffractive MC","l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);  
    leg->Draw();


    //Minus Side
    TCanvas *c2= new TCanvas("c2","c2",400,20,1200,800);
    c2->Divide(1,2);
    c2->cd(1);
    TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/DiffractiveMC.root");
    _file0->cd();
    TH1F *histoDiffM=new TH1F("histoDiffM","Sum E-pz for Diffractive and not Diffractive MC",20,0,1000);
    TH1F *histoDiff_NOHFM=new TH1F("histoDiff_NOHFM","Sum E-pz for Diffractive and not Diffractive MC excluding HF",20,0,1000);
    tree_->Draw("Epz_PF_minus_NOHF>>histoDiff_NOHFM");
    tree_->Draw("Epz_PF_minus>>histoDiffM");
    
    TFile *_file1 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/pythia.root");
    _file1->cd();   
    TH1F *histoNDM=new TH1F("histoNDM","histoNDM",20,0,1000);
    TH1F *histoND_NOHFM=new TH1F("histoND_NOHFM","histoND_NOHFM",20,0,1000);
    tree_->Draw("Epz_PF_minus_NOHF>>histoND_NOHFM");
    tree_->Draw("Epz_PF_minus>>histoNDM");

    cout<<histoDiffM->GetEntries()<<"---"<<histoNDM->GetEntries()<<endl;
    double ratio=histoDiffM->GetEntries()/histoNDM->GetEntries();
    histoNDM->Scale(ratio);
    gStyle->SetOptStat("e");
    gStyle->SetFillColor(0);
    histoDiffM->GetXaxis()->SetTitle("Energy [GeV]");
    histoDiffM->Draw();
    histoNDM->SetLineStyle(2);
    histoNDM->SetLineColor(kRed);    
    histoNDM->Draw("SAME");
    leg = new TLegend(0.2,0.6,0.4,0.89);
    leg->AddEntry(histoND_NOHFM,"Non Diffractive MC","l");
    leg->AddEntry(histoDiff_NOHFM,"Diffractive MC","l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);  
    leg->Draw();
    c2->cd(2);
    gStyle->SetOptStat("e");
    gStyle->SetFillColor(0);

    cout<<histoDiff_NOHFM->GetEntries()<<"---"<<histoND_NOHFM->GetEntries()<<endl;
    double ratio2=histoDiff_NOHFM->GetEntries()/histoND_NOHFM->GetEntries();
    histoND_NOHFM->Scale(ratio2);
    histoDiff_NOHFM->GetXaxis()->SetTitle("Energy [GeV]");
    histoDiff_NOHFM->Draw();
    histoND_NOHFM->SetLineStyle(2);
    histoND_NOHFM->SetLineColor(kRed);
    histoND_NOHFM->Draw("SAME");
    leg = new TLegend(0.2,0.6,0.4,0.89);
    leg->AddEntry(histoND_NOHFM,"Non Diffractive MC","l");
    leg->AddEntry(histoDiff_NOHFM,"Diffractive MC","l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);  
    leg->Draw();   
  }

 if (type==5){
    TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/DiffractiveMC.root");
    _file0->cd();
    TH1F *histoDiff=new TH1F("histoDiff","Sum EHF+ for Diffractive and not Diffractive MC",250,0,1000);
    TH1F *histoDiffM=new TH1F("histoDiffM","Sum EHF- for Diffractive and not Diffractive MC",250,0,1000);
    tree_->Draw("sumEHF_plus>>histoDiff");
    tree_->Draw("sumEHF_minus>>histoDiffM");

    TFile *_file1 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/pythia.root");
    _file1->cd();   
    TH1F *histoNDM=new TH1F("histoNDM","histoNDM",250,0,1000);
    TH1F *histoND=new TH1F("histoND","histoND",250,0,1000);
    tree_->Draw("sumEHF_plus>>histoND");
    tree_->Draw("sumEHF_minus>>histoNDM");

    cout<<histoDiff->GetEntries()<<"---"<<histoND->GetEntries()<<endl;
    double ratio=histoDiff->GetEntries()/histoND->GetEntries();
    histoND->Scale(ratio);

    TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
    c1->Divide(1,2);
    c1->cd(1);
    gStyle->SetOptStat("e");
    gStyle->SetFillColor(0);
    histoDiff->GetXaxis()->SetTitle("Energy [GeV]");
    gStyle->SetOptStat("e");
    histoDiff->Draw();
    histoND->SetLineStyle(2);
    histoND->SetLineColor(kRed);    
    histoND->Draw("SAME");
    leg = new TLegend(0.2,0.6,0.4,0.89);
    leg->AddEntry(histoND,"Non Diffractive MC","l");
    leg->AddEntry(histoDiff,"Diffractive MC","l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);  
    leg->Draw();
  
    c1->cd(2);
    gStyle->SetOptStat("e");
    cout<<histoDiffM->GetEntries()<<"---"<<histoNDM->GetEntries()<<endl;
    double ratio=histoDiffM->GetEntries()/histoNDM->GetEntries();
    histoNDM->Scale(ratio);

    gStyle->SetFillColor(0);
    histoDiffM->GetXaxis()->SetTitle("Energy [GeV]");
    histoDiffM->Draw();
    histoNDM->SetLineStyle(2);
    histoNDM->SetLineColor(kRed);    
    histoNDM->Draw("SAME");
    leg = new TLegend(0.2,0.6,0.4,0.89);
    leg->AddEntry(histoNDM,"Non Diffractive MC","l");
    leg->AddEntry(histoDiffM,"Diffractive MC","l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);  
    leg->Draw();

  }

 if (type==6){
   TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/JPsi.root");
   _file0->cd();
    TH1F *JPsi=new TH1F("JPsi","Sum EHF for JPsi",250,0,1000);
    TH1F *JPsiM=new TH1F("JPsiM","Sum EHF- for JPsi",250,0,1000);
    tree_->Draw("sumEHF_plus>>JPsi");
    tree_->Draw("sumEHF_minus>>JPsiM");

    TFile *_file1 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/Zee4NovSkim.root");
    _file1->cd();   
    TH1F *Z=new TH1F("Z","Sum EHF for Z",250,0,1000);
    TH1F *ZM=new TH1F("ZM","Sum EHF- for Z",250,0,1000);
    tree_->Draw("sumEHF_plus>>Z");
    tree_->Draw("sumEHF_minus>>ZM");

    TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
    c1->Divide(1,2);
    c1->cd(1);
    gStyle->SetOptStat("e");
    gStyle->SetFillColor(0);
    JPsi->GetXaxis()->SetTitle("Energy [GeV]");
    gStyle->SetOptStat("e");
    JPsi->Draw();
    JPsiM->SetLineStyle(2);
    JPsiM->SetLineColor(kRed);    
    JPsiM->Draw("SAME");
    leg = new TLegend(0.2,0.6,0.4,0.89);
    leg->AddEntry(JPsiM,"Sum minus side","l");
    leg->AddEntry(JPsi,"Sum plus side","l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);  
    leg->Draw();
  
    c1->cd(2);
    gStyle->SetOptStat("e");
    gStyle->SetFillColor(0);
    Z->GetXaxis()->SetTitle("Energy [GeV]");
    Z->SetMaximum(60);    
    Z->Draw();
    ZM->SetLineStyle(2);
    ZM->SetLineColor(kRed);    
    ZM->Draw("SAME");
    leg = new TLegend(0.2,0.6,0.4,0.89);
    leg->AddEntry(ZM,"Sum minus side","l");
    leg->AddEntry(Z,"Sum plus side","l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);  
    leg->Draw();

  }
ß
 if (type==7){
   TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/JPsi.root");
   _file0->cd();
    TH1F *JPsi=new TH1F("JPsi","Epz JPsi",20,0,1000);
    TH1F *JPsiM=new TH1F("JPsiM","Sum EHF- for JPsi",20,0,1000);
    tree_->Draw("Epz_PF_plus>>JPsi");
    tree_->Draw("Epz_PF_minus>>JPsiM");

    TFile *_file1 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/Zee4NovSkim.root");
    _file1->cd();   
    TH1F *Z=new TH1F("Z","Epz for Z",20,0,1000);
    TH1F *ZM=new TH1F("ZM","Sum EHF- for Z",20,0,1000);
    tree_->Draw("Epz_PF_plus>>Z");
    tree_->Draw("Epz_PF_minus>>ZM");

    TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
    c1->Divide(1,2);
    c1->cd(1);
    gStyle->SetOptStat("e");
    gStyle->SetFillColor(0);
    JPsi->GetXaxis()->SetTitle("Energy [GeV]");
    gStyle->SetOptStat("e");
    JPsi->Draw();
    JPsiM->SetLineStyle(2);
    JPsiM->SetLineColor(kRed);    
    //JPsiM->Draw("SAME");
    leg = new TLegend(0.2,0.6,0.4,0.89);
    //leg->AddEntry(JPsiM,"E-pz","l");
    leg->AddEntry(JPsi,"E+pz","l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);  
    leg->Draw();
  
    c1->cd(2);
    gStyle->SetOptStat("e");
    gStyle->SetFillColor(0);
    Z->GetXaxis()->SetTitle("Energy [GeV]");
    Z->Draw();
    ZM->SetLineStyle(2);
    ZM->SetLineColor(kRed);    
    //ZM->Draw("SAME");
    leg = new TLegend(0.2,0.6,0.4,0.89);
    //leg->AddEntry(ZM,"E-pz","l");
    leg->AddEntry(Z,"E+pz","l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);  
    leg->Draw();

  }

 if (type==8){
   if (KindOfData==1){
     PomPyt->cd();
     TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
     TH2F *histo=new TH2F("histo","(xi_measured-xi_gen)/xi_meas Vs xi_measured",20,0,0.1,36,-4,4);
     TH2F *histo2=new TH2F("histo2","",20,0,0.1,36,-4,4);
     c1->Divide(1,2);
     c1->cd(1);
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     tree_->Draw("((Epz_PF_minus/7000)-xi_gen)/(Epz_PF_minus/7000):(Epz_PF_minus/7000)>>histo","Epz_PF_minus < Epz_PF_plus  && xi_gen <0.2","goff");
     histo->GetXaxis()->SetTitle("xi_measured");
     histo->GetYaxis()->SetTitle("#frac{xi_{meas}-xi_{gen}}{xi_{meas}}");     
     histo->SetMarkerStyle(22);
     histo->SetMarkerSize(0.9);
     histo->Draw();
     tree_->Draw("((Epz_PF_plus/7000)-xi_gen)/(Epz_PF_plus/7000):(Epz_PF_plus/7000)>>histo2","Epz_PF_minus > Epz_PF_plus && xi_gen <0.2","goff");
     histo2->SetMarkerStyle(21);
     histo2->SetMarkerColor(kRed);
     histo2->SetMarkerSize(0.7);
     histo2->GetXaxis()->SetTitle("xi_measured");
     histo2->Draw("SAMES");    
     leg = new TLegend(0.2,0.6,0.4,0.89);
     leg->AddEntry(histo,"Epz plus","p");
     leg->AddEntry(histo2,"Epz minus","p");
     leg->SetBorderSize(0);
     leg->SetTextSize(0.06);  
     leg->Draw();
     c1->cd(2);
     TH2F *histo3=new TH2F("histo3","(xi_measured-xi_gen) Vs xi_measured",20,0,0.1,36,-0.2,0.2);
     TH2F *histo4=new TH2F("histo4","xi resolution (absolute value)",20,0,0.1,36,-0.2,0.2);
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     tree_->Draw("((Epz_PF_minus/7000)-xi_gen):(Epz_PF_minus/7000)>>histo3","Epz_PF_minus < Epz_PF_plus && xi_gen <0.2","goff");
     histo3->GetXaxis()->SetTitle("xi_measured");
     histo3->GetYaxis()->SetTitle("xi_{meas}-xi_{gen}"); 
     histo3->SetMarkerStyle(22);
     histo3->SetMarkerSize(0.9);
     histo3->Draw();
     tree_->Draw("((Epz_PF_plus/7000)-xi_gen):(Epz_PF_plus/7000)>>histo4","Epz_PF_minus > Epz_PF_plus && xi_gen <0.2","goff");
     histo4->SetMarkerStyle(21);
     histo4->SetMarkerColor(kRed);
     histo4->SetMarkerSize(0.7);
     histo4->GetXaxis()->SetTitle("xi_measured");
     histo4->Draw("SAMES");    
     leg->Draw();
   }
   if (KindOfData==2){
     PomPyt->cd();
     TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
     TProfile2D *histo=new TProfile2D("histo","(xi_measured-xi_gen)/xi_gen Vs xi_measured",20,0,0.15,36,-1.8,1.8);
     TProfile2D *histo2=new TProfile2D("histo2","",20,0,0.15,36,-1.8,1.8);
     TProfile2D *histo3=new TProfile2D("histo3","(xi_measured-xi_gen) Vs xi_measured",20,0,0.1,36,-0.08,0.08);
     TProfile2D *histo4=new TProfile2D("histo4","xi resolution (absolute value)",20,0,0.1,36,-0.08,0.08);
     c1->Divide(1,2);
     c1->cd(1);
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     tree_->Draw("((Epz_PF_minus/7000)-xi_gen)/(Epz_PF_minus/7000):(Epz_PF_minus/7000)>>histo","Epz_PF_minus < Epz_PF_plus && xi_gen <0.1","goff");
     histo->GetXaxis()->SetTitle("xi_measured");
     histo->GetYaxis()->SetTitle("#frac{xi_{meas}-xi_{gen}}{xi_{meas}}");
     histo->SetBins(20,0,0.15);
     histo->GetYaxis()->SetRangeUser(-1,1);
     histo->GetYaxis()->SetTitleSize(0.05);
     histo->SetTitle("(xi_meas-xi_gen)/xi_meas Vs xi_meas");
     histo->Draw();
     tree_->Draw("((Epz_PF_plus/7000)-xi_gen)/(Epz_PF_minus/7000):(Epz_PF_plus/7000)>>histo2","Epz_PF_minus > Epz_PF_plus && xi_gen <0.1","goff");
     histo2->SetMarkerColor(kRed);
     histo2->SetLineColor(kRed);     
     histo2->GetXaxis()->SetTitle("xi_measured");
     histo2->SetBins(20,0,0.15);
     histo2->Draw("SAMES");    
     leg = new TLegend(0.2,0.6,0.4,0.89);
     leg->AddEntry(histo,"Epz plus","lp");
     leg->AddEntry(histo2,"Epz minus","lp");
     leg->SetBorderSize(0);
     leg->SetTextSize(0.06);  
     leg->Draw();
     c1->cd(2);
      gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
      tree_->Draw("((Epz_PF_minus/7000)-xi_gen):(Epz_PF_minus/7000)>>histo3","Epz_PF_minus < Epz_PF_plus && xi_gen <0.1","goff");
     histo3->GetXaxis()->SetTitle("xi_measured");
     histo3->SetBins(20,0,0.15);
     histo3->GetYaxis()->SetRangeUser(-0.04,0.04);
     histo3->GetYaxis()->SetTitle("xi_{meas}-xi_{gen}");
     histo3->GetYaxis()->SetTitleSize(0.05);
     histo3->SetTitle("(xi_meas-xi_gen) Vs xi_meas");
     histo3->Draw();
     tree_->Draw("((Epz_PF_plus/7000)-xi_gen):(Epz_PF_plus/7000)>>histo4","Epz_PF_minus > Epz_PF_plus && xi_gen <0.1","goff");
     histo4->SetMarkerColor(kRed);
     histo4->SetLineColor(kRed);    
     histo4->SetBins(20,0,0.15);
     histo4->GetYaxis()->SetRangeUser(-0.04,0.04);
     histo4->Draw("SAMES");    
     leg->Draw();
   }

   if (KindOfData==3){
     PomPyt->cd();
     TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
     float ratio[20];
     float x[20];
     float y_err[20];
     float x_err[20];
     //c1->Divide(1,2);
     //c1->cd(1);
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     for (int i=0;i<20;i++){
       float down=(0.2/20.)*i;
       float up=(0.2/20.)*(i+1);
       stringstream stringa_down;
       stringa_down<<down;
       stringstream stringa_up;
       stringa_up<<up;
       string stringa=stringa_down.str()+"<(Epz_PF_plus/7000) && (Epz_PF_plus/7000)<"+stringa_up.str()+" && "+stringa_down.str()+"<xi_gen && xi_gen<"+stringa_up.str()+" && Epz_PF_minus > Epz_PF_plus";
       string stringa2=stringa_down.str()+"<(Epz_PF_plus/7000) && (Epz_PF_plus/7000)<"+stringa_up.str()+" && Epz_PF_minus > Epz_PF_plus";
       string stringa4=stringa_down.str()+"<(Epz_PF_minus/7000) && (Epz_PF_minus/7000)<"+stringa_up.str()+" && Epz_PF_minus < Epz_PF_plus";                     
       string stringa3=stringa_down.str()+"<(Epz_PF_minus/7000) && (Epz_PF_minus/7000)<"+stringa_up.str()+" && "+stringa_down.str()+"<xi_gen && xi_gen <"+stringa_up.str()+" && Epz_PF_minus < Epz_PF_plus";
       //cout<<stringa<<endl;
       //cout<<stringa2<<endl;
       //cout<<stringa3<<endl;
       //cout<<stringa4<<endl;
       int number=tree_->Draw("(Epz_PF_plus/7000)",stringa.c_str(),"goff");        
       int number2=tree_->Draw("(Epz_PF_plus/7000)",stringa2.c_str(),"goff");
       int number3=tree_->Draw("(Epz_PF_minus/7000)",stringa3.c_str(),"goff");
       int number4=tree_->Draw("(Epz_PF_minus/7000)",stringa4.c_str(),"goff");
       //number3=number4=0;
       x[i]=down+(up-down)/2;
       if ((float)number4+(float)number2>0) ratio[i]=((float)number+(float)number3)/((float)number4+(float)number2);
       else ratio[i]=0;
       double a=((float)number+(float)number3);
       double b=((float)number4+(float)number2);
       if (b>0) y_err[i]=pow((a/(b*b))*(1+(a/b)),0.5);
       else y_err[i]=0;
       cout<<y_err[i]<<endl;
       x_err[i]=0;
       cout<<a<<" /"<<b<<" -> ratio "<<ratio[i]<<endl;
       stringa_down.str("");
       stringa_up.str("");       
     }
     TGraphErrors *plus=new TGraphErrors(20,x,ratio,x_err,y_err);
     plus->SetMarkerColor(kBlack);
     plus->SetMarkerStyle(22);     
     plus->Draw("AP");
     plus->SetTitle("Purity");
     plus->GetYaxis()->SetTitle("#frac{events_{gen_{bin}}}{events_{meas}}");
     plus->GetXaxis()->SetTitle("xi_interval");
   }

   if (KindOfData==4){
     PomPyt->cd();
     TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
     c1->Divide(1,2);
     c1->cd(1);
     TH1F *histo=new TH1F("histo","x_gen distribution",20,0,0.1);
     TH1F *histo2=new TH1F("histo2","x_gen distribution",20,0,0.1);
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);

     tree_->Draw("xi_gen>>histo","xi_gen <0.2","goff");
     histo->GetXaxis()->SetTitle("xi_gen");
     histo->Draw();    
     //leg = new TLegend(0.2,0.6,0.4,0.89);
     //leg->AddEntry(histo,"Epz plus","l");
     //leg->AddEntry(histo2,"Epz minus","l");
     //leg->SetBorderSize(0);
     //leg->SetTextSize(0.06);  
     //leg->Draw();

     c1->cd(2);
     TH1F *histo3=new TH1F("histo3","x_meas distribution",20,0,0.1);
     TH1F *histo4=new TH1F("histo4","x_meas distribution",20,0,0.1);
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     tree_->Draw("(Epz_PF_minus/7000)>>histo3","xi_gen <0.2 && (Epz_PF_minus<Epz_PF_plus)","goff");
     tree_->Draw("(Epz_PF_plus/7000)>>histo4","xi_gen <0.2 && (Epz_PF_minus>Epz_PF_plus)","goff");
     //histo3->SetLineColor(kRed);     
     histo3->Add(histo4);
     histo3->Draw();    
     //leg = new TLegend(0.2,0.6,0.4,0.89);
     //leg->AddEntry(histo3,"Epz plus","l");
     //leg->AddEntry(histo4,"Epz minus","l");
     //leg->SetBorderSize(0);
     //leg->SetTextSize(0.06);  
     //leg->Draw();
     c1->cd(2);     
   }

   if (KindOfData==5){
     PomPyt->cd();
     TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
     TH2F *HFZero=new TH2F("HFZero","(xi_measured-xi_gen)/xi_meas Vs xi_measured",20,0,0.1,36,-4,4);
     TH2F *CastorZero=new TH2F("CastorZero","(xi_measured-xi_gen)/xi_meas Vs xi_measured",20,0,0.1,36,-4,4);
     TH2F *ZDCZero=new TH2F("ZDCZero","(xi_measured-xi_gen)/xi_meas Vs xi_measured",20,0,0.1,36,-4,4);

     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     tree_->Draw("((Epz_PF_minus/7000)-xi_gen)/(Epz_PF_minus/7000):(Epz_PF_minus/7000)>> HFZero","Epz_PF_minus < Epz_PF_plus  && xi_gen <0.2 && sumEHF_minus==0");
     tree_->Draw("((Epz_PF_minus/7000)-xi_gen)/(Epz_PF_minus/7000):(Epz_PF_minus/7000)>> CastorZero","Epz_PF_minus < Epz_PF_plus  && xi_gen <0.2 && sumECastor_minus==0");
     tree_->Draw("((Epz_PF_minus/7000)-xi_gen)/(Epz_PF_minus/7000):(Epz_PF_minus/7000)>> ZDCZero","Epz_PF_minus < Epz_PF_plus  && xi_gen <0.2 && sumEZDC_minus==0");
     HFZero->GetXaxis()->SetTitle("xi_measured");
     HFZero->SetMarkerStyle(22);
     HFZero->SetMarkerSize(0.9);
     HFZero->SetMarkerColor(kRed);
     HFZero->Draw();
     CastorZero->SetMarkerStyle(23);
     CastorZero->SetMarkerSize(0.9);
     CastorZero->SetMarkerColor(kBlue);
     CastorZero->Draw("SAMES");
     ZDCZero->SetMarkerStyle(24);
     ZDCZero->SetMarkerSize(0.9);
     ZDCZero->SetMarkerColor(kGreen);
     ZDCZero->Draw("SAMES");
     leg = new TLegend(0.2,0.6,0.4,0.89);
     leg->AddEntry(HFZero,"sumHF=0","p");
     leg->AddEntry(CastorZero,"sumCastor=0","p");
     leg->AddEntry(ZDCZero,"sumZDC=0","p");
     leg->SetBorderSize(0);
     leg->SetTextSize(0.04);  
     leg->Draw();
   }

   if (KindOfData==7){
     PomPyt->cd();
     TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     c1->Divide(2,2);
     c1->cd(1);
     TH1F *histo2=new TH1F("histo2","x_gen distribution, when 0 < x_meas < 0.01",20,0,0.1);
     tree_->Draw("xi_gen","0 <xi_gen && xi_gen<0.01");     
   }

   if (KindOfData==6){
     PomPyt->cd();
     TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
     float ratio[20];
     float x[20];
     float y_err[20];
     float x_err[20];
     //c1->Divide(1,2);
     //c1->cd(1);
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     for (int i=0;i<20;i++){
       float down=(0.2/20.)*i;
       float up=(0.2/20.)*(i+1);
       stringstream stringa_down;
       stringa_down<<down;
       stringstream stringa_up;
       stringa_up<<up;
       string stringa=stringa_down.str()+"<(Epz_PF_plus/7000) && (Epz_PF_plus/7000)<"+stringa_up.str()+" && Epz_PF_minus > Epz_PF_plus";
       string stringa2=stringa_down.str()+"<xi_gen && xi_gen <"+stringa_up.str();
       string stringa3=stringa_down.str()+"<(Epz_PF_minus/7000) && (Epz_PF_minus/7000)<"+stringa_up.str()+" && Epz_PF_minus < Epz_PF_plus";
       int number=tree_->Draw("(Epz_PF_plus/7000)",stringa.c_str(),"goff");        
       int number2=tree_->Draw("(Epz_PF_plus/7000)",stringa2.c_str(),"goff");
       int number3=tree_->Draw("(Epz_PF_plus/7000)",stringa3.c_str(),"goff");
       //cout<<stringa<<endl;
       //cout<<stringa2<<endl;
       //cout<<stringa3<<endl;
       x[i]=down;
       ratio[i]=((float)number+(float)number3)/((float)number2);
       double a=((float)number+(float)number3);
       double b=((float)number2);
       if (b>0) y_err[i]=pow((a/(b*b))*(1+(a/b)),0.5);
       else y_err[i]=0;
       cout<<y_err[i]<<endl;
       x_err[i]=0;
       cout<<a<<" /"<<b<<" -> ratio "<<ratio[i]<<endl;
       stringa_down.str("");
       stringa_up.str("");       
     }
     TGraphErrors *plus=new TGraphErrors(20,x,ratio,x_err,y_err);
     plus->SetMarkerColor(kBlack);
     plus->SetMarkerStyle(22);     
     plus->Draw("AP");
     plus->SetTitle("Efficiency");
     plus->GetYaxis()->SetTitle("#frac{events_{meas}}{events_{gen}}");
     plus->GetXaxis()->SetTitle("xi_interval");
   }
 }
 if (type==9){
   PomPyt->cd();
    TH1F *histo=new TH1F("histo","xi efficiency",20,0,0.2);
    TH1F *histo2=new TH1F("histo2","xi efficiency",20,0,0.2);
    TH1F *Division=new TH1F("Division","xi efficiency",20,0,0.2);
    tree_->Draw("xi_gen>>histo");
    tree_->Draw("xi_gen>>histo2","sumEHF_minus==0 || sumEHF_plus==0 && (etaWeightedOnEnergy<-2 || etaWeightedOnEnergy>2) && (Epz_PF_minus-Epz_PF_plus <-700 || Epz_PF_minus-Epz_PF_plus >700)"); 
    Division->Divide(histo2,histo,1,1);
    Division->Draw();
 }

 if (type==10){
   
   if (KindOfData==1){
     PomPyt->cd();
     TH2F *D=new TH2F("D","(Epz_minus-Epz_plus Vs etaWeighted)",32,-4,4,20,-3000,3000);
     tree_->Draw("(Epz_PF_plus-Epz_PF_minus):etaWeightedOnEnergy>>D","","goff");
     Pythia->cd();
     TH2F *ND=new TH2F("ND","(Epz_minus-Epz_plus Vs etaWeighted)",32,-4,4,20,-3000,3000);
     tree_->Draw("(Epz_PF_plus-Epz_PF_minus):etaWeightedOnEnergy>>ND","","goff");   
     TH2F *Division=new TH2F("Division","(Epz_minus-Epz_plus Vs etaWeighted)",32,-4,4,20,-3000,3000);      
   }

   if (KindOfData==2){
     PomPyt->cd();
     TH2F *D=new TH2F("D","( (sumHF+ - sumHF-) Vs etaWeighted)",32,-4,4,20,-2000,2000);
     tree_->Draw("(sumEHF_plus-sumEHF_minus):etaWeightedOnEnergy>>D","","goff");
     Pythia->cd();  
     TH2F *ND=new TH2F("ND","( (sumEHF_plus-sumEHF_minus) Vs etaWeighted)",32,-4,4,20,-2000,2000);  
     tree_->Draw("(sumEHF_plus-sumEHF_minus):etaWeightedOnEnergy>>ND","","goff");    
     TH2F *Division=new TH2F("Division","(Epz_minus-Epz_plus Vs etaWeighted)",32,-4,4,20,-2000,2000); 
   }

  if (KindOfData==3){
     PomPyt->cd();
     TH2F *D=new TH2F("D","( (sumHF+ - sumHF-)/(sumHF+ + sumHF-) Vs etaWeighted)",32,-4,4,20,-2,2);
     tree_->Draw("(sumEHF_plus-sumEHF_minus)/(sumEHF_plus+sumEHF_minus):etaWeightedOnEnergy>>D","","goff");
     Pythia->cd(); 
     TH2F *ND=new TH2F("ND","( (sumEHF_plus-sumEHF_minus)/(sumEHF_plus+sumEHF_minus) Vs etaWeighted)",32,-4,4,20,-2,2);
     tree_->Draw("(sumEHF_plus-sumEHF_minus)/(sumEHF_plus+sumEHF_minus):etaWeightedOnEnergy>>ND","","goff");    
     TH2F *Division=new TH2F("Division","( (sumEHF_plus-sumEHF_minus)/(sumEHF_plus+sumEHF_minus) Vs etaWeighted)",32,-4,4,20,-2,2);   
   }

  if (KindOfData==4){
    PomPyt->cd();
    TH2F *D=new TH2F("D","( (energyTot+ - energyTot-) Vs etaWeighted)",32,-4,4,20,-2000,2000);
    tree_->Draw("(energyTot_plus-energyTot_minus):etaWeightedOnEnergy>>D","","goff");
    Pythia->cd(); 
    TH2F *ND=new TH2F("ND","( (energyTot_plus-energyTot_minus) Vs etaWeighted)",32,-4,4,20,-2000,2000);
    tree_->Draw("(energyTot_plus-energyTot_minus):etaWeightedOnEnergy>>ND","","goff");    
    TH2F *Division=new TH2F("Division","( (energyTot_plus-energyTot_minus) Vs etaWeighted)",32,-4,4,20,-2000,2000);   
   }  

  if (KindOfData==5){
    PomPyt->cd();
     TH2F *D=new TH2F("D","( (HF- - HF+)/max(HF+-) Vs etaWeighted)",32,-4,4,40,-1,1.1);
     TH2F *D2=(TH2F*)D->Clone("D2");
     tree_->Draw("(sumEHF_minus-sumEHF_plus)/(sumEHF_minus):etaWeightedOnEnergy>>D","sumEHF_plus<sumEHF_minus","goff");
     tree_->Draw("(sumEHF_minus-sumEHF_plus)/(sumEHF_plus):etaWeightedOnEnergy>>D2","sumEHF_plus>sumEHF_minus","goff");
     D->Add(D2);
     Pythia->cd(); 
     TH2F *ND=new TH2F("ND","( (energyTot_plus-energyTot_minus) Vs etaWeighted)",32,-4,4,40,-1,1.1);
     TH2F *ND2=(TH2F*)D->Clone("ND2");
     tree_->Draw("(sumEHF_minus-sumEHF_plus)/(sumEHF_minus):etaWeightedOnEnergy>>ND","sumEHF_plus<sumEHF_minus","goff");  
     tree_->Draw("(sumEHF_minus-sumEHF_plus)/(sumEHF_plus):etaWeightedOnEnergy>>ND2","sumEHF_plus>sumEHF_minus","goff");
     ND->Add(ND2);    
     TH2F *Division=new TH2F("Division","( (HF+ -HF-)/max(HF+-)  Vs etaWeighted)",32,-4,4,40,-1,1.1);   
   }  
   
   TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
   gStyle->SetOptStat("e");
   gStyle->SetFillColor(0);
   D->GetXaxis()->SetTitle("Eta");
   D->SetMarkerColor(kRed);  
   D->SetMarkerSize(1);
   D->SetMarkerColor(632);
   D->SetMarkerStyle(3);   
   D->Draw();
   ND->SetMarkerColor(kBlack);
   ND->SetMarkerSize(1);
   ND->SetMarkerStyle(3);       
   ND->Draw("SAME");    

   TCanvas *c2= new TCanvas("c2","c2",400,20,1200,800);
   gStyle->SetPaintTextFormat("4.2f"); 
  
   Division->Divide(D,ND,1,1);
   Division->SetMarkerSize(0.8);
   Division->Draw("TEXT");       
 
 }

 if (type==11){
     cout<<"Retreving the rootupla from castor...wait a bit..."<<endl;
   TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/ZetaSkim.root");  
   if (KindOfData==1){
     TH1F *Mass=new TH1F("Mass","Invariant Mass Z->ee",200,60,120);
     tree_->Draw("InvariantMass>>Mass","","goff");
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     Mass->GetXaxis()->SetTitle("Mee [GeV]");
     Mass->Draw();
   }
   if (KindOfData==2){
     TH1F *Mass=new TH1F("Mass","Invariant Mass Z->ee",200,60,120);
     TH1F *Mass2=new TH1F("Mass2","Invariant Mass Z->ee",200,60,120);
     gPad->SetLogy(1);
     tree_->Draw("InvariantMass>>Mass","","goff");
     tree_->Draw("InvariantMass>>Mass2","sumEHF_minus==0 || sumEHF_plus==0","goff");
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     Mass->GetXaxis()->SetTitle("Mee [GeV]");
     Mass->Draw();
     Mass2->SetLineColor(kRed);
     Mass2->Draw("SAMES");
   }
 }
  
  if (type==12){
     cout<<"Retreving the rootupla from castor...wait a bit..."<<endl;
   TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/JPsiSkim.root");  
   if (KindOfData==1){
     TH1F *Mass=new TH1F("Mass","Invariant Mass X->ee",200,0,20);
     tree_->Draw("InvariantMass>>Mass","","goff");
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     Mass->GetXaxis()->SetTitle("Mee [GeV]");
     Mass->Draw();
   }
   if (KindOfData==2){
     TH1F *Mass=new TH1F("Mass","Invariant Mass X->ee",200,0,20);
     TH1F *Mass2=new TH1F("Mass2","Invariant Mass X->ee",200,0,20);
     gPad->SetLogy(1);
     tree_->Draw("InvariantMass>>Mass","","goff");
     tree_->Draw("InvariantMass>>Mass2","sumEHF_minus==0 || sumEHF_plus==0","goff");
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     Mass->GetXaxis()->SetTitle("Mee [GeV]");
     Mass->Draw();
     Mass2->SetLineColor(kRed);
     Mass2->Draw("SAMES");
   }
 }

  if (type==13){
     cout<<"Retreving the rootupla from castor...wait a bit..."<<endl;
   TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/MB.root");  
   if (KindOfData==1){
     TH1F *Mass=new TH1F("Mass","Invariant Mass MinimumBias->ee",20,0,0.1);
     tree_->Draw("InvariantMass>>Mass","","goff");
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     Mass->GetXaxis()->SetTitle("Mee [GeV]");
     Mass->Draw();
   }
   if (KindOfData==2){
     TH1F *Mass=new TH1F("Mass","Invariant Mass MinimumBias->ee",20,0,1);
     TH1F *Mass2=new TH1F("Mass2","",20,0,1);
     gPad->SetLogy(1);
     tree_->Draw("InvariantMass>>Mass","","goff");
     tree_->Draw("InvariantMass>>Mass2","sumEHF_minus==0 || sumEHF_plus==0","goff");
     gStyle->SetOptStat("e");
     gStyle->SetFillColor(0);
     Mass->GetXaxis()->SetTitle("Mee [GeV]");
     Mass->Draw();
     Mass2->SetLineColor(kRed);
     Mass2->Draw("SAMES");
   }
   if (KindOfData==3){
     TFile *_file0 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/MB.root");
     _file0->cd();
     //gPad->SetLogy(1);  
     TF1 *gfit = new TF1("Gaussian","gaus",-3000,3000); // Create the fit function
     TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
     TH1F *D=new TH1F("D","(sumEHF_plus-sumEHF_minus)",50,-3000,3000);
     gStyle->SetOptStat("emmrr");
     gStyle->SetOptFit(1111);     
     gStyle->SetFillColor(0);
     tree_->Draw("(sumEHF_plus-sumEHF_minus)>>D","","goff");
     D->GetXaxis()->SetTitle("Eta");
     D->SetMarkerColor(kRed);  
     D->SetMarkerSize(1);
     D->SetMarkerColor(632);
     D->SetMarkerStyle(3);   
     D->Draw();
     D->Fit("Gaussian","RQ"); 
     D->Draw("SAMES");
     TCanvas *c2= new TCanvas("c2","c2",400,20,1200,800);
     c2->Divide(1,2);
     c2->cd(1);
     TF1 *gfit = new TF1("gfit","[0]*2.7172^[0]",1,3000); // Create the fit function
     TH1F *plus=new TH1F("plus","(sumEHF_plus)",200,0,3000); gStyle->SetOptStat("emmrr");
     gStyle->SetOptFit(1111);     
     gStyle->SetFillColor(0);
     tree_->Draw("(sumEHF_plus)>>plus","","goff");
     plus->GetXaxis()->SetTitle("Eta");
     plus->SetMarkerColor(kRed);  
     plus->SetMarkerSize(1);
     plus->SetMarkerColor(632);
     plus->SetMarkerStyle(3);   
     plus->Draw();
     plus->Fit(gfit); 
     gfit->Draw("SAMES");
     c2->cd(2);
     //TF1 *gfit = new TF1("Gaussian","gaus",0,3000); // Create the fit function
     TH1F *minus=new TH1F("minus","(sumEHF_minus)",200,0,3000); gStyle->SetOptStat("emmrr");
     gStyle->SetOptFit(1111);     
     gStyle->SetFillColor(0);
     tree_->Draw("(sumEHF_minus)>>minus","","goff");
     minus->GetXaxis()->SetTitle("Eta");
     minus->SetMarkerColor(kRed);  
     minus->SetMarkerSize(1);
     minus->SetMarkerColor(632);
     minus->SetMarkerStyle(3);   
     minus->Draw();
     minus->Fit("Gaussian","RQ"); 
     //minus->Draw("SAMES");     
   }
  }

  if (type==14){

    if (PomPytHisto)  delete PomPytHisto; 
    if (PomPytHisto_plus) delete PomPytHisto_plus;
    if (PomPytScaled) delete PomPytScaled;
    if (ZDataEvent) delete ZDataEvent ;
    if (ZDataEvent_plus) delete ZDataEvent_plus ;
    if (PythiaHisto) delete  PythiaHisto;
    if (PythiaHisto_plus) delete PythiaHisto_plus ;
    if (PythiaScaled) delete PythiaScaled ;

    PomPyt->cd();
    int dummy;
    double crossSectionMC_ND=1300.;
    double TotalNumberOfEvent_MC_ND=2471816.;
    double TotalNumberOfEvent_Data=33074402.;

    double fractionOfEvents_MC_ND=11304./TotalNumberOfEvent_MC_ND;
    double fractionOfJobs=307./307.;   //To be improved! Check the ratio events processed/ event total  * Skim_luminosity
    double fractionOfJobs_2=754./808.;
    double skim_lumi=0;
    double skim_lumi_2=3.17;
    double real_skim_lumi=(skim_lumi*fractionOfJobs)+(skim_lumi_2*fractionOfJobs_2);    
    cout<<"Real Skim lumi is "<<real_skim_lumi<<endl;  

    double skim_lumi_MC_ND=TotalNumberOfEvent_MC_ND/crossSectionMC_ND;
    double real_skim_lumi_MC_ND=skim_lumi_MC_ND*fractionOfEvents_MC_ND;  
    cout<<"Lumi MC Non Diffractive is "<<real_skim_lumi_MC_ND<<endl;
    cout<<"Calculate the fraction of events in bin 0.00-0.03 and the corresponding cross section"<<endl;

    double PomPyt_cross_section=109.; //pb
    double PomPyt_total_events=3600;
    double PomPyt_lumi=PomPyt_total_events/PomPyt_cross_section;
    cout<<"Lumi MC Diffractive is "<<PomPyt_lumi<<endl;
    cout<<"Calculate the fraction of events in bin 0.00-0.03 and the corresponding cross section"<<endl;

    //Diffractive Montecarlo
    int size=treeMCGen_->GetEntries();
    const int numberOfBins=3;
    const double interval=0.01;
    double fraction[numberOfBins];
    for (int i=0; i < numberOfBins; i++){
      stringstream stringaup,stringadown;
      double down=i*interval;
      double up=(i+1)*interval;
      stringaup<<up;
      stringadown<<down;
      string cut="xi_gen>"+stringadown.str()+" && xi_gen < "+stringaup.str();   
      double number=treeMCGen_->Draw("xi_gen",cut.c_str(),"goff"); 
      double cs=(number/(double)size)* PomPyt_cross_section;
      cout<<cut<<" has a cross Section of "<<cs<<endl;
      fraction[i]=cs;
    }

    TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
    PomPytHisto=new TH1F("PomPytHisto","Distribution of events in diffractive MC in bins of xsi",20,0,0.2);
    PomPytHisto_plus=(TH1F*) PomPytHisto->Clone();
    PomPytHisto_plus->SetName("PomPytHisto_plus");
    PomPytHisto_plus->Reset(); 
    //TH1F *MCDifEvent=new TH1F("MCDifEvent","Distribution of events in diffractive MC in bins of xsi",numberOfBins,0,numberOfBins*interval);
   if (KindOfData==2){
    tree_->Draw("(Epz_PF_minus/7000)>>PomPytHisto","sumEHF_minus==0 && (Epz_PF_minus < Epz_PF_plus)","goff"); 
    tree_->Draw("(Epz_PF_plus/7000)>>PomPytHisto_plus","sumEHF_plus==0 && (Epz_PF_minus > Epz_PF_plus)","goff"); 
   }
   if (KindOfData==1){
    tree_->Draw("(Epz_PF_minus/7000)>>PomPytHisto","(Epz_PF_minus < Epz_PF_plus)","goff"); 
    tree_->Draw("(Epz_PF_plus/7000)>>PomPytHisto_plus","(Epz_PF_minus > Epz_PF_plus)","goff"); 
   }   
   cout << " before add " << endl; 
    PomPytHisto->Add(PomPytHisto_plus,1);
    PomPytHisto->Draw();
    double ratio2=real_skim_lumi/PomPyt_lumi;
    PomPytScaled=(TH1F*) PomPytHisto->Clone();
    PomPytScaled->SetName("PomPytScaled");
    PomPytScaled->Reset(); 
    cout<<"Ratio Diffractive / Data "<<ratio2<<endl;  
    for (int i=1; i<21; i++){                          //Normalizing pythia and realdata
      double pythiaB=PomPytHisto->GetBinContent(i)*ratio2;
      PomPytScaled->SetBinContent(i,pythiaB);
  }  

  //Z real data
    ZeeData->cd();
  double real_data_events=tree_->GetEntries();
  cout<<"Z events #"<<real_data_events<<endl;
  TCanvas *c2= new TCanvas("c2","c2",400,20,1200,800);
  ZDataEvent=(TH1F*) PomPytHisto->Clone();
  ZDataEvent->SetName("ZDataEvent");
  ZDataEvent->Reset();  
  ZDataEvent_plus=(TH1F*) PomPytHisto->Clone();
  ZDataEvent_plus->SetName("ZDataEvent_plus");
  ZDataEvent_plus->Reset(); 

  if (KindOfData==1){
  tree_->Draw("(Epz_PF_minus/7000)>>ZDataEvent","RunNumber<145762 && (Epz_PF_minus < Epz_PF_plus)","goff");
  tree_->Draw("(Epz_PF_plus/7000)>>ZDataEvent_plus","RunNumber<145762 && (Epz_PF_minus > Epz_PF_plus)","goff");
  }

  if (KindOfData==2){
  tree_->Draw("(Epz_PF_minus/7000)>>ZDataEvent","RunNumber<145762 && sumEHF_minus==0 && (Epz_PF_minus < Epz_PF_plus)","goff");
  tree_->Draw("(Epz_PF_plus/7000)>>ZDataEvent_plus","RunNumber<145762 && sumEHF_plus==0 && (Epz_PF_minus > Epz_PF_plus)","goff");
  }
 
  ZDataEvent->Add(ZDataEvent_plus,1); 
  ZDataEvent->Draw();
 
  //Pythia
  TCanvas *c3= new TCanvas("c3","c3",400,20,1200,800);
  Pythia->cd();
  double pythia_events=tree_->GetEntries();
  cout<<"pythia events #"<<pythia_events<<endl;
  PythiaHisto=(TH1F*) PomPytHisto->Clone();
  PythiaHisto->SetName("PythiaHisto");
  PythiaHisto->Reset();  
  PythiaHisto_plus=(TH1F*) PomPytHisto->Clone();
  PythiaHisto_plus->SetName("PythiaHisto_plus");
  PythiaHisto_plus->Reset();  
  if (KindOfData==1){
  tree_->Draw("(Epz_PF_minus/7000)>>PythiaHisto","(Epz_PF_minus < Epz_PF_plus)","goff");
  tree_->Draw("(Epz_PF_plus/7000)>>PythiaHisto_plus","(Epz_PF_minus > Epz_PF_plus)","goff");
  }
  if (KindOfData==2){
  tree_->Draw("(Epz_PF_minus/7000)>>PythiaHisto","sumEHF_minus==0 && (Epz_PF_minus < Epz_PF_plus)","goff");
  tree_->Draw("(Epz_PF_plus/7000)>>PythiaHisto_plus","sumEHF_plus==0 && (Epz_PF_minus > Epz_PF_plus)","goff");
  }
  PythiaHisto->Add(PythiaHisto_plus,1);
  Double_t ratio=real_skim_lumi/real_skim_lumi_MC_ND;
  PythiaScaled=(TH1F*) PomPytHisto->Clone();
  PythiaScaled->SetName("PythiaScaled");
  PythiaScaled->Reset(); 
  cout<<"Ratio "<<ratio<<endl;  
  for (int i=1; i<21; i++){                          //Normalizing pythia and realdata
  double pythiaB=PythiaHisto->GetBinContent(i)*ratio;
  PythiaScaled->SetBinContent(i,pythiaB);
  }  
  gStyle->SetOptStat("e");
  gStyle->SetFillColor(0);
  ZDataEvent->SetMarkerStyle(22); 
  ZDataEvent->SetMarkerSize(1);
  PythiaScaled->SetLineColor(kRed);
  ZDataEvent->Draw("EP"); 
  if (KindOfData==1) ZDataEvent->SetTitle("Z->ee data distribution Vs and MC diffractive and non Diffractive");
  if (KindOfData==2) ZDataEvent->SetTitle("Z->ee data distribution Vs and MC diffractive and non Diffractive, sum HF==0");
  ZDataEvent->GetXaxis()->SetTitle("xi_meas");
  PythiaScaled->Draw("SAMES");
  PomPytScaled->SetLineColor(kBlue);
  PomPytScaled->Draw("SAMES");

     leg = new TLegend(0.2,0.6,0.4,0.89);
     leg->AddEntry(ZDataEvent,"Data","p");
     leg->AddEntry(PythiaScaled,"Non Diffractive MC","l");
     leg->AddEntry(PomPytScaled,"Diffractive MC","l");
     leg->SetBorderSize(0);
     leg->SetTextSize(0.06);  
     leg->Draw();
  //PythiaScaled->Draw();
  //ZDataEvent->Draw("SAMES"); 
     //return;
  }

  if (type==15){
    
        TCanvas *c1= new TCanvas("c1","c1",400,20,1200,800);
	gStyle->SetOptStat("e");
	gStyle->SetFillColor(0);
	c1->Divide(1,3);
	c1->cd(1);
	TH1F *Epz_minus=new TH1F("Epz_minus","Distribution of xsi_meas",50,0,1);
	TH1F *Epz_minus2=(TH1F*) Epz_minus->Clone();
	Epz_minus2->SetName("Epz_minus2");
	TH1F *Epz_minus3=(TH1F*) Epz_minus->Clone();
	Epz_minus3->SetName("Epz_minus3");	
	TFile *_file1 = TFile::Open("rfio:/castor/cern.ch/user/m/marone/outputCRAB/Diffractive/Final_Skim/ZetaSkim.root");
	tree_->Draw("(Epz_PF_minus/7000)>>Epz_minus","(Epz_PF_minus/7000) <0.2 && (RunNumber>132440 && RunNumber<144114)");
	//Epz_minus->getXaxis()->SetTitle("xi_meas");	
	Epz_minus->Draw();
	c1->cd(2);
	tree_->Draw("(Epz_PF_minus/7000)>>Epz_minus2","(Epz_PF_minus/7000) <0.2 && (RunNumber>144115 && RunNumber<148058)");
	//Epz_minus2->getXaxis()->SetTitle("xi_meas");	
	//Epz_minus2->Draw();
	c1->cd(3);
	tree_->Draw("(Epz_PF_minus/7000)>>Epz_minus3","(Epz_PF_minus/7000) <0.2 && (RunNumber>148059 && RunNumber<149442)");
	//Epz_minus->getXaxis()->SetTitle("xi_meas");	
	//Epz_minus3->Draw();
  }

  //deleting the object

  
  return;
}
