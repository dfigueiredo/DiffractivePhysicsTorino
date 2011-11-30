#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLegend.h>
#include "string.h"
#include <iomanip>
#include <sstream>
#include "NCutil.C"
#include <iostream>
#include <fstream>
#include <string>
#include "tdrstyle.C"
#include <algorithm>

TH1F *Vtx_Chi2;
Float_t  sigma;
Float_t Chi2;
Float_t Chi2err;
Float_t  errsigma;

 
TH1F *Nvtx_cor[15];
TH1F *Nvtx_No_cor[15];
TFile *f;
TFile *fc;
TFile *fc_MC;
TH1F *Dat_all_Lumi;
TH1F *NTriggers;
TH1F *BxLumi;
TGraphErrors *RatFit;
Float_t VtxMult_Eff[20]; 

char DataInputFile[100]; 
char hname[100]; 
char CMSPrel[100]; 

// Parameter to decide how to run Efficiency and the file name
// Values read in "input_card.txt"

/*
string line;
string NameFile;
char DataFile[100];
char MigrationFile[100];
char arr[100];
Float_t Sigma;   // = 0.051;
Float_t BlindLimit;  // = 0.05; // minimum distance to check merging of 3 vtx 
Int_t Draw; 
Int_t SelNDOF;
bool RunListF;  // run only on selected runs
bool LumiCorF; // use lumicorrection
bool DAV; // for DAV files
*/

Int_t Z_limit = 10 ;
Float_t VtxQualityLimit = 0.1; // 0.1 = No use

TH1F *LumiBin[LumBin];
TH1F *Vtx_Sigma;

Int_t vertex(Int_t vtx, Int_t FlagScale=1){
  

  TH1F *Eff_corr;
  char hname[100]; 
  char Effhname[100]; 



  Dat_all_Lumi =   (TH1F*)f->Get("Dat_all_Lumi");
  Int_t Nbinx = Dat_all_Lumi->GetNbinsX();
  
  Float_t AllEvt = Dat_all_Lumi->Integral();
  // cout << " Total number of Events = " << AllEvt << endl;
  
  
  gDirectory->Delete("RatFit");
  
  //  TH1F *RatFit = new TH1F("RatFit","RatFit",1000,0.,0.7);
  //Read the luminosity bins
  
  for (Int_t N=1;N<=LumBin; N++){
    sprintf(hname,"LumiBin%i",N);
    LumiBin[N] = (TH1F*)f->Get(hname);
    AllEvt = LumiBin[N]->Integral();
    //      cout << " Number of Events in Lumi bin " << N << " = " << AllEvt << " with mean Lumi = " << LumiBin[N]->GetMean() << endl;
    }
  

  
  Int_t   BinConVtx;
  Float_t  ErrBinConVtx;
  Float_t  NewBinConVtx;
  Int_t BinConVtxp1;
  Float_t x[14];
  Float_t ex[14];
  Float_t y[14];
  Float_t ey[14];
  
  stringstream stringa1;
  stringstream stringam1;
  
  stringa1 << vtx;
  Int_t vtxm1 = vtx-1;
  stringam1 << vtxm1;
  
  string cut = "istlumiPerBX*6.37>0.05 && numberOfVertexes=="+stringa1.str();
  string title = "Instantaneous lumi per bx for events with "+stringa1.str()+" vxt";
  string name = "vxt"+stringa1.str();
  string fill = "istlumiPerBX*6.37>>"+name;
  string rat1_title = "Fraction of events with "+stringa1.str()+ " vertexes";  
  string rat1_name = stringam1.str()+ " PU Vtx";  
  string prob_title = "Probability of " +stringam1.str()+ " pile-up events (\sigma_{NSD} = 60 mb) ";  
  string probstr = "prob(x," +stringam1.str()+ ")";
  
  gDirectory->Delete("rat1");
  gDirectory->Delete("prob");
  gDirectory->Delete("pois1");
  gDirectory->Delete("Eff_corr");


  TH1F *rat1 =  NH1clone(rat1_name,rat1_title.c_str(),Dat_all_Lumi);


    if (vtx==10)
    { // 10 is a special case Vtx==1 && HF==0   
      sprintf(hname,"Vtx1_HF0");
      Nvtx_No_cor[vtx] =   (TH1F*)f->Get(hname); 

      if (eeF == 0)
	{   sprintf(hname,"Vtx1_HF0_MC");
	  Nvtx_No_cor[vtx] =   (TH1F*)fc_MC->Get(hname); 
	}

      Nvtx_cor[vtx] =  NH1clone(hname,hname,Dat_all_Lumi);
      sprintf(Effhname,"Eff_%iNvtx_MC",0);
      TH1F * Eff_corr = (TH1F*)fc_MC->Get(Effhname);
     }    
  else
    {
      sprintf(hname,"Nvtx%i_cor",vtx);
      Nvtx_cor[vtx] =  NH1clone(hname,hname,Dat_all_Lumi);

      // select as efficiency correction data  (MC_MigF ==0) or MC

      if (FlagScale==1) 
	{
	  if (MC_MigF == 0 ) 
	    {
	      sprintf(Effhname,"Eff_%iNvtx",vtx-1); // Analytic efficiency
	      TH1F * Eff_corr = (TH1F*)fc->Get(Effhname);
	    }
	  else 
	    {
	      
	      sprintf(Effhname,"Eff_%iNvtx_MC",vtx-1); // MC efficiency
	      TH1F * Eff_corr = (TH1F*)fc_MC->Get(Effhname);
	    }
	}

      // select as input points DATA  (eeF !=0) or MC

      if (eeF != 0) 
	{
	  sprintf(hname,"Vxt_Lumi%i",vtx);      
	  Nvtx_No_cor[vtx] =   (TH1F*)f->Get(hname);  //contain events with vtx vertices (1+PU)
	}
      else 
	{
	  sprintf(hname,"Vxt_Lumi%i_MC",vtx);      
	  Nvtx_No_cor[vtx] =   (TH1F*)fc_MC->Get(hname); 
	}

    }


  // Note: vxt is the total number of vertexes while Eff_corr refers to the pile-up
  // so it's necessary to subtract 1  
  // sprintf(hname,"Eff_%iNvtx",vtx-1);


  cout << "Opening Efficiency " << Effhname << endl;
  cout << "Input Plot " << hname << endl;

  /*
      if (MC_MigF == 0)
	{
	  TH1F * Eff_corr = (TH1F*)fc->Get(Effhname);
	  Nvtx_No_cor[vtx] =   (TH1F*)f->Get(hname);  //contain events with vtx vertices (1+PU)
	}
      else 
	{
	  TH1F * Eff_corr = (TH1F*)fc_MC->Get(Effhname);
	  Nvtx_No_cor[vtx] =   (TH1F*)fc_MC->Get(hname); 
	}
*/


      if (Eff_corr== 0 &&   (FlagScale==1) )
	{
	  cout << "Problem in opening the efficiency plot : " << Effhname << endl;
	  return(1);
	}
      if (Nvtx_No_cor[vtx] == 0)
	{
	  cout << "Problem in opening the data plot : " << hname << endl;
	  return(1);
	}


  if (FlagScale==1) 
    {
      Nvtx_cor[vtx]->Divide(Nvtx_No_cor[vtx],Eff_corr);
      if(vtx==30)
	{
	  rat1->Divide(Nvtx_cor[vtx], Nvtx_No_cor[1],1.,1.); 
	}
      else
	{
	  rat1->Divide(Nvtx_cor[vtx],Dat_all_Lumi,1.,1.); 
	}
    }
  else
    {
      rat1->Divide(Nvtx_No_cor[vtx],Dat_all_Lumi,1.,1.,"B"); 
    }


  RatFit = new TGraphErrors(14); 


  Int_t NLumi=14;
  Int_t M=0;
  for (Int_t N=2,; N<=NLumi;N++){
    x[N]=0;
    ex[N]=0;
    y[N]=0;
    ey[N]=0;
    //    cout << N << endl;
    if (rat1->GetBinContent(N)>0.)
      {
	x[N] = LumiBin[N]->GetMean();
	ex[N] = LumiBin[N]->GetMeanError();
	y[N] = rat1->GetBinContent(N);
	ey[N] = 1.*rat1->GetBinError(N);
	RatFit->SetPoint(N,x[N],y[N]);
	RatFit->SetPointError(N,ex[N],ey[N]);


      }
  }
  

  RatFit->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  RatFit->GetYaxis()->SetTitle("Fraction");

  //  NLogAxis(0,1);
  RatFit->SetMarkerColor(2);   
  RatFit->SetMarkerSize(1.);   
  RatFit->SetMarkerStyle(20);

  RatFit->Draw("p");

  //Initialize the Pois. Function

  if (vtx==10)  
    {
      TF1 *pois1 = new TF1("pois1",prob_vtx1,0.0,UpLim,2); // x in [0.1;0.6], 2 parameters
      pois1->SetParName(1,"Intercept:");

      //      TF1 *pois2 = new TF1("pois2",prob_vtx2,0.0,UpLim,2); // x in [0.1;0.6], 2 parameters
      //pois2->SetParName(1,"Intercept:");
      //pois2->SetParName(0,"Sigma");
      //pois2->SetParameter(0,0.05);
    }
  else
    {
    TF1 *pois1 = new TF1("pois1",prob_pois,0.0,UpLim,2); // x in [0.1;0.6], 2 parameters
    pois1->SetParName(1,"Pile-up");
    }
  pois1->SetParName(0,"Sigma");
  pois1->SetParameter(0,0.05);
  if (vtx !=10)  pois1->SetParameter(1,vtxm1);
  
  //Fix the number of vertexes
  if (vtx !=10) pois1->FixParameter(1,vtxm1);
  pois1->SetLineStyle(2);
  pois1->SetLineColor(1);
  pois1->SetLineWidth(0.4);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(00000);  

  //  Float_t llim[9] = {0.01,0.01,0.01,0.15,0.20,0.25,0.3,0.35,0.40};
  Float_t llim[12] = {0.015,0.015,0.015,0.2,0.25,0.3,0.35,0.40,0.45,0.,0.,0.};
   //Float_t llim[9] = {0.2};
   // Float_t ulim[9] = {0.4};
  // RatFit->Fit("pois1","LEM","SAME",0.1,0.6);

  //  RatFit->Fit("pois1","LEM","SAME",llim[vtx-1],UpLim);
RatFit->Fit("pois1","LEM","SAME",0.,UpLim);
   // RatFit->Fit("pois1","LEM","SAME",0.7,1.4);

  //   RatFit->Fit("pois1","I","SAME",0.05,0.4);  
  // RatFit->Fit("pois1","I","SAMES",0.,0.7);
     //  cout << "Chi2 = "<<  pois1->GetChiChisquare() << " NDOF = " << pois1->GetNDF() << endl;



  if (vtx==10) {
    //gStyle->SetOptFit(111111);
    //pois2->SetLineStyle(2);
    //pois2->SetLineColor(1);
    //pois2->SetLineWidth(0.4);
    // TH1F *RatFit2 = RatFit->Clone();
    //RatFit2->Draw("SAMEp");
    //RatFit->Fit("pois2","I","SAMES",0.08,0.61);
  }


  
  sigma = 1000*pois1->GetParameter(0);
  errsigma =  1000*pois1->GetParError(0);
  Chi2 = pois1->GetChisquare()/pois1->GetNDF();  
  // cout << pois1->GetNDF() << endl;
  Vtx_Sigma->SetBinContent(vtx,sigma);
  Vtx_Sigma->SetBinError(vtx,errsigma);
  Vtx_Chi2->SetBinContent(vtx,Chi2);
  sprintf(hname,"Residual for PU = %i",vtxm1);
  TH1F *Resid = NH1clone(hname,hname,rat1);
  TH1F *pippo = NH1clone("pippo","pippo",rat1);

  return;
  Float_t ResR = 0;
  pippo->Add(pois1,1.);
  for (Int_t N=2,; N<=NLumi;N++){

    y[N]=0;
    ey[N]=0;
    ResR = 0;

    y[N] = pow(rat1->GetBinContent(N)-pippo->GetBinContent(N),2);
    ey[N] = pow(1.*rat1->GetBinError(N),2);
    if (ey[N] !=0)
      ResR = sqrt(y[N]/ey[N]);
    Resid->SetBinContent(N,ResR);
    // cout << y[N] << " " << ey[N] << " " << y[N]/ey[N] << endl;

  }
  

  
  //  Resid->Add(pois1,-1.);
  // Resid->Add(rat1,1.);
  //  Resid->Divide(rat1);
  NHSetMarker(Resid,2,20,1.2);
  if (vtx==20) Res->cd(9);
  else  Res->cd(vtx);
  NLogAxis(0,0);
  Resid->Draw();
  return;


}

// Loops over vertex()
void all(Int_t Flag=1){



  if(f!=0) f->Close();
  if(fc!=0) fc->Close();
  if (fc_MC != 0 ) fc_MC->Close();
  
  if (readfile() != 0)
    {
      cout << "problem in file combination: check readfile() " << endl;
    }
  
  f = TFile::Open(DataFile); 
  if (f==0 && eeF !=0 ){
    cout << "Vertex: Problem in opening  data file = " << DataFile << endl;
    return;
  }

  


  fc = TFile::Open(MigrationFile);
  if (fc==0 && MC_MigF ==0 && Flag == 1){
    cout << "Vertex: problem in opening migration file  = " << MigrationFile << endl;
    return(1);
  }

  fc_MC = TFile::Open(MCMigFile);
  if (fc_MC==0 && MC_MigF != 0 && Flag == 1 ){
    cout << "Vertex: problem in opening MC Efficiency file  = " << MCMigFile << endl;
    return(1);
  }



  setTDRStyle();  
  // gROOT->Reset();

  Int_t FlagScale = Flag;
 
  gDirectory->Delete("Vtx_Sigma");
  gDirectory->Delete("Vtx_Chi2");
  gDirectory->Delete("ee_pt>10GeV");

  Vtx_Sigma = new TH1F("Vtx_Sigma","Vtx_Chi", NumPU-1,0.5,NumPU-0.5);
  Vtx_Chi2 = new TH1F("Vtx_Chi2","Vtx_Chi", NumPU-1,0.5,NumPU-0.5);
 
  TH1F *All0 =  new TH1F("All0","Fraction of Events with 0 Pile-Up events",14,0.,UpLim);
  All0->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All0->GetYaxis()->SetTitle("Fraction");

  TH1F *All1 =  new TH1F("All1","Fraction of Events with 1 Pile-Up events",14,0.,UpLim);
  All1->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All1->GetYaxis()->SetTitle("Fraction");

  TH1F *All2 =  new TH1F("All2","Fraction of Events with 2 Pile-Up events",14,0.,UpLim);
  All2->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All2->GetYaxis()->SetTitle("Fraction");

  TH1F *AllN =  new TH1F("AllN","Fraction of Events with 3-8 Pile-Up events",14,0.,UpLim);
  AllN->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  AllN->GetYaxis()->SetTitle("Fraction");

  TH1F *AllHF0 =  new TH1F("AllHF0","Fraction of Events with HF=0",14,0.,UpLim);
  AllHF0->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  AllHF0->GetYaxis()->SetTitle("Fraction");


  TCanvas *Res = new TCanvas("Res","Res",1);
  Res->Divide(3,3);

  TCanvas *HF0 = new TCanvas("HF0","HF0",1);
  HF0->Divide(1,1);
    

  TCanvas *MyC = NCanvas(2,2);

  NSetTitleSize(All0,0.8,.8,0.07);
  NSetTitleSize(All1,0.8,.8,0.07);
  NSetTitleSize(All2,0.8,.8,0.07);
  NSetTitleSize(AllN,0.8,.8,0.07);

  MyC->cd(1);
  All0->SetMinimum(0.02);
  All0->SetMaximum(1.1);
  All0->Draw();
  NLogAxis(0,1);
  MyC->cd(2);
  NLogAxis(0,0);
  All1->SetMinimum(0.08);
  All1->SetMaximum(0.4);
  All1->Draw();
  MyC->cd(3);
  NLogAxis(0,0);
  All2->SetMinimum(0.04);
  All2->SetMaximum(0.3);
  All2->Draw();
  MyC->cd(4);
  AllN->SetMinimum(0.00001);
  AllN->SetMaximum(2.);
  AllN->Draw();
  gStyle->SetOptFit(000000);
  NLogAxis(0,1);



  gStyle->SetOptFit(00000);
   for (Int_t i=1;i<=10;i++){ // to see HF=0
     //   for (Int_t i=1;i<10;i++){
    //  MyC->cd(i);
    if (i==1) {
      MyC->cd(1);
    }
    else if (i==2) {
      MyC->cd(2);
    }
    else if (i==3 ) {
      MyC->cd(3);
    }
    else if (i>3 && i <10 ){
      MyC->cd(4);
    }
    else if (i==10){
      HF0->cd(1);
      AllHF0->SetMinimum(0.0001);
      AllHF0->SetMaximum(0.01);
      AllHF0->Draw();
      NLogAxis(0,1);
    }

    vertex(i,FlagScale);

   }



  MyC->cd(1);
  NText(0.02, .1,"PU=0",1, 0.05);

  //  sprintf(CMSPrel,"CMS Simulation") ;
  sprintf(CMSPrel,"CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}") ;
  NText(0.1,0.8,CMSPrel,1,0.06);
  // NText(0.2, .7,"2010 CMS Preliminary");
  MyC->cd(2);
  NText(0.02, 0.15,"PU=1",1,0.05);
  MyC->cd(3);
  NText(0.02, 0.15,"PU=2",1,0.05);
  MyC->cd(4);
  NText(0.02, 0.2,"PU=3 - 8",1,0.05);


   Sigma();
  return;
}


