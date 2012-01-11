#ifndef _util_h
#define _util_h

#include <vector>
#include <string>
#include <TVector3.h>

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/FWLite/interface/Handle.h"

#include "PhysicsTools/SelectorUtils/interface/Selector.h"

typedef unsigned int uint;
typedef std::vector<int> vint;
typedef std::vector<std::string> vstring;
typedef math::XYZPoint Point;
typedef math::XYZTLorentzVector LorentzVector;
typedef edm::ParameterSet Pset;
typedef std::vector<Pset> VPset;

typedef std::vector<pat::Electron> PatElectronV;
typedef std::vector<pat::Muon    > PatMuonV;

typedef std::vector<pat::MET     > METV;
typedef std::vector<reco::Track  > TrackV;
typedef std::vector<edm::InputTag> VInputTag;
typedef std::vector<reco::Candidate> CandV;
typedef std::vector<reco::GenParticle> GenParticleV;

typedef edm::Handle<PatElectronV > PatElectronVH;
typedef edm::Handle<PatMuonV > PatMuonVH;
typedef edm::Handle<METV > METVH;


//////

namespace wprime{
  struct FilterEff{
    // # of (unweighted!) events surviving after each selection cut
    int Nsurv_evt_cut;
    // # of (weighted!) events surviving after each selection cut
    float Nsurv_evt_cut_w;
    // efficiency for each selection cut
    float eff;
    // efficiency uncertainty
    float deff;
    // absolute efficiency for all selection cuts
    float eff_abs;
    // absolute efficiency uncertainty
    float deff_abs;

    FilterEff(){Nsurv_evt_cut = 0; Nsurv_evt_cut_w = eff = deff = eff_abs = deff_abs = 0.0;}
  };

  // key: samplename, value: vector<FilterEff> (ie. statistics for selection steps)
  typedef std::vector<FilterEff> EffV;
  typedef std::map<std::string, EffV > SampleStat;

  static std::string INVALID = "INVALID";

  struct InputFile
  {
    float x_sect; // cross-section in pb
    int Nprod_evt;// unweighted # of events produced (should correspond to x_sect!)
    int Nact_evt; // unweighted # of events surviving pre-selection/skimming and
    // actually contained in input file
    float weight; // cross-section * integrated luminosity / (# of events produced)
    // Nact_evt * weight = Nexp_evt for given integrated luminosity
    std::string samplename;
    std::string subdir;
    std::vector<std::string> pathnames; // directory + subdir + filenames
    std::string description; // sample description
    float signalMass; // in <x>.<y> TeV for signal samples (e.g. 1.2), -1 otherwise (default)
    bool isSignal() const {return signalMass > 0;}
    bool runningOnData() const {return (samplename.find("data") != std::string::npos);}
    int splitInto;
    EffV results;
    //
    InputFile()
    {
      x_sect = signalMass = -1; Nprod_evt = Nact_evt = -1; weight = 0; splitInto = 1;
      samplename = description = INVALID;
      subdir = "";
    }
    void checkFile()
    {
      if(samplename.find("data") == std::string::npos){
        //Only require these if running on MC
        assert(x_sect > 0); 
        assert(Nprod_evt > 0); 
      }
      assert(weight > 0);
      assert(splitInto > 0);
      assert(pathnames.size()); 
      assert(description != INVALID); 
      assert(samplename != INVALID);
    }

  };

  const float MUON_MASS = 0.105658366;      // GeV
  const float ELECTRON_MASS = 0.000511;     // GeV
}

//// Global constants ////////////////////////////////////////////////////////

const float ZMASS = 91.188;
const float WMASS = 80.398;
const float VMASS = (ZMASS+WMASS)/2.;

const int PDG_ID_ELEC = 11;
const int PDG_ID_ELECNEU = 12;
const int PDG_ID_MUON = 13;
const int PDG_ID_MUONNEU = 14;

const int PDG_ID_W = 24;
const int PDG_ID_Z = 23;
const int PDG_ID_WPRIME = 34;

//////// Comparators (for sorting vectors) ///////////////////////////////////
struct closestToZMass {
  bool operator() (const reco::Candidate & a, const reco::Candidate & b) {
    return fabs(ZMASS - a.mass()) < fabs(ZMASS - b.mass());
  }
};

template<class C, class D>
struct highestPt {
  bool operator() (const C * a, const D * b) {
    return a->pt() > b->pt();
  }
  bool operator() (const C & a, const D & b) {
    return a.pt() > b.pt();
  }
};
struct highestPtLepton {
  bool operator() (const reco::CompositeCandidate a, 
                   const reco::CompositeCandidate b) {
    return a.daughter(0)->pt() > b.daughter(0)->pt();
  }
};


