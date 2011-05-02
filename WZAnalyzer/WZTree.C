#include "WZTree.h"
using namespace std;
WZTree::WZTree(){
  gROOT->ProcessLine("#include <vector>");

  TriggerHLTNames = NULL;
  TriggerHLTPrescales = NULL;
  TriggerHLTDecisions = NULL;

  electron_pdgId = NULL;
  electron_mass = NULL;
  electron_phi = NULL;
  electron_eta = NULL;
  electron_ScEta = NULL;
  electron_pt = NULL;
  electron_energy = NULL;
  electron_px = NULL;
  electron_py = NULL;
  electron_pz = NULL;
  electron_ScEt = NULL;
  electron_trackIso = NULL;
  electron_ecaloIso = NULL;
  electron_hcaloIso = NULL;
  electron_deltaEtaIn = NULL;
  electron_deltaPhiIn = NULL;
  electron_eOverP = NULL;
  electron_hOverE = NULL;
  electron_sigmaEtaEta = NULL;

  electron_simpleEleId60relIso = NULL;
  electron_simpleEleId70relIso = NULL;
  electron_simpleEleId80relIso = NULL;
  electron_simpleEleId85relIso = NULL;
  electron_simpleEleId90relIso = NULL;
  electron_simpleEleId95relIso = NULL;

  muon_pdgId = NULL;
  muon_energy = NULL;
  muon_eta = NULL;
  muon_phi = NULL;
  muon_pt = NULL;
  muon_px = NULL;
  muon_py = NULL;
  muon_pz = NULL;
  muon_innerD0 = NULL;
  muon_innerD0Error = NULL;
  muon_trackIso = NULL;
  muon_caloIso = NULL;
  muon_relIso = NULL;
  muon_fitType = NULL;
  muon_isGlobal = NULL;    
  muon_isTracker = NULL;    
  muon_numGlobalMatches = NULL;    
  muon_numValidMuonHits = NULL;    
  muon_globalNpixelHits = NULL;
  muon_globalNtrackerHits = NULL;
  muon_globalNstripHits = NULL;
  muon_globalChi2 = NULL;
  muon_globalNdof = NULL;
  muon_globalD0 = NULL;
  muon_globalD0Error = NULL;

  genMother_pdgId = NULL;
  genParticle_pdgId = NULL;

  genMother_energy = NULL;
  genMother_et = NULL;
  genMother_eta = NULL;
  genMother_mass = NULL;
  genMother_phi = NULL;
  genMother_pt = NULL;
  genMother_px = NULL;
  genMother_py = NULL;
  genMother_pz = NULL;
  genParticle_energy = NULL;
  genParticle_et = NULL;
  genParticle_eta = NULL;
  genParticle_mass = NULL;
  genParticle_phi = NULL;
  genParticle_pt = NULL;
  genParticle_px = NULL;
  genParticle_py = NULL;
  genParticle_pz = NULL;

  electronGenMother_pdgId = NULL;
  electronGenMother_energy = NULL;
  electronGenMother_px = NULL;
  electronGenMother_py = NULL;
  electronGenMother_pz = NULL;

  muonGenMother_pdgId = NULL;
  muonGenMother_energy = NULL;
  muonGenMother_px = NULL;
  muonGenMother_py = NULL;
  muonGenMother_pz = NULL;
}

WZTree::~WZTree(){
}

