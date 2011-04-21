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
  TGraph* gData[NMass];
  TMultiGraph *mg = new TMultiGraph("mg", "Significance vs Luminosity; Luminosity (pb^{-1}); Significance (\\sigma)");
  TCanvas* c1 = new TCanvas("c1", "Significance vs Luminosity");
  TLegend *legend = new TLegend(0.15,0.55,0.50,0.90,"");

  for(int imass=0; imass<NMass; ++imass){
    if(useTC && Mass[imass] > 500) continue;
    tree1->Draw("Lumi:nSigma", Form("Mass==%f && isData==0",Mass[imass]), "goff");
    n = tree1->GetSelectedRows();
    x = tree1->GetV1();
    y = tree1->GetV2();
    gr[imass] = new TGraph(n, x, y);
    gr[imass]->SetLineColor(imass+2);
    if(!useTC) legend->AddEntry(gr[imass], Form("W' %.0f GeV",Mass[imass]), "L");
    else       legend->AddEntry(gr[imass], Form("\\rho_{TC} %.0f GeV",Mass[imass]), "L");
    mg->Add(gr[imass],"L");

    /*//Cory: Don't plot data for now
    tree1->Draw("Lumi:nSigma", Form("Mass==%f && isData==1",Mass[imass]), "goff");
    n = tree1->GetSelectedRows();
    gData[imass] = new TGraph(n, tree1->GetV1(), tree1->GetV2());
    gData[imass]->SetMarkerStyle(kStar);
    gData[imass]->SetMarkerColor(imass+2);
    mg->Add(gData[imass], "P");
    legend->AddEntry(gData[imass], Form("Data (%.0f GeV)",Mass[imass]), "P");
    */
  }
  mg->Draw("a");

  legend->SetTextSize(0.05);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  //legend->SetNColumns(2);
  legend->Draw();

  TLine* l3sigma = new TLine(0,5,5000,5);
  l3sigma->SetLineStyle(9);
  l3sigma->Draw();
  
  TLine* l5sigma = new TLine(0,3,5000,3);
  l5sigma->SetLineStyle(9);
  l5sigma->Draw();

  mg->SetMaximum(7.);

  c1->SetLogx();

  if(!useTC) c1->SaveAs("SignificancevsLumi.eps");
  else       c1->SaveAs("SignificancevsLumi_TC.eps");

}
