#ifndef _ExecuteFunctions_cxx_
#define _ExecuteFunctions_cxx_

#include <ExecuteFunctions.h>

///////////////Utilities//////////////////
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
bool Load_Input_Files(string file_desc, 
                      vector<InputFile> & files)
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
  else if (!strcmp(file_desc.c_str(),"interesting")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "Interesting_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"EGSep17ReReco")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "TrileptonPatTuple-EGSep17ReReco-v02_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"MuSep17ReReco")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "TrileptonPatTuple-MuSep17ReReco-v02_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"ElectronPromptReco")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "TrileptonPatTuple-ElectronPromptReco_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"MuPromptReco")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "TrileptonPatTuple-MuPromptReco_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"EGSep17ReReco_Dilepton")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "DileptonPatTuple-EGSep17ReReco-v02_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"MuSep17ReReco_Dilepton")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "DileptonPatTuple-MuSep17ReReco-v02_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"ElectronPromptReco_Dilepton")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "DileptonPatTuple-ElectronPromptReco-v02_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else if (!strcmp(file_desc.c_str(),"MuPromptReco_Dilepton")){
          Nfiles = 1;
          files.push_back(InputFile()); 
          const string filename = "DileptonPatTuple-MuPromptReco-v02_WZ.root";
          RecruitOrderedFiles(files,Nfiles,0,0,
                              filename,"",file_desc);
  } 
  else{
      cout<<"No samples were found with the name "<<file_desc<<endl;
      return false;
  }

  
  float Total_Nprod_evt = 0;
  
  //Loop over the files in order to get the correct tree
  //and the number of total events 
  for(int i = 0; i != Nfiles; ++i){ // loop over input files
      string pathname = files[i].pathname;
      TFile * file = TFile::Open(pathname.c_str());
      if(!file || !(file->IsOpen())){
          cerr <<" *** Missing file: "<< pathname << " !!! "<<endl; 
          return false;
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
  
  return true;
}


//Set the branch addresses that we need for the analysis
//-----------------------------------------------------------
void Set_Branch_Addresses(TTree* WZtree)
{
//-----------------------------------------------------------
    if(debugme) cout<<"Setting Branch Addresses"<<endl;

    WZtree->SetBranchAddress("runNumber", &runNumber);
    WZtree->SetBranchAddress("eventID", &eventID);
    WZtree->SetBranchAddress("lumiBlock", &lumiBlock);

    WZtree->SetBranchAddress("pass_HLT_Photon10_Cleaned_L1R", &pass_HLT_Photon10_Cleaned_L1R);
    WZtree->SetBranchAddress("pass_HLT_Photon10_L1R", &pass_HLT_Photon10_L1R);
    WZtree->SetBranchAddress("pass_HLT_Photon15_Cleaned_L1R", &pass_HLT_Photon15_Cleaned_L1R);
    WZtree->SetBranchAddress("pass_HLT_Photon15_L1R", &pass_HLT_Photon15_L1R);
    WZtree->SetBranchAddress("pass_HLT_Ele12_SW_EleIdIsolNoDEtaInEE_L1R", &pass_HLT_Ele12_SW_EleIdIsolNoDEtaInEE_L1R);
    WZtree->SetBranchAddress("pass_HLT_Ele10_LW_EleId_L1R", &pass_HLT_Ele10_LW_EleId_L1R);
    WZtree->SetBranchAddress("pass_HLT_Ele10_SW_EleId_L1R", &pass_HLT_Ele10_SW_EleId_L1R);
    WZtree->SetBranchAddress("pass_HLT_Ele10_SW_L1R", &pass_HLT_Ele10_SW_L1R);
    WZtree->SetBranchAddress("pass_HLT_Ele12_SW_TightEleIdIsol_L1R", &pass_HLT_Ele12_SW_TightEleIdIsol_L1R);
    WZtree->SetBranchAddress("pass_HLT_Ele12_SW_TighterEleIdIsol_L1R_v1", &pass_HLT_Ele12_SW_TighterEleIdIsol_L1R_v1);
    WZtree->SetBranchAddress("pass_HLT_Ele15_LW_L1R", &pass_HLT_Ele15_LW_L1R);
    WZtree->SetBranchAddress("pass_HLT_Ele15_SW_L1R", &pass_HLT_Ele15_SW_L1R);
    WZtree->SetBranchAddress("pass_HLT_Ele17_SW_TighterEleIdIsol_L1R_v2", &pass_HLT_Ele17_SW_TighterEleIdIsol_L1R_v2);
    WZtree->SetBranchAddress("pass_HLT_Mu11", &pass_HLT_Mu11);
    WZtree->SetBranchAddress("pass_HLT_Mu15_v1", &pass_HLT_Mu15_v1);
    WZtree->SetBranchAddress("pass_HLT_Mu3", &pass_HLT_Mu3);
    WZtree->SetBranchAddress("pass_HLT_Mu5", &pass_HLT_Mu5);
    WZtree->SetBranchAddress("pass_HLT_Mu9", &pass_HLT_Mu9);

    WZtree->SetBranchAddress("prescale_HLT_Photon10_Cleaned_L1R", &prescale_HLT_Photon10_Cleaned_L1R);
    WZtree->SetBranchAddress("prescale_HLT_Photon10_L1R", &prescale_HLT_Photon10_L1R);
    WZtree->SetBranchAddress("prescale_HLT_Photon15_Cleaned_L1R", &prescale_HLT_Photon15_Cleaned_L1R);
    WZtree->SetBranchAddress("prescale_HLT_Photon15_L1R", &prescale_HLT_Photon15_L1R);
    WZtree->SetBranchAddress("prescale_HLT_Ele12_SW_EleIdIsolNoDEtaInEE_L1R", &prescale_HLT_Ele12_SW_EleIdIsolNoDEtaInEE_L1R);
    WZtree->SetBranchAddress("prescale_HLT_Ele10_LW_EleId_L1R", &prescale_HLT_Ele10_LW_EleId_L1R);
    WZtree->SetBranchAddress("prescale_HLT_Ele10_SW_EleId_L1R", &prescale_HLT_Ele10_SW_EleId_L1R);
    WZtree->SetBranchAddress("prescale_HLT_Ele10_SW_L1R", &prescale_HLT_Ele10_SW_L1R);
    WZtree->SetBranchAddress("prescale_HLT_Ele12_SW_TightEleIdIsol_L1R", &prescale_HLT_Ele12_SW_TightEleIdIsol_L1R);
    WZtree->SetBranchAddress("prescale_HLT_Ele12_SW_TighterEleIdIsol_L1R_v1", &prescale_HLT_Ele12_SW_TighterEleIdIsol_L1R_v1);
    WZtree->SetBranchAddress("prescale_HLT_Ele15_LW_L1R", &prescale_HLT_Ele15_LW_L1R);
    WZtree->SetBranchAddress("prescale_HLT_Ele15_SW_L1R", &prescale_HLT_Ele15_SW_L1R);
    WZtree->SetBranchAddress("prescale_HLT_Ele17_SW_TighterEleIdIsol_L1R_v2", &prescale_HLT_Ele17_SW_TighterEleIdIsol_L1R_v2);
    WZtree->SetBranchAddress("prescale_HLT_Mu11", &prescale_HLT_Mu11);
    WZtree->SetBranchAddress("prescale_HLT_Mu15_v1", &prescale_HLT_Mu15_v1);
    WZtree->SetBranchAddress("prescale_HLT_Mu3", &prescale_HLT_Mu3);
    WZtree->SetBranchAddress("prescale_HLT_Mu5", &prescale_HLT_Mu5);
    WZtree->SetBranchAddress("prescale_HLT_Mu9", &prescale_HLT_Mu9);

    WZtree->SetBranchAddress("pfW_flavor",&W_flavor);
    WZtree->SetBranchAddress("Z_flavor",&Z_flavor);
    WZtree->SetBranchAddress("pfW_pt",&W_pt);
    WZtree->SetBranchAddress("Z_pt",&Z_pt);
    WZtree->SetBranchAddress("Z_mass",&Z_mass);
    WZtree->SetBranchAddress("pfW_transMass",&W_transMass);
    WZtree->SetBranchAddress("pfW_phi",&W_phi);
    WZtree->SetBranchAddress("pfW_eta",&W_eta);
    WZtree->SetBranchAddress("numberOfZs",&numberOfZs);
    WZtree->SetBranchAddress("met_phi",&met_phi);
    WZtree->SetBranchAddress("met_et",&met_et);
    WZtree->SetBranchAddress("pfMet_et",&pfMet_et);
    WZtree->SetBranchAddress("tcMet_et", &tcMet_et);
    WZtree->SetBranchAddress("pfWZ_invMassMinPz",&WZ_invMassMinPz);
    WZtree->SetBranchAddress("pfW_neutrino_pzMinPz",&W_neutrino_pzMinPz);
    WZtree->SetBranchAddress("pfW_neutrino_pzMaxPz",&W_neutrino_pzMaxPz);
    WZtree->SetBranchAddress("WZ_transMass",&WZ_transMass);
    WZtree->SetBranchAddress("pfW_leptonIndex",&W_leptonIndex);
    WZtree->SetBranchAddress("Z_leptonIndex1",&Z_leptonIndex1);
    WZtree->SetBranchAddress("Z_leptonIndex2",&Z_leptonIndex2);

    WZtree->SetBranchAddress("electron_pdgId",&electron_pdgId);
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

//Tabulate results after the cut has been passed
//-----------------------------------------------------------
void Tabulate_Me(int Num_surv_cut[], int& cut_index, 
                 const float& weight)
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

void 
UseSample(string dir, vector<InputFile> & files, 
          TFile* fout, ofstream & out){
    if(!Load_Input_Files(dir, files)){
        return;
    }
    Get_Distributions(files, fout, dir, out);
}

void PrintEvent(){
    cout<<"run #: "<<runNumber
        <<" lumi: "<<lumiBlock
        <<" eventID: "<<eventID<<endl
        <<" Z_flavor: "<<Z_flavor
        <<" Z_mass: "<<Z_mass
        <<" W_flavor: "<<W_flavor
        <<" W_transMass: "<<W_transMass
        <<endl;

    if(Z_flavor == 11){
        cout<<" Z_electron_pt1 "<<electron_pt->at(Z_leptonIndex1)
            <<" Z_electron_pt2 "<<electron_pt->at(Z_leptonIndex2);
    }else{
        cout<<" Z_muon_pt1 "<<muon_pt->at(Z_leptonIndex1)
            <<" Z_muon_pt2 "<<muon_pt->at(Z_leptonIndex2);
    }

    cout<<endl;

    if(W_flavor == 11){
        cout<<" W_electron_pt "<<electron_pt->at(W_leptonIndex);
    }else{
        cout<<" W_muon_pt "<<muon_pt->at(W_leptonIndex);
    }
    
    
    cout<<" pfMet_et: "<<pfMet_et
        <<" tcMet_et: "<<tcMet_et
        <<" met_et: "<<met_et<<endl
        <<" Ht: "<<Ht
        <<" Zpt: "<<Z_pt
        <<" Wpt: "<<W_pt<<endl
        <<" WZ Mass: "<<WZ_invMassMinPz<<endl
        <<" # Elec: "<<electron_pt->size()
        <<" # Muon: "<<muon_pt->size()
        <<endl<<endl;
    return;
}

#endif//#define _ExecuteFunctions_h_
