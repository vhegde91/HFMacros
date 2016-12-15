#ifndef ANALYZEHFLONGSHORT_H
#define ANALYZEHFLONGSHORT_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "NtupleVariables.h"
#include "TH1F.h"
#include "TH2.h"
#include <TProfile.h>
#include "TFile.h"
#include "TLorentzVector.h"
#include "TDirectory.h"
#include "TH1.h"

class AnalyzeHFLongShort : public NtupleVariables{

 public:
  AnalyzeHFLongShort(const TString &inputFileList="foo.txt", const char *outFileName="histo.root",const char *dataset="data");
  ~AnalyzeHFLongShort();
  Bool_t   FillChain(TChain *chain, const TString &inputFileList);
  Long64_t LoadTree(Long64_t entry);
  void     EventLoop(const char *);
  void     BookHistogram(const char *,const char*);

//Variables defined
  static const int nHFADC=4;
  
  /*  std::vector<std::string> myTriggerName;
  myTriggerName.push_back("HLT_PFJet200_");
  myTriggerName.push_back("HLT_PFJet80_");
  myTriggerName.push_back("HLT_PFHT550_4Jet_");
  myTriggerName.push_back("AlCa_EcalPhiSym_");
  static const int nmyTriggers=myTriggerName.size();
  */

  float Emin=10.0;
  
  static const int nE1E2Cuts=11;
  float E1min[nE1E2Cuts]={20,30,40,50,100,10,20,40,80,100,50};
  float E2min[nE1E2Cuts]={10,10,10,10,10,10,20,20,20,20,50};
  //  static const int nE1E2Cuts=5;
  //  float E1min[nE1E2Cuts]={20,30,40,50,100};
  //  float E2min[nE1E2Cuts]={10,10,10,10,10};

  double weight=1;
  //  float E1min[nE1E2Cuts]={-100000,30,30,40,100};
  //float E2min[nE1E2Cuts]={-100000,5,10,10,10};

  //  double PupWtfor2015D_using2016B[100]={0,0.513379,0.0743577,0.0732576,0.0848765,0.104729,0.133723,0.176003,0.237647,0.325822,0.458319,0.651452,0.940165,1.36556,1.9949,2.90846,4.22059,6.14258,8.86499,12.7446,18.0187,24.9499,34.3573,46.67,63.8554,96.8791,104.385,150.006,217.231,340.451,690.508,384.796,529.889,0,0,471.507,306.711,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  double PupWtfor2016G_using2016BFinal[100]={0,2.03398,3.25857,4.97526,5.13178,4.86122,4.22726,3.69695,3.23731,2.85253,2.53858,2.27699,2.04051,1.839,1.64127,1.45727,1.2831,1.11481,0.958705,0.82353,0.699409,0.590644,0.498034,0.417028,0.352625,0.295804,0.250284,0.211551,0.17938,0.154927,0.13238,0.113546,0.100463,0.0866602,0.0760822,0.0666832,0.0570724,0.0542901,0.0474083,0.038042,0.0401405,0.0342922,0.0330816,0.0284335,0.0272434,0.0277165,0.0220433,0.0160144,0.0152878,0.0200876,0.0163526,0.0221469,0.00890785,0.00793694,0.00500027,0,0.0157241,0.0100005,0.0123769,0.0171242,0,0,0.0277793,0,0,0,0,0.113643,0,0,0,0,0,0.312517,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  //double PupWtforMC_using2016B[100]={0,0.723706,0.0940336,0.0675117,0.0687094,0.102507,0.136312,0.190057,0.273843,0.372792,0.497287,0.630933,0.777409,0.94478,1.0648,1.22188,1.31912,1.42458,1.46677,1.46823,1.47985,1.47911,1.54639,1.42446,1.38393,1.32883,1.22247,1.3744,1.37307,1.34443,1.95702,1.22463,0.773664,1.19487,0.930337,1.345,0.124783,0,0,0.847259,0.700729,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  float adc2fCMultFactor=2.6;
  static const int nietaHF=13*2, niphiHF=36;
  vector<float> adc2fc={-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,15.,17.,19.,21.,23.,25.,27.,29.5,32.5,35.5,38.5,42.,46.,50.,54.5,59.5,64.5,59.5,64.5,69.5,74.5,79.5,84.5,89.5,94.5,99.5,104.5,109.5,114.5,119.5,124.5,129.5,137.,147.,157.,167.,177.,187.,197.,209.5,224.5,239.5,254.5,272.,292.,312.,334.5,359.5,384.5,359.5,384.5,409.5,434.5,459.5,484.5,509.5,534.5,559.5,584.5,609.5,634.5,659.5,684.5,709.5,747.,797.,847.,897.,947.,997.,1047.,1109.5,1184.5,1259.5,1334.5,1422.,1522.,1622.,1734.5,1859.5,1984.5,1859.5,1984.5,2109.5,2234.5,2359.5,2484.5,2609.5,2734.5,2859.5,2984.5,3109.5,3234.5,3359.5,3484.5,3609.5,3797.,4047.,4297.,4547.,4797.,5047.,5297.,5609.5,5984.5,6359.5,6734.5,7172.,7672.,8172.,8734.5,9359.5,9984.5};

