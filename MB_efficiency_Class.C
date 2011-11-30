#define MB_efficiency_Class_cxx
#include "MB_efficiency_Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "string.h"
#include <sstream>
#include <iomanip>
#include <TRandom.h>
#include "NCutil.C"


const Int_t tracksbin = 11;
Float_t NtracksGenEta;
Float_t NtracksGenEtaPt200;
Float_t NtracksGenEtaPt250;
Float_t NtracksGenEtaPt500;


TH1F *TracksGenEta;
TH1F *TracksGenEtaPt200;
TH1F *TracksGenEtaPt200_w;
TH1F *TracksGenEtaPt250;
TH1F *TracksGenEtaPt250_w;

TH1F *TracksGenEtaPt200_NDOFGT0;
TH1F *TracksGenEtaPt200_NDOFGT0_w;

TH1F *TracksGenEta2Pt200;
TH1F *TracksGenEta2Pt200_w;
TH1F *TracksGenEta3Pt200;
TH1F *TracksGenEta3Pt200_w;
TH1F *TracksGenEta2Pt250;
TH1F *TracksGenEta2Pt250_w;
TH1F *TracksGenEta3Pt250;
TH1F *TracksGenEta3Pt250_w;
TH1F *TracksGenEta2Pt500;
TH1F *TracksGenEta2Pt500_w;

TH1F *TracksGenEta2Pt200_NDOFGT0;
TH1F *TracksGenEta2Pt200_NDOFGT0_w;
TH1F *TracksGenEta2Pt250_NDOFGT0;
TH1F *TracksGenEta2Pt250_NDOFGT0_w;

TH1F *TracksGenEtaPt200_NDOFGT05;
TH1F *TracksGenEtaPt200_NDOFGT05_w;

TH1F *TracksGenEtaPt200_NDOFGT05_2tr;
TH1F *TracksGenEtaPt200_NDOFGT05_2tr_w;

TH1F *TracksGenEtaPt200_NDOFGT05_3tr;
TH1F *TracksGenEtaPt200_NDOFGT05_3tr_w;

TH1F *TracksGenEtaPt250_NDOFGT05;
TH1F *TracksGenEtaPt250_NDOFGT05_w;


TH1F *TracksGenEta3Pt200_NDOFGE2;
TH1F *TracksGenEta3Pt200_NDOFGE2_w;
TH1F *TracksGenEta3Pt250_NDOFGE2;
TH1F *TracksGenEta3Pt250_NDOFGE2_w;



TH1F *TracksGenEta4Pt200_NDOFGE3;
TH1F *TracksGenEta4Pt200_NDOFGE3_w;
TH1F *TracksGenEta4Pt250_NDOFGE3;
TH1F *TracksGenEta4Pt250_NDOFGE3_w;

TH1F *TracksMeas;

TH1F *TracksMeas_NDOFGT0;
TH1F *TracksMeas_NDOFGT0_w;
TH1F *TracksMeas_GoodPos_NDOFGT0;
TH1F *TracksMeas_GoodPos_NDOFGT0_w;
TH1F *TracksMeas_NDOFGE1;
TH1F *TracksMeas_NDOFGE1_w;


TH1F *TracksMeas_NDOFGT05;
TH1F *TracksMeas_NDOFGT05_w;

TH1F *TracksMeas_NDOFGE2;
TH1F *TracksMeas_NDOFGE2_w;
TH1F *TracksMeas250_NDOFGE2;
TH1F *TracksMeas250_NDOFGE2_w;
TH1F *TracksMeas200_NDOFGE2;
TH1F *TracksMeas200_NDOFGE2_w;


TH1F *TracksMeas_NDOFGE3;
TH1F *TracksMeas_NDOFGE3_w;
TH1F *TracksMeas250_NDOFGE3;
TH1F *TracksMeas250_NDOFGE3_w;
TH1F *TracksMeas200_NDOFGE3;
TH1F *TracksMeas200_NDOFGE3_w;

TH1F *MeasPt_Mult6;
TH1F *MeasPt_Mult9;
TH1F *MeasPt_Mult6_GE2;
TH1F *MeasPt_Mult9_GE2;


TH1F *TracksGenMeasRatio;



TH1F *Xi_NDOFGE2;
TH1F *Xi_NDOFGE2_w;
TH1F *Xi_NDOFGE3;
TH1F *Xi_NDOFGE3_w;
TH1F *Xi;
TH1F *Xi_w;

