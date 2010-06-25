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
  float WptMax = 500.;
  int Wptbin = 25;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWpt_" + Cut_Name[i];
      string title = "p_{T}^{W} (After "+Cut_Name[i]+" Cut);p_{T} of W (GeV);";
      hWpt[i] = new TH1F(name.c_str(),title.c_str(),Wptbin,WptMin,WptMax);
  }

  //Zpt Histos
  float ZptMin = 0.;
  float ZptMax = 500.;
  int Zptbin = 25;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hZpt_" + Cut_Name[i];
      string title = "p_{T}^{Z} (After "+Cut_Name[i]+" Cut);p_{T} of Z (GeV);";
      hZpt[i] = new TH1F(name.c_str(),title.c_str(),Zptbin,ZptMin,ZptMax);
  }

  //Gen InvMass histos
  int GenWZinvMin = 300;
  int GenWZinvMax = 500;
  int GenWZbin = 200;
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

  //Z Mass Histos
  float ZmassMin = 40.;
  float ZmassMax = 140.;
  int Zmassbin = 100;
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

  //Zmumu Mass Histos
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hZmumumass_" + Cut_Name[i];
      string title = "Reconstructed Mass of Zmumu (After "+Cut_Name[i]+" Cut);m_{Z}^{Reco} (GeV);";
      hZmumumass[i] = new TH1F(name.c_str(),title.c_str(),Zmassbin,ZmassMin,ZmassMax);
  }

  //W Trans Mass Histos
  float WTransmassMin = 40.;
  float WTransmassMax = 140.;
  int WTransmassbin = 100;
  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hWTransmass_" + Cut_Name[i];
      string title = "Reconstructed Transmass of W (After "+Cut_Name[i]+" Cut);m_{W}^{Reco} (GeV);";
      hWTransmass[i] = new TH1F(name.c_str(),title.c_str(),WTransmassbin,WTransmassMin,WTransmassMax);
  }

//////////////
  //Electron Properties
  int ElecPtbin = 100;
  float ElecPtMin = 0.;
  float ElecPtMax = 500.;

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecPt_" + Cut_Name[i];
      string title = "Electron Pt (After "+Cut_Name[i]+" Cut);Pt;";
      hElecPt[i] = new TH1F(name.c_str(),title.c_str(),ElecPtbin,ElecPtMin,ElecPtMax);
  }
  int ElecdEtabin = 100;
  float ElecdEtaMin = 0.;
  float ElecdEtaMax = 1.;

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecdEta_" + Cut_Name[i];
      string title = "Electron dEta (After "+Cut_Name[i]+" Cut);dEta;";
      hElecdEta[i] = new TH1F(name.c_str(),title.c_str(),ElecdEtabin,ElecdEtaMin,ElecdEtaMax);
  }
  int ElecdPhibin = 100;
  float ElecdPhiMin = 0.;
  float ElecdPhiMax = 1.;

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecdPhi_" + Cut_Name[i];
      string title = "Electron dPhi (After "+Cut_Name[i]+" Cut);dPhi;";
      hElecdPhi[i] = new TH1F(name.c_str(),title.c_str(),ElecdPhibin,ElecdPhiMin,ElecdPhiMax);
  }
  int ElecSigmannbin = 100;
  float ElecSigmannMin = 0.;
  float ElecSigmannMax = 1.;

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecSigmann_" + Cut_Name[i];
      string title = "Electron Sigma Eta Eta (After "+Cut_Name[i]+" Cut);Sigma Eta Eta;";
      hElecSigmann[i] = new TH1F(name.c_str(),title.c_str(),ElecSigmannbin,ElecSigmannMin,ElecSigmannMax);
  }
  int ElecEPbin = 100;
  float ElecEPMin = 0.;
  float ElecEPMax = 2.;

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecEP_" + Cut_Name[i];
      string title = "Electron E Over P (After "+Cut_Name[i]+" Cut);E/P;";
      hElecEP[i] = new TH1F(name.c_str(),title.c_str(),ElecEPbin,ElecEPMin,ElecEPMax);
  }
  int ElecHEbin = 100;
  float ElecHEMin = 0.;
  float ElecHEMax = 0.1;

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecHE_" + Cut_Name[i];
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
  int ElecRelTrkIsobin = 100;
  float ElecRelTrkIsoMin = 0.;
  float ElecRelTrkIsoMax = 1.;

  for(int i=0; i<Num_histo_sets; ++i){
      string name = "hElecRelTrkIso_" + Cut_Name[i];
      string title = "Electron Relative Track Iso (After "+Cut_Name[i]+" Cut);RelTrkIso;";
      hElecRelTrkIso[i] = new TH1F(name.c_str(),title.c_str(),ElecRelTrkIsobin,ElecRelTrkIsoMin,ElecRelTrkIsoMax);
  }
