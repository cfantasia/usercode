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

#define ExecuteTTbar_cxx
#include <ExecuteTTbar.h>

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
///Eff Plots///////
  string title = "Expected # of Events / " + convertFloatToStr(lumiPb) + " pb^{-1}";
  hNumEvts = new TH1F("hNumEvts",title.c_str(),Num_histo_sets,0,Num_histo_sets);
  hEffRel = new TH1F("hEffRel","Relative Efficiency",Num_histo_sets,0,Num_histo_sets);
  hEffAbs = new TH1F("hEffAbs","Absolute Efficiency",Num_histo_sets,0,Num_histo_sets);
  for(int i=0; i<Num_histo_sets; ++i) hNumEvts->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());
  for(int i=0; i<Num_histo_sets; ++i) hEffRel ->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());
  for(int i=0; i<Num_histo_sets; ++i) hEffAbs ->GetXaxis()->SetBinLabel(i+1,Cut_Name[i].c_str());

  

}//Declare_Histos

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

  //switch between different sample cases and
  //recruit the files. 
  bool binned = false;
  float cross_sec = 0;
  int Nfiles = -1;
  if (!strcmp(file_desc.c_str(),"wprime400")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime400_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wprime500")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime500_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wprime600")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime600_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wprime700")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime700_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wprime800")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime800_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename, "",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wprime900")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "genWprime900_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename, "",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wenujets")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "WenuJets_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"wmunujets")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "WmunuJets_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"ttbar")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "TTbar_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"ttbarfast")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "TTbarFast_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"ttbar2l")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "TTbar2l_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"zz")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "ZZ_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"zz4l")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "ZZ4l_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"zgamma")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "Zgamma2l_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wz")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "WZ3l_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"zeejets")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "ZeeJets_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"zmumujets")){
          Nfiles = 1;
          binned = false;
          files.push_back(InputFile()); 
          const string filename = "ZmumuJets_WZ.root";
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
                              "","_WZ.root",file_desc);
  }
  else if (!strcmp(file_desc.c_str(),"wjets")){
          Nfiles = 1;
          cross_sec = 24901.3;
          files.push_back(InputFile(cross_sec)); 
          const string filename = "Wjets_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"TC400")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "TC400_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"test")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "test_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"EGSep17ReReco")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "EGSep17ReReco_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"MuSep17ReReco")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "MuSep17ReReco_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"ElectronPromptReco")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "ElectronPromptReco_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"MuPromptReco")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "MuPromptReco_WZ.root";
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
      
      if(files[i].x_sect == 0) files[i].weight = 1;

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

    //WZtree->SetBranchAddress("HLT_Mu9", &HLT_Mu9);
    //WZtree->SetBranchAddress("HLT_Photon10_L1R", &HLT_Photon10_L1R);

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
    WZtree->SetBranchAddress("electron_pdgId",&electron_pdgId);
    WZtree->SetBranchAddress("electron_phi",&electron_phi);
    WZtree->SetBranchAddress("electron_eta",&electron_eta);
    WZtree->SetBranchAddress("electron_ScEta",&electron_ScEta);
    WZtree->SetBranchAddress("electron_pt",&electron_pt);
    WZtree->SetBranchAddress("electron_energy",&electron_energy);
    WZtree->SetBranchAddress("electron_px",&electron_px);
    WZtree->SetBranchAddress("electron_py",&electron_py);
    WZtree->SetBranchAddress("electron_pz",&electron_pz);
    WZtree->SetBranchAddress("electron_ScEt",&electron_ScEt);
    WZtree->SetBranchAddress("electron_trackIso", &electron_trackIso);
    WZtree->SetBranchAddress("electron_ecalIso", &electron_ecaloIso);
    WZtree->SetBranchAddress("electron_hcalIso", &electron_hcaloIso);
    WZtree->SetBranchAddress("electron_deltaEtaIn", &electron_deltaEtaIn);
    WZtree->SetBranchAddress("electron_deltaPhiIn", &electron_deltaPhiIn);
    WZtree->SetBranchAddress("electron_eOverP", &electron_eOverP);
    WZtree->SetBranchAddress("electron_hOverE", &electron_hOverE);
    WZtree->SetBranchAddress("electron_sigmaEtaEta", &electron_sigmaEtaEta);
 
    WZtree->SetBranchAddress("muon_pdgId",&muon_pdgId);
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
        
}//Fill_Histos





//------------------------------------------------------------------------
void saveHistos(TFile * fout, string dir)
{
//------------------------------------------------------------------------
  if (debugme) cout<<"Save Histos....."<<endl;
  fout->cd(); 
  fout->mkdir(dir.c_str()); 
  fout->cd(dir.c_str());

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
      //////////////////////
      if (debugme) cout<<"Processing event "<<i<<endl;

      //an index to indicate current cut number
      int cut_index = 0;//Incremented in Tabulate_Me
      

      Tabulate_Me(Num_surv_cut,cut_index,weight,i); //Before All Cuts
      
      if( !PassFakeLeptonTagCut() ) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i); //After Tag Cut

      if( !PassFakeLeptonProbeCut() ) continue;
      Tabulate_Me(Num_surv_cut,cut_index,weight,i); //After Probe Cut

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
bool PassTightCut(int idx, int type)
{
    if(type == 11){
        bool inEC = inEndCap(electron_ScEta->at(idx));
        if(!PassElecEtCut         (idx,PDGW)) return false;
        if(!PassElecTrkRelIsoCut  (idx,inEC)) return false;
        if(!PassElecECalRelIsoCut (idx,inEC)) return false;
        if(!PassElecHCalRelIsoCut (idx,inEC)) return false;

    }else if (type == 13){
        if(!PassMuonPtCut(idx, PDGW)) return false;
        if(!PassMuonCombRelIsoCut(idx)) return false;
    }
    return true;
}//--- Tight Cut

