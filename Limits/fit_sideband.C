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
//--------------------------------------------------------------
Double_t zhistfunc(Double_t *v, Double_t *par){
//--------------------------------------------------------------
  Double_t x = v[0];
  //cout<<x<<endl;
  TH1D *h1 = (TH1D*)gDirectory->Get("zmasshist");
  
  //cout<<h1->GetNbinsX()<<endl; 
  int ibin = h1->FindBin(x);
  //cout<<ibin<<endl; 
  Double_t y1 = h1->GetBinContent(ibin);
  //cout<<y1<<endl;
  return par[0]*y1;
}  

// Quadratic background function
//----------------------------------------------------------
Double_t zfuncbreit(Double_t *x, Double_t *par) {
//-----------------------------------------------------------
   //[0]=half width
   //[1]=mean
   //[2]=norm
    return par[0]*par[2]/( PI * ((x[0]-par[1])*(x[0]-par[1]) + par[0]*par[0]) );
}


// Quadratic background function
//----------------------------------------------------------
Double_t background_quad(Double_t *x, Double_t *par) {
//-----------------------------------------------------------
    return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}


//Integrated quadratic function
//-------------------------------------------------------------
Double_t integrated_background_quad(Double_t x, Double_t *par){
//-------------------------------------------------------------

    return par[0]*x + 0.5*par[1]*x*x + 
        (1/3.)*par[2]*x*x*x;
}




//Error on quadratic function
//-------------------------------------------------------------
Double_t error_quad(Double_t *x, Double_t *par){
//-------------------------------------------------------------
    return sqrt(par[0]*par[0] + 
                par[1]*par[1]*TMath::Power(x[0],2) + 
                par[2]*par[2]*TMath::Power(x[0],4));
}



//Error on integrated quadratic
//-------------------------------------------------------------
Double_t integrated_error_quad(Double_t x, Double_t *par){
//-------------------------------------------------------------
    return sqrt(par[0]*par[0]*x*x + 
                0.25*par[1]*par[1]*TMath::Power(x,4) + 
                (1/9.)*par[2]*par[2]*TMath::Power(x,6));
}



// Linear background function
//----------------------------------------------------------
Double_t background_linear(Double_t *x, Double_t *par) {
//----------------------------------------------------------
   return par[0] + par[1]*x[0];
}




/*--------------------------------------------------------------------*/
Double_t breitgausfun(Double_t *x, Double_t *par) 
/*--------------------------------------------------------------------*/
{

   //Fit parameters:
   //par[0]=Width (scale) Breit-Wigner
   //par[1]=Most Probable (MP, location) Breit mean
   //par[2]=Total area (integral -inf to inf, normalization constant)
   //par[3]=Width (sigma) of convoluted Gaussian function
   //
   //In the Landau distribution (represented by the CERNLIB approximation), 
   //the maximum is located at x=-0.22278298 with the location parameter=0.
   //This shift is corrected within this function, so that the actual
   //maximum is identical to the MP parameter.

      // Numeric constants
      Double_t invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
      Double_t twoPi = 6.2831853071795;//2Pi

      // Control constants
      Double_t np = 2.0;      // number of convolution steps
      Double_t sc =   1.0;      // convolution extends to +-sc Gaussian sigmas

      // Variables
      Double_t xx;
      Double_t fland;
      Double_t sum = 0.0;
      Double_t xlow,xupp;
      Double_t step;
      Double_t i;

     
      // Range of convolution integral
      xlow = x[0] - sc * par[3];
      xupp = x[0] + sc * par[3];

      step = (xupp-xlow) / np;

      // Convolution integral of Breit and Gaussian by sum
      for(i=1.0; i<=np/2; i++) {
         xx = xlow + (i-.5) * step;
         fland = TMath::BreitWigner(xx,par[1],par[0]);
         sum += fland * TMath::Gaus(x[0],xx,par[3]);

         xx = xupp - (i-.5) * step;
         fland = TMath::BreitWigner(xx,par[1],par[0]);
         sum += fland * TMath::Gaus(x[0],xx,par[3]);
      }

      return (par[2] * step * sum * invsq2pi / par[3]);
}


// Lorenzian Peak function
//----------------------------------------------------------
//Double_t lorentzianPeak(Double_t *x, Double_t *par) {
//----------------------------------------------------------
//  return (0.5*par[0]*par[1]/TMath::Pi()) / 