//////////

  string title = "Expected # of Events / " + convertFloatToStr(lumiPb) + "pb^{-1}";
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
bool inBarrel(float eta, int parent)
{
    if      (parent == PDGW){
        return (fabs(eta) < maxWenuEtaBarrel);
    }else if (parent == PDGZ){
        return (fabs(eta) < maxZeeEtaBarrel);
    }
    return false;
  
}//InBarrel

bool inEndCap(float eta, int parent)
{
    float abs_eta = fabs(eta);
    if      (parent == PDGW){
        return (abs_eta > minWenuEtaEndcap && abs_eta < maxWenuEta);
    }else if (parent == PDGZ){
        return (abs_eta > minZeeEtaEndcap && abs_eta < maxZeeEta);
    }
    return false;
      
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





//---------------------------------------------------------
int Load_Cross_Sections(vector<InputFile> & wzjj_files, 
                      vector<InputFile> & wprime400_files)
{
//---------------------------------------------------------
  if (debugme)cout<<"Loading cross sections...."<<endl;

  //CalHEP cross sections in pb:
  float xsec_wzjj = 0.1958;
  //float xsec_wprime400 = 2.118995E-3;
  float xsec_wprime400 = 9.0E-3; //Cory: from pythia
  //float xsec_wprime500 = 3.7755E-3;
  //float xsec_wprime600 = 7.9664E-4;
  //float xsec_wprime700 = 5.3399E-4;
  //float xsec_wprime800 = 3.673218E-4;
  //float xsec_wprime900 = 2.58269E-4;
  //float xsec_wprime1000 = 1.84634E-4;
  //float xsec_wprime1100 = 1.32994E-4;
  //float xsec_wprime1200 = 9.702684E-5;
  


  //PYTHIA cross-section (pb)

  //qcd_files.push_back(InputFile(590000)); // 100_150
  //qcd_files.push_back(InputFile( 83000)); // 150_200
  //qcd_files.push_back(InputFile( 24000)); // 200_300
  //qcd_files.push_back(InputFile(  3000)); // 300_400
  //qcd_files.push_back(InputFile(   730)); // 400_600
  //qcd_files.push_back(InputFile(    66)); // 600_800
  //qcd_files.push_back(InputFile(    12)); // 800_1200
  //qcd_files.push_back(InputFile(    0.63)); // 1200_1600
  //qcd_files.push_back(InputFile(    0.54)); // 1600_2000

  wzjj_files.push_back(InputFile(xsec_wzjj)); // wzjj 
  wprime400_files.push_back(InputFile(xsec_wprime400)); // 400 GeV


 

  return 0;
}





//Set the branch addresses that we need for the analysis
//-----------------------------------------------------------
void Set_Branch_Addresses(TTree* WZtree)
{
//-----------------------------------------------------------
    if(debugme) cout<<"Setting Branch Addresses"<<endl;


    WZtree->SetBranchAddress("W_flavor",&W_flavor);
    WZtree->SetBranchAddress("Z_flavor",&Z_flavor);
    WZtree->SetBranchAddress("W_pt",&W_pt);
    WZtree->SetBranchAddress("Z_pt",&Z_pt);
    WZtree->SetBranchAddress("Z_mass",&Z_mass);
    WZtree->SetBranchAddress("W_transMass",&W_transMass);
    WZtree->SetBranchAddress("numberOfZs",&numberOfZs);
    WZtree->SetBranchAddress("met_et",&met_et);
    WZtree->SetBranchAddress("pfMet_et",&pfMet_et);
    WZtree->SetBranchAddress("WZ_invMassMinPz",&WZ_invMassMinPz);
    //WZtree->SetBranchAddress("WZ_invMassMaxPz",&WZ_invMassMaxPz);
    WZtree->SetBranchAddress("WZ_transMass",&WZ_transMass);
    WZtree->SetBranchAddress("W_leptonIndex",&W_leptonIndex);
    WZtree->SetBranchAddress("Z_leptonIndex1",&Z_leptonIndex1);
    WZtree->SetBranchAddress("Z_leptonIndex2",&Z_leptonIndex2);
    WZtree->SetBranchAddress("triggerBitMask", &triggerBitMask);
  
    WZtree->SetBranchAddress("electron_eta",&electron_eta);
    WZtree->SetBranchAddress("electron_pt",&electron_pt);
    WZtree->SetBranchAddress("electron_et",&electron_et);
    WZtree->SetBranchAddress("electron_isoEtTrackerDr30", &electron_trackIso);
    WZtree->SetBranchAddress("electron_isoEtEcalDr30", &electron_ecaloIso);
    WZtree->SetBranchAddress("electron_isoEtHcalDr30", &electron_hcaloIso);
    WZtree->SetBranchAddress("electron_deltaEtaIn", &electron_deltaEtaIn);
    WZtree->SetBranchAddress("electron_deltaPhiIn", &electron_deltaPhiIn);
    WZtree->SetBranchAddress("electron_eOverP", &electron_eOverP);
    WZtree->SetBranchAddress("electron_hOverE", &electron_hOverE);
    WZtree->SetBranchAddress("electron_sigmaEtaEta", &electron_sigmaEtaEta);
 
    WZtree->SetBranchAddress("muon_eta",&muon_eta);
    WZtree->SetBranchAddress("muon_pt",&muon_pt);
    WZtree->SetBranchAddress("muon_innerD0",&muon_innerD0);
    WZtree->SetBranchAddress("muon_innerD0Error",&muon_innerD0Error);
    WZtree->SetBranchAddress("muon_isoEtTrackerDr30",&muon_trackIso);
    WZtree->SetBranchAddress("muon_isoEtEcalDr30",&muon_ecaloIso); 
    WZtree->SetBranchAddress("muon_isoEtHcalDr30",&muon_hcaloIso); 
    WZtree->SetBranchAddress("muon_fitType",&muon_fitType);
    WZtree->SetBranchAddress("muon_GlobalandTracker",&muon_GlobalandTracker);    
    WZtree->SetBranchAddress("muon_numGlobalMatches",&muon_numGlobalMatches);    
    WZtree->SetBranchAddress("muon_numValidMuonHits",&muon_numValidMuonHits);    
    WZtree->SetBranchAddress("muon_numPixelHits",&muon_globalNpixelHits);
    WZtree->SetBranchAddress("muon_numTrackerHits",&muon_globalNtrackerHits);
    WZtree->SetBranchAddress("muon_numStripHits",&muon_globalNstripHits);
    WZtree->SetBranchAddress("muon_globalChi2",&muon_globalChi2);
    WZtree->SetBranchAddress("muon_globalNdof",&muon_globalNdof);
    WZtree->SetBranchAddress("muon_globalD0",&muon_globalD0);
    
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

    
    hWZInvMass[index]->Fill(WZ_invMassMinPz, weight);
    hWZTransMass[index]->Fill(WZ_transMass, weight);
    hHt[index]->Fill(Ht,weight);
    hZpt[index]->Fill(Z_pt,weight);
    hWpt[index]->Fill(W_pt,weight);
    hGenWZInvMass[index]->Fill(WZ_genMass, weight);
    hMET[index]->Fill(pfMet_et, weight);
    hZmass[index]->Fill(Z_mass,weight);
    if      (abs(Z_flavor) == 11) hZeemass[index]->Fill(Z_mass,weight);
    else if (abs(Z_flavor) == 13) hZmumumass[index]->Fill(Z_mass,weight);
    hWTransmass[index]->Fill(W_transMass,weight);
    
    if(abs(Z_flavor) == 11){
        hElecPt[index]->Fill(electron_pt->at(Z_leptonIndex1),weight);
        hElecdEta[index]->Fill(electron_deltaEtaIn->at(Z_leptonIndex1),weight);
        hElecdPhi[index]->Fill(electron_deltaPhiIn->at(Z_leptonIndex1),weight);
        hElecSigmann[index]->Fill(electron_sigmaEtaEta->at(Z_leptonIndex1),weight);
        hElecEP[index]->Fill(electron_eOverP->at(Z_leptonIndex1),weight);
        hElecHE[index]->Fill(electron_hOverE->at(Z_leptonIndex1),weight);
        //hElecRelCaloIso[index]->Fill(electron_caloIso->at(Z_leptonIndex1)/electron_pt->at(Z_leptonIndex1),weight);
        hElecRelTrkIso[index]->Fill(electron_trackIso->at(Z_leptonIndex1)/electron_pt->at(Z_leptonIndex1),weight);

        hElecPt[index]->Fill(electron_pt->at(Z_leptonIndex2),weight);
        hElecdEta[index]->Fill(electron_deltaEtaIn->at(Z_leptonIndex2),weight);
        hElecdPhi[index]->Fill(electron_deltaPhiIn->at(Z_leptonIndex2),weight);
        hElecSigmann[index]->Fill(electron_sigmaEtaEta->at(Z_leptonIndex2),weight);
        hElecEP[index]->Fill(electron_eOverP->at(Z_leptonIndex2),weight);
        hElecHE[index]->Fill(electron_hOverE->at(Z_leptonIndex2),weight);
        //hElecRelCaloIso[index]->Fill(electron_caloIso->at(Z_leptonIndex2)/electron_pt->at(Z_leptonIndex2),weight);
        hElecRelTrkIso[index]->Fill(electron_trackIso->at(Z_leptonIndex2)/electron_pt->at(Z_leptonIndex2),weight);
    }else if((W_flavor) == 11){
        hElecPt[index]->Fill(electron_pt->at(W_leptonIndex),weight);
        hElecdEta[index]->Fill(electron_deltaEtaIn->at(W_leptonIndex),weight);
        hElecdPhi[index]->Fill(electron_deltaPhiIn->at(W_leptonIndex),weight);
        hElecSigmann[index]->Fill(electron_sigmaEtaEta->at(W_leptonIndex),weight);
        hElecEP[index]->Fill(electron_eOverP->at(W_leptonIndex),weight);
        hElecHE[index]->Fill(electron_hOverE->at(W_leptonIndex),weight);
        //hElecRelCaloIso[index]->Fill(electron_caloIso->at(W_leptonIndex)/electron_pt->at(W_leptonIndex),weight);
        hElecRelTrkIso[index]->Fill(electron_trackIso->at(W_leptonIndex)/electron_pt->at(W_leptonIndex),weight);
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

  for(int i = 0; i != Num_histo_sets; ++i){
      hWZInvMass[i]->Write();   
      hWZTransMass[i]->Write();
      hHt[i]->Write();
      hWpt[i]->Write();
      hZpt[i]->Write();
      hGenWZInvMass[i]->Write();
      hMET[i]->Write();
      hZmass[i]->Write();
      hZeemass[i]->Write();
      hZmumumass[i]->Write();
      hWTransmass[i]->Write();
      
      hElecPt[i]->Write();
      hElecdEta[i]->Write();
      hElecdPhi[i]->Write();
      hElecSigmann[i]->Write();
      hElecEP[i]->Write();
      hElecHE[i]->Write();
      //hElecRelCaloIso[i]->Write();
      hElecRelTrkIso[i]->Write();
      
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
      //////////////////////
      if (debugme) cout<<"Processing event "<<i<<endl;
      //an index to indicate current cut number
      int cut_index = 0;

      //cuts: These need to be ordered the same as Cut_Name in header file
      if(!PassTriggersCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);
      if(!PassValidWandZCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);
      if(!PassMaxNumberOfZsCut()) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i);
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
    //implement it here

    return true;

}//--- PassTriggersCut()

//Check if there are valid W and Z particles in the event
//-----------------------------------------------------------
bool PassValidWandZCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check if there are valid W and Z particles in the event"
                    <<endl;
    bool has_valid_W_and_Z = (Z_flavor && W_flavor); //Cory: We can expand this (maybe in lepton cuts)
    has_valid_W_and_Z = (has_valid_W_and_Z && WZ_invMassMinPz>0); //Cory: Should this be here?
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
bool PassMaxNumberOfZsCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check if there is more Zs than required"<<endl;

    bool passnumZs = maxNumZs >= numberOfZs;
    return passnumZs;

}//--- MaxNumberOfZsCut

//Check W decay Properties
//-----------------------------------------------------------
bool 
PassWDecayCut(){
    switch(W_flavor){
    case PDGMUON:
        //return true;
        return PassWmunuCut();
        break;
    case PDGELEC:
        //return true;
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
    switch(Z_flavor){
    case PDGMUON:
        //return true;
        return PassZmumuCut();
        break;
    case PDGELEC:
        //return true;
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
    bool inEC = inEndCap(electron_eta->at(W_leptonIndex), PDGW);

    if(!PassElecEtaCut        (W_leptonIndex,PDGW,inEC)) return false;
    if(!PassElecEtCut         (W_leptonIndex,PDGW,inEC)) return false;
    if(!PassElecNMissHitsCut  (W_leptonIndex,PDGW,inEC)) return false; //Not Used
    if(!PassElecDistCut       (W_leptonIndex,PDGW,inEC)) return false; //Not Used
    if(!PassElecdCotThetaCut  (W_leptonIndex,PDGW,inEC)) return false; //Not Used
    if(!PassElecTrkRelIsoCut  (W_leptonIndex,PDGW,inEC)) return false;
    if(!PassElecECalRelIsoCut (W_leptonIndex,PDGW,inEC)) return false;
    if(!PassElecHCalRelIsoCut (W_leptonIndex,PDGW,inEC)) return false;
    if(!PassElecSigmaEtaEtaCut(W_leptonIndex,PDGW,inEC)) return false;
    if(!PassElecDeltaPhiCut   (W_leptonIndex,PDGW,inEC)) return false;
    if(!PassElecDeltaEtaCut   (W_leptonIndex,PDGW,inEC)) return false;
    if(!PassElecHOverECut     (W_leptonIndex,PDGW,inEC)) return false;
    
    return true;
}

//Check Wmunu decay Properties
//-----------------------------------------------------------
bool 
PassWmunuCut(){

    if(!PassMuonTypeCut      (W_leptonIndex,PDGW)) return false; 
    if(!PassMuonNpixhitCut   (W_leptonIndex,PDGW)) return false; 
    if(!PassMuonNtrkhitCut   (W_leptonIndex,PDGW)) return false; 
    if(!PassMuonDxyCut       (W_leptonIndex,PDGW)) return false; 
    if(!PassMuonNormChi2Cut  (W_leptonIndex,PDGW)) return false; 
    if(!PassMuonHitsUsedCut  (W_leptonIndex,PDGW)) return false; 
    if(!PassMuonStationsCut  (W_leptonIndex,PDGW)) return false; 
    if(!PassMuonEtaCut       (W_leptonIndex,PDGW)) return false;
    if(!PassMuonPtCut        (W_leptonIndex,PDGW)) return false;
    if(!PassMuonCombRelIsoCut(W_leptonIndex,PDGW)) return false;
    if(!PassMuonMETCut       (W_leptonIndex,PDGW)) return false;

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
        
        bool inEC = inEndCap(electron_eta->at(idx), PDGZ);
        if(!PassElecEtaCut        (idx,PDGZ,inEC)) return false;

        if(!PassElecEtCut         (idx,PDGZ,inEC)) return false;
        if(!PassElecMatchedCut    (idx,PDGZ,inEC)) return false; //Not Used
        if(!PassElecNMissHitsCut  (idx,PDGZ,inEC)) return false; //Not Used
        if(!PassElecDistCut       (idx,PDGZ,inEC)) return false; //Not Used
        if(!PassElecdCotThetaCut  (idx,PDGZ,inEC)) return false; //Not Used
        if(!PassElecZmassCut      (idx,PDGZ,inEC)) return false;
        if(!PassElecTrkRelIsoCut  (idx,PDGZ,inEC)) return false;
        if(!PassElecECalRelIsoCut (idx,PDGZ,inEC)) return false;
        if(!PassElecHCalRelIsoCut (idx,PDGZ,inEC)) return false;
        if(!PassElecSigmaEtaEtaCut(idx,PDGZ,inEC)) return false;
        if(!PassElecDeltaPhiCut   (idx,PDGZ,inEC)) return false;
        if(!PassElecDeltaEtaCut   (idx,PDGZ,inEC)) return false;
        if(!PassElecHOverECut     (idx,PDGZ,inEC)) return false;
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

        if(!PassMuonTypeCut     (idx,PDGZ)) return false; 
        if(!PassMuonDxyCut      (idx,PDGZ)) return false; 
        if(!PassMuonNormChi2Cut (idx,PDGZ)) return false;
        if(!PassMuonNpixhitCut  (idx,PDGZ)) return false; 
        if(!PassMuonNstriphitCut(idx,PDGZ)) return false; 
        if(!PassMuonTrkAbsIsoCut(idx,PDGZ)) return false; 
        if(!PassMuonPtCut       (idx,PDGZ)) return false; //Cory: Causing Trouble?
        if(!PassMuonEtaCut      (idx,PDGZ)) return false;
        if(!PassMuonZmassCut    (idx,PDGZ)) return false;
        if(!PassMuonStationsCut (idx,PDGZ)) return false;
    }
    return true;
}

/////////////////////////////////////////
//Check Electron Pt Cut
//-----------------------------------------------------------
bool PassElecPtCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron Pt Cut"<<endl;
    if      (parent == PDGW){
        return (electron_pt->at(idx) > minWenuPt);
    }else if(parent == PDGZ){
        return (electron_pt->at(idx) > minZeePt);
    }
    return false;
}//--- PassElecPtCut

bool PassElecEtCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    //Cory: Is this supercluster ET???? NO! need to change
    if(debugme) cout<<"Check Electron Et Cut"<<endl;
    if      (parent == PDGW){
        return (electron_et->at(idx) > minWenuEt);
    }else if(parent == PDGZ){
        return (electron_et->at(idx) > minZeeEt);
    }
    return false;
}//--- PassElecEtCut

