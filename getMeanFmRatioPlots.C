#include "TROOT.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TMath.h"
#include "TStyle.h"
#include <TPaveStats.h>



TH1D *getTruncMean(TH1D*);
int color[3]={kRed,kGreen+1,kBlue};
void getMeanFmRatioPlots(){
  char name[100];
  int counter=0,counter2=0;
  TObjArray hlist(0);
  TH1D *h_RvsIeta[3];

  TFile *ofile=new TFile("meanvsIetaEcuts.root","RECREATE");
  TFile *f=new TFile("254833_E2E1Hists20_40_50.root");

  gStyle->SetOptStat(0);
  
  for(int j=1;j<6;j=j+2){
    sprintf(name,"E1E2Cut%iRatio",j);
    TDirectory *dir=(TDirectory*)f->FindObjectAny(name);
    cout<<name<<endl;
    sprintf(name,"meanvsIeta%i",j);
    h_RvsIeta[counter2]=new TH1D(name,"meanvsIeta for diff. cuts of Elong Eshort",28,0,28);

    //cout<<"{";
    for(int i=41;i>=29;i--){
      counter++;
      sprintf(name,"RatioE2vsE1_ietaN%i",i);
      dir->cd();
      
      TH1D *h_ratio=(TH1D*)dir->FindObjectAny(name);
      //    cout<<h_ratio->GetMean()<<",";
      
      TH1D *h_hf2;
      h_hf2=getTruncMean(h_ratio);
      sprintf(name,"-%i",i);
      h_RvsIeta[counter2]->Fill(name,h_hf2->GetMean());
      h_RvsIeta[counter2]->SetBinError(counter,h_hf2->GetMeanError());
      h_RvsIeta[counter2]->SetLineColor(color[counter2]);
      h_RvsIeta[counter2]->SetMarkerColor(color[counter2]);
      //cout<<h_ratio->GetMeanError()<<endl;
      delete h_hf2;
    }
    for(int i=29;i<=41;i++){
      counter++;
      sprintf(name,"RatioE2vsE1_ietaP%i",i);
      TH1D *h_ratio=(TH1D*)dir->FindObjectAny(name);
      // cout<<h_ratio->GetMean()<<",";
      TH1D *h_hf2;
      h_hf2=getTruncMean(h_ratio);
      sprintf(name,"%i",i);
      h_RvsIeta[counter2]->Fill(name,h_hf2->GetMean());
      h_RvsIeta[counter2]->SetBinError(counter,h_hf2->GetMeanError());
      h_RvsIeta[counter2]->SetLineColor(color[counter2]);
      h_RvsIeta[counter2]->SetMarkerColor(color[counter2]);
      h_RvsIeta[counter2]->SetMarkerStyle(20+counter2);
      h_RvsIeta[counter2]->SetLineWidth(2);
      h_RvsIeta[counter2]->GetYaxis()->SetTitle("<Ratio>");
      h_RvsIeta[counter2]->GetXaxis()->SetTitle("ieta");
      
      delete h_hf2;
    }

    hlist.Add(h_RvsIeta[counter2]);
    counter2++;   

    // cout<<endl;

    //    h_RvsIeta->Draw();
   
 
    counter=0;
  }
  ofile->cd();
  hlist.Write();
TLegend *legend2=new TLegend(0.75,0.6,.9,.7);
  for(int i=0;i<3;i++){
    if(i==0){
      hlist[i]->Draw();
    }
    else{
      hlist[i]->Draw("same");
      
    }
    
    sprintf(name,"E1E2Cut%iRatio",i);
    legend2->AddEntry(h_RvsIeta[i],name,"lep");
    legend2->SetTextSize(0.05);
    legend2->Draw();

  }
}


TH1D *getTruncMean(TH1D* h_hf){
  int nbins=h_hf->GetNbinsX();
  double intgrl=0,totEntries=h_hf->GetEntries();
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
Cut0 
{0.508012,0.460746,0.485576,0.46077,0.452828,0.452105,0.450043,0.442284,0.462668,0.462303,0.469515,0.50135,0.688392,0.74041,0.505933,0.47565,0.471497,0.485622,0.458359,0.465287,0.463004,0.479694,0.477319,0.505712,0.469338,0.532044}

Cut1
{0.575793,0.569168,0.627716,0.592787,0.586709,0.589831,0.588636,0.579599,0.599009,0.594167,0.597803,0.617252,0.787017,0.84151,0.61812,0.601886,0.606848,0.628765,0.595298,0.60365,0.598716,0.614675,0.614255,0.648365,0.586518,0.609018};

Cut2
{0.416478,0.36462,0.406874,0.383029,0.384777,0.392267,0.394519,0.396306,0.435567,0.44159,0.457364,0.484373,0.703461,0.757687,0.495426,0.463637,0.458758,0.465971,0.417098,0.412832,0.40054,0.412981,0.399059,0.423326,0.375932,0.435732};

Cut3
{0.452087,0.419621,0.474918,0.448425,0.449409,0.457215,0.457994,0.457314,0.489383,0.491799,0.502914,0.523568,0.735905,0.794951,0.532921,0.508389,0.507269,0.521356,0.47741,0.476757,0.46568,0.478129,0.467064,0.492017,0.435816,0.478135};

Cut4
{0.394595,0.348915,0.401165,0.381861,0.390053,0.40296,0.406625,0.411756,0.453331,0.455849,0.466938,0.487042,0.713564,0.754282,0.498465,0.474249,0.473949,0.48756,0.436282,0.428451,0.411093,0.421321,0.398273,0.41867,0.359725,0.411238};

Cut5
{0.421377,0.389993,0.45111,0.429427,0.436601,0.447792,0.450122,0.451337,0.48623,0.486509,0.495474,0.513257,0.742328,0.789467,0.523765,0.501857,0.503185,0.521195,0.47514,0.47139,0.457138,0.466993,0.447787,0.468585,0.404269,0.44372};





 */
