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

TH1F *Vtx_Sigma;
TH1F *Vtx_Chi2;
Float_t  sigma;
Float_t Chi2;
Float_t Chi2err;
Float_t  errsigma;

 
TH1F *Nvtx_cor[15];
TH1F *Nvtx_No_cor[15];
TFile *f;
TFile *fc;
TH1F *Dat_all_Lumi;
TH1F *NTriggers;
TH1F *BxLumi;
TGraphErrors *RatFit;

char DataInputFile[100]; 

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

Int_t vertex(Int_t vtx, Int_t FlagScale=1){

  char hname[100]; 
  char Effhname[100]; 

  // Open two files 

  if(f==0 || vtx == 1)
    {  // Data File //

      readfile();
      f = TFile::Open(DataFile); 
      if (f==0){
	cout << "Vertex: Problem in opening  data file = " << DataFile << endl;
	return;
      }
    }
  

  if (fc == 0 || vtx==1 ){ //Migration File //

    fc = TFile::Open(MigrationFile);
    if (fc==0){
      cout << "Vertex: problem in opening migration file  = " << MigrationFile << endl;
      return(1);
    }
  }

  if (Dat_all_Lumi==0){

    //    cout << "DataInputFile= "<< DataInputFile<< endl;
    //cout << "NameMigrationFile= "<< NameMigrationFile<< endl;


    Dat_all_Lumi =   (TH1F*)f->Get("Dat_all_Lumi");
    Int_t Nbinx = Dat_all_Lumi->GetNbinsX();
    
    Float_t AllEvt = Dat_all_Lumi->Integral();
    cout << " Total number of Events = " << AllEvt << endl;
    
    
    gDirectory->Delete("RatFit");
    
    //  TH1F *RatFit = new TH1F("RatFit","RatFit",1000,0.,0.7);
    //Read the luminosity bins
    
    for (Int_t N=1;N<=LumBin; N++){
      sprintf(hname,"LumiBin%i",N);
      LumiBin[N] = (TH1F*)f->Get(hname);
      AllEvt = LumiBin[N]->Integral();
      cout << " Number of Events in Lumi bin " << N << " = " << AllEvt << " with mean Lumi = " << LumiBin[N]->GetMean() << endl;
    }
  }
  
  Int_t   BinConVtx;
  Float_t  ErrBinConVtx;
  Float_t  NewBinConVtx;
  Int_t BinConVtxp1;
  Float_t x[14];
  Float_t ex[14];
  Float_t y[14];
  Float_t ey[14];
  
  stringstream stringa;
  stringstream stringam1;
  
  stringa<<vtx;
  Int_t vtxm1 = vtx-1;
  stringam1<<vtxm1;
  
  string cut = "istlumiPerBX*6.37>0.05 && numberOfVertexes=="+stringa.str();
  string title = "Instantaneous lumi per bx for events with "+stringa.str()+" vxt";
  string name = "vxt"+stringa.str();
  string fill = "istlumiPerBX*6.37>>"+name;
  string rat1_title = "Fraction of events with "+stringa.str()+ " vertexes";  
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
      Nvtx_cor[vtx] =  NH1clone(hname,hname,Dat_all_Lumi);
      sprintf(Effhname,"Eff_%iNvtx",0); // use this definition for all migration files RunList_LumiCor
      sprintf(hname,"Vtx1_HF0");     
    }    
  else
    {
      sprintf(hname,"Nvtx%i_cor",vtx);
      Nvtx_cor[vtx] =  NH1clone(hname,hname,Dat_all_Lumi);
      sprintf(Effhname,"Eff_%iNvtx",vtx-1); // use this definition for all migration files RunList_LumiCor
      sprintf(hname,"Vxt_Lumi%i",vtx);      
    }

  TH1F *rat1 =  NH1clone(rat1_name,rat1_title.c_str(),Dat_all_Lumi);

  // Note: vxt is the total number of vertexes while Eff_corr refers to the pile-up
  // so it's necessary to subtract 1  
  // sprintf(hname,"Eff_%iNvtx",vtx-1);


  cout << "Opening Data plot " << hname << endl;  
  Nvtx_No_cor[vtx] =   (TH1F*)f->Get(hname);

  cout << "Opening Efficiency Plot " << Effhname << endl;
  TH1F * Eff_corr = (TH1F*)fc->Get(Effhname);




  
  // cout <<"Bin 6 before correction: "<<  Nvtx_No_cor[vtx]->GetBinContent(6)<< endl;
  // cout <<"Bin 8 before correction: "<<  Nvtx_No_cor[vtx]->GetBinContent(8)<< endl;  
  // cout <<"Bin 6 Eff. correction: "<<  Eff_corr->GetBinContent(6)<< endl;   
  // cout <<"Bin 8 Eff. correction: "<<  Eff_corr->GetBinContent(8)<< endl;
  
  
  if (FlagScale==1) 
    {
      Nvtx_cor[vtx]->Divide(Nvtx_No_cor[vtx],Eff_corr);
      if(vtx==10)
	{
	  rat1->Divide(Nvtx_cor[vtx], Nvtx_No_cor[1],1.,1.,"B"); 
	}
      else
	{
	  rat1->Divide(Nvtx_cor[vtx],Dat_all_Lumi,1.,1.,"B"); 
	}
    }
  else
    {
      rat1->Divide(Nvtx_No_cor[vtx],Dat_all_Lumi,1.,1.,"B"); 
    }
  

  RatFit = new TGraphErrors(14); 

  Int_t M=0;
  for (Int_t N=1,; N<=14;N++){
    x[N]=0;
    ex[N]=0;
    y[N]=0;
    ey[N]=0;
    if (rat1->GetBinContent(N)>0.)
      {
	
	x[N] = LumiBin[N]->GetMean();
	ex[N] = LumiBin[N]->GetMeanError();
	y[N] = rat1->GetBinContent(N);
	ey[N] = rat1->GetBinError(N);
	RatFit->SetPoint(N,x[N],y[N]);
	RatFit->SetPointError(N,ex[N],ey[N]);
	
      }
  }
  


  RatFit->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  RatFit->GetYaxis()->SetTitle("Fraction");

  NLogAxis(0,1);
  RatFit->SetMarkerColor(2);   
  RatFit->SetMarkerSize(1.);   
  RatFit->SetMarkerStyle(20);

  RatFit->Draw("p");

  //Initialize the Pois. Function

  if (vtx==10)  
    {
      TF1 *pois1 = new TF1("pois1",prob_vtx1,0.0,0.6,2); // x in [0.1;0.6], 2 parameters
      pois1->SetParName(1,"Intercept:");

      TF1 *pois2 = new TF1("pois2",prob_vtx2,0.0,0.6,2); // x in [0.1;0.6], 2 parameters
      pois2->SetParName(1,"Intercept:");
      pois2->SetParName(0,"Sigma");
      pois2->SetParameter(0,0.05);
    }
  else
    {
    TF1 *pois1 = new TF1("pois1",prob_pois,0.0,0.6,2); // x in [0.1;0.6], 2 parameters
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
  gStyle->SetOptFit(110);
  
  //  RatFit>SetStats(0);
  RatFit->Fit("pois1","I","SAMES",0.08,0.61);
  if (vtx==10) {
    pois2->SetLineStyle(2);
    pois2->SetLineColor(1);
    pois2->SetLineWidth(0.4);
    //TH1F *RatFit2 = RatFit->Clone();
    // RatFit2->Draw("SAMEp");
       RatFit->Fit("pois2","I","SAMES",0.08,0.61);
  }

  sigma = 1000*pois1->GetParameter(0);
  errsigma =  1000*pois1->GetParError(0);
  Chi2 = pois1->GetChisquare()/pois1->GetNDF();  
  cout << pois1->GetNDF() << endl;
  Vtx_Sigma->SetBinContent(vtx,sigma);
  Vtx_Sigma->SetBinError(vtx,errsigma);
  Vtx_Chi2->SetBinContent(vtx,Chi2);
  sprintf(hname,"Residual for PU = %i",vtxm1);
  TH1F *Resid = NH1clone(hname,hname,rat1);
  Resid->Add(pois1,-1.);
  Resid->Add(rat1,1.);
  Resid->Divide(rat1);
  NHSetMarker(Resid,2,20,1.2);
  if (vtx==10) Res->cd(9);
  else  Res->cd(vtx);
  NLogAxis(0,0);
  Resid->Draw();
  return;


}