////Others Fns///////

template<class C, class D>
inline bool areIdentical(const C & p1, const D & p2)
{
  float tolerance = 0.0001;
  if (p1.pdgId() == p2.pdgId() &&
      fabs(p1.eta() - p2.eta()) < tolerance &&
      fabs(p1.phi() - p2.phi()) < tolerance &&
      fabs(p1.pt () - p2.pt ()) < 0.1*p1.pt())
    return true;
  return false;
}

template<class T1, class T2>
  bool Overlap(const T1 & p, const std::vector<T2>& vec, const float minDR=0.01, const size_t maxToCheck=0 ){
  uint max = maxToCheck == 0 ? vec.size() : min(vec.size(), maxToCheck);
  for(uint i=0; i<max; ++i){
    if(reco::deltaR(p, vec[i]) < minDR) return true;
  }
  return false;
}

template<class T1,class T2>
bool Match(const T1 & p1, const T2 & p2, float tolerance = 0.01){
  if (p1.pdgId() == p2.pdgId() &&
      fabs(p1.eta() - p2.eta()) < tolerance &&
      fabs(reco::deltaPhi(p1.phi(),p2.phi())) < tolerance
    )
    return true;
  return false;
}


//////// Selectors ///////////////////////////////////////////////////////////
/// Class derived from Selector that implements some convenience functions
template<class T>
class MinMaxSelector : public Selector<T> {
 public:
  bool cutOnMin(std::string param) {
    bool useMin = param.find("min") != std::string::npos;
    bool useMax = param.find("max") != std::string::npos;
    if (!useMin && !useMax) {
      std::cout << param << " has neither 'min' nor 'max' in its name!" << std::endl;
      exit(1);
    }
    return useMin;
  }
  template<class C>
    void loadFromPset(Pset params, std::string param, bool shouldset = true) {
    C defaultValue = 0;
    if (!this->cutOnMin(param))
      defaultValue = std::numeric_limits<C>::max();
    C val = params.getUntrackedParameter<C>(param, defaultValue);
    if(!params.exists(param)){
      shouldset = false;//If you don't list it, I'll ignore it
      std::cout<<" You didn't specify param "<<param<<", so it will be ignored\n";
    }
    this->push_back(param, val);
    this->set(param, shouldset);
  }
  template<class C>
    void setpassCut(std::string param, C value, pat::strbitset & ret) {
    bool useMin = this->cutOnMin(param);
    if (this->ignoreCut(param) || 
        ( useMin && value >= this->cut(param, C())) ||
        (!useMin && value <= this->cut(param, C())) )
      this->passCut(ret, param);
  }
};

/// Selector for electrons (either barrel or endcap) based on params
class ElectronSelectorBase : public MinMaxSelector<pat::Electron> {
public:
  ElectronSelectorBase() {}
  ElectronSelectorBase(Pset const params) {
    // set the last parameter to false to turn off the cut
    loadFromPset<double>(params, "minPt", true);
    loadFromPset<double>(params, "minConv", true);
    loadFromPset<double>(params, "maxSigmaIEtaIEta", true);
    loadFromPset<double>(params, "maxDeltaEta", true);
    loadFromPset<double>(params, "maxDeltaPhi", true);
    loadFromPset<double>(params, "maxCombRelIso", true);
    loadFromPset<int>(params, "maxMissingHits", true);
  }
  virtual bool operator()(const pat::Electron & p, pat::strbitset & ret) {
    ret.set(false);
    setpassCut("minPt", p.pt(), ret);
    if(ignoreCut("minConv") || 
       fabs(p.convDist()) >= cut("minConv", double()) || fabs(p.convDcot()) >= cut("minConv", double()))
      passCut(ret, "minConv");
    setpassCut("maxSigmaIEtaIEta", p.sigmaIetaIeta(), ret);
    setpassCut("maxDeltaEta", fabs(p.deltaEtaSuperClusterTrackAtVtx()), ret);
    setpassCut("maxDeltaPhi", fabs(p.deltaPhiSuperClusterTrackAtVtx()), ret);   
    setpassCut("maxCombRelIso",calcCombRelIso(p), ret);
    setpassCut("maxMissingHits", 
               p.gsfTrack()->trackerExpectedHitsInner().numberOfHits(), ret);
    setIgnored(ret);
    return (bool) ret;
  }

  float
    calcTrkIso(const pat::Electron& elec){
    return elec.dr03TkSumPt();
  }

  float
    calcECalIso(const pat::Electron& elec){
    return elec.isEB() ? 
      std::max(0., elec.dr03EcalRecHitSumEt() - 1.)
      : elec.dr03EcalRecHitSumEt();
  }
  
