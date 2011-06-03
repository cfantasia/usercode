#ifndef _WZAnalysis_h_
#define _WZAnalysis_h_

#include "WZTree.h"

class WZAnalysis : public WZTree {
public:
  WZAnalysis();                         // constructor; initialize the list to be empty
  WZAnalysis(const std::vector<std::string>,
             const std::string &, const float&,
             const bool&);            // constructor
  ~WZAnalysis();

  void FillCutFns();
  void RecruitOrderedFile(std::vector<InputFile> & file, 
                          const std::string & filename,
                          const std::string & file_desc);
                          
  void RecruitOrderedFiles(std::vector<InputFile> & files, const int& Nfiles,
                           const int& filenum_low, const int& filenum_step,
                           const std::string& mask1, const std::string& mask2, 
                           const std::string& file_desc);
  void getEff(float & eff, float & deff, float Num, float Denom);
  double deltaEta(double eta1, double eta2);
  double deltaPhi(double phi1, double phi2);

  void Declare_Histos();
  void DeclareHistoSet(std::string n, std::string t, std::string xtitle,
                       int nbins, float min, float max,
                       std::vector<TH1F*>& h);
  double deltaR(double eta1, double phi1, double eta2, double phi2);
  int Check_Files(uint Nfiles, std::vector<InputFile> & files);
  std::string FindInputFilename(std::string file_desc);
  bool Load_Input_Files(std::string file_desc,std::vector<InputFile> & files);


  void Fill_Histos(int index, float weight);
  void saveHistos(std::string dir);
  void deleteHistos();
  void printSummary(const std::string& dir, const float& Nthe_evt,
                    const float& Nexp_evt, std::vector<float>& Nexp_evt_cut);
  void Tabulate_Me(std::vector<int>& Num_surv_cut, int& cut_index,const float& weight);
  void Get_Distributions(std::string dir, std::vector<InputFile>& files);
  void UseSample(std::string dir);
  void CalcEventVariables();
  bool PassCuts(std::vector<int>& Num_surv_cut, const float& weight);

  void PrintEventToFile();
  void PrintEvent();
  void PrintEventFull();
  void PrintElectron(int idx, int parent);
  void PrintMuon(int idx, int parent);
  float CalcLeadPt(int type=0);

//methods for utilities
  void CheckStream(ofstream& stream, std::string s);

//methods for modifiers
  void SetCandEvtFile(std::string s);
  void SetLogFile(std::string s);
  void SetOutputFile(std::string s);

//methods for accessors
  float GetLumiPb();
  
//methods for the cuts
  bool PassNoCut();
  bool PassTriggersCut();
  bool PassValidWCut();
  bool PassValidZCut();
  bool PassValidWandZCut();
  bool PassValidWZCandCut();
  bool PassLeadLepPt();
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

  bool PassWZElecLooseCut();
  bool PassZElecLooseCut();
  bool PassWElecLooseCut();
  bool PassElecLooseCut(int& idx);
  bool PassElecLooseWPCut(int& idx);
  bool PassElecLooseCut(int& idx, int& inEC, int parent=0);
  bool PassElecEtaCut(int idx);
  bool PassElecEtCut(int idx,int parent=0);
  bool PassElecTrkRelIsoCut(int idx,bool inEC);
  bool PassElecECalRelIsoCut(int idx,bool inEC);
  bool PassElecHCalRelIsoCut(int idx,bool inEC);
  bool PassElecWPRelIsoCut(int idx);
  bool PassElecSigmaEtaEtaCut(int idx,bool inEC);
  bool PassElecDeltaPhiCut(int idx,bool inEC);
  bool PassElecDeltaEtaCut(int idx,bool inEC);
  bool PassElecHOverECut(int idx,bool inEC);

  bool PassWZMuonLooseCut();
  bool PassZMuonLooseCut();
  bool PassWMuonLooseCut();
  bool PassMuonLooseCut(int& idx, int parent=0);
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


// +++++++++++++++++++useful constants
  bool debugme;//print stuff if active
  int PDGMUON;
  int PDGELEC;
  int PDGW;
  int PDGZ;
  int PDGWPRIME;

  float PDGZMASS;
  float W_mass;

  double PI;
  double TWOPI;
  float NOCUT;

// +++++++++++++++++++
//value of lumi to be used in the analysis
//the weights will scale accordingly.
  float lumiPb;
  
// +++++++++++++++++++location of data files and samples info
  std::string top_level_dir;
  TFile* fout;
  ofstream outCandEvt;
  ofstream outLogFile;

///My calculated qualities//////////////////
  float Ht;
  float Q;
  float LeadPt;
  float LeadElecPt;
  float LeadMuonPt;
  bool TT, TF;

// +++++++++++++++++++General Cut values
  int maxNumZs;
  int minNumLeptons;
  float minLepPt; 
  float minMET;

// +++++++++++++++++++Ht Cuts
  float minHt;
  float minHtMet;

// +++++++++++++++++++W Cuts
  float minWtransMass;
  float minWpt;

