//Usage: root -l CalcSig.C

#include "consts.h"

void
CalcSig(bool useTC=0){
  gROOT->ProcessLine(".L nSigma.cc++");

  TTree* tree = new TTree("tree", "Number of Events");
  tree->ReadFile("nEvents.txt");

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
    
  for(int ilumi=0; ilumi<NLumi; ++ilumi){
    for(int imass=0; imass<NMass; ++imass){
      for(int isData=0; isData<2; ++isData){
        if(ilumi != 0 && isData == 1) continue;
        tree->Draw("nTotEvts:nBkgEvts:snBkgEvts", 
                   Form("Mass==%f && Lumi==%f && isData==%i",
                        Mass[imass], Lumi[ilumi], isData), "goff");
        Double_t n = tree->GetSelectedRows();
        if( n != 1){
          cout<<"Something went wrong "<<n<<endl;
          cout<<Form("Mass==%f && Lumi==%f",Mass[imass], Lumi[ilumi])<<endl<<endl<<endl;
          return;
        }
        Double_t nTotEvts  = tree->GetV1()[0];
        Double_t nBkgEvts  = tree->GetV2()[0];
        Double_t snBkgEvts = tree->GetV3()[0];
        //Double_t snBkgEvts = min(tree->GetV3()[0], nBkgEvts);//Cory: remove min

        Double_t nObsEvts = floor(nTotEvts);
        if(useTC){//Scale to # of TC
          Double_t Mpi = Mass[imass]*3/4 - 25;
          Double_t ratio = XSecTC(Mass[imass], Mpi) / XSec(Mass[imass]);//Right, from PAS
          //Double_t ratio = XSecTC10TeV(Mass[imass]) / XSec(Mass[imass]);
          Double_t nSigEvts = (nTotEvts - nBkgEvts) * ratio;
          nObsEvts = floor(nSigEvts+nBkgEvts);

          cout<<"Mass: "<<Mass[imass]<<endl;
          cout<<"Pi: "<<Mpi<<endl;
          cout<<"Lumi: "<<Lumi[ilumi]<<endl;
          cout<<"W' xSec: "<<XSec(Mass[imass])<<endl;
          cout<<"TC xSec: "<<XSecTC(Mass[imass], Mpi)<<endl;
          //cout<<"TC xSec: "<<XSecTC10TeV(Mass[imass])<<endl;
          cout<<"ratio: "<<ratio<<endl;
          cout<<"nTot:"<<nTotEvts<<endl;
          cout<<"nBkg:"<<nBkgEvts<<endl;
          cout<<"nSig W':"<<nTotEvts - nBkgEvts<<endl;
          cout<<"nSig TC:"<<nSigEvts<<endl;
          cout<<"nObs W':"<<floor(nTotEvts)<<endl;
          cout<<"nObs TC:"<<nObsEvts<<endl;
          cout<<endl;

        }
        Double_t sNormFrac = snBkgEvts / nBkgEvts;

        //nSigma = nSigma(evts, nObs, sBfrac);
        Double_t nSig = nSigma(nBkgEvts, nObsEvts, sNormFrac);

        out<<isData<<"\t"
           <<setprecision(1)
           <<setw(6)<<Mass[imass]<<"\t"
           <<setw(6)<<Lumi[ilumi]<<"\t"
           <<setw(6)<<nObsEvts<<"\t"
           <<setprecision(4)
           <<setw(6)<<nBkgEvts<<"\t"
           <<setw(6)<<snBkgEvts<<"\t"
           <<setw(6)<<sNormFrac<<"\t"
           <<setw(6)<<nSig<<"\t"
           <<endl;
      }//isData Loop
    }//Mass Loop
  }//Lumi Loop    
  out.close(); 
}
