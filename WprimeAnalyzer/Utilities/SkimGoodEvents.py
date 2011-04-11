import FWCore.ParameterSet.Config as cms

process = cms.Process("SKIM")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

evtListFile = open("../candEvts.txt","r").readlines()
evtList = []
for k in evtListFile:
    evtList.append(k.rstrip())

fileListFile = open("fileList.txt","r").readlines()
fileList = []
for k in fileListFile:
    fileList.append(k.rstrip())

process.source = cms.Source("PoolSource",
     fileNames = cms.untracked.vstring(fileList),

#     fileNames = cms.untracked.vstring(
# '/store/data/Run2011A/SingleMu/AOD/PromptReco-v1/000/161/312/66095B41-0558-E011-9B2C-003048F118C6.root',
# '/store/data/Run2011A/SingleElectron/AOD/PromptReco-v1/000/161/312/90646AF9-F957-E011-B0DB-003048F118C4.root',
# '/store/data/Run2011A/SingleMu/AOD/PromptReco-v1/000/160/957/BCC3836A-5F55-E011-BB62-001617C3B70E.root',
# '/store/data/Run2011A/SingleElectron/AOD/PromptReco-v1/000/160/957/524EADA7-5456-E011-A192-001D09F251BD.root',
# '/store/data/Run2011A/SingleMu/AOD/PromptReco-v1/000/160/957/6009CA8F-5A55-E011-8226-000423D98B6C.root',
# '/store/data/Run2011A/SingleElectron/AOD/PromptReco-v1/000/160/957/644C60D7-A355-E011-8AEA-003048D375AA.root',
# '/store/data/Run2011A/SingleMu/AOD/PromptReco-v1/000/161/312/587F87B2-FA57-E011-B3AB-003048F0258C.root',
# '/store/data/Run2011A/SingleElectron/AOD/PromptReco-v1/000/161/312/90646AF9-F957-E011-B0DB-003048F118C4.root',
# '/store/data/Run2011A/SingleMu/AOD/PromptReco-v1/000/160/998/04099E04-BE55-E011-A9E6-001D09F2910A.root',
# '/store/data/Run2011A/SingleElectron/AOD/PromptReco-v1/000/160/998/2E032978-FA55-E011-A141-001617C3B6CC.root',
#     ),                        
    eventsToProcess = cms.untracked.VEventRange(evtList)                          
)

process.load("Configuration.EventContent.EventContent_cff")
process.hltPoolOutput = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('file:candEvts.root')
)
process.HLTOutput = cms.EndPath( process.hltPoolOutput)

