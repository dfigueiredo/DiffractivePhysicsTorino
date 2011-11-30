#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "string.h"
#include <iomanip>
#include <sstream>
#include "NCutil.C"
#include <iostream>
#include <fstream>
#include <string>
#include "tdrstyle.C"
#include <TLatex.h>

#include "TMath.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TVirtualFitter.h"
#include "TROOT.h"

TH1F *data;
TFile *f;
TH1F *trial;
TH1F *diff;
TH1F *HSigma;
TH1F *Sigma2;
TH1F *SigmaX;
TH1F *Sigma3;

void ReadHisto(Int_t choose=1)
{
  if (choose == 1 || choose ==2) // open the plot you want  
    {
      f = TFile::Open("files/histograms_data_May9_152.1pb_EBEB.root");  
	if (choose == 1) data =   (TH1F*)f->Get("h_Diphoton_Minv_low");
	if (choose == 2) data =   (TH1F*)f->Get("h_Diphoton_Minv_low_bin1GeV");
    }
  else if (choose == 3)
    {
      f = TFile::Open("files/histograms_data_137pb_ESfix.root");  
     data =   (TH1F*)f->Get("h_Diphoton_Minv_low");
    }
  else if (choose == 4)
    {
      f = TFile::Open("files/histograms_data_new_38.3pb_EBEB_new.root");  
     data =   (TH1F*)f->Get("h_Diphoton_Minv_low");
    }

  else if (choose == 5)
    {
      f = TFile::Open("files/histograms_data_May13_190.4pb_EBEB_new.root");  
     data =   (TH1F*)f->Get("h_Diphoton_Minv_low");
    }

}

