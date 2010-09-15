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
void getEff(float & eff, float & deff, float Num, float Denom)
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
string convertIntToStr(int number)
{
//--------------------------------------------------------------
   stringstream ss;
   ss << number;
   return ss.str();
}

//--------------------------------------------------------------
string convertFloatToStr(float number)
{
//--------------------------------------------------------------
   stringstream ss;
   ss << number;
   return ss.str();
}



//--------------------------------------------------------------
double deltaPhi(double phi1, double phi2)
{
//--------------------------------------------------------------

  double phi=fabs(phi1-phi2);
  return (phi <= PI) ? phi : TWOPI - phi;
}

//--------------------------------------------------------------
double deltaEta(double eta1, double eta2)
{
//--------------------------------------------------------------
    double eta = fabs(eta1 - eta2);
    return eta;
}

TH1F*
Declare_Histo(string name, string title, int nbins, float min, float max){
    TH1F* hist = new TH1F(name.c_str(),title.c_str(),nbins,min,max);
    return hist;
}

//--------------------------------------------------------------
void Declare_Histos()
{
//--------------------------------------------------------------

  if (debugme) cout<<"Declare histos"<<endl;

  //InvMass histos
  int WZinvMin = 0;
  int WZinvMax = 1500;
  int WZbin = 150;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWZInvMass_" + Cut_Name[i];
      string title = "Reconstructed WZ Invariant Mass (After "+Cut_Name[i]+" Cut);m_{WZ} (GeV);";
      hWZInvMass[i] = new TH1F(name.c_str(),title.c_str(),WZbin,WZinvMin,WZinvMax);
  }
 
  //TransMass histos
  int WZtransMin = 0;
  int WZtransMax = 1500;
  int WZtransbin = 100;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWZTransMass_" + Cut_Name[i];
      string title = "Reconstructed WZ Transverse Mass (After "+Cut_Name[i]+" Cut);m_{WZ} (GeV);";
      hWZTransMass[i] = new TH1F(name.c_str(),title.c_str(),WZtransbin,WZtransMin,WZtransMax);
  }
 
  //Ht Histos
  float HtMin = 0.;
  float HtMax = 1000.;
  int Htbin = 50;
    for(int i=0; i<Num_histo_sets; ++i){
      string name = "hHt_" + Cut_Name[i];
      string title = "H_{T} (After "+Cut_Name[i]+" Cut);Lepton Pt Sum: H_{T} (GeV);";
      hHt[i] = new TH1F(name.c_str(),title.c_str(),Htbin,HtMin,HtMax);
  }
 
  //Wpt Histos
  float WptMin = 0.;
  float WptMax = 400.;
  int Wptbin = 80;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWpt_" + Cut_Name[i];
      string title = "p_{T}^{W} (After "+Cut_Name[i]+" Cut);p_{T} of W (GeV);";
      hWpt[i] = new TH1F(name.c_str(),title.c_str(),Wptbin,WptMin,WptMax);
  }

  //Zpt Histos
  float ZptMin = 0.;
  float ZptMax = 400.;
  int Zptbin = 80;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hZpt_" + Cut_Name[i];
      string title = "p_{T}^{Z} (After "+Cut_Name[i]+" Cut);p_{T} of Z (GeV);";
      hZpt[i] = new TH1F(name.c_str(),title.c_str(),Zptbin,ZptMin,ZptMax);
  }

  //Gen InvMass histos
  int GenWZinvMin = 0;
  int GenWZinvMax = 1000;
  int GenWZbin = 500;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hGenWZInvMass_" + Cut_Name[i];
      string title = "Generated WZ Invariant Mass (After "+Cut_Name[i]+" Cut);m_{WZ}^{Gen} (GeV);";
      hGenWZInvMass[i] = new TH1F(name.c_str(),title.c_str(),GenWZbin,GenWZinvMin,GenWZinvMax);
  }
  
  //MET Histos
  float METMin = 0.;
  float METMax = 500.;
  int METbin = 100;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hMET_" + Cut_Name[i];
      string title = "MET (After "+Cut_Name[i]+" Cut);MET (GeV);";
      hMET[i] = new TH1F(name.c_str(),title.c_str(),METbin,METMin,METMax);
  }

  //METDiff Histos
  float METDiffMin = -500.;
  float METDiffMax = 500.;
  int METDiffbin = 200;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hMETDiff_" + Cut_Name[i];
      string title = "METDiff (After "+Cut_Name[i]+" Cut);METDiff (GeV);";
      hMETDiff[i] = new TH1F(name.c_str(),title.c_str(),METDiffbin,METDiffMin,METDiffMax);
  }

  //GenDP Histos
  float GenDPMin = 7.;
  float GenDPMax = 7.;
  int GenDPbin = 1400;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hGenDP_" + Cut_Name[i];
      string title = "GenDP (After "+Cut_Name[i]+" Cut);GenDP (GeV);";
      hGenDP[i] = new TH1F(name.c_str(),title.c_str(),GenDPbin,GenDPMin,GenDPMax);
  }

  //RecoDP Histos
  float RecoDPMin = 7.;
  float RecoDPMax = 7.;
  int RecoDPbin = 1400;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hRecoDP_" + Cut_Name[i];
      string title = "RecoDP (After "+Cut_Name[i]+" Cut);RecoDP (GeV);";
      hRecoDP[i] = new TH1F(name.c_str(),title.c_str(),RecoDPbin,RecoDPMin,RecoDPMax);
  }

  //DiffDP Histos
  float DiffDPMin = 7.;
  float DiffDPMax = 7.;
  int DiffDPbin = 140;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hDiffDP_" + Cut_Name[i];
      string title = "DiffDP (After "+Cut_Name[i]+" Cut);DiffDP (GeV);";
      hDiffDP[i] = new TH1F(name.c_str(),title.c_str(),DiffDPbin,DiffDPMin,DiffDPMax);
  }

  //Z Mass Histos
  float ZmassMin = 50.;
  float ZmassMax = 130.;
  int Zmassbin = 80;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hZmass_" + Cut_Name[i];
      string title = "Reconstructed Mass of Z (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
      hZmass[i] = new TH1F(name.c_str(),title.c_str(),Zmassbin,ZmassMin,ZmassMax);
  }

  //Zee Mass Histos
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hZeemass_" + Cut_Name[i];
      string title = "Reconstructed Mass of Zee (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
      hZeemass[i] = new TH1F(name.c_str(),title.c_str(),Zmassbin,ZmassMin,ZmassMax);
  }

  //ZeeTT Mass Histos
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hZeemassTT_" + Cut_Name[i];
      string title = "Reconstructed Mass of ZeeTT (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
      hZeemassTT[i] = new TH1F(name.c_str(),title.c_str(),Zmassbin,ZmassMin,ZmassMax);
  }

  //ZeeTF Mass Histos
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hZeemassTF_" + Cut_Name[i];
      string title = "Reconstructed Mass of ZeeTF (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
      hZeemassTF[i] = new TH1F(name.c_str(),title.c_str(),Zmassbin,ZmassMin,ZmassMax);
  }

  //Zmumu Mass Histos
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hZmumumass_" + Cut_Name[i];
      string title = "Reconstructed Mass of Zmumu (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
      hZmumumass[i] = new TH1F(name.c_str(),title.c_str(),Zmassbin,ZmassMin,ZmassMax);
  }

  //ZmumuTT Mass Histos
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hZmumumassTT_" + Cut_Name[i];
      string title = "Reconstructed Mass of ZmumuTT (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
      hZmumumassTT[i] = new TH1F(name.c_str(),title.c_str(),Zmassbin,ZmassMin,ZmassMax);
  }

  //ZmumuTF Mass Histos
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hZmumumassTF_" + Cut_Name[i];
      string title = "Reconstructed Mass of ZmumuTF (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
      hZmumumassTF[i] = new TH1F(name.c_str(),title.c_str(),Zmassbin,ZmassMin,ZmassMax);
  }

  //Gen Z Mass Histos
  float GenZmassMin = 40.;
  float GenZmassMax = 140.;
  int GenZmassbin = 100;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hGenZmass_" + Cut_Name[i];
      string title = "Reconstructed Mass of GenZ (After "+Cut_Name[i]+" Cut);m_{GenZ}^{Reco} (GeV);";
      hGenZmass[i] = new TH1F(name.c_str(),title.c_str(),GenZmassbin,GenZmassMin,GenZmassMax);
  }

  //GenW Trans Mass Histos
  float GenWTransmassMin = 0.;
  float GenWTransmassMax = 100.;
  int GenWTransmassbin = 10;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hGenWTransmass_" + Cut_Name[i];
      string title = "Generated Transmass of W (After "+Cut_Name[i]+" Cut);m_{W}^{Gen} (GeV);";
      hGenWTransmass[i] = new TH1F(name.c_str(),title.c_str(),GenWTransmassbin,GenWTransmassMin,GenWTransmassMax);
  }

  //GenW Trans Mass DiffHistos
  float GenWTransmassDiffMin = -100;
  float GenWTransmassDiffMax = 100.;
  int GenWTransmassDiffbin = 40;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hGenWTransmassDiff_" + Cut_Name[i];
      string title = "Generated Transmass Diff of W (After "+Cut_Name[i]+" Cut);m_{W}^{Gen} (GeV);";
      hGenWTransmassDiff[i] = new TH1F(name.c_str(),title.c_str(),GenWTransmassDiffbin,GenWTransmassDiffMin,GenWTransmassDiffMax);
  }

  //W Trans Mass Histos
  float WTransmassMin = 0.;
  float WTransmassMax = 100.;
  int WTransmassbin = 10;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWTransmass_" + Cut_Name[i];
      string title = "Reconstructed Transmass of W (After "+Cut_Name[i]+" Cut);m_{T W}^{Reco} (GeV);";
      hWTransmass[i] = new TH1F(name.c_str(),title.c_str(),WTransmassbin,WTransmassMin,WTransmassMax);
  }

  //Wenu Trans Mass Histos
  float WenuTransmassMin = 0.;
  float WenuTransmassMax = 100.;
  int WenuTransmassbin = 10;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWenuTransmass_" + Cut_Name[i];
      string title = "Reconstructed Transmass of Wenu (After "+Cut_Name[i]+" Cut);m_{T W}^{Reco} (GeV);";
      hWenuTransmass[i] = new TH1F(name.c_str(),title.c_str(),WenuTransmassbin,WenuTransmassMin,WenuTransmassMax);
  }

  //Wmunu Trans Mass Histos
  float WmunuTransmassMin = 0.;
  float WmunuTransmassMax = 100.;
  int WmunuTransmassbin = 10;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWmunuTransmass_" + Cut_Name[i];
      string title = "Reconstructed Transmass of Wmunu (After "+Cut_Name[i]+" Cut);m_{T W}^{Reco} (GeV);";
      hWmunuTransmass[i] = new TH1F(name.c_str(),title.c_str(),WmunuTransmassbin,WmunuTransmassMin,WmunuTransmassMax);
  }

  //W lep pt diffElectron Properties
  int ElecPtDiffbin = 100;
  float ElecPtDiffMin = -200.;
  float ElecPtDiffMax = 200.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecPtDiff_" + Cut_Name[i];
      string title = "Electron PtDiff (After "+Cut_Name[i]+" Cut);PtDiff;";
      hElecPtDiff[i] = new TH1F(name.c_str(),title.c_str(),ElecPtDiffbin,ElecPtDiffMin,ElecPtDiffMax);
  }

  //Muon Properties
  int MuonPtDiffbin = 100;
  float MuonPtDiffMin = -200.;
  float MuonPtDiffMax = 200.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hMuonPtDiff_" + Cut_Name[i];
      string title = "Muon Pt (After "+Cut_Name[i]+" Cut);Pt;";
      hMuonPtDiff[i] = new TH1F(name.c_str(),title.c_str(),MuonPtDiffbin,MuonPtDiffMin,MuonPtDiffMax);
  }



