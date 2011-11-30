#define MC_PU_Class_cxx
#include "MC_PU_Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "string.h"
#include <sstream>
#include <iomanip>
#include <TRandom.h>
#include "NCutil.C"
#include <iostream>
#include <fstream>
#include <TMath.h> 
#include <TProfile.h> 
#include <algorithm>

const Int_t BINS = 20;
TFile *MC;
TFile *Data;
TFile *fCorr;
TH1F *MCPU;
TH1F *LumiBin[BINS];
TH1F *pois_theory[BINS];
TH1F *Eff_corr[BINS];
TH1F *Eff_corr_MC[BINS];
TH1F *MC_Migration[BINS];
TH1F *MC_Vtx_Rew[BINS];
TH1F *MC_Vtx_Rew_NDOF2[BINS];
TH1F *MC_Vtx_Rew_NDOF2_Resc[BINS];
TH1F *LumiBin_Weight[BINS];
TH1F *MC_Mig_Ratio[BINS];
TH1F *Vxt_Lumi_MC[BINS];
TH1F *Vxt_Lumi[BINS];
TH1F *Vertex1Mult;
TH1F *Vertex1Mult_MC;
TH1F *Vertex1Mult_Ratio;
TH1F *Data_all_Lumi;
TH1F *GenVtx;
TH1F *RecVtx;
TH1F *GenRecVtx;
TH1F *RecGenRatio;
TH1F *Vtx1_HF0_MC;

char hname[100]; 
Float_t MinNDOF = 0;

Float_t Vertex_zpos[30];
Float_t Vertex_mult[30];
Int_t MinNtracksHighpT = 2 ;

Int_t TotVtx;

TFile *fA;
TTree *tree_fA;
TFile *fB;
TTree *tree_fB;

