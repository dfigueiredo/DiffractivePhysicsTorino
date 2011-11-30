#define fill_minEE_class_cxx
#include "fill_minEE_class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <sstream>
#include <istream>
#include <string>
#include <math.h>
#include "NCutil.C"

const Int_t NPAR   = 2;  /* number of Hystograms = ngauss * 3 */
const Int_t hnbin = 50;  /* number of bins */


// Put everything in arrays
  
Float_t *Pcpompyt = new Float_t [hnbin];
Float_t *Pepompyt = new Float_t [hnbin];
Float_t *Pcdata = new  Float_t [hnbin];
Float_t *Pedata  = new Float_t [hnbin];
Float_t *Pcpythia = new Float_t [hnbin];
Float_t *Pepythia = new Float_t [hnbin];


void fill_minEE_class::Loop()
{


   TFile *fpyt = new TFile("files/pythiaD6T_ee_v1.root");
   TTree *tree_pyt = (TTree*)gDirectory->Get("tree_");


   //   TFile *fpom = (TFile*)gROOT->GetListOfFiles()->FindObject("files/DiffractiveMC.root");
   TFile *fpom = new TFile("files/DiffractiveMC_ee_v1.root");
   TTree *tree_pom = (TTree*)gDirectory->Get("tree_");

   //   TFile *fzee = (TFile*)gROOT->GetListOfFiles()->FindObject("files/ZetaSkim_ee.root");
   TFile *fzee = new TFile("files/ZetaSkim_ee_v1.root");
   //   TFile *fzee = new TFile("files/ZetaSkim_mm.root");
   TTree *tree_zee = (TTree*)gDirectory->Get("tree_");



   //   Int_t hnbin = 25;
   Float_t llow = 0.;
   Float_t lup = 250.;
   TH1F *Hpompyt = new TH1F("Hpompyt", "pompyt", hnbin, llow, lup);
   TH1F *Hpythia = new TH1F("Hpythia", "pythia", hnbin, llow, lup);
   TH1F *Hdata = new TH1F("Hdata", "data", hnbin, llow, lup);
   TH1F *HSum = new TH1F("HSum", "HSum", hnbin, llow, lup);

   NCanvas(1,1);
   //Go to  Pythia

   fChain =tree_pyt;
   Init(fChain);


   Long64_t nentries = fChain->GetEntriesFast();   
   cout << "number of entries in Pythia = " << nentries << endl; 
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;     
     if (numberOfVertexes == 1){
     Hpythia->Fill(TMath::Min(energyTot_PF_EE_minus,energyTot_PF_EE_plus));
     }
   }


   // go to Pompyt

   fChain = tree_pom;
   Init(fChain);
   nentries = fChain->GetEntriesFast();
   cout << "number of entries in Pompyt = " << nentries << endl; 
   
   nbytes = 0, nb = 0;
   for (jentry=0; jentry<nentries;jentry++) {
     ientry = LoadTree(jentry);
     if (ientry < 0) break;
     
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;
     if (numberOfVertexes == 1){
       Hpompyt->Fill(TMath::Min(energyTot_PF_EE_minus,energyTot_PF_EE_plus));
     }
   }
   
   
   // go to  Zee

   fChain = tree_zee;
   Init(fChain);
   nentries = fChain->GetEntriesFast();
   cout << "number of entries in Zee = " << nentries << endl; 
   nbytes = 0, nb = 0;
   for (jentry=0; jentry<nentries;jentry++) {
     ientry = LoadTree(jentry);
     if (ientry < 0) break;
     
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;
     //      Zee->cd();
     if (numberOfVertexes == 1){
     Hdata->Fill(TMath::Min(energyTot_PF_EE_minus,energyTot_PF_EE_plus));
     }
   }
     


   // Show the results

   MyC->cd(1);

   Hpythia->Draw();
   Hpompyt->Draw("SAMES");
   Hdata->Draw("SAMES");
   


  //  cout << Pcdata->lenght() << endl;

  NHtoV(Hdata, Pcdata, Pedata);
  NHtoV(Hpompyt, Pcpompyt, Pepompyt);
  NHtoV(Hpythia, Pcpythia, Pepythia);


 cout << " the content of data[2] is = " << Pcdata[2] << "+-"<<Pedata[2] << endl ;
 cout << " the content of pythia[2] is = " << Pcpythia[2] << "+-"<<Pepythia[2] << endl ;
 cout << " the content of pythia[2] is = " << Pcpompyt[2] << "+-"<<Pepompyt[2] << endl ;


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
  par[1] = 0.05*Hdata->Integral()/Hpompyt->Integral();


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
  
  cout << " The final parameter values are: "<< fpar[0] << " , " << fpar[1] << endl;

  Float_t SD_frac = (fpar[1]*Hpompyt->Integral())/Hdata->Integral();
  //  Float_t NSD_events = fpar[0]*Hpythia->Integral();
  // Float_t Data_events = Hdata->Integral();

  cout << " The fraction of SD events is = " << SD_frac << endl;


  // }
  // void fill_minEE_class::show(){


  //Show the final plot

  MyC->cd(1);

  Hpythia->Scale(fpar[0]); 
  Hpompyt->Scale(fpar[1]); 

  Hdata->SetMarkerColor(2);
  Hdata->GetXaxis()->SetTitle("Min(EE-,EE+) Energy [GeV] ");
  Hdata->GetYaxis()->SetTitle("Entries");
  Hpompyt->SetLineColor(4);
  Hpythia->SetLineColor(6);
  Hpompyt->SetLineStyle(2);
  Hpythia->SetLineStyle(2);
   
  Float_t DMax = 1.2*Hdata->GetMaximum();
  Hdata->SetMaximum(DMax);
  Hdata->Draw("p");

  Hpythia->Draw("SAMES");
  Hpompyt->Draw("SAMES");
  
  HSum->Add(Hpythia);
  HSum->Add(Hpompyt);
  HSum->SetLineColor(1);
  HSum->SetLineStyle(1);
  HSum->Draw("SAMES");

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
   cout << " f = "<< f << " with Par = " << par[0] << " , " << par[1] << endl;
}
