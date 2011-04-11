#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include "TFile.h"
#include "TTree.h" 
#include "TH1F.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TMath.h"
#include "TLegend.h"
#include "THStack.h"
#include <vector>
#include "TROOT.h"
#include "TStyle.h"
#include "TLine.h"
#include "ExecuteAnalysis.C"//Cory:
//#include "ExecuteSMWZ.C"

struct Sample{
  string name;
  int line;
  int style;
  int fill;
  TH1F* hist;
  Sample(){
    name = ""; line = 0; style = 0; fill=0; hist=NULL;
  }
  Sample(string n){
    name = n; line = 1; style = 0; fill = 0; hist=NULL;
  }
  Sample(string n, int l, int s, int f){
    name = n; line = l; style = s; fill = f; hist=NULL;
  }
};

vector< vector<Sample>* > samples;
vector<Sample> Data;
vector<Sample> Bkg;
vector<Sample> Sig;
map<string, string> SampleNames;

//gROOT->SetStyle("Plain");
//TStyle::SetOptStat(kFALSE);
const bool debug = false;

string convertFloattoStr(float num);
void DrawandSave(TFile* fin, string title, bool norm, bool logy, bool eff);
void Draw(string filename, bool norm, bool logy, bool eff, TLine* line=NULL);
void CheckSamples(TFile* fin, vector<Sample> & sample);

