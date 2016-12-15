#define ANALYZEHFLONGSHORT_cxx

#include <iostream>
#include <vector>
#include <cstring>
#include "AnalyzeHFLongShort.h"

using namespace std;


int main(int argc, char* argv[])
{

  if (argc < 2) {
    cerr << "Please give 3 arguments " << "runList " << " " << "outputFileName" << " " << "dataset" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];
  const char *data          = argv[3];

  AnalyzeHFLongShort hf(inputFileList, outFileName, data);
  cout << "dataset " << data << " " << endl;

  hf.EventLoop(data);

  return 0;
}

void AnalyzeHFLongShort::EventLoop(const char *data) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  cout << "nentries " << nentries << endl;
  cout << "Analyzing dataset " << data << " " << endl;

  Long64_t nbytes = 0, nb = 0;
  int decade = 0;


  int myrun=atoi(data);
  bool runValid=false;

  //==============================================================                                                                                                      
  //  std::vector<std::string> myTriggerName;
  //myTriggerName.push_back("HLT_PFJet200_");
  //  myTriggerName.push_back("HLT_PFJet80_");
  //myTriggerName.push_back("HLT_PFHT550_4Jet_");
  //myTriggerName.push_back("AlCa_EcalPhiSym_");
  //static const int nmyTriggers=myTriggerName.size();
  int chooseTrigger=5;     //0 : All are selected. No preferred trigger
                           //1 : Events which satisfy trigger 1 are processed
                           //2 : Events which satisfy trigger 2 are processed
  /*
    1.myTriggerName.push_back("HLT_CaloJet500_NoJetID_");
    2.myTriggerName.push_back("HLT_DiPFJetAve500_");
    3.myTriggerName.push_back("HLT_PFHT750_4JetPt50_");
    4.myTriggerName.push_back("HLT_PFHT800_");
    5.myTriggerName.push_back("HLT_PFJet450_");
  */
  /*SingleMu Triggers
    myTriggerName.push_back("HLT_IsoTkMu22_");
    myTriggerName.push_back("HLT_IsoMu22_");
    myTriggerName.push_back("HLT_Mu50_");
    SingleMu Triggers*/
  //===============================================================    
  Long64_t nent1=0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    // ==============print number of events done == == == == == == == =
    double progress = 10.0 * jentry / (1.0 * nentries);
    int k = int (progress);
    if (k > decade)
      cout << 10 * k << " %" << endl;
    decade = k;

    // ===============read this entry == == == == == == == == == == == 
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    //    if((myrun==run || true) && ((nPrimaryVertices>10) && (nPrimaryVertices<17))){
    //    if((myrun==run || true)){   
    bool proceed=false;
    //    weight=PupWtfor2015D_using2016B[nPrimaryVertices];
    //    weight=PupWtfor2016G_using2016BFinal[nPrimaryVertices];
    //    weight=PupWtforMC_using2016B[nPrimaryVertices];
    if(jentry==0 && weight!=1) cout<<endl<<endl<<"!!!Filling histograms with weight NOT EQUAL to 1"<<endl<<endl;
    /*
      for(int i=0;i<HLTInsideDatasetTriggerDecisions->size();i++){
	std::string temp=(*HLTInsideDatasetTriggerNames)[i];
	temp.pop_back();
	temp.pop_back();
	//	cout<<temp<<endl;
	//if( ((*HLTInsideDatasetTriggerDecisions)[i]) && (temp == myTriggerName[p]) ){
	if( ((*HLTInsideDatasetTriggerDecisions)[i])){ 
	  if(chooseTrigger==(i+1)){
	    proceed=true;
	    //cout<<(*HLTInsideDatasetTriggerDecisions)[i];
	    //	  cout<<myTriggerName[p]<<" "<<(*HLTInsideDatasetTriggerNames)[i]<<" "<<temp<<endl; 
	    break;
	  }
	}
      }
      */
    if((chooseTrigger==0)){proceed=true;}      
    else if( ((*HLTInsideDatasetTriggerDecisions)[chooseTrigger-1]) ){
      // cout<<(*HLTInsideDatasetTriggerNames)[chooseTrigger-1]<<endl;
      proceed=true;
    }
    bool highPtJet=0;
    double leadJetPt=0,leadJetEta=-100;
    double ht=0;
    if(JetPt){
      for(int j_jet=0;j_jet<JetPt->size();j_jet++){
	if((*JetPt)[j_jet]>30 && abs((*JetEta)[j_jet])<2.4 ) { ht+=(*JetPt)[j_jet]; }
	if((*JetPt)[j_jet]>600 && abs((*JetEta)[j_jet])<2.4 ) {
	  highPtJet=true;
	  if( leadJetPt < (*JetPt)[j_jet] ) {leadJetPt = (*JetPt)[j_jet]; leadJetEta = (*JetEta)[j_jet];}
	}
      }
    }
    
    //if( (run==273492 && (ls==283 || ls==326)) || (run==273502 && (ls==257 || ls==319 || ls==814)) || (run==273725 && ls==253) ) continue;//for SingMu 
    //if(proceed && ((nPrimaryVertices>=9)&&(nPrimaryVertices<=12)) ){
    //    if(proceed && (nPrimaryVertices>=16) ){
    //    if(proceed && highPtJet && (nPrimaryVertices<=13) ){
    if(proceed){
      runValid=true;
      
      //      cout<<"++++++++++++++++++++++++++"<<endl;
      //cout<<event<<"\n";
      
      
      
      /*      for(int p=0;p<HLTInsideDatasetTriggerDecisions->size();p++){
	if((*HLTInsideDatasetTriggerDecisions)[p]==true){
	  cout<<(*HLTInsideDatasetTriggerNames)[p]<<"\n";
	  //	  cout<<"Prescales "<<(*HLTInsideDatasetTriggerPrescales)[p]<<endl;
	}
	}*/

      h_run->Fill(run);
      h_nvtx->Fill(nPrimaryVertices,weight);
      h_jet1Pt->Fill(leadJetPt,weight);
      h_jet1Eta->Fill(leadJetEta,weight);
      h_HT->Fill(ht,weight);

      int nRecHits=(HFRecHitEnergy->size());
      int nRecHitsEcut=0;
      double totEL=0,totES=0;
      for(int i=0;i<nRecHits;i++){
	if( ((((*HFRecHitFlags)[i]) >> 0) & 1) || ((((*HFRecHitFlags)[i]) >> 3) & 1) || ((((*HFRecHitFlags)[i]) >> 4) & 1)){continue;}
	double E=((*HFRecHitEnergy)[i]);
	if(E<Emin) continue;
	h_HFRecHitEnergy->Fill(E,weight);
	h_ieta->Fill((*HFRecHitIEta)[i],weight);
	h_iphi->Fill((*HFRecHitIPhi)[i],weight);
	h_HFRecHitTime->Fill((*HFRecHitTime)[i],weight);
	
	if(E>=Emin){ 
	  nRecHitsEcut++;
	  h_ietaEmin->Fill((*HFRecHitIEta)[i],weight);
	  h_iphiEmin->Fill((*HFRecHitIPhi)[i],weight);
	  h_HFRecHitTimeEmin->Fill((*HFRecHitTime)[i],weight);
	}
	
	if(((*HFRecHitDepth)[i])==1){
	  h_HFRecHitEnergyD1->Fill(E,weight);totEL=totEL+E;
	  h2_iEtaiPhiDepth1->Fill((*HFRecHitIEta)[i],(*HFRecHitIPhi)[i],weight);
	  h2_iEtaiPhiDepth1WtE->Fill((*HFRecHitIEta)[i],(*HFRecHitIPhi)[i],E*weight);
	  if(E>=Emin){
	    h2_iEtaiPhiDepth1Emin->Fill((*HFRecHitIEta)[i],(*HFRecHitIPhi)[i],weight);
	    h2_iEtaiPhiDepth1WtEmin->Fill((*HFRecHitIEta)[i],(*HFRecHitIPhi)[i],E*weight);
	  }
	}
	else if(((*HFRecHitDepth)[i])==2){
	  h_HFRecHitEnergyD2->Fill(E,weight);totES=totES+E;
	  h2_iEtaiPhiDepth2->Fill((*HFRecHitIEta)[i],(*HFRecHitIPhi)[i],weight);
	  h2_iEtaiPhiDepth2WtE->Fill((*HFRecHitIEta)[i],(*HFRecHitIPhi)[i],E*weight);
	  if(E>=Emin){
	    h2_iEtaiPhiDepth2Emin->Fill((*HFRecHitIEta)[i],(*HFRecHitIPhi)[i],weight);
	    h2_iEtaiPhiDepth2WtEmin->Fill((*HFRecHitIEta)[i],(*HFRecHitIPhi)[i],E*weight);
	  }
	}
	//==========================================  Eshort vs Elong FOR EACH ETA AND PHI ==================================================================
	storeE((*HFRecHitIEta)[i],(*HFRecHitIPhi)[i],(*HFRecHitDepth)[i],E);
	
	h_aux->Fill((*HFRecHitAux)[i],weight);
	uint32_t auxwd2 = (*HFRecHitAux)[i];                                    // i is the  HFRecHitCollection  iterator                                              
	uint32_t adc;
	for(int k=0;k<nHFADC;k++){                                   // nHFADC is set to value 4 in the beginning of the code
	  adc= (auxwd2>>7*k) & 0x7F;
	  //cout<<"k:"<<k<<" adc:"<<adc<<"\t";
	  h_HFADC[k]->Fill(adc,weight);
	  h_HFADC2fc[k]->Fill(adc2fCMultFactor*adc2fc[adc],weight);           //adc2fCMultFactor is set to 2. in the beginning of the code
	}
	//	cout<<"i:"<<i<<" Energy:"<<E<<" depth:"<<((*HFRecHitDepth)[i])<<" ieta:"<<(*HFRecHitIEta)[i]<<" ihpi:"<<(*HFRecHitIPhi)[i]<<endl;
      }
      h_nHFRecHit->Fill(nRecHits,weight);
      h_nHFRecHitEmin->Fill(nRecHitsEcut,weight);
      //std::cout <<"Run " << run << "  Event " << event << " lumisection " << ls << std::endl;
      fillHistE1E2();
      //      cout<<jentry<<" nVtx:"<<nPrimaryVertices<<" totEL:"<<totEL<<" totES:"<<totES<<" totE:"<<totEL+totES<<endl;
    }
  } // loop over entries
  if(!runValid){
    cout<<endl<<"Looked into all the entries. None of the entries satisfy trigger(s) you specified(trigger no."<<chooseTrigger<<")"<<endl;
    cout<<"OR none of the entries have this run no.: "<<data<<".\n Output file will have 0 entries"<<endl;
  }    


}

