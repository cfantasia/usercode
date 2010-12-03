int
PlotLumi(){
    const int Nlumi = 7;
    const float lumi[Nlumi] = {200,400,600,800,1000,2000,5000};//inv pb

    //const int Nlumi = 2;
    //const float lumi[Nlumi] = {200,5000};//inv pb

    const int Nmass = 8;
    const float mass[Nmass] = {   225,        300,      400,      500,
                                  600,        700,     800,        900};//GeV
    const float K = 1.35;//K factor
    const float xsec[Nmass] = {K*0.6218, K*0.2756, K*0.0890, K*0.0360,  
                               K*0.0150,  K*0.0078,  K*0.0044,  K*0.0023};//pb
    const int Nmass_TC = 4;
    const float mass_TC[Nmass_TC] = {225,300,400,500};//GeV
    const float K_TC = 1.35;//K factor for TC
    const float xsec_TC    [Nmass_TC] = {K_TC*0.148066, K_TC*0.0448773, 
                                         K_TC*0.0129922, K_TC*0.00522783}; //pb low pi mass
//    const float xsec_TC[Nmass_TC] = {K_TC*0.1487, K_TC*0.06488, 
//                                         K_TC*0.02416, K_TC*0.01049}; //pb high pi mass


    ////////////
    float limit[Nlumi][Nmass] = {{0}};   
    float limit_massvslumi[Nmass][Nlumi] = {{0}};   

    //Cut and Paste NLO
    limit[0][0]=0.129617;
    limit_massvslumi[0][0]=0.129617;
    limit[1][0]=0.075211;
    limit_massvslumi[0][1]=0.075211;
    limit[2][0]=0.056690;
    limit_massvslumi[0][2]=0.056690;
    limit[3][0]=0.046762;
    limit_massvslumi[0][3]=0.046762;
    limit[4][0]=0.041001;
    limit_massvslumi[0][4]=0.041001;
    limit[5][0]=0.028877;
    limit_massvslumi[0][5]=0.028877;
    limit[6][0]=0.021636;
    limit_massvslumi[0][6]=0.021636;
    limit[0][1]=0.121485;
    limit_massvslumi[1][0]=0.121485;
    limit[1][1]=0.068244;
    limit_massvslumi[1][1]=0.068244;
    limit[2][1]=0.049978;
    limit_massvslumi[1][2]=0.049978;
    limit[3][1]=0.040682;
    limit_massvslumi[1][3]=0.040682;
    limit[4][1]=0.035134;
    limit_massvslumi[1][4]=0.035134;
    limit[5][1]=0.023422;
    limit_massvslumi[1][5]=0.023422;
    limit[6][1]=0.016609;
    limit_massvslumi[1][6]=0.016609;
    limit[0][2]=0.120760;
    limit_massvslumi[2][0]=0.120760;
    limit[1][2]=0.067583;
    limit_massvslumi[2][1]=0.067583;
    limit[2][2]=0.049378;
    limit_massvslumi[2][2]=0.049378;
    limit[3][2]=0.040102;
    limit_massvslumi[2][3]=0.040102;
    limit[4][2]=0.034573;
    limit_massvslumi[2][4]=0.034573;
    limit[5][2]=0.022906;
    limit_massvslumi[2][5]=0.022906;
    limit[6][2]=0.016099;
    limit_massvslumi[2][6]=0.016099;
    limit[0][3]=0.098008;
    limit_massvslumi[3][0]=0.098008;
    limit[1][3]=0.051722;
    limit_massvslumi[3][1]=0.051722;
    limit[2][3]=0.036100;
    limit_massvslumi[3][2]=0.036100;
    limit[3][3]=0.028215;
    limit_massvslumi[3][3]=0.028215;
    limit[4][3]=0.023438;
    limit_massvslumi[3][4]=0.023438;
    limit[5][3]=0.013768;
    limit_massvslumi[3][5]=0.013768;
    limit[6][3]=0.006477;
    limit_massvslumi[3][6]=0.006477;
    limit[0][4]=0.080419;
    limit_massvslumi[4][0]=0.080419;
    limit[1][4]=0.041679;
    limit_massvslumi[4][1]=0.041679;
    limit[2][4]=0.028671;
    limit_massvslumi[4][2]=0.028671;
    limit[3][4]=0.022138;
    limit_massvslumi[4][3]=0.022138;
    limit[4][4]=0.018188;
    limit_massvslumi[4][4]=0.018188;
    limit[5][4]=0.010205;
    limit_massvslumi[4][5]=0.010205;
    limit[6][4]=0.005305;
    limit_massvslumi[4][6]=0.005305;
    limit[0][5]=0.079934;
    limit_massvslumi[5][0]=0.079934;
    limit[1][5]=0.040843;
    limit_massvslumi[5][1]=0.040843;
    limit[2][5]=0.027776;
    limit_massvslumi[5][2]=0.027776;
    limit[3][5]=0.021223;
    limit_massvslumi[5][3]=0.021223;
    limit[4][5]=0.017269;
    limit_massvslumi[5][4]=0.017269;
    limit[5][5]=0.009306;
    limit_massvslumi[5][5]=0.009306;
    limit[6][5]=0.004448;
    limit_massvslumi[5][6]=0.004448;
    limit[0][6]=0.078534;
    limit_massvslumi[6][0]=0.078534;
    limit[1][6]=0.039670;
    limit_massvslumi[6][1]=0.039670;
    limit[2][6]=0.026640;
    limit_massvslumi[6][2]=0.026640;
    limit[3][6]=0.020153;
    limit_massvslumi[6][3]=0.020153;
    limit[4][6]=0.016255;
    limit_massvslumi[6][4]=0.016255;
    limit[5][6]=0.008407;
    limit_massvslumi[6][5]=0.008407;
    limit[6][6]=0.003658;
    limit_massvslumi[6][6]=0.003658;
    limit[0][7]=0.075739;
    limit_massvslumi[7][0]=0.075739;
    limit[1][7]=0.038128;
    limit_massvslumi[7][1]=0.038128;
    limit[2][7]=0.025567;
    limit_massvslumi[7][2]=0.025567;
    limit[3][7]=0.019306;
    limit_massvslumi[7][3]=0.019306;
    limit[4][7]=0.015537;
    limit_massvslumi[7][4]=0.015537;
    limit[5][7]=0.007979;
    limit_massvslumi[7][5]=0.007979;
    limit[6][7]=0.003408;
    limit_massvslumi[7][6]=0.003408;
    //////Now plot Limit vs Mass//////////////////////

    TCanvas* c1 = new TCanvas("c1", "Limit vs Mass");

    TLegend *legend = new TLegend(0.70,0.50,0.95,0.89,"");
    
    TGraph* gxsec_TC = new TGraph(Nmass_TC,mass_TC, xsec_TC);
    gxsec_TC->SetTitle("Exclusion Limits vs Mass;M_{WZ} (GeV);\\sigma*BR (pb)");
    gxsec_TC->SetLineStyle(2);
    gxsec_TC->Draw("AC");
    legend->AddEntry(gxsec_TC,"\\rho_{TC} \\sigma", "L");

    TGraph* gxsec = new TGraph(Nmass,mass, xsec);
    gxsec->Draw("C");
    legend->AddEntry(gxsec,"SSM W' \\sigma", "L");


    TGraph* glumi[Nlumi];
    c1->SetLogy();

    for(int i=0; i<Nlumi; ++i){
        glumi[i] = new TGraph(Nmass, mass, limit[i]);
        
        glumi[i]->SetLineColor(i+2);
        glumi[i]->Draw("L");

        legend->AddEntry(glumi[i],Form("%4.0f pb^{-1}",lumi[i]), "L");

    }
    legend->SetTextSize(0.04);
	legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->Draw();

    /*
    TLine* line = new TLine(520,0,520,c1->GetUymax()); //Fermilab limit
    line->SetLineStyle(9);
    line->Draw();
    TText *limitlabel = new TText();
    xlabel-> SetNDC();
    xlabel -> SetTextFont(1);
    xlabel -> SetTextColor(1);
    xlabel -> SetTextSize(0.03);
    xlabel -> SetTextAlign(22);
    xlabel -> SetTextAngle(0);
    xlabel -> DrawText(0.5, 0.04, "Fermilab Limit: 520 GeV");
    */

    gxsec_TC->GetXaxis()->SetLimits(200,900);
    gxsec_TC->SetMinimum(xsec[Nmass-1]);
    gxsec_TC->SetMaximum(xsec_TC[0]);

    c1->SaveAs("limitvsMass.gif");
    c1->SaveAs("limitvsMass.eps");

    //////Now plot Limit vs Int Lumi//////////////////////

    TCanvas* c2 = new TCanvas("c2", "Limit vs Integrated Lumi");
    TLegend *l2 = new TLegend(0.60,0.50,0.85,0.89,"");
    c2->SetLogy();
    
    float limit_massvslumi[Nmass][Nlumi] = {{0}};
    for(int i=0; i<Nlumi; ++i){
        for(int j=0; j<Nmass; ++j){
            limit_massvslumi[j][i] = limit[i][j];
        }
    }

    TGraph* gmass[Nmass];
    TLine* lxsec[Nmass];
    
    gmass[2] = new TGraph(2, lumi+0, limit_massvslumi[2]+0);       
    gmass[2]->SetLineColor(3);
    gmass[2]->Draw("AL");
    gmass[2]->SetTitle("Exclusion Limits vs Int Lumi;Int Lumi (pb^{-1});\\sigma*BR (pb)");
    l2->AddEntry(gmass[2],"W' 400 GeV", "L");

    gmass[3] = new TGraph(3, lumi+0, limit_massvslumi[3]+0);       
    gmass[3]->SetLineColor(4);
    gmass[3]->Draw("L");
    l2->AddEntry(gmass[3],"W' 500 GeV", "L");

    gmass[4] = new TGraph(2, lumi+3, limit_massvslumi[4]+3);       
    gmass[4]->SetLineColor(5);
    gmass[4]->Draw("L");
    l2->AddEntry(gmass[4],"W' 600 GeV", "L");

    gmass[5] = new TGraph(2, lumi+4, limit_massvslumi[5]+4);       
    gmass[5]->SetLineColor(6);
    gmass[5]->Draw("L");
    l2->AddEntry(gmass[5],"W' 700 GeV", "L");

    gmass[6] = new TGraph(2, lumi+5, limit_massvslumi[6]+5);       
    gmass[6]->SetLineColor(7);
    gmass[6]->Draw("L");
    l2->AddEntry(gmass[6],"W' 800 GeV", "L");

    gmass[7] = new TGraph(2, lumi+5, limit_massvslumi[7]+5);       
    gmass[7]->SetLineColor(8);
    gmass[7]->Draw("L");
    l2->AddEntry(gmass[7],"W' 900 GeV", "L");
//
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

    gmass[2]->GetXaxis()->SetLimits(0,5000);
    gmass[2]->SetMinimum(0.9*xsec[Nmass-1]);
    gmass[2]->SetMaximum(1.1*xsec[2]);
    gmass[2]->GetXaxis()->SetNdivisions(5);

    c2->SaveAs("limitvsLumi.gif");
    c2->SaveAs("limitvsLumi.eps");

    //////Now plot Limit vs Int Lumi for TC//////////////////////

    TCanvas* c3 = new TCanvas("c3", "Limit vs Integrated Lumi");
    TLegend *l3 = new TLegend(0.60,0.50,0.85,0.89,"");
    c3->SetLogy();
    
    TGraph* gmass_TC[Nmass_TC];
    TLine* lxsec_TC[Nmass_TC];
    /*
    gmass_TC[0] = new TGraph(Nlumi, lumi, limit_massvslumi[0]);       
    gmass_TC[0]->SetLineColor(1);
    gmass_TC[0]->Draw("AL");
    gmass_TC[0]->SetTitle("Exclusion Limits vs Int Lumi;Int Lumi (pb^{-1});\\sigma*BR (pb)");
    l3->AddEntry(gmass[0],"\rho_{TC} 225 GeV", "L");
    */
    gmass_TC[1] = new TGraph(2, lumi+1, limit_massvslumi[1]+1);       
    gmass_TC[1]->SetLineColor(2);
    gmass_TC[1]->Draw("AL");
    gmass_TC[1]->SetTitle("Exclusion Limits vs Int Lumi;Int Lumi (pb^{-1});\\sigma*BR (pb)");
    l3->AddEntry(gmass_TC[1],"\\rho_{TC} 300 GeV", "L");

    gmass_TC[2] = new TGraph(2, lumi+5, limit_massvslumi[2]+5);       
    gmass_TC[2]->SetLineColor(3);
    gmass_TC[2]->Draw("L");
    l3->AddEntry(gmass_TC[2],"\\rho_{TC} 400 GeV", "L");

    gmass_TC[3] = new TGraph(2, lumi+5, limit_massvslumi[3]+5);       
    gmass_TC[3]->SetLineColor(4);
    gmass_TC[3]->Draw("L");
    l3->AddEntry(gmass_TC[3],"\\rho_{TC} 500 GeV", "L");

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

    gmass_TC[1]->GetXaxis()->SetLimits(0,5000);
    gmass_TC[1]->SetMinimum(0.9*xsec_TC[Nmass_TC-1]);
    gmass_TC[1]->SetMaximum(1.1*xsec_TC[0]);
    gmass_TC[1]->GetXaxis()->SetNdivisions(5);

    c3->SaveAs("limitTCvsLumi.gif");
    c3->SaveAs("limitTCvsLumi.eps");

}
