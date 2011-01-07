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

#define ExecuteFakeRate_cxx
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
      //////////////////////
      if (debugme) cout<<"Processing event "<<i<<endl;

      //an index to indicate current cut number
      int cut_index = 0;//Incremented in Tabulate_Me
      
      //Choose One of the following
      //if(W_flavor != PDGELEC) continue;//Are Muons faking jets
      if(W_flavor != PDGMUON) continue;//Are Elec faking jets

      Tabulate_Me(Num_surv_cut,cut_index,weight); //Before All Cuts
      
      if( !PassFakeLeptonTagCut() ) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight); //After Tag Cut

      if( !PassFakeLeptonProbeCut() ) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight); //After Probe Cut

      Tabulate_Me(Num_surv_cut,cut_index,weight); //After All Cuts

      
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

  vector<InputFile> Run2010_Dilepton_files;
  UseSample("Run2010_Dilepton",Run2010_Dilepton_files, fout, out);
  vector<InputFile> Run2010_files;
  //UseSample("Run2010",Run2010_files, fout, out);

  out.close(); 
  fout->Close();

}//ExecuteFakeRate





