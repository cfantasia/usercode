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
#include "TError.h"
#include "TStyle.h"
#include "TLine.h"

//#include "Tools.h"
using namespace std;


struct Sample{
  std::string name;
  int line;
  int style;
  int fill;
  TH1F* hist;
  Sample(){
    name = ""; line = 0; style = 0; fill=0; hist=NULL;
  }
  Sample(std::string n){
    name = n; line = 1; style = 0; fill = 0; hist=NULL;
  }
  Sample(std::string n, int l, int s, int f){
    name = n; line = l; style = s; fill = f; hist=NULL;
  }
};

std::vector< std::vector<Sample>* > samples;
std::vector<Sample> Data;
std::vector<Sample> Bkg;
std::vector<Sample> Sig;
std::map<std::string, std::string> SampleNames;

//gROOT->SetStyle("Plain");
//TStyle::SetOptStat(kFALSE);
const bool debug = false;

int main(int argc, char ** argv);
void MakePlots(string fname, string opt="");
void DrawandSave(TFile* fin, std::string title, bool norm, bool logy, bool eff, bool cum, TLine* line=NULL);
TH1F* FillCum(TH1F* h);
void GetHistograms(TFile* fin, std::string title, bool eff, bool cum);
void Draw(std::string filename, bool norm, bool logy, bool eff, bool cum, TLine* line);
void CheckSamples(TFile* fin, std::vector<Sample> & sample);
TH1F* GetValidHist(TFile* f);
vector<string> GetListofCuts(TFile* f);
float KFactor(string samepl);

