void ratioHists(){
  TCanvas *c1=new TCanvas("c1","c1",1550,850);

  TFile *fN = TFile::Open("2016B1_E2E1HistsJetPt600.root");
  TFile *fD = TFile::Open("MC_Flat_PU_obs_2016B1_E2E1HistsJetPt600.root");
    //TFile *fD = TFile::Open("MC_Flat_E2E1HistsJetPt600.root");
  //TFile *fD = TFile::Open("MC_Flat_PU_obs_NoWt_2016B1_E2E1HistsJetPt600.root");

  TH1D *hN=(TH1D*)fN->FindObjectAny("leadJetPt");
  TH1D *hD=(TH1D*)fD->FindObjectAny("leadJetPt");
  TH1D *hNC=(TH1D*)hN->Clone();
  TH1D *hDC=(TH1D*)hD->Clone();

  if(1){
    hDC->Scale(1.0/(hDC->Integral()) );
    hNC->Scale(1.0/(hNC->Integral()) );
    hD->Scale(1.0/(hD->Integral()) );
    hN->Scale(1.0/(hN->Integral()) );
  }
  hDC->Draw();  
  hNC->Draw("sames");
  gPad->Update();

  hNC->SetLineColor(kRed);hNC->SetName(fN->GetName()); 
  TPaveStats *stN=(TPaveStats*)hNC->FindObject("stats");
  stN->SetTextColor(kRed);

  hDC->SetLineColor(kBlue);hDC ->SetName(fD->GetName());
  TPaveStats *stD=(TPaveStats*)hDC->FindObject("stats");
  stD->SetTextColor(kBlue);
  
  

  TCanvas *c2=new TCanvas("c2","c2",800,500);
  hN->Divide(hD);
  hN->Draw();
  

}
