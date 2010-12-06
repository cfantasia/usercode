#include "consts.h"

void
Expected_Evts(){

  TCanvas* c1 = new TCanvas("c1", "Number of Events");
  string outfile("nEvents.txt");
  ofstream out(outfile.c_str());
  if(!out) { 
    cout << "Cannot open file " << outfile << endl; 
    abort();
  } 

  out<<"Mass/F:"
     <<"nTotEvts/F:"
     <<"snTotEvts/F:"
     <<"nBkgEvts/F:"
     <<"snBkgEvts/F:"
     <<"Eff/F:"
     <<"sEff/F"
     <<endl;
  out  << setiosflags(ios::fixed) << setprecision(4) << setiosflags(ios::left);

  for(int j=0; j<NMass; ++j){

    vector<string> bkgfiles;  
    bkgfiles.push_back("TTbar2l");
    bkgfiles.push_back("WenuJets");
    bkgfiles.push_back("WmunuJets");
    bkgfiles.push_back("ZJetsBinned");
    //bkgfiles.push_back("ZeeJets");
    //bkgfiles.push_back("ZmumuJets");
    bkgfiles.push_back("WZ");
    bkgfiles.push_back("ZZ4l");
    bkgfiles.push_back("ZGamma");
    TH1F* bkghist = get_sum_of_hists(bkgfiles,"_AllCuts");

    vector<string> allfiles(bkgfiles);  
    if( mass[j] < 400 ) allfiles.push_back(Form("TC%i",(int)mass[j]));
    else allfiles.push_back(Form("Wprime%i",(int)mass[j]));
    TH1F* hist = get_sum_of_hists(allfiles,"_AllCuts");

    hist->Fit("gaus", "", "", mass[j] - 50, mass[j] + 50);
    TF1 *fit = hist->GetFunction("gaus");
    
    double mean = fit->GetParameter(1);
    double gaus_sig = fit->GetParameter(2);
    cout<<"Peak at "<<mean<<" +/- "<<gaus_sig<<endl;

    double lowx = mean - 0.7*gaus_sig;
    double highx = 2000;//mean + 0.7*gaus_sig;//Cory: Trying something new
    int lowbin = hist->FindBin(lowx);
    int highbin = hist->FindBin(highx);
    
    //cout<<"Max at "<<hist->GetMaximumBin()<<endl;
    //cout<<"Max at "<<hist->GetBinCenter(hist->GetMaximumBin())<<endl;
    cout<<"Integral from mass "<<lowx<<" to "<<highx<<" GeV."<<endl;
    cout<<"Integral from bins "<<lowbin<<" to "<<highbin<<endl;  
    
    double  nTotEvts = hist->Integral(lowbin, highbin);
    double snTotEvts = 0;
    cout<<"# of All Evts in Mass Window is "<<nTotEvts<<" per inv fb "<<endl;
    cout<<"Total # of All Evts is "<<hist->Integral()<<" per inv fb "<<endl;
    for(int bin=lowbin;bin<=highbin;bin++) {
      snTotEvts += TMath::Power( hist->GetBinError(bin),2 );
    }
    snTotEvts = sqrt(snTotEvts);

    double  nBkgEvts = bkghist->Integral(lowbin, highbin);
    double snBkgEvts = 0;
    cout<<"# of Bkg Evts in Mass Window is "<<nBkgEvts<<" per inv fb "<<endl;
    cout<<"Total # of Bkg Evts is "<<bkghist->Integral()<<" per inv fb "<<endl;
    for(int bin=lowbin;bin<=highbin;bin++) {
      snBkgEvts += TMath::Power( bkghist->GetBinError(bin),2 );
    }
    snBkgEvts = sqrt(snBkgEvts);

    float nSigEvts = nTotEvts - nBkgEvts;
    cout<<"# of Sig Evts in Mass Window is "<<nSigEvts<<" per inv fb "<<endl;
    
    float nGeneratedNorm = LumiUsed*xsec[j];
    float  Eff = nSigEvts / nGeneratedNorm;
    float sEff = TMath::Sqrt(Eff * (1-Eff)/nGeneratedNorm); 

    out<<mass[j]<<"\t"
       <<nTotEvts<<"\t"
       <<snTotEvts<<"\t"
       <<nBkgEvts<<"\t"
       <<snBkgEvts<<"\t"
       <<Eff<<"\t"    
       <<sEff<<"\t"
       <<endl;

    c1->SaveAs(Form("Wprime%i.eps",(int)mass[j]));
  }


    /////////////////////////////////////
    /*
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
    */
  return;
}

