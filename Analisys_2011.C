#define Analisys_2011_cxx
#include "Analisys_2011.h"
#include <TH2.h>
#include <TH2F.h>
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

// lumiRunBin

const Int_t MultiBin = 10;

TH1F *Dat_all_Lumi;
TH1F *NTriggers;
TH1I *Runs;
TH1F *RunsLumi;
TH1F *BxLumi;
TH1F *Vertex1MultVtxQual;
TH1F *Vertex0MultVtxQual;
TH1F *Vertex1Mult;
TH1F *Vertex1MultGT200;
TH1F *Vertex0Mult;
TH1F *CorForLumi[RunBin];
TH1F *RunTriggers[RunBin];
TH1F *RunLumi[RunBin];
TH1F *LumiBin[LumBin];
TH1F *VxtLumiBin[LumBin];
TH1F *Multi[MultiBin];
TH1F *PUMulti[NumPU];
TH1F *Vz;
TH1F *VzNDOF[MultiBin];
TH1F *HNDOF;
TH1F *VtxQual;
TH1F *Vtx1_HF0;
TFile *ffc;
TProfile *LumiCorProf;
TH2F *LumiCor2D;
TH1F *ZDiff_2vtx_Alltrack;
TH1F *ZDiff_2vtx_2track;


TFile *fA;
TTree *tree_fA;
TFile *fB;
TTree *tree_fB;
TFile *fC;
TTree *tree_fC;
TFile *fD;
TTree *tree_fD;
TFile *fE;
TTree *tree_fE;

TH1F *MeasPt_Mult6;
TH1F *MeasPt_Mult9;

Int_t NDIR;  /* number or Directories*/      

string stringa;


Bool_t down = false;
Float_t  ZVtx[20]= {0};
Float_t  XVtx[20]= {0};
Float_t  YVtx[20]= {0};
Int_t  MultVtx[20]= {0};
Int_t  Nindex[20]= {0};
Int_t GoodTrk = 0;