void
MakePlots(string fname, string opt){  
  gErrorIgnoreLevel = kWarning;
  gStyle->SetOptStat(0);
  gROOT->SetStyle("Plain");
  
  
  //gStyle->SetOptStat(111111);
  gStyle->SetCanvasColor(kWhite);     // background is no longer mouse-dropping white
  gStyle->SetCanvasBorderMode(0);     // turn off canvas borders
  gStyle->SetPadBorderMode(0);
  gStyle->SetPaintTextFormat("5.2f");  // What precision to put numbers if plotted with "TEXT"
  
  //// For publishing:
  gStyle->SetLineWidth(2.);
  gStyle->SetTextSize(1.1);
  gStyle->SetLabelSize(0.06,"xy");
  gStyle->SetTitleSize(0.06,"xy");
  gStyle->SetTitleOffset(1.2,"x");
  gStyle->SetTitleOffset(1.0,"y");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.1);
  //gStyle->SetPadRightMargin(0.25);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.12);
  
  TFile *fin = TFile::Open(fname.c_str(), "read");//Cory:

  SampleNames["Run2010"]="Data";
  SampleNames["Run2011"]="Data";
  SampleNames["WlnuJetsMadgraph"]="W+Jets";
  SampleNames["WenuJets"]="W+Jets\\rightarrowe\\nu";
  SampleNames["WmunuJets"]="W+Jets\\rightarrow\\mu\\nu";
  SampleNames["TTbar"]="TTbar";
  SampleNames["TTbar2l"]="TTbar\\rightarrow2l";
  SampleNames["ZZ"]="ZZ";
  SampleNames["ZZ4l"]="ZZ\\rightarrow4l";
  SampleNames["ZGamma2l"]="Z\\gamma\\rightarrow2l";
  SampleNames["DYJets2l"]="DY+Jets\\rightarrow2l";
  SampleNames["DYee"]="DY\\rightarrowee";
  SampleNames["DYmumu"]="DY\\rightarrow\\mu\\mu";
  SampleNames["ZJetsBinned"]="Z+Jets";
  SampleNames["ZllJetsMadgraph"]="Z+Jets Madgraph";
  SampleNames["ZeeJets"]="Z+Jets\\rightarrowee";
  SampleNames["ZmumuJets"]="Z+Jets\\rightarrow\\mu\\mu";
  SampleNames["ZeeJetsPowheg"]="Z+Jets\\rightarrowee Powheg";
  SampleNames["ZmumuJetsPowheg"]="Z+Jets\\rightarrow\\mu\\mu Powheg";
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

  //Data.push_back(Sample("Run2010"));
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
//  Bkg.push_back(Sample("ZllJetsMadgraph", 7, 1, 7));
//  Bkg.push_back(Sample("ZeeJets"  , 7, 1, 7));
//  Bkg.push_back(Sample("ZmumuJets", 7, 1, 7));
//  Bkg.push_back(Sample("ZeeJetsPowheg"  , 7, 1, 7));
//  Bkg.push_back(Sample("ZmumuJetsPowheg", 7, 1, 7));
//  Bkg.push_back(Sample("DYJets2l", 7, 1, 7));
  Bkg.push_back(Sample("DYee", 7, 1, 7));
  Bkg.push_back(Sample("DYmumu", 7, 1, 7));
  Bkg.push_back(Sample("WZ3l"       , 2, 1, 2));
  CheckSamples(fin,Bkg);

  if(!fname.find("Wprime")){
    //Sig.push_back(Sample("Wprime300", 1, 1, 10));
    Sig.push_back(Sample("Wprime400", 1, 1, 10));
    //Sig.push_back(Sample("Wprime500", 1, 1, 10));
    //Sig.push_back(Sample("Wprime600", 1, 1, 10));
    //Sig.push_back(Sample("Wprime700", 1, 1, 10));
    //Sig.push_back(Sample("Wprime800", 1, 1, 10));
    //Sig.push_back(Sample("Wprime900", 1, 1, 10));

    Sig.push_back(Sample("TC225",     2, 1, 10));
    Sig.push_back(Sample("TC300",     2, 1, 10));
    Sig.push_back(Sample("TC400",     2, 1, 10));
    Sig.push_back(Sample("TC500",     2, 1, 10));
  }
  CheckSamples(fin,Sig);

  samples.push_back(&Data);
  samples.push_back(&Sig);
  samples.push_back(&Bkg);
  if(debug) cout<<"Size of samples: "<<samples.size()
                <<" Size of Data: "<<Data.size()
                <<" Size of Sig: "<<Sig.size()
                <<" Size of Bkg: "<<Bkg.size()<<endl;

  string efftitle[] = {"hEffAbs", "hEffRel", "hNumEvts"};

  vector<string> Cuts = GetListofCuts(fin);
  vector<string> variable; 
    
  if(!fname.find("Wprime")){
    variable.push_back("hWZInvMass");
/*
    variable.push_back("hWZ3e0muInvMass");
    variable.push_back("hWZ2e1muInvMass");
    variable.push_back("hWZ1e2muInvMass");
    variable.push_back("hWZ0e3muInvMass");
*/
//  variable.push_back("hWZTransMass");
    variable.push_back("hHt");       //2
    variable.push_back("hWpt");      
    variable.push_back("hZpt");      //4
    variable.push_back("hQ");      
  }
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

  variable.push_back("hLeadPt");      
  variable.push_back("hLeadElecPt");      
  variable.push_back("hLeadMuonPt");      
        
  TCanvas c1;
  c1.Print("Summary.pdf[", "pdf"); 
  for(int i=2;i<3;++i) DrawandSave(fin,efftitle[i], 0, i==2, 1, 0);

  uint begin = !opt.compare("final") ? Cuts.size()-1 : Cuts.size()-6;
  for(uint i=0;i<variable.size();++i){
    for(uint j=begin;j<Cuts.size();++j){
      string title = variable[i] + "_" + Cuts[j];
      DrawandSave(fin,title,0,1,0,0);
    }
  }

  c1.Print("Summary.pdf]", "pdf"); 
}

void
DrawandSave(TFile* fin, std::string title, bool norm, bool logy, bool eff, bool cum, TLine* line){
  GetHistograms(fin, title, eff, cum);
  string filename = "plots/" + title + ".gif";
  Draw(filename, norm, logy, eff, cum, line);
}

void
GetHistograms(TFile* fin, string title, bool eff, bool cum){
  if(debug) printf("  GetHisto %s\n", title.c_str());
  string hist_name;
  
  for(unsigned int i=0; i<samples.size(); ++i){
    for(unsigned int j=0; j<samples[i]->size(); ++j){
      hist_name = samples[i]->at(j).name + "/" + title;
      if(!fin->Get(hist_name.c_str()))
        cout<<"Failed getting "<<title<<" from "<<samples[i]->at(j).name<<endl;
      samples[i]->at(j).hist = (TH1F*) fin->Get(hist_name.c_str());
      samples[i]->at(j).hist->Scale(KFactor(samples[i]->at(j).name));
      samples[i]->at(j).hist->SetLineStyle(samples[i]->at(j).style);
      samples[i]->at(j).hist->SetLineColor(samples[i]->at(j).line); 
      if(!eff){
        samples[i]->at(j).hist->SetFillColor(samples[i]->at(j).fill);
        samples[i]->at(j).hist->SetFillStyle(4004); 
      }
      if(cum){
        samples[i]->at(j).hist = FillCum(samples[i]->at(j).hist);
      }
    }
  }
}

