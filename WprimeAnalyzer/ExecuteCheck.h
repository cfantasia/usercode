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
const vector<string> Cut(Cut_Name, Cut_Name + sizeof(Cut_Name) / sizeof(string) );
const int NCuts = sizeof(Cut_Name) / sizeof(string);//works

TH1F * hWZInvMass[NCuts];
TH1F * hWZTransMass[NCuts];
TH1F * hHt[NCuts];
TH1F * hWpt[NCuts];
TH1F * hZpt[NCuts];
TH1F * hGenWZInvMass[NCuts];
TH1F * hMET[NCuts];
TH1F * hMETDiff[NCuts];
TH1F * hGenDP[NCuts];
TH1F * hRecoDP[NCuts];
TH1F * hDiffDP[NCuts];
TH1F * hZmass[NCuts];
TH1F * hZeemass[NCuts];
TH1F * hZmumumass[NCuts];
TH1F * hGenZmass[NCuts];
TH1F * hGenWTransmass[NCuts];
TH1F * hGenWTransmassDiff[NCuts];
TH1F * hWmass[NCuts];
TH1F * hWTransmass[NCuts];
TH1F * hWenuTransmass[NCuts];
TH1F * hWmunuTransmass[NCuts];

TH1F * hElecPtDiff[NCuts];
TH1F * hMuonPtDiff[NCuts];

TH1F * hElecPt[NCuts];
TH1F * hElecEt[NCuts];
TH1F * hElecdEta[NCuts];
TH1F * hElecdPhi[NCuts];
TH1F * hElecSigmann[NCuts];
TH1F * hElecEP[NCuts];
TH1F * hElecHE[NCuts];
TH1F * hElecTrkRelIso[NCuts];
TH1F * hElecECalRelIso[NCuts];
TH1F * hElecHCalRelIso[NCuts];

TH1F * hMuonPt[NCuts];
TH1F * hMuonDxy[NCuts];
TH1F * hMuonNormChi2[NCuts];
TH1F * hMuonNPix[NCuts];
TH1F * hMuonNTrk[NCuts];
TH1F * hMuonRelIso[NCuts];
TH1F * hMuonStation[NCuts];
TH1F * hMuonSip[NCuts];

TH1F * hWDpt[NCuts];
TH1F * hWDphi[NCuts];
TH1F * hWDeta[NCuts];
TH1F * hWDr[NCuts];

bool Calc_RecoCompare();
void ExecuteCheck();

#endif//#define _ExecuteCheck_h_
