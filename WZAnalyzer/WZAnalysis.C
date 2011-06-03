#include "WZAnalysis.h"
using namespace std;
WZAnalysis::WZAnalysis(){cout<<"In def WZAnalysis con\n";}
WZAnalysis::~WZAnalysis(){
  outCandEvt.close(); 
  outLogFile.close(); 
  fout->Close();
}
WZAnalysis::WZAnalysis(const vector<string> C, 
                       const string& tld, const float& l,
                       const bool& dbg){
  Cuts = C;
  NCuts = Cuts.size();
  FillCutFns();
  debugme = dbg; 
  top_level_dir = tld;
  lumiPb = l;
  if(debugme) cout<<"Using "<<NCuts<<" cuts\n";

  fout = NULL;

  PDGMUON = 13;
  PDGELEC = 11;
  PDGW = 24;
  PDGZ = 23;
  PDGWPRIME = 34;

  PDGZMASS = 91.1876; //GeV
  W_mass = 80.398;

  PI    = 2.0 * TMath::ACos(0.);
  TWOPI = 2.0 * PI;
  NOCUT = 9e9;

  hEvtType.resize(NCuts);

  hWZInvMass     .resize(NCuts);
  hWZ3e0muInvMass.resize(NCuts);
  hWZ2e1muInvMass.resize(NCuts);
  hWZ1e2muInvMass.resize(NCuts);
  hWZ0e3muInvMass.resize(NCuts);

  hWZTransMass.resize(NCuts);
  hHt.resize(NCuts);
  hWpt.resize(NCuts);
  hZpt.resize(NCuts);
  hMET.resize(NCuts);

  hZMass     .resize(NCuts);
  hZeeMass   .resize(NCuts);
  hZmumuMass .resize(NCuts);
  hZ3e0muMass.resize(NCuts);
  hZ2e1muMass.resize(NCuts);
  hZ1e2muMass.resize(NCuts);
  hZ0e3muMass.resize(NCuts);
  hZeeMassTT.resize(NCuts);
  hZeeMassTF.resize(NCuts);
  hZmumuMassTT.resize(NCuts);
  hZmumuMassTF.resize(NCuts);

  hWTransMass     .resize(NCuts);
  hWenuTransMass  .resize(NCuts);
  hWmunuTransMass .resize(NCuts);
  hW3e0muTransMass.resize(NCuts);
  hW2e1muTransMass.resize(NCuts);
  hW1e2muTransMass.resize(NCuts);
  hW0e3muTransMass.resize(NCuts);

  hQ.resize(NCuts);

  hLeadPt.resize(NCuts);
  hLeadElecPt.resize(NCuts);
  hLeadMuonPt.resize(NCuts);

  hElecPt.resize(NCuts);
  hElecEt.resize(NCuts);
  hElecdEta.resize(NCuts);
  hElecdPhi.resize(NCuts);
  hElecSigmann.resize(NCuts);
  hElecEP.resize(NCuts);
  hElecHE.resize(NCuts);
  hElecTrkRelIso.resize(NCuts);
  hElecECalRelIso.resize(NCuts);
  hElecHCalRelIso.resize(NCuts);

  hMuonPt.resize(NCuts);
  hMuonDxy.resize(NCuts);
  hMuonNormChi2.resize(NCuts);
  hMuonNPix.resize(NCuts);
  hMuonNTrk.resize(NCuts);
  hMuonRelIso.resize(NCuts);
  hMuonStation.resize(NCuts);
  hMuonSip.resize(NCuts);

// +++++++++++++++++++General Cut values
  maxNumZs = 2;
  minNumLeptons = 3;
  minLepPt = 30.;
  minMET = 30;

// +++++++++++++++++++Ht Cuts
  minHt = 190;//150 for TC300; 190 for W'400
  minHtMet = 0; //Not Used

// +++++++++++++++++++W Cuts
  minWtransMass = 0;//Cory: Removed cut
  minWpt = 110;//90 for TC300; 110 for W'400

  minWmunuMuonPt = 20.;
  maxWmunuCombRelIso = 0.15;

  minWenuEt = 20.;
  cutWenuWPRelIsoMask = 2;//Cory: Iso only

  maxWenuTrkRelIso[0]   = 0.30;
  maxWenuTrkRelIso[1]   = 0.20;
  maxWenuECalRelIso[0]  = 0.20;
  maxWenuECalRelIso[1]  = 0.15;
  maxWenuHCalRelIso[0]  = 0.15;
  maxWenuHCalRelIso[1]  = 0.12;

// +++++++++++++++++++Z Cuts
  minZpt = 110;//90 for TC300; 110 for W'400
  minZmass = 80;
  maxZmass = 100;

  minZmumuMuonPt = 20.;
  minZeeEt = 20;

// +++++++++++++++++++Electron General Cuts
  maxElecEtaBarrel = 1.4442;
  minElecEtaEndcap = 1.56;
  maxElecEta = 2.5;
//VBTF Recommended Cuts
  minElecEt = 10;
  cutElecWPLooseMask = 5;//Cory: No Iso

  maxElecSigmaEtaEta[0] = 0.01;
  maxElecSigmaEtaEta[1] = 0.03;
  maxElecDeltaPhiIn [0] = 0.08;
  maxElecDeltaPhiIn [1] = 0.7 ;
  maxElecDeltaEtaIn [0] = 0.007;
  maxElecDeltaEtaIn [1] = 0.01;
  maxElecHOverE     [0] = 0.15;
  maxElecHOverE     [1] = 0.07;

// +++++++++++++++++++Muon General Cuts
  cutMuonIsGlobal = true;
  maxMuonEta = 2.5;
  minMuonPt = 10.;
//VBTF Recommended Cuts
  maxMuonDxy = 0.2;
  maxMuonNormChi2 = 10.;
  minMuonNPixHit = 0;
  minMuonNTrkHit = 10;
  minMuonStations = 1;
  minMuonHitsUsed = 0;
}

void WZAnalysis::FillCutFns(){
  mFnPtrs["NoCuts"] = &WZAnalysis::PassNoCut;
  mFnPtrs["HLT"] = &WZAnalysis::PassTriggersCut;
  mFnPtrs["ValidW"] = &WZAnalysis::PassValidWCut;
  mFnPtrs["ValidZ"] = &WZAnalysis::PassValidZCut;
  mFnPtrs["ValidWandZ"] = &WZAnalysis::PassValidWandZCut;
  mFnPtrs["ValidWZCand"] = &WZAnalysis::PassValidWZCandCut;
  mFnPtrs["MinLepPt"] = &WZAnalysis::PassLeadLepPt;
  mFnPtrs["NumZs"] = &WZAnalysis::PassNumberOfZsCut;
  mFnPtrs["LooseElec"] = &WZAnalysis::PassWZElecLooseCut;
  mFnPtrs["LooseMuon"] = &WZAnalysis::PassWZMuonLooseCut;
  mFnPtrs["LooseZElec"] = &WZAnalysis::PassZElecLooseCut;
  mFnPtrs["LooseZMuon"] = &WZAnalysis::PassZMuonLooseCut;
  mFnPtrs["WLepIso"] = &WZAnalysis::PassWLepIsoCut;
  mFnPtrs["ZMass"] = &WZAnalysis::PassZmassCut;
  mFnPtrs["WTransMass"] = &WZAnalysis::PassWtransMassCut;
  mFnPtrs["MET"] = &WZAnalysis::PassMETCut;
  mFnPtrs["ZLepPt"] = &WZAnalysis::PassZLepPtCut;
  mFnPtrs["WLepPt"] = &WZAnalysis::PassWLepPtCut;
  mFnPtrs["Ht"] = &WZAnalysis::PassHtCut;
  mFnPtrs["Zpt"] = &WZAnalysis::PassZptCut;
  mFnPtrs["Wpt"] = &WZAnalysis::PassWptCut;
  mFnPtrs["AllCuts"] = &WZAnalysis::PassNoCut;

  CutFns.resize(NCuts);
  for(int i=0; i<NCuts; ++i){
    CutFns[i] = mFnPtrs.find(Cuts[i])->second;
  }
}

//check if the input files are there
//----------------------------------------------------------
int WZAnalysis::Check_Files(uint Nfiles, vector<InputFile> & files)
{
//-----------------------------------------------------------

  if(Nfiles != files.size())
  {
    cerr << " *** Expected " << Nfiles << " files, got "
         << files.size() << " instead..." << endl;
    return -1;
  }  
  return 0;
}

void
WZAnalysis::RecruitOrderedFile(vector<InputFile> & file, 
                           const string& filename,
                           const string& file_desc){
  RecruitOrderedFiles(file, 1, 0, 0, filename, "", file_desc);
}

