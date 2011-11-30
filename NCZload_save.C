#include <iostream>
#include <sstream>

TFile *Pompyt;
TFile *DZeeA;
TFile *DZeeB;
TFile *Pythia;
TFile *Zmm;
TFile *Zee;

void NCZload_save(){

   cout<<"Loading Pythia"<<endl;
    //    Pythia->Close(); 
    Pythia = TFile::Open("files/pythia.root");
    cout<<"Loading DZeeA"<<endl;
    DZeeA = TFile::Open("files/oldfiles/Run2010A_Zee.root");
    cout<<"Loading DZeeB"<<endl;
    DZeeB = TFile::Open("files/oldfiles/Run2010B_Zee.root");
    cout<<"Loading  Pompyt"<< endl;
    Pompyt = TFile::Open("files/DiffractiveMC.root");

   cout<<"Loading  Zmm"<< endl;
   Zmm = TFile::Open("files/ZetaSkim_mm.root");

   cout<<"Loading  Zee"<< endl;
   Zee = TFile::Open("files/ZetaSkim_ee.root");

   //    tree_->SetMarkerStyle(20);
   //  tree_->SetMarkerSize(.5);

    
}
