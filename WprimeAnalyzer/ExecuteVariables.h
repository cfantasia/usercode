#ifndef _ExecuteVariables_h_
#define _ExecuteVariables_h_

#include <vector>
#include "TROOT.h"
#include <math.h>

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

std::vector<int  >   *electron_pdgId;
std::vector<float>   *electron_mass;
std::vector<float>   *electron_phi;
std::vector<float>   *electron_eta;
std::vector<float>   *electron_ScEta;
std::vector<float>   *electron_pt;
std::vector<float>   *electron_energy;
std::vector<float>   *electron_px;
std::vector<float>   *electron_py;
std::vector<float>   *electron_pz;
std::vector<float>   *electron_ScEt;
std::vector<float>   *electron_trackIso;
std::vector<float>   *electron_ecaloIso;
std::vector<float>   *electron_hcaloIso;
std::vector<float>   *electron_deltaEtaIn;
std::vector<float>   *electron_deltaPhiIn;
std::vector<float>   *electron_eOverP;
std::vector<float>   *electron_hOverE;
std::vector<float>   *electron_sigmaEtaEta;

std::vector<int>     *electron_simpleEleId60relIso;
std::vector<int>     *electron_simpleEleId70relIso;
std::vector<int>     *electron_simpleEleId80relIso;
std::vector<int>     *electron_simpleEleId85relIso;
std::vector<int>     *electron_simpleEleId90relIso;
std::vector<int>     *electron_simpleEleId95relIso;

std::vector<int  >   *muon_pdgId;
std::vector<float>   *muon_energy;
std::vector<float>   *muon_eta;
std::vector<float>   *muon_phi;
std::vector<float>   *muon_pt;
std::vector<float>   *muon_px;
std::vector<float>   *muon_py;
std::vector<float>   *muon_pz;
std::vector<float>   *muon_innerD0;
std::vector<float>   *muon_innerD0Error;
std::vector<float>   *muon_trackIso;
std::vector<float>   *muon_caloIso;
std::vector<float>   *muon_relIso;
std::vector<int  >   *muon_fitType;
std::vector<int  >   *muon_isGlobal;    
std::vector<int  >   *muon_isTracker;    
std::vector<int  >   *muon_numGlobalMatches;    
std::vector<int  >   *muon_numValidMuonHits;    
std::vector<int>     *muon_globalNpixelHits;
std::vector<int>     *muon_globalNtrackerHits;
std::vector<int>     *muon_globalNstripHits;
std::vector<float>   *muon_globalChi2;
std::vector<float>   *muon_globalNdof;
std::vector<float>   *muon_globalD0;
std::vector<float>   *muon_globalD0Error;

Float_t         genmet_et;
Float_t         genmet_phi;

std::vector<int>     *genMother_pdgId;
std::vector<int>     *genParticle_pdgId;

std::vector<float>   *genMother_energy;
std::vector<float>   *genMother_et;
std::vector<float>   *genMother_eta;
std::vector<float>   *genMother_mass;
std::vector<float>   *genMother_phi;
std::vector<float>   *genMother_pt;
std::vector<float>   *genMother_px;
std::vector<float>   *genMother_py;
std::vector<float>   *genMother_pz;
std::vector<float>   *genParticle_energy;
std::vector<float>   *genParticle_et;
std::vector<float>   *genParticle_eta;
std::vector<float>   *genParticle_mass;
std::vector<float>   *genParticle_phi;
std::vector<float>   *genParticle_pt;
std::vector<float>   *genParticle_px;
std::vector<float>   *genParticle_py;
std::vector<float>   *genParticle_pz;

std::vector<int>   *electronGenMother_pdgId;
std::vector<float>   *electronGenMother_energy;
std::vector<float>   *electronGenMother_px;
std::vector<float>   *electronGenMother_py;
std::vector<float>   *electronGenMother_pz;

std::vector<int>   *muonGenMother_pdgId;
std::vector<float>   *muonGenMother_energy;
std::vector<float>   *muonGenMother_px;
std::vector<float>   *muonGenMother_py;
std::vector<float>   *muonGenMother_pz;

// +++++++++++++++++++useful constants
const bool debugme = false; //print stuff if active
const int PDGMUON = 13;
const int PDGELEC = 11;
const int PDGW = 24;
const int PDGZ = 23;
const int PDGWPRIME = 34;

const double PI    = 2.0 * acos(0.);
const double TWOPI = 2.0 * PI;

// +++++++++++++++++++
//value of lumi to be used in the analysis
//the weights will scale accordingly.
const float lumiPb = 36.1;//1000;

// +++++++++++++++++++location of data files and samples info
const std::string top_level_dir = "/uscms_data/d2/fantasia/38X/";

///My calculated qualities//////////////////
float Ht;
float LeadPt;
float LeadElecPt;
float LeadMuonPt;

#endif//#define _ExecuteVariables_h_
