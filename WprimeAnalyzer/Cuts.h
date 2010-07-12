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

const int MUONFITGLOBAL = 1;
const int MUONFITTRACKER = 2;
const int MUONFITSTANDALONE = 3;

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

// +++++++++++++++++++Electron General Cuts
const float maxElecEtaBarrel = 1.4442;
const float minElecEtaEndcap = 1.56;
const float maxElecEta = 2.5;

const float minElecEt = 10;
const float maxElecTrkRelIso  [] = {1.70 ,1.01 }; //{0.15 ,0.08 };
const float maxElecECalRelIso [] = {0.49 ,0.24 }; //{2.00 ,0.06 };
const float maxElecHCalRelIso [] = {0.21 ,0.12 }; //{0.12 ,0.05 };
const float maxElecSigmaEtaEta[] = {0.02 ,0.04 }; //{0.01 ,0.03 };
const float maxElecDeltaPhiIn [] = {0.08 ,0.07 }; //{0.08 ,0.7  };
const float maxElecDeltaEtaIn [] = {0.010,0.02 }; //{0.007,0.01 };
const float maxElecHOverE     [] = {0.14 ,0.12 }; //{0.15 ,0.07 };

// +++++++++++++++++++Muon General Cuts
const int cutMuonIsGlobal = true;//MUONFITGLOBAL;
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

//Number of pixel hits > 0 
//const int minWmunuNpixhit = 0;

//Number of hits in the tracker > 10 
//const int minWmunuNtrkhit = 10;

//Transverse impact parameter of the muon with respect to the beam spot < 2 mm 
//const float maxWmunuDxy = 0.2;//It's in cm

//Chi2/ndof of the global muon fit < 10 A very loose cut. 
//const float maxWmunuNormChi2 = 10;

//Number of valid hits in the muon chambers used in the global muon fit > 0 
//This is a powerful but still loose cut to reject decays-in-flight and punch-through at high-pT. Together with the previous Chi2/ndof cut, this is what is known in the reco::Muon structure as GlobalMuonPromptTight bit requirement. We prefer not to not refer to strange names and explain clearly what is done without using CMSSW jargon. 
//const int minWmunuHitsUsed = 0;

//Number of muon stations > 1 
//This cut, particularly effective against punch-through and accidental matchings, is also consistent the the logic of the CMS muon trigger system, which also requires at least two stations in order to give a meaningful estimate of the transverse momentum. 
//const int minWmunuStations = 1;

//|eta(muon)|<2.1 This cut is required in order to match muon trigger requirements. It could be increased to 2.4 if the L1 single-muon trigger continues to be un-prescaled at high rapidity (but this would probably imply changing the HLT_Mu9 requirement and should not happen when the instantaneous luminosity starts to increase significantly).
const float maxWmunuEta = 2.1;

/* Trigger criteria 

HLT_Mu9 This should be sufficiently safe and should cover all the trigger scenarios planned for the first months of the LHC running in 2010. Note that these criteria imply by design of the CMS muon-trigger system the existence of a track in the muon chambers made out of at least two segments in different stations. Also, L3 criteria imply a good matching between the track measured in the muon chambers and the inner track built after regional reconstruction. So, as a matter of fact, trigger criteria can be considered as additional, unavoidable and rather effective conditions that improve the quality of a muon.
*/
//??Work
 
//Specific Wmunu selection criteria 
  
//Muon pt > 25 GeV 
//This can be relaxed to 20 GeV, but this decision will depend on the physics interest. The baseline pt cut significantly reduces the QCD background affecting minimally the signal efficiency. 
const float minWmunuMuonPt = 25.;
  
//Relative combined isolation = (sumPt + emEt + hcalEt)/ptmu < 0.15 in a deltaR < 0.3 cone 
//Default PFlow isolation in a deltaR < 0.3 cone is also an equally valid option, provided that there is perfect matching between muons selected with the muonId criteria described in this page and muons identified by the PFlow muon algorithms (which seems to be the case today). 
const float maxWmunuCombRelIso = 0.15;

