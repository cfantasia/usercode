#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
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
TH1F* get_sum_of_hists(vector<string> samples,string level){
//--------------------------------------------------------------
  int rebinme = 1;
  TH1F* hall;
  const int dim = samples.size();
  TFile *f = TFile::Open("../WprimeAnalyzer/Wprime_analysis.root", "read");

  TH1F* h[dim];
  for (int j = 0;j<dim;++j){
    string histname = samples[j]+"/hWZInvMass"+level;
    h[j] = (TH1F*)f->Get(histname.c_str());
    h[j]->Sumw2();
    if (rebinme) h[j]->Rebin(rebinme);
    //cout<<"Done with adding this histo"<<endl;
  }
  hall = (TH1F*)h[0]->Clone();
  string hallname = "hall";
  hall->SetName(hallname.c_str());
  
  for (int k =1;k<dim;++k){
    hall->Add(h[k]);
  }
  //cout<<"Done with adding histograms...."<<endl;
  return hall;

}
