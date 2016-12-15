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


const int nfiles=7;
TFile *f[nfiles];
void MC_CombineDataSets(){
  f[0] = new TFile("170to300_MC_E2E1Hists.root");
  f[1] = new TFile("300to470_MC_E2E1Hists.root");
  f[2] = new TFile("470to600_MC_E2E1Hists.root");
  f[3] = new TFile("600to800_MC_E2E1Hists.root");
  f[4] = new TFile("800to1000_MC_E2E1Hists.root");
  f[5] = new TFile("1000to1400_MC_E2E1Hists.root");
  f[6] = new TFile("1400to1800_MC_E2E1Hists.root");


}