void
Draw(string filename, bool norm, bool logy, bool eff, bool cum, TLine* line){
  if(debug) printf("  Draw (norm is %i) %s\n",norm, filename.c_str());

  TCanvas c1;
  if(logy) c1.SetLogy();

  string title;
  if(Data.size()){
    title = Data[0].hist->GetTitle();
    title += ";"; 
    title += Data[0].hist->GetXaxis()->GetTitle();
    title += ";";
    title += Data[0].hist->GetYaxis()->GetTitle();
  }else if(Bkg.size()){
    title = Bkg[0].hist->GetTitle();
    title += ";"; 
    title += Bkg[0].hist->GetXaxis()->GetTitle();
    title += ";";
    title += Bkg[0].hist->GetYaxis()->GetTitle();
  }
  TH1F* hData = NULL;
  for(uint i=0; i<Data.size(); i++){
    if(i==0) hData = (TH1F*)Data[i].hist->Clone("hData");
    else     hData->Add(Data[i].hist);
  }
  hData->SetMarkerSize(5);
  
  if(!eff){
    THStack* sBkg  = new THStack("sBkg",title.c_str());
    THStack* sSigs[Sig.size()];

    for(uint i=0; i<Bkg.size(); i++){
      sBkg->Add(Bkg[i].hist);
    } 
    
    for(uint i=0; i<Sig.size(); i++){
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

TH1F* GetValidHist(TFile* f){
  string name;
  for(unsigned int i=0; i<samples.size(); ++i){
    for(unsigned int j=0; j<samples[i]->size(); ++j){
      name = samples[i]->at(j).name + "/hNumEvts";
      TH1F* hist = (TH1F*) f->Get(name.c_str());
      if(hist) return hist;
    }
  }
  cout<<"Didn't find a valid histogram\n";
  return NULL;
}
vector<string> GetListofCuts(TFile* f){
  TH1F* hist = GetValidHist(f);
  if(!hist) return vector<string>();
  vector<string> Cuts(hist->GetXaxis()->GetNbins());
  for(uint i=0; i<Cuts.size(); ++i){
    Cuts[i] = hist->GetXaxis()->GetBinLabel(i+1);
  }
  return Cuts;
}

TH1F*
FillCum(TH1F* h){
  int size = h->GetXaxis()->GetNbins();
  TH1F* cumhist = (TH1F*)h->Clone();
  float sum = h->GetBinContent(size+1);//Overflow
  string title = h->GetTitle();
  title += "(Cumlative)";
  cumhist->SetTitle(title.c_str());
  for(int i=size; i>0; --i){
    sum += h->GetBinContent(i);
    cumhist->SetBinContent(i,sum);
  }
  return cumhist;
}

float
KFactor(string sample){
  if      (!sample.find("Wprime"))
    return 1.35;//Cory: Approx.
  else if (!sample.find("TC"))
    return 1.35;
  else if (!sample.find("WZ"))
    return 18./10.5;
  else if (!sample.find("TTbar"))
    return 165/94.3;
  else if (!sample.find("WenuJets"))
    return 28000/25900.4;
  else if (!sample.find("WmunuJets"))
    return 28000/25900.4;
  else if (!sample.find("WlnuJets"))
    return 28000/25900.4;
  else if (!sample.find("ZJets"))
    return 2800/2541.89;
  else if (!sample.find("DY"))
    return 2800/2541.89;
  else if (!sample.find("Zee"))
    return 2800/2541.89;
  else if (!sample.find("Zmumu"))
    return 2800/2541.89;
  else if (!sample.find("Zll"))
    return 2800/2541.89;
  else if (!sample.find("ZGamma"))
    return 5.9/4.3;///  7.3/7.3;//Cory: This is wrong, but no evts survive anyway(guess ~ZZ)
  else if (!sample.find("ZZ"))
    return 5.9/4.3;
  else if (!sample.find("Run20"))
    return 1;
  else
    cout<<"Didn't find the sample "<<sample
        <<" Not weighted!!!!!\n\n\n";
    return 1.;
}

int 
main(int argc, char ** argv){
  if(argc > 3){
    fprintf(stderr,"%s usage: %s infile opt\n",argv[0],argv[0]);
    exit( 1 );
  }
  MakePlots(argv[1], argc > 2 ? argv[2] : "");

  return 0;
}

