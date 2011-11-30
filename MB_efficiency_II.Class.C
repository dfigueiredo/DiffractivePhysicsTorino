#define MB_efficiency_II.Class_cxx
#include "MB_efficiency_II.Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "string.h"
#include <sstream>
#include <iomanip>
#include <TRandom.h>
#include "NCutil.C"

const Int_t NDIR   = 1;  /* number or Directories*/
Int_t Ntracks_eta;
TH1F *TracksEta;

void MB_efficiency_II.Class::Loop()
{
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  // for (Long64_t jentry=0; jentry<nentries;jentry++) {
  for (Long64_t jentry=0; jentry<100;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    
    cout << numberoOfTracks_gen <<endl;
    
  } //Jentry
} // Loop
