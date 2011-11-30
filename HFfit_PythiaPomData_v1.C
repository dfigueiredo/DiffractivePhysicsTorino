// .L HFfit_PythiaPomData_v1.C
// HFfit_PythiaPomData_v1() 

#define EEfit_PythiaPomData_v1_Class_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <sstream>
#include <istream>
#include <string>
#include <math.h>
#include <TFile.h>
#include "NCutil.C"

const Int_t NPAR   = 2;  /* number of Hystograms = ngauss * 3 */


// Put everything in arrays
  
Float_t *Pcpompyt;
Float_t *Pepompyt;
Float_t *Pcdata;
Float_t *Pedata;
Float_t *Pcpythia;
Float_t *Pepythia;


void HFfit_PythiaPomData_v1()
{
  TFile *f =TFile::Open("Ghosts_Removal_Class_files.root"); 
  TH1F *PytD6T_HF =  (TH1F*)f->Get("PytD6T_HF");
  TH1F *PytZ2_HF =  (TH1F*)f->Get("PytZ2_HF");
  TH1F *Dat_HF =  (TH1F*)f->Get("Dat_HF");
  TH1F *Dat_HF_NoGhosts =  (TH1F*)f->Get("Dat_HF_NoGhosts");
  TH1F *Dat_HF_Cor =  (TH1F*)f->Get("Dat_HF_Cor");
  TH1F *Hpompyt =  (TH1F*)f->Get("Pom_HF");

  //Here pick which histo we want to fit

  Int_t l = 4;
  if (l==1) {
    TH1F *Hpythia = PytD6T_HF;
    TH1F *Hdata = Dat_HF;
    cout << "Using  PytD6T_HF and Dat_HF"<< endl;
  }
  else if (l==2) {
    TH1F *Hpythia = PytD6T_HF;
    TH1F *Hdata = Dat_HF_NoGhosts;
    cout << "Using  PytD6T_HF and Dat_HF_NoGhosts"<< endl;
  }
  else if (l==3) {
    TH1F *Hpythia = PytZ2_HF;
    TH1F *Hdata = Dat_HF_NoGhosts;
    cout << "Using  PytZ2_HF and Dat_HF_NoGhosts"<< endl;
  }
  else if (l==4) {
    TH1F *Hpythia = PytZ2_HF;
    TH1F *Hdata = Dat_HF_Cor;
    cout << "Using  PytZ2_HF and Dat_HF_Cor"<< endl;
  }
  else if (l==5) {
    TH1F *Hpythia = PytD6T_HF;
    TH1F *Hdata = Dat_HF_Cor;
    cout << "Using  PytZ2_HF and Dat_HF_Cor"<< endl;
  }


  TH1F *HSum =NH1clone("HSum","Hsum",Hpompyt);

  Int_t hnbin = Hpompyt->GetNbinsX();  /* number of bins */

  Pcpompyt = new Float_t [hnbin];
  Pepompyt = new Float_t [hnbin];
  Pcdata = new  Float_t [hnbin];
  Pedata  = new Float_t [hnbin];
  Pcpythia = new Float_t [hnbin];
  Pepythia = new Float_t [hnbin];


  //  cout << Pcdata->lenght() << endl;

  NHtoV(Hdata, Pcdata, Pedata);
  NHtoV(Hpompyt, Pcpompyt, Pepompyt);
  NHtoV(Hpythia, Pcpythia, Pepythia);


 cout << " the content of data[2] is = " << Pcdata[2] << "+-"<<Pedata[2] << endl ;
 cout << " the content of pythia[2] is = " << Pcpythia[2] << "+-"<<Pepythia[2] << endl ;
 cout << " the content of Pompyt[2] is = " << Pcpompyt[2] << "+-"<<Pepompyt[2] << endl ;


 // Here  we go: the minuit show
 
  TMinuit *gMinuit = new TMinuit(NPAR);  //initialize TMinuit with a maximum of NPAR params
  Int_t iflag = hnbin;
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

  //Scan on parameter = 2
  arglist[0] = 2;
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

  NCanvas(1,1);
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

  Hpythia->Draw("SAMEHIST");
  Hpompyt->Draw("SAMEHIST");
  
  HSum->Add(Hpythia);
  HSum->Add(Hpompyt);
  HSum->SetLineColor(1);
  HSum->SetLineStyle(1);
  HSum->Draw("SAMESHIST");
  gPad->SetLogy(0);
  gPad->SetLogx(1);
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

   Int_t hnbin =6;  /* number of bins, To be made automatic */
   cout << "hnbin = "<< hnbin << endl;
   for (i=0;i<hnbin; i++) {
     //     cout << " for i = " << i << " Pcdata = " << Pcdata[i] << endl;
     num = (Pcdata[i]-par[0]*Pcpythia[i]-par[1]*Pcpompyt[i]);
     den = Pedata[i]*Pedata[i] + Pepythia[i]*Pepythia[i] + Pepompyt[i]* Pepompyt[i] ;
     if (den != 0)  delta  = num*num/den;
     chisq += delta;
     //     cout << "num^2, den^2 = " << num*num << " , " << den << " and chisq, i = " << chisq << " , " << i << endl;

   }
   f = chisq;
   // cout << " f = "<< f << " with Par = " << par[0] << " , " << par[1] << endl;
}
