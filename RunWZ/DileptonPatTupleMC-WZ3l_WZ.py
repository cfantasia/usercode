import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("UserAnalysis.WZAnalysis.wzTreeMaker_cfi")

process.wzTreeMaker.numEventsNames = ['nEventsTotal',
                                      'nEventsHLT',
                                      'nEventsPat',
                                      'nEventsFiltered']

# Manage text output
process.MessageLogger.cerr.FwkReport.reportEvery = 50
process.MessageLogger.cerr.threshold = 'ERROR'
process.MessageLogger.cerr.default.limit = 3
process.wzTreeMaker.debug = False

# To run on data, change useMC to False in wzPat_cff.py.  That variable is
# in both this module and patAndFilter to choose between MC and data.

# Apply electron ID requirements for the bosons
process.wzTreeMaker.eidTypeZ = cms.untracked.string("")
process.wzTreeMaker.eidTypeW = cms.untracked.string("")

# Any branch whose name matches one of these perl-style regular expressions
# will not be generated in the ouput tree (use '.*' for wildcard)
process.wzTreeMaker.contentToDrop = ["jet.*"]
process.wzTreeMaker.contentToKeep = []

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.p = cms.Path(process.wzTreeMaker)
process.GlobalTag.globaltag = 'START38_V13::All'
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/DileptonPatTupleMC-WZ3l_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WZ3l/DileptonPatTupleMC-V05-03-03-364CC5F7-7055-DF11-A916-001E0B5A6396.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WZ3l/DileptonPatTupleMC-V05-03-03-44F498BB-0456-DF11-A938-0015C5E5B9C5.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WZ3l/DileptonPatTupleMC-V05-03-03-48A7E2B6-C354-DF11-A893-0022198266CB.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WZ3l/DileptonPatTupleMC-V05-03-03-5E9BF62B-9356-DF11-94EF-0022198273F0.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WZ3l/DileptonPatTupleMC-V05-03-03-641CC938-0556-DF11-8119-001E0B5A636C.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WZ3l/DileptonPatTupleMC-V05-03-03-7AF597DF-F154-DF11-85FA-001EC9B48F8D.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WZ3l/DileptonPatTupleMC-V05-03-03-94E1F2B8-D554-DF11-9B6F-0015C5E5B335.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WZ3l/DileptonPatTupleMC-V05-03-03-9E3047F9-C954-DF11-8505-001D09645B2D.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WZ3l/DileptonPatTupleMC-V05-03-03-C84F281A-0556-DF11-ADAD-002219826BD1.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WZ3l/DileptonPatTupleMC-V05-03-03-D80B63D7-0456-DF11-B1C5-001D09645B2D.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-WZ3l/DileptonPatTupleMC-V05-03-03-E2D16ADB-0556-DF11-971B-003048CF3ED4.root',
)))