//Missing transverse mass (MT) using PFlow MET > 50 GeV We are using PFlow MET for the time being. But track-corrected MET is an equally performant option. The mimimum MT cut that we may be considering if we want to increase the signal efficiency as much as possible (but at the cost of a higher QCD background) is MT>45 GeV or so. 
const float minWmunuMET = 50;

//Acoplanarity between muon and MET directions < 2.0 This cut is only necessary for accurate estimates of QCD backgrounds using ABCD or template methods, which presently rely on a good description of the QCD shapes after isolation inversion. In a fully MC-based analysis - the most likely scenario for low integrated luminosities - this cut can even be safely ignored. This requirement cuts signal only at the per-cent level in inclusive measurements, but should be avoided in high-pT W-boson studies.
//IGNORING THIS CUT TO SAVE HIGH PT Ws  

//We are rejecting events with two global muons satisfying: ptmu1>20 GeV, ptmu2>10 GeV, where ptmu1 is the highest muon pt and ptmu2 is the second highest muon pt in the event.
//IGNORING THIS CUT BC OF W+Z signal, maybe use if Z->ee  

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

//dxy < 0.2 global muon 
//const float maxZmumuDxy = 0.2;

//chi-squared fit < 10 
//const float maxZmumuNormChi2 = 10.; 

//at least one pixel hit 
//const int minZmumuNpixhit = 0;

//Number of hits in the tracker > 10 
//const int minZmumuNtrkhit = 10;

//at least one muon hit matched to the global fit
//const int minZmumuStations = 0;
  
// Muon Isolation 
//track isolation < 3 GeV/c, where track isolation is defined as the sum of pT of tracks within a cone of deltaR <0.3 around the muon direction 
const float maxZmumuTrkAbsIso = 3;

//  Muon kinematics 
//selection muon must have opposite charge pT > 20 GeV/c for both muons one muon with
const float minZmumuMuonPt = 20.;
 
//|eta| < 2.1, the other with |eta|<2.4 
const float maxZmumuEta1 = 2.4;
const float maxZmumuEta2 = 2.1;

//the di-muon invariant mass between 60<mass_mumu<120 is considered 
const float minZmumuMass = 60;
const float maxZmumuMass = 120;

// +++++++++++++++++++Wenu

//Trigger Requirement (TBD)
//Process events that pass unprescaled single electron or photon triggers. The type(s) of triggers and their ET thresholds will be defined according to run conditions. We start with HLT_Photon10_L1R seeded on L1_SingleEG5 . When HLT_Photon10_L1R is prescaled we move to HLT_Photon15_L1R seeded on L1_SingleEG5 . When HLT_Photon15_L1R is prescaled we move to HLT_Ele15_LW_L1R seeded on L1_SingleEG5. (N.B. currently both HLT_Photon15_L1R & HLT_Ele15_LW_L1R are seeded on L1_SingleEG8, but it is intended that this be changed ).
//??Work

//Electron kinematics 
//electron supercluster ET > 25 GeV 
const float minWenuEt = 25;

//electron in supercluster position in ECAL fiducial region ( |eta| < 2.5, 1.4442 < |eta| < 1.560 excluded) 
//Cory: SC ECAL is different than ECAL??
const float maxWenuEtaBarrel = 1.4442;
const float minWenuEtaEndcap = 1.56;
const float maxWenuEta = 2.5;

//the offline electron should be matched with the online trigger object 
//no requirement on (electron,PV) matching
//??Work. Tulika said not needed now.  PV is primary vertex

//Electron ID criteria & Isolation Criteria 
//we use the 80% efficiency working point as it is defined here: https://twiki.cern.ch/twiki/bin/view/CMS/SimpleCutBasedEleID
const int maxWenuNmisshits =  1;
const float maxWenuDist = 0.02;
const float maxWenuDeltaCotTheta = 0.02; 

