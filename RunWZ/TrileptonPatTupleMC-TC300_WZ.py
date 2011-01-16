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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTupleMC-TC300_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_1.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_10.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_11.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_12.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_13.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_14.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_15.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_16.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_17.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_18.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_19.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_3.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_4.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_5.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_6.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_7.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_8.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-TC300/TrileptonPatTupleMC-V05-03-03-TC300_500events_9.root',
)))