void all11(Int_t Flag=1){



  if(f!=0) f->Close();
  if(fc!=0) fc->Close();
  if (fc_MC != 0 ) fc_MC->Close();
  
  if (readfile() != 0)
    {
      cout << "problem in file combination: check readfile() " << endl;
    }
  
  f = TFile::Open(DataFile); 
  if (f==0 && eeF !=0 ){
    cout << "Vertex: Problem in opening  data file = " << DataFile << endl;
    return;
  }

  


  fc = TFile::Open(MigrationFile);
  if (fc==0 && MC_MigF ==0 && Flag == 1){
    cout << "Vertex: problem in opening migration file  = " << MigrationFile << endl;
    return(1);
  }

  fc_MC = TFile::Open(MCMigFile);
  if (fc_MC==0 && MC_MigF != 0 && Flag == 1 ){
    cout << "Vertex: problem in opening MC Efficiency file  = " << MCMigFile << endl;
    return(1);
  }



  setTDRStyle();  
  // gROOT->Reset();

  Int_t FlagScale = Flag;
 
  gDirectory->Delete("Vtx_Sigma");
  gDirectory->Delete("Vtx_Chi2");
  gDirectory->Delete("ee_pt>10GeV");
  Vtx_Sigma = new TH1F("Vtx_Sigma","Vtx_Chi", NumPU-1,0.5,NumPU-0.5);
  Vtx_Chi2 = new TH1F("Vtx_Chi2","Vtx_Chi", NumPU-1,0.5,NumPU-0.5);

 
  TH1F *All0 =  new TH1F("All0","Fraction of Events with 0 Pile-Up events",14,LowLim,UpLim);

  All0->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All0->GetYaxis()->SetTitle("Fraction");

  TH1F *All1 =  new TH1F("All1","Fraction of Events with 1 Pile-Up events",14,LowLim,UpLim);
  All1->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All1->GetYaxis()->SetTitle("Fraction");

  TH1F *All2 =  new TH1F("All2","Fraction of Events with 2 Pile-Up events",14,LowLim,UpLim);
  All2->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All2->GetYaxis()->SetTitle("Fraction");

  TH1F *AllN =  new TH1F("AllN","Fraction of Events with 3-8 Pile-Up events",14,LowLim,UpLim);
  AllN->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  AllN->GetYaxis()->SetTitle("Fraction");

  TH1F *AllHF0 =  new TH1F("AllHF0","Fraction of Events with HF=0",14,0.,UpLim);
  AllHF0->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  AllHF0->GetYaxis()->SetTitle("Fraction");


  TCanvas *Res = new TCanvas("Res","Res",1);
  Res->Divide(3,3);

  TCanvas *HF0 = new TCanvas("HF0","HF0",1);
  HF0->Divide(1,1);
    

  TCanvas *MyC = NCanvas(1,2);



  MyC->cd(1);
  All0->SetMinimum(0.001);
  All0->SetMaximum(1.1);
  All0->Draw();
  NLogAxis(0,1);
  MyC->cd(2);
  NLogAxis(0,1);
  /*
  All1->SetMinimum(0.01);
  All1->SetMaximum(0.3);
  All1->Draw();
  MyC->cd(3);
  NLogAxis(0,1);
  All2->SetMinimum(0.01);
  All2->SetMaximum(0.2);
  All2->Draw();
  MyC->cd(4);
*/
  AllN->SetMinimum(0.001);
  AllN->SetMaximum(0.4);
  AllN->Draw();
  gStyle->SetOptFit(000000);
  NLogAxis(0,1);



  gStyle->SetOptFit(00000);
  for (Int_t i=1;i<14;i++)
    { 
      // to see HF=0
      //   for (Int_t i=1;i<10;i++){
      //  MyC->cd(i);
      if (i==1 || i==2 || i==3 || i ==4 || i == 5) {
	MyC->cd(1);
      }
      //      else if (i==6 ) {
      //	MyC->cd(2);
      // }
      //else if (i == 6) {
      //	MyC->cd(3);
      // }
      else if (i>5 && i < 14){
	MyC->cd(2);
      }
      //    else if (i=10){
      //  HF0->cd(1);
      //  AllHF0->SetMinimum(0.0002);
      //  AllHF0->SetMaximum(0.007);
      //  AllHF0->Draw();
      //  NLogAxis(0,1);


      vertex(i,FlagScale);
    }

  //    if (vertex(i,FlagScale) == 1) return;;
  



  MyC->cd(1);
  NText(0.02, .1,"PU=0",1, 0.05);

  sprintf(CMSPrel,"CMS Simulation") ;
  //  sprintf(CMSPrel,"CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}") ;
  NText(0.1,0.8,CMSPrel,1,0.06);
  // NText(0.2, .7,"2010 CMS Preliminary");
  MyC->cd(2);
  NText(0.02, 0.15,"PU=1",1,0.05);
  MyC->cd(3);
  NText(0.02, 0.15,"PU=2",1,0.05);
  MyC->cd(4);
  NText(0.02, 0.2,"PU=3 - 8",1,0.05);


   Sigma();
  return;
}




//show the Sigma and Chi2for all PU

void Sigma(){

  //  TCanvas *My = NCanvas(1,1,"Sigma");
  TCanvas *MyChi2 = NCanvas(1,2,"Chi2");

  MyChi2->cd(1);
  NHSetMarker(Vtx_Chi2,4,20,1.2);
  gStyle->SetOptFit(0);
  gStyle->SetOptFit(0111);
  NLogAxis(0,0);
  //  Vtx_Chi2->Scale(1./8.);
  NSetTitleSize(Vtx_Chi2, .8,.85,0.06);
  NSetLabelSize(Vtx_Chi2, 0.01,0.01,0.07);
  Vtx_Chi2->SetMaximum(4.);
  Vtx_Chi2->SetMinimum(0);
  Vtx_Chi2->Draw("p");
  Vtx_Chi2->GetXaxis()->SetTitle("Number of Vertices");
  Vtx_Chi2->GetYaxis()->SetTitle("#Sigma #chi^{2} of each fit");
  Float_t TotChi2 = Vtx_Chi2->Integral();
  sprintf(hname," #Sigma #chi^{2} =  %3.2f",TotChi2);
  cout << "Total Chi2 = " << hname << endl ;
  cout << "MC file = " << MCMigFile << endl ;
  gStyle->SetOptFit(000000);
  NLine(0.5,1,9.5,1);
  NText (1,3.1,hname,4, 0.05);
  //  NText (1,4.05,MigrationFile,1);


  MyChi2->cd(2);
  NHSetMarker(Vtx_Sigma,2,20,1.2);
  NLogAxis(0,0);
  Vtx_Sigma->SetMinimum(56.5);
  Vtx_Sigma->SetMaximum(60.);
  NSetTitleSize(Vtx_Sigma, .8,.85,0.06);
  NSetLabelSize(Vtx_Sigma, 0.01,0.01,0.07);
  Vtx_Sigma->Draw();
  Vtx_Sigma->GetXaxis()->SetTitle("Number of Vertices");
  Vtx_Sigma->GetYaxis()->SetTitle("#sigma(pp) [mb]");
  //Vtx_Sigma->Fit("pol1"," ","SAME");
  TH1F *Vtx_Sigma1 = Vtx_Sigma->Clone();
  Vtx_Sigma1->Fit("pol0"," " ,"SAME",0,9);

  Float_t res = pol0->GetParameter(0);
  Float_t chi2 = pol0->GetChisquare()/pol0->GetNDF();
     sprintf(hname,"#sigma =  %3.1f mb , #chi^{2} /NDOF = %3.1f ",res,chi2);
     // sprintf(hname,"#sigma = 56.4 mb , #chi^{2} /NDOF = %3.1f ",chi2);
  NText(1,58.3,hname,1,0.05);
  // if (selNDOF == 2 )
  sprintf(hname,"(At least %i charged particles with |#eta|<2.4 and p_{t} > %i MeV)",MinNtracksLowpT,MCPt);
  // sprintf(hname,"(At least %i charged particles with |#eta|<2.4 and p_{t} > 200 MeV)",MinNtracksLowpT);
    //  if (selNDOF == (float) 0.1 ) sprintf(hname,"(At least 2 charged particles with |#eta|<2.6 and p_{t} > 200 MeV)");
  NText(1,57.8,hname,1,0.03);
  pol0->SetLineWidth(0.6); 
  pol0->SetLineStyle(2);  
  // sprintf(CMSPrel,"CMS Simulation") ;
   sprintf(CMSPrel,"2011 CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}") ;
  //  NText(1,61.7,"2010 CMS Preliminary");
  NText(1,59.,CMSPrel,1,0.06);


}

// const Int_t LumBin=14; // Number of lumi bin


// pippo //

