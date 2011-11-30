#define Ghosts_Removal_Class_cxx
#include "Ghosts_Removal_Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <TMath.h>
#include <TLegend.h>
#include "string.h"
#include <iomanip>
#include "NCutil.C"

TH1F * Ratio;
TH1F * Pom_HF;
TH1F * Pom_Xi;
TH1F * PytD6T_HF;
TH1F * PytZ2_HF;
TH1F * PytD6T_Xi;
TH1F * PytZ2_Xi;
TH1F * Dat_HF;
TH1F * Dat_HF_NoGhosts;
TH1F * Ghosts_HF;
TH1F * Dat_HF_LowLumi;
TH1F * Dat_HF_HighLumi;

TH1F * Lumi_HF_LowLumi;
TH1F * Lumi_HF_HighLumi;
TH1F * Lumi_HF_all;
TH1F * Lumi_Xi_LowLumi;
TH1F * Lumi_Xi_HighLumi;
TH1F * Lumi_Xi_all;

TH1F * Dat_HF_Cor;
TH1F * Ratio_HF_HighLumi;
TH1F * Ratio_HF_LowLumi;
TH1F * Ratio_HF;

TH1F * Dat_Xi_LowLumi; 
TH1F * Dat_Xi_HighLumi;
TH1F * Dat_Xi;
TH1F * Dat_Xi_Cor;
TH1F * Ghosts_Xi;
TH1F * Dat_Xi_NoGhosts;


TTree          *fChain;   //!Pointer to the analyzed TTree or TChain

const Int_t NDIR   = 7;  /* number or Directories*/

const Int_t hnbin = 14;