//////////////
  //Electron Properties
  int ElecPtbin = 500;
  float ElecPtMin = 0.;
  float ElecPtMax = 500.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecPt_" + Cut_Name[i];
      string title = "Electron Pt (After "+Cut_Name[i]+" Cut);Pt;";
      hElecPt[i] = new TH1F(name.c_str(),title.c_str(),ElecPtbin,ElecPtMin,ElecPtMax);
  }

  int ElecEtbin = 500;
  float ElecEtMin = 0.;
  float ElecEtMax = 500.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecEt_" + Cut_Name[i];
      string title = "Electron Et (After "+Cut_Name[i]+" Cut);Et;";
      hElecEt[i] = new TH1F(name.c_str(),title.c_str(),ElecEtbin,ElecEtMin,ElecEtMax);
  }

  int ElecdEtabin = 1000;
  float ElecdEtaMin = 0.;
  float ElecdEtaMax = 1.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecDEta_" + Cut_Name[i];
      string title = "Electron Delta Eta (After "+Cut_Name[i]+" Cut);dEta;";
      hElecdEta[i] = new TH1F(name.c_str(),title.c_str(),ElecdEtabin,ElecdEtaMin,ElecdEtaMax);
  }

  int ElecdPhibin = 1000;
  float ElecdPhiMin = 0.;
  float ElecdPhiMax = 1.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecDPhi_" + Cut_Name[i];
      string title = "Electron Delta Phi (After "+Cut_Name[i]+" Cut);dPhi;";
      hElecdPhi[i] = new TH1F(name.c_str(),title.c_str(),ElecdPhibin,ElecdPhiMin,ElecdPhiMax);
  }

  int ElecSigmannbin = 1000;
  float ElecSigmannMin = 0.;
  float ElecSigmannMax = 1.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecSigmaEtaEta_" + Cut_Name[i];
      string title = "Electron Sigma Eta Eta (After "+Cut_Name[i]+" Cut);Sigma Eta Eta;";
      hElecSigmann[i] = new TH1F(name.c_str(),title.c_str(),ElecSigmannbin,ElecSigmannMin,ElecSigmannMax);
  }

  int ElecEPbin = 1000;
  float ElecEPMin = 0.;
  float ElecEPMax = 2.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecEP_" + Cut_Name[i];
      string title = "Electron E Over P (After "+Cut_Name[i]+" Cut);E/P;";
      hElecEP[i] = new TH1F(name.c_str(),title.c_str(),ElecEPbin,ElecEPMin,ElecEPMax);
  }

  int ElecHEbin = 2000;
  float ElecHEMin = 0.;
  float ElecHEMax = 2.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecHOverE_" + Cut_Name[i];
      string title = "Electron H over E (After "+Cut_Name[i]+" Cut);H/E;";
      hElecHE[i] = new TH1F(name.c_str(),title.c_str(),ElecHEbin,ElecHEMin,ElecHEMax);
  }
/*
  int ElecRelCaloIsobin = 100;
  float ElecRelCaloIsoMin = 0.;
  float ElecRelCaloIsoMax = 1.;

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecRelCaloIso_" + Cut_Name[i];
      string title = "Electron Relative CaloIso (After "+Cut_Name[i]+" Cut);RelCalIso;";
      hElecRelCaloIso[i] = new TH1F(name.c_str(),title.c_str(),ElecRelCaloIsobin,ElecRelCaloIsoMin,ElecRelCaloIsoMax);
  }
*/  
  int ElecTrkRelIsobin = 1000;
  float ElecTrkRelIsoMin = 0.;
  float ElecTrkRelIsoMax = 2.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecTrkRelIso_" + Cut_Name[i];
      string title = "Electron Relative Track Iso (After "+Cut_Name[i]+" Cut);TrkRelIso;";
      hElecTrkRelIso[i] = new TH1F(name.c_str(),title.c_str(),ElecTrkRelIsobin,ElecTrkRelIsoMin,ElecTrkRelIsoMax);
  }

  int ElecECalRelIsobin = 1000;
  float ElecECalRelIsoMin = 0.;
  float ElecECalRelIsoMax = 2.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecECalRelIso_" + Cut_Name[i];
      string title = "Electron Relative ECal Iso (After "+Cut_Name[i]+" Cut);ECalRelIso;";
      hElecECalRelIso[i] = new TH1F(name.c_str(),title.c_str(),ElecECalRelIsobin,ElecECalRelIsoMin,ElecECalRelIsoMax);
  }

  int ElecHCalRelIsobin = 1000;
  float ElecHCalRelIsoMin = 0.;
  float ElecHCalRelIsoMax = 2.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecHCalRelIso_" + Cut_Name[i];
      string title = "Electron Relative HCal Iso (After "+Cut_Name[i]+" Cut);HCalRelIso;";
      hElecHCalRelIso[i] = new TH1F(name.c_str(),title.c_str(),ElecHCalRelIsobin,ElecHCalRelIsoMin,ElecHCalRelIsoMax);
  }
