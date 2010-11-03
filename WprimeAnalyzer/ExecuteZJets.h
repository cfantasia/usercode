//---------------------------------------------
// Author: Edgar Carrera
// 2010-01-13
// This macro will be used for analyzing
// Wprime -> WZ -> lllnu events
// It works on an root-uple of events with
// variables created by the "official" CMS WZ code
//---------------------------------------------
#ifndef _ExecuteZJets_h_
#define _ExecuteZJets_h_

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
#include <vector>
#include <algorithm>
#include <limits>
#include "TLorentzVector.h"

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
string top_level_dir = "/uscms_data/d2/fantasia/CMSSW_3_8_4_patch2/src/DileptonSkim/";
//string top_level_dir = "dcap://cmsgridftp.fnal.gov:24125/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/"; //Doesn't work
//string top_level_dir = "dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/"; //Works

// +++++++++++++++++++Variables to store Branch Addresses:
Int_t           eventID;

Int_t           HLT_Mu9;
Int_t           HLT_Photon10_L1R;

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
Float_t         WZ_invMassMinPz;
Float_t         W_neutrino_pzMinPz;
Float_t         W_neutrino_pzMaxPz;
//Float_t         WZ_invMassMaxPz;
Float_t         WZ_transMass;
Int_t           W_leptonIndex;
Int_t           Z_leptonIndex1;
Int_t           Z_leptonIndex2;
Int_t           triggerBitMask;

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
//vector<float>   *electron_caloIso;
vector<float>   *electron_ecaloIso;
vector<float>   *electron_hcaloIso;
vector<float>   *electron_deltaEtaIn;
vector<float>   *electron_deltaPhiIn;
vector<float>   *electron_eOverP;
vector<float>   *electron_hOverE;
vector<float>   *electron_sigmaEtaEta;

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
//vector<float>   *muon_ecaloIso;
//vector<float>   *muon_hcaloIso;
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

///My calculated qualities//////////////////
float Ht;
bool TT;
bool TF;
float WZ_genMass;
float W_genTransMass;
float W_genpt;
float W_genphi;
float W_geneta;
float W_genpz;
float W_mass;
float Z_genMass;
float Z_genEta;
float Z_genPt;
float gendp;
float recodp;
float WlepGenPt;
float WDpt;
float WDphi;
float WDeta;
float WDr;

float lep_genpz;

float neu_px;
float neu_py;
float neu_pz;
float neu_genpx;
float neu_genpy;
float neu_genpz;
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
const int Num_histo_sets = 26; //matches the number of cuts
const string Cut_Name[] = {"NoCuts", "HLT", "ValidWZ", "NumZs", 
                           "ElecEta","ElecEt", 
                           "ElecSigmaEtaEta", "ElecDPhi",
                           "ElecDEta", "ElecHOverE",
                           "MuonType", "MuonEta",
                           "MuonPt", "MuonDxy",
                           "MuonNormChi2", "MuonNPix",
                           "MuonNTrk", "MuonStation",
                           "MuonHitsUsed",
                           "Zdecay", "Wdecay", 
                           "Ht", "Zpt", "Wpt", "MET",
                           "AllCuts"};
TH1F * hWZInvMass[Num_histo_sets];
TH1F * hWZTransMass[Num_histo_sets];
TH1F * hHt[Num_histo_sets];
TH1F * hWpt[Num_histo_sets];
TH1F * hZpt[Num_histo_sets];
TH1F * hMET[Num_histo_sets];
TH1F * hMETDiff[Num_histo_sets];
TH1F * hZmass[Num_histo_sets];
TH1F * hZeemass[Num_histo_sets];
TH1F * hZmumumass[Num_histo_sets];
TH1F * hWTransmass[Num_histo_sets];
TH1F * hWenuTransmass[Num_histo_sets];
TH1F * hWmunuTransmass[Num_histo_sets];

TH1F * hElecPt[Num_histo_sets];
TH1F * hElecEt[Num_histo_sets];
TH1F * hElecdEta[Num_histo_sets];
TH1F * hElecdPhi[Num_histo_sets];
TH1F * hElecSigmann[Num_histo_sets];
TH1F * hElecEP[Num_histo_sets];
TH1F * hElecHE[Num_histo_sets];
//TH1F * hElecRelCaloIso[Num_histo_sets];
TH1F * hElecTrkRelIso[Num_histo_sets];
TH1F * hElecECalRelIso[Num_histo_sets];
TH1F * hElecHCalRelIso[Num_histo_sets];

