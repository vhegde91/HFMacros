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

class c_RMSvsIphi{
public:
  void FileNames();  
  void RMSvsIphi1(int);
  int MCfileIndex=100;
private:
  char name[100],title[100],legendName[10];
  static const int nietaHF=26,niphiHF=36;
  static const int nfiles=2;
  int col[5]={kRed,kBlue,kTeal+9,kMagenta,kBlack};
  //TList *FileList;
  TFile *f[nfiles];
  double rms,errRMS;
  double rmsf0[nietaHF][niphiHF];
  string ELcut,EScut;

  int getieta(int);
  void setTruncRms(TH1D*,int);
  void nameLegend(const char*);
  int getPadIdx(int);
  int getCanvasIdx(int);
  void setCanvasName(int,const char*);
  bool ChnStatus(int,int,double);
  void CompChn(int,int,int,TH1D*);
};

void c_RMSvsIphi::FileNames(){
  // f[0]=new TFile("2015D_E2E1HistsTrgAll.root");
  //  f[0]=new TFile("2015D_E2E1HistsTrg5.root");
  //  f[0]=new TFile("2016B1_RcorrWhileFill_E2E2Hists_Trg5.root");
  //  f[1]=new TFile("2016B3_RcorrWhileFill_E2E2Hists_Trg5.root");
  // f[0]=new TFile("2016B1_E2E1HistsTrg5_Filt.root");
  // f[1]=new TFile("2016C_Expr_E2E1HistsTrg5_Filt.root");
  // f[2]=new TFile("2016D_Expr_E2E1HistsTrg5_Filt.root");
  // f[3]=new TFile("2016E_E2E1HistsTrg5.root");
  //  f[0]=new TFile("2016B_v1_E2E1HistsTrg5.root");
  //f[0]=new TFile("2016E_E2E1HistsTrg5.root");
  // f[2]=new TFile("2016F_E2E1HistsTrg5.root");
  // f[3]=new TFile("2016G_E2E1HistsTrg5.root");
  //  f[1]=new TFile("2016B1_E2E1Hists_Jets.root"); 
  //  f[1]=new TFile("2016B1_E2E2Hists_ECorrctd_Trg5.root");
  //  f[1]=new TFile("2016B2_E2E1HistsTrg5_Filt.root");
  //f[0]=new TFile("2016B3_E2E1HistsTrg5_Filt.root");
  //  f[0]=new TFile("2016B3_RcorrWhileFill_E2E2Hists_Trg5.root");
  //  f[2]=new TFile("SingMu2016B2_E2E1HistsTrg3_Filt.root");
  //  f[0]=new TFile("2015D_E2E1HistsTrg5PupWt2016B.root");MCfileIndex=0;
  //f[1]=new TFile("2015D_E2E1HistsTrg5PupWt2016B_Filt.root");MCfileIndex=0;
  f[0]=new TFile("2016E_E2E1HistsJetPt600_Trg5.root");
  f[1]=new TFile("MC_Flat_PU_obs_2016E_E2E1HistsJetPt600_18pcScaled.root");MCfileIndex=1;
  //f[1]=new TFile("2015D_E2E1HistsTrg5nVtxMin16.root");
  //  f[0]=new TFile("2016B1_E2E1HistsJetPt600.root");
  //  f[1]=new TFile("MC_Flat_PU_obs_2016B1_E2E1HistsJetPt600.root");MCfileIndex=1;
   //!!!!!!!!!! Add more colors if there are more than 5 files! *****************************
}

void RMSvsIphi(int cutnum){
  c_RMSvsIphi c1;
  c1.FileNames();
  c1.RMSvsIphi1(cutnum);
}

