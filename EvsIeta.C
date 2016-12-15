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

class c_EvsIeta{
public:
  void FileNames();
  void EvsIeta1(int);
  int MCfileIndex=100;
private:
  char name[100],title[100],legendName[10];
  int nietaHF=26,niphiHF=36,nfiles;
  int col[5]={kBlue,kRed,kTeal+9,kMagenta,kBlack};
  TList *FileList;
  double mean,errMean;
  bool LongNotShort=true;//for Long
  //bool LongNotShort=false;//for Short
  int getieta(int);
  void setTruncMean(TH1D*,int);
  void nameLegend(const char*);
};

void c_EvsIeta::FileNames(){
  FileList = new TList();
  
  //FileList->Add( TFile::Open("2015D_E2E1HistsTrg5.root") );
  //FileList->Add( TFile::Open("2016B_condor_E2E1Hists.root") );
  //  FileList->Add( TFile::Open("2016B_E2E1HistsTrg5nVtxMin16.root") );
  //  FileList->Add( TFile::Open("2016B_E2E1HistsTrg5_Filt.root") );
  //FileList->Add( TFile::Open("2016B2_E2E1HistsTrg5_Filt.root") );
  // FileList->Add( TFile::Open("SingMu2016B2_E2E1HistsTrg5_Filt.root") );
  //  FileList->Add( TFile::Open("2015D_E2E1HistsTrg5PupWt2016B.root") );MCfileIndex=1;
  //FileList->Add( TFile::Open("2015D_E2E1HistsTrg5PupWt2016B_Filt.root") );MCfileIndex=1;
  //  FileList->Add( TFile::Open("2016B1_E2E1HistsTrg5_Filt.root") );
  //  FileList->Add( TFile::Open("2016B1_E2E1Hists_Jets.root") );
  //  FileList->Add( TFile::Open("2016B1_I3_E2E2Hists_Trg5.root") );
  // FileList->Add( TFile::Open("2016B1_E2E1HistsJetPt600.root") );
  // FileList->Add( TFile::Open("MC_PupWt_Flat_E2E1HistsJetPt600.root") );MCfileIndex=1;
  FileList->Add(TFile::Open("2016E_E2E1HistsJetPt600_Trg5.root") );                                                                                                  
  FileList->Add(TFile::Open("MC_Flat_PU_obs_2016E_E2E1HistsJetPt600_18pcScaled.root") );MCfileIndex=1;     
  //  FileList->Add( TFile::Open("MC25ns_E2E1HistsTrg5PupWt2016B.root") );MCfileIndex=1;

  nfiles=2;
  //!!!!!!!!!! Add more colors if there are more than 5 files! *****************************
}

void EvsIeta(int cutnum){
  c_EvsIeta c1;
  c1.FileNames();
  c1.EvsIeta1(cutnum);
}