  void storeE(int,int,int,float);
  void fillHistE1E2();
  
  struct sct_ietaiphi{
    float E1=0,E2=0,Eratio=0;
    bool b_E1=false,b_E2=false;
  }sct_ratio[nietaHF][niphiHF];
    
  TH1D *h_run;
  TH1D *h_nvtx;
  TH1D *h_jet1Pt;
  TH1D *h_jet1Eta;
  TH1D *h_HT;

  TH1D *h_nHFRecHit;
  TH1D *h_nHFRecHitEmin;
  TH1D *h_HFRecHitEnergy;
  TH1D *h_HFRecHitEnergyD1;
  TH1D *h_HFRecHitEnergyD2;

  TH1D *h_HFRecHitTime;
  TH1D *h_HFRecHitTimeEmin;

  TH1D *h_ieta;
  TH1D *h_ietaEmin;

  TH1D *h_iphi;
  TH1D *h_iphiEmin;

  TH2D *h2_iEtaiPhiDepth1;
  TH2D *h2_iEtaiPhiDepth2;
  TH2D *h2_iEtaiPhiDepth1WtE;
  TH2D *h2_iEtaiPhiDepth2WtE;
  
  TH2D *h2_iEtaiPhiDepth1Emin;
  TH2D *h2_iEtaiPhiDepth2Emin;
  TH2D *h2_iEtaiPhiDepth1WtEmin;
  TH2D *h2_iEtaiPhiDepth2WtEmin;

  TH1D *h_aux;
  TH1D *h_HFADC[nHFADC];
  TH1D *h_HFADC2fc[nHFADC];
  
  TH2D *h2_EshortvsElong;
  TProfile *P_EshortvsElong;

  // TH2D *h2_EshortvsElong;

  TH2D *h2_E2E1BothPsnt;
  TH2D *h2_EsEl[nE1E2Cuts];
  TProfile *P_EsEl[nE1E2Cuts];
  TH1D *h_EL[nE1E2Cuts];
  TH1D *h_ES[nE1E2Cuts];

  TH2D *h2_E2vsE1[nE1E2Cuts][nietaHF][niphiHF];
  TProfile *P_E2vsE1[nE1E2Cuts][nietaHF][niphiHF];
  TH1D *h_RatioE2vsE1[nE1E2Cuts][nietaHF][niphiHF];
  TH1D *h_ELvsIphi[nE1E2Cuts][nietaHF][niphiHF];
  TH1D *h_ESvsIphi[nE1E2Cuts][nietaHF][niphiHF];


  TProfile *P_E2E1INCiphi[nE1E2Cuts][nietaHF];
  TH2D *h2_E2E1INCiphi[nE1E2Cuts][nietaHF];

  TH1D *h_RatioE2vsE1INCiphi[nE1E2Cuts][nietaHF];
  TProfile *P_RatiovsElong[nE1E2Cuts][nietaHF];

  TH1D *h_EL_INCiphi[nE1E2Cuts][nietaHF];
  TH1D *h_ES_INCiphi[nE1E2Cuts][nietaHF];

