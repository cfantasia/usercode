//Usage: root -l CalcSig.C

#include "consts.h"

int
CalcSig(bool useTC=0){
  gROOT->ProcessLine(".L nSigma.cc++");

  TTree* tree = new TTree("tree", "Number of Events");
  tree->ReadFile("nEvents.txt");

  TTree* tXsec = new TTree("tXsec", "W' Cross Sections");
  tXsec->ReadFile("xSec.txt");

  TTree* tXsec_TC = new TTree("tXsec", "TC Cross Sections");
  tXsec_TC->ReadFile("xSec_TC.txt");


  string outfile;
  if(!useTC) outfile = "nSigma.txt";
  else       outfile = "nSigma_TC.txt";
  ofstream out(outfile.c_str());
  if(!out) { 
    cout << "Cannot open file " << outfile << endl; 
    abort();
  } 
    
  out  << setiosflags(ios::fixed) << setprecision(3);
  //cout << setiosflags(ios::fixed) << setprecision(2) << setiosflags(ios::left);

  out<<"Mass:"
     <<"Lumi:"
     <<"nObs:"
     <<"nBkgEvts:"
     <<"snBkgEvts:"
     <<"sNormFrac:"
     <<"nSigma"
     <<endl;
    
  for(int i=0; i<NLumi; ++i){
    for(int j=0; j<NMass; ++j){
      tree->Draw("nTotEvts:nBkgEvts:snBkgEvts", 
                 Form("Mass==%f && Lumi==%f",mass[j], lumi[i]), "goff");
      Double_t n = tree->GetSelectedRows();
      if( n != 1) cout<<"Something went wrong "<<n<<endl;
      Double_t* nTotEvts  = tree->GetV1();
      Double_t* nBkgEvts  = tree->GetV2();
      Double_t* snBkgEvts = tree->GetV3();

      Double_t nObs = floor(nTotEvts[0]);
      if(useTC){//Scale to # of TC
        tXsec->Draw("Xsec", Form("Mass==%f", mass[j]), "goff");
        tXsec_TC->Draw("Xsec", Form("Rho==%f && Pi==%f", 
                                    mass[j], mass[j]-50), "goff");//Cory: High Pi Mass
        if(tXsec->GetSelectedRows() != 1) cout<<"Wrong\n\n\n\n\n";
        if(tXsec_TC->GetSelectedRows() != 1) cout<<"Wrong\n\n\n\n\n";
        
        Double_t nSig = nTotEvts[0] - nBkgEvts[0];
        nSig *= tXsec_TC->GetV1()[0] / tXsec->GetV1()[0];
        nObs = floor(nSig);
      }
      Double_t sNormFrac = snBkgEvts[0] / nBkgEvts[0];

      //nSigma = nSigma(evts, nObs, sBfrac);
      Double_t nSig = nSigma(nBkgEvts[0], nObs, sNormFrac);
      
      out<<mass[j]<<"\t"
         <<lumi[i]<<"\t"
         <<nObs<<"\t"
         <<nBkgEvts[0]<<"\t"
         <<snBkgEvts[0]<<"\t"
         <<sNormFrac<<"\t"
         <<nSig<<"\t"
         <<endl;
      
      cout<<mass[j]<<"\t"
          <<lumi[i]<<"\t"
          <<nObs<<"\t"
          <<nBkgEvts[0]<<"\t"
          <<snBkgEvts[0]<<"\t"
          <<sNormFrac<<"\t"
          <<nSig<<"\t"
          <<endl;
    }//Mass Loop
  }//Lumi Loop    
  out.close(); 
}
