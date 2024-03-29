void copytree3() 
{
  // Example of Root macro to copy a subset of a Tree to a new Tree// Only selected entries are copied to the new Tree.// The input file has been generated by the program in $ROOTSYS/test/Event// with   Event 1000 1 99 1//Author: Rene Brun
  
  //  gSystem->Load("$ROOTSYS/test/libEvent");   
  //Get old file, old tree and set top branch address   
  

  TFile *fA = new TFile("files/zdiff/4_2/DATA_Zee_2011_v2_4.root");
  TDirectory * dirA = (TDirectory*)fA->Get("files/zdiff/4_2/DATA_Zee_2011_v2_4.root:/Selection");
  TTree *oldtree;
  dirA->GetObject("tree_",oldtree);

   
  Int_t nentries = (Int_t)oldtree->GetEntries();   
  //  Event *event   = 0;   
 
 
  //Create a new file + a clone of old tree in new file   
  
  TFile *newfile = new TFile("small.root","recreate");   
  TTree *newtree = oldtree->CloneTree(0);   
  // Long64_t nentries = oldtree->GetEntriesFast();
  
  for (Int_t i=0;i<nentries; i++) 
    {      
      oldtree->GetEntry(i);     
      if (oldtree->numberOfVertexes < 4 ) newtree->Fill();      
      //      event->Clear();   
    }   
  newtree->Print();   
  newtree->AutoSave();   
  delete oldfile;   
  delete newfile;
}
