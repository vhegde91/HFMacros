#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include "TH1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TMath.h"
#include "TROOT.h"
#include "TStyle.h"
#include <TPaveStats.h>
TF1 *asymgaussfit(TH1F *his, Double_t *fitrange, Double_t *startvalues, Double_t *parlimitslo, Double_t *parlimitshi, Double_t *fitparams, Double_t *fiterrors, Double_t *ChiSqr, Int_t *NDF);
Int_t asymgausspro(Double_t *params, Double_t &maxx, Double_t &FWHM); 
TCanvas *c_ho = new TCanvas("cname","cname",1500,850);
void Overlay(int etaask);
int fitlinecolor=kRed;
vector<double> peakoffit;
void plots(int etaask=0){

  TFile *fout = new TFile("plots.root", "RECREATE");
  
  char fname[50];
  //sprintf(fname, "test_muons_corr.root");
  sprintf(fname, "254833_E2E1HistsVtx.root");
  
  TFile *_file0 = TFile::Open(fname);
  _file0->cd();
  TDirectory *dqm    = (TDirectory*)_file0->Get("E1E2Cut2Ratio"); dqm->cd();
  //TDirectory *dqm    = (TDirectory*)_file0->Get("E1E2Cut3Ietaiphi"); dqm->cd();
  
  char hname[50];
  c_ho->SetLogy();
  c_ho->Divide(4,2);
  int ietaArray[26]={29,30,31,32,-29,-30,-31,-32,33,34,35,36,-33,-34,-35,-36,37,38,39,40,-37,-38,-39,-40,41,-41};
  // TCanvas *c_ho = new TCanvas("ccname","ccname",1900,1900);
  //c_ho->Divide(4,2);
  TCanvas *c_hoo = new TCanvas("cnamea","cnamea",1500,850);
  c_hoo->Divide(2,1);
  int index=0;
  for(int l=abs(etaask);l<(abs(etaask)+8);l++){
    int ieta;
    if(etaask>40 && index>1){break;}
    if(etaask==33){ieta=ietaArray[8+index];}
    else if(etaask==37){ieta=ietaArray[16+index];}
    else if(etaask==41){ieta=ietaArray[24+index];}
    else{ieta=ietaArray[index];}

    //sprintf(hname, "EneHOTowEta1_%i", index+1);
    if(ieta>0){sprintf(hname, "RatioE2vsE1_ietaP%i", ieta);}
    else{sprintf(hname, "RatioE2vsE1_ietaN%i", abs(ieta));}
	//sprintf(hname, "RatioE2vsE1_ietaN34_iphi%i", index);
    
    index++;
    cout<<"hname "<<hname<<endl;
    
    TH1F *hist = (TH1F*)dqm->Get(hname);
    hist->Rebin(5);
    //        hist->Scale(1.0/hist->Integral());
    TH1F *hist1 = new TH1F(*hist);
    hist1->SetName("2015C");
    
    double mean = hist->GetMean();
    double rms  = hist->GetRMS();
    cout<<"Mean "<< setw(10)<<setprecision(6)<<mean<<setw(8)
	<<"RMS  "<<setw(10)<<setprecision(6)<<rms<<endl;
   
    // Setting fit range and start values for langaus fit
    Double_t fr[2];
    
    int max_bin = hist->GetMaximumBin();
    if (hist->GetBinCenter(max_bin) < 0.0005) {
      Double_t maxCont = 0.0;
      int nextbin = 0;
      
     for(int i=hist->GetMaximumBin()+1; i<hist->GetNbinsX(); i++) {
       if (hist->GetBinContent(i) > 0) {
	 nextbin = i;
	 break;
       }
     }
     
     for (int i=nextbin+1; i<hist->GetNbinsX(); i++) {
       if (hist->GetBinContent(i) > maxCont) {
	 maxCont = hist->GetBinContent(i);
	 max_bin = i;
       }
     }
    }
    
    cout << "max_bin "<<max_bin <<"  max_bin Center "
	 << hist->GetBinCenter(max_bin)<< "  max_bin Content " 
	 << hist->GetBinContent(max_bin) << endl;
   
    int last_bin = max_bin;  double preCont = hist->GetBinContent(last_bin);
    for(int i=max_bin-1; i>=0; i--){
      if(hist->GetBinContent(i)<preCont){
	preCont = hist->GetBinCenter(i);
       last_bin = i;
       break;
      }
    }
    
    //fr[0] = hist1->GetBinCenter(last_bin-1);
    if((abs(ieta))>=39){
      fr[0]=0.08;
    }
    else{
      fr[0] = hist1->GetMean() - 1.5*hist1->GetRMS();
    }
    
    fr[1] = 10.0*hist1->GetMean();
    
    if( abs(ieta)==4 ) fr[0] = 0.0032;
    
    //     fr[0] =  hist->GetBinCenter(max_bin-3);
    //     fr[1]=10.0*hist->GetMean();
    cout << "================================ " << endl;
    cout << "Fit Range   Max  " << hist->GetBinCenter(max_bin) << "   Range "
	 << fr[0] << "  " << fr[1] << endl;
    TCanvas *c_hoo = new TCanvas("cnamea","cnamea",1500,1500);
    //hist->Fit("landau", "", "", fr[0], fr[1]);
    hist->Fit("gaus", "", "", fr[0], fr[1]);
    //TF1 *fit = hist->GetFunction("landau");
    TF1 *fit = hist->GetFunction("gaus");
    double p1 = fit->GetParameter(1);
    double p2 = fit->GetParameter(2);
    //cout <<"landau "<<endl;
    cout <<"gaus "<<endl;
    cout <<"Eta "<<ieta<< "   MP " << p1 << " +- " << setw(10)<< fit->GetParError(1)
	 << "  Sigma "<< p2 << " +- " << setw(10)<< fit->GetParError(2)<<endl <<endl;
    cout << "&&&&&&&&&================================&&&&&&&&&&&& " << endl;
    
    Double_t sv1[4], pllo1[4], plhi1[4], fp1[4], fpe1[4];
    //pllo1[0]= 0.0;    pllo1[1]= 0.0;   pllo1[2]=0.0;      pllo1[3]=0.0;
    //plhi1[0]= 10.0;    plhi1[1]= 1.0;   plhi1[2]=200000.0; plhi1[3]=1.0;
    //sv1[0]=0.0; sv1[1]= hist1->GetBinCenter(max_bin); sv1[2]=100000.0; sv1[3]=0.25;
    
    pllo1[0]= 0.0;   pllo1[1]=  0.0;   pllo1[2]=0;     pllo1[3]=0.0;
    plhi1[0]= 1.0;    plhi1[1]= 1.0;   plhi1[2]=10.0;      plhi1[3]=100000.0;
    //sv1[0]=0.0; sv1[1]= hist1->GetBinCenter(max_bin); sv1[2]=100000.0; sv1[3]=0.25;
    sv1[0] = hist1->GetBinCenter(max_bin); sv1[1]=0.3; sv1[2]=0.3; sv1[3]=70000;
    
    //fr[0] = 0.1; //hist1->GetMean()-2.0*hist1->GetRMS();
    std::cout << " ***** " << hist1->GetMean() << " **** " <<  hist1->GetRMS()
	      << " " << hist1->GetMean() - 0.5*hist1->GetRMS()
	      << std::endl;
    if((abs(ieta))>=39){
      fr[0]=0.08;
    }
    else{
      fr[0] = hist1->GetMean() - 1.5*hist1->GetRMS();
    }
    fr[1] = 10.0*hist1->GetMean();
    
    Double_t chisqr1, SNRPeak1, SNRFWHM;
    Int_t    ndf1;
    fitlinecolor=kRed;
    //TF1 *fitHO = langaufit(hist1,fr,sv1,pllo1,plhi1,fp1,fpe1,&chisqr1,&ndf1);
    TF1 *fitHO = asymgaussfit(hist1,fr,sv1,pllo1,plhi1,fp1,fpe1,&chisqr1,&ndf1);
    cout << "langaus"<<endl;
    
    cout <<"Eta "<<ieta<< "   MP " << setw(10) << fp1[0] << " +- " << setw(10)
	 << fpe1[0] << " Width " << fp1[1] << " ErrFPar " << fp1[2] << " NormFactor " << fp1[3] << endl;
    cout<< endl;
    
    asymgausspro(fp1,SNRPeak1,SNRFWHM);
    
    cout << "asymgauss peak finder "<<endl;
    cout<< "Eta "<<ieta<< "   MP " << setw(10) << fp1[1] << " +- " << setw(10)
	<< fpe1[1] << "  Max@@ " << setw(10) << SNRPeak1 << "  FWHM " << setw(10)
	<< SNRFWHM << endl;
    cout<<"------------------------------------------------------------"<<endl;
    peakoffit.push_back(SNRPeak1);
    float error1 = (fpe1[1]/fp1[1])*SNRPeak1;
    
    gStyle->SetOptFit(101);
    char cname[50], img[50];
    sprintf(cname, "c_%s", hname);
    hist1->GetXaxis()->SetTitle("R_{S/L}");
   
   
   
    
    //hist->GetXaxis()->SetRangeUser(0.0005, 0.04);
    //---hist->Draw();
    //---fit->Draw("same");
    //---c_hoo->cd(2);
    //hist1->GetXaxis()->SetRangeUser(0.0005, 0.04);
    
    c_ho->cd(index);
    c_ho->SetLogy();
    hist1->Draw();
    fitHO->Draw("sames");
    //    hist1->SetMaximum(0.07);
    
    hist1->SetLineColor(fitlinecolor);
    //hist1->SetLineColor(kBlue);
    //    hist1->SetLineWidth(2);
    TPaveStats *st=(TPaveStats*)hist1->FindObject("stats");
    st->SetLineColor(fitlinecolor);
    st->SetTextColor(fitlinecolor);
    st->SetX1NDC(0.55);
    st->SetX2NDC(0.98); 
    st->SetY1NDC(0.93);
    st->SetY2NDC(0.55);
  }
  //Overlay(etaask);
  fout->cd();
  c_ho->Write();
  
  
  
  
  
  fout->Close();
  cout<<"*********************************************************************"<<endl;
  //for(int i=0;i<peakoffit.size();i++){
  for(int i=peakoffit.size()-1;i>=0;i--){
    cout<<peakoffit[i]<<",";
  }
 cout<<"*********************************************************************"<<endl;
}



