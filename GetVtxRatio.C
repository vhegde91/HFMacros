

void GetVtxRatio(){
  // TFile *fmc = TFile::Open("MC_Flat_E2E1HistsJetPt600.root");
  // TFile *fd= TFile::Open("2016B1_E2E1HistsJetPt600.root");
  TFile *fd= TFile::Open("2016B_E2E1HistsTrg5_Final.root");
  //  TFile *fmc = TFile::Open("2015D_E2E1HistsTrg5.root");
  TFile *fmc= TFile::Open("2016G_E2E1HistsTrg5.root");
  //  TFile *fmc = TFile::Open("MC_Flat_obs_PileupHistogramJetPt600.root");
  
  TH1D *hd=(TH1D*)fd->FindObjectAny("nVertices");
  TH1D *hmc=(TH1D*)fmc->FindObjectAny("nVertices");
  //  TH1D *h_VtxRatio=new TH1D("VtxRatio","Data Vtx Divided by MC Vtx",100,0,100);

  TH1D* h_VtxRatio=(TH1D*)hd->Clone();
  h_VtxRatio->Scale(1.0/(h_VtxRatio->Integral()));
  hmc->Scale(1.0/(hmc->Integral()));
  h_VtxRatio->Divide(hmc);
  double r[h_VtxRatio->GetNbinsX()];
  for(int i=1;i<=(h_VtxRatio->GetNbinsX());i++){
    cout<<"Bin:"<<i<<" Ratio:"<<h_VtxRatio->GetBinContent(i)<<endl;
    r[i-1]=h_VtxRatio->GetBinContent(i);
    /*
    if( (hmc->GetBinContent(i))!=0 ){
      r=(hd->GetBinContent(i)/hmc->GetBinContent(i));
      //  h_VtxRatio->Fill(hd->GetBinLowEdge(i),r);
      cout<<i<<" "<<"binLowEdge:"<<hd->GetBinLowEdge(i)<<" ratio:"<<r<<endl;
    }
    */
  }
  cout<<"{";
  for(int i=0;i<(h_VtxRatio->GetNbinsX());i++){
    cout<<r[i]<<",";
  }
  cout<<"};";
  h_VtxRatio->Draw();
  //hd->DrawNormalized();
  //  hmc->Draw("sames");
  
}
