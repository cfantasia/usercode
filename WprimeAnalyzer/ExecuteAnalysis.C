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
  float Min, Max, binWidth;
  int Nbin;
  string name, title;
  
  for(int i=0; i<NCuts; ++i){
    //InvMass histos
    Min = 0;
    Max = 1100;
    Nbin = 110;
    binWidth = (Max-Min)/Nbin;
    name = "hWZInvMass_" + Cut_Name[i];
    title = "Reconstructed WZ Invariant Mass (After "+Cut_Name[i]+" Cut);m_{WZ} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hWZInvMass[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
  
    //TransMass histos
    Min = 0;
    Max = 1100;
    Nbin = 110;
    binWidth = (Max-Min)/Nbin;
    name = "hWZTransMass_" + Cut_Name[i];
    title = "Reconstructed WZ Transverse Mass (After "+Cut_Name[i]+" Cut);m_{WZ} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hWZTransMass[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
 
    //Ht Histos
    Min = 0.;
    Max = 1000.;
    Nbin = 50;
    binWidth = (Max-Min)/Nbin;
    name = "hHt_" + Cut_Name[i];
    title = "H_{T} (After "+Cut_Name[i]+" Cut);Lepton Pt Sum: H_{T} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hHt[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
 
    //Wpt Histos
    Min = 0.;
    Max = 400.;
    Nbin = 80;
    binWidth = (Max-Min)/Nbin;
    name = "hWpt_" + Cut_Name[i];
    title = "p_{T}^{W} (After "+Cut_Name[i]+" Cut);p_{T} of W (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hWpt[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    //Zpt Histos
    Min = 0.;
    Max = 400.;
    Nbin = 80;
    binWidth = (Max-Min)/Nbin;
    name = "hZpt_" + Cut_Name[i];
    title = "p_{T}^{Z} (After "+Cut_Name[i]+" Cut);p_{T} of Z (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hZpt[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
  
    //MET Histos
    Min = 0.;
    Max = 500.;
    Nbin = 50;
    binWidth = (Max-Min)/Nbin;
    name = "hMET_" + Cut_Name[i];
    title = "MET (After "+Cut_Name[i]+" Cut);MET (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hMET[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    //Z Mass Histos
    Min = 50.;
    Max = 130.;
    Nbin = 40;
    binWidth = (Max-Min)/Nbin;
    name = "hZmass_" + Cut_Name[i];
    title = "Reconstructed Mass of Z (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hZmass[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    //Zee Mass Histos
    name = "hZeemass_" + Cut_Name[i];
    title = "Reconstructed Mass of Zee (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hZeemass[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
  
    //Zmumu Mass Histos
    name = "hZmumumass_" + Cut_Name[i];
    title = "Reconstructed Mass of Zmumu (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hZmumumass[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
  
    //W Trans Mass Histos
    Min = 0.;
    Max = 100.;
    Nbin = 10;
    binWidth = (Max-Min)/Nbin;
    name = "hWTransmass_" + Cut_Name[i];
    title = "Reconstructed Transmass of W (After "+Cut_Name[i]+" Cut);m_{T W}^{Reco} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hWTransmass[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
  
    //Wenu Trans Mass Histos
    name = "hWenuTransmass_" + Cut_Name[i];
    title = "Reconstructed Transmass of Wenu (After "+Cut_Name[i]+" Cut);m_{T W}^{Reco} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hWenuTransmass[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    //Wmunu Trans Mass Histos
    name = "hWmunuTransmass_" + Cut_Name[i];
    title = "Reconstructed Transmass of Wmunu (After "+Cut_Name[i]+" Cut);m_{T W}^{Reco} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hWmunuTransmass[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
  
    //Leading Lepton Pt
    Min = 0.;
    Max = 300.;
    Nbin = 30;
    binWidth = (Max-Min)/Nbin;
    name = "hLeadPt_" + Cut_Name[i];
    title = "Leading Lepton Pt (After "+Cut_Name[i]+" Cut);P_{T} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hLeadPt[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    name = "hLeadElecPt_" + Cut_Name[i];
    title = "Leading Electron Pt (After "+Cut_Name[i]+" Cut);P_{T} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hLeadElecPt[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    name = "hLeadMuonPt_" + Cut_Name[i];
    title = "Leading Muon Pt (After "+Cut_Name[i]+" Cut);P_{T} (GeV);";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hLeadMuonPt[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    //Electron Properties
    Nbin = 50;
    Min = 0.;
    Max = 500.;
    binWidth = (Max-Min)/Nbin;
    name = "hElecPt_" + Cut_Name[i];
    title = "Electron Pt (After "+Cut_Name[i]+" Cut);Pt;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hElecPt[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 50;
    Min = 0.;
    Max = 500.;
    binWidth = (Max-Min)/Nbin;
    name = "hElecEt_" + Cut_Name[i];
    title = "Electron Et (After "+Cut_Name[i]+" Cut);Et;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hElecEt[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
  
    Nbin = 100;
    Min = 0.;
    Max = 1.;
    binWidth = (Max-Min)/Nbin;
    name = "hElecDEta_" + Cut_Name[i];
    title = "Electron Delta Eta (After "+Cut_Name[i]+" Cut);dEta;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hElecdEta[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
  
    Nbin = 100;
    Min = 0.;
    Max = 1.;
    binWidth = (Max-Min)/Nbin;
    name = "hElecDPhi_" + Cut_Name[i];
    title = "Electron Delta Phi (After "+Cut_Name[i]+" Cut);dPhi;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hElecdPhi[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 100;
    Min = 0.;
    Max = 1.;
    binWidth = (Max-Min)/Nbin;
    name = "hElecSigmaEtaEta_" + Cut_Name[i];
    title = "Electron Sigma Eta Eta (After "+Cut_Name[i]+" Cut);Sigma Eta Eta;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hElecSigmann[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 100;
    Min = 0.;
    Max = 2.;
    binWidth = (Max-Min)/Nbin;
    name = "hElecEP_" + Cut_Name[i];
    title = "Electron E Over P (After "+Cut_Name[i]+" Cut);E/P;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hElecEP[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 200;
    Min = 0.;
    Max = 2.;
    binWidth = (Max-Min)/Nbin;
    name = "hElecHOverE_" + Cut_Name[i];
    title = "Electron H over E (After "+Cut_Name[i]+" Cut);H/E;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hElecHE[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 100;
    Min = 0.;
    Max = 2.;
    binWidth = (Max-Min)/Nbin;
    name = "hElecTrkRelIso_" + Cut_Name[i];
    title = "Electron Relative Track Iso (After "+Cut_Name[i]+" Cut);TrkRelIso;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hElecTrkRelIso[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 100;
    Min = 0.;
    Max = 2.;
    binWidth = (Max-Min)/Nbin;
    name = "hElecECalRelIso_" + Cut_Name[i];
    title = "Electron Relative ECal Iso (After "+Cut_Name[i]+" Cut);ECalRelIso;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hElecECalRelIso[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 100;
    Min = 0.;
    Max = 2.;
    binWidth = (Max-Min)/Nbin;
    name = "hElecHCalRelIso_" + Cut_Name[i];
    title = "Electron Relative HCal Iso (After "+Cut_Name[i]+" Cut);HCalRelIso;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hElecHCalRelIso[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    //Muon Histograms
    Nbin = 50;
    Min = 0.;
    Max = 500.;
    binWidth = (Max-Min)/Nbin;
    name = "hMuonPt_" + Cut_Name[i];
    title = "Muon Pt (After "+Cut_Name[i]+" Cut);Pt;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hMuonPt[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 100;
    Min = 0.;
    Max = 1.;
    binWidth = (Max-Min)/Nbin;
    name = "hMuonDxy_" + Cut_Name[i];
    title = "Muon Dxy (After "+Cut_Name[i]+" Cut);Dxy;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hMuonDxy[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 50;
    Min = 0.;
    Max = 50.;
    binWidth = (Max-Min)/Nbin;
    name = "hMuonNormChi2_" + Cut_Name[i];
    title = "Muon NormChi2 (After "+Cut_Name[i]+" Cut);NormChi2;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hMuonNormChi2[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
  
    Nbin = 50;
    Min = 0.;
    Max = 50.;
    binWidth = (Max-Min)/Nbin;
    name = "hMuonNPix_" + Cut_Name[i];
    title = "Muon NPix (After "+Cut_Name[i]+" Cut);NPix;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hMuonNPix[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
    
    Nbin = 50;
    Min = 0.;
    Max = 50.;
    binWidth = (Max-Min)/Nbin;
    name = "hMuonNTrk_" + Cut_Name[i];
    title = "Muon NTrk (After "+Cut_Name[i]+" Cut);NTrk;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hMuonNTrk[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 100;
    Min = 0;
    Max = 1.;
    binWidth = (Max-Min)/Nbin;
    name = "hMuonRelIso_" + Cut_Name[i];
    title = "Muon Rel Iso (After "+Cut_Name[i]+" Cut);Rel Iso;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hMuonRelIso[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 50;
    Min = 0.;
    Max = 50.;
    binWidth = (Max-Min)/Nbin;
    name = "hMuonStation_" + Cut_Name[i];
    title = "Muon Station (After "+Cut_Name[i]+" Cut);Station;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hMuonStation[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);

    Nbin = 100;
    Min = 0.;
    Max = 50.;
    binWidth = (Max-Min)/Nbin;
    name = "hMuonSip_" + Cut_Name[i];
    title = "Muon Sip (After "+Cut_Name[i]+" Cut);Sip;";
    title += "Evts/" + convertFloatToStr(binWidth) + " GeV/" + convertFloatToStr(lumiPb) + " pb^{-1}";
    hMuonSip[i] = new TH1F(name.c_str(),title.c_str(),Nbin,Min,Max);
  }  

  ///Eff Plots///////
  title = "Expected # of Events / " + convertFloatToStr(lumiPb) + " pb^{-1}";
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
    hLeadPt[i]->Write();
    hLeadElecPt[i]->Write();
    hLeadMuonPt[i]->Write();
      
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
      LeadPt = CalcLeadPt();
      LeadElecPt = CalcLeadPt(PDGELEC);
      LeadMuonPt = CalcLeadPt(PDGMUON);

      if (debugme) cout<<"Processing event "<<i<<endl;

      //an index to indicate current cut number
      int cut_index = 0;//Incremented in Tabulate_Me
      
      vector<int> idxs;
      vector<int> inEC;

      //cuts: These need to be ordered the same as Cut_Name in header file

      //No Cuts
      Tabulate_Me(Num_surv_cut,cut_index,weight); 
      
      //if(!PassTriggersCut()) continue; //Cory
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
      //cout<<" Passed All Cuts!!!\n\n";
      //PrintEvent();
      //cout<<" ------------------\n";
      
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
  //vector<InputFile> TTbarfast_files;
  //UseSample("TTbarfast",TTbarfast_files, fout, out);
  vector<InputFile> ZZ_files;
  UseSample("ZZ",ZZ_files, fout, out);
  vector<InputFile> ZGamma_files;
  UseSample("ZGamma",ZGamma_files, fout, out);
  vector<InputFile> ZeeJets_files;
  UseSample("ZeeJets",ZeeJets_files, fout, out);
  vector<InputFile> ZmumuJets_files;
  UseSample("ZmumuJets",ZmumuJets_files, fout, out);
  vector<InputFile> WenuJets_files;
  UseSample("WenuJets",WenuJets_files, fout, out);
  vector<InputFile> WmunuJets_files;
  UseSample("WmunuJets",WmunuJets_files, fout, out);
    
  vector<InputFile> Run2010_Nov4ReReco_files;
  UseSample("Run2010-Nov4ReReco",Run2010_Nov4ReReco_files, fout, out);

  //vector<InputFile> Interesting_files;
  //UseSample("interesting",Interesting_files, fout, out);

  out.close(); 
  fout->Close();

}//ExecuteAnalysis

