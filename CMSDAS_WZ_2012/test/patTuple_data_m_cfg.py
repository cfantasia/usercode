from PhysicsTools.PatAlgos.patTemplate_cfg import *
from PhysicsTools.PatAlgos.tools.coreTools import *

from UserCode.CMSDAS_WZ_2012.patTuple_lep_cfg import *
from UserCode.CMSDAS_WZ_2012.patTuple_trigger_cfg import *

## remove MC matching from the default sequence when running on data
removeMCMatching(process, ['All'])

# 2nd argument: message-logger frequency
# 3rd argument: # of events to process
lep_config(process, 1000, -1)

addHLTFilter(process, 'HLT', "doublemu")

process.p.replace(process.patTrigger, process.patTrigger+process.hltFilter)

process.source.fileNames = [

    # 'file:/PATH/TO/FILE.root'
    '/store/data/Run2011B/DoubleMu/AOD/PromptReco-v1/000/180/075/ECC2702C-6A02-E111-BA36-003048F1182E.root'
    
       
    ]
