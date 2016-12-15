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

class c_EnergyvsIphi{
public:
  void FileNames();  
  void EnergyvsIphi1(int);
  int MCfileIndex=100;
private:
  char name[100],title[100],legendName[10];
  static const int nietaHF=26,niphiHF=36;
  static const int nfiles=2;
  int col[5]={kBlue,kRed,kTeal+9,kMagenta,kBlack};
  //TList *FileList;
  TFile *f[nfiles];
  double mean,errMean;
  double meanf0[nietaHF][niphiHF];
  bool longNotShort=1;//for Long
  //bool longNotShort=0;//for Short

  int getieta(int);
  void setTruncMean(TH1D*,int);
  void nameLegend(const char*);
  int getPadIdx(int);
  int getCanvasIdx(int);
  void setCanvasName(int,const char*);
  bool ChnStatus(int,int,double);
  void CompChn(int,int,int,TH1D*);
};

void c_EnergyvsIphi::FileNames(){
  //  f[0]=new TFile("2015D_E2E1HistsTrg5.root");
  f[0]=new TFile("2016B_E2E1HistsTrg5_Final.root");
  f[1]=new TFile("2016H_E2E1HistsTrg5.root");
  //  f[1]=new TFile("2016B1_E2E2Hists_ECorrctd_Trg5.root");
  //  f[1]=new TFile("a_a.root");
  //f[0]=new TFile("2016B1_E2E1HistsTrg5_Filt.root");
  // f[1]=new TFile("2016C_Expr_E2E1HistsTrg5_Filt.root");
  //f[1]=new TFile("2016B1_E2E1Hists_Jets.root"); 
  //  f[1]=new TFile("MC_a.root");MCfileIndex=1;
 //  f[2]=new TFile("2016B2_E2E1Hists_Filt_HT2500.root");
  //  f[0]=new TFile("2016B2_E2E1HistsTrg5_Filt.root");
  //  f[1]=new TFile("2016B3_E2E1HistsTrg5_Filt.root");
  //f[2]=new TFile("SingMu2016B2_E2E1HistsTrg3_Filt.root");
  //  f[0]=new TFile("2015D_E2E1HistsTrg5PupWt2016B.root");MCfileIndex=0;
  //f[1]=new TFile("2015D_E2E1HistsTrg5PupWt2016B_Filt.root");MCfileIndex=0;

  //  f[0]=new TFile("MC25ns_E2E1HistsTrg5PupWt2016B.root");MCfileIndex=0;
  //  f[1]=new TFile("2016B_E2E1HistsTrg5.root");  
  
  //f[1]=new TFile("2015D_E2E1HistsTrg5nVtxMin16.root");

  //  f[2]=new TFile("MC25ns_2016B_E2E1HistsTrg5nVtxMin16.root");MCfileIndex=2;
  //f[0]=new TFile("2015D_E2E1HistsVtxL10Trg5.root");
  /* f[1]=new TFile("2015D_E2E1HistsTrg4.root");
     f[2]=new TFile("2015D_E2E1HistsTrg3.root");
     f[3]=new TFile("2015D_E2E1HistsTrg2.root");
     f[4]=new TFile("2015D_E2E1HistsTrg1.root");*/
   //!!!!!!!!!! Add more colors if there are more than 5 files! *****************************
}

void EnergyvsIphi(int cutnum){
  c_EnergyvsIphi c1;
  c1.FileNames();
  c1.EnergyvsIphi1(cutnum);
}

