#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include "TFile.h"
#include "TTree.h" 
#include "TH1F.h"
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
#include <ExecuteAnalysis.h>

struct Sample{
    string name;
    int line;
    int style;
    int fill;
    bool isSignal;
    Sample(){
        name = ""; line = 0; style = 0; fill=0; isSignal=0;
    }
    Sample(string n, int l, int s){
        name = n; line = l; style = s; fill=0; isSignal = 0;
    }
    Sample(string n, int l, int s, int f, bool i=0){
        name = n; line = l; style = s; fill = f; isSignal = i;
    }

};

const int Nlists = 7;
vector<Sample> samples;
//gROOT->SetStyle("Plain");
//TStyle::SetOptStat(kFALSE);

string convertFloattoStr(float num);
void DrawandSave(TFile* fin, string title, bool norm, bool logy, bool eff);
void Draw(vector<TH1F*> & hists,string filename, bool norm, bool logy, bool eff);
void DrawSelection(TFile* fin, string title, bool mincut);
void PlotEff(TFile* fin, string title);
bool Straddles(float a, float b, float num);

void
MakePlots(){  
    TFile *fin = TFile::Open("Wprime_analysis_Zjets.root");
    
    samples.push_back(Sample("wz", 2, 1, 0));
    //samples.push_back(Sample("ttbar", 3, 1, 0));
    samples.push_back(Sample("ttbarfast", 8, 1, 0));
    samples.push_back(Sample("zz", 4, 1, 0));
    samples.push_back(Sample("zgamma", 5, 1, 0));
    samples.push_back(Sample("zjets", 6, 1, 0));
    samples.push_back(Sample("wjets", 7, 1, 0));
    
    
    samples.push_back(Sample("wprime400", 1, 1, 0, 1));
    samples.push_back(Sample("wprime500", 1, 2, 0, 1));
    samples.push_back(Sample("wprime600", 1, 3, 0, 1));
    samples.push_back(Sample("wprime700", 1, 4, 0, 1));
    samples.push_back(Sample("wprime800", 1, 5, 0, 1));
    samples.push_back(Sample("wprime900", 1, 6, 0, 1));
    samples.push_back(Sample("TC400",     1, 7, 0, 1));

    for(size_t i=0; i<samples.size(); ++i){
        if(!fin->GetKey(samples[i].name.c_str() )){
            cout<<"Didn't find "<<samples[i].name<<". Removing."<<endl;
            samples.erase(samples.begin()+i);
            i--;
        }
    }
    
    
    string efftitle[] = {"hEffAbs", "hEffRel", "hNumEvts"};

    vector<string> variable; 
    
    variable.push_back("hWZInvMass");
    variable.push_back("hGenWZInvMass");
    variable.push_back("hWZTransMass");
    variable.push_back("hHt");       
    variable.push_back("hWpt");      
    variable.push_back("hZpt");      
    variable.push_back("hMET");          
    variable.push_back("hZmass");      //7
    variable.push_back("hZeemass");    //8  
    variable.push_back("hZmumumass");     //9 
    variable.push_back("hWTransmass");      
    variable.push_back("hWenuTransmass");      
    variable.push_back("hWmunuTransmass");      
    variable.push_back("hElecPt");
    variable.push_back("hElecEt");
    variable.push_back("hElecTrkRelIso");
    variable.push_back("hElecECalRelIso");
    variable.push_back("hElecHCalRelIso");
    variable.push_back("hElecSigmaEtaEta");
    variable.push_back("hElecDPhi");
    variable.push_back("hElecDEta");
    variable.push_back("hElecHOverE");
    //variable.push_back("hElecEP");

    variable.push_back("hMuonPt" );       
    variable.push_back("hMuonDxy");       
    variable.push_back("hMuonNormChi2");  
    variable.push_back("hMuonNPix");      
    variable.push_back("hMuonNTrk");      
    variable.push_back("hMuonStation");   
    variable.push_back("hMuonSip");   
        
    vector<string> selection_variable;  vector<bool> mincut;
    selection_variable.push_back("hElecEt");          mincut.push_back(true);
    selection_variable.push_back("hElecTrkRelIso");   mincut.push_back(false);
    selection_variable.push_back("hElecECalRelIso");  mincut.push_back(false);
    selection_variable.push_back("hElecHCalRelIso");  mincut.push_back(false);
    selection_variable.push_back("hElecSigmaEtaEta"); mincut.push_back(false);
    selection_variable.push_back("hElecDPhi");        mincut.push_back(false);
    selection_variable.push_back("hElecDEta");        mincut.push_back(false); 
    selection_variable.push_back("hElecHOverE");      mincut.push_back(false);
    //selection_variable.push_back("hElecEP");          mincut.push_back(true);

    selection_variable.push_back("hMuonPt" );          mincut.push_back(true);
    selection_variable.push_back("hMuonDxy");          mincut.push_back(false);
    selection_variable.push_back("hMuonNormChi2");     mincut.push_back(false);
    selection_variable.push_back("hMuonNPix");         mincut.push_back(true);
    selection_variable.push_back("hMuonNTrk");         mincut.push_back(true);
    selection_variable.push_back("hMuonStation");      mincut.push_back(true);
        

    TCanvas c1;
    c1.Print("Summary.pdf[", "pdf"); 
    c1.Print("Selection.pdf[", "pdf"); 
    for(int i=0;i<3;++i) DrawandSave(fin,efftitle[i], 0, i==2, 1);

    int size = variable.size();
    for(int i=0;i<size;++i){
        for(int j=0;j<Num_histo_sets;++j){
            string title = variable[i] + "_" + Cut_Name[j];
            DrawandSave(fin,title,0,i==7 || i==8 || i==9, 0);
        }
    }

    for(size_t i=0; i < selection_variable.size(); ++i){
        string title = selection_variable[i];
        DrawSelection(fin,title, mincut[i]);
    }
   
    c1.Print("Summary.pdf]", "pdf"); 
    c1.Print("Selection.pdf]", "pdf"); 

    //for(int i=0;i<3;++i) PlotEff(fin,efftitle[i]);

    /*
    int arraycuts[] = {0,1,2,3,4};
    vector<int> cuts(arraycuts, arraycuts + sizeof(arraycuts) / sizeof(int) );

    TEntryList* Slist[Nlists];
    TEntryList* Blist[Nlists];
    GetLists(fin,Slist,Blist);

    vector<TEntryList*> Slistvec;
    vector<TEntryList*> Blistvec;

    //Which lists to use?
    int Nlistused = cuts.size();
    for(int i=0; i<Nlistused; ++i){
		int entry = cuts.at(i);
		Slistvec.push_back(Slist[entry]);
		Blistvec.push_back(Blist[entry]);
    }

    TEntryList* SMergedlist = ListAnd(Slistvec);
    TEntryList* BMergedlist = ListAnd(Blistvec);

    for(int i=0; i<2; ++i){
		PlotList(SMergedlist,BMergedlist,variable[i]);
    }
	*/
  
}

