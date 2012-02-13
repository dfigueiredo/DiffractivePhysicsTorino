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


  Int_t const NDIR = 1;  /* number or Directories*/      
  string stringa;
  string HistoLabel;
  char hname[100]; 
  bool MCFlag;
  bool ReducedRootpleFlag = true;
  // bool ReducedRootpleFlag = false;
  string outputfile = "ZDiffOutputfile_OnlyData2011.root";



  Float_t *VtxWeight;
  
  // Generated using FindZ2Weight() //


  //Weight conserving MC luminosity
  //  Float_t Z2Weight[] = {2.23894, 2.85785, 2.15941, 1.02115, 0.428406, 
  //		0.162915, 0.0598376, 0.0172074, 0.00216154, 0, 
  //		0, 0, 0, 0, 0, 
  //		0, 0, 0, 0, 0} ;

  //Weight normalizing Z2 to Run2010



  Float_t Z248Weight[] = {0.47964, 0.554774, 0.45353, 0.225251, 
			  0.105393, 0.0346363, 0.0107122, 0.00352455, 
			  0.00113106, 0.000254455, 6.65032e-05, 1.76427e-05, 
			  4.32696e-06, 1.34231e-06, 3.05929e-07, 8.20312e-08,
			  2.32026e-08, 5.84059e-09, 3.51463e-09,  0 }; 


  Float_t Z255Weight[] = {0.407674, 0.522026, 0.473984, 0.261989, 
			  0.13662, 0.0500967, 0.0173046, 0.00636535, 
			  0.002286, 0.000576113, 0.000168832, 5.0265e-05, 
			  1.38453e-05, 4.82703e-06, 1.23713e-06, 3.73235e-07, 
			  1.18843e-07, 3.36936e-08, 2.28477e-08,  0 }; 
  
  Float_t Z260Weight[] = {0.360702, 0.494626, 0.482156, 0.286565, 0.160864, 
			  0.0635512, 0.0236683, 0.00939366, 0.00364267, 
			  0.000991992, 0.000314359, 0.000101273, 
			  3.02027e-05, 1.14069e-05, 3.16844e-06, 1.03642e-06, 
			  3.5795e-07, 1.10118e-07, 8.10555e-08,  0 }; 
  
  Float_t Z265Weight[] = {0.324997, 0.466232, 0.482681, 0.305854, 0.183623, 
			  0.0777688, 0.0310725, 0.0132125, 0.00547094, 0.00158306, 
			  0.000529799, 0.000179012, 5.55799e-05, 2.16849e-05, 
			  6.17319e-06, 2.05303e-06, 7.15205e-07, 2.20212e-07, 
			  1.61026e-07,  0 }; 
  

  Float_t Z270Weight2010[] = {0.289794, 0.439762, 0.481183, 0.323283, 0.205893, 
			      0.0923479, 0.0389474, 0.0174082, 0.00754358, 
			      0.00227488, 0.000790641, 0.000276655, 8.87695e-05, 
			      3.57425e-05, 1.04918e-05, 3.59642e-06, 1.29123e-06, 
			      4.09812e-07, 3.08998e-07,  0 }; 
  
  
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


 

  //  NDIR   = 3;  /* number or Directories*/      


  fA = new TFile("files/zdiff/4_2/DATA_Zee_2011_v2_4.root");
  TDirectory * dirA = (TDirectory*)fA->Get("files/zdiff/4_2/DATA_Zee_2011_v2_4.root:/Selection");
  dirA->GetObject("tree_",tree_fA);

      
  fB = new TFile("files/zdiff/4_2/MC_Zee_POMPYT_v2_4.root");
  TDirectory * dirB = (TDirectory*)fB->Get("files/zdiff/4_2/MC_Zee_POMPYT_v2_4.root:/Selection");
  dirB->GetObject("tree_",tree_fB); 
  
  
  
  fC = new TFile("files/zdiff/4_2/MC_Zee_Z2PY6_v2_4.root");
  TDirectory * dirC = (TDirectory*)fC->Get("files/zdiff/4_2/MC_Zee_Z2PY6_v2_4.root:/Selection");
  dirC->GetObject("tree_",tree_fC);


  fD = new TFile("files/zdiff/4_2/MC_Zee_4CPY8_v2_4.root");
  TDirectory * dirD = (TDirectory*)fD->Get("files/zdiff/4_2/MC_Zee_4CPY8_v2_4.root:/Selection");
  dirD->GetObject("tree_",tree_fD);
  
 
  TFile *file1 = new TFile(outputfile.c_str(),"RECREATE");
  file1->Close();





  double EnThPFBar = 1.5;
  double EnThPFEnd = 3.5;
  double EnThPFFw  = 6.0;
  vector<float> EnEta (40,0.);
  vector<float> SortedEnEta (40,0.);


  cout << NDIR << endl;

  for (Int_t i=1 ; i<=NDIR; i++){  

    if (i==1)
      {
	fChain =tree_fA; 
	HistoLabel = "DATA10";
       	VtxWeight = OneWeight; 
	MCFlag = false;
      }
    else if (i==2)
      {
	fChain =tree_fB; 
	HistoLabel = "POMPYT";
        VtxWeight = OneWeight; 
	MCFlag = true;
      }
    else if (i==3)
      { 
	fChain = tree_fC; 
	HistoLabel = "Z2PY6";
       	VtxWeight = Z270Weight2010; 
       	VtxWeight = Z273Weight2011; 
	MCFlag = true;
	//	VtxWeight = OneWeight; 
      }
    else if (i==4)
      { 
	fChain = tree_fD; 
	HistoLabel = "4CPY8";
       	VtxWeight = Z270Weight2010;
       	VtxWeight = Z273Weight2011;
	MCFlag = true; 
	//	VtxWeight = OneWeight; 

      }



    
    
    

    hCandNoCuts = new HCand("NoCuts",HistoLabel);
    hCandNVTX1 = new HCand("NVTX1",HistoLabel);
    hCandNVTX2 = new HCand("NVTX2",HistoLabel);
    hCandNVTX3 = new HCand("NVTX3",HistoLabel);
    hCandHF0 = new HCand("HF0",HistoLabel);
    hCandHF0NVTX1 = new HCand("HF0NVTX1",HistoLabel);
    hCandHFNVTX1 = new HCand("HFNVTX1",HistoLabel);
    hCandSGETA1NVTX1 = new HCand("SGETA1NVTX1",HistoLabel);
    hCandGEN = new HCandGen("Gen",HistoLabel);
   




    
    Init(fChain);

    if (fChain == 0)
      {
	 cout << "Error in loading the tree: fChain = " << fChain << endl;
	return;
      }


//Create a clone of old tree in new file

    if (ReducedRootpleFlag && !MCFlag)	
      {
	cout << "Creating a new file" << endl;
	TFile *newfile = new TFile("Data2011_NVTXLT4.root","recreate");
	TTree *newtree = fChain->CloneTree(0);
	cout << "Done" << endl;
      }      


    Init(fChain);

    if (fChain == 0)
      {
	 cout << "Error in loading the tree: fChain = " << fChain << endl;
	return;
      }


    Long64_t nentries = fChain->GetEntriesFast();
    
    cout << "Processing " << HistoLabel.c_str() << " with " << nentries << " events." << endl;


    Long64_t nbytes = 0, nb = 0;
    //    if (nentries > 50000) nentries = 500;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {

      // for (Long64_t jentry=0; jentry<10;jentry++) {

      if (jentry % 1000 == 0 && jentry != 0) cout << "jentry = " << jentry << endl;
      Long64_t ientry = LoadTree(jentry);      
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // if (Cut(ientry) < 0) continue;
      

      if (ReducedRootpleFlag && !MCFlag)	
	{

	  //	  cout << jentry << endl;

	  if (numberOfVertexes <3)  
	    {
	      newfile->cd();  
	      newtree->Fill();
	      newtree->AutoSave();
	      continue;
	    }
	}
	  
      //Fill generated variables

      if (MCFlag)      hCandGEN->Fill(PU_NumInt);

      float xi_min =  TMath::Min(xi_PF_plus, xi_PF_minus);
      float EminHF = TMath::Min(sumEHF_plus, sumEHF_minus);     
      float EB =  energyTot_PF_Barrel_minus+energyTot_PF_Barrel_plus;
      Int_t PUGoodVtx = 0;


      for (Int_t j = 1; j < numberOfVertexes; j++)
	{
	  if (vertexNDOF[j]>4) PUGoodVtx++;
	}
      
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
	  else
	    {
	      if (NEmpty > NMaxEmpty) NMaxEmpty = NEmpty;
	      NEmpty = 0 ;	      
	    }
	  //	  cout << EnEta[ij] << " " << -5+0.25*ij << " Nempty = " <<NEmpty << endl;
	  
	}
      if (NEmpty > NMaxEmpty) NMaxEmpty = NEmpty;
      


      Float_t MaxEtaGap = NMaxEmpty*0.25;

      //      std::cout << "new gap = " << MaxEtaGap << " PF Gap = " << max_eta_gap_PF << " Start PF Gap = " << eta_gap_limplus <<  std::endl;

      //The weight is derived from the generated number of Vtx

      Float_t Weight = 0;
      if (PU_NumInt < 19) Weight = VtxWeight[PU_NumInt];

      Int_t nVtx = vertexMolteplicity[0];
      Float_t Mx = sqrt(Mx2);

      hCandNoCuts->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
			PU_NumInt, nPart_PF, nVtx,Mx, 
			ZMass, max_eta_gap_PF, 
			etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
			EB, energyTot_PF_minus,  energyTot_PF_plus,
			EnEta, EnergyInEtaHFS,EnergyInEtaHFL,
			max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,istlumiPerBX,
			EnergyCastorModule, sumECASTOR_minus,Weight);

      
      if(PUGoodVtx == 0)  
	{
 	    // Fill histo for NVTX1 

	  hCandNVTX1->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
			   PU_NumInt, nPart_PF, nVtx,Mx, 
			   ZMass, max_eta_gap_PF,
			   etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
			   EB, energyTot_PF_minus,  energyTot_PF_plus,
			   EnEta, EnergyInEtaHFS,EnergyInEtaHFL,
			   max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,istlumiPerBX,
			   EnergyCastorModule, sumECASTOR_minus,Weight);

	  if (max_second_eta_gap_PF>1. || max_eta_gap_PF>3.) 
	    {
	      hCandSGETA1NVTX1->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
				     PU_NumInt, nPart_PF, nVtx,Mx, 
				     ZMass, max_eta_gap_PF,
				     etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
				     EB, energyTot_PF_minus,  energyTot_PF_plus,
				     EnergyInEta, EnergyInEtaHFS,EnergyInEtaHFL,
				     max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,istlumiPerBX,
				     EnergyCastorModule, sumECASTOR_minus,Weight);
	    }
	  
	  if(EminHF < 4.) 
	    {
	      hCandHF0NVTX1->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
				  PU_NumInt, nPart_PF, nVtx,Mx, 
				  ZMass, max_eta_gap_PF,
				  etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
				  EB, energyTot_PF_minus,  energyTot_PF_plus,
				  EnergyInEta, EnergyInEtaHFS,EnergyInEtaHFL,
				  max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,istlumiPerBX,
				  EnergyCastorModule, sumECASTOR_minus,Weight);
	    }
	  else
	    {
	      hCandHFNVTX1->Fill(EminHF, sumEHF_L_plus,sumEHF_S_plus, xi_min, PUGoodVtx, 
				 PU_NumInt, nPart_PF, nVtx,Mx, 
				 ZMass, max_eta_gap_PF,
				 etaZ,etaWeightedOnEnergy_PF,nTowersHF_plus,
				 EB, energyTot_PF_minus,  energyTot_PF_plus,
				 EnergyInEta, EnergyInEtaHFS,EnergyInEtaHFL,
				 max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,istlumiPerBX,
				 EnergyCastorModule, sumECASTOR_minus,Weight);
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
			   max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,istlumiPerBX,
			   EnergyCastorModule, sumECASTOR_minus,Weight);

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
			   max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,istlumiPerBX,
			   EnergyCastorModule, sumECASTOR_minus,Weight);

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
			 max_second_eta_gap_PF,MaxEtaGap,Gap_Calo,Gap_PF,istlumiPerBX,
			 EnergyCastorModule, sumECASTOR_minus,Weight);
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

    hCandGEN->WriteInFileGEN(outputfile.c_str());


  } // NDIR Loop


  //Write out reduced rootple

  if (ReducedRootpleFlag)  
    {
      newfile->cd();
      newfile->Close();

    }


  return;
} 
