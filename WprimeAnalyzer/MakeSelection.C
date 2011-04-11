#include "TText.h"
#include "../Limits/consts.h"
#include "MakePlots.C"

void DrawSelection(TFile* fin, string title, string type);
bool Straddles(float a, float b, float num);

map<string,float> SigSamples;
map<string,float> BkgSamples;
map<string, string> var; //Name, min or max 
map<string, string>::iterator it;

void
MakeSelection(){
  TFile *fin = TFile::Open("Wprime_analysis.root", "read");
  TCanvas c1;
  c1.Print("Selection.pdf[", "pdf"); 

  /***********
    Note: WZ is signal and TTbar + Zjets is background
    for Lepton Cut Plots!!!!!
  ***********/
  SigSamples["WZ3l"]=KFactor("SM WZ3l");

  BkgSamples["ZJetsBinned"]=KFactor("ZJetsBinned");
  BkgSamples["TTbar2l"]=KFactor("TTbar2l");

  //These need to be done for barrell/endcap 1 at a time
  //var["hElecEt"] = "min"; 
  /*
  var["hElecSigmaEtaEta"] = "max";
  var["hElecDPhi"] = "max";
  var["hElecDEta"] = "max";
  var["hElecHOverE"] = "max";
  */
  //var["hElecEP"] = "min";//Not using this cut

  //var["hMuonPt" ) = "min"; 
  /*
  var["hMuonDxy"] = "max"; 
  var["hMuonNormChi2"] = "max";
  var["hMuonNPix"]  = "min";
  var["hMuonNTrk"]  = "min";
  var["hMuonStation"]  = "min";
  */
  //var["hMuonSip"]  = "max";//not using this cut

  //These need to be done for barrell/endcap 1 at a time
  //var["hElecTrkRelIso"] = "max";
  //var["hElecECalRelIso"] = "max";
  //var["hElecHCalRelIso"] = "max";
  //var["hMuonRelIso"]  = "max";
  //var["hWLepIso"]  = "max";

  var["hWTransMass"] = "min";
  var["hMET"] = "min";
  
  for(it=var.begin() ; it != var.end(); it++ ){
    DrawSelection(fin, it->first, it->second);
  }

  SigSamples.clear();
  BkgSamples.clear();
  var.clear();

  SigSamples["Wprime400"]=KFactor("Wprime400");
  //SigSamples["TC300"]=KFactor("TC300");

  BkgSamples["WZ"]=KFactor("WZ");
  BkgSamples["ZJetsBinned"]=KFactor("ZJetsBinned");
  BkgSamples["TTbar2l"]=KFactor("TTbar2l");

  var["hHt"]  = "min";
  var["hZpt"] = "min";
  var["hWpt"] = "min";

   for(it=var.begin() ; it != var.end(); it++ ){
    DrawSelection(fin, it->first, it->second);
  }
   
  c1.Print("Selection.pdf]", "pdf"); 

}

