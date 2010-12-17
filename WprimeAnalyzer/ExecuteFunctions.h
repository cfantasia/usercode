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
#include <vector>
#include <algorithm>
#include <limits>
#include "TLorentzVector.h"

#include "ExecuteCuts.h"

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

Int_t           eventID;
Int_t           runNumber;
Int_t           lumiBlock;

Int_t pass_HLT_Photon10_Cleaned_L1R;
Int_t pass_HLT_Photon10_L1R;
Int_t pass_HLT_Photon15_Cleaned_L1R;
Int_t pass_HLT_Photon15_L1R;
Int_t pass_HLT_Ele12_SW_EleIdIsolNoDEtaInEE_L1R;
Int_t pass_HLT_Ele10_LW_EleId_L1R;
Int_t pass_HLT_Ele10_SW_EleId_L1R;
Int_t pass_HLT_Ele10_SW_L1R;
Int_t pass_HLT_Ele12_SW_TightEleIdIsol_L1R;
Int_t pass_HLT_Ele12_SW_TighterEleIdIsol_L1R_v1;
Int_t pass_HLT_Ele15_LW_L1R;
Int_t pass_HLT_Ele15_SW_L1R;
Int_t pass_HLT_Ele15_SW_CaloEleId_L1R;
Int_t pass_HLT_Ele17_SW_CaloEleId_L1R;
Int_t pass_HLT_Ele17_SW_TightEleId_L1R;
Int_t pass_HLT_Ele17_SW_TighterEleIdIsol_L1R_v2;
Int_t pass_HLT_Ele17_SW_TighterEleIdIsol_L1R_v3;
Int_t pass_HLT_Mu3;
Int_t pass_HLT_Mu5;
Int_t pass_HLT_Mu9;
Int_t pass_HLT_Mu11;
Int_t pass_HLT_Mu15_v1;

Int_t prescale_HLT_Photon10_Cleaned_L1R;
Int_t prescale_HLT_Photon10_L1R;
Int_t prescale_HLT_Photon15_Cleaned_L1R;
Int_t prescale_HLT_Photon15_L1R;
Int_t prescale_HLT_Ele12_SW_EleIdIsolNoDEtaInEE_L1R;
Int_t prescale_HLT_Ele10_LW_EleId_L1R;
Int_t prescale_HLT_Ele10_SW_EleId_L1R;
Int_t prescale_HLT_Ele10_SW_L1R;
Int_t prescale_HLT_Ele12_SW_TightEleIdIsol_L1R;
Int_t prescale_HLT_Ele12_SW_TighterEleIdIsol_L1R_v1;
Int_t prescale_HLT_Ele15_LW_L1R;
Int_t prescale_HLT_Ele15_SW_L1R;
Int_t prescale_HLT_Ele15_SW_CaloEleId_L1R;
Int_t prescale_HLT_Ele17_SW_CaloEleId_L1R;
Int_t prescale_HLT_Ele17_SW_TightEleId_L1R;
Int_t prescale_HLT_Ele17_SW_TighterEleIdIsol_L1R_v2;
Int_t prescale_HLT_Ele17_SW_TighterEleIdIsol_L1R_v3;

Int_t prescale_HLT_Mu3;
Int_t prescale_HLT_Mu5;
Int_t prescale_HLT_Mu9;
Int_t prescale_HLT_Mu11;
Int_t prescale_HLT_Mu15_v1;

Int_t           W_flavor;
Int_t           Z_flavor;
Float_t         W_pt;
Float_t         Z_pt;
Float_t         Z_mass;
Float_t         W_transMass;
Float_t         W_phi;
Float_t         W_eta;
Int_t           numberOfZs;
Float_t         met_phi;
Float_t         met_et;
Float_t         pfMet_et;
Float_t         tcMet_et;
Float_t         WZ_invMassMinPz;
Float_t         W_neutrino_pzMinPz;
Float_t         W_neutrino_pzMaxPz;
Float_t         WZ_transMass;
Int_t           W_leptonIndex;
Int_t           Z_leptonIndex1;
Int_t           Z_leptonIndex2;