void c_EnergyvsIphi::EnergyvsIphi1(int cutnum){
  char iDirName[50];
  sprintf(iDirName,"EnergyvsIphi_cut%i",cutnum);

  TCanvas *c_ieta[4];
  for(int i=0;i<4;i++){
    setCanvasName(i,iDirName);
    c_ieta[i]=new TCanvas(name,title,1500,850);
    c_ieta[i]->Divide(4,2);
    c_ieta[i]->SetGridx();
  }
  gStyle->SetOptStat(0);
  TH1D *h_EnergyvsIphi[nfiles][nietaHF];
  TH2D *h2_ietavsiphi=new TH2D("ietavsiphi","Mean Energy as a function of ieta and iphi",84,-42,42,75,0,75);
  TLegend *legend[nfiles];
  string fiber;if(longNotShort) fiber="ELong"; else fiber="EShort";
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
	if(ieta<0){sprintf(name,"Mean%svsIphi_ietaN%i",fiber.c_str(),abs(ieta));}
	else{sprintf(name,"Mean%svsIphi_ietaP%i",fiber.c_str(),ieta);}
	sprintf(title,"Mean %s vs Iphi for ieta %i ECut%i",fiber.c_str(),ieta,cutnum);
      }
      else{
	if(ieta<0){sprintf(name,"fnum%i_ietaN%i",i,abs(ieta));}
	else{sprintf(name,"fnum%i_ietaP%i",i,abs(ieta));}
      }
      h_EnergyvsIphi[i][j]=new TH1D(name,title,73,0,73);
      for(int k=0;k<niphiHF;k++){
	int iphi=2*k+1;
	//	if(i==1) fiber="EShort";
	if(ieta<0){sprintf(name,"%s_ietaN%i_iphi%i",fiber.c_str(),abs(ieta),iphi);}
	else{sprintf(name,"%s_ietaP%i_iphi%i",fiber.c_str(),ieta,iphi);}
	TH1D *h_hf=(TH1D*)dir->FindObjectAny(name);
	setTruncMean(h_hf,i);
	bool good=ChnStatus(ieta,iphi,mean);

	//mean=h_hf->GetMean();
	h_EnergyvsIphi[i][j]->Fill(iphi,mean);
	h_EnergyvsIphi[i][j]->SetBinError(iphi+1,errMean);
	if(i==0){
	  h2_ietavsiphi->Fill(ieta,iphi,mean);
	  meanf0[j][k]=mean;
	}
	//	if(i!=0) CompChn(i,ieta,iphi,h_hf);
	if(i!=0 && abs(ieta)!=29 && (abs(meanf0[j][k]-mean)/meanf0[j][k]) > 0.03 ){
	  // cout<<ieta<<"\t"<<iphi<<"\t"<<meanf0[j][k]<<"\t"<<mean<<"\t"<<((mean-meanf0[j][k])/meanf0[j][k])*100<<endl;
	}
	delete h_hf;
      }
      c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
      if(i==0){
	h_EnergyvsIphi[i][j]->Draw();
	// h_EnergyvsIphi[i][j]->SetMaximum(40);
	// h_EnergyvsIphi[i][j]->SetMinimum(12);
	h_EnergyvsIphi[i][j]->GetXaxis()->SetTitle("i\\phi");
	h_EnergyvsIphi[i][j]->GetXaxis()->SetTitleSize(0.05);
	h_EnergyvsIphi[i][j]->GetXaxis()->SetTitleOffset(0.94);
	h_EnergyvsIphi[i][j]->GetYaxis()->SetTitle("Energy(GeV)");
	h_EnergyvsIphi[i][j]->GetYaxis()->SetTitleSize(0.04);
	h_EnergyvsIphi[i][j]->GetYaxis()->SetTitleOffset(1.16);
      }
      else{h_EnergyvsIphi[i][j]->Draw("same");}

      h_EnergyvsIphi[i][j]->SetLineColor(col[i]);
      h_EnergyvsIphi[i][j]->SetMarkerColor(col[i]);
      h_EnergyvsIphi[i][j]->SetMarkerStyle(i+24);
      h_EnergyvsIphi[i][j]->SetLineWidth(2);
      h_EnergyvsIphi[i][j]->SetFillColor(col[i]);

      legend[i]=new TLegend(0.75,0.8-0.1*i,.98,.9-.1*i);
      nameLegend(f[i]->GetName());
      legend[i]->AddEntry(h_EnergyvsIphi[i][j],legendName,"p");
      legend[i]->SetTextSize(0.05);
      legend[i]->SetTextColor(col[i]);
      legend[i]->Draw();
      
    }//nfiles
    
  }//ieta

  TCanvas *c_ietavsiphi=new TCanvas("Emean_ietavsiphi","Mean Energy as a function of ieta and iphi",1500,1500);
  h2_ietavsiphi->Draw("colz");
  h2_ietavsiphi->GetXaxis()->SetTitle("ieta");
  h2_ietavsiphi->GetYaxis()->SetTitle("iphi");
  h2_ietavsiphi->GetZaxis()->SetRangeUser(15,50);
  for(int i=0;i<4;i++){
    sprintf(name,"%s.png",c_ieta[i]->GetName());
    // c_ieta[i]->SaveAs(name);
  }
}//c_EnergyvsIphi::EnergyvsIphi1
  