  float
    calcHCalIso(const pat::Electron& elec){
    return  elec.dr03HcalTowerSumEt();
  }
  
  float
    calcHCalIsoCor(const pat::Electron& elec){
    return elec.hadronicOverEm() * elec.energy() * fabs(sin(elec.superCluster()->position().theta()));
  }
  
  float
    calcAdjHCalIso(const pat::Electron& elec){
    return calcHCalIso(elec) + calcHCalIsoCor(elec);
  }
  
  float
    calcCombRelIso(const pat::Electron& elec){
    return (calcTrkIso(elec) + calcECalIso(elec) + calcAdjHCalIso(elec)) /
      elec.p4().Pt();
  }

};



/// A wrapper to handle the barrel/endcap split for electrons
class ElectronSelector {
 public:
  ElectronSelector() {}
  ElectronSelector(Pset pset, std::string selectorName) {
    Pset const params = pset.getParameter<Pset>(selectorName);
    barrelSelector_ = ElectronSelectorBase(params.getParameter<Pset>("barrel"));
    endcapSelector_ = ElectronSelectorBase(params.getParameter<Pset>("endcap"));
  }
  bool operator()(const pat::Electron & p, pat::strbitset & ret) {
    if     (p.isEB()) return barrelSelector_(p, ret);
    else if(p.isEE()) return endcapSelector_(p, ret);
    return false;
  }
  pat::strbitset getBitTemplate() { return barrelSelector_.getBitTemplate(); }
 private:
  ElectronSelectorBase barrelSelector_;
  ElectronSelectorBase endcapSelector_;
};



/// Selector for muons based on params
class MuonSelector : public MinMaxSelector<pat::Muon> {
public:
  MuonSelector() {}
  MuonSelector(Pset pset, std::string selectorName) {
    Pset const params = pset.getParameter<Pset>(selectorName);
    // set the last parameter to false to turn off the cut
    loadFromPset<double>(params, "minPt", true);
    loadFromPset<double>(params, "maxEta", true);
    loadFromPset<double>(params, "maxDxy", true);
    loadFromPset<double>(params, "maxIso", true);
    loadFromPset<double>(params, "maxIso03", true);
    loadFromPset<int>(params, "minIsGlobal", true);
    loadFromPset<int>(params, "minIsTracker", true);
    loadFromPset<int>(params, "minNMatches", true);
    loadFromPset<int>(params, "minNMatchedStations", true);
    loadFromPset<double>(params, "maxNormalizedChi2", true);
    loadFromPset<int>(params, "minNTrackerHits", true);
    loadFromPset<int>(params, "minNPixelHits", true);
    loadFromPset<int>(params, "minNMuonHits", true);
    loadFromPset<int>(params, "minNTrackerLayers", true);
    loadFromPset<double>(params, "minTrackerValidFrac", true);
  }
  virtual bool operator()(const pat::Muon & p, pat::strbitset & ret) {
    ret.set(false);
    setpassCut("minPt", p.pt(), ret);
    setpassCut("maxEta", fabs(p.eta()), ret);
    setpassCut("maxDxy", fabs(p.dB()), ret);
    setpassCut("maxIso", combRelIsolation(p), ret);
    setpassCut("maxIso03", combRelIsolation03(p), ret);
    setpassCut("minIsGlobal", p.isGlobalMuon(), ret);
    setpassCut("minIsTracker", p.isTrackerMuon(), ret);
    setpassCut("minNMatches", p.numberOfMatches(), ret);
    setpassCut("minNMatchedStations", p.numberOfMatchedStations(), ret);
    
    reco::TrackRef global = p.globalTrack();
    if(!global.isNull()){
      const reco::HitPattern& gtHP = global->hitPattern();
      setpassCut("maxNormalizedChi2", global->normalizedChi2(), ret);
      setpassCut("minNTrackerHits", gtHP.numberOfValidTrackerHits(), ret);
      setpassCut("minNPixelHits", gtHP.numberOfValidPixelHits(), ret);
      setpassCut("minNMuonHits", gtHP.numberOfValidMuonHits(), ret);
      setpassCut("minNTrackerLayers", gtHP.trackerLayersWithMeasurement(), ret);
      setpassCut("minTrackerValidFrac", global->validFraction(), ret);
    }
    setIgnored(ret);
    return (bool) ret;
  }

  inline float combRelIsolation(const pat::Muon & p) const
  {
    return ( p.ecalIso() + p.hcalIso() + p.trackIso() ) 
      / p.pt();
  }
  
  inline float combRelIsolation03(const pat::Muon & p) const{
    return (p.isolationR03().emEt + p.isolationR03().hadEt + p.isolationR03().sumPt)
      / p.pt();
  }

};


#endif // _util_h