  TDirectory E1E2CutIetaiphi[nE1E2Cuts],E1E2CutIeta[nE1E2Cuts],E1E2CutRatio[nE1E2Cuts],E1E2CutIetaE[nE1E2Cuts],EnergyvsIphi[nE1E2Cuts];


  //E2 hists for ieta 32 and 37==================================
  /*float E1cut[4]={10,20,50,100};
  TH1D *h_E2_ieta32E1cut[4];
  TH1D *h_E2_ieta37E1cut[4];
  */
  //============================================================

  
  // 
  TFile *oFile;
  
};
#endif

#ifdef ANALYZEHFLONGSHORT_cxx

void AnalyzeHFLongShort::BookHistogram(const char *outFileName,const char *dataset) {
  
  //  char hname[200], htit[200];
  //  double xlow = 0.0,  xhigh = 2000.0;
  //  int nbins = 2000;
  
  char name[100],title[100];
  sprintf(name,"%s_%s",dataset,outFileName);
  oFile = new TFile(name, "recreate");
  TH1::SetDefaultSumw2(1);  
  h_run=new TH1D("runs","Run nos.",100000,200000,300000);
  h_nvtx=new TH1D("nVertices","no. of vertices",100,0,100);
  h_jet1Pt=new TH1D("leadJetPt","leading central jet pt",200,0,2000);
  h_jet1Eta=new TH1D("leadJetEta","leading jet eta",120,-6,6);
  h_HT=new TH1D("HT","HT:jetPt>30,|jetEta|<2.4",400,0,4000);

  h_nHFRecHit= new TH1D("nHFRecHits","number of HF Rechits",2000,0,2000);
  h_nHFRecHitEmin= new TH1D("nHFRecHitsEmin","Rechits with Emin Cut",2000,0,2000);
  h_HFRecHitEnergy = new TH1D("HFRecHitEnergy","HFRecHitEnergy",101,-10,1000);
  h_HFRecHitEnergyD1 =  new TH1D("HFRecHitEnergyD1","HFRecHitEnergyD1",101,-10,1000);
  h_HFRecHitEnergyD2 =  new TH1D("HFRecHitEnergyD2","HFRecHitEnergyD2",101,-10,1000);

  h_HFRecHitTime = new TH1D("HFRecHitTime","HFRecHitTime",100,-50,50);
  h_HFRecHitTimeEmin = new TH1D("HFRecHitTimeE_Emin","HFRecHit Time for E>EminGev",100,-50,50);
  
  h_ieta   =new TH1D("ieta","ieta",86,-43,43);
  h_ietaEmin =new TH1D("ietaE_Emin","ietaE>Emin",86,-43,43);
  
  h_iphi  =new TH1D("iphi","iphi",80,0,80);
  h_iphiEmin=new TH1D("iphiEmin","iphiE>Emin",80,0,80);
  


  h2_iEtaiPhiDepth1 = new TH2D("iEtaiPhiDepth1","iEtaiPhiDepth1",84,-42,42,75,0,75);
  h2_iEtaiPhiDepth2 = new TH2D("iEtaiPhiDepth2","iEtaiPhiDepth2",84,-42,42,75,0,75);
  h2_iEtaiPhiDepth1WtE = new TH2D("iEtaiPhiDepth1energyW","iEtaiPhiDepth1 weighted with Energy",84,-42,42,75,0,75);
  h2_iEtaiPhiDepth2WtE = new TH2D("iEtaiPhiDepth2energyW","iEtaiPhiDepth2 weighted with Energy",84,-42,42,75,0,75);
  //h2_EshortvsElong     = new TH2D("ShortvsLong","Energy in short vs long",2100,-100,1000,2100,-100,1000);
  
  h2_iEtaiPhiDepth1Emin = new TH2D("iEtaiPhiDepth1E_Emin","iEtaiPhiDepth1E>Emin",84,-42,42,75,0,75);
  h2_iEtaiPhiDepth2Emin = new TH2D("iEtaiPhiDepth2E_Emin","iEtaiPhiDepth2E>Emin",84,-42,42,75,0,75);
  h2_iEtaiPhiDepth1WtEmin = new TH2D("iEtaiPhiDepth1energy_EminWt","iEtaiPhiDepth1 weighted with Energy>Emin",84,-42,42,75,0,75);
  h2_iEtaiPhiDepth2WtEmin = new TH2D("iEtaiPhiDepth2energy_EminWt","iEtaiPhiDepth2 weighted with Energy>Emin",84,-42,42,75,0,75);
  
  h_aux=new TH1D("HFAux","HF Aux word",10,0,900e6);
  //E2 hists for ieta 32 and 37==================================  
  /* for(int i=0;i<4;i++){
    sprintf(name,"E2_ieta32_E1_%imin",i);
    sprintf(title,"E2_ieta32_E1_%fmin",E1cut[i]);
    h_E2_ieta32E1cut[i]= new TH1D(name,name,220,-100,1100);
    sprintf(name,"E2_ieta37_E1_%imin",i);
    sprintf(title,"E2_ieta37_E1_%fmin",E1cut[i]);
    h_E2_ieta37E1cut[i]= new TH1D(name,name,220,-100,1100);
  }
*/

  //============================================================
  for(int i=0;i<nHFADC;i++){
    sprintf(name,"HFADC[%i]",i);
    sprintf(title,"HF ADC[%i]",i);
    h_HFADC[i]=new TH1D(name,title,140,0,140);
    sprintf(name,"HFADC2fc[%i]",i);
    sprintf(title,"HF ADC2fc[%i]",i);
    h_HFADC2fc[i]=new TH1D(name,title,1000,0,1000);
  }
  h2_E2E1BothPsnt = new TH2D("E2E1BothPsnt","Eshort vs Elong when both are Present",220,-100,1000,220,-100,1000);  
  h2_EshortvsElong     = new TH2D("EshortvsElong","Energy in short vs long",220,-100,1000,220,-100,1000);
  P_EshortvsElong= new TProfile("P_EshortvsElong","Energy profile in short vs long",220,-100,1000,0,0);
  
  for(int i=0;i<nE1E2Cuts;i++){
    char dirname1[100],dirname2[100],dirname3[100],dirname4[100],dirname5[100];
    //=============Variable bin Parameters===========================
    /*       const int nvarBins=36;
    double myxbins[nvarBins+1],sizeStart=5,sizeEnd=250,binsize=sizeStart;
    if(E1min[i]<0){myxbins[0]=-100;}  //Starting point of histogram. Start at -100 if there are no cuts on E1 and E2
    else{
      myxbins[0]=E1min[i];    //Starting point of histogram. Start at Elong cut 
    }
    for(int i=1;i<=nvarBins;i++){
      binsize=sizeStart+i*((sizeEnd-sizeStart)/nvarBins);
      myxbins[i]=myxbins[i-1]+binsize;
      //cout<<"binsize:"<<binsize<<" myxbins "<<i<<":"<<myxbins[i]<<endl;
      }*/
    
    const int nvarBins=56;
    double myxbins[nvarBins+1]={0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,220,240,260,280,300,320,340,360,380,400,450,500,550,600,800,1200};    
    
    //===============================================================
    sprintf(dirname1,"E1E2Cut%iIetaiphi",i);
    oFile->mkdir(dirname1);
    sprintf(dirname2,"E1E2Cut%iIeta",i);
    oFile->mkdir(dirname2);
    sprintf(dirname3,"E1E2Cut%iRatio",i);
    oFile->mkdir(dirname3);
    sprintf(dirname4,"E1E2Cut%iEnergy",i);
    oFile->mkdir(dirname4);
    sprintf(dirname5,"EnergyvsIphi_cut%i",i);
    oFile->mkdir(dirname5);
    
    sprintf(name,"E2vsE1Cut%i",i);
    sprintf(title,"E2>%.1fvsE1>%.1f",E2min[i],E1min[i]);
    oFile->cd(dirname2);
    h2_EsEl[i]=new TH2D(name,title,220,-100,1000,220,-100,1000);
    sprintf(name,"P_E2vsE1Cut%i",i);
    P_EsEl[i]=new TProfile(name,title,220,-100,1000,0,0);

    sprintf(name,"ELCut%i",i);
    sprintf(title,"Energy in Long E2>%.1f E1>%.1f",E2min[i],E1min[i]);
    oFile->cd(dirname4);
    h_EL[i]=new TH1D(name,title,200,0,1000);

    sprintf(name,"ESCut%i",i);
    sprintf(title,"Energy in Short E2>%.1f E1>%.1f",E2min[i],E1min[i]);
    oFile->cd(dirname4);
    h_ES[i]=new TH1D(name,title,200,0,1000);


     for(int j=0;j<nietaHF;j++){
      int ieta;
      if(j<13)
	ieta=j+29;
      else
	ieta= -(j+16);
      for(int k=0;k<niphiHF;k++){
	int iphi=2*k+1;

	//	if(ieta<0){sprintf(name,"E2E1Prof_ietaN%iiphi_%i",abs(ieta),iphi);}
	//	else{sprintf(name,"E2E1Prof_ietaP%iiphi_%i",ieta,iphi);}
	//	sprintf(title,"E2>%.1fvsE1>%.1f profile for ieta %i, iphi %i",E2min[i],E1min[i],ieta,iphi);

	// Can be uncommentted if u want to look at each ieta & iphi slices: P_E2vsE1[i][j][k]=new TProfile(name,title,220,-100,1000,0,0);  //profile of ieta phi separate. This is in constant binning !!!!!!
	//	if(ieta<0){sprintf(name,"E2E1_ietaN%iiphi_%i",abs(ieta),iphi);}
	//	else{sprintf(name,"E2E1_ietaP%iiphi_%i",ieta,iphi);}
	//        sprintf(title,"E2>%.1fvsE1>%.1f for ieta %i, iphi %i",E2min[i],E1min[i],ieta,iphi);
	// Can be uncommentted if u want to look at each ieta & iphi slices: h2_E2vsE1[i][j][k]=new TH2D(name,title,220,-100,1000,220,-100,1000);
	oFile->cd(dirname1);
	if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i_iphi%i",abs(ieta),iphi);}
	else{sprintf(name,"RatioE2vsE1_ietaP%i_iphi%i",ieta,iphi);}
	sprintf(title,"Plot of Eshort/Elong for ieta %i iphi %i (E2>%.1fvsE1>%.1f)",ieta,iphi,E2min[i],E1min[i]);
	h_RatioE2vsE1[i][j][k]=new TH1D(name,title,600,0.001,3);

	oFile->cd(dirname5);
	if(ieta<0){sprintf(name,"ELong_ietaN%i_iphi%i",abs(ieta),iphi);}
	else{sprintf(name,"ELong_ietaP%i_iphi%i",abs(ieta),iphi);}
	sprintf(title,"Energy in Long for ieta %i iphi %i (EL>%.1f)",ieta,iphi,E1min[i]);
	h_ELvsIphi[i][j][k]=new TH1D(name,title,200,0,1000);

	if(ieta<0){sprintf(name,"EShort_ietaN%i_iphi%i",abs(ieta),iphi);}
        else{sprintf(name,"EShort_ietaP%i_iphi%i",abs(ieta),iphi);}
        sprintf(title,"Energy in Short for ieta %i iphi %i (ES>%.1f)",ieta,iphi,E2min[i]);
        h_ESvsIphi[i][j][k]=new TH1D(name,title,200,0,1000);

      }
      if(ieta<0){sprintf(name,"E2E1Prof_ietaN%i",abs(ieta));}
      else{sprintf(name,"E2E1Prof_ietaP%i",ieta);}
      sprintf(title,"E2>%.1fvsE1>%.1f profile for ieta %i, iphi inclusive",E2min[i],E1min[i],ieta);
      oFile->cd(dirname2);

      if(i==0){P_E2E1INCiphi[i][j]=new TProfile(name,title,220,-100,1000,0,0);}  // Constant binning for each ieta for Cut 0(no cut)
      else{
	//      P_E2E1INCiphi[i][j]=new TProfile(name,title,220,-100,1000,0,0);  // Constant binning for each ieta
	P_E2E1INCiphi[i][j]=new TProfile(name,title,nvarBins,myxbins,0,0);      // Variable binning for each ieta 
	//P_E2E1INCiphi[i][j]->Sumw2();
      }

      if(ieta<0){sprintf(name,"E2E1_ietaN%i",abs(ieta));}
      else{sprintf(name,"E2E1_ietaP%i",ieta);}
      sprintf(title,"E2>%.1fvsE1>%.1f for ieta %i, iphi inclusive",E2min[i],E1min[i],ieta);
      h2_E2E1INCiphi[i][j]=new TH2D(name,title,220,-100,1000,220,-100,1000);

      oFile->cd(dirname3);
      if(ieta<0){sprintf(name,"RatioE2vsE1_ietaN%i",abs(ieta));}
      else{sprintf(name,"RatioE2vsE1_ietaP%i",ieta);}
      sprintf(title,"Plot of Eshort/Elong for ieta %i (E2>%.1fvsE1>%.1f)",ieta,E2min[i],E1min[i]);
      h_RatioE2vsE1INCiphi[i][j]=new TH1D(name,title,600,0.001,3);

      if(ieta<0){sprintf(name,"P_RatiovsElong_ietaN%i",abs(ieta));}
      else{sprintf(name,"P_RatiovsElong_ietaP%i",ieta);}
      sprintf(title,"Profile of Eshort/Elong vs Elong for ieta %i (E2>%.1fvsE1>%.1f)",ieta,E2min[i],E1min[i]);
      if(i==0){P_RatiovsElong[i][j]=new TProfile(name,title,220,-100,1000,0,0);} //Constant binning for each ieta for Cut 0(no cut) 
      else{
	P_RatiovsElong[i][j]=new TProfile(name,title,nvarBins,myxbins,0,0);      // Variable binning for each ieta (ratios)
      }

      oFile->cd(dirname4);
      if(ieta<0){sprintf(name,"EL_ietaN%i",abs(ieta));}
      else{sprintf(name,"EL_ietaP%i",ieta);}
      sprintf(title,"Energy in Long for ieta %i (E2>%.1fvsE1>%.1f)",ieta,E2min[i],E1min[i]);
      h_EL_INCiphi[i][j]=new TH1D(name,title,200,0,1000);

      if(ieta<0){sprintf(name,"ES_ietaN%i",abs(ieta));}
      else{sprintf(name,"ES_ietaP%i",ieta);}
      sprintf(title,"Energy in Short for ieta %i (E2>%.1fvsE1>%.1f)",ieta,E2min[i],E1min[i]);
      h_ES_INCiphi[i][j]=new TH1D(name,title,200,0,1000);

     }
  }
  
}


