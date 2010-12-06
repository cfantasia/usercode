//Macro to estimate the non-zpeaking background in a WZ resonance
//Author: Edgar Carrera with bits from root examples
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string>
#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"

TH1F* zmasshist;
const double PI=3.14159265358979323846;

//----------------------------------------------------------
Double_t zfuncbreit(Double_t *x, Double_t *par) {
//-----------------------------------------------------------
   //[0]=half width
   //[1]=mean
   //[2]=norm
    return par[0]*par[2]/( PI * ((x[0]-par[1])*(x[0]-par[1]) + par[0]*par[0]) );
}

// Linear background function
//----------------------------------------------------------
Double_t background_linear(Double_t *x, Double_t *par) {
//----------------------------------------------------------
   return par[0] + par[1]*x[0];
}
// Sum of background and peak function
//----------------------------------------------------------
Double_t fitFunction_linear(Double_t *x, Double_t *par) {
//----------------------------------------------------------
  return background_linear(x,par) + zfuncbreit(x,&par[2]);
}


//-----------------------------------------------------------
TF1* shape_nozpeakfunc(TH1F* myh){
//-----------------------------------------------------------
    
    TF1 *Pfunc = new TF1("Pfunc",background_linear,60,120,2);
        
    //Pfunc->SetParLimits(0,0.0001,100.);
    //Pfunc->SetParameter(0,4.24);
    myh->Fit(Pfunc,"MRLL");
    //myh->Fit(Pfunc,"MRELL");
    return Pfunc;
    
}


//-----------------------------------------------------------
TF1* shape_zpeakfunc(TH1F* myh ){
//-----------------------------------------------------------
    
    TF1 *BGfunc = new TF1("BGfunc",zfuncbreit,81,101,3);

    BGfunc->SetParameter(0,5);
    BGfunc->SetParameter(1,90.2);
    BGfunc->SetParameter(2,10);
    
    BGfunc->SetParLimits(1,85.,95.);

    myh->Fit(BGfunc,"MRELL");

    return BGfunc;
    
}



//-----------------------------------------------------------
TF1* shape_allfunc(TH1F* myh, Double_t polpars[]){
//-----------------------------------------------------------
    TF1* FitAllfunc;
    FitAllfunc = new TF1("FitAllfunc",fitFunction_linear,60,120,5);
    
    FitAllfunc->SetParameter(0,polpars[0]); FitAllfunc->SetParName(0,"Const Coef");
    FitAllfunc->SetParameter(1,polpars[1]); FitAllfunc->SetParName(1,"Linear Coef");
    FitAllfunc->SetParameter(2,10); FitAllfunc->SetParName(2,"Half Width");
    FitAllfunc->SetParameter(3,91); FitAllfunc->SetParName(3,"Z peak");
    FitAllfunc->SetParameter(4,10); FitAllfunc->SetParName(4,"Breit Norm");
    
    //cout<<"finished constructing FitAllfunc"<<endl;        
    myh->Fit(FitAllfunc,"MRELL");

    return FitAllfunc;

}