void StatTest(Float_t trials=1000.)
{
  
  char hname[100]; 
  
  // 3 sigma limits: 2, 3 and x
  Float_t   Lim2 = 2;
  Float_t   Lim3 = 3;
  Float_t   LimX = 3.8;

  Float_t    TrialEntry;
  Float_t    TrialEntryEr;
  Float_t    DataEntry;
  Float_t    Delta;
  Float_t    MaxDelta;

  Int_t NBin = data->GetNbinsX();



  cout << " Running on histo : "<< data->GetTitle() << endl;

  TH1F *trial =  NHclone("trial","trial",data);
  HSigma = new TH1F("HSigma","HSigma",100,-5.,5);
  Sigma2 = new TH1F("Sigma2","Sigma2",10,0.,10);
  SigmaX = new TH1F("SigmaX","SigmaX",10,0.,10);
  Sigma3 = new TH1F("Sigma3","Sigma3",10,0.,10);
  Sigma3->SetStats(0);
  Sigma2->Sumw2();
  SigmaX->Sumw2();
  Sigma3->Sumw2();

  
        
  // Select the mass interval, now 110-150 GeV

  Int_t LowBin = data->FindBin(110);
  Int_t HighBin = data->FindBin(150);
  Int_t  NEntry = data->Integral(LowBin,HighBin);
  Int_t  AllEntry = 1.02*data->Integral();
  Int_t NBin =  HighBin-LowBin;
  cout << "There are " << NBin << " bins in the Mass range  110 - 150 with  "<< NEntry<< " Entries" << endl;
  //  char txt[100]= "The number of entries in the data file is %i";
  // sprintf(txt,txt,NEntry);
  // cout << txt <<endl;

  for (Int_t j=LowBin;j<=HighBin;j++) // Estimate how many bins are high
	{
	  if (data->GetBinError(j)>0)
	    {
	      Float_t Av = (data->GetBinContent(j-2)+data->GetBinContent(j-1)+data->GetBinContent(j+1)+data->GetBinContent(j+2))/4;
	      Delta = (data->GetBinContent(j)-Av)/
		//sqrt(Av);
		sqrt(data->GetBinContent(j));
	      if (Delta>1.) cout << "# of sigmas = " << Delta << " Mass = " << data->GetBinLowEdge(j) << " GeV" <<  endl;

	    }
	}


  // here it's the real loop

  Int_t BinCont;
  for (Int_t k = 0; k<trials;k++)
    {
      
      
      //     for (Int_t i=LowBin;i<=HighBin;i++)
      //	{
        
      //  BinCont = gRandom->Poisson(data->GetBinContent(i));
      //  trial->SetBinContent(i,BinCont);
      //	}
      
      
      trial->Reset();
      trial->FillRandom(data,AllEntry);
      // trial->Draw();
      //      return;
      Int_t N2Sig = 0;
      Int_t NXSig = 0;
      Int_t N3Sig = 0;
      MaxDelta = 0;
      for (Int_t j=LowBin;j<=HighBin;j++)
	{
	  
	  TrialEntry = trial->GetBinContent(j);
	  //	  TrialEntryEr = trial->GetBinError(j);
	  TrialEntryEr = data->GetBinError(j);
	  // TrialEntryEr = sqrt(TrialEntry);
	  
	  DataEntry = data->GetBinContent(j);
	  Delta =0;
	  // cout << TrialEntry << " " << TrialEntryEr << " " << DataEntry << endl;
	  if (TrialEntryEr>0) Delta =1.*(TrialEntry - DataEntry)/(TrialEntryEr);
	  if (Delta>MaxDelta) MaxDelta = Delta;
	  // cout << "delta = " << Delta << endl;
	  
	  if (Delta>=Lim2) N2Sig++;
	  if (Delta>=LimX) NXSig++;
	  if (Delta>=Lim3) N3Sig++;
	}
      
      //      gDirectory->Delete("trial");
      
      HSigma->Fill(Delta);

      Sigma2->Fill(N2Sig);
      SigmaX->Fill(NXSig);
      Sigma3->Fill(N3Sig);


    } //trial loop
  

  TCanvas *Result = NCanvas(1,2,"Result");
  Result->cd(1);
  gPad->SetLogy(1);
  HSigma->Draw();

  Result->cd(2);

  NHArea1(Sigma2);
  NHArea1(SigmaX);
  NHArea1(Sigma3);
  Sigma3->SetMinimum(0.001);
  Sigma3->Draw("HIST");
  Sigma2->SetLineColor(2);
  Sigma2->SetLineStyle(2);
  Sigma2->Draw("SAMEHIST");

  SigmaX->SetLineColor(4);
  SigmaX->SetLineStyle(4);
  SigmaX->Draw("SAMEHIST");
  gPad->SetLogy(1);
  sprintf(hname,"Number of bins with an excess of %i, %3.2f or %i sigma",Lim2, LimX, Lim3 );
  Sigma3->GetXaxis()->SetTitle(hname);
  Sigma3->GetYaxis()->SetTitle("Fraction");
  TLegend *leg = new TLegend(0.5,0.6, 0.7 ,0.8);
  //  leg->SetfMargin(0.1);
  //  leg->SetTextSize(14);
  sprintf(hname,"%i Sigma bins ",Lim2 );
  leg->AddEntry(Sigma2,hname,"L");  
  sprintf(hname,"%3.2f Sigma bins ",LimX );
  leg->AddEntry(SigmaX,hname,"L");  
  sprintf(hname,"%i Sigma bins ",Lim3 );
  leg->AddEntry(Sigma3,hname,"L");  

  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);  
  leg->Draw();
  Sigma3->SetTitle();
 
  Float_t  prob = SigmaX->GetBinContent(2);
  Float_t  prober = SigmaX->GetBinError(2);
  char txt[100]= "Fraction of trials with at least 1 bin with an excess of %3.2f sigma is %3.4f +- %3.4f";
  sprintf(txt,txt,LimX,prob,prober);
  cout << txt <<endl;
  TLatex l;
  l.SetTextSize(0.04);
  l.DrawLatex(1.5,Sigma3->GetMaximum(),txt);

}


TH1F* NHclone (TString name_new, TString title_new, TH1F* histo_old )
{
  
  TH1F* histo_new =  (TH1F*) histo_old->Clone(); 
  histo_new->SetTitle(title_new); 
  histo_new->SetName(name_new); 
  histo_new->Reset();
  return histo_new;
}

void NHArea1(TH1F *file1)
{ 
  Int_t Max1 = file1->Integral();
  if(Max1>0.)  file1->Scale(1./Max1);
  return;
}
