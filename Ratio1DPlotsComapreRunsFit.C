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
#include"TPaveStats.h"
#include"TCanvas.h"
#include"TLegend.h"

int nietaHF=26;
const int nfiles=1;    //Specify no. of files
TFile *f[nfiles];
int col[5]={kBlue,kRed,kTeal+9,kMagenta,kBlack};
double peakVal[26],trunkMean[26];
char name[100],title[100];

int getieta(int);
int getPadIdx(int);
int getCanvasIdx(int);
void setCanvasName(int,const char*);
void Ratio1DPlotsComapreRunsFit(const char* iDirName){
  TDirectory *dir[nfiles];
  TCanvas *c_ieta[4];
  //================Files to be Compared=========================
  //  f[0]=TFile::Open("MC25ns_E2E1HistsTrg5PupWt2016B.root");
  // f[1]=TFile::Open("2016B_E2E1HistsTrg5.root");
  // f[0]=TFile::Open("2015D_E2E1HistsTrg5PupWt2016B.root");
  f[0]=TFile::Open("2016B1_E2E1HistsTrg5_Filt.root");
  //  f[1]=TFile::Open("2016B3_E2E1HistsTrg5_Filt.root");
  //f[2]=TFile::Open("2016B1_E2E1HistsTrg5_Filt.root");
  //  f[1]=TFile::Open("2016C_Expr_E2E1HistsTrg5_Filt.root");
  //f[2]=TFile::Open("2016D_Expr_E2E1HistsTrg5_Filt.root");
  //f[2]=TFile::Open("254833_E2E1HistsVtx.root");
  //=============================================================
 for(int i=0;i<nfiles;i++){
   dir[i]=(TDirectory*)f[i]->FindObjectAny(iDirName);
 }
 for(int i=0;i<4;i++){
   setCanvasName(i,iDirName);
   c_ieta[i]=new TCanvas(name,title,1500,1500);
   c_ieta[i]->Divide(4,2);
 }
 gStyle->SetOptFit(1111);
 for(int j=0;j<nietaHF;j++){
   int ieta=getieta(j);
   if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i",abs(ieta));}
   else{sprintf(name,"RatioE2vsE1_ietaP%i",ieta);}
   //   cout<<j<<" "<<ieta<<endl;
   for(int i=0;i<nfiles;i++){
     TH1D *h_hf=(TH1D*)dir[i]->FindObjectAny(name);
     c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
     TF1 *fit1=new TF1("fit1","gaus",0.3,0.7);
     h_hf->Rebin(10);
     h_hf->Fit("fit1","R");
     peakVal[j]=fit1->GetParameter("Mean");
     trunkMean[j]=h_hf->GetMean();
     //h_hf->Scale(1.0/(h_hf->Integral()));
     //     h_hf->SetMaximum(0.14);
     h_hf->SetMinimum(0);
     h_hf->SetLineColor(col[i]);
     h_hf->SetLineWidth(1);
     h_hf->SetLineStyle(i+1);
     if(i==0){
       h_hf->GetXaxis()->SetTitle("Ratio");
       //h_hf->Draw("hist");
       //       h_hf->SetFillColor(col[i]-4);
       c_ieta[(getCanvasIdx(j))]->Update();
       TPaveStats *st=(TPaveStats*)h_hf->FindObject("stats");
       st->SetLineColor(col[i]);
       st->SetTextColor(col[i]);
       st->SetX1NDC(0.65);
       st->SetX2NDC(0.98); 
       st->SetY1NDC(0.90);
       st->SetY2NDC(0.70);
       TLegend *legend1=new TLegend(0.65,0.85,.98,.9);
       legend1->AddEntry(h_hf,f[i]->GetName(),"l");
       legend1->SetTextSize(0.05);
       legend1->SetTextColor(col[i]);
       legend1->Draw();
     }
     else{
       h_hf->Draw("sames ");
       //h_hf->SetLineStyle(2);
       h_hf->SetLineWidth(2);
       c_ieta[(getCanvasIdx(j))]->Update();
       TPaveStats *st=(TPaveStats*)h_hf->FindObject("stats");
       st->SetLineColor(col[i]);
       st->SetTextColor(col[i]);
       st->SetX1NDC(0.65);
       st->SetX2NDC(0.98); 
       st->SetY1NDC(0.90-i*0.2);
       st->SetY2NDC(0.70-i*0.2);
       TLegend *legend2=new TLegend(0.65,0.90-i*0.2,0.98,0.85-i*0.2);
       legend2->AddEntry(h_hf,f[i]->GetName(),"l");
       legend2->SetTextSize(0.05);
       legend2->SetTextColor(col[i]);
       legend2->Draw();
     }
    
     
   }
 }

 cout<<"Mean: {"; 
 for(int j=0;j<nietaHF;j++)   cout<<trunkMean[j]<<",";
 cout<<endl<<"Peak: {";
 for(int j=0;j<nietaHF;j++)   cout<<peakVal[j]<<",";
   
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
