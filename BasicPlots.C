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
#include"TStyle.h"
#include"TLegend.h"

//#include"Variables.h"

using namespace std;

void drawBasicPlots(int,TList*);
void decorate(TH1*,int);
void decorate(TH2*);
void nameLegend2(const char*);
TList *FileList;
char name[100];
int col[6]={kRed,kBlue,kTeal+9,kMagenta,kBlack,kOrange};
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//float scalefct=0.01013492565;
float scalefct=1.0;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void BasicPlots(){
  FileList = new TList();
  int nfiles=4;
  TFile *f[nfiles];
  //  FileList->Add(TFile::Open("2015D_E2E1HistsTrg5.root") ); //w/o filters
  // FileList->Add(TFile::Open("2015D_E2E1HistsTrg5PupWt2016B.root") );//w/o filters
  // FileList->Add(TFile::Open("2016B_E2E1HistsTrg5.root") );//w/o filters
  //FileList->Add(TFile::Open("2015D_E2E1HistsTrg5PupWt2016B_Final.root") ); 
  //FileList->Add(TFile::Open("2016C_Expr_E2E1HistsTrg5_Filt.root") );
  //  FileList->Add(TFile::Open("2016B1_E2E1HistsTrg5_Filt.root") );
  // FileList->Add(TFile::Open("2016B2_E2E1HistsTrg5_Filt.root") );
  // FileList->Add(TFile::Open("2016B3_E2E1HistsTrg5_Filt.root") );
  FileList->Add(TFile::Open("2016B_E2E1HistsTrg5_Final.root") );
  // FileList->Add(TFile::Open("2016C_Expr_E2E1HistsTrg5_Filt.root") );
  // FileList->Add(TFile::Open("2016D_Expr_E2E1HistsTrg5_Filt.root") );
  // FileList->Add(TFile::Open("2016E_E2E1HistsTrg5.root") );
  FileList->Add(TFile::Open("2016F_E2E1HistsTrg5.root") );
  FileList->Add(TFile::Open("2016G_E2E1HistsTrg5.root") );
  FileList->Add(TFile::Open("2016H_E2E1HistsTrg5.root") );
  //  FileList->Add(TFile::Open("2016E_RecHitsBasedOnJets_E2E1HistsTrg5.root") );
  //  FileList->Add(TFile::Open("2016H_v2_E2E1HistsTrg5.root") );
  //  FileList->Add(TFile::Open("2016H_v3_E2E1HistsTrg5.root") );
  //FileList->Add(TFile::Open("2016F_E2E1HistsTrg5.root") );
  //  FileList->Add(TFile::Open("SingMu2016B2_E2E1HistsTrg3_Filt.root") );
  //  FileList->Add(TFile::Open("2016B1_E2E1HistsTrg5_Filt.root") );
  //FileList->Add(TFile::Open("MC25ns_E2E1HistsTrg5PupWt2016B.root") );
  //FileList->Add(TFile::Open("MC25ns_E2E1HistsTrg5_2016B.root") );
  //  FileList->Add(TFile::Open("2016B1_E2E1HistsJetPt600.root") );
  //  FileList->Add(TFile::Open("MC_Flat_PU_obs_2016B1_E2E1HistsJetPt600_10pcScaled.root") );
  //FileList->Add(TFile::Open("MC_Flat_PU_obs_2016B1_E2E1HistsJetPt600.root") );
  //  FileList->Add(TFile::Open("MC_Flat_PU_obs_2016E_E2E1HistsJetPt600.root") );
  //  FileList->Add(TFile::Open("2016E_E2E1HistsJetPt600_Trg5.root") );
  //  FileList->Add(TFile::Open("MC_Flat_PU_obs_2016E_E2E1HistsJetPt600_18pcScaled.root") );
  //  FileList->Add(TFile::Open("2016B1_E2E1HistsJetPt600_Trg5.root") );
  //  FileList->Add(TFile::Open("MC_sumwt_PU2016B1.root") );
 
    //FileList->Add(TFile::Open("MC_Flat_PU_obs_2016B1_E2E1HistsJetPt600_noEvtWt.root") );
 
  drawBasicPlots(nfiles,FileList);
  
}


