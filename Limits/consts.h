#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <map>
#include "TFile.h"
#include "TTree.h" 
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"

const float nGenerated = 10000; //Number of MC Sig Evts Gen
const float LumiUsed = 1000; //inv pb
const float sLumiFrac = 0.1;
const float sysEff = 0.05;//Guess?

const int NLumi = 9;
const float lumi[NLumi] = {200,400,600,800,1000,2000,3000,4000,5000};//inv pb

const int NMass = 6;
const float mass[NMass] = {   400,  500,  600,
                              700,  800,  900};//GeV
const float K = 1.35;//K factor
const float xsec[NMass] = {K*0.0890, K*0.0360, K*0.0150,  
                           K*0.0078, K*0.0044, K*0.0023};//pb

const int NMass_TC = 4;
const float mass_TC[NMass_TC] = {225,300,400,500};//GeV

//pb low pi mass
const float K_TC = 1.35;//K factor for TC
const float xsec_TC[NMass_TC] = {K_TC*0.148066, K_TC*0.0448773, 
                                 K_TC*0.0129922, K_TC*0.00522783}; 

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

    if(h[j] == NULL) cout<<"Failed Getting "<<histname<<endl;

    //h[j]->Sumw2();
    if (rebinme) h[j]->Rebin(rebinme);
    if(j==0){
      hall = (TH1F*)h[0]->Clone("hall");
      hall->Sumw2();
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