void
MakePlots(){  
  gStyle->SetOptStat(0);
  TFile *fin = TFile::Open("Wprime_analysis.root", "read");//Cory:
  //TFile *fin = TFile::Open("SMWZ_analysis.root", "read");

  SampleNames["Run2010"]="Data";
  SampleNames["WlnuJetsMadgraph"]="W+Jets";
  SampleNames["WenuJets"]="W+Jets\\rightarrowe\\nu";
  SampleNames["WmunuJets"]="W+Jets\\rightarrow\\mu\\nu";
  SampleNames["TTbar"]="TTbar";
  SampleNames["TTbar2l"]="TTbar\\rightarrow2l";
  SampleNames["ZZ"]="ZZ";
  SampleNames["ZZ4l"]="ZZ\\rightarrow4l";
  SampleNames["ZGamma2l"]="Z\\gamma\\rightarrow2l";
  SampleNames["DYJets2l"]="DY+Jets\\2l";
  SampleNames["DYee"]="DY\\rightarrowee";
  SampleNames["DYmumu"]="DY\\rightarrow\\mu\\mu";
  SampleNames["ZJetsBinned"]="Z+Jets";
  SampleNames["ZeeJets"]="Z+Jets\\rightarrowee";
  SampleNames["ZmumuJets"]="Z+Jets\\rightarrow\\mu\\mu";
  SampleNames["WZ3l"]="SM WZ\\rightarrow3l";
  SampleNames["Wprime300"]="W' 300";
  SampleNames["Wprime400"]="W' 400";
  SampleNames["Wprime500"]="W' 500";
  SampleNames["Wprime600"]="W' 600";
  SampleNames["Wprime700"]="W' 700";
  SampleNames["Wprime800"]="W' 800";
  SampleNames["Wprime900"]="W' 900";
  SampleNames["TC225"]="\\rho_{TC} 225";
  SampleNames["TC300"]="\\rho_{TC} 300";
  SampleNames["TC400"]="\\rho_{TC} 400";
  SampleNames["TC500"]="\\rho_{TC} 500";

  Data.push_back(Sample("Run2011"));
  CheckSamples(fin,Data);
  
  //Bkg.push_back(Sample("WlnuJetsMadgraph", 8, 1, 8));
  Bkg.push_back(Sample("WenuJets" , 8, 1, 8));
  Bkg.push_back(Sample("WmunuJets", 8, 1, 8));
  //Bkg.push_back(Sample("TTbar"  , 4, 1, 4));
  Bkg.push_back(Sample("TTbar2l"  , 4, 1, 4));
  Bkg.push_back(Sample("ZZ"     , 5, 1, 5));
  //Bkg.push_back(Sample("ZZ4l"     , 5, 1, 5));
  Bkg.push_back(Sample("ZGamma2l"   , 6, 1, 6));
  //Bkg.push_back(Sample("ZJetsBinned", 7, 1, 7));
  //Bkg.push_back(Sample("ZeeJets"  , 7, 1, 7));
  //Bkg.push_back(Sample("ZmumuJets", 7, 1, 7));
  Bkg.push_back(Sample("DYJets2l", 7, 1, 7));
  //Bkg.push_back(Sample("DYee", 7, 1, 7));
  //Bkg.push_back(Sample("DYmumu", 7, 1, 7));
  Bkg.push_back(Sample("WZ3l"       , 2, 1, 2));//Cory: Change back to 3
  CheckSamples(fin,Bkg);
  
  Sig.push_back(Sample("Wprime300", 1, 1, 10));
  //Sig.push_back(Sample("Wprime400", 1, 1, 10));
  Sig.push_back(Sample("Wprime500", 1, 1, 10));
  //Sig.push_back(Sample("Wprime600", 1, 1, 10));
  //Sig.push_back(Sample("Wprime700", 1, 1, 10));
  //Sig.push_back(Sample("Wprime800", 1, 1, 10));
  //Sig.push_back(Sample("Wprime900", 1, 1, 10));
/*
  Sig.push_back(Sample("TC225",     2, 1, 10));
  Sig.push_back(Sample("TC300",     2, 1, 10));
  Sig.push_back(Sample("TC400",     2, 1, 10));
  Sig.push_back(Sample("TC500",     2, 1, 10));
*/
  CheckSamples(fin,Sig);

  samples.push_back(&Data);
  samples.push_back(&Sig);
  samples.push_back(&Bkg);
  if(debug) cout<<"Size of samples: "<<samples.size()
                <<" Size of Data: "<<samples[0]->size()
                <<" Size of Sig: "<<Sig.size()
                <<" Size of Bkg: "<<Bkg.size()<<endl;

  string efftitle[] = {"hEffAbs", "hEffRel", "hNumEvts"};

  vector<string> variable; 
    
  variable.push_back("hWZInvMass");
  variable.push_back("hWZ3e0muInvMass");
  variable.push_back("hWZ2e1muInvMass");
  variable.push_back("hWZ1e2muInvMass");
  variable.push_back("hWZ0e3muInvMass");
  
  //variable.push_back("hWZTransMass");
  variable.push_back("hHt");       //2
  variable.push_back("hWpt");      
  variable.push_back("hZpt");      //4
  variable.push_back("hMET");          

  variable.push_back("hZMass");      //6
  variable.push_back("hZeeMass");      
  variable.push_back("hZmumuMass");  //8    
/*
  variable.push_back("hZ3e0muMass");      
  variable.push_back("hZ2e1muMass");      
  variable.push_back("hZ1e2muMass");      
  variable.push_back("hZ0e3muMass");      
*/
  variable.push_back("hWTransMass");      
  variable.push_back("hWenuTransMass");  //10    
  variable.push_back("hWmunuTransMass");      
/*
  variable.push_back("hW3e0muTransMass");      
  variable.push_back("hW2e1muTransMass");      
  variable.push_back("hW1e2muTransMass");      
  variable.push_back("hW0e3muTransMass");      
*/
  variable.push_back("hQ");      

  variable.push_back("hLeadPt");      
  variable.push_back("hLeadElecPt");      
  variable.push_back("hLeadMuonPt");      
        
  TCanvas c1;
  c1.Print("Summary.pdf[", "pdf"); 
  for(int i=0;i<3;++i) DrawandSave(fin,efftitle[i], 0, i==2, 1);

  int size = variable.size();
  for(int i=0;i<size;++i){
    for(int j=19;j<NCuts;++j){
      string title = variable[i] + "_" + Cut_Name[j];
      DrawandSave(fin,title,i>=13,0, 0);
    }
  }

  c1.Print("Summary.pdf]", "pdf"); 

}

void
DrawandSave(TFile* fin, string title, bool norm, bool logy, bool eff){
  if(debug) printf("  Draw and Save %s\n", title.c_str());
  string hist_name;

  for(unsigned int i=0; i<samples.size(); ++i){
    for(unsigned int j=0; j<samples[i]->size(); ++j){
      hist_name = samples[i]->at(j).name + "/" + title;
      if(!fin->Get(hist_name.c_str()))
        cout<<"Failed getting "<<title<<" from "<<samples[i]->at(j).name<<endl;
      samples[i]->at(j).hist = (TH1F*) fin->Get(hist_name.c_str());
      samples[i]->at(j).hist->SetLineStyle(samples[i]->at(j).style);
      samples[i]->at(j).hist->SetLineColor(samples[i]->at(j).line); 
      if(!eff){
        samples[i]->at(j).hist->SetFillColor(samples[i]->at(j).fill); //Cory:
        samples[i]->at(j).hist->SetFillStyle(4004); 
      }
    }
  }
    
  string filename = "plots/" + title + ".gif";
  Draw(filename, norm, logy, eff);
}

