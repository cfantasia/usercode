#include "consts.h"

int
PlotLumi(){
  /*
    Decide where Xsec info should come from!!!!
  */
  ////Load Trees////////
  TTree* tree1 = new TTree("tree1", "Significance");
  tree1->ReadFile("lumiNeeded.txt");

  TTree* tXsec = new TTree("tXsec", "W' Cross Sections");
  tXsec->ReadFile("xSec.txt");

  TTree* tXsec_TC = new TTree("tXsec", "TC Cross Sections");
  tXsec_TC->ReadFile("xSec_TC.txt");

  //////Now Plot Limit vs Mass//////////////////////
  TCanvas* c1 = new TCanvas("c1", "Limit vs Mass");
  TMultiGraph *mg = new TMultiGraph("mg", "Exclusion Limits vs Mass;M_{WZ} (GeV);\\sigma*BR (pb)");
  TLegend *legend = new TLegend(0.70,0.50,0.95,0.89,"");
  c1->SetLogy();
  float n=0;
  
  tXsec->Draw("Mass:Xsec", "", "goff"); //Sel on W'
  n = tXsec->GetSelectedRows();
  TGraph* gxsec = new TGraph(n, tXsec->GetV1(), tXsec->GetV2());
  mg->Add(gxsec,"lp");
  legend->AddEntry(gxsec,"W' \\sigma", "L");

  tXsec_TC->Draw("Rho:Xsec", "Pi==Rho - 100", "goff");//which pi mass? Sel on TC
  n = tXsec_TC->GetSelectedRows();
  TGraph* gxsec_TC = new TGraph(n, tXsec_TC->GetV1(), tXsec_TC->GetV2());
  gxsec_TC->SetLineStyle(2);
  mg->Add(gxsec_TC,"lp");
  legend->AddEntry(gxsec_TC,"\\rho_{TC} \\sigma", "L");

  TGraph* glumi[NLumi];
  for(int i=0; i<NLumi; ++i){
    tree1->Draw("Mass:Limit", Form("Lumi==%f", lumi[i]), "goff");
    n = tree1->GetSelectedRows();
    glumi[i] = new TGraph(n, tree1->GetV1(), tree1->GetV2());
    if(i+2 <10) glumi[i]->SetLineColor(i+2);
    else        glumi[i]->SetLineColor(i+3);   
    mg->Add(glumi[i], "l*");
    legend->AddEntry(glumi[i],Form("%4.0f pb^{-1}",lumi[i]), "L");
  }
  
  mg->Draw("a");

  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->Draw();
  /*
  mg->GetXaxis()->SetLimits(200,900);
  mg->SetMinimum(xsec[NMass-1]);
  mg->SetMaximum(xsec_TC[0]);
  */
  c1->SaveAs("limitvsMass.gif");
  c1->SaveAs("limitvsMass.eps");
  return 0;

  //////Now plot Limit vs Int Lumi//////////////////////

  TCanvas* c2 = new TCanvas("c2", "Limit vs Integrated Lumi");
  TMultiGraph* mg2 = new TMultiGraph("mg2", "Exclusion Limits vs Int Lumi;Int Lumi (pb^{-1});\\sigma*BR (pb)");
  TLegend *l2 = new TLegend(0.60,0.50,0.85,0.89,"");
  c2->SetLogy();
    
  TGraph* gmass[NMass];
  TLine* lxsec[NMass];
    
  tree1->Draw("Limit:Lumi", Form("Mass==%f", mass[2]), "goff");
  n = tree1->GetSelectedRows();
  gmass[2] = new TGraph(n, tree1->GetV1(), tree1->GetV2());       
  gmass[2]->SetLineColor(3);
  mg2->Add(gmass[2], "lp");
  l2->AddEntry(gmass[2],"W' 400 GeV", "L");

  tree1->Draw("Limit:Lumi", Form("Mass==%f", mass[3]), "goff");
  n = tree1->GetSelectedRows();
  gmass[3] = new TGraph(n, tree1->GetV1(), tree1->GetV2());       
  gmass[3]->SetLineColor(4);
  mg2->Add(gmass[3], "lp");
  l2->AddEntry(gmass[3],"W' 500 GeV", "L");

  tree1->Draw("Limit:Lumi", Form("Mass==%f", mass[4]), "goff");
  n = tree1->GetSelectedRows();
  gmass[4] = new TGraph(n, tree1->GetV1(), tree1->GetV2());       
  gmass[4]->SetLineColor(5);
  mg2->Add(gmass[4], "lp");
  l2->AddEntry(gmass[4],"W' 600 GeV", "L");

  tree1->Draw("Limit:Lumi", Form("Mass==%f", mass[5]), "goff");
  n = tree1->GetSelectedRows();
  gmass[5] = new TGraph(n, tree1->GetV1(), tree1->GetV2());       
  gmass[5]->SetLineColor(6);
  mg2->Add(gmass[5], "lp");
  l2->AddEntry(gmass[5],"W' 700 GeV", "L");

  tree1->Draw("Limit:Lumi", Form("Mass==%f", mass[6]), "goff");
  n = tree1->GetSelectedRows();
  gmass[6] = new TGraph(n, tree1->GetV1(), tree1->GetV2());       
  gmass[6]->SetLineColor(7);
  mg2->Add(gmass[6], "lp");
  l2->AddEntry(gmass[6],"W' 800 GeV", "L");

  tree1->Draw("Limit:Lumi", Form("Mass==%f", mass[7]), "goff");
  n = tree1->GetSelectedRows();
  gmass[7] = new TGraph(n, tree1->GetV1(), tree1->GetV2());       
  gmass[7]->SetLineColor(8);
  mg2->Add(gmass[7], "lp");
  l2->AddEntry(gmass[7],"W' 900 GeV", "L");

  mg2->Draw();
  //////////////////
  lxsec[2] = new TLine(0,xsec[2],500,xsec[2]); 
  lxsec[2]->SetLineColor(3);
  lxsec[2]->SetLineStyle(2);
  lxsec[2]->Draw("same");

  lxsec[3] = new TLine(300,xsec[3],1000,xsec[3]); 
  lxsec[3]->SetLineColor(4);
  lxsec[3]->SetLineStyle(2);
  lxsec[3]->Draw("same");
  
  lxsec[4] = new TLine(500,xsec[4],1500,xsec[4]); 
  lxsec[4]->SetLineColor(5);
  lxsec[4]->SetLineStyle(2);
  lxsec[4]->Draw("same");

  lxsec[5] = new TLine(1500,xsec[5],2500,xsec[5]); 
  lxsec[5]->SetLineColor(6);
  lxsec[5]->SetLineStyle(2);
  lxsec[5]->Draw("same");

  lxsec[6] = new TLine(3000,xsec[6],4000,xsec[6]); 
  lxsec[6]->SetLineColor(7);
  lxsec[6]->SetLineStyle(2);
  lxsec[6]->Draw("same");

  lxsec[7] = new TLine(4000,xsec[7],5000,xsec[7]); 
  lxsec[7]->SetLineColor(8);
  lxsec[7]->SetLineStyle(2);
  lxsec[7]->Draw("same");
   
  l2->SetTextSize(0.04);
  l2->SetBorderSize(0);
  l2->SetFillStyle(0);
  l2->Draw();
  
  /*
  gmass[2]->GetXaxis()->SetLimits(0,5000);
  gmass[2]->SetMinimum(0.9*xsec[NMass-1]);
  gmass[2]->SetMaximum(1.1*xsec[2]);
  gmass[2]->GetXaxis()->SetNdivisions(5);
  */

  c2->SaveAs("limitvsLumi.gif");
  c2->SaveAs("limitvsLumi.eps");

  //////Now plot Limit vs Int Lumi for TC//////////////////////

  TCanvas* c3 = new TCanvas("c3", "Limit vs Integrated Lumi");
  TMultiGraph* mg3 = new TMultiGraph("mg3", "Exclusion Limits vs Int Lumi;Int Lumi (pb^{-1});\\sigma*BR (pb)");
  TLegend *l3 = new TLegend(0.60,0.50,0.85,0.89,"");
  c3->SetLogy();
    
  TGraph* gmass_TC[NMass_TC];
  TLine* lxsec_TC[NMass_TC];
  /*
    gmass_TC[0] = new TGraph(NLumi, lumi, limit_massvslumi[0]);       
    gmass_TC[0]->SetLineColor(1);
    gmass_TC[0]->Draw("AL");
    gmass_TC[0]->SetTitle("Exclusion Limits vs Int Lumi;Int Lumi (pb^{-1});\\sigma*BR (pb)");
    l3->AddEntry(gmass[0],"\rho_{TC} 225 GeV", "L");
  */
  tree1->Draw("Limit:Lumi", Form("Mass==%f", mass[0]), "goff");
  n = tree1->GetSelectedRows();
  gmass_TC[1] = new TGraph(n, tree1->GetV1(), tree1->GetV2());       
  gmass_TC[1]->SetLineColor(2);
  mg3->Add(gmass_TC[1], "lp");
  l3->AddEntry(gmass_TC[1],"\\rho_{TC} 300 GeV", "L");

  tree1->Draw("Limit:Lumi", Form("Mass==%f", mass[0]), "goff");
  n = tree1->GetSelectedRows();
  gmass_TC[2] = new TGraph(n, tree1->GetV1(), tree1->GetV2());       
  gmass_TC[2]->SetLineColor(3);
  mg3->Add(gmass_TC[2], "lp");
  l3->AddEntry(gmass_TC[2],"\\rho_{TC} 400 GeV", "L");

  tree1->Draw("Limit:Lumi", Form("Mass==%f", mass[0]), "goff");
  n = tree1->GetSelectedRows();
  gmass_TC[3] = new TGraph(n, tree1->GetV1(), tree1->GetV2());       
  gmass_TC[3]->SetLineColor(4);
  mg3->Add(gmass_TC[3], "lp");
  l3->AddEntry(gmass_TC[3],"\\rho_{TC} 500 GeV", "L");

  mg3->Draw();
  /*
    lxsec_TC[0] = new TLine(0,xsec_TC[0],1000,xsec_TC[0]); 
    lxsec_TC[0]->SetLineColor(1);
    lxsec_TC[0]->SetLineStyle(2);
    lxsec_TC[0]->Draw("same");
  */
  lxsec_TC[1] = new TLine(0,xsec_TC[1],1000,xsec_TC[1]); 
  lxsec_TC[1]->SetLineColor(2);
  lxsec_TC[1]->SetLineStyle(2);
  lxsec_TC[1]->Draw("same");

  lxsec_TC[2] = new TLine(3000,xsec_TC[2],5000,xsec_TC[2]); 
  lxsec_TC[2]->SetLineColor(3);
  lxsec_TC[2]->SetLineStyle(2);
  lxsec_TC[2]->Draw("same");

  lxsec_TC[3] = new TLine(4000,xsec_TC[3],5000,xsec_TC[3]); 
  lxsec_TC[3]->SetLineColor(4);
  lxsec_TC[3]->SetLineStyle(2);
  lxsec_TC[3]->Draw("same");

  l3->SetTextSize(0.04);
  l3->SetBorderSize(0);
  l3->SetFillStyle(0);
  l3->Draw();
/*
  gmass_TC[1]->GetXaxis()->SetLimits(0,5000);
  gmass_TC[1]->SetMinimum(0.9*xsec_TC[NMass_TC-1]);
  gmass_TC[1]->SetMaximum(1.1*xsec_TC[0]);
  gmass_TC[1]->GetXaxis()->SetNdivisions(5);
*/
  c3->SaveAs("limitTCvsLumi.gif");
  c3->SaveAs("limitTCvsLumi.eps");

}
