from UserCode.CMSDAS_WZ_2012.patTuple_common_cfg import *

def mu_config(process) :

    # event content to include all muons within |eta|<2.4 with pt>10
    process.selectedPatMuons.cut = "pt > 10. & abs(eta) < 2.4"

    process.selectedPatPFParticles.cut = "abs(pdgId())==13"
    process.out.outputCommands.append('keep *_selectedPatMuons_*_*')
    
