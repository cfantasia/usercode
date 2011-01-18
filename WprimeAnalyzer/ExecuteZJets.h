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

#include "ExecuteCuts.C"
#include "ExecuteFunctions.C"

///My calculated qualities//////////////////
bool TT;
bool TF;
/////////////////////////

// +++++++++++++++++++ Histogram Definitions
//matches the number of cuts
const string Cut_Name[] = {"NoCuts", "HLT", "ValidZ", "NumZs", 
                           "ElecEta","ElecEt", 
                           "ElecSigmaEtaEta", "ElecDPhi",
                           "ElecDEta", "ElecHOverE",
                           "MuonType", "MuonEta",
                           "MuonPt", "MuonDxy",
                           "MuonNormChi2", "MuonNPix",
                           "MuonNTrk", "MuonStation",
                           "MuonHitsUsed",
                           "AllCuts"};
const vector<string> Cut(Cut_Name, Cut_Name + sizeof(Cut_Name) / sizeof(string) );
const int NCuts = sizeof(Cut_Name) / sizeof(string);//works

TH1F * hWZInvMass[NCuts];
TH1F * hWZTransMass[NCuts];
TH1F * hHt[NCuts];
TH1F * hWpt[NCuts];
TH1F * hZpt[NCuts];
TH1F * hMET[NCuts];
TH1F * hMETDiff[NCuts];
TH1F * hZmass[NCuts];
TH1F * hZeemass[NCuts];
TH1F * hZmumumass[NCuts];
TH1F * hWTransmass[NCuts];
TH1F * hWenuTransmass[NCuts];
TH1F * hWmunuTransmass[NCuts];

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

TH1F * hZeemassTT[NCuts];
TH1F * hZeemassTF[NCuts];
TH1F * hZmumumassTT[NCuts];
TH1F * hZmumumassTF[NCuts];

// +++++++++++++++++++ Declare the methods that we use:
void ExecuteZJets();

#endif//#define _ExecuteZJets_h_