void drawBasicPlots(int nfiles,TList *f){

 
  int fIndx=0;
  bool normalize=0;
  TCanvas *c_1D=new TCanvas("RunVerRecIs","Runs Vetrices RecHits Energy and ieta iphi",1500,850);
  c_1D->Divide(4,2);
  TCanvas *c_2D=new TCanvas("RecHitEnergy","RechitEnergy Plots",1500,850);
  c_2D->Divide(2,2);


  gStyle->SetOptStat("nemri");
  TFile *f_first = (TFile*)f->First();
  double binlow=-10000;
  // gStyle->SetLineColor(col[0]);
  //////////////////////////////
  // sprintf(name,"%s",f_first->GetName());
  nameLegend2(f_first->GetName());
  TH1I *runs=(TH1I*)f_first->FindObjectAny("runs");
  c_1D->cd(1);
  runs->Draw("HIST");	gPad->Update();decorate(runs,0);runs->SetTitle(";run rumber;");

  TH1D *nVertices=(TH1D*)f_first->FindObjectAny("nVertices");
  c_1D->cd(2);//nVertices->SetMarkerStyle(22);nVertices->SetMarkerColor(col[0]);
  nVertices->Draw("HIST");	gPad->Update();decorate(nVertices,0);
  nVertices->SetTitle(";no. of Vertices;");
  if(normalize)  nVertices->Scale(1/nVertices->Integral());

  TH1D *nRecs=(TH1D*)f_first->FindObjectAny("nHFRecHitsEmin");
  c_1D->cd(3);nRecs->Rebin(8);
  nRecs->Draw("HIST");	gPad->Update();decorate(nRecs,0);nRecs->SetTitle(";HF RecHits;");
  if(normalize)  nRecs    ->Scale(1/nRecs->Integral());

  TH1I *ieta=(TH1I*)f_first->FindObjectAny("ieta");
  c_1D->cd(4);
  ieta->Draw("HIST");	gPad->Update();decorate(ieta,0);ieta->SetTitle(";i#eta;");

  TH1D *HFRecHitEnergy=(TH1D*)f_first->FindObjectAny("HFRecHitEnergy");
  c_1D->cd(5);  gPad->SetLogy();//HFRecHitEnergy->Scale(0.01013492565);
  HFRecHitEnergy->Draw("HIST");	gPad->Update();decorate(HFRecHitEnergy,0);HFRecHitEnergy->SetTitle(";HF RecHit Energy;");
  if(normalize)  HFRecHitEnergy->Scale(1/HFRecHitEnergy->Integral());
  binlow=HFRecHitEnergy->GetBinLowEdge(1);

  TH1D *HFRecHitEnergyD1=(TH1D*)f_first->FindObjectAny("HFRecHitEnergyD1");
  c_1D->cd(6); gPad->SetLogy();
  HFRecHitEnergyD1->Draw("HIST");	gPad->Update();decorate(HFRecHitEnergyD1,0);HFRecHitEnergyD1->SetTitle(";HF RecHit Energy in Depth1;");
  if(normalize)  HFRecHitEnergyD1->Scale(1/HFRecHitEnergyD1->Integral());

  TH1D *HFRecHitEnergyD2=(TH1D*)f_first->FindObjectAny("HFRecHitEnergyD2");
  c_1D->cd(7);  gPad->SetLogy();
  HFRecHitEnergyD2->Draw("HIST");	gPad->Update();decorate(HFRecHitEnergyD2,0);HFRecHitEnergyD2->SetTitle(";HF RecHit Energy in Depth2;");
  if(normalize)  HFRecHitEnergyD2->Scale(1/HFRecHitEnergyD2->Integral());

  TH1I *iphi=(TH1I*)f_first->FindObjectAny("iphi");
  c_1D->cd(8);
  iphi->Draw("HIST");	gPad->Update();decorate(iphi,0);iphi->SetTitle(";i#phi;");

  // if(normalize){
  //   c_1D->cd(2);nVertices->Scale(1/nVertices->Integral());gPad->Update();
  //   //nRecs    ->Scale(1/nRecs->Integral());gPad->Update();
  //   HFRecHitEnergy->Scale(1/HFRecHitEnergy->Integral());
  //   HFRecHitEnergyD1->Scale(1/HFRecHitEnergyD1->Integral());
  //   HFRecHitEnergyD2->Scale(1/HFRecHitEnergyD2->Integral());
  // }
  /////////////////////////////////////////////////
  TH2I *iEtaiPhiDepth1=(TH2I*)f_first->FindObjectAny("iEtaiPhiDepth1");
  c_2D->cd(1); gPad->SetLogz();
  iEtaiPhiDepth1->Draw("colz");gPad->Update();decorate(iEtaiPhiDepth1);
  iEtaiPhiDepth1->GetXaxis()->SetTitle("i#eta");iEtaiPhiDepth1->GetYaxis()->SetTitle("i#phi");

  TH2I *iEtaiPhiDepth2=(TH2I*)f_first->FindObjectAny("iEtaiPhiDepth2");
  c_2D->cd(2); gPad->SetLogz();
  iEtaiPhiDepth2->Draw("colz");gPad->Update();decorate(iEtaiPhiDepth2);
  iEtaiPhiDepth2->GetXaxis()->SetTitle("i#eta");iEtaiPhiDepth2->GetYaxis()->SetTitle("i#phi");

  TH2I *iEtaiPhiDepth1energyW=(TH2I*)f_first->FindObjectAny("iEtaiPhiDepth1energyW");
  c_2D->cd(3); gPad->SetLogz();
  iEtaiPhiDepth1energyW->Draw("colz");gPad->Update();decorate(iEtaiPhiDepth1energyW);
  iEtaiPhiDepth1energyW->GetXaxis()->SetTitle("i#eta");iEtaiPhiDepth1energyW->GetYaxis()->SetTitle("i#phi");

  TH2I *iEtaiPhiDepth2energyW=(TH2I*)f_first->FindObjectAny("iEtaiPhiDepth2energyW");
  c_2D->cd(4); gPad->SetLogz();
  iEtaiPhiDepth2energyW->Draw("colz");gPad->Update();decorate(iEtaiPhiDepth2energyW);
  iEtaiPhiDepth2energyW->GetXaxis()->SetTitle("i#eta");iEtaiPhiDepth2energyW->GetYaxis()->SetTitle("i#phi");

  ///////////////////////////////////////
 TFile *f_next = (TFile*)f->After(f_first);
 while(f_next){
   fIndx++;
   nameLegend2(f_next->GetName());
   TH1I *runs=(TH1I*)f_next->FindObjectAny("runs");
   c_1D->cd(1);
   runs->Draw("sames HIST");	gPad->Update();decorate(runs,fIndx);;
   
   TH1D *nVertices=(TH1D*)f_next->FindObjectAny("nVertices");
   c_1D->cd(2);
   nVertices->Draw("sames HIST");	gPad->Update();decorate(nVertices,fIndx);
   if(normalize)  nVertices->Scale(1/nVertices->Integral());
   
   TH1D *nRecs=(TH1D*)f_next->FindObjectAny("nHFRecHitsEmin");
   c_1D->cd(3);nRecs->Rebin(8);
   nRecs->Draw("sames hist");	gPad->Update();decorate(nRecs,fIndx);
   if(normalize)   nRecs    ->Scale(1/nRecs->Integral());gPad->Update();     
     
   TH1D *HFRecHitEnergy=(TH1D*)f_next->FindObjectAny("HFRecHitEnergy");
   c_1D->cd(5);  gPad->SetLogy();
   HFRecHitEnergy->Draw("HIST sames");	gPad->Update();decorate(HFRecHitEnergy,fIndx);
   if(normalize)   HFRecHitEnergy->Scale(1/HFRecHitEnergy->Integral());
   if(abs(binlow-HFRecHitEnergy->GetBinLowEdge(1)) > 0.001){
     cout<<endl<<"!!!!!!!!!!!!!!!!!Warning: Binnings for HFRecHitEnergy in files might be different. Compaison may not work."<<endl<<endl;
     binlow=HFRecHitEnergy->GetBinLowEdge(1);
   }

   TH1D *HFRecHitEnergyD1=(TH1D*)f_next->FindObjectAny("HFRecHitEnergyD1");
   c_1D->cd(6); gPad->SetLogy();
   HFRecHitEnergyD1->Draw("HIST sames");	gPad->Update();decorate(HFRecHitEnergyD1,fIndx);
   if(normalize)   HFRecHitEnergyD1->Scale(1/HFRecHitEnergyD1->Integral());

   TH1D *HFRecHitEnergyD2=(TH1D*)f_next->FindObjectAny("HFRecHitEnergyD2");
   c_1D->cd(7);  gPad->SetLogy();
   HFRecHitEnergyD2->Draw("HIST sames");	gPad->Update();decorate(HFRecHitEnergyD2,fIndx);
   if(normalize) HFRecHitEnergyD2->Scale(1/HFRecHitEnergyD2->Integral());

   f_next = (TFile*)f->After( f_next );

 }

  for(int i=0;i<nfiles;i++){


  }//loop over no. of files
  sprintf(name,"a%i.png",1);
  c_1D->Print(name);
  /*  TPad *pad1=(TPad*)c_1D->GetPad(6);
  pad1->SaveAs("RecHitEL2016BEFG.eps");
  //  pad1->SaveAs("nVtx2016BEFG.png");
  pad1->SaveAs("RecHitEL2016BEFG.C");*/
 
}


