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
#include"TCanvas.h"
#include"TPaveStats.h"
#include"TLegend.h"

int nietaHF=26;
const int nfiles=2;
char name[100],title[100];
int col[nfiles]={kRed,kBlue};
bool LongNotShort=true;                 //for long
//bool LongNotShort=false;                  // for short(1 of 3)
TCanvas *c_ieta[4];

int getPadIdx(int);
int getCanvasIdx(int);
void setCanvasName(int,const char*);
int getieta(int);

void EnergyPlotsComparison(int cutnum){
  char iDirName[100];
  TFile *f[nfiles];
  TDirectory *dir[nfiles];
  
  float MCScale=1;
  gStyle->SetOptStat("nemi");
  sprintf(iDirName,"E1E2Cut%iIeta",cutnum);

  f[0]=new TFile("MC_E2E1HistsTrg1.root");
  //f[0]=new TFile("MC_E2E1HistsTrg1_7files.root");
  f[1]=new TFile("254833_E2E1HistsTrg1.root");
  // f[1]=new TFile("254833_E2E1HistsTrg1_1DE.root");

  for(int i=0;i<nfiles;i++){
    dir[i]=(TDirectory*)f[i]->FindObjectAny(iDirName);
  }
  
  
  for(int i=0;i<4;i++){
    setCanvasName(i,iDirName);
    c_ieta[i]=new TCanvas(name,title,1500,1500);
    c_ieta[i]->Divide(4,2);
   
  }
 
  for(int j=0;j<nietaHF;j++){
    int ieta=getieta(j);
    if(ieta<0){sprintf(name,"E2E1_ietaN%i",abs(ieta));}
    else{sprintf(name,"E2E1_ietaP%i",ieta);}
   
    char name2[50];
    for(int i=0;i<nfiles;i++){
      TH2D *h_2dhist=(TH2D*)dir[i]->FindObjectAny(name);
         
      TH1 *h_projection=h_2dhist->ProjectionX();           //for long
      //      TH1 *h_projection=h_2dhist->ProjectionY();             //for short(2 of 3)
      
     
      TH1D *h_new = (TH1D*)h_projection->Clone("hnew");    
      c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
     
      h_new->Rebin(10);
      h_new->Scale(1.0/(h_new->Integral()));
      h_new->SetMaximum(1);
      h_new->SetMinimum(0.001);
      gPad->SetLogy();
      h_new->SetLineColor(col[i]);
      h_new->SetLineWidth(2);
	
      if(i==0){
	c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
	//	h_new->Scale(MCScale);
	//	h_new->DrawCopy();
	h_new->Draw();
	if(LongNotShort){h_new->GetXaxis()->SetTitle("Energy in Long(GeV)");}
	else{h_new->GetXaxis()->SetTitle("Energy in Short(GeV)");}
	
	c_ieta[(getCanvasIdx(j))]->Update();
	gPad->Update();
	TPaveStats *st=(TPaveStats*)h_new->FindObject("stats");
	st->SetLineColor(col[i]);
	st->SetTextColor(col[i]);
	st->SetX1NDC(0.65);
	st->SetX2NDC(0.98); 
	st->SetY1NDC(0.90);
	st->SetY2NDC(0.70);
	TLegend *legend1=new TLegend(0.65,0.85,.98,.9);
	legend1->AddEntry(h_new,f[i]->GetName(),"l");
	legend1->SetTextSize(0.05);
	legend1->SetTextColor(col[i]);
	legend1->Draw();

      }
      else{
	c_ieta[(getCanvasIdx(j))]->cd((getPadIdx(j)));
	h_new->Draw("sames");
	c_ieta[(getCanvasIdx(j))]->Update();
	TPaveStats *st=(TPaveStats*)h_new->FindObject("stats");
	st->SetLineColor(col[i]);
	st->SetTextColor(col[i]);
	st->SetX1NDC(0.65);
	st->SetX2NDC(0.98); 
	st->SetY1NDC(0.90-i*0.2);
	st->SetY2NDC(0.70-i*0.2);
	TLegend *legend2=new TLegend(0.65,0.90-i*0.2,0.98,0.85-i*0.2);
	legend2->AddEntry(h_new,f[i]->GetName(),"l");
	legend2->SetTextSize(0.05);
	legend2->SetTextColor(col[i]);
	legend2->Draw();
      }
      //-------------------for summary plot(INclusive in ieta)-------------------------
      if(j==nietaHF-1){
	char name3[10];
	sprintf(name3,"E2vsE1Cut%i",cutnum);
	TH2D *h_2dhist2=(TH2D*)dir[i]->FindObjectAny(name3);
	TH1 *h_projection2=h_2dhist2->ProjectionX();             //for long
	//TH1 *h_projection2=h_2dhist2->ProjectionY();               //for short(3 of 3)
	TH1F *h_new2 = (TH1F*)h_projection2->Clone("hnew2");    
	c_ieta[3]->cd(3);
	h_new2->Rebin(10);
	h_new2->Scale(1.0/(h_new2->Integral()));
	h_new2->SetMaximum(1);
	h_new2->SetMinimum(0.001);

	gPad->SetLogy();
	h_new2->SetLineColor(col[i]);
	h_new2->SetLineWidth(2);
	if(i==0){
	  h_new2->Draw();
	  //	  h_new2->Scale(MCScale);
	  if(LongNotShort){h_new2->GetXaxis()->SetTitle("Energy in Long(GeV)");}
	  else{h_new2->GetXaxis()->SetTitle("Energy in Short(GeV)");}
	  c_ieta[(getCanvasIdx(j))]->Update();
	  gPad->Update();
	  TPaveStats *st=(TPaveStats*)h_new2->FindObject("stats");
	  st->SetLineColor(col[i]);
	  st->SetTextColor(col[i]);
	  st->SetX1NDC(0.65);
	  st->SetX2NDC(0.98); 
	  st->SetY1NDC(0.90);
	  st->SetY2NDC(0.70);
	  TLegend *legend1=new TLegend(0.65,0.85,.98,.9);
	  legend1->AddEntry(h_new2,f[i]->GetName(),"l");
	  legend1->SetTextSize(0.05);
	  legend1->SetTextColor(col[i]);
	  legend1->Draw();
	}
	else{
	  h_new2->Draw("sames");
	  c_ieta[(getCanvasIdx(j))]->Update();
	  TPaveStats *st=(TPaveStats*)h_new2->FindObject("stats");
	  st->SetLineColor(col[i]);
	  st->SetTextColor(col[i]);
	  st->SetX1NDC(0.65);
	  st->SetX2NDC(0.98); 
	  st->SetY1NDC(0.90-i*0.2);
	  st->SetY2NDC(0.70-i*0.2);
	  TLegend *legend2=new TLegend(0.65,0.90-i*0.2,0.98,0.85-i*0.2);
	  legend2->AddEntry(h_new2,f[i]->GetName(),"l");
	  legend2->SetTextSize(0.05);
	  legend2->SetTextColor(col[i]);
	  legend2->Draw();
	}
      }//if(j==nietaHF-1)
    }//nfiles loop    
  }//ieta loop
 
}//end of function


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

int getieta(int j){
  int ieta[26]={29,30,31,32,33,34,35,36,37,38,39,40,41,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39,-40,-41};
  return ieta[j];

}



