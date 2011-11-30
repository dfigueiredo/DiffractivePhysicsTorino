{

  TCanvas *MyC = new TCanvas("MyC","Test canvas",1);  MyC->Divide(1,2);
  gDirectory->Delete("JP_1");
  gDirectory->Delete("JP_all");
  gDirectory->Delete("JP");    
  gDirectory->Delete("JP_RN_1");
  gDirectory->Delete("JP_RN_all");
  gDirectory->Delete("JP_RN");    
    

    // string cut_1 = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 && (sumEHF_PF_minus==0 || sumEHF_PF_plus==0) &&  (RunNumber<146400 || RunNumber>146460)";      string cut_all = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 &&  (RunNumber<146400 || RunNumber>146460)";
    //    string cut_1 = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 && (sumEHF_minus<4. || sumEHF_plus<4.) &&  (RunNumber<146400 || RunNumber>146460)";      string cut_all = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 &&  (RunNumber<146400 || RunNumber>146460)";
    string cut_1 = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 && (sumEHF_minus<4. || sumEHF_plus<4.)";      string cut_all = "istlumiPerBX*6.37>0.1 && numberOfVertexes==1 &&  (RunNumber<146400 || RunNumber>146460)";

    int nbin = 14; 
    TH1F *JP_all = new TH1F("JP_all","Gap vs Inst. Lumi per bx; Inst.  Lumi per bx; Fraction",nbin,0.,0.7) ;    
    TH1F *JP_1 = new TH1F("JP_1","Gap vs Inst. Lumi per bx; Inst.  Lumi per bx; Fraction",nbin,0.,0.7) ;    
    TH1F *JP = new TH1F("JP","Gap vs Inst. Lumi per bx; Inst.  Lumi per bx; Fraction",nbin,0.,0.7) ;    
    TH1F *JP_RN_all = new TH1F("JP_RN_all","Gap; Run Number; Fraction",100,140000.,150000) ;    
    TH1F *JP_RN_1 = new TH1F("JP_RN_1","Gap; Run Number; Fraction",100,140000.,150000) ;    
    TH1F *JP_RN = new TH1F("JP_RN","Gap; Run Number; Fraction",100,140000.,150000) ;       


    JP->Sumw2();
    tree_->Draw("(istlumiPerBX*6.37)>>JP_1",cut_1.c_str(),"goff");
    tree_->Draw("(istlumiPerBX*6.37)>>JP_all",cut_all.c_str(),"goff");
    JP_RN->Sumw2();
    tree_->Draw("RunNumber>>JP_RN_1",cut_1.c_str(),"goff");
    tree_->Draw("RunNumber>>JP_RN_all",cut_all.c_str(),"goff");
    
    JP->Divide(JP_1,JP_all);
    JP_RN->Divide(JP_RN_1,JP_RN_all);
    
    Float_t max = 1.3*JP->GetMaximum();
    JP->SetMaximum(max);
    
    JP->GetYaxis()->SetTitleOffset(0.8);
    JP->SetMarkerStyle(20);
    JP->SetMarkerColor(2);
    JP->SetLineColor(2);
    JP->SetMarkerSize(1.);

    //MyC->Update();

    MyC->cd(1);          
    JP->Draw("e");
    // MyC->Update();


    MyC->cd(2);          
    JP_RN->GetYaxis()->SetTitleOffset(0.8);
    JP_RN->SetMarkerStyle(20);
    JP_RN->SetMarkerColor(4);
    JP_RN->SetMarkerSize(1.);
    JP_RN->SetLineColor(4);
    //    MyC_2->SetLogy();

    JP_RN->SetMinimum(0.005);
    JP_RN->Draw("e");
    // c1->Update();
    