//    TMath::Max( 1.e-10,(x[0]-par[2])*(x[0]-par[2]) + .25*par[1]*par[1]);
//}





// Sum of background and peak function
//----------------------------------------------------------
Double_t fitFunction_linear(Double_t *x, Double_t *par) {
//----------------------------------------------------------
  return background_linear(x,par) + breitgausfun(x,&par[2]);
}



//----------------------------------------------------------
Double_t fitFunction_quad(Double_t *x, Double_t *par) {
//----------------------------------------------------------
//  return background_quad(x,par) + breitgausfun(x,&par[3]);
    //cout<<"constructing fitFunction_quad"<<endl;

    //return background_quad(x,par) + zhistfunc(x,&par[3]);
  return background_quad(x,par) + zfuncbreit(x,&par[3]);
}


//-----------------------------------------------------------
TF1* shape_nozpeakfunc(TH1F* myh, bool linear=true ){
//-----------------------------------------------------------
    TF1* Pfunc;
    if (linear)
    {    
        TF1 *Pfunc = new TF1("Pfunc",background_linear,60,120,2);
    }
    else Pfunc = new TF1("Pfunc",background_quad,60,120,3);
    
    
    //Pfunc->SetParLimits(0,0.0001,100.);
    //Pfunc->SetParameter(0,4.24);
    myh->Fit(Pfunc,"MRLL");
    //myh->Fit(Pfunc,"MRELL");
    return Pfunc;
    
}


//-----------------------------------------------------------
TF1* shape_zpeakfunc(TH1F* myh ){
//-----------------------------------------------------------
    
    /* Cory
    TF1 *BGfunc = new TF1("BGfunc",breitgausfun,81,101,4);

    BGfunc->SetParameter(0,5);
    BGfunc->SetParameter(1,90.2);
    BGfunc->SetParameter(2,100);
    BGfunc->SetParameter(3,4.5);
    
    BGfunc->SetParLimits(1,85.,95.);
    //BGfunc->SetParLimits(2,0.00001,1.);
    //BGfunc->SetParLimits(3,0.00001,1.);
    

    myh->Fit(BGfunc,"MRELL");
    */
    TF1 *BGfunc = new TF1("BGfunc",zfuncbreit,81,101,3);

    BGfunc->SetParameter(0,5);
    BGfunc->SetParameter(1,90.2);
    BGfunc->SetParameter(2,10);
    
    BGfunc->SetParLimits(1,85.,95.);

    myh->Fit(BGfunc,"MRELL");

    return BGfunc;
    
}



//-----------------------------------------------------------
TF1* shape_allfunc(TH1F* myh,Double_t polpars[],bool linear=true ){
//-----------------------------------------------------------
 TF1* FitAllfunc;
    if(linear){
        FitAllfunc = new TF1("FitAllfunc",fitFunction_quad,60,120,3);
        FitAllfunc->SetParameter(0,polpars[0]);
        FitAllfunc->SetParameter(1,polpars[1]);
    }
    else {
        //FitAllfunc = new TF1("FitAllfunc",fitFunction_quad,60,120,4);//Cory
        FitAllfunc = new TF1("FitAllfunc",fitFunction_quad,60,120,6);

        FitAllfunc->SetParameter(0,polpars[0]); FitAllfunc->SetParName(0,"Const Coef");
        FitAllfunc->SetParameter(1,polpars[1]); FitAllfunc->SetParName(1,"Linear Coef");
        //FitAllfunc->SetParameter(2,polpars[2]);//Cory:
        FitAllfunc->FixParameter(2,0); FitAllfunc->SetParName(2,"Quad Coef");
        FitAllfunc->SetParameter(3,10); FitAllfunc->SetParName(3,"Half Width");
        FitAllfunc->SetParameter(4,91); FitAllfunc->SetParName(4,"Z peak");
        FitAllfunc->SetParameter(5,10); FitAllfunc->SetParName(5,"Breit Norm");

    }
    
    //cout<<"finished constructing FitAllfunc"<<endl;        
    myh->Fit(FitAllfunc,"MRELL");

    return FitAllfunc;

}









