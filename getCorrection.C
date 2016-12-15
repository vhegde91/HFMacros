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

class c_getCorrection{
public:
  void FileNames();  
  void getCorrection1(int);
  int MCfileIndex=100;
private:
  char name[100],title[100],legendName[10];
  static const int nietaHF=26,niphiHF=36;
  static const int nfiles=1;
  int col=kBlue;
  //TList *FileList;
  TFile *f1;
  double mean,errMean;
  double meanf0[nietaHF][niphiHF];

  int getieta(int);
  void setTruncMean(TH1D*);
  void nameLegend(const char*);
  int getPadIdx(int);
  int getCanvasIdx(int);
  void setCanvasName(int,const char*);
  bool ChnStatus(int,int,double);
};

void c_getCorrection::FileNames(){
  // f[0]=new TFile("2015D_E2E1HistsTrgAll.root");
  //  f[0]=new TFile("2015D_E2E1HistsTrg5.root");

  //  f1=new TFile("2016B_v1_E2E1HistsTrg5.root");
  f1=new TFile("2016B_E2E1HistsTrg5_Final.root");
  //  f1=new TFile("a_a.root");
  //  f1=new TFile("2016B2_E2E1HistsTrg5_Filt.root");
  //  f[1]=new TFile("SingMu2016B2_E2E1HistsTrg3_Filt.root");
  //  f[1]=new TFile("2016B3_E2E1HistsTrg5_Filt.root");
  //  f[0]=new TFile("2015D_E2E1HistsTrg5PupWt2016B.root");MCfileIndex=0;
  //f1=new TFile("2015D_E2E1HistsTrg5PupWt2016B_Filt.root");MCfileIndex=0;

  //f1=new TFile("MC25ns_E2E1HistsTrg5PupWt2016B.root");
  //  f[1]=new TFile("2016B_E2E1HistsTrg5.root");  
  
}

void getCorrection(int cutnum){
  c_getCorrection c1;
  c1.FileNames();
  c1.getCorrection1(cutnum);
}

void c_getCorrection::getCorrection1(int cutnum){
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
  gStyle->SetOptFit(1);
  TH1D *h_RatiovsIphi[nietaHF];
  double constVal[nietaHF];
  TH2D *h2_corrFac=new TH2D("corrFac","Correction factors as a function of ieta and iphi",84,-42,42,75,0,75);
  TH1D *h_constVal=new TH1D("constVal_ieta","p0 of the fit vs i#eta",28,0,28);
  TH2D *h2_corrFacTec=new TH2D("corrFacTec","correction factors (easy to read in code) as a function of ieta and iphi",26,0,26,36,0,36);
  TLegend *legend;
  for(int j=0;j<nietaHF;j++){
    TDirectory *dir = (TDirectory*) f1->FindObjectAny(iDirName);
    int ieta;
    if(j<13)
      ieta=j+29;
    else
      ieta=-(j+16);
    constVal[j]=-1;    
    if(ieta<0){sprintf(name,"MeanRatiovsIphi_ietaN%i",abs(ieta));}
    else{sprintf(name,"MeanRatiovsIphi_ietaP%i",ieta);}
    sprintf(title,"Mean Ratio vs Iphi for ieta %i ECut%i",ieta,cutnum);
    h_RatiovsIphi[j]=new TH1D(name,title,73,0,73);
    for(int k=0;k<niphiHF;k++){
      int iphi=2*k+1;
      if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i_iphi%i",abs(ieta),iphi);}
      else{sprintf(name,"RatioE2vsE1_ietaP%i_iphi%i",ieta,iphi);}
      TH1D *h_hf=(TH1D*)dir->FindObjectAny(name);
      setTruncMean(h_hf);
      h_RatiovsIphi[j]->Fill(iphi,mean);
      h_RatiovsIphi[j]->SetBinError(iphi+1,errMean);

      delete h_hf;
    }
    c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
    TF1 ft= TF1("ft","pol0");
    h_RatiovsIphi[j]->Fit("ft");
    sprintf(name,"%i",ieta);
    h_constVal->Fill(j,ft.GetParameter("p0"));
    constVal[j]=ft.GetParameter("p0");
    //	h_constVal->SetBinError(j+1,
    //c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
    //	h2_corrFac->Fill(ieta,iphi,ft.GetParameter("p0"));
    for(int k=0;k<niphiHF;k++){
      int iphi=2*k+1;
      if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i_iphi%i",abs(ieta),iphi);}
      else{sprintf(name,"RatioE2vsE1_ietaP%i_iphi%i",ieta,iphi);}
      TH1D *h_hf=(TH1D*)dir->FindObjectAny(name);
      setTruncMean(h_hf);
      if(mean>0.00001){
	h2_corrFac->Fill(ieta,iphi,constVal[j]/mean);
	h2_corrFacTec->Fill(j,k,constVal[j]/mean);
      }
    }
    c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
    h_RatiovsIphi[j]->Draw();
    h_RatiovsIphi[j]->SetMaximum(0.8);
    h_RatiovsIphi[j]->SetMinimum(0.2);
    h_RatiovsIphi[j]->GetXaxis()->SetTitle("i\\phi");
    h_RatiovsIphi[j]->GetXaxis()->SetTitleSize(0.05);
    h_RatiovsIphi[j]->GetXaxis()->SetTitleOffset(0.94);
    h_RatiovsIphi[j]->GetYaxis()->SetTitle("R_{S/L}");
    h_RatiovsIphi[j]->GetYaxis()->SetTitleSize(0.04);
    h_RatiovsIphi[j]->GetYaxis()->SetTitleOffset(1.16);
	
    h_RatiovsIphi[j]->SetLineColor(col);
    h_RatiovsIphi[j]->SetMarkerColor(col);
    h_RatiovsIphi[j]->SetMarkerStyle(24);
    h_RatiovsIphi[j]->SetLineWidth(2);
    h_RatiovsIphi[j]->SetFillColor(col);

    legend =new TLegend(0.25,0.8,.5,.9);
    nameLegend(f1->GetName());
    legend ->AddEntry(h_RatiovsIphi[j],legendName,"p");
    legend ->SetTextSize(0.05);
    legend ->SetTextColor(col);
    legend ->Draw();    
  }//ieta



  TCanvas *c_ietavsiphi=new TCanvas("c_corrFac","Correction factors as a function of ieta and iphi",1500,1500);
  h2_corrFac->Draw("colz");
  h2_corrFac->GetXaxis()->SetTitle("ieta");
  h2_corrFac->GetYaxis()->SetTitle("iphi");
  //h2_corrFac->GetZaxis()->SetRangeUser(0.3,0.7);
  for(int i=0;i<4;i++){
    sprintf(name,"%s.png",c_ieta[i]->GetName());
    // c_ieta[i]->SaveAs(name);
  }
  TCanvas *c_constVal=new TCanvas("constVal_ieta","p0 of the fit vs i#eta");
  h_constVal->Draw("HIST");

  TFile *fout =new TFile("correctionsRatio.root","RECREATE");
  h2_corrFac->Write();
  h_constVal->Write();
  h2_corrFacTec->Write();
}//c_getCorrection::getCorrection1
  