bool PassElecEtaCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron Eta Cut"<<endl;
    if      (parent == PDGW){
        float eta = electron_eta->at(idx);
        return (inBarrel(eta, parent) || inEndCap(eta,parent));
    }else if(parent == PDGZ){
        float eta = electron_eta->at(idx);
        return (inBarrel(eta, parent) || inEndCap(eta,parent));
    }
    return false;
}//--- PassElecEtaCut

bool PassElecMatchedCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron Matched Cut"<<endl;
    if      (parent == PDGW){
        return true;
    }else if(parent == PDGZ){
        return true;
    }
    return false;
}//--- PassElecMatchedCut

bool PassElecNMissHitsCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron # Missed Hits Cut"<<endl;
    if      (parent == PDGW){
        return true;
    }else if(parent == PDGZ){
        return true;
    }
    return false;
}//--- PassElecNMissedHitsCut

bool PassElecDistCut(int idx, int parent, bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron # Dist Cut"<<endl;
    if      (parent == PDGW){
        return true;
    }else if(parent == PDGZ){
        return true;
    }
    return false;
}//--- PassElecDistCut

bool PassElecdCotThetaCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron Cot theta Cut"<<endl;
    if      (parent == PDGW){
        return true;
    }else if(parent == PDGZ){
        return true;
    }
    return false;
}//--- PassElecCotThetaCut