// Loops over vertex()
void all(Int_t Flag=1){

  // gROOT->Reset();

  Int_t FlagScale = Flag;
 
  gDirectory->Delete("Vtx_Sigma");
  gDirectory->Delete("Vtx_Chi2");
  gDirectory->Delete("ee_pt>10GeV");

  Vtx_Sigma = new TH1F("Vtx_Sigma","Vtx_Chi", 9,0.5,9.5);
  Vtx_Chi2 = new TH1F("Vtx_Chi2","Vtx_Chi", 9,0.5,9.5);
 
  TH1F *All0 =  new TH1F("ee_pt>10GeV ","Fraction of Events with 0 Pile-Up events",14,0.,0.7);
  All0->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All0->GetYaxis()->SetTitle("Fraction");

  TH1F *All1 =  new TH1F("ee_pt>10GeV ","Fraction of Events with 1 Pile-Up events",14,0.,0.7);
  All1->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All1->GetYaxis()->SetTitle("Fraction");

  TH1F *All2 =  new TH1F("ee_pt>10GeV ","Fraction of Events with 2 Pile-Up events",14,0.,0.7);
  All2->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All2->GetYaxis()->SetTitle("Fraction");

  TH1F *AllN =  new TH1F("ee _pt>10 GeV ","Fraction of Events with 3-8 Pile-Up events",14,0.,0.7);
  AllN->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  AllN->GetYaxis()->SetTitle("Fraction");

  TH1F *AllHF0 =  new TH1F("ee _pt>10 GeV ","Fraction of Events with HF=0",14,0.,0.7);
  AllHF0->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  AllHF0->GetYaxis()->SetTitle("Fraction");


  TCanvas *Res = new TCanvas("Res","Res",1);
  Res->Divide(3,3);

  TCanvas *HF0 = new TCanvas("HF0","HF0",1);
  HF0->Divide(1,1);
    

  TCanvas *MyC = NCanvas(2,2);


  MyC->cd(1);
  All0->SetMinimum(0.03);
  All0->SetMaximum(1.1);
  All0->Draw();
  NLogAxis(0,1);
  MyC->cd(2);
  All1->SetMinimum(0.15);
  All1->SetMaximum(0.4);
  All1->Draw();
  MyC->cd(3);
  All2->SetMinimum(0.04);
  All2->SetMaximum(0.4);
  All2->Draw();
  MyC->cd(4);
  AllN->SetMinimum(0.00001);
  AllN->SetMaximum(2.);
  AllN->Draw();
  NLogAxis(0,1);


   for (Int_t i=1;i<11;i++){ // to see HF=0
     //   for (Int_t i=1;i<10;i++){
    //  MyC->cd(i);
    if (i==1) {
      MyC->cd(1);
    }
    else if (i==2) {
      MyC->cd(2);
    }
    else if (i==3) {
      MyC->cd(3);
    }
    else if (i>3 && i <10 ){
      MyC->cd(4);
    }
    else if (i=10){
      HF0->cd(1);
      AllHF0->SetMinimum(0.0002);
      AllHF0->SetMaximum(0.007);
      AllHF0->Draw();
      NLogAxis(0,1);
    }
    gStyle->SetOptFit(0);
    gStyle->SetOptFit(0111);
    //    if (vertex(i,FlagScale) == 1) return;;
    vertex(i,FlagScale);
  }

  MyC->cd(1);
  NText(0.5, .5,"PU=0");
  MyC->cd(2);
  NText(0.5, 0.08,"PU=1");
  MyC->cd(3);
  NText(0.5, 0.1,"PU=2");
  MyC->cd(4);
  NText(0.1, 0.2,"PU=3 - 8");


   Sigma();
  return;
}