void
DrawandSave(TFile* fin, string title, bool norm, bool logy, bool eff){
    //printf("  Draw and Save\n");
    vector<TH1F*> hists;
    vector<string> hist_names;

    int size = samples.size();
    for(int i=0; i<size; ++i){
        hist_names.push_back(samples[i].name + "/" + title);
        if(!fin->Get(hist_names[i].c_str())) 
            cout<<"Failed getting "<<title<<" from "<<samples[i].name<<endl;
        hists.push_back((TH1F*) fin->Get(hist_names[i].c_str()));
    }
    
    string filename = "plots/" + title + ".gif";

    Draw(hists,filename,norm, logy, eff);
}

void
Draw(vector<TH1F*> &  hists, string filename, bool norm, bool logy, bool eff){
    //printf("  Draw (norm is %i)\n",norm);
    TCanvas c1;
    if(logy) c1.SetLogy();
    TLegend *legend = new TLegend(0.60,0.50,0.85,0.89,"");

    string title =  hists[0]->GetTitle();
    title +=  ";";
    title +=  hists[0]->GetXaxis()->GetTitle();
    if(!eff){
        title +=  ";Evts/";
        title += convertFloattoStr(hists[0]->GetBinWidth(1));
        title += " GeV/";
        title += convertFloattoStr(lumiPb);
        title += " pb^{-1}";
    }
    
    THStack* hs = new THStack("hs",title.c_str());

    int size = hists.size();
    for(int i=0; i<size; i++){
        if(!hists[i]){
            cout<<"Didn't Find "<<hists[i]->GetName()<<endl;
            continue;
        }
        hists[i]->SetLineStyle(samples[i].style);
        hists[i]->SetLineColor(samples[i].line); 
        //if(!eff) hists[i]->SetFillColor(samples[i].fill); 
        hs->Add(hists[i]);
        
        legend->AddEntry(hists[i],(samples[i].name).c_str(), "L");

        if(norm){
            TAxis* axis = hists[i]->GetXaxis();
            int first = axis->GetFirst();
            int last  = axis->GetLast();
            float sum = hists[i]->Integral(first,last); 
            hists[i]->Scale(1./sum);
            axis->SetRange(first,last);
        }
    }
    
    //For Edgar's APS Plots
    //hs->SetStats(kFALSE);
    //printf("Getting axis\n");
    //TAxis* a = hs->GetXaxis();
    

    //hs->GetXaxis()->SetLabelSize(0.05);
    //hs->GetXaxis()->SetNdivisions(10); 
    //printf("Setting title\n");  

    if(eff){
        hs->Draw("nostack");
    }else{
        //hs->Draw();
        hs->Draw("nostack");
    }

    //printf("Getting legend\n");
    legend->SetTextSize(0.04);
	legend->SetBorderSize(0);
	//legend->SetFillColor(kWhite);
    //legend->SetEntrySeparation(0.8);
    legend->SetFillStyle(0);
    legend->Draw();

    c1.SaveAs(filename.c_str());
    c1.Print("Summary.pdf","pdf");	
    delete hs;
}

