/* To Use: 
   root -l LumiNeeded.C
*/
#include "consts.h"

void
LumiNeeded(){
  
  gROOT->ProcessLine(".L cl95cms.c++");
  
  string outfile("lumiNeeded.txt");
  ofstream out(outfile.c_str());
  if(!out) { 
    cout << "Cannot open file " << outfile << endl; 
    abort();
  } 
  
  out  << setiosflags(ios::fixed) << setprecision(4) << setiosflags(ios::left);
    
  out<<"Mass:"
     <<"Lumi:"
     <<"sLumi:"
     <<"Eff:"
     <<"sEff:"
     <<"NormEvts:"
     <<"sNormEvts:"
     <<"Limit"
     <<endl;

  TTree* tree = new TTree("tree", "Number of Events");
  tree->ReadFile("nEvents.txt");
  for(int i=0; i<NLumi; ++i){
    for(int j=0; j<NMass; ++j){
      tree->Draw("nBkgEvts:snBkgEvts:Eff:sEff", 
                 Form("Mass==%f",mass[j]), "goff");
      float n = tree->GetSelectedRows();
      if( n != 1){
        cout<<"Something went wrong "<<n<<endl;
        continue;
      }
      Double_t*  nBkgEvts = tree->GetV1();
      Double_t* snBkgEvts = tree->GetV2();
      Double_t*  Eff = tree->GetV3();
      Double_t* sEff = tree->GetV4();
      
      float  NormEvts =  nBkgEvts[0] * lumi[i] / LumiUsed;
      float sNormEvts = snBkgEvts[0] * lumi[i] / LumiUsed;
      float sLumi = sLumiFrac*lumi[i];

      printf("Mass: %i CLA(%4.2f,%4.2f,%4.4f,%4.4f,%4.2f,%4.2f)\n",
             mass[j],
             lumi[i], sLumi,
             Eff[0], sEff[0],
             NormEvts, sNormEvts);
      float limit = 0;
      limit = CLA(lumi[i], sLumi, 
                  Eff[0], sEff[0],
                  NormEvts, sNormEvts);
      out<<mass[j]<<"\t"
         <<lumi[i]<<"\t"
         <<sLumi<<"\t"
         <<Eff[0]<<"\t"
         <<sEff[0]<<"\t"
         <<NormEvts<<"\t"
         <<sNormEvts<<"\t"
         <<limit<<"\t"
         <<endl;
    }
  }
  out.close(); 
  return;
}
