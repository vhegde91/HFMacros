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
#include"TLatex.h"
using namespace std;

class c_RatiovsAbsIeta{
public:
  void FileNames();
  void RatiovsAbsIeta1(int);
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

void c_RatiovsAbsIeta::FileNames(){
  FileList = new TList();
  // FileList->Add( TFile::Open("2016B1_E2E1HistsTrg5_Filt.root") );
  //FileList->Add(TFile::Open("2016C_Expr_E2E1HistsTrg5_Filt.root") );
  // FileList->Add(TFile::Open("2016D_Expr_E2E1HistsTrg5_Filt.root") );
  FileList->Add(TFile::Open("2016E_E2E1HistsTrg5.root") );
  // FileList->Add(TFile::Open("2016F_E2E1HistsTrg5.root") );
  // FileList->Add(TFile::Open("2016G_E2E1HistsTrg5.root") );
  //FileList->Add(TFile::Open("2016B1_E2E1HistsJetPt600.root") );
  //FileList->Add(TFile::Open("MC_Flat_PU_obs_2016B1_E2E1HistsJetPt600.root") );MCfileIndex=1;
  //  FileList->Add(TFile::Open("2016E_E2E1HistsJetPt600_Trg5.root") );
  //  FileList->Add(TFile::Open("MC_Flat_PU_obs_2016E_E2E1HistsJetPt600_18pcScaled.root") );MCfileIndex=1;
  //  FileList->Add(TFile::Open("MC_Flat_PU_obs_2016E_E2E1HistsJetPt600.root") );MCfileIndex=1;
  //  FileList->Add(TFile::Open("2016E_E2E1HistsJetPt600_Trg5_PU22toInf.root") );
  //  FileList->Add(TFile::Open("MC_Flat_PU22toInf_obs_2016E_E2E1HistsJetPt600_18pcScaled.root") );MCfileIndex=1;
  nfiles=1;
  //!!!!!!!!!! Add more colors if there are more than 5 files! *****************************
}

void RatiovsAbsIeta(int cutnum){
  c_RatiovsAbsIeta c1;
  c1.FileNames();
  c1.RatiovsAbsIeta1(cutnum);
}

void c_RatiovsAbsIeta::RatiovsAbsIeta1(int cutnum){
  sprintf(name,"MeanRatiovsIetaECut%i",cutnum);
  sprintf(title,"Mean Ratio vs Ieta ECut%i",cutnum);
  TH1D *h_mRatiovsPosIeta[nfiles], *h_mRatiovsNegIeta[nfiles];;
  TLegend *legend[nfiles];
  TFile *f1=(TFile*)FileList->First();
  for(int i=0;i<nfiles;i++){
    sprintf(name,"%s_pos",name);
    h_mRatiovsPosIeta[i]=new TH1D(name,title,14,0,14);
    sprintf(name,"%s_neg",name);
    h_mRatiovsNegIeta[i]=new TH1D(name,title,14,0,14);
    sprintf(name,"file%i",i);
  }
  gStyle->SetOptStat(0);
  TCanvas *c_cA=new TCanvas("c_mRatiovsAbsIetaCompareRuns","c_mRatiovsAbsIetaCompareRuns",1500,850);
  h_mRatiovsNegIeta[0]->SetMaximum(0.8);
  h_mRatiovsNegIeta[0]->SetMinimum(0.2);

  for(int i=0;i<nfiles;i++){
    h_mRatiovsNegIeta[i]->SetFillColor(col[i]);
    h_mRatiovsNegIeta[i]->SetLineColor(col[i]);
    h_mRatiovsNegIeta[i]->SetLineWidth(3);
    h_mRatiovsNegIeta[i]->SetLineStyle(2);
    h_mRatiovsNegIeta[i]->SetMarkerColor(col[i]);
    h_mRatiovsNegIeta[i]->SetMarkerStyle(20+i);

    h_mRatiovsPosIeta[i]->SetFillColor(col[i]);
    h_mRatiovsPosIeta[i]->SetLineColor(col[i]);
    h_mRatiovsPosIeta[i]->SetLineWidth(3);
    h_mRatiovsPosIeta[i]->SetMarkerColor(col[i]);
    h_mRatiovsPosIeta[i]->SetMarkerStyle(20+i);

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
    
    sprintf(name,"%i",abs(ieta));
    if(ieta<0){
      h_mRatiovsNegIeta[0]->Fill(name,mean);
      h_mRatiovsNegIeta[0]->SetBinError(j+1,errMean);
      h_mRatiovsNegIeta[0]->Draw();
    }
    else{
      h_mRatiovsPosIeta[0]->Fill(name,mean);
      h_mRatiovsPosIeta[0]->SetBinError(j+1-13,errMean);
      h_mRatiovsPosIeta[0]->Draw("same");
    }
  }
  h_mRatiovsNegIeta[0]->GetYaxis()->SetTitle("R_{S/L}");
  h_mRatiovsNegIeta[0]->GetYaxis()->SetTitleOffset(0.65);
  h_mRatiovsNegIeta[0]->GetYaxis()->SetTitleSize(0.05);
  h_mRatiovsNegIeta[0]->GetXaxis()->SetTitle("|i\\eta|");
  h_mRatiovsNegIeta[0]->GetXaxis()->SetTitleOffset(0.65);
  h_mRatiovsNegIeta[0]->GetXaxis()->SetTitleSize(0.05);
  h_mRatiovsNegIeta[0]->SetTitle(0);
  nameLegend(f1->GetName());
  legend[0]->AddEntry(h_mRatiovsPosIeta[0],legendName,"lep");
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
      sprintf(name,"%i",abs(ieta));
      if(ieta<0){
	h_mRatiovsNegIeta[i]->Fill(name,mean);
	h_mRatiovsNegIeta[i]->SetBinError(j+1,errMean);
      }
      else{
	h_mRatiovsPosIeta[i]->Fill(name,mean);
	h_mRatiovsPosIeta[i]->SetBinError(j+1-13,errMean);
      }
    }
    h_mRatiovsNegIeta[i]->Draw("same");
    h_mRatiovsPosIeta[i]->Draw("same");
    nameLegend(f2->GetName());
    legend[i]->AddEntry(h_mRatiovsPosIeta[i],legendName,"lep");
    legend[i]->Draw();
    f2=(TFile*)FileList->After(f2);
    i++;
  }//while
  
 
  c_cA->SetGridx();
  c_cA->SetGridy();
  TLatex Tl; Tl.SetTextFont(6); Tl.SetTextSize(35);
  sprintf(name,"EL>%s, ES>%s",ELcut.c_str(),EScut.c_str());
  Tl.DrawText(10.5, 0.25, name);
  //c_cA->Draw();
  sprintf(name,"RatiovsAbsIeta_%i.png",cutnum);
  c_cA->SaveAs(name);
 
 
}//c_RatiovsAbsIeta::RatiovsAbsIeta1
  

int c_RatiovsAbsIeta::getieta(int j){
  int ieta[26]={-41,-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,-30,-29,41,40,39,38,37,36,35,34,33,32,31,30,29};
  //  int ieta[26]={-41,-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,-30,-29,29,30,31,32,33,34,35,36,37,38,39,40,41};
  return ieta[j];
}

void c_RatiovsAbsIeta::setTruncMean(TH1D* h_hf,int i){
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

void c_RatiovsAbsIeta::nameLegend(const char* temp){
  string name2;
  for(int i=0;i<6;i++){
    name2[i]=*(temp+i);
  }
  sprintf(legendName,"%s",name2.c_str());  
  
}

