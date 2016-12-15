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
void binsize(){
  TFile *f = new TFile("208307_E2E1Hists_uniformBin.root");
  TDirectory *dir = (TDirectory*) f->FindObjectAny("E1E2Cut0Ieta");
  TProfile *p1=(TProfile*)dir->FindObjectAny("P_E2vsE1Cut0");
  int nbins=p1->GetNbinsX(),nentries,j=0;
  nentries=(p1->GetBinEntries(0));
  for(int i=0;i<nbins;i++){
    
    if(nentries>100){
      cout<<"bin:"<<i+1<<" "<<p1->GetBinCenter(i)<<" "<<nentries<<endl;
      nentries=0;
      j++;
    }
    else{
      nentries=nentries+(p1->GetBinEntries(i));
    }
  }
  cout<<"j:"<<j<<endl;
}
