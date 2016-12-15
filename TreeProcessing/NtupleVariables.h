//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 27 01:22:50 2015 by ROOT version 5.34/25
// from TTree AUX/AUX
// found on file: DataPHYS14MC/TTJets/stopFlatNtuples_1.root
//////////////////////////////////////////////////////////

#ifndef NtupleVariables_h
#define NtupleVariables_h

#include <TROOT.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

using namespace std;
class NtupleVariables : public TSelector {
 public :

 NtupleVariables(TTree * /*tree*/ =0) : fChain(0) { }
  ~NtupleVariables() { }
  void    Init(TTree *tree);
  Bool_t  Notify();
  Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  double  DeltaPhi(double, double);
  double  DeltaR(double eta1, double phi1, double eta2, double phi2);

  //ClassDef(NtupleVariables,0);

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
   
  // Declaration of leaf types
  //   string          *HLTKey;
  //   vector<string>  *HLTInsideDatasetTriggerNames;
  //   vector<string>  *HLTOutsideDatasetTriggerNames;
  vector<bool>    *HLTInsideDatasetTriggerDecisions;
  //   vector<bool>    *HLTOutsideDatasetTriggerDecisions;
  vector<float>   *HFRecHitEnergy;
  vector<float>   *HFRecHitEta;
  vector<float>   *HFRecHitPhi;
  vector<float>   *HFRecHitTime;
  vector<int>     *HFRecHitAux;
  vector<int>     *HFRecHitDepth;
  vector<int>     *HFRecHitFlags;
  vector<int>     *HFRecHitHPDid;
  vector<int>     *HFRecHitIEta;
  vector<int>     *HFRecHitIPhi;
  vector<int>     *HFRecHitRBXid;
  //   vector<int>     *HLTBits;
  vector<int>     *HLTInsideDatasetTriggerPrescales;
  //   vector<int>     *HLTOutsideDatasetTriggerPrescales;
  //   vector<vector<int> > *L1PhysBits;
  //   vector<vector<int> > *L1TechBits;
  UInt_t          event;
  UInt_t          ls;
  UInt_t          run;
  UInt_t          nPrimaryVertices;
  vector<double>  *JetPt;
  vector<double>  *JetEta;
  // List of branches
  //   TBranch        *b_HLTKey;
  //   TBranch        *b_HLTInsideDatasetTriggerNames;   //!
  //   TBranch        *b_HLTOutsideDatasetTriggerNames;   //!
  TBranch        *b_HLTInsideDatasetTriggerDecisions;   //!
  //   TBranch        *b_HLTOutsideDatasetTriggerDecisions;   //!
  TBranch        *b_HFRecHitEnergy;   //!
  TBranch        *b_HFRecHitEta;   //!
  TBranch        *b_HFRecHitPhi;   //!
  TBranch        *b_HFRecHitTime;   //!
  TBranch        *b_HFRecHitAux;   //!
  TBranch        *b_HFRecHitDepth;   //!
  TBranch        *b_HFRecHitFlags;   //!
  TBranch        *b_HFRecHitHPDid;   //!
  TBranch        *b_HFRecHitIEta;   //!
  TBranch        *b_HFRecHitIPhi;   //!
  TBranch        *b_HFRecHitRBXid;   //!
  //   TBranch        *b_HLTBits;   //!
  TBranch        *b_HLTInsideDatasetTriggerPrescales;   //!
  //   TBranch        *b_HLTOutsideDatasetTriggerPrescales;   //!
  //   TBranch        *b_L1PhysBits;   //!
  //   TBranch        *b_L1TechBits;   //!
  TBranch        *b_event;   //!
  TBranch        *b_ls;   //!
  TBranch        *b_run;   //!
  TBranch        *b_nPrimaryVertices;
  /* TBranch        *b_JetPt; */ //@@@@@@@@@@@@@@@@
  /* TBranch        *b_JetEta; */ //@@@@@@@@@@@@@@@@
};
#endif

