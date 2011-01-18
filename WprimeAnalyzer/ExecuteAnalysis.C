#ifndef _ExecuteAnalysis_cxx_
#define _ExecuteAnalysis_cxx_
//------------------------------------------------
// Author: Edgar Carrera
// Cory Fantasia
// 2010-06-13
// This macro will be used mostly for analyzing
// Wprime -> WZ -> lllnu events but it should
// work on any root-uple of events with
// variables created by the "official" CMS WZ code
// 
//------------------------------------------------


#include "ExecuteVariables.h"
#include "ExecuteCuts.h"
#include "ExecuteFunctions.h"

#include "ExecuteAnalysis.h"


//--------------------------------------------------------------
void Declare_Histos()
{
//--------------------------------------------------------------

  if (debugme) cout<<"Declare histos"<<endl;
  listOfHists.clear();

  DeclareHistoSet("hWZInvMass", "Reconstructed WZ Invariant Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, Cut, hWZInvMass);
  DeclareHistoSet("hWZ3e0muInvMass", "Reconstructed WZ(3e0\\mu) Invariant Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, Cut, hWZ3e0muInvMass);
  DeclareHistoSet("hWZ2e1muInvMass", "Reconstructed WZ(2e1\\mu) Invariant Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, Cut, hWZ2e1muInvMass);
  DeclareHistoSet("hWZ1e2muInvMass", "Reconstructed WZ(1e2\\mu) Invariant Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, Cut, hWZ1e2muInvMass);
  DeclareHistoSet("hWZ0e3muInvMass", "Reconstructed WZ(0e3\\mu) Invariant Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, Cut, hWZ0e3muInvMass);

  DeclareHistoSet("hWZTransMass", "Reconstructed WZ Transverse Mass",
                  "m_{WZ} (GeV)", 100, 0, 1000, Cut, hWZTransMass);
  //Ht Histos
  DeclareHistoSet("hHt", "H_{T}", 
                  "Lepton Pt Sum: H_{T} (GeV)", 80, 0, 800, Cut, hHt);
  //Wpt Histos
  DeclareHistoSet("hWpt", "p_{T}^{W}", 
                  "p_{T}^{W} (GeV)", 40, 0, 400, Cut, hWpt);
  //Zpt Histos
  DeclareHistoSet("hZpt", "p_{T}^{Z}", 
                  "p_{T}^{Z} (GeV)", 40, 0, 400, Cut, hZpt);
  //MET Histos
  DeclareHistoSet("hMET", "MET",
                  "MET (GeV)", 50, 0, 500, Cut, hMET);

  //Z Mass Histos
  DeclareHistoSet("hZMass" , "Reconstructed Mass of Z",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZMass);
  DeclareHistoSet("hZeeMass","Reconstructed Mass of Zee",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZeeMass);
  DeclareHistoSet("hZmumuMass","Reconstructed Mass of Zmumu",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZmumuMass);
  DeclareHistoSet("hZ3e0muMass" , "Reconstructed Mass of Z(3e0\\mu)",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZ3e0muMass);
  DeclareHistoSet("hZ2e1muMass" , "Reconstructed Mass of Z(2e1\\mu)",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZ2e1muMass);
  DeclareHistoSet("hZ1e2muMass" , "Reconstructed Mass of Z(1e2\\mu)",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZ1e2muMass);
  DeclareHistoSet("hZ0e3muMass" , "Reconstructed Mass of Z(0e3\\mu)",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZ0e3muMass);

  //W Trans Mass Histos
  DeclareHistoSet("hWTransMass", "Reconstructed TransMass of W",
                  "m_{T}^{Reco} (GeV)", 10, 0, 100, Cut, hWTransMass);
  DeclareHistoSet("hWenuTransMass", "Reconstructed TransMass of Wenu",
                  "m_{T}^{Reco} (GeV)", 10, 0, 100, Cut, hWenuTransMass);
  DeclareHistoSet("hWmunuTransMass", "Reconstructed TransMass of Wmunu",
                  "m_{T}^{Reco} (GeV)", 10, 0, 100, Cut, hWmunuTransMass);
  DeclareHistoSet("hW3e0muTransMass", "Reconstructed TransMass of W(3e0\\mu)",
                  "m_{T}^{Reco} (GeV)", 10, 0, 100, Cut, hW3e0muTransMass);
  DeclareHistoSet("hW2e1muTransMass", "Reconstructed TransMass of W(2e1\\mu)",
                  "m_{T}^{Reco} (GeV)", 10, 0, 100, Cut, hW2e1muTransMass);
  DeclareHistoSet("hW1e2muTransMass", "Reconstructed TransMass of W(1e2\\mu)",
                  "m_{T}^{Reco} (GeV)", 10, 0, 100, Cut, hW1e2muTransMass);
  DeclareHistoSet("hW0e3muTransMass", "Reconstructed TransMass of W(0e3\\mu)",
                  "m_{T}^{Reco} (GeV)", 10, 0, 100, Cut, hW0e3muTransMass);
  
  //Leading Lepton Pt
  DeclareHistoSet("hLeadPt", "Leading Lepton Pt",
                  "P_{T} (GeV)", 30, 0, 300, Cut, hLeadPt);

  DeclareHistoSet("hLeadElecPt", "Leading Electron Pt",
                  "P_{T} (GeV)", 30, 0, 300, Cut, hLeadElecPt);

  DeclareHistoSet("hLeadMuonPt", "Leading Muon Pt",
                  "P_{T} (GeV)", 30, 0, 300, Cut, hLeadMuonPt);

  //Electron Properties
  DeclareHistoSet("hElecPt", "Electron Pt",
                  "Pt", 50, 0, 500, Cut, hElecPt);

  DeclareHistoSet("hElecEt", "Electron Et",
                  "Et", 50, 0, 500, Cut, hElecEt);
  
  DeclareHistoSet("hElecDEta", "Electron Delta Eta",
                  "dEta", 100, 0, 1, Cut, hElecdEta);
  
  DeclareHistoSet("hElecDPhi","Electron Delta Phi",
                  "dPhi", 100, 0, 1, Cut, hElecdPhi);

  DeclareHistoSet("hElecSigmaEtaEta", "Electron Sigma Eta Eta",
                  "Sigma Eta Eta", 100, 0, 1, Cut, hElecSigmann);

  DeclareHistoSet("hElecEP", "Electron E Over P",
                  "E/P", 100, 0, 2, Cut, hElecEP);

  DeclareHistoSet("hElecHOverE","Electron H over E",
                  "H/E", 200, 0, 2, Cut, hElecHE);

  DeclareHistoSet("hElecTrkRelIso", "Electron Relative Track Iso",
                  "TrkRelIso", 100, 0, 2, Cut, hElecTrkRelIso);

  DeclareHistoSet("hElecECalRelIso", "Electron Relative ECal Iso",
                  "ECalRelIso", 100, 0, 2, Cut, hElecECalRelIso);

  DeclareHistoSet("hElecHCalRelIso", "Electron Relative HCal Iso",
                  "HCalRelIso", 100, 0, 2, Cut, hElecHCalRelIso);

  //Muon Histograms
  DeclareHistoSet("hMuonPt", "Muon Pt",
                  "Pt", 50, 0, 500, Cut, hMuonPt);

  DeclareHistoSet("hMuonDxy", "Muon Dxy",
                  "Dxy", 100, 0, 1, Cut, hMuonDxy);

  DeclareHistoSet("hMuonNormChi2", "Muon NormChi2",
                  "NormChi2", 50, 0, 50, Cut, hMuonNormChi2);
  
  DeclareHistoSet("hMuonNPix", "Muon NPix",
                  "NPix", 50, 0, 50, Cut, hMuonNPix);
    
  DeclareHistoSet("hMuonNTrk", "Muon NTrk",
                  "NTrk", 50, 0, 50, Cut, hMuonNTrk);

  DeclareHistoSet("hMuonStation", "Muon Station",
                  "Station", 50, 0, 50, Cut, hMuonStation);

  DeclareHistoSet("hMuonSip", "Muon Sip",
                  "Sip", 100, 0, 50, Cut, hMuonSip);

  DeclareHistoSet("hMuonRelIso", "Muon Rel Iso",
                  "Rel Iso", 100, 0, 1, Cut, hMuonRelIso);

  ///Eff Plots///////
  string title = "Expected # of Events / " + convertFloatToStr(lumiPb) + " pb^{-1}";
  hNumEvts = new TH1F("hNumEvts",title.c_str(),NCuts,0,NCuts);
  hEffRel = new TH1F("hEffRel","Relative Efficiency",NCuts,0,NCuts);
  hEffAbs = new TH1F("hEffAbs","Absolute Efficiency",NCuts,0,NCuts);
  for(int i=0; i<NCuts; ++i) hNumEvts->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());
  for(int i=0; i<NCuts; ++i) hEffRel ->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());
  for(int i=0; i<NCuts; ++i) hEffAbs ->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());

  listOfHists.push_back(hNumEvts);
  listOfHists.push_back(hEffRel);
  listOfHists.push_back(hEffAbs);

}//Declare_Histos

//Fill Histograms
//-----------------------------------------------------------
void Fill_Histos(int index, float weight)
{
//-----------------------------------------------------------
  if(debugme) cout<<"Filling Histos"<<endl;

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
  if      (Z_flavor == PDGELEC) hZeeMass[index]->Fill(Z_mass,weight);
  else if (Z_flavor == PDGMUON) hZmumuMass[index]->Fill(Z_mass,weight);
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
CalcEventVariables(){
  ////Calculate Important Quantities for each event
  Ht = Calc_Ht();
  LeadPt = CalcLeadPt();
  LeadElecPt = CalcLeadPt(PDGELEC);
  LeadMuonPt = CalcLeadPt(PDGMUON);
}

bool
PassCuts(vector<int>& Num_surv_cut, const float& weight){
  //an index to indicate current cut number
  int cut_index = 0;//Incremented in Tabulate_Me
      
  vector<int> idxs;
  vector<int> inEC;

  //cuts: These need to be ordered the same as Cut_Name in header file
  //The ides is to keep each cut as a separate entity 
  //so they can be better handled

  //No Cuts
  Tabulate_Me(Num_surv_cut,cut_index,weight); 
      
  if(!PassTriggersCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  if(!PassValidWandZCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  if(!PassNumberOfZsCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  /////////General Electron Cuts////////////////
  if(Z_flavor == PDGELEC ){
    idxs.push_back(Z_leptonIndex1); 
    inEC.push_back(inEndCap(electron_ScEta->at(Z_leptonIndex1)));
    idxs.push_back(Z_leptonIndex2);
    inEC.push_back(inEndCap(electron_ScEta->at(Z_leptonIndex2)));
  }     
  if (W_flavor == PDGELEC){
    idxs.push_back(W_leptonIndex); 
    inEC.push_back(inEndCap(electron_ScEta->at(W_leptonIndex)));
  }
      
  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassElecEtaCut        (idxs[lep])) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassElecEtCut         (idxs[lep],0)) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassElecSigmaEtaEtaCut(idxs[lep],inEC[lep])) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassElecDeltaPhiCut   (idxs[lep],inEC[lep])) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassElecDeltaEtaCut   (idxs[lep],inEC[lep])) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassElecHOverECut     (idxs[lep],inEC[lep])) return false;       
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  //////General Muon Cuts////////////
      
  idxs.clear(); inEC.clear();
  if(Z_flavor == PDGMUON ){
    idxs.push_back(Z_leptonIndex1); 
    idxs.push_back(Z_leptonIndex2);
  }
  if (W_flavor == PDGMUON){
    idxs.push_back(W_leptonIndex); 
  }
      
  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassMuonTypeCut      (idxs[lep])) return false; 
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassMuonEtaCut       (idxs[lep])) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassMuonPtCut        (idxs[lep],0)) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassMuonDxyCut       (idxs[lep])) return false; 
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassMuonNormChi2Cut  (idxs[lep])) return false; 
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassMuonNpixhitCut   (idxs[lep])) return false; 
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassMuonNtrkhitCut   (idxs[lep])) return false; 
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassMuonStationsCut  (idxs[lep])) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  for(size_t lep=0; lep != idxs.size(); ++lep) 
    if(!PassMuonHitsUsedCut  (idxs[lep])) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  ////Boson Cuts/////////////
  if(!PassWLepIsoCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);      

  if(!PassZmassCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);
     
  if(!PassWtransMassCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  if(!PassMETCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  if(!PassZLepPtCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  if(!PassWLepPtCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);      

  ////Analysis Cuts/////////////
  if(!PassHtCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  if(!PassZptCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  if(!PassWptCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);

  //After All Cuts
  Tabulate_Me(Num_surv_cut,cut_index,weight); 

  return true;
}

//-----------------------------------------------------------
void ExecuteAnalysis()
{
//-----------------------------------------------------------
  if (debugme)cout<<"Master macro to execute analysis"<<endl;
  
  //lumiPb now defined in ExecuteAnalysis.h
  cout<<"Using integrated luminosity of "<<lumiPb<<" inv pb"<<endl;
 
  //name of file where to write all histograms
  TFile *fout = new TFile("Wprime_analysis.root","recreate");
 
  //keep account of events
  string outfile("event_counts.txt");
  ofstream out(outfile.c_str());
  if(!out) { 
    cout << "Cannot open file " << outfile << endl; 
    abort();
  } 
  
  //containers to
  //include signal and background files

  //go for the analysis now and separate 
  //nicely into background/signal-type directories
  //the results will be written under respective directories
  //Add as many as you need:
  
  vector<InputFile> Wprime300_files;
  UseSample("Wprime300",Wprime300_files, Cut, fout, out);
  vector<InputFile> Wprime400_files;
  UseSample("Wprime400",Wprime400_files, Cut, fout, out);
  vector<InputFile> Wprime500_files;
  UseSample("Wprime500",Wprime500_files, Cut, fout, out);
  vector<InputFile> Wprime600_files;
  UseSample("Wprime600",Wprime600_files, Cut, fout, out);
  vector<InputFile> Wprime700_files;
  UseSample("Wprime700",Wprime700_files, Cut, fout, out);
  vector<InputFile> Wprime800_files;
  UseSample("Wprime800",Wprime800_files, Cut, fout, out);
  vector<InputFile> Wprime900_files;
  UseSample("Wprime900",Wprime900_files, Cut, fout, out);
  
  vector<InputFile> TC225_files;
  UseSample("TC225", TC225_files, Cut, fout, out);
  vector<InputFile> TC300_files;
  UseSample("TC300", TC300_files, Cut, fout, out);
  vector<InputFile> TC400_files;
  UseSample("TC400", TC400_files, Cut, fout, out);
  vector<InputFile> TC500_files;
  UseSample("TC500", TC500_files, Cut, fout, out);
  
  vector<InputFile> WZ_files;
  UseSample("WZ",WZ_files, Cut, fout, out);
  vector<InputFile> TTbar_files;
  //UseSample("TTbar",TTbar_files, Cut, fout, out);
  vector<InputFile> TTbar2l_files;
  UseSample("TTbar2l",TTbar2l_files, Cut, fout, out);
  vector<InputFile> ZZ_files;
  //UseSample("ZZ",ZZ_files, Cut, fout, out);
  vector<InputFile> ZZ4l_files;
  UseSample("ZZ4l",ZZ4l_files, Cut, fout, out);
  vector<InputFile> ZGamma_files;
  UseSample("ZGamma",ZGamma_files, Cut, fout, out);

  vector<InputFile> ZJetsBinned_files;
  UseSample("ZJetsBinned",ZJetsBinned_files, Cut, fout, out);
  vector<InputFile> ZeeJets_files;
  //UseSample("ZeeJets",ZeeJets_files, Cut, fout, out);
  vector<InputFile> ZmumuJets_files;
  //UseSample("ZmumuJets",ZmumuJets_files, Cut, fout, out);
  vector<InputFile> ZeeJetsPowheg_files;
  //UseSample("ZeeJetsPowheg",ZeeJetsPowheg_files, Cut, fout, out);
  vector<InputFile> ZmumuJetsPowheg_files;
  //UseSample("ZmumuJetsPowheg",ZmumuJetsPowheg_files, Cut, fout, out);
  vector<InputFile> ZllJetsMadgraph_files;
  //UseSample("ZllJetsMadgraph",ZllJetsMadgraph_files, Cut, fout, out);

  vector<InputFile> WenuJets_files;
  //UseSample("WenuJets",WenuJets_files, Cut, fout, out);
  vector<InputFile> WmunuJets_files;
  //UseSample("WmunuJets",WmunuJets_files, Cut, fout, out);
  vector<InputFile> WlnuJetsMadgraph_files;
  UseSample("WlnuJetsMadgraph",WlnuJetsMadgraph_files, Cut, fout, out);
  
  vector<InputFile> Run2010_files;
  UseSample("Run2010",Run2010_files, Cut, fout, out);
  
  //vector<InputFile> Interesting_files;
  //UseSample("interesting",Interesting_files, Cut, fout, out);
    
  out.close(); 
  fout->Close();

}//ExecuteAnalysis

int 
main(int argc, char ** argv){
  if(argc > 1 || argv[1][1]=='?'){
    fprintf(stderr,"%s usage: %s \n",argv[0],argv[0]);
    exit( 1 );
  }
  ExecuteAnalysis();

  return 0;
}

#endif//#define _ExecuteAnalysis_cxx_
