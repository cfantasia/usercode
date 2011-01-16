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
process.wzTreeMaker.outputFileName = '/uscms_data/d2/fantasia/38X/TrileptonPatTupleMC-ZZ_WZ.root'
process.source = cms.Source("PoolSource",
fileNames = cms.untracked.vstring(*(
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-000CF521-0047-DF11-A982-0017A477080C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-0EE766CC-FF46-DF11-AF31-0017A477080C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-3225B70F-0047-DF11-89CE-0017A4770424.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-3267D121-0047-DF11-B50E-001E0B5F5898.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-56187632-BB47-DF11-8D43-00237DA10D14.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-609DAB3B-BB47-DF11-B30E-0017A477000C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-66589F15-0047-DF11-9EB2-001E0B5F95B2.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-6660C4CF-FF46-DF11-B9CA-00237DA12CA0.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-688F760F-0047-DF11-98C8-001B78CE74FE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-709C7A5A-0047-DF11-915F-0017A4770434.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-8E62EC0E-0047-DF11-8CF4-00237DA1CD7E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-929C8931-BB47-DF11-AE6B-00237DA1680E.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-92B60417-0047-DF11-99EF-0017A4770408.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-96BA5B17-0047-DF11-8642-0017A4771008.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-A69EDAC2-FF46-DF11-BF38-0017A4770820.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-A82F925E-0047-DF11-B727-001B78CE74FE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-AEA03A0D-0047-DF11-A507-0017A4770424.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-B23AC20F-0047-DF11-A12A-001E0B48E92A.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-C2A91163-5F48-DF11-A6CE-001B78CE74FE.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-C4A4FA0F-0047-DF11-82C8-0017A4770434.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-DC7A8D20-0047-DF11-B10E-0017A477041C.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-E848442D-CB47-DF11-961B-0017A4770000.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-EEAF691B-0047-DF11-BFB6-0017A4771028.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-F0264422-0047-DF11-AB5F-0022649F01AA.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-F2B358BC-CB47-DF11-87A1-0017A4770C24.root',
'/store/user/fantasia/38X/TrileptonPatTupleMC-V05-03-03-ZZ/TrileptonPatTupleMC-V05-03-03-F6ACEB20-0047-DF11-9EB3-0017A4770028.root',
)))
