from PhysicsTools.PatAlgos.patTemplate_cfg import *
from PhysicsTools.PatAlgos.tools.coreTools import *

from UserCode.CMSDAS_WZ_2012.patTuple_lep_cfg import *
from UserCode.CMSDAS_WZ_2012.patTuple_mc_cfg import *

# 2nd argument: message-logger frequency
# 3rd argument: # of events to process
lep_config(process, 1000, -1)
mc_config(process, cms)

process.p.replace(process.patMuons, process.muonMatch+process.patMuons+process.prunedGenParticles)
process.p.replace(process.patElectrons, process.electronMatch+process.patElectrons)

process.source.fileNames = [

    # 'file:/PATH/TO/FILE.root'
    'file:/home/fladias/WPrime/RSGravitonToZZToEEJJ_kMpl005_M_750_pythia6_cff_py_GEN_FASTSIM_HLT.root'
       
    ]
