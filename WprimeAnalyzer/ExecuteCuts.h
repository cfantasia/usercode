#ifndef _ExecuteCuts_h_
#define _ExecuteCuts_h_

// ++++++++++++++++++++ Consts
const float NOCUT = 9e9;

const float PDGZMASS = 91.1876; //GeV

// +++++++++++++++++++General Cut values
const int maxNumZs = 1;
const int minNumLeptons = 3;
const float minMET = 30;

// +++++++++++++++++++Ht Cuts
const float minHt = 190;//150 for TC300; 190 for W'400
const float minHtMet = 0; //Not Used

// +++++++++++++++++++W Cuts
const float minWtransMass = 0;//Cory: Removed cut
const float minWpt = 110;//90 for TC300; 110 for W'400

const float minWmunuMuonPt = 20.;
const float maxWmunuCombRelIso = 0.15;

const float minWenuEt = 20.;
const float maxWenuTrkRelIso[]    = {0.30 ,0.20};
const float maxWenuECalRelIso[]   = {0.20 ,0.15};
const float maxWenuHCalRelIso[]   = {0.15 ,0.12};

// +++++++++++++++++++Z Cuts
const float minZpt = 110;//90 for TC300; 110 for W'400
const float minZmass = 60;
const float maxZmass = 120;

const float minZmumuMuonPt = 20.;
const float minZeeEt = 20;

// +++++++++++++++++++Electron General Cuts
const float maxElecEtaBarrel = 1.4442;
const float minElecEtaEndcap = 1.56;
const float maxElecEta = 2.5;
//VBTF Recommended Cuts
const float minElecEt = 10;
const float maxElecSigmaEtaEta[] = {0.01 ,0.03 };
const float maxElecDeltaPhiIn [] = {0.08 ,0.7  };
const float maxElecDeltaEtaIn [] = {0.007,0.01 };
const float maxElecHOverE     [] = {0.15 ,0.07 };

// +++++++++++++++++++Muon General Cuts
const int cutMuonIsGlobal = true;
const float maxMuonEta = 2.5;
const float minMuonPt = 10.;
//VBTF Recommended Cuts
const float maxMuonDxy = 0.2;
const float maxMuonNormChi2 = 10.;
const int minMuonNPixHit = 0;
const int minMuonNTrkHit = 10;
const int minMuonStations = 1;
const int minMuonHitsUsed = 0;

//methods for the cuts
bool PassTriggersCut();
bool PassMuonTriggerCut();
bool PassElecTriggerCut();
bool PassValidWandZCut();
bool PassValidWZCandCut();
bool PassNumberOfZsCut();
bool PassWptCut();
bool PassZptCut();
bool PassHtCut();
bool PassHtMetCut();
bool PassMETCut();

bool PassZmassCut();
bool PassZLepPtCut();
bool PassZeePtCut();
bool PassZmumuPtCut();

bool PassWtransMassCut();
bool PassWLepPtCut();
bool PassWLepIsoCut();
bool PassWenuIsoCut();
bool PassWmunuIsoCut();

bool PassElecEtaCut(int idx);
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
float Calc_HtMET();
float Calc_ElecRelTrkIso(int idx);
float Calc_ElecRelECalIso(int idx);
float Calc_ElecRelHCalIso(int idx);
float Calc_MuonNormChi2(int idx);
float Calc_MuonRelIso(int idx);
float Calc_GenWZInvMass();

bool inBarrel(float eta);
bool inEndCap(float eta);

#endif//#define _ExecuteCuts_h_