void Efficiency(){


TH1F *pois_theory[LumBin];
TH1F *pois_meas[LumBin];
TH1F *pois_ratio[LumBin];
TH1F *Eff_corr[LumBin];
TH1F *LumiBin[LumBin];
TH1F *Mult[10];
TFile *Lf;
TFile *Gf;
char NameFileOut[100]; 
char hname[100];
Float_t LumiBinWidth = 0.1;

Int_t LostVtx = 0; // Number of lost Vertexes
Int_t TotVtx = 0; // Number of lost Vertexes

  
  bool VtxEffCorr = false;

  readfile();

  Int_t NTracksVtx;
  if (SelNDOF == 3) NTracksVtx = 4;
  if (SelNDOF == 2) NTracksVtx = 3;

  NTracksVtx = MinNtracksLowpT;

  Float_t DeltaMCEff = 0.;
  if (SystCheck == 4) DeltaMCEff= 0.02;
  if (SystCheck == 43) DeltaMCEff= 0.03;
  if (SystCheck == 44) DeltaMCEff= 0.04;
  if (SystCheck == 45) DeltaMCEff= 0.05;
  if (SystCheck == 46) DeltaMCEff= 0.06;
  if (SystCheck == 47) DeltaMCEff= 0.07;
  if (SystCheck == 5) DeltaMCEff= -0.02;	
  if (SystCheck == 51) DeltaMCEff= -0.03;	
  if (SystCheck == 52) DeltaMCEff= -0.01;	
  if (SystCheck == 53) DeltaMCEff= 0.01;	
  if (SystCheck == 54) DeltaMCEff= -0.04;	
  if (SystCheck == 55) DeltaMCEff= -0.05;	

  Int_t EffCounter = 0;
  Float_t FracSecVertex = 0.;
  if (SelNDOF == (float) 0.1) FracSecVertex = 0.0015;
  if (SelNDOF == 2) FracSecVertex = 0.0015;
  if (SelNDOF == 3) FracSecVertex = 0.00084;

  if (SystCheck == 11)  FracSecVertex =  0.5*FracSecVertex;	    
  if (SystCheck == 10) FracSecVertex =  2.*FracSecVertex;	    



 
  ReadEfficiency();



  if(Lf==0){  

     Lf = TFile::Open(DataFile);

    if (Lf ==0){
      cout << "Problem opening data file " << DataFile << endl;
      return;
    }
  }
  if(Gf==0){  

    //MB_efficiency_files_PtcutGen0.25_D6T0_save.root
    // sprintf(hname,"MB_efficiency_files_PtcutGen0.25_D6T0_save.root"); //Data vertex1Mult corrected for efficiency 
    // sprintf(hname,"Vertex1MultGen.root"); //Data vertex1Mult corrected for efficiency 

    //    Gf = TFile::Open(hname);
    Gf = TFile::Open(MCMBFile);

    if (Gf ==0){
      cout << "Problem opening MB File " << hname << endl;
      return;
    }
  }

  //Read the luminosity bins

  for (Int_t N=0;N<LumBin; N++){
    sprintf(hname,"LumiBin%i",N+1);
    LumiBin[N] = (TH1F*)Lf->Get(hname);
  }



  //Inputs from MigrationFile: //

  if (DAV)
    {
      // Gen Tracks Multiplicity for Hadron Correction, weighted//
      
         if (PtCut == 200)  TH1F *VertexGenMult =   (TH1F*)Gf->Get("TracksGenEta3Pt200_w_CW2"); 
         if (PtCut == 250)  TH1F *VertexGenMult =   (TH1F*)Gf->Get("TracksGenEta3Pt250_w_CW2"); 

	 if (SystCheck==14) //Pythia8
	   {
	     if (PtCut == 200)  TH1F *VertexGenMult =   (TH1F*)Gf->Get("TracksGenEta3Pt200_w_P8_CHA"); 
	     if (PtCut == 250)  TH1F *VertexGenMult =   (TH1F*)Gf->Get("TracksGenEta3Pt250_w_P8_CHA"); 
	   }
	 
    }
  else
    {
      if (PtCut == 200)  TH1F *VertexGenMult =   (TH1F*)Gf->Get("TracksGenEta3Pt200_w_P8"); 
      if (PtCut == 250)  TH1F *VertexGenMult =   (TH1F*)Gf->Get("TracksGenEta3Pt250_w_P8"); 
    }


  if (VertexGenMult == 0)
    {
      cout << "Problems in finding histos in MCMB   file " << MCMBFile << endl;
      return;
    }

   // Inputs from DataFile: // 

  TH1F *vertex =   (TH1F*)Lf->Get("Vz");  //Z vertex Position  
  TH1F *Vertex1Mult =   (TH1F*)Lf->Get("Vertex1Mult"); // Tracks Multiplicity PU events
  TH1F *Vertex0Mult =   (TH1F*)Lf->Get("Vertex0MultVtxQual"); // Tracks Multiplicity for main trigger
  
  if (vertex ==0 || Vertex1Mult==0 || Vertex0Mult==0){
    cout << "Problem in finding histos in Data files " << endl;
    return;
  }

  for (Int_t Nt = 0;Nt<10;Nt++) // read the blind spot files
    {
      //sprintf(hname,"SumMultVertex_%i_%i",Nt*25,(Nt+1)*25);
      sprintf(hname,"BlindSpotMult_%i_%i",Nt*25,(Nt+1)*25);
      Mult[Nt] =  (TH1F*)Lf->Get(hname); // BlindSpot
    }

  Int_t Nvtx;
  Int_t p;
  Int_t p1;


  Int_t num=0;
  const Int_t MaxVtxInEvent=18;

  //  Float_t vtx_gen[MaxVtxInEvent];
  // Float_t vtx_gen_mult[MaxVtxInEvent];
  // Float_t vtx_gen_Sur[MaxVtxInEvent];
  // Float_t vtx_gen_mult_Sur[MaxVtxInEvent];

  Float_t vtx_gen[MaxVtxInEvent];
  Float_t vtx_gen_Sur[MaxVtxInEvent];
  Int_t vtx_gen_mult[MaxVtxInEvent];
  Float_t vtx_gen_mult_Sur[MaxVtxInEvent];
  Float_t BinCont;
  Float_t BinErr;

  Int_t BinNum ;
  TRandom r;
  Float_t Rn ;
  Double_t BlindCont; 


  TCanvas *CRatio = new TCanvas("CRatio","CRatio",1);
  CRatio->Divide(4,4);
  TCanvas *CEff = new TCanvas("CEff","CEff",1);
  CEff->Divide(3,4);
  TCanvas *MyC= NCanvas(4,4);

  Int_t TotSec;
  Int_t LostForEfficiency;
  Int_t LostForMerging;
  Int_t Below18 = 0;
  Int_t Below18Lost = 0;
  Int_t NumPUGen;
  Float_t fka;
  Int_t index[20];
  Int_t index2[20];
  Bool_t down = false;
  
  Int_t NBinX = Mult[1]->GetNbinsX();
  Float_t BinLE = Mult[1]->GetBinLowEdge(1);
  Float_t BinW = Mult[1]->GetBinWidth(1);

  Float_t NRS = 5000.; 
 
  Int_t Nloop;
  //  for (Float_t Lumi = 0.025; Lumi<=0.7; Lumi+=0.05){
  //  for (Nloop = 1; Nloop<=LumBin; Nloop++ ){'

  Float_t DavDist = 0.1;
  if (SystCheck == 1) DavDist = 0.06;
  if (SystCheck == 8) DavDist = 0.2;
  if (SystCheck == 81) DavDist = 0.5;

  for (Nloop = 0; Nloop<LumBin; Nloop++ ){

    Double_t Lumi = LumiBin[Nloop]->GetMean();

    if (Lumi==0) {
      cout << " Luminosity == 0 for bin "<< Nloop << endl ;
      continue;
    }
    


    cout << "Loop " << Nloop << " with lumi = " << Lumi << endl; 


    sprintf(hname,"Pois_Theory_Lumi%5.3f",Lumi);
    gDirectory->Delete(hname);
    pois_theory[Nloop]  = new TH1F(hname,hname,MaxVtxInEvent,0,MaxVtxInEvent); // Pois hystograms
    pois_theory[Nloop]->Sumw2();
    //    cout << "Not crashed "<< endl;
    sprintf(hname,"Pois_Meas_Lumi%5.3f",Lumi);
    pois_meas[Nloop] = NH1clone(hname,hname,pois_theory[Nloop]);
    sprintf(hname,"Ratio_Meas_over_Theory_Lumi%5.3f",Lumi);
    pois_ratio[Nloop] = NH1clone(hname,hname,pois_theory[Nloop]);
    
    
    Double_t LumiR = LumiBin[Nloop]->GetMean();

    //Fill the hystogram that contains the Pois. Probability of having "MaxVtxInEvent" vertexes 
    // at the luminosity = Lumi
    
    //for (p=0;p<MaxVtxInEvent;p++){
    ////  cout << " p = "<<p<< " and prob_evt= "<< prob_evt(Lumi,p)  << endl;    
    //  pois_theory[Nloop]->SetBinContent(p+1,prob_evt(Sigma,Lumi,p));      
    //}
    

    
    for (Int_t NL = 1; NL<=NRS; NL++)
      {

	Double_t LumiR = LumiBin[Nloop]->GetRandom();
	
	for (p=0;p<MaxVtxInEvent;p++)
	  {
	    //	    if(	prob_evt(Sigma,LumiR,p)<0)    
	    //	    cout << "Lum = "<< LumiR << " Sigma = "<< Sigma << " p = "<<p<< " and prob_evt= "<< prob_evt(Sigma,LumiR,p)  << endl;    
	    pois_theory[Nloop]->Fill(p+0.01,prob_evt(Sigma,LumiR,p));

	  }
      }
    
    pois_theory[Nloop]->Scale(1./NRS);


    if (SystCheck == 9)
      {
	for (p=0;p<MaxVtxInEvent;p++)
	  {
	    //  cout << " p = "<<p<< " and prob_evt= "<< prob_evt(Lumi,p)  << endl;    
	    pois_theory[Nloop]->SetBinContent(p+1,prob_evt(Sigma,Lumi,p));      
	  }
      }

    //Loop over the possible number of vertexes



    for (Int_t i=1; i<=Draw;i++)
      {
	//	  continue;
	NumPUGen = 0;
	Int_t NumPUAfterZMerging=0;
	NumPUGen =   pois_theory[Nloop]->GetRandom();
	
	// cout << "Event "<< i << " start: "<< NumPUGen << " =  Number of Vertexes in addition to the primary trigger" << endl;
	// p=0 is the hypotetical triggering vertex
	// NumPUGen = number of additional vertexes in the event
	
	// Here we generate the Vertexes and check if they survive a Vertex Mult. efficiency cut
	// Note: all vertexes have already more than 4 tracks (done above)
	
	Int_t NVtxAfterMultEff = 0 ; // number of PU vertexes 
	
	for (p = 0;p<=NumPUGen;p++)  //assign Z and multiplicity to each vertex 
	  {  // the event is has NumPUGen PU + 1 primary event (p=0)
	     
	    Float_t vxt1 = vertex->GetRandom();      // Z position of vertex p
	    
	    vtx_gen[p] = vxt1;    
	    
	    if (p==0) 
	      {
		vtx_gen_mult[p] = Vertex0Mult->GetRandom();    // Main trigger mult		
	      }
	    
	    else 
	      {
		
		Int_t VtxMult_temp = 0;
		while (VtxMult_temp<NTracksVtx)
		  {
		    VtxMult_temp = VertexGenMult->GetRandom();    // Random PU Mult, Vtx larger than NTrkVtx	      
		  }
		vtx_gen_mult[p] = VtxMult_temp;    // PU trigger mult
	      }
	    
	  }
	
	// Merge events close to each other in Z
	
	//	for (Int_t H = 0; H<=NumPUGen;H++) cout << "index = "<< H << " pos = "<< vtx_gen[H] << endl;

	TMath::Sort(NumPUGen+1, vtx_gen, index, down);

	//	for (Int_t H = 0; H<=NumPUGen;H++) cout << "New index = "<< index[H] << " pos = "<< vtx_gen[index[H]] << endl;

	NumPUAfterZMerging = 0; // NumPUAfterZMerging = number of PU events after Z merging
	Int_t ipm1 = index[0];
	vtx_gen_Sur[NumPUAfterZMerging]= vtx_gen[ipm1];
	vtx_gen_mult_Sur[NumPUAfterZMerging] = vtx_gen_mult[ipm1];
	// cout <<  "Z vertex 0 = " << vtx_gen_Sur[0] << endl;
	for (p = 1;p<=NumPUGen;p++)
	  {

	    
	    Int_t ip = index[p];
	    Int_t ipm1 = index[p-1];
	    Float_t Dist = fabs(vtx_gen[ip]-vtx_gen[ipm1]);
	    Int_t SumMult = vtx_gen_mult[ip]+vtx_gen_mult[ipm1];

	    // cout <<  "Z vertex " << vtx_gen[ip] << endl;
	    
	    if (DAV) 
	      {
		if (Dist > DavDist) // DavDist =0.06; = 0.1 for SystCheck1
		  {  //Above 2 for sure they are separated
		    NumPUAfterZMerging++;
		    vtx_gen_Sur[NumPUAfterZMerging]= vtx_gen[ip];
		    vtx_gen_mult_Sur[NumPUAfterZMerging] = vtx_gen_mult[ip];
		    
		  }
		else
		  {
		    //		    cout << "Lost in DAV"<< endl;
		    vtx_gen_Sur[NumPUAfterZMerging]= vtx_gen[ipm1];
		    //    vtx_gen_mult_Sur[NumPUAfterZMerging] = vtx_gen_mult[ipm1]+ vtx_gen_mult[ip];
		  }
	      }
	    else if (!DAV)
	      {
		if (Dist > 2.) 
		  {
		    NumPUAfterZMerging++;
		    vtx_gen_Sur[NumPUAfterZMerging]= vtx_gen[ip];
		    vtx_gen_mult_Sur[NumPUAfterZMerging] = vtx_gen_mult[ip];
		    
		  }
		else
		  {
		    

		    
		    BinNum = (Int_t)( 1+ (Dist-BinLE)/BinW); // get the bin index. The histo binning start at 1, so bin 1 from 0-0,1;
		    for (Int_t Nm = 0;Nm<=9;Nm++)
		      {
			if (SumMult>=25*(Nm) && SumMult<25*(Nm+1))
			  {
			    if (SumMult<175)   BlindCont = Mult[Nm]->GetBinContent(BinNum);
			    else   BlindCont = Mult[7]->GetBinContent(BinNum);
			    //     cout << " BlindCount bin " << Nm << " Bin Number " << BinNum << " and content " <<  BlindCont << endl;
			    break;
			  }
		      }
		    
		    
		    Rn =  r.Uniform(0.,1.)*1.2; // 1.2 = Mysterious factor....
		    //	cout << " Rn = " << Rn << " <  BlindCont "<< BlindCont << " ? if yes, they are separated ! "<< endl;
		    if (Rn < BlindCont) 
		      {
			
			NumPUAfterZMerging++;
			vtx_gen_Sur[NumPUAfterZMerging]= vtx_gen[ip];
			vtx_gen_mult_Sur[NumPUAfterZMerging] = vtx_gen_mult[ip];
		      }
		    else  
		      {
			vtx_gen_Sur[NumPUAfterZMerging]= vtx_gen[ipm1];
			vtx_gen_mult_Sur[NumPUAfterZMerging] = vtx_gen_mult[ipm1]+ vtx_gen_mult[ip];
			
		      }
		    
		    
		  }
		
	      }
	    
	  }
	
	//       	cout << "NumPUGen = "<< NumPUGen << " NumPUAfterZMerging " << NumPUAfterZMerging << endl;
      
	Int_t NumPUAfterZ_and_HadronCor = 0;


	if (HadronF)    //decides if it's detected
	  {
	    down = true;
	    TMath::Sort(NumPUAfterZMerging+1, vtx_gen_mult_Sur, index2,down);

	    for (Int_t Np = 1;Np<=NumPUAfterZMerging;Np++) // I assume Np=0 to be thr primary event
	      { 
		
		
	       Int_t ip = index2[Np];
		
		VtxMult_temp = vtx_gen_mult_Sur[ip];  
		
		if(VtxMult_temp <18)    Below18++;
		
		// cout << "Mult = " << VtxMult_temp << endl;
		Rn =  r.Uniform(0.,1.);
		//		cout << Rn << endl;
		
		if ( VtxMult_temp > = 18)
		  {
		    NumPUAfterZ_and_HadronCor++; // This vertex has survived, increment the counter
		  }
		else if (VtxMult_temp < 18)
		  {
		    if (Rn <=(VtxMult_Eff[VtxMult_temp]+DeltaMCEff) )
		      {
			NumPUAfterZ_and_HadronCor++; // This vertex has survived, increment the counter			
		      }	 
		  }
	      }
	    
	    //	    NumPUAfterZ_and_HadronCor -=1 ; // remove the primary event	    	        
	  }
	else
	  {
	    NumPUAfterZ_and_HadronCor = NumPUAfterZMerging;	    	    
	  } 
	
	  
	// cout << "generated "<< NumPUGen << " vertexes and "<<   NumPUAfterZ_and_HadronCor << " survived " << endl;
	
	
	
	
	
	
	// Generate Secondary Vertices //
	
	
	Int_t FakeVtx = 0;
	for (Int_t NC = 0;NC<=NumPUAfterZ_and_HadronCor;NC++)
	  {
	    if ( r.Uniform(0.,1.) < FracSecVertex)  FakeVtx++;
	  }
	
	NumPUAfterZ_and_HadronCor = NumPUAfterZ_and_HadronCor + FakeVtx; // Add fake seconday Vtx
	EffCounter  += FakeVtx;
	//pois_meas[Nloop]->Fill(NumPUAfterZ_and_HadronCor+0.1);
	pois_meas[Nloop]->Fill(NumPUAfterZ_and_HadronCor+0.1);
	

	// cout << " Starting vtx = " << NumPUAfterZ_and_HadronCor << " Final vtx are = " << NumPUAfterZ_and_HadronCor<< endl;
	LostVtx += (NumPUGen-NumPUAfterZ_and_HadronCor);
	LostForMerging += (NumPUGen-NumPUAfterZMerging);
	LostForEfficiency += (NumPUAfterZMerging-NumPUAfterZ_and_HadronCor+FakeVtx);
	
	
	TotVtx +=NumPUGen;
	//	  cout << "pippo"<< endl; // to be removed
	
      } // Draw Loop

	// }  // End of Nloop
	
    //	cout << "Number of secondary vertices = "<< EffCounter << endl;	
    //	cout << "Number of Lost vertices = "<< LostVtx << endl;	



	MyC->cd(Nloop+1);
	Float_t scale = pois_meas[Nloop]->GetEntries();
	pois_meas[Nloop]->SetMaximum(1.);  
	pois_meas[Nloop]->SetMinimum(0.001);  
	
	NLogAxis(0,1);
	pois_meas[Nloop]->Scale(1./scale);
	pois_meas[Nloop]->SetLineStyle(2);
	NHSetMarker(pois_meas[Nloop],2,20,0.8);
	pois_meas[Nloop]->Draw();
	pois_theory[Nloop]->Draw("SAMEHIST");    
	pois_meas[Nloop]->GetXaxis()->SetTitle("vertex");
	pois_meas[Nloop]->GetYaxis()->SetTitle("Fraction");
	Float_t xl=LumiBinWidth*(Nloop);
	Float_t xu=LumiBinWidth*(Nloop+1);
	sprintf(hname,"L= %4.2f-%4.2f  10^{30} cm^{-2} s^{-1} ",xl,xu);
	NText(5,0.2,hname,1,0.06);
	
	CRatio->cd(Nloop+1);
	NLogAxis(0,0);
	
	pois_ratio[Nloop]->Divide(pois_meas[Nloop],pois_theory[Nloop]);
	pois_ratio[Nloop]->SetMaximum(1.8);  
	NHSetMarker(pois_ratio[Nloop],2,20,1.);
	pois_ratio[Nloop]->Draw("E");    
	pois_ratio[Nloop]->GetXaxis()->SetTitle("Vertex");
	pois_ratio[Nloop]->GetYaxis()->SetTitle("Predicted Vis./True");
	
	Float_t xl=LumiBinWidth*(Nloop);
	Float_t xu=LumiBinWidth*(Nloop+1);
	sprintf(hname,"L = %4.2f-%4.2f  10^{30} cm^{-2} s^{-1} ",xl,xu);
	NText(4,1.6,hname,1,0.08);
	
	//    Nloop++;
	
  }  // End of Nloop
  
  Float_t SecFrac =  (1.*EffCounter)/(1.*TotVtx);
  Float_t LostMerg =  (1.*LostForMerging)/(1.*TotVtx);
  Float_t LostEff =  (1.*LostForEfficiency)/(1.*TotVtx);
  //  cout << "Lost Vtx = " << LostVtx << " Sec Vtx = " << SecFrac << " Lost fraction = " << LostFrac << endl;
  cout << "Tot Vtx = " << TotVtx << endl;
  cout << "Lost in Merging = " << LostMerg << endl;
  cout<<  "Lost for Eff  " << LostEff << endl;
  cout<<  "Secondary Vtx = "<< SecFrac << endl;
  cout << "Events below 18 tracks = "<<  Below18 << ", Fraction = " << 1.*Below18/(1.*TotVtx) << endl; 
  

  
  MyC->cd(15);
  TLegend *leg = new TLegend(0.,0.5, 1 ,1);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(pois_theory[1],"True","L");  
  leg->AddEntry(pois_meas[1],"Predicted ","p");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.07);  
  leg->SetFillColor(0);

  leg->Draw();


  TPaveText *pave1 = new TPaveText(0,0.5,1,1);        
  TText *t1 =pave1->AddText("CMS Simulation") ;
  TText *t2 =pave1->AddText("#sqrt{s} = 7 TeV, L = 36 pb^{-1}");
  pave1->SetFillColor(0);
  pave1->SetBorderSize(0);
  MyC->cd(16);
  pave1->Draw();                   




  CRatio->cd(16);
  pave1->Draw(); 
  CRatio->cd(15);                  
  TLegend *leg1 = new TLegend(0.,0.8, 1 ,1);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg1->AddEntry(pois_ratio[1],"Predicted /","p");  
  leg1->AddEntry(pois_ratio[1],"True"," ");  
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.07);  
  leg1->SetFillColor(0);

  leg1->Draw();



  // Prepare the correction hystos
  
  sprintf(hname,"Eff_0Nvtx");
  Eff_corr[0]= new TH1F(hname, hname, LumBin, 0., 0.7);
  Eff_corr[0]->Sumw2();
  
  for (p=1;p<LumBin;p++)
    {
      sprintf(hname,"Eff_%iNvtx",p);
      Eff_corr[p] = NH1clone(hname,hname,Eff_corr[0]);
    }

  for (p=1;p<=LumBin;p++)
    {      //loop over the bin
    for (p1=1;p1<=LumBin;p1++)
      {  // loop over the histos
	
	if (LumiBin[p1-1]->GetMean()!=0)
	  {	
	    BinCont = pois_ratio[p1-1]->GetBinContent(p);
	    BinErr = pois_ratio[p1-1]->GetBinError(p);
	    Eff_corr[p-1]->SetBinContent(p1,BinCont);
	    Eff_corr[p-1]->SetBinError(p1,BinErr);
	  }
      }
    }
  
  for (p=4;p<=12;p++)
    {      //loop over the bin
      CEff->cd(p);
      Eff_corr[p-4]->SetMaximum(1.8);  
      Eff_corr[p-4]->SetMinimum(0.);  
      NHSetMarker(Eff_corr[p-4],4,20,1.);
      sprintf(hname,"Predicted Visible/True %i pile-up event",p-4);
      
      
      Eff_corr[p-4]->Draw("PE");
      Eff_corr[p-4]->GetXaxis()->SetTitle("Luminosity  10^{30} [cm^{-2} s^{-1}]");
      Eff_corr[p-4]->GetYaxis()->SetTitle(hname);
      Eff_corr[p-4]->SetTitle(hname);
       }

  CEff->cd(1);
  TLegend *leg = new TLegend(0.,0., 1. ,0.2);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Eff_corr[1],"Predicted Visible/","p");
  leg->AddEntry(VxtLumiBin[1],"True"," ");  

  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.1);  
  leg->Draw();


 TPaveText *pave1 = new TPaveText(0,0.5,1,1);        
  TText *t1 =pave1->AddText("CMS Simulation") ;
  TText *t2 =pave1->AddText("#sqrt{s} = 7 TeV, L = 36 pb^{-1}");
  pave1->SetFillColor(0);
  pave1->SetBorderSize(0);
  CEff->cd(1);
  pave1->Draw();                   


  cout << "Opening output files "<< MigrationFile << endl; 
  TFile fMig(MigrationFile,"recreate"); 

  for (p=0; p<LumBin; p++) 
    {
      
      Eff_corr[p]->Write();
      if (LumiBin[p]->GetMean()!=0)
	{	    
	  pois_ratio[p]->Write();
	  pois_theory[p]->Write();
	  pois_meas[p]->Write();
	}
    }
  fMig.Close(); 
  
 

    return;
}

