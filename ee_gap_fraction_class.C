#define ee_gap_fraction_class_cxx
#include "ee_gap_fraction_class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLegend.h>
#include "string.h"
#include <iomanip>
#include "NCutil.C"

TH1F *h_all;
TH1F *HF0;
TH1F *HF_ratio;
TH1F *Gap0;
TH1F *Gap_ratio;
TH1F *Castor0;
TH1F *Castor_ratio;

TH1F *Xi_HF0;
TH1F *Xi_HF0_03;
TH1F *Xi_HF0_lumi;
TH1F *Xi_HF0_03_lumi;


TH1F *evt_h_all;
TH1F *evt_HF0;
TH1F *evt_HF_ratio;
TH1F *evt_Gap0;
TH1F *evt_Gap_ratio;

TH1F *RunNumb;
TH1F *RunNumb_Castor0;
TH1F *RunNumb_HF0;
TH1F *RunNumb_Castor_ratio;
TH1F *RunNumb_HF_ratio;

TH1F *Ratio;
TH1F *Dat_ee_HF;
TH1F *Dat_Zll_HF;



const Int_t NDIR   = 2;  /* number or Directories*/
const Int_t hnbin = 14;

void ee_gap_fraction_class::Loop()
{

  int nbin = 14;
  //  TCanvas *MyC = new TCanvas("MyC","Test canvas",1);
  // MyC->Divide(1,2);


  /* bin limit */

  const int xbin = 15;
  Float_t xlow[xbin] = {0., 4.,10.,20.,40.,60.,90.,120.,150.,250.,400.,600.,800.,1000.,1500. };
  TH1F * HF_rat[xbin];
  TH1F * HF0_dat[xbin];

  gDirectory->Delete("h_all");
  gDirectory->Delete("HF_ratio");
  gDirectory->Delete("HF0");
  gDirectory->Delete("Gap_ratio");
  gDirectory->Delete("Gap0");
  gDirectory->Delete("Castor_ratio");
  gDirectory->Delete("Castor0");


  gDirectory->Delete("evt_h_all");
  gDirectory->Delete("evt_HF_ratio");
  gDirectory->Delete("evt_HF0");
  gDirectory->Delete("evt_Gap_ratio");
  gDirectory->Delete("evt_Gap0");

  gDirectory->Delete("RunNumb");
  gDirectory->Delete("RunNumb_HF0");
  gDirectory->Delete("RunNumb_HF_ratio");
  gDirectory->Delete("RunNumb_Castor_ratio");
  gDirectory->Delete("RunNumb_Castor0");


  h_all = new TH1F("h_all", "h_all", nbin, 0., 0.7);
  h_all->Sumw2();

  HF0 = NH1clone("HF0","HF0", h_all);
  HF_ratio = NH1clone("HF_ratio","HF_ratio", h_all);
  Gap0 = NH1clone("Gap0","Gap0", h_all);
  Gap_ratio = NH1clone("Gap_ratio","Gap_ratio", h_all);
  Castor0 = NH1clone("Castor0","Castor0", h_all);
  Castor_ratio = NH1clone("Castor_ratio","Castor_ratio", h_all);
  Xi_HF0_lumi = NH1clone("Xi_HF0_lumi","Xi_HF0_lumi", h_all);
  Xi_HF0_03_lumi = NH1clone("Xi_HF0_03_lumi","Xi_HF0_03_lumi", h_all);


  Xi_HF0 = new TH1F("Xi_HF0_lumi","Xi_HF0_lumi", 10,0.,0.05);
  Xi_HF0_03 = NH1clone("Xi_HF0_03","Xi_HF0_03", h_all);

  evt_h_all = new TH1F("evt_h_all", "evt_h_all", nbin, 0., 0.7);
  evt_h_all->Sumw2();

  evt_HF0 = NH1clone("evt_HF0","evt_HF0", evt_h_all);
  evt_HF_ratio = NH1clone("evt_HF_ratio","evt_HF_ratio", evt_h_all);
  evt_Gap0 = NH1clone("evt_Gap0","evt_Gap0", evt_h_all);
  evt_Gap_ratio = NH1clone("evt_Gap_ratio","evt_Gap_ratio", evt_h_all);


  RunNumb = new TH1F("RunNumb", "RunNumb",1000, 140000,150000);
  RunNumb->Sumw2();
  RunNumb_HF0 = NH1clone("RunNumb_HF0","RunNumb_HF0",RunNumb);
  RunNumb_Castor0 = NH1clone("RunNumb_Castor0","RunNumb_Castor0",RunNumb);
  RunNumb_HF_ratio = NH1clone("RunNumb_HF_ratio","RunNumb_HF_ratio",RunNumb);
  RunNumb_Castor_ratio = NH1clone("RunNumb_Castor_ratio","RunNumb_Castor_ratio",RunNumb);

  gDirectory->Delete("Ratio");
  Ratio = new TH1F("Ratio","Ratio", hnbin,xlow);
  Dat_ee_HF = NH1clone("Dat_ee_HF","Dat__ee_HF",Ratio);
  Dat_Zll_HF = NH1clone("Dat_Zll_HF","Dat_Zll_HF_Cor",Ratio);


  const int nHists=20;
  TH1F * myHists[nHists];

  myHists[0] =  h_all;
  myHists[1] =  HF0;
  myHists[2] =  HF_ratio;
  myHists[3] =  Gap0;
  myHists[4] =  Gap_ratio;
  myHists[5] =  Castor0;
  myHists[6] =  Castor_ratio;

  myHists[7] =  evt_h_all;
  myHists[8] =  evt_HF0;
  myHists[9] =  evt_HF_ratio;
  myHists[10] =  evt_Gap0;
  myHists[11] =  evt_Gap_ratio;


  myHists[12] =  RunNumb;
  myHists[13] =  RunNumb_Castor0;
  myHists[14] =  RunNumb_HF0;
  myHists[15] = RunNumb_Castor_ratio;
  myHists[16] = RunNumb_HF_ratio;

  myHists[17] =  Dat_ee_HF;
  myHists[18] =  Dat_Zll_HF;
  myHists[19] =  Xi_HF0;
  myHists[20] =  Xi_HF0_03;
  myHists[19] =  Xi_HF0_lumi;
  myHists[20] =  Xi_HF0_03_lumi;


  
  TFile *fA = new TFile("files/ZetaSkimA_ee_DL10.root");
  TTree *tree_fA= (TTree*)gDirectory->Get("tree_");

  TFile *fB = new TFile("files/ZetaSkimB_ee_DL10.root");
  TTree *tree_fB= (TTree*)gDirectory->Get("tree_");


  TCanvas* c[xbin];
  char cname[100]; 
  char hname[100]; 
  char hfname[100]; 
  char htitle[100]; 
  char hftitle[100]; 

  //Book the Histos

  for (Int_t j=0; j<xbin-1;j++){      

    Float_t xl = xlow[j];
    Float_t xu = xlow[j+1];
    
    sprintf(hname,"HF_rat%i",j);
    sprintf(htitle,"HF_rat%i_%f_%f",j,xl,xu);
    sprintf(hfname,"HF0_dat%i",j);
    sprintf(hftitle,"HF0_dat%i_%f_%f",j,xl,xu);
    
    HF_rat[j] = NH1clone(hname,htitle, evt_h_all); 
    HF0_dat[j] = NH1clone(hfname,hftitle, evt_h_all); 
  }
  
  for (Int_t i=1 ; i<=NDIR; i++){
      
      
      // Loop and RunA
      
      if (i==1){
	fChain =tree_fA;  /* Loop RunA */ 
      }
      else if (i==2){ 
	fChain =tree_fB;  /* Loop RunB */ 
      };
      
      Init(fChain);
      
      if (fChain == 0) return;
      
      Long64_t nentries = fChain->GetEntriesFast();
      
      cout << "file # "<< i << " has " << nentries << " entries" << endl;
      Long64_t nbytes = 0, nb = 0;
      for (Long64_t jentry=0; jentry<nentries;jentry++) {
	Long64_t ientry = LoadTree(jentry);
	if (ientry < 0) break;
	nb = fChain->GetEntry(jentry);   nbytes += nb;


       	bool RightSideGap = false ;
	if ( ( (sumEHF_PF_minus < sumEHF_PF_plus) && (xi_PF_minus < xi_PF_plus) ) ||
	     ( (sumEHF_PF_plus < sumEHF_PF_minus) && (xi_PF_plus < xi_PF_minus) ) ) RightSideGap = true;
	//	cout << "RightSideGap = " << RightSideGap << "Jentry = "<< jentry << endl;
	
	if(numberOfVertexes==1 && istlumiPerBX*6.37>0.005  && vertexMolteplicity[0]>=2 && RightSideGap) 
	  {
	    
	    Float_t MinHF = sumEHF_PF_plus;
	    Float_t MinXi = xi_PF_plus; 
	    if (sumEHF_PF_minus < sumEHF_PF_plus) {
	      MinHF = sumEHF_PF_minus;
	      MinXi = xi_PF_minus;
	    }
	    
	    for (Int_t j=0; j<xbin-1;j++){      
	      Float_t xl = xlow[j];
	      Float_t xu = xlow[j+1];	      
	      if (MinHF >=xl && MinHF <xu)
		{
		  HF0_dat[j]->Fill(istlumiPerBX*6.37);
		  break;
		}
	    }
	    
	    Dat_ee_HF->Fill(MinHF);
	    HF0->Fill(istlumiPerBX*6.37);
	    evt_HF0->Fill(istlumiPerBX*6.37,HFCor(istlumiPerBX,MinHF));
	    RunNumb_HF0->Fill(RunNumber);
	    
	      
	    if (MinHF==0){
	      Xi_HF0_lumi->Fill(istlumiPerBX*6.37);
	      Xi_HF0->Fill(MinXi);
	      
	      if (MinXi<0.03) {
		Xi_HF0_03_lumi->Fill(istlumiPerBX*6.37);
		// Xi_HF0_03->Fill(MinXi);
	      }
	    }

	    //	  if ( etaMax_PF<2.85  || etaMin_PF>-2.85 ) 	    {
	    if ( energyTot_PF_EE_minus==0  || energyTot_PF_EE_plus==0 ) 	    {
	      Gap0->Fill(istlumiPerBX*6.37);
	      evt_Gap0->Fill(istlumiPerBX*6.37,HFCor(istlumiPerBX,MinHF));
	    }
	    
	    if (sumECastor_Th_minus==0  && (RunNumber>140200 && RunNumber<146400))
	      {
		Castor0->Fill(istlumiPerBX*6.37);
		RunNumb_Castor0->Fill(RunNumber);
	      }
	   
	    h_all->Fill(istlumiPerBX*6.37);
	    evt_h_all->Fill(meanEvt(istlumiPerBX*6.37));
	    RunNumb->Fill(RunNumber);
	    
	  } // One vertex
      } //End of Events
  } //End of Directories
  
  
  // Plot using ee_gap_fraction_class_draw.C
  // Draw.....

  TCanvas *My = NCanvas(4,4);
    
  for (Int_t j=0; j<xbin-1;j++){      

    gStyle->SetOptFit(1111);
    My->cd(j+1); 
    //    HF0_dat[j]->Draw();
    // c[j]->cd(2); 
    HF_rat[j]->Divide(HF0_dat[j],h_all);
    HF_rat[j]->Fit("expo");
    //    HF_ratio->Fit("expo");
  }

  //
  TFile f("ee_gap_fraction_class_files.root","recreate"); 
  for (int i=0; i<nHists; i++) {
    myHists[i]->Write();
    cout << "writing file " << i << " to disks" << endl;
  }
  for (Int_t j=0; j<xbin-1;j++){      
    HF0_dat[j]->Write();
    HF_rat[j]->Write();
    cout << "writing file " << j << " to disks" << endl;
  }
  f.Close(); 
    
} //Loop


