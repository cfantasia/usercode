#ifndef _ExecuteCuts_cxx_
#define _ExecuteCuts_cxx_

#include "ExecuteCuts.h"

/////////////////Cuts///////////////////////
//Trigger requirements
//-----------------------------------------------------------
bool PassTriggersCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Trigger requirements"<<endl;

    return ( PassMuonTriggerCut() || PassElecTriggerCut() );

}//--- PassTriggersCut()

bool PassElecTriggerCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Electron Trigger requirements"<<endl;

    return ((prescale_HLT_Photon10_L1R == 1                     && pass_HLT_Photon10_L1R) ||
            (prescale_HLT_Photon10_Cleaned_L1R == 1             && pass_HLT_Photon10_Cleaned_L1R) ||
            (prescale_HLT_Photon15_L1R == 1                     && pass_HLT_Photon15_L1R) ||
            (prescale_HLT_Photon15_Cleaned_L1R == 1             && pass_HLT_Photon15_Cleaned_L1R) ||
            (prescale_HLT_Ele10_LW_EleId_L1R == 1               && pass_HLT_Ele10_LW_EleId_L1R ) ||
            (prescale_HLT_Ele10_SW_EleId_L1R == 1               && pass_HLT_Ele10_SW_EleId_L1R) ||
            (prescale_HLT_Ele10_SW_L1R == 1                     && pass_HLT_Ele10_SW_L1R) ||
            (prescale_HLT_Ele12_SW_EleIdIsolNoDEtaInEE_L1R == 1 && pass_HLT_Ele12_SW_EleIdIsolNoDEtaInEE_L1R ) ||
            (prescale_HLT_Ele12_SW_TightEleIdIsol_L1R == 1      && pass_HLT_Ele12_SW_TightEleIdIsol_L1R ) ||
            (prescale_HLT_Ele12_SW_TighterEleIdIsol_L1R_v1 == 1    && pass_HLT_Ele12_SW_TighterEleIdIsol_L1R_v1  ) ||
            (prescale_HLT_Ele15_LW_L1R == 1                     && pass_HLT_Ele15_LW_L1R ) ||
            (prescale_HLT_Ele15_SW_L1R == 1                     && pass_HLT_Ele15_SW_L1R ) ||
            (prescale_HLT_Ele17_SW_TighterEleIdIsol_L1R_v2 == 1    && pass_HLT_Ele17_SW_TighterEleIdIsol_L1R_v2 )
        );


}//--- PassElecTriggersCut()

bool PassMuonTriggerCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Muon Trigger requirements"<<endl;

    return ((prescale_HLT_Mu9     == 1 && pass_HLT_Mu9)     ||
            (prescale_HLT_Mu11    == 1 && pass_HLT_Mu11)    ||
            (prescale_HLT_Mu15_v1 == 1 && pass_HLT_Mu15_v1)
        );

}//--- PassMuonTriggersCut

//Check if there are valid W and Z particles in the event
//-----------------------------------------------------------
bool PassValidWandZCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check if there are valid W and Z particles in the event"
                    <<endl;
//Cory: We can expand this (maybe in lepton cuts)
//Cory: Should this be here?
    bool has_valid_W_and_Z = Z_flavor 
        && W_flavor;
//        && WZ_invMassMinPz>0; 
    return has_valid_W_and_Z;
    
}//--- NotValidWandZCut

//Check if there is more Zs than required
//-----------------------------------------------------------
bool PassNumberOfZsCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check if there is more Zs than required"<<endl;

    bool passnumZs = maxNumZs >= numberOfZs;
    return passnumZs;

}//--- NumberOfZsCut

//Check W decay Properties
//-----------------------------------------------------------
bool 
PassWDecayCut(){
    switch(W_flavor){
    case PDGMUON:
        return PassWmunuCut();
        break;
    case PDGELEC:
        return PassWenuCut();
        break;
    default:
        cout<<"W Didn't decay to electron or muon!"<<endl;
        break;
    }
    return false;
}

//Check Z decay Properties
//-----------------------------------------------------------
bool 
PassZDecayCut(){
    if(!PassZmassCut()) return false;

    switch(Z_flavor){
    case PDGMUON:
        return PassZmumuCut();
        break;
    case PDGELEC:
        return PassZeeCut();
        break;
    default:
        cout<<"Z Didn't decay to electron or muon!"<<endl;
        break;
    }
    return false;
}