TF1 *pois[100];
void Pois_Draw()
{  
  char hname[100]; 
  char h1name[100]; 
  NCanvas(3,2);

  for (Int_t j=0;j<6; j++){
    MyC->cd(j+1);
    NLogAxis(0,1);
    for (Int_t i = 1;i<5;i++){

      Int_t num = j*10+i;
      sprintf(hname,"pois%i",num);
      sprintf(h1name,"PU Event= %i",j);
      pois[num]  = new TF1(hname,prob_pois,0.0,0.7,2); // x in [0.1;0.6], 2 parameters
      Float_t sigma = 0.030 +0.005*(i-1) ;
      pois[num]->SetParameter(0,sigma);
      pois[num]->FixParameter(1,j);
      pois[num]->SetLineColor(i+1);
      pois[num]->SetName(h1name);
      pois[num]->SetTitle(h1name);
      if (j<4)     pois[num]->SetMinimum(0.05);
      if (j>=4)     pois[num]->SetMinimum(0.001);

      if (i==1) pois[num]->Draw();
      else pois[num]->Draw("SAME");
      if (j==0) {
	NText(0.3,1., "red: Sigma_PU = 30 mb");
	NText(0.3,0.75, "yellow:Sigma_PU = 50 mb");
      }
    };
  }
}

// Sorting function 

void bubbleSort(float arr[], int n) {
      bool swapped = true;
      int j = 0;
      float tmp;
      while (swapped) {
            swapped = false;
            j++;
            for (int i = 0; i < n - j; i++) {
                  if (arr[i] > arr[i + 1]) {
                        tmp = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = tmp;
                        swapped = true;
                  }
            }
      }
}




Float_t prob_evt( Float_t Sigma, Float_t LumInt, int nevt){

  Float_t sigma_NSD =  Sigma*pow(10,-24);
  //  Float_t sigma_NSD =  0.035*pow(10,-24);
  Float_t Lum_bunch = (LumInt*pow(10,30)/11346)*sigma_NSD ;
  Float_t pois_prob = pow(Lum_bunch,nevt) * exp(-Lum_bunch)/TMath::Factorial(nevt) ;


  return(pois_prob);
 
}
Double_t prob_pois( Double_t*x, Double_t *par){

  Double_t sigma =  par[0]*pow(10,-24);
  // cout << "x = " << x[0] << endl;
  Double_t Lum_bunch = (x[0]*pow(10,30)/11346)*sigma ;
  // cout << "Average events = " << Lum_bunch << endl;
  Double_t pois_prob = pow(Lum_bunch,par[1]) * exp(-Lum_bunch)/TMath::Factorial(par[1]) ;
  return pois_prob;
 
}



Double_t prob_vtx1( Double_t*x, Double_t *par){

  Double_t sigma =  par[0]*pow(10,-24);
  // cout << "x = " << x[0] << endl;
  Double_t Lum_bunch = (x[0]*pow(10,30)/11346)*sigma ;
  // cout << "Average events = " << Lum_bunch << endl;
  Double_t pois_vtx1 = par[1]* exp(-Lum_bunch) ;
  return pois_vtx1;
 
}


Double_t prob_vtx2( Double_t*x, Double_t *par){

  Double_t sigma =  par[0]*pow(10,-24);
  // cout << "x = " << x[0] << endl;
  Double_t Lum_bunch = (x[0]*pow(10,30)/11346)*sigma ;
  // cout << "Average events = " << Lum_bunch << endl;
  Double_t pois_vtx2 = par[1]* exp(-(Lum_bunch*Lum_bunch)) ;
  return pois_vtx2;
 
}


void Npileup( Float_t xLum, Float_t sig){

  Double_t sigma =  sig*pow(10,-24);
  // cout << "x = " << x[0] << endl;
  Double_t Lum_bunch = (xLum*pow(10,30)/11346)*sigma ;
  cout << "Average events = " << Lum_bunch << endl;
  return;
 
}


Double_t fitf(Double_t *x,Double_t *par) 
{ 
  Double_t arg = 0; 
  if (par[2] != 0) arg = (x[0] - par[1])/par[2]; 
  Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg); 
  return fitval; 
}   



void Read_File(){


  TFile *f =TFile::Open("Fraction_n_vertexes_files_Zll_try.root"); 
  TH1F *Dat_all_lumi =   (TH1F*)f->Get("Dat_all_Lumi");
  const int nHists=12;
  TH1F * Vxt_Lumi[nHists];
  char hname[100]; 
  for (Int_t i=0;i<nHists;i++){
    sprintf(hname,"Vxt_Lumi%i",i);
    Vxt_Lumi[i] =   (TH1F*)f->Get(hname);
  }

  // f->Close();
   return;
}


//TH1F *Runs;
// TH1F *RunsLumi;
TFile *ff;
void SeeRuns(){

  char hname[100]; 
  readfile();
  if(ff==0){
    ff = TFile::Open(DataFile); 
  }
  TH1I *Runs =   (TH1I*)ff->Get("Runs");
  TH1F *RunsLumi =   (TH1F*)ff->Get("RunsLumi");

  Runs->Draw();
  Int_t Nbin = Runs->GetNbinsX();
  for (Int_t i = 1; i<Nbin; i++){
    if (Runs->GetBinContent(i)>10000.){
      //    cout << i << " " <<Runs->GetBinCenter(i) << " " << RunsLumi->GetBinContent(i) << endl;
    cout << Runs->GetBinCenter(i) << ",";
    }
       
  }
  cout <<endl;
}

void BlindSpot(){

  gDirectory->Delete("V12");
  gDirectory->Delete("V01");
  //  Dat_eeB->cd();
  TH2F *V12 = new TH2F("V12","V12",200, -.25,0.25, 50,0.,200);
  TH2F *V01 = new TH2F("V01","V01",200, -.25,0.25, 50,0.,200);

  tree_->Draw("vertexMolteplicity[1]+vertexMolteplicity[0]:(V_z[0]-V_z[1])>>V01", "vertexNDOF[1]>2 && vertexNDOF[0]>2");
  tree_->Draw("vertexMolteplicity[1]+vertexMolteplicity[2]:(V_z[1]-V_z[2])>>V12", "vertexNDOF[1]>2 && vertexNDOF[2]>2");

  return;
}

  TH1F *VxtLumiBin[LumBin];

TH2F *res2d = new TH2F("res2D","res2D", 14,0,0.7,8,0,8.);
void CheckVxt(){

  TH1F *pois_theory[LumBin];
  TH1F *pois_meas[LumBin];
  TH1F *pois_ratio[LumBin];
  TH1F *Eff_corr[LumBin];
  TH1F *LumiBin[LumBin];
  TH1F *Mult[10];
  TFile *Lf;
  TFile *Gf;
  char NameFileOut[100]; 
  char hname[100];
  
  const Int_t LumBin=14; // Number of lumi bin
  
  //  char DataInputFile[100]; 



  Float_t xl;
  Float_t xu;
  readfile();
  //  if (f==0){
    f = TFile::Open(DataFile); if (f==0) return;
    
    if(MC_MigF ==0)    fc = TFile::Open(MigrationFile);
    else    fc = TFile::Open(MCMigFile);
    if (fc==0) return;
    //  }
  TH1F *H[15];
  TCanvas *My = NCanvas(4,4,"My");
  TCanvas *RatioC = NCanvas(4,4,"RatioC");
  TCanvas *Res2D = NCanvas(4,4,"Res2D");
  for (Int_t N=1;N<14; N++){
    My->cd(N+1);
    cout << "N = " << N << endl;
    xl=LumiBinWidth*(N);
    xu=LumiBinWidth*(N+1);
    sprintf(hname,"Vtx_Lumi_Int_%4.2f_%4.2f",xl,xu);
    VxtLumiBin[N] = (TH1F*) f->Get(hname);
    sprintf(hname,"LumiBin%i",N+1);
    LumiBin[N] = (TH1F*)f->Get(hname);
    Double_t Lumi = LumiBin[N]->GetMean();
    Int_t NLumi = Lumi*100;

    if(MC_MigF ==0)       sprintf(hname,"Pois_Meas_Lumi%5.3f",Lumi);
    else    sprintf(hname,"MC_Vtx_Rew_NDOF%i",NLumi);
    pois_meas[N] = (TH1F*)fc->Get(hname);
    VxtLumiBin[N]->Sumw2();
    
    NH1FArea1(VxtLumiBin[N]);
    VxtLumiBin[N]->SetMaximum(1.);
    if (N<4)    VxtLumiBin[N]->SetMinimum(0.000001);
    else    VxtLumiBin[N]->SetMinimum(0.0001);
    NHSetMarker(VxtLumiBin[N],2,20,0.9);
    NSetTitleSize(VxtLumiBin[N], .65,.9,0.09);
    NSetLabelSize(VxtLumiBin[N], 0.01,0.01,0.07);
    VxtLumiBin[N]->Draw("p");
    NLogAxis(0,1);
    H[N]=NH1clone("Ratio","Ratio", VxtLumiBin[N]);
    VxtLumiBin[N]->GetXaxis()->SetRange(0,10);
    VxtLumiBin[N]->GetXaxis()->SetTitle("Number of Vertexes");
    VxtLumiBin[N]->GetYaxis()->SetTitle("Fraction");
    Float_t xl=LumiBinWidth*(N);
    Float_t xu=LumiBinWidth*(N+1);
    sprintf(hname,"Luminosity: %4.2f-%4.2f  10^{30} cm^{-2} s^{-1} ",xl,xu);
    NText(0.5,1.1,hname,1,0.06);
    pois_meas[N]->SetLineColor(1);
    pois_meas[N]->Draw("SAMEHIST");



    //    cout <<  VxtLumiBin[N]->KolmogorovTest(pois_meas[N]) << endl;
    // VxtLumiBin[N]->Chi2Test(pois_meas[N]);

    RatioC->cd(N+1);
    H[N]->Add(VxtLumiBin[N]);
    H[N]->Divide(pois_meas[N]);
    H[N]->GetXaxis()->SetRange(0,8);
    for (Int_t jk = 1; jk<9; jk++) res2d->SetBinContent(N+1,jk,H[N]->GetBinContent(jk));
    // for (Int_t jk = 1; jk<9; jk++) res2d->SetBinContent(N+1,jk, N);
	
    H[N]->SetMinimum(0.8);
    H[N]->SetMaximum(1.2);
    H[N]->Draw("p");
    Float_t xl=LumiBinWidth*(N);
    Float_t xu=LumiBinWidth*(N+1);
    sprintf(hname,"Luminosity: %4.2f-%4.2f  10^{30} cm^{-2} s^{-1} ",xl,xu);
    NText(0.5,0.88,hname,1,0.06);
    H[N]->GetXaxis()->SetTitle("Number of Vertexes");
    H[N]->GetYaxis()->SetTitle("Data/MC ");
    NLine(0,1.,8,1.);
    
  }

  for (Int_t N=1;N<0; N++){
    My->cd(N);
    TH1F *pippo= pois_meas[N]->Clone();
    pippo->SetLineStyle(1);
    pippo->SetLineColor(2);
    pippo->Draw("SAMEHIST");
    
  }

  My->cd(1);
  TPaveText *pave1 = new TPaveText(0,0.5,1,1);        
  TText *t1 =pave1->AddText("CMS Preliminary") ;
  TText *t2 =pave1->AddText("#sqrt{s} = 7 TeV, L = 36 pb^{-1}");
  pave1->SetFillColor(0);
  pave1->SetBorderSize(0);
  pave1->Draw();                   


  My->cd(15);
  TLegend *leg = new TLegend(0.,0.2, 0.7 ,0.8);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(VxtLumiBin[1],"Measured","p");  
  if (MC_MigF == 0)  leg->AddEntry(pois_meas[1],"Analytic - Predicted","L");
  else   leg->AddEntry(pois_meas[1],"MC - Predicted ","L");

  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.1);  
  leg->Draw();


  RatioC->cd(1);
  pave1->Draw();                   

  RatioC->cd(15);
  TLegend *leg = new TLegend(0.0,0.8, 1. ,1.);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(H[1],"(Measured)/","p");  
  if (MC_MigF == 0)  leg->AddEntry(H[1],"(Analytic Predicted )","");  
  else   leg->AddEntry(H[1],"(MC - Predicted)","");  


  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.1);  
  leg->Draw();
  
  Res2D->cd();
  res2d->Draw("colz");
  res2d->GetYaxis()->SetTitle("# of Vertices");
  res2d->GetXaxis()->SetTitle("Luminosity  10^{30} [cm^{-2} s^{-1}]");
   sprintf(hname,"CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}") ;
   NText(0.1,8,hname,1,0.05);
  return;
}

TFile *fData;
TFile *fMC;
TFile *fD6T;
string stringa;


