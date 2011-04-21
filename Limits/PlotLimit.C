//Usage: root -l PlotLimit.C++

#include "consts.h"
int
GetEndPoints(int & start, int& end, Double_t* y, float line);

void
PlotLimit(){
  ////Load Trees////////
  TTree* tree1 = new TTree("tree1", "Limits");
  tree1->ReadFile("nLimit.txt");

  TTree* tXsec = new TTree("tXsec", "W' Cross Sections");
  tXsec->ReadFile("xSec.txt");

  TTree* tXsec_TC = new TTree("tXsec", "TC Cross Sections");
  tXsec_TC->ReadFile("xSec_TC.txt");

  //////Now Plot Limit vs Mass//////////////////////
  cout<<"Now Plot Limit vs Mass\n";
  TCanvas* c1 = new TCanvas("c1", "Exclusion Limit vs Mass");
  TMultiGraph *mg = new TMultiGraph("mg", "Exclusion Limits vs Mass;M_{WZ} (GeV);\\sigma BR (pb)");
  TLegend *legend = new TLegend(0.15,0.18,0.45,0.45,"");
  c1->SetLogy();
  int n=0;
  float* x; 
  float* y;

  TGraph* glumi[NLumi];
  TGraph* gData;
  cout<<"Drawing Limit Curves\n";
  for(int ilumi=0; ilumi<NLumi; ++ilumi){if(ilumi%2 == 1) continue;
    tree1->Draw("Mass:Limit", 
                Form("Lumi==%f && isData==0", Lumi[ilumi]), "goff");
    n = tree1->GetSelectedRows();
    glumi[ilumi] = new TGraph(n, tree1->GetV1(), tree1->GetV2());
    if(ilumi+2 <10) glumi[ilumi]->SetLineColor(ilumi+2);
    else        glumi[ilumi]->SetLineColor(ilumi+3);   
    mg->Add(glumi[ilumi], "C");
    legend->AddEntry(glumi[ilumi],Form("Exp Limit %4.0f pb^{-1}",Lumi[ilumi]), "L");
  }

  cout<<"Drawing W' Curve\n";
  tXsec->Draw("Mass:Xsec", "", "goff"); //Sel on W'
  n = tXsec->GetSelectedRows();
  x = new float[n]; y = new float[n];
  for(int i=0; i<n; ++i){
    x[i] = tXsec->GetV1()[i];
    y[i] = tXsec->GetV2()[i]*KFactor("Wprime");
  }
  TGraph* gxsec = new TGraph(n, x, y);
  mg->Add(gxsec,"l");
  legend->AddEntry(gxsec,"W' \\sigma", "L");
  delete x; delete y;
  /*//Don't show data for now
  tree1->Draw("Mass:Limit", "isData==1", "goff");
  n = tree1->GetSelectedRows();
  gData = new TGraph(n, tree1->GetV1(), tree1->GetV2());
  gData->SetMarkerStyle(kStar);
  mg->Add(gData, "P");
  legend->AddEntry(gData,"Actual Limit", "P");
  */
  
  cout<<"Drawing TC low Curve\n";
  tXsec_TC->Draw("Rho:Xsec", "Rho>=300 && Pi==Rho-100", "goff");//which pi mass? Sel on TC
  n = tXsec_TC->GetSelectedRows();
  x = new float[n]; y = new float[n];
  for(int i=0; i<n; ++i){
    x[i] = tXsec_TC->GetV1()[i];
    y[i] = tXsec_TC->GetV2()[i]*KFactor("TC");
  }
  TGraph* gxsec_TC_Low = new TGraph(n, x, y);
  gxsec_TC_Low->SetLineStyle(3);
  mg->Add(gxsec_TC_Low,"lp");
  legend->AddEntry(gxsec_TC_Low,"\\rho_{TC}^{Low}\\sigma", "L");
  delete x; delete y;
  

  cout<<"Drawing TC high Curve\n";
  tXsec_TC->Draw("Rho:Xsec", Form("Rho>=300 && Pi==Rho*3/4 - 25"), "goff");//which pi mass? Sel on TC
  n = tXsec_TC->GetSelectedRows();
  x = new float[n]; y = new float[n];
  for(int i=0; i<n; ++i){
    x[i] = tXsec_TC->GetV1()[i];
    y[i] = tXsec_TC->GetV2()[i]*KFactor("TC");
  }
  TGraph* gxsec_TC_High = new TGraph(n, x, y);
  gxsec_TC_High->SetLineStyle(2);
  mg->Add(gxsec_TC_High,"lp");
  legend->AddEntry(gxsec_TC_High,"\\rho_{TC} \\sigma", "L");
  delete x; delete y;
  
  cout<<"Drawing multigraph"<<endl;
  mg->Draw("a");
  
  cout<<"Drawing legend"<<endl;
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  //legend->SetNColumns(2);
  legend->Draw();

  //c1->SaveAs("limitvsMass.gif");
  c1->SaveAs("limitvsMass.eps");

  //////Now plot Limit vs Int Lumi//////////////////////
  cout<<"Now Plot Limit vs Lumi\n";
  TCanvas* c2 = new TCanvas("c2", "Limit vs Integrated Lumi");
  TMultiGraph* mg2 = new TMultiGraph("mg2", "Exclusion Limits vs Int Lumi;Int Lumi (pb^{-1});\\sigma \\cdot BR (pb)");
  TLegend *l2 = new TLegend(0.60,0.50,0.85,0.89,"");
  c2->SetLogy();
    
  TGraph* gmass[NMass];
  TLine* lxsec[NMass];

  for(int imass=0; imass<NMass; ++imass){
    tree1->Draw("Lumi:Limit", Form("Mass==%f && isData==0", Mass[imass]), "goff");
    n = tree1->GetSelectedRows();

    tXsec->Draw("Xsec", Form("Mass==%f", Mass[imass]), "goff");
    
    int start = 0;
    int end = n-1;
    n = GetEndPoints(start, end, tree1->GetV2(), tXsec->GetV1()[0]);

    lxsec[imass] = new TLine(0.9*tree1->GetV1()[start], tXsec->GetV1()[0], 1.1*tree1->GetV1()[end], tXsec->GetV1()[0]); 
    lxsec[imass]->SetLineColor(imass+1);
    lxsec[imass]->SetLineStyle(2);
    cout<<"start: "<<start<<" end: "<<end<<" size: "<<tree1->GetSelectedRows()<<endl;
    
    gmass[imass] = new TGraph(n, tree1->GetV1()+start, tree1->GetV2()+start);       
    gmass[imass]->SetLineColor(imass+1);
    mg2->Add(gmass[imass], "lp");
    l2->AddEntry(gmass[imass],Form("W' %i GeV", (int)Mass[imass]), "L");
  }

  mg2->Draw("a");
  //////////////////
  for(int imass=0; imass<NMass; ++imass){
    tXsec->Draw("Xsec", Form("Mass==%f", Mass[imass]), "goff");
    n = tree1->GetSelectedRows();
    lxsec[imass] = new TLine(0,tXsec->GetV1()[0],5000,tXsec->GetV1()[0]); 
    lxsec[imass]->SetLineColor(imass+1);
    lxsec[imass]->SetLineStyle(2);
    lxsec[imass]->Draw("same");
  }
   
  l2->SetTextSize(0.03);
  l2->SetBorderSize(0);
  l2->SetFillStyle(0);
  l2->SetNColumns(2);
  l2->Draw();
  
  /*
  gmass[2]->GetXaxis()->SetLimits(0,5000);
  gmass[2]->SetMinimum(0.9*xsec[NMass-1]);
  gmass[2]->SetMaximum(1.1*xsec[2]);
  gmass[2]->GetXaxis()->SetNdivisions(5);
  */

  //c2->SaveAs("limitvsLumi.gif");
  c2->SaveAs("limitvsLumi.eps");

  return;
}

int
GetEndPoints(int & start, int& end, Double_t* y, float line){
  for(int i=start; i<end; ++i){
    if(y[i] >= line && y[i+1] >= line) start = i+1;
  }
  start = TMath::Min(start, end-1);
  end   = TMath::Min(start+2, end);
  return end-start + 1;
}
