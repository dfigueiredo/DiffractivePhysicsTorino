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

  Int_t NLumi=14;
  Int_t M=0;
  for (Int_t N=2,; N<=NLumi;N++){
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

  //  NLogAxis(0,1);
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
  gStyle->SetOptFit(00000);  
  
  //  RatFit->Fit("pois1","I","SAME",0.05,0.61);
  RatFit->Fit("pois1","I","SAME",0.05,0.7);
  // RatFit->Fit("pois1","I","SAME",0.05,0.51);

  //  RatFit->Fit("pois1","I","SAMES",0.1,0.6);
  if (vtx==10) {
    //gStyle->SetOptFit(111111);
    pois2->SetLineStyle(2);
    pois2->SetLineColor(1);
    pois2->SetLineWidth(0.4);
    TH1F *RatFit2 = RatFit->Clone();
    RatFit2->Draw("SAMEp");
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

  setTDRStyle();  
  // gROOT->Reset();

  Int_t FlagScale = Flag;
 
  gDirectory->Delete("Vtx_Sigma");
  gDirectory->Delete("Vtx_Chi2");
  gDirectory->Delete("ee_pt>10GeV");

  Vtx_Sigma = new TH1F("Vtx_Sigma","Vtx_Chi", 9,0.5,9.5);
  Vtx_Chi2 = new TH1F("Vtx_Chi2","Vtx_Chi", 9,0.5,9.5);
 
  TH1F *All0 =  new TH1F("All0","Fraction of Events with 0 Pile-Up events",14,0.,0.7);
  All0->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All0->GetYaxis()->SetTitle("Fraction");

  TH1F *All1 =  new TH1F("All1","Fraction of Events with 1 Pile-Up events",14,0.,0.7);
  All1->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All1->GetYaxis()->SetTitle("Fraction");

  TH1F *All2 =  new TH1F("All2","Fraction of Events with 2 Pile-Up events",14,0.,0.7);
  All2->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  All2->GetYaxis()->SetTitle("Fraction");

  TH1F *AllN =  new TH1F("AllN","Fraction of Events with 3-8 Pile-Up events",14,0.,0.7);
  AllN->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  AllN->GetYaxis()->SetTitle("Fraction");

  TH1F *AllHF0 =  new TH1F("AllHF0","Fraction of Events with HF=0",14,0.,0.7);
  AllHF0->GetXaxis()->SetTitle("Luminosity per crossing 10^{30} cm^{-2}s^{-1}");
  AllHF0->GetYaxis()->SetTitle("Fraction");


  TCanvas *Res = new TCanvas("Res","Res",1);
  Res->Divide(3,3);

  TCanvas *HF0 = new TCanvas("HF0","HF0",1);
  HF0->Divide(1,1);
    

  TCanvas *MyC = NCanvas(2,2);


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
  All2->SetMinimum(0.07);
  All2->SetMaximum(0.3);
  All2->Draw();
  MyC->cd(4);
  AllN->SetMinimum(0.00001);
  AllN->SetMaximum(2.);
  AllN->Draw();
  gStyle->SetOptFit(000000);
  NLogAxis(0,1);


  gStyle->SetOptFit(00000);
   for (Int_t i=1;i<11;i++){ // to see HF=0
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
    else if (i=10){
      HF0->cd(1);
      AllHF0->SetMinimum(0.0002);
      AllHF0->SetMaximum(0.007);
      AllHF0->Draw();
      NLogAxis(0,1);
    }
    //    if (vertex(i,FlagScale) == 1) return;;
    vertex(i,FlagScale);
   }



  MyC->cd(1);
  NText(0.02, .1,"PU=0",1, 0.05);

  sprintf(CMSPrel,"CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}") ;
  NText(0.1,0.8,CMSPrel,1,0.07);
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

  TCanvas *My = NCanvas(1,1,"Sigma");
  TCanvas *MyChi2 = NCanvas(1,1,"Chi2");

  My->cd(1);
  NHSetMarker(Vtx_Chi2,4,20,1.2);
  gStyle->SetOptFit(0);
  gStyle->SetOptFit(0111);
  NLogAxis(0,0);
  //  Vtx_Chi2->Scale(1./8.);
  
  Vtx_Chi2->SetMaximum(4.);
  Vtx_Chi2->SetMinimum(0);
  Vtx_Chi2->Draw("p");
  Float_t TotChi2 = Vtx_Chi2->Integral();
  sprintf(hname,"Sum of Chi2 %3.2f",TotChi2);
  cout << "Total Chi2 = " << hname << endl ;
  cout << "Total Chi2 = " << MigrationFile << endl ;
  gStyle->SetOptFit(000000);
  NLine(0.5,1,9.5,1);
  NText (1,3.1,hname,2);
  NText (1,4.05,MigrationFile,1);


  MyChi2->cd(1);
  NHSetMarker(Vtx_Sigma,2,20,1.2);
  NLogAxis(0,0);
  Vtx_Sigma->SetMinimum(50.5);
  Vtx_Sigma->SetMaximum(61.5);

  Vtx_Sigma->Draw();
  Vtx_Sigma->GetXaxis()->SetTitle("Number of Vertices");
  Vtx_Sigma->GetYaxis()->SetTitle("#sigma(pp) [mb]");
  Vtx_Sigma->Fit("pol0");
  Float_t res = pol0->GetParameter(0);
  Float_t eres = pol0->GetParError(0);
  sprintf(hname,"#sigma =  %3.1f #pm %3.1f  mb",res,eres);
  NText(1,58,hname,1,0.05);
  sprintf(hname,"(At least 3 charged particles with |#eta|<2.4 and p_{t} > 200 MeV)");
  NText(1,57.8,hname,1,0.03);
  pol0->SetLineWidth(0.6); 
  pol0->SetLineStyle(2);  
  sprintf(CMSPrel,"2010 CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}") ;
  //  NText(1,61.7,"2010 CMS Preliminary");
  NText(1,61.2,CMSPrel);


}

// const Int_t LumBin=14; // Number of lumi bin

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


Int_t LostVtx = 0; // Number of lost Vertexes
Int_t TotVtx = 0; // Number of lost Vertexes

void Efficiency(){
  
  bool VtxEffCorr = false;

  readfile();

  Int_t NTracksVtx;
  if (SelNDOF == 2) NTracksVtx = 4;
  if (SelNDOF == 1) NTracksVtx = 3;

  Float_t DeltaMCEff = 0.;
  if (SystCheck == 4) DeltaMCEff= 0.02;
  if (SystCheck == 5) DeltaMCEff= -0.02;	
  if (SystCheck == 51) DeltaMCEff= -0.03;	
  if (SystCheck == 52) DeltaMCEff= -0.01;	
  if (SystCheck == 53) DeltaMCEff= 0.01;	
  if (SystCheck == 54) DeltaMCEff= -0.04;	
  if (SystCheck == 55) DeltaMCEff= -0.05;	

  Int_t EffCounter = 0;
  if (SelNDOF == 1) Float_t FracSecVertex = 0.0015;
  if (SelNDOF == 2) Float_t FracSecVertex = 0.00084;

  if (SystCheck == 11)  FracSecVertex =  0.5*FracSecVertex;	    
  if (SystCheck == 10) FracSecVertex =  2.*FracSecVertex;	    



  if (SelNDOF == 2 && PtCut == 250)
    {
      Float_t VtxMult_Eff[20] =   // vertex Efficiency array Reweighted (Z2)
	{
	  0,0.00155446,0.0131655,0.0426287,0.117015,
	  0.214614,0.365213,0.518457,0.641361,0.729362,
	  0.811376,0.874637,0.910823,0.951034,0.96775,
	  0.979241,0.988861,0.982491,0.993677,1.
	};
    }
  else if (SelNDOF == 1 && PtCut == 250)
    {
      Float_t VtxMult_Eff[20] =   // vertex Efficiency array Reweighted (Z2)
	{
	  6.31605e-05,0.0116355,0.0708339,0.187598,0.342431,
	  0.479881,0.640639,0.745975,0.823077,0.888743,
	  0.92317,0.947348,0.968029,0.986463,0.991285,
	  0.993724,0.997751,0.99557,0.998015,0.998701
	};
    }
  else if (SelNDOF == 2 && PtCut == 200)
    {
      Float_t VtxMult_Eff[20] =   // vertex Efficiency array Reweighted (Z2)
	{
	  0,0,0.00359288,0.0130714,0.0515917,
	  0.124751,0.215837,0.325146,0.474203,0.581261,
	  0.673725,0.748549,0.80563,0.866277,0.9038,
	  0.942375,0.95723,0.978127,0.983553,0.983155
	};
    }

  else if (SelNDOF == 1 && PtCut == 200)
    {
      Float_t VtxMult_Eff[20] =   // vertex Efficiency array Reweighted (Z2)
	{
	  9.18542e-05,0.0026698,0.0328251,0.112311,0.241605,
	  0.362283,0.496271,0.609561,0.707677,0.787134,
	  0.857843,0.893378,0.925096,0.949626,0.962866,
	  0.973265,0.983525,0.989421,0.992434,0.993801
	};
    }
  else    
    {
      Float_t VtxMult_Eff[20] = {0.0};  
    }
    
   
  if (HadronF && VtxMult_Eff[10] == 0.0 )
    {
      cout << "No MC Efficiency array for Pt Value = " << PtCut  << endl;
      return;
    }

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
      // Gen Tracks Multiplicity for Hadron Correction with pt>0.25, weighted//
      
      TH1F *VertexGenMult =   (TH1F*)Gf->Get("TracksGenEtaPt_w_CW"); 
    }
  else
    {
      TH1F *VertexGenMult =   (TH1F*)Gf->Get("TracksGenEtaPt_w_Z2");
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

  Float_t vtx_gen[MaxVtxInEvent];
  Float_t vtx_gen_mult[MaxVtxInEvent];
  Float_t vtx_gen_Sur[MaxVtxInEvent];
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



  Int_t NumPUGen;
  Float_t fka;
  Int_t index[20];
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
	
	//	for (Int_t H = 0; H<=NumPUGen;H++) cout << "index = "<< index[H] << " pos = "<< vtx_gen[index[H]] << endl;

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
		    vtx_gen_mult_Sur[NumPUAfterZMerging] = vtx_gen_mult[ipm1]+ vtx_gen_mult[ip];
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
	
       	//cout << "NumPUGen = "<< NumPUGen << " NumPUAfterZMerging " << NumPUAfterZMerging << endl;
      
	Int_t NumPUAfterZ_and_HadronCor = 0;


	if (HadronF)    //decides if it's detected
	  {

	    TMath::Sort(NumPUAfterZMerging+1, vtx_gen_mult_Sur, index, down);

	    for (p = 0;p<=NumPUAfterZMerging;p++) 
	      { 
		if (index[p]==0) continue; // Remove the highest Multiplicity (Primary Trigger)
		
		VtxMult_temp = vtx_gen_mult_Sur[p];    // Random PU Mult, Vtx larger than NTrkVtx	      		  
		// cout << "Mult = " << VtxMult_temp << endl;
		Rn =  r.Uniform(0.,1.);
		
		if (VtxMult_temp < 18 && ( Rn > (VtxMult_Eff[VtxMult_temp]+DeltaMCEff) ) )  //decides if it's detected
		  {
		    //    cout << "Lost for Multiplicy" << endl;
		    continue;

		  }
		else
		  {
		    NumPUAfterZ_and_HadronCor++; // This vertex has survived, increment the counter
		    
		  }
	      }
	  }
	else
	  {
	    NumPUAfterZ_and_HadronCor = NumPUAfterZMerging;	    	    
	  } 
      
	//	NumPUAfterZ_and_HadronCor -=1 ; // remove the primary event	    	    
	//       	cout << "generated "<< NumPUGen << " vertexes and "<<   NumPUAfterZ_and_HadronCor << " survived " << endl;
	
	
	
	
	
	
	// Generate Secondary Vertices //
	
	
	Int_t FakeVtx = 0;
	for (Int_t NC = 0;NC<=NumPUAfterZ_and_HadronCor;NC++)
	  {
	    if ( r.Uniform(0.,1.) < FracSecVertex)  FakeVtx++;
	  }
	
	NumPUAfterZ_and_HadronCor = NumPUAfterZ_and_HadronCor + FakeVtx; // Add fake seconday Vtx
	EffCounter  += FakeVtx;
	
	//pois_meas[Nloop]->Fill(NumPUAfterZ_and_HadronCor+0.1);
	pois_meas[Nloop]->Fill(NumPUAfterZ_and_HadronCor);
	
	if (NumPUGen> NumPUAfterZ_and_HadronCor)
	  {
	    // cout << " Starting vtx = " << NumPUAfterZ_and_HadronCor << " Final vtx are = " << NumPUAfterZ_and_HadronCor<< endl;
	    LostVtx += (NumPUGen-NumPUAfterZ_and_HadronCor);

	  }
	TotVtx +=NumPUGen;
	//	  cout << "pippo"<< endl; // to be removed
	
	} // Draw Loop

	// }  // End of Nloop
	
	cout << "Number of secondary vertices = "<< EffCounter << endl;	
	cout << "Number of Lost vertices = "<< LostVtx << endl;	
	EffCounter = 0;

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
	Float_t xl=0.05*(Nloop);
	Float_t xu=0.05*(Nloop+1);
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
	
	Float_t xl=0.05*(Nloop);
	Float_t xu=0.05*(Nloop+1);
	sprintf(hname,"L = %4.2f-%4.2f  10^{30} cm^{-2} s^{-1} ",xl,xu);
	NText(4,1.6,hname,1,0.08);
	
	//    Nloop++;
	
  }  // End of Nloop
  
  
  
  
  MyC->cd(15);
  TLegend *leg = new TLegend(0.,0.5, 1 ,1);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(pois_theory[1],"True","L");  
  leg->AddEntry(pois_meas[1],"Predicted Visible","p");
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
  leg1->AddEntry(pois_ratio[1],"Predicted Visible/","p");  
  leg1->AddEntry(pois_ratio[1],"True"," ");  
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.07);  
  leg1->SetFillColor(0);

  leg1->Draw();

  Float_t LostFrac =  (1.*LostVtx)/(1.*TotVtx);
  cout << "Lost Vtx = " << LostVtx << " Tot Vtx = " << TotVtx << " Lost fraction = " << LostFrac << endl;

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