void MCReweight(){

  if (readfile() == 1)
    {
      return;
    }

  if(fData==0)
    {  // Data File //
     
      fData = TFile::Open(DataFile);
      fMC = TFile::Open(MCMBFile);
      if (fData==0 || fMC == 0)
	{
	  cout << "Problem in opening the input files " << endl;
	  return;
	}
    }
  
  TH1F *Vertex1Mult =   (TH1F*)fData->Get("Vertex1Mult");
  TH1F *PtMeas =   (TH1F*)fData->Get("MeasPt_Mult9");

  if (PtMeas == 0)
    {
      cout << "No PT!!! you should run on mumu!!!" << endl;
      //      return;
    }

  // un-weighted distributions //



  stringa = "TracksMeas_NDOFGT0_P8_CHA";
  sprintf(hname,stringa.c_str());
  TH1F *VertexMultP8 =    (TH1F*)fMC->Get(hname);
  stringa = "TracksMeas_NDOFGT0_w_P8_CHA";
  sprintf(hname,stringa.c_str());
  TH1F *VertexMultP8w =    (TH1F*)fMC->Get(hname)
;

  stringa = "MeasPt_NDOFGE2_Mult9_P8_CHA";
  sprintf(hname,stringa.c_str());
  TH1F *PtP8 =    (TH1F*)fMC->Get(hname);

  stringa = "TracksMeas_NDOFGT0_w_CW";
  sprintf(hname,stringa.c_str());
  TH1F *VertexMultCWw =    (TH1F*)fMC->Get(hname);
  stringa = "TracksMeas_NDOFGT0_CW";
  sprintf(hname,stringa.c_str());
  TH1F *VertexMultCW =    (TH1F*)fMC->Get(hname);

  stringa = "MeasPt_NDOFGE2_Mult9_CW";
  sprintf(hname,stringa.c_str());
  TH1F *PtCW =    (TH1F*)fMC->Get(hname);


  // weighted Distributions //
  //  TH1F *VertexMultD6T =    (TH1F*)fD6T->Get("TracksMeas_NDOFGE2_w");
  //TH1F *VertexMultP8 =    (TH1F*)fP8->Get("TracksMeas_NDOFGE2_w");


  NH1FArea1(Vertex1Mult);
  NH1FArea1(VertexMultCW);
  NH1FArea1(VertexMultP8);


  NH1FArea1(VertexMultCWw);
  NH1FArea1(VertexMultP8w);


  //  NH1FMax1(Vertex1Mult);
 
  



  TCanvas *Rew = NCanvas(1,1,"Rew");

  Rew->cd(1);
  NLogAxis(1,1);
  Vertex1Mult->SetAxisRange(1,120);
  Vertex1Mult->SetMinimum(0.001);

  Vertex1Mult->SetMarkerSize(.8);
  Vertex1Mult->Draw("p");

  Vertex1Mult->GetXaxis()->SetTitle("Tracks per vertex");
  Vertex1Mult->GetYaxis()->SetTitle("Fraction");
  VertexMultCWw->SetLineColor(2);
  VertexMultCWw->SetLineStyle(2);
  VertexMultCWw->Draw("SAMEHIST");
  VertexMultP8w->SetLineColor(4);
  VertexMultP8w->Draw("SAMEHIST");

  TLegend *leg = new TLegend(0.7,0.7, 1. ,0.9);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Vertex1Mult,"Data","p");  
  leg->AddEntry(VertexMultCWw,"CW","L");  
  leg->AddEntry(VertexMultP8w,"P8","L");  
  leg->SetBorderSize(0);
  //  leg->SetTextSize(0.1);  
  leg->Draw();


  TCanvas *NotRew = NCanvas(1,1,"NotRew");

  //  NotRew->cd(1);
  NLogAxis(1,1);
  Vertex1Mult->SetAxisRange(1,120);
  Vertex1Mult->SetMinimum(0.001);

  Vertex1Mult->SetMarkerSize(.8);
  Vertex1Mult->Draw("p");

  Vertex1Mult->GetXaxis()->SetTitle("Tracks per vertex");
  Vertex1Mult->GetYaxis()->SetTitle("Fraction");
  VertexMultCW->SetLineColor(2);
  VertexMultCW->SetLineStyle(2);
  VertexMultCW->Draw("SAMEHIST");
  VertexMultP8->SetLineColor(4);
  VertexMultP8->Draw("SAMEHIST");

  TLegend *leg = new TLegend(0.7,0.7, .9 ,0.9);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Vertex1Mult,"Data","p");  
  leg->AddEntry(VertexMultCW,"CW","L");  
  leg->AddEntry(VertexMultP8,"P8","L");  
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  //  leg->SetTextSize(0.1);  
  leg->Draw();
  TH1F *ratioz2 = NH1clone("Data/P8_NDOFGE2","Data/P8_NDOFGE2",Vertex1Mult);
  TH1F *ratiocw = NH1clone("Data/CW_NDOFGE2","Data/CW_NDOFGE2",Vertex1Mult);
  TH1F *ratioPt = NH1clone("PtRatio","PtRatio",PtCW);
  

  TCanvas *Pt = NCanvas(1,1,"Pt");
  TCanvas *PtRatio = NCanvas(1,1,"PtRatio");

  Pt->cd();


  NH1FArea1(PtMeas);
  NH1FArea1(PtCW);
  NH1FArea1(PtP8);


  Float_t PtP8Frac = PtP8->Integral(3,100)/PtP8->Integral();
  Float_t PtMeasFrac = PtMeas->Integral(3,100)/PtMeas->Integral();
  Float_t PtCWFrac = PtCW->Integral(3,100)/PtCW->Integral();
  cout << "P8 fraction of events with Pt>0.2 = " << PtP8Frac << endl;
  cout << "Meas fraction of events with Pt>0.2 = " << PtMeasFrac << endl;
  cout << "CW fraction of events with Pt>0.2 = " << PtCWFrac << endl;


  PtCW->Draw("HIST");
  PtP8->SetLineColor(4);
  PtP8->Draw("SAMEHIST");
  PtMeas->SetMarkerSize(.8);
  PtMeas->Draw("SAMEp");
  PtCW->SetLineColor(2);
  PtCW->SetLineStyle(2);
  NLogAxis(1,1);
  PtMeas->GetXaxis()->SetTitle("Pt [GeV]");
  PtMeas->GetYaxis()->SetTitle("Fraction");
  TLegend *leg1 = new TLegend(0.6,0.7, 0.8. ,0.9);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg1->AddEntry(PtMeas,"Data","p");  
  leg1->AddEntry(PtCW,"CW","L");  
  leg1->AddEntry(PtP8,"P8","L");  
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  //  leg->SetTextSize(0.1);  
  leg1->Draw();

  PtRatio->cd();
  ratioPt->Add(PtMeas);
  ratioPt->Divide(PtP8);
  ratioPt->Draw("HIST");
  ratioPt->SetMinimum(0.);
  ratioPt->SetMaximum(3.);

  ratioPt->Fit("pol4","","",0.1,1.5);

    
  TCanvas *MyR = NCanvas(1,2,"MyR");
 

  MyR->cd(1);
  //  NLogAxis(0,0);
  // ratioz2->SetAxisRange(0,100);
  //  Vertex1Mult->SetMinimum(0.001);
  ratioz2->Add(Vertex1Mult);
  ratioz2->Divide(VertexMultP8);
  //  NH1FMax1(ratioz2);
  //  ratioz2->SetMaximum(5);
  // ratioz2->SetMinimum(0.);
  ratioz2->Draw();
  cout << "Fit P8 Multiplicty ratio:" << endl;
  ratioz2->Fit("pol3","","",3,20);

  MyR->cd(2);
  NLogAxis(0,0);
  ratiocw->SetAxisRange(0,100);
  //  Vertex1Mult->SetMinimum(0.001);
  ratiocw->Add(Vertex1Mult);
  ratiocw->Divide(VertexMultCW);
  // NH1FMax1(ratiocw);
  ratiocw->SetMaximum(5);
  ratioz2->SetMinimum(0.);
  ratiocw->Draw();
  cout << "Fit CW Multiplicty ratio:" << endl;
  ratiocw->Fit("pol4","","",3,100);




  TCanvas *MCGen = NCanvas(1,1,"MCgen");
  MCGen->cd();

  TH1F *P8Gen200 =    (TH1F*)fMC->Get("TracksGenEta3Pt200_P8");
  TH1F *CWGen200 =    (TH1F*)fMC->Get("TracksGenEta3Pt200_CW2");

  TH1F *P8Gen200w =    (TH1F*)fMC->Get("TracksGenEta3Pt200_w_P8");
  TH1F *CWGen200w =    (TH1F*)fMC->Get("TracksGenEta3Pt200_w_CW2");

  P8Gen200->SetAxisRange(1,30);
  P8Gen200->SetTitle("Pythia 8 Track Multiplicity");
  P8Gen200->Draw();
  P8Gen200w->Draw("SAMEHIST");
  P8Gen200->GetXaxis()->SetTitle("Generated Multiplicity [pt>200 MeV, |eta|<2.4]");
  P8Gen200->GetYaxis()->SetTitle("Entries");

  //  CW2Gen250->Draw("SAME");

  P8Gen200->SetMinimum(0);
  NHSetMarker(CWGen200,2,20,0.6);
  CWGen200->Draw("SAME");
  CWGen200w->SetLineColor(2);
  CWGen200w->Draw("SAMEHIST");





  //  TFile fRew("Reweight_files_NDOF2.root","recreate"); 
  //ratiocw->Write();
  //ratioz2->Write();
  // fRew.Close();
  return;

}


// This macro takes the meas. vertex1mult and correct for efficiency the bin 4->20

void BuildVxt1Mult(){

  if(fData==0)
    {  // Data File //
      
      fData = TFile::Open("Fraction_n_vertexes_files_ee10_EBGT50_runAB_NDOFGT2_VtxMultGT1_DAV1_RunList=1_LumiCor=1.root");
    }


  Float_t VtxMult_Eff[20] =   // vertex Efficiency array Reweighted (Z2)
  {
      0,       0,       0,       0,       0.122163,
      0.239812,0.374539,0.513237,0.632923,0.735469,
      0.807218,0.862626,0.906567,0.934381,0.957177,
      0.971498,0.979791,0.985438,0.99095, 1
	};
  
  TH1F *Vertex1Mult =   (TH1F*)fData->Get("Vertex1Mult");
  //  TH1F *Vertex1MultGen = Vertex1Mult->Clone();
  TH1F *Vertex1MultGen = NH1clone("Vertex1MultGen","Vertex1MultGen",Vertex1Mult);

  Int_t NN = Vertex1Mult->GetNbinsX();
  for (Int_t i = 1;i<20;i++)
    {
      if (VtxMult_Eff[i]>0)
	{
	  Float_t temp = Vertex1Mult->GetBinContent(i)/VtxMult_Eff[i];
	  cout << " i " << i << " Cont = " <<  Vertex1Mult->GetBinContent(i)<< " Bin = " << VtxMult_Eff[i] << endl;
	  //      cout << " i " << i << " Cont = " <<  Vertex1Mult->GetBinContent(i)<< endl;
	  Vertex1MultGen->SetBinContent(i,temp);
	}
    }
  Vertex1MultGen->Draw();
  Vertex1Mult->Draw("SAME");
  TFile fh("Vertex1MultGen.root","recreate"); 
  Vertex1MultGen->Write();
  fh.Close();

  return;
}

TFile *fee;
TFile *fmm;
TH1F *RunTriggersee[RunBin];
TH1F *RunTriggersmm[RunBin];
TH1F *RunLumiee[RunBin];
TH1F *RunLumimm[RunBin];
TH1F *ratioeemm[RunBin];
TH1F *ratiolumiee[RunBin];
TH1F *ratiolumimm[RunBin];

void LumiCheck_eemm(bool WriteFile =false){


  Int_t RunForLumi[RunBin] = 
    {
      142130,142422,142528,142928,142933,142971,143007,143181,143328,143657,
      143727,143827,143833,143835,143953,143954,143962,144011,144086,144089,
      144112,146804,146807,146944,147043,147048,147114,147115,147196,147217,
      147219,147222,147284,147390,147450,147451,147754,147755,147757,148002,
      148029,148031,148032,148058,148822,148862,148864,148952,149011,149058,
      149063,149181,149182,149291,149294,149442
    };

  char hname[100]; 
  Int_t xLim = 500;
  if(fee == 0){
    //  sprintf(hname ,"Fraction_n_vertexes_files_ee10_NDOFGT2_EBGT50_runAB.root"); 


    fee = TFile::Open("Vertexes_Data_NDOFGT1_RunList=0_LumiCor=0_SystCheck0_ee10_DAV.root"); 
    fmm = TFile::Open("Vertexes_Data_NDOFGT1_RunList=0_LumiCor=0_SystCheck0_sm_DAV.root"); 
    
    if (fee==0 || fmm ==0 )
      {
	cout << "Problem with the input data file" << endl;
	return;
      }
    
    
    for (Int_t M=0;M<RunBin;M++){

      sprintf(hname,"RunTriggers%i",M);
      RunTriggersee[M] =   (TH1F*)fee->Get(hname);
      RunTriggersmm[M] =   (TH1F*)fmm->Get(hname);

      sprintf(hname,"RunLumi%i",M);
      RunLumiee[M] =   (TH1F*)fee->Get(hname);
      RunLumimm[M] =   (TH1F*)fmm->Get(hname);

      sprintf(hname,"Ratio Triggers (ee)/(m) for run =  %i",RunForLumi[M]);
      ratioeemm[M] = NH1clone(hname,hname,RunTriggersee[0]);
      ratioeemm[M]->Divide(RunTriggersee[M],RunTriggersmm[M]);


      sprintf(hname,"Ratio Lum/(ee) for run =  %i",RunForLumi[M]);
      ratiolumiee[M] = NH1clone(hname,hname,RunTriggersee[0]);
      ratiolumiee[M]->Divide(RunLumiee[M],RunTriggersee[M]);

      sprintf(hname,"Ratio Lum/(m) for run =  %i",RunForLumi[M]);
      ratiolumimm[M] = NH1clone(hname,hname,RunTriggersmm[0]);
      ratiolumimm[M]->Divide(RunLumimm[M],RunTriggersmm[M]);
      

      ratiolumiee[M]->Divide(ratiolumimm[M],RunTriggersmm[M]);


      sprintf(hname,"Run %i",RunForLumi[M]);      
      MyC[M] = new TCanvas(hname,hname,M);
      MyC[M]->Divide(1,3);
      sprintf(hname,"Run %i Bunch Crossing",RunForLumi[M]);      

      MyC[M]->cd(1);
      ratioeemm[M]->SetAxisRange(0,xLim);
      ratioeemm[M]->Draw();
      // RunTriggersee[M]->Draw();
      ratioeemm[M]->GetXaxis()->SetTitle(hname);
      ratioeemm[M]->GetYaxis()->SetTitle("ee/single mu");

      MyC[M]->cd(2);
      ratiolumimm[M]->SetAxisRange(0,xLim);
      ratiolumimm[M]->Draw();
      // RunTriggersmm[M]->Draw();
      ratiolumimm[M]->GetXaxis()->SetTitle(hname);
      ratiolumimm[M]->GetYaxis()->SetTitle("lumi/single mu");

      MyC[M]->cd(3);
      ratiolumiee[M]->SetAxisRange(0,xLim);
      ratiolumiee[M]->Draw();
      //RunLumiee[M]->Draw();
      ratiolumiee[M]->GetXaxis()->SetTitle(hname);
      ratiolumiee[M]->GetYaxis()->SetTitle("lumi/ee");

      //MyC[M]->cd(4);
      // RunLumimm[M]->Draw();
      //ratiolumiee[M]->Divide(ratiolumimm[M]);
      //ratiolumiee[M]->Draw();
      if (WriteFile)
	{
	  if (M==0)  MyC[M]->Print("LumiCorFiles_eemm_ratio.ps");
	  else if (M==RunBin-1)MyC[M]->Print("LumiCorFiles_eemm_ratio.ps");
	  else   MyC[M]->Print("LumiCorFiles_eemm_ratio.ps");
	}

    }
  }

}

TH1F *proj;
const Int_t RunBinn = 1;
TH1F *NTriggers;
TH1F *RunTriggers[RunBin];
TH1F *RunLumi[RunBin];
TH1F *ratio[RunBin];
TH1F *RunLumiAv[RunBin];
TH1F *ratioCor[RunBin];
TH1F *ProjRatio[RunBin];
TH1F *LumiCor[RunBin];
TCanvas *MyC[RunBin];
TFile *ff;
TH1F *LumiAllCor;
TH1F *LumiMulCor;


