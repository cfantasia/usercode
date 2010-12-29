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

#define ExecuteCheck_cxx
#include "ExecuteCheck.h"

//--------------------------------------------------------------
void Declare_Histos()
{
//--------------------------------------------------------------
  if (debugme) cout<<"Declare histos"<<endl;
  listOfHists.clear();

  DeclareHistoSet("hWZInvMass","Reconstructed WZ Invariant Mass",
                  "m_{WZ} (GeV)", 110, 0, 1100, Cut, hWZInvMass);
  DeclareHistoSet("hWZTransMass", "Reconstructed WZ Transverse Mass",
                  "m_{WZ} (GeV)", 110, 0, 1100, Cut, hWZTransMass);
  //Ht Histos
  DeclareHistoSet("hHt", "H_{T}","Lepton Pt Sum: H_{T} (GeV)",
                  50, 0, 1000, Cut, hHt);
  //Wpt Histos
  DeclareHistoSet("hWpt", "p_{T} of W", 
                  "p_{T}^{W} (GeV)", 80, 0, 400, Cut, hWpt);
  //Zpt Histos
  DeclareHistoSet("hZpt", "p_{T} of Z", 
                  "p_{T}^{Z} (GeV)", 80, 0, 400, Cut, hZpt);
  //MET Histos
  DeclareHistoSet("hMET", "MET",
                  "MET (GeV)", 50, 0, 500, Cut, hMET);

  //Z Mass Histos
  DeclareHistoSet("hZmass" , "Reconstructed Mass of Z",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZmass);
  
  DeclareHistoSet("hZeemass","Reconstructed Mass of Zee",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZeemass);

  DeclareHistoSet("hZmumumass","Reconstructed Mass of Zmumu",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZmumumass);

  //W Trans Mass Histos
  DeclareHistoSet("hWTransmass", "Reconstructed Transmass of W",
                  "m_{T W}^{Reco} (GeV)", 10, 0, 100, Cut, hWTransmass);
  
  //Wenu Trans Mass Histos
  DeclareHistoSet("hWenuTransmass", "Reconstructed Transmass of Wenu",
                  "m_{T W}^{Reco} (GeV)", 10, 0, 100, Cut, hWenuTransmass);

  //Wmunu Trans Mass Histos
  DeclareHistoSet("hWmunuTransmass", "Reconstructed Transmass of Wmunu",
                  "m_{T W}^{Reco} (GeV)", 10, 0, 100, Cut, hWmunuTransmass);
  
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

  DeclareHistoSet("hMuonRelIso", "Muon Rel Iso",
                  "Rel Iso", 100, 0, 1, Cut, hMuonRelIso);

  DeclareHistoSet("hMuonStation", "Muon Station",
                  "Station", 50, 0, 50, Cut, hMuonStation);

  DeclareHistoSet("hMuonSip", "Muon Sip",
                  "Sip", 100, 0, 50, Cut, hMuonSip);

  //////////Generator Level Plots
  DeclareHistoSet("hGenWZInvMass","Generated WZ Invariant Mass",
                  "m_{WZ} (GeV)", 110, 0, 1100, Cut, hGenWZInvMass);

  DeclareHistoSet("hMETDiff", "MET Difference",
                  "MET (GeV)", 200, -500, 500, Cut, hMETDiff);

  DeclareHistoSet("hGenDP", "GenDP",
                  "GenDP (GeV)", 1000, -7, 7, Cut, hGenDP);
  DeclareHistoSet("hRecoDP", "RecoDP",
                  "RecoDP (GeV)", 1000, -7, 7, Cut, hRecoDP);
  DeclareHistoSet("hDiffDP", "Diff DP",
                  "Diff DP (GeV)", 1000, -7, 7, Cut, hDiffDP);

  DeclareHistoSet("hGenZmass", "Generated Z Mass",
                  "M_{Z} (GeV)", 100, 0, 100, Cut, hGenZmass);

  DeclareHistoSet("hGenWTransmass", "Generated W TransMass",
                  "M_{T}^{W} (GeV)", 100, 0, 100, Cut, hGenWTransmass);
  DeclareHistoSet("hGenWTransmassDiff", "Diff Generated W TransMass",
                  "M_{T}^{W} (GeV)", 100, -100, 100, Cut, hGenWTransmassDiff);

  DeclareHistoSet("hElecPtDiff", "Electron Pt Diff",
                  "Delta Pt (GeV)", 100, -200, 200, Cut, hElecPtDiff);
  DeclareHistoSet("hMuonPtDiff", "Muon Pt Diff",
                  "Delta Pt (GeV)", 100, -200, 200, Cut, hMuonPtDiff);

  ///W Reco Check Plots/////////////////
  DeclareHistoSet("hWmass", "W Mass",
                  "M_{W} (GeV)", 100, 0, 100, Cut, hWmass);
  DeclareHistoSet("hWDpt", "W Lepton Delta Pt",
                  "D Pt", 100, -100, 100, Cut, hWDpt);
  DeclareHistoSet("hWDphi", "W Lepton Delta Phi",
                  "D Phi", 100, -4, 4, Cut, hWDphi);
  DeclareHistoSet("hWDeta", "W Lepton Delta Eta",
                  "D Eta", 100, 0, 10, Cut, hWDeta);
  DeclareHistoSet("hWDr", "W Lepton Delta R",
                  "DR ", 1000, 0, 5, Cut, hWDr);

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
    hWZTransMass[index]->Fill(WZ_transMass, weight);
    hHt[index]->Fill(Ht,weight);
    hZpt[index]->Fill(Z_pt,weight);
    hWpt[index]->Fill(W_pt,weight);
    hGenWZInvMass[index]->Fill(WZ_genMass, weight);
    hMET[index]->Fill(pfMet_et, weight);
    hMETDiff[index]->Fill(pfMet_et-genmet_et, weight);
    hGenDP[index]->Fill(gendp, weight);
    hRecoDP[index]->Fill(recodp, weight);
    hDiffDP[index]->Fill(gendp-recodp, weight);
    hZmass[index]->Fill(Z_mass,weight);
    if      (Z_flavor == PDGELEC){
        hZeemass[index]->Fill(Z_mass,weight);
    }else if (Z_flavor == PDGMUON){
        hZmumumass[index]->Fill(Z_mass,weight);
    }
    hGenZmass[index]->Fill(Z_genMass,weight);
    hWmass[index]->Fill(W_mass,weight);
    hGenWTransmass[index]->Fill(W_genTransMass,weight);
    if(W_transMass>0){
        hGenWTransmassDiff[index]->Fill(W_genTransMass-W_transMass,weight);
        hWTransmass[index]->Fill(W_transMass,weight);
        if      (W_flavor == PDGELEC) hWenuTransmass[index]->Fill(W_transMass,weight);
        else if (W_flavor == PDGMUON) hWmunuTransmass[index]->Fill(W_transMass,weight);
    }
    if     (W_flavor == PDGELEC) hElecPtDiff[index]->Fill(WlepGenPt - electron_pt->at(W_leptonIndex),weight);
    else if(W_flavor == PDGMUON) hMuonPtDiff[index]->Fill(WlepGenPt - muon_pt->at(W_leptonIndex), weight);


    vector<int> idxs;
    if(Z_flavor == PDGELEC){//Only write W electrons
        //idxs.push_back(Z_leptonIndex1);
        //idxs.push_back(Z_leptonIndex2);
    }
    if(W_flavor == PDGELEC && Z_flavor == PDGMUON){
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
    if(W_flavor == PDGMUON && Z_flavor == PDGELEC){
        idxs.push_back(W_leptonIndex);
    }
    for(size_t i=0; i<idxs.size(); ++i){
        hMuonPt[index]->Fill(muon_pt->at(idxs[i]), weight);
        hMuonDxy[index]->Fill(muon_globalD0->at(idxs[i]), weight);
        hMuonNormChi2[index]->Fill(
            muon_globalChi2->at(idxs[i])/muon_globalNdof->at(idxs[i]), weight);
        hMuonNPix[index]->Fill(muon_globalNpixelHits->at(idxs[i]), weight);
        hMuonNTrk[index]->Fill(muon_globalNtrackerHits->at(idxs[i]), weight);
        hMuonRelIso[index]->Fill(Calc_MuonRelIso(idxs[i]), weight);
        hMuonStation[index]->Fill(muon_numGlobalMatches->at(idxs[i]), weight);
        hMuonSip[index]->Fill(
            muon_globalD0->at(idxs[i])/muon_globalD0Error->at(idxs[i]),weight);
    }
    
    hWDpt[index]->Fill(WDpt,weight);
    hWDphi[index]->Fill(WDphi,weight);
    hWDeta[index]->Fill(WDeta,weight);
    hWDr[index]->Fill(WDr,weight);
        
}//Fill_Histos

//Get different types of distribution
//-----------------------------------------------------------
void Get_Distributions(vector<InputFile>& files, 
                       TFile *fout, string dir, ofstream & out)
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
  float Nexp_evt_cut[NCuts] = {0};
  
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
    int Num_surv_cut[NCuts] = {0};
    
    
    //Loop over events:
    //The ides is to keep each cut as a separate entity 
    //so they can be better handled
    for(int i = 0; i != nevents; ++i){//event loop

      WZtree->GetEntry(i);
      ////Calculate Important Quantities for each event
      Ht = Calc_Ht();
      WZ_genMass = Calc_GenWZInvMass();

      if (debugme) cout<<"Processing event "<<i<<endl;

      //an index to indicate current cut number
      int cut_index = 0;//Incremented in Tabulate_Me
      
      vector<int> idxs;
      vector<int> inEC;

      //cuts: These need to be ordered the same as Cut_Name in header file
      Tabulate_Me(Num_surv_cut,cut_index,weight); //No Cuts
      
      //if(!PassTriggersCut()) continue; //Cory
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      //These are used to look at cut eff.
      //if(Z_flavor != PDGELEC || W_flavor != PDGMUON) continue;
      //if(Z_flavor != PDGMUON || W_flavor != PDGELEC) continue;
      //if(!inBarrel(electron_ScEta->at(W_leptonIndex))) continue;
      //if(!inEndCap(electron_ScEta->at(W_leptonIndex))) continue;
      
      if(!PassValidWandZCut()) continue; //Cory
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      if(!PassNumberOfZsCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      ////////////////New Elec Cuts////////////////
      bool pass = true;
      
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
          if(!PassElecEtaCut        (idxs[lep])) pass = false;
      if(!pass) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassElecEtCut         (idxs[lep],0)) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassElecSigmaEtaEtaCut(idxs[lep],inEC[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassElecDeltaPhiCut   (idxs[lep],inEC[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassElecDeltaEtaCut   (idxs[lep],inEC[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassElecHOverECut     (idxs[lep],inEC[lep])) pass = false;       
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      /////////Muon Cuts////////////
      
      idxs.clear(); inEC.clear();
      if(Z_flavor == PDGMUON ){
          idxs.push_back(Z_leptonIndex1); 
          idxs.push_back(Z_leptonIndex2);
      }
      if (W_flavor == PDGMUON){
          idxs.push_back(W_leptonIndex); 
      }
      
      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonTypeCut      (idxs[lep])) pass = false; 
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonEtaCut       (idxs[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonPtCut        (idxs[lep],0)) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonDxyCut       (idxs[lep])) pass = false; 
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonNormChi2Cut  (idxs[lep])) pass = false; 
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonNpixhitCut   (idxs[lep])) pass = false; 
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonNtrkhitCut   (idxs[lep])) pass = false; 
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonStationsCut  (idxs[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonHitsUsedCut  (idxs[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      ////Other Cuts/////////////
      if(!PassZDecayCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      if(!PassWDecayCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);      

      if(!PassHtCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      if(!PassZptCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      if(!PassWptCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      PrintEvent();

      if(!PassMETCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      //After All Cuts
      Tabulate_Me(Num_surv_cut,cut_index,weight); 
      
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
  
  printSummary(out, dir, Nthe_evt, Nexp_evt, Nexp_evt_cut, Cut);
  saveHistos(fout, dir);
  deleteHistos();
  
}//Get_Distributions

//Compare Reco
//-----------------------------------------------------------
bool Calc_RecoCompare()
{
    if     (W_flavor == PDGELEC) recodp = deltaPhi(electron_phi->at(W_leptonIndex),met_phi);
    else if(W_flavor == PDGMUON) recodp = deltaPhi(muon_phi->at(W_leptonIndex),met_phi);
    else                    recodp = -999;
    
    if     (W_flavor == PDGELEC && W_neutrino_pzMinPz){
        float nu_energy = sqrt(met_et*met_et +
                               W_neutrino_pzMinPz*W_neutrino_pzMinPz);
        float e = electron_energy->at(W_leptonIndex)+nu_energy;
        float px = electron_px->at(W_leptonIndex)+met_et*cos(met_phi);
        float py = electron_py->at(W_leptonIndex)+met_et*sin(met_phi);
        float pz = electron_pz->at(W_leptonIndex)+W_neutrino_pzMinPz;
        W_mass = sqrt(e*e - px*px - py*py - pz*pz);
    }else if(W_flavor == PDGMUON && W_neutrino_pzMinPz){
        float nu_energy = sqrt(met_et*met_et +
                               W_neutrino_pzMinPz*W_neutrino_pzMinPz);
        float e = muon_energy->at(W_leptonIndex)+nu_energy;
        float px = muon_px->at(W_leptonIndex)+met_et*cos(met_phi);
        float py = muon_py->at(W_leptonIndex)+met_et*sin(met_phi);
        float pz = muon_pz->at(W_leptonIndex)+W_neutrino_pzMinPz;
        W_mass = sqrt(e*e - px*px - py*py - pz*pz);
    }else{
        W_mass = -999;
    }
    /*    
      bool check = false;
    
      if(Z_mass > 60 && Z_mass < 70){
      check = true;
      cout<<"Event: "<<eventID<<endl;
      cout<<"Z_flavor: "<<Z_flavor<<" Z_mass: "<<Z_mass<<" Gen:"<<Z_genMass
      <<" #Elec"<<electron_pt->size()<<" #Muon"<<muon_pt->size()
      <<" Z_pt: "<<Z_pt<<" Z_genpt: "<<Z_genPt
      <<" ZdaugIdx1:"<<Z_leptonIndex1
      <<" ZdaugIdx2:"<<Z_leptonIndex2
      <<endl;
      
      }
    */
    
    for(unsigned int part=0; part!=genParticle_et->size(); part++){
        /*
          if(abs(genParticle_pdgId->at(part)) == PDGW){
          W_genTransMass = sqrt(
          genParticle_et->at(part)*genParticle_et->at(part) -
          genParticle_pt->at(part)*genParticle_pt->at(part) );
          cout<<"Event: "<<i<<"Index:"<<part
          <<" gen trans mass: "<<W_genTransMass
          <<" gen mass: "<<genParticle_mass->at(part)
          <<" gen eta: "<<genParticle_eta->at(part)
          <<endl;
          }
        */
        if(abs(genMother_pdgId->at(part)) == PDGW){
            WlepGenPt = genParticle_pt->at(part);
            gendp = deltaPhi(genParticle_phi->at(part), genmet_phi);
            
            if      (W_flavor == PDGELEC){
                WDpt = genParticle_pt->at(part) - electron_pt->at(W_leptonIndex);
                WDphi = genParticle_phi->at(part);//deltaPhi(genParticle_phi->at(part), electron_phi->at(W_leptonIndex));
                WDeta = deltaEta(genParticle_eta->at(part), electron_eta->at(W_leptonIndex));
                WDr = sqrt(WDphi*WDphi + WDeta*WDeta);
                //cout<<"gen: "<<genParticle_phi->at(part)<<" phi: "<<electron_phi->at(W_leptonIndex)<<endl
                //    <<"gen: "<<genParticle_eta->at(part)<<" reco: "<<electron_eta->at(W_leptonIndex)<<endl;
            }else if(W_flavor == PDGMUON){
                WDpt = genParticle_pt->at(part) - muon_pt->at(W_leptonIndex);
                WDphi = deltaPhi(genParticle_phi->at(part), muon_phi->at(W_leptonIndex));
                WDeta = deltaEta(genParticle_eta->at(part), muon_eta->at(W_leptonIndex));
                WDr = sqrt(WDphi*WDphi + WDeta*WDeta);
            }else{
                WDpt = -999;
                WDphi = -999;
                WDeta = -999;
                WDr = -999;
            }
            
            /*
              cout<<genParticle_et->at(part)<<endl
              <<genmet_et<<endl
              <<genParticle_phi->at(part)<<endl
              <<genmet_phi<<endl
              <<dp<<endl
              <<1-cos(dp)<<endl
              
              <<endl;
            */
            W_genTransMass = sqrt(2*genmet_et*genParticle_et->at(part)*(1-cos(gendp)));
            
            W_genpt = genMother_pt->at(part);
            W_genphi = genMother_phi->at(part);
            W_geneta = genMother_eta->at(part);
            W_genpz = genMother_pz->at(part);
            
            lep_genpz = genParticle_pz->at(part);
            //lep_genpt = genParticle_pt->at(part);
            //lep_genphi = genParticle_phi->at(part);
            
            neu_px = met_et*cos(met_phi);
            neu_py = met_et*sin(met_phi);
            neu_pz = W_neutrino_pzMinPz;
            
            neu_genpx = genMother_px->at(part) - genParticle_px->at(part);
            neu_genpy = genMother_py->at(part) - genParticle_py->at(part);
            neu_genpz = genMother_pz->at(part) - genParticle_pz->at(part);
            
              /*
                cout<<"Event: "<<i<<" Index:"<<part
                <<" gen trans mass: "<<W_genTransMass
                <<endl;
              */
        }
        /*
          if(abs(genMother_pdgId->at(part)) == PDGZ){
          Z_genMass = genMother_mass->at(part);
          Z_genEta = genMother_eta->at(part);
          Z_genPt = genMother_pt->at(part);
          if(check && Z_flavor == PDGELEC && abs(genParticle_pdgId->at(part)) == PDGELEC){
          cout<<"Gen PDG:"<<genParticle_pdgId->at(part)
          <<" E: "<<genParticle_energy->at(part)
          <<" px: "<<genParticle_px->at(part)
          <<" py: "<<genParticle_py->at(part)
          <<" pz: "<<genParticle_pz->at(part)
          <<endl;
          for(int e=0; e<electron_pt->size(); ++e){
          cout<<"Electron "<<e
          <<" E: "<<electron_energy->at(e)
          <<" px: "<<electron_px->at(e)
          <<" py: "<<electron_py->at(e)
          <<" pz: "<<electron_pz->at(e)
          <<endl;
          }
          }else if(check && Z_flavor == PDGELEC){
          cout<<"Other particle: "<<genParticle_pdgId->at(part)
          <<" E: "<<genParticle_energy->at(part)
          <<" px: "<<genParticle_px->at(part)
          <<" py: "<<genParticle_py->at(part)
          <<" pz: "<<genParticle_pz->at(part)
          <<endl;
          }
          }
        */
    }
    
    
    //cout<<"-------------"<<endl;
    
    if(false && W_transMass < 10){
        cout<<" W_transMass: "<<W_transMass
            <<" W_transMass (gen): "<<W_genTransMass<<endl
            <<" W_pt: "<<W_pt
            <<" W_pt (gen): "<<W_genpt<<endl
            <<" W_eta: "<<W_eta
            <<" W_eta (gen): "<<W_geneta<<endl
            <<" W_phi: "<<W_phi
            <<" W_phi (gen): "<<W_genphi<<endl
            /*
              <<" lep_pt: "<<lep_pt
              <<" lep_pt (gen): "<<lep_genpt<<endl
              <<" lep_phi: "<<lep_phi
              <<" lep_phi (gen): "<<lep_genphi<<endl
              */
            <<" neu_px: "<<neu_px
            <<" neu_px (gen): "<<neu_genpx<<endl
            <<" neu_py: "<<neu_py
            <<" neu_py (gen): "<<neu_genpy<<endl
            <<" neu_pz: "<<neu_pz
            <<" neu_pz (gen): "<<neu_genpz<<endl
            
            <<" W_pz (gen): "<<W_genpz<<endl;
        cout<<" lep_pz (gen): "<<lep_genpz<<endl;
        cout<<" lep_pz: ";
        if(Z_flavor == PDGELEC) cout<<electron_pz->at(W_leptonIndex);
        if(Z_flavor == PDGMUON) cout<<muon_pz->at(W_leptonIndex);
        cout<<endl;
        cout<<" neu minpz"<<W_neutrino_pzMinPz<<endl 
            <<" neu maxpz"<<W_neutrino_pzMaxPz<<endl 
            <<endl;
    }

    return 0;
}

//-----------------------------------------------------------
void ExecuteCheck()
{
//-----------------------------------------------------------
  if (debugme)cout<<"Master macro to execute analysis"<<endl;

  //lumiPb now defined in ExecuteCheck.h
  cout<<"Using integrated luminosity of "<<lumiPb<<" inv pb"<<endl;
 
  //name of file where to write all histograms
  TFile *fout = new TFile("Check_analysis.root","recreate");
 
  //containers to
  //include signal and background files

  //keep account of events
  string outfile("event_counts_Check.txt");
  ofstream out(outfile.c_str());
  if(!out) { 
    cout << "Cannot open file " << outfile << endl; 
    abort();
  } 
  
  //go for the analysis now and separate 
  //nicely into background/signal-type directories
  //the results will be written under respective directories
  //Add as many as you need:

  vector<InputFile> Wprime300_files;
  UseSample("Wprime300",Wprime300_files, fout, out);
  vector<InputFile> Wprime400_files;
  UseSample("Wprime400",Wprime400_files, fout, out);
  vector<InputFile> Wprime500_files;
  UseSample("Wprime500",Wprime500_files, fout, out);
  vector<InputFile> Wprime600_files;
  UseSample("Wprime600",Wprime600_files, fout, out);
  vector<InputFile> Wprime700_files;
  UseSample("Wprime700",Wprime700_files, fout, out);
  vector<InputFile> Wprime800_files;
  UseSample("Wprime800",Wprime800_files, fout, out);
  vector<InputFile> Wprime900_files;
  UseSample("Wprime900",Wprime900_files, fout, out);
  
  vector<InputFile> TC225_files;
  UseSample("TC225", TC225_files, fout, out);
  vector<InputFile> TC300_files;
  UseSample("TC300", TC300_files, fout, out);
  vector<InputFile> TC400_files;
  UseSample("TC400", TC400_files, fout, out);
  vector<InputFile> TC500_files;
  UseSample("TC500", TC500_files, fout, out);
  
  vector<InputFile> WZ_files;
  UseSample("WZ",WZ_files, fout, out);
  vector<InputFile> TTbar_files;
  UseSample("TTbar",TTbar_files, fout, out);
  vector<InputFile> TTbar2l_files;
  UseSample("TTbar2l",TTbar2l_files, fout, out);
  vector<InputFile> ZZ_files;
  UseSample("ZZ",ZZ_files, fout, out);
  vector<InputFile> ZZ4l_files;
  UseSample("ZZ4l",ZZ4l_files, fout, out);
  vector<InputFile> ZGamma_files;
  UseSample("ZGamma",ZGamma_files, fout, out);

  vector<InputFile> ZJetsBinned_files;
  UseSample("ZJetsBinned",ZJetsBinned_files, fout, out);
  vector<InputFile> ZeeJets_files;
  UseSample("ZeeJets",ZeeJets_files, fout, out);
  vector<InputFile> ZmumuJets_files;
  UseSample("ZmumuJets",ZmumuJets_files, fout, out);
  vector<InputFile> ZeeJetsPowheg_files;
  UseSample("ZeeJetsPowheg",ZeeJetsPowheg_files, fout, out);
  vector<InputFile> ZmumuJetsPowheg_files;
  UseSample("ZmumuJetsPowheg",ZmumuJetsPowheg_files, fout, out);
  vector<InputFile> ZllJetsMadgraph_files;
  UseSample("ZllJetsMadgraph",ZllJetsMadgraph_files, fout, out);

  vector<InputFile> WenuJets_files;
  UseSample("WenuJets",WenuJets_files, fout, out);
  vector<InputFile> WmunuJets_files;
  UseSample("WmunuJets",WmunuJets_files, fout, out);
  vector<InputFile> WlnuJetsMadgraph_files;
  UseSample("WlnuJetsMadgraph",WlnuJetsMadgraph_files, fout, out);
  
  vector<InputFile> Run2010_files;
  UseSample("Run2010",Run2010_files, fout, out);
  
  //vector<InputFile> Interesting_files;
  //UseSample("interesting",Interesting_files, fout, out);

  out.close(); 
  fout->Close();

}//ExecuteCheck

