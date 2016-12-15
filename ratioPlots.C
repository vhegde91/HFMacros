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

class c_ratioPlots{
public:
  void FileNames();  
  void ratioPlots1(int);
  int MCfileIndex=100;
private:
  char name[100],title[100],legendName[10];
  int nietaHF=26,niphiHF=36;
  static const int nfiles=3;
  int col[5]={kBlue,kRed,kTeal+9,kMagenta,kBlack};
  //TList *FileList;
  TFile *f[nfiles];
  double mean,errMean;

  int getieta(int);
  void setTruncMean(TH1D*,int);
  void nameLegend(const char*);
  int getPadIdx(int);
  int getCanvasIdx(int);
  void setCanvasName(int,const char*);
  bool ChnStatus(int,int,double);
};

void c_ratioPlots::FileNames(){
  // f[0]=new TFile("2015D_E2E1HistsTrgAll.root");
  f[0]=new TFile("2015D_E2E1HistsTrg5.root");
  f[1]=new TFile("2016B_E2E1HistsTrg5.root");

  //f[0]=new TFile("2015D_E2E1HistsVtxL10Trg5.root");
  /* f[1]=new TFile("2015D_E2E1HistsTrg4.root");
     f[2]=new TFile("2015D_E2E1HistsTrg3.root");
     f[3]=new TFile("2015D_E2E1HistsTrg2.root");
     f[4]=new TFile("2015D_E2E1HistsTrg1.root");*/
  //f[1]=new TFile("MC25nsPupWt_E2E1HistsTrg5.root");MCfileIndex=1;
  //f[1]=new TFile("MC25ns_E2E1HistsVtxL10Trg5.root");MCfileIndex=1;
  f[2]=new TFile("MC25ns_E2E1HistsTrg5.root");MCfileIndex=2;
  // f[1]=new TFile("257400_E2E1HistsTrgAll.root");
  //!!!!!!!!!! Add more colors if there are more than 5 files! *****************************
}

void ratioPlots(int cutnum){
  c_ratioPlots c1;
  c1.FileNames();
  c1.ratioPlots1(cutnum);
}

void c_ratioPlots::ratioPlots1(int cutnum){
  char iDirName[50];
  sprintf(iDirName,"E1E2Cut%iIetaiphi",cutnum);

  TCanvas *c_ieta[4];
  for(int i=0;i<4;i++){
    setCanvasName(i,iDirName);
    c_ieta[i]=new TCanvas(name,title,1500,850);
    c_ieta[i]->Divide(4,2);
    c_ieta[i]->SetGridx();
  }
  gStyle->SetOptStat(0);
  TH1D *h_ratioPlots[nfiles][nietaHF];
  TH2D *h2_ietavsiphi=new TH2D("ietavsiphi","Ratio as a function of ieta and iphi",84,-42,42,75,0,75);
  TLegend *legend[nfiles];
  cout<<"*********************************"<<endl<<"Problematic Channels:"<<endl<<"*********************************"<<endl;;
  for(int j=0;j<nietaHF;j++){
    for(int i=0;i<nfiles;i++){
      TDirectory *dir = (TDirectory*) f[i]->FindObjectAny(iDirName);
      int ieta;
      if(j<13)
	ieta=j+29;
      else
	ieta=-(j+16);

      if(i==0){
	if(ieta<0){sprintf(name,"MeanRatiovsIphi_ietaN%i",abs(ieta));}
	else{sprintf(name,"MeanRatiovsIphi_ietaP%i",ieta);}
	sprintf(title,"Mean Ratio vs Iphi for ieta %i ECut%i",ieta,cutnum);
      }
      else{
	if(ieta<0){sprintf(name,"fnum%i_ietaN%i",i,abs(ieta));}
	else{sprintf(name,"fnum%i_ietaP%i",i,abs(ieta));}
      }
      h_RatiovsIphi[i][j]=new TH1D(name,title,73,0,73);
      for(int k=0;k<niphiHF;k++){
	int iphi=2*k+1;
      
	if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i_iphi%i",abs(ieta),iphi);}
	else{sprintf(name,"RatioE2vsE1_ietaP%i_iphi%i",ieta,iphi);}
	TH1D *h_hf=(TH1D*)dir->FindObjectAny(name);


	setTruncMean(h_hf,i);
	delete h_hf;
	bool good=ChnStatus(ieta,iphi,mean);
	if(!good){cout<<f[i]->GetName()<<" ieta:"<<ieta<<" iphi:"<<iphi<<" mean:"<<mean<<endl;}
	h_ratioPlots[i][j]->Fill(iphi,mean);
	h_ratioPlots[i][j]->SetBinError(iphi+1,errMean);
	if(i==0){h2_ietavsiphi->Fill(ieta,iphi,mean);}
      }
      c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
      if(i==0){
	h_ratioPlots[i][j]->Draw();
	h_ratioPlots[i][j]->SetMaximum(0.8);
	h_ratioPlots[i][j]->SetMinimum(0.2);
	h_ratioPlots[i][j]->GetXaxis()->SetTitle("i\\phi");
	h_ratioPlots[i][j]->GetXaxis()->SetTitleSize(0.05);
	h_ratioPlots[i][j]->GetXaxis()->SetTitleOffset(0.94);
	h_ratioPlots[i][j]->GetYaxis()->SetTitle("R_{S/L}");
	h_ratioPlots[i][j]->GetYaxis()->SetTitleSize(0.04);
	h_ratioPlots[i][j]->GetYaxis()->SetTitleOffset(1.16);
      }
      else{h_ratioPlots[i][j]->Draw("same");}

      h_ratioPlots[i][j]->SetLineColor(col[i]);
      h_ratioPlots[i][j]->SetMarkerColor(col[i]);
      h_ratioPlots[i][j]->SetMarkerStyle(i+24);
      h_ratioPlots[i][j]->SetLineWidth(2);
      h_ratioPlots[i][j]->SetFillColor(col[i]);

      legend[i]=new TLegend(0.75,0.8-0.1*i,.98,.9-.1*i);
      nameLegend(f[i]->GetName());
      legend[i]->AddEntry(h_ratioPlots[i][j],legendName,"p");
      legend[i]->SetTextSize(0.05);
      legend[i]->SetTextColor(col[i]);
      legend[i]->Draw();
      
    }//nfiles
    
  }//ieta

  TCanvas *c_ietavsiphi=new TCanvas("R_ietavsiphi","Ratio as a function of ieta and iphi",1500,1500);
  h2_ietavsiphi->Draw("colz");
  h2_ietavsiphi->GetXaxis()->SetTitle("ieta");
  h2_ietavsiphi->GetYaxis()->SetTitle("iphi");

  for(int i=0;i<4;i++){
    sprintf(name,"%s.png",c_ieta[i]->GetName());
    // c_ieta[i]->SaveAs(name);
  }
}//c_ratioPlots::ratioPlots1
  

