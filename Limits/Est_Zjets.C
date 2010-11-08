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
//#include <ExecuteAnalysis.h>

//---------------------------------------------------------------
TH1F* get_sum_of_hists(vector<string> samples,bool useElec,
                       string level){
//--------------------------------------------------------------
    int rebinme = 0;
    TH1F* hall;
    const int dim = samples.size();
    TFile *f = TFile::Open("../WprimeAnalyzer/Wprime_analysis.root");

    TH1F* h[dim];
    for (int j = 0;j<dim;++j){
        cout<<"Getting histogram # "<<j+1<<" of "<<dim<<endl;

        if (useElec) {
            string histname = samples[j]+"/hZeemass"+level;
            h[j] = (TH1F*)f->Get(histname.c_str());
            cout<<histname<<" status: "<<h[j]<<endl;
        }
        else {
            string histname = samples[j]+"/hZmumumass"+level;
            h[j] = (TH1F*)f->Get(histname.c_str());
            cout<<histname<<" status: "<<h[j]<<endl;
        }
       
        //char result[40];   
        //sprintf( result, "%d", j );
        //string myhname = "h"+result;
        //h[j]->SetName(myhname.c_str());
      
        //cout<<"Sample: "<<j<<" = "<<samples[j]<<endl;
        
        
        //cout<<"Setting directory"<<endl;
        h[j]->SetDirectory(0);
        //cout<<"Setting errors"<<endl;
        h[j]->Sumw2();
        //cout<<"Rebinning"<<endl;
        if (rebinme) h[j]->Rebin(rebinme);
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
Est_Zjets(){  
    const bool useElec = false;

    vector<string> nozshapefiles;  
    nozshapefiles.push_back("ttbarfast");
    nozshapefiles.push_back("wjets");
    TH1F* nozpeakTThist = get_sum_of_hists(nozshapefiles,useElec,"TT_MuonHitsUsed");//"TT"
    TH1F* nozpeakTFhist = get_sum_of_hists(nozshapefiles,useElec,"TF_MuonHitsUsed");//"TF"

    vector<string> allfiles;  
    allfiles.push_back("ttbarfast");
    allfiles.push_back("wjets");
    allfiles.push_back("zjets");
    allfiles.push_back("wprime400");
    TH1F* allTThist = get_sum_of_hists(allfiles,useElec,"TT_MuonHitsUsed");//"TT"
    TH1F* allTFhist = get_sum_of_hists(allfiles,useElec,"TF_MuonHitsUsed");//"TF"

    TF1* linearTT = new TF1("linearTT", "[0]+[1]*x", 82, 100);
    TF1* linearTF = new TF1("linearTF", "[0]+[1]*x", 82, 100);

    cout<<"Fitting Background TT"<<endl;
    TCanvas* c1 = new TCanvas("c1");
    nozpeakTThist->Fit(linearTT, "MRELL");
    double B_TT = linearTT->Integral(82,100);
    double sigma_B_TT = linearTT->IntegralError(82,100);
    c1->Print("fit_zjets_BTT.gif");

    cout<<"Fitting Background TF"<<endl;
    TCanvas* c2 = new TCanvas("c2");
    nozpeakTFhist->Fit(linearTF, "MRELL");
    double B_TF = linearTF->Integral(82,100);
    double sigma_B_TF = linearTF->IntegralError(82,100);
    c2->Print("fit_zjets_BTF.gif");

    cout<<"Drawing All TT"<<endl;
    TCanvas* c3 = new TCanvas("c3");
    allTThist->Draw();
    //Fit(linearTT, "MRELL");
    c3->Print("fit_zjets_NTT.gif");

    cout<<"Drawing All TF"<<endl;
    TCanvas* c4 = new TCanvas("c4");
    allTFhist->Draw();
    //Fit(linearTF, "MRELL");
    c4->Print("fit_zjets_NTF.gif");

    int low, high;
    low = allTThist->FindBin(82);  high = allTThist->FindBin(100);

    double sigma_N_TT=0, sigma_N_TF=0;//Cory: Need integral error
    double N_TT = allTThist->IntegralAndError(low,high,sigma_N_TT);
    double N_TF = allTFhist->IntegralAndError(low,high,sigma_N_TF);
    //double N_TT = allTThist->Integral(low,high);
    //double N_TF = allTFhist->Integral(low,high);
    
    double num = 2*(N_TT - B_TT);
    double denom = (N_TF - B_TF) + 2*(N_TT - B_TT);
    double e_tight = num / denom;

    double sigma2_TT = sigma_N_TT*sigma_N_TT + sigma_B_TT*sigma_B_TT;
    double sigma2_TF = sigma_N_TF*sigma_N_TF + sigma_B_TF*sigma_B_TF;

    double term1 = 4 * pow(N_TF-B_TF,2) * sigma2_TT;
    double term2 = 4 * pow(N_TT-B_TT,2) * sigma2_TF;
    double sigma_e = sqrt(term1 + term2) / (denom*denom);

    cout<<endl;
    cout<<"Using ";
    if(useElec) cout<<"Electrons"<<endl;
    else        cout<<"Muons"<<endl;
    cout<<"  B_TT:"<<B_TT<<" +/- " <<sigma_B_TT<<endl
        <<"  B_TF:"<<B_TF<<" +/- " <<sigma_B_TF<<endl
        <<"  N_TT:"<<N_TT<<" +/- " <<sigma_N_TT<<endl
        <<"  N_TF:"<<N_TF<<" +/- " <<sigma_N_TF<<endl
        <<"  e_tight:"<<e_tight<<" +/- " <<sigma_e<<endl
        <<endl;
    //N_loose and N_tight are only observables
    //N_loose = N_lep + N_jet
    //N_tight = e_tight * N_lep + P_fake * N_jet
    //get e_tight and p_fake from data
    //e_tight = 2*(N_TT - B_TT) / [ (N_TF - B_TF) + 2*(N_TT - BTT) ]

}

