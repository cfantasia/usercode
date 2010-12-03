/* To Use: 
root -l LumiNeeded.C
*/
int
LumiNeeded(){

    gROOT->ProcessLine(".L cl95cms.c++");

    
    //const int Nlumi = 7;
    //const float lumi[Nlumi] = {200,400,600,800,1000,2000,5000};//inv pb

    const int Nlumi = 2;
    const float lumi[Nlumi] = {200,5000};//inv pb

    const int Nmass = 8;
    const float mass[Nmass] = {   225, 300, 400, 500,
                                  600, 700, 800, 900};
    const float K = 1.35;//1.35;//K factor
    const float xsec[Nmass] = {K*0.6218, K*0.2756, K*0.0890, K*0.0360,  
                               K*0.0150, K*0.0078, K*0.0044, K*0.0023};//pb
    ////////////
    /*
    const float evts[Nmass]  = {1.65,  1.09,  1.04,  0.39,  //LO
                                0.23,  0.14,  0.05,  0.04};
    const float sevts[Nmass] = {1.28,  1.04,  1.01,  0.63,  //LO
                                0.48,  0.37,  0.23,  0.21};
    */
    const float evts[Nmass]  = {2.65,  1.75,  1.67,  0.60,  //NLO
                                0.37,  0.21,  0.08,  0.06}; 
    const float sevts[Nmass] = {1.63,  1.32,  1.29,  0.78,  //NLO 
                                0.61,  0.46,  0.28,  0.25};

    ///////////
    const float eff [Nmass] = {0.1786,    0.1786,   0.1786,   0.1946, 
                               0.2240,    0.2220,    0.2224,  0.2290};
    float deff[Nmass] = {0};
    
    const int Nmass_TC = 4;
    const float mass_TC[Nmass_TC] = {225,300,400,500};//GeV
    const float K_TC = 1.35;//K factor for TC
    //const float xsec_TC[Nmass_TC] = {K_TC*0.148066, K_TC*0.0448773, K_TC*0.0129922, K_TC*0.00522783}; //pb low pi mass
    const float xsec_TC[Nmass_TC] = {K_TC*0.1487, K_TC*0.06488, K_TC*0.02416, K_TC*0.01049}; //pb high pi mass

    //Cory: should grab evts and eff from ExpectedEvents.C
    //deff only includes stat error (putting in factor of 10)
    string outfile("lumiNeeded.txt");
    ofstream out(outfile.c_str());
    if(!out) { 
      cout << "Cannot open file " << outfile << endl; 
      abort();
    } 

    float limit[Nlumi][Nmass] = {{0}};   
    for(int i=0; i<Nlumi; ++i){
        for(int j=0; j<Nmass; ++j){
            deff[j] = 10*sqrt(eff[j]*(1-eff[j])/10000);

            float norm_evts  =  evts[j] * lumi[i] / 1000;
            float snorm_evts = sevts[j] * lumi[i] / 1000;

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

            out<<mass[j]<<"\t"
               <<lumi[i]<<"\t"
               <<0.1*lumi[i]<<"\t"
               <<eff[j]<<"\t"
               <<deff[j]<<"\t"
               <<norm_evts<<"\t"
               <<snorm_evts<<"\t"
               <<limit[i][j]<<"\t"
               <<endl;

            printf("For Mass %4i: CLA(%5.1f,%5.1f,%6.4f,%6.4f,%4.2f,%4.2f) = %5.3f\n",
                   mass[j],
                   lumi[i], 0.1*lumi[i],
                   eff[j], deff[j],
                   norm_evts, snorm_evts,
                   limit[i][j]);

        }
    }

    for(int j=0; j<Nmass; ++j){
        for(int i=0; i<Nlumi; ++i){

            printf("limit[%i][%i]=%f;\n",i,j,limit[i][j]);
            printf("limit_massvslumi[%i][%i]=%f;\n",j,i,limit[i][j]);
        }
    }

    out.close(); 

    return 0;
}
