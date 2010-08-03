// ++++++++++++++++++++ Consts
//const float NOCUT = numeric_limits<float>::max();
//just make a big number for now
const float NOCUT = 9e9;//99999999;

const int PDGMUON = 13;
const int PDGELEC = 11;
const int PDGW = 24;
const int PDGZ = 23;
const int PDGWPRIME = 34;

const float PDGZMASS = 91.1876; //GeV

// +++++++++++++++++++General Cut values
const int maxNumZs = 1;
const int minNumLeptons = 3;
const float minMET = 50;

// +++++++++++++++++++Ht Cuts
const float minHt = 160;
const float minHtMet = 0;

// +++++++++++++++++++W Cuts
const float minWpt = 90;

// +++++++++++++++++++Z Cuts
const float minZpt = 90;
const float minZmass = 60;
const float maxZmass = 120;

// +++++++++++++++++++Electron General Cuts
const float maxElecEtaBarrel = 1.4442;
const float minElecEtaEndcap = 1.56;
const float maxElecEta = 2.5;

const float minElecEt = 10;
const float maxElecSigmaEtaEta[] = {0.02 ,0.04 }; //{0.01 ,0.03 };
const float maxElecDeltaPhiIn [] = {0.08 ,0.07 }; //{0.08 ,0.7  };
const float maxElecDeltaEtaIn [] = {0.010,0.02 }; //{0.007,0.01 };
const float maxElecHOverE     [] = {0.14 ,0.12 }; //{0.15 ,0.07 };

// +++++++++++++++++++Muon General Cuts
const int cutMuonIsGlobal = true;
const float maxMuonEta = 2.5;
const float minMuonPt = 10.;
const float maxMuonDxy = 0.1;
const float maxMuonNormChi2 = 5.;
const int minMuonNPixHit = 1;
const int minMuonNTrkHit = 12;
const int minMuonStations = 1;
const int minMuonHitsUsed = 4;

// +++++++++++++++++++Wmunu
//The muon must be identified as both global muon and tracker muon 
const int cutWmunuIsGlobal = true;
const int cutWmunuIsTracker= true;

//|eta(muon)|<2.1 This cut is required in order to match muon trigger requirements. It could be increased to 2.4 if the L1 single-muon trigger continues to be un-prescaled at high rapidity (but this would probably imply changing the HLT_Mu9 requirement and should not happen when the instantaneous luminosity starts to increase significantly).
//const float maxWmunuEta = 2.5;
 
//Muon pt > 25 GeV 
//This can be relaxed to 20 GeV, but this decision will depend on the physics interest. The baseline pt cut significantly reduces the QCD background affecting minimally the signal efficiency. 
const float minWmunuMuonPt = 20.;
  
//Relative combined isolation = (sumPt + emEt + hcalEt)/ptmu < 0.15 in a deltaR < 0.3 cone 
//Default PFlow isolation in a deltaR < 0.3 cone is also an equally valid option, provided that there is perfect matching between muons selected with the muonId criteria described in this page and muons identified by the PFlow muon algorithms (which seems to be the case today). 
const float maxWmunuCombRelIso = 0.15;

// +++++++++++++++++++Zmumu
  
/* https://twiki.cern.ch/twiki/bin/view/CMS/VbtfZMuMuBaselineSelection 
  
  * Event selection 
  */  
//we require the presence of a muon trigger. Muon trigger pT threshold has to be defined according to run conditions.
//??Work
  
/* Muon ID criteria 
   we require the presence of two global muons Detailed quality cuts are under study. Preliminary cut are: 
*/
const int cutZmumuIsGlobal = true;//MUONFITGLOBAL;

//  Muon kinematics 
//selection muon must have opposite charge pT > 20 GeV/c for both muons one muon with
const float minZmumuMuonPt = 20.;
 
//|eta| < 2.1, the other with |eta|<2.4 
//const float maxZmumuEta = 2.5;

// +++++++++++++++++++Wenu

//Electron kinematics 
//electron supercluster ET > 25 GeV 
const float minWenuEt = 20;
const float maxWenuTrkRelIso[]    = {0.30 ,0.20}; //1.70, 1.01
const float maxWenuECalRelIso[]   = {0.20 ,0.15}; //0.49, 0.24
const float maxWenuHCalRelIso[]   = {0.15 ,0.12}; //0.21, 0.12
/*
const float maxWenuTrkRelIso[]    = {0.09 ,0.04};
const float maxWenuECalRelIso[]   = {0.07 ,0.05};
const float maxWenuHCalRelIso[]   = {0.10 ,0.025};
*/

// +++++++++++++++++++Zee
//Electron kinematics 
//electron supercluster ET > 20 GeV 
const float minZeeEt = 20;

/////////////////////////////////
// +++++++++++++++++++ Older Cuts
/////////////////////////////////

const float maxWmunuMuonSip = 8.; //Sip
const float maxWmunuECalTrkRelIso = 0.1;

const float maxEtaBarrel = 1.479;
const float minEtaEndcap = 1.55;

const float minZeePt = 15;
const float minWenuPt = 20;

const float maxWenuCombRelIso[]  = {NOCUT,NOCUT};  
const float minWenuEOverP[]      = {0.760, 0.680};
const float maxWenuCalRelIso[]   = {0.100, 0.160};


// Cut arrays are Zee for {barrel, endcap}
const float minZeeEOverP[]      = {0.000, 0.000};
const float maxZeeCalRelIso[]   = {NOCUT, NOCUT};

