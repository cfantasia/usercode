#include "consts.h"
/* To Use: 
root -l CalcSig.C
*/
int
CalcSig(){
  ////////
  //Cory: Fix the number of events, should be read in from output of ExpectedEvts (these are from 357)
  //Cory: Fix error on number of events (systematics, stat, lumi?)
  //    steal Edgars add in quad fn for this.
  //Cory: make fn that plots significance vs lumi for each massOB

  gROOT->ProcessLine(".L nSigma.cc++");

  TTree* tree = new TTree("tree", "Number of Events");
  tree->ReadFile("nEvents.txt");
  

  string outfile("nSigma.txt");
  ofstream out(outfile.c_str());
  if(!out) { 
    cout << "Cannot open file " << outfile << endl; 
    abort();
  } 
    
  out  << setiosflags(ios::fixed) << setprecision(2) << setiosflags(ios::left);
  cout << setiosflags(ios::fixed) << setprecision(2) << setiosflags(ios::left);

  out<<"Mass:"
     <<"Lumi:"
     <<"nObs:"
     <<"normEvts:"
     <<"snormEvts:"
     <<"snormFrac:"
     <<"nSig"
     <<endl;
    
  for(int i=0; i<NLumi; ++i){
    for(int j=0; j<NMass; ++j){
      tree->Draw("nTotEvts:nBkgEvts:snBkgEvts", Form("Mass==%f",mass[j]), "goff");
      float n = tree->GetSelectedRows();
      if( n != 1) cout<<"Something went wrong "<<n<<endl;
      Double_t* nTotEvts  = tree->GetV1();
      Double_t* nBkgEvts  = tree->GetV2();
      Double_t* snBkgEvts = tree->GetV3();

      float nObs = floor(nTotEvts[0] * lumi[i] / LumiUsed);
      float normEvts  =  nBkgEvts[0] * lumi[i] / LumiUsed; 
      float snormEvts = snBkgEvts[0] * lumi[i] / LumiUsed; //Cory: not right

      //nSig = nSigma(evts, nObs, sBfrac);
      float nSig= nSigma(normEvts, nObs, snormEvts/normEvts);
      
      out<<mass[j]<<"\t"
         <<lumi[i]<<"\t"
         <<nObs<<"\t"
         <<normEvts<<"\t"
         <<snormEvts<<"\t"
         <<snormEvts/normEvts<<"\t"
         <<nSig<<"\t"
         <<endl;

      ++nObs;
      
      cout<<mass[j]<<"\t"
          <<lumi[i]<<"\t"
          <<nObs<<"\t"
          <<normEvts<<"\t"
          <<snormEvts<<"\t"
          <<snormEvts/normEvts<<"\t"
          <<nSig<<"\t"
          <<endl;
    }//Mass Loop
  }//Lumi Loop    
  out.close(); 
}