bool PassElecZmassCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron Zmass Cut"<<endl;
    if      (parent == PDGW){
        cout<<"You are asking for ZeeMass of W boson!!!"<<endl;
        return true;
    }else if(parent == PDGZ){
        return (Z_mass > minZeeMass && Z_mass < maxZeeMass);
    }
    return false;
}//--- PassElecZmassCut

bool PassElecTrkRelIsoCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron ElecTrkRelIso Cut"<<endl;
    if      (parent == PDGW){
        return ((electron_trackIso->at(idx)/electron_pt->at(idx))
                 < maxWenuTrkRelIso[inEC]);
    }else if(parent == PDGZ){
        return ((electron_trackIso->at(idx)/electron_pt->at(idx))
                  < maxZeeTrkRelIso[inEC]);
    }
    return false;
}//--- PassElecTrkRelIsoCut

bool PassElecECalRelIsoCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron EcalRelIso Cut"<<endl;
    if      (parent == PDGW){
        return ((electron_ecaloIso->at(idx)/electron_pt->at(idx))
                  < maxWenuECalRelIso[inEC]);
    }else if(parent == PDGZ){
        return ((electron_ecaloIso->at(idx)/electron_pt->at(idx))
                  < maxZeeECalRelIso[inEC]);
    }
    return false;
}//--- PassElecEcalRelIsoCut

bool PassElecHCalRelIsoCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron HcalRelIso Cut"<<endl;
    if      (parent == PDGW){
        return ((electron_hcaloIso->at(idx)/electron_pt->at(idx))
                < maxWenuHCalRelIso[inEC]);
    }else if(parent == PDGZ){
        return ((electron_hcaloIso->at(idx)/electron_pt->at(idx))
                  < maxZeeHCalRelIso[inEC]);
    }
    return false;
}//--- PassHcalRelIsoElecCut

bool PassElecSigmaEtaEtaCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    //Cory: Should this be the supercluster sigmaetaeta??
    if(debugme) cout<<"Check Electron Sigma nn Cut"<<endl;
    if      (parent == PDGW){
        return (electron_sigmaEtaEta->at(idx) < maxWenuSigmaEtaEta[inEC]);
    }else if(parent == PDGZ){
        return (electron_sigmaEtaEta->at(idx) < maxZeeSigmaEtaEta[inEC]);
    }
    return false;
}//--- PassElecSigmaEtaEtaCut

bool PassElecDeltaPhiCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron dPhi Cut"<<endl;
    if      (parent == PDGW){
        return (electron_deltaPhiIn->at(idx) < maxWenuDeltaPhiIn[inEC]);
    }else if(parent == PDGZ){
        return (electron_deltaPhiIn->at(idx) < maxZeeDeltaPhiIn[inEC]);
    }
    return false;
}//--- PassElecDeltaPhiCut

