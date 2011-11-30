{

  gSystem->Load("DiffAnalysis_C.so");

  DiffAnalysis t;

  TFile* outFile = new TFile("NC.root","RECREATE");

  t->_outF = outFile;
  t->_cutEnergy = 0.0;
  t->Loop();

}