void c_EvsIeta::EvsIeta1(int cutnum){
  sprintf(name,"MeanEvsIetaECut%i",cutnum);
  sprintf(title,"Mean Energy vs Ieta ECut%i",cutnum);
  TH1D *h_mEvsIeta[nfiles];
  TLegend *legend[nfiles];
  TFile *f1=(TFile*)FileList->First();
  for(int i=0;i<nfiles;i++){
    h_mEvsIeta[i]=new TH1D(name,title,28,0,28);
    sprintf(name,"file%i",i);
  }
  gStyle->SetOptStat(0);
  TCanvas *c_cA=new TCanvas("c_mEvsIetaCompareRuns","c_mEvsIetaCompareRuns",1500,850);
  h_mEvsIeta[0]->SetMaximum(150);
  h_mEvsIeta[0]->SetMinimum(0);
  for(int i=0;i<nfiles;i++){
    h_mEvsIeta[i]->SetFillColor(col[i]);
    h_mEvsIeta[i]->SetLineColor(col[i]);
    h_mEvsIeta[i]->SetLineWidth(2);
    h_mEvsIeta[i]->SetMarkerColor(col[i]);
    h_mEvsIeta[i]->SetMarkerStyle(20+i);
    legend[i]=new TLegend(0.75,0.85-0.05*i,.9,.9-.05*i);
    legend[i]->SetTextSize(0.04);
  }

  
  char iDirName[50];
  // sprintf(iDirName,"E1E2Cut%iRatio",cutnum); 
  sprintf(iDirName,"E1E2Cut%iEnergy",cutnum); 
                         
  TDirectory *dir = (TDirectory*) f1->FindObjectAny(iDirName);
  for(int j=0;j<nietaHF;j++){
    int ieta=getieta(j);
    if(ieta<0 && LongNotShort){sprintf(name,"EL_ietaN%i",abs(ieta));}
    else if(ieta>0 && LongNotShort){sprintf(name,"EL_ietaP%i",ieta);}
    else if(ieta<0 && !LongNotShort){sprintf(name,"ES_ietaN%i",abs(ieta));}
    else if(ieta>0 && !LongNotShort){sprintf(name,"ES_ietaP%i",ieta);}
    
    TH1D *h_new = (TH1D*)dir->FindObjectAny(name); 
    setTruncMean(h_new,0);
    delete h_new;  
    
    sprintf(name,"%i",ieta);
    h_mEvsIeta[0]->Fill(name,mean);
    h_mEvsIeta[0]->SetBinError(j+1,errMean);
  }
  h_mEvsIeta[0]->Draw();
  if(LongNotShort){h_mEvsIeta[0]->GetYaxis()->SetTitle("<Energy> in Long(GeV)");}
  else{h_mEvsIeta[0]->GetYaxis()->SetTitle("<Energy> in Short(GeV)");}
  h_mEvsIeta[0]->GetXaxis()->SetTitle("ieta");
  nameLegend(f1->GetName());
  //legend[0]->AddEntry(h_mEvsIeta[0],legendName,"lep");
  legend[0]->AddEntry(h_mEvsIeta[0],f1->GetName(),"lep");
  legend[0]->Draw();

  TFile *f2=(TFile*)FileList->After(f1);
  int i=1;
  while(f2){
    dir = (TDirectory*) f2->FindObjectAny(iDirName);
    for(int j=0;j<nietaHF;j++){
      int ieta=getieta(j);
      if(ieta<0 && LongNotShort){sprintf(name,"EL_ietaN%i",abs(ieta));}
      else if(ieta>0 && LongNotShort){sprintf(name,"EL_ietaP%i",ieta);}
      else if(ieta<0 && !LongNotShort){sprintf(name,"ES_ietaN%i",abs(ieta));}
      else if(ieta>0 && !LongNotShort){sprintf(name,"ES_ietaP%i",ieta);}
    
      TH1D *h_new = (TH1D*)dir->FindObjectAny(name); 
      setTruncMean(h_new,i);
      delete h_new; 
     
      sprintf(name,"%i",ieta);
      h_mEvsIeta[i]->Fill(name,mean);
      h_mEvsIeta[i]->SetBinError(j+1,errMean);
    }
    h_mEvsIeta[i]->Draw("same");
    nameLegend(f2->GetName());
    //legend[i]->AddEntry(h_mEvsIeta[i],legendName,"lep");
    legend[i]->AddEntry(h_mEvsIeta[i],f2->GetName(),"lep");
    legend[i]->Draw();
    f2=(TFile*)FileList->After(f2);
    i++;
  }//while
  
 
  c_cA->SetGridx();
  c_cA->SetGridy();
  //c_cA->Draw();
  c_cA->SaveAs("EvsIeta.png");
 
 
}//c_EvsIeta::EvsIeta1
  

int c_EvsIeta::getieta(int j){
  int ieta[26]={-41,-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,-30,-29,29,30,31,32,33,34,35,36,37,38,39,40,41};
  return ieta[j];
}

void c_EvsIeta::setTruncMean(TH1D* h_hf,int i){
  int nbins=h_hf->GetNbinsX();
  //  double intgrl=0,totEntries=h_hf->GetEntries();
  double intgrl=0,totEntries;
  if(i==MCfileIndex){totEntries=h_hf->Integral();}
  else{totEntries=h_hf->GetEntries();}
  //  totEntries=h_hf->Integral();
  TH1D *h_hf2= new TH1D("name","title",220,-100,1000);
  for(int i=1;i<=nbins;i++){
    intgrl=intgrl+h_hf->GetBinContent(i);
    //if(h_hf->GetBinContent(i)<100){continue;}
    h_hf2->SetBinContent(i,h_hf->GetBinContent(i));
    /*    for(int j=0;j<(h_hf->GetBinContent(i));j++){
      h_hf2->Fill(h_hf->GetBinCenter(i));
    }*/
    h_hf2->SetBinError(i,h_hf->GetBinError(i));
    if((intgrl/totEntries)>0.90){break;}
  }
  mean=h_hf->GetMean();
  errMean=h_hf->GetMeanError();
  delete h_hf2;

 

}



void c_EvsIeta::nameLegend(const char* temp){
  string name2;
  for(int i=0;i<6;i++){
    name2[i]=*(temp+i);
  }
  sprintf(legendName,"%s",name2.c_str());  
  
}

