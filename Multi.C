void fill(){

  gDirectory->Delete("V01");
  gDirectory->Delete("V011");
  gDirectory->Delete("V013");
  gDirectory->Delete("V015");
  gDirectory->Delete("V04");
  gDirectory->Delete("V06");

  gDirectory->Delete("V12");
  gDirectory->Delete("V34");
  gDirectory->Delete("V56");
  Dat_eeB->cd();

  Int_t nbin = 40;
  TH2F *V01 = new TH2F("V01","V01",nbin, -2.,2, 60,0.,300);
  TH2F *V011 = new TH2F("V011","V011",nbin, -2.,2, 60,0.,300);
  TH2F *V013 = new TH2F("V013","V013",nbin, -2.,2, 60,0.,300);
  TH2F *V015 = new TH2F("V015","V015",nbin, -2.,2, 60,0.,300);
  TH2F *V04 = new TH2F("V04","V04",nbin, -2.,2, 60,0.,300);
  TH2F *V06 = new TH2F("V06","V06",nbin, -2.,2, 60,0.,300);
  TH2F *V12 = new TH2F("V12","V12",nbin, -2.,2, 60,0.,300);
  TH2F *V34 = new TH2F("V34","V34",nbin, -2.,2, 60,0.,300);
  TH2F *V56 = new TH2F("V56","V56",nbin, -2.,2, 60,0.,300);

  TProfile *Tpf0 = new TProfile("Tpf0","Tpf0", 10,-0.5, 9.5, 0.,100.);
  TProfile *Tpf1 = new TProfile("Tpf1","Tpf1", 10,-0.5, 9.5, 0.,100.);
  TProfile *Tpf2 = new TProfile("Tpf2","Tpf2", 10,-0.5, 9.5, 0.,100.);
  TProfile *Tpf3 = new TProfile("Tpf3","Tpf3", 10,-0.5, 9.5, 0.,100.);
  TProfile *Tpf4 = new TProfile("Tpf4","Tpf4", 10,-0.5, 9.5, 0.,100.);
  TProfile *Tpf5 = new TProfile("Tpf5","Tpf5", 10,-0.5, 9.5, 0.,100.);
  TProfile *Tpf6 = new TProfile("Tpf6","Tpf6", 10,-0.5, 9.5, 0.,100.);
  TProfile *Tpf7 = new TProfile("Tpf7","Tpf7", 10,-0.5, 9.5, 0.,100.);
  TProfile *Tpf8 = new TProfile("Tpf8","Tpf8", 10,-0.5, 9.5, 0.,100.);

  tree_->Draw("vertexMolteplicity[0]+vertexMolteplicity[1]:(V_z[0]-V_z[1])>>V01", "vertexNDOF[1]>2 && vertexNDOF[0]>2");
  return;
  tree_->Draw("vertexMolteplicity[0]+vertexMolteplicity[1]:(V_z[0]-V_z[1])>>V011", "vertexNDOF[1]>2 && vertexNDOF[0]>2 && numberOfVertexes==2");
  tree_->Draw("vertexMolteplicity[0]+vertexMolteplicity[1]:(V_z[0]-V_z[1])>>V013", "vertexNDOF[1]>2 && vertexNDOF[0]>2 && numberOfVertexes==4");
  tree_->Draw("vertexMolteplicity[0]+vertexMolteplicity[1]:(V_z[0]-V_z[1])>>V015", "vertexNDOF[1]>2 && vertexNDOF[0]>2 && numberOfVertexes==6");
  tree_->Draw("vertexMolteplicity[0]+vertexMolteplicity[4]:(V_z[0]-V_z[4])>>V04", "vertexNDOF[0]>2 && vertexNDOF[4]>2");
  tree_->Draw("vertexMolteplicity[0]+vertexMolteplicity[6]:(V_z[0]-V_z[6])>>V06", "vertexNDOF[0]>2 && vertexNDOF[6]>2");

  tree_->Draw("vertexMolteplicity[1]+vertexMolteplicity[2]:(V_z[1]-V_z[2])>>V12", "vertexNDOF[1]>2 && vertexNDOF[2]>2");
  tree_->Draw("vertexMolteplicity[3]+vertexMolteplicity[4]:(V_z[3]-V_z[4])>>V34", "vertexNDOF[3]>2 && vertexNDOF[4]>2");
  tree_->Draw("vertexMolteplicity[5]+vertexMolteplicity[6]:(V_z[5]-V_z[6])>>V56", "vertexNDOF[5]>2 && vertexNDOF[6]>2");


  tree_->Draw("vertexMolteplicity[0]:numberOfVertexes>>Tpf0", "vertexNDOF[0]>2");
  tree_->Draw("vertexMolteplicity[1]:numberOfVertexes>>Tpf1", "vertexNDOF[1]>2");
  tree_->Draw("vertexMolteplicity[2]:numberOfVertexes>>Tpf2", "vertexNDOF[2]>2");
  tree_->Draw("vertexMolteplicity[3]:numberOfVertexes>>Tpf3", "vertexNDOF[3]>2");
  tree_->Draw("vertexMolteplicity[4]:numberOfVertexes>>Tpf4", "vertexNDOF[4]>2");
  tree_->Draw("vertexMolteplicity[5]:numberOfVertexes>>Tpf5", "vertexNDOF[5]>2");
  tree_->Draw("vertexMolteplicity[6]:numberOfVertexes>>Tpf6", "vertexNDOF[6]>2");
  tree_->Draw("vertexMolteplicity[7]:numberOfVertexes>>Tpf7", "vertexNDOF[7]>2");
  tree_->Draw("vertexMolteplicity[8]:numberOfVertexes>>Tpf8", "vertexNDOF[8]>2");

  V01->SetMarkerSize(0.3);
  V011->SetMarkerSize(0.3);
  V011->SetMarkerColor(2);
  V013->SetMarkerColor(3);
  V015->SetMarkerColor(4);

  V013->SetMarkerSize(0.3);
  V015->SetMarkerSize(0.3);
  V04->SetMarkerSize(0.3);
  V06->SetMarkerSize(0.3);
  V12->SetMarkerSize(0.3);
  V34->SetMarkerSize(0.3);
  V56->SetMarkerSize(0.3);
}

