//---------------------------------------------
// Author: Edgar Carrera
// 2010-01-13
// This macro will be used for analyzing
// Wprime -> WZ -> lllnu events
// It works on an root-uple of events with
// variables created by the "official" CMS WZ code
//---------------------------------------------
#ifndef _ExecuteAnalysis_h_
#define _ExecuteAnalysis_h_

#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TMath.h"
#include "TEntryList.h"
#include <vector>
#include <algorithm>
#include <limits>
#include "TLorentzVector.h"

//#include "../wprime_wz_macros/Cuts.h"
#include "Cuts.h"

//gROOT->Reset();

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

// +++++++++++++++++++location of data files and samples info
//string top_level_dir = "/localdata/ecarrera/analyses/wprime_to_wz/root_uples/";
string top_level_dir = "/uscms_data/d2/fantasia/CMSSW_3_5_7/src/Wprime/";
//string top_level_dir = "dcap://cmsgridftp.fnal.gov:24125/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/"; //Doesn't work
//string top_level_dir = "dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/"; //Works

// +++++++++++++++++++Variables to store Branch Addresses:
Int_t           W_flavor;
Int_t           Z_flavor;
Float_t         W_pt;
Float_t         Z_pt;
Float_t         Z_mass;
Float_t         W_transMass;
Int_t           numberOfZs;
Float_t         met_et;
Float_t         pfMet_et;
Float_t         WZ_invMassMinPz;
//Float_t         WZ_invMassMaxPz;
Float_t         WZ_transMass;
Int_t           W_leptonIndex;
Int_t           Z_leptonIndex1;
Int_t           Z_leptonIndex2;
Int_t           triggerBitMask;

vector<float>   *electron_eta;
vector<float>   *electron_pt;
vector<float>   *electron_et;
vector<float>   *electron_trackIso;
//vector<float>   *electron_caloIso;
vector<float>   *electron_ecaloIso;
vector<float>   *electron_hcaloIso;
vector<float>   *electron_deltaEtaIn;
vector<float>   *electron_deltaPhiIn;
vector<float>   *electron_eOverP;
vector<float>   *electron_hOverE;
vector<float>   *electron_sigmaEtaEta;

vector<float>   *muon_eta;
vector<float>   *muon_pt;
vector<float>   *muon_innerD0;
vector<float>   *muon_innerD0Error;
vector<float>   *muon_trackIso;
vector<float>   *muon_ecaloIso;
vector<float>   *muon_hcaloIso;
vector<int  >   *muon_fitType;
vector<int  >   *muon_GlobalandTracker;    
vector<int  >   *muon_numGlobalMatches;    
vector<int  >   *muon_numValidMuonHits;    
vector<int>     *muon_globalNpixelHits;
vector<int>     *muon_globalNtrackerHits;
vector<int>     *muon_globalNstripHits;
vector<float>   *muon_globalChi2;
vector<float>   *muon_globalNdof;
vector<float>   *muon_globalD0;

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

///My calculated qualities//////////////////
float Ht;
float WZ_genMass;
/////////////////////////

// +++++++++++++++++++useful constants
const double PI    = 2.0 * acos(0.);
const double TWOPI = 2.0 * PI;
const bool debugme = false; //print stuff if active

// +++++++++++++++++++
//value of lumi to be used in the analysis
//the weights will scale accordingly.
const float lumiPb = 1000;


// +++++++++++++++++++ Histogram Definitions
/*
const int Num_histo_sets = 10; //matches the number of cuts
const string Cut_Name[] = {"HLT", "ValidWZ", "NumZs", "Muon", "Elec", 
                           "ZMass", "Ht", "Zpt", "Wpt", "FwdJets"};
*/
const int Num_histo_sets = 9; //matches the number of cuts
const string Cut_Name[] = {"HLT", "ValidWZ", "NumZs", "Zdecay", "Wdecay", 
                           "Ht", "Zpt", "Wpt", "MET"};
TH1F * hWZInvMass[Num_histo_sets];
TH1F * hWZTransMass[Num_histo_sets];
TH1F * hHt[Num_histo_sets];
TH1F * hWpt[Num_histo_sets];
TH1F * hZpt[Num_histo_sets];
TH1F * hGenWZInvMass[Num_histo_sets];
TH1F * hMET[Num_histo_sets];
TH1F * hZmass[Num_histo_sets];
TH1F * hZeemass[Num_histo_sets];
TH1F * hZmumumass[Num_histo_sets];
TH1F * hWTransmass[Num_histo_sets];

