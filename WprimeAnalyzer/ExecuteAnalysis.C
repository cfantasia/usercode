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

#define ExecuteAnalysis_cxx
#include <ExecuteAnalysis.h>

//--------------------------------------------------------------
void Declare_Histos()
{
//--------------------------------------------------------------

  if (debugme) cout<<"Declare histos"<<endl;

  //InvMass histos
  int WZinvMin = 0;
  int WZinvMax = 1500;
  int WZbin = 150;
  for(int i=0; i<NCuts; ++i){
      string name = "hWZInvMass_" + Cut_Name[i];
      string title = "Reconstructed WZ Invariant Mass (After "+Cut_Name[i]+" Cut);m_{WZ} (GeV);";
      hWZInvMass[i] = new TH1F(name.c_str(),title.c_str(),WZbin,WZinvMin,WZinvMax);
  }
 
  //TransMass histos
  int WZtransMin = 0;
  int WZtransMax = 1500;
  int WZtransbin = 100;
  for(int i=0; i<NCuts; ++i){
      string name = "hWZTransMass_" + Cut_Name[i];
      string title = "Reconstructed WZ Transverse Mass (After "+Cut_Name[i]+" Cut);m_{WZ} (GeV);";
      hWZTransMass[i] = new TH1F(name.c_str(),title.c_str(),WZtransbin,WZtransMin,WZtransMax);
  }
 
  //Ht Histos
  float HtMin = 0.;
  float HtMax = 1000.;
  int Htbin = 50;
    for(int i=0; i<NCuts; ++i){
      string name = "hHt_" + Cut_Name[i];
      string title = "H_{T} (After "+Cut_Name[i]+" Cut);Lepton Pt Sum: H_{T} (GeV);";
      hHt[i] = new TH1F(name.c_str(),title.c_str(),Htbin,HtMin,HtMax);
  }
 
  //Wpt Histos
  float WptMin = 0.;
  float WptMax = 400.;
  int Wptbin = 80;
  for(int i=0; i<NCuts; ++i){
      string name = "hWpt_" + Cut_Name[i];
      string title = "p_{T}^{W} (After "+Cut_Name[i]+" Cut);p_{T} of W (GeV);";
      hWpt[i] = new TH1F(name.c_str(),title.c_str(),Wptbin,WptMin,WptMax);
  }

  //Zpt Histos
  float ZptMin = 0.;
  float ZptMax = 400.;
  int Zptbin = 80;
  for(int i=0; i<NCuts; ++i){
      string name = "hZpt_" + Cut_Name[i];
      string title = "p_{T}^{Z} (After "+Cut_Name[i]+" Cut);p_{T} of Z (GeV);";
      hZpt[i] = new TH1F(name.c_str(),title.c_str(),Zptbin,ZptMin,ZptMax);
  }
  
  //MET Histos
  float METMin = 0.;
  float METMax = 500.;
  int METbin = 100;
  for(int i=0; i<NCuts; ++i){
      string name = "hMET_" + Cut_Name[i];
      string title = "MET (After "+Cut_Name[i]+" Cut);MET (GeV);";
      hMET[i] = new TH1F(name.c_str(),title.c_str(),METbin,METMin,METMax);
  }

  //Z Mass Histos
  float ZmassMin = 50.;
  float ZmassMax = 130.;
  int Zmassbin = 80;
  for(int i=0; i<NCuts; ++i){
      string name = "hZmass_" + Cut_Name[i];
      string title = "Reconstructed Mass of Z (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
      hZmass[i] = new TH1F(name.c_str(),title.c_str(),Zmassbin,ZmassMin,ZmassMax);
  }

  //Zee Mass Histos
  for(int i=0; i<NCuts; ++i){
      string name = "hZeemass_" + Cut_Name[i];
      string title = "Reconstructed Mass of Zee (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
      hZeemass[i] = new TH1F(name.c_str(),title.c_str(),Zmassbin,ZmassMin,ZmassMax);
  }

  //Zmumu Mass Histos
  for(int i=0; i<NCuts; ++i){
      string name = "hZmumumass_" + Cut_Name[i];
      string title = "Reconstructed Mass of Zmumu (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
      hZmumumass[i] = new TH1F(name.c_str(),title.c_str(),Zmassbin,ZmassMin,ZmassMax);
  }

  //W Trans Mass Histos
  float WTransmassMin = 0.;
  float WTransmassMax = 100.;
  int WTransmassbin = 10;
  for(int i=0; i<NCuts; ++i){
      string name = "hWTransmass_" + Cut_Name[i];
      string title = "Reconstructed Transmass of W (After "+Cut_Name[i]+" Cut);m_{T W}^{Reco} (GeV);";
      hWTransmass[i] = new TH1F(name.c_str(),title.c_str(),WTransmassbin,WTransmassMin,WTransmassMax);
  }

  //Wenu Trans Mass Histos
  float WenuTransmassMin = 0.;
  float WenuTransmassMax = 100.;
  int WenuTransmassbin = 10;
  for(int i=0; i<NCuts; ++i){
      string name = "hWenuTransmass_" + Cut_Name[i];
      string title = "Reconstructed Transmass of Wenu (After "+Cut_Name[i]+" Cut);m_{T W}^{Reco} (GeV);";
      hWenuTransmass[i] = new TH1F(name.c_str(),title.c_str(),WenuTransmassbin,WenuTransmassMin,WenuTransmassMax);
  }

  //Wmunu Trans Mass Histos
  float WmunuTransmassMin = 0.;
  float WmunuTransmassMax = 100.;
  int WmunuTransmassbin = 10;
  for(int i=0; i<NCuts; ++i){
      string name = "hWmunuTransmass_" + Cut_Name[i];
      string title = "Reconstructed Transmass of Wmunu (After "+Cut_Name[i]+" Cut);m_{T W}^{Reco} (GeV);";
      hWmunuTransmass[i] = new TH1F(name.c_str(),title.c_str(),WmunuTransmassbin,WmunuTransmassMin,WmunuTransmassMax);
  }

//////////////
  //Electron Properties
  int ElecPtbin = 500;
  float ElecPtMin = 0.;
  float ElecPtMax = 500.;
  for(int i=0; i<NCuts; ++i){
      string name = "hElecPt_" + Cut_Name[i];
      string title = "Electron Pt (After "+Cut_Name[i]+" Cut);Pt;";
      hElecPt[i] = new TH1F(name.c_str(),title.c_str(),ElecPtbin,ElecPtMin,ElecPtMax);
  }

  int ElecEtbin = 500;
  float ElecEtMin = 0.;
  float ElecEtMax = 500.;
  for(int i=0; i<NCuts; ++i){
      string name = "hElecEt_" + Cut_Name[i];
      string title = "Electron Et (After "+Cut_Name[i]+" Cut);Et;";
      hElecEt[i] = new TH1F(name.c_str(),title.c_str(),ElecEtbin,ElecEtMin,ElecEtMax);
  }

  int ElecdEtabin = 1000;
  float ElecdEtaMin = 0.;
  float ElecdEtaMax = 1.;
  for(int i=0; i<NCuts; ++i){
      string name = "hElecDEta_" + Cut_Name[i];
      string title = "Electron Delta Eta (After "+Cut_Name[i]+" Cut);dEta;";
      hElecdEta[i] = new TH1F(name.c_str(),title.c_str(),ElecdEtabin,ElecdEtaMin,ElecdEtaMax);
  }

  int ElecdPhibin = 1000;
  float ElecdPhiMin = 0.;
  float ElecdPhiMax = 1.;
  for(int i=0; i<NCuts; ++i){
      string name = "hElecDPhi_" + Cut_Name[i];
      string title = "Electron Delta Phi (After "+Cut_Name[i]+" Cut);dPhi;";
      hElecdPhi[i] = new TH1F(name.c_str(),title.c_str(),ElecdPhibin,ElecdPhiMin,ElecdPhiMax);
  }

  int ElecSigmannbin = 1000;
  float ElecSigmannMin = 0.;
  float ElecSigmannMax = 1.;
  for(int i=0; i<NCuts; ++i){
      string name = "hElecSigmaEtaEta_" + Cut_Name[i];
      string title = "Electron Sigma Eta Eta (After "+Cut_Name[i]+" Cut);Sigma Eta Eta;";
      hElecSigmann[i] = new TH1F(name.c_str(),title.c_str(),ElecSigmannbin,ElecSigmannMin,ElecSigmannMax);
  }

  int ElecEPbin = 1000;
  float ElecEPMin = 0.;
  float ElecEPMax = 2.;
  for(int i=0; i<NCuts; ++i){
      string name = "hElecEP_" + Cut_Name[i];
      string title = "Electron E Over P (After "+Cut_Name[i]+" Cut);E/P;";
      hElecEP[i] = new TH1F(name.c_str(),title.c_str(),ElecEPbin,ElecEPMin,ElecEPMax);
  }

  int ElecHEbin = 2000;
  float ElecHEMin = 0.;
  float ElecHEMax = 2.;
  for(int i=0; i<NCuts; ++i){
      string name = "hElecHOverE_" + Cut_Name[i];
      string title = "Electron H over E (After "+Cut_Name[i]+" Cut);H/E;";
      hElecHE[i] = new TH1F(name.c_str(),title.c_str(),ElecHEbin,ElecHEMin,ElecHEMax);
  }

  int ElecTrkRelIsobin = 1000;
  float ElecTrkRelIsoMin = 0.;
  float ElecTrkRelIsoMax = 2.;
  for(int i=0; i<NCuts; ++i){
      string name = "hElecTrkRelIso_" + Cut_Name[i];
      string title = "Electron Relative Track Iso (After "+Cut_Name[i]+" Cut);TrkRelIso;";
      hElecTrkRelIso[i] = new TH1F(name.c_str(),title.c_str(),ElecTrkRelIsobin,ElecTrkRelIsoMin,ElecTrkRelIsoMax);
  }

  int ElecECalRelIsobin = 1000;
  float ElecECalRelIsoMin = 0.;
  float ElecECalRelIsoMax = 2.;
  for(int i=0; i<NCuts; ++i){
      string name = "hElecECalRelIso_" + Cut_Name[i];
      string title = "Electron Relative ECal Iso (After "+Cut_Name[i]+" Cut);ECalRelIso;";
      hElecECalRelIso[i] = new TH1F(name.c_str(),title.c_str(),ElecECalRelIsobin,ElecECalRelIsoMin,ElecECalRelIsoMax);
  }

  int ElecHCalRelIsobin = 1000;
  float ElecHCalRelIsoMin = 0.;
  float ElecHCalRelIsoMax = 2.;
  for(int i=0; i<NCuts; ++i){
      string name = "hElecHCalRelIso_" + Cut_Name[i];
      string title = "Electron Relative HCal Iso (After "+Cut_Name[i]+" Cut);HCalRelIso;";
      hElecHCalRelIso[i] = new TH1F(name.c_str(),title.c_str(),ElecHCalRelIsobin,ElecHCalRelIsoMin,ElecHCalRelIsoMax);
  }

  //Muon Histograms
  int MuonPtbin = 500;
  float MuonPtMin = 0.;
  float MuonPtMax = 500.;
  for(int i=0; i<NCuts; ++i){
      string name = "hMuonPt_" + Cut_Name[i];
      string title = "Muon Pt (After "+Cut_Name[i]+" Cut);Pt;";
      hMuonPt[i] = new TH1F(name.c_str(),title.c_str(),MuonPtbin,MuonPtMin,MuonPtMax);
  }

  int MuonDxybin = 500;
  float MuonDxyMin = 0.;
  float MuonDxyMax = 1.;
  for(int i=0; i<NCuts; ++i){
      string name = "hMuonDxy_" + Cut_Name[i];
      string title = "Muon Dxy (After "+Cut_Name[i]+" Cut);Dxy;";
      hMuonDxy[i] = new TH1F(name.c_str(),title.c_str(),MuonDxybin,MuonDxyMin,MuonDxyMax);
  }

  int MuonNormChi2bin = 50;
  float MuonNormChi2Min = 0.;
  float MuonNormChi2Max = 50.;
  for(int i=0; i<NCuts; ++i){
      string name = "hMuonNormChi2_" + Cut_Name[i];
      string title = "Muon NormChi2 (After "+Cut_Name[i]+" Cut);NormChi2;";
      hMuonNormChi2[i] = new TH1F(name.c_str(),title.c_str(),MuonNormChi2bin,MuonNormChi2Min,MuonNormChi2Max);
  }

  int MuonNPixbin = 50;
  float MuonNPixMin = 0.;
  float MuonNPixMax = 50.;
  for(int i=0; i<NCuts; ++i){
      string name = "hMuonNPix_" + Cut_Name[i];
      string title = "Muon NPix (After "+Cut_Name[i]+" Cut);NPix;";
      hMuonNPix[i] = new TH1F(name.c_str(),title.c_str(),MuonNPixbin,MuonNPixMin,MuonNPixMax);
  }

  int MuonNTrkbin = 50;
  float MuonNTrkMin = 0.;
  float MuonNTrkMax = 50.;
  for(int i=0; i<NCuts; ++i){
      string name = "hMuonNTrk_" + Cut_Name[i];
      string title = "Muon NTrk (After "+Cut_Name[i]+" Cut);NTrk;";
      hMuonNTrk[i] = new TH1F(name.c_str(),title.c_str(),MuonNTrkbin,MuonNTrkMin,MuonNTrkMax);
  }

  for(int i=0; i<NCuts; ++i){
      string name = "hMuonRelIso_" + Cut_Name[i];
      string title = "Muon Rel Iso (After "+Cut_Name[i]+" Cut);Rel Iso;";
      hMuonRelIso[i] = new TH1F(name.c_str(),title.c_str(),100,0,0.2);
  }

  int MuonStationbin = 50;
  float MuonStationMin = 0.;
  float MuonStationMax = 50.;
  for(int i=0; i<NCuts; ++i){
      string name = "hMuonStation_" + Cut_Name[i];
      string title = "Muon Station (After "+Cut_Name[i]+" Cut);Station;";
      hMuonStation[i] = new TH1F(name.c_str(),title.c_str(),MuonStationbin,MuonStationMin,MuonStationMax);
  }

  int MuonSipbin = 1000;
  float MuonSipMin = 0.;
  float MuonSipMax = 50.;
  for(int i=0; i<NCuts; ++i){
      string name = "hMuonSip_" + Cut_Name[i];
      string title = "Muon Sip (After "+Cut_Name[i]+" Cut);Sip;";
      hMuonSip[i] = new TH1F(name.c_str(),title.c_str(),MuonSipbin,MuonSipMin,MuonSipMax);
  }

///Eff Plots///////
  string title = "Expected # of Events / " + convertFloatToStr(lumiPb) + " pb^{-1}";
  hNumEvts = new TH1F("hNumEvts",title.c_str(),NCuts,0,NCuts);
  hEffRel = new TH1F("hEffRel","Relative Efficiency",NCuts,0,NCuts);
  hEffAbs = new TH1F("hEffAbs","Absolute Efficiency",NCuts,0,NCuts);
  for(int i=0; i<NCuts; ++i) hNumEvts->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());
  for(int i=0; i<NCuts; ++i) hEffRel ->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());
  for(int i=0; i<NCuts; ++i) hEffAbs ->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());

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
    hMET[index]->Fill(pfMet_et, weight);
    hZmass[index]->Fill(Z_mass,weight);
    if      (Z_flavor == PDGELEC){
        hZeemass[index]->Fill(Z_mass,weight);
    }else if (Z_flavor == PDGMUON){
        hZmumumass[index]->Fill(Z_mass,weight);
    }
    if(W_transMass>0){
        hWTransmass[index]->Fill(W_transMass,weight);
        if      (W_flavor == PDGELEC) hWenuTransmass[index]->Fill(W_transMass,weight);
        else if (W_flavor == PDGMUON) hWmunuTransmass[index]->Fill(W_transMass,weight);
    }

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
    
}//Fill_Histos

