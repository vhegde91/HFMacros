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
#include"TCanvas.h"
#include"TPaveStats.h"
#include"TLegend.h"
#include"TStyle.h"
using namespace std;

class c_RatiovsIeta{
public:
  void FileNames();
  void RatiovsIeta1(int);
  int MCfileIndex=100;
private:
  char name[100],title[100],legendName[10];
  int nietaHF=26,niphiHF=36,nfiles;
  int col[5]={kRed,kBlue,kTeal+9,kMagenta,kBlack};
  TList *FileList;
  double mean,errMean;
  string ELcut,EScut;

  int getieta(int);
  void setTruncMean(TH1D*,int);
  void nameLegend(const char*);
};

void c_RatiovsIeta::FileNames(){
  FileList = new TList();

  //  FileList->Add(TFile::Open("2015D_E2E1HistsTrg5.root") ); //w/o filters
  FileList->Add(TFile::Open("2015D_E2E1HistsTrg5PupWt2016B.root") );MCfileIndex=0;//w/o filters
  FileList->Add(TFile::Open("2016B_E2E1HistsTrg5.root") );//w/o filters
  // FileList->Add( TFile::Open("2016B1_E2E1HistsTrg5_Filt.root") );
  // FileList->Add(TFile::Open("2016C_Expr_E2E1HistsTrg5_Filt.root") );
  // FileList->Add(TFile::Open("2016D_Expr_E2E1HistsTrg5_Filt.root") );
  //  FileList->Add(TFile::Open("2016B_v1_E2E1HistsTrg5.root") );
  //  FileList->Add(TFile::Open("2016B_E2E1HistsTrg5_Final.root") );
  // FileList->Add(TFile::Open("2016E_E2E1HistsTrg5.root") );
  // FileList->Add(TFile::Open("2016E_RecHitsBasedOnJets_E2E1HistsTrg5.root") );
  // FileList->Add(TFile::Open("2016F_E2E1HistsTrg5.root") );
  // FileList->Add(TFile::Open("2016G_E2E1HistsTrg5.root") );
  // FileList->Add(TFile::Open("2016H_E2E1HistsTrg5.root") );
  //  FileList->Add(TFile::Open("2016B1_E2E1HistsJetPt600.root") );
  //FileList->Add(TFile::Open("MC_Flat_PU_obs_2016B1_E2E1HistsJetPt600.root") );MCfileIndex=1;
  // FileList->Add(TFile::Open("2016E_E2E1HistsJetPt600_Trg5.root") );
  //  FileList->Add(TFile::Open("MC_Flat_PU_obs_2016E_E2E1HistsJetPt600_18pcScaled.root") );MCfileIndex=1;
  //  FileList->Add(TFile::Open("MC_Flat_PU_obs_2016E_E2E1HistsJetPt600.root") );MCfileIndex=1;
  //  FileList->Add(TFile::Open("2016E_E2E1HistsJetPt600_Trg5_PU22toInf.root") );
  //  FileList->Add(TFile::Open("MC_Flat_PU22toInf_obs_2016E_E2E1HistsJetPt600_18pcScaled.root") );MCfileIndex=1;
  //  FileList->Add(TFile::Open("2016B1_E2E1Hists_Jets.root") );
  // FileList->Add( TFile::Open("SingMu2016B2_E2E1HistsTrg1_Filt.root") );  
  // FileList->Add( TFile::Open("SingMu2016B2_E2E1HistsTrg2_Filt.root") );
  // FileList->Add( TFile::Open("SingMu2016B2_E2E1HistsTrg3_Filt.root") );
  //  FileList->Add( TFile::Open("2016B3_E2E1HistsTrg5_Filt.root") );
  //  FileList->Add( TFile::Open("2016B2_E2E1HistsTrg5_Filt.root") );
  //FileList->Add( TFile::Open("2016B2_E2E1HistsTrg5_Jets.root") );
  //FileList->Add(TFile::Open("MC_Flat_E2E1HistsTrg5_Jets.root") );MCfileIndex=1;

  //  FileList->Add(TFile::Open("2016B_E2E1Hists.root") );
  //  FileList->Add(TFile::Open("2016C_Expr_E2E1HistsTrg5_Filt.root") );
  //  FileList->Add( TFile::Open("2016B1_E2E1HistsTrg5_Filt.root") );
  
  //FileList->Add(TFile::Open("2015D_E2E1HistsTrg5PupWt2016B.root") );MCfileIndex=1;
  //  FileList->Add(TFile::Open("2015D_E2E1HistsTrg5PupWt2016B_Filt.root") );MCfileIndex=1;
  //  FileList->Add( TFile::Open("MC25ns_E2E1HistsTrg5PupWt2016B.root") );MCfileIndex=1;
  //FileList->Add( TFile::Open("MC25ns_E2E1HistsTrg5_2016B.root") );MCfileIndex=1;
  //  FileList->Add( TFile::Open("MC25ns_E2E1HistsTrg5_300to470.root") );
  //FileList->Add( TFile::Open("MC25ns_E2E1HistsTrg5_3200toInf.root") );
  //FileList->Add( TFile::Open("2015D_E2E1HistsTrg5nVtxMin16.root") );
  //FileList->Add( TFile::Open("2016B_E2E1HistsTrg5nVtxMin16.root") );
  //FileList->Add( TFile::Open("MC25ns_2016B_E2E1HistsTrg5nVtxMin16.root") );MCfileIndex=1;
  //FileList->Add( TFile::Open("MC25ns_E2E1HistsTrg5.root") );MCfileIndex=2;
  nfiles=2;
  //!!!!!!!!!! Add more colors if there are more than 5 files! *****************************
}

