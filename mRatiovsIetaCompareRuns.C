#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"TH1.h"
#include"TROOT.h"
#include"TH2.h"
#include"TFile.h"
#include"TDirectory.h"
#include"TTree.h"
#include"TBrowser.h"
#include"TF1.h"
#include<iomanip>
#include"TGraphErrors.h"
#include"TGraph.h"
#include"TCanvas.h"
#include"TPaveStats.h"
using namespace std;

int col3=(kRed),col2=kBlue,col1=12,col4=kTeal+9;
void mRatiovsIetaCompareRuns(){
  TFile *f1=new TFile("mRatiovsIeta_2012D_E2E1HistsVtx.root");
  TFile *f2=new TFile("mRatiovsIeta_254833_E2E1HistsVtx.root");
  TFile *f3=new TFile("mRatiovsIeta_2015B_E2E1HistsVtx.root");
  //TFile *f1=new TFile("mRatiovsIeta_MC_E2E1HistsTrg1.root");
  // TFile *f2=new TFile("mRatiovsIeta_254833_E2E1HistsTrg1.root");
  //TFile *f3=new TFile("mRatiovsIeta_MC_E2E1HistsTrg1_170to300.root");
  //  TFile *f3=new TFile("mRatiovsIeta_MC_E2E1HistsTrg1_1000to1400.root");

  //TFile *f3=new TFile("mRatiovsIeta_MC_E2E1Hists.root");
  // TFile *f3=new TFile("mRatiovsIeta_1400to1800_MC_E2E1Hists.root");
 
  
  TH1D *h_hist1=(TH1D*)f1->FindObjectAny("MeanRatiovsIetaECut2");
  TH1D *h_hist2=(TH1D*)f2->FindObjectAny("MeanRatiovsIetaECut2");
  TH1D *h_hist3=(TH1D*)f3->FindObjectAny("MeanRatiovsIetaECut2");
  

  gStyle->SetOptStat(0);
  TCanvas *c_cA=new TCanvas("c_mRatiovsIetaCompareRuns","c_mRatiovsIetaCompareRuns",1500,1500);

  h_hist1->SetMaximum(0.8);
  h_hist1->SetMinimum(0.2);
 
  h_hist1->SetFillColor(col1);
  h_hist1->SetLineColor(col1);
  h_hist2->SetLineColor(col2);
  h_hist3->SetLineColor(col3);
  //h_hist4->SetLineColor(col4);/////////////////
  h_hist1->GetYaxis()->SetTitle("Ratio");
  h_hist1->GetXaxis()->SetTitle("i\eta");

  h_hist1->SetLineWidth(2);
  h_hist2->SetLineWidth(2);
  h_hist3->SetLineWidth(2);
  // h_hist4->SetLineWidth(2);//////////////////

  h_hist1->SetMarkerColor(col1);
  h_hist2->SetMarkerColor(col2);
  h_hist3->SetMarkerColor(col3);
  // h_hist4->SetMarkerColor(col4);//////////////

  h_hist1->SetMarkerStyle(21);
  h_hist2->SetMarkerStyle(20);
  h_hist3->SetMarkerStyle(22);
  //h_hist4->SetMarkerStyle(23);/////////


  TLegend *legend1=new TLegend(0.75,0.85,.9,.9);
  legend1->AddEntry(h_hist1,"2012D","fep");
  //  legend1->AddEntry(h_hist1,"MC","lep");
  legend1->SetTextSize(0.04);
 

  TLegend *legend2=new TLegend(0.75,0.8,.9,.85);
  legend2->AddEntry(h_hist2,"2015C","lep");
  //legend2->AddEntry(h_hist2,"254833 Data","lep");
  legend2->SetTextSize(0.04);
  
  
  TLegend *legend3=new TLegend(0.75,0.75,.9,.8);
  legend3->AddEntry(h_hist3,"2015B","LEP");
  //legend3->AddEntry(h_hist3,"MC2","LEP");
  legend3->SetTextSize(0.04);

  /*  TLegend *legend4=new TLegend(0.75,0.7,.9,.75);
  //legend3->AddEntry(h_hist3,"2015B","LEP");
  legend4->AddEntry(h_hist4,"MC","LEP");
  legend4->SetTextSize(0.04);
  */
  
    
  h_hist1->Draw("BAR");
  //h_hist1->Draw();
  h_hist2->Draw("same");
  h_hist3->Draw("same");
  // h_hist4->Draw("same");//////////////////
  c_cA->SetGridx();
  c_cA->SetGridy();
  legend1->Draw();
  legend2->Draw();
  legend3->Draw();
  //legend4->Draw();///////////////////////


}