int c_EnergyvsIphi::getieta(int j){
  int ieta[26]={-41,-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,-30,-29,29,30,31,32,33,34,35,36,37,38,39,40,41};
  return ieta[j];
}

void c_EnergyvsIphi::setTruncMean(TH1D* h_hf,int i){
  int nbins=h_hf->GetNbinsX();
  // double intgrl=0,totEntries=h_hf->GetEntries();
  //double intgrl=0,totEntries=h_hf->Integral();
  double intgrl=0,totEntries;
  if(i==MCfileIndex){totEntries=h_hf->Integral();}
  else{totEntries=h_hf->GetEntries();}

  TH1D *h_hf2= new TH1D("name","title",200,0,1000);
  for(int i=1;i<=nbins;i++){
    //if(h_hf->GetBinLowEdge(i)>100) break;
    intgrl=intgrl+h_hf->GetBinContent(i);
    /*
    for(int j=0;j<(h_hf->GetBinContent(i));j++){
      h_hf2->Fill(h_hf->GetBinCenter(i));
    }*/
    h_hf2->SetBinContent(i,h_hf->GetBinContent(i));
    h_hf2->SetBinError(i,h_hf->GetBinError(i));
    if((intgrl/totEntries)>0.90){break;}
  }

  mean=h_hf2->GetMean();
  if( (h_hf->GetMeanError()) > (h_hf2->GetMeanError()) ){errMean=h_hf->GetMeanError();}
  else{errMean=h_hf2->GetMeanError();}
  delete h_hf2;
}

bool c_EnergyvsIphi::ChnStatus(int ieta,int iphi,double mean1){
  if( abs(ieta)==29 ){return true;}
  else if( abs(ieta)>=40 ){
    if( ((iphi-1)%4)==0 ){return true;}
  }
  if(mean1>0.3 && mean1<0.7){return true;}
  else{return false;}
}

void c_EnergyvsIphi::CompChn(int fIndx,int ieta,int iphi,TH1D *h_hf){
  double m0=meanf0[ieta][iphi];
  setTruncMean(h_hf,fIndx);
  double meanfi=mean;
  if(abs(ieta)!=29){
    if( (abs(m0-meanfi)/m0)*100 > 10){
      cout<<f[fIndx]->GetName()<<"\t"<<meanfi<<"\t"<<f[0]->GetName()<<"\t"<<m0<<"\t"<<ieta<<"\t"<<iphi<<"\t"<<(abs(m0-meanfi)/m0)*100<<endl;
    }
  }
}

void c_EnergyvsIphi::nameLegend(const char* temp){
  string name2;
  for(int i=0;i<6;i++){
    name2[i]=*(temp+i);
  }
  sprintf(legendName,"%s",name2.c_str());  
  
}

void c_EnergyvsIphi::setCanvasName(int i, const char* iDirName){
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


int c_EnergyvsIphi::getPadIdx(int i){
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

int c_EnergyvsIphi::getCanvasIdx(int i){
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


