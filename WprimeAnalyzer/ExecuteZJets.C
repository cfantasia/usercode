#ifndef _ExecuteZJets_cxx_
#define ExecuteZJets_cxx
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


#include "ExecuteVariables.C"
#include "ExecuteCuts.C"
#include "ExecuteFunctions.C"

#include "ExecuteZJets.h"

//--------------------------------------------------------------
void Declare_Histos()
{
//--------------------------------------------------------------

  if (debugme) cout<<"Declare histos"<<endl;
  listOfHists.clear();

  DeclareHistoSet("hWZInvMass","Reconstructed WZ Invariant Mass",
                  "m_{WZ} (GeV)", 110, 0, 1100, Cut, hWZInvMass);
  //Z Mass Histos
  DeclareHistoSet("hZmass" , "Reconstructed Mass of Z",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZmass);
  
  DeclareHistoSet("hZeemass","Reconstructed Mass of Zee",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZeemass);

  DeclareHistoSet("hZeemassTT","Reconstructed MassTT of ZeeTT",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZeemassTT);

  DeclareHistoSet("hZeemassTF","Reconstructed Mass of ZeeTF",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZeemassTF);

  DeclareHistoSet("hZmumumass","Reconstructed Mass of Zmumu",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZmumumass);

  DeclareHistoSet("hZmumumassTT","Reconstructed Mass of ZmumuTT",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZmumumassTT);

  DeclareHistoSet("hZmumumassTF","Reconstructed Mass of ZmumuTF",
                  "m_{Z}^{Reco} (GeV)", 40, 50, 130, Cut, hZmumumassTF);

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
  hZmass[index]->Fill(Z_mass,weight);
  if      (Z_flavor == PDGELEC){
    hZeemass[index]->Fill(Z_mass,weight);
    if(TT) hZeemassTT[index]->Fill(Z_mass,weight);
    if(TF) hZeemassTF[index]->Fill(Z_mass,weight);
  }else if (Z_flavor == PDGMUON){
    hZmumumass[index]->Fill(Z_mass,weight);
    if(TT) hZmumumassTT[index]->Fill(Z_mass,weight);
    if(TF) hZmumumassTF[index]->Fill(Z_mass,weight);
  }

}//Fill_Histos

void
CalcEventVariables(){
  ////Calculate Important Quantities for each event
  Ht = Calc_Ht();

  TT = TF = false;
  if(Z_flavor){
    bool tight1 = PassTightCut(Z_leptonIndex1, Z_flavor);
    bool tight2 = PassTightCut(Z_leptonIndex2, Z_flavor);
    //cout<<"tight1: "<<tight1<<" tight2: "<<tight2<<endl;
    TT = tight1 && tight2;
    TF = (tight1 && !tight2) || (!tight1 && tight2);
  }

}

