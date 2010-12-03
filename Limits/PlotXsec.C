{
    TCanvas* c1 = new TCanvas("c1");
    TTree* tree1 = new TTree("tree1", "Xsec");
    tree1->ReadFile("Xsec.dat","rho/I:pi/I:eh/I:xsec/F");

    TTree* tree2 = new TTree("tree2", "Limits");
    tree2->ReadFile("Limits.dat","lumi/I:rho/I:limit/F");

    TH2F* hist = new TH2F("hist", "Xsec;Rho;Pi;Xsec (pb)", 13, 200, 525, 15, 100, 475);
    TH1F* hlimit = new TH1F("hlimit", "Xsec;Rho;Xsec (pb)", 13, 200, 525);

    tree1->Draw("pi:rho>>hist", "10^9*xsec", "goff");
    tree2->Draw("rho>>hlimit", "limit*(lumi==1000)", "goff");
    hist->Draw("text");
    //hlimit->Draw();
    c1->SetLogz();


    
    

    
}