bool PassElecDeltaEtaCut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron dEta Cut"<<endl;
    if      (parent == PDGW){
        return (electron_deltaEtaIn->at(idx) < maxWenuDeltaEtaIn[inEC]);
    }else if(parent == PDGZ){
        return (electron_deltaEtaIn->at(idx) < maxZeeDeltaEtaIn[inEC]);
    }
    return false;
}//--- PassElecDeltaEtaCut

bool PassElecHOverECut(int idx,int parent,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron HOverE Cut"<<endl;
    if      (parent == PDGW){
        return (electron_hOverE->at(idx) < maxWenuHOverE[inEC]);
    }else if(parent == PDGZ){
        return (electron_hOverE->at(idx) < maxZeeHOverE[inEC]);
    }
    return false;
}//--- PassElecHOverECut

////Muon Cuts//////////////////////////////

//--------------------------
bool PassMuonTypeCut(int idx,int parent){
    if(debugme) cout<<"Check Muon Type Cut"<<endl;
    if      (parent == PDGW){
        //Are all global muons tracker muons? NO!
        return (muon_GlobalandTracker->at(idx) == cutWmunuGlobalandTracker); 
    }else if(parent == PDGZ){
        return (muon_fitType->at(Z_leptonIndex1) == cutZmumuType &&
                muon_fitType->at(Z_leptonIndex2) == cutZmumuType );
    }
    return false;
}//--- PassMuonTypeCut