void CheckVxt(){

  const Int_t LumBin=14; // Number of lumi bin

  //  char DataInputFile[100]; 

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
  TCanvas *My = NCanvas(4,4,"My");
  TCanvas *RatioC = NCanvas(4,4,"RatioC");
  for (Int_t N=1;N<14; N++){
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
    VxtLumiBin[N]->SetMaximum(1.);
    if (N<4)    VxtLumiBin[N]->SetMinimum(0.000001);
    else    VxtLumiBin[N]->SetMinimum(0.0001);
    NHSetMarker(VxtLumiBin[N],2,20,0.9);
    VxtLumiBin[N]->Draw("p");
    NLogAxis(0,1);
    H[N]=NH1clone("Ratio","Ratio", VxtLumiBin[N]);
    VxtLumiBin[N]->GetXaxis()->SetRange(0,10);
    VxtLumiBin[N]->GetXaxis()->SetTitle("Number of Vertexes");
    VxtLumiBin[N]->GetYaxis()->SetTitle("Fraction");
    Float_t xl=0.05*(N);
    Float_t xu=0.05*(N+1);
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
    H[N]->SetMinimum(0.8);
    H[N]->SetMaximum(1.2);
    H[N]->Draw("p");
    Float_t xl=0.05*(N);
    Float_t xu=0.05*(N+1);
    sprintf(hname,"Luminosity: %4.2f-%4.2f  10^{30} cm^{-2} s^{-1} ",xl,xu);
    NText(0.5,0.88,hname,1,0.06);
    H[N]->GetXaxis()->SetTitle("Number of Vertexes");
    H[N]->GetYaxis()->SetTitle("Measured/Predicted Visible ");
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
  leg->AddEntry(pois_meas[1],"Predicted Visible","L");
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
  leg->AddEntry(H[1],"Measured/","p");  
  leg->AddEntry(H[1],"Predicted Visible","");  
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.1);  
  leg->Draw();
  
  return;
}

