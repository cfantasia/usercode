//---------------------------------------------
// Author: Edgar Carrera
// 2010-01-13
// This macro will be used for analyzing
// Wprime -> WZ -> lllnu events
// It works on an root-uple of events with
// variables created by the "official" CMS WZ code
//---------------------------------------------
#ifndef _ExecuteCheck_h_
#define _ExecuteCheck_h_

#include <ExecuteFunctions.C>
#include <ExecuteCheck.C>

// +++++++++++++++++++Variables to store Branch Addresses:

///My calculated qualities//////////////////
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
TH1F * hGenWZInvMass[Num_histo_sets];
TH1F * hMET[Num_histo_sets];
TH1F * hMETDiff[Num_histo_sets];
TH1F * hGenDP[Num_histo_sets];
TH1F * hRecoDP[Num_histo_sets];
TH1F * hDiffDP[Num_histo_sets];
TH1F * hZmass[Num_histo_sets];
TH1F * hZeemass[Num_histo_sets];
TH1F * hZmumumass[Num_histo_sets];
TH1F * hGenZmass[Num_histo_sets];
TH1F * hGenWTransmass[Num_histo_sets];
TH1F * hGenWTransmassDiff[Num_histo_sets];
TH1F * hWmass[Num_histo_sets];
TH1F * hWTransmass[Num_histo_sets];
TH1F * hWenuTransmass[Num_histo_sets];
TH1F * hWmunuTransmass[Num_histo_sets];

TH1F * hElecPtDiff[Num_histo_sets];
TH1F * hMuonPtDiff[Num_histo_sets];

TH1F * hElecPt[Num_histo_sets];
TH1F * hElecEt[Num_histo_sets];
TH1F * hElecdEta[Num_histo_sets];
TH1F * hElecdPhi[Num_histo_sets];
TH1F * hElecSigmann[Num_histo_sets];
TH1F * hElecEP[Num_histo_sets];
TH1F * hElecHE[Num_histo_sets];
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

TH1F * hWDpt[Num_histo_sets];
TH1F * hWDphi[Num_histo_sets];
TH1F * hWDeta[Num_histo_sets];
TH1F * hWDr[Num_histo_sets];

bool Calc_RecoCompare();
void ExecuteCheck();

#endif//#define _ExecuteCheck_h_