const float maxWenuCombIso[]      = {0.07 ,0.06};
const float maxWenuTrkRelIso[]    = {0.09 ,0.04};
const float maxWenuECalRelIso[]   = {0.07 ,0.05};
const float maxWenuHCalRelIso[]   = {0.10 ,0.025};
const float maxWenuSigmaEtaEta[]  = {0.01 ,0.03};
const float maxWenuDeltaPhiIn[]   = {0.06 ,0.03};
const float maxWenuDeltaEtaIn[]   = {0.004,0.007};
const float maxWenuHOverE[]       = {0.04 ,0.025};


//DY veto 
//we reject events with a second electron passing the electron WP95 selection and having ET > 20.0 GeV
//IGNORING this cut b/c of W+Z signal, maybe use if Z->mumu


// +++++++++++++++++++Zee

//https://twiki.cern.ch/twiki/bin/view/CMS/VbtfZeeBaselineSelection 
//referencing 95% levels at https://twiki.cern.ch/twiki/bin/view/CMS/SimpleCutBasedEleID
    
//Trigger Requirement 
//Process events that pass unprescaled single electron or photon triggers. The type(s) of triggers and their ET thresholds will be defined according to run conditions. We start with HLT_Photon10_L1R seeded on L1_SingleEG5 . When HLT_Photon10_L1R is prescaled we move to HLT_Photon15_L1R seeded on L1_SingleEG5 . When HLT_Photon15_L1R is prescaled we move to HLT_Ele15_LW_L1R seeded on L1_SingleEG5. (N.B. currently both HLT_Photon15_L1R & HLT_Ele15_LW_L1R are seeded on L1_SingleEG8, but it is intended that this be changed ).
//??Work
    
//Electron kinematics 
//electron supercluster ET > 20 GeV 
const float minZeeEt = 20;

//electron supercluster position in ECAL fiducial region ( |eta| < 2.5, 1.4442 < |eta| < 1.560 excluded) 
const float maxZeeEtaBarrel = 1.4442;
const float minZeeEtaEndcap = 1.560;
const float maxZeeEta = 2.5;

//one offline electron should be matched with the online trigger object 
//?????????????

//no requirement on (electron,PV) matching
//?????????????
    
//Electron ID criteria & Isolation Criteria    
//we use the 95% efficiency working point as it is defined here:

// Cut arrays are for {barrel, endcap} Eff 95%
const int maxZeeNmisshits =  2;
const float maxZeeDist = NOCUT;
const float maxZeedeltaCotTheta = NOCUT;

const float maxZeeCombIso[]      = {0.15 ,0.10};
const float maxZeeTrkRelIso[]    = {0.15 ,0.08};
const float maxZeeECalRelIso[]   = {2.00 ,0.06};
const float maxZeeHCalRelIso[]   = {0.12 ,0.05};
const float maxZeeSigmaEtaEta[]  = {0.01 ,0.03};
const float maxZeeDeltaPhiIn[]   = {0.80 ,0.70};
const float maxZeeDeltaEtaIn[]   = {0.007,0.01};
const float maxZeeHOverE[]       = {0.50 ,0.07};

const float minZeeMass = 60;
const float maxZeeMass = 120;

// +++++++++++++++++++ Older Cuts
const float minSeparation = 0.1;
const float minJetEta = 2.;
const float cutMinJetE = 300;
const float cutMinJetPt = 10;
const float cutMinJetsDeltaEta = 4;

// +++++++++++++++++++ Muon ID Cuts

const float maxWmunuMuonSip = 8.; //Sip
const float maxWmunuECalTrkRelIso = 0.1;

// +++++++++++++++++++ Electron ID Cuts
const float maxEtaBarrel = 1.479;
const float minEtaEndcap = 1.55;

const float minZeePt = 15;
const float minWenuPt = 20;
// +++++++++++++++++++ 

const float maxWenuCombRelIso[]  = {NOCUT,NOCUT};  
const float minWenuEOverP[]      = {0.760, 0.680};
const float maxWenuCalRelIso[]   = {0.100, 0.160};


// Cut arrays are Zee for {barrel, endcap}
const float minZeeEOverP[]      = {0.000, 0.000};
const float maxZeeCalRelIso[]   = {NOCUT, NOCUT};