//Recruit files that are numbered from a given sample
//----------------------------------------------------------
void WZAnalysis::RecruitOrderedFiles(vector<InputFile> & files, const int& Nfiles,
                                 const int& filenum_low, const int& filenum_step,
                                 const string& mask1, const string& mask2, 
                                 const string& file_desc)
{
//-----------------------------------------------------------
  cout<<"Recruiting " << file_desc << " files."<<endl;
  for(int i = 0; i != Nfiles; ++i){
    int filenum = filenum_low + i*filenum_step;
    files[i].pathname = top_level_dir + mask1;
    if(Nfiles > 1) files[i].pathname += convertIntToStr(filenum) + mask2;
    files[i].description = file_desc;
  }
}// --RecruitOrderedFiles

string
WZAnalysis::FindInputFilename(string file_desc){
  string sDi = "Dilepton";
  string sTri = "Trilepton";
  bool isDilepton = (file_desc.find(sDi) != string::npos);
  if(isDilepton) file_desc.replace(file_desc.find(sDi),sDi.length(),"");

  string filename;
  if (!file_desc.compare("Wprime300")){
    filename = "TrileptonPatTupleV05-04-00-WprimeToWZTo3LNu_M-300_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("Wprime400")){
    filename = "TrileptonPatTupleV05-04-00-WprimeToWZTo3LNu_M-400_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("Wprime500")){
    filename = "TrileptonPatTupleV05-04-00-WprimeToWZTo3LNu_M-500_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("Wprime600")){
    filename = "TrileptonPatTupleV05-04-00-WprimeToWZTo3LNu_M-600_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("Wprime700")){
    filename = "TrileptonPatTupleV05-04-00-WprimeToWZTo3LNu_M-700_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("Wprime800")){
    filename = "TrileptonPatTupleV05-04-00-WprimeToWZTo3LNu_M-800_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("Wprime900")){
    filename = "TrileptonPatTupleV05-04-00-WprimeToWZTo3LNu_M-900_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("TC225")){
    filename = "TrileptonPatTupleMC-TC225_WZ.root";
  }else if (!file_desc.compare("TC300")){
    filename = "TrileptonPatTupleMC-TC300_WZ.root";
  }else if (!file_desc.compare("TC400")){
    filename = "TrileptonPatTupleMC-TC400_WZ.root";
  }else if (!file_desc.compare("TC500")){
    filename = "TrileptonPatTupleMC-TC500_WZ.root";
  }else if (!file_desc.compare("WZ3l")){
    filename = "TrileptonPatTupleV05-04-00-WZTo3LNu_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("TTbar")){
    filename = "TrileptonPatTupleMC-TTbar_outputTree.root";
  }else if (!file_desc.compare("TTbar2l")){
    filename = "TrileptonPatTupleV05-04-00-TTTo2L2Nu2B_7TeV-powheg-pythia6_outputTree.root";
  }else if (!file_desc.compare("TTbarfast")){
    filename = "TrileptonPatTupleMC-TTbarFast_outputTree.root";
  }else if (!file_desc.compare("ZZ")){
    filename = "TrileptonPatTupleV05-04-00-ZZtoAnything_TuneZ2_7TeV-pythia6-tauola_outputTree.root";
  }else if (!file_desc.compare("ZZ4l")){
    filename = "TrileptonPatTupleMC-ZZ4l_outputTree.root";
  }else if (!file_desc.compare("ZGamma2l")){
    filename = "TrileptonPatTupleV05-04-00-ZGtoLLG_TuneZ2_7TeV-pythia6-tauola_outputTree.root";
  }else if (!file_desc.compare("WenuJets")){
    filename = "TrileptonPatTupleV05-04-00-WToENu_TuneZ2_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("WmunuJets")){
    filename = "TrileptonPatTupleV05-04-00-WToMuNu_TuneZ2_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("WlnuJetsMadgraph")){
    filename = "TrileptonPatTupleMC-WlnuJetsMadgraph_outputTree.root";
  }else if (!file_desc.compare("ZeeJets")){
    filename = "TrileptonPatTupleMC-ZeeJets_WZ.root";
  }else if (!file_desc.compare("ZmumuJets")){
    filename = "TrileptonPatTupleMC-ZmumuJets_WZ.root";
  }else if (!file_desc.compare("ZeeJetsPowheg")){
    filename = "TrileptonPatTupleMC-ZeeJetsPowheg_WZ.root";
  }else if (!file_desc.compare("ZmumuJetsPowheg")){
    filename = "TrileptonPatTupleMC-ZmumuJetsPowheg_WZ.root";
  }else if (!file_desc.compare("ZllJetsMadgraph")){
    filename = "TrileptonPatTupleMC-ZllJetsMadgraph_WZ.root";
  }else if (!file_desc.compare("DYJets2l")){
    filename = "TrileptonPatTupleV05-04-00-DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_outputTree.root";
  }else if (!file_desc.compare("DYee")){
    filename = "TrileptonPatTupleV05-04-00-DYToEE_M-20_TuneZ2_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("DYmumu")){
    filename = "TrileptonPatTupleV05-04-00-DYToMuMu_M-20_TuneZ2_7TeV-pythia6_outputTree.root";
  }else if (!file_desc.compare("test")){
    filename = "outputTree.root";
  }else if (!file_desc.compare("interesting")){
    filename = "Interesting_outputTree.root";
  }else if (!file_desc.compare("Run2010")){
    filename = "TrileptonPatTuple-2010_WZ.root";
  }else if (!file_desc.compare("Run2011")){
    filename = "TrileptonPatTupleV05-04-01GIJ-2011A_outputTree.root";
  }else{
    cout<<"No samples were found with the name "<<file_desc<<endl;
    abort();//return "";
  }
  
  if(isDilepton){
    filename.replace(filename.find(sTri),sTri.length(),sDi);
  }
  return filename;
}

//load the input files from the top_level_dir
//-----------------------------------------------------------
bool WZAnalysis::Load_Input_Files(string file_desc, vector<InputFile> & files)
{
//-----------------------------------------------------------
  if (debugme)cout<<"Loading input Files...."<<endl;

  cout << "\n Processing " << file_desc<< " files " << endl << endl;

//switch between different sample cases and
//recruit the files. 
  files.push_back(InputFile()); 
  string filename = FindInputFilename(file_desc);
  //if(Check_Files(Nfiles, files) == -1) return false;
  RecruitOrderedFile(files, filename,file_desc);
  
  float Total_Nprod_evt = 0;
  
//Loop over the files in order to get the correct tree
//and the number of total events 
  int Nfiles = files.size();
  for(int i = 0; i != Nfiles; ++i){ // loop over input files
    string pathname = files[i].pathname;
    TFile * file = TFile::Open(pathname.c_str(), "read");
    if(!file || !(file->IsOpen())){
      cerr <<" *** Missing file: "<< pathname << " !!! "<<endl; 
      return false;
    }
    if (debugme)cout<<"Processing file: "<<pathname<<endl;
      
    files[i].tree = (TTree *) file->Get("WZ");
      
    TH1F* histNumEvents       = (TH1F  *)file->Get("numEvents");
    const float eventsAnalyzed  = histNumEvents->GetBinContent(1);
    delete histNumEvents;
    files[i].Nprod_evt = eventsAnalyzed;

    if(files[i].x_sect == 0){
      //Cory: If we don't merge files, we can use this method
      TH1F* histWeight       = (TH1F  *)file->Get("weight");
      const float cross_sec  = histWeight->GetBinContent(2);
      delete histWeight;
      files[i].x_sect = cross_sec;
    }
  
    Total_Nprod_evt += files[i].Nprod_evt;
  }// loop over input files 1

  for(int i = 0; i != Nfiles; ++i){ // loop over input files 2
    files[i].weight = lumiPb*(files[i].x_sect)/(Total_Nprod_evt);
    //if(binned) files[i].weight = lumiPb*(files[i].x_sect)/(files[i].Nprod_evt);
      
    if(files[i].x_sect == 0) files[i].weight = 1.;

    cout <<"Events produced in file = "<<files[i].Nprod_evt
         <<",  # of entries = "<< files[i].tree->GetEntries() 
         << ", x-sect = " << files[i].x_sect 
         << ", weight = " << files[i].weight 
         << ", Eff Lumi = " << files[i].Nprod_evt / files[i].x_sect 
         << endl;
      
  } // loop over input files 2
  
  return true;
}