//*** added by Seema// 
Double_t asymgauss(Double_t *x, Double_t *par) {
  //double sum = TMath::Gaus(x[0],par[0],par[1]) + TMath::Gaus(x[0],par[0],par[2]*par[1]);
  //double sum = TMath::Gaus(x[0],par[0],par[1]) + TMath::Exp(x[0]/par[2]);
  //double sum = TMath::Gaus(x[0],par[0],par[1]) * (TMath::Erf(par[2]* (x[0]-par[0])/(par[1]*sqrt(2.0))) );
  double sum = TMath::Gaus(x[0],par[0],par[1]) * (1+ TMath::Erf(par[2]* (x[0]-par[0])/(par[1]*sqrt(2.0))) );
  return sum*par[3];
}
//**********//

//*** added by Seema//
TF1 *asymgaussfit(TH1F *his, Double_t *fitrange, Double_t *startvalues, Double_t *parlimitslo, Double_t *parlimitshi, Double_t *fitparams, Double_t *fiterrors, Double_t *ChiSqr, Int_t *NDF)
{
   // Once again, here are the Landau * Gaussian parameters:
   //   par[0]=Width (scale) parameter of Landau density
   //   par[1]=Most Probable (MP, location) parameter of Landau density
   //   par[2]=Total area (integral inf to inf, normalization constant)
   //   par[3]=Width (sigma) of convoluted Gaussian function
   //
   // Variables for langaufit call:
   //   his             histogram to fit
   //   fitrange[2]     lo and hi boundaries of fit range
   //   startvalues[4]  reasonable start values for the fit
   //   parlimitslo[4]  lower parameter limits
   //   parlimitshi[4]  upper parameter limits
   //   fitparams[4]    returns the final fit parameters
   //   fiterrors[4]    returns the final fit errors
   //   ChiSqr          returns the chi square
   //   NDF             returns ndf

   Int_t i;
   Char_t FunName[100];

   sprintf(FunName,"Fitfcn_%s",his->GetName());

   TF1 *ffitold = (TF1*)gROOT->GetListOfFunctions()->FindObject(FunName);
   if (ffitold) delete ffitold;

   //TF1 *ffit = new TF1(FunName,langaufun,fitrange[0],fitrange[1],4);
   TF1 *ffit = new TF1(FunName,asymgauss,fitrange[0],fitrange[1],4);
   ffit->SetParameters(startvalues);
   ffit->SetParNames("Mu","Width","ErrFPar","NormFactor");
   
   for (i=0; i<4; i++) {
      ffit->SetParLimits(i, parlimitslo[i], parlimitshi[i]);
   }
   ffit->SetLineColor(fitlinecolor);
   his->Fit(FunName,"RB");   // fit within specified range, use ParLimits, do not plot

   ffit->GetParameters(fitparams);    // obtain fit parameters
   for (i=0; i<4; i++) {
      fiterrors[i] = ffit->GetParError(i);     // obtain fit parameter errors
   }
   ChiSqr[0] = ffit->GetChisquare();  // obtain chi^2
   NDF[0] = ffit->GetNDF();           // obtain ndf

   return (ffit);              // return fit function

}
//**********//