//Check Wenu decay Properties
//-----------------------------------------------------------
bool 
PassWenuCut(){
    bool inEC = inEndCap(electron_ScEta->at(W_leptonIndex));
    if(!PassElecEtCut         (W_leptonIndex,PDGW)) return false;
    if(!PassElecTrkRelIsoCut  (W_leptonIndex,inEC)) return false;
    if(!PassElecECalRelIsoCut (W_leptonIndex,inEC)) return false;
    if(!PassElecHCalRelIsoCut (W_leptonIndex,inEC)) return false;

    return true;
}

//Check Wmunu decay Properties
//-----------------------------------------------------------
bool 
PassWmunuCut(){
    if(!PassMuonPtCut        (W_leptonIndex,PDGW)) return false;
    if(!PassMuonCombRelIsoCut(W_leptonIndex)) return false;
    
    return true;
}

//Check Zee decay Properties
//-----------------------------------------------------------
bool 
PassZeeCut(){
    int idx;
    for(int i=0; i!=2; ++i){
        if(i==0) idx = Z_leptonIndex1;
        else     idx = Z_leptonIndex2;
        
        if(!PassElecEtCut         (idx,PDGZ)) return false;
    }
    return true;
}

//Check Zmumu decay Properties
//-----------------------------------------------------------
bool 
PassZmumuCut(){
    int idx;
    for(int i=0; i!=2; ++i){
        if(i==0) idx = Z_leptonIndex1;
        else     idx = Z_leptonIndex2;

        if(!PassMuonPtCut       (idx,PDGZ)) return false; 
    }
    return true;
}

bool PassElecEtCut(int idx,int parent){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron Et Cut"<<endl;

    if      (parent == 0){
        return (electron_ScEt->at(idx) > minElecEt);
    }else if      (parent == PDGW){
        return (electron_ScEt->at(idx) > minWenuEt);
    }else if(parent == PDGZ){
        return (electron_ScEt->at(idx) > minZeeEt);
    }
    return false;
}//--- PassElecEtCut

bool PassElecEtaCut(int idx){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron Eta Cut"<<endl;
    float eta = electron_ScEta->at(idx);
    return (inBarrel(eta) || inEndCap(eta));
}//--- PassElecEtaCut

bool PassElecTrkRelIsoCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron ElecTrkRelIso Cut"<<endl;
    return ((electron_trackIso->at(idx)/electron_pt->at(idx))
            < maxWenuTrkRelIso[inEC]);

}//--- PassElecTrkRelIsoCut

bool PassElecECalRelIsoCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron EcalRelIso Cut"<<endl;
    return ((electron_ecaloIso->at(idx)/electron_pt->at(idx))
                  < maxWenuECalRelIso[inEC]);

}//--- PassElecEcalRelIsoCut

bool PassElecHCalRelIsoCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron HcalRelIso Cut"<<endl;
    return ((electron_hcaloIso->at(idx)/electron_pt->at(idx))
            < maxWenuHCalRelIso[inEC]);
}//--- PassHcalRelIsoElecCut

bool PassElecSigmaEtaEtaCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron Sigma nn Cut"<<endl;
    return (electron_sigmaEtaEta->at(idx) < maxElecSigmaEtaEta[inEC]);
}//--- PassElecSigmaEtaEtaCut

bool PassElecDeltaPhiCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron dPhi Cut"<<endl;
    return (electron_deltaPhiIn->at(idx) < maxElecDeltaPhiIn[inEC]);
}//--- PassElecDeltaPhiCut

bool PassElecDeltaEtaCut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron dEta Cut"<<endl;
    return (electron_deltaEtaIn->at(idx) < maxElecDeltaEtaIn[inEC]);
}//--- PassElecDeltaEtaCut

bool PassElecHOverECut(int idx,bool inEC){
//-----------------------------------------------------------
    if(debugme) cout<<"Check Electron HOverE Cut"<<endl;
    return (electron_hOverE->at(idx) < maxElecHOverE[inEC]);
}//--- PassElecHOverECut