//---------------------------------------------------------------
TH1F* get_sum_of_hists(vector<string> samples,bool weighted=true,
                       string level){
//--------------------------------------------------------------
    int rebinme = 4;
    TH1F* hall;
    const int dim = samples.size();
    TFile *f = TFile::Open("../WprimeAnalyzer/Wprime_analysis.root");

    TH1F* h[dim];
    for (int j = 0;j<dim;++j){
        if (weighted) {
            string histname = samples[j]+"/hZmass"+level;
            h[j] = (TH1F*)f->Get(histname.c_str());
            //cout<<histname<<" status: "<<h[j]<<endl;
        }
        else {
            string histname = samples[j]+"/hZmass"+level;
            h[j] = (TH1F*)f->Get(histname.c_str());
        }
        
        //char result[40];   
        //sprintf( result, "%d", j );
        //string myhname = "h"+result;
        //h[j]->SetName(myhname.c_str());
      
        //cout<<"Sample: "<<j<<" = "<<samples[j]<<endl;

        h[j]->SetDirectory(0);
        h[j]->Sumw2();
        if (rebinme) h[j]->Rebin(rebinme);

        
    }

    hall = (TH1F*)h[0]->Clone();
    string hallname = "hall";
    hall->SetName(hallname.c_str());
    for (int k =1;k<dim;++k){
        hall->Add(h[k]);
    }
    cout<<"Done with adding histograms...."<<endl;
    return hall;

}