//////////
  //Muon Histograms
  int MuonPtbin = 500;
  float MuonPtMin = 0.;
  float MuonPtMax = 500.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hMuonPt_" + Cut_Name[i];
      string title = "Muon Pt (After "+Cut_Name[i]+" Cut);Pt;";
      hMuonPt[i] = new TH1F(name.c_str(),title.c_str(),MuonPtbin,MuonPtMin,MuonPtMax);
  }

  int MuonDxybin = 500;
  float MuonDxyMin = 0.;
  float MuonDxyMax = 1.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hMuonDxy_" + Cut_Name[i];
      string title = "Muon Dxy (After "+Cut_Name[i]+" Cut);Dxy;";
      hMuonDxy[i] = new TH1F(name.c_str(),title.c_str(),MuonDxybin,MuonDxyMin,MuonDxyMax);
  }

  int MuonNormChi2bin = 50;
  float MuonNormChi2Min = 0.;
  float MuonNormChi2Max = 50.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hMuonNormChi2_" + Cut_Name[i];
      string title = "Muon NormChi2 (After "+Cut_Name[i]+" Cut);NormChi2;";
      hMuonNormChi2[i] = new TH1F(name.c_str(),title.c_str(),MuonNormChi2bin,MuonNormChi2Min,MuonNormChi2Max);
  }

  int MuonNPixbin = 50;
  float MuonNPixMin = 0.;
  float MuonNPixMax = 50.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hMuonNPix_" + Cut_Name[i];
      string title = "Muon NPix (After "+Cut_Name[i]+" Cut);NPix;";
      hMuonNPix[i] = new TH1F(name.c_str(),title.c_str(),MuonNPixbin,MuonNPixMin,MuonNPixMax);
  }

  int MuonNTrkbin = 50;
  float MuonNTrkMin = 0.;
  float MuonNTrkMax = 50.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hMuonNTrk_" + Cut_Name[i];
      string title = "Muon NTrk (After "+Cut_Name[i]+" Cut);NTrk;";
      hMuonNTrk[i] = new TH1F(name.c_str(),title.c_str(),MuonNTrkbin,MuonNTrkMin,MuonNTrkMax);
  }

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hMuonRelIso_" + Cut_Name[i];
      string title = "Muon Rel Iso (After "+Cut_Name[i]+" Cut);Rel Iso;";
      hMuonRelIso[i] = new TH1F(name.c_str(),title.c_str(),100,0,0.2);
  }

  int MuonStationbin = 50;
  float MuonStationMin = 0.;
  float MuonStationMax = 50.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hMuonStation_" + Cut_Name[i];
      string title = "Muon Station (After "+Cut_Name[i]+" Cut);Station;";
      hMuonStation[i] = new TH1F(name.c_str(),title.c_str(),MuonStationbin,MuonStationMin,MuonStationMax);
  }

  int MuonSipbin = 1000;
  float MuonSipMin = 0.;
  float MuonSipMax = 50.;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hMuonSip_" + Cut_Name[i];
      string title = "Muon Sip (After "+Cut_Name[i]+" Cut);Sip;";
      hMuonSip[i] = new TH1F(name.c_str(),title.c_str(),MuonSipbin,MuonSipMin,MuonSipMax);
  }

///W Reco Check Plots/////////////////
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWmass_" + Cut_Name[i];
      string title = "W Mass (After "+Cut_Name[i]+" Cut);M_{W};";
      hWmass[i] = new TH1F(name.c_str(),title.c_str(),100,0,100);
  }

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWDpt_" + Cut_Name[i];
      string title = "W Lepton Delta pt (After "+Cut_Name[i]+" Cut);Dpt;";
      hWDpt[i] = new TH1F(name.c_str(),title.c_str(),100,-100,100);
  }

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWDphi_" + Cut_Name[i];
      string title = "W Lepton Delta phi (After "+Cut_Name[i]+" Cut);Dphi;";
      hWDphi[i] = new TH1F(name.c_str(),title.c_str(),100,-4,4);
  }

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWDeta_" + Cut_Name[i];
      string title = "W Lepton Delta eta (After "+Cut_Name[i]+" Cut);Deta;";
      hWDeta[i] = new TH1F(name.c_str(),title.c_str(),100,0,10);
  }

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWDr_" + Cut_Name[i];
      string title = "W Lepton Delta R (After "+Cut_Name[i]+" Cut);DR;";
      hWDr[i] = new TH1F(name.c_str(),title.c_str(),1000,0,5);
  }



///Eff Plots///////
  string title = "Expected # of Events / " + convertFloatToStr(lumiPb) + " pb^{-1}";
  hNumEvts = new TH1F("hNumEvts",title.c_str(),Num_histo_sets,0,Num_histo_sets);
  hEffRel = new TH1F("hEffRel","Relative Efficiency",Num_histo_sets,0,Num_histo_sets);
  hEffAbs = new TH1F("hEffAbs","Absolute Efficiency",Num_histo_sets,0,Num_histo_sets);
  for(int i=0; i<Num_histo_sets; ++i) hNumEvts->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());
  for(int i=0; i<Num_histo_sets; ++i) hEffRel ->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());
  for(int i=0; i<Num_histo_sets; ++i) hEffAbs ->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());

  

}//Declare_Histos

void Declare_Lists()
{
//--------------------------------------------------------------

  if (debugme) cout<<"Declare lists"<<endl;

  for(int i=0; i<Num_histo_sets; ++i) cutlist[i] = new TEntryList(Cut_Name[i].c_str(),Cut_Name[i].c_str());

}//Declare_Lists


//See if particle(only Electron??) is in Barrel
//--------------------------------------------------------------
bool inBarrel(float eta)
{
    return (fabs(eta) < maxElecEtaBarrel);
    
}//InBarrel

bool inEndCap(float eta)
{
    float abs_eta = fabs(eta);
    return (abs_eta > minElecEtaEndcap && abs_eta < maxElecEta);
          
}//InEndCap


//Just a function to calculate DeltaR
//--------------------------------------------------------------
double deltaR(double eta1, double phi1, double eta2, double phi2)
{
//--------------------------------------------------------------
  double deta = eta1 - eta2;
  double dphi = deltaPhi(phi1, phi2);
  return sqrt(deta * deta + dphi * dphi);
}




//check if the input files are there
//----------------------------------------------------------
int Check_Files(unsigned Nfiles, vector<InputFile> & files)
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





//Recruit files that are numbered from a given sample
//----------------------------------------------------------
void RecruitOrderedFiles(vector<InputFile> & files, const int& Nfiles,
                         const int& filenum_low, const int& filenum_step,
                         const string& mask1, const string& mask2, 
                         const string& file_desc)
{
//-----------------------------------------------------------
    cout<<"Recruiting " << file_desc << " files."<<endl;
    if(Check_Files(Nfiles, files)) {
        cout<<"WARNING!!!!! No Files were found for "<<
            file_desc<<"sample"<<endl;
        return;
    }
    //Do I need to know if it is merged?? I guess, then don't use xsec
    if(Nfiles > 1){
        int filenum = filenum_low;
        for(int i = 0; i != Nfiles; ++i){
            filenum = filenum_low + i*filenum_step;
            files[i].pathname = top_level_dir + mask1 + 
                convertIntToStr(filenum) + mask2;
            files[i].description = file_desc;
            //cout<<files[i].pathname<<endl;
        }
    }
    else if (Nfiles == 1){
        files[0].pathname = top_level_dir + mask1;
        files[0].description = file_desc;
    }
    else {cout<<"Something went wrong with the files. Quiting..."
              <<endl; abort();}
    
  
}// --RecruitOrderedFiles