Int_t asymgausspro(Double_t *params, Double_t &maxx, Double_t &FWHM) {

   // Seaches for the location (x value) at the maximum of the 
   // Landau-Gaussian convolute and its full width at half-maximum.
   //
   // The search is probably not very efficient, but it's a first try.

   Double_t p,x,fy,fxr,fxl;
   Double_t step;
   Double_t l,lold;
   Int_t i = 0;
   Int_t MAXCALLS = 10000;


   // Search for maximum

   p = params[1] - 0.1 * params[0];
   step = 0.05 * params[0];
   lold = -2.0;
   l    = -1.0;


   while ( (l != lold) && (i < MAXCALLS) ) {
      i++;

      lold = l;
      x = p + step;
      //l = langaufun(&x,params);
      l = asymgauss(&x,params);
 
      if (l < lold)
         step = -step/10;
 
      p += step;
   }

   if (i == MAXCALLS)
      return (-1);

   maxx = x;

   fy = l/2;


   // Search for right x location of fy

   p = maxx + params[0];
   step = params[0];
   lold = -2.0;
   l    = -1e300;
   i    = 0;


   while ( (l != lold) && (i < MAXCALLS) ) {
      i++;

      lold = l;
      x = p + step;
      //l = TMath::Abs(langaufun(&x,params) - fy);
      l = TMath::Abs(asymgauss(&x,params) - fy);
 
      if (l > lold)
         step = -step/10;
 
      p += step;
   }

   if (i == MAXCALLS)
      return (-2);

   fxr = x;


   // Search for left x location of fy

   p = maxx - 0.5 * params[0];
   step = -params[0];
   lold = -2.0;
   l    = -1e300;
   i    = 0;

   while ( (l != lold) && (i < MAXCALLS) ) {
      i++;

      lold = l;
      x = p + step;
      //l = TMath::Abs(langaufun(&x,params) - fy);
      l = TMath::Abs(asymgauss(&x,params) - fy);
 
      if (l > lold)
         step = -step/10;
 
      p += step;
   }

   if (i == MAXCALLS)
      return (-3);


   fxl = x;

   FWHM = fxr - fxl;
   return (0);
}




