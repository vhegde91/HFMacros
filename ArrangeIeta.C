//this will arrange plots into 4 canvases accoring to ieta values for 3 files
#include"TH1.h"
#include"TFile.h"
#include<iostream>
#include<iomanip>
#include"TROOT.h"
#include"TH2.h"
#include"TDirectory.h"
#include"TTree.h"
#include"TBrowser.h"
#include"TF1.h"
#include<string>
#include<vector>
#include"TGraphErrors.h"
#include"TGraph.h"

//using namepsace std;

char name[100],title[100];
int nietaHF=26,niphiHF=36;
int getPadIdx(int);
int getCanvasIdx(int);
void setCanvasName(int,const char*);
void ArrangeIeta(const char* iDirName){
  //  TFile *f=new TFile(ipfname);
  TFile *f[3];
  f[0]=new TFile("mRatiovsIphi_2012D_E2E1HistsVtx.root");
  // f[1]=new TFile("mRatiovsIphi_2015B_E2E1HistsVtx.root");
  //f[2]=new TFile("mRatiovsIphi_254833_E2E1HistsVtx.root");
  // f[0]=new TFile("mRatiovsIphi_2012D_E2E1HistsVtx30_40_100.root");
  f[1]=new TFile("mRatiovsIphi_MC_E2E1HistsTrg1.root");
  f[2]=new TFile("mRatiovsIphi_254833_E2E1HistsTrg1.root");


  TCanvas *c_ieta[4];
  for(int i=0;i<4;i++){
   
    setCanvasName(i,iDirName);
    
    c_ieta[i]=new TCanvas(name,title,1500,1500);
    c_ieta[i]->Divide(4,2);
    c_ieta[i]->SetGridx();
  }

  
  gStyle->SetOptStat(0);
  for(int i=0;i<3;i++){
   
    /*    //=========================================================
    TDirectory *dir1;
    if(i==0){dir1=(TDirectory*)f[i]->FindObjectAny("E1E2Cut4Ietaiphi");}
    else{dir1=(TDirectory*)f[i]->FindObjectAny("E1E2Cut4Ietaiphi");}*/
    //==========================================================
    TDirectory *dir1=(TDirectory*)f[i]->FindObjectAny(iDirName);
    for(int j=0;j<nietaHF;j++){
      int ieta;
      if(j<13)
	ieta=j+29;
      else
	ieta=-(j+16);
      //cout<<"mark1"<<endl;
      if(ieta<0){sprintf(name,"MeanRatiovsIphi_ietaN%i",abs(ieta));}
      else{sprintf(name,"MeanRatiovsIphi_ietaP%i",ieta);}
      dir1->cd();
      TH1D *h1=(TH1D*)dir1->FindObjectAny(name);
      h1->SetMaximum(0.8);
      h1->SetMinimum(0.2);
      h1->GetXaxis()->SetTitle("iphi");
      h1->GetYaxis()->SetTitle("Ratio");
      c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
      
      if(i==0){
	h1->Draw();
	h1->SetLineColor(kTeal+9);
	h1->SetMarkerColor(kTeal+9);
	h1->SetLineWidth(2);
	h1->SetFillColor(kTeal+9);
	TLegend *legend=new TLegend(0.75,0.8,.98,.9);
	legend->AddEntry(h1,"2012D","L");
	legend->SetTextSize(0.05);
	legend->Draw();
      }
      else{
	if(i==1){
	  h1->SetLineColor(kRed);
	  h1->SetMarkerColor(kRed);
	  TLegend *legend=new TLegend(0.75,0.7,.98,.8);
	  legend->AddEntry(h1,"2015B","L");
	  legend->SetTextSize(0.05);
	  legend->Draw();
	}
	if(i==2){
	  h1->SetLineColor(kBlue);
	  h1->SetMarkerColor(kBlue);
	  TLegend *legend=new TLegend(0.75,0.6,.98,.7);
	  legend->AddEntry(h1,"2015C","L");
	  legend->SetTextSize(0.05);
	  legend->Draw();
	}
	h1->SetLineWidth(2);

	h1->Draw("same");
      }      
     

      // cout<<"mark2"<<endl;
    }
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



/*
TCanvas *c_ieta[7];
  for(int i=0;i<7;i++){
   
    //setCanvasName(i,iDirName);
    sprintf(name,"Set%i",i);
    c_ieta[i]=new TCanvas(name,title,1500,1500);
    c_ieta[i]->Divide(2,2);
  }

  
  gStyle->SetOptStat(0);
  for(int i=0;i<3;i++){
    TDirectory *dir1=(TDirectory*)f[i]->FindObjectAny(iDirName);
    for(int j=0;j<12;j++){
      int ieta;
      if(j<13)
	ieta=j+29;
      else
	ieta=-(j+16);
      //cout<<"mark1"<<endl;
      if(ieta<0){sprintf(name,"MeanRatiovsIphi_ietaN%i",abs(ieta));}
      else{sprintf(name,"MeanRatiovsIphi_ietaP%i",ieta);}
      dir1->cd();
      TH1D *h1=(TH1D*)dir1->FindObjectAny(name);
      h1->SetMaximum(0.9);
      h1->SetMinimum(0.25);
      h1->GetXaxis()->SetTitle("ihpi");
      h1->GetYaxis()->SetTitle("Ratio");
      c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
      
      if(i==0){
	h1->Draw();
	h1->SetLineColor(kGreen);
	h1->SetMarkerColor(kGreen);
	h1->SetLineWidth(2);
	h1->SetFillColor(kGreen);
	TLegend *legend=new TLegend(0.75,0.8,.98,.9);
	legend->AddEntry(h1,"2012D","L");
	legend->SetTextSize(0.05);
	legend->Draw();
      }
      else{
	if(i==1){
	  h1->SetLineColor(kRed);
	  h1->SetMarkerColor(kRed);
	  TLegend *legend=new TLegend(0.75,0.7,.98,.8);
	  legend->AddEntry(h1,"2015B","L");
	  legend->SetTextSize(0.05);
	  legend->Draw();
	}
	if(i==2){
	  h1->SetLineColor(kBlue);
	  h1->SetMarkerColor(kBlue);
	  TLegend *legend=new TLegend(0.75,0.6,.98,.7);
	  legend->AddEntry(h1,"2015C","L");
	  legend->SetTextSize(0.05);
	  legend->Draw();
	}
	h1->SetLineWidth(2);

	h1->Draw("same");
      }      
     

      // cout<<"mark2"<<endl;
    }
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
  if(i<=1){return 0;}
  else if(i<=3){return 1;}
  else if(i<=5){return 2;}
  else if(i==7){return 3;}
  else if(i<=9){return 4;}
  else if(i<=11){return 5;}
  else if(i<=24){return 2;}
  else if(i==25){return 3;}
  else{
    cout<<"!!Cannot assign Canvas index"<<endl; 
    return -1;
  }
}*/
