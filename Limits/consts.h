#include "TROOT.h"
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <map>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include "TFile.h"
#include "TTree.h" 
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TMath.h"

const float nGenerated = 10000; //Number of MC Sig Evts Gen
const float LumiUsed = 1000; //inv pb
const float sLumiFrac = 0.1;
const float sysEffFrac = 0.05;//Cory: Guess
const float sysEvtFrac = 0.30;//Cory: Guess

const int NLumi = 10;
const float lumi[NLumi] = {36, 200,400,600,800,1000,2000,3000,4000,5000};//inv pb

const int NMass = 7;
const float mass[NMass] = {   300,  400,  500,  600,
                              700,  800,  900};//GeV
float
KFactor(string sample){
  if      (!sample.find("Wprime"))
    return 1.35;//Cory: Don't think this is right
  else if (!sample.find("TC"))
    return 1.35;
  else if (!sample.find("WZ"))
    return 18./10.5;
  else if (!sample.find("TTbar"))
    return 165/94.3;
  else if (!sample.find("WenuJets"))
    return 28000/25900.4;
  else if (!sample.find("WmunuJets"))
    return 28000/25900.4;
  else if (!sample.find("WlnuJets"))
    return 28000/25900.4;
  else if (!sample.find("ZJetsBinned"))
    return 2800/2541.89;
  else if (!sample.find("Zee"))
    return 2800/2541.89;
  else if (!sample.find("Zmumu"))
    return 2800/2541.89;
  else if (!sample.find("ZGamma"))
    return 7.3/7.3;//Cory: This is wrong, but no evts survive anyway
  else if (!sample.find("ZZ"))
    return 5.9/4.3;
  else
    cout<<"Didn't find the sample "<<sample
        <<" Not weighted!!!!!\n\n\n";
    return 1.;
}

//---------------------------------------------------------------
TH1F* get_sum_of_hists(TFile* f, map<string,float> & samples,
                       string level, int rebinme=0){
//--------------------------------------------------------------
  TH1F* hall=NULL;
  const int dim = samples.size();
  
  TH1F* h[dim];

  int j=0;
  map<string, float>::iterator iter;
  for (iter=samples.begin(),j=0; iter != samples.end(); ++iter, ++j) {
    
    string histname = iter->first + "/" + level;
    h[j] = (TH1F*)f->Get(histname.c_str());

    if(h[j] == NULL){
      cout<<"Failed Getting "<<histname<<endl;
      continue;
    }

    if(!h[j]->GetSumw2N()) h[j]->Sumw2();
    if (rebinme) h[j]->Rebin(rebinme);
    if(j==0){
      hall = (TH1F*)h[0]->Clone("hall");
      hall->Scale(iter->second);
    }else{
      hall->Add(h[j], iter->second);
    }

  }if(j != dim) cout<<"Something went wrong with map!!!!\n\n\n";
  
  //cout<<"Done with adding histograms...."<<endl;
  return hall;

}

float
AddInQuad(float a, float b){
  return sqrt(a*a + b*b);
}

const float ZWind_low = 80;
const float ZWind_high = 100;
Bool_t reject;
Double_t fline(Double_t *x, Double_t *par)
{
    if (reject && x[0] > ZWind_low && x[0] < ZWind_high) {
      TF1::RejectPoint();
      return 0;
   }
   return par[0] + par[1]*x[0];
}

float
IntegralError(const TH1F* h, int lowbin, int highbin){
  float err2=0;
  for(int bin=lowbin;bin<=highbin;bin++) {
    err2 += TMath::Power( h->GetBinError(bin),2 );
  }
  return sqrt(err2);
}

float
LinearIntegralError(Double_t a, Double_t b, const Double_t * params, const Double_t * errs){
  //Linear Function Error
//y = params[0] + params[1]*x
// integral(y) = params[0]*(b-a) + 0.5*params[1]*(b^2 - a^2)
  return AddInQuad( errs[0]*(b-a),  0.5*errs[1]*(b*b - a*a));
}


