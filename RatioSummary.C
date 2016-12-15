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
//double fitMax[nietaHF]={0.169916,0.163957,0.192013,0.256217,0.375591,0.406287,0.407111,0.412611,0.439225,0.413864,0.412984,0.431688,0.70882,0.786337,0.446497,0.42411,0.432364,0.47493,0.441738,0.429883,0.421553,0.419904,0.266988,0.202053,0.173519,0.169916};
double fitMax[nietaHF]={0.260772,0.27159,0.278067,0.269543,0.270123,0.27578,0.277444,0.275995,0.289728,0.291361,0.299158,0.33388,0.629152,0.683037,0.338566,0.301744,0.29546,0.295979,0.279636,0.278931,0.274237,0.274442,0.272059,0.277309,0.279914,0.265955};//for Elong > 40 GeV
int getieta(int);
TH1D *getTruncMean(TH1D*);
void RatioSummary(const char* ipfname){
  // ********************************** nE1E2Cuts **************************************
  int nE1E2Cuts=5;
  //*************************************************************************************
  
  
  //double ietaX[nietaHF+1]={-41,-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,-30,-29,29,30,31,32,33,34,35,36,37,38,39,40,41,42};
  //double ietaX[nietaHF]={29,30,31,32,33,34,35,36,37,38,39,40,41,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39,-40,-41};
  double ietaerr[nietaHF]={0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  char name[100],oDirName[100],iDirName[100],iDirNameRatio[100],title[100]; 
  TFile *f = new TFile(ipfname);
  sprintf(name,"mRatiovsIeta_%s",ipfname);
  TFile *fout = new TFile(name,"RECREATE");
  //  fout->mkdir("Cut0");
  TObjArray Hlist(0);
  TH1D *h_mRatiovsIeta[nE1E2Cuts];

  for(int i=0;i<nE1E2Cuts;i++){
    vector<double> mean,errMean;
    
    sprintf(iDirName,"E1E2Cut%iRatio",i);                          
    TDirectory *dir = (TDirectory*) f->FindObjectAny(iDirName);
    //dir->cd();
    //cout<<iDirName<<" ";
    sprintf(name,"MeanRatiovsIetaECut%i",i);
    sprintf(title,"Mean Ratio vs Ieta ECut%i",i);
    h_mRatiovsIeta[i]=new TH1D(name,title,28,0,28);
    for(int j=0;j<nietaHF;j++){
      int ieta=getieta(j);
      //cout<<ieta<<" ";
      if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i",abs(ieta));}
      else{sprintf(name,"RatioE2vsE1_ietaP%i",ieta);}
      TH1D *h_hf=(TH1D*)dir->FindObjectAny(name);

      TH1D *h_hf2;

      h_hf2=getTruncMean(h_hf);                          //for truncated mean uncomment this(1 of 3)
      mean.push_back(h_hf2->GetMean());                  //for truncated mean uncomment this(2 of 3)
      errMean.push_back(h_hf2->GetMeanError());          //for truncated mean uncomment this(3 of 3)
      
      //mean.push_back(h_hf->GetMean());                     //for untruncated mean uncomment this(1 of 2)
      //errMean.push_back(h_hf->GetMeanError());             //for untruncated mean uncomment this(2 of 2)
      
      sprintf(name,"%i",ieta);
      //cout<<name<<" mean:"<<mean[j]<<" errMean:"<<errMean[j]<<endl;
      
      h_mRatiovsIeta[i]->Fill(name,mean[j]);
      h_mRatiovsIeta[i]->SetBinError(j+1,errMean[j]);
      /*if(ieta==31){
	TCanvas *c_TrMean=new TCanvas("TrMean","TrMean",500,500);
	h_hf2->Draw();
	}*/
      
      delete h_hf2;                                      //for truncated mean
    }
    for(int k=1;k<=(h_mRatiovsIeta[i]->GetNbinsX());k++){   
      // h_mRatiovsIeta[i]->SetBinError(k,errMean[k-1]);
      //      cout<<h_mRatiovsIeta[i]->GetBin(k)<<endl;
    }
    //gr[i]=new TGraphErrors(nietaHF,ietaX,&(mean[0]),ietaerr,&(errMean[0]));
    
    //gr[i]->Draw("AP");
    Hlist.Add(h_mRatiovsIeta[i]);
  }

  TH1D *h_fitMax=new TH1D("Peak_Fit","Peak value from fit(ECut40) Run 254833",28,0,28);
  for(int j=0;j<nietaHF;j++){
    int ieta=getieta(j);
    sprintf(name,"%i",ieta);
    h_fitMax->Fill(name,fitMax[j]);
    h_fitMax->SetBinError(j+1,0.00001);
    
  }
  Hlist.Add(h_fitMax);
  fout->cd();
  Hlist.Write();
  sprintf(name,"mRatiovsIeta_%s",ipfname);
  cout<<name<<" has been created"<<endl;
}

int getieta(int j){
  int ieta[26]={-41,-40,-39,-38,-37,-36,-35,-34,-33,-32,-31,-30,-29,29,30,31,32,33,34,35,36,37,38,39,40,41};
  return ieta[j];

}

TH1D *getTruncMean(TH1D* h_hf){
  int nbins=h_hf->GetNbinsX();
  double intgrl=0,totEntries=h_hf->GetEntries();
  //double intgrl=0,totEntries=h_hf->Integral();
  
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






/*

Eta 29 0.786337
Eta 30 0.446497
Eta 31 0.42411
Eta 32 0.432364
Eta 33 0.47493
Eta 34 0.441738
Eta 35 0.429883
Eta 36 0.421553
Eta 37 0.419904
Eta 38 0.266988
Eta 39 0.202053
Eta 40 0.173519
Eta 41 0.169916

Eta -29 0.70882
Eta -30 0.431688
Eta -31 0.412984
Eta -32 0.413864
Eta -33 0.439225
Eta -34 0.412611
Eta -35 0.407111
Eta -36 0.406287
Eta -37 0.375591
Eta -38 0.256217
Eta -39 0.192013
Eta -40 0.163957
Eta -41 0.169916












Eta 41    Max   0.169916  FWHM   0.427861
Eta -41   Max   0.176521  FWHM   0.387221
vinay@vinay-ThinkCentre-Edge-72z:~/work/HFanalysisLocal/TreeMakerFiles$ grep FWHM log3.log
Eta 37   MP   0.381359 +- 0.00339319  Max   0.419904  FWHM   0.699939
Eta 38   MP   0.436529 +- 0.00137338  Max   0.266988  FWHM   0.544492
Eta 39   MP   0.453467 +- 0.00204758  Max   0.202053  FWHM   0.550053
Eta 40   MP    0.35236 +-  0.0013393  Max   0.173519  FWHM   0.427411
Eta -37   MP   0.354712 +- 0.00325782  Max   0.375591  FWHM   0.660473
Eta -38   MP   0.409707 +- 0.00125882  Max   0.256217  FWHM   0.510979
Eta -39   MP   0.426766 +- 0.00189506  Max   0.192013  FWHM   0.517665
Eta -40   MP   0.337394 +- 0.00127073  Max   0.163957  FWHM   0.409257
vinay@vinay-ThinkCentre-Edge-72z:~/work/HFanalysisLocal/TreeMakerFiles$ grep FWHM log2.log
Eta 33   MP    0.33651 +-  0.0048246  Max    0.47493  FWHM   0.692615
Eta 34   MP   0.334877 +- 0.00246218  Max   0.441738  FWHM   0.612644
Eta 35   MP   0.352223 +- 0.00289221  Max   0.429883  FWHM   0.650128
Eta 36   MP   0.359457 +- 0.00278338  Max   0.421553  FWHM   0.652799
Eta -33   MP   0.300445 +- 0.00589112  Max   0.439225  FWHM   0.643694
Eta -34   MP   0.311971 +- 0.00268121  Max   0.412611  FWHM   0.589375
Eta -35   MP   0.329947 +-  0.0026392  Max   0.407111  FWHM   0.612495
Eta -36   MP   0.343372 +- 0.00249828  Max   0.406287  FWHM   0.614841
vinay@vinay-ThinkCentre-Edge-72z:~/work/HFanalysisLocal/TreeMakerFiles$ grep FWHM log.log
Eta 29   MP   0.318035 +-  0.0182979  Max   0.786337  FWHM   0.535111
Eta 30   MP   0.297354 +- 0.00168891  Max   0.446497  FWHM   0.700195
Eta 31   MP   0.318846 +- 0.00605041  Max    0.42411  FWHM   0.678445
Eta 32   MP   0.330135 +- 0.00413648  Max   0.432364  FWHM   0.667775
Eta -29   MP   0.334793 +-  0.0160924  Max    0.70882  FWHM   0.538684
Eta -30   MP   0.324158 +- 0.00706562  Max   0.431688  FWHM   0.680476
Eta -31   MP     0.3277 +- 0.00479711  Max   0.412984  FWHM    0.67738
Eta -32   MP   0.339064 +- 0.00271929  Max   0.413864  FWHM   0.626374


 */