//----------------------------------------------------------
void fit_sideband() {
//----------------------------------------------------------
    //gROOT->ProcessLine(".L tdrstyle.C");
    //gROOT->ProcessLine("setTDRStyle()");
    gROOT->ProcessLine("gStyle->SetOptStat(0)");
    
    TFile *f = TFile::Open("../WprimeAnalyzer/Wprime_analysis.root", "read");
    
    cout<<"$$$$$$$$$$$$$$$$$$  get Z mass template function"<<endl;
    TCanvas *c1 = new TCanvas("c1");
    c1->cd();
    //1.get the samples to shape the Z
    vector<string> zshapesamples;
    zshapesamples["Wprime400"]=1;
    zshapesamples["WZ"]=1;
    zshapesamples["ZGamma"]=1;
    zshapesamples["ZJetsBinned"]=1;
    zshapesamples["ZZ4l"]=1;

    TH1F* zpeakhist = get_sum_of_hists(f, zshapesamples, "hZmass_AllCuts", 4);//_Zcut  
    //2.shape the function
    TF1* zpeakfunc;
    zpeakfunc = shape_zpeakfunc(zpeakhist);
    Double_t zpeakfunc_pars[3];
    zpeakfunc->GetParameters(zpeakfunc_pars);

    zpeakfunc->SetParameters(zpeakfunc_pars);
    zpeakhist->Fit(zpeakfunc,"MRELL", "e1");
    
    c1->Print("fit_zpeak.gif");

    ///////////////////////////////

    cout<<"$$$$$$$$$$$$$$$$$  get the non-genuine-Z background shape"<<endl;
    TCanvas *c2 = new TCanvas("c2");
    c2->cd();
    //1.get the samples to shape the non-genuine Z background
    vector<string> nozshapesamples;
    nozshapesamples["TTbar2l"]=1;
    nozshapesamples["WenuJets"]=1;
    nozshapesamples["WmunuJets"]=1;
    TH1F* nozpeakhist = get_sum_of_hists(f, nozshapesamples, "hZmass_AllCuts", 4);

    //2.shape the function
    TF1* nozpeakfunc;
    nozpeakfunc = shape_nozpeakfunc(nozpeakhist);
    Double_t nozpeakfunc_pars[2];
    nozpeakfunc->GetParameters(nozpeakfunc_pars);
    //try once again
    nozpeakfunc->SetParameters(nozpeakfunc_pars);

    nozpeakhist->Fit(nozpeakfunc,"MRLL", "e1");
    //nozpeakhist->Fit(nozpeakfunc,"MRELL");
    c2->Print("fit_nozpeak.gif");

    cout<<"$$$$$$$$$$$$$$ fit signal + background"<<endl;
   
   
    //1.get the samples
    vector<string> allshapesamples;
    allshapesamples["Wprime400"]=1; cout<<"Using W' in signal"<<endl;
    //allshapesamples["TC400"]=1;  cout<<"Using TC in signal"<<endl;
    allshapesamples["WZ"]=1;
    allshapesamples["TTbar2l"]=1;
    allshapesamples["ZZ4l"]=1;
    allshapesamples["ZGamma"]=1;
    allshapesamples["ZJetsBinned"]=1;
    allshapesamples["Wenuets"]=1;
    allshapesamples["Wmunuets"]=1;
    TH1F* allhist = get_sum_of_hists(f, allshapesamples, "hZmass_AllCuts", 4);

    //2.shape the function

    TCanvas *c3 = new TCanvas("c3");
    c3->cd();
    TF1* allfunc;
    allfunc = shape_allfunc(allhist,nozpeakfunc_pars); //Cory:

    allfunc->SetLineColor(kMagenta);
    allfunc->SetLineWidth(2);
    allfunc->SetNpx(500);
    //allhist->Fit(allfunc,"MRELL");
    c3->Print("fit_global.gif");

    ////////////////

    //$$$$$$$$$$$$$$$$$$$Draw and extract the components
    cout<<"  Final Steps "<<endl;

    TCanvas *c4 = new TCanvas("c4");
    c4->cd();
    allhist->Draw("e");//Cory:
    allhist->Fit(allfunc,"MRELL"); //Cory:
    allhist->SetMinimum(0);
    allhist->SetMarkerStyle(1);
    
    //Get the final results of the fit
    TF1 *backFcn = new TF1("backFcn",background_linear,60,120,2);
    backFcn->SetLineColor(kRed);
    backFcn->SetNpx(500);
    
   // write the fit results into the par array
    Double_t* allfunc_pars;
    Double_t* allfunc_errs;
    allfunc_pars = allfunc->GetParameters();
    allfunc_errs = allfunc->GetParErrors ();

    //assign the corresponding parameters to background and signal
    //cout<<"Error 0: "<<allfunc->GetParError(0)<<endl;
    //cout<<"Error 1: "<<allfunc->GetParError(1)<<endl;
    backFcn->SetParameters(allfunc_pars);
    backFcn->SetParErrors (allfunc_errs);
    backFcn->Draw("same");

    TF1 *signalFcn = new TF1("signalFcn",zfuncbreit,81,101,3);
    signalFcn->SetLineColor(kBlue);
    signalFcn->SetNpx(500);
    signalFcn->SetParameters(&allfunc_pars[2]);
    signalFcn->Draw("same"); 

    // draw the legend
    TLegend *legend=new TLegend(0.6,0.45,0.88,0.65);
    legend->AddEntry(allhist,"All MC","lpe");
    legend->AddEntry(backFcn,"Background fit","l");
    legend->AddEntry(signalFcn,"Signal fit (BW)","l");
    legend->AddEntry(allfunc,"Global Fit (Bkg+Sig)","l");
    legend->Draw("same");
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->SetLineWidth(0);
    legend->SetBorderSize(0);

    c4->Print("fit_components.gif");

/*
    allfunc->Print();
    backFcn->Print();
    double N_bk       = backFcn->Integral     (81,101);
    double sigma_N_bk = backFcn->IntegralError(81,101);

    cout<<"Number of background events in range = "<<N_bk
        <<" +/- "<<sigma_N_bk
        <<endl;
*/
    ///////////////////////
    double sumbkg = 0;
    double sumerr_sq = 0;
    for(int bin=0;bin<nozpeakhist->GetXaxis()->GetNbins();bin++) {
        float x = nozpeakhist->GetBinCenter(bin);
        if(x>=78.67 && x<=103.68) {
            sumbkg += max(0,nozpeakhist->GetBinContent(bin));
            sumerr_sq += TMath::Power( nozpeakhist->GetBinError(bin),2 );
            cout<<x<<"\t"<<nozpeakhist->GetBinContent(bin)<<"\t"<<nozpeakhist->GetBinError(bin)<<endl;
        }
        
    }
    cout<<"sumbkg = "<<sumbkg<<" +/- "<<sqrt(sumerr_sq)<<endl;

    /*
    //binned
    double bkgerrs[2];
    for (int i = 0;i<2;i++) bkgerrs[i] = allfunc->GetParError(i);
    
    double sumbkg = 0;
    double sumerr_sq = 0;
    TF1* errlinearfunc = new TF1("errlinearfunc",error_linear,60,120,2);
    errquadfunc->SetParameters(bkgerrs);
    for(int bin=0;bin<allhist->GetXaxis()->GetNbins();bin++) {
        float x = allhist->GetBinCenter(bin);
        if(x>=78.67 && x<=103.68) {
            sumbkg += backFcn->Eval(x);
            sumerr_sq += TMath::Power(errquadfunc->Eval(x),2);
            cout<<x<<"\t"<<backFcn->Eval(x)<<"\t"<<errquadfunc->Eval(x)<<endl;
        }
        
    }
    */

} 
