//Usage: root -b -q "Est_Zjets.C+(useElec, useData)"

#include <vector>
#include "THStack.h"
#include "TStyle.h"
#include "TLine.h"
#include "consts.h"

void
Est_Zjets(bool useElec=false, bool useData=false){  
    TFile *f = TFile::Open("../WprimeAnalyzer/ZJets_analysis.root", "read");

    map<string,float> allsamples;
    if(!useData){
      allsamples["TTbar2l_Dilepton"]=KFactor("TTbar2l");
//      allsamples["TTbar2l"]=KFactor("TTbar2l");
      allsamples["WenuJets_Dilepton"]=KFactor("WmunuJets");
//      allsamples["WenuJets"]=KFactor("WmunuJets");
      allsamples["WmunuJets_Dilepton"]=KFactor("WmunuJets");
//      allsamples["WmunuJets"]=KFactor("WmunuJets");
      allsamples["ZJetsBinned_Dilepton"]=KFactor("ZJetsBinned");
      allsamples["ZJetsBinned"]=KFactor("ZJetsBinned");
//      allsamples["Wprime400_Dilepton"]=KFactor("Wprime400");
//      allsamples["Wprime400"]=KFactor("Wprime400");
    }else{
      allsamples["Run2010_Dilepton"]=1.;
//      allsamples["Run2010"]=1.;
    }
    TH1F* allTThist=NULL;
    TH1F* allTFhist=NULL;
    if(useElec){
      allTThist = get_sum_of_hists(f, allsamples,"hZeemassTT_AllCuts", 0);
      allTFhist = get_sum_of_hists(f, allsamples,"hZeemassTF_AllCuts", 0);
    }else{
      allTThist = get_sum_of_hists(f, allsamples,"hZmumumassTT_AllCuts", 0);
      allTFhist = get_sum_of_hists(f, allsamples,"hZmumumassTF_AllCuts", 0);
    }

    TF1* linearTT = new TF1("linearTT", fline, 60, 120, 2);
    TF1* linearTF = new TF1("linearTF", fline, 60, 120, 2);

    cout<<"Fitting Background TT"<<endl;
    TCanvas* c1 = new TCanvas("c1", "Z Mass TT");
    reject = true;
    allTThist->Fit(linearTT, "MRELL");
    reject = false;
    double B_TT = linearTT->Integral(ZWind_low,ZWind_high);
    double sigma_B_TT = linearTT->IntegralError(ZWind_low,ZWind_high);

    c1->Print("fit_zjets_BTT.gif");

    cout<<"Fitting Background TF"<<endl;
    TCanvas* c2 = new TCanvas("c2", "Z Mass TF");
    reject = true;
    allTFhist->Fit(linearTF, "MRELL");
    reject = false;
    double B_TF = linearTF->Integral(ZWind_low,ZWind_high);
    double sigma_B_TF = linearTF->IntegralError(ZWind_low,ZWind_high);
    c2->Print("fit_zjets_BTF.gif");

    int lowBin, highBin;
    lowBin = allTThist->FindBin(ZWind_low);  
    highBin = allTThist->FindBin(ZWind_high);

    //double N_TT = allTThist->IntegralAndError(low,high,sigma_N_TT);
    //double N_TF = allTFhist->IntegralAndError(low,high,sigma_N_TF);
    double N_TT = allTThist->Integral(lowBin,highBin);
    double N_TF = allTFhist->Integral(lowBin,highBin);

    double sigma_N_TT = IntegralError(allTThist, lowBin, highBin);
    double sigma_N_TF = IntegralError(allTFhist, lowBin, highBin);
    ///////////////////////

    double num = 2*(N_TT - B_TT);
    double denom = (N_TF - B_TF) + 2*(N_TT - B_TT);
    double e_tight = num / denom;

    double sigma2_TT = sigma_N_TT*sigma_N_TT + sigma_B_TT*sigma_B_TT;
    double sigma2_TF = sigma_N_TF*sigma_N_TF + sigma_B_TF*sigma_B_TF;

    double term1 = 4 * pow(N_TF-B_TF,2) * sigma2_TT;
    double term2 = 4 * pow(N_TT-B_TT,2) * sigma2_TF;
    double sigma_e = sqrt(term1 + term2) / (denom*denom);

    cout<<"\n\nUsing ";
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