//show the Sigma and Chi2for all PU

void Sigma(){
  gStyle->SetOptFit(0);
  gStyle->SetOptFit(0111);
  TCanvas *My = NCanvas(1,2,"Sigma");
  My->cd(1);
  NHSetMarker(Vtx_Sigma,2,20,1.2);
  NLogAxis(0,0);
  Vtx_Sigma->SetMinimum(40);
  Vtx_Sigma->SetMaximum(65);

  Vtx_Sigma->Draw();
  Vtx_Sigma->GetXaxis()->SetTitle("Number Vertexes");
  Vtx_Sigma->GetYaxis()->SetTitle("sigma_{1vxt} [mb]");
  Vtx_Sigma->Fit("pol0");
  pol0->SetLineWidth(0.6); 
  pol0->SetLineStyle(2);   
  My->cd(2);
  NHSetMarker(Vtx_Chi2,4,20,1.2);

  NLogAxis(0,0);
  //  Vtx_Chi2->Scale(1./8.);
  Vtx_Chi2->Draw("p");
  NLine(0.5,1,9.5,1);
}

const Int_t LumBin=14; // Number of lumi bin
TH1F *pois_theory0[LumBin];
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


// Compute the Migration plots

// char NameMigrationFile[100]; 

// pippo

void Efficiency(){
  
  bool VtxEffCorr = false;

  Int_t LostVtx = 0; // Number of lost Vertexes

  readfile();


  Float_t VtxMult_Eff[20] =   // vertex Efficiency array Reweighted (Z2)
  {
      0,       0,       0,       0,       0.122163,
      0.239812,0.374539,0.513237,0.632923,0.735469,
      0.807218,0.862626,0.906567,0.934381,0.957177,
      0.971498,0.979791,0.985438,0.99095, 1
	};

  //  { \\ wrong reweight
  //  0, 0, 0, 0, 0.229515,
  //  0.379046,0.524577,0.654603,0.754703,0.83511,
  //  0.885352,0.923125,0.949875,0.966367,0.97876,
  //  0.986288,0.990682,0.993436,1.,1.
  // };


  // ?
  //    {
  //    0, 0, 0, 0, 0.11639, 
  //    0.228477,0.373528,0.494195,0.621559,0.717274,
  //    0.794274,0.845247,0.901483,0.929595,0.956605,
  //    0.969992, 0.976752,0.982955,0.989738,0.992284
  //  };

  // Z2 Array
  //  {
  //  0,0,0,0,0.113798,
  //    0.227539,0.363269,0.492206,0.612451,0.717942,
  //    0.797522,0.85247,0.891731,0.927602,0.954639,
  //    0.965596,0.978687,0.985922,0.990443,1.
  //    };
  
  if(Lf==0){  

     Lf = TFile::Open(DataFile);

    if (Lf ==0){
      cout << "Problem opening data file " << DataInputFile << endl;
      return;
    }
  }
  
  if(Gf==0){  

    sprintf(hname,"MB_efficiency_files_PtcutGen0.25_D6T0.root");
    Gf = TFile::Open(hname);

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


  TH1F *vertex =   (TH1F*)Lf->Get("Vz");  //Z vertex Position


  //  TH1F *Vertex1Mult =   (TH1F*)Gf->Get("TracksGenEta_w"); // Tracks Multiplicity for Pileup with pt>0.25, weighted
  // TH1F *Vertex1Mult =   (TH1F*)Gf->Get("TracksGenEta_All"); // Tracks Multiplicity for Pileup 

  TH1F *Vertex1Mult =   (TH1F*)Lf->Get("vertex1Mult"); // Tracks Multiplicity PU events
  TH1F *Vertex0Mult =   (TH1F*)Lf->Get("Vertex0MultVtxQual"); // Tracks Multiplicity for main trigger
  

  for (Int_t Nt = 1;Nt<10;Nt++) // read the blind spot files
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

  Float_t vtx_gen[MaxVtxInEvent];
  Float_t vtx_gen_mult[MaxVtxInEvent];
  Float_t BinCont;
  Float_t BinErr;

  Int_t BinNum ;
  TRandom r;
  Float_t Rn ;
  Double_t BlindCont; 


  TCanvas *CRatio = new TCanvas("CRatio","CRatio",1);
  CRatio->Divide(4,4);
  TCanvas *CEff = new TCanvas("CEff","CEff",1);
  CEff->Divide(3,3);
  TCanvas *MyC= NCanvas(4,4);
  
  Int_t Nloop;
  //  for (Float_t Lumi = 0.025; Lumi<=0.7; Lumi+=0.05){
  //  for (Nloop = 1; Nloop<=LumBin; Nloop++ ){'

  for (Nloop = 1; Nloop<=LumBin; Nloop++ ){

    Double_t Lumi = LumiBin[Nloop-1]->GetMean();

    if (Lumi==0) {
      cout << " Luminosity == 0 for bin "<< Nloop << endl ;
      continue;
    }
    


    cout << "Loop " << Nloop << " with lumi = " << Lumi << endl; 

    sprintf(hname,"Pois_Theory0_Lumi%5.3f",Lumi);
    gDirectory->Delete(hname);
    pois_theory0[Nloop-1]  = new TH1F(hname,hname,MaxVtxInEvent,0,MaxVtxInEvent); // Pois hystograms
    pois_theory0[Nloop-1]->Sumw2();

    sprintf(hname,"Pois_Theory_Lumi%5.3f",Lumi);
    gDirectory->Delete(hname);
    pois_theory[Nloop-1]  = new TH1F(hname,hname,MaxVtxInEvent,0,MaxVtxInEvent); // Pois hystograms
    pois_theory[Nloop-1]->Sumw2();

    sprintf(hname,"Pois_Meas_Lumi%5.3f",Lumi);
    pois_meas[Nloop-1] = NH1clone(hname,hname,pois_theory[Nloop-1]);
    sprintf(hname,"Ratio_Meas_over_Theory_Lumi%5.3f",Lumi);
    pois_ratio[Nloop-1] = NH1clone(hname,hname,pois_theory[Nloop-1]);
    
    
    Double_t LumiR = LumiBin[Nloop-1]->GetMean();

    //Fill the hystogram that contains the Pois. Probability of having "MaxVtxInEvent" vertexes 
    // at the luminosity = Lumi
    
    //for (p=0;p<MaxVtxInEvent;p++){
    ////  cout << " p = "<<p<< " and prob_evt= "<< prob_evt(Lumi,p)  << endl;    
    //  pois_theory[Nloop-1]->SetBinContent(p+1,prob_evt(Sigma,Lumi,p));      
    //}
    
    Float_t NRS = 500.;
    
    for (Int_t NL = 1; NL<=NRS; NL++)
      {
	
	Double_t LumiR = LumiBin[Nloop-1]->GetRandom();
	
	for (p=0;p<MaxVtxInEvent;p++)
	  {
	    if(	prob_evt(Sigma,LumiR,p)<0)    
	      cout << "Lum = "<< LumiR << " Sigma = "<< Sigma << " p = "<<p<< " and prob_evt= "<< prob_evt(Sigma,LumiR,p)  << endl;    
	    pois_theory[Nloop-1]->Fill(p+0.1,prob_evt(Sigma,LumiR,p));

	  }
      }
    
    pois_theory[Nloop-1]->Scale(1./NRS);

    Int_t ka;
    Float_t fka;

    //Loop over the possible number of vertexes
    
    for (Int_t i=1; i<=Draw;i++)
      {
	
	ka = 0;
	Int_t counter=0;
	ka =   pois_theory[Nloop-1]->GetRandom();
	
	//// cout << "Event start: "<< ka << " Number of Vertexes in addition to the primary trigger: " << fka << endl;
	// p=0 is the hypotetical triggering vertex
	// ka = number of additional vertexes in the event
	
	// Here we generate the Vertexes and check if they survive a Vertex Mult. efficiency cut
	// Note: all vertexes have already more than 4 tracks (done above)

	Int_t NVtxAfterMultEff = 0 ; // number of PU vertexes 
	for (p = 0;p<=ka;p++) {  // the event is has ka vertexes 

	  Float_t vxt1 = vertex->GetRandom();      // Z position of vertex p

	  //	  while (fabs(vxt1 > Z_limit)) 
	  // {
	  // vxt1 = vertex->GetRandom(); 
	  // }

	  if (p==0) 
	    {
	      //	      vtx_gen_mult[0] = Vertex0Mult->GetRandom();    // Main trigger mult
	      vtx_gen[0] = vxt1;    

	    }
	  else 
	    {
	      Int_t VtxMult_temp = 0;
	      while (VtxMult_temp<4)
		{
		  VtxMult_temp = Vertex1Mult->GetRandom();    // Random PU Mult	      
		}
	      Rn =  r.Uniform(0.,1.);

	      //	      cout << "Vtx = " <<p  << " Vtx Multiplicity = " << VtxMult_temp
	      //   << " and Rnd " << Rn << " Eff29 = "<< VtxMult_Eff[28] << endl ;
	      // if (VtxMult_temp<27)   cout << "Eff = "<< VtxMult_Eff[VtxMult_temp] << endl ;
		
	      if (HadronF && VtxMult_temp < 18 && ( Rn > VtxMult_Eff[VtxMult_temp] ) ) 
		{
		  continue;
		}
	      else
		{
		  NVtxAfterMultEff++; // This vertex has survived, increment the counter
		  vtx_gen_mult[NVtxAfterMultEff] = VtxMult_temp ;    // PU multiplicity
		  vtx_gen[NVtxAfterMultEff] = vxt1;    // z position
		}
	    }
	}
	//	cout << "generated "<< ka << " vertexes and "<<   NVtxAfterMultEff << " survived " << endl;

	Int_t index[20];
	Bool_t down = false;
	TMath::Sort(ka+1, vtx_gen, index, down);
	
	Int_t NBinX = Mult[1]->GetNbinsX();
	Float_t BinLE = Mult[1]->GetBinLowEdge(1);
	Float_t BinW = Mult[1]->GetBinWidth(1);

	for (p = 1;p<=NVtxAfterMultEff;p++)
	  {
	    Int_t ip = index[p];
	    Int_t ipm1 = index[p-1];
	    Float_t Dist = fabs(vtx_gen[ip]-vtx_gen[ipm1]);
	    Int_t SumMult = vtx_gen_mult[ip]+vtx_gen_mult[ipm1];
	    
	  
	    if (DAV && Dist > BlindLimit)
	      {  //Above 2 for sure they are separated
		counter++;	
	      }
	    else
	      {
		if (DAV) vtx_gen[p]= vtx_gen[p-1];
		else if (Dist > 2.) counter++;
		else
		  {
		  
		    // cout << "Distance between " << ip << " and " << ipm1 << " = "<<  Dist << " Mult =" << SumMult << endl;
		    
		    BinNum = (Int_t)( 1+ (Dist-BinLE)/BinW); // get the bin index. The histo binning start at 1, so bin 1 from 0-0,1;
		    if (SumMult< 50){
		      BlindCont = Mult[1]->GetBinContent(BinNum);
		      // cout << " BlindCount < 50 Bin Number " << BinNum << " and content " <<  BlindCont << endl;
		    }
		    else 
		      {
			for (Int_t Nm = 2;Nm<=9;Nm++)
			  {
			    if (SumMult>=25*(Nm) && SumMult<25*(Nm+1))
			      {
				BlindCont = Mult[Nm]->GetBinContent(BinNum);
				//    cout << " BlindCount bin " << Nm << " Bin Number " << BinNum << " and content " <<  BlindCont << endl;
				break;
			      }
			  }
		      }
		    
		    Rn =  r.Uniform(0.,1.);
		    //		cout << " Rn = " << Rn << " <  BlindCont "<< BlindCont << " ? if yes, they are separated ! "<< endl;
		    if (Rn < BlindCont) counter++; //the vertexes are separated	      
		    else  vtx_gen[p]= vtx_gen[p-1];	    
		    
		  } // DAV
		
		
	      }
	    
	  }
	
	pois_meas[Nloop-1]->Fill(counter+0.1);
	
	
	if (NVtxAfterMultEff> counter)
	  {
	    // cout << " Starting vtx = " << NVtxAfterMultEff << " Final vtx are = " << counter<< endl;
	    LostVtx += (NVtxAfterMultEff-counter);
	  }
      }
  
    
    MyC->cd(Nloop);

    Float_t scale = pois_meas[Nloop-1]->GetEntries();
    pois_meas[Nloop-1]->SetMaximum(1.);  
    pois_meas[Nloop-1]->SetMinimum(0.001);  
    
    NLogAxis(0,1);
    pois_meas[Nloop-1]->Scale(1./scale);
    pois_meas[Nloop-1]->SetLineStyle(2);
    pois_meas[Nloop-1]->Draw();
    pois_theory0[Nloop-1]->SetLineStyle(2);    
    pois_theory0[Nloop-1]->Draw("SAMEHIST");    
    pois_theory[Nloop-1]->Draw("SAMEHIST");    
    CRatio->cd(Nloop);
    NLogAxis(0,0);

    pois_ratio[Nloop-1]->Divide(pois_meas[Nloop-1],pois_theory[Nloop-1]);
    pois_ratio[Nloop-1]->SetMaximum(1.8);  
    NHSetMarker(pois_ratio[Nloop-1],2,20,1.);
    pois_ratio[Nloop-1]->Draw("E");    
     

    //    Nloop++;

  }  // End of Nloop

  cout << "Lost Vtx = " << LostVtx << endl;
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
  
  for (p=1;p<=9;p++)
    {      //loop over the bin
      CEff->cd(p);
      //    Eff_corr[p]->SetMaximum(1.8);  
      // Eff_corr[p]->SetMinimum(0.);  
      NHSetMarker(Eff_corr[p-1],4,20,1.);
      sprintf(hname,"Efficiency to detect %i vertexes vs luminosity",p);
      Eff_corr[p-1]->Draw("PE");
      Eff_corr[p-1]->GetXaxis()->SetTitle("Bunch Luminosity  10^{30} [cm^2 s^{-1}]");
      Eff_corr[p-1]->SetTitle(hname);
      
    }
  
  TFile fC(MigrationFile,"recreate"); 
  for (p=0; p<LumBin; p++) 
    {
      
      Eff_corr[p]->Write();
      if (LumiBin[p]->GetMean()!=0)
	{	    
	  pois_ratio[p]->Write();
	  pois_theory0[p]->Write();
	  pois_theory[p]->Write();
	  pois_meas[p]->Write();
	}
    }
  fC.Close(); 
  
  
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


// Check the relationship between triggers and luminosity

// TFile *ffc;

TH1F *proj;
const Int_t RunBin = 50;
TH1F *NTriggers;
TH1F *RunTriggers[RunBin];
TH1F *RunLumi[RunBin];
TH1F *ratio[RunBin];
TH1F *ratioCor[RunBin];
TH1F *ProjRatio[RunBin];
TH1F *LumiCor[RunBin];
TCanvas *MyC[RunBin];
TFile *ff;

void LumiCheck(){

  Int_t RunForLumi[RunBin] = 
    {
      142130,142422,142528,142928,142933,142971,143181,143323,143657,143727,
      143827,143833,143953,143954,143961,143962,144011,144086,144089,144112,
      146804,146807,147043,147048,147114,147115,147284,147390,147450,147451,
      147453,147454,147754,147755,147757,148029,148031,148032,148862,148864,
      148952,148953,149003,149011,149058,149063,149181,149182,149291,149294
    };
  ///{140361,142419,143326,143827,143833,143953,
  //		      144011,144089,144112,146804,147114,148029,
  //		      148862,148952,149003,149011,149181,149291};

  char hname[100]; 
  
  if(ff==0){
    sprintf(hname ,"Fraction_n_vertexes_files_ee10_NDOFGT2_EBGT50_runAB.root"); 
    ff = TFile::Open(hname); 
    
    for (Int_t M=0;M<RunBin;M++){
      sprintf(hname,"RunTriggers%i",M);
      RunTriggers[M] =   (TH1F*)ff->Get(hname);
      sprintf(hname,"RunLumi%i",M);
      RunLumi[M] =   (TH1F*)ff->Get(hname);
      sprintf(hname,"Ratio%i",M);
      ratio[M] = NH1clone(hname,hname,RunLumi[0]);
      ratio[M]->Divide(RunLumi[M],RunTriggers[M]);
      
      sprintf(hname,"Run %i",RunForLumi[M]);
      
      MyC[M] = new TCanvas(hname,hname,M);
      MyC[M]->Divide(2,3);
      
      sprintf(hname,"Proj%i",M);
      ProjRatio[M]= new TH1F(hname,hname, 100, 0.001,1.);
      
      sprintf(hname,"MultiplicativeLumiCor%i",RunForLumi[M]);
      LumiCor[M] = NH1clone(hname,hname,RunLumi[0]);
      
      sprintf(hname,"RatioCor%i",M);
      ratioCor[M] = NH1clone(hname,hname,RunLumi[0]);
    }
  }

  NTriggers =   (TH1F*)ff->Get("NTriggers");
  
  TFile ffc("Files_For_Lumi_Correction.root","recreate"); 
  
  for (Int_t M=0;M<RunBin;M++){
    
    
    MyC[M]->cd(1);
    RunTriggers[M]->Draw();
    RunTriggers[M]->GetXaxis()->SetTitle("Bunch Crossing");
    RunTriggers[M]->GetYaxis()->SetTitle("Events");
    MyC[M]->cd(2);
    RunLumi[M]->Draw();
    // RunLumi[M]->Scale(1./11346);
    RunLumi[M]->GetXaxis()->SetTitle("Bunch Crossing");
    RunLumi[M]->GetYaxis()->SetTitle("Luminosity");
    //cout << "total Lumi: "<< BxLumi->Integral()<<endl;
    
    MyC[M]->cd(3);
    
    ratio[M]->Draw();
    
    Int_t Nbin = ratio[M]->GetNbinsX();
    for (Int_t i=1;i<Nbin; i++)
      ProjRatio[M]->Fill(ratio[M]->GetBinContent(i));
    
    MyC[M]->cd(4);
    ProjRatio[M]->Draw();
    //    ProjRatio[M]->Fit("gaus");
    
    Float_t ProjMean = ProjRatio[M]->GetMean();
    Float_t ProjRMS = ProjRatio[M]->GetRMS();
    
    if (ProjMean > 0.) Float_t RMSMean = ProjRMS/ProjMean;
    cout << RunForLumi[M] << " ProjMean= " << ProjMean << " Proj RMS = " << ProjRMS<<  " Ratio = " << RMSMean <<endl;
    for (Int_t i=1;i<=Nbin; i++){
      if(ratio[M]->GetBinContent(i)>0.)
	LumiCor[M]->SetBinContent(i,ProjMean/ratio[M]->GetBinContent(i));
	LumiCor[M]->SetBinError(i,ratio[M]->GetBinError(i));
    }
    
    MyC[M]->cd(5);
    LumiCor[M]->Draw();
    
    MyC[M]->cd(6);
    ratioCor[M]->Add(ratio[M]);
    ratioCor[M]->Multiply(LumiCor[M]);
    ratioCor[M]->Draw();
    
    ratio[M]->Write();
    ProjRatio[M]->Write();
    LumiCor[M]->Write();
    RunLumi[M]->Write();
    RunTriggers[M]->Write();
  }
  
  ffc.Close();
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


TH1I *Runs;
TH1F *RunsLumi;

void SeeRuns(){

  char hname[100]; 
  
  if(ff==0){
    sprintf(hname ,"Fraction_n_vertexes_files_ee10_NDOFGT2_EBGT50_runAB.root"); 
    ff = TFile::Open(hname); 
  }
  Runs =   (TH1F*)ff->Get("Runs");
  RunsLumi =   (TH1F*)ff->Get("RunsLumi");

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
void CheckVxt(){

  const Int_t LumBin=14; // Number of lumi bin

  char DataInputFile[100]; 
  Float_t xl;
  Float_t xu;
  readfile();
  if (f==0){
    f = TFile::Open(DataFile); 
    //cout << DataInputFile << endl;
    if (f==0) return;
    fc = TFile::Open(MigrationFile);
    // cout << MigrationFile << endl;
    if (fc==0) return;
  }
  TH1F *H[15];
  TCanvas *My = NCanvas(3,4);
  TCanvas *RatioC = NCanvas(3,4,"Ratio");
  for (Int_t N=1;N<12; N++){
    My->cd(N+1);
    cout << "N = " << N << endl;
    xl=0.05*(N);
    xu=0.05*(N+1);
    sprintf(hname,"Vtx_Lumi_Int_%4.2f_%4.2f",xl,xu);
    VxtLumiBin[N] = (TH1F*) f->Get(hname);
    sprintf(hname,"LumiBin%i",N+1);
    LumiBin[N] = (TH1F*)f->Get(hname);
    Double_t Lumi = LumiBin[N]->GetMean();
    sprintf(hname,"Pois_Meas_Lumi%5.3f",Lumi);
    pois_meas[N] = (TH1F*)fc->Get(hname);
    VxtLumiBin[N]->Sumw2();
    
    NH1FArea1(VxtLumiBin[N]);
    VxtLumiBin[N]->Draw("p");
    NLogAxis(0,1);
    H[N]=NH1clone("Ratio","Ratio", VxtLumiBin[N]);
    VxtLumiBin[N]->GetXaxis()->SetRange(0,10);
    VxtLumiBin[N]->GetXaxis()->SetTitle("Number of Vertexes");
    VxtLumiBin[N]->GetYaxis()->SetTitle("Fraction");
    pois_meas[N]->Draw("SAMEHIST");
    //    cout <<  VxtLumiBin[N]->KolmogorovTest(pois_meas[N]) << endl;
    // VxtLumiBin[N]->Chi2Test(pois_meas[N]);

    RatioC->cd(N+1);
    H[N]->Add(VxtLumiBin[N]);
    H[N]->Divide(pois_meas[N]);
    H[N]->GetXaxis()->SetRange(0,8);
    H[N]->SetMinimum(0.8);
    H[N]->SetMaximum(1.2);
    H[N]->Draw("p");
    NLine(0,1.,8,1.);
    
  }

  My->cd(1);
  TLegend *leg = new TLegend(0.,0.2, 0.7 ,0.8);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(VxtLumiBin[1],"Measured vertex distribution","p");  
  leg->AddEntry(pois_meas[1],"Calculated vertex distribution","L");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.1);  
  leg->Draw();
  
  return;
}

TFile *fData;
TFile *fZ2;
TFile *fD6T;

void MCReweight(){

  if(fData==0)
    {  // Data File //
      
      fData = TFile::Open("Fraction_n_vertexes_files_ee10_EBGT50_runAB_NDOFGT2_VtxMultGT1_DAV1_RunList=1_LumiCor=1.root");
      fD6T = TFile::Open("MB_efficiency_files_PtcutGen0.25_D6T1.root");
      fZ2  = TFile::Open("MB_efficiency_files_PtcutGen0.25_D6T0.root");


    }
  
  TH1F *Vertex1Mult =   (TH1F*)fData->Get("Vertex1Mult");
  TH1F *VertexMultD6T =    (TH1F*)fD6T->Get("VertexMultD6T");
  TH1F *VertexMultZ2 =    (TH1F*)fZ2->Get("VertexMultZ2");
  NH1FMax1(Vertex1Mult);
  NH1FMax1(VertexMultD6T);
  NH1FMax1(VertexMultZ2);
  
  TCanvas *My = NCanvas(1,1);

  My->cd(1);
  NLogAxis(0,1);
  Vertex1Mult->SetAxisRange(0,120);
  Vertex1Mult->SetMinimum(0.001);

  Vertex1Mult->SetMarkerSize(.8);
  Vertex1Mult->Draw("p");

  Vertex1Mult->GetXaxis()->SetTitle("Tracks per vertex");
  Vertex1Mult->GetYaxis()->SetTitle("Fraction");
  VertexMultD6T->SetLineColor(2);
  VertexMultD6T->SetLineStyle(2);

  VertexMultD6T->Draw("SAMEHIST");
  VertexMultZ2->SetLineColor(4);
  VertexMultZ2->Draw("SAMEHIST");

  TLegend *leg = new TLegend(0.7,0.5, 1. ,0.8);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(Vertex1Mult,"Data","p");  
  leg->AddEntry(VertexMultD6T,"D6T","L");  
  leg->AddEntry(VertexMultZ2,"Z2","L");  
  leg->SetBorderSize(0);
  //  leg->SetTextSize(0.1);  
  leg->Draw();
  TH1F *ratio = NH1clone("Data/D6T","Data/D6T",Vertex1Mult);
  return;
  My->cd(2);
  NLogAxis(0,0);
  ratio->SetAxisRange(0,100);
  //  Vertex1Mult->SetMinimum(0.001);
  ratio->Add(Vertex1Mult);
  ratio->Divide(VertexMultD6T);
  ratio->Draw();
  ratio->SetMaximum(8.);
  ratio->Fit("pol3","","",4,70);
  return;
}