//-----------------------------------------------------------
void WZTree::Set_Branch_Addresses(TTree* WZtree)
{
//-----------------------------------------------------------
  WZtree->SetBranchAddress("runNumber", &runNumber);
  WZtree->SetBranchAddress("eventID", &eventID);
  WZtree->SetBranchAddress("lumiBlock", &lumiBlock);

  WZtree->SetBranchAddress("pfW_flavor",&W_flavor);
  WZtree->SetBranchAddress("Z_flavor",&Z_flavor);
  WZtree->SetBranchAddress("pfW_pt",&W_pt);
  WZtree->SetBranchAddress("Z_pt",&Z_pt);
  WZtree->SetBranchAddress("Z_mass",&Z_mass);
  WZtree->SetBranchAddress("pfW_transMass",&W_transMass);
  WZtree->SetBranchAddress("pfW_phi",&W_phi);
  WZtree->SetBranchAddress("pfW_eta",&W_eta);
  WZtree->SetBranchAddress("numberOfZs",&numberOfZs);
  WZtree->SetBranchAddress("met_phi",&met_phi);
  WZtree->SetBranchAddress("met_et",&met_et);
  WZtree->SetBranchAddress("pfMet_et",&pfMet_et);
  WZtree->SetBranchAddress("tcMet_et", &tcMet_et);
  WZtree->SetBranchAddress("pfWZ_invMassMinPz",&WZ_invMassMinPz);
  WZtree->SetBranchAddress("pfW_neutrino_pzMinPz",&W_neutrino_pzMinPz);
  WZtree->SetBranchAddress("pfW_neutrino_pzMaxPz",&W_neutrino_pzMaxPz);
  WZtree->SetBranchAddress("WZ_transMass",&WZ_transMass);
  WZtree->SetBranchAddress("pfW_leptonIndex",&W_leptonIndex);
  WZtree->SetBranchAddress("Z_leptonIndex1",&Z_leptonIndex1);
  WZtree->SetBranchAddress("Z_leptonIndex2",&Z_leptonIndex2);

  WZtree->SetBranchAddress("TriggerHLTNames", &TriggerHLTNames);
  WZtree->SetBranchAddress("TriggerHLTPrescales", &TriggerHLTPrescales);
  WZtree->SetBranchAddress("TriggerHLTDecisions", &TriggerHLTDecisions);

  WZtree->SetBranchAddress("electron_pdgId",&electron_pdgId);
  WZtree->SetBranchAddress("electron_mass",&electron_mass);
  WZtree->SetBranchAddress("electron_phi",&electron_phi);
  WZtree->SetBranchAddress("electron_eta",&electron_eta);
  WZtree->SetBranchAddress("electron_ScEta",&electron_ScEta);
  WZtree->SetBranchAddress("electron_pt",&electron_pt);
  WZtree->SetBranchAddress("electron_energy",&electron_energy);
  WZtree->SetBranchAddress("electron_px",&electron_px);
  WZtree->SetBranchAddress("electron_py",&electron_py);
  WZtree->SetBranchAddress("electron_pz",&electron_pz);
  WZtree->SetBranchAddress("electron_ScEt",&electron_ScEt);
  WZtree->SetBranchAddress("electron_trackIso", &electron_trackIso);
  WZtree->SetBranchAddress("electron_ecalIso", &electron_ecaloIso);
  WZtree->SetBranchAddress("electron_hcalIso", &electron_hcaloIso);
  WZtree->SetBranchAddress("electron_deltaEtaIn", &electron_deltaEtaIn);
  WZtree->SetBranchAddress("electron_deltaPhiIn", &electron_deltaPhiIn);
  WZtree->SetBranchAddress("electron_eOverP", &electron_eOverP);
  WZtree->SetBranchAddress("electron_hOverE", &electron_hOverE);
  WZtree->SetBranchAddress("electron_sigmaIEtaIEta", &electron_sigmaEtaEta);

  WZtree->SetBranchAddress("electron_simpleEleId60relIso", &electron_simpleEleId60relIso);
  WZtree->SetBranchAddress("electron_simpleEleId70relIso", &electron_simpleEleId70relIso);
  WZtree->SetBranchAddress("electron_simpleEleId80relIso", &electron_simpleEleId80relIso);
  WZtree->SetBranchAddress("electron_simpleEleId85relIso", &electron_simpleEleId85relIso);
  WZtree->SetBranchAddress("electron_simpleEleId90relIso", &electron_simpleEleId90relIso);
  WZtree->SetBranchAddress("electron_simpleEleId95relIso", &electron_simpleEleId95relIso);

  WZtree->SetBranchAddress("muon_pdgId",&muon_pdgId);
  WZtree->SetBranchAddress("muon_energy",&muon_energy);
  WZtree->SetBranchAddress("muon_eta",&muon_eta);
  WZtree->SetBranchAddress("muon_phi",&muon_phi);
  WZtree->SetBranchAddress("muon_pt",&muon_pt);
  WZtree->SetBranchAddress("muon_px",&muon_px);
  WZtree->SetBranchAddress("muon_py",&muon_py);
  WZtree->SetBranchAddress("muon_pz",&muon_pz);
  WZtree->SetBranchAddress("muon_innerD0",&muon_innerD0);
  WZtree->SetBranchAddress("muon_innerD0Error",&muon_innerD0Error);
  WZtree->SetBranchAddress("muon_trackIso",&muon_trackIso);
  WZtree->SetBranchAddress("muon_caloIso",&muon_caloIso); 
  WZtree->SetBranchAddress("muon_relIso",&muon_relIso); 
  WZtree->SetBranchAddress("muon_fitType",&muon_fitType);
  WZtree->SetBranchAddress("muon_isGlobal",&muon_isGlobal);    
  WZtree->SetBranchAddress("muon_isTracker",&muon_isTracker);    
  WZtree->SetBranchAddress("muon_numGlobalMatches",&muon_numGlobalMatches);    
  WZtree->SetBranchAddress("muon_numValidMuonHits",&muon_numValidMuonHits);    
  WZtree->SetBranchAddress("muon_numPixelHits",&muon_globalNpixelHits);
  WZtree->SetBranchAddress("muon_numTrackerHits",&muon_globalNtrackerHits);
  WZtree->SetBranchAddress("muon_numStripHits",&muon_globalNstripHits);
  WZtree->SetBranchAddress("muon_globalChi2",&muon_globalChi2);
  WZtree->SetBranchAddress("muon_globalNdof",&muon_globalNdof);
  WZtree->SetBranchAddress("muon_globalD0",&muon_globalD0);
  WZtree->SetBranchAddress("muon_globalD0Error",&muon_globalD0Error);
    
  WZtree->SetBranchAddress("metGen_et", &genmet_et);
  WZtree->SetBranchAddress("metGen_phi", &genmet_phi);

  WZtree->SetBranchAddress("genMother_pdgId", &genMother_pdgId);
  WZtree->SetBranchAddress("genParticle_pdgId", &genParticle_pdgId);

  WZtree->SetBranchAddress("genMother_energy", &genMother_energy);
  WZtree->SetBranchAddress("genMother_et", &genMother_et);
  WZtree->SetBranchAddress("genMother_eta", &genMother_eta);
  WZtree->SetBranchAddress("genMother_mass", &genMother_mass);
  WZtree->SetBranchAddress("genMother_phi", &genMother_phi);
  WZtree->SetBranchAddress("genMother_pt", &genMother_pt);
  WZtree->SetBranchAddress("genMother_px", &genMother_px);
  WZtree->SetBranchAddress("genMother_py", &genMother_py);
  WZtree->SetBranchAddress("genMother_pz", &genMother_pz);
  WZtree->SetBranchAddress("genParticle_energy", &genParticle_energy);
  WZtree->SetBranchAddress("genParticle_et", &genParticle_et);
  WZtree->SetBranchAddress("genParticle_eta", &genParticle_eta);
  WZtree->SetBranchAddress("genParticle_mass", &genParticle_mass);
  WZtree->SetBranchAddress("genParticle_phi", &genParticle_phi);
  WZtree->SetBranchAddress("genParticle_pt", &genParticle_pt);
  WZtree->SetBranchAddress("genParticle_px", &genParticle_px);
  WZtree->SetBranchAddress("genParticle_py", &genParticle_py);
  WZtree->SetBranchAddress("genParticle_pz", &genParticle_pz);

  WZtree->SetBranchAddress("electronGenMother_pdgId", &electronGenMother_pdgId);
  WZtree->SetBranchAddress("electronGenMother_energy", &electronGenMother_energy);
  WZtree->SetBranchAddress("electronGenMother_px", &electronGenMother_px);
  WZtree->SetBranchAddress("electronGenMother_py", &electronGenMother_py);
  WZtree->SetBranchAddress("electronGenMother_pz", &electronGenMother_pz);
    
  WZtree->SetBranchAddress("muonGenMother_pdgId", &muonGenMother_pdgId);
  WZtree->SetBranchAddress("muonGenMother_energy", &muonGenMother_energy);
  WZtree->SetBranchAddress("muonGenMother_px", &muonGenMother_px);
  WZtree->SetBranchAddress("muonGenMother_py", &muonGenMother_py);
  WZtree->SetBranchAddress("muonGenMother_pz", &muonGenMother_pz);
}//Set_Branch_Addresses


//--------------------------------------------------------------
string WZTree::convertIntToStr(int number)
{
//--------------------------------------------------------------
  stringstream ss;
  ss << number;
  return ss.str();
}

//--------------------------------------------------------------
string WZTree::convertFloatToStr(float number)
{
//--------------------------------------------------------------
  stringstream ss;
  ss << number;
  return ss.str();
}