void Analisys_2011::Loop()
{

  char hname[100]; 
  char htitle[100]; 
  TRandom r; 
  Float_t xl;
  Float_t xu;



  // read the parameters and Outputfilename

  readfile();

  // To restrict the vertex Z range  //

  //   Int_t Z_limit = 11; // Not in use 

   // Limit for Vertex Quality cut  //

  Float_t VtxQualityLimit = 0.;// 0. = not in use
  
  
  Int_t RunForLumi[RunBin] = 
    {
      142130,142422,142528,142928,142933,142971,143007,143181,143328,143657,
      143727,143827,143833,143835,143953,143954,143962,144011,144086,144089,
      144112,146804,146807,146944,147043,147048,147114,147115,147196,147217,
      147219,147222,147284,147390,147450,147451,147754,147755,147757,148002,
      148029,148031,148032,148058,148822,148862,148864,148952,149011,149058,
      149063,149181,149182,149291,149294,149442
    };
  

  const int VxtBin=20;

  Runs = new TH1I("Runs","Runs",10000, 139500.5,149500.5);
  RunsLumi = new TH1F("RunsLumi","RunsLumi",10000, 139500.5,149500.5);

  Dat_all_Lumi = new TH1F("Dat_all_Lumi", "Dat_all_Lumi", LumBin, LowLim, UpLim);
  Dat_all_Lumi->Sumw2();

  LumiCorProf =  new TProfile("Luminosity Correction", "Luminosity Correction", LumBin, LowLim, UpLim,0.,2.,"s");
  LumiCor2D =  new TH2F("Luminosity_Correction_2D", "Luminosity_Correction_2D", 100, LowLim, UpLim,100,0.,2.);


  NTriggers = new TH1F("NTriggers", "NTriggers", 3501.,-0.5 , 3500.5);
  NTriggers->Sumw2();
  BxLumi = NH1clone("BxLumi","BxLumi",NTriggers);

  Vz = new TH1F("Vz","Vz",80,-20.,20);
  HNDOF = new TH1F("HNDOF","HNDOF",400,0.25,200.25);

  ZDiff_2vtx_Alltrack = new TH1F("ZDiff_2vtx_Alltrack","ZDiff_2vtx_Alltrack",500,0.,50.);
  ZDiff_2vtx_2track = NH1clone("ZDiff_2vtx_2track","ZDiff_2vtx_2track" ,ZDiff_2vtx_Alltrack);


  TH1F *Vertex1Mult = new TH1F("Vertex1Mult","Vertex1Mult",200,0.5,200.5);
  TH1F *Vertex1MultGT200 = new TH1F("Vertex1MultGT200","Vertex1MultGT200",200,0.5,200.5);
  TH1F *Vertex0Mult = new TH1F("Vertex0Mult","Vertex0Mult",200,0.5,200.5);
  TH1F *Vertex1MultVtxQual = new TH1F("Vertex1MultVtxQual","Vertex1MultVtxQual",200,0.5,200.5);
  TH1F *Vertex0MultVtxQual = new TH1F("Vertex0MultVtxQual","Vertex0MultVtxQual",200,0.5,200.5);


  //SystCheck
  Float_t DeltaLumi = 1.;
  if (SystCheck == 2) DeltaLumi= 1.04;
  if (SystCheck == 3) DeltaLumi= 0.96;	
  if (SystCheck == 21) DeltaLumi= 1.08;
  if (SystCheck == 31) DeltaLumi= 0.92;	



  // Files for Multiplicity - Vertex Studies //

  //  sprintf(hname,"SumMultVertex_0_25");
  sprintf(hname,"BlindSpotMult_0_25");

  if (DAV)  Multi[0] = new TH1F(hname,hname,50,0.,1.);
  else  Multi[0] = new TH1F(hname,hname,60,0.,3.);
  
  VzNDOF[0] = new TH1F("VzNDOF0","VzNDOF0",20,-20.,20);
  VtxQual = new TH1F("VtxQual","VtxQual", 105,0.,1.05);

  for (Int_t M=1;M<MultiBin;M++){
    sprintf(hname,"BlindSpotMult_%i_%i",25*M,25*(M+1));
    Multi[M] =  NH1clone(hname,hname,Multi[0]);
    sprintf(hname,"VzNDOF%i",M);
    VzNDOF[M] =  NH1clone(hname,hname,VzNDOF[0]);
  }

  for (Int_t M=0;M<NumPU;M++){
    sprintf(hname,"Pile-up = %i  Track Multiplicity ",M);
    PUMulti[M] = NH1clone(hname,hname,Vertex1Mult);

  }

  stringa = "MeasPt_Mult6";
  sprintf(hname,stringa.c_str());
  MeasPt_Mult6 = new TH1F(hname,hname,60,0.,6.);  
  MeasPt_Mult6->Sumw2();  
      
  stringa = "MeasPt_Mult9";
  sprintf(hname,stringa.c_str());
  MeasPt_Mult9 = NH1clone(hname,hname, MeasPt_Mult6);  
  

  for (Int_t M=0;M<RunBin;M++)
    {
      sprintf(hname,"RunTriggers%i",M);
      sprintf(htitle,"%i",RunForLumi[M]);
      RunTriggers[M] = NH1clone(hname,htitle,NTriggers);
      sprintf(hname,"RunLumi%i",M);
      RunLumi[M] = NH1clone(hname,htitle,NTriggers);
    }
  
  //--------------------------// 
  
  if (LumiCorF || RunListF)
    {
      ffc= TFile::Open(LumiCorFile); 
      if (ffc==0)
	{
	  cout << "Problem with LumiCorFile" << LumiCorFile << endl;
	  return;
	}
      
      
      for (Int_t M=0;M<RunBin;M++)
	{
	  	  
	  // Files to correct for lumi
	  
	  sprintf(hname,"DivideLumiCor%i",RunForLumi[M]);
	  CorForLumi[M]= (TH1F*)ffc->Get(hname);
	  if (CorForLumi[M]==0)
	    {
	      cout << "Problem in reading Histo " << hname << endl;
	      return;
	    }
	}
      
    }
    //
      
      //  LumiBin[0] = new TH1F("Lumi", "Lumi", 70, 0., UpLim);
      
  // Histos to measure the average Luminosity per Bin
  LumiBinWidth = (UpLim-LowLim)/LumBin;
 
  for (Int_t i=0;i<LumBin;i++)
    {

      Float_t xl=LowLim+LumiBinWidth*(i);
      Float_t xu=LowLim+LumiBinWidth*(i+1);
      sprintf(hname,"LumiBin%i",i+1);
      sprintf(htitle,"Lumi_Int_%4.2f_%4.2f",xl,xu);
      LumiBin[i] = new TH1F(hname, htitle, 100, xl, xu);
      sprintf(htitle,"Vtx_Lumi_Int_%4.2f_%4.2f",xl,xu);
      VxtLumiBin[i] = new TH1F(htitle, htitle, 18,0 ,18);
      
    }
  
  
  // Histos to measure the number of Vertexes 
  
  TH1F * Vxt_Lumi[VxtBin];
  
  for (Int_t i=0;i<VxtBin;i++)
    {
      sprintf(hname,"Vxt_Lumi%i",i);
      Vxt_Lumi[i] =  NH1clone(hname,hname,Dat_all_Lumi);
    }
  sprintf(hname,"Vtx1_HF0");
  Vtx1_HF0 =  NH1clone(hname,hname,Dat_all_Lumi);
  
  if (eeF == 1)
    {
      NDIR   = 2;  /* number or Directories*/      
      
      if (DAV==1) // ee + DAV
	{
	  fA = new TFile("files/SkimA_ee_DL10_DAV_v1_7.root");
	  tree_fA= (TTree*)gDirectory->Get("tree_");
	  
	  fB = new TFile("files/SkimB_ee_DL10_DAV_v1_7.root");
	  tree_fB= (TTree*)gDirectory->Get("tree_");	  	  
	}
      else // ee + STD
	{	 
	  fA = new TFile("files/ZetaSkimA_ee_DL10_v1_6.root");
	  tree_fA= (TTree*)gDirectory->Get("tree_");
	  
	  fB = new TFile("files/ZetaSkimB_ee_DL10_v1_6.root");
	  tree_fB= (TTree*)gDirectory->Get("tree_");	  	  
	}
    }
  else if (eeF == 2)  // mm files
    {
      NDIR   = 3;  /* number or Directories*/   
      
      if (DAV == 1) // mm + DAV
	{
	  fA = new TFile("files/SkimA_mm_DAV_v1_8.root");
	  tree_fA= (TTree*)gDirectory->Get("tree_");
	  
	  fB = new TFile("files/SkimB1_mm_DAV_v1_8.root");
	  tree_fB= (TTree*)gDirectory->Get("tree_");
	  
	  fC = new TFile("files/SkimB2_mm_DAV_v1_8.root");
	  tree_fC= (TTree*)gDirectory->Get("tree_");
	}
      else 
	{
	  cout << "Sorry, no mumu files without DAV" << endl;
	  return;
	}
      
    }
  else if (eeF == 3 )  // mm files
    {
      NDIR   = 5;  /* number or Directories*/   
      
      if (DAV == 1) // mm + DAV
	{
	  fA = new TFile("files/SkimA_sm_DAV_v1_11.root");
	  tree_fA= (TTree*)gDirectory->Get("tree_");

	  fB = new TFile("files/SkimB_sm_DAV_v1_11.root");
	  tree_fB= (TTree*)gDirectory->Get("tree_");

	  fC = new TFile("files/SkimA_ee_DAV_v1_11.root");
	  tree_fC= (TTree*)gDirectory->Get("tree_");

	  fD = new TFile("files/SkimB1_ee_DAV_v1_11.root");
	  tree_fD= (TTree*)gDirectory->Get("tree_");

	  fE = new TFile("files/SkimB2_ee_DAV_v1_11.root");
	  tree_fE= (TTree*)gDirectory->Get("tree_");
	  
	}
      else 
	{
	  cout << "Sorry, no ee-mumu files without DAV" << endl;
	  return;
	}
    }
  else if (eeF == 4 )  // mm files
    {
      NDIR   = 2;  /* number or Directories*/   
      
      if (DAV == 1) // mm + DAV
	{
	  fA = new TFile("files/SkimA_sm_DAV_v1_11.root");
	  tree_fA= (TTree*)gDirectory->Get("tree_");

	  fB = new TFile("files/SkimB_sm_DAV_v1_11.root");
	  tree_fB= (TTree*)gDirectory->Get("tree_");
	  	  
	}
      else 
	{
	  cout << "Sorry, no Single mu files without DAV" << endl;
	  return;
	}
      
    }  // mm+ee files
    
  else if (eeF == 5 )  // mm files
    {
      NDIR   = 3;  /* number or Directories*/   
      
      if (DAV == 1) // mm + DAV
	{
	  fA = new TFile("files/SkimA_ee_DAV_v1_11.root");
	  tree_fA= (TTree*)gDirectory->Get("tree_");

	  fB = new TFile("files/SkimB1_ee_DAV_v1_11.root");
	  tree_fB= (TTree*)gDirectory->Get("tree_");

	  fC = new TFile("files/SkimB2_ee_DAV_v1_11.root");
	  tree_fC= (TTree*)gDirectory->Get("tree_");
	}
      else 
	{
	  cout << "Sorry, no Single mu files without DAV" << endl;
	  return;
	}
    }


  else if (eeF == 6 )  // sm files
    {
      NDIR   = 2;  /* number or Directories*/   
      
      if (DAV == 1) // sm + DAV
	{
	  fA = new TFile("files/SkimA_sm_DAV_v1_16.root");
	  tree_fA= (TTree*)gDirectory->Get("tree_");

	  fB = new TFile("files/SkimB_sm_DAV_v1_16.root");
	  tree_fB= (TTree*)gDirectory->Get("tree_");
	  	  
	}
      else 
	{
	  cout << "Sorry, no Single mu files without DAV" << endl;
	  return;
	}
      
    }  // mm+ee files
    
  else if (eeF == 7 )  // ee files
    {
      NDIR   = 3;  /* number or Directories*/   
      
      if (DAV == 1) // ee + DAV
	{
	  fA = new TFile("files/SkimA_ee_DAV_v1_16.root");
	  tree_fA= (TTree*)gDirectory->Get("tree_");

	  fB = new TFile("files/SkimB1_ee_DAV_v1_16.root");
	  tree_fB= (TTree*)gDirectory->Get("tree_");

	  fC = new TFile("files/SkimB2_ee_DAV_v1_16.root");
	  tree_fC= (TTree*)gDirectory->Get("tree_");
	}
      else 
	{
	  cout << "Sorry, no Single mu files without DAV" << endl;
	  return;
	}
    }
  else if (eeF == 8 )  // 2011 files
    {
      NDIR   = 2;  /* number or Directories*/   
      
      fA = new TFile("files/2011.root");
      tree_fA= (TTree*)gDirectory->Get("tree_");

      fB = new TFile("files/2011_NGT.root");
      tree_fB= (TTree*)gDirectory->Get("tree_");


    }  // 2011 files



  for (Int_t i=1 ; i<=NDIR; i++){
  
      // Loop and RunA
      
      if (i==1){
	fChain =tree_fA;  /* mm Loop RunA */ 
      }
      else if (i==2){ 
	fChain =tree_fB;  /* mm Loop RunB */ 
      }
      else if (i==3){ 
	fChain =tree_fC;  /* mm Loop RunB2 */ 
      }
      else if (i==4){ 
	fChain =tree_fD;  /* ee Loop RunA */ 
      }
      else if (i==5){ 
	fChain =tree_fE;  /* ee Loop RunB */ 
      }


      Int_t RunC = 0;
      
    Init(fChain);
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    
    cout << "file # "<< i << " has " << nentries << " entries" << endl;

    cout << "MinDist = " << MinDist << " MinSig = " << MinSig << endl; 
    Int_t NewRun = 0;
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) 
      //        for (Long64_t jentry=0; jentry<10000;jentry++) 
      {
	//            for (Long64_t jentry=396700; jentry<nentries;jentry++) 
	//  for (Long64_t jentry=0; jentry<10;jentry++) 
	
	
	Long64_t ientry = LoadTree(jentry);
	if (ientry < 0) break;
	nb = fChain->GetEntry(jentry);   nbytes += nb;

	Float_t LumiCor= istlumiPerBX*6.37;
	if(LumiCor <0.02) continue;  // some events have 0 Luminosity...

	
	if (jentry> 100000 && jentry % 100000 == 0) cout << "jentry = " << jentry << endl;
	
	// x2 = r.Gaus(1.,0.1); //Random number of mean 1 and sigma = 0.1
	// Float_t LumiCor= istlumiPerBX*6.37*x2;
	// Float_t LumiCor= istlumiPerBX*6.37*1.05;
	
	//	Float_t DivideLumiCor = 0.;



	// Systematic check on the Lumi value

	if(LumiCor <0.02) continue;  // Safety check
	LumiCor= LumiCor*DeltaLumi;
	
	
	Int_t NHPU=0; //index of the highest PU
	const Int_t Max_Num_Vxt = numberOfVertexes;
	
	
	bool AdditReq = true;
	
	if (SystCheck == 6)
	  {
	    AdditReq = false;
	    if ((energyTot_PF_Barrel_minus+energyTot_PF_Barrel_plus)>25) AdditReq=true;
	  }
	
	if (SystCheck == 7)
	  {
	    AdditReq = false;
	    if ((energyTot_PF_Barrel_minus+energyTot_PF_Barrel_plus)>15) AdditReq=true;
	  }
	
	if (eeF == 3)
	  {
	    AdditReq = false;
	    // cout << jentry << endl;
	    if (i >2 )
	      {
		if (electronEnergy[0]>11. && electronEnergy[1]> 11.) AdditReq = true;
	      } 
	    if ( i <=2 )
	      {
	        if (muEnergy[0]>20 ) AdditReq = true;
	      }
	  }
	
	
	
	
	if (eeF == 4)
	  {
	    AdditReq = false;
	    if (muEnergy[0]>20) AdditReq = true;
	  }
	
	
	if (eeF == 5)
	  {
	    AdditReq = false;
	    // cout << jentry << endl;
	    
	    if (electronEnergy[0]>11. && electronEnergy[1]> 11) AdditReq = true;
	    if (SystCheck == 12)
	      { 
		AdditReq = false;
		if (electronEnergy[0]>15. && electronEnergy[1]> 15) AdditReq = true;
	      }
	  }
	
	
	if(LumiCor>0.01 && LumiCor<UpLim && AdditReq )
	  {
	    
	    
	    if (NewRun != RunNumber) 
	      {
		//		cout << RunNumber << endl;
		NewRun = RunNumber;
		RunC = 0;
	      }
	    
	    // cout << "Final loop: runnumber = " << RunNumber << " and   Lumicor " << LumiCor << endl;
	    
	    Float_t NvtxNDOF = 0.;
	    Int_t Num_Vxt = 0;
	    for (Int_t k = 0; k < Max_Num_Vxt ;k++)// here we count the real number of vertices //
	      { 
		ZVtx[k]=0;
		XVtx[k]=0;
		YVtx[k]=0;
		MultVtx[k]=0;
		
		//  NHPU=0; //index of the highest PU
		NvtxNDOF = vertexNDOF[k];
		
		Float_t VtxQuality =  ((vertexNDOF[k]+3)/2)/vertexMolteplicity[k];
		HNDOF->Fill(vertexNDOF[k]);
		VtxQual->Fill(VtxQuality);
		if (NvtxNDOF==MultiBin) VzNDOF[MultiBin]->Fill(V_z[k]);
		
		bool VtxNTrack = false;
		bool VtxTransPos = false;

		 //bool VtxNTrack = true;
		 // bool VtxTransPos = true;

		if (SystCheck == 40) VtxNTrack = true;	 

		if (vertexMolteplicity[k] >= MinNtracksLowpT) VtxNTrack = true;



		// Here we select vertices on the beam line, the others are either fakes or secondary
		
		

		if (fabs(sqrt(pow(V_x[k],2)+pow(V_y[k],2))-0.094)<MinSig)   VtxTransPos = true;

	       	//if (fabs(V_x[k]-0.0919)<LumiBinWidth && fabs(V_y[k]-0.0189)<0.1)   VtxTransPos = true;

		
		if (NvtxNDOF>=SelNDOF && VtxTransPos && VtxNTrack)
		  {
		    
		    NHPU=k;
		    //		  if ( fabs(V_z[k])>Z_limit ) goto loop;
		    ZVtx[Num_Vxt] = V_z[k];
		    XVtx[Num_Vxt] = V_x[k];
		    YVtx[Num_Vxt] = V_y[k];
		    
		    MultVtx[Num_Vxt] = vertexMolteplicity[k];
		    Num_Vxt++ ;

		  }
	      }   //End loop on vertices


	    if (Num_Vxt==2   &&   Max_Num_Vxt == 2) // There are only two good vertices
	      {
		if (MultVtx[1] == 2) ZDiff_2vtx_2track->Fill(fabs(ZVtx[0]-ZVtx[1]));
		else ZDiff_2vtx_Alltrack->Fill(fabs(ZVtx[0]-ZVtx[1]));


		// unbiased pile-up distributions only if there is a single PU  vertex  
		
		Vertex1Mult->Fill(vertexMolteplicity[1]);
		
		//nicolo
		Int_t NumPtGT200 = 0;
		for (Int_t t = 0; t < vertexMolteplicity[1]; t++)
		  {
		    if (tracksPT[1][t]>0.2) NumPtGT200++  ;
		  }
		
		Vertex1MultGT200->Fill(NumPtGT200);

		Float_t VtxQuality =  ((vertexNDOF[1]+3)/2)/MultVtx[1];
		if (VtxQuality>VtxQualityLimit) Vertex1MultVtxQual->Fill(MultVtx[1]);		

	      }
	    	      
	    // Fill the 1 Vtx with HF=0 histo // Fill with everything that is not included in the Vtx selection
	    if ( (Num_Vxt==1  && TMath::Min(sumEHF_PF_plus,sumEHF_PF_minus) ==0))
	      {
		Vtx1_HF0->Fill(LumiCor);
	      }
	    


	    if (Num_Vxt>0 ) { // The multiplicity of Vtx=0 is independent of the other vertexes. 
	      Vertex0Mult->Fill(MultVtx[0]);
	      Float_t VtxQuality =  ((vertexNDOF[0]+3)/2)/MultVtx[0];

	      if (VtxQuality>VtxQualityLimit) Vertex0MultVtxQual->Fill(MultVtx[0]);
	    }
	    
	    


	      
	    
	    // Fill the PU multiplicity Histo for the Highest PU (index = NHPU)
	    
	    if (Num_Vxt>1 && NHPU < NumPU) PUMulti[Num_Vxt-1]->Fill(MultVtx[NHPU]);
	    



	    
	    //here we fill the Multiplicity Pt  files for blind spot /MC  studies //
	    
	    
	    for (Int_t Nv = 0; Nv < Num_Vxt ; Nv++)
	      {
		if (MultVtx[Nv]>5 )
		  {
		    for (Int_t Nv2 = Nv+1; Nv2<Num_Vxt; Nv2++)
		      {
			if (MultVtx[Nv2]>5) // Multiplicity cut removes Fakes
			  {
			    
			    if (eeF == 2) //Only mumu data have the pt values.
			      {
				
				if (MultVtx[Nv2]==7) // fill pt distributions for two multiplicities
				  {
				    for (Int_t yy = 0;yy<6;yy++) MeasPt_Mult6->Fill(tracksPT[Nv2][yy]);
				  }
				if (MultVtx[Nv2]==10)
				  {
				    for (Int_t yy = 0;yy<9;yy++) MeasPt_Mult9->Fill(tracksPT[Nv2][yy]);
				  }
			      } // !eeF
			    
			    Float_t NMult = MultVtx[Nv]+MultVtx[Nv2];
			    
			    for (Int_t NM=0;NM<MultiBin;NM++)
			      {
				if (NMult > NM*25 && NMult<(NM+1)*25)
				  {
				    if (NMult<175)  Multi[NM]->Fill(fabs(V_z[Nv]-V_z[Nv2]));
				    else  Multi[7]->Fill(fabs(V_z[Nv]-V_z[Nv2]));
				    break;
				  }
			      }
			  } // NDOF[Nv2]>=SelNDOF
		      } //loop Nv2
		  }  // NDOF [Nv]>=SelNDOF
	      } //loop Nv

	    // Impose a minimum distance between vtx, done in NCutil.C


	    Int_t GoodVtx = 1;  // There is always one vertex
	    TMath::Sort(Num_Vxt, ZVtx, Nindex, down);
	    for (Int_t kl = 1;kl<Num_Vxt;kl++)
	      {
		Int_t ip = Nindex[kl];
		Int_t ipm1 = Nindex[kl-1];
		Float_t Dist = fabs(ZVtx[ip]-ZVtx[ipm1]);
		if (Dist> MinDist) GoodVtx++ ;
	      }

	    Num_Vxt = GoodVtx; 

	    //	cout << "Number of Vxt " << Max_Num_Vxt << " while Vxt with NDOF>=SelNDOF = "
	    //     <<Num_Vxt << endl;
	    
	    for (Int_t N=0;N<LumBin;N++){
	      xl=LowLim+LumiBinWidth*(N);
	      xu=LowLim+LumiBinWidth*(N+1);
	      if (LumiCor>= xl && LumiCor < xu){
		LumiBin[N]->Fill(LumiCor);
		VxtLumiBin[N]->Fill(Num_Vxt+0.1-1); // remove the Z vxt 
		
		break;
	      }
	    }
	    

	    
	    
	    // ----------------------------------------//
	    Dat_all_Lumi->Fill(LumiCor);
	    Vxt_Lumi[Num_Vxt]->Fill(LumiCor);
	    NTriggers->Fill(1.*bx);
	    BxLumi->Fill(bx,LumiCor);
	    Runs->Fill(RunNumber);
	    RunsLumi->Fill(RunNumber,LumiCor);
	    if (vertexNDOF[0]>=SelNDOF){
	      Vz->Fill(V_z[0]);
	      VzNDOF[0]->Fill(V_z[0],vertexNDOF[0]);
	    }
	    
	    //Files for Luminosity Correction  //
	    
	    for(Int_t M=0;M<RunBin;M++){
	      if (RunNumber==RunForLumi[M]){
		RunTriggers[M]->Fill(bx);
		RunLumi[M]->Fill(bx,LumiCor);
	      }	    
	    }	  
	    // -------------------------------//
	    
	    
	  } //LumiCor>0.005
      } //jentry
	
  }//NDIR
  
    
  cout << "Writing out the Histos" << endl;

  TFile f(DataFile,"recreate"); 
  
  for (Int_t N=0; N<LumBin; N++) {
    LumiBin[N]->Write();
    VxtLumiBin[N]->Write(); 
  }
  
  for (Int_t N=0; N<VxtBin; N++) {
    Vxt_Lumi[N]->Write();
  }
  
  for(Int_t M=0;M<RunBin;M++){
    RunTriggers[M]->Write();
    RunLumi[M]->Write();
  }	    

  Int_t NNM= Multi[1]->GetNbinsX();

  for(Int_t M=0;M<MultiBin;M++){

    Float_t Multi_norm = 0;
    for (Int_t MK=NNM-10;MK<=NNM;MK++)   Multi_norm +=  Multi[M]->GetBinContent(MK);
    Multi[M]->Scale(11./Multi_norm);

    Multi[M]->Write();
    VzNDOF[M]->Write();

  }

  for(Int_t M=0;M<NumPU;M++){
    PUMulti[M]->Write();
  }
  
  Dat_all_Lumi->Write();
  BxLumi->Write();
  NTriggers->Write();
  Runs->Write();
  RunsLumi->Write();
  Vertex1Mult->Write();
  Vertex1MultGT200->Write();
  Vertex0Mult->Write();
  Vertex1MultVtxQual->Write();
  Vertex0MultVtxQual->Write();
  Vz->Write();
  HNDOF->Write();
  VtxQual->Write();
  Vtx1_HF0->Write();

  MeasPt_Mult6->Write();  
  MeasPt_Mult9->Write();  
  LumiCorProf->Write();      
  LumiCor2D->Write();      

  ZDiff_2vtx_Alltrack->Write();      
  ZDiff_2vtx_2track->Write();      

  f.Close(); 
  
}//Loop


