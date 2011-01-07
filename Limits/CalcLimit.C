/* To Use: 
   root -l CalcLimit.C
*/
#include "consts.h"

void
CalcLimit(){
  
  gROOT->ProcessLine(".L cl95cms.c++");
  
  string outfile("nLimit.txt");
  ofstream out(outfile.c_str());
  if(!out) { 
    cout << "Cannot open file " << outfile << endl; 
    abort();
  } 
  
  out  << setiosflags(ios::fixed) << setprecision(4) << setiosflags(ios::left);
    
  out<<"isData/I:"
     <<"Mass/F:"
     <<"Lumi/F:"
     <<"sLumi/F:"
     <<"Eff/F:"
     <<"sEff/F:"
     <<"nBkgEvts/F:"
     <<"snBkgEvts/F:"
     <<"Limit/F"
     <<endl;

  TTree* tree = new TTree("tree", "Number of Events");
  tree->ReadFile("nEvents.txt");
  for(int i=0; i<NLumi; ++i){
    for(int j=0; j<NMass; ++j){
      for(int isData=0; isData<2; ++isData){
        if(i != 0 && isData == 1) continue;
        if(!isData){
          tree->Draw("nBkgEvts:snBkgEvts:Eff:sEff", 
                     Form("isData==%i && Mass==%f && Lumi==%f", 
                          isData, mass[j],lumi[i]), "goff");
        }else{
          tree->Draw("nTotEvts:snTotEvts:Eff:sEff", 
                     Form("isData==%i && Mass==%f && Lumi==%f", 
                          isData, mass[j],lumi[i]), "goff");
        }
        float n = tree->GetSelectedRows();
        if( n != 1){
          cout<<"Something went wrong "<<n<<endl;
          return;
        }
        Double_t*  nEvts = tree->GetV1();
        Double_t* snEvts = tree->GetV2();
        Double_t*  Eff = tree->GetV3();
        Double_t* sEff = tree->GetV4();
      
        float sLumi = sLumiFrac*lumi[i];
        printf("Mass: %i CLA(%4.2f,%4.2f,%4.4f,%4.4f,%4.2f,%4.2f)\n",
               mass[j],
               lumi[i], sLumi,
               Eff[0], sEff[0],
               nEvts[0], snEvts[0]);
        float limit = 0;
        limit = CLA(lumi[i], sLumi, 
                    Eff[0], sEff[0],
                    nEvts[0], snEvts[0]);

        out<<setprecision(1)
           <<isData<<"\t"
           <<mass[j]<<"\t"
           <<lumi[i]<<"\t"
           <<sLumi<<"\t"
           <<setprecision(4)
           <<Eff[0]<<"\t"
           <<sEff[0]<<"\t"
           <<nEvts[0]<<"\t"
           <<snEvts[0]<<"\t"
           <<limit<<"\t"
           <<endl;
      }
    }
  }
  out.close(); 
  return;
}
