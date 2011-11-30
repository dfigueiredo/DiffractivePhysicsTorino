TFile *file;
TTree *tree;

if (i==1) {
  file = new TFile("files/ZetaSkim_mm_v1.root");
  tree = (TTree*)gDirectory->Get("tree_");
  fChain = tree;  /* Loop RunB */ 
 }
 else if (i==2){ 
   fChain =tree_Zmm;  /* Loop RunB */ 
 }
