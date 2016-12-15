//Arrange 1D ratio histograms in 4 canvases according to value of ieta
#include<iostream>
#include<iomanip>
#include"TH1.h"
#include"TROOT.h"
#include"TH2.h"
#include"TFile.h"
#include"TDirectory.h"
#include"TTree.h"
#include"TBrowser.h"
#include"TF1.h"
#include<string>
#include<vector>
#include"TGraphErrors.h"
#include"TGraph.h"
#include <TPaveStats.h>

int nietaHF=26;
const int nfiles=3;
TFile *f[nfiles];
char name[100],title[100];
int col2=kRed,col1=kBlue;
int getieta(int);
int getPadIdx(int);
int getCanvasIdx(int);
void setCanvasName(int,const char*);

void Ratio1DArrangeIeta(const char* iDirName){

  /* TDirectory *dir[nfiles];
  TFile *f[0]=new TFile("254833_E2E1Hists30_100.root");
  TFile *f[1]=new TFile("Run2015B_E2E1Hists30_100.root");
  TFile *f[2]=new TFile("Run2012D_E2E1Hists30_100.root");

  for(int i=0;i<3;i++){
    TDirectory *dir[i]=(TDirectory*)f[i]->FindObjectAny(iDirName);
    }*/

  //  TFile *f=new TFile("254833_E2E1HistsVtx.root");
  TFile *f1=new TFile("254833_E2E1HistsTrg.root");
  TFile *f2=new TFile("254833_E2E1HistsTrg1.root");  
  TDirectory *dir1=(TDirectory*)f1->FindObjectAny(iDirName);  
  TDirectory *dir2=(TDirectory*)f2->FindObjectAny(iDirName);

  TCanvas *c_ieta[4];
  for(int i=0;i<4;i++){
    setCanvasName(i,iDirName);
    c_ieta[i]=new TCanvas(name,title,1500,1500);
    c_ieta[i]->Divide(4,2);
  }

  TLegend *legend1=new TLegend(0.75,0.85,.9,.9);
  TLegend *legend2=new TLegend(0.75,0.8,.9,.85);
  //  gStyle->SetOptStat(0);
  for(int j=0;j<nietaHF;j++){
    int ieta=getieta(j);
    if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i",abs(ieta));}
    else{sprintf(name,"RatioE2vsE1_ietaP%i",ieta);}
    TH1D *h_hf=(TH1D*)dir1->FindObjectAny(name);
    h_hf->Rebin(10);
    dir1->cd();
    c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
    h_hf->Scale(1.0/(h_hf->Integral()));
    h_hf->SetLineColor(col1);
    h_hf->SetLineWidth(2);
    h_hf->GetXaxis()->SetTitle("Ratio");
    h_hf->SetMaximum(0.14);
    h_hf->SetMinimum(0);
    h_hf->Draw();
    TPaveStats *st=(TPaveStats*)h_hf->FindObject("stats");
    st->SetLineColor(col1);
    /* st->SetX1NDC(0.55);
    st->SetX2NDC(0.98); 
    st->SetY1NDC(0.93);
    st->SetY2NDC(0.55);*/
   
    if(j==0){
      legend1->AddEntry(h_hf,"254833","lep");
      legend1->SetTextSize(0.06);
    }

    if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i",abs(ieta));}
    else{sprintf(name,"RatioE2vsE1_ietaP%i",ieta);}
    h_hf=(TH1D*)dir2->FindObjectAny(name);
    h_hf->Rebin(10);
    dir2->cd();
    c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
    h_hf->Scale(1.0/(h_hf->Integral()));
    h_hf->SetLineColor(col2);
    h_hf->SetLineWidth(2);
    h_hf->Draw("sames");
    if(j==0){
      legend2->AddEntry(h_hf,"MC","lep");
      legend2->SetTextSize(0.06);
    }
        
    legend1->Draw();
    legend2->Draw();
    
    
  }
  
  
  
}


int getPadIdx(int i){
  int ret;
  if(i<=11){return ((i%4)+1);}
  else if(i==12){return 1;}
  else if(i>12 && i<25){return (((i-1)%4)+5);}
  else if(i==25){return 2;}
  else{
    cout<<"!!Cannot assign Pad index"<<endl;
    return -1;
  }
  
}

int getCanvasIdx(int i){
  if(i<=3){return 0;}
  else if(i<=7){return 1;}
  else if(i<=11){return 2;}
  else if(i==12){return 3;}
  else if(i<=16){return 0;}
  else if(i<=20){return 1;}
  else if(i<=24){return 2;}
  else if(i==25){return 3;}
  else{
    cout<<"!!Cannot assign Canvas index"<<endl; 
    return -1;
  }
}


void setCanvasName(int i, const char* iDirName){
  //const char* iDirName="llasd";
  // int iDirName=0;
  if(i==0){
    sprintf(name,"ieta29_32_%s",iDirName);
    sprintf(title,"%s for |ieta| 29 to 32",iDirName);
  }
  else if(i==1){
    sprintf(name,"ieta33_36_%s",iDirName);
    sprintf(title,"%s for |ieta| 33 to 36",iDirName);
  }
  else if(i==2){
    sprintf(name,"ieta37_40_%s",iDirName);
    sprintf(title,"%s for |ieta| 37 to 40",iDirName);
  }
  else if(i==3){
    sprintf(name,"ieta41_%s",iDirName);
    sprintf(title,"%s for |ieta| 41",iDirName);
  }
  
}

int getieta(int j){
  int ieta[26]={29,30,31,32,33,34,35,36,37,38,39,40,41,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39,-40,-41};
  return ieta[j];

}
