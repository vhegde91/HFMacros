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

void errorProf(){
  TFile *f=new TFile("fit_251252_E2E1Hists.root");
  TDirectory *dir = (TDirectory*) f->FindObjectAny("E1E2Cut3Ieta");
  TGraphErrors*ge=(TGraphErrors*)dir->FindObjectAny("Graph;14");
  TProfile *p=(TProfile*)dir->FindObjectAny("E2E1Prof_ieta29");
  ge->Draw("AP");

  double x[13],y[13];
  int nbins=p->GetNbinsX(),j=0;
  vector<double> E1,E2,dE1,dE2,nentries;
  //cout<<nbins;
  for(int i=0;i<nbins;i++){
    if((p->GetBinEntries(i)>10)){
      nentries.push_back(p->GetBinEntries(i));
      E1.push_back(p->GetBinCenter(i));   
      E2.push_back(p->GetBinContent(i));
      dE1.push_back((p->GetBinWidth(i))/2);
      dE2.push_back(p->GetBinError(i));
    }
  }
  for(int i=0;i<E1.size();i++){
    
    cout<<"i:"<<i<<" "<<"E1:"<<E1[i]<<" E2:"<<E2[i]<<" entries:"<<nentries[i]<<endl;
  }
  
  TProfile *p1= new TProfile("nameP1","titleP1",220,-100,1000,0,0);
  TProfile *p2= new TProfile("nameP2","titleP2",220,-100,1000,0,0);
  TProfile *p3= new TProfile("nameP3","titleP3",220,-100,1000,0,0);
  //p1->Sumw2();
 for(int i=0;i<E1.size();i++){

   //for(int k=0;k<(nentries[i]);k++){
   for(int k=0;k<5;k++){
     double e2=E2[i];
     e2=e2+k;
     p1->Fill(E1[i],e2);
   }
 }
 p1->Draw();

 for(int i=0;i<E1.size();i++){
   //for(int k=0;k<(nentries[i]);k++){
   for(int k=5;k<10;k++){
     double e2=E2[i];
     e2=e2+k;
     p2->Fill(E1[i],e2);
   }
 }

 p3->Add(p1);
 p3->Add(p2);
 p2->Draw(); 




  /* double x[47]={-5,-8,1,3,8,11,14,15,18,21,29,28,25,24,31,32,33,34,35,39,41,42,43,44,45,46,49,52,51,53,58,59,57,65,64,63,67,62,71,77,75,75,88,82,85,94,96};
   double y[47]={-5,-5,5,5,5,15,15,15,15,25,25,25,25,25,35,35,35,35,35,35,45,45,45,45,45,45,45,55,55,55,55,55,55,65,65,65,65,65,75,75,75,75,85,85,85,95,95};
  TH1D *h_hist=new TH1D("hname","htitle",11,-10,100);
  TProfile *p_prof=new TProfile("pname","ptitle",11,-10,100,0,0);
  for(int i=0;i<47;i++){
    h_hist->Fill(y[i]);
    p_prof->Fill(x[i],y[i]);
  }

  //h_hist->Draw();
  
  p_prof->Draw();*/
}
