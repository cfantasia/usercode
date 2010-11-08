/* To Use: 
root -l LumiNeeded.C
*/
int
LumiNeeded(){

    gROOT->ProcessLine(".L cl95cms.c++");


    const int Nlumi = 7;
    const float lumi[Nlumi] = {200,400,600,800,1000,2000,5000};//inv pb

    const int Nmass = 8;
    const float mass[Nmass] = {   225,    300,    400,    500,      600,      700,   800,    900};//GeV
    const float xsec[Nmass] = {0.6218, 0.2756, 0.0890, 0.0360,  0.0150,  0.0078,  0.0044,   0.0023};//pb
    const float evts[Nmass] = {1.0155, 1.0155, 1.0155, 0.478205,0.287681,0.188414,0.0990156,0.0494355};
    const float eff [Nmass] = {0.1786, 0.1786, 0.1786, 0.1946,  0.2240,  0.2220,  0.2224,   0.2290};
    float deff[Nmass] = {0};
    
    const float mass_TC[4] = {225,300,400,500};//GeV
    const float K = 1.0;//1.35;//K factor for TC
    //const float xsec_TC[4] = {K*0.148066, K*0.0448773, K*0.0129922, K*0.00522783}; //pb low pi mass
    const float xsec_TC[4] = {K*0.1487, K*0.06488, K*0.02416, K*0.01049}; //pb high pi mass

    //Cory: should grab evts and eff from ExpectedEvents.C
    //deff only includes stat error (putting in factor of 10)

    float limit[Nlumi][Nmass] = {{0}};   
    for(int i=0; i<Nlumi; ++i){
        for(int j=0; j<Nmass; ++j){
            deff[j] = 10*sqrt(eff[j]*(1-eff[j])/10000);

            float norm_evts = evts[j] * lumi[i] / 1000;
            float snorm_evts = sqrt(norm_evts);

            printf("CLA(%4.2f,%4.2f,%4.4f,%4.4f,%4.2f,%4.2f)\n",
                   lumi[i], 0.1*lumi[i],
                   eff[j], deff[j],
                   norm_evts, snorm_evts);
            if(lumi[i] == 5000 && mass[j] == 500){
                limit[i][j] = 0.0064766;
            }else{ limit[i][j] = CLA(lumi[i], 0.1*lumi[i], 
                                     eff[j], deff[j],
                                     norm_evts, snorm_evts);
            }
            cout<<"For mass "<<mass[j]<<" lumi: "<<lumi[i]<<" inv pb we exclude xsec of "<<limit[i][j]<<" pb"<<endl<<endl;;
            
        }
    }
    
    cout<<"Done!"<<endl;
    for(int j=0; j<Nmass; ++j){
        for(int i=0; i<Nlumi; ++i){

            float norm_evts = evts[j] * lumi[i] / 1000;
            float snorm_evts = sqrt(norm_evts);

            printf("For Mass %4i: CLA(%5.1f,%5.1f,%6.4f,%6.4f,%4.2f,%4.2f) = %5.3f\n",
                   mass[j],
                   lumi[i], 0.1*lumi[i],
                   eff[j], deff[j],
                   norm_evts, snorm_evts,
                   limit[i][j]);

        }
    }

    TCanvas* c1 = new TCanvas("c1", "Limits");

    TLegend *legend = new TLegend(0.60,0.50,0.85,0.89,"");
    
    TGraph* gxsec_TC = new TGraph(4,mass_TC, xsec_TC);
    gxsec_TC->SetTitle("Exclusion Limits vs Int Lumi;M_{WZ} (GeV);xsec*BR (pb)");
    gxsec_TC->SetLineStyle(9);
    gxsec_TC->Draw("AC");
    legend->AddEntry(gxsec_TC,"TC xsec", "L");

    TGraph* gxsec = new TGraph(Nmass,mass, xsec);
    gxsec->Draw("C");
    legend->AddEntry(gxsec,"SSM W' xsec", "L");


    TGraph* glumi[Nlumi];
    c1->SetLogy();

    for(int i=0; i<Nlumi; ++i){
        glumi[i] = new TGraph(Nmass, mass, limit[i]);
        
        glumi[i]->SetLineColor(i+2);
        glumi[i]->Draw("L*");

        legend->AddEntry(glumi[i],Form("%4.0f inv pb",lumi[i]), "L");

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

    c1->SaveAs("limit.gif");
    c1->SaveAs("limit.eps");

    return 0;
}
