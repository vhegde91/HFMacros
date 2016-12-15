//This will overlay E2 vs E1 profile plots obtained for different runs.
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
#include"TGraphErrors.h"
#include"TGraph.h"
#include"TCanvas.h"
#include"TPaveStats.h"
using namespace std;

int nietaHF=26,niphiHF=36;
const int nfiles=3;
TFile *f[nfiles];
TCanvas *c_ieta[8];
int canvasIdx=0,padIdx=0;
float p_x1,p_y1,p_x2,p_y2,p=0.15;
//void movestat(TPavestats*);
void Overlay(const char* iDirName){
  int pad=0;
  TFile *f[nfiles];
  char name[100];
    
  /*  f[0]=new TFile("fit_251244_E2E1Hists.root");
  f[1]=new TFile("fit_251251_E2E1Hists.root");
  f[2]=new TFile("fit_251252_E2E1Hists.root");
  f[4]=new TFile("fit_251562_E2E1Hists.root");
  f[3]=new TFile("fit_251561_E2E1Hists.root");*/
  /*
  f[0]=new TFile("fit_254833_E2E1Hists.root");
  f[1]=new TFile("fit_251721_E2E1Hists.root");
  f[2]=new TFile("fit_251883_E2E1Hists.root");
  f[3]=new TFile("fit_251643_E2E1Hists.root");*/

  f[0]=new TFile("fit_254833_E2E1HistsVtx.root");
  f[1]=new TFile("fit_2015B_E2E1HistsVtx.root");
  f[2]=new TFile("fit_2012D_E2E1HistsVtx.root");
  /*f[0]=new TFile("fit_254833_E2E1HistsTrg1.root");
  f[1]=new TFile("fit_MC_E2E1HistsTrg_1000to1400.root");
  f[2]=new TFile("fit_2012D_E2E1HistsVtx.root");*/

  for(int i=0;i<8;i++){
    sprintf(name,"IetaSet_%i",i);
    c_ieta[i]= new TCanvas(name,name,1500,500);
    c_ieta[i]->Divide(4,1);
  }
  
  TFile *fout = new TFile("Overlayed.root","RECREATE");
  TObjArray Hlist(0);
 
  
  for(int i=0;i<nfiles;i++){

    TDirectory *dir1 = (TDirectory*) f[i]->FindObjectAny(iDirName);
   
    for(int j=0;j<nietaHF/2;j++){
      sprintf(name,"Graph;%d",j+1);
      dir1->cd();
      TGraphErrors *g1=(TGraphErrors*)dir1->FindObjectAny(name);
      
     
      TPaveStats *st1 = (TPaveStats*)g1->FindObject("stats");
      if(st1){
      st1->SetTextSize(0.03);
      st1->SetLineColor(g1->GetLineColor());
      st1->SetTextColor(g1->GetLineColor());
      if(i==0){
	st1->SetX1NDC(0.15);
	st1->SetX2NDC(0.4);
	st1->SetY1NDC(0.9);
	st1->SetY2NDC(0.8);
      }
      
      if(i==1){
	st1->SetX1NDC(0.4);
	st1->SetX2NDC(0.65);
	st1->SetY1NDC(0.9);
	st1->SetY2NDC(0.8);
      }
      if(i==2){
	st1->SetX1NDC(0.15);
	st1->SetX2NDC(0.4);
	st1->SetY1NDC(0.7);
	st1->SetY2NDC(0.8);
      }
      if(i==3){
	st1->SetX1NDC(0.65);
	st1->SetX2NDC(0.9);
	st1->SetY1NDC(0.4);
	st1->SetY2NDC(0.5);
      }
      if(i==4){
	st1->SetX1NDC(0.65);
	st1->SetX2NDC(0.9);
	st1->SetY1NDC(0.3);
	st1->SetY2NDC(0.4);
      }
      }

      //      movestat(st1);
      /*   TLegend *legend=new TLegend(0.75,0.8,.98,.9);
      sprintf(name,"Data%i",i);
      legend->AddEntry(g1,f[i]->GetName(),"L");
      legend->SetTextSize(0.04);
      legend->Draw();*/

      if(j!=((nietaHF/2)-1)){      
	canvasIdx=(j/4);
	padIdx=(j%4);
	c_ieta[canvasIdx]->cd(1+padIdx);
	//	cout<<"j:"<<j<<" canvasIdx:"<<canvasIdx<<"  padIdx:"<<padIdx<<endl;
      }
      else{
	c_ieta[7]->cd(1);
      }
      
      if(i==0){
	g1->Draw("AP");
      }
      else{
	g1->Draw("sames");
      }
    }
    
    for(int j=(nietaHF/2);j<nietaHF;j++){
      sprintf(name,"Graph;%d",j+1);
      dir1->cd();
      TGraphErrors *g1=(TGraphErrors*)dir1->FindObjectAny(name);
      TPaveStats *st2 = (TPaveStats*)g1->FindObject("stats");
      if(st2){
      
      st2->SetTextSize(0.03);
      st2->SetLineColor(g1->GetLineColor());
      st2->SetTextColor(g1->GetLineColor());
      if(i==0){
	st2->SetX1NDC(0.15);
	st2->SetX2NDC(0.4);
	st2->SetY1NDC(0.9);
	st2->SetY2NDC(0.8);
      }
      if(i==1){
	st2->SetX1NDC(0.4);
	st2->SetX2NDC(0.65);
	st2->SetY1NDC(0.9);
	st2->SetY2NDC(0.8);
      }
      if(i==2){
	st2->SetX1NDC(0.15);
	st2->SetX2NDC(0.4);
	st2->SetY1NDC(0.7);
	st2->SetY2NDC(0.8);
      }
      if(i==3){
	st2->SetX1NDC(0.65);
	st2->SetX2NDC(0.9);
	st2->SetY1NDC(0.4);
	st2->SetY2NDC(0.5);
      }
      if(i==4){
	st2->SetX1NDC(0.65);
	st2->SetX2NDC(0.9);
	st2->SetY1NDC(0.3);
	st2->SetY2NDC(0.4);
      }
      }
      /* TLegend *legend=new TLegend(0.75,0.8,.98,.9);
      sprintf(name,"Data%i",i);
      legend->AddEntry(g1,f[i]->GetName(),"L");
      
      legend->SetTextSize(0.05);
      legend->Draw();*/
      if(j!=nietaHF-1){
	canvasIdx=((j-1)/4)+1;
	padIdx=((j-1)%4)+1;
	c_ieta[canvasIdx]->cd(padIdx);
	//cout<<"j:"<<j<<" canvasIdx:"<<canvasIdx<<"  padIdx:"<<padIdx<<endl;
      }
      else{
       	c_ieta[7]->cd(2);
      }
        if(i==0){
	  g1->Draw("AP");
	}
	else{
	  g1->Draw("sames");
	}
    }
    
  }
}