void
DrawSelection(TFile* fin, string title, string type){
  //printf("  Draw Selection\n");
  string fulltitle;
  TH1F* hSig = NULL;
  TH1F* hBkg = NULL;
  for(int cut=0; cut != NCuts; ++cut){
    string title_match = "h" + Cut_Name[cut];
    if(!title_match.compare(title)){
      fulltitle = title + "_" + Cut_Name[cut-1];//Look before cut is applied
      //cout<<"Using Cut: "<<Cut_Name[cut-1]<<" for histo:"<<title<<endl;
      hSig = get_sum_of_hists(fin, SigSamples, fulltitle, 0);
      hBkg = get_sum_of_hists(fin, BkgSamples, fulltitle, 0);
      break;
    }
  }    

  if(!hSig || !hBkg){
    cout<<"Didn't find a histogram\n";
    cout<<"hSig: "<<hSig<<" hBkg:"<<hBkg<<endl;
    return;
  }
  //TAxis* axis = hists[0]->GetXaxis();
  int first = 0;//Include under/over flow
  int last  = hSig->GetNbinsX() + 1;//axis->GetLast() + 1;
  int nbins = hSig->GetNbinsX() + 2;//last-first+1;

  const float Nsig_tot  = hSig->Integral(first, last);
  const float Nbkg_tot  = hBkg->Integral(first, last);

  //printf("Tot sig:%f   Tot Bkg:%f\n", Nsig_tot, Nbkg_tot);
  //printf("first:%i, last:%i, nbins:%i or %i\n", first, last, nbins, hists[0]->GetNbinsX());

  double* Nsig = new double[nbins];
  double* Nbkg = new double[nbins];
  double* fsig = new double[nbins];
  double* fbkg = new double[nbins];

  double* cut = new double[nbins];
  double* Signif = new double[nbins];

  for(int bin=first; bin<=last; ++bin){//for min cut
    //printf("bin:%i low:%f\n",bin, hists[0]->GetBinCenter(bin));
    Nsig[bin] = 0;
    Nbkg[bin] = 0;
    fsig[bin] = 0;
    fbkg[bin] = 0;
    cut[bin] = 0;
    Signif[bin] = 0;

    if(!type.compare("min")){
      Nsig[bin] = hSig->Integral(bin, last);
      Nbkg[bin] = hBkg->Integral(bin, last);
    }else if(!type.compare("max")){
      Nsig[bin] = hSig->Integral(first, bin);
      Nbkg[bin] = hBkg->Integral(first, bin);
    }else{
      cout<<"You screwed up!\n";
      return;
    }
    fsig[bin] = Nsig[bin] / Nsig_tot;
    fbkg[bin] = Nbkg[bin] / Nbkg_tot;
    
    cut[bin] = hSig->GetBinCenter(bin);
    if(Nsig[bin] + Nbkg[bin] > 0) Signif[bin] = Nsig[bin] / sqrt(Nsig[bin] + Nbkg[bin]);
  }

  int cutbin=-1;
  for(int bin=first; bin<last; ++bin){
    if(Straddles(fsig[bin],fsig[bin+1], 0.98)){
      //cout<<"Bin: "<<bin<<" straddles: "<<fsig[bin]<<" -> "<<fsig[bin+1]<<endl;
      cutbin = bin+1;
/*      
      cout<<title<<" cut is "
          <<hSig->GetBinLowEdge(cutbin-1)
          <<" < "<<hSig->GetBinLowEdge(cutbin)
          <<" < "<<hSig->GetBinLowEdge(cutbin+1)<<endl
          <<" With Sig Eff "<<fsig[cutbin]<<" and Bkg Eff "<<fbkg[cutbin]
          <<endl;
*/
      break;
    }
  }


  TCanvas c1;
  string graph_name = "g" + title;
  string graph_title = title + " Selection Plot;Signal Eff;Background Eff";

  TMultiGraph mg(graph_name.c_str(), graph_title.c_str());
  TGraph graph(nbins, fsig, fbkg);
  TGraph point(1, &fsig[cutbin], &fbkg[cutbin]);
  point.SetMarkerColor(kRed);

  mg.Add(&graph,"*");
  mg.Add(&point,"*");
    
  mg.Draw("A");

  TText tCut;
  tCut.SetNDC();
  tCut.SetTextSize(0.1);
  tCut.SetTextColor(2);
  //tCut.SetTextAlign(22);
  tCut.DrawText(0.3, 0.8, Form("Cut is %.1f GeV", hSig->GetBinLowEdge(cutbin)));

  c1.Print("Selection.pdf", "pdf");
  ////////////////////////////
  int Scutbin = 0;
  for(int bin=first; bin<last; ++bin){
    if(Signif[bin] > Signif[Scutbin]) Scutbin = bin;
  }
  
  TCanvas c2;
  graph_title = title + " Selection Plot; Cut Value (GeV);Significance \\frac{S}{sqrt(S+B)}";
  TMultiGraph mgSignif(graph_name.c_str(), graph_title.c_str());
  TGraph gSignif(nbins, cut, Signif);
  TGraph gSignifPoint(1, &cut[Scutbin], &Signif[Scutbin]);
  gSignifPoint.SetMarkerColor(kRed);

  mgSignif.Add(&gSignif,"*");
  mgSignif.Add(&gSignifPoint,"*");
    
  mgSignif.Draw("A");
  

  TText tSignifCut;
  tSignifCut.SetNDC();
  tSignifCut.SetTextSize(0.07);
  tSignifCut.SetTextColor(2);
  //tSignif.SetTextAlign(22);
  tSignifCut.DrawText(0.3, 0.8, Form("Significance Cut is %.1f GeV", hSig->GetBinLowEdge(Scutbin)));

  c2.Print("Selection.pdf", "pdf");
  
}

bool 
Straddles(float a, float b, float num){
  if(a >= num && num >= b) return true;
  if(b >= num && num >= a) return true;
    
  return false;
}