void RatiovsIeta(int cutnum){
  c_RatiovsIeta c1;
  c1.FileNames();
  c1.RatiovsIeta1(cutnum);
}

void c_RatiovsIeta::RatiovsIeta1(int cutnum){
  sprintf(name,"MeanRatiovsIetaECut%i",cutnum);
  sprintf(title,"Mean Ratio vs Ieta ECut%i",cutnum);
  TH1D *h_mRatiovsIeta[nfiles];
  TLegend *legend[nfiles];
  TFile *f1=(TFile*)FileList->First();
  for(int i=0;i<nfiles;i++){
    h_mRatiovsIeta[i]=new TH1D(name,title,28,0,28);
    sprintf(name,"file%i",i);
  }
  gStyle->SetOptStat(0);
  TCanvas *c_cA=new TCanvas("c_mRatiovsIetaCompareRuns","c_mRatiovsIetaCompareRuns",1500,850);
  h_mRatiovsIeta[0]->SetMaximum(0.8);
  h_mRatiovsIeta[0]->SetMinimum(0.2);
  for(int i=0;i<nfiles;i++){
    h_mRatiovsIeta[i]->SetFillColor(col[i]);
    h_mRatiovsIeta[i]->SetLineColor(col[i]);
    h_mRatiovsIeta[i]->SetLineWidth(2);
    h_mRatiovsIeta[i]->SetMarkerColor(col[i]);
    h_mRatiovsIeta[i]->SetMarkerStyle(20+i);
    legend[i]=new TLegend(0.75,0.85-0.05*i,.9,.9-.05*i);
    legend[i]->SetTextSize(0.04);
  }

  
  char iDirName[50];
  sprintf(iDirName,"E1E2Cut%iRatio",cutnum); 
                         
  TDirectory *dir = (TDirectory*) f1->FindObjectAny(iDirName);
  for(int j=0;j<nietaHF;j++){
    int ieta=getieta(j);
    if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i",abs(ieta));}
    else{sprintf(name,"RatioE2vsE1_ietaP%i",ieta);}
    TH1D *h_hf=(TH1D*)dir->FindObjectAny(name);
    setTruncMean(h_hf,0);
    if(j==0){
      int iStart=-100;
      string s1=h_hf->GetTitle();
      ELcut=s1.substr(s1.find("E1>")+3,4);
      EScut=s1.substr(s1.find("E2>")+3,4);
    }
    delete h_hf;  
    
    sprintf(name,"%i",ieta);
    h_mRatiovsIeta[0]->Fill(name,mean);
    h_mRatiovsIeta[0]->SetBinError(j+1,errMean);
  }
  h_mRatiovsIeta[0]->Draw();
  h_mRatiovsIeta[0]->GetYaxis()->SetTitle("R_{S/L}");
  h_mRatiovsIeta[0]->GetYaxis()->SetTitleOffset(0.65);
  h_mRatiovsIeta[0]->GetYaxis()->SetTitleSize(0.05);
  h_mRatiovsIeta[0]->GetXaxis()->SetTitle("i\\eta");
  h_mRatiovsIeta[0]->GetXaxis()->SetTitleOffset(0.65);
  h_mRatiovsIeta[0]->GetXaxis()->SetTitleSize(0.05);
  h_mRatiovsIeta[0]->SetTitle(0);
  nameLegend(f1->GetName());
  legend[0]->AddEntry(h_mRatiovsIeta[0],legendName,"lep");
  legend[0]->Draw();

  TFile *f2=(TFile*)FileList->After(f1);
  int i=1;
  while(f2){
    dir = (TDirectory*) f2->FindObjectAny(iDirName);
    for(int j=0;j<nietaHF;j++){
      int ieta=getieta(j);
      if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i",abs(ieta));}
      else{sprintf(name,"RatioE2vsE1_ietaP%i",ieta);}
      TH1D *h_hf=(TH1D*)dir->FindObjectAny(name);
      setTruncMean(h_hf,i);
      delete h_hf;  
      sprintf(name,"%i",ieta);
      h_mRatiovsIeta[i]->Fill(name,mean);
      h_mRatiovsIeta[i]->SetBinError(j+1,errMean);
    }
    h_mRatiovsIeta[i]->Draw("same");
    nameLegend(f2->GetName());
    legend[i]->AddEntry(h_mRatiovsIeta[i],legendName,"lep");
    legend[i]->Draw();
    f2=(TFile*)FileList->After(f2);
    i++;
  }//while
  
 
  c_cA->SetGridx();
  c_cA->SetGridy();
  //  TLatex Tl; Tl.SetTextFont(6); Tl.SetTextSize(35);
  TPaveText *pt = new TPaveText(21,0.25,28,0.3);
  sprintf(name,"EL>%s, ES>%s",ELcut.c_str(),EScut.c_str());
  //  Tl.DrawText(21, 0.25, name);
  //c_cA->Draw();
  pt->AddText(name);pt->SetShadowColor(0);pt->SetFillColor(0);pt->Draw();
  sprintf(name,"RatiovsIeta_%i.png",cutnum);
  c_cA->SaveAs(name);
 
 
}//c_RatiovsIeta::RatiovsIeta1
  