void MC_PU_Class::Loop()
{


  readfile();

  if (MC_MigF == 1 || MC_MigF == 11) // Use DW PU 2010
    {

      fA = new TFile("files/MCWtoenu_P6DW_PU2010_v1_16.root");
      tree_fA= (TTree*)gDirectory->Get("tree_");
      fChain =tree_fA;  /* mm Loop RunA */ 
    }
  else if (MC_MigF == 2 || MC_MigF == 21 ) // Use Z2 PU 2011
    {
      fB = new TFile("files/MCZZ_P6Z2_PU2011_v1_16.root");
      tree_fB= (TTree*)gDirectory->Get("tree_");
      fChain =tree_fB; 

    }


  TCanvas *MCW  = new TCanvas("MCW","MCW",1);
  TCanvas *MC_Rew  = new TCanvas("MC_Rew","MC_Rew",1);
  TCanvas *MC_Mig = new TCanvas("MC_Mig","MC_Mig",1);
  TCanvas *MC_Mig_Rat = new TCanvas("MC_Mig_Rat","MC_Mig_Rat",1);
  TCanvas *EffC =  new TCanvas("EffC","EffC",1);
  TCanvas *StartPU = new TCanvas("Start PU","Start PU",1);
  TCanvas *VtxLumi = new TCanvas("Vtx Lumi","Vtx Lumi",1);
  TCanvas *VtxMult = new TCanvas("VtxMult","VtxMult",1);
  TCanvas *pois = new TCanvas("pois","pois",1);
  TCanvas *TrkEff = new TCanvas("TrkEff","TrkEff",1);
  
  StartPU->Divide(1,1);
  MCW->Divide(4,4);
  MC_Rew->Divide(4,4);
  MC_Mig->Divide(4,4);
  MC_Mig_Rat->Divide(4,4);
  EffC->Divide(3,3);
  VtxLumi->Divide(3,4);
  VtxMult->Divide(1,2);
  pois->Divide(4,4);
  TrkEff->Divide(1,2);

  //  if (MC==0)   MC= TFile::Open(MigrationFile); 

  Data= TFile::Open(DataFile); 

  if (Data==0)
    {
      cout << "Problem with Data input file " << DataFile << endl;
      return;
    }
  
  MinNDOF = SelNDOF;
  //if (MinNtracksLowpT==2) MinNDOF = 0.1;

  Vertex1Mult = (TH1F*)Data->Get("Vertex1Mult");
  Data_all_Lumi = (TH1F*)Data->Get("Dat_all_Lumi");
  Vertex1Mult_MC = NH1clone("Vertex1Mult_MC","Vertex1Mult_MC",Vertex1Mult);
  Vertex1Mult_Ratio = NH1clone("Vertex1Mult_Ratio","Vertex1Mult_Ratio",Vertex1Mult);

  GenVtx = new TH1F("GenVtx","GenVtx", 100,0.,100);
  RecVtx = new TH1F("RecVtx","RecVtx", 100,0.,100);
  GenRecVtx = new TH1F("GenRecVtx","GenRecVtx", 100,0.,100);

  const Int_t MaxVtxInEvent=18;
  Float_t NRS = 5000.; 
  Float_t sigma_NSD =  Sigma*pow(10,-24);

  //Read the luminosity bins and the "theory Pois. vertex Distributions"

  for (Int_t N=MinLumBin;N<LumBin; N++)
    {

      sprintf(hname,"LumiBin%i",N+1);
      LumiBin[N] = (TH1F*)Data->Get(hname);

      if (LumiBin[N]==0) 
	{
	  cout << " File not found: "<< LumiBin[N] << " LumiBin "<< N << endl ;
	  return;
	}
      
      Double_t Lumi = LumiBin[N]->GetMean();
      //if (Lumi==0) {
          cout << " Luminosity = " << Lumi << " for bin "<< N << endl ;
	  //  Lumi = 0.01;
	  //	  continue;
	  //  }


      sprintf(hname,"Pois_Theory_Lumi%5.3f",Lumi);
      gDirectory->Delete(hname);
      pois_theory[N]  = new TH1F(hname,hname,MaxVtxInEvent,0,MaxVtxInEvent); // Pois hystograms
      pois_theory[N]->Sumw2();
      if (SystCheck != 9){
	for (Int_t NL = 1; NL<=NRS; NL++)
	  {
	    
	    Double_t LumiR = LumiBin[N]->GetRandom();
	    
	    for (Int_t p=0;p<MaxVtxInEvent;p++)
	      {
		
		Float_t Lum_bunch = (LumiR*pow(10,30)/11346)*sigma_NSD ;
		Float_t pois_prob = pow(Lum_bunch,p) * exp(-Lum_bunch)/TMath::Factorial(p) ;		
		pois_theory[N]->Fill(p+0.01,pois_prob);
		
	      }
	  }
	
	//	cout << "pippo2" << endl;
	if (pois_theory[N]->GetEntries() !=0)
		  {
	    pois_theory[N]->Scale(1./NRS);
	    pois->cd(N+1);
	    pois_theory[N]->Draw();
	  }
	//	cout << "pippo3" << endl;
      }
      else if (SystCheck == 9){
	for (Int_t p=0;p<MaxVtxInEvent;p++)
	  {
	    //  cout << " p = "<<p<< " and prob_evt= "<< prob_evt(Lumi,p)  << endl;    
	    Float_t Lum_bunch = (Lumi*pow(10,30)/11346)*sigma_NSD ;
	    Float_t pois_prob = pow(Lum_bunch,p) * exp(-Lum_bunch)/TMath::Factorial(p) ;
	    pois_theory[N]->SetBinContent(p+1,pois_prob); // Here is has to be p+1       
	  }
	pois->cd(N+1);
	pois_theory[N]->Draw();
      }

      //      cout << "pippo4" << endl;

      Int_t NLumi = Lumi*100;
      sprintf(hname,"MC_Weight_Lumi%i",NLumi);
      LumiBin_Weight[N] = NH1clone(hname,hname,pois_theory[N]);
      sprintf(hname,"MC_Vtx_Rew%i",NLumi);
      MC_Vtx_Rew[N] = NH1clone(hname,hname,pois_theory[N]);
      sprintf(hname,"MC_Vtx_Rew_NDOF%i",NLumi);
      MC_Vtx_Rew_NDOF2[N] = NH1clone(hname,hname,pois_theory[N]);
      sprintf(hname,"MC_Migration%i",NLumi);
      MC_Migration[N] = NH1clone(hname,hname,pois_theory[N]);


      sprintf(hname,"MC_Analytic_Mig_Ratio%5.3f",Lumi);
      MC_Mig_Ratio[N] = NH1clone(hname,hname,pois_theory[N]);
      
      if (Data_all_Lumi == 0) 
	{
	  cout << "Problem in opening Data_all_Lumi" << endl;
	  return;
	}

    }

  for (Int_t N=0;N<=NumPU; N++)
    {
      sprintf(hname,"Eff_%iNvtx_MC",N);
      Eff_corr_MC[N]=  NH1clone(hname,hname,Data_all_Lumi);
      sprintf(hname,"Vxt_Lumi%i_MC",N);      
      Vxt_Lumi_MC[N]=  NH1clone(hname,hname,Data_all_Lumi);

    }
  sprintf(hname,"Vtx1_HF0_MC");
  Vtx1_HF0_MC =  NH1clone(hname,hname,Data_all_Lumi);
  // Vtx1_HF0_MC->Sumw2();

  MCPU = NH1clone("MCPU","MCPU",pois_theory[3]);


  Init(fChain);
  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   cout << "file # "<< MC_MigF << " has " << nentries << " entries" << endl;

   Long64_t nbytes = 0, nb = 0;

   //compute the starting distribution

   for (Long64_t jentry=0; jentry<nentries;jentry++) 
     // for (Long64_t jentry=0; jentry<10;jentry++) 
     {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       MCPU->Fill(PU_NumInt);

       //       if (PU_NumInt==1)   Vertex1Mult_MC->Fill(PU_ntrks_lowpT[0]);
       if (PU_NumInt==1) 
	 {
	   
	   if (fabs(sqrt(pow(V_x[1],2)+pow(V_y[1],2))-0.463)<MinSig)
	     {
	       Vertex1Mult_MC->Fill(vertexMolteplicity[1]);
	     }
	 }
     }


   VtxMult->cd(1);
   Float_t scale2 = Vertex1Mult->Integral()/Vertex1Mult_MC->Integral();
   Vertex1Mult_MC->Scale(scale2);

   Vertex1Mult_MC->Draw();
   Vertex1Mult->Draw("pSAME");

   TLegend *leg3 = new TLegend(0.6,0.6, 0.9 ,0.8);
   leg3->AddEntry(Vertex1Mult_MC,"MC Vertex Mult","L");  
   leg3->AddEntry(Vertex1Mult,"Data vertex Mult","p");
   leg3->SetFillColor(0);
   leg3->SetBorderSize(0);
   leg3->SetTextSize(0.09);  
   leg3->Draw();
   VtxMult->cd(2);

   Vertex1Mult_Ratio->Add(Vertex1Mult);
   Vertex1Mult_Ratio->Divide(Vertex1Mult_MC);

   Vertex1Mult_Ratio->Draw();

   //   return;

   StartPU->cd(1);
   MCPU->Draw();
   //   Int_t Normaliz = MCPU->GetEntries();

   // Compute the Lumi weights

   for (Int_t N=MinLumBin;N<LumBin; N++)
    {


      LumiBin_Weight[N]->Add(pois_theory[N]);
      LumiBin_Weight[N]->Divide(MCPU);
      Float_t scale =  LumiBin_Weight[N]->Integral();
      LumiBin_Weight[N]->Scale(1./scale);

      //Do I need to scale the bins by the entries in each bin ?
      //Double_t Lumi = LumiBin[N]->GetEntries();
      //  LumiBin_Weight[N]->Scale(Lumi);
      //cout << "Lumi  = " << Lumi << endl;
      // cout << " Sum of weight = " <<  (float) LumiBin_Weight[N]->Integral() << endl;

      MCW->cd(N+1);
      LumiBin_Weight[N]->GetXaxis()->SetRange(0,10);
      LumiBin_Weight[N]->Draw();
      NLogAxis(0,1);
    }


   Int_t  Nindex[20]= {0};
   Int_t ShortDist = 0;
   Float_t LostToPos = 0;
   Float_t LostToMerg = 0;
   Float_t LostToNDOF = 0;
   Int_t VtxTot = 0;



   //Computed the weighted distributions


   Int_t PU1C1 = 0;
   Int_t PU1C2 = 0;
   Int_t PU1C3 = 0;
   Int_t PU1C4 = 0;
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
     //  for (Long64_t jentry=0; jentry<100;jentry++) 
     // for (Long64_t jentry=0; jentry<10;jentry++) 
     {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;

       if (PU_NumInt==1) PU1C1++;
       Int_t True_Vtx = TrueVtx();


       if (PU_NumInt==1 && True_Vtx ==1 ) PU1C2++;
       Float_t Weight = 0;
       Float_t Weight_Mult = 0.;
       Int_t Bin = 0;
       Bool_t down = false;
       Int_t GoodVtx=0;
       Int_t Nvtx_NDOF2 = 0;


       Vertex_zpos[0] = V_z[0]; // z-pos of the primary Vtx
       Vertex_mult[0] = vertexMolteplicity[0];

       for (Int_t Nv = 1;Nv<numberOfVertexes;Nv++) //Loop only on PU vertices (Nv !=0)
	 {
	    bool VtxTransPos = false;
	    bool VtxNTrack = false;
	    
	    // bool VtxTransPos = true;
	    if (SystCheck == 40) VtxNTrack = true;	 

	    // 
	    // MinNDOF = 0.;
	    // MinDist = 0.;
	    
	    
	    if (PU_NumInt==1) PU1C3++;
	    if (vertexMolteplicity[Nv] >= MinNtracksLowpT) VtxNTrack = true;

	   if (fabs(sqrt(pow(V_x[Nv],2)+pow(V_y[Nv],2))-0.463)<MinSig)   VtxTransPos = true;	
	   if(!VtxTransPos)     LostToPos++;

	   if (vertexNDOF[Nv]<MinNDOF) LostToNDOF++;

	   if (vertexNDOF[Nv]>=MinNDOF && VtxTransPos && VtxNTrack ) 
	     {
	       Nvtx_NDOF2++;
	       Vertex_zpos[Nvtx_NDOF2] = V_z[Nv];
	       Vertex_mult[Nvtx_NDOF2] = vertexMolteplicity[Nv];
	     
	       if (vertexMolteplicity[Nv] == 0)
		 cout << " zero Mult!!! " <<  vertexNDOF[Nv] << endl;

	       Int_t tmp = Vertex1Mult_Ratio->FindBin(vertexMolteplicity[Nv]);
	       Float_t dummy =    Vertex1Mult_Ratio->GetBinContent(tmp);
	       Weight_Mult += dummy;

	     }
	   
	 } // Nvtx_NDOF2 = Good PU  vertices

       if (Nvtx_NDOF2>0)    Weight_Mult = Weight_Mult/Nvtx_NDOF2;
       if (SystCheck == 30) Weight_Mult = 1;

       TMath::Sort(Nvtx_NDOF2+1, Vertex_zpos, Nindex, down);
       
       GoodVtx = 0;
       
       for (Int_t kl = 1;kl<=Nvtx_NDOF2;kl++)
	 {
	   Int_t ip = Nindex[kl];
	   Int_t ipm1 = Nindex[kl-1];
	   Float_t Dist = fabs(Vertex_zpos[ip]-Vertex_zpos[ipm1]);
	   if (Dist> MinDist)  
	     {
	       GoodVtx++ ;
	       if (PU_NumInt==1) PU1C4++;
	     }
	   if (Dist <= MinDist)  LostToMerg++;

	   
	 }

       VtxTot += GoodVtx; 
       
       if (PU_NumInt == 1 && GoodVtx >0 ) 
	 {
	   RecVtx->Fill(Vertex_mult[1]);
	   GenRecVtx->Fill(PU_ntrks_lowpT[0]);
	 }    

       for (Int_t N=MinLumBin;N<LumBin; N++)  // Fill every LumiBin
	  {  	   
	    Bin = LumiBin_Weight[N]->FindBin(PU_NumInt);
	    
	    if (GoodVtx == 0) Weight_Mult = 1.;


	    //The total weight is the product of the weight_lum and the weight_mult

	    Weight = LumiBin_Weight[N]->GetBinContent(Bin)*Weight_Mult;


	    MC_Vtx_Rew_NDOF2[N]->Fill(GoodVtx,Weight);
	    MC_Vtx_Rew[N]->Fill(True_Vtx,Weight);	    	    
	    if ( (GoodVtx==1  && TMath::Min(sumEHF_PF_plus,sumEHF_PF_minus) ==0))
	      {
		Double_t Lumi = LumiBin[N]->GetMean();
		Vtx1_HF0_MC->Fill(Lumi,Weight);
	      }
	  }


     }

   cout << "All= " << PU1C1<<  " Good for us= " << PU1C2 << " with 1 Rec vertex= " << PU1C3 << " Final = " << PU1C4 << endl;
   cout << "Lost to Position = "<< (float_t) LostToPos/VtxTot << endl;
   cout << "Lost to NDOF  = "<< (Float_t) LostToNDOF/VtxTot << endl;
   cout << "Lost to Merging (Min Dist = "<< MinDist <<" ) = "<< (Float_t)LostToMerg/VtxTot << endl;
   
   for (Int_t oo=MinLumBin;oo<LumBin;oo++)
     {
       MC_Vtx_Rew_NDOF2_Resc[oo]= (TH1F*) MC_Vtx_Rew_NDOF2[oo]->Clone();
       sprintf(hname,"MC_Vtx_Rew_NDOF_Resc%i",oo);
       MC_Vtx_Rew_NDOF2_Resc[oo]->SetName(hname);
       MC_Vtx_Rew_NDOF2_Resc[oo]->SetTitle(hname);
       Double_t Lumi = LumiBin[oo]->GetEntries()/MC_Vtx_Rew_NDOF2_Resc[oo]->Integral();
       // cout << "Lumi = " << Lumi << endl;
       MC_Vtx_Rew_NDOF2_Resc[oo]->Scale(Lumi);
     }

   //   cout << "Fraction of events lost due to vertex overlapping = " << 1.*ShortDist/nentries << endl;
   //   cout << "Minimum Distance = " << MinDist << endl;
   // cout << "Minimum NDOF = " << MinNDOF << endl;

   // Draw the result of this part

   TrkEff->cd(1);
   RecVtx->Draw();

   GenVtx->SetLineStyle(2);
   GenVtx->SetLineColor(2);
   GenVtx->Draw("SAMES");

   GenRecVtx->SetLineStyle(4);
   GenRecVtx->SetLineColor(4);
   GenRecVtx->Draw("SAMES");

   RecGenRatio = NH1clone("RecGenRatio","RecGenRatio",GenRecVtx);
   RecGenRatio->Add(GenRecVtx);
   RecGenRatio->Divide(GenVtx);

   TrkEff->cd(2);
   RecGenRatio->Draw();

   


   for (Int_t N=MinLumBin;N<LumBin; N++)
     {

     MC_Rew->cd(N+1);

     NH1FArea1(MC_Vtx_Rew[N]);
     NH1FArea1(MC_Vtx_Rew_NDOF2[N]);
     NH1FArea1(pois_theory[N]);

     MC_Vtx_Rew[N]->GetXaxis()->SetRange(0,10);
     //     
     MC_Vtx_Rew[N]->GetYaxis()->SetTitle("Vertices");
     //MC_Vtx_Rew_NDOF2[N]->Draw("SAMEHIST");
     MC_Vtx_Rew_NDOF2[N]->SetMinimum(0.0001);

     NSetTitleSize(MC_Vtx_Rew_NDOF2[N], .65,.9,0.09);
     NSetLabelSize(MC_Vtx_Rew_NDOF2[N], 0.01,0.01,0.07);

     sprintf(hname,"Events in Lum. bin  %i ",N+1);
     MC_Vtx_Rew_NDOF2[N]->GetXaxis()->SetTitle("# of Vertices");
     MC_Vtx_Rew_NDOF2[N]->GetYaxis()->SetTitle(hname);

     MC_Vtx_Rew_NDOF2[N]->Draw();
     MC_Vtx_Rew[N]->Draw("SAMEHIST");
     pois_theory[N]->SetLineColor(2);
     pois_theory[N]->SetLineStyle(2);

     pois_theory[N]->Draw("SAMEHIST");
     NLogAxis(0,1);



     MC_Mig->cd(N+1);



     if (MC_Vtx_Rew[N]->GetEntries() !=0) 
       {
	 MC_Migration[N]->Add(MC_Vtx_Rew_NDOF2[N]);
	 MC_Migration[N]->Divide(MC_Vtx_Rew[N]);
       }
     // MC_Migration[N]->Divide(pois_theory[N]);
     MC_Migration[N]->SetMaximum(2.);
     MC_Migration[N]->SetMinimum(0.);
     MC_Migration[N]->GetXaxis()->SetRange(0,10);
     MC_Migration[N]->Draw();
     // Meas_over_Theory[N]->Draw("SAMEHIST");

     MC_Mig_Ratio[N]->Add(MC_Migration[N]);
     // MC_Mig_Ratio[N]->Divide(Meas_over_Theory[N]);
     MC_Mig_Rat->cd(N+1);
     MC_Mig_Ratio[N]->GetXaxis()->SetRange(0,10);
     MC_Mig_Ratio[N]->Draw();
     MC_Mig_Ratio[N]->SetMinimum(0.5);
     MC_Mig_Ratio[N]->SetMaximum(1.5);


     }



   MC_Rew->cd(15);
   TLegend *leg2 = new TLegend(LowLim,0.2, UpLim ,0.8);
   //  leg->SetfMargin(0.1);
   //  leg->SetTextSize(14);

   leg2->AddEntry(pois_theory[1],"Poisson Theory","L");
   leg2->AddEntry(MC_Vtx_Rew[1],"MC Generated, p_{t}>200 MeV ","L");  
   leg2->AddEntry(MC_Vtx_Rew_NDOF2[1],"MC Reconstructed, p_{t}>200 MeV","p");
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->SetTextSize(0.09);  
   leg2->Draw();

   sprintf(hname,"CMS Simulation") ;
   NText(0.1,0.9,hname,1,0.12);

  // Prepare the correction hystos
  

   Float_t BinCont= 0;
   Float_t BinErr = 0;

   //   for (Int_t p=1;p<=LumBin;p++)
   for (Int_t p=1;p<=NumPU+1;p++)
     {      //loop over the bin
       for (Int_t p1=1;p1<=LumBin;p1++)
	 {  // loop over the histos

	   if (LumiBin[p1-1]->GetMean()!=0)
	     {	
	       BinCont = MC_Migration[p1-1]->GetBinContent(p);
	       BinErr = MC_Migration[p1-1]->GetBinError(p);

	       Eff_corr_MC[p-1]->SetBinContent(p1,BinCont);
	       Eff_corr_MC[p-1]->SetBinError(p1,BinErr);
	      
	       BinCont = MC_Vtx_Rew_NDOF2_Resc[p1-1]->GetBinContent(p);
	       BinErr = MC_Vtx_Rew_NDOF2_Resc[p1-1]->GetBinError(p);


	       if (p < LumBin)
		 {
		   Vxt_Lumi_MC[p]->SetBinContent(p1,BinCont);
		   Vxt_Lumi_MC[p]->SetBinError(p1,BinErr);
		 }
	     }
	 }
     }
   
     cout << " pippo " << endl;
   // Draw the reconst. Vertices

   for (Int_t N=1+MinLumBin;N<TMath::Min(12,LumBin); N++)
     {
       VtxLumi->cd(N);
       NHSetMarker(Vxt_Lumi_MC[N],2,24,0.4);
       sprintf(hname,"Vxt_Lumi%i",N);      
       Vxt_Lumi[N] = (TH1F*)Data->Get(hname);

        if (Vxt_Lumi_MC[N]->Integral() != 0)
	 {
	   Float_t Entries =  Vxt_Lumi[N]->GetEntries()/Vxt_Lumi_MC[N]->Integral();       
	   cout << "Should scale by " << Entries << endl;
	   
	   //	   if (Entries != 0)     Vxt_Lumi_MC[N]->Scale(1.);
	 }
       
       //       Vxt_Lumi_MC[N]->Draw("HIST");
	NHSetMarker(Vxt_Lumi[N],4,20,1.);
	Vxt_Lumi[N]->Draw("p");
       Vxt_Lumi_MC[N]->Draw("SAMEHIST");
       
       //       NSetTitleSize(Vxt_Lumi[N], 0.7,1.,0.08);
       //NSetLabelSize(Vxt_Lumi[N], 0.01,0.01,0.06);

       Vxt_Lumi[N]->GetYaxis()->SetTitleSize(0.08);
       Vxt_Lumi[N]->GetXaxis()->SetTitleSize(0.08);
       Vxt_Lumi[N]->GetYaxis()->SetTitleOffset(1.);
       Vxt_Lumi[N]->GetXaxis()->SetTitleOffset(0.7);
       
       Vxt_Lumi[N]->GetYaxis()->SetLabelSize(0.06);
       Vxt_Lumi[N]->GetXaxis()->SetLabelSize(0.06);
       Vxt_Lumi[N]->GetYaxis()->SetLabelOffset(0.01);
       Vxt_Lumi[N]->GetXaxis()->SetLabelOffset(0.01);

		// */

       sprintf(hname,"Events with %i vtx",N);
       Vxt_Lumi[N]->GetYaxis()->SetTitle(hname);
       Vxt_Lumi[N]->GetXaxis()->SetTitle("Luminosity  10^{30} [cm^{-2} s^{-1}]");



     }

   cout << "pippo1" << endl;
   VtxLumi->cd(12);
   TLegend *leg = new TLegend(LowLim,0.2, UpLim ,0.8);
   //  leg->SetfMargin(0.1);
   //  leg->SetTextSize(14);
   leg->AddEntry(Vxt_Lumi_MC[1],"MC Simulation","L");  
   leg->AddEntry(Vxt_Lumi[1],"Data","P");
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.09);  
   leg->Draw();

   sprintf(hname,"CMS Preliminary, #sqrt{s} = 7 TeV, L = 36 pb^{-1}") ;
   NText(0.1,0.8,hname,1,0.11);


   //   for (Int_t N=0+MinLumBin;N<TMath::Min(12,LumBin); N++)
   for (Int_t N=0;N<=NumPU; N++)
     {
       EffC->cd(N+1);
       NHSetMarker(Eff_corr_MC[N],2,24,0.4);
       sprintf(hname,"(Measured/True) events with %i PU",N);
       Eff_corr_MC[N]->GetYaxis()->SetTitle(hname);
       NSetTitleSize(Eff_corr_MC[N], .8,.85,0.06);
       NSetLabelSize(Eff_corr_MC[N], 0.01,0.01,0.07);
       Eff_corr_MC[N]->Draw();
       Eff_corr_MC[N]->SetMinimum(.0);
       Eff_corr_MC[N]->SetMaximum(2.5);
       // Eff_corr[N]->Draw("SAMEHIST");

     }


   

   EffC->cd(9);
   TLegend *leg1 = new TLegend(LowLim,0.2, UpLim ,0.6);
   //  leg->SetfMargin(0.1);
   //  leg->SetTextSize(14);
   leg1->AddEntry(Eff_corr_MC[1],"Monte Carlo","p");  
   // leg1->AddEntry(Eff_corr[1],"Analytic Calculation","L");
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->SetTextSize(0.09);  
   leg1->Draw();

   sprintf(hname,"CMS Simulation") ;
   NText(0.1,0.8,hname,1,0.11);
  

   cout << "Not Writing Migration Correction File: " << MCMigFile << endl;

   //   TFile fCo(MCMigFile, "RECREATE" );

   fCorr = new TFile(MCMigFile,"recreate");     
   // fCorr = new TFile("fCorr","recreate");     
   //
   for (Int_t N=0;N<LumBin; N++)
   //   for (Int_t N=0;N<0; N++)
     {

       MC_Migration[N]->Write();
       MC_Vtx_Rew[N]->Write();
       MC_Vtx_Rew_NDOF2[N]->Write();
       LumiBin_Weight[N]->Write();
       MC_Mig_Ratio[N]->Write();
       Vxt_Lumi_MC[N]->Write();
       pois_theory[N]->Write();

     }


   for (Int_t N=0;N<=NumPU; N++)
   //   for (Int_t N=0;N<0; N++)
     {
       Eff_corr_MC[N]->Write();
     }



   Vertex1Mult_Ratio->Write();
   Vertex1Mult->Write();
   Vertex1Mult_MC->Write();
   Data_all_Lumi->Write();
   RecVtx->Write();
   GenVtx->Write();
   GenRecVtx->Write();
   RecGenRatio->Write();   
   Vtx1_HF0_MC->Write();   
   cout << "done!" << endl;

   fCorr->Close();




}



Int_t MC_PU_Class::TrueVtx()
{

  Int_t True_Vtx = 0;

  for (Int_t UU = 0; UU<PU_NumInt; UU++)
    {
      if (PU_sumpT_lowpT[UU]>= (1.*MCPt*MinNtracksLowpT)/1000. && PU_ntrks_lowpT[UU] >= MinNtracksLowpT)  
	{
	  if (PU_NumInt == 1) GenVtx->Fill(PU_ntrks_lowpT[UU]);
	  True_Vtx++;	       	  
	}
    }

  
  return(True_Vtx); // this is already the number of PU

}

