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
  for(int ilumi=0; ilumi<NLumi; ++ilumi){
    for(int imass=0; imass<NMass; ++imass){
      for(int isData=0; isData<2; ++isData){
        if(ilumi != 0 && isData == 1) continue;
        if(!isData){
          tree->Draw("nBkgEvts:snBkgEvts:Eff:sEff", 
                     Form("isData==%i && Mass==%f && Lumi==%f", 
                          isData, Mass[imass],Lumi[ilumi]), "goff");
        }else{
          tree->Draw("nTotEvts:snTotEvts:Eff:sEff", 
                     Form("isData==%i && Mass==%f && Lumi==%f", 
                          isData, Mass[imass],Lumi[ilumi]), "goff");
        }
        float n = tree->GetSelectedRows();
        if( n != 1){
          cout<<"Something went wrong "<<n<<endl;
          return;
        }
        Double_t  nEvts = tree->GetV1()[0];
        Double_t snEvts = tree->GetV2()[0];
        Double_t  Eff = tree->GetV3()[0];
        Double_t sEff = tree->GetV4()[0];
      
        float sLumi = sLumiFrac*Lumi[ilumi];
        float limit = CLA(Lumi[ilumi], sLumi, 
                          Eff, sEff,
                          nEvts, snEvts);

        out<<setprecision(1)
           <<isData<<"\t"
           <<Mass[imass]<<"\t"
           <<Lumi[ilumi]<<"\t"
           <<sLumi<<"\t"
           <<setprecision(4)
           <<Eff<<"\t"
           <<sEff<<"\t"
           <<nEvts<<"\t"
           <<snEvts<<"\t"
           <<limit<<"\t"
           <<endl;
      }
    }
  }
  out.close(); 
  return;
}
