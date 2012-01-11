#include "UserCode/CMSDAS_WZ_2012/interface/WZAnalyzer.h"

using namespace std;

WZAnalyzer::WZAnalyzer(){}
WZAnalyzer::WZAnalyzer(const edm::ParameterSet & cfg, int fileToRun){
  reportAfter_ = cfg.getParameter<int>("reportAfter");
  maxEvents_   = cfg.getParameter<int>("maxEvents");
  debug_ = cfg.getParameter<bool>("debug");

  getInputFiles(cfg);
  if(fileToRun != -1){
    if(fileToRun < (int)inputFiles_.size()){
      inputFiles_.assign(1,inputFiles_[fileToRun]);
    }else{
      cerr<<"You asked for sample "<<fileToRun
          <<" but only "<<inputFiles_.size()
          <<" are listed!\n";
      inputFiles_.clear();
      abort();
    }
  }

  //////Output Files
  string outputFile  = cfg.getParameter<string  >("outputFile" );

  if(fileToRun != -1){
    outputFile = Form("Sample%i_%s",fileToRun,outputFile.c_str()); 
  }

  fs = new fwlite::TFileService(outputFile);

  //////////////////////

  electronsLabel_ = cfg.getParameter<edm::InputTag>("electrons");
  muonsLabel_ = cfg.getParameter<edm::InputTag>("muons");
  metLabel_ = cfg.getParameter<edm::InputTag>("met");
  vertexLabel_ = cfg.getParameter<edm::InputTag>("vertexTag");

}

WZAnalyzer::~WZAnalyzer(){
  delete fs; 
}

void WZAnalyzer::run(){
  int ievt_all=0;  int ievt_skipped = 0;
  unsigned i_sample = 1;
  float reportPercent = reportAfter_<0 ? reportAfter_/100. : 0;
  vector<wprime::InputFile>::iterator it;
  
  //Loop Over input files
  for(it = inputFiles_.begin(); it != inputFiles_.end(); ++it, ++i_sample){
    int ievt=0;//Evts checked in this input file  
    cout << "\n Opening sample " << it->samplename 
         << " (" << it->description << ")... "<<std::flush;
    fwlite::ChainEvent ev(it->pathnames);
    it->Nact_evt = ev.size();
    cout<<" Done." << endl;
  
    cout << " Opened sample " << it->samplename << " with " << it->Nact_evt
         << " events (Input file #" << i_sample << " out of " << inputFiles_.size()
         << " samples) " << endl << endl;   
    cout << std::fixed << std::setprecision(2);

    beginFile(it);//Set up for input file
    assert(it->Nact_evt <= it->Nprod_evt);
    if(reportPercent) reportAfter_ = fabs(it->Nact_evt * reportPercent);

    for(ev.toBegin(); !ev.atEnd(); ++ev, ++ievt){// loop over events
      edm::EventBase const & event = ev;

      // skip event if maximal number of events per input file is reached 
      if(maxEvents_>0 &&  ievt > maxEvents_) break;
      
      // simple event counter
      if(reportAfter_!=0 ? (ievt>0 && ievt%reportAfter_==0) : false) 
        cout << " Processing event: " << ievt << " or " 
             << 100.*ievt/it->Nact_evt << "% of input file #" << i_sample
             << " (Total events processed: " << ievt_all 
             << ", non-certified/skipped: " << ievt_skipped << ") " << endl;
      
      
      ++ievt_all;
      
      eventLoop(event); //Analyze each vent
    } // loop over events

    endFile(it);//Finish up with this input sample
    
  } // loop over input files
  cout<<"Done with Input Samples\n";

  endAnalysis();//Finish up with analysis

}

void WZAnalyzer::defineHistos(const TFileDirectory & dir){
  if(debug_) printf("Declare histos\n");
  hNLElec= dir.make<TH1F>("hNLElec", "Number of Loose Electrons in Event;N_{e}^{Loose}", 10, 0, 10);
  hNLMuon= dir.make<TH1F>("hNLMuon", "Number of Loose Muons in Event;N_{#mu}^{Loose}", 10, 0, 10);
  hNLLeps= dir.make<TH1F>("hNLLeps", "Number of Loose Leptons in Event; N_{Lep}^{Loose}", 10, 0, 10);
}//defineHistos