//Recruit files that are binned from a given sample
//----------------------------------------------------------
void RecruitBinnedFiles(vector<InputFile> & files, const int& Nfiles,
                        const vector<string>& dir, const vector<string>& bin,
                         const string& mask1,
                         const string& mask2, const string& file_desc)
{
//-----------------------------------------------------------
    cout<<"Recruiting " << file_desc << " files."<<endl;
    if(Check_Files(Nfiles, files)) {
        cout<<"WARNING!!!!! No Files were found for "<<
            file_desc<<"sample"<<endl;
        return;
    }

    int Ndirs = dir.size();
    int Nbins = bin.size();
    for(int i = 0; i != Ndirs; ++i){
        for(int j=0; j != Nbins; ++j){
            string filename = dir[i] + bin[j];
            files[i*Nbins + j].pathname = top_level_dir + mask1 + 
                filename + mask2;
            files[i*Nbins + j].description = file_desc;
            //cout<<files[i*bin.size() + j].pathname<<endl;
            //Cory: if more than 1 for each bin? Call RecruitOrderedFiles
        }
    }
    
  
}// --RecruitBinnedFiles



//load the input files from the top_level_dir
//-----------------------------------------------------------
void Load_Input_Files(string file_desc, 
                    vector<InputFile> & files, 
                    float lumiPb)
{
//-----------------------------------------------------------
  if (debugme)cout<<"Loading input Files...."<<endl;

  cout << "\n Processing " << file_desc<< " files " << endl << endl;

//   if(file_desc == "QCD")
//     {
//       const int NfilesQCD = 09;
//       Nfiles = NfilesQCD;
//       if(Check_Files(Nfiles, files))
// 	return;

//       string low[NfilesQCD]= 
// 	{"100", "150", "200", "300", "400", "600", "800", "1200", "1600"};
//       string high[NfilesQCD]=
// 	{"150", "200", "300", "400", "600", "800","1200", "1600", "up"};
  
//       for(int i = 0; i != Nfiles; ++i)
// 	{
// 	  files[i].pathname = top_level_dir + string("QCD_")+low[i]+string("_")+high[i]+string("_212_Ideal_Minv_ptGlobMu.root");
// 	}
      
//     } // QCD

  //switch between different sample cases and
  //recruit the files. 
  bool binned = false;
  float cross_sec = 0;
  int Nfiles = -1;
  if (!strcmp(file_desc.c_str(),"wprime400")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime400_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wprime500")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime500_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wprime600")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime600_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wprime700")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime700_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wprime800")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime800_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename, "",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wprime900")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime900_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename, "",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wz")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "WZ_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"ttbar")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "TTbar_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"ttbarfast")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "TTbarFast_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"zz")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "ZZ_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"zgamma")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "Zgamma_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"zjets")){
      vector<string> dirs;
      vector<string> bins;
      
      dirs.push_back("ZeejetsPt");
      dirs.push_back("ZmumujetsPt");
      
      bins.push_back("0to15");
      bins.push_back("15to20");
      bins.push_back("20to30");
      bins.push_back("30to50");
      bins.push_back("50to80");
      bins.push_back("80to120");
      bins.push_back("120to170");
      bins.push_back("170to230");
      bins.push_back("230to300");
      bins.push_back("300toInf");

      Nfiles = dirs.size()*bins.size();
      //float Zee_xsec[] = {4416,145.4,131.5,84.38,32.32,9.981,2.76 ,0.7241,0.1946,0.07539};
      //float Zmm_xsec[] = {4434,143.8,131.8,83.92,32.35,9.918,2.757,0.7226,0.193 ,0.07627};
      binned = true;
      for(int i=0; i!=Nfiles; ++i){
          files.push_back(InputFile());
      }

      RecruitBinnedFiles(files,Nfiles,dirs,bins,
                              "","_outputTree.root",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wjets")){
          Nfiles = 1;
          cross_sec = 24901.3;
          files.push_back(InputFile(cross_sec)); 
          const string filename = "Wjets_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"TC400")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "TC400_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"test")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "test_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"wmunu")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "Wmunu_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"wenu")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "Wenu_outputTree.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else cout<<"No samples were found with the name "<<file_desc<<endl;

  
  float Total_Nprod_evt = 0;
  
  //Loop over the files in order to get the correct tree
  //and the number of total events 
  for(int i = 0; i != Nfiles; ++i){ // loop over input files
      string pathname = files[i].pathname;
      TFile * file = TFile::Open(pathname.c_str());
      //TFile * file = new TFile(pathname.c_str());
      if(!(file->IsOpen()))	{
          cerr <<" *** Missing file: "<< pathname << " !!! "<<endl; 
          continue;
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
          const float cross_sec  = histWeight->GetBinContent(2);  //Cory: this doesn't give correct weight?
          delete histWeight;
          files[i].x_sect = cross_sec;
      }
  
      Total_Nprod_evt += files[i].Nprod_evt;
  }// loop over input files 1

  for(int i = 0; i != Nfiles; ++i){ // loop over input files 2
      if(!binned){
          files[i].weight = lumiPb*(files[i].x_sect)/(Total_Nprod_evt);
      }else{
          files[i].weight = lumiPb*(files[i].x_sect)/(files[i].Nprod_evt);
      }

      cout <<"Events produced in file = "<<files[i].Nprod_evt
           <<",  # of entries = "<< files[i].tree->GetEntries() 
           << ", x-sect = " << files[i].x_sect 
           << ", weight = " << files[i].weight << endl;
      
  } // loop over input files 2
  
  return;
}