TFile *fData;
TFile *fMC;
TFile *fD6T;
string stringa;

void MCReweight(){

  readfile();

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



  stringa = "TracksMeas_NDOFGE2_P8";
  sprintf(hname,stringa.c_str());
  TH1F *VertexMultP8 =    (TH1F*)fMC->Get(hname);
  stringa = "TracksMeas_NDOFGE2_w_P8";
  sprintf(hname,stringa.c_str());
  TH1F *VertexMultP8w =    (TH1F*)fMC->Get(hname)
;
  stringa = "MeasPt_NDOFGE2_Mult9_P8";
  sprintf(hname,stringa.c_str());
  TH1F *PtP8 =    (TH1F*)fMC->Get(hname);

  stringa = "TracksMeas_NDOFGE2_w_CW2";
  sprintf(hname,stringa.c_str());
  TH1F *VertexMultCWw =    (TH1F*)fMC->Get(hname);
  stringa = "TracksMeas_NDOFGE2_CW2";
  sprintf(hname,stringa.c_str());
  TH1F *VertexMultCW =    (TH1F*)fMC->Get(hname);

  stringa = "MeasPt_NDOFGE2_Mult9_CW2";
  sprintf(hname,stringa.c_str());
  TH1F *PtCW =    (TH1F*)fMC->Get(hname);

  cout << "pippo1" << endl;

  // weighted Distributions //
  //  TH1F *VertexMultD6T =    (TH1F*)fD6T->Get("TracksMeas_NDOFGE2_w");
  //TH1F *VertexMultP8 =    (TH1F*)fP8->Get("TracksMeas_NDOFGE2_w");


  NH1FArea1(Vertex1Mult);
  cout << "pippo21" << endl;
  NH1FArea1(VertexMultCW);
  cout << "pippo22" << endl;
  NH1FArea1(VertexMultP8);

  cout << "pippo23" << endl;

  NH1FArea1(VertexMultCWw);
  NH1FArea1(VertexMultP8w);


  //  NH1FMax1(Vertex1Mult);
  //  NH1FArea1(PtMeas);
  //NH1FArea1(PtCW);
  // NH1FArea1(PtP8);
  
  cout << "pippo2" << endl;


  TCanvas *Rew = NCanvas(1,1,"Rew");

  Rew->cd(1);
  NLogAxis(1,1);
  Vertex1Mult->SetAxisRange(2,120);
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
  Vertex1Mult->SetAxisRange(2,120);
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
  

  TCanvas *My = NCanvas(1,1,"My");
  My->cd();



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
  ratioz2->Fit("pol3","","",3,30);

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
  ratiocw->Fit("pol4","","",3,100);
  My->Update();


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
	  if (M==0)  MyC[M]->Print("LumiCorFiles_eemm_ratio.ps(");
	  else if (M==RunBin-1)MyC[M]->Print("LumiCorFiles_eemm_ratio.ps)");
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


void MCEff(){

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
  
  TH1F *Z2Meas2 =   (TH1F*)fMC->Get("TracksGenEtaPt_NDOFGT2_w_Z2");
  TH1F *Z2Meas1 =   (TH1F*)fMC->Get("TracksGenEtaPt_NDOFGT1_w_Z2");
  TH1F *Z2Gen =   (TH1F*)fMC->Get("TracksGenEtaPt_w_Z2");

  TH1F *CWMeas2 =   (TH1F*)fMC->Get("TracksGenEtaPt_NDOFGT2_w_CW");
  TH1F *CWMeas1 =   (TH1F*)fMC->Get("TracksGenEtaPt_NDOFGT1_w_CW");
  TH1F *CWGen =   (TH1F*)fMC->Get("TracksGenEtaPt_w_CW");

  TH1F *D6TMeas2 =   (TH1F*)fMC->Get("TracksGenEtaPt_NDOFGT2_w_D6T");
  TH1F *D6TMeas1 =   (TH1F*)fMC->Get("TracksGenEtaPt_NDOFGT1_w_D6T");
  TH1F *D6TGen =   (TH1F*)fMC->Get("TracksGenEtaPt_w_D6T");




  TH1F *pippo2DAV = NH1clone("Fraction of Generated vertexes detected","Fraction of recorded vertexes with NDOF>=2 or NDOF>=3",CWMeas1);
  TH1F *pippo2STD = NH1clone("pippo2","pippo2",CWMeas1);
  pippo2DAV->Sumw2();
  pippo2STD->Sumw2();

  pippo2DAV->SetMarkerColor(2);

  pippo2DAV->SetMinimum(0.);
  pippo2DAV->SetMaximum(1.2);
  pippo2DAV->GetXaxis()->SetTitle("Generated Multiplicity [pt>250 MeV, |eta|<2.4]");
  if (PtCut == 200)  pippo2DAV->GetXaxis()->SetTitle("Generated Multiplicity [pt>200 MeV, |eta|<2.4]");
  pippo2DAV->GetYaxis()->SetTitle("Efficiency");

  pippo2DAV->Add(CWMeas2);
  pippo2DAV->Divide(CWGen);

  pippo2STD->Add(Z2Meas2);
  pippo2STD->Divide(Z2Gen);

  Int_t Nbin =pippo2DAV->GetNbinsX();
  cout << "Efficiency for DAV NDOF2" << endl;
  for (Int_t j=0;j<16;j+=5)
    {
      for (Int_t i=1; i<6;i++)
	{
	  
	  cout << pippo2DAV->GetBinContent(i+j) <<",";
	}
      cout << endl;
    }

  cout << "Efficiency for STD NDOF 2" << endl;
  //  for (j=0;k
  for (Int_t j=0;j<16;j+=5)
    {
      for (Int_t i=1; i<6;i++)
	{
	  
	  cout << pippo2STD->GetBinContent(i+j) <<",";
	}
      cout << endl;
    }



  TH1F *pippo1DAV = NH1clone("Fraction of Generated vertexes detected","Fraction of recorded vertexes with NDOF>=2 or NDOF>=3",CWMeas1);
  TH1F *pippo1STD = NH1clone("pippo2","pippo2",CWMeas1);
  TH1F *Dif = NH1clone("Dif","Dif",CWMeas1);
  Dif->Sumw2();
  pippo1DAV->Sumw2();
  pippo1STD->Sumw2();

  pippo1DAV->SetMarkerColor(2);

  pippo1DAV->SetMinimum(0.);
  pippo1DAV->SetMaximum(1.2);

  pippo1DAV->GetXaxis()->SetTitle("Generated Multiplicity [pt>250 MeV, |eta|<2.4]");
  if (PtCut == 200)  pippo2DAV->GetXaxis()->SetTitle("Generated Multiplicity [pt>200 MeV, |eta|<2.4]");

  pippo1DAV->GetYaxis()->SetTitle("Efficiency");

  pippo1DAV->Add(CWMeas1);
  pippo1DAV->Divide(CWGen);

  pippo1STD->Add(Z2Meas1);
  pippo1STD->Divide(Z2Gen);


  Dif->Add(pippo1DAV);
  Dif->Add(pippo1STD,-1);

  Int_t Nbin =pippo1DAV->GetNbinsX();
  cout << "Efficiency for DAV NDOF1" << endl;
  for (Int_t j=0;j<16;j+=5)
    {
      for (Int_t i=1; i<6;i++)
	{
	  
	  cout << pippo1DAV->GetBinContent(i+j) <<",";
	}
      cout << endl;
    }

  cout << "Efficiency for STD NDOF1" << endl;
  //  for (j=0;k
  for (Int_t j=0;j<16;j+=5)
    {
      for (Int_t i=1; i<6;i++)
	{
	  
	  cout << pippo1STD->GetBinContent(i+j) <<",";
	}
      cout << endl;
    }



  TCanvas *NDOF2 = NCanvas(1,1,"NDOF2");
  TCanvas *NDOF1 = NCanvas(1,1,"NDOF1");
  TCanvas *NDOF3 = NCanvas(1,1,"NDOF3");

  NDOF3->cd(1);
  Dif->SetAxisRange(0,20);
  Dif->Draw("p");
  Dif->GetXaxis()->SetTitle("Generated Multiplicity [pt>200 MeV, |eta|<2.4]");
  Dif->GetYaxis()->SetTitle("Efficiency difference (DAV-STD)");
  NLine(0,0,20,0);


  NDOF2->cd();
  pippo2DAV->SetAxisRange(0,20);
  NHSetMarker(pippo2DAV,2,20,0.8);
  NHSetMarker(pippo1DAV,2,20,0.8);

  NHSetMarker(pippo2STD,4,24,0.8);
  NHSetMarker(pippo1STD,4,24,0.8);
  pippo2DAV->SetMaximum(1.2);
  pippo2DAV->Draw("p");


  NLogAxis(0,0);
  
  pippo2STD->Draw("pSAME");
  // NLine(0,1,20,1);


  TLegend *leg = new TLegend(0.6,0.1, 0.8 ,0.4);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg->AddEntry(pippo2DAV,"Vertex Reconstruction A","p");  
  leg->AddEntry(pippo2STD,"Vertex Reconstruction B","p");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);  
  leg->SetFillColor(0);  
  leg->Draw();

  sprintf(CMSPrel,"CMS Preliminary,#sqrt{s} = 7 TeV, L = 36 pb^{-1}") ;
  NText(0.1,1.1,CMSPrel,1,0.07);


  pippo1DAV->Draw("pSAME");
  pippo1STD->Draw("pSAME");
  NLine(0,1,20,1,2);

  NText(3,0.8,"NDOF>=2");
  NText(15,0.6,"NDOF>=3");

  NDOF1->cd();
  NLogAxis(0,0);
  CWGen->SetAxisRange(1,30);
  CWGen->SetTitle("Track Multiplicity");
  CWGen->Draw();
  CWGen->GetXaxis()->SetTitle("Generated Multiplicity [pt>200 MeV, |eta|<2.4]");
  CWGen->GetYaxis()->SetTitle("Entries");

  CWGen->SetMinimum(0);
  NHSetMarker(CWMeas1,2,20,0.6);
  CWMeas1->Draw("SAME");

  NHSetMarker(CWMeas2,4,24,0.6);
  CWMeas2->Draw("SAME");

  cout << CWGen->Integral(4,100) << endl;
  cout << CWMeas1->Integral(4,100) << endl;
  cout << CWMeas2->Integral(5,100) << endl;

  cout << "Efficiency for 3 tracks: "<< CWMeas1->Integral(4,100)/CWGen->Integral(4,100) << endl;
  cout << "Efficiency for 4 tracks: "<< CWMeas2->Integral(5,100)/CWGen->Integral(5,100) << endl;


  TLegend *leg1 = new TLegend(0.5,0.7, 0.8 ,0.9);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  leg1->AddEntry(CWGen,"Generated","p");  
  leg1->AddEntry(CWMeas1,"Measured by NDOF>=2","p");
  leg1->AddEntry(CWMeas2,"Measured by NDOF>=3","p");
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.03);  
  leg1->Draw();
  TLine *NLine = new TLine(3,0,3,2200);
  NLine->SetLineColor(2);
  NLine->SetLineStyle(2);
  NLine->Draw();
  TArrow *NArrow = new TArrow(3,1700,8,1700,0.03,">");
  NArrow->SetLineColor(2);
  NArrow->SetLineStyle(1);
  NArrow->Draw();
  NText(3.2,1750,"Eff= 89%",2);
  


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
  //  NText(1.4, 200,"Luminosity too low");
  // NArrow(1.8,150,1.4,50,0.02, ">");

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
  // NText(1.4, 400,"Luminosity too low");
  // NArrow(1.8,350,1.4,50,0.02, ">");

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
  All1->SetMinimum(55);
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


  y[0] = 59.7;
  y[1] = 58.6;

  ey[0] = 0.1;
  ey[1] = 0.1;

  eys[0] = 1.1;
  eys[1] = 1.1;

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

