//Usage: root -l PlotSig.C++

#include "consts.h"

void
PlotSig(bool useTC=0){
  /*
    Plot for each mass: significance vs lumi
    Read in expected number of evts for each mass and lumi (compare? NO)
  */
  TTree* tree1 = new TTree("tree1", "Significance");
  if(!useTC) tree1->ReadFile("nSigma.txt");
  else tree1->ReadFile("nSigma_TC.txt");

  int n=0;
  Double_t* x=NULL;
  Double_t* y=NULL;
  
  TGraph* gr[NMass];
  TMultiGraph *mg = new TMultiGraph("mg", "Significance vs Lumi; Lumi (pb^{-1}); Signicance (\\sigma)");
  TCanvas* c1 = new TCanvas("c1", "Significance vs Lumi");
  TLegend *legend = new TLegend(0.15,0.60,0.25,0.89,"");

  for(int j=0; j<NMass; ++j){
    tree1->Draw("Lumi:nSigma", Form("Mass==%f",mass[j]), "goff");
    n = tree1->GetSelectedRows();
    x = tree1->GetV1();
    y = tree1->GetV2();
    gr[j] = new TGraph(n, x, y);
    gr[j]->SetLineColor(j+2);
    if(!useTC) legend->AddEntry(gr[j], Form("W' %.0f GeV",mass[j]), "L");
    else       legend->AddEntry(gr[j], Form("\\rho_{TC} %.0f GeV",mass[j]), "L");
    mg->Add(gr[j],"l");
  }
  mg->Draw("a");

  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->Draw();

  TLine* l3sigma = new TLine(0,5,5000,5);
  l3sigma->SetLineStyle(9);
  l3sigma->Draw();
  
  TLine* l5sigma = new TLine(0,3,5000,3);
  l5sigma->SetLineStyle(9);
  l5sigma->Draw();

  mg->SetMaximum(6.);

  
  if(!useTC) c1->SaveAs("SignificancevsLumi.eps");
  else       c1->SaveAs("SignificancevsLumi_TC.eps");

}