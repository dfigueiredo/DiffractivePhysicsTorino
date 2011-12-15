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


  Int_t NDIR;  /* number or Directories*/      
  string stringa;
  string HistoLabel;
  char hname[100]; 


  Float_t *VtxWeight;
  
  // Generated using FindZ2Weight() //

  Float_t Z2Weight[] = {2.23894, 2.85785, 2.15941, 1.02115, 0.428406, 
			0.162915, 0.0598376, 0.0172074, 0.00216154, 0, 
			0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0} ;

  Float_t OneWeight[] = {1.,1.,1.,1.,1.,
			 1.,1.,1.,1.,1.,
			 1.,1.,1.,1.,1.,
			 1.,1.,1.,1.,1.};

 



  NDIR   = 4;  /* number or Directories*/      
      
  fA = new TFile("files/zdiff/4_2/EGrunAZee_v2_2.root");
  fA->GetObject("tree_",tree_fA);

  fB = new TFile("files/zdiff/4_2/EGZee_v2_2.root");
  fB->GetObject("tree_",tree_fB);


  fC = new TFile("files/zdiff/4_2/PythiaZ2Zee_v2_2.root");
  TDirectory * dirC = (TDirectory*)fC->Get("files/zdiff/4_2/PythiaZ2Zee_v2_2.root:/Selection");
  dirC->GetObject("tree_",tree_fC);



  fD = new TFile("files/zdiff/4_2/PompytZee_v2_2.root");
  TDirectory * dirD = (TDirectory*)fD->Get("files/zdiff/4_2/PompytZee_v2_2.root:/Selection");
  dirD->GetObject("tree_",tree_fD);

 
  string outputfile = "ZDiffOutputfile.root";

  TFile *file1 = new TFile(outputfile.c_str(),"RECREATE");
  file1->Close();

  for (Int_t i=1 ; i<=NDIR; i++){  

    if (i==1)
      {
	fChain =tree_fA; 
	HistoLabel = "DataA";
       	VtxWeight = OneWeight; 
      }
    else if (i==2)
      {
	fChain =tree_fB; 
	HistoLabel = "DataAB";
        VtxWeight = OneWeight; 
      }
    else if (i==3)
      { 
	fChain = tree_fC; 
	HistoLabel = "PythiaZ2";
       	VtxWeight = Z2Weight; 
	//       	VtxWeight = OneWeight; 
      }

    else if (i==4)
      { 
	fChain =tree_fD; 
	HistoLabel = "Pompyt";
       	VtxWeight = OneWeight; 

      }


    hCandNoCuts = new HCand("NoCuts",HistoLabel);
    hCandNVTX1 = new HCand("NVTX1",HistoLabel);
    hCandHF0 = new HCand("HF0",HistoLabel);
    hCandHF0NVTX1 = new HCand("HF0NVTX1",HistoLabel);
    hCandHFNVTX1 = new HCand("HFNVTX1",HistoLabel);

    
    Init(fChain);

    if (fChain == 0)
      {
	cout << "Error in loading the tree: fChain = " << fChain << endl;
	return;
      }
    Long64_t nentries = fChain->GetEntriesFast();
    
    cout << "Processing " << HistoLabel.c_str() << " with " << nentries << " events." << endl;

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {

      if (jentry % 10000 == 0 && jentry != 0) cout << "jentry = " << jentry << endl;
      Long64_t ientry = LoadTree(jentry);      
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      

      float xi_min = TMath::Min(xi_PF_plus, xi_PF_minus);
     

      // This call fill all generic Histos

      Int_t GoodVtx = 0;

      //j=1 is the first PU event
      for (Int_t j = 1; j < numberOfVertexes; j++)
	{
	  if (vertexNDOF[j]>4) GoodVtx++;
	}
      
      Float_t Weight = VtxWeight[GoodVtx];
      hCandNoCuts->Fill(minEHF,xi_min,GoodVtx,PU_NumInt,Weight);



      if(numberOfVertexes == 1 || ( numberOfVertexes == 2 && vertexNDOF[1]<4)) 
	{
	  // Fill histo for NVTX1 
	  hCandNVTX1->Fill(minEHF,xi_min,GoodVtx,PU_NumInt,Weight);
	  
	  if(minEHF == 0) 
	    {
	      hCandHF0NVTX1->Fill(minEHF,xi_min,GoodVtx,PU_NumInt,Weight);
	    }
	  else
	    {
	      hCandHFNVTX1->Fill(minEHF,xi_min,GoodVtx,PU_NumInt,Weight);
	    }


	}


      if(minEHF == 0) 
	{
	  // Fill histo for minEHF=0 
	  hCandHF0->Fill(minEHF,xi_min,GoodVtx,PU_NumInt,Weight);
	}


  
    }
    

    hCandNoCuts->WriteInFile(outputfile.c_str());
    hCandNVTX1->WriteInFile(outputfile.c_str());
    hCandHF0->WriteInFile(outputfile.c_str());
    hCandHF0NVTX1->WriteInFile(outputfile.c_str());
    hCandHFNVTX1->WriteInFile(outputfile.c_str());

  } // NDIR Loop


  return;
} 