///////////////////////////
////Muon Cuts//////////////
///////////////////////////
//--------------------------
bool PassMuonTypeCut(int idx){
    if(debugme) cout<<"Check Muon Type Cut"<<endl;
    return (muon_isGlobal->at(idx) ); 
}//--- PassMuonTypeCut

bool PassMuonNpixhitCut(int idx){
    if(debugme) cout<<"Check Muon NpixhitCut"<<endl;
    return (muon_globalNpixelHits->at(idx) > minMuonNPixHit);
}//--- PassMuonNpixhitCut

bool PassMuonNtrkhitCut(int idx){
    if(debugme) cout<<"Check Muon NtrkhitCut"<<endl;
    return (muon_globalNtrackerHits->at(idx) > minMuonNTrkHit);
}//--- PassMuonNtrkhitCut

bool PassMuonNormChi2Cut(int idx){
    if(debugme) cout<<"Check Muon Chi2 Cut"<<endl;
    return ((muon_globalChi2->at(idx)/muon_globalNdof->at(idx) )
            < maxMuonNormChi2);
}//--- PassMuonChi2Cut

bool PassMuonHitsUsedCut(int idx){
    //Num Valid Muon Hits
    if(debugme) cout<<"Check Muon Hits Used Cut"<<endl;
    return (muon_numValidMuonHits->at(idx) > minMuonHitsUsed);
}//--- PassMuonHits Used Cut

bool PassMuonStationsCut(int idx){
    if(debugme) cout<<"Check Muon Stations Cut"<<endl;
    return (muon_numGlobalMatches->at(idx) > minMuonStations);
}//--- PassMuonStationsCut

bool PassMuonEtaCut(int idx){
    if(debugme) cout<<"Check Muon Eta Cut"<<endl;
    return (fabs(muon_eta->at(idx)) < maxMuonEta);
}//--- PassMuonEta Cut

bool PassMuonPtCut(int idx,int parent){
    if(debugme) cout<<"Check Muon Pt Cut"<<endl;
    if      (parent == 0){
        return (muon_pt->at(idx) > minMuonPt);
    }else if      (parent == PDGW){
        return (muon_pt->at(idx) > minWmunuMuonPt);
    }else if(parent == PDGZ){
        return (muon_pt->at(idx) > minZmumuMuonPt);
    }
    return false;
}//--- PassMuonPtCut

bool PassMuonCombRelIsoCut(int idx){
    if(debugme) cout<<"Check Muon CombRelIso Cut"<<endl;
    return ( Calc_MuonRelIso(idx) < maxWmunuCombRelIso);
}//--- PassMuonCombRelIsoCut

float 
Calc_MuonRelIso(int idx){

    if(muon_trackIso == 0 || muon_caloIso == 0) return 999;

    return (muon_trackIso->at(idx) + 
            muon_caloIso->at(idx) ) /
        muon_pt->at(idx);
}//--- Calc_MuonRelIso

bool PassMuonDxyCut(int idx){
    //Use: muon_globalD0
    if(debugme) cout<<"Check Muon Dxy Cut"<<endl;
    return (muon_globalD0->at(idx) < maxMuonDxy);
}//--- PassMuonDxyCut

////////////////////////////////

//Check Z Properties

bool PassZmassCut(){
    if(debugme) cout<<"Check Zmass Cut"<<endl;
    return (Z_mass > minZmass && Z_mass < maxZmass);
}//--- PassZmassCut



//Check Z pt
//-----------------------------------------------------------
bool PassZptCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check Z pt"<<endl;
    
    if(Z_pt < minZpt) return false;
    
    return true;

}//--- PassZptCut

//Check W pt
//-----------------------------------------------------------
bool PassWptCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check W pt"<<endl;

    if(W_pt < minWpt) return false;
    
    return true;

}//--- PassWptCut

//Check Ht Properties
//-----------------------------------------------------------
bool PassHtCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check Ht Cuts"<<endl;
   
    return Ht > minHt;
    
}//--- PassHtCut