//--------------------------------------------------------------
void WZAnalysis::Declare_Histos()
{
//--------------------------------------------------------------

  if (debugme) cout<<"Declare histos"<<endl;
  listOfHists.clear();

  DeclareHistoSet("hEvtType", "Event Type (Number of Electrons)",
                  "N_{Elec}", 4, 0, 4, hEvtType);

  DeclareHistoSet("hWZInvMass", "Reconstructed WZ Invariant Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, hWZInvMass);
  DeclareHistoSet("hWZ3e0muInvMass", "Reconstructed WZ(3e0\\mu) Invariant Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, hWZ3e0muInvMass);
  DeclareHistoSet("hWZ2e1muInvMass", "Reconstructed WZ(2e1\\mu) Invariant Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, hWZ2e1muInvMass);
  DeclareHistoSet("hWZ1e2muInvMass", "Reconstructed WZ(1e2\\mu) Invariant Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, hWZ1e2muInvMass);
  DeclareHistoSet("hWZ0e3muInvMass", "Reconstructed WZ(0e3\\mu) Invariant Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, hWZ0e3muInvMass);

  DeclareHistoSet("hWZTransMass", "Reconstructed WZ Transverse Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, hWZTransMass);
//Ht Histos
  DeclareHistoSet("hHt", "H_{T}", 
                  "Lepton Pt Sum: H_{T} (GeV)", 80, 0, 800, hHt);
//Wpt Histos
  DeclareHistoSet("hWpt", "p_{T}^{W}", 
                  "p_{T}^{W} (GeV)", 40, 0, 400, hWpt);
//Zpt Histos
  DeclareHistoSet("hZpt", "p_{T}^{Z}", 
                  "p_{T}^{Z} (GeV)", 40, 0, 400, hZpt);
//MET Histos
  DeclareHistoSet("hMET", "MET",
                  "MET (GeV)", 30, 0, 300, hMET);

//Z Mass Histos
  DeclareHistoSet("hZMass" , "Reconstructed Mass of Z",
                  "m_{Z}^{Reco} (GeV)", 30, 60, 120, hZMass);
  DeclareHistoSet("hZeeMass","Reconstructed Mass of Zee",
                  "m_{Z}^{Reco} (GeV)", 30, 60, 120, hZeeMass);
  DeclareHistoSet("hZmumuMass","Reconstructed Mass of Zmumu",
                  "m_{Z}^{Reco} (GeV)", 30, 60, 120, hZmumuMass);
  DeclareHistoSet("hZ3e0muMass" , "Reconstructed Mass of Z(3e0\\mu)",
                  "m_{Z}^{Reco} (GeV)", 30, 60, 120, hZ3e0muMass);
  DeclareHistoSet("hZ2e1muMass" , "Reconstructed Mass of Z(2e1\\mu)",
                  "m_{Z}^{Reco} (GeV)", 30, 60, 120, hZ2e1muMass);
  DeclareHistoSet("hZ1e2muMass" , "Reconstructed Mass of Z(1e2\\mu)",
                  "m_{Z}^{Reco} (GeV)", 30, 60, 120, hZ1e2muMass);
  DeclareHistoSet("hZ0e3muMass" , "Reconstructed Mass of Z(0e3\\mu)",
                  "m_{Z}^{Reco} (GeV)", 30, 60, 120, hZ0e3muMass);
  DeclareHistoSet("hZeeMassTT","Reconstructed MassTT of ZeeTT",
                  "m_{Z}^{Reco} (GeV)", 30, 60, 120, hZeeMassTT);
  DeclareHistoSet("hZeeMassTF","Reconstructed Mass of ZeeTF",
                  "m_{Z}^{Reco} (GeV)", 30, 60, 120, hZeeMassTF);
  DeclareHistoSet("hZmumuMassTT","Reconstructed Mass of ZmumuTT",
                  "m_{Z}^{Reco} (GeV)", 30, 60, 120, hZmumuMassTT);
  DeclareHistoSet("hZmumuMassTF","Reconstructed Mass of ZmumuTF",
                  "m_{Z}^{Reco} (GeV)", 30, 60, 120, hZmumuMassTF);

//W Trans Mass Histos
  DeclareHistoSet("hWTransMass", "Reconstructed TransMass of W",
                  "m_{T}^{Reco} (GeV)", 20, 0, 100, hWTransMass);
  DeclareHistoSet("hWenuTransMass", "Reconstructed TransMass of Wenu",
                  "m_{T}^{Reco} (GeV)", 20, 0, 100, hWenuTransMass);
  DeclareHistoSet("hWmunuTransMass", "Reconstructed TransMass of Wmunu",
                  "m_{T}^{Reco} (GeV)", 20, 0, 100, hWmunuTransMass);
  DeclareHistoSet("hW3e0muTransMass", "Reconstructed TransMass of W(3e0\\mu)",
                  "m_{T}^{Reco} (GeV)", 20, 0, 100, hW3e0muTransMass);
  DeclareHistoSet("hW2e1muTransMass", "Reconstructed TransMass of W(2e1\\mu)",
                  "m_{T}^{Reco} (GeV)", 20, 0, 100, hW2e1muTransMass);
  DeclareHistoSet("hW1e2muTransMass", "Reconstructed TransMass of W(1e2\\mu)",
                  "m_{T}^{Reco} (GeV)", 20, 0, 100, hW1e2muTransMass);
  DeclareHistoSet("hW0e3muTransMass", "Reconstructed TransMass of W(0e3\\mu)",
                  "m_{T}^{Reco} (GeV)", 20, 0, 100, hW0e3muTransMass);

//Q=M_{WZ} - M_W - M_Z
  DeclareHistoSet("hQ", "Q=M_{WZ} - M_{W} - M_{Z}",
                  "Q (GeV)", 30, 0, 300, hQ);
  
//Leading Lepton Pt
  DeclareHistoSet("hLeadPt", "Leading Lepton Pt",
                  "P_{T} (GeV)", 30, 0, 300, hLeadPt);

  DeclareHistoSet("hLeadElecPt", "Leading Electron Pt",
                  "P_{T} (GeV)", 30, 0, 300, hLeadElecPt);

  DeclareHistoSet("hLeadMuonPt", "Leading Muon Pt",
                  "P_{T} (GeV)", 30, 0, 300, hLeadMuonPt);

//Electron Properties
  DeclareHistoSet("hElecPt", "Electron Pt",
                  "Pt", 50, 0, 500, hElecPt);

  DeclareHistoSet("hElecEt", "Electron Et",
                  "Et", 50, 0, 500, hElecEt);
  
  DeclareHistoSet("hElecDEta", "Electron Delta Eta",
                  "dEta", 100, 0, 1, hElecdEta);
  
  DeclareHistoSet("hElecDPhi","Electron Delta Phi",
                  "dPhi", 100, 0, 1, hElecdPhi);

  DeclareHistoSet("hElecSigmaEtaEta", "Electron Sigma Eta Eta",
                  "Sigma Eta Eta", 100, 0, 1, hElecSigmann);

  DeclareHistoSet("hElecEP", "Electron E Over P",
                  "E/P", 100, 0, 2, hElecEP);

  DeclareHistoSet("hElecHOverE","Electron H over E",
                  "H/E", 200, 0, 2, hElecHE);

  DeclareHistoSet("hElecTrkRelIso", "Electron Relative Track Iso",
                  "TrkRelIso", 100, 0, 2, hElecTrkRelIso);

  DeclareHistoSet("hElecECalRelIso", "Electron Relative ECal Iso",
                  "ECalRelIso", 100, 0, 2, hElecECalRelIso);

  DeclareHistoSet("hElecHCalRelIso", "Electron Relative HCal Iso",
                  "HCalRelIso", 100, 0, 2, hElecHCalRelIso);

//Muon Histograms
  DeclareHistoSet("hMuonPt", "Muon Pt",
                  "Pt", 50, 0, 500, hMuonPt);

  DeclareHistoSet("hMuonDxy", "Muon Dxy",
                  "Dxy", 100, 0, 1, hMuonDxy);

  DeclareHistoSet("hMuonNormChi2", "Muon NormChi2",
                  "NormChi2", 50, 0, 50, hMuonNormChi2);
  
  DeclareHistoSet("hMuonNPix", "Muon NPix",
                  "NPix", 50, 0, 50, hMuonNPix);
    
  DeclareHistoSet("hMuonNTrk", "Muon NTrk",
                  "NTrk", 50, 0, 50, hMuonNTrk);

  DeclareHistoSet("hMuonStation", "Muon Station",
                  "Station", 50, 0, 50, hMuonStation);

  DeclareHistoSet("hMuonSip", "Muon Sip",
                  "Sip", 100, 0, 50, hMuonSip);

  DeclareHistoSet("hMuonRelIso", "Muon Rel Iso",
                  "Rel Iso", 100, 0, 1, hMuonRelIso);

///Eff Plots///////
  string title = "Expected # of Events / " + convertFloatToStr(lumiPb) + " pb^{-1}";
  hNumEvts = new TH1F("hNumEvts",title.c_str(),NCuts,0,NCuts);
  hEffRel = new TH1F("hEffRel","Relative Efficiency",NCuts,0,NCuts);
  hEffAbs = new TH1F("hEffAbs","Absolute Efficiency",NCuts,0,NCuts);
  for(int i=0; i<NCuts; ++i) hNumEvts->GetXaxis()->SetBinLabel(i+1,Cuts[i].c_str());
  for(int i=0; i<NCuts; ++i) hEffRel ->GetXaxis()->SetBinLabel(i+1,Cuts[i].c_str());
  for(int i=0; i<NCuts; ++i) hEffAbs ->GetXaxis()->SetBinLabel(i+1,Cuts[i].c_str());

  listOfHists.push_back(hNumEvts);
  listOfHists.push_back(hEffRel);
  listOfHists.push_back(hEffAbs);

  hLumiPb = new TH1F("hLumiPb", "Integrated luminosity in pb^{-1}", 1, 0, 1);
  hLumiPb->SetBinContent(1, lumiPb);
  listOfHists.push_back(hLumiPb);

}//Declare_Histos

//Fill Histograms
//-----------------------------------------------------------
void WZAnalysis::Fill_Histos(int index, float weight)
{
//-----------------------------------------------------------
  if(debugme) cout<<"Filling Histos"<<endl;
  if(Z_flavor == PDGELEC && W_flavor == PDGELEC) hEvtType[index]->Fill(3., weight);
  if(Z_flavor == PDGELEC && W_flavor == PDGMUON) hEvtType[index]->Fill(2., weight);
  if(Z_flavor == PDGMUON && W_flavor == PDGELEC) hEvtType[index]->Fill(1., weight);
  if(Z_flavor == PDGMUON && W_flavor == PDGMUON) hEvtType[index]->Fill(0., weight);

  hWZInvMass[index]->Fill(WZ_invMassMinPz, weight);
  if(Z_flavor == PDGELEC && W_flavor == PDGELEC) hWZ3e0muInvMass[index]->Fill(WZ_invMassMinPz, weight);
  if(Z_flavor == PDGELEC && W_flavor == PDGMUON) hWZ2e1muInvMass[index]->Fill(WZ_invMassMinPz, weight);
  if(Z_flavor == PDGMUON && W_flavor == PDGELEC) hWZ1e2muInvMass[index]->Fill(WZ_invMassMinPz, weight);
  if(Z_flavor == PDGMUON && W_flavor == PDGMUON) hWZ0e3muInvMass[index]->Fill(WZ_invMassMinPz, weight);

  hWZTransMass[index]->Fill(WZ_transMass, weight);
  hHt[index]->Fill(Ht,weight);
  hZpt[index]->Fill(Z_pt,weight);
  hWpt[index]->Fill(W_pt,weight);
  hMET[index]->Fill(pfMet_et, weight);

  hZMass[index]->Fill(Z_mass,weight);
  if      (Z_flavor == PDGELEC){
    hZeeMass[index]->Fill(Z_mass,weight);
    if(TT) hZeeMassTT[index]->Fill(Z_mass,weight);
    if(TF) hZeeMassTF[index]->Fill(Z_mass,weight);
  }else if (Z_flavor == PDGMUON){
    hZmumuMass[index]->Fill(Z_mass,weight);
    if(TT) hZmumuMassTT[index]->Fill(Z_mass,weight);
    if(TF) hZmumuMassTF[index]->Fill(Z_mass,weight);
  }
  if(Z_flavor == PDGELEC && W_flavor == PDGELEC) hZ3e0muMass[index]->Fill(Z_mass, weight);
  if(Z_flavor == PDGELEC && W_flavor == PDGMUON) hZ2e1muMass[index]->Fill(Z_mass, weight);
  if(Z_flavor == PDGMUON && W_flavor == PDGELEC) hZ1e2muMass[index]->Fill(Z_mass, weight);
  if(Z_flavor == PDGMUON && W_flavor == PDGMUON) hZ0e3muMass[index]->Fill(Z_mass, weight);

  if(W_transMass>0){
    hWTransMass[index]->Fill(W_transMass,weight);
    if      (W_flavor == PDGELEC) hWenuTransMass[index]->Fill(W_transMass,weight);
    else if (W_flavor == PDGMUON) hWmunuTransMass[index]->Fill(W_transMass,weight);
    if(Z_flavor == PDGELEC && W_flavor == PDGELEC) hW3e0muTransMass[index]->Fill(W_transMass, weight);
    if(Z_flavor == PDGELEC && W_flavor == PDGMUON) hW2e1muTransMass[index]->Fill(W_transMass, weight);
    if(Z_flavor == PDGMUON && W_flavor == PDGELEC) hW1e2muTransMass[index]->Fill(W_transMass, weight);
    if(Z_flavor == PDGMUON && W_flavor == PDGMUON) hW0e3muTransMass[index]->Fill(W_transMass, weight);
  }
  
  hQ[index]->Fill(Q, weight);

  hLeadPt[index]->Fill(LeadPt,weight);
  hLeadElecPt[index]->Fill(LeadElecPt,weight);
  hLeadMuonPt[index]->Fill(LeadMuonPt,weight);
  
  vector<int> idxs;
  if(Z_flavor == PDGELEC){//Only write W electrons
//idxs.push_back(Z_leptonIndex1);
//idxs.push_back(Z_leptonIndex2);
  }
  if(W_flavor == PDGELEC){
    idxs.push_back(W_leptonIndex);
  }
  for(size_t i=0; i<idxs.size(); ++i){
    hElecPt[index]->Fill(electron_pt->at(idxs[i]),weight);
    hElecEt[index]->Fill(electron_ScEt->at(idxs[i]),weight);
    hElecdEta[index]->Fill(fabs(electron_deltaEtaIn->at(idxs[i])),weight);
    hElecdPhi[index]->Fill(fabs(electron_deltaPhiIn->at(idxs[i])),weight);
    hElecSigmann[index]->Fill(electron_sigmaEtaEta->at(idxs[i]),weight);
    hElecEP[index]->Fill(electron_eOverP->at(idxs[i]),weight);
    hElecHE[index]->Fill(electron_hOverE->at(idxs[i]),weight);
    hElecTrkRelIso[index]->Fill(electron_trackIso->at(idxs[i])/electron_pt->at(idxs[i]),weight);
    hElecECalRelIso[index]->Fill(electron_ecaloIso->at(idxs[i])/electron_pt->at(idxs[i]),weight);
    hElecHCalRelIso[index]->Fill(electron_hcaloIso->at(idxs[i])/electron_pt->at(idxs[i]),weight);
  }

  idxs.clear();
  if(Z_flavor == PDGMUON){
//idxs.push_back(Z_leptonIndex1);
//idxs.push_back(Z_leptonIndex2);
  }
  if(W_flavor == PDGMUON){
    idxs.push_back(W_leptonIndex);
  }
  for(size_t i=0; i<idxs.size(); ++i){
    hMuonPt[index]->Fill(muon_pt->at(idxs[i]), weight);
    hMuonDxy[index]->Fill(fabs(muon_globalD0->at(idxs[i])), weight);
    hMuonNormChi2[index]->Fill(Calc_MuonRelIso(idxs[i]), weight);
    hMuonNPix[index]->Fill(muon_globalNpixelHits->at(idxs[i]), weight);
    hMuonNTrk[index]->Fill(muon_globalNtrackerHits->at(idxs[i]), weight);
    hMuonStation[index]->Fill(muon_numGlobalMatches->at(idxs[i]), weight);
    hMuonSip[index]->Fill(
      muon_globalD0->at(idxs[i])/muon_globalD0Error->at(idxs[i]),weight);
    hMuonRelIso[index]->Fill(Calc_MuonRelIso(idxs[i]), weight);
  }
    
}//Fill_Histos

void
WZAnalysis::CalcEventVariables(){
  if (debugme) cout<<"In CalcEventVariables\n";
////Calculate Important Quantities for each event
  Ht = Calc_Ht();
  Q = WZ_invMassMinPz - Z_mass - W_mass;
  LeadPt = CalcLeadPt();
  LeadElecPt = CalcLeadPt(PDGELEC);
  LeadMuonPt = CalcLeadPt(PDGMUON);
  TT = TF = false;
  if(Z_flavor){
    bool tight1 = PassTightCut(Z_leptonIndex1, Z_flavor);
    bool tight2 = PassTightCut(Z_leptonIndex2, Z_flavor);
    //cout<<"tight1: "<<tight1<<" tight2: "<<tight2<<endl;
    TT = tight1 && tight2;
    TF = (tight1 && !tight2) || (!tight1 && tight2);
  }
}

void
WZAnalysis::DeclareHistoSet(string n, string t, string xtitle,
                        int nbins, float min, float max,
                        vector<TH1F*>& h){
  float binWidth = (max-min)/nbins;
  for(int i=0; i<NCuts; ++i){
    
    string name = n + "_" + Cuts[i];
    string title = t + " (After " + Cuts[i] + " Cut);" 
      + xtitle
      + ";Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    h[i] = new TH1F(name.c_str(),title.c_str(),nbins,min,max);
    listOfHists.push_back(h[i]);
  }
}

//------------------------------------------------------------------------
void WZAnalysis::saveHistos(string dir)
{
//------------------------------------------------------------------------
  if (debugme) cout<<"Save Histos....."<<endl;
  fout->cd(); 
  fout->mkdir(dir.c_str()); 
  fout->cd(dir.c_str());

  for(uint i = 0; i != listOfHists.size(); ++i){
    listOfHists[i]->Write();
  }  
  return;

}//saveHistos

//------------------------------------------------------------------------
void WZAnalysis::deleteHistos()
{
//------------------------------------------------------------------------
  if (debugme) cout<<"Delete Histos....."<<endl;

  for(uint i = 0; i != listOfHists.size(); ++i){
    delete listOfHists[i];
  }  
  return;

}//deleteHistos

//Tabulate results after the cut has been passed
//-----------------------------------------------------------
void WZAnalysis::Tabulate_Me(vector<int>& Num_surv_cut, int& cut_index, 
                             const float& weight)
{
//-----------------------------------------------------------
  if(debugme) cout<<"Tabulating results for cut_index = "
                  <<cut_index<<endl;

//increase the number of events passing the cuts
  ++Num_surv_cut[cut_index];
//fill the histograms
  Fill_Histos(cut_index,weight);
    
}//Tabulate_Me

//Writing results to a txt file
//--------------------------------------------------------------------------
void WZAnalysis::printSummary(const string& dir, const float& Nthe_evt,
                              const float& Nexp_evt, vector<float>& Nexp_evt_cut) 
{ 
//------------------------------------------------------------------------
  if(debugme) cout<<"Writing results to a txt file"<<endl;

  outLogFile << setiosflags(ios::fixed) << setprecision(2);
  outLogFile<<"$$$$$$$$$$$$$$$$$$$$$$$ Type of sample: "<<dir<<endl;
  outLogFile << " xsec*lumi expected events = " << Nthe_evt << endl;
  outLogFile << " # of evt passing preselection = " << Nexp_evt << " per "<<convertFloatToStr(lumiPb)<<" inv pb"<<endl;
        
  for(int i = 0; i < NCuts; ++i){
    outLogFile<<right<<"Cut " << setw(2) << i << "("
       <<left<< setw(15) << Cuts[i]
       <<right << "): " <<"expected evts = " << setw(10) << Nexp_evt_cut[i];
    hNumEvts->Fill(i,Nexp_evt_cut[i]);

//calculate efficiencies
    float eff, deff;
    if(i == 0){
      getEff(eff, deff, Nexp_evt_cut[i], Nexp_evt);
    }else{
      getEff(eff, deff, Nexp_evt_cut[i], Nexp_evt_cut[i-1]);
    }
    hEffRel->Fill(i,eff*100);
    outLogFile << setw(15) <<"\tRelative eff = "<<setw(6)<<eff*100 << " +/- " << setw(6)<<deff*100 << "%";
//    if(Nexp_evt_cut[i-1] && Nexp_evt_cut[i-1] < 1.) printf("eff:%.2f deff:%.2f num:%.2f den:%.2f\n",eff,deff,Nexp_evt_cut[i],Nexp_evt_cut[i-1]);
    getEff(eff, deff, Nexp_evt_cut[i], Nexp_evt);
    hEffAbs->Fill(i,eff*100);
    outLogFile << setw(15) <<"\tAbsolute eff = "<<setw(6)<<eff*100 << " +/- " << setw(6)<<deff*100 << "%"
        << endl;
        
  } // loop over different cuts
}//printSummary

void 
WZAnalysis::UseSample(string dir){
  vector<InputFile> files;
  if(!Load_Input_Files(dir, files)){
    return;
  }
  Get_Distributions(dir, files);
}

//Get different types of distribution
//-----------------------------------------------------------
void WZAnalysis::Get_Distributions(string dir, vector<InputFile>& files)
{
//-----------------------------------------------------------
  if (debugme) cout<<"Get Distributions....."<<endl;

  Declare_Histos();

  int Nfiles = files.size();

//initialize counters for expected (already weighted) 
//number of events
//total, and after each cut.
  float Nthe_evt = 0;
  float Nexp_evt = 0;
  vector<float> Nexp_evt_cut(NCuts,0);  
//loop over files
  for(int tr = 0; tr != Nfiles; ++tr){
    if(!files[tr].tree){
      cout<<"Tree doesn't exist!!!!"<<endl;
      continue;
    }
  
    cout << "Processing file "<<files[tr].pathname<<endl;
    

    TTree *WZtree = files[tr].tree;    
    int nevents = WZtree->GetEntries();
    float weight = files[tr].weight;
    float x_sect = files[tr].x_sect;

//get the variables that we need right here:
    Set_Branch_Addresses(WZtree);

//counter (unweighted) events that pass each cut
    vector<int> Num_surv_cut(NCuts,0);
    
//Loop over events:
    for(int i = 0; i != nevents; ++i){//event loop
      if (debugme) cout<<"Processing event "<<i<<endl;

      WZtree->GetEntry(i);
      CalcEventVariables();
      if(!PassCuts(Num_surv_cut, weight)) continue;
      if(!dir.find("Run201")){
        cout<<" The following data events passed All Cuts!!!\n\n";
        PrintEventFull();
        cout<<" ------------------\n";
      }
      
    }//event loop
    
// total # of events (before any cuts)
    Nexp_evt += nevents * weight;
    Nthe_evt += lumiPb * x_sect;

//Number of expected events for each cut (weighted)
    for(int ii = 0; ii < NCuts; ++ii){
      if(debugme) cout<<"Num_surv_cut["<<ii<<"] = "<<
        Num_surv_cut[ii]<<endl;
      Nexp_evt_cut[ii] += Num_surv_cut[ii] * weight;
      if(debugme) cout<<"Nexp_evt_cut["<<ii<<"] = "<<
        Nexp_evt_cut[ii]<<endl;
    }

  }//loop over files
  
  printSummary(dir, Nthe_evt, Nexp_evt, Nexp_evt_cut);
  saveHistos(dir);
  deleteHistos();
  
}//Get_Distributions

void WZAnalysis::PrintEventToFile(){
  outCandEvt<<runNumber<<":"
            <<lumiBlock<<":"
            <<eventID<<endl;
}

void WZAnalysis::PrintEvent(){
  PrintEventToFile();
  cout<<"run #: "<<runNumber
      <<" lumi: "<<lumiBlock
      <<" eventID: "<<eventID<<endl
      <<" Z_flavor: "<<Z_flavor
      <<" Z_mass: "<<Z_mass
      <<" W_flavor: "<<W_flavor
      <<" W_transMass: "<<W_transMass
      <<endl;

  if(Z_flavor == PDGELEC){
    cout<<" Z_electron_pt1 "<<electron_pt->at(Z_leptonIndex1)
        <<" Z_electron_pt2 "<<electron_pt->at(Z_leptonIndex2);
  }else if(Z_flavor == PDGMUON){
    cout<<" Z_muon_pt1 "<<muon_pt->at(Z_leptonIndex1)
        <<" Z_muon_pt2 "<<muon_pt->at(Z_leptonIndex2);
  }

  cout<<endl;

  if(W_flavor == PDGELEC){
    cout<<" W_electron_pt "<<electron_pt->at(W_leptonIndex);
  }else if(W_flavor == PDGMUON){
    cout<<" W_muon_pt "<<muon_pt->at(W_leptonIndex);
  }
    
  cout<<" pfMet_et: "<<pfMet_et
      <<" tcMet_et: "<<tcMet_et
      <<" met_et: "<<met_et<<endl
      <<" Ht: "<<Ht
      <<" Zpt: "<<Z_pt
      <<" Wpt: "<<W_pt<<endl
      <<" WZ Mass: "<<WZ_invMassMinPz<<endl
      <<" # Elec: "<<electron_pt->size()
      <<" # Muon: "<<muon_pt->size()
      <<endl<<endl;
  return;
}

void
WZAnalysis::PrintEventFull(){
  PrintEvent();
  if     (Z_flavor == PDGELEC){
    PrintElectron(Z_leptonIndex1, PDGZ);
    PrintElectron(Z_leptonIndex2, PDGZ);
  }else if(Z_flavor == PDGMUON){
    PrintMuon(Z_leptonIndex1, PDGZ);
    PrintMuon(Z_leptonIndex2, PDGZ);
  }

  if     (W_flavor == PDGELEC) PrintElectron(W_leptonIndex, PDGW);
  else if(W_flavor == PDGMUON) PrintMuon(W_leptonIndex, PDGW);
}

void
WZAnalysis::PrintElectron(int idx, int parent){
  if     (parent == PDGZ) cout<<"-----Electron from Z-------------------------"<<endl;
  else if(parent == PDGW) cout<<"-----Electron from W-------------------------"<<endl;
  else                    cout<<"-----Electron from ?-------------------------"<<endl;
  cout<<" Elec Pt: "<<electron_pt->at(idx)<<endl
      <<" Elec ScEt: "<<electron_ScEt->at(idx)<<endl //ScEt
      <<" Elec Eta: "<<electron_eta->at(idx)<<endl //Eta
      <<" Elec SigmaNN: "<<electron_sigmaEtaEta->at(idx)<<endl //sigmaNN
      <<" Elec dPhi: "<<electron_deltaPhiIn->at(idx)<<endl //DeltaPhi
      <<" Elec dEta: "<<electron_deltaEtaIn->at(idx)<<endl //DeltaEta
      <<" Elec HoverE: "<<electron_hOverE->at(idx)<<endl// H/E
      <<" Elec EoverP: "<<electron_eOverP->at(idx)<<endl// E/P
      <<" Elec WP95: "<<electron_simpleEleId95relIso->at(idx)<<endl
      <<" Elec WP90: "<<electron_simpleEleId90relIso->at(idx)<<endl
      <<" Elec WP85: "<<electron_simpleEleId85relIso->at(idx)<<endl
      <<" Elec WP80: "<<electron_simpleEleId80relIso->at(idx)<<endl;
/*
  cout<<"Elec 60%: "<<electron_simpleEleId60relIso->at(idx)<<endl
  <<"Elec 70%: "<<electron_simpleEleId70relIso->at(idx)<<endl
  <<"Elec 80%: "<<electron_simpleEleId80relIso->at(idx)<<endl
  <<"Elec 85%: "<<electron_simpleEleId85relIso->at(idx)<<endl
  <<"Elec 90%: "<<electron_simpleEleId90relIso->at(idx)<<endl
  <<"Elec 95%: "<<electron_simpleEleId95relIso->at(idx)<<endl;
*/
  if(parent == PDGW){
    cout<<" Elec RelTrkIso: "<<Calc_ElecRelTrkIso(idx)<<endl
        <<" Elec RelECalIso: "<<Calc_ElecRelECalIso(idx)<<endl
        <<" Elec RelHCalIso: "<<Calc_ElecRelHCalIso(idx)<<endl;
  }
}

void
WZAnalysis::PrintMuon(int idx, int parent){
  if     (parent == PDGZ) cout<<"-----Muon from Z-------------------------"<<endl;
  else if(parent == PDGW) cout<<"-----Muon from W-------------------------"<<endl;
  else                    cout<<"-----Muon from ?-------------------------"<<endl;
  cout<<" Muon Pt: "<<muon_pt->at(idx)<<endl
      <<" Muon Eta: "<<muon_eta->at(idx)<<endl
      <<" Muon Dxy: "<<muon_globalD0->at(idx)<<endl //Dxy
      <<" Muon NormX2: "<<muon_globalChi2->at(idx)/muon_globalNdof->at(idx)<<endl //NormX2
      <<" Muon NPix: "<<muon_globalNpixelHits->at(idx)<<endl //Npixhit
      <<" Muon NTrk: "<<muon_globalNtrackerHits->at(idx)<<endl //Ntrk hit
      <<" Muon NMatches: "<<muon_numGlobalMatches->at(idx)<<endl //MuonStations
      <<" Muon NValid: "<<muon_numValidMuonHits->at(idx)<<endl; //Hits Used
  
  if(parent == PDGW){
    cout<<" Muon RelIso: "<<Calc_MuonRelIso(idx)<<endl;// CombRelIso
  }
}

float
WZAnalysis::CalcLeadPt(int type){
  float leadpt=-999;
  if(type==0){
    if(W_flavor == PDGELEC || Z_flavor == PDGELEC) leadpt=TMath::Max(leadpt,electron_pt->at(0));
    if(W_flavor == PDGMUON || Z_flavor == PDGMUON) leadpt=TMath::Max(leadpt,muon_pt->at(0));
  }else if(type==PDGELEC){
        if(W_flavor == PDGELEC || Z_flavor == PDGELEC) leadpt=TMath::Max(leadpt,electron_pt->at(0));
  }else if(type==PDGMUON){
    if(W_flavor == PDGMUON || Z_flavor == PDGMUON) leadpt=TMath::Max(leadpt,muon_pt->at(0));
  }
  return leadpt;
}

/////////////////Accessors///////////////////////
float WZAnalysis::GetLumiPb(){ 
  return lumiPb;
}

/////////////////Modifies///////////////////////
void WZAnalysis::CheckStream(ofstream& stream, string s){
  if(!stream) { 
    cout << "Cannot open file " << s << endl; 
    abort();
  } 
}

void WZAnalysis::SetCandEvtFile(string s){
  outCandEvt.open(s.c_str());
  CheckStream(outCandEvt, s);
}

void WZAnalysis::SetOutputFile(string s){
  fout = new TFile(s.c_str(),"recreate");
}

void WZAnalysis::SetLogFile(string s){
  outLogFile.open(s.c_str());      
  CheckStream(outLogFile, s); 
}

/////////////////Cuts///////////////////////
bool
WZAnalysis::PassCuts(vector<int>& Num_surv_cut, const float& weight){
  if (debugme) cout<<"In Pass Cuts\n";
  
  for(int i=0; i<NCuts; ++i){
    if(!(this->*CutFns[i])()) return false;
    Tabulate_Me(Num_surv_cut,i,weight); 
  }
  return true;
}

bool WZAnalysis::PassNoCut(){ 
  return true;
}

//Trigger requirements
//-----------------------------------------------------------
bool WZAnalysis::PassTriggersCut()
{
//-----------------------------------------------------------
  if(debugme) cout<<"Trigger requirements"<<endl;
  
  int NTriggers = TriggerHLTNames->size();
  for(int i=0; i<NTriggers; ++i){
    if(TriggerHLTDecisions->at(i) == 1 && TriggerHLTPrescales->at(i) <= 1) return true;
  }
  return false;
}//--- PassTriggersCut()

//Check if there are valid W and Z particles in the event
//-----------------------------------------------------------
bool WZAnalysis::PassValidWandZCut()
{
//-----------------------------------------------------------
  if(debugme) cout<<"Check if there are valid W and Z particles in the event"
                  <<endl;
  return PassValidZCut() && PassValidWCut();
}//--- NotValidWandZCut

bool WZAnalysis::PassValidWCut()
{
//-----------------------------------------------------------
  if(debugme) cout<<"Check if there is a valid W particle in the event"
                  <<endl;
  return W_flavor && W_transMass>0.;
}//--- NotValidWCut

bool WZAnalysis::PassValidZCut()
{
//-----------------------------------------------------------
  if(debugme) cout<<"Check if there is a valid Z particle in the event"
                  <<endl;
  return Z_flavor && Z_mass > 0.;
}//--- NotValidZCut

bool WZAnalysis::PassValidWZCandCut()
{
  if(debugme) cout<<"Check if there are valid WZ Candidate"<<endl;
  return PassValidWandZCut() && WZ_invMassMinPz>0.; 
}

bool WZAnalysis::PassLeadLepPt(){
  if(debugme) cout<<"Check if Leading Lep Pt"<<endl;
  return LeadPt > minLepPt;
}

//Check if there is more Zs than required
//-----------------------------------------------------------
bool WZAnalysis::PassNumberOfZsCut()
{
//-----------------------------------------------------------
  if(debugme) cout<<"Check if there is more Zs than required"<<endl;

  return (numberOfZs < maxNumZs);
}//--- NumberOfZsCut

//Check W decay Properties
//-----------------------------------------------------------
bool WZAnalysis::PassWLepPtCut(){
  if      (W_flavor == PDGELEC){
    return PassElecEtCut(W_leptonIndex,PDGW);
  }else if(W_flavor == PDGMUON){
    return PassMuonPtCut(W_leptonIndex,PDGW);
  }  
  return false;
}

bool WZAnalysis::PassWLepIsoCut(){
  if      (W_flavor == PDGMUON){
    return PassWmunuIsoCut();
  }else if(W_flavor == PDGELEC){
    return PassWenuIsoCut();
  }
  return false;
}

//Check Z decay Properties
//-----------------------------------------------------------
bool WZAnalysis::PassZLepPtCut(){
  if      (Z_flavor == PDGMUON){
    return PassZmumuPtCut();
  }else if(Z_flavor == PDGELEC){
    return PassZeePtCut();
  }
  return false;
}

//Check Wenu decay Properties
//-----------------------------------------------------------
bool WZAnalysis::PassWenuIsoCut(){
  /*
    bool inEC = inEndCap(electron_ScEta->at(W_leptonIndex));
    if(!PassElecTrkRelIsoCut (W_leptonIndex,inEC)) return false;
    if(!PassElecECalRelIsoCut(W_leptonIndex,inEC)) return false;
    if(!PassElecHCalRelIsoCut(W_leptonIndex,inEC)) return false;
    return true;
  */
  return PassElecWPRelIsoCut(W_leptonIndex);
}

//Check Wmunu decay Properties
//-----------------------------------------------------------
bool WZAnalysis::PassWmunuIsoCut(){
  if(!PassMuonCombRelIsoCut(W_leptonIndex)) return false;   
  return true;
}

//Check Zee decay Properties
//-----------------------------------------------------------
bool WZAnalysis::PassZeePtCut(){
  if(!PassElecEtCut(Z_leptonIndex1,PDGZ)) return false;
  if(!PassElecEtCut(Z_leptonIndex2,PDGZ)) return false;
  return true;
}

//Check Zmumu decay Properties
//-----------------------------------------------------------
bool WZAnalysis::PassZmumuPtCut(){
  if(!PassMuonPtCut(Z_leptonIndex1,PDGZ)) return false; 
  if(!PassMuonPtCut(Z_leptonIndex2,PDGZ)) return false; 
  return true;
}

//////////////////////////////////
//////Electron Cuts///////////////
//////////////////////////////////
bool WZAnalysis::PassWZElecLooseCut(){
  if(!PassZElecLooseCut()) return false;
  if(!PassWElecLooseCut()) return false;
  return true;
}

bool WZAnalysis::PassZElecLooseCut(){
  if(Z_flavor == PDGELEC ){
    if(!PassElecLooseCut(Z_leptonIndex1)) return false;
    if(!PassElecLooseCut(Z_leptonIndex2)) return false;
  }
  return true;
}

bool WZAnalysis::PassWElecLooseCut(){
  if(W_flavor == PDGELEC ){
    if(!PassElecLooseCut(W_leptonIndex)) return false;
  }
  return true;
}

bool WZAnalysis::PassElecLooseCut(int& idx){
  if(!PassElecEtCut     (idx)) return false;
  if(!PassElecLooseWPCut(idx)) return false;
  return true;
}

bool WZAnalysis::PassElecLooseCut(int& idx, int& inEC, int parent){
  if(!PassElecEtaCut        (idx))        return false;
  if(!PassElecEtCut         (idx,parent)) return false;
  if(!PassElecSigmaEtaEtaCut(idx,inEC))   return false;
  if(!PassElecDeltaPhiCut   (idx,inEC))   return false;
  if(!PassElecDeltaEtaCut   (idx,inEC))   return false;
  if(!PassElecHOverECut     (idx,inEC))   return false;       
  return true;
}

bool WZAnalysis::PassElecLooseWPCut(int& idx){
//-----------------------------------------------------------
  if(debugme) cout<<"Check Electron WP Loose Cut"<<endl;
  return (electron_simpleEleId95relIso->at(idx) & cutElecWPLooseMask) 
    == cutElecWPLooseMask;
}//--- PassElecLooseWPCut

bool WZAnalysis::PassElecEtCut(int idx,int parent){
//-----------------------------------------------------------
  if(debugme) cout<<"Check Electron Et Cut"<<endl;

  if      (parent == 0){
    return (electron_ScEt->at(idx) > minElecEt);
  }else if      (parent == PDGW){
    return (electron_ScEt->at(idx) > minWenuEt);
  }else if(parent == PDGZ){
    return (electron_ScEt->at(idx) > minZeeEt);
  }
  return false;
}//--- PassElecEtCut

bool WZAnalysis::PassElecEtaCut(int idx){
//-----------------------------------------------------------
  if(debugme) cout<<"Check Electron Eta Cut"<<endl;
  float eta = electron_ScEta->at(idx);
  return (inBarrel(eta) || inEndCap(eta));
}//--- PassElecEtaCut

bool WZAnalysis::PassElecTrkRelIsoCut(int idx,bool inEC){
//-----------------------------------------------------------
  if(debugme) cout<<"Check Electron ElecTrkRelIso Cut"<<endl;
  return (Calc_ElecRelTrkIso(idx) < maxWenuTrkRelIso[inEC]);
}//--- PassElecTrkRelIsoCut

bool WZAnalysis::PassElecECalRelIsoCut(int idx,bool inEC){
//-----------------------------------------------------------
  if(debugme) cout<<"Check Electron EcalRelIso Cut"<<endl;
  return (Calc_ElecRelECalIso(idx) < maxWenuECalRelIso[inEC]);
}//--- PassElecEcalRelIsoCut

bool WZAnalysis::PassElecHCalRelIsoCut(int idx,bool inEC){
//-----------------------------------------------------------
  if(debugme) cout<<"Check Electron HcalRelIso Cut"<<endl;
  return (Calc_ElecRelHCalIso(idx) < maxWenuHCalRelIso[inEC]);
}//--- PassHcalRelIsoElecCut

bool WZAnalysis::PassElecWPRelIsoCut(int idx){
//-----------------------------------------------------------
  if(debugme) cout<<"Check Electron WP RelIso Cut"<<endl;
  return (electron_simpleEleId80relIso->at(idx) & cutWenuWPRelIsoMask) 
    == cutWenuWPRelIsoMask;
}//--- PassElecWPRelIsoElecCut

bool WZAnalysis::PassElecSigmaEtaEtaCut(int idx,bool inEC){
//-----------------------------------------------------------
  if(debugme) cout<<"Check Electron Sigma nn Cut"<<endl;
  return (electron_sigmaEtaEta->at(idx) < maxElecSigmaEtaEta[inEC]);
}//--- PassElecSigmaEtaEtaCut

bool WZAnalysis::PassElecDeltaPhiCut(int idx,bool inEC){
//-----------------------------------------------------------
  if(debugme) cout<<"Check Electron dPhi Cut"<<endl;
  return (fabs(electron_deltaPhiIn->at(idx)) < maxElecDeltaPhiIn[inEC]);
}//--- PassElecDeltaPhiCut

bool WZAnalysis::PassElecDeltaEtaCut(int idx,bool inEC){
//-----------------------------------------------------------
  if(debugme) cout<<"Check Electron dEta Cut"<<endl;
  return (fabs(electron_deltaEtaIn->at(idx)) < maxElecDeltaEtaIn[inEC]);
}//--- PassElecDeltaEtaCut

bool WZAnalysis::PassElecHOverECut(int idx,bool inEC){
//-----------------------------------------------------------
  if(debugme) cout<<"Check Electron HOverE Cut"<<endl;
  return (electron_hOverE->at(idx) < maxElecHOverE[inEC]);
}//--- PassElecHOverECut

float
WZAnalysis::Calc_ElecRelTrkIso(int idx){
  return electron_trackIso->at(idx)/electron_pt->at(idx);
}

float
WZAnalysis::Calc_ElecRelECalIso(int idx){
  return electron_ecaloIso->at(idx)/electron_pt->at(idx);
}
float
WZAnalysis::Calc_ElecRelHCalIso(int idx){
  return electron_hcaloIso->at(idx)/electron_pt->at(idx);
}

///////////////////////////
////Muon Cuts//////////////
///////////////////////////
bool WZAnalysis::PassWZMuonLooseCut(){
  if(!PassZMuonLooseCut()) return false;
  if(!PassWMuonLooseCut()) return false;
  return true;
}

bool WZAnalysis::PassZMuonLooseCut(){
  if(Z_flavor == PDGMUON ){
    if(!PassMuonLooseCut(Z_leptonIndex1)) return false;
    if(!PassMuonLooseCut(Z_leptonIndex2)) return false;
  }
  return true;
}

bool WZAnalysis::PassWMuonLooseCut(){
  if(W_flavor == PDGMUON ){
    if(!PassMuonLooseCut(W_leptonIndex)) return false;
  }
  return true;
}

bool WZAnalysis::PassMuonLooseCut(int& idx, int parent){
  if(!PassMuonTypeCut      (idx)) return false; 
  if(!PassMuonEtaCut       (idx)) return false;
  if(!PassMuonPtCut        (idx,parent)) return false;
  if(!PassMuonDxyCut       (idx)) return false; 
  if(!PassMuonNormChi2Cut  (idx)) return false; 
  if(!PassMuonNpixhitCut   (idx)) return false; 
  if(!PassMuonNtrkhitCut   (idx)) return false; 
  if(!PassMuonStationsCut  (idx)) return false;
  if(!PassMuonHitsUsedCut  (idx)) return false;
  return true;
}

bool WZAnalysis::PassMuonTypeCut(int idx){
  if(debugme) cout<<"Check Muon Type Cut"<<endl;
  return (muon_isGlobal->at(idx) ); 
}//--- PassMuonTypeCut

bool WZAnalysis::PassMuonNpixhitCut(int idx){
  if(debugme) cout<<"Check Muon NpixhitCut"<<endl;
  return (muon_globalNpixelHits->at(idx) > minMuonNPixHit);
}//--- PassMuonNpixhitCut

bool WZAnalysis::PassMuonNtrkhitCut(int idx){
  if(debugme) cout<<"Check Muon NtrkhitCut"<<endl;
  return (muon_globalNtrackerHits->at(idx) > minMuonNTrkHit);
}//--- PassMuonNtrkhitCut

bool WZAnalysis::PassMuonNormChi2Cut(int idx){
  if(debugme) cout<<"Check Muon Chi2 Cut"<<endl;
  return (Calc_MuonNormChi2(idx) < maxMuonNormChi2);
}//--- PassMuonChi2Cut

bool WZAnalysis::PassMuonHitsUsedCut(int idx){
  //Num Valid Muon Hits
  if(debugme) cout<<"Check Muon Hits Used Cut"<<endl;
  return (muon_numValidMuonHits->at(idx) > minMuonHitsUsed);
}//--- PassMuonHits Used Cut

bool WZAnalysis::PassMuonStationsCut(int idx){
  if(debugme) cout<<"Check Muon Stations Cut"<<endl;
  return (muon_numGlobalMatches->at(idx) > minMuonStations);
}//--- PassMuonStationsCut

bool WZAnalysis::PassMuonEtaCut(int idx){
  if(debugme) cout<<"Check Muon Eta Cut"<<endl;
  return (fabs(muon_eta->at(idx)) < maxMuonEta);
}//--- PassMuonEta Cut

bool WZAnalysis::PassMuonPtCut(int idx,int parent){
  if(debugme) cout<<"Check Muon Pt Cut"<<endl;
  if      (parent == 0){
    return (muon_pt->at(idx) > minMuonPt);
  }else if      (parent == PDGW){
    return (muon_pt->at(idx) > minWmunuMuonPt);
  }else if(parent == PDGZ){
    return (muon_pt->at(idx) > minZmumuMuonPt);
  }
  return false;
}//--- PassMuonPtCut

bool WZAnalysis::PassMuonCombRelIsoCut(int idx){
  if(debugme) cout<<"Check Muon CombRelIso Cut"<<endl;
  return (Calc_MuonRelIso(idx) < maxWmunuCombRelIso);
}//--- PassMuonCombRelIsoCut

float
WZAnalysis::Calc_MuonNormChi2(int idx){
  return muon_globalChi2->at(idx)/muon_globalNdof->at(idx);
}

float 
WZAnalysis::Calc_MuonRelIso(int idx){
  return muon_relIso->at(idx);
  //if(muon_trackIso == 0 || muon_caloIso == 0) return 999;
  //return (muon_trackIso->at(idx) + muon_caloIso->at(idx)) / muon_pt->at(idx);
}//--- Calc_MuonRelIso

bool WZAnalysis::PassMuonDxyCut(int idx){
  if(debugme) cout<<"Check Muon Dxy Cut"<<endl;
  return (fabs(muon_globalD0->at(idx)) < maxMuonDxy);
}//--- PassMuonDxyCut

////////////////////////////////
/////////Check Z Properties/////
////////////////////////////////

//Check Z Mass
//-----------------------------------------------------------
bool WZAnalysis::PassZmassCut(){
  if(debugme) cout<<"Check Zmass Cut"<<endl;
  return (Z_mass > minZmass) && (Z_mass < maxZmass);
}//--- PassZmassCut

//Check Z pt
//-----------------------------------------------------------
bool WZAnalysis::PassZptCut()
{
//-----------------------------------------------------------
  if(debugme) cout<<"Check Z pt"<<endl;
  return (Z_pt > minZpt);
}//--- PassZptCut

////////////////////////////////
/////////Check W Properties/////
////////////////////////////////

//Check W Transverse Mass
//-----------------------------------------------------------
bool WZAnalysis::PassWtransMassCut(){
  if(debugme) cout<<"Check W Transverse Mass Cut"<<endl;
  return (W_transMass > minWtransMass);
}//--- PassWtransMassCut

//Check W pt
//-----------------------------------------------------------
bool WZAnalysis::PassWptCut()
{
//-----------------------------------------------------------
  if(debugme) cout<<"Check W pt"<<endl;
  return (W_pt > minWpt);
}//--- PassWptCut

////////////////////////////////
/////////Check Other Properties/////
////////////////////////////////

//Check Ht Properties
//-----------------------------------------------------------
bool WZAnalysis::PassHtCut()
{
//-----------------------------------------------------------
  if(debugme) cout<<"Check Ht Cuts"<<endl;
   
  return Ht > minHt;
    
}//--- PassHtCut

//Calc Ht
//-----------------------------------------------------------
float WZAnalysis::Calc_Ht()
{
  float retval=0;
  
  if     (W_flavor == PDGELEC) retval += electron_pt->at(W_leptonIndex);
  else if(W_flavor == PDGMUON) retval += muon_pt->at(W_leptonIndex);
  //else                         cout<<"W didn't decay into e,mu"<<endl;
  
  if     (Z_flavor == PDGELEC){
    retval += electron_pt->at(Z_leptonIndex1);
		retval += electron_pt->at(Z_leptonIndex2);
  }else if(Z_flavor == PDGMUON){
		retval += muon_pt->at(Z_leptonIndex1);
		retval += muon_pt->at(Z_leptonIndex2);
  }//else                         cout<<"Z didn't decay into e,mu"<<endl;
  
  return retval;
  
}//--- CalcHt

//Calc HtMET
//-----------------------------------------------------------
float WZAnalysis::Calc_HtMET()
{
  return Calc_Ht() + pfMet_et;
}//--- CalcHt

//Check Ht Met Properties
//-----------------------------------------------------------
bool WZAnalysis::PassHtMetCut()
{
//-----------------------------------------------------------
  if(debugme) cout<<"Check Ht Cuts"<<endl;
  return Calc_HtMET() > minHtMet;
}//--- PassHtMetCut

//MET Cut
//-----------------------------------------------------------
bool WZAnalysis::PassMETCut()
{
  return (pfMet_et > minMET);
}//--- MET Cut

//Pass Tight Cut
//-----------------------------------------------------------
bool WZAnalysis::PassTightCut(int idx, int flavor)
{
  if(flavor == PDGELEC){
    //bool inEC = inEndCap(electron_ScEta->at(idx));
    if(!PassElecEtCut         (idx,PDGW)) return false;
    if(!PassElecWPRelIsoCut(W_leptonIndex)) return false;
    //if(!PassElecTrkRelIsoCut  (idx,inEC)) return false;
    //if(!PassElecECalRelIsoCut (idx,inEC)) return false;
    //if(!PassElecHCalRelIsoCut (idx,inEC)) return false;
  }else if (flavor == PDGMUON){
    if(!PassMuonPtCut(idx, PDGW)) return false;
    if(!PassMuonCombRelIsoCut(idx)) return false;
  }
  return true;
}//--- Tight Cut

float WZAnalysis::Calc_GenWZInvMass()
{
  int pdg=0, pdgM=0;
  int idZ=-1;
  int idW=-1;    
  int size = genMother_pdgId->size();
  for(int i=0; i != size; i++){
    pdg = fabs(genParticle_pdgId->at(i));
    pdgM = fabs(genMother_pdgId->at(i));
    if (pdgM == PDGWPRIME){
      return genMother_mass->at(i);
    }
    if( pdg == PDGZ && pdgM != PDGZ){
      idZ = i;
    }
    if( pdg == PDGW && pdgM != PDGW){
      idW = i;
    }
        
    if( fabs(genParticle_pdgId->at(i)) == PDGZ && pdg > 50){
      cout<<"Mother of Z is "<<pdg<<endl;
    }
  }
  if(idZ != -1 && idW != -1){
    float E = genParticle_energy->at(idZ)+genParticle_energy->at(idW);
    float PX = genParticle_px->at(idZ)+genParticle_px->at(idW);
    float PY = genParticle_py->at(idZ)+genParticle_py->at(idW);
    float PZ = genParticle_pz->at(idZ)+genParticle_pz->at(idW);
    float m = sqrt(E*E - PX*PX - PY*PY - PZ*PZ);
    /*
      cout<<"E:"<<E
      <<" PX:"<<PX
      <<" PY:"<<PY
      <<" PZ:"<<PZ
      <<" Mass calc is "<<m<<endl;
    */
    return m;
             
  }
  return -1;
    
}//--- Calc Gen Inv Mass

///////////////Utilities//////////////////
//See if Electron is in Barrel
bool WZAnalysis::inBarrel(float eta)
{
  return (fabs(eta) < maxElecEtaBarrel);
}//InBarrel

bool WZAnalysis::inEndCap(float eta)
{
  float abs_eta = fabs(eta);
  return (abs_eta > minElecEtaEndcap && abs_eta < maxElecEta);         
}//InEndCap

//--------------------------------------------------------------
void WZAnalysis::getEff(float & eff, float & deff, float Num, float Denom)
{
//--------------------------------------------------------------
  if(Denom){
    eff = Num/Denom;
    deff = TMath::Sqrt(eff * (1-eff)/Denom);
  }else{
    eff = deff = 0;
  }

}//getEff

//--------------------------------------------------------------
double WZAnalysis::deltaPhi(double phi1, double phi2)
{
//--------------------------------------------------------------

  double phi=fabs(phi1-phi2);
  return (phi <= PI) ? phi : TWOPI - phi;
}

//--------------------------------------------------------------
double WZAnalysis::deltaEta(double eta1, double eta2)
{
//--------------------------------------------------------------
  double eta = fabs(eta1 - eta2);
  return eta;
}

//Just a function to calculate DeltaR
//--------------------------------------------------------------
double WZAnalysis::deltaR(double eta1, double phi1, double eta2, double phi2)
{
//--------------------------------------------------------------
  double deta = eta1 - eta2;
  double dphi = deltaPhi(phi1, phi2);
  return sqrt(deta * deta + dphi * dphi);
}