int c_RatiovsIeta::getieta(int j){
  int ieta[26]={-41,-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,-30,-29,29,30,31,32,33,34,35,36,37,38,39,40,41};
  return ieta[j];
}

void c_RatiovsIeta::setTruncMean(TH1D* h_hf,int i){
  int nbins=h_hf->GetNbinsX();
  //  double intgrl=0,totEntries=h_hf->GetEntries();
  double intgrl=0,totEntries;
  if(i==MCfileIndex){totEntries=h_hf->Integral();}
  else{totEntries=h_hf->GetEntries();}
  //  totEntries=h_hf->Integral();
  TH1D *h_hf2= new TH1D("name","title",600,0,3);
  for(int i=1;i<=nbins;i++){
    intgrl=intgrl+h_hf->GetBinContent(i);
    h_hf2->SetBinContent(i,h_hf->GetBinContent(i));/*
    for(int j=0;j<(h_hf->GetBinContent(i));j++){
      h_hf2->Fill(h_hf->GetBinCenter(i));
    }*/
    h_hf2->SetBinError(i,h_hf->GetBinError(i));
    if((intgrl/totEntries)>0.90){break;}
  }

  mean=h_hf2->GetMean();/*
  if( (h_hf->GetMeanError()) > (h_hf2->GetMeanError()) ){errMean=h_hf->GetMeanError();}
  else{errMean=h_hf2->GetMeanError();}*/
  errMean=h_hf2->GetMeanError();
  delete h_hf2;
}

void c_RatiovsIeta::nameLegend(const char* temp){
  string name2;
  for(int i=0;i<5;i++){
    name2[i]=*(temp+i);
  }
  sprintf(legendName,"%s",name2.c_str());  
  
}