#ifdef NtupleVariables_cxx
void NtupleVariables::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  HLTInsideDatasetTriggerDecisions = 0;
  HFRecHitEnergy = 0;
  HFRecHitEta = 0;
  HFRecHitPhi = 0;
  HFRecHitTime = 0;
  HFRecHitAux = 0;
  HFRecHitDepth = 0;
  HFRecHitFlags = 0;
  HFRecHitHPDid = 0;
  HFRecHitIEta = 0;
  HFRecHitIPhi = 0;
  HFRecHitRBXid = 0;
  HLTInsideDatasetTriggerPrescales = 0;
  JetPt = 0;
  JetEta=0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fChain->SetMakeClass(1);
  //   fChain->SetBranchAddress("HLTKey", &HLTKey, &b_HLTKey);
  //   fChain->SetBranchAddress("HLTInsideDatasetTriggerNames", &HLTInsideDatasetTriggerNames, &b_HLTInsideDatasetTriggerNames);
  //   fChain->SetBranchAddress("HLTOutsideDatasetTriggerNames", &HLTOutsideDatasetTriggerNames, &b_HLTOutsideDatasetTriggerNames);
  fChain->SetBranchAddress("HLTInsideDatasetTriggerDecisions", &HLTInsideDatasetTriggerDecisions, &b_HLTInsideDatasetTriggerDecisions);
  //   fChain->SetBranchAddress("HLTOutsideDatasetTriggerDecisions", &HLTOutsideDatasetTriggerDecisions, &b_HLTOutsideDatasetTriggerDecisions);
  fChain->SetBranchAddress("HFRecHitEnergy", &HFRecHitEnergy, &b_HFRecHitEnergy);
  fChain->SetBranchAddress("HFRecHitEta", &HFRecHitEta, &b_HFRecHitEta);
  fChain->SetBranchAddress("HFRecHitPhi", &HFRecHitPhi, &b_HFRecHitPhi);
  fChain->SetBranchAddress("HFRecHitTime", &HFRecHitTime, &b_HFRecHitTime);
  fChain->SetBranchAddress("HFRecHitAux", &HFRecHitAux, &b_HFRecHitAux);
  fChain->SetBranchAddress("HFRecHitDepth", &HFRecHitDepth, &b_HFRecHitDepth);
  fChain->SetBranchAddress("HFRecHitFlags", &HFRecHitFlags, &b_HFRecHitFlags);
  fChain->SetBranchAddress("HFRecHitHPDid", &HFRecHitHPDid, &b_HFRecHitHPDid);
  fChain->SetBranchAddress("HFRecHitIEta", &HFRecHitIEta, &b_HFRecHitIEta);
  fChain->SetBranchAddress("HFRecHitIPhi", &HFRecHitIPhi, &b_HFRecHitIPhi);
  fChain->SetBranchAddress("HFRecHitRBXid", &HFRecHitRBXid, &b_HFRecHitRBXid);
  //   fChain->SetBranchAddress("HLTBits", &HLTBits, &b_HLTBits);
  fChain->SetBranchAddress("HLTInsideDatasetTriggerPrescales", &HLTInsideDatasetTriggerPrescales, &b_HLTInsideDatasetTriggerPrescales);
  //   fChain->SetBranchAddress("HLTOutsideDatasetTriggerPrescales", &HLTOutsideDatasetTriggerPrescales, &b_HLTOutsideDatasetTriggerPrescales);
  //   fChain->SetBranchAddress("L1PhysBits", &L1PhysBits, &b_L1PhysBits);
  //   fChain->SetBranchAddress("L1TechBits", &L1TechBits, &b_L1TechBits);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("ls", &ls, &b_ls);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("nPrimaryVertices",&nPrimaryVertices,&b_nPrimaryVertices);
  //  fChain->SetBranchAddress("JetPt", &JetPt, &b_JetPt); //@@@@@@@@@@@@@@@@
  //  fChain->SetBranchAddress("JetEta", &JetEta, &b_JetEta); //@@@@@@@@@@@@@@@@

  Notify();
}

Bool_t NtupleVariables::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

#endif // #ifdef NtupleVariables_cxx
