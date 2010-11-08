#ifndef _ExecuteCuts_h_
#define _ExecuteCuts_h_

#include "ExecuteFunctions.h"

//methods for the cuts
bool PassTriggersCut();
bool PassValidWandZCut();
bool PassNumberOfZsCut();
bool PassWptCut();
bool PassZptCut();
bool PassHtCut();
bool PassHtMetCut();
bool PassMETCut();

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

bool PassTightCut(int idx, int flavor);

float Calc_Ht();
float Calc_MuonRelIso(int idx);

#endif//#define _ExecuteCuts_h_