//----------------------------------------------------------
void fit_sideband() {
//----------------------------------------------------------
    //gROOT->ProcessLine(".L tdrstyle.C");
    //gROOT->ProcessLine("setTDRStyle()");
    gROOT->ProcessLine("gStyle->SetOptStat(0)");
    
    cout<<"$$$$$$$$$$$$$$$$$  get the non-genuine-Z background shape"<<endl;
    TCanvas *c2 = new TCanvas("c2");
    c2->cd();
    //1.get the samples to shape the non-genuine Z background
    vector<string> nozshapefiles;
    /*
    nozshapefiles.push_back("WjetsFast_cutsB_200pb_loose.root");
    nozshapefiles.push_back("TTbarFast_cutsB_200pb_loose.root");
    //nozshapefiles.push_back("WjetsFull26_cutsB_200pb_loose.root");
    //nozshapefiles.push_back("TTbarFast25_cutsB_200pb_loose.root");
    */
    nozshapefiles.push_back("ttbarfast");
    nozshapefiles.push_back("wjets");
    TH1F* nozpeakhist = get_sum_of_hists(nozshapefiles,true,"_AllCuts");//""
    //2.shape the function
    TF1* nozpeakfunc;
    bool linear = false;
    nozpeakfunc = shape_nozpeakfunc(nozpeakhist,linear);
    Double_t nozpeakfunc_pars[3];
    nozpeakfunc->GetParameters(nozpeakfunc_pars);
    //try once again
    nozpeakfunc->SetParameters(nozpeakfunc_pars);

    nozpeakfunc->FixParameter(2,0);//Cory;

    nozpeakhist->Fit(nozpeakfunc,"MRLL", "e1");
    //nozpeakhist->Fit(nozpeakfunc,"MRELL");
    c2->Print("fit_300_nozpeak.gif");






    cout<<"$$$$$$$$$$$$$$ fit signal + background"<<endl;
   
   
    //1.get the samples
    vector<string> allshapefiles;
    /*
    allshapefiles.push_back("TC_M300_cutsB_200pb_effkfac.root");
    allshapefiles.push_back("WZ3lFull_cutsB_200pb_effkfac.root");
    allshapefiles.push_back("ZZ4lFull_cutsB_200pb_effkfac.root");
    allshapefiles.push_back("VQQFull_cutsB_200pb_effkfac.root");
    allshapefiles.push_back("WjetsFast_cutsB_200pb_effkfac.root");
    allshapefiles.push_back("TTbarFast_cutsB_200pb_effkfac.root");
    allshapefiles.push_back("ZllJetBinned_cutsB_200pb_effkfac.root");
    //allshapefiles.push_back("AVjetsFull_cutsB_200pb_effkfac.root");
    */
    allshapefiles.push_back("wprime400"); cout<<"Using W' in signal"<<endl;
    //allshapefiles.push_back("TC400");  cout<<"Using TC in signal"<<endl;
    allshapefiles.push_back("wz");
    allshapefiles.push_back("ttbarfast");
    allshapefiles.push_back("zz");
    allshapefiles.push_back("zgamma");
    allshapefiles.push_back("zjets");
    allshapefiles.push_back("wjets");
    TH1F* allhist = get_sum_of_hists(allshapefiles,true,"_AllCuts");//_mw
    //2.shape the function


cout<<"$$$$$$$$$$$$$$$$$$  get Z mass template function"<<endl;
    TCanvas *c1 = new TCanvas("c1");
    c1->cd();
    //1.get the samples to shape the Z
    vector<string> zshapefiles;
/*
//    zshapefiles.push_back("ZllJetBinned_cutsB_200pb_loose.root");
    zshapefiles.push_back("AVjetsFull_cutsB_200pb_loose.root");
    zshapefiles.push_back("WZ3lFull_cutsB_200pb_loose.root");
*/
    zshapefiles.push_back("wprime400");
    zshapefiles.push_back("wz");
    zshapefiles.push_back("zgamma");
    zshapefiles.push_back("zjets");
    zshapefiles.push_back("zz");

    TH1F* zpeakhist = get_sum_of_hists(zshapefiles,true,"_AllCuts");//_Zcut  
    //store z-peak histogram to use it in the fit
    zmasshist = (TH1F*)zpeakhist->Clone();
    zmasshist->SetName("zmasshist");
    //zpeakhist->Draw("histe");
    //2.shape the function
    TF1* zpeakfunc;
    zpeakfunc = shape_zpeakfunc(zpeakhist);
    Double_t zpeakfunc_pars[3];
    zpeakfunc->GetParameters(zpeakfunc_pars);
    //zpeakfunc->SetLineColor("
    //do it again
    zpeakfunc->SetParameters(zpeakfunc_pars);
    zpeakhist->Fit(zpeakfunc,"MRELL", "e1");
    
    c1->Print("fit_300_zpeak.gif");


    TCanvas *c3 = new TCanvas("c3");
    c3->cd();
    TF1* allfunc;
    //allfunc = shape_allfunc(allhist,nozpeakfunc_pars,zpeakfunc_pars,linear);
    cout<<"A"<<endl;
    allfunc = shape_allfunc(allhist,nozpeakfunc_pars,linear); //Cory:
    cout<<"B"<<endl;

    allfunc->SetLineColor(kMagenta);
    allfunc->SetLineWidth(2);
    allfunc->SetNpx(500);
    //allhist->Fit(allfunc,"MRELL");
    //allhist->Fit(allfunc,"MRELL");
    c3->Print("fit_300_global.gif");





    //$$$$$$$$$$$$$$$$$$$Draw and extract the components
    cout<<"  Final Steps "<<endl;

    TCanvas *c4 = new TCanvas("c4");
    c4->cd();
    allhist->Draw("e");//Cory:
    allhist->Fit(allfunc,"MRELL"); //Cory:
    allhist->SetMinimum(0);
    allhist->SetMarkerStyle(1);
    

    //Get the final results of the fit
    TF1 *backFcn;
    if (linear){ 
        backFcn = new TF1("backFcn",background_linear,60,120,2);
    }
    else backFcn = new TF1("backFcn",background_quad,60,120,3);
    backFcn->SetLineColor(kRed);
    backFcn->SetNpx(500);
    
   // write the fit results into the par array
    //Double_t allfunc_pars[4];//Cory:
    Double_t allfunc_pars[6];
    //Double_t allfunc_errs[4];//Cory:
    Double_t allfunc_errs[6];
    allfunc->GetParameters(allfunc_pars);

    //assign the corresponding parameters to background and signal
    backFcn->SetParameters(allfunc_pars);
    backFcn->Draw("same");

    TF1 *signalFcn = new TF1("signalFcn",zfuncbreit,81,101,3);
    signalFcn->SetLineColor(kBlue);
    signalFcn->SetNpx(500);
    signalFcn->SetParameters(&allfunc_pars[3]);
    signalFcn->Draw("same"); 
    /*Cory:
    TH1F* hsignalFcn = (TH1F*)zpeakhist->Clone("hsignalFcn");
    hsignalFcn->Reset();
    for (Int_t bin=1;bin<=hsignalFcn->GetNbinsX();bin++) {
    
    }
    for(int bin=0;bin<allhist->GetXaxis()->GetNbins();bin++) {
        float x = allhist->GetBinCenter(bin);
        if(x>=81 && x<=101) {
            hsignalFcn->SetBinContent(bin,allfunc_pars[3]*zpeakhist->GetBinContent(bin));
        }
        else hsignalFcn->SetBinContent(bin,0);
    }
    hsignalFcn->SetLineColor(kBlue);
    hsignalFcn->Draw("same");
    */

    // draw the legend
    TLegend *legend=new TLegend(0.6,0.45,0.88,0.65);
    legend->AddEntry(allhist,"All MC","lpe");
    legend->AddEntry(backFcn,"Background fit (Linear)","l");
    //legend->AddEntry(hsignalFcn,"Signal fit (Linear to Z Curve)","l");Cory
    legend->AddEntry(signalFcn,"Signal fit (BW)","l");
    legend->AddEntry(allfunc,"Global Fit (Bkg+Sig)","l");
    legend->Draw("same");
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->SetLineWidth(0);
    legend->SetBorderSize(0);

    /*
    TText* pre = new TText(0.13,0.90,"CMS Preliminary");
    //pre->SetTextAlign(31);
    pre->SetNDC(kTRUE);
    pre->SetTextFont(132);
    pre->Draw("same");
    */
      
    
    //c4->Print("~/web/exotica_wz/iteration15/test/fit_300_components.eps");
    c4->Print("fit_300_components.gif");

/*
    //--------------------------------------------------------------------
    //Check:
    //determine the amount of background
    //this only works if the binning is one
    double mynonzback = backFcn->Integral(78.67,103.68);
    cout<<"non-peak = "<<mynonzback<<endl;
    double myglobal = allfunc->Integral(78.67,103.68);
    cout<<"total = "<<myglobal<<endl;
    double myzpeak = signalFcn->Integral(78.67,103.68);
    cout<<"peaking = "<<myzpeak<<endl;

    //manually
    double mymanualback = fabs(integrated_background_quad(103.68,allfunc_pars)-
                               integrated_background_quad(78.67,allfunc_pars));

    //error on the fit
   
    double errfit = fabs(integrated_error_quad(103.68,bkgerrs)-
                         integrated_error_quad(78.67,bkgerrs));
    cout<<"mymanualback = "<<mymanualback<<" +/- errfit = "<<errfit<<endl;
    //---------------------------------------------------------------------

*/

    double bkgerrs[3];
    for (int i = 0;i<3;i++) bkgerrs[i] = allfunc->GetParError(i);
    
    //binned
    double sumbkg = 0;
    double sumerr_sq = 0;
    TF1* errquadfunc = new TF1("errquadfunc",error_quad,60,120,3);
    errquadfunc->SetParameters(bkgerrs);
    for(int bin=0;bin<allhist->GetXaxis()->GetNbins();bin++) {
        float x = allhist->GetBinCenter(bin);
        if(x>=78.67 && x<=103.68) {
            sumbkg += backFcn->Eval(x);
            sumerr_sq += TMath::Power(errquadfunc->Eval(x),2);
            cout<<x<<"\t"<<backFcn->Eval(x)<<"\t"<<errquadfunc->Eval(x)<<endl;
        }
        
    }
    
    
    cout<<"sumbkg = "<<sumbkg<<" +/- "<<sqrt(sumerr_sq)<<endl;
    ///////////////////////
    sumbkg = 0;
    sumerr_sq = 0;
    for(int bin=0;bin<nozpeakhist->GetXaxis()->GetNbins();bin++) {
        float x = nozpeakhist->GetBinCenter(bin);
        if(x>=78.67 && x<=103.68) {
            sumbkg += nozpeakhist->GetBinContent(bin);
            sumerr_sq += TMath::Power( nozpeakhist->GetBinError(bin),2 );
            cout<<x<<"\t"<<nozpeakhist->GetBinContent(bin)<<"\t"<<nozpeakhist->GetBinError(bin)<<endl;
        }
        
    }
    
    
    cout<<"sumbkg = "<<sumbkg<<" +/- "<<sqrt(sumerr_sq)<<endl;


    //Sephanie's code method:
    //float overall = 103.68-78.67;
    //double _sumerr = overall*integrated_error_quad(overall,bkgerrs);
    //cout<<"_sumerr = "<<_sumerr<<endl;

} 