void
Draw(string filename, bool norm, bool logy, bool eff, TLine* line){
  if(debug) printf("  Draw (norm is %i) %s\n",norm, filename.c_str());

  TCanvas c1;
  if(logy) c1.SetLogy();

  string title;
  TH1F* hData = NULL;
  if(Data.size()){
    title = Data[0].hist->GetTitle();
    title += ";"; 
    title += Data[0].hist->GetXaxis()->GetTitle();
    title += ";";
    title += Data[0].hist->GetYaxis()->GetTitle();
    hData = Data[0].hist;
    hData->SetMarkerSize(5);
  }else if(Bkg.size()){
    title = Bkg[0].hist->GetTitle();
    title += ";"; 
    title += Bkg[0].hist->GetXaxis()->GetTitle();
    title += ";";
    title += Bkg[0].hist->GetYaxis()->GetTitle();
  }
  if(!eff){
    
    THStack* sBkg  = new THStack("sBkg",title.c_str());
    THStack* sSigs[Sig.size()];

    for(unsigned int i=0; i<Bkg.size(); i++){
      sBkg->Add(Bkg[i].hist);
    } 
    
    for(unsigned int i=0; i<Sig.size(); i++){
      sSigs[i] = (THStack*) sBkg->Clone();
      sSigs[i]->Add(Sig[i].hist);
    }
    
    Double_t max = sBkg->GetMaximum();
    sBkg->Draw("HIST");
    for(unsigned int i=0; i<Sig.size(); i++){
      max = TMath::Max(max, sSigs[i]->GetMaximum());
      sSigs[i]->Draw("HIST SAME");
    }
    if(hData){
      max = TMath::Max(max, hData->GetMaximum());
      hData->Draw("E1 SAME");
    }
    sBkg->SetMaximum(1.1*max);
    
  }else{
    THStack* hs = new THStack("hs",title.c_str());
    hs->Add(hData);
    for(unsigned int i=0; i<Bkg.size(); ++i){
      hs->Add(Bkg[i].hist);
    }
    for(unsigned int i=0; i<Sig.size(); ++i){
      hs->Add(Sig[i].hist);
    }
    hs->Draw("nostack HIST");
  }
  if(debug) cout<<"Title: "<<title<<endl;

  if(debug) cout<<"Creating Legend\n";
  TLegend *legend = new TLegend(0.65,0.50,0.88,0.89,"");
  if(Data.size()) legend->AddEntry(hData, "Data", "PLE");
  for(unsigned int i=0; i<Bkg.size(); ++i){
    legend->AddEntry(Bkg[i].hist,SampleNames[Bkg[i].name].c_str(), "L");
  }
  for(unsigned int i=0; i<Sig.size(); ++i){
    legend->AddEntry(Sig[i].hist,SampleNames[Sig[i].name].c_str(), "L");
  }
  
  if(norm){//????
    //TAxis* axis = samples[0]->at(0).hist->GetXaxis();
    //int first = axis->GetFirst();
    //int last  = axis->GetLast();
    //float sum = hists[i]->Integral(first,last); 
    //hists[i]->Scale(1./sum);
    //axis->SetRange(first,last);
  }
 
  //hs->GetXaxis()->SetNdivisions(10); 
  if(debug) printf("Setting title\n");  

  legend->SetTextSize(0.03);
	legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->Draw();

  if(line) line->Draw();

  c1.SaveAs(filename.c_str());
  c1.Print("Summary.pdf","pdf");	
}

string convertFloattoStr(float num){
  stringstream ss;
  ss << num;
  return ss.str();
}

void
CheckSamples(TFile* fin, vector<Sample> & sample){
  for(size_t i=0; i<sample.size(); ++i){
    if(!fin->GetKey(sample[i].name.c_str() )){
      cout<<"Didn't find "<<sample[i].name<<". Removing."<<endl;
      sample.erase(sample.begin()+i);
      i--;
    }
  }
}