TH1F * hMuonPt[Num_histo_sets];
TH1F * hMuonDxy[Num_histo_sets];
TH1F * hMuonNormChi2[Num_histo_sets];
TH1F * hMuonNPix[Num_histo_sets];
TH1F * hMuonNTrk[Num_histo_sets];
TH1F * hMuonRelIso[Num_histo_sets];
TH1F * hMuonStation[Num_histo_sets];
TH1F * hMuonSip[Num_histo_sets];

TH1F * hZeemassTT[Num_histo_sets];
TH1F * hZeemassTF[Num_histo_sets];
TH1F * hZmumumassTT[Num_histo_sets];
TH1F * hZmumumassTF[Num_histo_sets];

TH1F * hEffRel;
TH1F * hEffAbs;
TH1F * hNumEvts;

// +++++++++++++++++++ Declare the methods that we use:
void RecruitOrderedFiles(vector<InputFile> & files, const int& Nfiles,
                         const int& filenum_low, const int& filenum_step,
                         const string& mask1, const string& mask2, 
                         const string& file_desc);
string convertIntToStr(int number);
void getEff(float & eff, float & deff, float Num, float Denom);
double deltaEta(double eta1, double eta2);
double deltaPhi(double phi1, double phi2);
bool inBarrel(float eta);
bool inEndCap(float eta);

void Declare_Histos();
double deltaR(double eta1, double phi1, double eta2, double phi2);
int Check_Files(unsigned Nfiles, vector<InputFile> & files);
void Load_Input_Files(string file_desc,vector<InputFile> & files,float lumiPb);
void Set_Branch_Addresses(TTree* WZtree);
void Fill_Histos(int index, float weight);
void saveHistos(TFile * fout, string dir);
void printSummary(ofstream & out, const string& dir, const float& Nthe_evt,
                  const float& Nexp_evt, float Nexp_evt_cut[]);
void Tabulate_Me(int Num_surv_cut[], int& cut_index,const float& weight,const int& evtnum);
void Get_Distributions(vector<InputFile>& files,TFile *fout, 
                       string dir, ofstream & out);
void UseSample(string dir, vector<InputFile> & files, float lumiPb,
               TFile * fout, ofstream & out);
void ExecuteZJets();

///
//methods for the cuts
bool PassTriggersCut();
bool PassValidWandZCut();
bool PassNumberOfZsCut();
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
bool PassZmassCut();

bool PassElecEtaCut(int idx);
bool PassElecPtCut(int idx,int parent);
bool PassElecEtCut(int idx,int parent);
//bool PassElecMatchedCut(int idx,int parent,bool inEC);
//bool PassElecNMissHitsCut(int idx,int parent,bool inEC);
//bool PassElecDistCut(int idx,int parent,bool inEC);
//bool PassElecdCotThetaCut(int idx,int parent,bool inEC);
bool PassElecTrkRelIsoCut(int idx,bool inEC);
bool PassElecECalRelIsoCut(int idx,bool inEC);
bool PassElecHCalRelIsoCut(int idx,bool inEC);
bool PassElecSigmaEtaEtaCut(int idx,bool inEC);
bool PassElecDeltaPhiCut(int idx,bool inEC);
bool PassElecDeltaEtaCut(int idx,bool inEC);
bool PassElecHOverECut(int idx,bool inEC);

bool PassMuonTypeCut(int idx);
bool PassMuonNpixhitCut(int idx);
bool PassMuonNtrkhitCut(int idx);
bool PassMuonNormChi2Cut(int idx);
bool PassMuonHitsUsedCut(int idx);
bool PassMuonStationsCut(int idx);
bool PassMuonEtaCut(int idx);
bool PassMuonPtCut(int idx,int parent);
bool PassMuonCombRelIsoCut(int idx);
bool PassMuonDxyCut(int idx);

float Calc_Ht();
float Calc_GenWZInvMass();
float Calc_MuonRelIso(int idx);
bool PassTightCut(int idx);


#endif//#define _ExecuteZJets_h_