//------------------------------------------------------------------------
void saveHistos(TFile * fout, string dir)
{
//------------------------------------------------------------------------
  if (debugme) cout<<"Save Histos....."<<endl;
  fout->cd(); 
  fout->mkdir(dir.c_str()); 
  fout->cd(dir.c_str());

  for(int i = 0; i != NCuts; ++i){
      hWZInvMass[i]->Write();   
      hWZTransMass[i]->Write();
      hHt[i]->Write();
      hWpt[i]->Write();
      hZpt[i]->Write();
      hMET[i]->Write();
      hZmass[i]->Write();
      hZeemass[i]->Write();
      hZmumumass[i]->Write();
      hWTransmass[i]->Write();
      hWenuTransmass[i]->Write();
      hWmunuTransmass[i]->Write();
      
      hElecPt[i]->Write();
      hElecEt[i]->Write();
      hElecdEta[i]->Write();
      hElecdPhi[i]->Write();
      hElecSigmann[i]->Write();
      hElecEP[i]->Write();
      hElecHE[i]->Write();
      hElecTrkRelIso[i]->Write();
      hElecECalRelIso[i]->Write();
      hElecHCalRelIso[i]->Write();
    
      hMuonPt[i]->Write();
      hMuonDxy[i]->Write();
      hMuonNormChi2[i]->Write();
      hMuonNPix[i]->Write();
      hMuonNTrk[i]->Write();
      hMuonRelIso[i]->Write();
      hMuonStation[i]->Write();
      hMuonSip[i]->Write();
  }
  hNumEvts->Write();
  hEffRel->Write();
  hEffAbs->Write();
  
  return;

}//saveHistos

