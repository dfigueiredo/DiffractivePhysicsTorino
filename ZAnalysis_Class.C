#define ZAnalysis_Class_cxx
#include "ZAnalysis_Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2F.h>
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




void ZAnalysis_Class::Loop()
{

//   In a ROOT session, you can do:
//      Root > .L ZAnalysis_Class.C
//      Root > ZAnalysis_Class t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//


  Int_t const NDIR = 4;  /* number or Directories*/      
  string stringa;
  string HistoLabel;
  char hname[100]; 



  Float_t *VtxWeight;
  
  // Generated using FindZ2Weight() //


  //Weight conserving MC luminosity
  //  Float_t Z2Weight[] = {2.23894, 2.85785, 2.15941, 1.02115, 0.428406, 
  //		0.162915, 0.0598376, 0.0172074, 0.00216154, 0, 
  //		0, 0, 0, 0, 0, 
  //		0, 0, 0, 0, 0} ;

  //Weight normalizing Z2 to Run2010

  Float_t Z2Weight[] = {0.27356, 0.380519, 0.302952, 0.14631, 
			0.0610787, 0.0235886, 0.00850702, 0.00252781, 
			0.00032113, 0, 0, 0, 
			0, 0, 0, 0, 
			0, 0, 0,  0 };


  //{0.311428, 0.397517, 0.300365, 0.142039, 0.0595897, 
  //			0.0226608, 0.00832318, 0.00239349, 0.000300661, 0, 
  //			0, 0, 0, 0, 0, 
  //			0, 0, 0, 0, 0};
  
  Float_t C4Weight[] = {0.275802, 0.379986, 0.298846, 0.145418, 
			0.0612283, 0.0234525, 0.00860585, 0.00250125, 
			0.000321543, 0, 0, 0, 
			0, 0, 0, 0, 
			0, 0, 0,  0 };


  Float_t OneWeight[] = {1.,1.,1.,1.,1.,
			 1.,1.,1.,1.,1.,
			 1.,1.,1.,1.,1.,
			 1.,1.,1.,1.,1.};


 



  //  NDIR   = 3;  /* number or Directories*/      
      
  fA = new TFile("files/zdiff/4_2/MC_Zee_POMPYT_v2_4.root");
  TDirectory * dirA = (TDirectory*)fA->Get("files/zdiff/4_2/MC_Zee_POMPYT_v2_4.root:/Selection");
  dirA->GetObject("tree_",tree_fA); 


  
  fB = new TFile("files/zdiff/4_2/DATA_Zee_2010_v2_4.root");
  TDirectory * dirB = (TDirectory*)fB->Get("files/zdiff/4_2/DATA_Zee_2010_v2_4.root:/Selection");
    //fB->GetObject("tree_",tree_fB);
  dirB->GetObject("tree_",tree_fB);
  
  
  fC = new TFile("files/zdiff/4_2/MC_Zee_4CPY8_v2_4.root");
  TDirectory * dirC = (TDirectory*)fC->Get("files/zdiff/4_2/MC_Zee_4CPY8_v2_4.root:/Selection");
  dirC->GetObject("tree_",tree_fC);


  fD = new TFile("files/zdiff/4_2/MC_Zee_Z2PY6_v2_4.root");
  TDirectory * dirD = (TDirectory*)fD->Get("files/zdiff/4_2/MC_Zee_Z2PY6_v2_4.root:/Selection");
  dirD->GetObject("tree_",tree_fD);
  
 
  string outputfile = "ZDiffOutputfile.root";

  TFile *file1 = new TFile(outputfile.c_str(),"RECREATE");
  file1->Close();

  for (Int_t i=1 ; i<=NDIR; i++){  

    if (i==1)
      {
	fChain =tree_fA; 
	HistoLabel = "POMPYT";
       	VtxWeight = OneWeight; 
      }
    else if (i==2)
      {
	fChain =tree_fB; 
	HistoLabel = "DATA10";
        VtxWeight = OneWeight; 
      }
    else if (i==3)
      { 
	fChain = tree_fC; 
	HistoLabel = "4CPY8";
       	VtxWeight = C4Weight; 
	VtxWeight = OneWeight; 
      }
    else if (i==4)
      { 
	fChain = tree_fD; 
	HistoLabel = "Z2PY6";
       	VtxWeight = Z2Weight; 
 	VtxWeight = OneWeight; 

      }


    hCandNoCuts = new HCand("NoCuts",HistoLabel);
    hCandNVTX1 = new HCand("NVTX1",HistoLabel);
    hCandNVTX2 = new HCand("NVTX2",HistoLabel);
    hCandNVTX3 = new HCand("NVTX3",HistoLabel);
    hCandHF0 = new HCand("HF0",HistoLabel);
    hCandHF0NVTX1 = new HCand("HF0NVTX1",HistoLabel);
    hCandHFNVTX1 = new HCand("HFNVTX1",HistoLabel);
    hCandSGETA1NVTX1 = new HCand("SGETA1NVTX1",HistoLabel);

    
    Init(fChain);

    if (fChain == 0)
      {
	cout << "Error in loading the tree: fChain = " << fChain << endl;
	return;
      }
    Long64_t nentries = fChain->GetEntriesFast();
    
    cout << "Processing " << HistoLabel.c_str() << " with " << nentries << " events." << endl;

    Long64_t nbytes = 0, nb = 0;
    if (nentries > 50000) nentries = 50000;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {

      if (jentry % 10000 == 0 && jentry != 0) cout << "jentry = " << jentry << endl;
      Long64_t ientry = LoadTree(jentry);      
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      

      float xi_min = TMath::Min(xi_PF_plus, xi_PF_minus);
      float EminHF = TMath::Min(sumEHF_plus, sumEHF_minus);     
      float EB =  energyTot_PF_Barrel_minus+energyTot_PF_Barrel_plus;
      // This call fill all generic Histos

      Int_t PUGoodVtx = 0;

      //j=1 is the first PU event
      for (Int_t j = 1; j < numberOfVertexes; j++)
	{
	  if (vertexNDOF[j]>4) PUGoodVtx++;
	}
      
      Float_t Gap_Calo = TMath::Max((4.9 - etaMax_Calo), -(-4.9 - etaMin_Calo));
      Float_t Gap_PF = TMath::Max((4.9 - etaMax_PF), -(-4.9 - etaMin_PF));


      Float_t Weight = VtxWeight[PUGoodVtx];
      Int_t nVtx = vertexMolteplicity[0];
      Float_t Mx = sqrt(Mx2);
      hCandNoCuts->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
			PU_NumInt, nPart_PF, nVtx,Mx, 
			ZMass, max_eta_gap_PF, 
			etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
			EB, energyTot_PF_minus,  energyTot_PF_plus,
			EnergyInEta, EnergyInEtaHFS,EnergyInEtaHFL,
			max_second_eta_gap_PF,Gap_Calo,Gap_PF,
			Weight);

      
      if(PUGoodVtx == 0)  
	{
 	    // Fill histo for NVTX1 

	  hCandNVTX1->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
			   PU_NumInt, nPart_PF, nVtx,Mx, 
			   ZMass, max_eta_gap_PF,
			   etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
			   EB, energyTot_PF_minus,  energyTot_PF_plus,
			   EnergyInEta, EnergyInEtaHFS,EnergyInEtaHFL,
			   max_second_eta_gap_PF,Gap_Calo,Gap_PF,
			   Weight);

	  if (max_second_eta_gap_PF>1. || max_eta_gap_PF>3.) 
	    {
	      hCandSGETA1NVTX1->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
				     PU_NumInt, nPart_PF, nVtx,Mx, 
				     ZMass, max_eta_gap_PF,
				     etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
				     EB, energyTot_PF_minus,  energyTot_PF_plus,
				     EnergyInEta, EnergyInEtaHFS,EnergyInEtaHFL,
				     max_second_eta_gap_PF,Gap_Calo,Gap_PF,
				     Weight);
	    }
	  
	  if(EminHF < 4.) 
	    {
	      hCandHF0NVTX1->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
				  PU_NumInt, nPart_PF, nVtx,Mx, 
				  ZMass, max_eta_gap_PF, 				  				  etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
				  EB, energyTot_PF_minus,  energyTot_PF_plus,
				  EnergyInEta, EnergyInEtaHFS,EnergyInEtaHFL,
				  max_second_eta_gap_PF,Gap_Calo,Gap_PF,
				  Weight);
	    }
	  else
	    {
	      hCandHFNVTX1->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
				 PU_NumInt, nPart_PF, nVtx,Mx, 
				 ZMass, max_eta_gap_PF,
				 etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
				 EB, energyTot_PF_minus,  energyTot_PF_plus,
				 EnergyInEta, EnergyInEtaHFS,EnergyInEtaHFL,
				 max_second_eta_gap_PF,Gap_Calo,Gap_PF,
				 Weight);
	    }


	}
      else if(PUGoodVtx == 1) 
	{
	  // Fill histo for NVTX1 

	  hCandNVTX2->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
			   PU_NumInt, nPart_PF, nVtx,Mx, 
			   ZMass, max_eta_gap_PF,
			   etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
			   EB, energyTot_PF_minus,  energyTot_PF_plus,
			   EnergyInEta, EnergyInEtaHFS,EnergyInEtaHFL,
			   max_second_eta_gap_PF,Gap_Calo,Gap_PF,
			   Weight);

	}
      else if(PUGoodVtx == 2) 
	{
	  // Fill histo for NVTX1 

	  hCandNVTX3->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
			   PU_NumInt, nPart_PF, nVtx,Mx, 
			   ZMass, max_eta_gap_PF,
			   etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
			   EB, energyTot_PF_minus,  energyTot_PF_plus,
			   EnergyInEta, EnergyInEtaHFS,EnergyInEtaHFL,
			   max_second_eta_gap_PF,Gap_Calo,Gap_PF,
			   Weight);

	}


      if(EminHF == 0) 
	{
	  // Fill histo for EminHF=0 
	  hCandHF0->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
			PU_NumInt, nPart_PF, nVtx,Mx, 
			ZMass, max_eta_gap_PF, 
			 etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
			 EB, energyTot_PF_minus,  energyTot_PF_plus,
			 EnergyInEta, EnergyInEtaHFS,EnergyInEtaHFL,
			 max_second_eta_gap_PF,Gap_Calo,Gap_PF,
			 Weight);
	}


  
    } // Loop nentries
    

    hCandNoCuts->WriteInFile(outputfile.c_str());
    hCandNVTX1->WriteInFile(outputfile.c_str());
    hCandNVTX2->WriteInFile(outputfile.c_str());
    hCandNVTX3->WriteInFile(outputfile.c_str());
    hCandHF0->WriteInFile(outputfile.c_str());
    hCandHF0NVTX1->WriteInFile(outputfile.c_str());
    hCandHFNVTX1->WriteInFile(outputfile.c_str());
    hCandSGETA1NVTX1->WriteInFile(outputfile.c_str());


  } // NDIR Loop


  return;
} 