//Calc Ht
//-----------------------------------------------------------
float Calc_Ht()
{
    float Ht=0;
  
    if     (W_flavor == PDGELEC) Ht += electron_pt->at(W_leptonIndex);
    else if(W_flavor == PDGMUON) Ht += muon_pt->at(W_leptonIndex);
    //else                         cout<<"W didn't decay into e,mu"<<endl;

    if     (Z_flavor == PDGELEC){
		Ht += electron_pt->at(Z_leptonIndex1);
		Ht += electron_pt->at(Z_leptonIndex2);
    }else if(Z_flavor == PDGMUON){
		Ht += muon_pt->at(Z_leptonIndex1);
		Ht += muon_pt->at(Z_leptonIndex2);
    }//else                         cout<<"Z didn't decay into e,mu"<<endl;

    return Ht;

}//--- CalcHt

//Check Ht Met Properties
//-----------------------------------------------------------
bool PassHtMetCut()
{
//-----------------------------------------------------------
    if(debugme) cout<<"Check Ht Cuts"<<endl;
    float Ht=0;
  
    if     (W_flavor == PDGELEC) Ht += electron_pt->at(W_leptonIndex);
    else if(W_flavor == PDGMUON) Ht += muon_pt->at(W_leptonIndex);
    else                         cout<<"W didn't decay into e,mu"<<endl;

    if     (Z_flavor == PDGELEC){
	Ht += electron_pt->at(Z_leptonIndex1);
	Ht += electron_pt->at(Z_leptonIndex2);
    }else if(Z_flavor == PDGMUON){
	Ht += muon_pt->at(Z_leptonIndex1);
	Ht += muon_pt->at(Z_leptonIndex2);
    }else                         cout<<"Z didn't decay into e,mu"<<endl;

    Ht += pfMet_et;
    
    return Ht > minHtMet;
    
}//--- PassHtMetCut

//MET Cut
//-----------------------------------------------------------
bool PassMETCut()
{
    return pfMet_et > minMET;
}//--- MET Cut

//Pass Tight Cut
//-----------------------------------------------------------
bool PassTightCut(int idx, int flavor)
{
    if(flavor == 11){
        bool inEC = inEndCap(electron_ScEta->at(idx));
        if(!PassElecEtCut         (idx,PDGW)) return false;
        if(!PassElecTrkRelIsoCut  (idx,inEC)) return false;
        if(!PassElecECalRelIsoCut (idx,inEC)) return false;
        if(!PassElecHCalRelIsoCut (idx,inEC)) return false;

    }else if (flavor == 13){
        if(!PassMuonPtCut(idx, PDGW)) return false;
        if(!PassMuonCombRelIsoCut(idx)) return false;
    }
    return true;
}//--- Tight Cut

float Calc_GenWZInvMass()
{
    int pdg=0, pdgM=0;
    int idZ=-1;
    int idW=-1;    
    int size = genMother_pdgId->size();
    for(int i=0; i != size; i++){
        pdg = abs(genParticle_pdgId->at(i));
        pdgM = abs(genMother_pdgId->at(i));
        if (pdgM == PDGWPRIME){
            return genMother_mass->at(i);
        }
        if( pdg == PDGZ && pdgM != PDGZ){
            idZ = i;
        }
        if( pdg == PDGW && pdgM != PDGW){
            idW = i;
        }
        
        if( abs(genParticle_pdgId->at(i)) == PDGZ && pdg > 50){
            cout<<"Mother of Z is "<<pdg<<endl;
        }
    }
    if(idZ != -1 && idW != -1){
        float E = genParticle_energy->at(idZ)+genParticle_energy->at(idW);
        float PX = genParticle_px->at(idZ)+genParticle_px->at(idW);
        float PY = genParticle_py->at(idZ)+genParticle_py->at(idW);
        float PZ = genParticle_pz->at(idZ)+genParticle_pz->at(idW);
        float m = sqrt(E*E - PX*PX - PY*PY - PZ*PZ);
        /*
          cout<<"E:"<<E
          <<" PX:"<<PX
          <<" PY:"<<PY
          <<" PZ:"<<PZ
          <<" Mass calc is "<<m<<endl;
        */
        return m;
             
    }
    return -1;
    
}//--- Calc Gen Inv Mass

//See if Electron is in Barrel
bool inBarrel(float eta)
{
    return (fabs(eta) < maxElecEtaBarrel);
}//InBarrel

bool inEndCap(float eta)
{
    float abs_eta = fabs(eta);
    return (abs_eta > minElecEtaEndcap && abs_eta < maxElecEta);         
}//InEndCap

#endif//#define _ExecuteCuts_h_