//Overlay-------------------------------------------------------

void Overlay(int etaask){
char fname[50];
  //sprintf(fname, "test_muons_corr.root");
  sprintf(fname, "2012D_E2E1HistsVtx.root");
  
  TFile *_file1 = TFile::Open(fname);
  _file1->cd();
  TDirectory *dqm    = (TDirectory*)_file1->Get("E1E2Cut4Ratio"); dqm->cd();
  //TDirectory *dqm    = (TDirectory*)_file0->Get("E1E2Cut3Ietaiphi"); dqm->cd();
  
  char hname[50];
  
  int ietaArray[26]={29,30,31,32,-29,-30,-31,-32,33,34,35,36,-33,-34,-35,-36,37,38,39,40,-37,-38,-39,-40,41,-41};
// TCanvas *c_ho = new TCanvas("cname","cname",1900,1900);
//c_ho->Divide(4,2);
  TCanvas *c_hoo = new TCanvas("cnamea","cnamea",1500,1500);
  //c_hoo->Divide(2,1);
  int index=0;
  for(int l=abs(etaask);l<(abs(etaask)+8);l++){
    int ieta;
    if(etaask>40 && index>1){break;}
    if(etaask==33){ieta=ietaArray[8+index];}
    else if(etaask==37){ieta=ietaArray[16+index];}
    else if(etaask==41){ieta=ietaArray[24+index];}
    else{ieta=ietaArray[index];}

    //sprintf(hname, "EneHOTowEta1_%i", index+1);
    if(ieta>0){sprintf(hname, "RatioE2vsE1_ietaP%i", ieta);}
    else{sprintf(hname, "RatioE2vsE1_ietaN%i", abs(ieta));}
	//sprintf(hname, "RatioE2vsE1_ietaN34_iphi%i", index);
    
    index++;
    cout<<"hname "<<hname<<endl;
    
    TH1F *hist = (TH1F*)dqm->Get(hname);
    hist->Rebin(5);
    //    hist->Scale(1.0/hist->Integral());
    //hist->Scale(3);
    TH1F *hist1 = new TH1F(*hist);
    hist1->SetName("2012D");
    
    double mean = hist->GetMean();
    double rms  = hist->GetRMS();
    cout<<"Mean "<< setw(10)<<setprecision(6)<<mean<<setw(8)
	<<"RMS  "<<setw(10)<<setprecision(6)<<rms<<endl;
   
    // Setting fit range and start values for langaus fit
    Double_t fr[2];
    
    int max_bin = hist->GetMaximumBin();
    if (hist->GetBinCenter(max_bin) < 0.0005) {
      Double_t maxCont = 0.0;
      int nextbin = 0;
      
     for(int i=hist->GetMaximumBin()+1; i<hist->GetNbinsX(); i++) {
       if (hist->GetBinContent(i) > 0) {
	 nextbin = i;
	 break;
       }
     }
     
     for (int i=nextbin+1; i<hist->GetNbinsX(); i++) {
       if (hist->GetBinContent(i) > maxCont) {
	 maxCont = hist->GetBinContent(i);
	 max_bin = i;
       }
     }
    }
    
    cout << "max_bin "<<max_bin <<"  max_bin Center "
	 << hist->GetBinCenter(max_bin)<< "  max_bin Content " 
	 << hist->GetBinContent(max_bin) << endl;
   
    int last_bin = max_bin;  double preCont = hist->GetBinContent(last_bin);
    for(int i=max_bin-1; i>=0; i--){
      if(hist->GetBinContent(i)<preCont){
	preCont = hist->GetBinCenter(i);
       last_bin = i;
       break;
      }
    }
    
    //fr[0] = hist1->GetBinCenter(last_bin-1);
    if((abs(ieta))>=39){
      fr[0]=0.08;
    }
    else{
      fr[0] = hist1->GetMean() - 1.5*hist1->GetRMS();
    }
    
    fr[1] = 10.0*hist1->GetMean();
    
    if( abs(ieta)==4 ) fr[0] = 0.0032;
    
    //     fr[0] =  hist->GetBinCenter(max_bin-3);
    //     fr[1]=10.0*hist->GetMean();
    cout << "================================ " << endl;
    cout << "Fit Range   Max  " << hist->GetBinCenter(max_bin) << "   Range "
	 << fr[0] << "  " << fr[1] << endl;
    TCanvas *c_hoo = new TCanvas("cnamea","cnamea",1500,1500);
    //hist->Fit("landau", "", "", fr[0], fr[1]);
    hist->Fit("gaus", "", "", fr[0], fr[1]);
    //TF1 *fit = hist->GetFunction("landau");
    TF1 *fit = hist->GetFunction("gaus");
    double p1 = fit->GetParameter(1);
    double p2 = fit->GetParameter(2);
    //cout <<"landau "<<endl;
    cout <<"gaus "<<endl;
    cout <<"Eta "<<ieta<< "   MP " << p1 << " +- " << setw(10)<< fit->GetParError(1)
	 << "  Sigma "<< p2 << " +- " << setw(10)<< fit->GetParError(2)<<endl <<endl;
    cout << "&&&&&&&&&================================&&&&&&&&&&&& " << endl;
    
    Double_t sv1[4], pllo1[4], plhi1[4], fp1[4], fpe1[4];
    //pllo1[0]= 0.0;    pllo1[1]= 0.0;   pllo1[2]=0.0;      pllo1[3]=0.0;
    //plhi1[0]= 10.0;    plhi1[1]= 1.0;   plhi1[2]=200000.0; plhi1[3]=1.0;
    //sv1[0]=0.0; sv1[1]= hist1->GetBinCenter(max_bin); sv1[2]=100000.0; sv1[3]=0.25;
    
    pllo1[0]= 0.0;   pllo1[1]=  0.0;   pllo1[2]=0;     pllo1[3]=0.0;
    plhi1[0]= 1.0;    plhi1[1]= 1.0;   plhi1[2]=10.0;      plhi1[3]=100000.0;
    //sv1[0]=0.0; sv1[1]= hist1->GetBinCenter(max_bin); sv1[2]=100000.0; sv1[3]=0.25;
    sv1[0] = hist1->GetBinCenter(max_bin); sv1[1]=0.3; sv1[2]=0.3; sv1[3]=70000;
    
    //fr[0] = 0.1; //hist1->GetMean()-2.0*hist1->GetRMS();
    std::cout << " ***** " << hist1->GetMean() << " **** " <<  hist1->GetRMS()
	      << " " << hist1->GetMean() - 0.5*hist1->GetRMS()
	      << std::endl;
    if((abs(ieta))>=39){
      fr[0]=0.08;
    }
    else{
      fr[0] = hist1->GetMean() - 1.5*hist1->GetRMS();
    }
    fr[1] = 10.0*hist1->GetMean();
    
    Double_t chisqr1, SNRPeak1, SNRFWHM;
    Int_t    ndf1;
    fitlinecolor=kRed;
    //TF1 *fitHO = langaufit(hist1,fr,sv1,pllo1,plhi1,fp1,fpe1,&chisqr1,&ndf1);
    TF1 *fitHO = asymgaussfit(hist1,fr,sv1,pllo1,plhi1,fp1,fpe1,&chisqr1,&ndf1);
    cout << "langaus"<<endl;
    
    cout <<"Eta "<<ieta<< "   MP " << setw(10) << fp1[0] << " +- " << setw(10)
	 << fpe1[0] << " Width " << fp1[1] << " ErrFPar " << fp1[2] << " NormFactor " << fp1[3] << endl;
    cout<< endl;
    
    asymgausspro(fp1,SNRPeak1,SNRFWHM);
    
    cout << "asymgauss peak finder "<<endl;
    cout<< "Eta "<<ieta<< "   MP " << setw(10) << fp1[1] << " +- " << setw(10)
	<< fpe1[1] << "  Max " << setw(10) << SNRPeak1 << "  FWHM " << setw(10)
	<< SNRFWHM << endl;
    cout<<"------------------------------------------------------------"<<endl;
    
    float error1 = (fpe1[1]/fp1[1])*SNRPeak1;
    
    gStyle->SetOptFit(101);
    char cname[50], img[50];
    sprintf(cname, "c_%s", hname);
    hist1->GetXaxis()->SetTitle("Ratio");
    
   
   
    
    //hist->GetXaxis()->SetRangeUser(0.0005, 0.04);
    //---hist->Draw();
    //---fit->Draw("same");
    //---c_hoo->cd(2);
    //hist1->GetXaxis()->SetRangeUser(0.0005, 0.04);

    c_ho->cd(index);
    hist1->Draw("sames");
    fitHO->Draw("sames");
    
    hist1->SetLineColor(fitlinecolor);
    TPaveStats *st=(TPaveStats*)hist1->FindObject("stats");
    st->SetLineColor(fitlinecolor);
    st->SetTextColor(fitlinecolor);
    st->SetX1NDC(0.55);
    st->SetX2NDC(0.98); 
    st->SetY1NDC(0.55);
    st->SetY2NDC(0.15);
  }
  
}