vector<int  >   *electron_pdgId;
vector<float>   *electron_mass;
vector<float>   *electron_phi;
vector<float>   *electron_eta;
vector<float>   *electron_ScEta;
vector<float>   *electron_pt;
vector<float>   *electron_energy;
vector<float>   *electron_px;
vector<float>   *electron_py;
vector<float>   *electron_pz;
vector<float>   *electron_ScEt;
vector<float>   *electron_trackIso;
vector<float>   *electron_ecaloIso;
vector<float>   *electron_hcaloIso;
vector<float>   *electron_deltaEtaIn;
vector<float>   *electron_deltaPhiIn;
vector<float>   *electron_eOverP;
vector<float>   *electron_hOverE;
vector<float>   *electron_sigmaEtaEta;

vector<int>     *electron_simpleEleId60relIso;
vector<int>     *electron_simpleEleId70relIso;
vector<int>     *electron_simpleEleId80relIso;
vector<int>     *electron_simpleEleId85relIso;
vector<int>     *electron_simpleEleId90relIso;
vector<int>     *electron_simpleEleId95relIso;

vector<int  >   *muon_pdgId;
vector<float>   *muon_energy;
vector<float>   *muon_eta;
vector<float>   *muon_phi;
vector<float>   *muon_pt;
vector<float>   *muon_px;
vector<float>   *muon_py;
vector<float>   *muon_pz;
vector<float>   *muon_innerD0;
vector<float>   *muon_innerD0Error;
vector<float>   *muon_trackIso;
vector<float>   *muon_caloIso;
vector<float>   *muon_relIso;
vector<int  >   *muon_fitType;
vector<int  >   *muon_isGlobal;    
vector<int  >   *muon_isTracker;    
vector<int  >   *muon_numGlobalMatches;    
vector<int  >   *muon_numValidMuonHits;    
vector<int>     *muon_globalNpixelHits;
vector<int>     *muon_globalNtrackerHits;
vector<int>     *muon_globalNstripHits;
vector<float>   *muon_globalChi2;
vector<float>   *muon_globalNdof;
vector<float>   *muon_globalD0;
vector<float>   *muon_globalD0Error;

Float_t         genmet_et;
Float_t         genmet_phi;

vector<int>     *genMother_pdgId;
vector<int>     *genParticle_pdgId;

vector<float>   *genMother_energy;
vector<float>   *genMother_et;
vector<float>   *genMother_eta;
vector<float>   *genMother_mass;
vector<float>   *genMother_phi;
vector<float>   *genMother_pt;
vector<float>   *genMother_px;
vector<float>   *genMother_py;
vector<float>   *genMother_pz;
vector<float>   *genParticle_energy;
vector<float>   *genParticle_et;
vector<float>   *genParticle_eta;
vector<float>   *genParticle_mass;
vector<float>   *genParticle_phi;
vector<float>   *genParticle_pt;
vector<float>   *genParticle_px;
vector<float>   *genParticle_py;
vector<float>   *genParticle_pz;

vector<int>   *electronGenMother_pdgId;
vector<float>   *electronGenMother_energy;
vector<float>   *electronGenMother_px;
vector<float>   *electronGenMother_py;
vector<float>   *electronGenMother_pz;

vector<int>   *muonGenMother_pdgId;
vector<float>   *muonGenMother_energy;
vector<float>   *muonGenMother_px;
vector<float>   *muonGenMother_py;
vector<float>   *muonGenMother_pz;

// +++++++++++++++++++useful constants
const bool debugme = false; //print stuff if active

// +++++++++++++++++++
//value of lumi to be used in the analysis
//the weights will scale accordingly.
const float lumiPb = 1000;//36.1;

// +++++++++++++++++++location of data files and samples info
const string top_level_dir = "/uscms_data/d2/fantasia/38X/";

// +++++++++++++++++++ Histogram Definitions
vector<TH1F*> listOfHists;

TH1F * hEffRel;
TH1F * hEffAbs;
TH1F * hNumEvts;

///My calculated qualities//////////////////
float Ht;
float LeadPt;
float LeadElecPt;
float LeadMuonPt;

#endif//#define _ExecuteFunctions_h_