void LumiCheck(bool WriteFile = false){

  Int_t RunForLumi[RunBin] = 
    {
      142130,142422,142528,142928,142933,142971,143007,143181,143328,143657,
      143727,143827,143833,143835,143953,143954,143962,144011,144086,144089,
      144112,146804,146807,146944,147043,147048,147114,147115,147196,147217,
      147219,147222,147284,147390,147450,147451,147754,147755,147757,148002,
      148029,148031,148032,148058,148822,148862,148864,148952,149011,149058,
      149063,149181,149182,149291,149294,149442
    };


      //      142130,142422,142528,142928,142933,142971,143181,143323,143657,143727,
      // 143827,143833,143953,143954,143961,143962,144011,144086,144089,144112,
      // 146804,146807,147043,147048,147114,147115,147284,147390,147450,147451,
      // 147453,147454,147754,147755,147757,148029,148031,148032,148862,148864,
      // 148952,148953,149003,149011,149058,149063,149181,149182,149291,149294

  ///{140361,142419,143326,143827,143833,143953,
  //		      144011,144089,144112,146804,147114,148029,
  //		      148862,148952,149003,149011,149181,149291};


  char hname[100]; 
  Int_t xLim = 3000;
  if(ff==0){
    //  sprintf(hname ,"Fraction_n_vertexes_files_ee10_NDOFGT2_EBGT50_runAB.root"); 


    readfile();
    ff = TFile::Open(DataFile); 
    if (RunListF == 1 || LumiCorF  == 1)
      {
	cout << "This macro can only be run on RunList ==0. Lumicor==0" << endl;
	return;
      }
    if (ff==0)
      {
	cout << "Problem with the input data file" << endl;
	return;
      }

    LumiMulCor = new TH1F("Correction_over_Mean","Correction_over_Mean",160, 0,2.);
    LumiAllCor = new TH1F("Relative Correction","Relative Correction",80, -0.6.,.6);
    
    for (Int_t M=0;M<RunBin;M++){
      // for (Int_t M=0;M<1;M++){
      sprintf(hname,"RunTriggers%i",M);
      RunTriggers[M] =   (TH1F*)ff->Get(hname);
      sprintf(hname,"RunLumi%i",M);
      RunLumi[M] =   (TH1F*)ff->Get(hname);
      if ( RunTriggers[M]  == 0 ||  RunLumi[M] == 0 )
	{
	  cout << "Problem with reading file " << hname << endl;
	  return;
	}
      sprintf(hname,"Ratio Lumi/events bin for run = %i",RunTriggers[M]);
      ratio[M] = NH1clone(hname,hname,RunLumi[0]);
      RunLumiAv[M] = NH1clone(hname,hname,RunLumi[0]);
      RunLumiAv[M]->Divide(RunLumi[M],RunTriggers[M]);
      ratio[M]->Divide(RunTriggers[M],RunLumiAv[M]);
      
      sprintf(hname,"Run %i",RunForLumi[M]);
      TCanvas *ALL = NCanvas(1,2,"All");
 
      MyC[M] = new TCanvas(hname,hname,M);
      MyC[M]->Divide(2,3);
      
      sprintf(hname,"Corrections for run %i",RunForLumi[M]);
      ProjRatio[M]= new TH1F(hname,hname, 400, 0.01,2000);
      
      sprintf(hname,"DivideLumiCor%i",RunForLumi[M]);
      LumiCor[M] = NH1clone(hname,hname,RunLumi[0]);
      
      sprintf(hname,"RatioCor%i",M);
      ratioCor[M] = NH1clone(hname,hname,RunLumi[0]);
    }
  }

  NTriggers =   (TH1F*)ff->Get("NTriggers");
  
  
  for (Int_t M=0;M<RunBin;M++){
    //  for (Int_t M=0;M<1;M++){
    

    
    MyC[M]->cd(1);
    RunTriggers[M]->SetAxisRange(0,xLim);
    RunTriggers[M]->Draw();
    RunTriggers[M]->GetXaxis()->SetTitle("Bunch Crossing");
    RunTriggers[M]->GetYaxis()->SetTitle("Events");
    MyC[M]->cd(2);
    //    RunLumi[M]->Divide(RunLumi[M], RunTriggers[M]);
    RunLumiAv[M]->Draw();
    RunLumi[M]->SetAxisRange(0,xLim);
    // RunLumi[M]->Scale(1./11346);
    RunLumiAv[M]->GetXaxis()->SetTitle("Bunch Crossing");
    RunLumiAv[M]->GetYaxis()->SetTitle("Average Luminosity");
    //cout << "total Lumi: "<< BxLumi->Integral()<<endl;
    
    MyC[M]->cd(3);
    ratio[M]->SetAxisRange(0,xLim);
    ratio[M]->Draw();
    ratio[M]->GetXaxis()->SetTitle("Bunch Crossing");
    ratio[M]->GetYaxis()->SetTitle("Events/<Lum>");
    Int_t Nbin = ratio[M]->GetNbinsX();
    for (Int_t i=1;i<Nbin; i++)
      if (ratio[M]->GetBinContent(i)>0) ProjRatio[M]->Fill(ratio[M]->GetBinContent(i));
    
    MyC[M]->cd(4);
    ProjRatio[M]->Draw();
    ProjRatio[M]->GetXaxis()->SetTitle("ratio");

    Float_t MaxB = ProjRatio[M]->GetBinCenter(ProjRatio[M]->GetMaximumBin());
    ProjRatio[M]->Fit("gaus"," ", "SAME",MaxB-50,MaxB+50);
    // ProjRatio[M]->Fit("gaus"," ", "SAME");
    //     cout << "mean = "<< gaus->GetParameter(1) << endl;

    Float_t ProjMean =  gaus->GetParameter(1);
    Float_t ProjRMS = ProjRatio[M]->GetRMS();
    if (ProjRMS>0) Float_t Ra =  gaus->GetParameter(2)/ProjRMS;
    sprintf(hname,"%4.2f",Ra);
    // NText(0.1,5,hname);
    if (ProjMean > 0.) Float_t RMSMean = ProjRMS/ProjMean;
    cout << RunForLumi[M] << " ProjMean= " << ProjMean << " Proj RMS = " << ProjRMS<<  " Ratio = " << RMSMean <<endl;
    for (Int_t i=1;i<=Nbin; i++){
      Float_t BinCon = ratio[M]->GetBinContent(i);
      Float_t BinErr = ratio[M]->GetBinError(i);
      if(BinCon>0.)
	{
	  if (fabs(BinCon-ProjMean)< 1.*BinErr && Ra <1.1  && ProjMean>0.) 
	    {
	      LumiCor[M]->SetBinContent(i,BinCon/ProjMean);
	      LumiCor[M]->SetBinError(i,ratio[M]->GetBinError(i)/ProjMean);
	      LumiAllCor->Fill((ProjMean-BinCon)/ProjMean);
	      LumiMulCor->Fill( BinCon/ProjMean );
	  //	  LumiMulCor->Fill( ProjMean/BinCon );
	    }

	}
    }
    
    MyC[M]->cd(5);
    LumiCor[M]->SetAxisRange(0,xLim);
    LumiCor[M]->Draw();
    LumiCor[M]->GetXaxis()->SetTitle("Bunch Crossing");
    LumiCor[M]->GetYaxis()->SetTitle("Correction Factor");    

    if (!WriteFile)
      {
	MyC[M]->cd(6);
	//    ratioCor[M]->Add(ratio[M]);
	ratioCor[M]->Divide(ratio[M],LumiCor[M]);
	//    ratioCor[M]->Scale(1./ProjMean);
	ratioCor[M]->Draw();
      }
  }

  All->cd(1);
  LumiAllCor->Draw();
  All->cd(2);
  LumiMulCor->Draw();



  if (WriteFile)
    {
      cout << "Writing New Lumi Correction File" << endl;

     TFile fCor(LumiCorFile,"recreate");     
      
      
      for (Int_t M=0;M<RunBin;M++){
	
	ratio[M]->Write();
	ProjRatio[M]->Write();
	LumiCor[M]->Write();
	RunLumi[M]->Write();
	RunTriggers[M]->Write();
	
      }
      
      LumiAllCor->Write();
      LumiMulCor->Write();
      
      fCor.Close();
    }

   for (Int_t M=0;M<RunBin;M++){
     if (eeF == 1) 
       {
	 if (M==0)  MyC[M]->Print("LumiCorFiles_ee.ps(");
	 else if (M==RunBin-1)MyC[M]->Print("LumiCorFiles_ee.ps)");
	 else   MyC[M]->Print("LumiCorFiles_ee.ps");
       }
     else if (eeF == 2)
       {
	 if (M==0)  MyC[M]->Print("LumiCorFiles_mm.ps(");
	 else if (M==RunBin-1)MyC[M]->Print("LumiCorFiles_mm.ps)");
	 else   MyC[M]->Print("LumiCorFiles_mm.ps");
       }
     
     else if (eeF == 3)
       {
	 if (M==0)  MyC[M]->Print("LumiCorFiles_eemm.ps(");
	 else if (M==RunBin-1)MyC[M]->Print("LumiCorFiles_eemm.ps)");
	 else   MyC[M]->Print("LumiCorFiles_eemm.ps");
       }
   }
    
}


void MCEff(Int_t NTrk = 3){


  char Fi2[3] = "CW";
  //char Fi2[3] = "P8";
  char Fi1[6] = "P8_CHA";
  // char Fi2[6] = "P8_ALL";


  readfile();

  if(fMC==0)
    {  // Data File //
     
      fMC = TFile::Open(MCMBFile);
      if (fMC == 0)
	{
	  cout << "Problem in opening the input files " << endl;
	  return;
	}
    }
  //

  if (NTrk == 2)
    {
      char temp[100] = "TracksGenEta2Pt200_w_";  
      TH1F *Fi1Gen200 =   (TH1F*)fMC->Get(strcat(temp,Fi1));  
      if ( Fi1Gen200==0) cout << " Fi1Gen200  " << endl;

      char temp1[100] = "TracksGenEta2Pt200_NDOFGT0_2tr_w_";  
      TH1F *Fi1Meas200 =   (TH1F*)fMC->Get(strcat(temp1,Fi1));  

      if ( Fi1Meas200==0) cout << " Fi1Meas200  " << endl;

      char temp2[100] = "TracksGenEta2Pt200_w_";  
      TH1F *Fi1Gen250 =   (TH1F*)fMC->Get(strcat(temp2,Fi1));  
      if ( Fi1Gen250 == 0) cout << " Fi1Gen250  " << endl;

      char temp3[100] = "TracksGenEta2Pt200_NDOFGT0_3tr_w_";  
      TH1F *Fi1Meas250 =   (TH1F*)fMC->Get(strcat(temp3,Fi1));  
      if (Fi1Meas250 ==0) cout << " Fi1Meas250  " << endl;

      char Temp[100] = "TracksGenEta2Pt200_w_";  
      TH1F *Fi2Gen200 =   (TH1F*)fMC->Get(strcat(Temp,Fi2));  
      char Temp1[100] = "TracksGenEta2Pt200_NDOFGT0_2tr_w_";  
      TH1F *Fi2Meas200 =   (TH1F*)fMC->Get(strcat(Temp1,Fi2));  
      char Temp2[100] = "TracksGenEta2Pt200_w_";  
      TH1F *Fi2Gen250 =   (TH1F*)fMC->Get(strcat(Temp2,Fi2));  
      char Temp3[100] = "TracksGenEta2Pt250_NDOFGT0_3tr_w_";  
      TH1F *Fi2Meas250 =   (TH1F*)fMC->Get(strcat(Temp3,Fi2));  
    }
  else if (NTrk == 3) 
    {
      
      char temp[100] = "TracksGenEta3Pt200_w_";  
      TH1F *Fi1Gen200 =   (TH1F*)fMC->Get(strcat(temp,Fi1));  
      char temp1[100] = "TracksGenEta3Pt200_NDOFGE2_w_";  
      TH1F *Fi1Meas200 =   (TH1F*)fMC->Get(strcat(temp1,Fi1));  
      char temp2[100] = "TracksGenEta3Pt250_w_";  
      TH1F *Fi1Gen250 =   (TH1F*)fMC->Get(strcat(temp2,Fi1));  
      char temp3[100] = "TracksGenEta3Pt250_NDOFGE2_w_";  
      TH1F *Fi1Meas250 =   (TH1F*)fMC->Get(strcat(temp3,Fi1));  
      

      char Temp[100] = "TracksGenEta3Pt200_w_";  
      TH1F *Fi2Gen200 =   (TH1F*)fMC->Get(strcat(Temp,Fi2));  
      char Temp1[100] = "TracksGenEta3Pt200_NDOFGE2_w_";  
      TH1F *Fi2Meas200 =   (TH1F*)fMC->Get(strcat(Temp1,Fi2));  
      char Temp2[100] = "TracksGenEta3Pt250_w_";  
      TH1F *Fi2Gen250 =   (TH1F*)fMC->Get(strcat(Temp2,Fi2));  
      char Temp3[100] = "TracksGenEta3Pt250_NDOFGE2_w_";  
      TH1F *Fi2Meas250 =   (TH1F*)fMC->Get(strcat(Temp3,Fi2));  
    }

  else if (NTrk == 4) // NDOF  = 0.5, 3 traks 
    {
      
      char temp[100] = "TracksGenEta2Pt200_w_";  
      TH1F *Fi1Gen200 =   (TH1F*)fMC->Get(strcat(temp,Fi1));  
      char temp1[100] = "TracksGenEtaPt200_NDOFGT05_2tr_w_";  
      TH1F *Fi1Meas200 =   (TH1F*)fMC->Get(strcat(temp1,Fi1));  
      char temp2[100] = "TracksGenEta2Pt200_w_";  
      TH1F *Fi1Gen250 =   (TH1F*)fMC->Get(strcat(temp2,Fi1));  
      char temp3[100] = "TracksGenEtaPt200_NDOFGT05_3tr_w_";  
      TH1F *Fi1Meas250 =   (TH1F*)fMC->Get(strcat(temp3,Fi1));  
      
      
      char Temp[100] = "TracksGenEta2Pt200_w_";  
      TH1F *Fi2Gen200 =   (TH1F*)fMC->Get(strcat(Temp,Fi2));  
      char Temp1[100] = "TracksGenEtaPt200_NDOFGT05_2tr_w_";  
      TH1F *Fi2Meas200 =   (TH1F*)fMC->Get(strcat(Temp1,Fi2));  
      char Temp2[100] = "TracksGenEta2Pt200_w_";  
      TH1F *Fi2Gen250 =   (TH1F*)fMC->Get(strcat(Temp2,Fi2));  
      char Temp3[100] = "TracksGenEtaPt200_NDOFGT05_3tr_w_";  
      TH1F *Fi2Meas250 =   (TH1F*)fMC->Get(strcat(Temp3,Fi2));  
    }

  else if (NTrk == 5) // NDOF  = 0.5, 3 traks, unweighted 
    {
      
      char temp[100] = "TracksGenEtaPt200_";  
      TH1F *Fi1Gen200 =   (TH1F*)fMC->Get(strcat(temp,Fi1));  
      char temp1[100] = "TracksGenEtaPt200_NDOFGT05_";  
      TH1F *Fi1Meas200 =   (TH1F*)fMC->Get(strcat(temp1,Fi1));  
      char temp2[100] = "TracksGenEtaPt250_";  
      TH1F *Fi1Gen250 =   (TH1F*)fMC->Get(strcat(temp2,Fi1));  
      char temp3[100] = "TracksGenEtaPt250_NDOFGT05_";  
      TH1F *Fi1Meas250 =   (TH1F*)fMC->Get(strcat(temp3,Fi1));  
      
      
      char Temp[100] = "TracksGenEtaPt200_";  
      TH1F *Fi2Gen200 =   (TH1F*)fMC->Get(strcat(Temp,Fi2));  
      char Temp1[100] = "TracksGenEtaPt200_NDOFGT05_";  
      TH1F *Fi2Meas200 =   (TH1F*)fMC->Get(strcat(Temp1,Fi2));  
      char Temp2[100] = "TracksGenEtaPt250_";  
      TH1F *Fi2Gen250 =   (TH1F*)fMC->Get(strcat(Temp2,Fi2));  
      char Temp3[100] = "TracksGenEtaPt250_NDOFGT05_";  
      TH1F *Fi2Meas250 =   (TH1F*)fMC->Get(strcat(Temp3,Fi2));  
    }





   TH1F *EffFi2_250 = NH1clone("Fraction of Generated vertexes detected","Fraction of recorded vertexes with $p_t >$ 200 or 250 MeV",Fi2Meas200);
   TH1F *EffCW_250 = NH1clone("Efficiency","Efficiency",Fi2Meas200);

   EffFi2_250->Sumw2();
   EffCW_250->Sumw2();
   EffFi2_250->SetMarkerColor(2);
   
   EffFi2_250->SetMinimum(0.);
   EffFi2_250->SetMaximum(1.2);
   EffFi2_250->GetXaxis()->SetTitle("Generated Multiplicity |eta|<2.4]");
   EffFi2_250->GetYaxis()->SetTitle("Efficiency");


  EffFi2_250->Add(Fi2Meas250);
  EffFi2_250->Divide(Fi2Gen250);

  EffCW_250->Add(Fi1Meas250);
  EffCW_250->Divide(Fi1Gen250);


  Int_t Nbin =EffFi2_250->GetNbinsX();
  cout << "Efficiency for "<< Fi2 << " pt>250 and Eta = " << MCEff_EtaCut << " : " << endl;
  

  for (Int_t j=0;j<16;j+=5)
    {
      for (Int_t i=1; i<6;i++)
	{
	  
	  cout << EffFi2_250->GetBinContent(i+j) <<",";
	}
      cout << endl;
    }

  cout << "Efficiency for "<< Fi1 << " pt>250  and Eta = " << MCEff_EtaCut << " : "<< endl;
  //  for (j=0;k
  for (Int_t j=0;j<16;j+=5)
    {
      for (Int_t i=1; i<6;i++)
	{
	  
	  cout << EffCW_250->GetBinContent(i+j) <<",";
	}
      cout << endl;
    }



  TH1F *EffFi2_200 = NH1clone("Fraction of Generated vertexes detected","Fraction of recorded vertexes with NDOF>=2 or NDOF>=3",Fi2Meas200);
  TH1F *EffCW_200 = NH1clone("Efficiency","Efficiency",Fi2Meas200);
  TH1F *Dif = NH1clone("Dif","Dif",Fi2Meas200);

  Dif->Sumw2();
  EffFi2_200->Sumw2();
  EffCW_200->Sumw2();

  EffFi2_200->SetMarkerColor(2);

  EffFi2_200->SetMinimum(0.);
  EffFi2_200->SetMaximum(1.2);

  EffFi2_200->GetXaxis()->SetTitle("Generated Multiplicity [pt>250 MeV, |eta|<2.4]");
  if (PtCut == 200)  EffFi2_250->GetXaxis()->SetTitle("Generated Multiplicity [pt>200 MeV, |eta|<2.4]");

  EffFi2_200->GetYaxis()->SetTitle("Efficiency");

  EffFi2_200->Add(Fi2Meas200);
  EffFi2_200->Divide(Fi2Gen200);

  EffCW_200->Add(Fi1Meas200);
  EffCW_200->Divide(Fi1Gen200);


  Dif->Add(EffFi2_200);
  Dif->Add(EffCW_200,-1);

  Int_t Nbin =EffFi2_200->GetNbinsX();
  cout << "Efficiency for "<< Fi2  << " 200 MeV  and Eta = " << MCEff_EtaCut << endl;
  for (Int_t j=0;j<16;j+=5)
    {
      for (Int_t i=1; i<6;i++)
	{
	  
	  cout << EffFi2_200->GetBinContent(i+j) <<",";
	}
      cout << endl;
    }

  cout << "Efficiency for " << Fi1 << "  200 MeV and Eta = " << MCEff_EtaCut << endl;
  //  for (j=0;k
  for (Int_t j=0;j<16;j+=5)
    {
      for (Int_t i=1; i<6;i++)
	{
	  
	  cout << EffCW_200->GetBinContent(i+j) <<",";
	}
      cout << endl;
    }


  TCanvas *NDOF2 = NCanvas(1,1,"NDOF2");
  TCanvas *NDOF1 = NCanvas(1,1,"NDOF1");
  TCanvas *NDOF3 = NCanvas(1,1,"NDOF3");






  NDOF3->cd(1);
  Dif->SetAxisRange(0,10);
  Dif->SetMaximum(0.15);
  Dif->SetMinimum(-0.15);
  Dif->Draw("p");
  Dif->GetXaxis()->SetTitle("Generated Track Multiplicity [pt>200 MeV, |eta|<2.4]");
  Dif->GetYaxis()->SetTitle("Efficiency difference");
  NLine(0,0,20,0);


  NDOF2->cd();
  EffFi2_250->SetAxisRange(0,10);
  NHSetMarker(EffFi2_250,2,20,1.);
  NHSetMarker(EffFi2_200,2,24,1.);
  EffFi2_250->SetMaximum(1.2);

  EffFi2_250->Draw("p");
  EffFi2_250->GetXaxis()->SetTitle("Generated Vertex Track Multiplicity [p_{t}> 200 MeV, |#eta|<2.4]");
  EffFi2_250->GetYaxis()->SetTitle("Vertex Reconstruction Efficiency [NDOF>0.5]");
  NLogAxis(0,0);
  
  EffFi2_200->Draw("pSAME");
  // NLine(0,1,12,1);


  TLegend *leg = new TLegend(0.4,0.2, 0.8 ,0.4);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  //leg->AddEntry(EffCW_200,"Pythia 6 CW 200 MeV","p");  
  // leg->AddEntry(EffCW_250,"Pythia 6 CW 250 MeV","p");
  leg->AddEntry(EffFi2_200,"Pythia8: At least 2 reconstructed tracks","p");
  leg->AddEntry(EffFi2_250,"Pythia8: At least 3 reconstructed tracks","p");
  leg->AddEntry(EffCW_200,"Pythia6 CW: At least 2 reconstructed tracks","p");
  leg->AddEntry(EffCW_250,"Pythia6 CW: At least 3 reconstructed tracks","p");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);  
  leg->SetFillColor(0);  
  leg->Draw();

  sprintf(CMSPrel,"CMS Simulation") ;
  NText(0.1,1.1,CMSPrel,1,0.07);


  NHSetMarker(EffCW_250,4,20,1.);
  NHSetMarker(EffCW_200,4,24,1.);
  EffCW_200->Draw("pSAME");
  EffCW_250->Draw("pSAME");
  NLine(0,1,12,1,2);

  //  NText(3,0.8,"pt>200");
  // NText(15,0.6,"pt >250");

  NDOF1->cd(1);
  NLogAxis(0,0);
  Fi1Gen200->SetAxisRange(1,30);
  //  Fi1Gen200->SetTitle("Pyhtia CW Track Multiplicity");
  NHSetMarker(Fi1Gen200,1,22,0.9);
  Fi1Gen200->Draw();
  Fi1Gen200->GetXaxis()->SetTitle("Generated Vertex Track Multiplicity [p_{t}> 200 MeV, |#eta|<2.4]");
  //  Fi1Gen200->GetXaxis()->SetTitle("Generated Multiplicity [pt>200 MeV, |eta|<2.4]");
  Fi1Gen200->GetYaxis()->SetTitle("Entries");

  //  Fi1Gen250->Draw("SAME");

  Fi1Gen200->SetMinimum(0);
  NHSetMarker(Fi1Meas200,2,20,0.9);
  Fi1Meas200->Draw("SAME");


  NHSetMarker(Fi1Meas250,4,24,0.9);
  Fi1Meas250->Draw("SAME");


  //  NDOF1->cd(2);

  //  NH1FArea1(Fi2Gen200);
  // NH1FArea1(Fi1Gen200);
  // NH1FArea1(Fi2Meas200);
  // NH1FArea1(Fi1Meas200);
  /*  NLogAxis(0,0);
  Fi2Gen200->SetAxisRange(1,30);
  Fi2Gen200->SetTitle("Pythia 8 Track Multiplicity");
  Fi2Gen200->Draw();
  Fi2Gen200->GetXaxis()->SetTitle("Generated Multiplicity [pt>200 MeV, |eta|<2.4]");
  Fi2Gen200->GetYaxis()->SetTitle("Entries");

  //  Fi1Gen250->Draw("SAME");

  Fi2Gen200->SetMinimum(0);
  NHSetMarker(Fi2Meas200,2,20,0.6);
  Fi2Meas200->Draw("SAME");

  NHSetMarker(Fi2Meas250,4,24,0.6);

*/


  cout << Fi1 << " Efficiency for 2 tracks at 200 MeV and Eta = " << MCEff_EtaCut << " : "<< Fi1Meas200->Integral(0,100)/Fi1Gen200->Integral(0,100) << endl;
  cout << Fi1 << " Efficiency for 3 tracks at 200 MeV and Eta = " << MCEff_EtaCut << " : "<< Fi1Meas250->Integral(0,100)/Fi1Gen250->Integral(0,100) << endl;


  cout << Fi2 <<" Efficiency for 2 tracks at 200 MeV and Eta = " << MCEff_EtaCut << " : "<< Fi2Meas200->Integral(0,100)/Fi2Gen200->Integral(0,100) << endl;
  cout << Fi2 << " Efficiency for 3 tracks at 200 MeV: and Eta = " << MCEff_EtaCut << " : "<< Fi2Meas250->Integral(0,100)/Fi2Gen250->Integral(0,100) << endl;

  NDOF1->cd(1);
  sprintf(CMSPrel,"CMS Simulation") ;
  NText(19,5000,CMSPrel,1,0.06);
  TLegend *leg1 = new TLegend(0.4,0.2, 0.6 ,0.4);
  leg1->AddEntry(Fi1Gen200,"Pythia 8 - Generated","p");  
  leg1->AddEntry(Fi1Meas200,"Pythia 8 - NDOF> 0.5 and 2 reconstructed tracks","p");
  leg1->AddEntry(Fi1Meas250,"Pythia 8 - NDOF> 0.5 and 3 reconstructed tracks","p");
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.04);  
  leg1->Draw();
  TLine *NLine = new TLine(2,0,2,1600);
  NLine->SetLineColor(2);
  NLine->SetLineStyle(2);
  NLine->Draw();
  TArrow *NArrow = new TArrow(2,1500,8,1500,0.02,">");
  NArrow->SetLineColor(2);
  NArrow->SetLineStyle(1);
  NArrow->Draw();
  NText(3.2,1750,"Eff= 93%",2);

  TLine *NLine1 = new TLine(3,0,3,1100);
  NLine1->SetLineColor(4);
  NLine1->SetLineStyle(4);
  NLine1->Draw();
  TArrow *NArrow1 = new TArrow(3,500,8,500,0.02,">");
  NArrow1->SetLineColor(4);
  NArrow1->SetLineStyle(1);
  NArrow1->Draw();
  NText(3.2,750,"Eff= 96%",4);



  

  return;
}