//Set the branch addresses that we need for the analysis
//-----------------------------------------------------------
void Set_Branch_Addresses(TTree* WZtree)
{
//-----------------------------------------------------------
    if(debugme) cout<<"Setting Branch Addresses"<<endl;

    WZtree->SetBranchAddress("eventID", &eventID);

    WZtree->SetBranchAddress("HLT_Mu9", &HLT_Mu9);
    WZtree->SetBranchAddress("HLT_Photon10_L1R", &HLT_Photon10_L1R);

    WZtree->SetBranchAddress("W_flavor",&W_flavor);
    WZtree->SetBranchAddress("Z_flavor",&Z_flavor);
    WZtree->SetBranchAddress("W_pt",&W_pt);
    WZtree->SetBranchAddress("Z_pt",&Z_pt);
    WZtree->SetBranchAddress("Z_mass",&Z_mass);
    WZtree->SetBranchAddress("W_transMass",&W_transMass);
    WZtree->SetBranchAddress("W_phi",&W_phi);
    WZtree->SetBranchAddress("W_eta",&W_eta);
    WZtree->SetBranchAddress("numberOfZs",&numberOfZs);
    WZtree->SetBranchAddress("met_phi",&met_phi);
    WZtree->SetBranchAddress("met_et",&met_et);
    WZtree->SetBranchAddress("pfMet_et",&pfMet_et);
    WZtree->SetBranchAddress("WZ_invMassMinPz",&WZ_invMassMinPz);
    WZtree->SetBranchAddress("W_neutrino_pzMinPz",&W_neutrino_pzMinPz);
    WZtree->SetBranchAddress("W_neutrino_pzMaxPz",&W_neutrino_pzMaxPz);
    //WZtree->SetBranchAddress("WZ_invMassMaxPz",&WZ_invMassMaxPz);
    WZtree->SetBranchAddress("WZ_transMass",&WZ_transMass);
    WZtree->SetBranchAddress("W_leptonIndex",&W_leptonIndex);
    WZtree->SetBranchAddress("Z_leptonIndex1",&Z_leptonIndex1);
    WZtree->SetBranchAddress("Z_leptonIndex2",&Z_leptonIndex2);
    WZtree->SetBranchAddress("triggerBitMask", &triggerBitMask);

    //WZtree->SetBranchAddress("electron_ScEt",&electron_ScEt);
    //WZtree->SetBranchAddress("electron_ScEta",&electron_ScEta);
  
    WZtree->SetBranchAddress("electron_mass",&electron_mass);
    WZtree->SetBranchAddress("electron_phi",&electron_phi);
    WZtree->SetBranchAddress("electron_eta",&electron_eta);
    WZtree->SetBranchAddress("electron_ScEta",&electron_ScEta);
    WZtree->SetBranchAddress("electron_pt",&electron_pt);
    WZtree->SetBranchAddress("electron_energy",&electron_energy);
    WZtree->SetBranchAddress("electron_px",&electron_px);
    WZtree->SetBranchAddress("electron_py",&electron_py);
    WZtree->SetBranchAddress("electron_pz",&electron_pz);
    WZtree->SetBranchAddress("electron_ScEt",&electron_ScEt);
    WZtree->SetBranchAddress("electron_isoEtTrackerDr30", &electron_trackIso);
    WZtree->SetBranchAddress("electron_isoEtEcalDr30", &electron_ecaloIso);
    WZtree->SetBranchAddress("electron_isoEtHcalDr30", &electron_hcaloIso);
    WZtree->SetBranchAddress("electron_deltaEtaIn", &electron_deltaEtaIn);
    WZtree->SetBranchAddress("electron_deltaPhiIn", &electron_deltaPhiIn);
    WZtree->SetBranchAddress("electron_eOverP", &electron_eOverP);
    WZtree->SetBranchAddress("electron_hOverE", &electron_hOverE);
    WZtree->SetBranchAddress("electron_sigmaEtaEta", &electron_sigmaEtaEta);
 
    WZtree->SetBranchAddress("muon_energy",&muon_energy);
    WZtree->SetBranchAddress("muon_eta",&muon_eta);
    WZtree->SetBranchAddress("muon_phi",&muon_phi);
    WZtree->SetBranchAddress("muon_pt",&muon_pt);
    WZtree->SetBranchAddress("muon_px",&muon_px);
    WZtree->SetBranchAddress("muon_py",&muon_py);
    WZtree->SetBranchAddress("muon_pz",&muon_pz);
    WZtree->SetBranchAddress("muon_innerD0",&muon_innerD0);
    WZtree->SetBranchAddress("muon_innerD0Error",&muon_innerD0Error);
    WZtree->SetBranchAddress("muon_trackIso",&muon_trackIso);
    WZtree->SetBranchAddress("muon_caloIso",&muon_caloIso); 
    //WZtree->SetBranchAddress("muon_isoEtEcalDr30",&muon_ecaloIso); 
    //WZtree->SetBranchAddress("muon_isoEtHcalDr30",&muon_hcaloIso); 
    WZtree->SetBranchAddress("muon_fitType",&muon_fitType);
    WZtree->SetBranchAddress("muon_isGlobal",&muon_isGlobal);    
    WZtree->SetBranchAddress("muon_isTracker",&muon_isTracker);    
    WZtree->SetBranchAddress("muon_numGlobalMatches",&muon_numGlobalMatches);    
    WZtree->SetBranchAddress("muon_numValidMuonHits",&muon_numValidMuonHits);    
    WZtree->SetBranchAddress("muon_numPixelHits",&muon_globalNpixelHits);
    WZtree->SetBranchAddress("muon_numTrackerHits",&muon_globalNtrackerHits);
    WZtree->SetBranchAddress("muon_numStripHits",&muon_globalNstripHits);
    WZtree->SetBranchAddress("muon_globalChi2",&muon_globalChi2);
    WZtree->SetBranchAddress("muon_globalNdof",&muon_globalNdof);
    WZtree->SetBranchAddress("muon_globalD0",&muon_globalD0);
    WZtree->SetBranchAddress("muon_globalD0Error",&muon_globalD0Error);
    
    WZtree->SetBranchAddress("metGen_et", &genmet_et);
    WZtree->SetBranchAddress("metGen_phi", &genmet_phi);

    WZtree->SetBranchAddress("genMother_pdgId", &genMother_pdgId);
    WZtree->SetBranchAddress("genParticle_pdgId", &genParticle_pdgId);

    WZtree->SetBranchAddress("genMother_energy", &genMother_energy);
    WZtree->SetBranchAddress("genMother_et", &genMother_et);
    WZtree->SetBranchAddress("genMother_eta", &genMother_eta);
    WZtree->SetBranchAddress("genMother_mass", &genMother_mass);
    WZtree->SetBranchAddress("genMother_phi", &genMother_phi);
    WZtree->SetBranchAddress("genMother_pt", &genMother_pt);
    WZtree->SetBranchAddress("genMother_px", &genMother_px);
    WZtree->SetBranchAddress("genMother_py", &genMother_py);
    WZtree->SetBranchAddress("genMother_pz", &genMother_pz);
    WZtree->SetBranchAddress("genParticle_energy", &genParticle_energy);
    WZtree->SetBranchAddress("genParticle_et", &genParticle_et);
    WZtree->SetBranchAddress("genParticle_eta", &genParticle_eta);
    WZtree->SetBranchAddress("genParticle_mass", &genParticle_mass);
    WZtree->SetBranchAddress("genParticle_phi", &genParticle_phi);
    WZtree->SetBranchAddress("genParticle_pt", &genParticle_pt);
    WZtree->SetBranchAddress("genParticle_px", &genParticle_px);
    WZtree->SetBranchAddress("genParticle_py", &genParticle_py);
    WZtree->SetBranchAddress("genParticle_pz", &genParticle_pz);


    WZtree->SetBranchAddress("electronGenMother_pdgId", &electronGenMother_pdgId);
    WZtree->SetBranchAddress("electronGenMother_energy", &electronGenMother_energy);
    WZtree->SetBranchAddress("electronGenMother_px", &electronGenMother_px);
    WZtree->SetBranchAddress("electronGenMother_py", &electronGenMother_py);
    WZtree->SetBranchAddress("electronGenMother_pz", &electronGenMother_pz);
    
    WZtree->SetBranchAddress("muonGenMother_pdgId", &muonGenMother_pdgId);
    WZtree->SetBranchAddress("muonGenMother_energy", &muonGenMother_energy);
    WZtree->SetBranchAddress("muonGenMother_px", &muonGenMother_px);
    WZtree->SetBranchAddress("muonGenMother_py", &muonGenMother_py);
    WZtree->SetBranchAddress("muonGenMother_pz", &muonGenMother_pz);
}//Set_Branch_Addresses







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
    if      (Z_flavor == 11){
        hZeemass[index]->Fill(Z_mass,weight);
        if(TT) hZeemassTT[index]->Fill(Z_mass,weight);
        if(TF) hZeemassTF[index]->Fill(Z_mass,weight);
    }else if (Z_flavor == 13){
        hZmumumass[index]->Fill(Z_mass,weight);
        if(TT) hZmumumassTT[index]->Fill(Z_mass,weight);
        if(TF) hZmumumassTF[index]->Fill(Z_mass,weight);
    }
    hGenZmass[index]->Fill(Z_genMass,weight);
    hWmass[index]->Fill(W_mass,weight);
    hGenWTransmass[index]->Fill(W_genTransMass,weight);
    if(W_transMass>0){
        hGenWTransmassDiff[index]->Fill(W_genTransMass-W_transMass,weight);
        hWTransmass[index]->Fill(W_transMass,weight);
        if      (W_flavor == 11) hWenuTransmass[index]->Fill(W_transMass,weight);
        else if (W_flavor == 13) hWmunuTransmass[index]->Fill(W_transMass,weight);
    }
    if     (W_flavor == 11) hElecPtDiff[index]->Fill(WlepGenPt - electron_pt->at(W_leptonIndex),weight);
    else if(W_flavor == 13) hMuonPtDiff[index]->Fill(WlepGenPt - muon_pt->at(W_leptonIndex), weight);


    vector<int> idxs;
    if(Z_flavor == PDGELEC){//Only write W electrons
        //idxs.push_back(Z_leptonIndex1);
        //idxs.push_back(Z_leptonIndex2);
    }
    if(W_flavor == PDGELEC && Z_flavor == PDGMUON 
       && inEndCap(electron_ScEta->at(W_leptonIndex))){
        idxs.push_back(W_leptonIndex);
    }
    for(size_t i=0; i<idxs.size(); ++i){
        hElecPt[index]->Fill(electron_pt->at(idxs[i]),weight);
        hElecEt[index]->Fill(electron_ScEt->at(idxs[i]),weight);
        hElecdEta[index]->Fill(electron_deltaEtaIn->at(idxs[i]),weight);
        hElecdPhi[index]->Fill(electron_deltaPhiIn->at(idxs[i]),weight);
        hElecSigmann[index]->Fill(electron_sigmaEtaEta->at(idxs[i]),weight);
        hElecEP[index]->Fill(electron_eOverP->at(idxs[i]),weight);
        hElecHE[index]->Fill(electron_hOverE->at(idxs[i]),weight);
        //hElecRelCaloIso[index]->Fill(electron_caloIso->at(idxs[i])/electron_pt->at(idxs[i]),weight);
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





//------------------------------------------------------------------------
void saveHistos(TFile * fout, string dir)
{
//------------------------------------------------------------------------
  if (debugme) cout<<"Save Histos....."<<endl;
  fout->cd(); 
  fout->mkdir(dir.c_str()); 
  fout->cd(dir.c_str());

  for(int i = 0; i != Num_histo_sets; ++i){
      hWZInvMass[i]->Write();   
      hWZTransMass[i]->Write();
      hHt[i]->Write();
      hWpt[i]->Write();
      hZpt[i]->Write();
      hGenWZInvMass[i]->Write();
      hMET[i]->Write();
      hMETDiff[i]->Write();
      hGenDP[i]->Write();
      hRecoDP[i]->Write();
      hDiffDP[i]->Write();
      hZmass[i]->Write();
      hZeemass[i]->Write();
      hZeemassTT[i]->Write();
      hZeemassTF[i]->Write();
      hZmumumass[i]->Write();
      hZmumumassTT[i]->Write();
      hZmumumassTF[i]->Write();
      hGenZmass[i]->Write();
      hWmass[i]->Write();
      hGenWTransmass[i]->Write();
      hGenWTransmassDiff[i]->Write();
      hWTransmass[i]->Write();
      hWenuTransmass[i]->Write();
      hWmunuTransmass[i]->Write();
      
      hElecPtDiff[i]->Write();
      hMuonPtDiff[i]->Write();


      hElecPt[i]->Write();
      hElecEt[i]->Write();
      hElecdEta[i]->Write();
      hElecdPhi[i]->Write();
      hElecSigmann[i]->Write();
      hElecEP[i]->Write();
      hElecHE[i]->Write();
      //hElecRelCaloIso[i]->Write();
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

      hWDpt[i]->Write();
      hWDphi[i]->Write();
      hWDeta[i]->Write();
      hWDr[i]->Write();

      cutlist[i]->Write();
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
        
    for(int i = 0; i < Num_histo_sets; ++i){
        
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






//Tabulate results after the cut has been passed
//-----------------------------------------------------------
void Tabulate_Me(int Num_surv_cut[], int& cut_index, 
		 const float& weight, const int& evtnum)
{
//-----------------------------------------------------------
    if(debugme) cout<<"Tabulating results for cut_index = "
                    <<cut_index<<endl;

    //increase the number of events passing the cuts
    ++Num_surv_cut[cut_index];
    //fill the histograms
    Fill_Histos(cut_index,weight);
    
    cutlist[cut_index]->Enter(evtnum);

    //since the event has passed the cut,
    //increase the cut_index for the next cut
    ++cut_index;
    if(debugme) cout<<"cut_index is now = "<<cut_index<<endl;

}//Tabulate_Me







//Get different types of distribution
//-----------------------------------------------------------
void Get_Distributions(vector<InputFile>& files, 
                       TFile *fout, string dir, ofstream & out)
{
//-----------------------------------------------------------
  if (debugme) cout<<"Get Distributions....."<<endl;
  
  
  Declare_Histos();
  Declare_Lists();

  int Nfiles = files.size();

  //initialize counters for expected (already weighted) 
  //number of events
  //total, and after each cut.
  float Nthe_evt = 0;
  float Nexp_evt = 0;
  float Nexp_evt_cut[Num_histo_sets] = {0};
  
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
    int Num_surv_cut[Num_histo_sets] = {0};
    
    
    //Loop over events:
    //The ides is to keep each cut as a separate entity 
    //so they can be better handled
    for(int i = 0; i != nevents; ++i){//event loop

      WZtree->GetEntry(i);
      ////Calculate Important Quantities for each event
      Ht = Calc_Ht();
      WZ_genMass = Calc_GenWZInvMass();

      TT = TF = false;
      if(Z_flavor){
          bool tight1 = PassTightCut(Z_leptonIndex1);
          bool tight2 = PassTightCut(Z_leptonIndex2);
          //cout<<"tight1: "<<tight1<<" tight2: "<<tight2<<endl;
          TT = tight1 && tight2;
          TF = (tight1 && !tight2) || (!tight1 && tight2);
      }

      if     (W_flavor == 11) recodp = deltaPhi(electron_phi->at(W_leptonIndex),met_phi);
      else if(W_flavor == 13) recodp = deltaPhi(muon_phi->at(W_leptonIndex),met_phi);
      else                    recodp = -999;
      
      if     (W_flavor == 11 && W_neutrino_pzMinPz){
          float nu_energy = sqrt(met_et*met_et +
                                 W_neutrino_pzMinPz*W_neutrino_pzMinPz);
          float e = electron_energy->at(W_leptonIndex)+nu_energy;
          float px = electron_px->at(W_leptonIndex)+met_et*cos(met_phi);
          float py = electron_py->at(W_leptonIndex)+met_et*sin(met_phi);
          float pz = electron_pz->at(W_leptonIndex)+W_neutrino_pzMinPz;
          W_mass = sqrt(e*e - px*px - py*py - pz*pz);
      }else if(W_flavor == 13 && W_neutrino_pzMinPz){
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
      bool check = false;
      /*
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

              if      (W_flavor == 11){
                  WDpt = genParticle_pt->at(part) - electron_pt->at(W_leptonIndex);
                  WDphi = genParticle_phi->at(part);//deltaPhi(genParticle_phi->at(part), electron_phi->at(W_leptonIndex));
                  WDeta = deltaEta(genParticle_eta->at(part), electron_eta->at(W_leptonIndex));
                  WDr = sqrt(WDphi*WDphi + WDeta*WDeta);
                  //cout<<"gen: "<<genParticle_phi->at(part)<<" phi: "<<electron_phi->at(W_leptonIndex)<<endl
                  //    <<"gen: "<<genParticle_eta->at(part)<<" reco: "<<electron_eta->at(W_leptonIndex)<<endl;
              }else if(W_flavor == 13){
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
              if(check && Z_flavor == 11 && abs(genParticle_pdgId->at(part)) == 11){
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
              }else if(check && Z_flavor == 11){
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

      //////////////////////
      if (debugme) cout<<"Processing event "<<i<<endl;

      //an index to indicate current cut number
      int cut_index = 0;//Incremented in Tabulate_Me
      
      vector<int> idxs;
      vector<int> inEC;


      //cuts: These need to be ordered the same as Cut_Name in header file
      Tabulate_Me(Num_surv_cut,cut_index,weight,i); //No Cuts
      
      if(!PassTriggersCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);
      
      //These are used to look at cut eff.
      //if(Z_flavor != 11 || W_flavor != 13) continue;
      //if(Z_flavor != 13 || W_flavor != 11) continue;
      //if(!inBarrel(electron_ScEta->at(W_leptonIndex))) continue;
      //if(!inEndCap(electron_ScEta->at(W_leptonIndex))) continue;
      if(!PassValidWandZCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);
      
      if(!PassNumberOfZsCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);
      
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
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassElecEtCut         (idxs[lep],0)) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassElecSigmaEtaEtaCut(idxs[lep],inEC[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassElecDeltaPhiCut   (idxs[lep],inEC[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassElecDeltaEtaCut   (idxs[lep],inEC[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassElecHOverECut     (idxs[lep],inEC[lep])) pass = false;       
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      /////////
      //if(!PassElecCut()) continue;
      //Tabulate_Me(Num_surv_cut,cut_index,weight,i);
      /////////
      //if(!PassMuonCut()) continue;
      //Tabulate_Me(Num_surv_cut,cut_index,weight,i);      
      
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
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);
      
      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonEtaCut       (idxs[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);
      
      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonPtCut        (idxs[lep],0)) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonDxyCut       (idxs[lep])) pass = false; 
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonNormChi2Cut  (idxs[lep])) pass = false; 
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);
      
      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonNpixhitCut   (idxs[lep])) pass = false; 
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);
      
      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonNtrkhitCut   (idxs[lep])) pass = false; 
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonStationsCut  (idxs[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      for(size_t lep=0; lep != idxs.size(); ++lep) 
          if(!PassMuonHitsUsedCut  (idxs[lep])) pass = false;
      if(!pass) continue; 
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);
      
      ////Other Cuts/////////////
      if(!PassZDecayCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      if(!PassWDecayCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);      

      if(!PassHtCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      if(!PassZptCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      if(!PassWptCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

      if(!PassMETCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);

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
          if(Z_flavor == 11) cout<<electron_pz->at(W_leptonIndex);
          if(Z_flavor == 13) cout<<muon_pz->at(W_leptonIndex);
          cout<<endl;
          cout<<" neu minpz"<<W_neutrino_pzMinPz<<endl 
              <<" neu maxpz"<<W_neutrino_pzMaxPz<<endl 
              <<endl;
      }

      Tabulate_Me(Num_surv_cut,cut_index,weight,i); //After All Cuts
      
    }//event loop
    
    // total # of events (before any cuts)
    Nexp_evt += nevents * weight;
    Nthe_evt += lumiPb * x_sect;

    //Number of expected events for each cut (weighted)
    for(int ii = 0; ii < Num_histo_sets; ++ii){
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


//Trigger requirements
//-----------------------------------------------------------
bool PassTriggersCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Trigger requirements"<<endl;

    if( !(HLT_Photon10_L1R || HLT_Mu9) ) return false;

    return true;

}//--- PassTriggersCut()

//Check if there are valid W and Z particles in the event
//-----------------------------------------------------------
bool PassValidWandZCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check if there are valid W and Z particles in the event"
                    <<endl;
//Cory: We can expand this (maybe in lepton cuts)
//Cory: Should this be here?
    bool has_valid_W_and_Z = Z_flavor 
        && W_flavor
        && WZ_invMassMinPz>0; 
    return has_valid_W_and_Z;
    
}//--- NotValidWandZCut

/*
//Check if there is min number of leptons
//-----------------------------------------------------------
bool PassNumLeptonsCut()
{
//-----------------------------------------------------------
    //Cory: Not using this cut 
   if(debugme) cout<<"Check if there is min # of leptons"<<endl;
   if((int)(muon_pt->size() + electron_pt->size()) < minNumLeptons) return false;

    return true;
}//--- PassNumLeptonsCut

//Check if min # of leptons have min pt
//-----------------------------------------------------------
bool PassLeptonPtCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check min pt"<<endl;
    //Cory: This is not the right way to do this, should check boson leptons
    //but it is not used anywhere
    int count=0;
    int size = muon_pt->size();
    for(int i=0;i<size;++i){
	if(muon_pt->at(i) > minMuonPt) ++count;
	if(count > 3) return true;
    }

    size = electron_pt->size();
    for(int i=0;i<size;++i){
	if(electron_pt->at(i) > minElecPt) ++count;
	if(count > 3) return true;
    }

    return false;
}//--- PassLeptonPtCut
*/

//Check if there is more Zs than required
//-----------------------------------------------------------
bool PassNumberOfZsCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check if there is more Zs than required"<<endl;

    bool passnumZs = maxNumZs >= numberOfZs;
    return passnumZs;

}//--- NumberOfZsCut

//Check W decay Properties
//-----------------------------------------------------------
bool 
PassWDecayCut(){
    switch(W_flavor){
    case PDGMUON:
        return PassWmunuCut();
        break;
    case PDGELEC:
        return PassWenuCut();
        break;
    default:
        cout<<"W Didn't decay to electron or muon!"<<endl;
        break;
    }
    return false;
}

//Check Z decay Properties
//-----------------------------------------------------------
bool 
PassZDecayCut(){
    if(!PassZmassCut()) return false;

    switch(Z_flavor){
    case PDGMUON:
        return PassZmumuCut();
        break;
    case PDGELEC:
        return PassZeeCut();
        break;
    default:
        cout<<"Z Didn't decay to electron or muon!"<<endl;
        break;
    }
    return false;
}

//Check Wenu decay Properties
//-----------------------------------------------------------
bool 
PassWenuCut(){
    bool inEC = inEndCap(electron_ScEta->at(W_leptonIndex));
    if(!PassElecEtCut         (W_leptonIndex,PDGW)) return false;
    if(!PassElecTrkRelIsoCut  (W_leptonIndex,inEC)) return false;
    if(!PassElecECalRelIsoCut (W_leptonIndex,inEC)) return false;
    if(!PassElecHCalRelIsoCut (W_leptonIndex,inEC)) return false;

    return true;
}

//Check Wmunu decay Properties
//-----------------------------------------------------------
bool 
PassWmunuCut(){
    if(!PassMuonPtCut        (W_leptonIndex,PDGW)) return false;
    if(!PassMuonCombRelIsoCut(W_leptonIndex)) return false;
    
    return true;
}

//Check Zee decay Properties
//-----------------------------------------------------------
bool 
PassZeeCut(){
    int idx;
    for(int i=0; i!=2; ++i){
        if(i==0) idx = Z_leptonIndex1;
        else     idx = Z_leptonIndex2;
        
        if(!PassElecEtCut         (idx,PDGZ)) return false;
    }
    return true;
}

//Check Zmumu decay Properties
//-----------------------------------------------------------
bool 
PassZmumuCut(){
    int idx;
    for(int i=0; i!=2; ++i){
        if(i==0) idx = Z_leptonIndex1;
        else     idx = Z_leptonIndex2;

        if(!PassMuonPtCut       (idx,PDGZ)) return false; 
    }
    return true;
}

/////////////////////////////////////////
//Check Electron Pt Cut
//-----------------------------------------------------------
bool PassElecPtCut(int idx,int parent){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron Pt Cut"<<endl;
    if      (parent == PDGW){
        return (electron_pt->at(idx) > minWenuPt);
    }else if(parent == PDGZ){
        return (electron_pt->at(idx) > minZeePt);
    }
    return false;
}//--- PassElecPtCut

bool PassElecEtCut(int idx,int parent){
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

bool PassElecEtaCut(int idx){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron Eta Cut"<<endl;
    float eta = electron_ScEta->at(idx);
    return (inBarrel(eta) || inEndCap(eta));
}//--- PassElecEtaCut

bool PassElecTrkRelIsoCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron ElecTrkRelIso Cut"<<endl;
    return ((electron_trackIso->at(idx)/electron_pt->at(idx))
            < maxWenuTrkRelIso[inEC]);

}//--- PassElecTrkRelIsoCut

bool PassElecECalRelIsoCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron EcalRelIso Cut"<<endl;
    return ((electron_ecaloIso->at(idx)/electron_pt->at(idx))
                  < maxWenuECalRelIso[inEC]);

}//--- PassElecEcalRelIsoCut

bool PassElecHCalRelIsoCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron HcalRelIso Cut"<<endl;
    return ((electron_hcaloIso->at(idx)/electron_pt->at(idx))
            < maxWenuHCalRelIso[inEC]);
}//--- PassHcalRelIsoElecCut

bool PassElecSigmaEtaEtaCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron Sigma nn Cut"<<endl;
    return (electron_sigmaEtaEta->at(idx) < maxElecSigmaEtaEta[inEC]);
}//--- PassElecSigmaEtaEtaCut

bool PassElecDeltaPhiCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron dPhi Cut"<<endl;
    return (electron_deltaPhiIn->at(idx) < maxElecDeltaPhiIn[inEC]);
}//--- PassElecDeltaPhiCut

bool PassElecDeltaEtaCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron dEta Cut"<<endl;
    return (electron_deltaEtaIn->at(idx) < maxElecDeltaEtaIn[inEC]);
}//--- PassElecDeltaEtaCut

bool PassElecHOverECut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron HOverE Cut"<<endl;
    return (electron_hOverE->at(idx) < maxElecHOverE[inEC]);
}//--- PassElecHOverECut