void 
WZAnalyzer::eventLoop(edm::EventBase const & event){
  // get leptons
  event.getByLabel(electronsLabel_,patElectronsH_);
  const vector<pat::Electron> & patElectrons = *patElectronsH_.product();
  event.getByLabel(muonsLabel_,patMuonsH_);
  const vector<pat::Muon> & patMuons = *patMuonsH_.product();

}


///////////////Utilities//////////////////
//--------------------------------------------------------------

//////////////////
//file stuff//////
//////////////////

// operations to be done when changing input file (e.g. create new histograms)
void WZAnalyzer::beginFile(std::vector<wprime::InputFile>::iterator fi){

  if(fi->runningOnData())
    // Nprod_evt presumably contains the # of events before any filtering
    // that results in Nact_evt (< Nprod_evt) events contained in the file.
    // For data, we tend not to know how many events we started with,
    // so just assume pre-selection efficiency = 100%;
    // this affects only the efficiency calculations printed
    // at the end of the job - nothing else!
    fi->Nprod_evt = fi->Nact_evt;

  TFileDirectory dir = fs->mkdir(fi->samplename, fi->description); 

  defineHistos(dir);
}

// operations to be done when closing input file 
// (e.g. print summary)
void WZAnalyzer::endFile(std::vector<wprime::InputFile>::iterator fi){
}

// e.g. print summmary of expected events for all samples
void WZAnalyzer::endAnalysis(){
}

void WZAnalyzer::getInputFiles(const Pset & cfg){
  //fill in
  Pset inputFiles = cfg.getParameter<Pset>("inputFiles");
  string top_level_dir = inputFiles.getUntrackedParameter<string>("top_level_dir");
  lumi_ipb_ = inputFiles.getParameter<double>("lumi_ipb");
  VPset files = inputFiles.getParameter<VPset>("files");

  for(uint i=0; i<files.size(); ++i){
    Pset & file = files[i];
    wprime::InputFile * new_file = new wprime::InputFile();

    new_file->samplename = file.getParameter<string>("samplename");
    new_file->description = file.getUntrackedParameter<string>("description", new_file->samplename);
    
    new_file->subdir = file.getUntrackedParameter<string>("subdir", "");
    new_file->x_sect = file.getUntrackedParameter<double>("x_section", 0.);
    new_file->signalMass = file.getUntrackedParameter<double>("signalMass", -1);
    new_file->Nprod_evt = file.getUntrackedParameter<int>("Nprod_evt", -1);
    new_file->weight = 1.;

    string pathname = file.getParameter<string>("pathname");
    vector<string> pathnames;
    if(pathname.find(".txt") != string::npos){
      cout<<"Using input file "<<pathname<<endl;
      ifstream infile;
      pathname = "UserCode/CMGWPrimeGroup/config/" + pathname;
      infile.open (pathname.c_str(), ifstream::in);
      
      while (infile.good()){
        string fname;
        infile>>fname;
        if(fname != ""){
          cout<<" filename: "<<fname.c_str()<<endl;
          pathnames.push_back(top_level_dir + new_file->subdir+ "/" + fname);
        }
      }
      infile.close();
    }else{
      pathname = top_level_dir + new_file->subdir + "/" + pathname;
      pathnames.push_back(pathname);
    }
    
    size_t splitInto = file.getUntrackedParameter<int>("splitInto", 1);
    size_t nPerFile = ceil((float) pathnames.size() / splitInto);
    if(splitInto > 1) 
      cout<<"Trying to split file with "<<pathnames.size()<<" files into "
          <<splitInto<<" parts, with "<<nPerFile<<" files per part"<<endl;
    for(size_t i=0; i<splitInto; ++i){
      size_t first = i*nPerFile;
      size_t last  = std::min(first+nPerFile, pathnames.size());
      if(first >= pathnames.size()) break;
      new_file->pathnames.assign(pathnames.begin()+first,
                                 pathnames.begin()+last);

      new_file->checkFile();
      inputFiles_.push_back(*new_file);
    }
    delete new_file;
  }
}

