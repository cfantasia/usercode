#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include "TFile.h"
#include "TTree.h" 
#include "TH1.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TMath.h"
#include "TEntryList.h"
#include "TLegend.h"
#include "THStack.h"
#include <vector>
#include "TROOT.h"
#include "TStyle.h"
#include "TLine.h"


void
ComparePz(){  

  TFile *f = TFile::Open("~/nobackup/38X/TrileptonPatTupleMC-Wprime400_WZ.root", "read");
  //TFile *f = TFile::Open("~/nobackup/38X/TrileptonPatTupleMC-Wprime600_WZ.root", "read");
  //TFile *f = TFile::Open("~/nobackup/38X/TrileptonPatTupleMC-WZ3l_WZ.root", "read");
  TTree* WZ = f->Get("WZ");

  int right[8] = {0};
  int wrong = 0;

  TH1F* hminpz = new TH1F("hminpz", "Delta Min PZ", 40, -20, 20);
  TH1F* hmaxpz = new TH1F("hmaxpz", "Delta Max PZ", 40, -20, 20);
  TH1F* hminr = new TH1F("hminr", "Delta Min R", 40, -20, 20);
  TH1F* hmaxr = new TH1F("hmaxr", "Delta Max R", 40, -20, 20);
  TH1F* hminw = new TH1F("hminw", "Delta Min W pz", 40, -20, 20);
  TH1F* hmaxw = new TH1F("hmaxw", "Delta Max W pz", 40, -20, 20);
  TH1F* hmintot = new TH1F("hmintot", "Delta Min tot pz", 40, -20, 20);
  TH1F* hmaxtot = new TH1F("hmaxtot", "Delta Max tot pz", 40, -20, 20);

  vector<float>   *electron_energy;
  vector<float>   *muon_energy;
  vector<float>   *electron_px;
  vector<float>   *muon_px;
  vector<float>   *electron_py;
  vector<float>   *muon_py;
  vector<float>   *electron_pz;
  vector<float>   *muon_pz;

  Float_t   metGen_et;
  Float_t        met_et;
  Float_t        met_phi;

  Int_t           W_flavor;
  Int_t           Z_flavor;

  Int_t           W_leptonIndex;
  Int_t           Z_leptonIndex1;
  Int_t           Z_leptonIndex2;

  Float_t         W_neutrino_pzMaxAngle;
  Float_t         W_neutrino_pzMaxPz;
  Float_t         W_neutrino_pzMinAngle;
  Float_t         W_neutrino_pzMinPz;

  Float_t        WZ_invMassMinPz;
  Float_t        WZ_invMassMaxPz;

  WZ->SetBranchAddress("pfW_flavor",&W_flavor);
  WZ->SetBranchAddress("Z_flavor",&Z_flavor);

  WZ->SetBranchAddress("pfW_leptonIndex",&W_leptonIndex);
  WZ->SetBranchAddress("Z_leptonIndex1",&Z_leptonIndex1);
  WZ->SetBranchAddress("Z_leptonIndex2",&Z_leptonIndex2);

  WZ->SetBranchAddress("electron_energy",&electron_energy);
  WZ->SetBranchAddress("muon_energy",&muon_energy);

  WZ->SetBranchAddress("electron_px",&electron_px);
  WZ->SetBranchAddress("muon_px",&muon_px);

  WZ->SetBranchAddress("electron_py",&electron_py);
  WZ->SetBranchAddress("muon_py",&muon_py);

  WZ->SetBranchAddress("electron_pz",&electron_pz);
  WZ->SetBranchAddress("muon_pz",&muon_pz);

  WZ->SetBranchAddress("metGen_et", &metGen_et);
  WZ->SetBranchAddress("met_et", &met_et);
  WZ->SetBranchAddress("met_phi", &met_phi);

  WZ->SetBranchAddress("pfW_neutrino_pzMaxAngle", &W_neutrino_pzMaxAngle);
  WZ->SetBranchAddress("pfW_neutrino_pzMaxPz", &W_neutrino_pzMaxPz);
  WZ->SetBranchAddress("pfW_neutrino_pzMinAngle", &W_neutrino_pzMinAngle);
  WZ->SetBranchAddress("pfW_neutrino_pzMinPz", &W_neutrino_pzMinPz);

  WZ->SetBranchAddress("pfWZ_invMassMinPz",&WZ_invMassMinPz);
  WZ->SetBranchAddress("pfWZ_invMassMaxPz",&WZ_invMassMaxPz);

  vector<int>     *genMother_pdgId;
  vector<int>     *genParticle_pdgId;
  WZ->SetBranchAddress("genMother_pdgId", &genMother_pdgId);
  WZ->SetBranchAddress("genParticle_pdgId", &genParticle_pdgId);
    
  vector<float>   *genMother_pz;
  vector<float>   *genParticle_pz;
  WZ->SetBranchAddress("genMother_pz", &genMother_pz);
  WZ->SetBranchAddress("genParticle_pz", &genParticle_pz);

  int nevents = WZ->GetEntries();
  for(int i = 0; i != nevents; ++i){//event loop
    cout<<endl<<"Event: "<<i<<endl;
    WZ->GetEntry(i);
    if(!W_flavor) continue;
    if(W_neutrino_pzMinPz == 0 && W_neutrino_pzMinPz == 0) continue;
    /////////
    float WLep_pz = 0;
    if     (W_flavor == 11) WLep_pz += electron_pz->at(W_leptonIndex);
    else if(W_flavor == 13) WLep_pz += muon_pz->at(W_leptonIndex);

    float TriLep_pz = WLep_pz;

    if(!Z_flavor){
      cout<<" No Z!!!"<<endl;
      continue;
    }

    if     (Z_flavor == 11){
      TriLep_pz += electron_pz->at(Z_leptonIndex1);
      TriLep_pz += electron_pz->at(Z_leptonIndex2);
    }else if(Z_flavor == 13){
      TriLep_pz += muon_pz->at(Z_leptonIndex1);
      TriLep_pz += muon_pz->at(Z_leptonIndex2);
    }else cout<<"What did it decay to ???"<<endl;

    cout<<"W Lepton pz: "<<WLep_pz
        <<" 3 Lepton pz: "<<TriLep_pz
        <<" Min: "<<W_neutrino_pzMinPz
        <<" Max: "<<W_neutrino_pzMaxPz
        <<endl;

    //X, Y, Z, E
    TLorentzVector Z;
    TLorentzVector W1;
    TLorentzVector W2;
    
    float neu_px = met_et*cos(met_phi);
    float neu_py = met_et*sin(met_phi);
    float W_neutrino_EMinPz = sqrt(neu_px**2+neu_py**2+W_neutrino_pzMinPz**2);
    float W_neutrino_EMaxPz = sqrt(neu_px**2+neu_py**2+W_neutrino_pzMaxPz**2);

    if(W_flavor == 11){
      W1.SetPxPyPzE(electron_px->at(W_leptonIndex) + neu_px,
                    electron_py->at(W_leptonIndex) + neu_py,
                    electron_pz->at(W_leptonIndex) + W_neutrino_pzMinPz,
                    electron_energy->at(W_leptonIndex) + W_neutrino_EMinPz);
      W2.SetPxPyPzE(electron_px->at(W_leptonIndex) + neu_px,
                    electron_py->at(W_leptonIndex) + neu_py,
                    electron_pz->at(W_leptonIndex) + W_neutrino_pzMaxPz,
                    electron_energy->at(W_leptonIndex) + W_neutrino_EMaxPz);
    }else if(W_flavor == 13){
      W1.SetPxPyPzE(muon_px->at(W_leptonIndex) + neu_px,
                    muon_py->at(W_leptonIndex) + neu_py,
                    muon_pz->at(W_leptonIndex) + W_neutrino_pzMinPz,
                    muon_energy->at(W_leptonIndex) + W_neutrino_EMinPz);
      W2.SetPxPyPzE(muon_px->at(W_leptonIndex) + neu_px,
                    muon_py->at(W_leptonIndex) + neu_py,
                    muon_pz->at(W_leptonIndex) + W_neutrino_pzMaxPz,
                    muon_energy->at(W_leptonIndex) + W_neutrino_EMaxPz);
    }

    if(Z_flavor == 11){
      Z.SetPxPyPzE(electron_px->at(Z_leptonIndex1) + electron_px->at(Z_leptonIndex2),
                   electron_py->at(Z_leptonIndex1) + electron_py->at(Z_leptonIndex2),
                   electron_pz->at(Z_leptonIndex1) + electron_pz->at(Z_leptonIndex2),
                   electron_energy->at(Z_leptonIndex1) + electron_energy->at(Z_leptonIndex2));
    }else if(Z_flavor == 13){
      Z.SetPxPyPzE(muon_px->at(Z_leptonIndex1) + muon_px->at(Z_leptonIndex2),
                   muon_py->at(Z_leptonIndex1) + muon_py->at(Z_leptonIndex2),
                   muon_pz->at(Z_leptonIndex1) + muon_pz->at(Z_leptonIndex2),
                   muon_energy->at(Z_leptonIndex1) + muon_energy->at(Z_leptonIndex2));
    }

    float dR1 = Z.DeltaR(W1);
    float dR2 = Z.DeltaR(W2);
    cout<<" dR1: "<<dR1<<" dR2: "<<dR2<<endl;

    ///////////////////////////
    float W_neutrino_pzMinR = 0;
    float W_neutrino_pzMaxR = 0;
    float op1 = fabs(dR1);
    float op2 = fabs(dR2);
        
    if(op1 > op2){//op2 is better
      W_neutrino_pzMinR = W_neutrino_pzMaxPz;
      W_neutrino_pzMaxR = W_neutrino_pzMinPz;
    }else{
      W_neutrino_pzMinR = W_neutrino_pzMinPz;
      W_neutrino_pzMaxR = W_neutrino_pzMaxPz;
    }


    ///////////////////////////
    float W_neutrino_pzMinW = 0;
    float W_neutrino_pzMaxW = 0;
    op1 = fabs(WLep_pz + W_neutrino_pzMinPz);
    op2 = fabs(WLep_pz + W_neutrino_pzMaxPz);
        
    if(op1 > op2){//op2 is better
      cout<<"Bigger is better!"<<endl;
      W_neutrino_pzMinW = W_neutrino_pzMaxPz;
      W_neutrino_pzMaxW = W_neutrino_pzMinPz;
    }else{
      //cout<<"Good things in small packages"<<endl;
      W_neutrino_pzMinW = W_neutrino_pzMinPz;
      W_neutrino_pzMaxW = W_neutrino_pzMaxPz;
    }

    ///////////////////////////
    float W_neutrino_pzMinTot = 0;
    float W_neutrino_pzMaxTot = 0;      
    op1 = fabs(TriLep_pz + W_neutrino_pzMinPz);
    op2 = fabs(TriLep_pz + W_neutrino_pzMaxPz);
        
    if(op1 > op2){//op2 is better
      //cout<<"Bigger is better!"<<endl;
      W_neutrino_pzMinTot = W_neutrino_pzMaxPz;
      W_neutrino_pzMaxTot = W_neutrino_pzMinPz;
    }else{
      //cout<<"Good things in small packages"<<endl;
      W_neutrino_pzMinTot = W_neutrino_pzMinPz;
      W_neutrino_pzMaxTot = W_neutrino_pzMaxPz;
    }
      
    //cout<<"";



    if(fabs(W_neutrino_pzMinPz) > fabs(W_neutrino_pzMaxPz)){
      cout<<"Wrong Choice!!!"<<endl;
      cout<<"Wrong: "<<WZ_invMassMinPz<<" Right: "<<WZ_invMassMaxPz<<endl;
      wrong++;
    }

    float w_genpz = -1;
    float lep_genpz = -1;
    float neu_genpz = -1;
    for(unsigned int part=0; part!=genParticle_pdgId->size(); part++){
      if(abs(genMother_pdgId->at(part)) == 24){

        w_genpz = genMother_pz->at(part);
        lep_genpz = genParticle_pz->at(part);
        neu_genpz = genMother_pz->at(part) - genParticle_pz->at(part);
        
          cout<<"W pz: "<<w_genpz<<"   pdg: "<<genMother_pdgId->at(part)<<endl;
          cout<<"lep gen pz: "<<lep_genpz<<"  pdg: "<<genParticle_pdgId->at(part)<<endl;
          cout<<"lep rec pz: "<<WLep_pz<<"  fla: "<<W_flavor<<endl;
          cout<<"tot lep pz: "<<TriLep_pz<<endl;
          cout<<"nu gen pz: "<<neu_genpz<<" *****"<<endl;
          cout<<"nu min pz: "<<W_neutrino_pzMinPz
              <<"  nu max pz: "<<W_neutrino_pzMaxPz<<endl;
          cout<<"nu min R:"<<W_neutrino_pzMinR
          <<"  nu max R:"<<W_neutrino_pzMaxR<<endl;
          cout<<"nu min ang:"<<W_neutrino_pzMinAngle
              <<"  nu max ang:"<<W_neutrino_pzMaxAngle<<endl;
          cout<<"nu min w:"<<W_neutrino_pzMinW
              <<"  nu max w:"<<W_neutrino_pzMaxW<<endl;
          cout<<"nu min tot:"<<W_neutrino_pzMinTot
              <<"  nu max tot:"<<W_neutrino_pzMaxTot<<endl;
        
        float range = 50;
        if(fabs(W_neutrino_pzMinPz-neu_genpz) < range) right[0]++;
        if(fabs(W_neutrino_pzMaxPz-neu_genpz) < range) right[1]++;
        
        if(fabs(W_neutrino_pzMinR-neu_genpz) < range) right[2]++;
        if(fabs(W_neutrino_pzMaxR-neu_genpz) < range) right[3]++;
        
        if(fabs(W_neutrino_pzMinW-neu_genpz) < range) right[4]++;
        if(fabs(W_neutrino_pzMaxW-neu_genpz) < range) right[5]++;
        
        if(fabs(W_neutrino_pzMinTot-neu_genpz) < range) right[6]++;
        if(fabs(W_neutrino_pzMaxTot-neu_genpz) < range) right[7]++;

        break;
      }
    }
    if(neu_genpz == -1){
      cout<<"Didn't find a W in this event!!!!!!"<<endl;
      continue;
    }
    ////////////

    hminpz->Fill(W_neutrino_pzMinPz-neu_genpz);
    hmaxpz->Fill(W_neutrino_pzMaxPz-neu_genpz);
    hminr->Fill(W_neutrino_pzMinR-neu_genpz);
    hmaxr->Fill(W_neutrino_pzMaxR-neu_genpz);
        
    hminw->Fill(W_neutrino_pzMinW-neu_genpz);
    hmaxw->Fill(W_neutrino_pzMaxW-neu_genpz);
    hmintot->Fill(W_neutrino_pzMinTot-neu_genpz);
    hmaxtot->Fill(W_neutrino_pzMaxTot-neu_genpz);
        
  }
    
  THStack* hs = new THStack("hs", "Neutrino Pz (Reco-Gen)");
  hminpz->SetLineColor(1); 
  hmaxpz->SetLineColor(1); 
  hminr->SetLineColor(2); 
  hmaxr->SetLineColor(2); 
  hminw->SetLineColor(3); 
  hmaxw->SetLineColor(3); 
  hmintot->SetLineColor(4); 
  hmaxtot->SetLineColor(4); 

  hminpz->SetLineStyle(1); 
  hmaxpz->SetLineStyle(2); 
  hminr->SetLineStyle(1); 
  hmaxr->SetLineStyle(2); 
  hminw->SetLineStyle(1); 
  hmaxw->SetLineStyle(2); 
  hmintot->SetLineStyle(1); 
  hmaxtot->SetLineStyle(2); 
    
  hs->Add(hminpz);
  hs->Add(hmaxpz);
  hs->Add(hminr);
  hs->Add(hmaxr);
  //hs->Add(hminw);
  //hs->Add(hmaxw);
  hs->Add(hmintot);
  hs->Add(hmaxtot);
    
  TLegend *legend = new TLegend(0.70,0.60,0.85,0.89,"");
  legend->SetBorderSize(0);
  legend->SetFillColor(kWhite);
  legend->SetNColumns(2);

  legend->AddEntry(hminpz,"Min PZ", "L");
  legend->AddEntry(hmaxpz,"Max PZ", "L");
  legend->AddEntry(hminr,"Min R", "L");
  legend->AddEntry(hmaxr,"Max R", "L");
  //legend->AddEntry(hminw,"Min W", "L");
  //legend->AddEntry(hmaxw,"Max W", "L");
  legend->AddEntry(hmintot,"Min Tot", "L");
  legend->AddEntry(hmaxtot,"Max Tot", "L");

  TCanvas* c1 = new TCanvas();
  hs->Draw("nostack");
  legend->Draw();
  c1->SaveAs("ComparePz.gif");
  c1->SaveAs("ComparePz.eps");

  cout<<"Mean: "<<endl;
  cout<<" minpz : "<<hminpz->GetMean()
      <<" maxpz : "<<hmaxpz->GetMean() <<endl
      <<" minr: "<<hminr->GetMean() 
      <<" maxr: "<<hmaxr->GetMean() <<endl
      <<" minw  : "<<hminw->GetMean()
      <<" maxw  : "<<hmaxw->GetMean()<<endl
      <<" mintot: "<<hmintot->GetMean()
      <<" maxtot: "<<hmaxtot->GetMean()<<endl
      <<endl;

  cout<<"Sigma: "<<endl;
  cout<<" minpz : "<<hminpz->GetRMS()
      <<" maxpz : "<<hmaxpz->GetRMS() <<endl
      <<" minr: "<<hminr->GetRMS() 
      <<" maxr: "<<hmaxr->GetRMS() <<endl
      <<" minw  : "<<hminw->GetRMS()
      <<" maxw  : "<<hmaxw->GetRMS()<<endl
      <<" mintot: "<<hmintot->GetRMS()
      <<" maxtot: "<<hmaxtot->GetRMS()<<endl
      <<endl;

  cout<<"Right: "<<endl;
  cout<<" minpz : "<<right[0]
      <<" maxpz : "<<right[1]
      <<" ratio : "<<1.*right[0]/(right[0]+right[1])<<endl
      <<" minr: "<<right[2] 
      <<" maxr: "<<right[3]
      <<" ratio : "<<1.*right[2]/(right[2]+right[3])<<endl
      <<" minw  : "<<right[4]
      <<" maxw  : "<<right[5]
      <<" ratio : "<<1.*right[4]/(right[4]+right[5])<<endl
      <<" mintot: "<<right[6]
      <<" maxtot: "<<right[7]
      <<" ratio : "<<1.*right[6]/(right[6]+right[7])<<endl
      <<endl;

  float min = hminpz->FindBin(-1*range);
  float max = hminpz->FindBin(   range);
  cout<<"Right2: "<<endl;
  cout<<" minpz : "<<hminpz->Integral(min,max)
      <<" maxpz : "<<hmaxpz->Integral(min,max) <<endl
      <<" minr: "<<hminr->Integral(min,max) 
      <<" maxr: "<<hmaxr->Integral(min,max) <<endl
      <<" minw  : "<<hminw->Integral(min,max)
      <<" maxw  : "<<hmaxw->Integral(min,max)<<endl
      <<" mintot: "<<hmintot->Integral(min,max)
      <<" maxtot: "<<hmaxtot->Integral(min,max)<<endl
      <<endl;

  cout<<"Chose the wrong sol'n "<<wrong<<" times."<<endl;

}
