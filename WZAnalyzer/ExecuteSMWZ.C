#include "WZAnalysis.h"
using namespace std;
int main(int argc, char ** argv);
void ExecuteAnalysis(float lumi=1000, bool verbose=false);

//-----------------------------------------------------------
void ExecuteAnalysis(float lumi, bool verbose)
{
//-----------------------------------------------------------
  if (verbose)cout<<"Master macro to execute analysis"<<endl;
  const string Cut_Name[] = {"NoCuts", 
                             //"HLT", 
                             "ValidWandZ", 
                             "MinLepPt",
                             "NumZs", 
                             "LooseElec", 
                             "LooseMuon",
                             "WLepIso",
                             "WLepPt", 
                             "ZMass", 
                             //"WTransMass", 
                             "MET",
                             //"ZLepPt", 
                             "AllCuts"};
  const std::vector<string> vCuts(Cut_Name, Cut_Name + sizeof(Cut_Name) / sizeof(string) );
  WZAnalysis wz(vCuts, "/uscms_data/d2/fantasia/41X/", lumi, verbose);
  wz.SetCandEvtFile("SMWZ_candEvts.txt");
  wz.SetLogFile("SMWZ_event_counts.txt");
  wz.SetOutputFile("SMWZ_analysis.root");

  cout<<"Using integrated luminosity of "<<wz.GetLumiPb()<<" inv pb"<<endl;
 
  //Improves ability to rescale histograms
  TH1::SetDefaultSumw2();
 
  //go for the analysis now and separate 
  //nicely into background/signal-type directories
  //the results will be written under respective directories
  //Add as many as you need:
  wz.UseSample("Wprime300");
  wz.UseSample("Wprime400");
  wz.UseSample("Wprime500");
  wz.UseSample("Wprime600");
  wz.UseSample("Wprime700");
  wz.UseSample("Wprime800");
  wz.UseSample("Wprime900");
  
  //wz.UseSample("TC300");
  //wz.UseSample("TC400");
  //wz.UseSample("TC500");
  
  wz.UseSample("WZ3l");
  //wz.UseSample("TTbar");
  wz.UseSample("TTbar2l");
  wz.UseSample("ZZ");
  //wz.UseSample("ZZ4l");
  wz.UseSample("ZGamma2l");

  //wz.UseSample("ZJetsBinned");
  wz.UseSample("ZeeJets");
  wz.UseSample("ZmumuJets");
  wz.UseSample("ZeeJetsPowheg");
  wz.UseSample("ZmumuJetsPowheg");
  wz.UseSample("ZllJetsMadgraph");
  wz.UseSample("DYJets2l");
  wz.UseSample("DYee");
  wz.UseSample("DYmumu");

  wz.UseSample("WenuJets");
  wz.UseSample("WmunuJets");
  //wz.UseSample("WlnuJetsMadgraph");

  wz.UseSample("Run2010");
  wz.UseSample("Run2011");

  //wz.UseSample("interesting");
  //wz.UseSample("test");
    
}//ExecuteAnalysis

int 
main(int argc, char ** argv){
  if(argc > 3){
    fprintf(stderr,"%s usage: %s [lumi] [verbose]\n",argv[0],argv[0]);
    exit( 1 );
  }
  float lumi   = (argc > 1) ? atoi(argv[1]) : 1000;
  bool verbose = (argc > 2) ? atoi(argv[2]) : false;
  ExecuteAnalysis(lumi, verbose);

  return 0;
}