bool PassMuonNpixhitCut(int idx,int parent){
    if(debugme) cout<<"Check Muon NpixhitCut"<<endl;
    if      (parent == PDGW){
        return (muon_globalNpixelHits->at(idx) > minWmunuNpixhit);
    }else if(parent == PDGZ){
        return (muon_globalNpixelHits->at(idx) > minZmumuNpixhit);
    }
    return false;
}//--- PassMuonNpixhitCut

bool PassMuonNtrkhitCut(int idx,int parent){
    //Use: muon_NtrackerHits
    if(debugme) cout<<"Check Muon NtrkhitCut"<<endl;
    if      (parent == PDGW){
        return (muon_globalNtrackerHits->at(idx) > minWmunuNtrkhit);
    }else if(parent == PDGZ){
        return true;
    }
    return false;
}//--- PassMuonNtrkhitCut

bool PassMuonNormChi2Cut(int idx,int parent){
    if(debugme) cout<<"Check Muon Chi2 Cut"<<endl;
    //Use: muon_globalChi2
    if      (parent == PDGW){
        return ((muon_globalChi2->at(idx)/muon_globalNdof->at(idx) )
                < maxWmunuNormChi2);
    }else if(parent == PDGZ){
        return ((muon_globalChi2->at(idx)/muon_globalNdof->at(idx) ) 
                < maxZmumuNormChi2); 
    }
    return false;
}//--- PassMuonChi2Cut

bool PassMuonHitsUsedCut(int idx,int parent){
    //Num Valid Muon Hits
    if(debugme) cout<<"Check Muon Hits Used Cut"<<endl;
    if      (parent == PDGW){
        return (muon_numValidMuonHits->at(idx) > minWmunuHitsUsed);
    }else if(parent == PDGZ){
        return true;
    }
    return false;
}//--- PassMuonHits Used Cut

bool PassMuonStationsCut(int idx,int parent){
    if(debugme) cout<<"Check Muon Stations Cut"<<endl;
    if      (parent == PDGW){
        return (muon_numGlobalMatches->at(idx) > minWmunuStations);
    }else if(parent == PDGZ){
        return (muon_numGlobalMatches->at(idx) > minZmumuStations);
    }
    return false;
}//--- PassMuonStationsCut

bool PassMuonEtaCut(int idx,int parent){
    if(debugme) cout<<"Check Muon Eta Cut"<<endl;
    if      (parent == PDGW){
        return (muon_eta->at(idx) < maxWmunuEta);
    }else if(parent == PDGZ){
        return (((muon_eta->at(Z_leptonIndex1) < maxZmumuEta1) &&
                 (muon_eta->at(Z_leptonIndex2) < maxZmumuEta2))  ||
                ((muon_eta->at(Z_leptonIndex1) < maxZmumuEta2) &&
                 (muon_eta->at(Z_leptonIndex2) < maxZmumuEta1)));
    }
    return false;
}//--- PassMuonEta Cut

bool PassMuonPtCut(int idx,int parent){
    if(debugme) cout<<"Check Muon Pt Cut"<<endl;
    if      (parent == PDGW){
        return (muon_pt->at(idx) > minWmunuMuonPt);
    }else if(parent == PDGZ){
        return (muon_pt->at(idx) > minZmumuMuonPt);
    }
    return false;
}//--- PassMuonPtCut

bool PassMuonCombRelIsoCut(int idx,int parent){
    if(debugme) cout<<"Check Muon CombRelIso Cut"<<endl;
    if      (parent == PDGW){
        return (((muon_trackIso->at(idx)+muon_ecaloIso->at(idx)+muon_hcaloIso->at(idx))/muon_pt->at(idx))
                < maxWmunuCombRelIso);
    }else if(parent == PDGZ){
        return true;
    }
    return false;
}//--- PassMuonCombRelIsoCut