TH1F * hElecPt[Num_histo_sets];
TH1F * hElecdEta[Num_histo_sets];
TH1F * hElecdPhi[Num_histo_sets];
TH1F * hElecSigmann[Num_histo_sets];
TH1F * hElecEP[Num_histo_sets];
TH1F * hElecHE[Num_histo_sets];
//TH1F * hElecRelCaloIso[Num_histo_sets];
TH1F * hElecRelTrkIso[Num_histo_sets];


TH1F * hEffRel;
TH1F * hEffAbs;
TH1F * hNumEvts;

TEntryList *cutlist[Num_histo_sets];


// +++++++++++++++++++ Declare the methods that we use:
void RecruitOrderedFiles(vector<InputFile> & files, const int& Nfiles,
                         const int& filenum_low, const int& filenum_step,
                         const string& mask1, const string& mask2, 
                         const string& file_desc);
string convertIntToStr(int number);
void getEff(float & eff, float & deff, float Num, float Denom);
double deltaEta(double eta1, double eta2);
double deltaPhi(double phi1, double phi2);
bool inBarrel(float eta, int parent);
bool inEndCap(float eta, int parent);

void Declare_Histos();
void Declare_Lists();
double deltaR(double eta1, double phi1, double eta2, double phi2);
int Check_Files(unsigned Nfiles, vector<InputFile> & files);
void Load_Input_Files(string file_desc,vector<InputFile> & files,float lumiPb);
int Load_Cross_Sections(vector<InputFile> & wzjj_files,
                        vector<InputFile> & wprime400_files);
void Set_Branch_Addresses(TTree* WZtree);
void Fill_Histos(int index, float weight);
void saveHistos(TFile * fout, string dir);
void printSummary(ofstream & out, const string& dir, const float& Nthe_evt,
                  const float& Nexp_evt, float Nexp_evt_cut[]);
void Tabulate_Me(int Num_surv_cut[], int& cut_index,const float& weight,const int& evtnum);
void Get_Distributions(vector<InputFile>& files,TFile *fout, 
                       string dir, ofstream & out);
void ExecuteAnalysis();

///
//methods for the cuts
bool PassTriggersCut();
bool PassValidWandZCut();
bool PassMaxNumberOfZsCut();
bool PassWptCut();
bool PassZptCut();
bool PassHtCut();
bool PassHtMetCut();
bool PassMETCut();
//////////////////
bool PassWDecayCut();
bool PassZDecayCut();
bool PassWenuCut();
bool PassWmunuCut();
bool PassZeeCut();
bool PassZmumuCut();

bool PassElecEtaCut(int idx,int parent,bool inEC);
bool PassElecEtCut(int idx,int parent,bool inEC);
bool PassElecMatchedCut(int idx,int parent,bool inEC);
bool PassElecNMissHitsCut(int idx,int parent,bool inEC);
bool PassElecDistCut(int idx,int parent,bool inEC);
bool PassElecdCotThetaCut(int idx,int parent,bool inEC);
bool PassElecZmassCut(int idx,int parent,bool inEC);
bool PassElecTrkRelIsoCut(int idx,int parent,bool inEC);
bool PassElecECalRelIsoCut(int idx,int parent,bool inEC);
bool PassElecHCalRelIsoCut(int idx,int parent,bool inEC);
bool PassElecSigmaEtaEtaCut(int idx,int parent,bool inEC);
bool PassElecDeltaPhiCut(int idx,int parent,bool inEC);
bool PassElecDeltaEtaCut(int idx,int parent,bool inEC);
bool PassElecHOverECut(int idx,int parent,bool inEC);

bool PassMuonTypeCut(int idx,int parent);
bool PassMuonNpixhitCut(int idx,int parent);
bool PassMuonNtrkhitCut(int idx,int parent);
bool PassMuonNormChi2Cut(int idx,int parent);
bool PassMuonHitsUsedCut(int idx,int parent);
bool PassMuonStationsCut(int idx,int parent);
bool PassMuonEtaCut(int idx,int parent);
bool PassMuonPtCut(int idx,int parent);
bool PassMuonCombRelIsoCut(int idx,int parent);
bool PassMuonMETCut(int idx,int parent);
bool PassMuonDxyCut(int idx,int parent);
bool PassMuonNstriphitCut(int idx,int parent);
bool PassMuonTrkAbsIsoCut(int idx,int parent);
bool PassMuonEtaCut(int idx,int parent);
bool PassMuonZmassCut(int idx,int parent);

float Calc_Ht();
float Calc_GenWZInvMass();


#endif//#define _ExecuteAnalysis_h_