AnalyzeHFLongShort::AnalyzeHFLongShort(const TString &inputFileList, const char *outFileName, const char* dataset) {

  TChain *tree = new TChain("hcalTupleTree/tree");

  if( ! FillChain(tree, inputFileList) ) {
    std::cerr << "Cannot get the tree " << std::endl;
  } else {
    std::cout << "Initiating analysis of dataset " << dataset << std::endl;
  }

  NtupleVariables::Init(tree);

  BookHistogram(outFileName,dataset);
  
}

Bool_t AnalyzeHFLongShort::FillChain(TChain *chain, const TString &inputFileList) {

  ifstream infile(inputFileList, ifstream::in);
  std::string buffer;

  if(!infile.is_open()) {
    std::cerr << "** ERROR: Can't open '" << inputFileList << "' for input" << std::endl;
    return kFALSE;
  }

  std::cout << "TreeUtilities : FillChain " << std::endl;
  while(1) {
    infile >> buffer;
    if(!infile.good()) break;
    //std::cout << "Adding tree from " << buffer.c_str() << std::endl;                                                              
    chain->Add(buffer.c_str());
  }
  std::cout << "No. of Entries in this tree : " << chain->GetEntries() << std::endl;
  return kTRUE;
}

Long64_t AnalyzeHFLongShort::LoadTree(Long64_t entry) {
  // Set the environment to read one entry                                                                                          
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    //    Notify();
  }
  return centry;
}

AnalyzeHFLongShort::~AnalyzeHFLongShort() { 

  if (!fChain) return;
  delete fChain->GetCurrentFile();
  oFile->cd();
  oFile->Write();
  oFile->Close();

}

#endif