bool PassMuonMETCut(int idx,int parent){
    if(debugme) cout<<"Check Muon MET Cut"<<endl;
    if      (parent == PDGW){
        return (pfMet_et > minWmunuMET);
    }else if(parent == PDGZ){
        return true;
    }
    return false;
}//--- PassMuonMETCut

bool PassMuonDxyCut(int idx,int parent){
    //Use: muon_globalD0
    if(debugme) cout<<"Check Muon Dxy Cut"<<endl;
    if      (parent == PDGW){
        return (muon_globalD0->at(idx) < maxWmunuDxy);
    }else if(parent == PDGZ){
        return (muon_globalD0->at(idx) < maxZmumuDxy);
    }
    return false;
}//--- PassMuonDxyCut

bool PassMuonNstriphitCut(int idx,int parent){
    if(debugme) cout<<"Check Muon # strip hit Cut"<<endl;
    if      (parent == PDGW){
        return true;
    }else if(parent == PDGZ){
        return (muon_globalNstripHits->at(idx) > minZmumuNstriphit);
    }
    return false;
}//--- PassMuonNstriphitCut

bool PassMuonTrkAbsIsoCut(int idx,int parent){
    if(debugme) cout<<"Check Muon TrkAbsIsoCut"<<endl;
    if      (parent == PDGW){
        return true;
    }else if(parent == PDGZ){
        return (muon_trackIso->at(idx) < maxZmumuTrkAbsIso);
    }
    return false;
}//--- PassMuonTrkAbsIsoCut

bool PassMuonZmassCut(int idx,int parent){
    if(debugme) cout<<"Check Muon Zmass Cut"<<endl;
    if      (parent == PDGW){
        cout<<"You are asking for Zmumu for W boson"<<endl;
        return true;
    }else if(parent == PDGZ){
        return (Z_mass > minZmumuMass && Z_mass < maxZmumuMass);
    }
    return false;
}//--- PassMuonZmassCut

////////////////////////////////

//Check Z Properties


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
  string dir;
  
  dir = "wprime400";
  Load_Input_Files(dir, wprime400_files, lumiPb);
  Get_Distributions(wprime400_files, fout, dir, out);
  
  //dir = "wprime400_WDef";
  //Load_Input_Files(dir, wprime400_WDef_files, lumiPb);
  //Get_Distributions(wprime400_WDef_files, fout, dir, out);

  dir = "wprime500";
  Load_Input_Files(dir, wprime500_files, lumiPb);
  Get_Distributions(wprime500_files, fout, dir, out);
  
  dir = "wprime600";
  Load_Input_Files(dir, wprime600_files, lumiPb);
  Get_Distributions(wprime600_files, fout, dir, out);
  
  dir = "wprime700";
  Load_Input_Files(dir, wprime700_files, lumiPb);
  Get_Distributions(wprime700_files, fout, dir, out);

  dir = "wprime800";
  Load_Input_Files(dir, wprime800_files, lumiPb);
  Get_Distributions(wprime800_files, fout, dir, out);

  dir = "wprime900";
  Load_Input_Files(dir, wprime900_files, lumiPb);
  Get_Distributions(wprime900_files, fout, dir, out);
  
  dir = "wz";
  Load_Input_Files(dir, wz_files, lumiPb);
  Get_Distributions(wz_files, fout, dir, out);
  
  dir = "ttbar";
  Load_Input_Files(dir, ttbar_files, lumiPb);
  Get_Distributions(ttbar_files, fout, dir, out);

  dir = "ttbarfast";
  Load_Input_Files(dir, ttbarfast_files, lumiPb);
  Get_Distributions(ttbarfast_files, fout, dir, out);

  dir = "zz";
  Load_Input_Files(dir, zz_files, lumiPb);
  Get_Distributions(zz_files, fout, dir, out);

  dir = "zgamma";
  Load_Input_Files(dir, zgamma_files, lumiPb);
  Get_Distributions(zgamma_files, fout, dir, out);

  dir = "zjets";
  Load_Input_Files(dir, zjets_files, lumiPb);
  Get_Distributions(zjets_files, fout, dir, out);

  dir = "wjets";
  Load_Input_Files(dir, wjets_files, lumiPb);
  Get_Distributions(wjets_files, fout, dir, out);
  
  dir = "TC400";
  Load_Input_Files(dir, TC400_files, lumiPb);
  Get_Distributions(TC400_files, fout, dir, out);

  //dir = "test";
  //Load_Input_Files(dir, test_files, lumiPb);
  //Get_Distributions(test_files, fout, dir, out);
  
  out.close(); 
  fout->Close();

}//ExecuteAnalysis