///////////////////////////
////Muon Cuts//////////////
///////////////////////////
//--------------------------
bool PassMuonTypeCut(int idx){
    if(debugme) cout<<"Check Muon Type Cut"<<endl;
    return (muon_isGlobal->at(idx) ); 
}//--- PassMuonTypeCut

bool PassMuonNpixhitCut(int idx){
    if(debugme) cout<<"Check Muon NpixhitCut"<<endl;
    return (muon_globalNpixelHits->at(idx) > minMuonNPixHit);
}//--- PassMuonNpixhitCut

bool PassMuonNtrkhitCut(int idx){
    if(debugme) cout<<"Check Muon NtrkhitCut"<<endl;
    return (muon_globalNtrackerHits->at(idx) > minMuonNTrkHit);
}//--- PassMuonNtrkhitCut

bool PassMuonNormChi2Cut(int idx){
    if(debugme) cout<<"Check Muon Chi2 Cut"<<endl;
    return ((muon_globalChi2->at(idx)/muon_globalNdof->at(idx) )
            < maxMuonNormChi2);
}//--- PassMuonChi2Cut

bool PassMuonHitsUsedCut(int idx){
    //Num Valid Muon Hits
    if(debugme) cout<<"Check Muon Hits Used Cut"<<endl;
    return (muon_numValidMuonHits->at(idx) > minMuonHitsUsed);
}//--- PassMuonHits Used Cut