void Mult(){

  Tpf1->SetStats(0);
  Tpf0->SetStats(0);
  Tpf8->SetStats(0);
  Tpf0->Draw();
  Tpf0->GetXaxis()->SetTitle("# of vertexes in event");
  Tpf0->GetYaxis()->SetTitle("Average Multiplicity");

  Tpf1->SetLineColor(9);  
  Tpf1->Draw("SAME");

  Tpf2->SetLineColor(2);  
  Tpf2->Draw("SAME");

  Tpf3->SetLineColor(3);  
  Tpf3->Draw("SAME");

  Tpf4->SetLineColor(4);  
  Tpf4->Draw("SAME");

  Tpf5->SetLineColor(5);  
  Tpf5->Draw("SAME");


  Tpf6->SetLineColor(6);  
  Tpf6->Draw("SAME");

  Tpf7->SetLineColor(7);  
  Tpf7->Draw("SAME");
  
  Tpf8->SetLineColor(8);  
  Tpf8->Draw("SAME");

  NText(9.6,60,"Vtx[0]");
  NText(9.6,45,"Vtx[1]");
  NText(9.6,30,"Vtx[2]");
  NText(9.6,20,"Vtx[3]");
  NText(9.6,15,"Vtx[4]");
  NText(9.6,10,"Vtx[5]");
  NText(9.6,7,"Vtx[6]");
  NText(9.6,4,"Vtx[7]");

  return;
}

