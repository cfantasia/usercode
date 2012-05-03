import FWCore.ParameterSet.Config as cms

process = cms.Process("SKIM")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

#List of events to be skimmed with format run:lumi:evt or maybe even run:event
templist = open("evtskim.txt","r").readlines()

mylist = []
for k in templist:
    mylist.append(k.rstrip())
  

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
	    'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_1_1.root',
      'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_2_1.root',
    ),                        
    eventsToProcess = cms.untracked.VEventRange(mylist)                          
)

process.load("Configuration.EventContent.EventContent_cff")
process.hltPoolOutput = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('file:Skim.root')
)
process.HLTOutput = cms.EndPath( process.hltPoolOutput)

