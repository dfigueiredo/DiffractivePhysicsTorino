#include "th1fmorph.C"
// #include "morphData.C"


void interpolate3( int mass1=110, int mass2=120, int mass=115, int cat=0, const char * filename="CMS-HGG.root",const char * outfile="out.root")
{

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gSystem->Load("libRooFit.so");


  TDatime today;
  std::cout << "Time Begin " <<   today.GetTime() << std::endl;

  // open files
  TFile * fin = new TFile(filename,"READONLY");

  ///////

  // grab the workspace


  // RooWorkspace * w = (RooWorkspace*)fin->Get("cms_hgg_workspace");

  // grab the unbinned data
  char hname1[300];
  char hname2[300];
  char hname3[300];


  sprintf(hname1,"sig_mass_m%i_cat%i",mass1,0);
  sprintf(hname2,"sig_mass_m%i_cat%i",mass2,0);
  sprintf(hname3,"sig_mass_m%i_cat%i",mass,0);
  //
  //RooDataSet * data1 = w->data(hname1);
  //RooDataSet * data2 = w->data(hname2);
  //RooDataSet * data3 = w->data(hname3);

  // RooRealVar * m = w->var("mass");
  //  m->setBins(100) ;
  //  m->setRange(100,200) ;

  //  RooDataHist* h1= new RooDataHist("h1","h1",RooArgSet(*m),*data1); 
  //  RooDataHist* h2= new RooDataHist("h2","h2",RooArgSet(*m),*data2); 
  //  RooDataHist* h3= new RooDataHist("h3","h3",RooArgSet(*m),*data3); 
  
  TH1F* h1 = data1->createHistogram("mass",100);
  TH1F* h2 = data2->createHistogram("mass",100);
  TH1F* h3 = data3->createHistogram("mass",100);

  //  RooPlot * frame = m->frame();  
  //  h1->plotOn(frame);
  //  h2->plotOn(frame);
  //  h3->plotOn(frame,RooFit::LineColor(kRed),RooFit::MarkerColor(kRed),RooFit::LineStyle(kSolid)) ;

  //  data1->plotOn(frame);
  //  data2->plotOn(frame);
  //  data3->plotOn(frame,RooFit::LineColor(kRed),RooFit::MarkerColor(kRed),RooFit::LineStyle(kSolid));

  //  frame->Draw();
  //  c1->Print("minv_binned.png");

  //  h3->SetLineColor(kGreen);

  //  h1->Draw("hist");
  //  h2->Draw("histsame");
  //  h3->Draw("histsame");
  //  return;


  ///////
  ////
  sprintf(hname1,"th1f_sig_mass_m%i_cat%i",mass1,cat);
  sprintf(hname2,"th1f_sig_mass_m%i_cat%i",mass2,cat);
  sprintf(hname3,"th1f_sig_mass_m%i_cat%i",mass,cat);    

  TH1F * hist1 = (TH1F*)fin->Get(hname1);
  TH1F * hist2 = (TH1F*)fin->Get(hname2);
  TH1F * histActual = (TH1F*)fin->Get(hname3);

  TH1F* hist = th1fmorph("hist","morph", hist1, hist2, mass1, mass2, mass);

  float alpha = 1.0*(mass-mass1)/(mass2-mass1);
  float scaleHist = hist1->Integral() + alpha * (hist2->Integral() - hist1->Integral());

  cout << endl;
  cout << "alpha & scale : " << alpha << " " << scaleHist << endl;
  
  // try also BR scaling

  float xsec1=1.0;
  float br1=1.0;
  float xsec2=1.0;
  float br2=1.0;
  float xsec=1.0;
  float br=1.0;

  if (mass==115) {
    xsec = 20.7379;
    br   = 0.00213;
  } else if (mass==120) {
    xsec = 19.0125;
    br   = 0.00225;
  } else if (mass==130) {
    xsec = 16.1292;
    br   = 0.00226;
  } 

  if (mass1==110) {
    xsec1 = 22.7112;
    br1   = 0.00197;
  } else if (mass1==115) {
    xsec1 = 20.7379;
    br1   = 0.00213;
  } else if (mass1==120) {
    xsec1 = 19.0125;
    br1   = 0.00225;
  } 

  if (mass2==120) {
    xsec2 = 19.0125;
    br2   = 0.00225;
  } else if (mass2==130) {
    xsec2 = 16.1292;
    br2   = 0.00226;
  } else if (mass2=140) {
    xsec2=13.8456;
    br2=0.00193;
  }


  cout << endl;
  cout << "mass " << mass << " " << mass1 << " " << mass2 << endl;
  cout << "xsec " << xsec << " " << xsec1 << " " << xsec2 << endl;
  cout << "br " << br << " " << br1 << " " << br2 << endl;
  cout << "integral " << hist->Integral() << " " << hist1->Integral() << " " << hist2->Integral() << endl;

  cout << "integral/(xsec*br) " << hist->Integral()/(xsec*br) << " " << hist1->Integral()/(xsec1*br1) << " " << hist2->Integral()/(xsec2*br2) << endl;
  cout << endl;
  cout << "alpha * " << endl;

  float effAcc1 = hist1->Integral()/(xsec1*br1)/(xsec1*br1);
  float effAcc2 = hist2->Integral()/(xsec2*br2)/(xsec1*br1);

  float scaleHistBR = (xsec*br)*(xsec*br)*(effAcc1 + alpha * (effAcc2 - effAcc1));

  //  h1->SetMaximum(1.1*TMath::Max(h1->GetMaximum(),h2->GetMaximum()));
  //  hist1->SetLineColor(kRed);
  //  hist1->Draw();
  
  //  hist2->SetLineColor(kBlue);
  //  hist2->Draw("same");
  
  hist->SetLineColor(kGreen);
  hist->SetLineWidth(2);
  //  hist->Draw();
  

  histActual->GetXaxis()->SetRangeUser( mass1-10.0, mass2+10.0 ) ;
  histActual->SetLineColor(2);
  histActual->SetLineWidth(2);
  cout << histActual->GetMaximum() << " " << hist->GetMaximum() << endl;
  histActual->Draw();

  //  scaleHist = histActual->Integral()/hist->Integral();
  TH1F* histBR = (TH1F*)hist->Clone();

  hist->Scale(scaleHist);
  hist->Draw("same");

  histBR->Scale(scaleHistBR);
  histBR->SetLineColor(kCyan+1);
  histBR->Draw("same");

  histActual->SetMaximum(1.1*TMath::Max(histActual->GetMaximum(),hist->GetMaximum()));
  histActual->SetTitle(Form("Interpolate between %i and %i for %i cat%i",mass1,mass2,mass,cat));


  TLegend *leg = new TLegend(0.6522989,0.6800847,0.8534483,0.8580508,NULL,"brNDC");
  leg->SetBorderSize(1);
  leg->SetTextFont(62);
  leg->SetTextSize(0.03225806);
  leg->SetLineColor(0);
  leg->SetFillColor(0);
  leg->AddEntry(histActual,"MC");
  leg->AddEntry(histBR,"scale by xsec*BR");
  leg->AddEntry(hist,"scale by yield");
  leg->Draw();


  TPaveText *pt = new TPaveText(0.4195402,0.9088983,0.6393678,0.9915254,"blNDC");
  pt->SetName("scale");
  pt->SetBorderSize(1);
  pt->SetFillColor(0);
  pt->SetLineColor(0);
  pt->SetTextSize(0.0454545);

  char fname[100];
  sprintf(fname,"Scaled by integral1 + 0.5*(integral2-integral1) (x %0.2f)",scaleHist);
  TText *text = pt->AddText(fname);
  //  pt->Draw();

  c1->Update();
  c1->SaveAs(Form("norm_morphed_dist_%i_%i_%i_cat%i.gif",mass1,mass2,mass,cat));

  //  cout << histActual->Integral() << " " << hist->Integral() << endl;
  //  cout << histActual->GetEntries() << " " << hist->GetEntries() << endl;
  //  cout << histActual->GetBinWidth(1) << " " << hist->GetBinWidth(1) << endl;




  TFile * fout = new TFile(outfile,"RECREATE");
  
  hist->Write();

  TDatime today2;
  std::cout <<   "Time End " << today2.GetTime() << std::endl;


  // residuals

  TH1F* resid = (TH1F*)histActual->Clone();
  TH1F* residBR = (TH1F*)histActual->Clone();

  resid->Add(hist,-1); 
  resid->SetLineWidth(2);
  resid->SetLineColor(kGreen);

  residBR->Add(histBR,-1); 
  residBR->SetLineWidth(2);
  residBR->SetLineColor(kCyan+1);
  residBR->SetLineStyle(kDashed);

  resid->SetTitle(Form("Residual for interpolation between %i and %i for %i cat%i",mass1,mass2,mass,cat));
  //  resid->Draw("hist");
  //  residBR->Draw("histsame");

  c1->Update();
  c1->SaveAs(Form("residuals_norm_morphed_dist_%i_%i_%i_cat%i.gif",mass1,mass2,mass,cat));







}