void Proj_all(){

  TCanvas *My = NCanvas(2,2);


  V01->ProjectionX("V01_0_10",0,10); 
  V34->ProjectionX("V34_0_10",0,10); 
  V12->ProjectionX("V12_0_10",0,10); 
  V56->ProjectionX("V56_0_10",0,10); 
  My->cd(1);
  V01_0_10->SetStats(0);
  NH1DArea1(V01_0_10);
  V01->GetXaxis()->SetTitle("(Vz[i]-Vz[j])  [cm]");


  NH1DArea1(V12_0_10);
  NH1DArea1(V34_0_10);
  NH1DArea1(V56_0_10);
  V01_0_10->SetLineColor(2);
  V12_0_10->SetLineColor(3);
  V34_0_10->SetLineColor(4);
  V56_0_10->SetLineColor(6);
  V01_0_10->SetMaximum(0.05);
  V01_0_10->SetTitle("");
  V01_0_10->Draw();
  V12_0_10->Draw("SAME");
  V34_0_10->Draw("SAME");
  V56_0_10->Draw("SAME");
  
  NText(-1.7,0.051, "Blind distance for sum of vertex multiplicity = 0-50 tracks");

  NText(-1.7,0.046, "Red = V[0]+V[1]; Green = V[1]+V[2]");
  NText(-1.7,0.043, "Blue = V[3]+V[4]; Magenta = V[5]+V[6]");

  My->cd(2);
  V01->ProjectionX("V01_10_20",0,10); 
  V34->ProjectionX("V34_10_20",0,10); 
  V12->ProjectionX("V12_10_20",0,10); 

  V01_10_20->SetStats(0);

  NH1DArea1(V01_10_20);
  NH1DArea1(V12_10_20);
  NH1DArea1(V34_10_20);
  V01_10_20->SetLineColor(2);
  V12_10_20->SetLineColor(3);
  V34_10_20->SetLineColor(4);
  V01_10_20->SetMaximum(0.050);
  V01_10_20->SetTitle("");
  V01_10_20->Draw();
  V12_10_20->Draw("SAME");
  V34_10_20->Draw("SAME");
  

  NText(-1.7,0.051, "Blind distance for sum of vertex multiplicity = 50-100 tracks");


  My->cd(3);


  V01_20_30->SetStats(0);

  V01->ProjectionX("V01_20_30",20,30); 
  V12->ProjectionX("V12_20_30",20,30); 
  V34->ProjectionX("V34_20_30",20,30); 


  V01_20_30->SetLineColor(2);
  V12_20_30->SetLineColor(3);
  V34_20_30->SetLineColor(4);

  NH1DArea1(V01_20_30);
  NH1DArea1(V12_20_30);
  V01_20_30->SetTitle("");
  V01_20_30->SetMaximum(0.050);
  V01_20_30->Draw();
  V12_20_30->Draw("SAME");

  V01_20_30->SetMaximum(0.050);
  NText(-1.7,0.051, "Blind distance for sum of vertex multiplicity = 100-150 tracks");
  My->cd(4);


  V01_30_40->SetStats(0);

  V01->ProjectionX("V01_30_40",30,40); 
  V12->ProjectionX("V12_30_40",30,40); 

  V01_30_40->SetTitle("");
  V01_30_40->SetLineColor(2);
  V12_30_40->SetLineColor(3);

  NH1DArea1(V01_30_40);
  NH1DArea1(V12_30_40);
  V01_30_40->SetMaximum(0.050);
  V01_30_40->Draw();
  V12_30_40->Draw("SAME");
 
  NText(-1.7,0.051, "Blind distance for sum of vertex multiplicity = 150-200 tracks");

  return;
    }