void c_RMSvsIphi::RMSvsIphi1(int cutnum){
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
  TH1D *h_RMSvsIphi[nfiles][nietaHF];
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
	if(ieta<0){sprintf(name,"RmsRMSvsIphi_ietaN%i",abs(ieta));}
	else{sprintf(name,"RmsRMSvsIphi_ietaP%i",ieta);}
	sprintf(title,"Rms Ratio vs Iphi for ieta %i ECut%i",ieta,cutnum);
      }
      else{
	if(ieta<0){sprintf(name,"fnum%i_ietaN%i",i,abs(ieta));}
	else{sprintf(name,"fnum%i_ietaP%i",i,abs(ieta));}
      }
      h_RMSvsIphi[i][j]=new TH1D(name,title,73,0,73);
      for(int k=0;k<niphiHF;k++){
	int iphi=2*k+1;
      
	if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i_iphi%i",abs(ieta),iphi);}
	else{sprintf(name,"RatioE2vsE1_ietaP%i_iphi%i",ieta,iphi);}
	TH1D *h_hf=(TH1D*)dir->FindObjectAny(name);
	setTruncRms(h_hf,i);
	bool good=ChnStatus(ieta,iphi,rms);
	if(!good){cout<<f[i]->GetName()<<" ieta:"<<ieta<<" iphi:"<<iphi<<" RMS:"<<rms<<endl;}
	//	if(ieta==35) cout<<rms<<",";
	h_RMSvsIphi[i][j]->Fill(iphi,rms);
	h_RMSvsIphi[i][j]->SetBinError(iphi+1,errRMS);
	if(i==0){
	  h2_ietavsiphi->Fill(ieta,iphi,rms);
	  rmsf0[j][k]=rms;
	}
	//	if(i!=0) CompChn(i,ieta,iphi,h_hf);
	// if(i!=0 && abs(ieta)!=29 && (abs(rmsf0[j][k]-rms)/rmsf0[j][k]) > 0.05 ){
	//   cout<<ieta<<"\t"<<iphi<<"\t"<<rmsf0[j][k]<<"\t"<<rms<<"\t"<<((rms-rmsf0[j][k])/rmsf0[j][k])*100<<endl;
	// }
	if(j==0 && i==0){
	  int iStart=-100;
	  string s1=h_hf->GetTitle();
	  ELcut=s1.substr(s1.find("E1>")+3,4);
	  EScut=s1.substr(s1.find("E2>")+3,4);
	}
	delete h_hf;
      }
      c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
      if(i==0){
	h_RMSvsIphi[i][j]->Draw();
	h_RMSvsIphi[i][j]->SetMaximum(0.4);
	h_RMSvsIphi[i][j]->SetMinimum(0.0);
	h_RMSvsIphi[i][j]->GetXaxis()->SetTitle("i\\phi");
	h_RMSvsIphi[i][j]->GetXaxis()->SetTitleSize(0.05);
	h_RMSvsIphi[i][j]->GetXaxis()->SetTitleOffset(0.94);
	h_RMSvsIphi[i][j]->GetYaxis()->SetTitle("R_{S/L}");
	h_RMSvsIphi[i][j]->GetYaxis()->SetTitleSize(0.04);
	h_RMSvsIphi[i][j]->GetYaxis()->SetTitleOffset(1.16);

	TLatex Tl; Tl.SetTextFont(43); Tl.SetTextSize(35);
	sprintf(name,"#font[22]{i#eta %s}",to_string(ieta).c_str());
	Tl.DrawLatex(30,0.25, name); 
	Tl.SetTextSize(18);
	sprintf(name,"R_{S/L} vs i#phi (E_{L} > %s, E_{S} > %s)",ELcut.c_str(),EScut.c_str());
	Tl.DrawLatex(8,0.82, name);
      }
      else{h_RMSvsIphi[i][j]->Draw("same");}

      h_RMSvsIphi[i][j]->SetLineColor(col[i]);
      h_RMSvsIphi[i][j]->SetMarkerColor(col[i]);
      h_RMSvsIphi[i][j]->SetMarkerStyle(i+24);
      h_RMSvsIphi[i][j]->SetLineWidth(2);
      h_RMSvsIphi[i][j]->SetFillColor(col[i]);
      h_RMSvsIphi[i][j]->SetTitle(0);

      legend[i]=new TLegend(0.75,0.8-0.1*i,.98,.9-.1*i);
      nameLegend(f[i]->GetName());
      legend[i]->AddEntry(h_RMSvsIphi[i][j],legendName,"p");
      legend[i]->SetTextSize(0.05);
      legend[i]->SetTextColor(col[i]);
      legend[i]->Draw();
      
    }//nfiles
    
  }//ieta

  TCanvas *c_ietavsiphi=new TCanvas("R_ietavsiphi","Ratio as a function of ieta and iphi",1500,1500);
  h2_ietavsiphi->Draw("colz");
  h2_ietavsiphi->GetXaxis()->SetTitle("ieta");
  h2_ietavsiphi->GetYaxis()->SetTitle("iphi");
  h2_ietavsiphi->GetZaxis()->SetRangeUser(0.3,0.7);
  for(int i=0;i<4;i++){
    sprintf(name,"%s.png",c_ieta[i]->GetName());
    //    c_ieta[i]->SaveAs(name);
  }
}//c_RMSvsIphi::RMSvsIphi1
  

