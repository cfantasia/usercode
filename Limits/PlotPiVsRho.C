int
PlotPiVsRho(){
    //////Now plot Limit vs Int Lumi//////////////////////

    TCanvas* c2 = new TCanvas("c2", "Limit");
    TLegend *l2 = new TLegend(0.20,0.50,0.45,0.89,"");
    
    float x[] = {225,250,275,300,325,350,375};
    float y[] = {120,140,170,190,225,270,5000};

    TGraph* gmass = new TGraph(7, x, y);       
    gmass->SetLineColor(4);
    gmass->SetFillColor(4);
    gmass->SetLineWidth(2002);
    gmass->SetFillStyle(3004);
    gmass->Draw("AL");
    l2->AddEntry(gmass,"\\rho_{TC} Limit", "L");

    TLine* lxsec = new TLine(180,100,400,320); 
    lxsec->SetLineStyle(1);
    lxsec->Draw("same");
    l2->AddEntry(lxsec,"\\rho_{TC} \\rightarrow \\piW Threshold", "L");

    TLine* lpi = new TLine(200,100,400,200); 
    lpi->SetLineStyle(2);
    lpi->Draw("same");
    l2->AddEntry(lpi,"\\rho_{TC} \\rightarrow \\pi\\pi Threshold", "L");

    l2->SetTextSize(0.04);
    l2->SetBorderSize(0);
    l2->SetFillStyle(0);
    l2->Draw();

    gmass->GetXaxis()->SetLimits(180,400);
    gmass->SetMinimum(100);
    gmass->SetMaximum(350);
    //gmass->GetXaxis()->SetNdivisions(5);

    c2->SaveAs("pivsrho.gif");
    c2->SaveAs("pivsrho.eps");

}
