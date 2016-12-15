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

using namespace std;

int nietaHF=26,niphiHF=36,minEntryPerBin=20;
vector<double> E1,E2,dE1,dE2;
int fitlinecolor=kRed;
void hist_fit(const char* ipfname){
  // ********************************** nE1E2Cuts **************************************
  int nE1E2Cuts=5;
  //*************************************************************************************

  void hist1D(TH1D*);
  void ProfileFit(TProfile*);

  char name[100],oDirName[100],iDirName[100],iDirNameRatio[100],title[100]; 
  TFile *f = new TFile(ipfname);
  sprintf(name,"fit_%s",ipfname);
  TFile *fout = new TFile(name,"RECREATE");
  //  fout->mkdir("Cut0");
  TObjArray Hlist(0);
  
  TH1D *h=(TH1D*)f->FindObjectAny("nHFREcHits");
  Hlist.Add(h);
  h=(TH1D*)f->FindObjectAny("HFRecHitEnergy");
  hist1D(h);
  Hlist.Add(h);
  
  TProfile *p=(TProfile*)f->FindObjectAny("P_EshortvsElong");
  Hlist.Add(p);
  TH2D *h2=(TH2D*)f->FindObjectAny("EshortvsElong");
  Hlist.Add(h2);



 
  //    TObjArray Hlist2(0);

  

  //  use this if you are raeding files obtained from ED Analyzer(no trees) TDirectory *demo = (TDirectory*) f->FindObjectAny("demo");

  for(int i=0;i<nE1E2Cuts;i++){
    TObjArray Hlist2(0),HlistRatio(0);  
    char name_pdf[100];
    
    sprintf(oDirName,"E1E2Cut%iIeta",i);
    fout->mkdir(oDirName);
    sprintf(oDirName,"RatiovsE1_ECut%iIeta",i);
    fout->mkdir(oDirName);

    // use this if you are reading files obtained from ED Analyzer(no trees) demo->cd();
    sprintf(iDirName,"E1E2Cut%iIeta",i);                          //for E2 vs E1 plots
    TDirectory *dir = (TDirectory*) f->FindObjectAny(iDirName);
    dir->cd();
    
    sprintf(name,"P_E2vsE1Cut%i",i);
    TProfile *p1=(TProfile*)dir->FindObjectAny(name);
    sprintf(name,"E2vsE1Cut%i",i);
    h2=(TH2D*)dir->FindObjectAny(name);
    Hlist2.Add(p1);
    Hlist2.Add(h2);

    TCanvas *c_ieta=new TCanvas(iDirName,iDirName,1000,1000); 
    h2->Draw("colz");
    h2->GetXaxis()->SetTitle("E in long(GeV)");
    h2->GetYaxis()->SetTitle("E in short(GeV)");
    c_ieta->SetLogz();
    sprintf(name_pdf,"%s.pdf(",iDirName);
    sprintf(title,"Title:2D_E2vsE1");
    c_ieta->Print(name_pdf,title);
    p1->Draw();
    p1->GetXaxis()->SetTitle("E in long(GeV)");
    p1->GetYaxis()->SetTitle("E in short(GeV)");
    sprintf(name_pdf,"%s.pdf",iDirName);
    sprintf(title,"Title:P_E2vsE1");
    c_ieta->Print(name_pdf,title);

    for(int j=0;j<nietaHF;j++){
      //for(int j=16;j<17;j++){
      int ieta;
      if(j<13)
	ieta=j+29;
      else
	ieta=-(j+16);
      
      if(ieta<0){sprintf(name,"E2E1_ietaN%i",abs(ieta));}
      else{sprintf(name,"E2E1_ietaP%i",ieta);}
      h2=(TH2D*)dir->FindObjectAny(name);
      Hlist2.Add(h2);

      if(ieta<0){sprintf(name,"E2E1Prof_ietaN%i",abs(ieta));}
      else{sprintf(name,"E2E1Prof_ietaP%i",ieta);}
      p1=(TProfile*)dir->FindObjectAny(name);
      Hlist2.Add(p1);

      
      ProfileFit(p1);
      TGraphErrors *GrError=new TGraphErrors(E1.size(),&(E1[0]),&(E2[0]),&(dE1[0]),&(dE2[0]));

    
      sprintf(title,"E2vsE1 for ieta=%i",ieta);
      GrError->SetTitle(title);
      TF1 *ft=new TF1("ft","pol1");
      ft->SetLineColor(fitlinecolor);
      GrError->Fit("ft");
      
      gStyle->SetOptFit(101);
      GrError->SetLineColor(fitlinecolor);
      sprintf(name,"E2vsE1_ieta_%i",ieta);
      GrError->Draw("AP");
      //ft->SetLineColor(fitlinecolor);
      GrError->GetXaxis()->SetTitle("E in long(GeV)");
      GrError->GetYaxis()->SetTitle("E in short(GeV)");
      sprintf(title,"Title:ieta:%i iphi INC",ieta);
      if(j<(nietaHF-1)){
	sprintf(name_pdf,"%s.pdf",iDirName);
	c_ieta->Print(name_pdf,title);
      }
      else if(j==(nietaHF-1)){
	sprintf(name_pdf,"%s.pdf)",iDirName);
	c_ieta->Print(name_pdf,title);
      }
      Hlist2.Add(GrError);
      
      // Ratio vs Elong Plots------------------------------------------
      sprintf(iDirNameRatio,"E1E2Cut%iRatio",i);
      TDirectory *dirRatio = (TDirectory*) f->FindObjectAny(iDirNameRatio);
      
      if(ieta<0){sprintf(name,"P_RatiovsElong_ietaN%i",abs(ieta));}
      else{sprintf(name,"P_RatiovsElong_ietaP%i",ieta);}
      TProfile *p_ratio=(TProfile*)dirRatio->FindObjectAny(name);
      //TCanvas *canva=new TCanvas("ratio","ratio",500,500);
      //p_ratio->Draw();

      ProfileFit(p_ratio);
      TGraphErrors *GrErrorRatio=new TGraphErrors(E1.size(),&(E1[0]),&(E2[0]),&(dE1[0]),&(dE2[0]));
      sprintf(title,"RatiovsE1 for ieta=%i",ieta);
      GrErrorRatio->SetTitle(title);
      TF1 *ft_ratio=new TF1("ft_ratio","pol0");
      ft_ratio->SetLineColor(fitlinecolor);
      GrErrorRatio->Fit("ft_ratio");
      
      GrErrorRatio->Draw();
      GrErrorRatio->GetXaxis()->SetTitle("E in long(GeV)");
      GrErrorRatio->GetYaxis()->SetTitle("Ratio");
      gStyle->SetOptFit(101);
      HlistRatio.Add(GrErrorRatio);

      //---------------------------------------------------------------
      
      //TF1 *ft = new TF1("ft","[0]+[1]*x");
      //	p1->Fit("ft");
      
      // }
      for(int k=0;k<niphiHF;k++){
      }
      //      cout<<"************************************************************************"<<endl;
    }
   
    sprintf(oDirName,"E1E2Cut%iIeta",i);
    fout->cd(oDirName);
    Hlist2.Write();

    sprintf(oDirName,"RatiovsE1_ECut%iIeta",i);
    fout->cd(oDirName);
    HlistRatio.Write();
  }

  fout->cd();
  Hlist.Write();
}

