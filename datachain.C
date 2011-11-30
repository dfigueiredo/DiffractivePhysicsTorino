{
  //Why it does not work???? //
  // data.Delete();
  TChain data("tree_");
  data.Add("files/Run2010A_Zmm.root");
  data.Add("files/Run2010B_Zmm.root"); 
  cout << "Files chained in data" << endl ;
  data.GetListOfFiles()->Print() ;
  return();
}
