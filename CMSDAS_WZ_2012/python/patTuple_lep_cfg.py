from UserCode.CMSDAS_WZ_2012.patTuple_common_cfg import *
from UserCode.CMSDAS_WZ_2012.patTuple_mc_cfg import *
from UserCode.CMSDAS_WZ_2012.patTuple_el_cfg import *
from UserCode.CMSDAS_WZ_2012.patTuple_mu_cfg import *
from UserCode.CMSDAS_WZ_2012.patTuple_met_cfg import *

def lep_config(process, reportEveryNum=100, maxEvents=-1) :
    common_config(process, reportEveryNum, maxEvents)
    el_config(process)
    mu_config(process)
    met_config(process)
    
    # redefine selectedPatMuons (isGlobalMuon not included in std definition)
    process.selectedPatMuons.cut = "pt > 10. & abs(eta) < 2.4 & isGlobalMuon"
    
    from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector
    process.goodOfflinePrimaryVertices = cms.EDFilter(
        "PrimaryVertexObjectFilter",
        filterParams = pvSelector.clone( minNdof = cms.double(4.0), maxZ = cms.double(24.0) ),
        src=cms.InputTag('offlinePrimaryVertices')
        )
    
    ## let it run
    process.p = cms.Path(
        process.patMuons *
        process.selectedPatMuons *
        process.patElectrons *
        process.selectedPatElectrons *
        process.goodOfflinePrimaryVertices*
        process.patTrigger *
        process.patTriggerEvent *
        process.patMETsPF
        )
    #Keep NVtxs
    process.out.outputCommands.append('keep *_offlinePrimaryVertices_*_*')
    
    process.patJetCorrFactors.rho = cms.InputTag("kt6PFJetsPFlow", "rho")
    process.out.outputCommands.append('keep *_kt6PFJetsPFlow_*_PAT')

             
