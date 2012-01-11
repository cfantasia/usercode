#ifndef _WZAnalyzer_h_
#define _WZAnalyzer_h_

#include <vector>
#include <string>
#include <map>

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"

#include <fstream>
#include <iostream>
#include <iomanip>

#include <TROOT.h>
#include <TH1F.h>
#include <TVector3.h>
#include <TFile.h>
#include <TSystem.h>

#include "PhysicsTools/SelectorUtils/interface/Selector.h"
#include "PhysicsTools/CandUtils/interface/AddFourMomenta.h"

#include "UserCode/CMGWPrimeGroup/interface/util.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"




class WZAnalyzer {
public:
  WZAnalyzer();                         // constructor; initialize the list to be empty
  WZAnalyzer(const edm::ParameterSet & cfg, int fileToRun);
  ~WZAnalyzer();


  //methods for stuff to be done for each sample
  void defineHistos(const TFileDirectory& dir);

//methods for modifiers

//methods for the cuts

//////////////////
/////Variables////
//////////////////

// +++++++++++++++++++General Cut values
  uint minNLeptons_;
  uint maxNumZs_;
  float minMET_;

// +++++++++++++++++++Ht Cuts
  float minHt_;

// +++++++++++++++++++W Cuts
  float minWtransMass_;
  float minWpt_;

// +++++++++++++++++++Z Cuts
  float minZmass_;
  float maxZmass_;
  float minZpt_;

  float minZl1Pt_;
  float minZl2Pt_;

  //Selectors
  ElectronSelector looseElectron_;
  ElectronSelector tightElectron_;
  pat::strbitset eLooseBitMask, eTightBitMask;

  MuonSelector looseMuon_;
  MuonSelector tightMuon_;
  pat::strbitset mLooseBitMask, mTightBitMask;

  //Handles
  PatElectronVH patElectronsH_;
  PatMuonVH patMuonsH_;
  METVH metH_;
  edm::Handle<std::vector<reco::Vertex> > verticesH_;

// +++++++++++++++++++ Histogram Definitions
  TH1F *hWZMass;
  TH1F *hWZ3e0muMass, *hWZ2e1muMass, *hWZ1e2muMass, *hWZ0e3muMass;

  TH1F *hHt;
  TH1F *hEvtType;

  TH1F *hZMass, *hZeeMass, *hZmmMass ;
  TH1F *hZpt, *hZeept, *hZmmpt;

  TH1F *hMET, *hMETee, *hMETmm, *hMETSig;

  TH1F *hWTransMass, *hWenuTransMass, *hWmnuTransMass;
  TH1F *hWpt, *hWenupt, *hWmnupt;

  TH1F *hElecPt, *hMuonPt;

  TH1F *hNLElec, *hNLMuon, *hNLLeps;
  
  TH1F *hNVtxs;

// Run the analysis
  void run();

// operations to be done when opening input file 
  void beginFile(std::vector<wprime::InputFile>::iterator fi);

// operations to be done for each event
  void eventLoop(edm::EventBase const & event);
  
// operations to be done when closing input file 
  void endFile(std::vector<wprime::InputFile>::iterator fi);

// operations to be done when finishing analysis
  void endAnalysis();

  //Input Tags
  edm::InputTag electronsLabel_;
  edm::InputTag muonsLabel_;
  edm::InputTag metLabel_;
  edm::InputTag vertexLabel_;
  edm::InputTag pileupLabel_;

  std::vector<wprime::InputFile> inputFiles_; 

  edm::Handle<std::vector< PileupSummaryInfo > > PupH_;

  fwlite::TFileService * fs;

  TH1F * hNumEvts;

  void setEventWeight(edm::EventBase const & event, std::vector<wprime::InputFile>::iterator fi);

  //print stuff if active
  bool debug_;
  // print out event # (set to <0 for percentage of events)
  int reportAfter_;
  // maximum # of events to process (set to <0 for processing all events)
  int maxEvents_;

  void getInputFiles(const Pset & cfg);

  void setLumiWeights(const std::string & MCFile, const std::string & DataFile,
                      const std::string & MCHist, const std::string & DataHist,
                      const float & puScale);
  edm::Lumi3DReWeighting LumiWeights3D_;
  float getPUWeight3D(const std::vector< PileupSummaryInfo > & PupInfo);

  float lumi_ipb_;

  float weight_;
};

#endif//#define _WZAnalyzer_h_