//Writing results to a txt file
//--------------------------------------------------------------------------
void printSummary(ofstream & out, const string& dir, const float& Nthe_evt,
                  const float& Nexp_evt, float Nexp_evt_cut[]) 
{ 
//------------------------------------------------------------------------
    if(debugme) cout<<"Writing results to a txt file"<<endl;

    out<<"$$$$$$$$$$$$$$$$$$$$$$$ Type of sample: "<<dir<<endl;
    out << " Total # of Theoretical expected events = " << Nthe_evt << endl;
    out << " Total # of expected events = " << Nexp_evt << endl;
        
    for(int i = 0; i < NCuts; ++i){
        
        out <<"Cut # "<<i<<"("<<Cut_Name[i]<<"): expected evts = " << Nexp_evt_cut[i];
	hNumEvts->Fill(i,Nexp_evt_cut[i]);

        //calculate efficiencies
        float eff, deff;
        if(i == 0){
            getEff(eff, deff, Nexp_evt_cut[i], Nexp_evt);
	    hEffRel->Fill(i,eff*100);	
	}else{
            getEff(eff, deff, Nexp_evt_cut[i], Nexp_evt_cut[i-1]);
	    hEffRel->Fill(i,eff*100);
	}
        out << ", Relative eff = "<<eff*100 << " +/- " << deff*100 << "%";
        
	getEff(eff, deff, Nexp_evt_cut[i], Nexp_evt);
        hEffAbs->Fill(i,eff*100);
	out << ", Absolute eff = "<< eff*100 << " +/- " << deff*100 << "%"
             << endl;
        
        //to do: put these results in a file
        
    } // loop over different cuts
    
    
}//printSummary

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

      if (debugme) cout<<"Processing event "<<i<<endl;

      //an index to indicate current cut number
      int cut_index = 0;//Incremented in Tabulate_Me
      
      vector<int> idxs;
      vector<int> inEC;

      //cuts: These need to be ordered the same as Cut_Name in header file

      //No Cuts
      Tabulate_Me(Num_surv_cut,cut_index,weight); 
      
      if(!PassTriggersCut()) continue; //Cory
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      if(!PassValidWandZCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      if(!PassNumberOfZsCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);
      
      /////////General Electron Cuts////////////////
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
      
      ////Boson Cuts/////////////
      if(!PassZDecayCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      if(!PassWDecayCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);      

      PrintEvent();
      ////Other Cuts/////////////
      if(!PassHtCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      if(!PassZptCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      if(!PassWptCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      if(!PassMETCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight);

      //After All Cuts
      Tabulate_Me(Num_surv_cut,cut_index,weight); 
      PrintEvent();
      
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
  
  printSummary(out, dir, Nthe_evt, Nexp_evt, Nexp_evt_cut);
  saveHistos(fout, dir);
  
}//Get_Distributions

//-----------------------------------------------------------
void ExecuteAnalysis()
{
//-----------------------------------------------------------
  top_level_dir = "/uscms_data/d2/fantasia/CMSSW_3_8_4_patch2/src/RunWZ/";
  
  if (debugme)cout<<"Master macro to execute analysis"<<endl;

  //lumiPb now defined in ExecuteAnalysis.h
  cout<<"Using integrated luminosity of "<<lumiPb<<" inv pb"<<endl;
 
  //name of file where to write all histograms
  TFile *fout = new TFile("Wprime_analysis.root","recreate");
 
  //containers to
  //include signal and background files

  vector<InputFile> Interesting_files;

  vector<InputFile> EGSep17_files;
  vector<InputFile> MuSep17_files;
  vector<InputFile> ElectronPrompt_files;
  vector<InputFile> MuPromptReco_files;

  //keep account of events
  string outfile("event_counts.txt");
  ofstream out(outfile.c_str());
  if(!out) { 
    cout << "Cannot open file " << outfile << endl; 
    abort();
  } 
  
  //go for the analysis now and separate 
  //nicely into background/signal-type directories
  //the results will be written under respective directories
  //Add as many as you need:

  //UseSample("wprime400",wprime400_files, fout, out);
  //UseSample("wprime500",wprime500_files, fout, out);
  //UseSample("wprime600",wprime600_files, fout, out);
  //UseSample("wprime700",wprime700_files, fout, out);
  //UseSample("wprime800",wprime800_files, fout, out);
  //UseSample("wprime900",wprime900_files, fout, out);
  //UseSample("TC400", TC400_files, fout, out);
  /*
  UseSample("wz",wz_files, fout, out);
  UseSample("ttbar",ttbar_files, fout, out);
  UseSample("ttbarfast",ttbarfast_files, fout, out);
  UseSample("zz",zz_files, fout, out);
  UseSample("zgamma",zgamma_files, fout, out);
  UseSample("zjets",zjets_files, fout, out);
  UseSample("wjets",wjets_files, fout, out);
  */
  //UseSample("interesting",Interesting_files, fout, out);

  UseSample("EGSep17ReReco",EGSep17_files, fout, out);
  UseSample("MuSep17ReReco",MuSep17_files, fout, out);
  UseSample("ElectronPromptReco",ElectronPrompt_files, fout, out);
  UseSample("MuPromptReco",MuPromptReco_files, fout, out);

  out.close(); 
  fout->Close();

}//ExecuteAnalysis

