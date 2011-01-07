//Usage: root -b -q Expected_Evts.C

#include "consts.h"

void
Expected_Evts(){

  TFile *f = TFile::Open("../WprimeAnalyzer/Wprime_analysis.root", "read");
  TCanvas* c1 = new TCanvas("c1", "Number of Events");
  string outfile("nEvents.txt");
  ofstream out(outfile.c_str());
  if(!out) { 
    cout << "Cannot open file " << outfile << endl; 
    abort();
  } 

  TTree* tXsec = new TTree("tXsec", "W' Cross Sections");
  tXsec->ReadFile("xSec.txt");

  out<<"isData/I:"
     <<"Mass/F:"
     <<"Lumi/F:"
     <<"nTotEvts/F:"
     <<"statnTotEvts/F:"
     <<"sysnTotEvts/F:"
     <<"snTotEvts/F:"
     <<"nBkgEvts/F:"
     <<"statnBkgEvts/F:"
     <<"sysnBkgEvts/F:"
     <<"snBkgEvts/F:"
     <<"Eff/F:"
     <<"statEff/F:"
     <<"sysEff/F:"
     <<"sEff/F"
     <<endl;
  out  << setiosflags(ios::fixed) << setprecision(4);;

  for(int i=0; i<NLumi; ++i){
    for(int j=0; j<NMass; ++j){

      float weight=lumi[i]/LumiUsed;
      map<string,float> bkgsamples;   
      bkgsamples["TTbar2l"]    =weight*KFactor("TTbar2l");
      //bkgsamples["WenuJets"]   =weight*KFactor("WenuJets");
      //bkgsamples["WmunuJets"]  =weight*KFactor("WmunuJets");
      bkgsamples["WlnuJetsMadgraph"]  =weight*KFactor("WlnuJets");
      bkgsamples["ZJetsBinned"]=weight*KFactor("ZJetsBinned");
      bkgsamples["WZ"]         =weight*KFactor("WZ");
      bkgsamples["ZZ4l"]       =weight*KFactor("ZZ4l");
      bkgsamples["ZGamma"]     =weight*KFactor("ZGamma");
      TH1F* bkghist = get_sum_of_hists(f, bkgsamples, "hWZInvMass_AllCuts", 0);

      map<string,float> allsamples(bkgsamples);  
      string signalName = Form("Wprime%i",(int)mass[j]);
      cout<<"signalName: "<<signalName<<endl;
      allsamples[signalName]=weight*KFactor(signalName);
      TH1F* allhist = get_sum_of_hists(f, allsamples, "hWZInvMass_AllCuts", 0);

      map<string,float> datasamples;
      datasamples["Run2010"]=1.;
      TH1F* datahist = get_sum_of_hists(f, datasamples, "hWZInvMass_AllCuts", 0);

      float fitWindowLow  = mass[j] - 25;
      float fitWindowHigh = mass[j] + 25;
      allhist->Fit("gaus", "", "", fitWindowLow, fitWindowHigh);
      TF1 *fit = allhist->GetFunction("gaus");
    
      double mean = fit->GetParameter(1);
      double gaus_sig = fit->GetParameter(2);
      cout<<"Peak at "<<mean<<" +/- "<<gaus_sig<<endl;

      double lowx = mean - 0.7*gaus_sig;
      double highx = mean + 0.7*gaus_sig;//Cory: Mass Window Method
      //double highx = 2000;//Cory: Trying something new (seems to increase bkg x5.0, signal x0.5)
      int lowbin = allhist->FindBin(lowx);
      int highbin = allhist->FindBin(highx);
    
      cout<<"Integral from mass "<<lowx<<" to "<<highx<<" GeV."<<endl;
      cout<<"Integral from bins "<<lowbin<<" to "<<highbin<<endl;  
    
      double     nTotEvts = allhist->Integral     (lowbin, highbin);
      double statnTotEvts = IntegralError(allhist, lowbin, highbin);
      cout<<"# of All Evts in Mass Window is "<<nTotEvts<<" +/- "<<statnTotEvts<<" per "<<lumi[i]<<" inv pb "<<endl;
      cout<<"Total # of All Evts is "<<allhist->Integral()<<endl;

      double     nBkgEvts = bkghist->Integral     (lowbin, highbin);
      double statnBkgEvts = IntegralError(bkghist, lowbin, highbin);
      cout<<"# of Bkg Evts in Mass Window is "<<nBkgEvts<<" +/- "<<statnBkgEvts<<" per "<<lumi[i]<<" inv pb "<<endl;
      cout<<"Total # of Bkg Evts is "<<bkghist->Integral()<<endl;

      float nSigEvts = nTotEvts - nBkgEvts;
      cout<<"# of Sig Evts in Mass Window is "<<nSigEvts<<" per "<<lumi[i]<<" inv pb "<<endl;
    
      double     nDataEvts = datahist->Integral     (lowbin, highbin);
      double statnDataEvts = IntegralError(datahist, lowbin, highbin);
      cout<<"# of Data Evts in Mass Window is "<<nDataEvts<<" +/- "<<statnDataEvts<<" per "<<lumi[i]<<" inv pb "<<endl;
      cout<<"Total # of Data Evts is "<<datahist->Integral()<<endl;

      //Pull Xsec from txt file
      tXsec->Draw("Xsec", Form("Mass==%f", mass[j]), "goff");
      if(tXsec->GetSelectedRows() != 1){
        cout<<"Wrong\n\n\n\n\n";
        return;
      }
      float xsec = tXsec->GetV1()[0];
      float nGeneratedNorm = lumi[i]*xsec*KFactor(signalName);
      float     Eff = nSigEvts / nGeneratedNorm;
      float statEff = TMath::Sqrt(Eff * (1-Eff)/nGenerated); 
      //float statEff = TMath::Sqrt(Eff * (1-Eff)/nGeneratedNorm); 
      //cout<<"nGenNorm: "<<nGeneratedNorm<<endl;

      //Add in systematic errors
      //Cory: Don't think sys errors are right
      float sysnTotEvts = nTotEvts*sysEvtFrac;
      float sysnBkgEvts = nBkgEvts*sysEvtFrac;
      float sysnDataEvts = 1;
      float sysEff      = Eff*sysEffFrac;

      float snTotEvts = AddInQuad(statnTotEvts, sysnTotEvts);
      float snBkgEvts = AddInQuad(statnBkgEvts, sysnBkgEvts);
      float snDataEvts = AddInQuad(statnDataEvts, sysnDataEvts);
      float sEff      = AddInQuad(statEff,           Eff*sysEffFrac);

      out<<setprecision(1)
         <<setw(4)<<false<<"   "
         <<setw(6)<<mass[j]<<"   "
         <<setw(6)<<lumi[i]<<"   "
         <<setprecision(4)
         <<setw(8)<<    nTotEvts<<"   "
         <<setw(8)<<statnTotEvts<<"   "
         <<setw(8)<< sysnTotEvts<<"   "
         <<setw(8)<<   snTotEvts<<"   "
         <<setw(8)<<    nBkgEvts<<"   "
         <<setw(8)<<statnBkgEvts<<"   "
         <<setw(8)<< sysnBkgEvts<<"   "
         <<setw(8)<<   snBkgEvts<<"   "
         <<setw(6)<<    Eff<<"   "    
         <<setw(6)<<statEff<<"   "
         <<setw(6)<< sysEff<<"   "
         <<setw(6)<<   sEff<<"   "
         <<endl;
      if(i==0){//Print out Data info as well
        out<<setprecision(1)
           <<setw(4)<<true<<"   "
           <<setw(6)<<mass[j]<<"   "
           <<setw(6)<<lumi[i]<<"   "
           <<setprecision(4)
           <<setw(8)<<    nDataEvts<<"   "
           <<setw(8)<<statnDataEvts<<"   "
           <<setw(8)<< sysnDataEvts<<"   "
           <<setw(8)<<   snDataEvts<<"   "
           <<setw(8)<<    nBkgEvts<<"   "
           <<setw(8)<<statnBkgEvts<<"   "
           <<setw(8)<< sysnBkgEvts<<"   "
           <<setw(8)<<   snBkgEvts<<"   "
           <<setw(6)<<    Eff<<"   "    
           <<setw(6)<<statEff<<"   "
           <<setw(6)<< sysEff<<"   "
           <<setw(6)<<   sEff<<"   "
           <<endl;
      }
      c1->SaveAs((signalName + ".eps").c_str());

      map<string, float>::iterator iter;
      for (iter=allsamples.begin(); iter != allsamples.end(); ++iter) {
        map<string, float> persample;
        persample[iter->first]=iter->second;
        TH1F* perhist = get_sum_of_hists(f, persample, "hWZInvMass_AllCuts", 0);
        float n = perhist->Integral(lowbin, highbin);
        cout<<iter->first<<": # of Evts in Mass Window is "<<n<<" per "<<lumi[i]<<" inv pb "<<endl;
              
      }
    }
  }
  return;
}

