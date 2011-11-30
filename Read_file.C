#include "Riostream.h"
#include <iostream>
#include <sstream>
#include "tdrstyle.C"
#include "NCutil.C"
void Read_file() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
  TCanvas *pippo = NCanvas(3,2,"pippo");
  TCanvas *ratio = NCanvas(2,3,"ratio");
  TH1F *xi[6];
  TH1F *xit[6];
  TH1F *xi_ra[6];


// TFile *_file0 = TFile::Open("Vertex_MCMB_nTrkPt_EtaCut2.6.root")
  TH1F  *Xi_All =   (TH1F*)_file0->Get("Xi_TrkGenEta2Pt200_P8_CHA");
  xi[0] = NH1clone("xi_sib","xi_sib",Xi_All);
  xi[1] = NH1clone("xi_pho","xi_pho",Xi_All);
  xi[2] = NH1clone("xi_qll","xi_qll",Xi_All);
  xi[3] = NH1clone("xi_qgs","xi_qgs",Xi_All);
  xi[4] = NH1clone("xi_phy","xi_phy",Xi_All);
  xi[5] = NH1clone("xi_epo","xi_epo",Xi_All);

  xi_ra[0] = NH1clone("xi_sib_ra","xi_sib_ra",Xi_All);
  xi_ra[1] = NH1clone("xi_pho_ra","xi_pho_ra",Xi_All);
  xi_ra[2] = NH1clone("xi_qll_ra","xi_qll_ra",Xi_All);
  xi_ra[3] = NH1clone("xi_qgs_ra","xi_qgs_ra",Xi_All);
  xi_ra[4] = NH1clone("xi_phy_ra","xi_phy_ra",Xi_All);
  xi_ra[5] = NH1clone("xi_epo_ra","xi_epo_ra",Xi_All);



  xit[0] = NH1clone("xit_sib","xit_sib",Xi_All);
  xit[1] = NH1clone("xit_pho","xit_pho",Xi_All);
  xit[2] = NH1clone("xit_qll","xit_qll",Xi_All);
  xit[3] = NH1clone("xit_qgs","xit_qgs",Xi_All);
  xit[4] = NH1clone("xit_phy","xit_phy",Xi_All);
  xit[5] = NH1clone("xit_epo","xit_epo",Xi_All);

  Double_t scale = 1./Xi_All->Integral();
  Xi_All->Scale(scale);
  //  Xi_All->Draw();
// read file $ROOTSYS/tutorials/tree/basic.dat
// this file has 3 columns of float data
//   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   //   dir.ReplaceAll("basic.C","");
   //dir.ReplaceAll("/./","/");

   ifstream in[6];
   in[0].open("xsi_CR_models/ppc7his_sib.histo",ifstream::in);
   in[1].open("xsi_CR_models/ppc7his_pho.histo",ifstream::in);
   in[2].open("xsi_CR_models/ppc7his_qII.histo",ifstream::in);
   in[3].open("xsi_CR_models/ppc7his_qgs.histo",ifstream::in);
   in[4].open("xsi_CR_models/ppc7his_pyt.histo",ifstream::in);
   in[5].open("xsi_CR_models/ppc7his_epo.histo",ifstream::in);

   string MCType[6] = {"SYBILL", "PHOJET", "Q-II","QGSJET","PYTHIA","EPOS"};
   char name[256];
   Double_t x,y,z;   

   for (Int_t k = 0;k<6;k++)
     {
       Int_t nlines = 0;
       while (1) 
	 {
	   nlines++;
	   if (nlines <545 || (nlines >= 645 && nlines <= 655 ))      
	     {
	  	   in[k].getline(name,256);
		   //  cout << name << " " << nlines << endl;
	       }

	   if (nlines >=545 && nlines <= 644)
	     {
	       in[k] >> x >> y >> z;
	       // printf("x=%E, y=%8f, z=%8f, nline = %i \n",x,y,z,nlines);
	       Int_t Bin = xit[k]->FindBin(log10(x));
	       xit[k]->SetBinContent(Bin,y);
	     }
	   else if (nlines >=656 && nlines <= 752)
	     {
	       in[k] >> x >> y >> z;
	       // printf("x=%E, y=%8f, z=%8f\n",x,y,z);
	       Int_t Bin = xi[k]->FindBin(log10(x));
	       xi[k]->SetBinContent(Bin,y);
	     }
	   else if (nlines >= 753) break;
	 }
       xi_ra[k]->Add(xi[k]);
       xi_ra[k]->Divide(xit[k]);
       //       xi_ra[k]->Scale(1.);
       pippo->cd(k+1);   
       NLogAxis(0,1);
       printf(" found %d points\n",nlines);
       xit[k]->SetMarkerColor(1);
       xi[k]->SetMarkerColor(k+2);
       NSetTitleSize(xit[k],1.1,1.1,0.06);
       NSetLabelSize(xit[k]);
       xit[k]->SetMinimum(0.0001);
       xit[k]->SetMaximum(0.1);
       xit[k]->Draw("P");
       NText(-7,0.05, MCType[k].c_str(),1,0.06);
       xit[k]->GetXaxis()->SetTitle("log_{10}#xi");
       xit[k]->GetYaxis()->SetTitle("Fraction");
            xi[k]->Draw("SAMEP");
       //       xi[k]->Draw();
       ratio->cd(k+1);   
       xi_ra[k]->Draw("P");
       xi_ra[k]->Fit("pol1","","",-4..,-3.5);
       Float_t a  =  ( 0.5 - pol1->GetParameter(0))/ pol1->GetParameter(1);
       cout << pow(10,a) << endl;
       in[k].close();
     }
   return();
}