bool
PassCuts(vector<int>& Num_surv_cut, const float& weight){
  //an index to indicate current cut number
  int cut_index = 0;//Incremented in Tabulate_Me
      
  vector<int> idxs;
  vector<int> inEC;


  //cuts: These need to be ordered the same as Cut_Name in header file
  Tabulate_Me(Num_surv_cut,cut_index,weight); //No Cuts
      
  //if(!PassTriggersCut()) return false; //Cory
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  if(!Z_flavor) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  if(!PassNumberOfZsCut()) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight);
      
  ////////////////New Elec Cuts////////////////
  if(Z_flavor == PDGELEC ){
    idxs.push_back(Z_leptonIndex1); 
    inEC.push_back(inEndCap(electron_ScEta->at(Z_leptonIndex1)));
    idxs.push_back(Z_leptonIndex2);
    inEC.push_back(inEndCap(electron_ScEta->at(Z_leptonIndex2)));
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

  idxs.clear(); inEC.clear();
  if(Z_flavor == PDGMUON ){
    idxs.push_back(Z_leptonIndex1); 
    idxs.push_back(Z_leptonIndex2);
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
      

  Tabulate_Me(Num_surv_cut,cut_index,weight); //After All Cuts
      
  return true;
}



//-----------------------------------------------------------
void ExecuteZJets()
{
//-----------------------------------------------------------
  if (debugme)cout<<"Master macro to execute analysis"<<endl;

  //lumiPb now defined in ExecuteAnalysis.h
  cout<<"Using integrated luminosity of "<<lumiPb<<" inv pb"<<endl;
 
  //name of file where to write all histograms
  TFile *fout = new TFile("ZJets_analysis.root","recreate");
 
  
  //Improves ability to rescale histograms
  TH1::SetDefaultSumw2();

  //containers to
  //include signal and background files

  //keep account of events
  string outfile("event_counts_Zjets.txt");
  ofstream out(outfile.c_str());
  if(!out) { 
    cout << "Cannot open file " << outfile << endl; 
    abort();
  } 

  //go for the analysis now and separate 
  //nicely into background/signal-type directories
  //the results will be written under respective directories
  //Add as many as you need:

  UseSample("Wprime300", Cut, fout, out);
  UseSample("Wprime400", Cut, fout, out);
  UseSample("Wprime500", Cut, fout, out);
  UseSample("Wprime600", Cut, fout, out);
  UseSample("Wprime700", Cut, fout, out);
  UseSample("Wprime800", Cut, fout, out);
  UseSample("Wprime900", Cut, fout, out);
  
  UseSample("TC225", Cut, fout, out);
  UseSample("TC300", Cut, fout, out);
  UseSample("TC400", Cut, fout, out);
  UseSample("TC500", Cut, fout, out);
  
  UseSample("WZ3l", Cut, fout, out);
  //UseSample("TTbar", Cut, fout, out);
  UseSample("TTbar2l", Cut, fout, out);
  UseSample("ZZ", Cut, fout, out);
  //UseSample("ZZ4l", Cut, fout, out);
  UseSample("ZGamma2l", Cut, fout, out);

  //UseSample("ZJetsBinned", Cut, fout, out);
  //UseSample("ZeeJets", Cut, fout, out);
  //UseSample("ZmumuJets", Cut, fout, out);
  //UseSample("ZeeJetsPowheg", Cut, fout, out);
  //UseSample("ZmumuJetsPowheg", Cut, fout, out);
  //UseSample("ZllJetsMadgraph", Cut, fout, out);
  UseSample("DYJets2l", Cut, fout, out);
  //UseSample("DYee", Cut, fout, out);
  UseSample("DYmumu", Cut, fout, out);

  UseSample("WenuJets", Cut, fout, out);
  UseSample("WmunuJets", Cut, fout, out);
  //UseSample("WlnuJetsMadgraph", Cut, fout, out);
  
  //UseSample("Run2010", Cut, fout, out);
  UseSample("Run2011", Cut, fout, out);
/*
  UseSample("WZ3l_Dilepton", Cut, fout, out);
  //UseSample("TTbar_Dilepton", Cut, fout, out);
  UseSample("TTbar2l_Dilepton", Cut, fout, out);
  UseSample("ZZ_Dilepton", Cut, fout, out);
  //UseSample("ZZ4l_Dilepton", Cut, fout, out);
  UseSample("ZGamma2l_Dilepton", Cut, fout, out);

  //UseSample("ZJetsBinned_Dilepton", Cut, fout, out);
  //UseSample("ZeeJets_Dilepton", Cut, fout, out);
  //UseSample("ZmumuJets_Dilepton", Cut, fout, out);
  //UseSample("ZeeJetsPowheg_Dilepton", Cut, fout, out);
  //UseSample("ZmumuJetsPowheg_Dilepton", Cut, fout, out);
  //UseSample("ZllJetsMadgraph_Dilepton", Cut, fout, out);
  UseSample("DYJets2l_Dilepton", Cut, fout, out);
  //UseSample("DYee_Dilepton", Cut, fout, out);
  UseSample("DYmumu_Dilepton", Cut, fout, out);

  UseSample("WenuJets_Dilepton", Cut, fout, out);
  UseSample("WmunuJets_Dilepton", Cut, fout, out);
  //UseSample("WlnuJetsMadgraph_Dilepton", Cut, fout, out);
  
  //UseSample("Run2010_Dilepton", Cut, fout, out);
  UseSample("Run2011_Dilepton", Cut, fout, out);
*/
  out.close(); 
  fout->Close();
}//ExecuteZJets

#endif//#define _ExecuteAnalysis_cxx_