bool PassMuonStationsCut(int idx){
    if(debugme) cout<<"Check Muon Stations Cut"<<endl;
    return (muon_numGlobalMatches->at(idx) > minMuonStations);
}//--- PassMuonStationsCut

bool PassMuonEtaCut(int idx){
    if(debugme) cout<<"Check Muon Eta Cut"<<endl;
    return (fabs(muon_eta->at(idx)) < maxMuonEta);
}//--- PassMuonEta Cut

bool PassMuonPtCut(int idx,int parent){
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

bool PassMuonCombRelIsoCut(int idx){
    if(debugme) cout<<"Check Muon CombRelIso Cut"<<endl;
    return ( Calc_MuonRelIso(idx) < maxWmunuCombRelIso);
}//--- PassMuonCombRelIsoCut

float 
Calc_MuonRelIso(int idx){

    if(muon_trackIso == 0 || muon_caloIso == 0) return 999;

    return (muon_trackIso->at(idx) + 
            muon_caloIso->at(idx) ) /
        muon_pt->at(idx);
}//--- Calc_MuonRelIso

bool PassMuonDxyCut(int idx){
    //Use: muon_globalD0
    if(debugme) cout<<"Check Muon Dxy Cut"<<endl;
    return (muon_globalD0->at(idx) < maxMuonDxy);
}//--- PassMuonDxyCut

////////////////////////////////

//Check Z Properties

bool PassZmassCut(){
    if(debugme) cout<<"Check Zmass Cut"<<endl;
    return (Z_mass > minZmass && Z_mass < maxZmass);
}//--- PassZmassCut



//Check Z pt
//-----------------------------------------------------------
bool PassZptCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check Z pt"<<endl;
    
    if(Z_pt < minZpt) return false;
    
    return true;

}//--- PassZptCut

