#include "consts.h"
/* To Use: 
root -l CalcSig.C
*/
int
CalcSig(){
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
     <<"nBkgEvts:"
     <<"snBkgEvts:"
     <<"sNormFrac:"
     <<"nSigma"
     <<endl;
    
  for(int i=0; i<NLumi; ++i){
    for(int j=0; j<NMass; ++j){
      tree->Draw("nTotEvts:nBkgEvts:snBkgEvts", 
                 Form("Mass==%f && Lumi==%f",mass[j], lumi[i]), "goff");
      float n = tree->GetSelectedRows();
      if( n != 1) cout<<"Something went wrong "<<n<<endl;
      Double_t* nTotEvts  = tree->GetV1();
      Double_t* nBkgEvts  = tree->GetV2();
      Double_t* snBkgEvts = tree->GetV3();

      float nObs = floor(nTotEvts[0]);
      float sNormFrac = snBkgEvts[0] / nBkgEvts[0];

      //nSigma = nSigma(evts, nObs, sBfrac);
      float nSig = nSigma(nBkgEvts[0], nObs, sNormFrac);
      
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