  float minWmunuMuonPt;
  float maxWmunuCombRelIso;

  float minWenuEt;
  int   cutWenuWPRelIsoMask;
  float maxWenuTrkRelIso[2];
  float maxWenuECalRelIso[2];
  float maxWenuHCalRelIso[2];

// +++++++++++++++++++Z Cuts
  float minZpt;
  float minZmass;
  float maxZmass;

  float minZmumuMuonPt;
  float minZeeEt;

// +++++++++++++++++++Electron General Cuts
  float maxElecEtaBarrel;
  float minElecEtaEndcap;
  float maxElecEta;
//VBTF Recommended Cuts
  float minElecEt;
  int cutElecWPLooseMask;
  float maxElecSigmaEtaEta[2];
  float maxElecDeltaPhiIn [2];
  float maxElecDeltaEtaIn [2];
  float maxElecHOverE     [2];

// +++++++++++++++++++Muon General Cuts
  int cutMuonIsGlobal;
  float maxMuonEta;
  float minMuonPt;
//VBTF Recommended Cuts
  float maxMuonDxy;
  float maxMuonNormChi2;
  int minMuonNPixHit;
  int minMuonNTrkHit;
  int minMuonStations;
  int minMuonHitsUsed;


// +++++++++++++++++++ Histogram Definitions
  std::vector<TH1F*> listOfHists;
  TH1F * hEffRel;
  TH1F * hEffAbs;
  TH1F * hNumEvts;
  TH1F * hLumiPb;

  std::vector<TH1F*> hEvtType;

  std::vector<TH1F*> hWZInvMass     ;
  std::vector<TH1F*> hWZ3e0muInvMass;
  std::vector<TH1F*> hWZ2e1muInvMass;
  std::vector<TH1F*> hWZ1e2muInvMass;
  std::vector<TH1F*> hWZ0e3muInvMass;

  std::vector<TH1F*> hWZTransMass;
  std::vector<TH1F*> hHt;
  std::vector<TH1F*> hWpt;
  std::vector<TH1F*> hZpt;
  std::vector<TH1F*> hMET;

  std::vector<TH1F*> hZMass     ;
  std::vector<TH1F*> hZeeMass   ;
  std::vector<TH1F*> hZmumuMass ;
  std::vector<TH1F*> hZ3e0muMass;
  std::vector<TH1F*> hZ2e1muMass;
  std::vector<TH1F*> hZ1e2muMass;
  std::vector<TH1F*> hZ0e3muMass;
  std::vector<TH1F*> hZeeMassTT;
  std::vector<TH1F*> hZeeMassTF;
  std::vector<TH1F*> hZmumuMassTT ;
  std::vector<TH1F*> hZmumuMassTF ;

  std::vector<TH1F*> hWTransMass     ;
  std::vector<TH1F*> hWenuTransMass  ;
  std::vector<TH1F*> hWmunuTransMass ;
  std::vector<TH1F*> hW3e0muTransMass;
  std::vector<TH1F*> hW2e1muTransMass;
  std::vector<TH1F*> hW1e2muTransMass;
  std::vector<TH1F*> hW0e3muTransMass;

  std::vector<TH1F*> hQ;

  std::vector<TH1F*> hLeadPt;
  std::vector<TH1F*> hLeadElecPt;
  std::vector<TH1F*> hLeadMuonPt;

  std::vector<TH1F*> hElecPt;
  std::vector<TH1F*> hElecEt;
  std::vector<TH1F*> hElecdEta;
  std::vector<TH1F*> hElecdPhi;
  std::vector<TH1F*> hElecSigmann;
  std::vector<TH1F*> hElecEP;
  std::vector<TH1F*> hElecHE;
  std::vector<TH1F*> hElecTrkRelIso;
  std::vector<TH1F*> hElecECalRelIso;
  std::vector<TH1F*> hElecHCalRelIso;

  std::vector<TH1F*> hMuonPt;
  std::vector<TH1F*> hMuonDxy;
  std::vector<TH1F*> hMuonNormChi2;
  std::vector<TH1F*> hMuonNPix;
  std::vector<TH1F*> hMuonNTrk;
  std::vector<TH1F*> hMuonRelIso;
  std::vector<TH1F*> hMuonStation;
  std::vector<TH1F*> hMuonSip;

//Cuts
  
  int NCuts;
  std::vector<std::string> Cuts;
  typedef bool (WZAnalysis::*CutFnPtr)(); 
#ifndef __CINT__
  std::map<std::string, CutFnPtr> mFnPtrs;
  std::vector<CutFnPtr> CutFns;
#endif
};

#endif//#define _WZAnalysis_h_