int c_ratioPlots::getieta(int j){
  int ieta[26]={-41,-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,-30,-29,29,30,31,32,33,34,35,36,37,38,39,40,41};
  return ieta[j];
}

void c_ratioPlots::setTruncMean(TH1D* h_hf,int i){
  int nbins=h_hf->GetNbinsX();
  // double intgrl=0,totEntries=h_hf->GetEntries();
  //double intgrl=0,totEntries=h_hf->Integral();
  double intgrl=0,totEntries;
  if(i==MCfileIndex){totEntries=h_hf->Integral();}
  else{totEntries=h_hf->GetEntries();}
  TH1D *h_hf2= new TH1D("name","title",600,0,3);
  for(int i=1;i<=nbins;i++){
    intgrl=intgrl+h_hf->GetBinContent(i);
    for(int j=0;j<(h_hf->GetBinContent(i));j++){
      h_hf2->Fill(h_hf->GetBinCenter(i));
    }
    h_hf2->SetBinError(i,h_hf->GetBinError(i));
    if((intgrl/totEntries)>0.90){break;}
  }

  mean=h_hf2->GetMean();
  if( (h_hf->GetMeanError()) > (h_hf2->GetMeanError()) ){errMean=h_hf->GetMeanError();}
  else{errMean=h_hf2->GetMeanError();}
  delete h_hf2;
}

bool c_ratioPlots::ChnStatus(int ieta,int iphi,double mean1){
  if( abs(ieta)==29 ){return true;}
  else if( abs(ieta)>=40 ){
    if( ((iphi-1)%4)==0 ){return true;}
  }
  if(mean1>0.3 && mean1<0.6){return true;}
  else{return false;}
}



void c_ratioPlots::nameLegend(const char* temp){
  string name2;
  for(int i=0;i<6;i++){
    name2[i]=*(temp+i);
  }
  sprintf(legendName,"%s",name2.c_str());  
  
}

void c_ratioPlots::setCanvasName(int i, const char* iDirName){
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


int c_ratioPlots::getPadIdx(int i){
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

int c_ratioPlots::getCanvasIdx(int i){
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