int c_getCorrection::getieta(int j){
  int ieta[26]={-41,-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,-30,-29,29,30,31,32,33,34,35,36,37,38,39,40,41};
  return ieta[j];
}

void c_getCorrection::setTruncMean(TH1D* h_hf){
  int nbins=h_hf->GetNbinsX();
  // double intgrl=0,totEntries=h_hf->GetEntries();
  //double intgrl=0,totEntries=h_hf->Integral();
  double intgrl=0,totEntries;
  //  totEntries=h_hf->Integral();
  totEntries=h_hf->GetEntries();
  
  TH1D *h_hf2= new TH1D("name","title",600,0,3);
  for(int i=1;i<=nbins;i++){
    intgrl=intgrl+h_hf->GetBinContent(i);
    // for(int j=0;j<(h_hf->GetBinContent(i));j++){
    //   h_hf2->Fill(h_hf->GetBinCenter(i));
    // }
    h_hf2->SetBinContent(i,h_hf->GetBinContent(i));
    h_hf2->SetBinError(i,h_hf->GetBinError(i));
    if((intgrl/totEntries)>0.90){break;}
  }

  mean=h_hf2->GetMean();
  errMean=h_hf2->GetMeanError();
  //  if( (h_hf->GetMeanError()) > (h_hf2->GetMeanError()) ){errMean=h_hf->GetMeanError();}
  //else{errMean=h_hf2->GetMeanError();}
  delete h_hf2;
}

bool c_getCorrection::ChnStatus(int ieta,int iphi,double mean1){
  if( abs(ieta)==29 ){return true;}
  else if( abs(ieta)>=40 ){
    if( ((iphi-1)%4)==0 ){return true;}
  }
  if(mean1>0.3 && mean1<0.7){return true;}
  else{return false;}
}

void c_getCorrection::nameLegend(const char* temp){
  string name2;
  for(int i=0;i<6;i++){
    name2[i]=*(temp+i);
  }
  sprintf(legendName,"%s",name2.c_str());  
  
}

void c_getCorrection::setCanvasName(int i, const char* iDirName){
  //const char* iDirName="llasd";
  // int iDirName=0;
  if(i==0){
    sprintf(name,"ieta29_32_%s_Fit",iDirName);
    sprintf(title,"%s for |ieta| 29 to 32",iDirName);
  }
  else if(i==1){
    sprintf(name,"ieta33_36_%s_Fit",iDirName);
    sprintf(title,"%s for |ieta| 33 to 36",iDirName);
  }
  else if(i==2){
    sprintf(name,"ieta37_40_%s_Fit",iDirName);
    sprintf(title,"%s for |ieta| 37 to 40",iDirName);
  }
  else if(i==3){
    sprintf(name,"ieta41_%s_Fit",iDirName);
    sprintf(title,"%s for |ieta| 41",iDirName);
  }
  
}


int c_getCorrection::getPadIdx(int i){
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

int c_getCorrection::getCanvasIdx(int i){
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