//Check W pt
//-----------------------------------------------------------
bool PassWptCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check W pt"<<endl;

    if(W_pt < minWpt) return false;
    
    return true;

}//--- PassWptCut

//Check Ht Properties
//-----------------------------------------------------------
bool PassHtCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check Ht Cuts"<<endl;
   
    return Ht > minHt;
    
}//--- PassHtCut

//Calc Ht
//-----------------------------------------------------------
float Calc_Ht()
{
    float Ht=0;
  
    if     (W_flavor == PDGELEC) Ht += electron_pt->at(W_leptonIndex);
    else if(W_flavor == PDGMUON) Ht += muon_pt->at(W_leptonIndex);
    //else                         cout<<"W didn't decay into e,mu"<<endl;

    if     (Z_flavor == PDGELEC){
		Ht += electron_pt->at(Z_leptonIndex1);
		Ht += electron_pt->at(Z_leptonIndex2);
    }else if(Z_flavor == PDGMUON){
		Ht += muon_pt->at(Z_leptonIndex1);
		Ht += muon_pt->at(Z_leptonIndex2);
    }//else                         cout<<"Z didn't decay into e,mu"<<endl;

    return Ht;

}//--- CalcHt

//Check Ht Met Properties
//-----------------------------------------------------------
bool PassHtMetCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check Ht Cuts"<<endl;
    float Ht=0;
  
    if     (W_flavor == PDGELEC) Ht += electron_pt->at(W_leptonIndex);
    else if(W_flavor == PDGMUON) Ht += muon_pt->at(W_leptonIndex);
    else                         cout<<"W didn't decay into e,mu"<<endl;

    if     (Z_flavor == PDGELEC){
	Ht += electron_pt->at(Z_leptonIndex1);
	Ht += electron_pt->at(Z_leptonIndex2);
    }else if(Z_flavor == PDGMUON){
	Ht += muon_pt->at(Z_leptonIndex1);
	Ht += muon_pt->at(Z_leptonIndex2);
    }else                         cout<<"Z didn't decay into e,mu"<<endl;

    Ht += pfMet_et;
    
    return Ht > minHtMet;
    
}//--- PassHtMetCut

//Calc Gen Inv Mass
//-----------------------------------------------------------
float Calc_GenWZInvMass()
{
    int pdg=0, pdgM=0;
    int idZ=-1;
    int idW=-1;    
    int size = genMother_pdgId->size();
    for(int i=0; i != size; i++){
        pdg = abs(genParticle_pdgId->at(i));
        pdgM = abs(genMother_pdgId->at(i));
        if (pdgM == PDGWPRIME){
            return genMother_mass->at(i);
        }
        if( pdg == PDGZ && pdgM != PDGZ){
            idZ = i;
        }
        if( pdg == PDGW && pdgM != PDGW){
            idW = i;
        }
        
        if( abs(genParticle_pdgId->at(i)) == PDGZ && pdg > 50){
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

//MET Cut
//-----------------------------------------------------------
bool PassMETCut()
{
    return pfMet_et > minMET;
}//--- MET Cut

//Pass Tight Cut
//-----------------------------------------------------------
bool PassTightCut(int idx)
{
    if(Z_flavor == 11){
        bool inEC = inEndCap(electron_ScEta->at(idx));
        if(!PassElecEtCut         (idx,PDGW)) return false;
        if(!PassElecTrkRelIsoCut  (idx,inEC)) return false;
        if(!PassElecECalRelIsoCut (idx,inEC)) return false;
        if(!PassElecHCalRelIsoCut (idx,inEC)) return false;

    }else if (Z_flavor == 13){
        if(!PassMuonPtCut(idx, PDGW)) return false;
        if(!PassMuonCombRelIsoCut(idx)) return false;
    }
    return true;
}//--- Tight Cut

void 
UseSample(string dir, vector<InputFile> & files, 
          float lumiPb, TFile* fout, ofstream & out){
    Load_Input_Files(dir, files, lumiPb);
    Get_Distributions(files, fout, dir, out);
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
 
  //containers to
  //include signal and background files
  vector<InputFile> wprime400_files;
  vector<InputFile> wprime400STARTUP_files;
  vector<InputFile> wprime400_W20_files;
  vector<InputFile> wprime400_W40_files;
  vector<InputFile> wprime400_WDef_files;
  vector<InputFile> wprime500_files;
  vector<InputFile> wprime600_files;
  vector<InputFile> wprime700_files;
  vector<InputFile> wprime800_files;
  vector<InputFile> wprime900_files;
  //vector<InputFile> wzjj_files;
  vector<InputFile> wz_files;
  vector<InputFile> ttbar_files;
  vector<InputFile> ttbarfast_files;
  vector<InputFile> zz_files;
  vector<InputFile> zgamma_files;
  vector<InputFile> zjets_files;
  vector<InputFile> wjets_files;
  vector<InputFile> TC400_files;
  vector<InputFile> test_files;
  vector<InputFile> wmunu_files;
  vector<InputFile> wenu_files;

  //load the harcoded crosssectios
  //add background or signal containers as needed
  //Load_Cross_Sections(wzjj_files, wprime400_files); //Cory: took this out
 
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
  UseSample("wprime400",wprime400_files, lumiPb, fout, out);
  //UseSample("wprime500",wprime500_files, lumiPb, fout, out);
  //UseSample("wprime600",wprime600_files, lumiPb, fout, out);
  //UseSample("wprime700",wprime700_files, lumiPb, fout, out);
  //UseSample("wprime800",wprime800_files, lumiPb, fout, out);
  //UseSample("wprime900",wprime900_files, lumiPb, fout, out);
  UseSample("TC400", TC400_files, lumiPb, fout, out);
  
  UseSample("wz",wz_files, lumiPb, fout, out);
  UseSample("ttbar",ttbar_files, lumiPb, fout, out);
  UseSample("ttbarfast",ttbarfast_files, lumiPb, fout, out);
  UseSample("zz",zz_files, lumiPb, fout, out);
  UseSample("zgamma",zgamma_files, lumiPb, fout, out);
  UseSample("zjets",zjets_files, lumiPb, fout, out);
  UseSample("wjets",wjets_files, lumiPb, fout, out);

  //UseSample("test",test_files, lumiPb, fout, out);
  //UseSample("wenu",wenu_files, lumiPb, fout, out);
  //UseSample("wmunu",wmunu_files, lumiPb, fout, out);

  out.close(); 
  fout->Close();

}//ExecuteAnalysis





//  LocalWords:  pzMinPz
