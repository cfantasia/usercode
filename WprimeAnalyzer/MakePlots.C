#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include "TFile.h"
#include "TTree.h" 
#include "TH1F.h"
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
    Sample(){
        name = ""; line = 0; style = 0; fill=0;
    }
    Sample(string n, int l, int s){
        name = n; line = l; style = s; fill = l;
    }
    Sample(string n, int l, int s, int f){
        name = n; line = l; style = s; fill = f;
    }

};

const int Nlists = 7;
vector<Sample> samples;
//gROOT->SetStyle("Plain");
//TStyle::SetOptStat(kFALSE);

string convertFloattoStr(float num);
void DrawandSave(TFile* fin, string title, bool norm, bool logy, bool eff);
void Draw(vector<TH1F*> & hists,string filename, bool norm, bool logy, bool eff);
void PlotEff(TFile* fin, string title);
void PlotList(TEntryList* SMergedlist,TEntryList* BMergedlist,string title);
void GetLists(TFile* fin,TEntryList** Slist,TEntryList** Blist);
TEntryList* ListAnd(TEntryList* l1,TEntryList* l2);
TEntryList* ListAnd(vector<TEntryList*> list);


void
MakePlots(){  
    TFile *fin = TFile::Open("Wprime_analysis.root");
    
    samples.push_back(Sample("wz", 2, 1));
    //samples.push_back(Sample("ttbar", 3, 1));
    samples.push_back(Sample("ttbarfast", 8, 1));
    samples.push_back(Sample("zz", 4, 1));
    samples.push_back(Sample("zgamma", 5, 1));
    samples.push_back(Sample("zjets", 6, 1));
    //samples.push_back(Sample("wjets", 7, 1));
    
    //samples.push_back("wprime400_W20");
    //samples.push_back("wprime400_W40");
    //samples.push_back("wprime400_WDef");
    //samples.push_back("wprime400_STARTUP");
    
    samples.push_back(Sample("wprime400", 1, 1, 0));
    samples.push_back(Sample("wprime500", 1, 2, 0));
    samples.push_back(Sample("wprime600", 1, 3, 0));
    samples.push_back(Sample("wprime700", 1, 4, 0));
    samples.push_back(Sample("wprime800", 1, 5, 0));
    samples.push_back(Sample("wprime900", 1, 6, 0));
    samples.push_back(Sample("TC400",     1, 7, 0));
    
    
    string efftitle[] = {"hEffAbs", "hEffRel", "hNumEvts"};

    vector<string> variable; 
    
    variable.push_back("hWZInvMass");
    variable.push_back("hGenWZInvMass");
    variable.push_back("hWZTransMass");
    variable.push_back("hHt");       
    variable.push_back("hWpt");      
    variable.push_back("hZpt");      
    variable.push_back("hMET");          
    variable.push_back("hZmass");      
    variable.push_back("hZeemass");      
    variable.push_back("hZmumumass");      
    variable.push_back("hElecPt");
    /*
    variable.push_back("hElecdEta");
    variable.push_back("hElecdPhi");
    variable.push_back("hElecSigmann");
    variable.push_back("hElecEP");
    variable.push_back("hElecHE");
    variable.push_back("hElecRelCaloIso");
    variable.push_back("hElecRelTrkIso");
    */
    //variable.push_back("hJetsDeltaEta");


    TCanvas c1;
    c1.Print("Summary.pdf[", "pdf"); 
    for(int i=0;i<3;++i) DrawandSave(fin,efftitle[i], 0, i==2, 1);

    int size = variable.size();
    for(int i=0;i<size;++i){
        for(int j=0;j<Num_histo_sets;++j){
            string title = variable[i] + "_" + Cut_Name[j];
            DrawandSave(fin,title,0,i==8 || i==15, 0);
        }
    }
   
    c1.Print("Summary.pdf]", "pdf"); 
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
    
    string filename = "plots/" + title + ".eps";

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
/*
Draw2(vector<TH1F*> &  hists, string filename){
    float sum,max1,max2,max;
    int first, last, Ndiv;

    TCanvas c1;
    TH1F *h1,*h2;
    TAxis *axis;

    h1 = (TH1F*) fin->Get(h1_name.c_str());
    axis = h1->GetXaxis();
    first = axis->GetFirst();
    last  = axis->GetLast();
    sum = h1->Integral(first+1,last); 
    h1->Scale(1./sum);
    axis->SetRange(first+1,last);

    h2 = (TH1F*) fin->Get(h2_name.c_str());
    axis = h2->GetXaxis();
    first = axis->GetFirst();
    last  = axis->GetLast();
    sum = h2->Integral(first+1,last); 
    h2->Scale(1./sum);
    axis->SetRange(first+1,last);

    max1 = h1->GetMaximum();
    max2 = h2->GetMaximum();

    max = 1.1*TMath::Max(max1,max2);
    h1->SetMaximum(max);

    //For Edgar's APS Plots
    h1->SetStats(kFALSE);
    h2->SetStats(kFALSE);
    
    h1->GetXaxis()->SetLabelSize(0.05);
    h2->GetXaxis()->SetLabelSize(0.05);

	//Ndiv = h1->GetXaxis()->GetNdivisions(); cout<<"Ndiv is "<<Ndiv<<endl;
	h1->GetXaxis()->SetNdivisions(10);

    h1->SetTitle("");
    h2->SetTitle("");
    ///////////

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
*/
void
MakePlots2(){
    
}

void
PlotEff(TFile* fin, string title){
    printf("  Plot Eff\n");

    string dir1 = "wprime400";
    string dir2 = "wzjj";

    string h1_name = dir1 + "/" + title;
    string h2_name = dir2 + "/" + title;
    string filename = title + ".eps";

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
PlotList(TEntryList* SMergedlist,TEntryList* BMergedlist,string title){
    printf("  Plot Lists\n");
    TCanvas c1;

    string filename = title + ".eps";

    TFile *fin1 = TFile::Open("data/Wprime400_mergedOutputTree.root");
    TFile *fin2 = TFile::Open("data/WZjj_mergedOutputTree.root");
 
    TTree* tree1 = (TTree*) fin1->Get("WZ");
    TTree* tree2 = (TTree*) fin2->Get("WZ");
     
    tree1->SetEntryList(SMergedlist);
    tree2->SetEntryList(BMergedlist);
    
    tree1->SetLineColor(kRed);
    tree2->SetLineColor(kBlue);

    tree1->Draw(title.c_str(),"weight");
    tree2->Draw(title.c_str(), "weight", "same");    

    c1.SaveAs(filename.c_str());

    //list1->Print("all");
    printf("Signal Tree: %s\n",SMergedlist->GetTreeName());
    cout<<"Signal: "<<SMergedlist->GetN()<<endl
	<<"Bkgrd: "<<BMergedlist->GetN()<<endl;

    //BMergedlist->Print("all");
}

void
GetLists(TFile* fin,TEntryList** Slist,TEntryList** Blist){
    printf("  Get Lists\n");
    for(int i=0;i<Nlists;++i){
	Slist[i] = (TEntryList*) fin->Get(Form("wprime400/cut%i",i));
	Blist[i] = (TEntryList*) fin->Get(Form("wzjj/cut%i",i));
    }
}

TEntryList* 
ListAnd(TEntryList* l1,TEntryList* l2){
    printf("  List Add\n");
    int size = l1->GetN();
    TEntryList* l3 = new TEntryList("mergedcuts","merged");

    int evtnum = l1->GetEntry(0);
    for(int i=0;i<size;++i){
	if(l2->Contains(evtnum)) l3->Enter(evtnum);
	evtnum = l1->Next();
    }

    return l3;
}

TEntryList* 
ListAnd(vector<TEntryList*> list){
    printf("  List And (Vectors)\n");
    int Nlistused = list.size();
    int Nevts = list.at(0)->GetN();
    TEntryList* newlist = new TEntryList("mergedcuts","merged");
    
    bool keep = true;
    int evtnum = list.at(0)->GetEntry(0); //initialize
    for(int i=0;i<Nevts;++i){
	keep = true;
	for(int j=0;keep && j<Nlistused; ++j){
	    if(!list.at(j)->Contains(evtnum)) keep=false;
	}
	if(keep) newlist->Enter(evtnum);
	evtnum = list.at(0)->Next();
    }

    return newlist;
}

string convertFloattoStr(float num){
    stringstream ss;
    ss << num;
    return ss.str();
}
