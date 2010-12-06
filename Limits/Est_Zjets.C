/*
Usage: root -b -q "Est_Zjets.C+(1)" //For Electrons
Usage: root -b -q "Est_Zjets.C+(0)" //For Muons
*/

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

const double ZWind_low = 80;
const double ZWind_high = 100;

Bool_t reject;
Double_t fline(Double_t *x, Double_t *par)
{
    if (reject && x[0] > ZWind_low && x[0] < ZWind_high) {
      TF1::RejectPoint();
      return 0;
   }
   return par[0] + par[1]*x[0];
}

void
Est_Zjets(bool useElec=false){  
    TFile *f = TFile::Open("../WprimeAnalyzer/ZJets_analysis.root", "read");

    vector<string> allfiles;  //Cory: Need Weights!!!!
    allfiles.push_back("ttbarfast");
    allfiles.push_back("wjets");
    allfiles.push_back("zjets");
    allfiles.push_back("wprime400");

    vector<float> weights;

    if(useElec){
      TH1F* allTThist = get_sum_of_hists(f, allfiles, weights,"hZeemassTT_MuonHitsCuts", 0);
      TH1F* allTFhist = get_sum_of_hists(f, allfiles, weights,"hZeemassTF_MuonHitsCuts", 0);
    }else{
      TH1F* allTThist = get_sum_of_hists(f, allfiles, weights,"hZmumumassTT_MuonHitsCuts", 0);
      TH1F* allTFhist = get_sum_of_hists(f, allfiles, weights,"hZmumumassTF_MuonHitsCuts", 0);
    }

    TF1* linearTT = new TF1("linearTT", fline, 60, 120, 2);
    TF1* linearTF = new TF1("linearTF", fline, 60, 120, 2);

    cout<<"Fitting Background TT"<<endl;
    TCanvas* c1 = new TCanvas("c1");
    reject = true;
    allTThist->Fit(linearTT, "MRELL");
    reject = false;
    double B_TT = linearTT->Integral(ZWind_low,ZWind_high);
    double sigma_B_TT = linearTT->IntegralError(ZWind_low,ZWind_high);

    c1->Print("fit_zjets_BTT.gif");

    cout<<"Fitting Background TF"<<endl;
    TCanvas* c2 = new TCanvas("c2");
    reject = true;
    allTFhist->Fit(linearTF, "MRELL");
    reject = false;
    double B_TF = linearTF->Integral(ZWind_low,ZWind_high);
    double sigma_B_TF = linearTF->IntegralError(ZWind_low,ZWind_high);
    c2->Print("fit_zjets_BTF.gif");

    int lowBin, highBin;
    lowBin = allTThist->FindBin(ZWind_low);  
    highBin = allTThist->FindBin(ZWind_high);

    double sigma_N_TT=0, sigma_N_TF=0;
    //double N_TT = allTThist->IntegralAndError(low,high,sigma_N_TT);
    //double N_TF = allTFhist->IntegralAndError(low,high,sigma_N_TF);
    double N_TT = allTThist->Integral(lowBin,highBin);
    double N_TF = allTFhist->Integral(lowBin,highBin);

    sigma_N_TT = 0;
    for(int bin=lowBin;bin<=highBin;bin++) {
        //sum_N_TT += allTThist->GetBinContent(bin);
        sigma_N_TT += TMath::Power( allTThist->GetBinError(bin),2 );
    }
    sigma_N_TT = sqrt(sigma_N_TT);
    //cout<<"N_TT: "<<N_TT<<" vs "<<sum_N_TT<<endl;

    sigma_N_TF = 0;
    for(int bin=lowBin;bin<=highBin;bin++) {
        //sum_N_TF += allTFhist->GetBinContent(bin);
        sigma_N_TF += TMath::Power( allTFhist->GetBinError(bin),2 );
    }
    sigma_N_TF = sqrt(sigma_N_TF);
    //cout<<"N_TF: "<<N_TF<<" vs "<<sum_N_TF<<endl;

    ///////////////////////

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
    //doesn't work: P_fake = (N_tight - e_tight*N_lep) / (N_loose - N_lep)
    

}