//------------- Functions defined by me ---------------------------------
void AnalyzeHFLongShort::storeE(int ieta,int iphi,int depth,float E){
  int ietaIndx,iphiIndx;
  if(ieta>0){
    ietaIndx=ieta-29;
  }
  else{
    ietaIndx=abs(ieta)-16;
  }
  iphiIndx=(iphi-1)/2;
  if(depth==1){
    sct_ratio[ietaIndx][iphiIndx].E1=E;
    sct_ratio[ietaIndx][iphiIndx].b_E1=true;
  }
  else if(depth==2){
    sct_ratio[ietaIndx][iphiIndx].E2=E;
    sct_ratio[ietaIndx][iphiIndx].b_E2=true;

  }
  
}


//Filling ietaiphi, ietaiphiInclusive 2D and profile histograms 
void AnalyzeHFLongShort::fillHistE1E2(){
  for(int i=0;i<nietaHF;i++){
    for(int j=0;j<niphiHF;j++){
      //      cout<<"ietaIndx:"<<i<<" iphiIndx:"<<j<<" E1:"<<sct_ratio[i][j].E1<<" E2:"<<sct_ratio[i][j].E2<<endl;
      for(int k=0;k<nE1E2Cuts;k++){
	if(sct_ratio[i][j].E1>E1min[k]){h_EL[k]->Fill(sct_ratio[i][j].E1,weight);}
	if(sct_ratio[i][j].E2>E2min[k]){h_ES[k]->Fill(sct_ratio[i][j].E2,weight);}
	if(sct_ratio[i][j].E1>E1min[k]){
	  h_EL_INCiphi[k][i]->Fill(sct_ratio[i][j].E1,weight);
	  h_ELvsIphi[k][i][j]->Fill(sct_ratio[i][j].E1,weight);
	}
	if(sct_ratio[i][j].E2>E2min[k]){
	  h_ES_INCiphi[k][i]->Fill(sct_ratio[i][j].E2,weight); 
	  h_ESvsIphi[k][i][j]->Fill(sct_ratio[i][j].E2,weight); 
	}

	if(sct_ratio[i][j].E1>E1min[k] && sct_ratio[i][j].E2>E2min[k]){
	  if(sct_ratio[i][j].b_E1 || sct_ratio[i][j].b_E2){

	    // Can be uncommentted if u want to look at each ieta & iphi slices: P_E2vsE1[k][i][j]->Fill(sct_ratio[i][j].E1,sct_ratio[i][j].E2,weight);
	    // Can be uncommentted if u want to look at each ieta & iphi slices: h2_E2vsE1[k][i][j]->Fill(sct_ratio[i][j].E1,sct_ratio[i][j].E2,weight);
	    
	    P_E2E1INCiphi[k][i]->Fill(sct_ratio[i][j].E1,sct_ratio[i][j].E2,weight);
	    h2_E2E1INCiphi[k][i]->Fill(sct_ratio[i][j].E1,sct_ratio[i][j].E2,weight);
	    P_EsEl[k]->Fill(sct_ratio[i][j].E1,sct_ratio[i][j].E2,weight);
	    h2_EsEl[k]->Fill(sct_ratio[i][j].E1,sct_ratio[i][j].E2,weight);

	    if((sct_ratio[i][j].E1!=0) && (sct_ratio[i][j].b_E1) && sct_ratio[i][j].b_E2){
	    //	    if((sct_ratio[i][j].E1!=0)){ 
	      sct_ratio[i][j].Eratio=(sct_ratio[i][j].E2)/(sct_ratio[i][j].E1);
	      //cout<<"ieta:"<<i<<" iphi:"<<j<<" E1:"<<sct_ratio[i][j].E1<<" E2:"<<sct_ratio[i][j].E2<<" Eratio:"<<sct_ratio[i][j].Eratio<<endl;
	      h_RatioE2vsE1[k][i][j]->Fill(sct_ratio[i][j].Eratio,weight);
	      h_RatioE2vsE1INCiphi[k][i]->Fill(sct_ratio[i][j].Eratio,weight);
	      P_RatiovsElong[k][i]->Fill(sct_ratio[i][j].E1,sct_ratio[i][j].Eratio,weight);
	    }
	    
	  }
	}
      }
      if((sct_ratio[i][j].b_E1) && (sct_ratio[i][j].b_E2)){h2_E2E1BothPsnt->Fill(sct_ratio[i][j].E1,sct_ratio[i][j].E2,weight);}
      P_EshortvsElong->Fill(sct_ratio[i][j].E1,sct_ratio[i][j].E2,weight);
      h2_EshortvsElong->Fill(sct_ratio[i][j].E1,sct_ratio[i][j].E2,weight);

    }
  }
  /*  for(int i=0;i<nietaHF;i++)
      for(int j=0;j<niphiHF;j++)
      cout<<"E1:"<<sct_ratio[i][j].E1<<" E2:"<<sct_ratio[i][j].E2<<"b_E1:"<<sct_ratio[i][j].b_E1<<"b_E2:"<<sct_ratio[i][j].b_E2<<endl;*/
  
  memset(sct_ratio,0,sizeof(sct_ratio));
  /*  for(int i=0;i<nietaHF;i++)
      for(int j=0;j<niphiHF;j++)
      cout<<"E1:"<<sct_ratio[i][j].E1<<" E2:"<<sct_ratio[i][j].E2<<"b_E1:"<<sct_ratio[i][j].b_E1<<"b_E2:"<<sct_ratio[i][j].b_E2<<endl;*/
}