/*void movestat(TPavestat *st1){
  st1->SetX1NDC(0.7);
  st1->SetX2NDC(0.95); 
  st1->SetY1NDC(p-.15);
  st1->SetY2NDC(p);

  }*/












/*
void Overlay(const char* iDirName){
  vector<char*> ipfname;
  
  //------------------------------------
  string line;
  ifstream myfile ("OverlayHistFiles.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
      {
	ipfname.push_back(line);
      }
    myfile.close();
  }
  else cout << "Unable to open file"<<endl; 
  //-----------------------------------
  TObjArray Hlist(0);
  TFile *fout = new TFile("Overlayed.root","RECREATE");
  for(int i=0;i<ipfname.size();i++){
    cout<<"-------"<<ipfname[i]<<"---------";
    const char* fname=&(ipfname[i]);
    TFile *f=new TFile(fname);
    
    

    TDirectory *dir1 = (TDirectory*) f->FindObjectAny(iDirName);
    for(int j=0;j<nietaHF;j++){
      char name[100];
      sprintf(name,"Graph;%d",i+1);
      dir1->cd();
      TGraphErrors *g1=(TGraphErrors*)dir1->FindObjectAny(name);
      Hlist.Add(g1);
    }
  }//loop over all files
  fout->cd();
  Hlist.Write();
  



   
}
*/