void ProfileFit(TProfile *p){
  //TF1 *f1 = new TF1("f1","[0]+[1]*x");
  //p->Fit("f1");
  //cout<<endl<<"chi2:"<<f1->GetChisquare();
  //vector<double> E1,E2,dE1,dE2;
  E1.resize(0);
  E2.resize(0);
  dE1.resize(0);
  dE2.resize(0);
  int nbins=p->GetNbinsX();
  //cout<<"**************\n size:"<<E1.size()<<E2.size()<<dE1.size()<<dE2.size()<<endl;
  
  for(int i=0;i<nbins;i++){
    if((p->GetBinEntries(i))>=minEntryPerBin){
      E1.push_back(p->GetBinCenter(i));   
      E2.push_back(p->GetBinContent(i));
      dE1.push_back((p->GetBinWidth(i))/2);
      dE2.push_back(p->GetBinError(i));
  
      //  if(ieta==-32)
      //cout<<"p->GetBinEntries(i):"<<p->GetBinEntries(i)<<" p->GetBinCenter(i):"<<p->GetBinCenter(i)<<" p->GetBinContent(i)):"<<p->GetBinContent(i)<<" p->GetBinWidth(i):"<<p->GetBinWidth(i)<<" p->GetBinError(i):"<<p->GetBinError(i)<<endl;
    }
  }
  //cout<<"**************\n size later:"<<E1.size()<<E2.size()<<dE1.size()<<dE2.size()<<endl;
 
  
  
}

void hist1D(TH1D *h){
  
}


/* if(ieta==41 && iphi==47){
	//      ProfileFit(p1);
	Hlist.Add(p1);
ssh -Y vhegde@ui.indiacms.res.in
exit
rm crab.log
logout
exit

	cout<<"***********"<<p1->GetNbinsX()<<endl;
	cout<<"bin entries:"<<endl<<endl<<endl<<p1->GetBinEntries(76)<<endl<<p1->GetBinEntries(103)<<endl<<p1->GetBinEntries(104)<<endl<<"------\n\n\n\n"<<p1->GetBinContent(76)<<endl<<p1->GetBinContent(103)<<endl<<p1->GetBinContent(104)<<endl<<p1->GetBinError(104)<<"\t";
	for(int k=1;k<=p1->GetNbinsX();k++){
	  if(p1->GetBinEntries(k)<5){
	    p1->SetBinEntries(k,0);
	  }
	}
      }*/
