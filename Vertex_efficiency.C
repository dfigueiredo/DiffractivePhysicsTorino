#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <TMath.h>
#include <TLegend.h>
#include "string.h"
#include <iomanip>
#include "NCutil.C"

void Read_file(){

TFile *f =TFile::Open("PytD6T_vertex_z.root"); 
TH1F *z_dist =   (TH1F*)f->Get("z_dist");
 z_dist->Draw();
 return;
}

Float_t RandomVtx(){

  return z_dist->GetRandom();
}

void Efficiency(){

  Int_t SeenVtx1=0;
  Int_t SeenVtx2=0;
  Int_t SeenVtx3=0;
  Int_t SeenVtx4=0;
  Int_t SeenVtx5=0;
  Int_t SeenVtx6=0;
  Int_t SeenVtx7=0;
  Int_t FakeVtx31=0;
  Int_t FakeVtx32=0;
  Int_t FakeVtx41=0;
  Int_t FakeVtx42=0;
  Int_t FakeVtx43=0;
  Int_t FakeVtx54=0;
  Int_t FakeVtx65=0;
  Int_t FakeVtx76=0;
  Float_t vtx[7];
  Float_t Eff_Fakevtx31=0;
  Float_t Eff_Fakevtx32=0;
  Float_t Eff_Fakevtx43=0;
  Float_t Eff_Fakevtx42=0;
  Float_t Eff_Fakevtx54=0;
  Float_t Eff_Fakevtx65=0;
  Float_t Eff_Fakevtx76=0;
  Float_t Eff_vtx1;
  Float_t Eff_vtx2;
  Float_t Eff_vtx3;
  Float_t Eff_vtx4;
  Float_t Eff_vtx5;
  Float_t Eff_vtx6;
  Float_t Eff_vtx7;
  Float_t Seen;
  Float_t FakeVtx53;
  Float_t FakeVtx64;

  Float_t Limit= 0.3;
  Float_t draw = 100000.;
  for (Int_t i=1; i<=draw;i++){

    vtx[0] =z_dist->GetRandom();    
    vtx[1] =z_dist->GetRandom();
    vtx[2] =z_dist->GetRandom();
    vtx[3] =z_dist->GetRandom();
    vtx[4] =z_dist->GetRandom();
    vtx[5] =z_dist->GetRandom();
    vtx[6] =z_dist->GetRandom();

    //    cout << vtx1 << " "<< vtx2 << " "<< fabs(vtx1-vtx2) << endl; 

    // Second vertex

    if (fabs(vtx[1]-vtx[0])>Limit) SeenVtx2++;

    //Third vertex

    if (fabs(vtx[2]-vtx[0])>Limit && fabs(vtx[2]-vtx[1])>Limit) SeenVtx3++;

    if ((fabs(vtx[2]-vtx[0])>Limit && fabs(vtx[2]-vtx[1])<Limit) ||
	(fabs(vtx[2]-vtx[0])<Limit && fabs(vtx[2]-vtx[1])>Limit)) FakeVtx32++;

    if (fabs(vtx[2]-vtx[0])<Limit && fabs(vtx[2]-vtx[1])<Limit)  FakeVtx31++;


    //Forth vertex


    Seen = 1;
    if (fabs(vtx[3]-vtx[0])>Limit) Seen++;
    if (fabs(vtx[3]-vtx[1])>Limit) Seen++;
    if (fabs(vtx[3]-vtx[2])>Limit) Seen++;
    if (Seen == 4) SeenVtx4++;
    if (Seen == 3) FakeVtx43++;
    if (Seen == 2) FakeVtx42++;



    //Fifth vertex

    Seen = 1;
    if (fabs(vtx[4]-vtx[0])>Limit) Seen++;
    if (fabs(vtx[4]-vtx[1])>Limit) Seen++;
    if (fabs(vtx[4]-vtx[2])>Limit) Seen++;
    if (fabs(vtx[4]-vtx[3])>Limit) Seen++;
    if (Seen == 5) SeenVtx5++;
    if (Seen == 4) FakeVtx54++;
    if (Seen == 3) FakeVtx53++;


    //Sixth vertex

    Seen = 1;
    if (fabs(vtx[5]-vtx[0])>Limit) Seen++;
    if (fabs(vtx[5]-vtx[1])>Limit) Seen++;
    if (fabs(vtx[5]-vtx[2])>Limit) Seen++;
    if (fabs(vtx[5]-vtx[3])>Limit) Seen++;
    if (fabs(vtx[5]-vtx[4])>Limit) Seen++;
    if (Seen == 6) SeenVtx6++;
    if (Seen == 5) FakeVtx65++;
    if (Seen == 4) FakeVtx64++;

    //Seventh vertex

    Seen = 1;
    if (fabs(vtx[6]-vtx[0])>Limit) Seen++;
    if (fabs(vtx[6]-vtx[1])>Limit) Seen++;
    if (fabs(vtx[6]-vtx[2])>Limit) Seen++;
    if (fabs(vtx[6]-vtx[3])>Limit) Seen++;
    if (fabs(vtx[6]-vtx[4])>Limit) Seen++;
    if (fabs(vtx[6]-vtx[5])>Limit) Seen++;
    if (Seen == 7) SeenVtx7++;
    if (Seen == 6) FakeVtx76++;

  }
  Eff_vtx2 = SeenVtx2/draw;
  Eff_vtx3 = SeenVtx3/draw;
  Eff_vtx4 = SeenVtx4/draw;
  Eff_vtx5 = SeenVtx5/draw;
  Eff_vtx6 = SeenVtx6/draw;
  Eff_vtx7 = SeenVtx7/draw;

  Eff_Fakevtx32 = FakeVtx32/draw;
  Eff_Fakevtx31 = FakeVtx31/draw;
  Eff_Fakevtx43 = FakeVtx43/draw;
  Eff_Fakevtx42 = FakeVtx42/draw;
  Eff_Fakevtx54 = FakeVtx54/draw;
  Eff_Fakevtx65 = FakeVtx65/draw;
  Eff_Fakevtx76 = FakeVtx76/draw;
  

  cout << "Limit for overlapping vertexes = "<< Limit << " cm"<< endl;
  cout << "Efficiency of seeing the 2nd vertex = "<< Eff_vtx2 << endl;
  cout << "Efficiency of seeing the 3rd vertex = "<< Eff_vtx3 << endl;
  cout << "Efficiency of seeing the 4th vertex = "<< Eff_vtx4 << endl;
  cout << "Efficiency of seeing the 5th vertex = "<< Eff_vtx5 << endl;
  cout << "Efficiency of seeing the 6th vertex = "<< Eff_vtx6 << endl;
  cout << "Efficiency of seeing the 7th vertex = "<< Eff_vtx7 << endl;

  cout << " 2 vtx that looks 1 vtx = "<< 1. - Eff_vtx2 << endl;
  cout << " 3 vtx that looks 2 vtx = "<< Eff_Fakevtx32 << endl;
  cout << " 4 vtx that looks 3 vtx = "<< Eff_Fakevtx43 << endl;
  cout << " 5 vtx that looks 4 vtx = "<< Eff_Fakevtx54 << endl;
  cout << " 6 vtx that looks 5 vtx = "<< Eff_Fakevtx65 << endl;
  cout << " 7 vtx that looks 6 vtx = "<< Eff_Fakevtx76 << endl;

  cout << " 3 vtx that looks 1 vtx = "<< Eff_Fakevtx31 << endl;
  cout << " 4 vtx that looks 2 vtx = "<< Eff_Fakevtx42 << endl;
  }