void Ghosts_Removal_Class::Loop()
{

  int nbin = 100;

  // HF plots

  Float_t xlow[15] = {0., 4.,10.,20.,40.,60.,90.,120.,150.,250.,400.,600.,800.,1000.,1500. };

  gDirectory->Delete("Ratio");
  Ratio = new TH1F("Ratio","Ratio", hnbin,xlow);
  Pom_HF = NH1clone("Pom_HF","Pom_HF",Ratio);
  PytD6T_HF = NH1clone("PytD6T_HF","Pyt_HF",Ratio);
  PytZ2_HF = NH1clone("PytZ2_HF","Pyt_HF",Ratio);
  Dat_HF_LowLumi = NH1clone("Dat_HF_LowLumi","Dat_HF",Ratio);
  Dat_HF_HighLumi = NH1clone("Dat_HF_HighLumi","Dat_HF",Ratio);
  Dat_HF = NH1clone("Dat_HF","Dat_HF",Ratio);
  Dat_HF_Cor = NH1clone("Dat_HF_Cor","Dat_HF_Cor",Ratio);
  Ratio_HF_LowLumi = NH1clone("Ratio_HF_LowLumi","Ratio_HF",Ratio);
  Ratio_HF_HighLumi = NH1clone("Ratio_HF_HighLumi","Ratio_HF",Ratio);
  Dat_HF_NoGhosts=NH1clone("Dat_HF_NoGhosts","Dat_HF_NoGhosts",Dat_HF_LowLumi);
  Ghosts_HF=NH1clone("Ghosts_HF","Ghosts_HF",Dat_HF_LowLumi);

  //Xi plots

  gDirectory->Delete("Dat_Xi_LowLumi");
  Dat_Xi_LowLumi = new TH1F("Dat_Xi_LowLumi","Dat_Xi",10 ,0.,0.1);
  Dat_Xi_HighLumi = NH1clone("Dat_Xi_HighLumi","Dat_Xi",Dat_Xi_LowLumi);
  Dat_Xi = NH1clone("Dat_Xi","Dat_Xi",Dat_Xi_LowLumi);
  Dat_Xi_Cor = NH1clone("Dat_Xi_Cor","Dat_Xi_Cor",Dat_Xi_LowLumi);
  Ghosts_Xi=NH1clone("Ghosts_Xi","Ghosts_Xi",Dat_Xi_LowLumi);
  Dat_Xi_NoGhosts=NH1clone("Dat_Xi_NoGhosts","Ghosts_Xi",Dat_Xi_LowLumi);
  PytD6T_Xi=NH1clone("PytD6T_Xi","Ghosts_Xi",Dat_Xi_LowLumi);
  PytZ2_Xi=NH1clone("PytZ2_Xi","Ghosts_Xi",Dat_Xi_LowLumi);
  Pom_Xi=NH1clone("Pom_Xi","Pom_Xi",Dat_Xi_LowLumi);


  // Lumi plots

  gDirectory->Delete("Lumi_HF_all");
  Lumi_HF_all = new TH1F("Lumi_HF_all","Lumi", 28,0.,0.7);
  Lumi_HF_HighLumi = NH1clone("Lumi_HF_HighLumi", "Lumi_HighLumi",Lumi_HF_all);
  Lumi_HF_LowLumi = NH1clone("Lumi_HF_LowLumi", "Lumi_LowLumi",Lumi_HF_all);
  Lumi_Xi_HighLumi = NH1clone("Lumi_Xi_HighLumi", "Lumi_HighLumi",Lumi_HF_all);
  Lumi_Xi_LowLumi = NH1clone("Lumi_Xi_LowLumi", "Lumi_LowLumi",Lumi_HF_all);
  Lumi_Xi_all = NH1clone("Lumi_Xi_all", "Lumi_LowLumi",Lumi_HF_all);


  const int nHists=26;
  TH1F * myHists[nHists];
  myHists[0] = Lumi_HF_all;
  myHists[1] = Lumi_HF_HighLumi;
  myHists[2] = Lumi_HF_LowLumi;
  myHists[3] = Lumi_Xi_HighLumi;
  myHists[4] = Lumi_Xi_LowLumi;
  myHists[5] = Lumi_Xi_all;
  myHists[6] = Ratio;
  myHists[7] = PytD6T_HF;
  myHists[8] = PytZ2_HF;
  myHists[9] = Dat_HF_LowLumi;
  myHists[10] = Dat_HF_HighLumi;
  myHists[11] = Dat_HF;
  myHists[12] = Dat_HF_Cor;
  myHists[13] = Ratio_HF_LowLumi;
  myHists[14] = Ratio_HF_HighLumi;
  myHists[15] = Dat_HF_NoGhosts;
  myHists[16] = Ghosts_HF;
  myHists[17] = Dat_Xi_LowLumi;
  myHists[18] = Dat_Xi_HighLumi;
  myHists[19] = Dat_Xi;
  myHists[20] = Dat_Xi_Cor;
  myHists[21] = Ghosts_Xi;
  myHists[22] = Dat_Xi_NoGhosts;
  myHists[22] = PytD6T_Xi;
  myHists[23] = PytZ2_Xi;
  myHists[24] = Pom_HF;
  myHists[25] = Pom_Xi;
  
  for (int i=0; i<nHists; i++) {
    myHists[i]->Sumw2();
  }
  
  TFile *fZ2 = new TFile("files/pythiaZ2_ee_v1_2.root");
  TTree *tree_fZ2= (TTree*)gDirectory->Get("tree_");

  TFile *fD6T = new TFile("files/pythiaD6T_ee_v1_2.root");
  TTree *tree_fD6T= (TTree*)gDirectory->Get("tree_");


  TFile *fB = new TFile("files/ZetaSkim_ee_v1.root");
  TTree *tree_fZee= (TTree*)gDirectory->Get("tree_");


  TFile *fmu = new TFile("files/ZetaSkim_mm_v1.root");
  TTree *tree_fZmm= (TTree*)gDirectory->Get("tree_");

  TFile *fee = new TFile("files/ZetaSkimB_ee_DL10.root");
  TTree *tree_fee= (TTree*)gDirectory->Get("tree_");

  TFile *fpom_Zee = new TFile("files/DiffractiveMC_ee_v1_2.root");
  TTree *tree_fpom_Zee= (TTree*)gDirectory->Get("tree_");

  TFile *fpom_Zmm = new TFile("files/DiffractiveMC_mm_v1_2.root");
  TTree *tree_fpom_Zmm = (TTree*)gDirectory->Get("tree_");


  // Lumi intervals
  Float_t LowLumi_Low = 0.005;
  Float_t LowLumi_High = 0.25;
  Float_t HighLumi_Low = 0.40;
  Float_t HighLumi_High = 0.55;


  TCanvas *MyC = new TCanvas("MyC","Test canvas",1);
  MyC->Divide(1,2);

  for (Int_t i=1 ; i<=NDIR; i++){
    
    // Loop and RunA
    
    if (i==1){
      fChain =tree_fD6T;  /* Loop RunB */ 
    }
    else if (i==2){ 
      fChain =tree_fZee;  /* Loop RunB */ 
    }
    else if (i==3){ 
      fChain =tree_fZmm;  /* Loop RunB */ 
    }
    else if (i==4){ 
      fChain =tree_fee;  /* Loop RunB */ 
    }
    else if (i==5){ 
      fChain =tree_fZ2;  /* Loop RunB */ 
    }
    else if (i==6){ 
      fChain =tree_fpom_Zee;  /* Pompyt, not used for the analysis but good to have*/ 
    }
    else if (i==7){ 
      fChain =tree_fpom_Zmm;  /* Pompyt, not used for the analysis but good to have*/ 
    };
    
    Init(fChain);


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   cout << "File number " << i << " has " << nentries << " entries" << endl; 
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {


      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;


      if(numberOfVertexes==1 && vertexMolteplicity[0]>=2) 
	{

	  //	 cout << vertexMolteplicity << endl;

	  Float_t MinHF = sumEHF_PF_plus;
	  Float_t MinXi = xi_PF_plus; 
	  if (sumEHF_PF_minus < sumEHF_PF_plus) {
	    MinHF = sumEHF_PF_minus;
	    MinXi = xi_PF_minus;
	  }

	  Float_t LumCor = istlumiPerBX*6.37 ;
	  
	  if (i==1) { // Pythia D6T
	    PytD6T_HF->Fill(MinHF);
	    if (MinHF <1.)
	      PytD6T_Xi->Fill(MinXi);
	  };
	  if (i==5) { // Pythia Z2
	    PytZ2_HF->Fill(MinHF);
	    if (MinHF <1.)
	      PytZ2_Xi->Fill(MinXi);
	  };
	  if (i==6 || i==7 ) { // Pompyt
	    Pom_HF->Fill(MinHF);
	    if (MinHF <1.)
	      Pom_Xi->Fill(MinXi);
	  };
	  
	  if (i==2 || i==3) { // fill the Z HF distribution
	    if  (LumCor >LowLumi_Low ){
	      Dat_HF->Fill(MinHF);
	      Lumi_HF_all->Fill(LumCor);
	      Dat_HF_Cor->Fill(MinHF,HFCor(istlumiPerBX,MinHF));

	      if (MinHF <1.) {
		Dat_Xi->Fill(MinXi);
		Lumi_Xi_all->Fill(LumCor);
	      }
	    };
	  };
	  if (i==4) {  //Fill the Ghost distribution using ee_pt10
	    if  (LumCor >LowLumi_Low && LumCor <LowLumi_High){
	      Dat_HF_LowLumi->Fill(MinHF);
	      Lumi_HF_LowLumi->Fill( LumCor);
	      if (MinHF <1.) {
		Dat_Xi_LowLumi->Fill(MinXi);
		Lumi_Xi_LowLumi->Fill(LumCor);
	      }
	    }
	    else if  (LumCor >HighLumi_Low &&  LumCor <HighLumi_High ){
	      Dat_HF_HighLumi->Fill(MinHF);
	      Lumi_HF_HighLumi->Fill(LumCor);
      	      if (MinHF <1.) {
		Dat_Xi_HighLumi->Fill(MinXi);
		Lumi_Xi_HighLumi->Fill(LumCor);
	      }
	    };
	  };
	  
	} // # of Vertexes
      
      
   }
   
  } // NDIR
  
  
  
  // Normalize to a single event
  Double_t Nevt = Dat_HF_LowLumi->GetEntries();
  Dat_HF_LowLumi->Scale(1./Nevt);
  Nevt = Dat_HF_HighLumi->GetEntries();
  Dat_HF_HighLumi->Scale(1./Nevt);
  
  Nevt = Dat_Xi_LowLumi->GetEntries();
  // Dat_Xi_LowLumi->Scale(1./Nevt);

  Nevt = Dat_Xi_HighLumi->GetEntries();
  // Dat_Xi_HighLumi->Scale(1./Nevt);
  
  
  
  //Compute the average Lumi and ghost contribution to each plot
  
  // <1.25> - <0.49> =<0.76> 
  Float_t sigma_ghost =  0.035*pow(10,-24);
  
  //HF lumi & ghosts
  Float_t Lum_HF_high = Lumi_HF_HighLumi->GetMean();
  Float_t Lum_HF_low = Lumi_HF_LowLumi->GetMean();
  Float_t Lum_HF = Lumi_HF_all->GetMean();
  Float_t Ghost_HF_high = (Lum_HF_high*pow(10,30)/11346)*sigma_ghost ;
  Float_t Ghost_HF_low = (Lum_HF_low*pow(10,30)/11346)*sigma_ghost ;
  Float_t Ghost_HF_total = (Lum_HF*pow(10,30)/11346)*sigma_ghost ;
  Float_t Ghost_HF_scale = Ghost_HF_total/( Ghost_HF_high- Ghost_HF_low);
  
  
  //Xi lumi & ghosts
  Float_t Lum_Xi_high = Lumi_Xi_HighLumi->GetMean();
  Float_t Lum_Xi_low = Lumi_Xi_LowLumi->GetMean();
  Float_t Lum_Xi = Lumi_Xi_all->GetMean();
  Float_t Ghost_Xi_high = (Lum_Xi_high*pow(10,30)/11346)*sigma_ghost ;
  Float_t Ghost_Xi_low = (Lum_Xi_low*pow(10,30)/11346)*sigma_ghost ;
  Float_t Ghost_Xi_total = (Lum_Xi*pow(10,30)/11346)*sigma_ghost ;
  Float_t Ghost_Xi_scale = Ghost_Xi_total/( Ghost_Xi_high- Ghost_Xi_low);
  
  cout << "the average luminosity:"<< endl;
  cout << "High_HF lumi interval= "<< Lum_HF_high << " and <ghost> " << Ghost_HF_high << endl;
  cout << "Low_HF lumi interval= "<<  Lum_HF_low << " and <ghost> " <<Ghost_HF_low << endl;
  cout << "Full_HF lumi interval= "<<  Lum_HF << " and <ghost> " << Ghost_HF_total << endl;
  cout << "To get one HF ghost we scale by = "<< Ghost_HF_scale << endl;
  
  cout << "High_Xi lumi interval= "<< Lum_Xi_high << " and <ghost> " << Ghost_Xi_high << endl;
  cout << "Low_Xi lumi interval= "<<  Lum_Xi_low << " and <ghost> " <<Ghost_Xi_low << endl;
  cout << "Full_Xi lumi interval= "<<  Lum_Xi << " and <ghost> " << Ghost_Xi_total << endl;
  cout << "To get to " <<  Ghost_Xi_total << "Xi ghost we scale by = "<< Ghost_Xi_scale << endl;
  
  
  
  // Here we compute the contribution of a single ghost, normalized to one
  
  Ghosts_HF->Add(Dat_HF_HighLumi, 1);
  Ghosts_HF->Add(Dat_HF_LowLumi, -1);
  Ghosts_HF->Scale(Ghost_HF_scale);
  
  Ghosts_Xi->Add(Dat_Xi_HighLumi, 1);
  Ghosts_Xi->Add(Dat_Xi_LowLumi, -1);
  Ghosts_Xi->Scale(Ghost_Xi_scale);
  
  
  //HF:
  
  //Get the entries in the Data plot
  Nevt = Dat_HF->GetEntries();
  
  // This is now the contribution of the ghosts to the total Nevt
  Ghosts_HF->Scale(Nevt);
  
  //Remove the ghosts from the Data
  
  Dat_HF_NoGhosts->Add(Dat_HF,1.);
  Dat_HF_NoGhosts->Add(Ghosts_HF,-1.);
  
  //Normalize Pythhia to the Data entries for HF 
  Float_t NPytHF = PytD6T_HF->GetEntries();
  PytD6T_HF->Scale(Nevt/NPytHF);
  PytD6T_Xi->Scale(Nevt/NPytHF);
  
  NPytHF = PytZ2_HF->GetEntries();
  PytZ2_HF->Scale(Nevt/NPytHF);
  PytZ2_Xi->Scale(Nevt/NPytHF);
  
  
  
  //Xi:
  
  //Get the entries in the Data plot
  Nevt = Dat_Xi->Integral();
  
  // This is now the contribution of the ghosts to the total Nevt
  Ghosts_Xi->Scale(Nevt);
  
  //Remove the ghosts from the Data
  
  Dat_Xi_NoGhosts->Add(Dat_Xi,1.);
  Dat_Xi_NoGhosts->Add(Ghosts_Xi,-1.);
  
  
  
  
  // Plot data and Data_noGhost
  
  MyC->cd(1);
  

  //Dat_HF_NoGhosts->SetMarkerColor(2);
  // Dat_HF_NoGhosts->SetLineColor(2);
  Dat_HF_Cor->SetLineColor(4);
  Dat_Xi->SetLineColor(4);
  Dat_Xi_NoGhosts->SetMarkerColor(2);
  Dat_Xi_NoGhosts->SetLineColor(2);
  
  
  //Color for MCs
  PytD6T_HF->SetLineColor(6);
  PytD6T_HF->SetLineStyle(6);
  PytZ2_HF->SetLineColor(8);
  PytZ2_HF->SetLineStyle(8);
  
  PytD6T_Xi->SetLineColor(6);
  PytD6T_Xi->SetLineStyle(6);
  PytZ2_Xi->SetLineColor(8);
  PytZ2_Xi->SetLineStyle(8);
  


  PytD6T_HF->Draw("Same eHIST");
  PytZ2_HF->Draw("Same eHIST");
  
 
  NHSetMarker(Dat_HF,2,20,1.);
  NHSetMarker(Dat_HF_Cor,4,20,1.);

  Dat_HF->SetStats(0);
  Dat_HF_Cor->SetStats(0);
  Dat_HF->Draw("e");
  Dat_HF_Cor->Draw("SAMEe");
  Dat_HF->SetTitle("HF Energy for 1-vxt Z->ll events");
  Dat_HF->GetXaxis()->SetTitle("Min(EE-,EE+) Energy [GeV] ");
  Dat_HF->GetYaxis()->SetTitle("Entries");
  //  PytD6T_HF->Draw("Same eHIST");
  // PytZ2_HF->Draw("Same eHIST");
  gPad->SetLogy(1);
  gPad->SetLogx(1);

  TLegend *leg = new TLegend(0.1,0.8,0.6,0.9); 
  leg->AddEntry(Dat_HF," HF  <Lumi> = 0.31 10^{30} cm^{-2}s^{-1}, <Ghost> = 0.95 ","p"); 
  leg->AddEntry(Dat_HF_Cor,"HF - Ghost Subtracted ","p"); 
  leg->Draw();
  
  MyC->cd(2);
  Dat_Xi_NoGhosts->Draw("e");
  Dat_Xi->Draw("HIST SAME");
  //      PytD6T_Xi->Draw("Same HIST");
  // PytZ2_Xi->Draw("Same HIST");
  

  //
  TFile f("Ghost_Removal_Class_files.root","recreate"); 
  for (int i=0; i<nHists; i++) {
    myHists[i]->Write();
  }
  f.Close(); 

  
  
}