int c_RMSvsIphi::getieta(int j){
  int ieta[26]={-41,-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,-30,-29,29,30,31,32,33,34,35,36,37,38,39,40,41};
  return ieta[j];
}

void c_RMSvsIphi::setTruncRms(TH1D* h_hf,int i){
  int nbins=h_hf->GetNbinsX();
  // double intgrl=0,totEntries=h_hf->GetEntries();
  //double intgrl=0,totEntries=h_hf->Integral();
  double intgrl=0,totEntries;
  if(i==MCfileIndex){totEntries=h_hf->Integral();}
  else{totEntries=h_hf->GetEntries();}

  TH1D *h_hf2= new TH1D("name","title",600,0,3);
  for(int i=1;i<=nbins;i++){
    intgrl=intgrl+h_hf->GetBinContent(i);
    h_hf2->SetBinContent(i,h_hf->GetBinContent(i));
    /*
    for(int j=0;j<(h_hf->GetBinContent(i));j++){
      h_hf2->Fill(h_hf->GetBinCenter(i));
    }*/
    h_hf2->SetBinError(i,h_hf->GetBinError(i));
    if((intgrl/totEntries)>0.90){break;}
  }

  // rms=h_hf2->GetRms();
  // errRms=h_hf2->GetRmsError();
  rms=h_hf2->GetRMS();
  errRMS=h_hf2->GetRMSError();
  //if( (h_hf->GetMeanError()) > (h_hf2->GetMeanError()) ){errMean=h_hf->GetMeanError();}
  //  else{errMean=h_hf2->GetMeanError();}
  delete h_hf2;
}

bool c_RMSvsIphi::ChnStatus(int ieta,int iphi,double rms1){
  if( abs(ieta)==29 ){return true;}
  else if( abs(ieta)>=40 ){
    if( ((iphi-1)%4)==0 ){return true;}
  }
  if(rms1>0.3 && rms1<0.7){return true;}
  else{return false;}
}

void c_RMSvsIphi::CompChn(int fIndx,int ieta,int iphi,TH1D *h_hf){
  double m0=rmsf0[ieta][iphi];
  setTruncRms(h_hf,fIndx);
  double rmsfi=rms;
  if(abs(ieta)!=29){
    if( (abs(m0-rmsfi)/m0)*100 > 10){
      cout<<f[fIndx]->GetName()<<"\t"<<rmsfi<<"\t"<<f[0]->GetName()<<"\t"<<m0<<"\t"<<ieta<<"\t"<<iphi<<"\t"<<(abs(m0-rmsfi)/m0)*100<<endl;
    }
  }
}

void c_RMSvsIphi::nameLegend(const char* temp){
  string name2;
  for(int i=0;i<6;i++){
    name2[i]=*(temp+i);
  }
  sprintf(legendName,"%s",name2.c_str());  
  
}

void c_RMSvsIphi::setCanvasName(int i, const char* iDirName){
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


int c_RMSvsIphi::getPadIdx(int i){
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

int c_RMSvsIphi::getCanvasIdx(int i){
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