void PUMultiCheck(){

  Float_t PUArray[10];

  readfile();
  
  if(fData==0)
    {  // Data File //
      
      fData = TFile::Open(DataFile);
      
      if (fData==0 )
	{
	  cout << "Problem in opening the input files " << endl;
	  return;
	}
    }
  
  TH1F *Vertex1Mult =   (TH1F*)fData->Get("Vertex1Mult");
  TH1F *PUSim[15];
  TH1F *PUMeas[15];
  
  for (Int_t M=0;M<10;M++){
    sprintf(hname,"Pile-up = %i  Track Multiplicity",M);
    PUMeas[M] =  (TH1F*)fData->Get(hname);
    if (PUMeas[M] ==0) 
      {
	cout << "Missing file: " << hname << endl;
	return;
      }
    sprintf(hname,"Simulated and Measured Pile-up = %i  Track Multiplicity",M);
    PUSim[M] = NH1clone(hname,hname,Vertex1Mult);
    
  }
  

  TCanvas *Pileup = NCanvas(3,3, "Pileup");


  Int_t NPUMax;
  for (NPUMax = 1;NPUMax<9;NPUMax++)
    {
      for (Int_t jj = 1; jj<50000;jj++)
	{
	  
	  for (Int_t i=1; i<=NPUMax; i++)
	    {
	      PUArray[i] =    Vertex1Mult->GetRandom();
	    }
	  
	  
	  bubbleSort(PUArray,NPUMax+1);
	  PUSim[NPUMax]->Fill(PUArray[1]);
	  
	}
      Pileup->cd(NPUMax);
      NLogAxis(0,1);
      NH1FArea1(PUSim[NPUMax]);
      NH1FArea1(PUMeas[NPUMax]);
      PUSim[NPUMax]->SetAxisRange(0,40);      
      PUSim[NPUMax]->Draw();
      PUMeas[NPUMax]->Draw("PSAME");
      //      if (NPUMax ==1)
      //	{
      //	  NH1FArea1(Vertex1Mult);
      //	  Vertex1Mult->Draw("SAMEHIST");
      //	}
    }

  //  bubbleSort(float arr[], int n)
  //  for (Int_t i=1; i<=NPUMax; i++)
  // {
  //  cout << PUArray[i] << endl;
  // }

}

TFile *Fcor;
void AllCorrFact()
{
  
  TCanvas *My= NCanvas(1,1,"MyC");
  My->cd(2);

  if(Fcor==0)
    {      
      readfile();
      Fcor = TFile::Open(LumiCorFile); 
      LumiMulCor = (TH1F*)Fcor->Get("Correction_over_Mean");
      LumiAllCor = (TH1F*)Fcor->Get("Relative Correction");
      
    }
  if (Fcor==0 || LumiMulCor == 0 || LumiAllCor ==0 )
    {
      cout << "Problem with the input data file" << endl;
      return;
    }
  //  LumiAllCor->Draw();
  //LumiAllCor->Fit("gaus"," ","SAME ",-0.2,0.2);
  //LumiAllCor->GetXaxis()->SetTitle("(Mean - Correction Factor)/Mean");
  // LumiAllCor->GetYaxis()->SetTitle("Entries");
  //  NText(-0.55, 1780,"Relative Correction Factor");
  //  NText(UpLim, 200,"Luminosity too low");
  // NArrow(1.8,150,UpLim,50,0.02, ">");

  My->cd(1);
  gStyle->SetOptStat(0);
  LumiMulCor->SetStats(1);
  gStyle->SetOptFit(00100);
  LumiMulCor->Draw();
  LumiMulCor->SetMaximum(500);


  LumiMulCor->Fit("gaus"," ","SAMES");
  LumiMulCor->GetXaxis()->SetTitle("Correction Factor");
  LumiMulCor->GetYaxis()->SetTitle("Entries");
  NText(0.1, 450,"Luminosity correction factor");
  // NText(UpLim, 400,"Luminosity too low");
  // NArrow(1.8,350,UpLim,50,0.02, ">");

}

TGraphErrors *Sig;
void SigmaTot(){

  Float_t x[2];
  Float_t xmc[2];
  Float_t ex[2];
  Float_t y[2];
  Float_t yD6T[2];
  Float_t yP8[2];
  Float_t yPho[2];
  Float_t yS[2];
  Float_t yQ3[2];
  Float_t yQ4[2];
  Float_t yE[2];
  Float_t ey[2];
  Float_t eys[2];
  Float_t eyl[2];

  gDirectory->Delete("All1");
  TH1F *All1 =  new TH1F("All1","All1", 1, 0.1,0.3);
  NSetTitleSize(All1, .85,.8,0.06);
  All1->SetMinimum(50);
  All1->SetMaximum(75);

  All1->Draw();
  Sig = new TGraphErrors(2); 
  Sigs = new TGraphErrors(2); 
  Sigl = new TGraphErrors(2); 
  SigD6T = new TGraphErrors(2); 
  SigP8 = new TGraphErrors(2); 
  SigPho = new TGraphErrors(2); 
  SigQ4 = new TGraphErrors(2); 
  SigQ3 = new TGraphErrors(2); 
  SigS = new TGraphErrors(2); 
  SigE = new TGraphErrors(2); 

  //CMS
  
  x[0] = 0.2;
  x[1] = 0.25;

  xmc[0] = 0.203;
  xmc[1] = 0.253;

  ex[0] = 0;
  ex[1] = 0;


  y[0] = 56.4;
  y[1] = 54.9;

  ey[0] = 0.1;
  ey[1] = 0.1;

  eys[0] = 2.0;
  eys[1] = 2.0;

  eyl[0] = 2.4;
  eyl[1] = 2.4;


  yD6T[0] = 59.6;
  yD6T[1] = 57.2;

  yP8[0] = 61.9;
  yP8[1] = 60.9;

  yPho[0] = 71.8;
  yPho[1] = 70.5;


  yQ3[0] = 56.4;
  yQ3[1] = 55.7;

  yQ4[0] = 65.2;
  yQ4[1] = 64.6;

  yS[0] = 71.5;
  yS[1] = 71.0;

  yE[0] = 60.7;
  yE[1] = 59.0;

  for (Int_t N=0,; N<2;N++)
    {
      Sig->SetPoint(N,x[N],y[N]);
      Sig->SetPointError(N,ex[N],ey[N]);
      Sigs->SetPoint(N,x[N],y[N]);
      Sigs->SetPointError(N,ex[N],eys[N]);
      Sigl->SetPoint(N,x[N],y[N]);
      Sigl->SetPointError(N,ex[N],eyl[N]);
      SigD6T->SetPoint(N,xmc[N],yD6T[N]);
      SigD6T->SetPointError(N,ex[N],ey[N]);
      SigP8->SetPoint(N,xmc[N],yP8[N]);
      SigP8->SetPointError(N,ex[N],ey[N]);
      SigPho->SetPoint(N,xmc[N],yPho[N]);
      SigPho->SetPointError(N,ex[N],ey[N]);
      SigQ3->SetPoint(N,xmc[N],yQ3[N]);
      SigQ3->SetPointError(N,ex[N],ey[N]);
      SigQ4->SetPoint(N,xmc[N],yQ4[N]);
      SigQ4->SetPointError(N,ex[N],ey[N]);
      SigS->SetPoint(N,xmc[N],yS[N]);
      SigS->SetPointError(N,ex[N],ey[N]);
      SigE->SetPoint(N,xmc[N],yE[N]);
      SigE->SetPointError(N,ex[N],ey[N]);
    }


  Float_t PSiz = 1.7;
  Sig->SetMarkerColor(2);   
  Sig->SetMarkerSize(PSiz);   
  Sig->SetMarkerStyle(20);

  Sigs->SetMarkerColor(2);   
  Sigs->SetMarkerSize(PSiz);   
  Sigs->SetMarkerStyle(20);
  Sigs->SetLineColor(2);
  Sigs->SetLineWidth(3.);

  Sigl->SetMarkerColor(2);   
  Sigl->SetMarkerSize(PSiz);   
  Sigl->SetMarkerStyle(20);
  Sigl->SetLineStyle(1);
  Sigl->SetLineWidth(3.);

  Sig->Draw("p");
  Sigl->Draw("pe1");
  Sigs->Draw("p");


  SigD6T->SetMarkerSize(PSiz);   
  SigD6T->SetMarkerColor(3);
  SigD6T->SetMarkerStyle(21);;   
  SigD6T->Draw("p");


  SigP8->SetMarkerSize(PSiz);   
  SigP8->SetMarkerColor(4);   
  SigP8->SetMarkerStyle(22);;   
  SigP8->Draw("p");

  SigPho->SetMarkerSize(PSiz);   
  SigPho->SetMarkerStyle(23);;   
  SigPho->SetMarkerColor(6);   
  SigPho->Draw("p");



  SigQ3->SetMarkerSize(PSiz);   
  SigQ3->SetMarkerStyle(24);;   
  SigQ3->SetMarkerColor(7);   
  SigQ3->Draw("p");



  SigQ4->SetMarkerSize(PSiz);   
  SigQ4->SetMarkerStyle(25);;   
  SigQ4->SetMarkerColor(8);   
  SigQ4->Draw("p");


  SigS->SetMarkerSize(PSiz);   
  SigS->SetMarkerStyle(26);;   
  SigS->SetMarkerColor(9);   
  SigS->Draw("p");

  SigE->SetMarkerSize(PSiz);   
  SigE->SetMarkerStyle(27);;   
  SigE->SetMarkerColor(1);   
  SigE->Draw("p");


  sprintf(CMSPrel,"CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}") ;
  NText(0.11,73,CMSPrel,1,0.05);

  TLegend *leg = new TLegend(0.2,0.2, 0.35 ,0.5);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Sig,"CMS Preliminary","p");  
  leg->AddEntry(SigD6T,"PYTHIA D6T","p");
  leg->AddEntry(SigP8,"PYTHIA8","p");
  leg->AddEntry(SigPho,"PHOJET","p");
  leg->AddEntry(SigQ3,"QGSJET-II-03","p");
  leg->AddEntry(SigQ4,"QGSJET-II-04","p");
  leg->AddEntry(SigS,"SIBYLL-2.1","p");
  leg->AddEntry(SigE,"EPOS","p");

  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);  
  leg->SetFillColor(0);
  leg->Draw();

  All1->GetXaxis()->SetTitle("Minimum p_{t} [MeV]");
  All1->GetYaxis()->SetTitle("#sigma [mb]");
  NText(0.11,75.2,"Inelastic pp cross section for events with at least 3 charged particles  in |#eta| < 2.4",1,0.04);


  return;

}



