#ifndef _ExecuteFunctions_h_
#define _ExecuteFunctions_h_

#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TMath.h"
#include <algorithm>
#include <limits>
#include "TLorentzVector.h"

#include "ExecuteCuts.h"
#include "ExecuteVariables.h"

using namespace std;

// ++++++++++++++data structure to accumulate info about the file
struct InputFile{
  float x_sect; // cross-section in pb
  float Nprod_evt; // # of events produced
  float weight; // cross-section * integrated luminosity / (# of events produced)
  string pathname;
  string description; // sample description
  TTree * tree; // pointer to ROOT file
  //
  InputFile(){
    x_sect = 0; Nprod_evt = 0; weight = 0; tree = 0;
  }
  InputFile(float cross_sect)
  {
    x_sect = cross_sect; Nprod_evt = 0; weight = 0; tree = 0;
  }
};


// +++++++++++++++++++ Declare the methods that we use:
void RecruitOrderedFiles(vector<InputFile> & files, const int& Nfiles,
                         const int& filenum_low, const int& filenum_step,
                         const string& mask1, const string& mask2, 
                         const string& file_desc);
string convertIntToStr(int number);
string convertFloatToStr(int number);
void getEff(float & eff, float & deff, float Num, float Denom);
double deltaEta(double eta1, double eta2);
double deltaPhi(double phi1, double phi2);

void Declare_Histos();
void DeclareHistoSet(string n, string t, string xtitle,
                     int nbins, float min, float max,
                     const vector<string> & Cuts, TH1F** h);
double deltaR(double eta1, double phi1, double eta2, double phi2);
int Check_Files(unsigned Nfiles, vector<InputFile> & files);
bool Load_Input_Files(string file_desc,vector<InputFile> & files);
void Set_Branch_Addresses(TTree* WZtree);
void Fill_Histos(int index, float weight);
void saveHistos(TFile * fout, string dir);
void deleteHistos();
void printSummary(ofstream & out, const string& dir, const float& Nthe_evt,
                  const float& Nexp_evt, float Nexp_evt_cut[], const vector<string> & Cuts);
void Tabulate_Me(int Num_surv_cut[], int& cut_index,const float& weight);
void Get_Distributions(vector<InputFile>& files,TFile *fout, 
                       string dir, ofstream & out);
void UseSample(string dir, vector<InputFile> & files,
               TFile * fout, ofstream & out);

void PrintEvent();
void PrintEventFull();
void PrintElectron(int idx, int parent);
void PrintMuon(int idx, int parent);
float CalcLeadPt(int type=0);

// +++++++++++++++++++ Histogram Definitions
vector<TH1F*> listOfHists;

TH1F * hEffRel;
TH1F * hEffAbs;
TH1F * hNumEvts;

#endif//#define _ExecuteFunctions_h_
