from UserCode.CMSDAS_WZ_2012.patTuple_common_cfg import *

def el_config(process) :
    # event content to include all electrons within |eta|<2.5 with pt>10
    process.selectedPatElectrons.cut = "pt > 10. & abs(eta) < 2.5"
    
    process.selectedPatPFParticles.cut = "abs(pdgId())==11"
    process.out.outputCommands.append('keep *_selectedPatElectrons_*_*')
    
