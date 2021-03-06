#ifndef _ExecuteFakeRate_cxx_
#define _ExecuteFakeRate_cxx_
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

#include "ExecuteFakeRate.h"

//--------------------------------------------------------------
void Declare_Histos()
{
//--------------------------------------------------------------

  if (debugme) cout<<"Declare histos"<<endl;
  listOfHists.clear();

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
        
}//Fill_Histos

void
CalcEventVariables(){
}

bool
PassCuts(vector<int>& Num_surv_cut, const float& weight){
  //an index to indicate current cut number
  int cut_index = 0;//Incremented in Tabulate_Me
      
  //Choose One of the following
  //if(W_flavor != PDGELEC) return false;//Are Muons faking jets
  if(W_flavor != PDGMUON) return false;//Are Elec faking jets

  Tabulate_Me(Num_surv_cut,cut_index,weight); //Before All Cuts
      
  if( !PassFakeLeptonTagCut() ) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight); //After Tag Cut

  if( !PassFakeLeptonProbeCut() ) return false;
  Tabulate_Me(Num_surv_cut,cut_index,weight); //After Probe Cut

  Tabulate_Me(Num_surv_cut,cut_index,weight); //After All Cuts
 
  return true;
}
    
//Pass Fake Lepton Tag Cut
//-----------------------------------------------------------
bool PassFakeLeptonTagCut()
{
  if( !W_flavor ) return false;
  if( W_transMass < 20 ) return false;
  if( pfMet_et < 20) return false;

  if(electron_pdgId->size() != 1)          return false;
  if(muon_pdgId->size() != 1)              return false;
  /*
    cout<<"There are "<<electron_pdgId->size()<<" electrons and "
    <<muon_pdgId->size()<<" muons and "
    <<W_flavor<<" is W_flavor!!!"<<endl;
  */
  if(muon_pdgId->at(0) * electron_pdgId->at(0) < 0.0) return false;
    
  if( !PassTightCut(W_leptonIndex, W_flavor)) return false;

  return true;
}//--- Tag Cut

//Pass Fake Lepton Probe Cut
//-----------------------------------------------------------
bool PassFakeLeptonProbeCut()
{
    
  if(W_flavor == PDGELEC){
    return PassTightCut(0, PDGMUON); //Check the other lepton
  }else if(W_flavor == PDGMUON){
    return PassTightCut(0, PDGELEC);
  }
    

  return true;
}//--- Probe Cut

//-----------------------------------------------------------
void ExecuteFakeRate()
{
//-----------------------------------------------------------

  if (debugme)cout<<"Master macro to execute analysis"<<endl;

  //lumiPb now defined in ExecuteAnalysis.h
  cout<<"Using integrated luminosity of "<<lumiPb<<" inv pb"<<endl;
 
  //name of file where to write all histograms
  TFile *fout = new TFile("FakeRate_analysis.root","recreate");
 
  //Improves ability to rescale histograms
  TH1::SetDefaultSumw2();

  //containers to
  //include signal and background files

  //keep account of events
  string outfile("event_counts_FakeRate.txt");
  ofstream out(outfile.c_str());
  if(!out) { 
    cout << "Cannot open file " << outfile << endl; 
    abort();
  } 
  
  //go for the analysis now and separate 
  //nicely into background/signal-type directories
  //the results will be written under respective directories
  //Add as many as you need:

  //UseSample("Run2010_Dilepton", Cut, fout, out);
  //UseSample("Run2010", Cut, fout, out);
  //UseSample("Run2011_Dilepton", Cut, fout, out);
  UseSample("Run2011", Cut, fout, out);

  out.close(); 
  fout->Close();

}//ExecuteFakeRate

#endif//#define _ExecuteAnalysis_cxx_
