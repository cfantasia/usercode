import FWCore.ParameterSet.Config as cms

process = cms.Process("SKIM")

#process.load("FWCore.MessageService.MessageLogger_cfi")
#process.options = cms.untracked.PSet(
#    wantSummary = cms.untracked.bool(True)
#)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



#templist = open("f_events_path_180.txt","r").readlines()
templist = open("evtskim.txt","r").readlines()


mylist = []
for k in templist:
    mylist.append(k.rstrip())
  

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
	    'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_1_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_2_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_3_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_4_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_5_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_6_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_7_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_8_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_9_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_10_1.root',
        
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_11_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_12_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_13_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_14_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_15_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_16_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_17_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_18_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_19_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_20_1.root',

	    'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_21_1.root',
        'dcache:/pnfs/cms/WAX/11/store/user/fantasia/3_5_7/Wprime/ZeejetsPt0to15/PAT_22_1.root',
    ),                        
    eventsToProcess = cms.untracked.VEventRange(mylist)                          
)

process.load("Configuration.EventContent.EventContent_cff")
process.hltPoolOutput = cms.OutputModule("PoolOutputModule",
#    process.FEVTDEBUGHLTEventContent,
#    dataset = cms.untracked.PSet(
#        dataTier = cms.untracked.string('RECO')
#    ),
#    outputCommands = cms.untracked.vstring( 'drop *_*_*_*','keep FEDRawDataCollection_rawDataCollector_*_*'),
#    basketSize = cms.untracked.int32(4096),
    fileName = cms.untracked.string('file:Skim.root')
)
process.HLTOutput = cms.EndPath( process.hltPoolOutput)