void SigmaTotPart(){

  Float_t x[3];
  Float_t xmc[3];
  Float_t ex[3];
  Float_t y[3];
  Float_t yD6T[3];
  Float_t yP8[3];
  Float_t yPho[3];
  Float_t yQGS[3];
  Float_t yS[3];
  Float_t yQ3[3];
  Float_t yQ4[3];
  Float_t yE[3];
  Float_t ey[3];
  Float_t eys[3];
  Float_t eyl[3];

  gDirectory->Delete("All1");
  TH1F *All1 =  new TH1F("All1","All1", 1, 0.,5);
  NSetTitleSize(All1, .85,.8,0.06);
  All1->SetMinimum(50);
  All1->SetMaximum(75);
  All1->GetXaxis()->SetNdivisions(109);
  All1->Draw();
  Sig = new TGraphErrors(3); 
  Sigs = new TGraphErrors(3); 
  Sigl = new TGraphErrors(3); 
  SigD6T = new TGraphErrors(3); 
  SigP8 = new TGraphErrors(3); 
  SigPho = new TGraphErrors(3); 
  SigQ4 = new TGraphErrors(3); 
  SigQ3 = new TGraphErrors(3); 
  SigS = new TGraphErrors(3); 
  SigE = new TGraphErrors(3); 
  SigQGS = new TGraphErrors(3); 

  //CMS
  

  x[0] = 2;
  x[1] = 3;
  x[2] = 4;




  xmc[0] = 2.1;
  xmc[1] = 3.1;
  xmc[2] = 4.1;

  ex[0] = 0;
  ex[1] = 0;
  ex[2] = 0;


  y[0] = 58.7;
  y[1] = 57.2;
  y[2] = 55.4;

  ey[0] = 0.;
  ey[1] = 0.;
  ey[2] = 0.;

  eys[0] = 2.0;
  eys[1] = 2.0;
  eys[2] = 2.0;

  eyl[0] = 2.4;
  eyl[1] = 2.4;
  eyl[2] = 2.4;


  yD6T[0] = 64.2;
  yD6T[1] = 62.8;
  yD6T[2] = 61.0;

  yP8[0] = 64.6;
  yP8[1] = 61.9;
  yP8[2] = 60.8;


  yPho[0] = 0;
  yPho[1] = 71.8;
  yPho[2] = 70.5;


  yQGS[0] = 60.0;
  yQGS[1] = 57.6;
  yQGS[2] = 55.2;


  yQ4[0] = 57.8;
  yQ4[1] = 56.4;
  yQ4[2] = 54.2;


  yQ3[0] = 67.0;
  yQ3[1] = 65.2;
  yQ3[2] = 63.0;

  yS[0] = 72.5;
  yS[1] = 71.5;
  yS[2] = 70.2;

  yE[0] = 61.9;
  yE[1] = 60.7;
  yE[2] = 59.0;

  for (Int_t N=0,; N<3;N++)
    {
      Sig->SetPoint(N,x[N],y[N]);
      Sig->SetPointError(N,ex[N],ey[N]);
      Sigs->SetPoint(N,x[N],y[N]);
      Sigs->SetPointError(N,ex[N],eys[N]);
      Sigl->SetPoint(N,x[N],y[N]);
      Sigl->SetPointError(N,ex[N],eyl[N]);
      SigD6T->SetPoint(N,xmc[N],yD6T[N]);
      SigD6T->SetPointError(N,ex[N],ey[N]);
      SigP8->SetPoint(N,xmc[N],yP8[N]);
      SigP8->SetPointError(N,ex[N],ey[N]);
      SigPho->SetPoint(N,xmc[N],yPho[N]);
      SigPho->SetPointError(N,ex[N],ey[N]);
      SigQ3->SetPoint(N,xmc[N],yQ3[N]);
      SigQ3->SetPointError(N,ex[N],ey[N]);
      SigQGS->SetPoint(N,xmc[N],yQGS[N]);
      SigQ4->SetPoint(N,xmc[N],yQ4[N]);
      SigQ4->SetPointError(N,ex[N],ey[N]);
      SigS->SetPoint(N,xmc[N],yS[N]);
      SigS->SetPointError(N,ex[N],ey[N]);
      SigE->SetPoint(N,xmc[N],yE[N]);
      SigE->SetPointError(N,ex[N],ey[N]);
    }


  Float_t PSiz = 1.7;
  Sig->SetMarkerColor(2);   
  Sig->SetMarkerSize(PSiz);   
  Sig->SetMarkerStyle(20);

  Sigs->SetMarkerColor(2);   
  Sigs->SetMarkerSize(PSiz);   
  Sigs->SetMarkerStyle(20);
  Sigs->SetLineColor(2);
  Sigs->SetLineWidth(3.);

  Sigl->SetMarkerColor(2);   
  Sigl->SetMarkerSize(PSiz);   
  Sigl->SetMarkerStyle(20);
  Sigl->SetLineStyle(1);
  Sigl->SetLineWidth(3.);

  Sig->Draw("p");
  Sigl->Draw("pe1");
  Sigs->Draw("p");


  SigD6T->SetMarkerSize(PSiz);   
  SigD6T->SetMarkerColor(3);
  SigD6T->SetMarkerStyle(21);;   
  SigD6T->Draw("p");


  SigP8->SetMarkerSize(PSiz);   
  SigP8->SetMarkerColor(4);   
  SigP8->SetMarkerStyle(22);;   
  SigP8->Draw("p");

  SigPho->SetMarkerSize(PSiz);   
  SigPho->SetMarkerStyle(23);;   
  SigPho->SetMarkerColor(6);   
  SigPho->Draw("p");



  SigQ3->SetMarkerSize(PSiz);   
  SigQ3->SetMarkerStyle(24);;   
  SigQ3->SetMarkerColor(7);   
  SigQ3->Draw("p");



  SigQ4->SetMarkerSize(PSiz);   
  SigQ4->SetMarkerStyle(25);;   
  SigQ4->SetMarkerColor(8);   
  SigQ4->Draw("p");


  SigS->SetMarkerSize(PSiz);   
  SigS->SetMarkerStyle(26);;   
  SigS->SetMarkerColor(9);   
  SigS->Draw("p");

  SigE->SetMarkerSize(PSiz);   
  SigE->SetMarkerStyle(27);;   
  SigE->SetMarkerColor(1);   
  SigE->Draw("p");


  SigQGS->SetMarkerSize(PSiz);   
  SigQGS->SetMarkerStyle(28);;   
  SigQGS->SetMarkerColor(1);   
  SigQGS->Draw("p");


  sprintf(CMSPrel,"CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}") ;
  NText(0.11,75.1,CMSPrel,1,0.05);

  TLegend *leg = new TLegend(0.2,0.2, 0.35 ,0.5);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Sig,"CMS Preliminary","p");  
  leg->AddEntry(SigD6T,"PYTHIA6","p");
  leg->AddEntry(SigP8,"PYTHIA8","p");
  leg->AddEntry(SigPho,"PHOJET","p");
  leg->AddEntry(SigQ3,"QGSJET-II-03","p");
  leg->AddEntry(SigQ4,"QGSJET-II-04","p");
  leg->AddEntry(SigS,"SIBYLL-2.1","p");
  leg->AddEntry(SigE,"EPOS","p");
  leg->AddEntry(SigQGS,"QGS-01","p");

  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);  
  leg->SetFillColor(0);
  leg->Draw();
  All1->GetXaxis()->SetTitle(" Minimum Number of Charged Particles [p_{t} > 200 MeV, |#eta| < 2.4]");
  All1->GetYaxis()->SetTitle("#sigma [mb]");
  //  NText(0.11,75.2,"Inelastic pp cross section",1,0.04);


  return;

}


Float_t ReadEfficiency()
{

  cout << "Reading Efficiency vector for eta = " << MCEff_EtaCut << " and File " << TrkEffF << endl; 

  if (SelNDOF == 2 && PtCut == 200)
    {
      if (TrkEffF == 1 && MCEff_EtaCut == (float) 2.4 ) // Old-CW eta<2.4
	{
	 Float_t  dummy[20] = 
	    {
	      0,0,0,0.342645,0.615709,
	      0.791384,0.898148,0.946139,0.974808,0.9892,
	      0.995775,0.997288,0.998715,0.999119,0.999813,
	      1,1,1,1,1
	      // NO cut on position
	      //	      0,0,0,0.245846,0.526735,
	      //0.742659,0.878747,0.937515,0.971304,0.988416,
	      //0.995133,0.997227,0.998636,0.998978,0.999738,
	      //1,1,1,1,1
	    };
	}
      
      else if (TrkEffF == 2  && MCEff_EtaCut == (float ) 2.4) // P8 eta <2.4
	{
	 Float_t  dummy[20] =  
	    {
	      0,0,0,0.337742,0.527963,
	      0.713161,0.815423,0.899401,0.942188,0.965994,
	      0.979332,0.990599,0.996548,0.998502,0.998861,
	      0.999385,0.999545,1,0.998775,0.99895
	    };
	}
      
      
      else if (TrkEffF == 3)// New-P8Charged eta<2.6
	{
	  if (MCEff_EtaCut > 2.5) 
	    {
	     Float_t  dummy[20] =  
		{
		  0,0,0,0.306486,0.597514,
		  0.779859,0.887444,0.942707,0.976125,0.986989,
		  0.994854,0.997172,0.999105,0.999352,0.999645,
		  0.999807,0.99958,0.999539,0.999752,1
		  //without cut on good position
		  //		  0,0,0,0.308123,0.599133,
		  //0.780509,0.88839,0.943198,0.976419,0.987129,
		  //0.994854,0.997172,0.999105,0.999352,0.999645,
		  //0.999807,0.99958,0.999539,0.999752,1
		};
	    }
	  else if (MCEff_EtaCut < 2.5) 
	    {
	     Float_t  dummy[20] =  
		{
		  0,0,0,0.42602,0.702232,
		  0.847306,0.927749,0.97086,0.987909,0.994581,
		  0.997242,0.99958,0.999552,0.999494,0.999634,
		  0.999801,0.999784,0.999765,1,0.999727
		  //without cut on good position
		  //		  0,0,0,0.427485,0.703828,
		  //0.84826,0.92823,0.971144,0.988043,0.994581,
		  //0.997242,0.99958,0.999552,0.999494,0.999634,
		  //0.999801,0.999784,0.999765,1,0.999727
		};

	    }
	}
      else if (TrkEffF == 4) // New-P8All, eta<2.6
	{
	  if (MCEff_EtaCut == (Float) 2.6) 
	    {
	     Float_t  dummy[20] =  
		{
		  0,0,0,0.0699345,0.191664,
		  0.350156,0.483037,0.580716,0.706968,0.779358,
		  0.837157,0.882898,0.91992,0.936666,0.960071,
		  0.968844,0.982,0.987059,0.990128,0.994722
		  //Without cut on good vtx pos
		  //		  0,0,0,0.0699355,0.192948
		  // 0.351334,0.483596,0.581215,0.707836,0.780451,
		  // 0.838101,0.883183,0.920694,0.937373,0.960295,
		  // 0.969282,0.98222,0.987064,0.990128,0.994964
		};
	    }
	  else if (MCEff_EtaCut == (Float) 2.4) 
	    {
	     Float_t  dummy[20] =  
		{
		  0,0,0,0.146527,0.276517,
		  0.431529,0.571995,0.687198,0.769631,0.832827,
		  0.886753,0.919503,0.938276,0.960629,0.979915,
		  0.983887,0.987622,0.993212,0.998838,0.996834
		  //without cut on good position
		  // 0,0,0,0.146529,0.278901,
		  //0.432064,0.572951,0.687623,0.769649,0.835254,
		  //0.887021,0.919743,0.939164,0.960825,0.980316,
		  // 0.983888,0.987624,0.993434,0.998838,0.996835
		};	     
	    }
	}

    }
  
  else if (SelNDOF == 2 && PtCut == 250)
    {
     Float_t  dummy[20] =   // vertex Efficiency array Reweighted (Z2)
	{
	  0,0,0,0.24107,0.456026,
	  0.670681,0.814656,0.902289,0.95044,0.974966,
	  0.987707,0.993123,0.997788,0.998331,0.999262,
	  1,0.999786,1,1,1
	  //	  6.31605e-05,0.0116355,0.0708339,0.187598,0.342431,
	  // 0.479881,0.640639,0.745975,0.823077,0.888743,
	  // 0.92317,0.947348,0.968029,0.986463,0.991285,
	  // 0.993724,0.997751,0.99557,0.998015,0.998701
	  // 0.00010918,0.00958729,0.0564136,0.15289,0.292977,
	  // 0.461493,0.616584,0.740512,0.826024,0.891834,
	  // 0.932528,0.95458,0.971623,0.983424,0.99111,
	  // 0.994457,0.996454,0.996889,0.998544,0.999363
	};
      if (SystCheck == 14)
	{
	 Float_t  dummy[20] =   // vertex Efficiency array Reweighted (Z2)
	    {
	      0,0,0,0.367357,0.554704,
	      0.726086,0.817245,0.895899,0.937393,0.964122,
	      0.978642,0.989445,0.99643,0.99824,0.998949,
	      0.999402,0.999419,1,0.998855,0.999115
	    };
	}


    }
  else if (SelNDOF == 3 && PtCut == 200)
    {
     Float_t  dummy[20] =   // vertex Efficiency array Reweighted (Z2)
	{
	  0,0,0.00359288,0.0130714,0.0515917,
	  0.124751,0.215837,0.325146,0.474203,0.581261,
	  0.673725,0.748549,0.80563,0.866277,0.9038,
	  0.942375,0.95723,0.978127,0.983553,0.983155
	};
    }

  else if (SelNDOF == 3 && PtCut == 250)
    {
     Float_t  dummy[20] =   // vertex Efficiency array Reweighted (Z2)
	{
	  0,0.00155446,0.0131655,0.0426287,0.117015,
	  0.214614,0.365213,0.518457,0.641361,0.729362,
	  0.811376,0.874637,0.910823,0.951034,0.96775,
	  0.979241,0.988861,0.982491,0.993677,1.
	};
    }

  else if (SelNDOF == (float) 0.1)
    {
     Float_t  dummy[20] =   // vertex Efficiency array Reweighted (Z2)
	{
	  0,0.00155446,0.0131655,0.0426287,0.117015,
	  0.214614,0.365213,0.518457,0.641361,0.729362,
	  0.811376,0.874637,0.910823,0.951034,0.96775,
	  0.979241,0.988861,0.982491,0.993677,1.
	};
    }


  else    
    {
      if (SelNDOF >=4 || SelNDOF ==1 || SelNDOF == (float) 0.5 || SelNDOF == (float) 2.5 ) 
       Float_t  dummy[20] = {1.};
     else
       {
	 Float_t  dummy[20] = {0.0};  
	 cout << " No MC Efficiency, need to stop :-( " << endl;
	 
	 return();
       }
    };

  cout << "Read Eff. vector " << endl;
  std::copy(dummy,dummy+sizeof(dummy)/sizeof(*dummy),VtxMult_Eff);

  return ();
}