//Pass Fake Lepton Tag Cut
//-----------------------------------------------------------
bool PassFakeLeptonTagCut()
{
    if( !W_flavor ) return false;
    if(electron_pt->size() + muon_pt->size() == 2) cout<<"Only 2 leptons in event"<<endl;
    if( W_transMass < 20 ) return false;
    if( pfMet_et < 20) return false;
    if( !PassTightCut(W_leptonIndex, W_flavor)) return false;

    return true;
}//--- Tag Cut

//Pass Fake Lepton Probe Cut
//-----------------------------------------------------------
bool PassFakeLeptonProbeCut()
{
    
    //cout<<"There are "<<electron_pdgId->size() + muon_pdgId->size()<<" leptons in event"<<endl;


    if(electron_pdgId->size() != 1)          return false;
    if(muon_pdgId->size() != 1)              return false;

    cout<<"There are "<<electron_pdgId->size()<<" electrons and "
        <<muon_pdgId->size()<<" muons and "
        <<W_flavor<<" is W_flavor!!!"<<endl;


    if(muon_pdgId->at(0) * electron_pdgId->at(0) < 0.0) return false;
    
    cout<<"Testing other lepton!!!"<<endl;

    if(W_flavor == 11){
        return PassTightCut(0, PDGMUON); //Check the other lepton
    }else if(W_flavor == 13){
        return PassTightCut(0, PDGELEC);
    }
    

    return true;
}//--- Probe Cut

void 
UseSample(string dir, vector<InputFile> & files, 
          float lumiPb, TFile* fout, ofstream & out){
    Load_Input_Files(dir, files, lumiPb);
    Get_Distributions(files, fout, dir, out);
}

//-----------------------------------------------------------
void ExecuteTTbar()
{
//-----------------------------------------------------------


  if (debugme)cout<<"Master macro to execute analysis"<<endl;

  //lumiPb now defined in ExecuteAnalysis.h
  cout<<"Using integrated luminosity of "<<lumiPb<<" inv pb"<<endl;
 
  //name of file where to write all histograms
  TFile *fout = new TFile("TTbar_analysis.root","recreate");
 
  //containers to
  //include signal and background files
  vector<InputFile> wprime400_files;
  vector<InputFile> wprime500_files;
  vector<InputFile> wprime600_files;
  vector<InputFile> wprime700_files;
  vector<InputFile> wprime800_files;
  vector<InputFile> wprime900_files;
  vector<InputFile> wz_files;
  vector<InputFile> ttbar_files;
  vector<InputFile> ttbarfast_files;
  vector<InputFile> ttbar2l_files;
  vector<InputFile> zz_files;
  vector<InputFile> zz4l_files;
  vector<InputFile> zgamma_files;
  vector<InputFile> zeejets_files;
  vector<InputFile> zmumujets_files;
  vector<InputFile> wenujets_files;
  vector<InputFile> wmunujets_files;
  vector<InputFile> TC400_files;


  vector<InputFile> EGSep17_files;
  vector<InputFile> MuSep17_files;
  vector<InputFile> ElectronPrompt_files;
  vector<InputFile> MuPromptReco_files;


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
  //UseSample("wprime400",wprime400_files, lumiPb, fout, out);
  //UseSample("wprime500",wprime500_files, lumiPb, fout, out);
  //UseSample("wprime600",wprime600_files, lumiPb, fout, out);
  //UseSample("wprime700",wprime700_files, lumiPb, fout, out);
  //UseSample("wprime800",wprime800_files, lumiPb, fout, out);
  //UseSample("wprime900",wprime900_files, lumiPb, fout, out);
  //UseSample("TC400", TC400_files, lumiPb, fout, out);
  
  //UseSample("wz",wz_files, lumiPb, fout, out);
  //UseSample("ttbar",ttbar_files, lumiPb, fout, out);
  //UseSample("ttbar2l",ttbar2l_files, lumiPb, fout, out);
  //UseSample("zz",zz_files, lumiPb, fout, out);
  //UseSample("zz4l",zz4l_files, lumiPb, fout, out);
  //UseSample("zgamma",zgamma_files, lumiPb, fout, out);
  //UseSample("zeejets",zeejets_files, lumiPb, fout, out);
  //UseSample("zmumujets",zmumujets_files, lumiPb, fout, out);
  //UseSample("wenujets",wenujets_files, lumiPb, fout, out);
  //UseSample("wmunujets",wmunujets_files, lumiPb, fout, out);
  
  
  UseSample("EGSep17ReReco",EGSep17_files, lumiPb, fout, out);
  UseSample("MuSep17ReReco",MuSep17_files, lumiPb, fout, out);
  UseSample("ElectronPromptReco",ElectronPrompt_files, lumiPb, fout, out);
  UseSample("MuPromptReco",MuPromptReco_files, lumiPb, fout, out);
   

  out.close(); 
  fout->Close();

}//ExecuteTTbar





//  LocalWords:  pzMinPz
