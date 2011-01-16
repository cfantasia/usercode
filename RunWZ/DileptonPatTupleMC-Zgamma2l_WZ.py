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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/DileptonPatTupleMC-Zgamma2l_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-06C0570E-6B46-DF11-97FD-0030487F1775.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-0E800852-7C46-DF11-82D2-0030487F1BD5.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-1CAC0D2B-6E46-DF11-A019-003048D4397E.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-2E96F631-6E46-DF11-BB3B-003048C69424.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-48341FE3-6D46-DF11-91B8-0030487F1BE5.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-54E7DC2E-6E46-DF11-8CBA-003048C69312.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-74338932-6B46-DF11-A862-003048C65E4A.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-7C77E4E2-6D46-DF11-8B4A-0030487DE7C1.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-AE137A2E-6E46-DF11-9965-0030487F1655.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-C0697410-6B46-DF11-971D-0030487D5DC3.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-CEDED62C-6E46-DF11-83F5-003048D436D2.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-E20D610D-6B46-DF11-ADC4-0030487E4ED5.root',
'/store/user/fantasia/38X/DileptonPatTupleMC-V05-03-03-Zgamma2l/DileptonPatTupleMC-V05-03-03-F8F8CD71-DE46-DF11-84AC-0030487F16BF.root',
)))
