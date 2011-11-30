#define EEfit_PythiaPomData_v1_Class_cxx
#include "EEfit_PythiaPomData_v1_Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <sstream>
#include <istream>
#include <string>
#include <math.h>
#include "NCutil.C"

const Int_t NDIR   = 4;  /* number of Directory*/
const Int_t NPAR   = 2;  /* number of Fit Parameters*/

const Int_t hnbin = 14;

// Put everything in arrays
  
Float_t *Pcpompyt = new Float_t [hnbin];
Float_t *Pepompyt = new Float_t [hnbin];
Float_t *Pcdata = new  Float_t [hnbin];
Float_t *Pedata  = new Float_t [hnbin];
Float_t *Pcpythia = new Float_t [hnbin];
Float_t *Pepythia = new Float_t [hnbin];

void EEfit_PythiaPomData_v1_Class::Loop()
{

   TFile *fpyt = new TFile("files/pythiaD6T_ee_v1.root");
   TTree *tree_pyt = (TTree*)gDirectory->Get("tree_");

   TFile *fpom = new TFile("files/DiffractiveMC_ee_v1.root");
   TTree *tree_pom = (TTree*)gDirectory->Get("tree_");

   TFile *fzee = new TFile("files/ZetaSkim_ee_v1.root");
   TTree *tree_zee = (TTree*)gDirectory->Get("tree_");

   TFile *fzmm = new TFile("files/ZetaSkim_mm_v1.root");
   TTree *tree_zmm = (TTree*)gDirectory->Get("tree_");


   Float_t xlow[15] = {0., 4.,10.,20.,40.,60.,90.,120.,150.,250.,400.,600.,800.,1000.,1500. }

   // Float_t llow = 0.;
   // Float_t lup = 500.;


   gDirectory->Delete("Hpom");
   gDirectory->Delete("Hpytia");
   gDirectory->Delete("Hdata");
   gDirectory->Delete("Hdata1");
   gDirectory->Delete("Hdata2");
   gDirectory->Delete("Hdata3");

   gDirectory->Delete("HSum");
    TH1F *Hpom = new TH1F("Hpom", " pompyt", hnbin, xlow);
   TH1F *Hpythia = new TH1F("Hpythia", "pythia", hnbin, xlow);
   TH1F *Hdata = new TH1F("Hdata", "data", hnbin, xlow);
   TH1F *Hdata1 = new TH1F("Hdata1", "data", hnbin, xlow);
   TH1F *Hdata2 = new TH1F("Hdata2", "data", hnbin, xlow);
   TH1F *Hdata3 = new TH1F("Hdata3", "data", hnbin, xlow);
   TH1F *HSum = new TH1F("HSum", "HSum", hnbin, xlow);

   Hpom->Sumw2();
   Hdata->Sumw2();
   Hdata1->Sumw2();
   Hdata2->Sumw2();
   Hdata3->Sumw2();
   Hpythia->Sumw2();

   TCanvas *MyC = new TCanvas("MyC","Test canvas",1);
   MyC->Divide(1,1);


   for (Int_t i=1 ; i<=NDIR; i++){
    
    // Loop and RunA
    
     if (i==1){
       fChain =tree_pyt;
     }
     else if (i==2){ 
       fChain = tree_pom;
     }
     else if (i==3){ 
       fChain = tree_zee;
     }
     else if (i==4){ 
       fChain = tree_zmm;
     };
     
     Init(fChain);
     
     // go to  Zee
     
     
     
     if (fChain == 0) return;


     Long64_t nentries = fChain->GetEntriesFast();   
     cout << "number of entries in "<< i << " = " << nentries << endl; 
     
     Long64_t nbytes = 0, nb = 0;
     for (Long64_t jentry=0; jentry<nentries;jentry++) {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       
       nb = fChain->GetEntry(jentry);   nbytes += nb;

       if (numberOfVertexes == 1)
	 {
	   if(i==1){
	     Hpythia->Fill(TMath::Min(sumEHF_minus,sumEHF_plus));
	   }
	   else if (i==2){
	     Hpom->Fill(TMath::Min(sumEHF_minus,sumEHF_plus));
	   }
	   else if (i==3 || i==4){
	     if (istlumiPerBX*6.37>0.005 && istlumiPerBX*6.37<0.62)
	       Hdata->Fill(TMath::Min(sumEHF_minus,sumEHF_plus));
	     if  (istlumiPerBX*6.37>0.005 && istlumiPerBX*6.37<0.25)
	       Hdata1->Fill(TMath::Min(sumEHF_minus,sumEHF_plus));
	     else if  (istlumiPerBX*6.37>0.25 && istlumiPerBX*6.37<0.32)
	       Hdata2->Fill(TMath::Min(sumEHF_minus,sumEHF_plus));
	     else if  (istlumiPerBX*6.32>0.35 && istlumiPerBX*6.37<0.7)
	       Hdata3->Fill(TMath::Min(sumEHF_minus,sumEHF_plus));
	   }
	 }
       
     }
   }
     
   Double_t Nevt = Hdata1->GetEntries();
   Hdata1->Scale(1./Nevt);

   Nevt = Hdata2->GetEntries();
   Hdata2->Scale(1./Nevt);

   Nevt = Hdata3->GetEntries();
   Hdata3->Scale(1./Nevt);


   // Show the results

   MyC->cd(1);
   Hdata->Draw("e");   

   Hpythia->Draw("SAMES");
   Hpom->Draw("SAMES");
   
   
   
   
   //  Cout << Pcdata->lenght() << endl;
   
   NHtoV(Hdata, Pcdata, Pedata);
   NHtoV(Hpom, Pcpompyt, Pepompyt);
   NHtoV(Hpythia, Pcpythia, Pepythia);
   
   
   cout << " the content of data[2] is = " << Pcdata[2] << "+-"<<Pedata[2] << endl ;
   cout << " the content of pythia[2] is = " << Pcpythia[2] << "+-"<<Pepythia[2] << endl ;
   cout << " the content of pompyt[2] is = " << Pcpompyt[2] << "+-"<<Pepompyt[2] << endl ;
   
   
   // Here  we go: the minuit show
   
   TMinuit *gMinuit = new TMinuit(NPAR);  //initialize TMinuit with a maximum of NPAR params
   gMinuit->SetFCN(fcn);
   
   Double_t arglist[NPAR]; // ???
   Int_t ierflg = 0;
   
   // Set starting values and step sizes for parameters
   
   Double_t vstart[NPAR] ;
   Double_t step[NPAR] ;
   Double_t par[NPAR] ,fpar[NPAR];
   char parName[NPAR];
   Int_t n;
   parName[0] = "Pythia";
   parName[1] = "Pompyt";
   
   par[0] = Hdata->Integral()/Hpythia->Integral();
   par[1] = 0.05*Hdata->Integral()/Hpom->Integral();
   
   
   for (n=0 ; n<NPAR ; n++)
     {
       vstart[n] = par[n]  ;
       step[n] = 0.5 ;
       sprintf(parName,"a%d",n);
       gMinuit->mnparm(n, parName, vstart[n], step[n], 0,0,ierflg);
     }
   
   cout << "par[0] set to = " << par[0] << " while par[1] = " << par[1] << endl;
   arglist[0] = 1;
   
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);  
   gMinuit->mnexcm("SET PRINT", arglist,1,ierflg);
   
   //Scan on parameter = 1
   arglist[0] = 1;
   gMinuit->mnexcm("SCAN",  arglist,1,ierflg);
   
   //Maximum number of calls
   arglist[0] = 500;
   gMinuit->mnexcm("MIGRAD", arglist,1,ierflg);
   
   
   
   // Print results
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   gMinuit->mnprin(3,amin);
   

  //Get the final fit parameters
  for (n=0 ; n<NPAR ; n++)
    {
      Double_t parameter, erro ;
      gMinuit->GetParameter(n,parameter,erro) ;
      fpar[n] = parameter ;
    }
  
  cout << " The final scaling  values are: Pythia= "<< fpar[0] << " , Pompyt= " << fpar[1] << endl;

  Hpythia->Scale(fpar[0]); 
  Hpom->Scale(fpar[1]); 

  Float_t SD_frac = (Hpom->Integral())/Hdata->Integral();

  //  Float_t NSD_events = fpar[0]*Hpythia->Integral();
  // Float_t Data_events = Hdata->Integral();

  cout << "number of Pompyt: " << Hpom->Integral() << " Number of Data " << Hdata->Integral() << " The fraction of SD events is = " << SD_frac << endl;


  MyC->cd(1);

  Hdata->SetMarkerColor(2);
  Hdata->GetXaxis()->SetTitle("Min(EE-,EE+) Energy [GeV] ");
  Hdata->GetYaxis()->SetTitle("Entries");
  Hpom->SetLineColor(4);
  Hpythia->SetLineColor(6);
  Hpom->SetLineStyle(2);
  Hpythia->SetLineStyle(2);
   
  Float_t DMax = 1.2*Hdata->GetMaximum();

  Hdata->SetMaximum(DMax);
  Hdata->Draw("e");

  Hpythia->Draw("SAMES");
  Hpom->Draw("SAMES");
  
  HSum->Add(Hpythia);
  HSum->Add(Hpom);
  HSum->SetLineColor(1);
  HSum->SetLineStyle(1);
  HSum->Draw("SAMES");
  return;
}




void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)

{
  // computes Chi^2
  // &npar = number of parameters 
  // *gin  = ? , not used here
  // &f = returns the chisq^2 value in this variable
  // *par = the array of parameters
  // iflag = ? , not used here
  //const Int_t nbins = 5;
   Int_t i;


// calculate chisquare
   Double_t chisq = 0;
   Double_t delta = 0;
   Double_t num;
   Double_t den;


   for (i=0;i<hnbin; i++) {
     //     cout << " for i = " << i << " Pcdata = " << Pcdata[i] << endl;
     num = (Pcdata[i]-par[0]*Pcpythia[i]-par[1]*Pcpompyt[i]);
     den = Pedata[i]*Pedata[i] + Pepythia[i]*Pepythia[i] + Pepompyt[i]* Pepompyt[i] ;
     if (den != 0)  delta  = num*num/den;
     chisq += delta;
     //     cout << "num^2, den^2 = " << num*num << " , " << den << " and chisq, i = " << chisq << " , " << i << endl;

   }
   f = chisq;
   //   cout << " f = "<< f << " with Par = " << par[0] << " , " << par[1] << endl;
}

