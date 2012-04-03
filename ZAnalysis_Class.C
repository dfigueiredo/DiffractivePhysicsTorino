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

  Float_t year = 2010;
  Int_t const NDIR = 3;  /* number or Directories*/      
  double EnThPFBar = 5;
  double EnThPFEnd = 5;
  double EnThPFFw  = 10.0;
  Float_t LumiLimit = .7;

  string stringa;
  string HistoLabel;
  char hname[100]; 
  Int_t MCFlag;
  Float_t *VtxWeight;
  
  // Generated using FindZ2Weight() //
  //Weight conserving MC luminosity
  //  Float_t Z2Weight[] = {2.23894, 2.85785, 2.15941, 1.02115, 0.428406, 
  //		0.162915, 0.0598376, 0.0172074, 0.00216154, 0, 
  //		0, 0, 0, 0, 0, 
  //		0, 0, 0, 0, 0} ;
  //Weight normalizing Z2 to Run2010


 
Float_t Z273Weight2010[] = {0.114206, 0.178379, 0.198474, 0.13873, 
			    0.0925946, 0.0437444, 0.0190941, 0.00902592, 
			    0.00402162, 0.00129004, 0.000493531, 0.000185931, 
			    6.31591e-05, 2.7516e-05, 8.74868e-06, 3.3339e-06, 
			    1.24274e-06, 4.41102e-07, 3.88413e-07,  0 }; 


  Float_t Z270Weight2011[] = {0.431501, 1.42236, 3.56685, 5.37323, 7.47586, 
			      7.20722, 6.34516, 6.02714, 5.41296, 3.53101, 
			      2.78457, 2.19957, 1.59709, 1.51779, 1.0744, 
			      0.929744, 0.801867, 0.670116, 1.41189,  0 };
  
  Float_t Z273Weight2011[] = {0.372563, 1.23027, 3.17373, 4.92436, 7.05479, 
			      7.00055, 6.3415, 6.19588, 5.72188, 3.83716, 
			      3.11039, 2.52551, 1.88533, 1.84288, 1.34254, 
			      1.19646, 1.0635, 0.916662, 1.9934,  0 };
  
  Float_t Z275Weight2011[] = {0.338942, 1.11737, 2.93448, 4.63984, 6.77264, 
			      6.84567, 6.31515, 6.28216, 5.90571, 4.03084, 
			      3.3251, 2.74747, 2.08742, 2.0771, 1.54091, 
			      1.39903, 1.26751, 1.11409, 2.47179,  0 }; 
  
    
  Float_t OneWeight[] = {1.,1.,1.,1.,1.,
			 1.,1.,1.,1.,1.,
			 1.,1.,1.,1.,1.,
			 1.,1.,1.,1.,1.};


 



  if (year == 2011)
    {
      fA = new TFile("files/zdiff/4_2/DATA_Zee_2011_v2_6.root");
      TDirectory * dirA = (TDirectory*)fA->Get("files/zdiff/4_2/DATA_Zee_2011_v2_6.root:/Selection");
    }
  if (year == 2010) 
    {
      fA = new TFile("files/zdiff/4_2/DATA_Zee_2010_v2_6.root");
      TDirectory * dirA = (TDirectory*)fA->Get("files/zdiff/4_2/DATA_Zee_2010_v2_6.root:/Selection");
    }

    dirA->GetObject("tree_",tree_fA);


  // fA = new TFile("files/zdiff/4_2/Data_Zee_2010_2011_NVTXLT3_v2_4.root");
  // fA->GetObject("tree_",tree_fA);


  fB = new TFile("files/zdiff/4_2/MC_Zee_Z2PY6_v2_6.root");
  TDirectory * dirB = (TDirectory*)fB->Get("files/zdiff/4_2/MC_Zee_Z2PY6_v2_6.root:/Selection");
  dirB->GetObject("tree_",tree_fB);


      
  fC = new TFile("files/zdiff/4_2/MC_Zee_POMPYT_v2_6.root");
  TDirectory * dirC = (TDirectory*)fC->Get("files/zdiff/4_2/MC_Zee_POMPYT_v2_6.root:/Selection");
  dirC->GetObject("tree_",tree_fC); 
  
  
  


  fD = new TFile("files/zdiff/4_2/MC_Zee_4CPY8_v2_4.root");
  TDirectory * dirD = (TDirectory*)fD->Get("files/zdiff/4_2/MC_Zee_4CPY8_v2_4.root:/Selection");
  dirD->GetObject("tree_",tree_fD);
  
 
  if (year == 2010) string outputfile = "ZDiffOutputfile2010HFCorEHFMinS.root";
  if (year == 2011) string outputfile = "ZDiffOutputfile2011HFCorEHFMinS.root";

  TFile *file1 = new TFile(outputfile.c_str(),"RECREATE");
  file1->Close();



  vector<float> EnEta (40,0.);
  vector<float> SortedEnEta (40,0.);


  cout << NDIR << endl;

  for (Int_t i=1 ; i<=NDIR; i++){  

    
    if (i==1)
      {
	fChain =tree_fA; 
	HistoLabel = "DATA";
       	VtxWeight = OneWeight; 
	MCFlag = 0;
      }

    else if (i==2)
      { 
	fChain = tree_fB; 
	HistoLabel = "Z2PY6";
	VtxWeight = Z273Weight2011; 
	if (year == 2010) VtxWeight = Z273Weight2010; 

	// VtxWeight = OneWeight; 
	MCFlag = 2;
      }
    else if (i==3)
      {
	fChain =tree_fC; 
	HistoLabel = "POMPYT";
        VtxWeight = OneWeight; 
	MCFlag = 3;
      }


    else if (i==4)
      { 
	fChain = tree_fD; 
	HistoLabel = "4CPY8";
	VtxWeight = Z273Weight2011; 
	if (year == 2010) VtxWeight = Z273Weight2010; 
	MCFlag = 4; 
	//	VtxWeight = OneWeight; 

      }


    

    hCandNoCuts = new HCand("NoCuts",HistoLabel);
    hCandNVTX1 = new HCand("NVTX1",HistoLabel);
    hCandNVTX1NoPUBef = new HCand("NVTX1noPUBef",HistoLabel);
    hCandNVTX1NoPUAft = new HCand("NVTX1noPUAft",HistoLabel);
    hCandHF0NVTX1 = new HCand("HF0NVTX1",HistoLabel);
    hCandGAP3NVTX1 = new HCand("GAP3NVTX1",HistoLabel);
    hCandNVTX2 = new HCand("NVTX2",HistoLabel);
    hCandNVTX3 = new HCand("NVTX3",HistoLabel);
    hCandHF0 = new HCand("HF0",HistoLabel);

    hCandGEN = new HCandGen("Gen",HistoLabel);


    //    hCandSGETA1NVTX1 = new HCand("SGETA1NVTX1",HistoLabel); 
    //    hCandHFNVTX1 = new HCand("HFNVTX1",HistoLabel);
    //    hCandNVTX3 = new HCand("NVTX3",HistoLabel);
  

    
    Init(fChain);

    if (fChain == 0)
      {
	 cout << "Error in loading the tree: fChain = " << fChain << endl;
	return;
      }


    Long64_t nentries = fChain->GetEntriesFast();
    
    cout << "Processing " << HistoLabel.c_str() << " with " << nentries << " events." << endl;


    Long64_t nbytes = 0, nb = 0;
    //     if (nentries > 50000) 
    //    nentries = 10000;

    for (Long64_t jentry=0; jentry<nentries;jentry++) {

      // for (Long64_t jentry=0; jentry<10;jentry++) {

      if (jentry % 1000 == 0 && jentry != 0) cout << "jentry = " << jentry << endl;
      Long64_t ientry = LoadTree(jentry);      
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // if (Cut(ientry) < 0) continue;


      if( MCFlag == 0 &&  istlumiPerBX*6.37 > LumiLimit) continue;

      Int_t PUNumInt[3];

      if(PU_NumInt.size() == 0) 
	{
	  PUNumInt[0]=0;
	  PUNumInt[1]=0;
	  PUNumInt[2]=0;
	}
      else 
	{
	  PUNumInt[0] = PU_NumInt[0];
	  PUNumInt[1] = PU_NumInt[1];
	  PUNumInt[2] = PU_NumInt[2];
	}
      //      cout << "pippo1 = " << pippo1 << endl;
      //     
      //cout <<PUNumInt[0]<< " , " <<PUNumInt[1] << endl;




      //Remove events with very large out-of-time pile up

      //The weight is derived from the generated number of Vtx

      Float_t Weight = 1;
      Float_t Weight0 = 0;
      Float_t WeightM1 = 0;
      Float_t WeightP1 = 0;

      //      continue;

      // 3D weighting

      if (MCFlag == 2 )
	{
	  if (PUNumInt[1] < 19) 
	    {
	      WeightM1 = VtxWeight[PUNumInt[0]];
	      Weight0 = VtxWeight[PUNumInt[1]];
	      WeightP1 = VtxWeight[PUNumInt[2]];
	      Weight = Weight0*WeightM1*WeightP1;
	      if (year == 2010) Weight = Weight*100*1.4;
	      if (year == 2011) Weight = Weight*0.03;
	      hCandGEN->Fill(PUNumInt[1],Weight);
	      if (Weight <  0.005 || Weight >100.)  continue;
	    }
	}


      float xi_min =  TMath::Min(xi_PF_plus, xi_PF_minus);
      float xi_min_calo =  TMath::Min(xi_Calo_plus, xi_Calo_minus);
      float xi_min_Z =  TMath::Min(xi_Z_plus, xi_Z_minus);
   
     
      float EB =  energyTot_PF_Barrel_minus+energyTot_PF_Barrel_plus;
      float EE =  energyTot_PF_EE_minus+energyTot_PF_EE_plus;
      Int_t PUGoodVtx = 0;




      for (Int_t j = 1; j < numberOfVertexes; j++)
	{
	  if (vertexNDOF[j]>4) PUGoodVtx++;
	}
     
      if (PUGoodVtx>3) continue;

      
  
      Float_t Gap_Calo = TMath::Max((4.9 - etaMax_Calo), -(-4.9 - etaMin_Calo));
      Float_t Gap_PF = TMath::Max((4.9 - etaMax_PF), -(-4.9 - etaMin_PF));



      // Find the largest Gap
      Int_t const ESize = EnergyInEta.size();

      for (Int_t ik = 0; ik<ESize; ik++) 
	{
	  EnEta[ik] = 0;

	  Float_t eta = -5+0.25*ik;
	  Float_t energy = EnergyInEta[ik];

	  if  ( (fabs(eta) <= 1.51 && energy > EnThPFBar)  ||
		(fabs(eta) > 1.51 && fabs(eta) <= 3.1 && energy > EnThPFEnd) ||
		(fabs(eta) > 3.1 && energy >EnThPFFw) )
	    {        	      
	      EnEta[ik] = EnergyInEta[ik];
	    }
	}

      EnEta[8] = (EnEta[7]+EnEta[9])/2;
      EnEta[31] =(EnEta[30]+EnEta[32])/2;
      
      Int_t NEmpty =0;
      Int_t NMaxEmpty =0;
      
      for (Int_t ij = 0; ij<ESize; ij++)  
	{
	  if ( EnEta[ij] <= 0. )  NEmpty ++;	    
	  else 	  NEmpty = 0 ;	      
	  if (NEmpty > NMaxEmpty) 
	    {
	      NMaxEmpty = NEmpty;
	    }
	}
      if (NEmpty > NMaxEmpty) NMaxEmpty = NEmpty;
      
      Float_t MaxEtaGap = NMaxEmpty*0.25;

      Int_t nVtx = vertexMolteplicity[0];
      Float_t Mx = sqrt(Mx2);

      
      Float_t CastorConst = 13.;
      if (MCFlag != 0) Float_t CastorConst = 1.;

      Float_t ECastor_Cor = sumECASTOR_minus/CastorConst;


      //EtaZ and MinHF : etaZ_con is positive if HF_min and Z have same-sign rapidities
      
      Float_t etaZ_con = etaZ*(sumEHF_minus - sumEHF_plus)/abs(sumEHF_plus - sumEHF_minus+.1);
      Float_t EWeighted_con = etaWeightedOnEnergy_PF*(sumEHF_minus - sumEHF_plus)/abs(sumEHF_plus - sumEHF_minus+.1);


      //======================

    float Eta = 0;
    float Cor = 1;
    float HFS[80];
    float HFL[80];
    float EFLOW_PF[40];
    float EHFSTot_minus = 0;
    float EHFLTot_minus = 0;    
    float EHFSTot_plus = 0;
    float EHFLTot_plus = 0;

    


    for (Int_t ij=0;ij<80;ij++)
      {
	Eta = -5+(ij+1)*0.125;

	if(MCFlag != 0)
	  {
	    if (Eta > 3)  Cor = (-0.3*Eta+2.35);
	    if (Eta < -3)  Cor =(0.3*Eta+2.35);
	    if (year == 2011) Cor *= 0.77;
	  }

	HFS[ij] =  Cor*EnergyInEtaHFS[ij];
	HFL[ij] =  Cor*EnergyInEtaHFL[ij];
	
	//	cout << i << " " << HFS[i] << " " << HFL[i] << " " << Cor << endl;
	if (HFS[ij] > 5) 
	  {
	    if (Eta > 3) EHFSTot_plus += HFS[ij];
	    if (Eta < -3) EHFSTot_minus +=HFS[ij];
	  }

	if (HFL[ij] > 5) 
	  {
	    if (Eta > 3) EHFLTot_plus += HFL[ij];
	    if (Eta < -3) EHFLTot_minus +=HFL[ij];
	  } 
      }

    float EHFTot_plus = EHFSTot_plus+EHFLTot_plus;
    float EHFTot_minus = EHFSTot_minus+EHFLTot_minus;
    float EminHF = TMath::Min(EHFSTot_plus, EHFSTot_minus);


    float EHFSTot = EHFSTot_plus;
    float EHFLTot = EHFLTot_plus;

    //    cout << "Summary = " << EminHF << " ," << EHFSTot << "," << EHFLTot << endl;

    //===================


      hCandNoCuts->Fill(MCFlag,EminHF, EHFSTot,EHFLTot, 
			xi_min, xi_min_calo, xi_min_Z, PUGoodVtx, 
			PUNumInt[1], nPart_PF, nVtx,Mx, 
			ZMass, max_eta_gap_PF, etaZ_con,EWeighted_con,
			nTowersHF_plus,	EB, EE,bx,  
			EnEta, HFS,HFL,
			max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,
			istlumiPerBX,
			EnergyCastorModule, ECastor_Cor,
			etaMax_Charged_PV_PF, Weight);

      

      if(PUGoodVtx == 0) 
	{
 	    // Fill histo for NVTX1 

	  hCandNVTX1->Fill(
			   MCFlag,EminHF, EHFSTot,EHFLTot, 
			   xi_min, xi_min_calo, xi_min_Z, PUGoodVtx, 
			   PUNumInt[1], nPart_PF, nVtx,Mx, 
			   ZMass, max_eta_gap_PF, 
			   etaZ_con,EWeighted_con,nTowersHF_plus,
			   EB, EE,bx,  
			   EnEta, HFS,HFL,
			   max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,
			   istlumiPerBX,
			   EnergyCastorModule, ECastor_Cor,
			   etaMax_Charged_PV_PF, Weight);


	    if(EminHF < 4.) {
	      hCandHF0NVTX1->Fill(
				  MCFlag,EminHF, EHFSTot,EHFLTot, 
				  xi_min, xi_min_calo, xi_min_Z, PUGoodVtx, 
				  PUNumInt[1], nPart_PF, nVtx,Mx, 
				  ZMass, max_eta_gap_PF, 
				  etaZ_con,EWeighted_con,nTowersHF_plus,
				  EB, EE,bx,  
				  EnEta, HFS,HFL,
				  max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,
				  istlumiPerBX,
				  EnergyCastorModule, ECastor_Cor,
				  etaMax_Charged_PV_PF, Weight);
	      
	      
	      
	    }
	    if (max_eta_gap_PF>3) {
	      hCandGAP3NVTX1->Fill(
				   MCFlag,EminHF, EHFSTot,EHFLTot, 
				   xi_min, xi_min_calo, xi_min_Z, PUGoodVtx, 
				   PUNumInt[1], nPart_PF, nVtx,Mx, 
				   ZMass, max_eta_gap_PF, 
				   etaZ_con,EWeighted_con,nTowersHF_plus,
				   EB, EE,bx,  
				   EnEta, HFS,HFL,
				   max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,
				   istlumiPerBX,
				   EnergyCastorModule, ECastor_Cor,
				   etaMax_Charged_PV_PF, Weight);
	      
	      

	    }	 
	    // List from FindNoPUBx() //
	    
	    if (year == 2011 && MCFlag == 0)
	      {
		if (bx == 45 || bx == 181 || bx == 263 || bx == 342 || bx == 348 || 
		    bx == 380 || bx == 447 || bx == 528 || bx == 607 || bx == 615 || bx == 686 || 
		    bx == 694 || bx == 813 || bx == 892 || bx == 896 || bx == 999 || bx == 1078 || 
		    bx == 1157 || bx == 1236 || bx == 1336 || bx == 1342 || bx == 1422 || bx == 1501 || 
		    bx == 1580 || bx == 1634 || bx == 1707 || bx == 1786 || bx == 1893 || bx == 1972 || 
		    bx == 2051 || bx == 2130 || bx == 2138 || bx == 2166 || bx == 2316 || bx == 2395 || 
		    bx == 2474 || bx == 2589 || bx == 2668 || bx == 2775 || bx == 2854 || bx == 2933 || 
		    bx == 2937 || bx == 2977 || bx == 3012 || bx == 3080 || bx == 3119 || bx == 3198 || 
		    bx == 3202 || bx == 3277)
		  {
		    hCandNVTX1NoPUBef->Fill(
					    MCFlag,EminHF, EHFSTot,EHFLTot, 
					    xi_min, xi_min_calo, xi_min_Z, PUGoodVtx, 
					    PUNumInt[1], nPart_PF, nVtx,Mx, 
					    ZMass, max_eta_gap_PF, 
					    etaZ_con,EWeighted_con,nTowersHF_plus,
					    EB, EE,bx,  
					    EnEta, HFS,HFL,
					    max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,
					    istlumiPerBX,
					    EnergyCastorModule, ECastor_Cor,
					    etaMax_Charged_PV_PF, Weight);

		  }	 
		
		
		if ( bx == 61 || bx == 175 || bx == 254 || bx == 333 || bx == 344 || 
		     bx == 376 || bx == 392 || bx == 412 || bx == 519 || bx == 598 || 
		     bx == 611 || bx == 677 || bx == 690 || bx == 756 || bx == 883 || 
		     bx == 892 || bx == 962 || bx == 1069 || bx == 1148 || bx == 1227 || 
		     bx == 1306 || bx == 1336 || bx == 1413 || bx == 1492 || bx == 1571 || 
		     bx == 1630 || bx == 1650 || bx == 1765 || bx == 1844 || bx == 1951 || 
		     bx == 2030 || bx == 2109 || bx == 2134 || bx == 2162 || bx == 2180 || 
		     bx == 2295 || bx == 2374 || bx == 2453 || bx == 2532 || bx == 2659 || 
		     bx == 2738 || bx == 2845 || bx == 2924 || bx == 2933 || bx == 2971 || 
		     bx == 3003 || bx == 3076 || bx == 3082 || bx == 3189 || bx == 3198 || bx == 3268
		     )	{
		  hCandNVTX1NoPUAft->Fill(
					  MCFlag,EminHF, EHFSTot,EHFLTot, 
					  xi_min, xi_min_calo, xi_min_Z, PUGoodVtx, 
					  PUNumInt[1], nPart_PF, nVtx,Mx, 
					  ZMass, max_eta_gap_PF, 
					  etaZ_con,EWeighted_con,nTowersHF_plus,
					  EB, EE,bx,  
					  EnEta, HFS,HFL,
					  max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,
					  istlumiPerBX,
					  EnergyCastorModule, ECastor_Cor,
					  etaMax_Charged_PV_PF, Weight);
		  
		}	 
	      }
	    
	    
	    
	}
      
      else if(PUGoodVtx == 1) 	{
	  // Fill histo for NVTX2 

	hCandNVTX2->Fill(
			 MCFlag,EminHF, EHFSTot,EHFLTot, 
			 xi_min, xi_min_calo, xi_min_Z, PUGoodVtx, 
			 PUNumInt[1], nPart_PF, nVtx,Mx, 
			 ZMass, max_eta_gap_PF, 
			 etaZ_con,EWeighted_con,nTowersHF_plus,
			 EB, EE,bx,  
			 EnEta, HFS,HFL,
			 max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,
			 istlumiPerBX,
			 EnergyCastorModule, ECastor_Cor,
			 etaMax_Charged_PV_PF, Weight);
	
	}

      else if(PUGoodVtx == 2) 	{
	  // Fill histo for NVTX3 

	hCandNVTX3->Fill(
			 MCFlag,EminHF, EHFSTot,EHFLTot, 
			 xi_min, xi_min_calo, xi_min_Z, PUGoodVtx, 
			 PUNumInt[1], nPart_PF, nVtx,Mx, 
			 ZMass, max_eta_gap_PF, 
			 etaZ_con,EWeighted_con,nTowersHF_plus,
			 EB, EE,bx,  
			 EnEta, HFS,HFL,
			 max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,
			 istlumiPerBX,
			 EnergyCastorModule, ECastor_Cor,
			 etaMax_Charged_PV_PF, Weight);
	
	}



      
      //      if(xi_min_calo < 0.02 && PUGoodVtx ==0 && EminHF < 4.) 	{
      if(EminHF < 4.) 	{
	// Fill histo for EminHF=0 
	hCandHF0->Fill(
		       MCFlag,EminHF, EHFSTot,EHFLTot, 
		       xi_min, xi_min_calo, xi_min_Z, PUGoodVtx, 
		       PUNumInt[1], nPart_PF, nVtx,Mx, 
		       ZMass, max_eta_gap_PF, 
		       etaZ_con,EWeighted_con,nTowersHF_plus,
		       EB, EE,bx,  
		       EnEta, HFS,HFL,
		       max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,
		       istlumiPerBX,
		       EnergyCastorModule, ECastor_Cor,
		       etaMax_Charged_PV_PF, Weight);		       
      }
      
      
      
    } // Loop nentries
    
    
    
    hCandNoCuts->WriteInFile(outputfile.c_str());
    hCandNVTX1->WriteInFile(outputfile.c_str());
    hCandNVTX1NoPUBef->WriteInFile(outputfile.c_str());
    hCandNVTX1NoPUAft->WriteInFile(outputfile.c_str());
    hCandHF0NVTX1->WriteInFile(outputfile.c_str());
    hCandGAP3NVTX1->WriteInFile(outputfile.c_str());
    hCandNVTX2->WriteInFile(outputfile.c_str());
    hCandNVTX3->WriteInFile(outputfile.c_str());
    hCandHF0->WriteInFile(outputfile.c_str());
    hCandGEN->WriteInFileGEN(outputfile.c_str());



    //    hCandSGETA1NVTX1->WriteInFile(outputfile.c_str());
    // hCandHFNVTX1->WriteInFile(outputfile.c_str());
    //    hCandNVTX3->WriteInFile(outputfile.c_str());
 


  } // NDIR Loop


  return;
} 