void
PlotEff(TFile* fin, string title){
    printf("  Plot Eff\n");

    string dir1 = "wprime400";
    string dir2 = "wzjj";

    string h1_name = dir1 + "/" + title;
    string h2_name = dir2 + "/" + title;
    string filename = title + ".gif";

    TCanvas c1;
    TH1F *h1,*h2;

    h1 = (TH1F*) fin->Get(h1_name.c_str());
    h2 = (TH1F*) fin->Get(h2_name.c_str());

    h1->SetStats(kFALSE);
    h2->SetStats(kFALSE);

    TAxis* axis = h1->GetXaxis();
    for(int i=0; i<Num_histo_sets; ++i) axis->SetBinLabel(i+1,Cut_Name[i].c_str());

    h1->SetLineColor(kRed);  h1->Draw();
    h2->SetLineColor(kBlue); h2->Draw("same");

    TLegend *legend = new TLegend(0.60,0.78,0.85,0.87,"");
    legend->AddEntry(h1,"W'(M=400GeV)", "L");
    legend->AddEntry(h2,"WZjj", "L");
    legend->SetTextSize(0.04);
    legend->SetBorderSize(0);
    legend->SetFillColor(kWhite);
    legend->Draw();


    c1.SaveAs(filename.c_str());
}


void
DrawSelection(TFile* fin, string title, bool mincut){
    //printf("  Draw Selection\n");
    /***********
    Note: WZ is signal and TTbar + Zjets is background
    for these plots!!!!!
    ***********/

    int sig_idx, bkg1_idx, bkg2_idx;
    sig_idx = bkg1_idx = bkg2_idx = -1;
 
    const string signal_name = "wz";
    const string bkg1_name = "ttbarfast";
    const string bkg2_name = "zjets";

    for(size_t i=0; i<samples.size(); ++i){
        if(!signal_name.compare(samples[i].name)){
            sig_idx = i;
            //cout<<"Sample Signal"<<endl;
        }
        if(!bkg1_name.compare(samples[i].name)){
            bkg1_idx = i; cout<<samples[i].name<<endl;
        }
        if(!bkg2_name.compare(samples[i].name)){
            bkg2_idx = i; cout<<samples[i].name<<endl;
        }
    }
    if(sig_idx == -1 || bkg1_idx == -1 || bkg2_idx == -1){
        cout<<"Didn't find a sample.  Exiting."<<endl;
        return;
    }

    vector<TH1F*> hists;
    string fulltitle;
    for(int cut=0; cut!= Num_histo_sets; ++cut){
        string title_match = "h" + Cut_Name[cut];
        if(!title_match.compare(title)){
            fulltitle = title + "_" + Cut_Name[cut-1];
            cout<<"Using Cut: "<<Cut_Name[cut-1]<<" for histo:"<<title<<endl;
            //cout<<"Check: "<<Cut_Name[cut]<<" == "<<title<<endl; 
            break;
        }
    }    

    vector<string> hist_names;     
    int size = samples.size();
    for(int i=0; i<size; ++i){
        hist_names.push_back(samples[i].name + "/" + fulltitle);
        if(!fin->Get(hist_names[i].c_str())) 
            cout<<"Failed getting "<<fulltitle<<" from "<<samples[i].name<<endl;
        hists.push_back((TH1F*) fin->Get(hist_names[i].c_str()));
    }
    
    //TAxis* axis = hists[0]->GetXaxis();
    int first = 0;
    int last  = hists[0]->GetNbinsX() + 1;//axis->GetLast() + 1;
    int nbins = hists[0]->GetNbinsX() + 2;//last-first+1;

    const float Nsig_tot  = hists[ sig_idx]->Integral(first, last);
    const float Nbkg_tot  = hists[bkg1_idx]->Integral(first, last)
                          + hists[bkg2_idx]->Integral(first, last);

    //printf("Tot sig:%f   Tot Bkg:%f\n", Nsig_tot, Nbkg_tot);
    //printf("first:%i, last:%i, nbins:%i or %i\n", first, last, nbins, hists[0]->GetNbinsX());

    double* Nsig = new double[nbins];
    double* Nbkg = new double[nbins];

    if(mincut){
        for(int bin=first; bin<=last; ++bin){//for min cut
            //printf("bin:%i low:%f\n",bin, hists[0]->GetBinCenter(bin));
            Nsig[bin] = 0;
            Nbkg[bin] = 0;
            
            Nsig[bin] = hists[sig_idx]->Integral(bin, last);
            
            Nbkg[bin]  = hists[bkg1_idx]->Integral(bin, last);
            Nbkg[bin] += hists[bkg2_idx]->Integral(bin, last);
            
            Nsig[bin] /= Nsig_tot;
            Nbkg[bin] /= Nbkg_tot;
        }
    }else{
        for(int bin=first; bin<=last; ++bin){//for max cut
            //printf("bin:%i low:%f\n",bin, hists[0]->GetBinCenter(bin));
            Nsig[bin] = 0;
            Nbkg[bin] = 0;
            
            Nsig[bin] = hists[sig_idx]->Integral(first, bin);
            
            Nbkg[bin]  = hists[bkg1_idx]->Integral(first, bin);
            Nbkg[bin] += hists[bkg2_idx]->Integral(first, bin);
            
            Nsig[bin] /= Nsig_tot;
            Nbkg[bin] /= Nbkg_tot;
        }
    }

    TCanvas c1;
    TGraph graph(nbins, Nsig, Nbkg);
    string graph_title = title + " Selection Plot;Signal Eff;Background Eff";
    graph.SetTitle(graph_title.c_str());
    graph.Draw("A*");
    c1.Print("Summary.pdf", "pdf");
    c1.Print("Selection.pdf", "pdf");

    int cutbin;
    for(int bin=first; bin<last; ++bin){
        if(Straddles(Nsig[bin],Nsig[bin+1], 0.98)){
            cout<<"Bin: "<<bin<<": "<<Nsig[bin]<<" - "<<Nsig[bin+1]<<endl;
            if(Nsig[bin] > Nsig[bin+1]) cutbin = bin;
            else                        cutbin = bin+1;
            cout<<title<<" cut is "<<hists[0]->GetBinCenter(cutbin)<<endl;
        }
    }

}

bool 
Straddles(float a, float b, float num){
    if(a >= num && num >= b) return true;
    if(b >= num && num >= a) return true;
    
    return false;
}

string convertFloattoStr(float num){
    stringstream ss;
    ss << num;
    return ss.str();
}
