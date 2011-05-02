#ifndef _WZTree_h_
#define _WZTree_h_

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <limits>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "InputFile.h"

class WZTree {
public:
  WZTree();                         // constructor; initialize the list to be empty
  ~WZTree();

  void Set_Branch_Addresses(TTree* WZtree);
  std::string convertIntToStr(int number);
  std::string convertFloatToStr(float number);

//private:
  int           eventID;
  int           runNumber;
  int           lumiBlock;

  int           W_flavor;
  int           Z_flavor;
  float         W_pt;
  float         Z_pt;
  float         Z_mass;
  float         W_transMass;
  float         W_phi;
  float         W_eta;
  int           numberOfZs;
  float         met_phi;
  float         met_et;
  float         pfMet_et;
  float         tcMet_et;
  float         WZ_invMassMinPz;
  float         W_neutrino_pzMinPz;
  float         W_neutrino_pzMaxPz;
  float         WZ_transMass;
  int           W_leptonIndex;
  int           Z_leptonIndex1;
  int           Z_leptonIndex2;

  std::vector<std::string> *TriggerHLTNames;
  std::vector<int> *TriggerHLTPrescales;
  std::vector<int> *TriggerHLTDecisions;

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

  float         genmet_et;
  float         genmet_phi;

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
};

#endif//#define _WZTree_h_