void Proj_v01(){

  TCanvas *My = NCanvas(1,1);


  V01->ProjectionX("V01_0_5",0,5); 
  V01->ProjectionX("V01_5_10",5,10); 
  V01->ProjectionX("V01_10_15",10,15); 
  V01->ProjectionX("V01_15_20",15,20); 
  V01->ProjectionX("V01_20_25",20,25); 
  V01->ProjectionX("V01_25_30",25,30); 
  V01->ProjectionX("V01_30_35",30,35); 
  V01->ProjectionX("V01_35_40",35,40); 
  V01->ProjectionX("V01_40_50",40,50); 
  V01->ProjectionX("V01_45_50",45,50); 

  NH1DMax1(V01_0_5);
  NH1DMax1(V01_5_10);
  NH1DMax1(V01_10_15);
  NH1DMax1(V01_15_20);
  NH1DMax1(V01_20_25);
  NH1DMax1(V01_25_30);
  NH1DMax1(V01_30_35);
  NH1DMax1(V01_35_40);
  NH1DMax1(V01_40_50);
  NH1DMax1(V01_45_50);


  //  V01_5_10->SetMaximum(0.05);

  V01_10_15->SetLineColor(2);
  V01_15_20->SetLineColor(3);
  V01_20_25->SetLineColor(4);
  V01_25_30->SetLineColor(5);
  V01_30_35->SetLineColor(6);
  V01_35_40->SetLineColor(7);
  V01_40_50->SetLineColor(8);
  V01_45_50->SetLineColor(9);

  V01_5_10->Draw();
  V01_5_10->SetStats(0);
  V01_10_15->Draw("SAME");
  V01_15_20->Draw("SAME");
  V01_20_25->Draw("SAME");
  V01_25_30->Draw("SAME");
  V01_30_35->Draw("SAME");
  V01_35_40->Draw("SAME");
  V01_40_50->Draw("SAME");
  //  V01_45_50->Draw("SAME");

  V01->GetXaxis()->SetTitle("(Vz[0]-Vz[1])  [cm]");
  NText(-2.1,1.08, "Blind distance between two vertexes for different sum of tracks multiplicity");

  NText(-1.9,0.05, "Black=25-50");
  NText(-1.9,0.1, "Red=50-75");
  NText(-1.9,0.15, "Light Green=75-100");
  NText(-1.9,0.20, "Blue=100-125");
  NText(-1.9,0.25, "Yellow=125-150");
  NText(-1.9,0.3, "Magenta=150-175");
  NText(-1.9,0.35, "Light blue=175-200");
  NText(-1.9,0.40, "Green=200-250");


  return;
}
void Norm(){

  // Run after starting root with 
  //  root Fraction_n_vertexes_files_ee10_NDOFGT2_EBGT50_runAB_RunList=0_LumiCor=0.root

  Vertex0Mult->Draw();
  Vertex1Mult->Draw();

  SumMultVertex_0_25->Draw();
  NH1FMax1(SumMultVertex_0_25);
  SumMultVertex_0_25->Scale(2.);

  SumMultVertex_25_50->Draw();
  NH1FMax1(SumMultVertex_25_50);
  SumMultVertex_25_50->Scale(1.1);

  SumMultVertex_50_75->Draw("SAME");
  NH1FMax1(SumMultVertex_50_75);
  SumMultVertex_50_75->Scale(1.05);



 SumMultVertex_75_100->Draw("SAME");
  NH1FMax1(SumMultVertex_75_100);
  SumMultVertex_75_100->Scale(1.05);


 SumMultVertex_100_125->Draw("SAME");
  NH1FMax1(SumMultVertex_100_125);
  SumMultVertex_100_125->Scale(1.1);
  
 SumMultVertex_125_150->Draw("SAME");
  NH1FMax1(SumMultVertex_125_150);
  SumMultVertex_125_150->Scale(1.1);


 SumMultVertex_150_175->Draw("SAME");
  NH1FMax1(SumMultVertex_150_175);
  SumMultVertex_150_175->Scale(1.1);


 SumMultVertex_175_200->Draw("SAME");
  NH1FMax1(SumMultVertex_175_200);
  SumMultVertex_175_200->Scale(1.2);


 SumMultVertex_200_225->Draw("SAME");
  NH1FMax1(SumMultVertex_200_225);
  SumMultVertex_200_225->Scale(1.4);



 SumMultVertex_225_250->Draw("SAME");
  NH1FMax1(SumMultVertex_225_250);
  SumMultVertex_225_250->Scale(1.4);


  TFile *ffc= TFile::Open("vertex_ee10_NDOFGT4.root","update"); 

  //  SumMultVertex_0_25->Write();
  SumMultVertex_25_50->Write();
  SumMultVertex_50_75->Write();
  SumMultVertex_75_100->Write();
  SumMultVertex_100_125->Write();
  SumMultVertex_125_150->Write();
  SumMultVertex_150_175->Write();
  SumMultVertex_175_200->Write();
  SumMultVertex_200_225->Write();
  SumMultVertex_225_250->Write();

  //  Vertex0Mult->Write();
  // Vertex1Mult->Write();

  ffc->Close();







}
