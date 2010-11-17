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

#include <ExecuteFunctions.C>
#include <ExecuteCuts.C>

///My calculated qualities//////////////////
bool TT;
bool TF;
/////////////////////////

// +++++++++++++++++++ Histogram Definitions
const int Num_histo_sets = 20; //matches the number of cuts
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

// +++++++++++++++++++ Declare the methods that we use:
void ExecuteZJets();

#endif//#define _ExecuteZJets_h_
