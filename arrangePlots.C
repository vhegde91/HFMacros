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


int nietaHF=26;
char name[100],title[100];

int getPadIdx(int);
int getCanvasIdx(int);
void setCanvasName(int,const char*);


void arrangePlots(const char* ifname,const char* iDirName){
  TFile *f=new TFile(ifname);
  TDirectory *dir1=(TDirectory*)f->FindObjectAny(iDirName);

  TCanvas *c_ieta[4];
  for(int i=0;i<4;i++){
    
    setCanvasName(i,iDirName);
    
    c_ieta[i]=new TCanvas(name,title,1500,1500);
    c_ieta[i]->Divide(4,2);
  }
    

  for(int i=0;i<nietaHF;i++){
   
    //cout<<"mark1"<<endl;
    sprintf(name,"Graph;%d",i+1);
    dir1->cd();
    // cout<<"mark2"<<endl;

    TGraphErrors *g1=(TGraphErrors*)dir1->FindObjectAny(name);
    
    if((g1->GetHistogram()->GetMaximumStored())<2){
      g1->GetHistogram()->SetMaximum(0.7);
      g1->GetHistogram()->SetMinimum(0.2);
    }
    TPaveStats *st1 = (TPaveStats*)g1->FindObject("stats");
    if(st1){
    st1->SetTextSize(0.03);
    st1->SetLineColor(g1->GetLineColor());
    st1->SetTextColor(g1->GetLineColor());
    //cout<<"i:"<<i<<" getCanvasIdx(i):"<<getCanvasIdx(i)<<" getPadIdx(i):"<<getPadIdx(i)<<endl;
    c_ieta[(getCanvasIdx(i))]->cd((getPadIdx(i)));
    
    g1->Draw("AP");
    }
    
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

