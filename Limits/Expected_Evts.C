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
        //cout<<"Getting histogram # "<<j+1<<" of "<<dim<<endl;

        string histname = samples[j]+"/hWZInvMass"+level;
        h[j] = (TH1F*)f->Get(histname.c_str());
        //cout<<histname<<" status: "<<h[j]<<endl;
        
        //cout<<"Setting directory"<<endl;
        /////h[j]->SetDirectory(0);
        //cout<<"Setting errors"<<endl;
        /////h[j]->Sumw2();
        //cout<<"Rebinning"<<endl;
        /////if (rebinme) h[j]->Rebin(rebinme);
        //cout<<"Done with adding this histo"<<endl;
        
    }
    hall = (TH1F*)h[0]->Clone();

    string hallname = "hall";
    hall->SetName(hallname.c_str());

    for (int k =1;k<dim;++k){
        hall->Add(h[k]);
    }
    //cout<<"Done with adding histograms...."<<endl;
    return hall;

}

void
Expected_Evts(){

    vector<string> allfiles;  
    allfiles.push_back("ttbarfast");
    allfiles.push_back("wjets");
    allfiles.push_back("zjets");
    allfiles.push_back("wz");
    allfiles.push_back("zz");
    allfiles.push_back("zgamma");
    //allfiles.push_back("TC400");
    allfiles.push_back("wprime400");
    TH1F* hist = get_sum_of_hists(allfiles,"_AllCuts");

    vector<string> bkgfiles;  
    bkgfiles.push_back("ttbarfast");
    bkgfiles.push_back("wjets");
    bkgfiles.push_back("zjets");
    bkgfiles.push_back("wz");
    bkgfiles.push_back("zz");
    bkgfiles.push_back("zgamma");
    TH1F* bkghist = get_sum_of_hists(bkgfiles,"_AllCuts");

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

    double Nbkgevts = bkghist->Integral(lowbin, highbin);
    cout<<"# of Bkg Evts in Mass Window is "<<Nbkgevts<<" per inv fb "<<endl;
    cout<<"Total # of Bkg Evts is "<<bkghist->Integral()<<" per inv fb "<<endl;

    cout<<"# of Sig Evts in Mass Window is "<<Nevts - Nbkgevts<<" per inv fb "<<endl;


    vector<string> persamplefiles;  
    double evts=0, sigma=0;
   
    persamplefiles.push_back("ttbarfast");
    TH1F* persamplehist = get_sum_of_hists(persamplefiles,"_AllCuts");
    evts = persamplehist->Integral(lowbin, highbin);
    sigma = 0;
    for(int bin=lowbin;bin<=highbin;bin++) {
        sigma += TMath::Power( persamplehist->GetBinError(bin),2 );
    }
    sigma = sqrt(sigma);
    cout<<"# of ttbar Evts in Mass Window is "<<evts<<" +/- "<<sigma<<" per inv fb "<<endl;
    persamplefiles.clear();

    persamplefiles.push_back("wjets");
    TH1F* persamplehist = get_sum_of_hists(persamplefiles,"_AllCuts");
    evts = persamplehist->Integral(lowbin, highbin);
    sigma = 0;
    for(int bin=lowbin;bin<=highbin;bin++) {
        sigma += TMath::Power( persamplehist->GetBinError(bin),2 );
    }
    sigma = sqrt(sigma);
    cout<<"# of wjets Evts in Mass Window is "<<evts<<" +/- "<<sigma<<" per inv fb "<<endl;
    persamplefiles.clear();

    persamplefiles.push_back("zjets");
    TH1F* persamplehist = get_sum_of_hists(persamplefiles,"_AllCuts");
    evts = persamplehist->Integral(lowbin, highbin);
    sigma = 0;
    for(int bin=lowbin;bin<=highbin;bin++) {
        sigma += TMath::Power( persamplehist->GetBinError(bin),2 );
    }
    sigma = sqrt(sigma);
    cout<<"# of zjets Evts in Mass Window is "<<evts<<" +/- "<<sigma<<" per inv fb "<<endl;
    persamplefiles.clear();

    persamplefiles.push_back("wz");
    TH1F* persamplehist = get_sum_of_hists(persamplefiles,"_AllCuts");
    evts = persamplehist->Integral(lowbin, highbin);
    sigma = 0;
    for(int bin=lowbin;bin<=highbin;bin++) {
        sigma += TMath::Power( persamplehist->GetBinError(bin),2 );
    }
    sigma = sqrt(sigma);
    cout<<"# of wz Evts in Mass Window is "<<evts<<" +/- "<<sigma<<" per inv fb "<<endl;
    persamplefiles.clear();

    persamplefiles.push_back("zz");
    TH1F* persamplehist = get_sum_of_hists(persamplefiles,"_AllCuts");
    evts = persamplehist->Integral(lowbin, highbin);
    sigma = 0;
    for(int bin=lowbin;bin<=highbin;bin++) {
        sigma += TMath::Power( persamplehist->GetBinError(bin),2 );
    }
    sigma = sqrt(sigma);
    cout<<"# of zz Evts in Mass Window is "<<evts<<" +/- "<<sigma<<" per inv fb "<<endl;
    persamplefiles.clear();

    persamplefiles.push_back("zgamma");
    TH1F* persamplehist = get_sum_of_hists(persamplefiles,"_AllCuts");
    evts = persamplehist->Integral(lowbin, highbin);
    sigma = 0;
    for(int bin=lowbin;bin<=highbin;bin++) {
        sigma += TMath::Power( persamplehist->GetBinError(bin),2 );
    }
    sigma = sqrt(sigma);
    cout<<"# of zgamma Evts in Mass Window is "<<evts<<" +/- "<<sigma<<" per inv fb "<<endl;
    persamplefiles.clear();

    
    
    return;
}

