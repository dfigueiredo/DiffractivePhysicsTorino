#include <iostream>
#include <sstream>

TFile *Pythia; 
TFile *DZeeA; 
TFile *DZeeB ;
TFile *Pompyt;
//TFile *Zee;
//TFile *Zmm;




struct rootpla{ 
  TFile* label; 
  TString file; 
}; 

void NCZload(){

  const int nfiles = 6;
  rootpla zanalysis;

  TString ntupleDir = "files";
  zanalysis.file = "pythia.root";
  //  zanalysis.label =  DZeeB;

  TString filename= TString::Format("%s/%s",ntupleDir.Data(),zanalysis.file.Data());
  zanalysis.label = TFile::Open(filename.Data());

  cout << filename << " and " << zanalysis.label << endl ;
  zanalysis.label->cd();


  /*

  TString labels[nfiles]= {
    "pythia.root",
    "oldfiles/Run2010A_Zee.root",    
    "oldfiles/Run2010B_Zee.root",
    "DiffractiveMC.root",
    "ZetaSkim_ee.root",
    "ZetaSkim_mm.root"};

  TFile *pippo[nfiles];
  TFile *labels[nfiles]; 
    "Pythia",
    "DZeeA",
    "DZeeB",
    "Pompyt"
    "Zee",
    "Zmm",
  };

  TString fileName;


  for(int ifile=0;ifile<nfiles;ifile++) {
TString::Format("%s/%s",ntupleDir.Data(),labels[ifile].Data());
    cout << " loading File  = " << fileName.Data() <<endl;
    labels[ifile] = TFile::Open(fileName.Data());
  }     
 
  //    tree_->SetMarkerStyle(20);
  // tree_->SetMarkerSize(.5);

  */

  return();
}
