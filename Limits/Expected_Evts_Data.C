#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include "TFile.h"
#include "TTree.h" 
#include "TH1F.h"
#include "TF1.h"

//---------------------------------------------------------------
TH1F* get_sum_of_hists(vector<string> samples,string level){
//--------------------------------------------------------------
    int rebinme = 0;
    TH1F* hall;
    const int dim = samples.size();
    TFile *f = TFile::Open("../WprimeAnalyzer/Wprime_analysis.root");

    TH1F* h[dim];
    for (int j = 0;j<dim;++j){
        cout<<"Getting histogram # "<<j+1<<" of "<<dim<<endl;

        string histname = samples[j]+"/hWZInvMass"+level;
        h[j] = (TH1F*)f->Get(histname.c_str());
        cout<<histname<<" status: "<<h[j]<<endl;
        
        //char result[40];   
        //sprintf( result, "%d", j );
        //string myhname = "h"+result;
        //h[j]->SetName(myhname.c_str());
      
        //cout<<"Sample: "<<j<<" = "<<samples[j]<<endl;
        
        
        //cout<<"Setting directory"<<endl;
        /////h[j]->SetDirectory(0);
        //cout<<"Setting errors"<<endl;
        /////h[j]->Sumw2();
        //cout<<"Rebinning"<<endl;
        /////if (rebinme) h[j]->Rebin(rebinme);
        //cout<<"Done with adding this histo"<<endl;
        
    }
    //cout<<"Cloning"<<endl;
    hall = (TH1F*)h[0]->Clone();

    //cout<<"Renaming"<<endl;
    string hallname = "hall";
    hall->SetName(hallname.c_str());

    //cout<<"Adding"<<endl;
    for (int k =1;k<dim;++k){
        hall->Add(h[k]);
    }
    cout<<"Done with adding histograms...."<<endl;
    return hall;

}

void
Expected_Evts(){

    vector<string> allfiles;  
    allfiles.push_back("EGSep17ReReco");
    allfiles.push_back("MuSep17ReReco");
    allfiles.push_back("ElectronPromptReco");
    allfiles.push_back("MuPromptReco");
    TH1F* hist = get_sum_of_hists(allfiles,"_AllCuts");

    hist->Fit("gaus", "", "");
    TF1 *fit = hist->GetFunction("gaus");
    
    double mean = fit->GetParameter(1);
    double gaus_sig = fit->GetParameter(2);
    cout<<"Peak at "<<mean<<" +/- "<<gaus_sig<<endl;

    double lowx = mean - 0.7*gaus_sig;
    double highx = mean + 0.7*gaus_sig;
    int lowbin = hist->FindBin(lowx);
    int highbin = hist->FindBin(highx);
    
    cout<<"Integral from mass "<<lowx<<" to "<<highx<<" GeV."<<endl;
    cout<<"Integral from bins "<<lowbin<<" to "<<highbin<<endl;  
    
    double Nevts = hist->Integral(lowbin, highbin);
    cout<<"# of All Evts in Mass Window is "<<Nevts<<" per inv fb "<<endl;
    cout<<"Total # of All Evts is "<<hist->Integral()<<" per inv fb "<<endl;

/////////////
    return;
}