TH1F *Xi_TrkGenEta2Pt200_w;
TH1F *Xi_TrkGenEta2Pt200;
TH1F *Xi_TrkGenEta3Pt200_w;
TH1F *Xi_TrkGenEta3Pt200;
TH1F *Xi_TrkGenEta3Pt250_w;
TH1F *Xi_TrkGenEta3Pt250;
TH1F *Xi_TrkGenEta2Pt500_w;
TH1F *Xi_TrkGenEta2Pt500;






const Int_t NDIR   = 3;  /* number or Directories*/

//stringstream stringa;
//stringstream MCstr;

string stringa;
string MCstr;

char hnameout[100]; 
char hname[100]; 
char htitle[100]; 

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
TFile *fF;
TTree *tree_fF;

TFile *fOut;
Float_t weight;


TFile *fRew2;


TCanvas *My[3];

void MB_efficiency_Class::Loop()
{
   



    fA = new TFile("files/MBPythia8_v1_16_CHA.root");
    tree_fA= (TTree*)gDirectory->Get("tree_");

    fB = new TFile("files/MBPythia8_v1_16_ALL.root");
    tree_fB= (TTree*)gDirectory->Get("tree_");

    fC = new TFile("files/MBPythiaCW_DAV_v1_12.root");
    tree_fC= (TTree*)gDirectory->Get("tree_");




    readfile();

    TFile fOut(MCMBFile,"recreate"); 


    for (Int_t i=1 ; i<=NDIR; i++)
      {
	
	if (i==1)
	  {
	    fChain =tree_fA;  /* Loop RunA */ 
	    MCstr = "P8_CHA";
	    cout << MCstr.c_str()<< endl;
	    
	  }
	else if (i==2)
	  { 
	    fChain = tree_fB;  /* Loop RunB */ 
	    MCstr = "P8_ALL";
	    cout << MCstr.c_str()<< endl;
	    
	  }
	
	else if (i==3)
	  { 
	    fChain =tree_fC;  /* Loop RunB */ 
	    MCstr = "CW";
	    cout << MCstr.c_str()<< endl;
	    
	  }

	else if (i==4)
	  { 
	    fChain =tree_fD;  /* Loop RunB */ 
	    MCstr = "P8_CHA";
	    cout << MCstr.c_str()<< endl;
	    
	  }

	else if (i==5)
	  { 
	    fChain =tree_fE; 
	    MCstr = "P8_ALL";
	    cout << MCstr.c_str()<< endl;
	    
	  }


	else if (i==6)
	  { 
	    fChain =tree_fE; 
	    MCstr = "DW";
	    cout << MCstr.c_str()<< endl;
	    
	  }
	

	Init(fChain);
	
	if (fChain == 0) 
	  {
	    cout << "Problem with the input file " << endl;
	    return;
	  }
	
	
	
	//if (vertexNDOF[0]>2)  GenPt_vtxNDOF[Ntracks_eta]->Fill(tracksPT_gen[3]);
	

	
	stringa = "TracksMeas_"+ MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas = new TH1F(hname,hname,71, -0.5, 70.5);  
	TracksMeas->Sumw2(); 


	stringa = "TracksGenEtaPt200_NDOFGT0_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt200_NDOFGT0 = NH1clone(hname, hname,TracksMeas);

	stringa = "TracksGenEtaPt200_NDOFGT0_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt200_NDOFGT0_w = NH1clone(hname, hname,TracksMeas);

	stringa = "TracksGenEtaPt200_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt200 = NH1clone(hname, hname,TracksMeas);
	
	stringa = "TracksGenEtaPt200_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt200_w = NH1clone(hname, hname,TracksMeas);


	stringa = "TracksGenEtaPt250_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt250 = NH1clone(hname, hname,TracksMeas);
	
	stringa = "TracksGenEtaPt250_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt250_w = NH1clone(hname, hname,TracksMeas);




	stringa = "TracksGenEtaPt200_NDOFGT05_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt200_NDOFGT05 = NH1clone(hname, hname,TracksMeas);

	stringa = "TracksGenEtaPt200_NDOFGT05_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt200_NDOFGT05_w = NH1clone(hname, hname,TracksMeas);


	stringa = "TracksGenEtaPt200_NDOFGT05_2tr_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt200_NDOFGT05_2tr = NH1clone(hname, hname,TracksMeas);

	stringa = "TracksGenEtaPt200_NDOFGT05_2tr_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt200_NDOFGT05_2tr_w = NH1clone(hname, hname,TracksMeas);


	stringa = "TracksGenEtaPt200_NDOFGT05_3tr_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt200_NDOFGT05_3tr = NH1clone(hname, hname,TracksMeas);

	stringa = "TracksGenEtaPt200_NDOFGT05_3tr_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt200_NDOFGT05_3tr_w = NH1clone(hname, hname,TracksMeas);


	stringa = "TracksGenEtaPt250_NDOFGT05_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt250_NDOFGT05 = NH1clone(hname, hname,TracksMeas);

	stringa = "TracksGenEtaPt250_NDOFGT05_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEtaPt250_NDOFGT05_w = NH1clone(hname, hname,TracksMeas);

      
	
	
	stringa = "TracksGenEta2Pt250_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEta2Pt250 = NH1clone(hname, hname,TracksMeas);

	stringa = "TracksGenEta2Pt250_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEta2Pt250_w = NH1clone(hname, hname,TracksMeas);

	stringa = "TracksGenEta2Pt200_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEta2Pt200 = NH1clone(hname, hname,TracksMeas);

	stringa = "TracksGenEta2Pt200_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEta2Pt200_w = NH1clone(hname, hname,TracksMeas);


	stringa = "TracksGenEta3Pt200_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEta3Pt200 = NH1clone(hname, hname,TracksMeas);
	
	stringa = "TracksGenEta3Pt200_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEta3Pt200_w = NH1clone(hname, hname,TracksMeas);


	stringa = "TracksGenEta2Pt200_NDOFGT0_"+MCstr;
	sprintf(hname,stringa.c_str());      
	TracksGenEta2Pt200_NDOFGT0 = NH1clone(hname, hname,TracksMeas);
	
	stringa = "TracksGenEta2Pt200_NDOFGT0_w_"+MCstr;
	sprintf(hname,stringa.c_str());      
	TracksGenEta2Pt200_NDOFGT0_w = NH1clone(hname, hname,TracksMeas);


	stringa = "TracksGenEta2Pt250_NDOFGT0_"+MCstr;
	sprintf(hname,stringa.c_str());      
	TracksGenEta2Pt250_NDOFGT0 = NH1clone(hname, hname,TracksMeas);
	
	stringa = "TracksGenEta2Pt250_NDOFGT0_w_"+MCstr;
	sprintf(hname,stringa.c_str());      
	TracksGenEta2Pt250_NDOFGT0_w = NH1clone(hname, hname,TracksMeas);


	stringa = "TracksGenEta3Pt200_NDOFGE2_"+MCstr;
	sprintf(hname,stringa.c_str());      
	TracksGenEta3Pt200_NDOFGE2 = NH1clone(hname, hname,TracksMeas);
	
	stringa = "TracksGenEta3Pt200_NDOFGE2_w_"+MCstr;
	sprintf(hname,stringa.c_str());      
	TracksGenEta3Pt200_NDOFGE2_w = NH1clone(hname, hname,TracksMeas);


	stringa = "TracksGenEta3Pt250_NDOFGE2_"+MCstr;
	sprintf(hname,stringa.c_str());      
	TracksGenEta3Pt250_NDOFGE2 = NH1clone(hname, hname,TracksMeas);
	
	stringa = "TracksGenEta3Pt250_NDOFGE2_w_"+MCstr;
	sprintf(hname,stringa.c_str());      
	TracksGenEta3Pt250_NDOFGE2_w = NH1clone(hname, hname,TracksMeas);

	

	stringa = "TracksGenEta3Pt250_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEta3Pt250 = NH1clone(hname, hname,TracksMeas);
	
	stringa = "TracksGenEta3Pt250_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEta3Pt250_w = NH1clone(hname, hname,TracksMeas);
	

	stringa = "TracksGenEta4Pt200_NDOFGE3_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEta4Pt200_NDOFGE3 = NH1clone(hname, hname,TracksMeas);
	
	stringa = "TracksGenEta4Pt200_NDOFGE3_w_"+MCstr;
	sprintf(hname,stringa.c_str());      
	TracksGenEta4Pt200_NDOFGE3_w = NH1clone(hname, hname,TracksMeas);

	stringa = "TracksGenEta4Pt250_NDOFGE3_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEta4Pt250_NDOFGE3 = NH1clone(hname, hname,TracksMeas);
	
	stringa = "TracksGenEta4Pt250_NDOFGE3_w_"+MCstr;
	sprintf(hname,stringa.c_str());      
	TracksGenEta4Pt250_NDOFGE3_w = NH1clone(hname, hname,TracksMeas);
	



	
	stringa = "TracksGenEta_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenEta = NH1clone(hname, hname,TracksMeas);
	
	stringa = "TracksGenMeasRatio_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksGenMeasRatio = NH1clone(hname, hname,TracksMeas);
	
	
	
	stringa = "TracksMeas_NDOFGE3_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGE3 = new TH1F(hname,hname,200, 0.5, 200.5);  
	stringa = "TracksMeas_NDOFGE3_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGE3_w = NH1clone(hname,hname, TracksMeas_NDOFGE3);  

	stringa = "TracksMeas200_NDOFGE3_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas200_NDOFGE3 = new TH1F(hname,hname,200, 0.5, 200.5);  	
	stringa = "TracksMeas200_NDOFGE3_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas200_NDOFGE3_w = NH1clone(hname,hname, TracksMeas_NDOFGE3);  


	stringa = "TracksMeas250_NDOFGE3_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas250_NDOFGE3 = new TH1F(hname,hname,200, 0.5, 200.5);  	
	stringa = "TracksMeas250_NDOFGE3_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas250_NDOFGE3_w = NH1clone(hname,hname, TracksMeas_NDOFGE3);  


	
	stringa = "TracksMeas_NDOFGE2_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGE2 = NH1clone(hname,hname, TracksMeas_NDOFGE3);  
	stringa = "TracksMeas_NDOFGE2_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGE2_w = NH1clone(hname,hname, TracksMeas_NDOFGE3);  


	stringa = "TracksMeas200_NDOFGE2_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas200_NDOFGE2 = NH1clone(hname,hname, TracksMeas_NDOFGE3);  
	stringa = "TracksMeas200_NDOFGE2_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas200_NDOFGE2_w = NH1clone(hname,hname, TracksMeas_NDOFGE3);  

	stringa = "TracksMeas250_NDOFGE2_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas250_NDOFGE2 = NH1clone(hname,hname, TracksMeas_NDOFGE3);  
	stringa = "TracksMeas250_NDOFGE2_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas250_NDOFGE2_w = NH1clone(hname,hname, TracksMeas_NDOFGE3);  


	stringa = "TracksMeas_NDOFGT0_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGT0 = new TH1F(hname,hname,200, 0.5, 200.5);  
	stringa = "TracksMeas_NDOFGT0_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGT0_w = NH1clone(hname,hname, TracksMeas_NDOFGE3);  


	stringa = "TracksMeas_NDOFGT05_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGT05 = new TH1F(hname,hname,200, 0.5, 200.5);  
	stringa = "TracksMeas_NDOFGT05_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGT05_w = NH1clone(hname,hname, TracksMeas_NDOFGE3);  


	stringa = "TracksMeas_GoodPos_NDOFGT0_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_GoodPos_NDOFGT0 = new TH1F(hname,hname,200, 0.5, 200.5);  
	stringa = "TracksMeas_GoodPos_NDOFGT0_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_GoodPos_NDOFGT0_w = NH1clone(hname,hname, TracksMeas_NDOFGE3);  


	stringa = "TracksMeas_NDOFGE1_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGE1 = new TH1F(hname,hname,200, 0.5, 200.5);  
	stringa = "TracksMeas_NDOFGE1_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGE1_w = NH1clone(hname,hname, TracksMeas_NDOFGE3);  


	stringa = "TracksMeas_NDOFGE3_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGE3 = new TH1F(hname,hname,200, 0.5, 200.5);  
	stringa = "TracksMeas_NDOFGE3_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	TracksMeas_NDOFGE3_w = NH1clone(hname,hname, TracksMeas_NDOFGE3);  
	
	
	stringa = "MeasPt_NDOFGE3_Mult6_"+MCstr;
	sprintf(hname,stringa.c_str());
	MeasPt_Mult6 = new TH1F(hname,hname,60,0.,6.);  
	MeasPt_Mult6->Sumw2();  
	
	stringa = "MeasPt_NDOFGE3_Mult9_"+MCstr;
	sprintf(hname,stringa.c_str());
	MeasPt_Mult9 = NH1clone(hname,hname, MeasPt_Mult6);  



	stringa = "MeasPt_NDOFGE2_Mult6_"+MCstr;
	sprintf(hname,stringa.c_str());
	MeasPt_Mult6_GE2 = new TH1F(hname,hname,60,0.,6.);  
	MeasPt_Mult6_GE2->Sumw2();  
	
	stringa = "MeasPt_NDOFGE2_Mult9_"+MCstr;
	sprintf(hname,stringa.c_str());
	MeasPt_Mult9_GE2 = NH1clone(hname,hname, MeasPt_Mult6_GE2);  


	stringa = "Xi_NDOFGE2_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_NDOFGE2 = new TH1F(hname,hname,160, -8., 0.);  
	
	stringa = "Xi_NDOFGE2_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_NDOFGE2_w = NH1clone(hname,hname, Xi_NDOFGE2);  

	stringa = "Xi_NDOFGE3_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_NDOFGE3 = NH1clone(hname,hname, Xi_NDOFGE2);  

	stringa = "Xi_NDOFGE3_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_NDOFGE3_w = NH1clone(hname,hname, Xi_NDOFGE2);  

	stringa = "Xi_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_w = NH1clone(hname,hname, Xi_NDOFGE2);  

	stringa = "Xi_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi = NH1clone(hname,hname, Xi_NDOFGE2);  


	stringa = "Xi_TrkGenEta2Pt200_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_TrkGenEta2Pt200_w = NH1clone(hname,hname, Xi_NDOFGE2);  

	stringa = "Xi_TrkGenEta2Pt200_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_TrkGenEta2Pt200 = NH1clone(hname,hname, Xi_NDOFGE2);  

	stringa = "Xi_TrkGenEta3Pt200_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_TrkGenEta3Pt200_w = NH1clone(hname,hname, Xi_NDOFGE2);  

	stringa = "Xi_TrkGenEta3Pt200_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_TrkGenEta3Pt200 = NH1clone(hname,hname, Xi_NDOFGE2);  

	stringa = "Xi_TrkGenEta3Pt250_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_TrkGenEta3Pt250_w = NH1clone(hname,hname, Xi_NDOFGE2);  

	stringa = "Xi_TrkGenEta3Pt250_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_TrkGenEta3Pt250 = NH1clone(hname,hname, Xi_NDOFGE2);  
	

	stringa = "Xi_TrkGenEta2Pt500_w_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_TrkGenEta2Pt500_w = NH1clone(hname,hname, Xi_NDOFGE2);  

	stringa = "Xi_TrkGenEta2Pt500_"+MCstr;
	sprintf(hname,stringa.c_str());
	Xi_TrkGenEta2Pt500 = NH1clone(hname,hname, Xi_NDOFGE2);  
	
	
	
	Long64_t nentries = fChain->GetEntriesFast();
	
	cout << "The MB file has "  <<  nentries << endl;
	
	Long64_t nbytes = 0, nb = 0;
	//  for (Long64_t jentry=0; jentry<nentries;jentry++) {
	

	for (Long64_t jentry=0; jentry<200000;jentry++) {
	  //  for (Long64_t jentry=0; jentry<10;jentry++) {

	  Long64_t ientry = LoadTree(jentry);
	  if (ientry < 0) break;
	  nb = fChain->GetEntry(jentry);   nbytes += nb;
	  // if (Cut(ientry) < 0) continue;
	  
	  
	  if (jentry> 100000 && jentry % 10000 == 0) cout << "jentry = " << jentry << endl;
	  
	  
	  NtracksGenEtaPt200 = 0;
	  NtracksGenEtaPt250 = 0;
	  NtracksGenEtaPt500 = 0;
	  NtracksGenEta=0;
	  // Float_t FPtCut = 1.*PtCut/1000.;
	  for (Int_t ii=0; ii<numberoOfTracks_gen;ii++)  // calculate the number of generated tracks in eta&&Pt
	    {
	      if (ii<=30)
		{
		  //	
		  if ( fabs(etaOfTracksPT_gen[ii])<MCEff_EtaCut)
		    {
		      NtracksGenEta++;
		      if ( tracksPT_gen[ii]>0.200)     NtracksGenEtaPt200++;
		      if ( tracksPT_gen[ii]>0.250)     NtracksGenEtaPt250++;
		      if ( tracksPT_gen[ii]>0.500)     NtracksGenEtaPt500++;
		    }
		}
	    }
	  
	  
	  Int_t VtxMult = vertexMolteplicity[0];
	  Int_t xw = NtracksGenEtaPt200;
	  
	  
	  // Reweight, in Fraction_n_vertexes_Draw() //
	  
	  if (i == 1 || i == 4 || i == 5 )
	    {
	      weight = (1.85-0.243*xw+0.0183*xw*xw-0.000411*xw*xw*xw); //Z2 NDOF GT 2
	      //    	      cout << " Z2 = x = "<< x << " weight " << weight << endl;
	      //	      if (x==4) weight = weight*0.9;
	      //	      if (x==4) weight = weight*0.9;
	      //	      if (x == 4) weight = weight*0.8;
	      if (xw >20 || xw ==2 ) weight = 1.;
	      if (xw ==3) weight = weight*0.92;
	    }
	  
	  if (i == 2 || i ==3 ) // D6T & CW NDOF GT 2	
	    {
	      //	      if (xw>3 && xw< 15) xw = 7;
	      weight = 
		+1.139
		-0.097*xw
		+0.00814*xw*xw
		-0.000208*xw*xw*xw
		+0.00000210*xw*xw*xw*xw
		-0.0000000066*xw*xw*xw*xw*xw;
	      
	      if (xw==4) weight = weight*0.85;
	      if (xw==3) weight = weight*0.65;
	      if (xw==2) weight = weight*0.45;
	    }
	  
	  //	  if ( x > 30) weight = 0;
	  
	  Int_t x = vertexMolteplicity[0];

	  Float_t LogXi = log10(1.- fabs(xL_gen));	
	  
	  Xi_w->Fill(LogXi,weight);	  	  
	  Xi->Fill(LogXi);
	  
	  
	  TracksGenEta->Fill(numberoOfTracks_gen); // no pt cut
	  TracksGenEtaPt200->Fill(NtracksGenEtaPt200);
	  TracksGenEtaPt200_w->Fill(NtracksGenEtaPt200,weight);
	  TracksGenEtaPt250->Fill(NtracksGenEtaPt250);
	  TracksGenEtaPt250_w->Fill(NtracksGenEtaPt250,weight);



	  if (NtracksGenEtaPt200>= 2) 
	    {
	      TracksGenEta2Pt200->Fill(NtracksGenEtaPt200);
	      TracksGenEta2Pt200_w->Fill(NtracksGenEtaPt200,weight);


	      Xi_TrkGenEta2Pt200_w->Fill(LogXi,weight);
	      Xi_TrkGenEta2Pt200->Fill(LogXi);
	    }
	  
	  
	  if (NtracksGenEtaPt200>= 3) 
	    {
	      TracksGenEta3Pt200->Fill(NtracksGenEtaPt200);
	      TracksGenEta3Pt200_w->Fill(NtracksGenEtaPt200,weight);
	    }

	  

	  
	  if(NtracksGenEtaPt200 >=3)
	    {
	      Xi_TrkGenEta3Pt200_w->Fill(LogXi,weight);
	      Xi_TrkGenEta3Pt200->Fill(LogXi);
	      
	      
	      TracksGenEta3Pt250->Fill(NtracksGenEtaPt250);
	      TracksGenEta3Pt250_w->Fill(NtracksGenEtaPt250,weight);
	    }
	  
	  //new
	  if (NtracksGenEtaPt250 >=2)
	    {
	      TracksGenEta2Pt250->Fill(NtracksGenEtaPt250);
	      TracksGenEta2Pt250_w->Fill(NtracksGenEtaPt250,weight);
	    }

	  if (NtracksGenEtaPt250 >=3)
	    {
	      Xi_TrkGenEta3Pt250_w->Fill(LogXi,weight);
	      Xi_TrkGenEta3Pt250->Fill(LogXi);
	    }
	  
	  if (NtracksGenEtaPt500 >=2)
	    {
	      Xi_TrkGenEta2Pt500_w->Fill(LogXi,weight);
	      Xi_TrkGenEta2Pt500->Fill(LogXi);
	    }
	  

	  bool GoodPosF = false;
	  if (fabs(sqrt(pow(V_x[0],2)+pow(V_y[0],2))-0.463)<0.06) GoodPosF = true;
	  
	  // Here we start the "measured" part //
	  if (!GoodPosF) continue;

	  if (vertexNDOF[0]>0) 
	    {
	      TracksMeas_NDOFGT0_w->Fill(x,weight);
	      TracksMeas_NDOFGT0->Fill(x);
	      TracksGenEtaPt200_NDOFGT0->Fill(NtracksGenEtaPt200);
	      TracksGenEtaPt200_NDOFGT0_w->Fill(NtracksGenEtaPt200,weight);


	      
	      if (NtracksGenEtaPt200 >=2)
		{
		  TracksGenEta2Pt200_NDOFGT0->Fill(NtracksGenEtaPt200);
		  TracksGenEta2Pt200_NDOFGT0_w->Fill(NtracksGenEtaPt200,weight);
		}
	      if (NtracksGenEtaPt250 >=2)
		{
		  TracksGenEta2Pt250_NDOFGT0->Fill(NtracksGenEtaPt250);
		  TracksGenEta2Pt250_NDOFGT0_w->Fill(NtracksGenEtaPt250,weight);
		}


	    }
	  
	  if (vertexNDOF[0]>0.5) 
	    {
	      TracksMeas_NDOFGT05_w->Fill(x,weight);
	      TracksMeas_NDOFGT05->Fill(x);
	      TracksGenEtaPt200_NDOFGT05->Fill(NtracksGenEtaPt200);
	      TracksGenEtaPt200_NDOFGT05_w->Fill(NtracksGenEtaPt200,weight);
	      TracksGenEtaPt250_NDOFGT05->Fill(NtracksGenEtaPt250);
	      TracksGenEtaPt250_NDOFGT05_w->Fill(NtracksGenEtaPt250,weight);
	      if (x>=2) 
		{
		  TracksGenEtaPt200_NDOFGT05_2tr->Fill(NtracksGenEtaPt200);
		  TracksGenEtaPt200_NDOFGT05_2tr_w->Fill(NtracksGenEtaPt200,weight);
		}
	      if (x>=3) 
		{
		  TracksGenEtaPt200_NDOFGT05_3tr->Fill(NtracksGenEtaPt200);
		  TracksGenEtaPt200_NDOFGT05_3tr_w->Fill(NtracksGenEtaPt200,weight);
		}

	    }


	  if (vertexNDOF[0]>=1) 
	    {
	      TracksMeas_NDOFGE1_w->Fill(x,weight);
	      TracksMeas_NDOFGE1->Fill(x);
	    }
	  
	  
	  if (vertexNDOF[0]>=2) 
	    {
	      
	      Int_t GoodTrk200 = 0;
	      Int_t GoodTrk250 = 0;
	      for (Int_t Ntr = 0; Ntr< vertexMolteplicity[0]; Ntr++)
		{
		  if (Ntr<=30)
		    {
		      if(tracksPT[0][Ntr]>0.200) GoodTrk200++;
		      if(tracksPT[0][Ntr]>0.250) GoodTrk250++;
		    }
		  else continue;
		}
	      
	      
	      
	      if (NtracksGenEtaPt200 >=3)
		{
		  TracksGenEta3Pt200_NDOFGE2->Fill(NtracksGenEtaPt200);
		  TracksGenEta3Pt200_NDOFGE2_w->Fill(NtracksGenEtaPt200,weight);
		}
	      if (NtracksGenEtaPt250 >=3)
		{
		  TracksGenEta3Pt250_NDOFGE2->Fill(NtracksGenEtaPt250);
		  TracksGenEta3Pt250_NDOFGE2_w->Fill(NtracksGenEtaPt250,weight);
		}
	      
	      
	      TracksMeas_NDOFGE2_w->Fill(x,weight);
	      TracksMeas_NDOFGE2->Fill(x);
	      
	      TracksMeas250_NDOFGE2_w->Fill(GoodTrk250,weight);
	      TracksMeas250_NDOFGE2->Fill(GoodTrk250);
	      
	      TracksMeas200_NDOFGE2_w->Fill(GoodTrk200,weight);
	      TracksMeas200_NDOFGE2->Fill(GoodTrk200);
	      
	      
	      Xi_NDOFGE2_w->Fill(LogXi,weight);
	      Xi_NDOFGE2->Fill(LogXi);
	      
	      
	      
	      if (x==7)
		{
		  for (Int_t yy = 0;yy<6;yy++) MeasPt_Mult6_GE2->Fill(tracksPT[0][yy]);
		}
	      
	      
	      if (x==10)
		{
		  for (Int_t yy = 0;yy<9;yy++) MeasPt_Mult9_GE2->Fill(tracksPT[0][yy]);
		}	    

	    } // end of NDOF>=2
	  
	  
	  
	  
	  if (vertexNDOF[0]>=3)	  
	    {
	      
	      Int_t GoodTrk200 = 0;
	      Int_t GoodTrk250 = 0;
	      for (Int_t Ntr = 0; Ntr< vertexMolteplicity[0]; Ntr++)
		{
		  if (Ntr<30)
		    {
		      if(tracksPT[0][Ntr]>0.250) GoodTrk250++;
		      if(tracksPT[0][Ntr]>0.200) GoodTrk200++;
		    }
		}
	      
	      if (NtracksGenEtaPt250>=4)
		{
		  TracksGenEta4Pt250_NDOFGE3->Fill(NtracksGenEtaPt200);
		  TracksGenEta4Pt250_NDOFGE3_w->Fill(NtracksGenEtaPt200,weight);
		}
	      
	      if (NtracksGenEtaPt200>=4)
		{
		  TracksGenEta4Pt200_NDOFGE3->Fill(NtracksGenEtaPt200);
		  TracksGenEta4Pt200_NDOFGE3_w->Fill(NtracksGenEtaPt200,weight);
		}
	      
	      
	      TracksMeas_NDOFGE3_w->Fill(x,weight);
	      TracksMeas_NDOFGE3->Fill(x);
	      
	      
	      Xi_NDOFGE3_w->Fill(LogXi,weight);
	      Xi_NDOFGE3->Fill(LogXi);
	      
	      if (x==7)
		{
		  for (Int_t yy = 0;yy<6;yy++) MeasPt_Mult6->Fill(tracksPT[0][yy],weight);
		}
	      
	      
	      if (x==10)
		{
		  for (Int_t yy = 0;yy<9;yy++) MeasPt_Mult9->Fill(tracksPT[0][yy],weight);
		}
	      
	    }
	  
	  
	  
	} // Jentry
	
	
	
	TracksGenEta->Write();
	TracksGenEtaPt200->Write();
	TracksGenEtaPt200_w->Write();
	TracksGenEtaPt250->Write();
	TracksGenEtaPt250_w->Write();

	TracksGenEtaPt200_NDOFGT0->Write();
	TracksGenEtaPt200_NDOFGT0_w->Write();
	TracksGenEtaPt200_NDOFGT05->Write();
	TracksGenEtaPt200_NDOFGT05_w->Write();
	TracksGenEtaPt200_NDOFGT05_2tr->Write();
	TracksGenEtaPt200_NDOFGT05_2tr_w->Write();
	TracksGenEtaPt200_NDOFGT05_3tr->Write();
	TracksGenEtaPt200_NDOFGT05_3tr_w->Write();
	TracksGenEtaPt250_NDOFGT05->Write();
	TracksGenEtaPt250_NDOFGT05_w->Write();
	
	TracksGenEta2Pt200->Write();
	TracksGenEta2Pt200_w->Write();
	TracksGenEta2Pt250->Write();
	TracksGenEta2Pt250_w->Write();

	TracksGenEta3Pt200->Write();
	TracksGenEta3Pt200_w->Write();
	TracksGenEta3Pt250->Write();
	TracksGenEta3Pt250_w->Write();
	
	TracksGenEta2Pt200_NDOFGT0->Write();
	TracksGenEta2Pt200_NDOFGT0_w->Write();
	TracksGenEta2Pt250_NDOFGT0->Write();
	TracksGenEta2Pt250_NDOFGT0_w->Write();


	TracksGenEta3Pt200_NDOFGE2->Write();
	TracksGenEta3Pt200_NDOFGE2_w->Write();
	TracksGenEta3Pt250_NDOFGE2->Write();
	TracksGenEta3Pt250_NDOFGE2_w->Write();
	
	
	TracksGenEta4Pt200_NDOFGE3->Write();
	TracksGenEta4Pt200_NDOFGE3_w->Write();
	TracksGenEta4Pt250_NDOFGE3->Write();
	TracksGenEta4Pt250_NDOFGE3_w->Write();
	
	
	TracksMeas_NDOFGT0_w->Write();
	TracksMeas_NDOFGT0->Write();
	TracksMeas_GoodPos_NDOFGT0_w->Write();
	TracksMeas_GoodPos_NDOFGT0->Write();
	TracksMeas_NDOFGE1_w->Write();
	TracksMeas_NDOFGE1->Write();
	
	TracksMeas_NDOFGT05_w->Write();
	TracksMeas_NDOFGT05->Write();
	
	TracksMeas_NDOFGE2_w->Write();
	TracksMeas_NDOFGE2->Write();
	TracksMeas200_NDOFGE2_w->Write();
	TracksMeas200_NDOFGE2->Write();
	TracksMeas250_NDOFGE2_w->Write();
	TracksMeas250_NDOFGE2->Write();
	
	
	TracksMeas_NDOFGE3_w->Write();
	TracksMeas_NDOFGE3->Write();
	
	TracksMeas250_NDOFGE3_w->Write();
	TracksMeas250_NDOFGE3->Write();
	
	MeasPt_Mult6->Write();
	MeasPt_Mult9->Write();
	MeasPt_Mult6_GE2->Write();
	MeasPt_Mult9_GE2->Write();
	
	
	
	
	Xi_NDOFGE3_w->Write();
	Xi_NDOFGE3->Write();
	Xi_NDOFGE2_w->Write();
	Xi_NDOFGE2->Write();
	Xi_w->Write();
	Xi->Write();
	
	Xi_TrkGenEta2Pt200_w->Write();
	Xi_TrkGenEta2Pt200->Write();
	Xi_TrkGenEta3Pt200_w->Write();
	Xi_TrkGenEta3Pt200->Write();
	Xi_TrkGenEta3Pt250_w->Write();
	Xi_TrkGenEta3Pt250->Write();
	Xi_TrkGenEta2Pt500_w->Write();
	Xi_TrkGenEta2Pt500->Write();
	
      }
    fOut.Close();
    
} // Loop