void decorate(TH1* h,int i){
  h->SetLineColor(col[i]);
  //  if(i==0){h->Scale(scalefct);}
  TPaveStats *st=(TPaveStats*)h->FindObject("stats");
  st->SetLineColor(col[i]);
  st->SetTextColor(col[i]);
  st->SetX1NDC(0.55);
  st->SetX2NDC(0.9); 
  st->SetY1NDC(0.90-i*.2);
  st->SetY2NDC(0.70-i*.2);

  //  TLegend *legend1=new TLegend(0.55,0.85,.9-i*.2,0.9-i*.08);
  TLegend *legend1=new TLegend(0.55,0.9-.2*i,0.9,0.86-.2*i);
  //(x1,y1,x2,y2)
  legend1->AddEntry(h,name,"l");
  legend1->SetTextSize(0.042);
  legend1->SetTextColor(col[i]);
  legend1->Draw();

}

void decorate(TH2* h){
TPaveStats *st=(TPaveStats*)h->FindObject("stats");
 st->SetX1NDC(0.375);
 st->SetX2NDC(0.625); 
 st->SetY1NDC(0.90);
 st->SetY2NDC(0.6);

}


void nameLegend2(const char* temp){
  string name2;
  for(int i=0;i<5;i++){
    name2[i]=*(temp+i);
  }
  sprintf(name,"%s",name2.c_str());  
  
}
