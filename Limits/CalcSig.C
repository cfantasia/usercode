//Usage: root -l CalcSig.C

#include "consts.h"

void
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

  out<<"isData/I:"
     <<"Mass/F:"
     <<"Lumi:"
     <<"nObs:"
     <<"nBkgEvts:"
     <<"snBkgEvts:"
     <<"sNormFrac:"
     <<"nSigma"
     <<endl;
    
  for(int i=0; i<NLumi; ++i){
    for(int j=0; j<NMass; ++j){
      for(int isData=0; isData<2; ++isData){
        if(i != 0 && isData == 1) continue;
        tree->Draw("nTotEvts:nBkgEvts:snBkgEvts", 
                   Form("Mass==%f && Lumi==%f && isData==%i",
                        mass[j], lumi[i], isData), "goff");
        Double_t n = tree->GetSelectedRows();
        if( n != 1){
          cout<<"Something went wrong "<<n<<endl;
          cout<<Form("Mass==%f && Lumi==%f",mass[j], lumi[i])<<endl<<endl<<endl;
          return;
        }
        Double_t* nTotEvts  = tree->GetV1();
        Double_t* nBkgEvts  = tree->GetV2();
        Double_t* snBkgEvts = tree->GetV3();

        Double_t nObs = floor(nTotEvts[0]);
        if(useTC){//Scale to # of TC
          tXsec->Draw("Xsec", Form("Mass==%f", mass[j]), "goff");
          tXsec_TC->Draw("Xsec", Form("Rho==%f && Pi==%f", 
                                      mass[j], mass[j]-50), "goff");//Cory: High Pi Mass
          if(tXsec->GetSelectedRows() != 1 || tXsec_TC->GetSelectedRows() != 1){
            cout<<"Wrong\n\n\n\n\n";
            return;
          }
        
          Double_t nSig = nTotEvts[0] - nBkgEvts[0];
          nSig *= tXsec_TC->GetV1()[0] / tXsec->GetV1()[0];
          nObs = floor(nSig+nBkgEvts[0]);
        }
        Double_t sNormFrac = snBkgEvts[0] / nBkgEvts[0];

        //nSigma = nSigma(evts, nObs, sBfrac);
        Double_t nSig = nSigma(nBkgEvts[0], nObs, sNormFrac);
      
        out<<isData<<"\t"
           <<setprecision(1)
           <<setw(6)<<mass[j]<<"\t"
           <<setw(6)<<lumi[i]<<"\t"
           <<setw(6)<<nObs<<"\t"
           <<setprecision(4)
           <<setw(6)<<nBkgEvts[0]<<"\t"
           <<setw(6)<<snBkgEvts[0]<<"\t"
           <<setw(6)<<sNormFrac<<"\t"
           <<setw(6)<<nSig<<"\t"
           <<endl;
      }//isData Loop
    }//Mass Loop
  }//Lumi Loop    
  out.close(); 
}
