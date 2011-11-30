{
TCanvas *pippo = NCanvas(2,3,"pippo");
pippo->cd(1);
tree_->Draw("log10(Epz_PF_plus/7000):log10(1-fabs(xL_gen))","vertexNDOF[0]>0 && xL_gen>0");
pippo->cd(2);
tree_->Draw("log10(Epz_Calo_plus/7000):log10(1-fabs(xL_gen))","vertexNDOF[0]>0 && xL_gen>0");
pippo->cd(5);
tree_->Draw("log10(Mx2/(7000*7000)):log10(1-fabs(xL_gen))","vertexNDOF[0]>0 && xL_gen>0");
pippo->cd(6);
tree_->Draw("log10(Mx2_gen/(7000*7000)):log10(1-fabs(xL_gen))","vertexNDOF[0]>0 && xL_gen>0");
pippo->cd(3);
tree_->Draw("log10(xi_PF_plus):log10(1-fabs(xL_gen))","vertexNDOF[0]>0 && xL_gen>0");
pippo->cd(4);
tree_->Draw("log10(xi_Calo_plus):log10(1-fabs(xL_gen))","vertexNDOF[0]>0 && xL_gen>0");
}
return;

tree_->Draw("sumEHF_plus","vertexNDOF[0]==0 && xL_gen>0 && energyTot_PF_plus==0")   
tree_->Draw("xi_Calo_plus*3500","vertexNDOF[0]==0 && xL_gen>0 && energyTot_PF_plus==0")
tree_->Draw("log10(Mx2/(7000*7000)):etaMax_PF","vertexNDOF[0]>0 && xL_gen>0 && etaMax_PF>-10")
tree_->Draw("sumEHF_PF_plus","vertexNDOF[0]>0 && xL_gen>0 && etaMax_PF>-10 && sumEHF_PF_plus <20")
tree_->Draw("numberoOfTracks_gen:log10(1-xL_gen)","xL_gen>0 && log10(1-xL_gen)>-6 && etaMax_PF<1")
