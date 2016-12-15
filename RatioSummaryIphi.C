// You should know how many cuts are placed on Elong and Eshort. This value will be used as **** nE1E2Cuts ***.
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

const int nietaHF=26,niphiHF=36;
//int getieta(int);
TH1D *getTruncMean(TH1D*);
void RatioSummaryIphi(const char* ipfname){
  // ********************************** nE1E2Cuts **************************************
  int nE1E2Cuts=5;
  //*************************************************************************************
  char name[100],oDirName[100],iDirName[100],iDirNameRatio[100],title[100]; 
  TFile *f = new TFile(ipfname);
  sprintf(name,"mRatiovsIphi_%s",ipfname);
  TFile *fout = new TFile(name,"RECREATE");
  TObjArray Hlist(0);
  // TH1D *h_mRatiovsIphi[nE1E2Cuts];
  for(int i=0;i<nE1E2Cuts;i++){
    vector<double> mean,errMean;
    TH1D *h_mRatiovsIphi[nietaHF];

    sprintf(iDirName,"E1E2Cut%iIetaiphi",i);       
    fout->mkdir(iDirName);
    //cout<<iDirName<<endl;

    TDirectory *dir = (TDirectory*) f->FindObjectAny(iDirName);
    dir->cd();
   

    for(int j=0;j<nietaHF;j++){
      int ieta;
      if(j<13)
	ieta=j+29;
      else
	ieta=-(j+16);
      if(ieta<0){sprintf(name,"MeanRatiovsIphi_ietaN%i",abs(ieta));}
      else{sprintf(name,"MeanRatiovsIphi_ietaP%i",ieta);}
      sprintf(title,"Mean Ratio vs Iphi for ieta %i ECut%i",ieta,i);
      h_mRatiovsIphi[j]=new TH1D(name,title,73,0,73);
      //h_mRatiovsIphi[j]=new TH1D(name,title,16,0.2,0.6);
      
      mean.resize(0);
      errMean.resize(0);

      //cout<<"2222222222222ieta:"<<ieta<<" ";
      for(int k=0;k<niphiHF;k++){
	int iphi=2*k+1;

	if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i_iphi%i",abs(ieta),iphi);}
	else{sprintf(name,"RatioE2vsE1_ietaP%i_iphi%i",ieta,iphi);}
	TH1D *h_hf=(TH1D*)dir->FindObjectAny(name);
	
	TH1D *h_hf2;
	h_hf2=getTruncMean(h_hf);                          //for truncated mean uncomment this(1 of 3)
	mean.push_back(h_hf2->GetMean());                  //for truncated mean uncomment this(2 of 3)
	errMean.push_back(h_hf2->GetMeanError());          //for truncated mean uncomment this(3 of 3)
      
	//mean.push_back(h_hf->GetMean());                   //for untruncated mean uncomment this(1 of 2)
	//errMean.push_back(h_hf->GetMeanError());           //for untruncated mean uncomment this(2 of 2)

	sprintf(name,"%i",iphi);
	h_mRatiovsIphi[j]->Fill(iphi,mean[k]);
	//	h_mRatiovsIphi[j]->Fill(mean[k]);
	h_mRatiovsIphi[j]->SetBinError(iphi+1,errMean[k]);
	//cout<<ieta<<" "<<iphi<<" "<<h_hf->GetMean()<<" "<<h_hf->GetMeanError()<<endl;

	delete h_hf2;                                      //for truncated mean
      }
      Hlist.Add(h_mRatiovsIphi[j]);
    }
    fout->cd(iDirName);
    Hlist.Write();
    Hlist.Clear();
  }
 sprintf(name,"mRatiovsIphi_%s",ipfname);
 cout<<name<<" has been created"<<endl;
}



TH1D *getTruncMean(TH1D* h_hf){
  int nbins=h_hf->GetNbinsX();
  //double intgrl=0,totEntries=h_hf->GetEntries();
  double intgrl=0,totEntries=h_hf->Integral();
  TH1D *h_hf2= new TH1D("name","title",600,0,3);
  
  for(int i=1;i<=nbins;i++){
    intgrl=intgrl+h_hf->GetBinContent(i);
    for(int j=0;j<(h_hf->GetBinContent(i));j++){
      h_hf2->Fill(h_hf->GetBinCenter(i));
    }
    h_hf2->SetBinError(i,h_hf->GetBinError(i));
    if((intgrl/totEntries)>0.90){break;}
  }
  
  
  return h_hf2;
}
